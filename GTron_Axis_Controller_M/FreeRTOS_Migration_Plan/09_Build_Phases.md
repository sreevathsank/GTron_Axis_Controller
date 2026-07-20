# 09 — Build Phases

Five phases, each producing a buildable binary. Commit at the start of each phase as rollback point.

---

## Phase 1: Project Creation & MCC Configuration

**Goal:** New project compiles. MCC generates all peripheral init. FreeRTOS boots.

### Steps

1. **Create MPLAB X project:**
   - File → New Project → Microchip Embedded → Standalone Project
   - Device: `ATSAMC21N18A`
   - Tool: Select your debugger/programmer (e.g., PICkit, Atmel-ICE)
   - Compiler: XC32 (ARM GCC)
   - Project name and location

2. **Launch MCC:**
   - Tools → Embedded → MPLAB Code Configurator
   - Accept Harmony V3 framework
   - Load required components (SAMC21 DFP, CMSIS, Harmony Core)

3. **Configure peripherals in MCC UI** per document 07 checklist:
   - Clock tree (4 GCLKs)
   - SERCOM0 (SPI, 2 MHz)
   - SERCOM3 (SPI, 50 kHz)
   - SERCOM5 (UART, 230400 baud)
   - SERCOM7 (UART, 2 Mbaud)
   - TC0 (1 MHz, free-running)
   - TC1 (25 MHz PWM)
   - TC2 (1ms timer with interrupt)
   - TC4 (1ms timer with interrupt)
   - CAN1 (500 kbps with interrupt)
   - EIC (EXTINT 5, 10, 12, 13)
   - ADC0 (Ch9)
   - DMAC (Ch0, SERCOM7 TX trigger)
   - GPIO (all pins)

4. **Add FreeRTOS component** via MCC → configure per document 07 checklist

5. **Generate code:** Click Generate in MCC

6. **Add FreeRTOS kernel source files** to project (MCC may auto-add, verify):
   - `FreeRTOS/Source/tasks.c`
   - `FreeRTOS/Source/queue.c`
   - `FreeRTOS/Source/list.c`
   - `FreeRTOS/Source/portable/GCC/ARM_CM0/port.c`

7. **Add a minimal main.c:**
   ```c
   #include "definitions.h"   // MCC-generated master header
   #include "FreeRTOS.h"
   #include "task.h"

   int main(void) {
       SYS_Initialize();   // MCC-generated: all peripherals, clocks, GPIO

       // Temporary: verify boot
       for (;;) {
           // Toggle LED, verify board is alive
       }
   }
   ```

8. **Build:** Project → Build. Fix any compilation errors.

### Verification
- [ ] MCC generates without errors
- [ ] Project compiles with zero warnings
- [ ] Flash to board → boot messages on debug UART (if wired) or LED toggles

---

## Phase 2: Port Drivers & Strip Dead Code

**Goal:** All drivers and application code ported. Dead code removed. System initializes in the same way as old project but under the new Harmony build.

### Steps

1. **Create the directory structure** per document 10 module tree:
   ```
   src/app/
   ├── app_config.h / app_state.h / app_state.c
   ├── can/
   ├── motor_4671/
   ├── motor_2209/
   ├── supervisor/
   ├── debug/
   └── drivers/
       ├── tmc4671/
       ├── tmc2209/
       ├── io_expander/
       └── ext_flash/
   ```

2. **Port drivers** (copy from old project → adapt → integrate):
   - Copy TMC4671, TMC2209, flash, IOXP driver files
   - Copy CAN protocol headers (IMM_CAN_Message_Id.h → can_protocol.h)
   - Copy ramp math (Motion.c/h → motor_4671/)
   - Copy hybrid trigger (Hybrid_Trigger.c/h → motor_4671/)
   - Copy TLV flash (tlv_flash.c/h → supervisor/)
   - Copy debug transport (dbg_transport.c/h → debug/)
   - Copy Motor_Info_t struct + parser (gtron_can_cmd_parser.c/h → can/)

3. **Adapt low-level API calls:** Replace Atmel Start function bodies with Harmony PLIB equivalents (see doc 08 adaptation notes). Keep the function names.

4. **Create split global header files:**
   - `app_state.h`: ISR-shared flags, RTOS handles, `axis_id`, `sbridge_addr`, `Motor_Info_t` externs
   - `motor_4671_internal.h`: ramp params, limit vars, hybrid state, motion globals
   - `motor_2209_internal.h`: step counter, IOXP state, TMC2209 globals
   - `can_state.h`: busy flags, queue handles
   - `supervisor_internal.h`: heartbeats, LED state

5. **Create `app_state.c`** — instance definitions for all externs in `app_state.h`

6. **Implement init sequence** in `main()` (before scheduler):
   ```c
   int main(void) {
       SYS_Initialize();           // MCC generated
       WDT_Initialize();

       // Ported init from old project (call_All_Init_Functions equivalent):
       //  - TC1 PWM start (25 MHz for TMC4671)
       //  - TMC4671 reset + SPI verify
       //  - GPIO defaults (LEDs on, CS high)
       //  - SERCOM5 UART init (for TMC2209)
       //  - ADC axis ID read
       //  - External flash init + TLV read
       //  - IOXP init
       //  - read_Set_Parameters_From_Flash()
       //  - TMC4671 init + open-loop alignment
       //  - TMC2209 motor init
       //  - Motor struct init (mot_array[])
       //  - EIC callback registration
       // WDT_Clear() after long operations

       // (Tasks created in Phase 3)
       for (;;);  // placeholder
   }
   ```

7. **Build and verify:**
   - Fix all compilation errors
   - Verify init completes (LED sequence, debug prints)
   - Verify TMC4671 responds to SPI (chip ID read)
   - Verify flash reads TLV parameters
   - Disable interrupts during this phase if ISR code is incomplete

### Verification
- [ ] Project compiles with ported driver code
- [ ] Init sequence runs to completion
- [ ] TMC4671 chip ID verified over SPI
- [ ] Debug prints work via DMA transport
- [ ] No hard fault during init

---

## Phase 3: Task Implementation (Bottom-Up)

**Goal:** All 5 FreeRTOS tasks implemented. Scheduler running. No superloop.

Build each task layer starting from the lowest priority. Each sub-step adds one task and verifies it works.

### 3a. DEBUG_TASK (Priority 0)

1. Create `g_q_debug` in `app_state.c`
2. Implement `vDebug_Task` (see doc 02)
3. Update `DBG_Printf` to use `xQueueSend(g_q_debug, buf, 0)`
4. Create task: `xTaskCreateStatic(vDebug_Task, "DBG", ...)`
5. **Test:** `DBG_Printf` from main() → message appears on debug UART

### 3b. SUPERVISOR_TASK (Priority 1)

1. Create `g_q_sup_rx`, `g_m_sercom3` in `app_state.c`
2. Create heartbeat globals in `app_state.c`
3. Implement `vSupervisor_Task` (see doc 02)
4. Create task: `xTaskCreateStatic(vSupervisor_Task, "SUP", ...)`
5. **Test:** Supervisor prints heartbeat debug messages, WDT is petted

### 3c. TMC2209_TASK (Priority 2)

1. Create `g_q_2209_rx` in `app_state.c`
2. Create `motor_2209_internal.h` with step counter, IOXP state
3. Implement `vTMC2209_Task` (see doc 02)
4. Wire TC2 ISR: `vTaskNotifyGiveFromISR(h_2209, &woken)`
5. Wire IOXP_INT ISR: `vTaskNotifyGiveFromISR(h_2209, &woken)` + `g_ioxp_int_pending = true`
6. Wire DIAG ISR: `g_diag_pending = true` (flag only)
7. Start TC2 timer
8. Create task: `xTaskCreateStatic(vTMC2209_Task, "2209", ...)`
9. **Test:** Task blocks on notify. TC2 ISR wakes it → prints debug confirmation. DIAG flag detected.

### 3d. CAN_GATEKEEPER (Priority 3)

**Source:** Ported from IO_Ctrl_Master FreeRTOS project with bug fixes.

1. Create `g_q_can_work`, `g_q_4671_rx`, `g_q_2209_rx`, `g_q_sup_rx`, busy flags in `app_state.c`
2. Copy CAN functions from IO_Ctrl_Master:
   - `CAN1_Read()` + `CAN1_Write()` from `IO_Ctrl_Master/src/can.c`
   - `CAN1_RxFifo0Callback` / `CAN1_RxFifo1Callback` / `CAN1_TxFifoCallback` from `IO_Ctrl_Master/IOCtrl1.X/interrupt_callbacks.c`
   - `CAN_Cmd_Parser_t`, `CAN_Rx_Fifo_CB_Info`, `Can1MessageRAM[]` from `IO_Ctrl_Master/IOCtrl1.X/global_vars.c/h`
3. Apply bug fixes (see doc 03): `woken = pdFALSE`, local `can_frame_t` on ISR stack, non-blocking dispatch, remove `canData` state machine, static allocation
4. Register CAN callbacks (Harmony PLIB) in init: `CAN1_RxFifoCallbackRegister(...)`
5. Implement `vCAN_Gatekeeper_Task` (see doc 02/03) — single-hop dispatch (no parser task)
6. Create task: `xTaskCreateStatic(vCAN_Gatekeeper_Task, "CAN", ...)`
7. **Test:** Send CAN frame from external tool -> dispatched to motor queue -> debug print confirms routing

**Files created/modified in this phase:**

| Operation | File | Contents |
|-----------|------|----------|
| CREATE | `src/app/can/can_isr_callbacks.c` | `CAN1_RxFifo0Callback`, `CAN1_RxFifo1Callback`, `CAN1_TxFifoCallback` (ported from `IO_Ctrl_Master/IOCtrl1.X/interrupt_callbacks.c`) |
| CREATE | `src/app/can/can_isr_callbacks.h` | Declarations for 3 CAN callbacks |
| CREATE | `src/app/can/can_gatekeeper.c` | `vCAN_Gatekeeper_Task` + `CAN1_Read()` + `CAN1_Write()` + util functions (ported from `IO_Ctrl_Master/src/can.c`) |
| CREATE | `src/app/can/can_state.h` | `can_cmd_t`, `CAN_Cmd_Parser_t`, `CAN_Rx_Fifo_CB_Info`, `g_4671_busy`, `g_2209_busy`, `can_cmd_parse_info` extern |
| CREATE | `src/app/can/can_state.c` | Instance defs: `can_cmd_parse_info`, `can1_rx_fifo0_cb_info`, `can1_rx_fifo1_cb_info`, `Can1MessageRAM[]`, busy flags |
| CREATE | `src/app/can/can_protocol.h` | `can_union_type`, `can_frame_t`, `can_direction_t`, CAN ID macros (ported from old `IMM_CAN_Message_Id.h`) |
| CREATE | `src/app/motor_4671/limit_isr.c` | `right_Limit_Interrupt_Callback`, `left_Limit_Interrupt_Callback` |
| CREATE | `src/app/motor_2209/stepper_isr.c` | `ioxp_Interrupt_Callback`, `diag_Interrupt_Callback` |
| CREATE | `src/app/eic_init.c` | `EIC_Init()` — registers all 4 EIC callbacks via `EIC_CallbackRegister()` |
| MODIFY | `src/app/app_state.h` | Add externs: `g_q_can_work`, `g_q_4671_rx`, `g_q_2209_rx`, `g_q_sup_rx`, `g_limit_flags`, `g_ioxp_int_pending`, `g_diag_pending`, `g_flash_busy`, `g_heartbeat_*`, `h_*`, `g_m_sercom3` |
| MODIFY | `src/app/app_state.c` | Add static buffers: `qbuf_can_work[]`, `qbuf_4671_rx[]`, `qbuf_2209_rx[]`, `qbuf_sup_rx[]`, all control blocks, instance defs for heartbeat counters and ISR flags |
| MODIFY | `main.c` | Add: CAN1 init (message RAM + callback registration), static queue creation, task creation for all 5 tasks, `EIC_Init()` call, `vTaskStartScheduler()` |

### 3e. TMC4671_TASK (Priority 4)

1. Create `motor_4671_internal.h` with ramp params, limit vars, motion globals
2. Implement `vTMC4671_Task` (see doc 02)
3. Wire TC4 ISR: `vTaskNotifyGiveFromISR(h_4671, &woken)`
4. Wire LIM_RT, LIM_LFT ISRs: `g_limit_flags |= BIT` (no notification)
5. Start TC4 timer
6. Create task: `xTaskCreateStatic(vTMC4671_Task, "4671", ...)`
7. **Test:** Task processes 1ms ticks, ramp math runs (verify via debug), hybrid trigger fires camera GPIO

### 3f. Replace Placeholder Loop

1. Remove `for (;;);` from main()
2. Add `vTaskStartScheduler();` at the end of main()
3. Add `for (;;);` after `vTaskStartScheduler()` (never reached, but prevents compiler warning)
4. `main()` code after this is unreachable

### Verification
- [ ] All 5 tasks created and scheduler running
- [ ] DEBUG_TASK drains queue
- [ ] SUPERVISOR_TASK pets WDT
- [ ] TMC2209_TASK polls MSCNT, detects DIAG
- [ ] CAN_GATEKEEPER receives and dispatches frames
- [ ] TMC4671_TASK runs ramp, hybrid trigger, limits
- [ ] Heartbeat counters incrementing in all 4 monitored tasks
- [ ] No stack overflow (check watermarks)

---

## Phase 4: Integration & Timing Verification

**Goal:** All subsystems integrated. Timing verified. Edge cases handled.

### Test Cases

| # | Test | Method | Accept Criteria |
|---|------|--------|----------------|
| 1 | CAN round-trip latency | Send GET_POSITION from external CAN tool → measure reply time | ≤2ms |
| 2 | Ramp 1ms period | Scope on GPIO toggle in `run_S_ramp_step()` | 1ms ± 25us |
| 3 | Move arbitration | Send two simultaneous MOVE commands | Second rejected with BUSY |
| 4 | Busy flag clears on completion | Wait for move done → send new move | New move accepted immediately |
| 5 | Hybrid trigger fires camera | Enable inspection mode → pulse LIM_LFT → scope on REELER_INT | Camera pulse at correct position interval |
| 6 | Hybrid slip detection | Vary step size by >10% → verify slip reported via CAN | CAN error frame sent |
| 7 | Hybrid N-shot auto-disable | Enable N-shot mode → let it complete | Hybrid mode auto-disabled, motor paused |
| 8 | REELER limit stop | Drive motor into LIM_RT (or jumper) | Motor stops within 1ms |
| 9 | GUIDE limit stop | Trigger IOXP GPIO limit input | Motor stops within 11ms |
| 10 | DIAG stall detection | Mechanically stall TMC2209 motor | DIAG detected, motor stopped, CAN error sent |
| 11 | Flash busy blocks moves | Start flash sector erase → attempt homing | Rejected with ERR_FLASH_BUSY |
| 12 | Flash busy during ongoing move | Start flash erase while move in progress → IOXP read skipped | Motor completes (no false limit trigger) |
| 13 | CAN gatekeeper queue never overflows | Send CAN messages at max bus rate for 10 seconds | No dropped messages, all dispatched correctly |
| 14 | WDT fires on hung task | (Test build only) Insert infinite loop in TMC4671_TASK | System resets within ~250ms |

### Stack Watermark Check

```c
// After running all features at max load:
DBG_Printf(ERR_LVL_INFO, "Stack free: 4671=%u CAN=%u 2209=%u SUP=%u DBG=%u\n",
    uxTaskGetStackHighWaterMark(h_4671),
    uxTaskGetStackHighWaterMark(h_can),
    uxTaskGetStackHighWaterMark(h_2209),
    uxTaskGetStackHighWaterMark(h_sup),
    uxTaskGetStackHighWaterMark(h_dbg));
```

Adjust stack sizes with 20% margin above worst case.

### Verification
- [ ] All 14 test cases pass
- [ ] Stack watermarks have >20% margin
- [ ] CAN queue never overflows at max bus rate
- [ ] No task starves (heartbeats increment within 50ms window)

---

## Phase 5: Hardening

**Goal:** Production-ready firmware.

### Steps

1. **Set debug severity to ERROR only:**
   ```c
   #define DBG_ACTIVE_LEVEL  ERR_LVL_ERROR
   ```

2. **Remove test code:** WDT hang test, timing GPIO toggles, debug dump functions

3. **Endurance test:**
   - Run repetitive move cycles for 4+ hours
   - Cycle through all move types (ABS, REL, homing, velocity knob)
   - Enable hybrid trigger
   - Send CAN traffic at expected rate
   - Verify no stack growth, no memory corruption, no missed heartbeats

4. **Power cycle robustness:**
   - 100 power cycles
   - Verify successful boot every time
   - Verify TLV flash parameters survive power cycles
   - Verify TMC4671 SPI chip ID read succeeds every boot

5. **CAN error recovery:**
   - Disconnect CAN bus → reconnect → verify recovery
   - Send malformed frames → verify gatekeeper handles gracefully

6. **Enable all compiler warnings and fix:**
   ```
   -Wall -Wextra -Werror -Wshadow -Wundef
   ```

7. **Final stack size tuning:**
   - Run worst-case scenario (all features active simultaneously, max debug output)
   - Set production stack sizes to observed max + 20%

8. **Production build settings:**
   - Optimization: `-O2` or `-Os`
   - Debug info: stripped or minimized
   - Assertions: `configASSERT` → defined (failures trigger WDT reset)

### Verification
- [ ] Endurance test passes (4+ hours, no issues)
- [ ] 100/100 power cycles boot successfully
- [ ] Zero compiler warnings with -Wall -Wextra
- [ ] Production stack sizes set with margin
