# 03 — CAN Gatekeeper Design

## Source

The CAN gatekeeper is ported from the **IO_Ctrl_Master FreeRTOS project** (`IO_Ctrl_Master/src/can.c`, `interrupt_callbacks.c`). That project already implements a working unified CAN queue with a read/write operation flag. The GTron migration refines this with bug fixes, static allocation, and direct one-hop dispatch (eliminating the separate parser task).

## Unified CAN Work Queue

A single queue carries all CAN frames with a direction flag. No separate TX queues or semaphores needed.

### can_frame_t (Uses Old Project's can_union_type)

```c
// File: src/app/can/can_protocol.h
//  -> can_union_type: ported from old Bring_Up/CAN/IMM_CAN_Message_Id.h
typedef union {
    unsigned char data[8];
    int64_t data_64bit;
} can_union_type;

typedef enum { CAN_FROM_BUS, CAN_TO_BUS } can_direction_t;

typedef struct {
    uint32_t         can_id;       // 29-bit CAN ID (0 for FROM_BUS signals from ISR)
    can_direction_t  direction;    // FROM_BUS = signal from CAN ISR, TO_BUS = from motor/supervisor
    uint8_t          dlc;          // 0-8 data bytes
    can_union_type   payload;      // data as array or 64-bit scalar
} can_frame_t;                     // 4 + 1 + 1 + 2pad + 8 = 16 bytes
```

### Struct Mapping (IO_Ctrl_Master -> GTron)

| IO_Ctrl_Master `Can_Queue_t` | GTron `can_frame_t` |
|------------------------------|---------------------|
| `uint8_t operation_flag` | `can_direction_t direction` (CAN_FROM_BUS / CAN_TO_BUS) |
| `uint8_t buffer_X` | REMOVED — gatekeeper calls CAN1_Read() which handles FIFO selection |
| `uint8_t data[8]` | `can_union_type payload` (backward-compat with existing CAN protocol code) |
| `uint32_t msg_id` | `uint32_t can_id` |
| `uint8_t dlc` | `uint8_t dlc` |

### Queue Configuration

```c
#define Q_CAN_WORK_LEN  16
QueueHandle_t g_q_can_work;  // 16 x 16B = 256 bytes, static allocation
```

## Producers

### CAN ISR (FROM_BUS) — Lightweight Signal, No Data Read in ISR

Ported from IO_Ctrl_Master's `CAN1_RxFifo0Callback` / `CAN1_RxFifo1Callback`. The ISR does NOT read CAN frame data. It sends a lightweight signal — just `direction = CAN_FROM_BUS`. The gatekeeper task calls `CAN1_Read()` to drain the FIFO. This keeps ISR time minimal.

```c
// File: src/app/can/can_isr_callbacks.c (ported from IO_Ctrl_Master/IOCtrl1.X/interrupt_callbacks.c)
//  -> g_q_can_work: src/app/app_state.h
//  -> can1_rx_fifo0_cb_info, can1_rx_fifo1_cb_info: src/app/can/can_state.h
//  -> can_frame_t, CAN_FROM_BUS: src/app/can/can_protocol.h

// CAN1_RxFifo0Callback — registered via CAN1_RxFifoCallbackRegister()
void CAN1_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context) {
    can1_rx_fifo0_cb_info.buf_cnt += 1;
    can1_rx_fifo0_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo0_cb_info.context = context;

    can_frame_t frame = { .direction = CAN_FROM_BUS };   // LOCAL — no shared global
    BaseType_t woken = pdFALSE;                           // BUGFIX: was pdTRUE
    xQueueSendFromISR(g_q_can_work, &frame, &woken);
    portYIELD_FROM_ISR(woken);
}

// CAN1_RxFifo1Callback — identical pattern
void CAN1_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context) {
    can1_rx_fifo1_cb_info.buf_cnt += 1;
    can1_rx_fifo1_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo1_cb_info.context = context;

    can_frame_t frame = { .direction = CAN_FROM_BUS };   // LOCAL
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(g_q_can_work, &frame, &woken);
    portYIELD_FROM_ISR(woken);
}
```

### Motor Tasks / SUPERVISOR (TO_BUS)

```c
can_frame_t tx = {
    .can_id    = reply_id,
    .direction = CAN_TO_BUS,
    .dlc       = 4,
    .payload.data_64bit = response_value
};
xQueueSend(g_q_can_work, &tx, 0);  // non-blocking
```

All TO_BUS frames go through the same queue. If queue is full, frames are dropped — acceptable for status events. Critical error reports retry next tick.

## Consumer: Gatekeeper Task

Core functions ported from IO_Ctrl_Master: `CAN1_Read()` (lines 312-380 of can.c) and `CAN1_Write()` (lines 288-310 of can.c).

```c
// File: src/app/can/can_gatekeeper.c
//  -> g_q_can_work: src/app/app_state.h
//  -> can_frame_t, CAN_FROM_BUS, CAN_TO_BUS: src/app/can/can_protocol.h
//  -> can1_rx_fifo0_cb_info, can1_rx_fifo1_cb_info: src/app/can/can_state.h (CAN_Rx_Fifo_CB_Info type + extern), src/app/can/can_state.c (instances defined)
//  -> can_cmd_parse_info, CAN_Cmd_Parser_t: src/app/can/can_state.h/.c
//  -> g_q_4671_rx, g_q_2209_rx, g_q_sup_rx: src/app/app_state.h
//  -> g_4671_busy, g_2209_busy: src/app/can/can_state.h/.c
void vCAN_Gatekeeper_Task(void *pv) {
    can_frame_t frame;

    for (;;) {
        xQueueReceive(g_q_can_work, &frame, portMAX_DELAY);

        if (frame.direction == CAN_FROM_BUS) {
            // Drain ALL pending frames from both FIFOs
            while (can1_rx_fifo0_cb_info.buf_cnt || can1_rx_fifo1_cb_info.buf_cnt) {  // cb_info: src/app/can/can_state.h/.c
                CAN1_Read();  // ported from IO_Ctrl_Master — drains FIFO, fills can_cmd_parse_info

                uint32_t msg_id = can_cmd_parse_info.msg_id;
                uint8_t  cmd    = GET_CMD(msg_id);
                uint8_t  mot    = GET_MOT(msg_id);

                can_cmd_t dispatch_cmd = {
                    .can_id = msg_id, .type = cmd, .motor = mot,
                    .value = can_cmd_parse_info.data_64bit
                };

                // Route based on command type
                if (cmd == CHK_FW_PARAM || cmd == WR_FW_PARAM || cmd == RD_FW_PARAM) {
                    xQueueSend(g_q_sup_rx, &dispatch_cmd, 0);
                } else if (is_2209_command(cmd, mot)) {
                    xQueueSend(g_q_2209_rx, &dispatch_cmd, 0);
                } else {
                    if (is_move_command(msg_id)) {
                        if (g_4671_busy || g_2209_busy)
                            send_error_reply(msg_id, ERR_BUSY);
                        else {
                            xQueueSend(g_q_4671_rx, &dispatch_cmd, 0);
                            g_4671_busy = true;
                        }
                    } else {
                        xQueueSend(g_q_4671_rx, &dispatch_cmd, 0);
                    }
                }
            }
        } else {
            // CAN_TO_BUS — transmit on CAN bus
            CAN1_Write(frame.can_id, frame.payload.data, frame.dlc);
            // ported from IO_Ctrl_Master: formats CAN_TX_BUFFER, calls CAN1_MessageTransmitFifo

            // Clear busy flag on move completion
            if (frame.payload.data[1] == COMPLETE_MOVE_DONE) {
                if (frame.payload.data[0] == MOTOR_REELER1) g_4671_busy = false;
                else                                       g_2209_busy = false;
            }
        }

        g_heartbeat_can++;
    }
}
```

### Two-Hop Elimination (IO_Ctrl_Master vs GTron)

| IO_Ctrl_Master | GTron |
|----------------|-------|
| CAN ISR -> xcan_rd_wr_queue -> CAN_Tasks -> xcmd_parser_queue -> parser task | CAN ISR -> g_q_can_work -> CAN_GATEKEEPER -> motor/supervisor queue directly |
| 2 hops, 2 queues, 2 tasks | 1 hop, 1 queue, 1 task |

The gatekeeper IS the parser. No separate parser task or xcmd_parser_queue.

---

## CAN ID Structure (From Existing Protocol)

```c
// 29-bit CAN ID: (ad << 25) | (cmd << 17) | (typ << 9) | (mot)
#define CAN_ID(ad, cmd, typ, mot)  ((ad << 25) | (cmd << 17) | (typ << 9) | (mot))
#define GET_AD(msg_id)             ((msg_id >> 25) & 0x0F)
#define GET_CMD(msg_id)            ((msg_id >> 17) & 0xFF)
#define GET_TYP(msg_id)            ((msg_id >> 9) & 0xFF)
#define GET_MOT(msg_id)            (msg_id & 0x1FF)
```

### Axis Addresses (ad field)

```
X = 0x01, Y = 0x02, Z = 0x03, RF = 0x04, FP = 0x05
```

### Command Types (cmd field — subset used for routing)

| cmd | Name | Route To |
|-----|------|----------|
| 0x00 | MVP (Move Position) | Motor RX queue |
| 0x01 | RFS (Reference Search) | TMC4671_RX |
| 0x02 | MST (Motor Stop) | Motor RX queue |
| 0x03 | SAP (Set Axis Parameter) | Motor RX queue |
| 0x04 | GAP (Get Axis Parameter) | Motor RX queue |
| 0x05 | ROL (Rotate Left) | TMC4671_RX |
| 0x06 | ROR (Rotate Right) | TMC4671_RX |
| 0x80 | CHK_FW_PARAM | g_q_sup_rx |
| 0x82 | WR_FW_PARAM | g_q_sup_rx |
| 0x84 | RD_FW_PARAM | g_q_sup_rx |
| 0xC4 | RFS_DISTANCE | TMC4671_RX |
| 0xC5 | START_RANGE | TMC4671_RX |
| 0xC6 | END_RANGE | TMC4671_RX |
| 138 | Ping / MoveDonePing / RefSearchPing | TMC4671_RX |

### can_cmd_parse_info (Decoded CAN Frame — From IO_Ctrl_Master)

CAN1_Read() fills this struct using the raw buffer parsing functions ported from IO_Ctrl_Master:

```c
// File: src/app/can/can_state.h (ported from IO_Ctrl_Master/IOCtrl1.X/global_vars.h)
typedef struct {
    uint8_t  dlc;
    uint8_t  data[8];
    uint32_t msg_id;
} CAN_Cmd_Parser_t;

// File: src/app/can/can_state.c
CAN_Cmd_Parser_t can_cmd_parse_info;
```

The parsing functions (`get_can_id_from_buffer`, `get_can_dlc_from_buffer`, `get_can_data_from_buffer`) extract the 29-bit ID, DLC, and 8-byte payload from the 16-byte raw CAN FIFO buffer. These are ported directly from IO_Ctrl_Master into `src/app/can/can_gatekeeper.c`.

### Command Routing Logic

```c
// File: src/app/can/can_gatekeeper.c (inside vCAN_Gatekeeper_Task)
//  -> GET_CMD, GET_MOT, CHK_FW_PARAM etc.: src/app/can/can_protocol.h
//  -> g_q_sup_rx, g_q_4671_rx, g_q_2209_rx: src/app/app_state.h
uint8_t cmd = GET_CMD(can_cmd_parse_info.msg_id);
uint8_t mot = GET_MOT(can_cmd_parse_info.msg_id);

if (cmd == CHK_FW_PARAM || cmd == WR_FW_PARAM || cmd == RD_FW_PARAM) {
    target_q = g_q_sup_rx;
} else if (cmd == RFS_DISTANCE || cmd == START_RANGE || cmd == END_RANGE) {
    target_q = g_q_4671_rx;   // These are TMC4671 motor params, not flash params
} else {
    target_q = (mot <= TMC2209_MOTOR_LAST) ? g_q_2209_rx : g_q_4671_rx;
}
```

### can_cmd_t (Internal Dispatch Struct)

```c
// File: src/app/can/can_state.h
typedef struct {
    uint32_t   can_id;    // original CAN ID for reply routing
    uint8_t    type;      // cmd field from CAN ID
    uint8_t    motor;     // target motor ID
    int32_t    value;     // data payload as signed 32-bit
    uint8_t    extra[4];  // additional bytes if needed
} can_cmd_t;    // 4 + 1 + 1 + 2pad + 4 + 4 = 16 bytes
```

---

## Move Arbitration

Only one motor moves at a time. Gatekeeper tracks two busy flags.

```c
bool g_4671_busy;   // REELER motor (TMC4671)
bool g_2209_busy;   // GUIDE or VARREST (TMC2209)
```

### New Move Command

```c
if (is_move_command(msg_id)) {
    if (g_4671_busy || g_2209_busy) {
        send_error_reply(msg_id, ERR_BUSY);
    } else {
        can_cmd_t cmd = { .can_id = msg_id, .type = cmd, .motor = mot, .value = val };
        xQueueSend(target_q, &cmd, 0);
        if (mot == REELER_MOTOR_1) g_4671_busy = true;
        else                       g_2209_busy = true;
    }
}
```

### Move Completion

Motor tasks signal completion via TO_BUS frames. Gatekeeper clears the busy flag when transmitting the completion frame:

```c
// Completion frame payload format:
//   payload.data[0] = motor ID
//   payload.data[1] = completion reason (COMPLETE_MOVE_DONE / COMPLETE_LIMIT_HIT / COMPLETE_ERROR)

if (frame.direction == CAN_TO_BUS) {
    CAN1_Write(frame.can_id, frame.payload.data, frame.dlc);

    if (frame.payload.data[1] == COMPLETE_MOVE_DONE ||
        frame.payload.data[1] == COMPLETE_ERROR) {
        if (frame.payload.data[0] == MOTOR_REELER1) g_4671_busy = false;
        else                                       g_2209_busy = false;
    }
}
```

### Query Reply Timing

- Host sends GAP (Get Actual Position) → gatekeeper queues to motor task
- Motor task processes on next tick (<=1ms) -> reads position -> queues TO_BUS frame
- Gatekeeper transmits next wake -> round trip <=2ms
- Host CAN timeout: 100ms -> 50x margin

---

## Flash Parameters Via CAN

The `can_frame_t` design allows the gatekeeper to treat flash commands identically to motor commands — just routed to a different queue.

```
HOST → CAN → CAN ISR → g_q_can_work (FROM_BUS)
  → CAN_GATEKEEPER: GET_CMD = CHK_FW_PARAM → dispatch to g_q_sup_rx
  → SUPERVISOR: drain g_q_sup_rx → process flash op → push TO_BUS to g_q_can_work
  -> CAN_GATEKEEPER: drain TO_BUS -> CAN1_Write(reply)
```

No separate flash-specific mechanism. SUPERVISOR_TASK uses the same `g_q_can_work` for its replies that motor tasks use.

---

## Init Sequence (Ported From IO_Ctrl_Master's call_All_Init_Funcs_Vars)

```c
// File: main.c (pre-scheduler init section)
//  -> CAN1_MessageRAMConfigSet, CAN1_TxFifoCallbackRegister, CAN1_RxFifoCallbackRegister: Harmony CAN PLIB
//  -> CAN1_RxFifo0Callback, CAN1_RxFifo1Callback: src/app/can/can_isr_callbacks.c
//  -> CAN1_TxFifoCallback: src/app/can/can_isr_callbacks.c
//  -> g_q_can_work, qbuf_can_work, sq_can_work: src/app/app_state.c

// CAN message RAM (aligned, from IO_Ctrl_Master pattern)
// Defined in: src/app/can/can_state.c
uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(32)));

// Register callbacks (Harmony PLIB API — identical to IO_Ctrl_Master)
CAN1_MessageRAMConfigSet(Can1MessageRAM);
CAN1_TxFifoCallbackRegister(CAN1_TxFifoCallback, (uintptr_t)NULL);
CAN1_RxFifoCallbackRegister(CAN_RX_FIFO_0, CAN1_RxFifo0Callback, (uintptr_t)NULL);
CAN1_RxFifoCallbackRegister(CAN_RX_FIFO_1, CAN1_RxFifo1Callback, (uintptr_t)NULL);

// Static queues (GTron: xQueueCreateStatic, not dynamic xQueueCreate)
g_q_can_work = xQueueCreateStatic(16, sizeof(can_frame_t), qbuf_can_work, &sq_can_work);

// FIFO callback tracking state (same pattern as IO_Ctrl_Master)
// CAN_Rx_Fifo_CB_Info type declared in: src/app/can/can_state.h
// Instances defined in: src/app/can/can_state.c
can1_rx_fifo0_cb_info.buf_cnt = 0;
can1_rx_fifo0_cb_info.no_of_msgs = 0;
can1_rx_fifo1_cb_info.buf_cnt = 0;
can1_rx_fifo1_cb_info.no_of_msgs = 0;
```

## Bug Fixes Applied From IO_Ctrl_Master

| # | IO_Ctrl_Master Bug (File:Line) | Fix Applied |
|---|-------------------|-------------|
| 1 | `xHigherPriorityTaskWoken = pdTRUE` before `xQueueSendFromISR` (`interrupt_callbacks.c:148`) | `= pdFALSE` — only set to TRUE by the API if a task was actually woken |
| 2 | `can_queue_struct` global shared by two ISRs (`interrupt_callbacks.c:145-149`, `interrupt_callbacks.c:190-195`) | Local `can_frame_t` on each ISR's stack, copied into queue by value |
| 3 | `xQueueSend(xcmd_parser_queue, ..., portMAX_DELAY)` — infinite block (`can.c:430`) | `xQueueSend(..., 0)` — non-blocking dispatch |
| 4 | `canData.state = CAN_STATE_SERVICE_TASKS` unreachable after break (`can.c:442`) | Removed state machine entirely. `xQueueReceive` blocking IS the state. |
| 5 | `xEventGroupClearBits(grp, 0)` no-op (`init_funcs.c:80`) | Removed. Event groups start at zero. |
| 6 | `all_headers.h` (`can.h:11`, `global_vars.h:11`, `interrupt_callbacks.h:11`) | Removed. Each `.c` includes only what it needs. |
| 7 | `xQueueCreate` (dynamic allocation) (`init_funcs.c:60,62`) | `xQueueCreateStatic` in GTron |
| 8 | WDT commented out (`init_funcs.c:95`) | `WDT_Initialize()` + `WDT_Clear()` in SUPERVISOR (see doc 05) |

## Why Unified Queue Over Separate TX/RX + Semaphore

| Aspect | Separate Queues + Semaphore | Unified Queue |
|--------|---------------------------|---------------|
| RTOS objects | 3 queues + 1 sem = 4 | 1 queue |
| RAM overhead | ~460 bytes | 256 bytes |
| Gatekeeper wake source | Semaphore (from 3 different ISR/task sources) | Single queue receive |
| TO_BUS from motor tasks | Separate TX queue -> semaphore poke | Same queue as FROM_BUS |
| Dropped frames | Handled in separate queue | All centralized |
| Code complexity | 2 paths (FROM_ISR + FROM_TASK) | 1 path (all via queue) |
