# 05 — WDT and Safety Design

## WDT Configuration

SAMC21 WDT peripheral. Clocked from 32.768 kHz internal oscillator (1 kHz WDT clock). Timeout: ~250ms.

Harmony V3 MCC generates WDT init. Configured in MCC UI with `WDT_Initialize()`. Manual clearing via `WDT_Clear()`.

```c
// Init (before scheduler):
WDT_Initialize();   // 250ms timeout from MCC config

// Clear (called periodically):
WDT_Clear();        // writes 0xA5 to CLEAR register
```

## Heartbeat Method

Five tasks, four heartbeats. DEBUG_TASK excluded (cannot deadlock — only blocks on `xQueueReceive`).

```c
// File: src/app/app_state.h (declared), src/app/app_state.c (defined)
volatile uint32_t g_heartbeat_can         __attribute__((aligned(4)));
volatile uint32_t g_heartbeat_tmc4671     __attribute__((aligned(4)));
volatile uint32_t g_heartbeat_tmc2209     __attribute__((aligned(4)));
volatile uint32_t g_heartbeat_supervisor  __attribute__((aligned(4)));

volatile uint32_t * const g_heartbeat_array[4] = {
    &g_heartbeat_can,
    &g_heartbeat_tmc4671,
    &g_heartbeat_tmc2209,
    &g_heartbeat_supervisor
};
```

### Per-Task Increment

Each task increments its counter at the **end** of its main loop iteration:

```c
// In TMC4671_TASK loop:
g_heartbeat_tmc4671++;

// In CAN_GATEKEEPER loop:
g_heartbeat_can++;

// In TMC2209_TASK loop:
g_heartbeat_tmc2209++;

// In SUPERVISOR_TASK loop:
g_heartbeat_supervisor++;
```

### Supervisor Check (Every 50ms)

```c
static uint32_t prev_hb[4] = {0};
bool all_alive = true;

for (int i = 0; i < 4; i++) {
    uint32_t current = *g_heartbeat_array[i];
    if (current == prev_hb[i]) {
        all_alive = false;
        break;   // this task has stopped incrementing
    }
    prev_hb[i] = current;
}

if (all_alive) {
    WDT_Clear();
}
// else: let WDT timeout → system reset
```

### Thread Safety of Heartbeat Counters

- Each counter is written by exactly ONE task (no concurrent writers)
- Read by SUPERVISOR_TASK (one reader, one writer per counter)
- `uint32_t` aligned read/write on Cortex-M0+ is single-instruction atomic (LDR/STR)
- Worst case: SUPERVISOR reads a counter mid-increment → uses old value → heartbeat detected as "alive" one cycle later. Harmless.
- No mutex, no critical section, no FreeRTOS API — just raw globals

## Failure Detection Latency

| Failure | Detection Time | Mechanism |
|---------|---------------|-----------|
| TMC4671_TASK hangs | 50ms + 250ms → reset | SUPERVISOR sees stale heartbeat → stops petting WDT |
| CAN_GATEKEEPER hangs | Same | Same |
| TMC2209_TASK hangs | Same | Same |
| SUPERVISOR_TASK hangs | 250ms → reset | WDT timeout (nobody pets it) |
| DEBUG_TASK hangs | Not detected | Can't deadlock — only blocks on queue receive |
| All tasks alive but CAN stuck | Not detected by WDT | Host times out on CAN replies → physical watchdog |
| Kernel crash (hard fault) | 250ms → reset | WDT timeout |
| Stack overflow | AS SOON AS IT HAPPENS | `configCHECK_FOR_STACK_OVERFLOW = 2` — hook can directly trigger reset or stop petting WDT |

## Why Not Event Groups?

- Event groups require `xEventGroupSetBits()` in every task + `xEventGroupWaitBits()` in supervisor
- Heartbeat counters are simpler: globals + WDT write, no RTOS objects
- Less RAM (16 bytes vs ~80 bytes for event group)
- Directly readable in debugger — useful during development
- No FromISR variant needed (heartbeats only incremented in task context)

## Init-Time WDT Service (Before Scheduler)

Long init operations manually clear WDT:

```c
void init_sequence(void) {
    WDT_Initialize();   // Harmony PLIB — WDT_Clear() called from src/app/supervisor/supervisor_task.c post-scheduler

    // After flash sector erase (~100ms):
    ext_flash_sector_erase(addr);       // src/app/drivers/ext_flash/ext_flash.c
    WDT_Clear();

    // After TMC4671 SPI retry loop:
    for (int i = 0; i < 50; i++) {
        chip_id = tmc4671_readInt(MOTOR, CHIPINFO_DATA);
        if (chip_id == 0x34363731) break;
        WDT_Clear();
    }

    // After open-loop alignment (~1-2s):
    run_Open_Loop_Setup_Closed_Loop(50);
    WDT_Clear();

    // After TMC2209 init (multiple UART writes):
    init_tmc2209_motors();
    WDT_Clear();
}
```

## g_flash_busy Safety Flag

When SUPERVISOR holds the SERCOM3 mutex for flash operations, motor tasks must not start moves that require limit detection during the flash window.

```c
// File: src/app/app_state.h / .c
extern volatile bool g_flash_busy;

// Set by SUPERVISOR (src/app/supervisor/supervisor_task.c) when it acquires g_m_sercom3
// Cleared when it releases the mutex

// Checked by TMC4671_TASK (src/app/motor_4671/motor_4671_task.c) before starting homing:
if (g_flash_busy && cmd.type == CMD_HOMING_START) {
    send_error(cmd.can_id, ERR_FLASH_BUSY);
    return;
}

// Checked by TMC2209_TASK before starting guide motor moves:
if (g_flash_busy && motor == MOTOR_GUIDE && is_move_command(cmd)) {
    send_error(cmd.can_id, ERR_FLASH_BUSY);
    return;
}
```

Flash writes only occur during idle (no motor moving), so `g_flash_busy` is a safety net, not a common code path. In practice it's rarely true during motion.

## Stack Overflow Detection

```c
// File: src/app/app_state.c (FreeRTOSConfig.h)
#define configCHECK_FOR_STACK_OVERFLOW  2
```

FreeRTOS fills task stacks with `0xA5` at creation and checks the watermark at every context switch. The stack overflow hook fires BEFORE corruption occurs:

```c
// File: main.c (FreeRTOS hook — must be defined at global scope)
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // Log which task overflowed (if debug is still alive)
    // Then sit here and let WDT reset the system
    taskDISABLE_INTERRUPTS();
    for (;;) { /* WDT fires -> reset */ }
}
```
