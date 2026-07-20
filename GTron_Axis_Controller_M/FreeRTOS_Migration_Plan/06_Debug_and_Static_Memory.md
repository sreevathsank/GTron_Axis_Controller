# 06 — Debug Print and Static Memory Allocation

## Non-Blocking Debug Architecture

`DBG_Printf()` returns immediately. A dedicated idle-priority task drains messages to the DMA UART.

```
┌──────────┐    ┌──────────┐    ┌──────────┐
│ Any Task │    │ Any Task │    │ Any Task │
│ DBG_Printf│   │ DBG_Printf│   │ DBG_Printf│
└────┬─────┘    └────┬─────┘    └────┬─────┘
     │               │               │
     │  vsnprintf to local stack buf  │
     │  xQueueSend(g_q_debug, buf, 0)│
     │               │               │
     └───────────────┼───────────────┘
                     ▼
            ┌────────────────┐
            │  g_q_debug     │  16 x 132 bytes
            └───────┬────────┘
                    │  xQueueReceive(portMAX_DELAY)
                    ▼
            ┌────────────────┐
            │  DEBUG_TASK    │  Priority 0 (idle)
            │  transport_send│  DMA → SERCOM7
            └────────────────┘
```

### DBG_Printf (Callable From Any Task)

```c
// File: src/app/debug/dbg_print_config.h
//  -> Used by: src/app/debug/dbg_print.c
#define ERR_LVL_ERROR    0
#define ERR_LVL_WARNING  1
#define ERR_LVL_INFO     2
#define ERR_LVL_DEBUG    3

void DBG_Printf(uint8_t level, const char *fmt, ...);
```

```c
// File: src/app/debug/dbg_print.c
//  -> g_q_debug: src/app/app_state.h
#define DBG_MSG_BUF_SIZE  132   // 4-byte prefix + 128-byte message

void DBG_Printf(uint8_t level, const char *fmt, ...) {
    char buf[DBG_MSG_BUF_SIZE];
    buf[0] = (char)level;       // severity as first byte

    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(&buf[1], DBG_MSG_BUF_SIZE - 1, fmt, args);
    va_end(args);

    if (len > 0) {
        xQueueSend(g_q_debug, buf, 0);  // non-blocking, drop if queue full
    }
}
```

- Formats on caller's **stack** → no shared buffer, no mutex needed
- Pushes to queue → returns immediately
- Queue full: message silently dropped (debug output is best-effort)
- NO `DBG_Printf` calls from ISR context (requires `FromISR` variant if needed later)

### DEBUG_TASK

```c
// File: src/app/debug/debug_task.c
//  -> g_q_debug: src/app/app_state.h
//  -> transport_send(): src/app/debug/dbg_transport.c (ported from old Bring_Up/Debug/dbg_transport.c)
void vDebug_Task(void *pv) {
    char buf[DBG_MSG_BUF_SIZE];
    for (;;) {
        if (xQueueReceive(g_q_debug, buf, portMAX_DELAY) == pdTRUE) {
            // buf[0] = severity (can filter here if desired)
            transport_send(&buf[1], strlen(&buf[1]));
            // transport_send blocks up to ~2.5ms at 2 Mbaud for 512B
            // Blocking here is safe — this is the lowest priority task
            // The DMA continues in background even if this task is preempted
        }
    }
}
```

**No heartbeat.** DEBUG_TASK cannot deadlock — its only blocking point is `xQueueReceive`. If no messages arrive, it blocks forever harmlessly. If a message arrives, it processes and blocks again.

### Existing DMA Transport (Unchanged From Old Project)

`transport_send()` writes data to the DMA buffer, configures DMAC Channel 0 to transfer byte-by-byte to SERCOM7 DATA register, and waits for the DMA transfer complete interrupt. At 2 Mbaud, a 512-byte message blocks ~2.56ms within the debug task. Since the debug task is the lowest priority, this blocking never delays motor, CAN, or supervisor tasks.

### Queue Sizing

16 slots x 132 bytes = 2,112 bytes. With 16 slots:
- All 4 user tasks can queue messages simultaneously
- At 2 Mbaud drain: each 128B message ~640us to drain
- 16 messages = ~10ms backlog at maximum debug rate
- Production builds log at ERROR level only → queue rarely fills

---

## Static Memory Allocation

`configTOTAL_HEAP_SIZE = 0` — no dynamic allocation. All RTOS objects created with `x*CreateStatic()`.

### Task Stacks and TCBs

```c
// File: src/app/app_state.c
// All static RTOS objects — declarations in src/app/app_state.h
#define STACK_TMC4671      256    // 1024 bytes
#define STACK_CAN          160    // 640 bytes
#define STACK_TMC2209      192    // 768 bytes
#define STACK_SUPERVISOR   160    // 640 bytes
#define STACK_DEBUG        160    // 640 bytes

static StackType_t  stack_tmc4671[STACK_TMC4671];
static StackType_t  stack_can[STACK_CAN];
static StackType_t  stack_tmc2209[STACK_TMC2209];
static StackType_t  stack_supervisor[STACK_SUPERVISOR];
static StackType_t  stack_debug[STACK_DEBUG];

static StaticTask_t tcb_4671, tcb_can, tcb_2209, tcb_sup, tcb_dbg;
TaskHandle_t        h_4671, h_can, h_2209, h_sup, h_dbg;
```

### Queues

```c
// CAN work queue — 16 slots x 16 bytes = 256 bytes
#define Q_CAN_WORK_LEN  16
static uint8_t       qbuf_can_work[Q_CAN_WORK_LEN * sizeof(can_frame_t)];
static StaticQueue_t sq_can_work;
QueueHandle_t        g_q_can_work;

// Motor command queues — 8 slots x 16 bytes = 128 bytes each
#define Q_MOTOR_CMD_LEN  8
#define Q_MOTOR_CMD_SIZE 16
static uint8_t       qbuf_4671_rx[Q_MOTOR_CMD_LEN * Q_MOTOR_CMD_SIZE];
static uint8_t       qbuf_2209_rx[Q_MOTOR_CMD_LEN * Q_MOTOR_CMD_SIZE];
static StaticQueue_t sq_4671_rx, sq_2209_rx;
QueueHandle_t        g_q_4671_rx, g_q_2209_rx;

// Supervisor command queue — 8 slots x 16 bytes = 128 bytes
static uint8_t       qbuf_sup_rx[Q_MOTOR_CMD_LEN * Q_MOTOR_CMD_SIZE];
static StaticQueue_t sq_sup_rx;
QueueHandle_t        g_q_sup_rx;

// Debug queue — 16 slots x 132 bytes = 2,112 bytes
#define Q_DEBUG_LEN   16
#define Q_DEBUG_SIZE  132
static uint8_t       qbuf_debug[Q_DEBUG_LEN * Q_DEBUG_SIZE];
static StaticQueue_t sq_debug;
QueueHandle_t        g_q_debug;
```

### Mutex

```c
static StaticSemaphore_t sm_sercom3;
SemaphoreHandle_t        g_m_sercom3;
```

### Creation (In Init, Before vTaskStartScheduler)

```c
// File: main.c (pre-scheduler init section)
// All static buffers declared in src/app/app_state.c

// Tasks
h_4671 = xTaskCreateStatic(vTMC4671_Task,    "4671", STACK_TMC4671,    NULL, 4, stack_tmc4671,    &tcb_4671);
h_can  = xTaskCreateStatic(vCAN_Gatekeeper,  "CAN",  STACK_CAN,        NULL, 3, stack_can,        &tcb_can);
h_2209 = xTaskCreateStatic(vTMC2209_Task,    "2209", STACK_TMC2209,    NULL, 2, stack_tmc2209,    &tcb_2209);
h_sup  = xTaskCreateStatic(vSupervisor_Task, "SUP",  STACK_SUPERVISOR, NULL, 1, stack_supervisor, &tcb_sup);
h_dbg  = xTaskCreateStatic(vDebug_Task,      "DBG",  STACK_DEBUG,      NULL, 0, stack_debug,      &tcb_dbg);

// Queues
g_q_can_work = xQueueCreateStatic(Q_CAN_WORK_LEN, sizeof(can_frame_t), qbuf_can_work, &sq_can_work);
g_q_4671_rx  = xQueueCreateStatic(Q_MOTOR_CMD_LEN, Q_MOTOR_CMD_SIZE,  qbuf_4671_rx,  &sq_4671_rx);
g_q_2209_rx  = xQueueCreateStatic(Q_MOTOR_CMD_LEN, Q_MOTOR_CMD_SIZE,  qbuf_2209_rx,  &sq_2209_rx);
g_q_sup_rx   = xQueueCreateStatic(Q_MOTOR_CMD_LEN, Q_MOTOR_CMD_SIZE,  qbuf_sup_rx,   &sq_sup_rx);
g_q_debug    = xQueueCreateStatic(Q_DEBUG_LEN,      Q_DEBUG_SIZE,      qbuf_debug,    &sq_debug);

// Mutex
g_m_sercom3  = xSemaphoreCreateMutexStatic(&sm_sercom3);
```

### RAM Budget

| Category | Size |
|----------|------|
| Task stacks | 3,712 bytes |
| Task TCBs (5 x ~120B) | 600 bytes |
| Queue buffers | 2,752 bytes |
| Queue control blocks (5 x ~80B) | 400 bytes |
| Mutex control block | 80 bytes |
| Kernel structures | ~2,000 bytes |
| **Total RTOS overhead** | **~9,544 bytes** |
| **Available for globals** | **~23,224 bytes** |

Total SRAM: 32,768 bytes.

### Stack Overflow Detection

```c
#define configCHECK_FOR_STACK_OVERFLOW  2
```

With static allocation, FreeRTOS fills each stack with `0xA5` at task creation. At every context switch, the kernel checks the watermark. An overflow hook fires.

During Phase 4/5 verification, check stack high watermarks via `uxTaskGetStackHighWaterMark()`:
```c
DBG_Printf(ERR_LVL_DEBUG, "4671 stack free: %u\n", uxTaskGetStackHighWaterMark(h_4671));
// ... for all tasks
```

Adjust stack sizes with 20% margin above worst-case observed usage.
