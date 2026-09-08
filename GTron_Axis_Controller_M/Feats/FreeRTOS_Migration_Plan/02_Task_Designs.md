# 02 — Task Designs

## TMC4671_TASK (Priority 4)

**File:** `src/app/motor_4671/motor_4671_task.c`
**Stack:** 1024 bytes (256 words)
**Trigger:** TC4 ISR at 1ms → `vTaskNotifyGiveFromISR(h_4671)`
**Owns:** SERCOM0 (SPI), TMC4671 CS/EN/RST GPIOs, REELER_INT GPIO
**States:** STOPPED, S_RAMP, TRAPEZOIDAL, VELOCITY_KNOB, HOMING

| Symbol | Defined In |
|--------|-----------|
| `h_4671`, `g_q_4671_rx`, `g_q_can_work`, `g_limit_flags`, `g_heartbeat_tmc4671` | `src/app/app_state.h` / `.c` |
| `g_motion_state`, `g_move_just_completed`, `g_move_given_s_ramp`, `g_move_given_trapezoidal_ramp` | `src/app/motor_4671/motor_4671_internal.h` / `.c` |
| `can_cmd_t`, `CMD_MOVE_TO`, `CMD_STOP`, `CMD_HOMING_START` etc. | `src/app/can/can_state.h` |
| `can_frame_t`, `can_direction_t`, `CAN_TO_BUS`, `CAN_ID()`, `can_union_type` | `src/app/can/can_protocol.h` |
| `COMPLETE_MOVE_DONE`, `ERR_BUSY` | `src/app/can/can_state.h` |
| `MOTOR_REELER1`, `HYBRID_TRIGGER_INSPECTION`, `AXC_ERR_SLIP`, `CAN_ERR_REPLY_TOP_RACK_ID`, `AXC_MOVE_DONE`, `REELER_MOTOR_1` | `src/app/can/can_protocol.h` (ported from old `IMM_CAN_Message_Id.h`) |
| `p_reeler1_info`, `Motor_Info_t`, `Hybrid_t`, `mot_array[]` | `src/app/can/can_cmd_parser.h` / `.c` (ported from old `gtron_can_cmd_parser.c`) |
| `check_Limit_Flags()` | `src/app/motor_4671/limit_handler.c` |
| `check_For_Hybrid_Trigger()`, `trigger_Camera_Line()`, `enable_hybrid_mode()`, `disable_hybrid_mode()` | `src/app/motor_4671/hybrid_trigger.c` (ported from `Bring_Up/Motion/Hybrid_Trigger.c`) |
| `run_S_ramp_step()`, `run_trap_step()`, `run_velocity_step()`, `run_homing_step()` | `src/app/motor_4671/motion.c` (ported from `Bring_Up/Motion/Motion.c`) |
| `start_move()`, `set_target_vel()`, `reply_position()`, `reply_status()`, `update_pi_gains()`, `set_soft_limits()` | `src/app/motor_4671/motor_4671_task.c` |
| `reeler_Pause_Motor()`, `tmc4671_getActualPosition()`, `tmc4671_writeInt()`, `tmc4671_setModeMotion()` | `src/app/drivers/tmc4671/TMC4671.c` (ported from `TMC-API/tmc/ic/TMC4671/TMC4671.c`) |
| `axis_id` | `src/app/app_state.h` / `.c` |
| `LIM_RT_BIT`, `LIM_LFT_BIT` | `src/app/app_state.h` |

```c
// File: src/app/motor_4671/motor_4671_task.c
void vTMC4671_Task(void *pv) {
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // block until TC4 1ms tick

        // 1. Process incoming CAN commands (non-blocking drain)
        can_cmd_t cmd;
        while (xQueueReceive(g_q_4671_rx, &cmd, 0) == pdTRUE) {
            switch (cmd.type) {
                case CMD_MOVE_TO:       start_move(&cmd);             break;
                case CMD_MOVE_BY:       start_move(&cmd);             break;
                case CMD_SET_VELOCITY:  set_target_vel(&cmd);         break;
                case CMD_STOP:          g_motion_state = STOPPED;     break;
                case CMD_HOMING_START:  g_motion_state = HOMING;      break;
                case CMD_HYBRID_ENABLE: enable_hybrid_mode(&cmd);     break;
                case CMD_HYBRID_DISABLE: disable_hybrid_mode();       break;
                case CMD_QUERY_POS:     reply_position(&cmd);         break;
                case CMD_QUERY_STATUS:  reply_status(&cmd);           break;
                case CMD_CONFIG_PI:     update_pi_gains(&cmd);        break;
                case CMD_CONFIG_LIMITS: set_soft_limits(&cmd);        break;
            }
        }

        // 2. Check limits (LIM_RT / LIM_LFT flags set by EIC ISR)
        if (g_limit_flags && g_motion_state != STOPPED) {
            check_Limit_Flags();  // homing sequence + emergency stop
        }

        // 3. Hybrid trigger — runs every tick regardless of motion state
        //    Reads TMC4671 position via SPI (~20us per read, up to 3 reads)
        //    Fires camera GPIO, detects slips, auto-disables on completion
        //    May internally call reeler_Pause_Motor()
        check_For_Hybrid_Trigger();

        // 4. One step of current motion state
        switch (g_motion_state) {
            case STOPPED:        break;
            case S_RAMP:         run_S_ramp_step();      break;
            case TRAPEZOIDAL:    run_trap_step();         break;
            case VELOCITY_KNOB:  run_velocity_step();    break;
            case HOMING:         run_homing_step();       break;
        }

        // 5. Check move completion → notify CAN gatekeeper
        if (g_move_just_completed) {
            can_frame_t tx = {
                .can_id    = CAN_ID(axis_id, MVP, AXC_MOVE_DONE, 0),
                .direction = CAN_TO_BUS,
                .dlc       = 4,
                .payload.data = {MOTOR_REELER1, COMPLETE_MOVE_DONE, 0, 0}
            };
            xQueueSend(g_q_can_work, &tx, 0);
            g_move_just_completed = false;
        }

        g_heartbeat_tmc4671++;
    }
}
```

### Motion State Details

| State | Entry Condition | Tick Action | Exit To | Exit Condition |
|-------|----------------|-------------|---------|---------------|
| STOPPED | Init / CAN stop / move done | None | S_RAMP, TRAP, VEL_KNOB, HOMING | CAN command received |
| S_RAMP | `move_given_s_ramp && move_dir` set | `run_S_ramp_step()` — advances 7-phase S-curve | STOPPED | Phase 7 complete or limit hit |
| TRAPEZOIDAL | `move_given_trapezoidal_ramp` set | `run_trap_step()` — ACCEL→CRUISE→DECEL | STOPPED | Position reached or limit hit |
| VELOCITY_KNOB | CAN velocity command while STOPPED | `run_velocity_step()` — reads physical knob position, maps to TMC4671 velocity | STOPPED | CAN stop or knob returns to zero |
| HOMING | CAN homing start command | `run_homing_step()` — switch sequence state machine | STOPPED | Homing done, limit hit, or timeout |

### Hybrid Trigger Integration

`check_For_Hybrid_Trigger()` runs every tick unconditionally:
- If hybrid mode == OFF: early return (~3 cycles)
- If active: reads TMC4671 position via SPI
- Detects sensor_trigger flag (set by LIM_LFT EIC ISR)
- Fires camera line (GPIO toggle on REELER_INT, 1us pulse)
- Slip detection: delta between consecutive anchor positions vs expected step size
- Slip threshold exceeded → pause motor + push CAN error frame to `g_q_can_work`
- N-shot complete → auto-disable hybrid mode + pause motor + push completion frame

### Error Reporting (Via TO_BUS to g_q_can_work)

```c
// Slip error in hybrid trigger:
can_frame_t err = {
    .can_id    = CAN_ERR_REPLY_TOP_RACK_ID,
    .direction = CAN_TO_BUS,
    .dlc       = 4,
    .payload.data = {MOTOR_REELER1, HYBRID_TRIGGER_INSPECTION, AXC_ERR_SLIP, 0}
};
xQueueSend(g_q_can_work, &err, 0);

// Homing complete:
can_frame_t done = {
    .can_id    = CAN_ID(axis_id, MVP, AXC_MOVE_DONE, REELER_MOTOR_1),
    .direction = CAN_TO_BUS,
    .dlc       = 4,
    .payload.data = {MOTOR_REELER1, COMPLETE_MOVE_DONE, 0, 0}
};
xQueueSend(g_q_can_work, &done, 0);
```

### Limit Handling (Same-As-Old Pattern)

- LIM_RT / LIM_LFT EIC ISRs set `g_limit_flags` bits only (no task notification)
- TMC4671_TASK checks `g_limit_flags` every 1ms → worst case 999us latency
- Inside `check_Limit_Flags()`: homing mode uses switch sequence FSM; non-homing stops motor

---

## CAN_GATEKEEPER (Priority 3)

**Stack:** 640 bytes (160 words)
**Trigger:** `xQueueReceive(g_q_can_work, ...)` — unified CAN work queue
**Owns:** CAN1 peripheral
**Enforces:** Move arbitration — only 1 motor moves at a time
**Source:** `CAN1_Read()` and `CAN1_Write()` ported from IO_Ctrl_Master project with bug fixes

### ISR → Task Flow

The CAN ISR (RxFifo0/RxFifo1 callbacks) sends a **lightweight signal** to `g_q_can_work` — just a `can_frame_t` with `direction = CAN_FROM_BUS`. The actual CAN frame data (ID, DLC, payload) is NOT read in the ISR. The gatekeeper calls `CAN1_Read()` in task context to drain the FIFO. This keeps ISR time minimal.

| Symbol | Defined In |
|--------|-----------|
| `g_q_can_work`, `g_q_4671_rx`, `g_q_2209_rx`, `g_q_sup_rx`, `h_can`, `g_heartbeat_can` | `src/app/app_state.h` / `.c` |
| `can_frame_t`, `can_direction_t`, `CAN_FROM_BUS`, `CAN_TO_BUS`, `can_union_type` | `src/app/can/can_protocol.h` |
| `can_cmd_t`, `COMPLETE_MOVE_DONE`, `ERR_BUSY`, `g_4671_busy`, `g_2209_busy` | `src/app/can/can_state.h` / `.c` |
| `can_cmd_parse_info`, `CAN_Cmd_Parser_t`, `can1_rx_fifo0_cb_info`, `can1_rx_fifo1_cb_info`, `CAN_Rx_Fifo_CB_Info` | `src/app/can/can_state.h` / `.c` (ported from `IO_Ctrl_Master/IOCtrl1.X/global_vars.h`) |
| `CAN1_Read()`, `CAN1_Write()` | `src/app/can/can_gatekeeper.c` (ported from `IO_Ctrl_Master/src/can.c`) |
| `get_can_id_from_buffer()`, `get_can_dlc_from_buffer()`, `get_can_data_from_buffer()`, `CANDlcToLengthGet()`, `CANLengthToDlcGet()` | `src/app/can/can_gatekeeper.c` (ported from `IO_Ctrl_Master/src/can.c`) |
| `GET_CMD()`, `GET_MOT()`, `CAN_ID()`, `CHK_FW_PARAM`, `WR_FW_PARAM`, `RD_FW_PARAM`, `RFS_DISTANCE`, `START_RANGE`, `END_RANGE` | `src/app/can/can_protocol.h` (ported from old `IMM_CAN_Message_Id.h`) |
| `MOTOR_REELER1`, `REELER_MOTOR_1` | `src/app/can/can_protocol.h` (ported from old `IMM_CAN_Message_Id.h` + `gtron_can_cmd_parser.h`) |
| `is_tmc2209_motor_command()`, `is_move_command()`, `send_error_reply()` | `src/app/can/can_gatekeeper.c` |
| `axis_id` | `src/app/app_state.h` / `.c` |

```c
// File: src/app/can/can_gatekeeper.c
void vCAN_Gatekeeper_Task(void *pv) {
    can_frame_t frame;

    for (;;) {
        xQueueReceive(g_q_can_work, &frame, portMAX_DELAY);

        if (frame.direction == CAN_FROM_BUS) {
            // Drain ALL pending frames from CAN FIFOs
            while (can1_rx_fifo0_cb_info.buf_cnt || can1_rx_fifo1_cb_info.buf_cnt) {
                CAN1_Read();   // ported from IO_Ctrl_Master — reads FIFO, fills can_cmd_parse_info
                
                uint32_t msg_id = can_cmd_parse_info.msg_id;
                uint8_t  cmd    = GET_CMD(msg_id);
                uint8_t  mot    = GET_MOT(msg_id);
                QueueHandle_t target_q = NULL;

                // Route based on command type
                if (cmd == CHK_FW_PARAM || cmd == WR_FW_PARAM || cmd == RD_FW_PARAM) {
                    target_q = g_q_sup_rx;
                } else if (is_tmc2209_motor_command(cmd, mot)) {
                    target_q = g_q_2209_rx;
                } else {
                    target_q = g_q_4671_rx;
                }

                can_cmd_t dispatch_cmd = {
                    .can_id = msg_id,
                    .type   = cmd,
                    .motor  = mot,
                    .value  = can_cmd_parse_info.data_64bit   // can_union_type compatibility
                };

                // Move arbitration
                if (is_move_command(msg_id)) {
                    if (g_4671_busy || g_2209_busy) {
                        send_error_reply(msg_id, ERR_BUSY);
                    } else {
                        xQueueSend(target_q, &dispatch_cmd, 0);
                        if (mot == REELER_MOTOR_1) g_4671_busy = true;
                        else                       g_2209_busy = true;
                    }
                } else {
                    // Non-move command — dispatch immediately
                    xQueueSend(target_q, &dispatch_cmd, 0);
                }
            }
        } else {
            // CAN_TO_BUS — transmit on CAN bus
            CAN1_Write(frame.can_id, frame.payload.data, frame.dlc);
            // ported from IO_Ctrl_Master: formats CAN_TX_BUFFER, calls CAN1_MessageTransmitFifo

            // Check for move completion event → clear busy flag
            if (frame.payload.data[1] == COMPLETE_MOVE_DONE) {
                if (frame.payload.data[0] == MOTOR_REELER1) g_4671_busy = false;
                else                                       g_2209_busy = false;
            }
        }

        g_heartbeat_can++;
    }
}
```

### Move Arbitration

| State | Effect |
|-------|--------|
| `g_4671_busy == true` | Reject new REELER MOVE commands with BUSY |
| `g_2209_busy == true` | Reject new GUIDE/VARREST MOVE commands with BUSY |
| Both busy | Reject ALL new MOVE commands |
| Move complete TO_BUS frame received | Clear corresponding busy flag |

### Command Routing Map

| cmd (8-bit) | typ (8-bit) | Target Queue | Purpose |
|-------------|-------------|-------------|---------|
| MVP | MVP_ABS / MVP_REL | Motor RX queue (4671 or 2209) | Move to / move by |
| RFS | 0 / 1 / 2 | Motor RX queue | Reference search / homing |
| MST | 0 | Motor RX queue | Motor stop |
| SAP | various | Motor RX queue | Set axis parameter |
| GAP | various | Motor RX queue | Get axis parameter |
| ROL / ROR | 0 | TMC4671_RX | Rotate left/right (direct mode) |
| CHK_FW_PARAM (0x80) | 0 | g_q_sup_rx | Verify flash parameter |
| WR_FW_PARAM (0x82) | 0 | g_q_sup_rx | Write flash parameter |
| RD_FW_PARAM (0x84) | 0 | g_q_sup_rx | Read flash parameter |
| RFS_DISTANCE (0xC4) | 0 | TMC4671_RX | Stroke length config |
| START_RANGE (0xC5) | 0 | TMC4671_RX | Start range config |
| END_RANGE (0xC6) | 0 | TMC4671_RX | End range config |
| 138 | 0 / 1 / 2 | TMC4671_RX | Ping / move-done-ping / ref-search-ping |

---

## TMC2209_TASK (Priority 2)

**File:** `src/app/motor_2209/motor_2209_task.c`
**Stack:** 768 bytes (192 words)
**Trigger:** TC2 ISR (1ms) via `vTaskNotifyGiveFromISR(h_2209)` AND IOXP_INT EIC notify
**Owns:** SERCOM5 (UART), SERCOM3 mutex (for IOXP reads)
**Motors:** GUIDE + VARREST1/VARREST2 (only one moves at a time)

| Symbol | Defined In |
|--------|-----------|
| `h_2209`, `g_q_2209_rx`, `g_q_can_work`, `g_ioxp_int_pending`, `g_diag_pending`, `g_m_sercom3`, `g_flash_busy`, `g_heartbeat_tmc2209` | `src/app/app_state.h` / `.c` |
| `g_2209_moving`, `g_2209_move_done`, `g_active_2209_motor`, `g_guide_limit_triggered`, `g_which_limit` | `src/app/motor_2209/motor_2209_internal.h` / `.c` |
| `can_cmd_t` | `src/app/can/can_state.h` |
| `can_frame_t`, `can_direction_t`, `CAN_TO_BUS`, `CAN_ID()`, `can_union_type` | `src/app/can/can_protocol.h` |
| `MOTOR_GUIDE`, `CAN_ERR_REPLY_TOP_RACK_ID`, `AXC_MOVE_DONE`, `AXC_MOTOR_GUIDE` | `src/app/can/can_protocol.h` (ported from old `IMM_CAN_Message_Id.h`) |
| `ERR_LIMIT_HIT`, `ERR_FLASH_BUSY`, `COMPLETE_MOVE_DONE` | `src/app/can/can_state.h` |
| `read_ioxp_and_detect_limits()` | `src/app/drivers/io_expander/spi_io_expander.c` (ported from old `Bring_Up/IO_Expander/spi_io_expander.c`) |
| `stop_guide_motor()` | `src/app/motor_2209/motor_2209_task.c` |
| `dispatch_2209_cmd()`, `handle_stall()` | `src/app/motor_2209/motor_2209_task.c` |
| `check_Which_2209_Motor_Moving()` | `src/app/motor_2209/step_counter.c` (ported from old `tmc2209_uart/Step_Counter.c`) |
| `axis_id` | `src/app/app_state.h` / `.c` |

```c
// File: src/app/motor_2209/motor_2209_task.c
void vTMC2209_Task(void *pv) {
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // TC2 tick + IOXP notify

        // 1. IOXP interrupt — guide motor limit switch
        if (g_ioxp_int_pending) {
            if (xSemaphoreTake(g_m_sercom3, 0) == pdTRUE) {
                // Got mutex — read IOXP register
                read_ioxp_and_detect_limits();   // ~20us SPI
                xSemaphoreGive(g_m_sercom3);
                if (g_guide_limit_triggered) {
                    stop_guide_motor();
                    // Report via CAN
                    can_frame_t tx = {
                        .can_id    = CAN_ERR_REPLY_TOP_RACK_ID,
                        .direction = CAN_TO_BUS,
                        .dlc       = 3,
                        .payload.data = {MOTOR_GUIDE, ERR_LIMIT_HIT, g_which_limit}
                    };
                    xQueueSend(g_q_can_work, &tx, 0);
                }
            }
            // If mutex not available (flash op in progress): skip, retry next tick
            g_ioxp_int_pending = false;
        }

        // 2. Process CAN commands
        can_cmd_t cmd;
        while (xQueueReceive(g_q_2209_rx, &cmd, 0) == pdTRUE) {
            dispatch_2209_cmd(&cmd);
        }

        // 3. DIAG stall detection (flag set by EIC ISR, checked every tick)
        if (g_diag_pending) {
            handle_stall();          // pause motor, report via CAN
            g_diag_pending = false;
        }

        // 4. Poll MSCNT if any motor is moving
        if (g_2209_moving) {
            check_Which_2209_Motor_Moving();  // existing function
        }

        // 5. Move completion check
        if (g_2209_move_done) {
            can_frame_t tx = {
                .can_id    = CAN_ID(axis_id, MVP, AXC_MOVE_DONE, 0),
                .direction = CAN_TO_BUS,
                .dlc       = 4,
                .payload.data = {g_active_2209_motor, COMPLETE_MOVE_DONE, 0, 0}
            };
            xQueueSend(g_q_can_work, &tx, 0);
            g_2209_move_done = false;
        }

        g_heartbeat_tmc2209++;
    }
}
```

### IOXP Limit Response Latency

```
IOXP_INT EIC ISR → vTaskNotifyGiveFromISR(h_2209)
    → TMC2209_TASK unblocks (≤10us context switch)
    → xSemaphoreTake(g_m_sercom3) (non-blocking — mutex free during normal ops)
    → read IOXP ~20us
    → stop motor and report

Worst-case: mutex held by flash op → skip, retry next tick (≤1ms)
Normal-case: <50us from physical edge to motor stop
```

### Guide Move Rejection When Flash Busy

```c
// In dispatch_2209_cmd, before starting any guide motor move:
if (motor == MOTOR_GUIDE && g_flash_busy && is_move_command(cmd)) {
    can_frame_t reject = {
        .can_id    = cmd.can_id,
        .direction = CAN_TO_BUS,
        .dlc       = 2,
        .payload.data = {MOTOR_GUIDE, ERR_FLASH_BUSY}
    };
    xQueueSend(g_q_can_work, &reject, 0);
    return;  // do not start the move
}
```

### MSCNT Poll Rate

- TC2 configured at 1ms tick (via MCC)
- TMC2209 UART read cycle at 230400 baud: ~870us per transaction
- MSCNT wraps every 1024 microsteps
- 1ms polling handles max step rate of ~500 full-steps/sec at 256 microstepping
- If faster step rates are needed, reduce TC2 period (parameterize via TLV flash)

---

## SUPERVISOR_TASK (Priority 1)

**File:** `src/app/supervisor/supervisor_task.c`
**Stack:** 640 bytes (160 words)
**Trigger:** `vTaskDelay(10ms)` periodic loop
**Owns:** WDT, LEDs, `g_flash_busy` flag, SERCOM3 mutex (for flash operations)
**Handles:** CHK_FW_PARAM, WR_FW_PARAM, RD_FW_PARAM via `g_q_sup_rx`

| Symbol | Defined In |
|--------|-----------|
| `g_q_sup_rx`, `g_q_can_work`, `g_m_sercom3`, `g_flash_busy`, `g_heartbeat_array[]`, `g_heartbeat_*` | `src/app/app_state.h` / `.c` |
| `can_cmd_t`, `STATUS_OK`, `ERR_FLASH_BUSY` | `src/app/can/can_state.h` |
| `can_frame_t`, `can_direction_t`, `CAN_TO_BUS`, `can_union_type` | `src/app/can/can_protocol.h` |
| `CHK_FW_PARAM`, `WR_FW_PARAM`, `RD_FW_PARAM` | `src/app/can/can_protocol.h` (ported from old `IMM_CAN_Message_Id.h`) |
| `tlv_read_parameter()`, `tlv_write_parameter()` | `src/app/supervisor/tlv_flash.c` / `.h` (ported from old `Code_Dump/tlv_flash.c`) |
| `WDT_Clear()` | Harmony PLIB — called from `src/app/supervisor/supervisor_task.c` |
| `update_leds()` | `src/app/supervisor/supervisor_task.c` |

```c
// File: src/app/supervisor/supervisor_task.c
void vSupervisor_Task(void *pv) {
    TickType_t last_wake = xTaskGetTickCount();
    static uint32_t prev_hb[4] = {0};
    uint8_t hb_cycle = 0;
    can_cmd_t cmd;

    for (;;) {
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));

        // 1. Process flash parameter commands from CAN gatekeeper
        while (xQueueReceive(g_q_sup_rx, &cmd, 0) == pdTRUE) {
            switch (cmd.type) {
                case CHK_FW_PARAM: {
                    // Verify parameter matches flash
                    int32_t flash_val = tlv_read_parameter(cmd.value);
                    can_frame_t reply = {
                        .can_id    = cmd.can_id,
                        .direction = CAN_TO_BUS,
                        .dlc       = 4,
                        .payload.data_64bit = flash_val
                    };
                    xQueueSend(g_q_can_work, &reply, 0);
                    break;
                }
                case WR_FW_PARAM: {
                    // Write parameter to flash
                    xSemaphoreTake(g_m_sercom3, portMAX_DELAY);
                    g_flash_busy = true;
                    tlv_write_parameter(cmd.motor, cmd.value);
                    g_flash_busy = false;
                    xSemaphoreGive(g_m_sercom3);
                    // Acknowledge
                    can_frame_t ack = {
                        .can_id    = cmd.can_id,
                        .direction = CAN_TO_BUS,
                        .dlc       = 2,
                        .payload.data = {STATUS_OK, 0}
                    };
                    xQueueSend(g_q_can_work, &ack, 0);
                    break;
                }
                case RD_FW_PARAM: {
                    // Read parameter from flash
                    xSemaphoreTake(g_m_sercom3, portMAX_DELAY);
                    g_flash_busy = true;
                    int32_t val = tlv_read_parameter(cmd.value);
                    g_flash_busy = false;
                    xSemaphoreGive(g_m_sercom3);
                    can_frame_t reply = {
                        .can_id    = cmd.can_id,
                        .direction = CAN_TO_BUS,
                        .dlc       = 4,
                        .payload.data_64bit = val
                    };
                    xQueueSend(g_q_can_work, &reply, 0);
                    break;
                }
            }
        }

        // 2. WDT heartbeat check (every 5th cycle = every 50ms)
        if (++hb_cycle >= 5) {
            hb_cycle = 0;
            bool all_alive = true;
            for (int i = 0; i < 4; i++) {
                if (g_heartbeat_array[i] == prev_hb[i]) {
                    all_alive = false;
                    break;
                }
                prev_hb[i] = g_heartbeat_array[i];
            }
            if (all_alive) WDT_Clear();
            // else: let WDT fire → system reset
        }

        // 3. LED status update
        update_leds();

        g_heartbeat_supervisor++;
    }
}
```

---

## DEBUG_TASK (Priority 0 — Idle)

**File:** `src/app/debug/debug_task.c`
**Stack:** 640 bytes (160 words)
**Trigger:** `xQueueReceive(g_q_debug, ...)` — blocking on debug queue
**Owns:** SERCOM7 DMA UART
**No heartbeat** — cannot deadlock (only blocks on queue receive)

| Symbol | Defined In |
|--------|-----------|
| `g_q_debug`, `h_dbg` | `src/app/app_state.h` / `.c` |
| `transport_send()` | `src/app/debug/dbg_transport.c` / `.h` (ported from old `Bring_Up/Debug/dbg_transport.c`) |

```c
// File: src/app/debug/debug_task.c
void vDebug_Task(void *pv) {
    char buf[132];
    for (;;) {
        if (xQueueReceive(g_q_debug, buf, portMAX_DELAY) == pdTRUE) {
            transport_send(&buf[1], strlen(&buf[1]));
            // transport_send blocks ~2.5ms for 512 bytes at 2 Mbaud
            // Blocking is OK — this is the lowest priority task
        }
    }
}
```

`DBG_Printf()` called from any task:

```c
// File: src/app/debug/dbg_print.c
void DBG_Printf(uint8_t level, const char *fmt, ...) {
    char buf[132];
    buf[0] = level;   // severity prefix
    va_list args;
    va_start(args, fmt);
    vsnprintf(&buf[1], sizeof(buf) - 1, fmt, args);
    va_end(args);
    xQueueSend(g_q_debug, buf, 0);  // non-blocking, drop if full
}
```

- Formats on caller's stack → pushes to queue → returns immediately
- If queue is full (16 messages pending), message is silently dropped
- Debug task drains at idle priority — never delays motor or CAN tasks
