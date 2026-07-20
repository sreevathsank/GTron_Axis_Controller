# 04 — ISR and Interrupt Design

## NVIC Priority Map (SAMC21, 2-bit = 4 Levels)

| NVIC Priority | Shifted Value | Usage | FromISR API? |
|---------------|--------------|-------|--------------|
| 0 (highest) | 0x00 | (reserved) | No |
| 1 | 0x40 | (reserved) | Yes (but not used) |
| 2 | 0x80 | **ALL application ISRs** | **Yes** |
| 3 (lowest) | 0xC0 | FreeRTOS kernel (PendSV, SysTick) | Yes |

All application ISRs at same priority (2). No ISR preempts another. NVIC handles tie-breaking by IRQ number.

## ISR Assignments

| IRQ | Source | Handler | File | Action |
|-----|--------|---------|------|--------|
| TC4 | TIMER_0 (1ms) | `TC4_Handler` | MCC-generated PLIB file | Clear int flag -> `vTaskNotifyGiveFromISR(h_4671, &woken)` -> `portYIELD_FROM_ISR` |
| TC2 | VEL_TIMER (1ms) | `TC2_Handler` | MCC-generated PLIB file | Clear int flag -> `vTaskNotifyGiveFromISR(h_2209, &woken)` -> `portYIELD_FROM_ISR` |
| TC0 | Free-running (1 MHz) | None | MCC-generated PLIB file | No ISR — read-only counter register for `micros()` |
| CAN1 | CAN1 RX FIFO0 | `CAN1_RxFifo0Callback` | `src/app/can/can_isr_callbacks.c` | Increment buf_cnt -> `xQueueSendFromISR(g_q_can_work, &frame, &woken)` -> `portYIELD_FROM_ISR` |
| CAN1 | CAN1 RX FIFO1 | `CAN1_RxFifo1Callback` | `src/app/can/can_isr_callbacks.c` | Same as FIFO0 |
| CAN1 | CAN1 TX done | `CAN1_TxFifoCallback` | `src/app/can/can_isr_callbacks.c` | Error check, update `can_state` |
| DMAC | DMAC Ch0 | `DMAC_Handler` | MCC-generated PLIB file | Existing DMA complete callback (unchanged from old project) |
| EIC EXTINT5 | IOXP_INT (PB21) | `ioxp_Interrupt_Callback` | `src/app/motor_2209/stepper_isr.c` | Set `g_ioxp_int_pending = true` + `vTaskNotifyGiveFromISR(h_2209, &woken)` + `portYIELD_FROM_ISR` |
| EIC EXTINT10 | LIM_RT (PC18) | `right_Limit_Interrupt_Callback` | `src/app/motor_4671/limit_isr.c` | Set `g_limit_flags \|= LIM_RT_BIT` — no notification (TMC4671 checks every 1ms) |
| EIC EXTINT12 | LIM_LFT (PC20) | `left_Limit_Interrupt_Callback` | `src/app/motor_4671/limit_isr.c` | Set `g_limit_flags \|= LIM_LFT_BIT` + `p_reeler1_info->flags.sensor_trigger = true` — no notification (TMC4671 checks every 1ms) |
| EIC EXTINT13 | DIAG (PC21) | `diag_Interrupt_Callback` | `src/app/motor_2209/stepper_isr.c` | Set `g_diag_pending = true` — no notification (TMC2209 checks every tick) |

EIC callback registration lives in `src/app/eic_init.c` -> `EIC_Init()` called from `main.c` pre-scheduler init.

## Removed ISRs (From Old Project)

| EXTINT | Pin | Reason |
|--------|-----|--------|
| EXTINT1 | PA17 (LINENC_DIR) | Dead — unused linear encoder |
| EXTINT2 | PA18 (LINENC_Z) | Dead — unused linear encoder |
| EXTINT3 | PA19 (ROTENC_COUNT) | Dead — TMC4671 reads encoder, not MCU |
| EXTINT7 | PB23 (INDEX) | Dead — TMC2209 index not used |
| EXTINT8 | PC16 (ROTENC_DIR) | Dead — TMC4671 reads encoder, not MCU |
| EXTINT9 | PC17 (ROTENC_Z) | Dead — TMC4671 reads encoder, not MCU |

## Per-ISR Pseudocode

### TC4_Handler (1ms Ramp Tick)

```c
// File: MCC-generated PLIB file (e.g. plib_tc4.c)
// Insert vTaskNotifyGiveFromISR call inside the generated ISR body
//  -> h_4671: src/app/app_state.h
void TC4_Handler(void) {
    hri_tc_clear_interrupt_OVF_bit(TC4);
    BaseType_t woken = pdFALSE;
    vTaskNotifyGiveFromISR(h_4671, &woken);
    portYIELD_FROM_ISR(woken);
}
```

### TC2_Handler (1ms Step Tracking Tick)

```c
// File: MCC-generated PLIB file (e.g. plib_tc2.c)
//  -> h_2209: src/app/app_state.h
void TC2_Handler(void) {
    hri_tc_clear_interrupt_OVF_bit(TC2);
    BaseType_t woken = pdFALSE;
    vTaskNotifyGiveFromISR(h_2209, &woken);
    portYIELD_FROM_ISR(woken);
}
```

### CAN1 RxFifo Callbacks (Lightweight Signal — No Data Read in ISR)

Ported from IO_Ctrl_Master's `CAN1_RxFifo0Callback` / `CAN1_RxFifo1Callback`.
The ISR does NOT read CAN frame data. It sends a lightweight signal to `g_q_can_work`.
The gatekeeper task calls `CAN1_Read()` to drain the FIFO. This keeps ISR time minimal.

```c
// File: src/app/can/can_isr_callbacks.c (ported from IO_Ctrl_Master/IOCtrl1.X/interrupt_callbacks.c)
//  -> can1_rx_fifo0_cb_info: src/app/can/can_state.h (CAN_Rx_Fifo_CB_Info type + extern),
//     src/app/can/can_state.c (instance defined)
//  -> can_frame_t, CAN_FROM_BUS: src/app/can/can_protocol.h
//  -> g_q_can_work: src/app/app_state.h
void CAN1_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context) {
    can1_rx_fifo0_cb_info.buf_cnt += 1;
    can1_rx_fifo0_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo0_cb_info.context = context;

    can_frame_t frame = { .direction = CAN_FROM_BUS };   // LOCAL — not shared global
    BaseType_t woken = pdFALSE;                           // BUGFIX: was pdTRUE in IO_Ctrl_Master
    xQueueSendFromISR(g_q_can_work, &frame, &woken);
    portYIELD_FROM_ISR(woken);
}

// CAN1_RxFifo1Callback — identical pattern
//  -> can1_rx_fifo1_cb_info: src/app/can/can_state.h (extern), src/app/can/can_state.c (defined)
void CAN1_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context) {
    can1_rx_fifo1_cb_info.buf_cnt += 1;
    can1_rx_fifo1_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo1_cb_info.context = context;

    can_frame_t frame = { .direction = CAN_FROM_BUS };
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(g_q_can_work, &frame, &woken);
    portYIELD_FROM_ISR(woken);
}
```

### CAN1_TxFifoCallback

Ported from IO_Ctrl_Master. Minimal — tracks TX completion status.

```c
// File: src/app/can/can_isr_callbacks.c
void CAN1_TxFifoCallback(uintptr_t context) {
    xferContext = context;
    status = CAN1_ErrorGet();
    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) ||
        ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC)) {
        can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
    } else {
        can_state = APP_STATE_CAN_XFER_ERROR;
    }
}
```

### LIM_RT Callback (EXTINT10)

```c
// File: src/app/motor_4671/limit_isr.c
//  -> g_limit_flags, LIM_RT_BIT: src/app/app_state.h
static void right_Limit_Interrupt_Callback(void) {
    g_limit_flags |= LIM_RT_BIT;
    // No FreeRTOS API call — TMC4671_TASK checks every 1ms
}
```

### LIM_LFT Callback (EXTINT12)

```c
// File: src/app/motor_4671/limit_isr.c
//  -> g_limit_flags, LIM_LFT_BIT: src/app/app_state.h
//  -> p_reeler1_info: src/app/can/can_cmd_parser.h (Motor_Info_t, defined in src/app/can/can_cmd_parser.c)
static void left_Limit_Interrupt_Callback(void) {
    g_limit_flags |= LIM_LFT_BIT;
    p_reeler1_info->flags.sensor_trigger = true;  // hybrid trigger sensor
    // No FreeRTOS API call — TMC4671_TASK checks every 1ms
}
```

### IOXP_INT Callback (EXTINT5)

```c
// File: src/app/motor_2209/stepper_isr.c
//  -> g_ioxp_int_pending: src/app/app_state.h
//  -> h_2209: src/app/app_state.h
static void ioxp_Interrupt_Callback(void) {
    g_ioxp_int_pending = true;
    BaseType_t woken = pdFALSE;
    vTaskNotifyGiveFromISR(h_2209, &woken);
    portYIELD_FROM_ISR(woken);
}
```

### DIAG Callback (EXTINT13)

```c
// File: src/app/motor_2209/stepper_isr.c
//  -> g_diag_pending: src/app/app_state.h
static void diag_Interrupt_Callback(void) {
    g_diag_pending = true;
    // No FreeRTOS API call — TMC2209_TASK checks every tick
}
```

## LIM_RT / LIM_LFT: Why No Task Notification?

TMC4671_TASK is already woken every 1ms by TC4. Adding LIM ISR notifications would be redundant — the task already checks `g_limit_flags` at the top of each tick. Worst-case latency from physical edge to detection: 999us.

LIM_LFT also serves double duty as the hybrid trigger sensor input. The same flag (`p_reeler1_info->flags.sensor_trigger`) is read inside `check_For_Hybrid_Trigger()` which runs every tick in the same task. Single consumer, simple ownership.

## Harmony V3 EIC Callback Registration

Harmony V3 MCC generates EIC initialization code. Registering callbacks uses the Harmony EIC PLIB API:

```c
// In system_init() or a custom init function:
EIC_CallbackRegister(EIC_PIN_5, ioxp_Interrupt_Callback, 0);
EIC_CallbackRegister(EIC_PIN_10, right_Limit_Interrupt_Callback, 0);
EIC_CallbackRegister(EIC_PIN_12, left_Limit_Interrupt_Callback, 0);
EIC_CallbackRegister(EIC_PIN_13, diag_Interrupt_Callback, 0);
```

MCC configures EXTINTs via the UI (pin, sense edge, debounce, async). The generated code handles NVIC priority and pin mux. You only need to register callbacks.

## FreeRTOS ISR Configuration

```c
#define configPRIO_BITS                          2
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY  0x03
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  0x01
#define configKERNEL_INTERRUPT_PRIORITY          (0x03 << 6)   // 0xC0
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     (0x01 << 6)   // 0x40

// All application ISRs at NVIC priority 2 = 0x80
// 0x80 > 0x40 → all can call FromISR APIs
```

MCC's FreeRTOS component generates these automatically when you set interrupt priority levels in the UI.

## TC0 — Microsecond Free-Running Counter

No ISR. Configured as 32-bit free-running timer at 1 MHz:

```c
// MCC UI: TC0 → 2 MHz GCLK, prescaler /2 → 1 MHz, 32-bit mode
// Generated init code starts the timer

uint32_t micros(void) {
    return TC0_Timer32bitCounterGet();  // Harmony PLIB
}

void delay_us_blocking(uint32_t us) {
    uint32_t start = micros();
    while ((micros() - start) < us) { /* spin */ }
}
```

For non-blocking delay:
```c
bool delay_us_nonblocking(uint32_t start_us, uint32_t duration_us) {
    return ((micros() - start_us) >= duration_us);
}
```

Used for `trigger_Camera_Line()` 1us pulse and any other microsecond-precision timing.
