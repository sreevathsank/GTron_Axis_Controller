# 10 — Module File Structure and Variable Reorganization

## Source Tree

```
src/
├── main.c                          // SYS_Initialize() → init sequence → create objects → vTaskStartScheduler()
│
├── config/                         // MCC-generated (do not edit)
│   └── FreeRTOSConfig.h
│
├── app/
│   ├── app_config.h                // Project-wide macros, dead-code-free Macros.h
│   │
│   ├── app_state.h                 // Cross-module globals (ISR flags, RTOS handles, motor structs)
│   ├── app_state.c                 // Instance definitions for externs in app_state.h
│   │
│   ├── can/
│   │   ├── can_protocol.h          // CAN ID macros, enums, can_union_type (from IMM_CAN_Message_Id.h)
│   │   ├── can_state.h             // Internal: g_4671_busy, g_2209_busy, can_cmd_t
│   │   ├── can_state.c
│   │   ├── can_gatekeeper.c        // vCAN_Gatekeeper_Task + dispatch logic
│   │   ├── can_read.c/h            // CAN frame reception (PLIB-adapted)
│   │   ├── can_write.c/h           // CAN frame transmission (PLIB-adapted)
│   │   └── can_cmd_parser.c/h      // Motor_Info_t struct + parse_GTron_CAN_Msg_Data() (from gtron_can_cmd_parser)
│   │
│   ├── motor_4671/
│   │   ├── motor_4671_internal.h   // ALL motion globals (ramp, limits, hybrid state, velocity knob)
│   │   ├── motor_4671_internal.c   // Instance definitions
│   │   ├── motor_4671_task.c       // vTMC4671_Task
│   │   ├── motor_4671_init.c/h     // TMC4671 init sequence (from DBG_bring_up)
│   │   ├── motion.c/h              // Ramp math (S-curve + trapezoidal) (from Motion.c)
│   │   ├── hybrid_trigger.c/h      // Hybrid trigger (inspection, n-shot, encoder mode)
│   │   └── limit_handler.c/h       // LIM_RT/LIM_LFT → stop + homing sequence
│   │
│   ├── motor_2209/
│   │   ├── motor_2209_internal.h   // Step counter, IOXP state, TMC2209 move flags
│   │   ├── motor_2209_internal.c
│   │   ├── motor_2209_task.c       // vTMC2209_Task
│   │   ├── motor_2209_init.c/h     // TMC2209 motor configuration
│   │   └── step_counter.c/h        // MSCNT polling + step tracking (from Step_Counter)
│   │
│   ├── supervisor/
│   │   ├── supervisor_internal.h   // Heartbeat counters, LED state, flash param cache
│   │   ├── supervisor_internal.c
│   │   ├── supervisor_task.c       // vSupervisor_Task
│   │   ├── tlv_flash.c/h           // TLV parameter encode/decode (from tlv_flash.c)
│   │   └── flash_ops.c/h           // Flash sector/page r/w wrappers (from ext_flash.c, adapted)
│   │
│   ├── debug/
│   │   ├── debug_task.c            // vDebug_Task
│   │   ├── dbg_print.c/h           // DBG_Printf (queue-based, non-blocking)
│   │   ├── dbg_print_config.h      // Severity levels
│   │   └── dbg_transport.c/h       // DMA-driven SERCOM7 UART (from old project)
│   │
│   └── drivers/
│       ├── tmc4671/                // TMC-API/tmc/ic/TMC4671/ (entire directory)
│       ├── tmc2209/                // TMC2209.c/h, TMC2209_HW_Abstraction.h
│       ├── io_expander/            // spi_io_expander.c/h (MCP23S08)
│       └── ext_flash/              // ext_flash.c/h (Adesto NOR flash, low-level)
```

## Include Rules

- `app_state.h` — included by tasks that need cross-module data (all 5 task files)
- `app_config.h` — included by any file that needs global macros
- `*_internal.h` — included ONLY by files within the same module directory. Never included by other modules.
- `can_protocol.h` — included by CAN gatekeeper + any module that constructs CAN frames
- Driver headers — included only by files that directly call those drivers

**No `All_Headers.h`.** Each `.c` includes exactly what it uses.

## Variable Reorganization: Complete Audit

### app_state.h (Cross-Module Globals)

```c
// File: src/app/app_state.h
// Instance definitions in: src/app/app_state.c
// Pin configuration (set at init, read-only thereafter)
extern axis_current    g_axis_id;
extern SouthBridge_t   g_sbridge_addr;

// ISR → task flags (volatile: written by ISR, read by exactly one task)
extern volatile bool   g_diag_pending;         // DIAG EIC → TMC2209_TASK
extern volatile uint8_t g_limit_flags;         // LIM EICs → TMC4671_TASK
#define LIM_RT_BIT   0x01
#define LIM_LFT_BIT  0x02
extern volatile bool   g_ioxp_int_pending;     // IOXP EIC → TMC2209_TASK

// Cross-task flags
extern volatile bool   g_flash_busy;           // SUPERVISOR (during flash ops) → both motor tasks

// Motor_Info_t instances (allocated statically, one per physical motor)
extern Motor_Info_t    g_motor_reeler1;
extern Motor_Info_t    g_motor_guide;
extern Motor_Info_t    g_motor_varrest1;
extern Motor_Info_t    g_motor_varrest2;
extern Motor_Info_t    g_motor_reeleradj1;
extern Motor_Info_t    g_motor_reeleradj2;
extern Motor_Info_t    g_motor_frontcam;
extern Motor_Info_t    g_motor_reeler2;

// Pointer array for indexed access (used by CAN parser dispatch)
extern Motor_Info_t   *mot_array[NO_OF_MOT_INDICES];

// Convenience pointers (set during init based on sbridge_addr)
extern Motor_Info_t   *p_reeler1_info;
extern Motor_Info_t   *p_guide_info;
extern Motor_Info_t   *p_varrest1_info;
extern Motor_Info_t   *p_varrest2_info;
extern Motor_Info_t   *p_reeleradj1_info;
extern Motor_Info_t   *p_reeleradj2_info;
extern Motor_Info_t   *p_frontcam_info;
extern Motor_Info_t   *p_reeler2_info;

// RTOS handles (needed to create tasks, use queues from modules)
extern QueueHandle_t   g_q_can_work;           // 16 x 16B
extern QueueHandle_t   g_q_4671_rx;            // 8 x 16B
extern QueueHandle_t   g_q_2209_rx;            // 8 x 16B
extern QueueHandle_t   g_q_sup_rx;             // 8 x 16B
extern QueueHandle_t   g_q_debug;              // 16 x 132B
extern SemaphoreHandle_t g_m_sercom3;          // mutex for flash + IOXP SPI bus

extern TaskHandle_t    h_4671, h_can, h_2209, h_sup, h_dbg;

// Heartbeat counters
extern volatile uint32_t g_heartbeat_can;
extern volatile uint32_t g_heartbeat_tmc4671;
extern volatile uint32_t g_heartbeat_tmc2209;
extern volatile uint32_t g_heartbeat_supervisor;
extern volatile uint32_t * const g_heartbeat_array[4];
```

### motor_4671_internal.h (TMC4671 Module Private)

```c
// File: src/app/motor_4671/motor_4671_internal.h
// Instance definitions in: src/app/motor_4671/motor_4671_internal.c
// Flash parameters
extern axis_parameters g_axis_params;   // PI gains, velocities, accel, jerk, encoder res

// Ramp parameters
extern rampParams       rParams;        // S-curve + trapezoidal ramp calculation state
extern trapezoidal_state ramp_State;    // STOP, ACCEL, CRUISE, DECEL, DO_NOTHING
extern s_state          s_curve_phase; // PHASE_1 through PHASE_7, DO_REPEAT

// Motion state
extern int32_t g_motion_state;          // STOPPED, S_RAMP, TRAPEZOIDAL, VELOCITY_KNOB, HOMING
extern int32_t g_target_position;
extern bool    g_move_just_completed;
extern bool    g_move_given_s_ramp;
extern bool    g_move_given_trapezoidal_ramp;

// Ramp temporaries
extern int32_t velocity_limit;
extern int32_t prev_velocity_limit;
extern double  v, v_temp, a_temp;
extern int32_t t, p, p_time, c_time;
extern bool    timer_flag, non_rep;

// Flash parameter
extern uint8_t repeat_ramp;

// Limiter / homing (CLEANED — bitfield only, no duplicate bools)
typedef struct {
    struct {
        uint16_t left_limit_hit       : 1;
        uint16_t right_limit_hit      : 1;
        uint16_t homing_active        : 1;
        uint16_t hit_limit_left       : 1;
        uint16_t hit_limit_right      : 1;
        uint16_t loop_active          : 1;
        uint16_t first_limit_hit      : 1;
        uint16_t other_limit_hit      : 1;
        uint16_t switch_seq_active    : 1;
        uint16_t homing_done          : 1;
        uint16_t z_first_hit          : 1;
        uint16_t z_second_hit         : 1;
        uint16_t rfs_ping_received    : 1;   // added from old rfs_ping_rxvd
        uint16_t reserved             : 3;
    } flags;
    int32_t right_limit_pos;
    int32_t left_limit_pos;
    int32_t home_position;
    int32_t zero_limit_pos;
    int32_t other_limit_pos;
    int32_t middle_position;
    int32_t soft_limit_high;
    int32_t soft_limit_low;
    int32_t switch_seq_state;
} Limits_t;
extern Limits_t g_limits;

// Velocity knob
typedef struct {
    struct {
        uint8_t reeler_rotate     : 1;
        uint8_t reeler_vel_timer  : 1;
        uint8_t sag_enabled       : 1;
        uint8_t reeler_move       : 1;
        uint8_t reeler_move_timer : 1;
        uint8_t direction         : 1;
    } flags;
    int32_t vel_state;
} Velocity_Knob_t;
extern Velocity_Knob_t  g_vel_knob;
extern int32_t          g_velocity_state;

// Autofocus
extern autofocus_vars g_autofocus;

// Timestamps
typedef struct {
    uint32_t move_start_time;
    uint32_t move_done_time;
} Timestamps;
extern Timestamps g_timestamp;

// Move completion tracking
extern uint32_t g_move_done_check_num;

// Init-only (used during pre-scheduler init, kept here for isolation)
typedef struct {
    int32_t acceleration;
    int32_t velocity;
    int32_t uq_ud;
} OpenLoopData;
extern OpenLoopData g_open_loop;
```

### motor_2209_internal.h (TMC2209 Module Private)

```c
// File: src/app/motor_2209/motor_2209_internal.h
// Instance definitions in: src/app/motor_2209/motor_2209_internal.c
// Step tracking
extern volatile int32_t g_step_count;   // NOT volatile (no ISR writes it). Keeping label for existing code compat.
extern uint32_t g_step_dir;

// Motor state
extern bool g_2209_moving;
extern bool g_2209_move_done;
extern uint8_t g_active_2209_motor;     // which TMC2209 motor is currently active

// IOXP guide limit state
extern bool g_guide_limit_hit;
extern uint8_t g_which_limit;

// UART handle
extern struct io_descriptor *g_io_tmc2209;  // Harmony USART handle
```

### can_state.h (CAN Module Private)

```c
// File: src/app/can/can_state.h
// Instance definitions in: src/app/can/can_state.c
// Busy flags for move arbitration
extern bool g_4671_busy;
extern bool g_2209_busy;

// CAN command dispatch struct
typedef struct {
    uint32_t   can_id;
    uint8_t    type;
    uint8_t    motor;
    int32_t    value;
    uint8_t    extra[4];
} can_cmd_t;

// CAN decoded frame struct (from IO_Ctrl_Master global_vars.h)
typedef struct {
    uint8_t  dlc;
    uint8_t  data[8];
    uint32_t msg_id;
} CAN_Cmd_Parser_t;
extern CAN_Cmd_Parser_t can_cmd_parse_info;

// CAN FIFO callback tracking (from IO_Ctrl_Master global_vars.h)
typedef struct {
    uint8_t   buf_cnt;
    uint8_t   no_of_msgs;
    uintptr_t context;
} CAN_Rx_Fifo_CB_Info;
extern CAN_Rx_Fifo_CB_Info can1_rx_fifo0_cb_info;
extern CAN_Rx_Fifo_CB_Info can1_rx_fifo1_cb_info;

// CAN message RAM (aligned, from IO_Ctrl_Master pattern)
extern uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(32)));
```

### supervisor_internal.h (SUPERVISOR Module Private)

```c
// File: src/app/supervisor/supervisor_internal.h
// Instance definitions in: src/app/supervisor/supervisor_internal.c
// LED state
extern uint8_t g_led_state;

// Flash parameter cache (if needed for CHK_FW_PARAM verification)
extern int32_t g_flash_param_cache[];
```

## Removed Variables (From Old Global_Vars.h)

| Old Variable | Disposition |
|-------------|-------------|
| `volatile uint8_t can_rx_int` | Replaced by `g_q_can_work` queue |
| `ad, cmd, typ, mot` | → Function-local in CAN dispatch |
| `crc, checksum` | → Function-local |
| `can_status, idx` | → Function-local |
| `trig_no, prev_trig_no` | Dead — use `Hybrid_t.gc` inside `Motor_Info_t` |
| `int32_t prev_sens_pos` | Dead — use `Hybrid_t.anchor_pos` |
| `bool motor_dir_rev` | Init-only local |
| `bool lim_edge_detection` | Init-only local |
| `bool rfs_ping_rxvd` | → `Limits_t.flags.rfs_ping_received` |
| `GEncoderVars x_axis_encoder_counters` | Dead — TMC4671 reads encoder |
| `GTron_Limits_t gtron_limits` | Split: `limit_flags` → `g_limit_flags` in app_state; `interrupt_raised` → dead |
| `adc_values adc_reading` | Init-only local |
| `int32_t current_position` | Function-local |
| `int32_t decel_error_position` | Function-local |
| `int32_t stop_error_position` | Function-local |
| `int32_t decel_velocity` | Function-local |
| `int32_t stop_velocity` | Function-local |
| `uint32_t current_time, prev_time` | Use `xTaskGetTickCount()` |
| Can_Cmd_Info_t rx_can_cmd_info | Function-local in CAN gatekeeper |
| `bool is_tmc2209_mot_moving` | → `g_2209_moving` in motor_2209_internal |
| `bool check_move_done, move_done` | → `g_move_just_completed` in motor_4671_internal; `g_2209_move_done` in motor_2209_internal |
| Duplicate `bool` fields in `limitVariablesData` | Removed — bitfield only |
| `limitVariablesData.flags.rot_enc_z_first_hit` | Renamed → `z_first_hit` |
| `limitVariablesData.flags.lin_enc_z_second_hit` | Renamed → `z_second_hit` |

## volatile Audit

| Variable | volatile? | Reason |
|----------|-----------|--------|
| `g_diag_pending` | YES | ISR writes, task reads |
| `g_limit_flags` | YES | ISR writes, task reads |
| `g_ioxp_int_pending` | YES | ISR writes, task reads |
| `g_flash_busy` | YES | Supervisor writes, motor tasks read |
| Heartbeat counters | YES | ISR/task writes (atomic), supervisor reads |
| `Motor_Info_t` pointers | NO | Set once at init, read-only thereafter |
| `Motor_Info_t` struct members | NO | Single-task ownership per motor (only one task accesses a given motor's state) |
| `g_step_count` | NO | Only TMC2209_TASK accesses it (no ISR) |
| `g_4671_busy`, `g_2209_busy` | NO | Only CAN_GATEKEEPER accesses them |
| All ramp variables | NO | Only TMC4671_TASK accesses them |
| All `*_internal.h` globals | NO | Single-task ownership |

Rule: `volatile` is only for variables written by an ISR and read by a task (or written by one task and read by another without a synchronization primitive). FreeRTOS task preemption eliminates the need for `volatile` on task-owned data — the scheduler guarantees mutual exclusion.

## CRITICAL_SECTION Removal

Old project used `CRITICAL_SECTION_ENTER/LEAVE` around TMC2209 UART writes. With FreeRTOS:
- SERCOM5 is owned exclusively by TMC2209_TASK
- No other task touches SERCOM5
- No ISR touches SERCOM5 (CAN ISR uses CAN peripheral, timer ISRs are flag-only)
- Remove ALL `CRITICAL_SECTION_ENTER/LEAVE` calls from TMC2209 driver code
- Task preemption handles mutual exclusion automatically
