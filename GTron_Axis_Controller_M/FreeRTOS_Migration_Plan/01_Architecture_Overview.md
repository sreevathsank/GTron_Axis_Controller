# 01 — Architecture Overview

## Project Context

- **New project** created from scratch in MPLAB X IDE using Harmony V3 + MCC Melody
- **Target MCU:** ATSAMC21N18A, Cortex-M0+, 48 MHz, 32KB SRAM, 256KB Flash
- **Old project** serves as a reference library — port drivers, don't port generated code
- **Motor configuration:** 1x TMC4671 (SPI, REELER motor) + 2x TMC2209 (UART, GUIDE + VARREST motors)
- **Only one motor moves at a time**

## Hardware Summary

| Resource | MCU Peripheral | Device | Speed |
|----------|---------------|--------|-------|
| Motor 1 (REELER) | SERCOM0 SPI Master | TMC4671 FOC controller | 2 MHz |
| Motor 2 (GUIDE) | SERCOM5 UART | TMC2209 stepper | 230400 baud, single-wire half-duplex |
| Motor 3 (VARREST) | SERCOM5 UART (same bus, diff addr) | TMC2209 stepper | 230400 baud |
| IO Expander | SERCOM3 SPI Master | MCP23S08 | 50 kHz (shared bus with flash) |
| External Flash | SERCOM3 SPI Master | Adesto SPI NOR | 50 kHz |
| CAN Bus | CAN1 | System bus | 500 kbps, 29-bit extended IDs |
| Debug UART | SERCOM7 USART, DMA Ch0 | PC terminal | 2 Mbaud |
| TMC4671 clock | TC1 PWM output | 25 MHz square wave | 50 MHz GCLK → 25 MHz |
| Ramp tick | TC4 timer | 1ms interval | 2 MHz GCLK |
| Step tracking tick | TC2 timer | 1ms interval | 2 MHz GCLK |
| Microsecond counter | TC0 free-running timer | 1 MHz | 2 MHz GCLK |
| Axis ID | ADC0 Ch9 | Voltage divider on PC01 | 48 MHz |

## Task Map

```
Pri 4 (highest): TMC4671_TASK    [1024B]   1ms TC4 tick notify
                   REELER master            RX queue (8 slots) from CAN
                   Owns: SERCOM0, TMC4671 GPIOs, REELER_INT GPIO
                   Handles: S-ramp, trapezoidal ramp, velocity knob,
                            homing (rotary encoder Z + linear encoder Z),
                            hybrid trigger (inspection / n-shot / encoder mode),
                            limit switch stops (LIM_RT / LIM_LFT)

Pri 3:          CAN_GATEKEEPER   [640B]    Unified CAN work queue (16 x 16B)
                   gatekeeper              Dispatches to: TMC4671_RX, TMC2209_RX, SUPERVISOR_RX
                   Owns: CAN1 peripheral
                   Enforces: move arbitration (only 1 motor at a time)

Pri 2:          TMC2209_TASK     [768B]    TC2 1ms tick notify + IOXP_INT EIC notify
                   STEPPER master          RX queue (8 slots) from CAN
                   Owns: SERCOM5, SERCOM3 mutex (for IOXP reads)
                   Handles: MSCNT step tracking, DIAG stall detection,
                            guide motor limit switches (via IOXP)

Pri 1:          SUPERVISOR_TASK  [640B]    vTaskDelay(10ms) periodic
                   housekeeping            RX queue (8 slots) from CAN
                   Owns: WDT, LEDs, SERCOM3 mutex (for flash ops), g_flash_busy
                   Handles: TLV flash parameter read/write/verify,
                            WDT heartbeat monitoring, LED status

Pri 0 (idle):   DEBUG_TASK       [640B]    Queue receive (16 x 132B)
                   debug drain             Owns: SERCOM7 DMA UART
                   No heartbeat
```

## Inter-Task Communication

```
TC4 ISR (1ms)
    │  vTaskNotifyGiveFromISR(h_4671)
    ▼
┌──────────────────────────────────────────────────────────────────┐
│  TMC4671_TASK (prio 4)                                           │
│                                                                   │
│  Each tick:                                                       │
│    1. Drain g_q_4671_rx (CAN commands)                           │
│    2. Read g_limit_flags (ISR-set: LIM_RT / LIM_LFT)             │
│    3. check_For_Hybrid_Trigger() — reads position, fires camera  │
│    4. One step of motion FSM (STOPPED/S_RAMP/TRAP/VEL/HOMING)    │
│    5. If move complete → push TO_BUS frame to g_q_can_work       │
│                                                                   │
│  TO_BUS frames (responses / events):                              │
│    g_q_can_work ← TMC4671_TASK (move done, slip error, pos reply) │
└──────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────┐
│  CAN_GATEKEEPER (prio 3)                                         │
│                                                                   │
│  Block on xQueueReceive(g_q_can_work)                            │
│                                                                   │
│  FROM_BUS frames (CAN ISR pushed):                                │
│    GET_CMD(can_id) dispatch:                                      │
│      MVP, RFS, MST, SAP, GAP, ROL, ROR        → g_q_4671_rx     │
│      TMC2209 motor moves, config queries       → g_q_2209_rx     │
│      CHK_FW_PARAM, WR_FW_PARAM, RD_FW_PARAM   → g_q_sup_rx      │
│      RFS_DISTANCE, START_RANGE, END_RANGE      → g_q_4671_rx     │
│                                                                   │
│  TO_BUS frames (motor tasks + supervisor):                        │
│    can_Send(can_id, dlc, data) — transmit on CAN bus             │
│                                                                   │
│  Move arbitration:                                                │
│    g_4671_busy / g_2209_busy — reject new MOVE if either true    │
│    Clear on TO_BUS completion frame (TX_EVENT_MOVE_COMPLETE)     │
└──────────────────────────────────────────────────────────────────┘
        │                    │                    │
   ┌────▼──────┐       ┌─────▼─────┐       ┌─────▼─────┐
   │ q_4671_rx │       │ q_2209_rx │       │ q_sup_rx  │
   │  8 x 16B  │       │  8 x 16B  │       │  8 x 16B  │
   └───────────┘       └───────────┘       └─────┬─────┘
                                                 │
┌────────────────────────────────────────────────┼─────────────────┐
│  TMC2209_TASK (prio 2)                         │                  │
│                                                 │                  │
│  Wake sources: TC2 1ms + IOXP EIC notify        │                  │
│  On IOXP notify: xSemaphoreTake(g_m_sercom3),   │                  │
│    read IOXP, detect guide limits, stop motor    │                  │
│  On each tick: drain g_q_2209_rx, check DIAG,    │                  │
│    poll MSCNT if moving                           │                  │
│  TO_BUS → g_q_can_work (responses, events)       │                  │
└──────────────────────────────────────────────────┼─────────────────┘
                                                   │
┌──────────────────────────────────────────────────┼─────────────────┐
│  SUPERVISOR_TASK (prio 1)                        │                  │
│                                                   ▼                  │
│  Every 10ms:                                      │                  │
│    Drain g_q_sup_rx: CHK/WR/RD_FW_PARAM          │                  │
│    For flash ops: xSemaphoreTake(g_m_sercom3),    │                  │
│      set g_flash_busy, do flash r/w, release      │                  │
│    Every 50ms: check heartbeats, pet WDT          │                  │
│    Update LEDs                                    │                  │
│  TO_BUS → g_q_can_work (flash read replies)       │                  │
└──────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────┐
│  DEBUG_TASK (prio 0)                                              │
│                                                                   │
│  All tasks: DBG_Printf() → vsnprintf → xQueueSend(g_q_debug, 0) │
│  Debug task: xQueueReceive → transport_send(DMA → SERCOM7)       │
└──────────────────────────────────────────────────────────────────┘
```

## Queues

| Queue | Direction | Slots x Size | Purpose |
|-------|-----------|-------------|---------|
| `g_q_can_work` | ISR + motor tasks + supervisor → CAN gatekeeper | 16 × 16B | Unified CAN read/write queue |
| `g_q_4671_rx` | CAN gatekeeper → TMC4671 | 8 × 16B | Motor commands + queries |
| `g_q_2209_rx` | CAN gatekeeper → TMC2209 | 8 × 16B | Stepper commands + queries |
| `g_q_sup_rx` | CAN gatekeeper → SUPERVISOR | 8 × 16B | Flash parameter commands |
| `g_q_debug` | All tasks → DEBUG | 16 × 132B | Non-blocking printf |

## Resource Ownership

| Peripheral | Owner | Lock |
|-----------|-------|------|
| SERCOM0 (TMC4671 SPI) | TMC4671_TASK exclusive | None |
| SERCOM3 (Flash + IOXP) | Shared | Mutex `g_m_sercom3` |
| SERCOM5 (TMC2209 UART) | TMC2209_TASK exclusive | None |
| SERCOM7 (Debug DMA) | DEBUG_TASK exclusive | None (queue dispatch) |
| CAN1 | CAN_GATEKEEPER exclusive | None |
| TC4 (ramp tick) | ISR → TMC4671_TASK notify | — |
| TC2 (step tick) | ISR → TMC2209_TASK notify | — |
| TC0 (microsecond) | Free-running counter, no ISR | — |

## can_frame_t (Uses Old Project's can_union_type)

```c
typedef union {
    unsigned char data[8];
    int64_t data_64bit;
} can_union_type;

typedef enum { CAN_FROM_BUS, CAN_TO_BUS } can_direction_t;

typedef struct {
    uint32_t         can_id;
    can_direction_t  direction;
    uint8_t          dlc;           // 0-8
    can_union_type   payload;
} can_frame_t;   // 4 + 1 + 1 + 2pad + 8 = 16 bytes
```

## Key Design Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Task count | 5 | One per motor bus, one CAN, one housekeeping, one debug |
| Init timing | Before scheduler | Linear init chain, no sync complexity |
| Memory | Static allocation | 32KB SRAM, no fragmentation |
| Debug | Non-blocking queue | `DBG_Printf` returns immediately |
| WDT | Heartbeat counters | Detects per-task starvation |
| CAN | Single unified queue | `can_frame_t` with direction field |
| Move arbitration | Gatekeeper busy flags | Only 1 motor moves at a time |
| ISR priority | All at NVIC 2 | All FromISR-capable, flat model |
| SERCOM3 | Mutex + g_flash_busy | Flash ops don't starve IOXP reads during motion |
| Limits ownership | Each motor task owns its limits | TMC4671 → LIM_RT/LIM_LFT. TMC2209 → IOXP |
| State machine | Not needed | switch/enum sufficient for motion states |
| Globals | Per-module _internal.h pattern | Split 60+ globals into 6 module files |
| All_Headers.h | Removed | Each .c includes only what it needs |
| volatile | ISR-shared scalars only | Drop volatile from task-owned data |
| CRITICAL_SECTION | Removed | Task preemption handles mutual exclusion |
