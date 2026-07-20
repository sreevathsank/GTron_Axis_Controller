# Codebase Review & Remediation Plan

**Date:** 28 January 2026
**Project:** GTron IO Controller Firmware
**Current Rating:** 4.5/10 (Hobbyist Grade)

---

## 1. Critical Stability Issues (High Priority)
*These issues pose immediate risks of system crashes, lockups, or undefined behavior.*

### 1.1 Debug Logging Inside ISRs
**File:** `@IOCtrl1.X/interrupt_callbacks.c`
**Problem:** You are calling `SYS_DEBUG_MESSAGE` inside Interrupt Service Routines (e.g., `run_Button_Interrupt_Callback`).
**Why it's bad:** Printing usually involves blocking UART transmission or complex formatting logic. ISRs must execute as fast as possible. Blocking inside an ISR prevents other interrupts from firing and can cause stack overflows if the logging function uses too much stack.
**Remediation:**
Set a flag or send a notification to a task to handle the logging.

**Bad:**
```c
void run_Button_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Run Button Pressed!\n"); // <--- CRITICAL ERROR
    // ...
}
```

**Good:**
```c
void run_Button_Interrupt_Callback( unsigned int val )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // Just set the event bit. The task handling this bit can print the log.
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_RUN_BUTTON_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
```

### 1.2 Misuse of Scheduler Suspension (`vTaskSuspendAll`)
**File:** `@src/system_state.c`
**Problem:** Wrapping `LED_Show_DMA()` calls inside `vTaskSuspendAll()`.
**Why it's bad:** DMA (Direct Memory Access) operates independently of the CPU. Suspending the RTOS scheduler does *not* pause or protect the DMA hardware. It only prevents other software tasks from running. This destroys the multitasking capability of your system for no gain.
**Remediation:**
Remove `vTaskSuspendAll()`. If you need to ensure two tasks don't write to the LED buffer at the same time, use a **Mutex**.

**Bad:**
```c
vTaskSuspendAll();
{
    LED_SetPixel(LED_STRIP_LENGTH - 1, 0, 0, 255);
    LED_Show_DMA();
}
xTaskResumeAll();
```

**Good:**
```c
// Assuming xLedMutex was created earlier
if (xSemaphoreTake(xLedMutex, portMAX_DELAY) == pdTRUE) {
    LED_SetPixel(LED_STRIP_LENGTH - 1, 0, 0, 255);
    LED_Show_DMA();
    xSemaphoreGive(xLedMutex);
}
```

### 1.3 Busy Waiting in Tasks
**File:** `@src/led_driver.c`
**Problem:** Using `while (DMAC_ChannelIsBusy(DMAC_CHANNEL_0));` and `delay_cycles(15000);` inside a task.
**Why it's bad:** This is "Polling." You are keeping the CPU active at 100% usage just waiting for hardware or time to pass. In an RTOS, this starves lower-priority tasks and wastes power.
**Remediation:**
1. Use `vTaskDelay` for the reset signal.
2. Use a **Binary Semaphore** for DMA completion. Register a DMA Interrupt Callback that gives the semaphore, and have the `LED_Show_DMA` function block (take) the semaphore.

**Refactored Logic:** 
```c
void LED_Show_DMA(void)
{
    // 1. Reset Signal: Let other tasks run while we wait
    vTaskDelay(pdMS_TO_TICKS(1)); // Approx 1ms wait

    // ... Prepare Buffer ...

    // 2. Start Transfer
    DMAC_ChannelTransfer(...);

    // 3. Block until ISR says it's done
    xSemaphoreTake(xDmaDoneSemaphore, portMAX_DELAY);
}
```

---

## 2. Architectural & Structural Issues
*These issues make the code hard to maintain, test, and expand.*

### 2.1 The "God Header" (`all_headers.h`)
**File:** `@IOCtrl1.X/all_headers.h`
**Problem:** A single header file includes every other header, and every source file includes this one.
**Why it's bad:** 
1. **Compilation Time:** Changing one macro in `custom_macros.h` forces the *entire project* to recompile.
2. **Coupling:** Files have access to definitions they don't need, making dependencies spaghetti-like.
**Remediation:**
Delete `all_headers.h`. In every `.c` file, include *only* the specific `.h` files that are actually used in that file.

### 2.2 Project Folder Hygiene
**File:** `@IOCtrl1.X/init_funcs.c`, `@IOCtrl1.X/interrupt_callbacks.c`, etc.
**Problem:** Source code files are located inside the MPLAB X IDE configuration folder (`IOCtrl1.X`).
**Why it's bad:** The `.X` folder is for IDE project settings (Makefiles, XML configurations). Source code belongs in `src/`.
**Remediation:**
Move the following files to `src/` and update project paths:
*   `init_funcs.c/h`
*   `interrupt_callbacks.c/h`
*   `global_vars.c/h`
*   `custom_macros.h`

### 2.3 Global Variable Exposure
**File:** `@IOCtrl1.X/global_vars.c`
**Problem:** Critical RTOS handles (`xbtn_state_event_grp`, `xcan_rd_wr_queue`) are global variables.
**Why it's bad:** Any part of the code can corrupt these handles or the data within them. It makes unit testing impossible because dependencies aren't injected.
**Remediation:**
Declare these as `static` inside the module that owns them. Provide "Getter" functions or wrapping API calls if other modules need to interact with them.

---

## 3. Design & Protocol Optimization
*Issues related to efficiency and software design choices.*

### 3.1 String-Based Protocol
**File:** `@src/cmd_parser.c`
**Problem:** You are parsing ASCII strings (e.g., "ATRUN", "ATPAU") to control the board.
**Why it's bad:** 
1. **Slow:** `memcmp` and string searching consume significant CPU cycles.
2. **Bandwidth:** Sending 5 bytes ("ATRUN") is 5x more data than sending 1 byte (e.g., `0x02`).
3. **Complexity:** You need complex lookups tables.
**Remediation:**
Switch to a binary protocol.
*   `0x01`: Run
*   `0x02`: Pause
*   `0x03`: Stop
This removes the entire string parsing logic and replaces it with a simple `switch(byte)` statement.

### 3.2 Implicit State Priorities
**File:** `@src/system_state.c`
**Problem:** You iterate through `bit_map[]` to determine the next state.
**Why it's bad:** If multiple bits are set (e.g., RUN and STOP), the priority is determined purely by the order in the array. This is "implicit" behavior.
**Remediation:**
Make priority explicit in the code logic. Check for critical errors (FAIL state) first, then Stop, then Pause, then Run.

---

## 4. Code Style & "Smells" 

### 4.1 Non-Standard Macros
**File:** `@IOCtrl1.X/custom_macros.h`
**Problem:** `#define ever (;;)`
**Why it's bad:** It forces other developers to look up what `ever` means. It's "cute" code, not professional code.
**Remediation:** Use standard C: `for(;;)` or `while(1)`.

### 4.2 Dead Code (Graveyards)
**File:** `@src/cmd_parser.c`, `@src/led_driver.c`
**Problem:** Large blocks of commented-out code (Binary search logic, black pixel fix).
**Why it's bad:** It clutters the file and confuses readers. "Is this referenced? Do I need this?"
**Remediation:** Delete it. Git history remembers it if you need it back.

### 4.3 Fragile Delays
**File:** `@src/led_driver.c`
**Problem:** `__asm__ volatile("nop; ...")`
**Why it's bad:** If you change the clock speed or compiler optimization level, these delays will change, breaking your LED timing.
**Remediation:** Since you are moving to SPI/DMA, delete the bit-banging code entirely. It is obsolete.
