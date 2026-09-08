# Hybrid Trigger Firmware -- Implementation Plan (v2)

**Target:** AXC firmware (SAMC21N18A) on the GTron Axis Controller
**Date:** May 2026
**Status:** Approved for implementation (Q1-Q21 locked)
**Companion documents:**
- `Hybrid_Triggering_Firmware_Design - Copy.md` -- design specification (v2, locked Q1-Q21)
- `GTron_CAN_Message_Structure.xlsx` -- CAN message contract (source of truth for IDs/ops)
- `TMC4671-LA_datasheet_rev2.08.md` -- sections 4.7.5, 4.7.8, 4.7.11, 6.5 referenced (Q21)
- `GTron_Axis_Controller/.../Bring_Up/Motion/Hybrid_Trigger.c` -- current minimal stub being replaced

---

## Table of Contents

1. [Scope and Deliberate Deviations](#1-scope-and-deliberate-deviations)
2. [Background & Existing State](#2-background--existing-state)
3. [CAN Contract](#3-can-contract)
4. [Files Touched](#4-files-touched)
5. [Data Model Additions](#5-data-model-additions)
6. [Sensor Edge ISR](#6-sensor-edge-isr)
7. [Main-Loop State Machine](#7-main-loop-state-machine)
8. [Polling Cadence](#8-polling-cadence)
9. [One-Shot Engagement & Auto-Disable](#9-one-shot-engagement--auto-disable)
10. [Pause / Resume](#10-pause--resume)
11. [Camera Trigger Helper](#11-camera-trigger-helper)
12. [Bug Fixes Bundled & Bugs Explicitly Left Alone](#12-bug-fixes-bundled--bugs-explicitly-left-alone)
13. [Constants](#13-constants)
14. [Verification Plan](#14-verification-plan)
15. [Open Items at Implementation Start](#15-open-items-at-implementation-start)
16. [Risk Notes](#16-risk-notes)
17. [Appendix A -- File-by-File Reference](#17-appendix-a--file-by-file-reference)
18. [Appendix B -- Decision Log (Q1-Q21)](#18-appendix-b--decision-log-q1-q21)

---

## 1. Scope and Deliberate Deviations

### 1.1 In Scope (v2)

- Implement Hybrid Triggering on the AXC per the design document, with deliberate deviations called out below.
- Two hybrid peripherals: `HYBRID_TRIGGER_INSPECTION` (8) and `HYBRID_TRIGGER_ONE_SHOT` (9). One-Shot replaces the legacy Configurator naming (Q2).
- New `AXC_PAUSE` operation (op 18) with the TMC4671 position-hold pause sequence (Q7-Q15).
- New `flags.is_paused` bit (bit 11) and state-aware `AXC_START` resume (Q9-Q10).
- Bundled correctness fixes adjacent to the rewritten code path.

### 1.2 Deliberate Deviations from the Design Document

| # | Spec says | v2 does | Rationale |
|---|---|---|---|
| 1 | Fractional step accumulator (`step_size_int` + `step_size_frac`, fixed-point uint16/65536ths) | **Drop fractional accumulator (Q1).** Use integer `step_size = round(offset)` only, transmitted via existing `AXC_TEETH` op into `position.trig_step_size`. | Hybrid re-anchors at every sensor edge -> no long-term drift. The single-cycle systematic offset (<= 0.5 microstep ~= 0.0014 mm at the example pinch roller) is sub-pixel for any realistic optic and operator-recalibratable. |
| 2 | GC (`uint64`) traceability transmitted to Software | **Count `gc` internally only, Inspection-only (Q6)**; do not transmit over CAN. One-Shot fires do **not** increment `gc`. | Software architecture does not currently support GC traceability. Counter is added to the state struct so the field is ready when SW is ready. |
| 3 | CAN slip / spurious alert from AXC -> SC | **Defer CAN alert (Q17).** Increment `consecutive_failures`, log via `DBG_Printf(ERR_LVL_WARN, ...)` at threshold. | Error-message protocol between FW and SW is not yet defined. A clearly-marked TODO comment block is left at the would-be `can_Write` call site. |
| 4 | Single hybrid mode | **Two hybrid peripherals (Q2):** Inspection (continuous) and One-Shot (single). | Distinct use cases; distinct cycling, RHD, GC behaviour. |
| 5 | One-Shot edge sends `AXC_PRESSED` reply with reeler position | **No CAN reply on One-Shot edge (Q3).** Only the Reeler_Int pulse fires the camera. | Per locked decision -- One-Shot now stops + holds + fires the camera (Q4) rather than reporting position to SW for fine-tuning. |
| 6 | (Not in spec) | **Pause / Resume via `AXC_PAUSE` (op 18) and state-aware `AXC_START` (Q7, Q9).** | Software requires a Pause that preserves all hybrid state across an arbitrary stop without losing anchor / failure / GC context. |
| 7 | (Not in spec) | **Do not modify the legacy encoder-mode trigger block** (`Motion.c:1225-1239`). | The plan is to remove encoder-mode once Hybrid is proven. |

### 1.3 Out of Scope (per design doc Section 9 -- Future Enhancements)

- Trigger latency compensation (velocity-dependent fire-early offset)
- Sag detection by firmware
- Pinch roller degradation auto-correction
- SC-side firmware changes (separate work item; SC team mirrors the AXC contract documented in Section 3)
- ISR-safe `DBG_Printf` (Phase 5.6 deferred -- see Section 16.7)

### 1.4 Relationship to `dbg_print` Migration

Phase 5 replaced project-wide `printf` with the new non-blocking `DBG_Printf` library. All log calls in Phase 8 use `DBG_Printf(ERR_LVL_DEBUG, ...)` or `(ERR_LVL_WARN, ...)` accordingly. The library is **not yet ISR-safe** (Phase 5.6 deferred -- see Section 16.7). Phase 8 incidentally eliminates the only known ISR-context `DBG_Printf` call site by trimming the LIM_LFT ISR (Section 6.1).

---

## 2. Background & Existing State

### 2.1 Current Hybrid Implementation (the stub being replaced)

`Bring_Up/Motion/Hybrid_Trigger.c` (49 lines) -- minimal, dormant, contains a known compile/runtime bug:

```c
void check_For_Hybrid_Trigger(void)
{
    int32_t current_pos = tmc4671_getActualPosition(MOTOR);
    uint32_t diff_pos = abs(prev_trig_pos - current_pos);

    if (p_reeler_info->flags.sensor_trigger && (diff_pos >= p_reeler_info->position.trig_step_size)) {
        trigger_Camera_Line();
        p_reeler_info->flags.sensor_trigger = false;
        prev_trig_time_ms = millis();
        // ... debug prints ...
        prev_trig_pos = current_position;   // BUG: should be current_pos
    }
}
```

Limitations vs. design doc:
- No anchor capture in the ISR -- uses `prev_trig_pos` set at fire time.
- No first-trigger-skip after Start.
- No fractional accumulator (also dropped in v2 per Q1).
- No slip / spurious detection.
- No CAN alert plumbing.
- No GC counter.
- No pause / resume state handling.
- No One-Shot mode.
- `prev_trig_pos = current_position;` references an undeclared local -- pre-existing bug.

### 2.2 Existing Architecture Touchpoints

| Concern | Location | Notes |
|---|---|---|
| Hybrid check call site | `Motion.c:1224` (`run_Velocity_Ramp`) | Gated by `is_hybrid_trig_enabled` |
| Polling cadence | `main.c:81-83` + VEL_TIMER (TC2, 1 ms) | Only while `rotate_vel_mode && vel_timer && sag_enabled` |
| Sensor ISR | `Motion.c:644` (`left_Limit_Interrupt_Callback`, **LIM_LFT** -- the hybrid sensor input) | Repurposed limit ISR; previously contained `printf` (bad in ISR). `right_Limit_Interrupt_Callback` (LIM_RT) is **not** a hybrid input and is out of scope (Q18). |
| EIC line config | `driver_init.c` + `Macros.h:265-269` | Edge sense via build switches |
| Reeler struct | `gtron_can_cmd_parser.h:59-104` (`Motor_Info_t`) | Has `flags.sensor_trigger`, `flags.is_hybrid_trig_enabled`, `position.trig_step_size`, `time_ms.sens_trig`, `time_ms.cam_trig` |
| Instance | `gtron_can_cmd_parser.c:13-14` | `volatile Motor_Info_t reeler_info; volatile Motor_Info_t *p_reeler_info = &reeler_info;` |
| CAN dispatcher | `gtron_can_cmd_parser.c:383, 487-501` | `parse_GTron_CAN_Msg_Data()` |
| Hybrid CAN handler | `gtron_can_cmd_parser.c:569-585` | Has missing-`break;` bug |
| Step-size opcode | `gtron_can_cmd_parser.c:108-115, 496` | `reeler_Set_Teeth` / `AXC_TEETH = 12` |
| Start / Stop | `gtron_can_cmd_parser.c:139, 159` | Manage VEL_TIMER, vel_ramp flags |
| AXC -> SC async path | `Bring_Up/CAN/IMM_CAN_Write.c:23` (`can_Write`) + global `can_tx_frame` | Standard pattern: fill `can_tx_frame.data[0..5]`, call `can_Write` |
| `REELER_INT` pin | `atmel_start_pins.h:56` (`PB30`) | Driven `HIGH` for 1 us then `LOW` to fire camera |
| TMC4671 SPI | `TMC-API/.../TMC4671.c:51-78, 406-409` | Blocking SPI, 5 byte-transfers per register read; **no mutex** |
| Move-Done loop | `Motion.c:1109-1144` (`check_For_Move_Done`) | Called from main loop while `check_move_done == true`; sends RHD when settled. **One-Shot polling hook.** |

### 2.3 SPI Latency Analysis (informational)

At SPI baud 2 MHz, 9 bytes ~= 36 us of pure shift time. Single-register read via `tmc4671_readInt` is 5 SPI byte transfers ~= 20 us. At 1200 parts/min and step ~= 86,572 microsteps:
- Reeler velocity ~= 1.73 M microsteps / sec -> 20 us SPI ~= 35 microsteps of position uncertainty.
- 5%-of-step tolerance band ~= 4,328 microsteps. SPI latency is well inside the tolerance.

Conclusion: ISR-side SPI is **not** required for accuracy. We deliberately keep SPI in main-loop context (see Section 6).

---

## 3. CAN Contract

Aligned with `GTron_CAN_Message_Structure.xlsx` and the existing `AxC_Operations_t` enum. **One new operation value** (`AXC_PAUSE = 18`) is required; **one new peripheral value** (`HYBRID_TRIGGER_ONE_SHOT = 9`) is required; the existing peripheral `HYBRID_TRIGGER` (8) is renamed to `HYBRID_TRIGGER_INSPECTION` with its value preserved.

### 3.1 Commands SC -> AXC

CAN IDs: `0x108` (Top rack) / `0x109` (Bottom rack). Standard payload layout: `data[0] = peripheral`, `data[1] = operation`, `data[2..5] = int32 value (LE)`. DLC = 6, EXT_ID.

| Peripheral | Op | Op value | Value bytes | Effect |
|---|---|---|---|---|
| `REELER_MOTOR` (1) | `AXC_TEETH` | 12 | uint32 step_size in microsteps | **Existing.** Sets `position.trig_step_size`. The hybrid pipeline reads its `step_size` from this field. SW sends this once before enabling either hybrid peripheral. |
| `HYBRID_TRIGGER_INSPECTION` (8) | `AXC_ENABLE` | 3 | unused | Enter Inspection mode; arm `first_trigger_skip`; clear `cycle_armed`; clear `consecutive_failures`; clear stale `flags.sensor_trigger`. |
| `HYBRID_TRIGGER_INSPECTION` (8) | `AXC_DISABLE` | 4 | unused | Exit Inspection mode (returns mode to OFF). |
| `HYBRID_TRIGGER_INSPECTION` (8) | `AXC_PAUSE` | **18 (new)** | unused | Pause Inspection (Q7). Sets `flags.is_paused = true`. Hybrid state preserved. |
| `HYBRID_TRIGGER_ONE_SHOT` (9, new) | `AXC_ENABLE` | 3 | unused | Enter One-Shot mode; will engage on next Move-To/By. |
| `HYBRID_TRIGGER_ONE_SHOT` (9, new) | `AXC_DISABLE` | 4 | unused | Exit One-Shot mode. |
| `HYBRID_TRIGGER_ONE_SHOT` (9, new) | `AXC_PAUSE` | 18 | unused | Pause request (Q12). **No-op if a One-Shot move is in flight**; logs warning. SW must not send in that case. |
| `REELER_MOTOR` (1) | `AXC_START` | 1 | unused | **Existing, modified.** State-aware (Q9): if `flags.is_paused` resume from paused state; otherwise fresh start (resets Inspection hybrid state if Inspection is the active mode). |
| `REELER_MOTOR` (1) | `AXC_STOP` | 2 | unused | **Existing, modified.** Free-rotation Stopped. Hybrid Inspection state is reset on stop (Q11). `flags.is_paused = false`. Mode is preserved. |
| `REELER_MOTOR` (1) | `AXC_PAUSE` | **18 (new)** | unused | Pause reeler (TMC4671 position-hold per Q8). Sets `flags.is_paused = true`. |
| `REELER_MOTOR` (1) | `AXC_VELOCITY` | 5 | int32 RPM | **Existing.** Sets target velocity. |
| `REELER_MOTOR` (1) | `AXC_MOVE_TO` | 7 | int32 absolute position microsteps | **Existing, hooked.** Used to engage One-Shot. |
| `REELER_MOTOR` (1) | `AXC_MOVE_BY` | 8 | int32 relative delta microsteps | **Existing, hooked.** Used to engage One-Shot. |

### 3.2 Replies AXC -> SC

CAN IDs: `0x10A` (Top -> SC) / `0x10B` (Bot -> SC). Same payload layout.

| Peripheral | Op | Op value | When |
|---|---|---|---|
| `REELER_MOTOR` (1) | `AXC_HOMING` | 17 | **Existing.** "Move Done / RHD" reply (semantics misnamed in current code; see Section 12 -- left as-is per decision). **Suppressed when One-Shot fires** during the move (Q4): `check_move_done` is cleared in the One-Shot edge handler. |

> **No One-Shot edge reply.** The legacy `AXC_PRESSED` (op 14) reply is **removed** for One-Shot (Q3). The One-Shot fire path is: stop reeler in position-hold -> pulse Reeler_Int (camera fires) -> suppress RHD -> auto-disable. No CAN frame is sent to SC on the edge.

### 3.3 Slip / Spurious Alert -- DEFERRED (Q17)

Not transmitted in v2. The AXC tracks `consecutive_failures` internally and emits a `DBG_Printf(ERR_LVL_WARN, ...)` line when the threshold is crossed. A clearly-marked TODO block is left at the would-be `can_Write` call site:

```c
// TODO(slip-alert): Send CAN slip/spurious alert to SC (Q17 deferred).
// Pending: error-message protocol decision. See design doc section 6.4.
// Draft payload (subject to change):
//   data[0] = HYBRID_TRIGGER_INSPECTION (8)
//   data[1] = <new op TBD>     // candidate name: AXC_HYBRID_SLIP_ALERT
//   data[2] = consecutive_failures (uint8)
//   data[3..5] = packed expected/actual delta info
// Reply ID = CAN_REPLY_TOP_RACK_ID or CAN_REPLY_BOT_RACK_ID per axis_id.
```

---

## 4. Files Touched

| File | Action |
|---|---|
| `Bring_Up/Motion/Hybrid_Trigger.h` | **Rewrite.** Add `hybrid_mode_t` enum (or move to `Hybrid_Trigger_Types.h` -- see Section 17.1 cycle-breaker note). Add public prototypes. Expose `trigger_Camera_Line()`. |
| `Bring_Up/Motion/Hybrid_Trigger.c` | **Rewrite.** State machine, slip detection, first-trigger skip, GC counter (Inspection-only), One-Shot edge sequence, helpers. Drop the buggy `current_position` reference from the old stub. |
| `Bring_Up/Motion/Hybrid_Trigger_Types.h` (new, optional) | **Add (cycle-breaker).** `hybrid_mode_t` enum if including it from `Hybrid_Trigger.h` would create a circular include with `gtron_can_cmd_parser.h`. See Section 17.1. |
| `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h` | **Extend.** Add `flags.is_paused : 1` at bit 11 (Q10) -- reduce `reserved` from `:21` to `:20`. Add `hybrid` substruct to `Motor_Info_t`. Add prototype for new `reeler_Pause_Motor`. |
| `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.c` | **Modify.** Rename `HYBRID_TRIGGER` case to `HYBRID_TRIGGER_INSPECTION`; add `HYBRID_TRIGGER_ONE_SHOT` case; add `AXC_PAUSE` handler in `REELER_MOTOR` case; fix missing `break;` at the end of each case; add hybrid-state hooks in `reeler_Start_Motor` (state-aware resume vs fresh-start) and `reeler_Stop_Motor`; add One-Shot engagement block in `reeler_Move()`; add new `reeler_Pause_Motor()` function (Q8). |
| `Bring_Up/Motion/Motion.c` | **Modify.** Trim `left_Limit_Interrupt_Callback` (LIM_LFT) -- remove `printf` / `DBG_Printf`, keep flag + timestamp only (Q18). Add One-Shot polling call + auto-disable block in `check_For_Move_Done()`. **Do NOT modify** the encoder-mode block at L1225-1239 or `right_Limit_Interrupt_Callback` (LIM_RT) or the L1128 `AXC_HOMING` reply. |
| `Bring_Up/CAN/IMM_CAN_Message_Id.h` | **Modify.** Rename `HYBRID_TRIGGER` enum -> `HYBRID_TRIGGER_INSPECTION` (value 8 unchanged). Add `HYBRID_TRIGGER_ONE_SHOT = 9`. Add `AXC_PAUSE = 18`. |
| `Macros.h` (or new `Bring_Up/Motion/Hybrid_Trigger_Cfg.h`) | **Add constants.** `HYBRID_SLIP_TOLERANCE_PCT 5u`, `HYBRID_ALERT_THRESHOLD 3u`, `HYBRID_PAUSE_HOLD_VELOCITY_RPM 2u`. |

**Files NOT touched:**
- `main.c` -- existing main loop already calls `run_Velocity_Ramp` and `check_For_Move_Done`; no new call sites required.
- Encoder-mode trigger block at `Motion.c:1225-1239` (decision row 7 of Section 1.2).
- `right_Limit_Interrupt_Callback` (LIM_RT) -- not a hybrid sensor (Q18).
- `Motion.c:1128` `AXC_HOMING`-vs-`AXC_MOVE_DONE` mismatch -- SC contract risk; out of scope.
- Z-pulse ISR `rot_Enc_Z_Pulse_Interrupt_Callback` at `Motion.c:601` -- pre-existing SPI-from-ISR race; not introduced by Phase 8.
- TMC-API source.
- Driver init / Atmel Start config.

---

## 5. Data Model Additions

### 5.1 New enum

```c
typedef enum {
    HYBRID_MODE_OFF        = 0,
    HYBRID_MODE_INSPECTION = 1,
    HYBRID_MODE_ONE_SHOT   = 2,
} hybrid_mode_t;
```

Lives either in `Hybrid_Trigger.h` (preferred) or in a new `Hybrid_Trigger_Types.h` if the include graph requires a cycle-breaker (see Section 17.1).

### 5.2 New `flags.is_paused` bit (Q10)

In `Motor_Info_t.flags` substruct (`gtron_can_cmd_parser.h:83-96`), bits 0-10 are currently used and `reserved : 21`. Add `is_paused` at bit 11:

```c
struct {
    uint32_t is_homing                 : 1;   // bit 0
    uint32_t is_homed                  : 1;   // bit 1
    uint32_t is_at_open_limit          : 1;   // bit 2
    uint32_t is_at_close_limit         : 1;   // bit 3
    uint32_t is_initialized            : 1;   // bit 4
    uint32_t is_at_init_position       : 1;   // bit 5
    uint32_t is_moving                 : 1;   // bit 6
    uint32_t is_in_pos_mode            : 1;   // bit 7
    uint32_t is_in_vel_mode            : 1;   // bit 8
    uint32_t sensor_trigger            : 1;   // bit 9
    uint32_t is_hybrid_trig_enabled    : 1;   // bit 10
    uint32_t is_paused                 : 1;   // bit 11  (NEW, Q10)
    uint32_t reserved                  : 20;  // was 21
} flags;
```

> Verify the exact bit ordering against the actual struct in `gtron_can_cmd_parser.h:83-96` before merging. The mapping above reflects the current layout per investigation; layout drift since investigation must be reconciled at code-write time.

### 5.3 New `hybrid` substruct in `Motor_Info_t`

Add to the existing struct, after the `flags` substruct:

```c
struct {
    hybrid_mode_t mode;                 // current hybrid mode
    int32_t   anchor_position;          // microsteps; latched by main loop on edge
    int32_t   prev_anchor_position;     // for slip / spurious anchor-to-anchor delta
    bool      cycle_armed;              // anchor valid; awaiting offset to fire (Inspection)
    bool      first_trigger_skip;       // skip first edge after Inspection enable / fresh start
    bool      one_shot_armed;           // One-Shot armed for the current Move-To / Move-By
    uint8_t   consecutive_failures;     // slip / spurious counter (Q16: preserved across pause)
    uint64_t  gc;                       // global trigger count; Inspection-only (Q6)
    uint32_t  unhandled_edges;          // diagnostic: edges seen with mode == OFF
} hybrid;
```

Field naming: `cfg_armed` from earlier drafts is renamed to `one_shot_armed` (Q2).

### 5.4 Existing fields reused

| Field | Used for |
|---|---|
| `flags.sensor_trigger` (1-bit) | ISR -> main loop edge handoff. ISR sets `true`; main loop clears after processing. |
| `flags.is_hybrid_trig_enabled` (1-bit) | Back-compat alias. **Maintained as a mirror** of `mode != HYBRID_MODE_OFF`. Set/cleared by the same code paths that change `mode`. Existing call sites (`Motion.c:1224`, etc.) continue to work without modification. |
| `flags.is_paused` (1-bit, **new**) | Set by `reeler_Pause_Motor`. Cleared by `reeler_Start_Motor` (resume path) and `reeler_Stop_Motor`. Q10. |
| `time_ms.sens_trig` (uint32) | ISR latches `millis()` at edge. Diagnostic; not consumed by hybrid logic. |
| `time_ms.cam_trig` (uint32) | Set inside `trigger_Camera_Line()`. Diagnostic. |
| `position.trig_step_size` (uint32) | The hybrid step size (microsteps). Set via existing `AXC_TEETH` opcode. |

### 5.5 State Initialization

Hybrid substruct fields are initialized to zero by the existing zero-initialization of `reeler_info`. `mode` defaults to `HYBRID_MODE_OFF`, all flags `false`, counters `0`. A `hybrid_trigger_init()` helper is added for clarity and as a hook for future wiring (e.g., loading persisted settings later).

---

## 6. Sensor Edge ISR

### 6.1 Updated ISR body -- LIM_LFT only

**Scope clarification (Q18):** Only `LIM_LFT` is wired to the hybrid sensor input. `LIM_RT` is **not** a hybrid sensor input and `right_Limit_Interrupt_Callback` is **left unchanged** by Phase 8.

`Motion.c:644-649` -- `left_Limit_Interrupt_Callback` made minimal:

```c
void left_Limit_Interrupt_Callback(void)
{
    p_reeler_info->flags.sensor_trigger = true;
    p_reeler_info->time_ms.sens_trig = millis();
    // Intentionally minimal. Mode-blind (Q18). Main loop dispatches based on hybrid.mode.
}
```

Removed:
- Any `DBG_Printf(...)` from the ISR -- the Phase 5 `dbg_print` library is not yet ISR-safe (Phase 5.6 deferred -- see Section 16.7).
- Any parallel `printf` workarounds.

Not added:
- TMC4671 SPI read (deferred to main loop -- see decision rationale in Section 16).
- Mode check (deferred to main loop -- see decision rationale in Section 18).

### 6.2 ISR Registration

Unchanged:
```c
ext_irq_register(LIM_LFT, left_Limit_Interrupt_Callback);   // hybrid sensor (Q18)
ext_irq_register(LIM_RT,  right_Limit_Interrupt_Callback);  // not a hybrid sensor
```

### 6.3 Edge Polarity

Controlled by build switches in `Macros.h:265-269` -- unchanged. Document in the `Hybrid_Trigger.h` header comment which polarity is required for the production sensor.

### 6.4 ISR Behavior With Mode == OFF or Paused

The ISR is mode-blind (Q18). Main loop sees the flag and:
- If `flags.is_paused`: leaves the flag alone -- the resume path will explicitly clear it (Q14).
- Else if `mode == OFF`: increments `hybrid.unhandled_edges`, then clears the flag.
- Else: dispatches to the appropriate handler.

---

## 7. Main-Loop State Machine

### 7.1 Top-Level Dispatch

```c
void check_For_Hybrid_Trigger(void)
{
    if (p_reeler_info->flags.is_paused) {
        // Don't touch sensor_trigger here; resume will clear it (Q14).
        return;
    }

    switch (p_reeler_info->hybrid.mode) {
        case HYBRID_MODE_INSPECTION: handle_inspection_tick(); break;
        case HYBRID_MODE_ONE_SHOT:   handle_one_shot_tick();   break;
        case HYBRID_MODE_OFF:
        default:
            if (p_reeler_info->flags.sensor_trigger) {
                p_reeler_info->hybrid.unhandled_edges++;
                p_reeler_info->flags.sensor_trigger = false;
            }
            break;
    }
}
```

### 7.2 Inspection Tick -- `handle_inspection_tick()`

```c
static void handle_inspection_tick(void)
{
    volatile struct hybrid_state_s *H = &p_reeler_info->hybrid;
    uint32_t step = p_reeler_info->position.trig_step_size;

    // (A) Process sensor edge if present
    if (p_reeler_info->flags.sensor_trigger) {
        int32_t new_anchor = tmc4671_getActualPosition(MOTOR);
        p_reeler_info->flags.sensor_trigger = false;

        // First-trigger skip -- first edge after fresh start only records anchor.
        if (H->first_trigger_skip) {
            H->first_trigger_skip   = false;
            H->prev_anchor_position = new_anchor;
            H->anchor_position      = new_anchor;
            H->cycle_armed          = true;
            return;
        }

        // Slip / spurious detection (anchor-to-anchor delta)
        uint32_t actual    = (uint32_t)labs(new_anchor - H->prev_anchor_position);
        uint32_t expected  = step;
        uint32_t tolerance = (expected * HYBRID_SLIP_TOLERANCE_PCT) / 100u;
        uint32_t deviation = (actual > expected) ? (actual - expected) : (expected - actual);

        if (deviation > tolerance) {
            H->consecutive_failures++;
            if (H->consecutive_failures == HYBRID_ALERT_THRESHOLD) {
                DBG_Printf(ERR_LVL_WARN,
                           "[HYB] slip threshold: fail=%u exp=%lu act=%lu\n",
                           H->consecutive_failures,
                           (unsigned long)expected, (unsigned long)actual);
                // TODO(slip-alert): Send CAN slip alert here once protocol is defined (Q17).
                //   peripheral = HYBRID_TRIGGER_INSPECTION
                //   op         = <new op TBD>
                //   payload    = {fail_count, expected, actual}
            }
            // Re-anchor anyway per design section 6.3; do NOT fire this cycle.
        } else {
            H->consecutive_failures = 0;
        }

        H->prev_anchor_position = new_anchor;
        H->anchor_position      = new_anchor;
        H->cycle_armed          = true;
        return;   // do not also poll-and-fire in the same tick
    }

    // (B) No edge this tick -- if armed, check offset and fire when reached
    if (H->cycle_armed) {
        int32_t cur = tmc4671_getActualPosition(MOTOR);
        if ((uint32_t)labs(cur - H->anchor_position) >= step) {
            trigger_Camera_Line();
            H->gc++;                        // Inspection-only (Q6)
            H->cycle_armed = false;
            // Remain in INSPECTION mode; next sensor edge re-arms.
        }
    }
}
```

**Per-tick SPI cost:**
- Edge tick: 1 x `getActualPosition` (5 byte-transfers).
- Non-edge tick when armed: 1 x `getActualPosition`.
- Non-edge tick when disarmed: 0 SPI.

This is consistent with the existing `run_Velocity_Ramp` SPI budget (already does >= 3 SPI ops/tick).

### 7.3 One-Shot Tick -- `handle_one_shot_tick()`

```c
static void handle_one_shot_tick(void)
{
    volatile struct hybrid_state_s *H = &p_reeler_info->hybrid;

    if (!H->one_shot_armed) {
        // One-Shot mode is on but no Move-To / Move-By is active yet.
        // Drop any stale flag so the next move starts clean.
        if (p_reeler_info->flags.sensor_trigger) {
            p_reeler_info->flags.sensor_trigger = false;
        }
        return;
    }

    if (p_reeler_info->flags.sensor_trigger) {
        p_reeler_info->flags.sensor_trigger = false;

        // One-Shot edge sequence (Q4) -- in this order:
        // 1. Stop reeler with position hold.
        reeler_Pause_Motor();

        // 2. Fire camera (Reeler_Int pulse).
        trigger_Camera_Line();
        // GC is NOT incremented for One-Shot fires (Q6).

        // 3. Suppress RHD reply for the aborted move.
        check_move_done = false;

        // 4. Auto-disable.
        H->one_shot_armed = false;
        H->mode           = HYBRID_MODE_OFF;
        p_reeler_info->flags.is_hybrid_trig_enabled = false;

        DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot fired; auto-disabled\n");
    }
}
```

**Behavior summary (Q3, Q4, Q6):**
- One-Shot fires the camera (does **not** send `AXC_PRESSED`).
- One-Shot does NOT skip the first edge (the first edge IS the trigger edge).
- One-Shot does NOT run slip / spurious detection.
- One-Shot auto-disables on whichever happens first: sensor edge OR move-done (the move-done path is described in Section 8.2).
- After fire, the reeler stays in TMC4671 position-hold (`reeler_Pause_Motor` left it there) until the next `MOVE_TO` / `MOVE_BY` or `AXC_START` (Q5).

---

## 8. Polling Cadence

### 8.1 Inspection -- existing call site

`run_Velocity_Ramp()` at `Motion.c:1224`:
```c
if (p_reeler_info->flags.is_hybrid_trig_enabled) {
    check_For_Hybrid_Trigger();
} else if (...encoder mode...) {
    ...
}
```

This is gated by `vel_timer && rotate_vel_mode && sag_enabled` (from `main.c:81-83` and the VEL_TIMER 1 ms tick). Pause sets `vel_timer = false; rotate_vel_mode = false;` (Q13), which short-circuits the call cleanly without needing an explicit `is_paused` check at this site.

### 8.2 One-Shot -- new call site

Add to `check_For_Move_Done()` (`Motion.c:1109`) at the **top** of the function, before the position-error settle check:

```c
void check_For_Move_Done(void)
{
    // NEW: One-Shot polling. Runs while a move is in progress and
    // mode == ONE_SHOT. Placed BEFORE the move-done settle check so a
    // sensor edge in the final polling tick is reported instead of being
    // lost to RHD.
    if (p_reeler_info->hybrid.mode == HYBRID_MODE_ONE_SHOT &&
        p_reeler_info->hybrid.one_shot_armed) {
        check_For_Hybrid_Trigger();
        // If the One-Shot fired this tick, it cleared check_move_done already.
        if (!check_move_done) {
            return;
        }
    }

    // ... existing settle check unchanged ...

    if (move_done_check_num >= NO_OF_MOVE_DONE_CHECK) {
        // NEW: One-Shot auto-disable on move-done (no edge seen during move)
        if (p_reeler_info->hybrid.mode == HYBRID_MODE_ONE_SHOT &&
            p_reeler_info->hybrid.one_shot_armed) {
            p_reeler_info->hybrid.one_shot_armed = false;
            p_reeler_info->hybrid.mode           = HYBRID_MODE_OFF;
            p_reeler_info->flags.is_hybrid_trig_enabled = false;
            DBG_Printf(ERR_LVL_DEBUG,
                       "[HYB] One-Shot move done with no edge; auto-disabled\n");
        }

        // ... existing RHD CAN send unchanged ...
    }
}
```

### 8.3 Why this hook works

`check_For_Move_Done()` is called from the main loop while `check_move_done == true`. That flag is set by `move_With_Trapezoidal_Ramp()` (L1054) and `move_With_S_Ramp()` (L1080) when a Move-To / By is dispatched, and cleared when the position settles. The polling lifetime exactly matches the move lifetime -- no separate timer or scheduler needed for One-Shot.

### 8.4 Polling tick rate

For One-Shot: every iteration of the main loop while a move is in progress. Loop body is small. Empirically sub-millisecond; sensor-edge -> Reeler_Int latency is dominated by the sensor edge -> ISR latency + main-loop iteration latency, well under 1 ms.

---

## 9. One-Shot Engagement & Auto-Disable

### 9.1 Enable One-Shot (CAN ENABLE op)

In `gtron_can_cmd_parser.c` `HYBRID_TRIGGER_ONE_SHOT` case:
```c
case HYBRID_TRIGGER_ONE_SHOT: {
    switch (rx_can_cmd_info.data[OPERATION_BYTE_IDX]) {
        case AXC_ENABLE:
            p_reeler_info->hybrid.mode           = HYBRID_MODE_ONE_SHOT;
            p_reeler_info->hybrid.one_shot_armed = false;   // armed on next Move-To / By
            p_reeler_info->flags.is_hybrid_trig_enabled = true;   // back-compat alias
            DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot ENABLE\n");
            break;
        case AXC_DISABLE:
            p_reeler_info->hybrid.mode           = HYBRID_MODE_OFF;
            p_reeler_info->hybrid.one_shot_armed = false;
            p_reeler_info->flags.is_hybrid_trig_enabled = false;
            DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot DISABLE\n");
            break;
        case AXC_PAUSE:
            // Q12: log and ignore if a One-Shot move is in flight.
            if (p_reeler_info->hybrid.one_shot_armed) {
                DBG_Printf(ERR_LVL_DEBUG,
                           "[HYB] PAUSE on ONE_SHOT ignored - One-Shot move active\n");
            } else {
                p_reeler_info->flags.is_paused = true;
            }
            break;
        default: break;
    }
    break;   // explicit break -- fixes the missing-break bug class
}
```

### 9.2 Engagement on Move-To / By

In `reeler_Move()` (`gtron_can_cmd_parser.c:64-82`), AFTER dispatching the move to TMC4671 (after `tmc4671_setAbsolutTargetPosition` / `tmc4671_setRelativeTargetPosition` and ramp setup):
```c
if (p_reeler_info->hybrid.mode == HYBRID_MODE_ONE_SHOT) {
    p_reeler_info->flags.sensor_trigger     = false;   // clear any stale edge flag
    p_reeler_info->hybrid.one_shot_armed    = true;
    DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot armed for this move\n");
}
```

This block runs for both `AXC_MOVE_TO` and `AXC_MOVE_BY` (per spec -- only those two engage One-Shot). The `AXC_ROTATE` / `AXC_VELOCITY` paths don't call `reeler_Move`, so they don't engage One-Shot (correct per spec).

### 9.3 Auto-Disable Paths

Two mutually exclusive paths, whichever happens first:

**Path A -- Sensor edge during move:** handled in `handle_one_shot_tick()` (Section 7.3). Stops + holds reeler, fires camera, suppresses RHD (`check_move_done = false`), sets `mode = OFF`, `one_shot_armed = false`. SW receives no CAN reply for this move (Q3, Q4).

**Path B -- Move completes without edge:** handled in `check_For_Move_Done()` (Section 8.2). Sets `mode = OFF`, `one_shot_armed = false`. RHD is sent normally. SW receives the existing RHD; no other reply.

The two paths are exclusive: either the camera fires (Path A, no RHD) or the move completes without firing (Path B, RHD only). SW must accept either outcome.

### 9.4 Enable Inspection (CAN ENABLE op)

In the renamed `HYBRID_TRIGGER_INSPECTION` case:
```c
case HYBRID_TRIGGER_INSPECTION: {
    switch (rx_can_cmd_info.data[OPERATION_BYTE_IDX]) {
        case AXC_ENABLE:
            p_reeler_info->hybrid.mode                  = HYBRID_MODE_INSPECTION;
            p_reeler_info->hybrid.first_trigger_skip    = true;
            p_reeler_info->hybrid.consecutive_failures  = 0;
            p_reeler_info->hybrid.cycle_armed           = false;
            p_reeler_info->flags.sensor_trigger         = false;   // clear stale
            p_reeler_info->flags.is_hybrid_trig_enabled = true;
            DBG_Printf(ERR_LVL_DEBUG, "[HYB] Inspection ENABLE\n");
            break;
        case AXC_DISABLE:
            p_reeler_info->hybrid.mode                  = HYBRID_MODE_OFF;
            p_reeler_info->hybrid.cycle_armed           = false;
            p_reeler_info->flags.is_hybrid_trig_enabled = false;
            DBG_Printf(ERR_LVL_DEBUG, "[HYB] Inspection DISABLE\n");
            break;
        case AXC_PAUSE:
            // Q7: pause on the Inspection peripheral -- preserves all hybrid state.
            p_reeler_info->flags.is_paused = true;
            DBG_Printf(ERR_LVL_DEBUG, "[HYB] Inspection PAUSE\n");
            break;
        default: break;
    }
    break;
}
```

---

## 10. Pause / Resume

The Pause / Resume model is locked by Q7-Q16. Three peripherals accept `AXC_PAUSE` independently: `REELER_MOTOR`, `HYBRID_TRIGGER_INSPECTION`, `HYBRID_TRIGGER_ONE_SHOT`.

### 10.1 New `reeler_Pause_Motor()` (`gtron_can_cmd_parser.c`, new function)

Implements the TMC4671 position-hold sequence (Q8). Called by:
- The `REELER_MOTOR / AXC_PAUSE` CAN handler.
- The One-Shot edge handler (Section 7.3) at fire time.

```c
void reeler_Pause_Motor(void)
{
    // 1. TMC4671 -> Stopped mode (immediate; halts torque output).
    //    Reference: TMC4671 datasheet section 4.7.11 / 6.5 (Q21).
    tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, TMC4671_MOTION_MODE_STOPPED);

    // 2. Latch current position as target.
    int32_t cur = tmc4671_getActualPosition(MOTOR);
    tmc4671_writeInt(MOTOR, TMC4671_PID_POSITION_TARGET, (uint32_t)cur);

    // 3. Set velocity_limit to the hold limit (~2 RPM) to prevent lurch.
    //    Conversion to TMC4671 internal units happens via existing helper.
    tmc4671_setVelocityLimit_RPM(HYBRID_PAUSE_HOLD_VELOCITY_RPM);

    // 4. Switch to Position mode -- controller actively holds the latched position.
    tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, TMC4671_MOTION_MODE_POSITION);

    // 5. Short-circuit ramp / hybrid checks (Q13).
    vel_timer       = false;
    rotate_vel_mode = false;

    // 6. Mark paused (Q10).
    p_reeler_info->flags.is_paused = true;

    DBG_Printf(ERR_LVL_DEBUG, "[HYB] reeler paused at pos = %ld\n", (long)cur);
}
```

> Helper / register names (`TMC4671_MODE_RAMP_MODE_MOTION`, `TMC4671_PID_POSITION_TARGET`, `TMC4671_MOTION_MODE_*`, `tmc4671_setVelocityLimit_RPM`) are placeholders; final names must match the project's TMC-API headers and existing helpers used by `reeler_Move()`. Reconcile at code-write time.

### 10.2 `reeler_Stop_Motor()` modifications (`gtron_can_cmd_parser.c:159`)

Append at end of existing function body:
```c
// Hybrid-state reset on Stop (Q11). Mode is preserved; mode is owned only by
// HYBRID_TRIGGER_* / AXC_ENABLE | AXC_DISABLE.
p_reeler_info->hybrid.cycle_armed           = false;
p_reeler_info->hybrid.first_trigger_skip    = true;   // re-anchor on next fresh Start
p_reeler_info->hybrid.consecutive_failures  = 0;
// Do NOT reset:
//   - hybrid.mode (preserve -- Q11)
//   - hybrid.gc (preserve)
//   - hybrid.unhandled_edges (preserve -- diagnostic)
//   - hybrid.one_shot_armed (Stop while One-Shot armed: leave for the
//     One-Shot DISABLE path to clean up; in practice the move handler's
//     stop path already invalidates the move).

p_reeler_info->flags.is_paused = false;   // Q10
```

### 10.3 `reeler_Start_Motor()` modifications (`gtron_can_cmd_parser.c:139`)

State-aware (Q9). Two paths:

**Resume path** (`is_paused == true`):
```c
if (p_reeler_info->flags.is_paused) {
    // Resume from paused state; preserve all hybrid state (Q14, Q16).
    p_reeler_info->flags.sensor_trigger = false;   // discard any edge captured during pause (Q14)

    // TMC4671 back to Velocity mode (Q15).
    tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, TMC4671_MOTION_MODE_VELOCITY);

    // Restore velocity ramp from 0 toward previously SW-set target (Q15).
    vel_timer       = true;
    rotate_vel_mode = true;

    p_reeler_info->flags.is_paused = false;

    DBG_Printf(ERR_LVL_DEBUG, "[HYB] reeler resumed\n");
    return;
}
```

**Fresh-start path** (`is_paused == false`):
```c
// ... existing fresh-start body unchanged ...

// At the end, reset Inspection hybrid state for fresh start.
if (p_reeler_info->hybrid.mode == HYBRID_MODE_INSPECTION) {
    p_reeler_info->hybrid.first_trigger_skip   = true;
    p_reeler_info->hybrid.consecutive_failures = 0;
    p_reeler_info->hybrid.cycle_armed          = false;
    p_reeler_info->flags.sensor_trigger        = false;
}
```

### 10.4 `REELER_MOTOR / AXC_PAUSE` handler (new)

Add to the `REELER_MOTOR` case in `parse_GTron_CAN_Msg_Data`:
```c
case AXC_PAUSE:
    reeler_Pause_Motor();
    break;
```

### 10.5 Behavior summary

- Pause -> Resume in Inspection: TMC4671 hard-holds the web; on Resume the velocity ramp re-engages from 0; the cycle continues from wherever it was. `consecutive_failures`, `gc`, anchors, and `cycle_armed` all preserved (Q14, Q16). Edges seen during pause are discarded by `sensor_trigger = false` in the resume path.
- Pause during a One-Shot move: ignored (Q12).
- One-Shot fire: leaves the reeler in position-hold (`flags.is_paused = true`). Exits hold on next `MOVE_TO` / `MOVE_BY` (which initiates a new position move and clears hold implicitly via the existing motion-start path) or `AXC_START` (Q5; state-aware Q9).
- Stop while paused: free-rotation Stopped, hybrid Inspection state reset, mode preserved, `is_paused = false` (Q11).

---

## 11. Camera Trigger Helper

```c
void trigger_Camera_Line(void)
{
    gpio_set_pin_level(REELER_INT, HIGH);
    delay_us(1);
    gpio_toggle_pin_level(DBGLED3);
    gpio_set_pin_level(REELER_INT, LOW);
    p_reeler_info->time_ms.cam_trig = millis();
}
```

> No CAN reply is emitted by this helper. The legacy `send_configurator_edge_reply` helper described in earlier drafts is **removed** (Q3).

---

## 12. Bug Fixes Bundled & Bugs Explicitly Left Alone

### 12.1 Fixed in this work

| # | Location | Bug | Fix |
|---|---|---|---|
| 1 | `Hybrid_Trigger.c:46` | `prev_trig_pos = current_position;` references undeclared `current_position` (should be local `current_pos`). | File is rewritten; bug naturally goes away. |
| 2 | `gtron_can_cmd_parser.c:584` | Missing `break;` before outer `default:` in `HYBRID_TRIGGER` case -> fall-through into default. | Add explicit `break;` in the renamed (`HYBRID_TRIGGER_INSPECTION`) and new (`HYBRID_TRIGGER_ONE_SHOT`) cases. |
| 3 | `Bring_Up/Motion/Hybrid_Trigger.h` | Header exposes nothing -- no prototypes, types, or macros. `check_For_Hybrid_Trigger()` works only by implicit extern. | Add proper prototypes and `hybrid_mode_t` enum (or move enum to `Hybrid_Trigger_Types.h` if include cycle). |
| 4 | `Motion.c:644` | `printf` / `DBG_Printf` in LIM_LFT ISR. Both are removed (Q18). | LIM_LFT ISR trimmed to flag + timestamp only. (LIM_RT is not a hybrid sensor and is left alone.) |

### 12.2 Pre-existing bugs explicitly left alone (decisions)

| Location | Bug | Decision rationale |
|---|---|---|
| `Motion.c:1226` | `abs(prev_trig_pos - current_position)` uses `current_position` declared on L1227 (after-use). | Encoder-mode block. Will be removed once Hybrid is proven; not worth fixing. |
| `Motion.c:1228-1231` | Duplicates the REELER_INT pulse code that lives in `trigger_Camera_Line()` in `Hybrid_Trigger.c`. | Same -- encoder-mode block, scheduled for removal. |
| `Motion.c:1128` | RHD reply uses `data[1] = AXC_HOMING` (17) instead of `AXC_MOVE_DONE` (11). | SC may currently parse `AXC_HOMING` as Move-Done. Touching this risks SC contract breakage. Out of scope. |
| `Motion.c:601` (`rot_Enc_Z_Pulse_Interrupt_Callback`) | Calls TMC4671 SPI inside an ISR -- race against main-loop SPI access. | Pre-existing, only fires during homing, presumably doesn't overlap with main-loop SPI in practice. Out of scope; flagged for future cleanup. Hybrid v2 introduces no new SPI-from-ISR access. |
| TMC4671 SPI mutex | No mutex/critical section guarding TMC4671 SPI bus. | Acceptable for v2. Hybrid v2 does **not** introduce any new SPI-from-ISR path (all hybrid SPI is in main-loop context). Cooperative single-thread model preserved. |

---

## 13. Constants

In `Macros.h` (or new `Bring_Up/Motion/Hybrid_Trigger_Cfg.h`):

```c
/* Hybrid Trigger configuration */
#define HYBRID_SLIP_TOLERANCE_PCT        5u   /* % of step_size; deviation band for slip detection */
#define HYBRID_ALERT_THRESHOLD           3u   /* consecutive failures before warn log */
#define HYBRID_PAUSE_HOLD_VELOCITY_RPM   2u   /* TMC4671 velocity_limit during position-hold pause (Q8) */
```

**Rationale for compile-time-only:**
- 5% scales with `step_size`, no need for application-specific tuning at runtime.
- Threshold of 3 is the design-doc default; can be promoted to a CAN-configurable parameter later if SW needs it.
- 2 RPM hold-limit is conservative; small enough to be unnoticeable, large enough to allow PI to reach target without latch-up.

---

## 14. Verification Plan

Manual on-target verification (no automated test harness in this repo). Each row is independent and can be exercised in any order; counters such as `gc` will accumulate across rows unless explicitly reset.

### 14.1 Compile-Clean Check

User builds the project on the existing Atmel Start / IAR toolchain. Expected: zero new warnings introduced by hybrid changes; existing warnings tolerated.

### 14.2 Inspection Mode Bench Test

| # | Step | Expected |
|---|---|---|
| 1 | SC: `REELER_MOTOR / AXC_TEETH / 86573`. | `position.trig_step_size = 86573`. |
| 2 | SC: `HYBRID_TRIGGER_INSPECTION / AXC_ENABLE`. | `mode = INSPECTION`. `is_hybrid_trig_enabled = true`. PRINTF: `[HYB] Inspection ENABLE`. |
| 3 | SC: `REELER_MOTOR / AXC_VELOCITY / rpm`. | Target velocity stored. |
| 4 | SC: `REELER_MOTOR / AXC_START`. | Reeler ramps. `first_trigger_skip = true`. |
| 5 | First sensor edge. | Anchor latched. No camera fire. `cycle_armed = true`. |
| 6 | Second sensor edge after >= step_size of rotation. | Camera fires (REELER_INT pulse, ~1 us HIGH). DBGLED3 toggles. `gc++`. |
| 7 | Force two consecutive spurious edges. | `consecutive_failures = 2`. No camera fire on those cycles. |
| 8 | Force one more spurious edge. | `consecutive_failures = 3`. PRINTF (WARN): `[HYB] slip threshold: fail=3 ...`. No CAN sent (Q17). |
| 9 | One valid trigger. | `consecutive_failures = 0`. Camera fires. `gc++`. |
| 10 | SC: `HYBRID_TRIGGER_INSPECTION / AXC_DISABLE`. | `mode = OFF`. `is_hybrid_trig_enabled = false`. |

### 14.3 One-Shot Mode -- edge case A (sensor crossed mid-move)

| # | Step | Expected |
|---|---|---|
| 1 | SC: `REELER_MOTOR / AXC_TEETH / 86573`. | step_size stored. |
| 2 | SC: `HYBRID_TRIGGER_ONE_SHOT / AXC_ENABLE`. | `mode = ONE_SHOT`. `one_shot_armed = false`. |
| 3 | SC: `REELER_MOTOR / AXC_MOVE_BY` distance long enough to cross the sensor. | `one_shot_armed = true`. Move begins. |
| 4 | Sensor crosses mid-move. | (a) `reeler_Pause_Motor` called: TMC4671 in Position mode, `flags.is_paused = true`. (b) Camera fires (REELER_INT pulse). (c) `check_move_done = false`. (d) `mode = OFF`, `one_shot_armed = false`. (e) **No RHD CAN sent**, **no `AXC_PRESSED` CAN sent** (Q3, Q4). (f) `gc` unchanged (Q6). |
| 5 | SC: `REELER_MOTOR / AXC_MOVE_BY ...`. | Reeler exits hold, executes move (Q5). |

### 14.4 One-Shot Mode -- edge case B (sensor not crossed)

| # | Step | Expected |
|---|---|---|
| 1 | SC: `HYBRID_TRIGGER_ONE_SHOT / AXC_ENABLE`. | `mode = ONE_SHOT`. |
| 2 | SC: `REELER_MOTOR / AXC_MOVE_BY` (short distance, no sensor crossing). | `one_shot_armed = true`. |
| 3 | Move completes without sensor edge. | RHD CAN sent (existing). `mode = OFF`, `one_shot_armed = false`. No camera fire. PRINTF: `[HYB] One-Shot move done with no edge; auto-disabled`. |

### 14.5 One-Shot Mode -- edge case C (re-issue after fire)

| # | Step | Expected |
|---|---|---|
| 1 | After 14.3 step 4: reeler is in position-hold, mode = OFF. | -- |
| 2 | SC: `REELER_MOTOR / AXC_START`. | State-aware resume (Q9): TMC4671 -> Velocity mode, ramp from 0 to `velocity.target`. Mode is OFF so no Inspection re-init. |
| 3 | Verify reeler is rotating in velocity mode. | Yes. |

### 14.6 Pause / Resume on `REELER_MOTOR` (Q7)

| # | Step | Expected |
|---|---|---|
| 1 | Inspection running, several successful triggers, `gc = N`, `cycle_armed = true`. | -- |
| 2 | SC: `REELER_MOTOR / AXC_PAUSE`. | `reeler_Pause_Motor` runs: TMC4671 -> Stopped -> position-hold @ 2 RPM -> Position mode. `vel_timer = false`, `rotate_vel_mode = false`, `flags.is_paused = true`. PRINTF: `[HYB] reeler paused at pos = ...`. |
| 3 | Force a sensor edge during pause. | `flags.sensor_trigger = true` (ISR). Main loop sees `is_paused`, leaves it alone. No anchor capture. No camera. |
| 4 | SC: `REELER_MOTOR / AXC_START`. | Resume path: `flags.sensor_trigger = false`, TMC4671 -> Velocity, ramp from 0, `is_paused = false`. PRINTF: `[HYB] reeler resumed`. |
| 5 | Hybrid state preserved. | `gc = N`, `cycle_armed = true`, `consecutive_failures` preserved (Q16). No first-trigger re-skip. |
| 6 | Next sensor edge after Resume (assuming web has moved >= step). | Normal Inspection cycle: re-anchor, slip check, fire if armed. |

### 14.7 Pause on `HYBRID_TRIGGER_INSPECTION` (Q7)

| # | Step | Expected |
|---|---|---|
| 1 | Inspection running. | -- |
| 2 | SC: `HYBRID_TRIGGER_INSPECTION / AXC_PAUSE`. | `flags.is_paused = true`. `mode` preserved. PRINTF: `[HYB] Inspection PAUSE`. |
| 3 | SC: `REELER_MOTOR / AXC_PAUSE`. | TMC4671 hold sequence runs (this is the motion-side pause). |
| 4 | SC: `REELER_MOTOR / AXC_START`. | Resume; `is_paused = false`. |

### 14.8 Pause on `HYBRID_TRIGGER_ONE_SHOT` (Q12)

| # | Step | Expected |
|---|---|---|
| 1 | One-Shot enabled, no move active (`one_shot_armed = false`). | -- |
| 2 | SC: `HYBRID_TRIGGER_ONE_SHOT / AXC_PAUSE`. | `flags.is_paused = true`. |
| 3 | One-Shot enabled, move in flight (`one_shot_armed = true`). | -- |
| 4 | SC: `HYBRID_TRIGGER_ONE_SHOT / AXC_PAUSE`. | **Ignored.** PRINTF: `[HYB] PAUSE on ONE_SHOT ignored - One-Shot move active`. `flags.is_paused` unchanged. |

### 14.9 Stop while paused (Q11)

| # | Step | Expected |
|---|---|---|
| 1 | After 14.6 step 2: reeler is paused. | `is_paused = true`. |
| 2 | SC: `REELER_MOTOR / AXC_STOP`. | Free-rotation Stopped. `cycle_armed = false`, `first_trigger_skip = true`, `consecutive_failures = 0`. `mode` preserved. `is_paused = false`. |

### 14.10 Diagnostic Counters

While exercising the above tests, the debugger watch window shows `hybrid.gc`, `hybrid.unhandled_edges`, `hybrid.consecutive_failures`, `hybrid.mode`, `hybrid.cycle_armed`, `hybrid.one_shot_armed`, `hybrid.first_trigger_skip`, `flags.is_paused` updating consistently with the test narrative.

### 14.11 Edge-During-Mode-OFF Diagnostic

| # | Step | Expected |
|---|---|---|
| 1 | `mode = OFF`, `is_paused = false`. Trip sensor. | `flags.sensor_trigger` set by ISR; main loop clears and increments `hybrid.unhandled_edges`. No state change otherwise. |

---

## 15. Open Items at Implementation Start

These are confirmation tasks that don't require fresh decisions but should be checked when touching the code:

1. **`flags.is_paused` bit position.** Verify the actual `Motor_Info_t.flags` substruct in `gtron_can_cmd_parser.h:83-96` matches the layout assumed in Section 5.2 before adding bit 11. Drift since investigation possible.
2. **Edge polarity.** Confirm `Macros.h:265-269` build switches (`LIMIT_SWITCH_RISING` / `LIMIT_SWITCH_FALLING`) are set correctly for the production sensor.
3. **TMC-API helper names.** Confirm names of `tmc4671_setVelocityLimit_RPM`, motion-mode constants, and target-position register macros against the actual TMC-API headers used by the project (`TMC-API/tmc/ic/TMC4671/TMC4671.h`). Reconcile placeholder names in Section 10.1 if necessary.
4. **`hybrid_state_s` struct tag visibility.** Avoided by referencing `&p_reeler_info->hybrid` directly in static helpers -- no aliasing required.
5. **Cycle-breaker for `hybrid_mode_t`.** If `Hybrid_Trigger.h` includes `gtron_can_cmd_parser.h` (for `Motor_Info_t`) AND `gtron_can_cmd_parser.h` needs `hybrid_mode_t` (for the `hybrid` substruct), a circular include results. Resolve by extracting `hybrid_mode_t` to `Hybrid_Trigger_Types.h` and including that small header from both. See Section 17.1.

---

## 16. Risk Notes

### 16.1 SPI Bus Contention

Hybrid v2 keeps every TMC4671 SPI access in main-loop context (`run_Velocity_Ramp` for Inspection; `check_For_Move_Done` for One-Shot; `reeler_Pause_Motor` is invoked from a CAN handler or from the One-Shot edge handler, both main-loop). The existing Z-pulse ISR is the only SPI-from-ISR access on the AXC and is unrelated to hybrid. **No new mutex required.**

### 16.2 Polling Cadence Coverage

- Inspection cadence is bound to VEL_TIMER (1 ms) and gated by `sag_enabled && rotate_vel_mode`. Pause sets `rotate_vel_mode = false`, which cleanly halts polling without explicit checks at the call site.
- One-Shot cadence is bound to the main loop iteration rate while a move is active. Sub-millisecond.

### 16.3 Lost Edges During High-Frequency Bursts

The ISR sets `flags.sensor_trigger = true` (bit, no queue). If two sensor edges arrive between main-loop ticks, the second is silently coalesced. At realistic reeler speeds (<= 1200 parts/min ~= 20 Hz) and >= 1 kHz polling, this is impossible.

### 16.4 `is_hybrid_trig_enabled` Back-Compat Aliasing

The legacy 1-bit flag is maintained in lockstep with `hybrid.mode`. There is exactly one writer pattern (CAN handlers + One-Shot auto-disable). Risk of divergence: low. Mitigation: a brief comment in the struct definition warning that the flag is a legacy mirror.

### 16.5 RHD vs One-Shot Fire Ordering

One-Shot polling is placed BEFORE the move-done settle check in `check_For_Move_Done()`. This guarantees: if the sensor edge arrives in the SAME polling tick that detects move-done, the One-Shot fire path (which clears `check_move_done`) wins, and the subsequent settle check returns early without sending RHD. SW receives exactly one of:
- Reeler_Int pulse (camera fired, no RHD), OR
- RHD only (no edge during move).

### 16.6 GC Overflow

`uint64_t` at 1200 parts/min overflows in ~487,000 years. Not a concern.

### 16.7 Latent `DBG_Printf` ISR-Deadlock Hazard (carried over from Phase 5)

The Phase 5 migration replaced `printf` with the new `DBG_Printf` library (DMA-driven SERCOM7 transport, busy-wait on a DMA-done flag in `DBG_RTOS_NONE` mode). When called from an ISR while a foreground `DBG_Printf` has DMA in flight, the ISR will spin forever on the flag -- DMAC ISR cannot preempt it (Cortex-M0+, equal NVIC priorities) -- and CAN1_Handler is starved, manifesting as silent CAN failure.

**Phase 8 incidentally eliminates the only known ISR call site** (LIM_LFT in Section 6.1) by removing `DBG_Printf` from the ISR body. After Phase 8, no ISR in this codebase calls `DBG_Printf`.

A proper library-side fix (Phase 5.6: IPSR-detect + non-blocking ISR fast path) is **deferred**. New ISR-context `DBG_Printf` callers must NOT be added until Phase 5.6 lands.

### 16.8 TMC4671 Mode Transitions

The pause sequence (Q8) toggles `MODE_MOTION` register multiple times in quick succession (Stopped -> set target -> set vel limit -> Position). Per TMC4671 datasheet section 4.7.11 / 6.5 (Q21), mode switches take effect on the next PWM cycle. The intermediate values written between mode switches (target position, velocity limit) should be sampled by the controller cleanly because the active mode at write time is "Stopped" (no torque). This has been validated by the TMC team's reference designs but **must be verified on bench**.

---

## 17. Appendix A -- File-by-File Reference

### 17.1 `Bring_Up/Motion/Hybrid_Trigger.h` (and optional `Hybrid_Trigger_Types.h`)

If `gtron_can_cmd_parser.h` needs `hybrid_mode_t` for the new `hybrid` substruct member, and `Hybrid_Trigger.h` needs `Motor_Info_t` from `gtron_can_cmd_parser.h`, the include graph would be circular. **Cycle-breaker:** extract the enum to a tiny `Hybrid_Trigger_Types.h` and include it from both.

`Hybrid_Trigger_Types.h`:
```c
#ifndef HYBRID_TRIGGER_TYPES_H_
#define HYBRID_TRIGGER_TYPES_H_

typedef enum {
    HYBRID_MODE_OFF        = 0,
    HYBRID_MODE_INSPECTION = 1,
    HYBRID_MODE_ONE_SHOT   = 2,
} hybrid_mode_t;

#endif
```

`Hybrid_Trigger.h` (final shape):
```c
#ifndef HYBRID_TRIGGER_H_
#define HYBRID_TRIGGER_H_

#include <atmel_start.h>
#include "Global_Vars.h"
#include "TMC-API/tmc/ic/TMC4671/TMC4671.h"
#include "Bring_Up/Motion/Hybrid_Trigger_Types.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

/* Public API */
void hybrid_trigger_init(void);                          /* zero/reset state at boot */
void check_For_Hybrid_Trigger(void);                     /* main-loop dispatcher */
void trigger_Camera_Line(void);                          /* shared pulse helper */

/* Configuration constants (kept here for visibility; can be moved to Hybrid_Trigger_Cfg.h) */
#ifndef HYBRID_SLIP_TOLERANCE_PCT
#define HYBRID_SLIP_TOLERANCE_PCT     5u
#endif
#ifndef HYBRID_ALERT_THRESHOLD
#define HYBRID_ALERT_THRESHOLD        3u
#endif
#ifndef HYBRID_PAUSE_HOLD_VELOCITY_RPM
#define HYBRID_PAUSE_HOLD_VELOCITY_RPM 2u
#endif

#endif /* HYBRID_TRIGGER_H_ */
```

### 17.2 `Bring_Up/Motion/Hybrid_Trigger.c`

Final structure (skeleton -- full bodies in Sections 6, 7, 11):

```c
#include "Hybrid_Trigger.h"

/* Forward declarations of statics */
static void handle_inspection_tick(void);
static void handle_one_shot_tick(void);

/* Public -- pulse helper (Section 11) */
void trigger_Camera_Line(void) { /* ... */ }

/* Public -- boot init */
void hybrid_trigger_init(void) { /* zero-init reserved hook */ }

/* Public -- main-loop dispatcher (Section 7.1) */
void check_For_Hybrid_Trigger(void) { /* ... */ }

/* Static -- Inspection (Section 7.2) */
static void handle_inspection_tick(void) { /* ... */ }

/* Static -- One-Shot (Section 7.3) */
static void handle_one_shot_tick(void) { /* ... */ }
```

### 17.3 `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h`

Modifications:
- Add `is_paused : 1` to `flags` substruct at bit 11; reduce `reserved` from 21 to 20 (Section 5.2).
- Add `hybrid` substruct (Section 5.3), after `flags`.
- Add prototype: `void reeler_Pause_Motor(void);`
- Add `#include "Bring_Up/Motion/Hybrid_Trigger_Types.h"` near the top.

### 17.4 `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.c`

Modifications:
- `reeler_Start_Motor()` (~L139): split into resume-vs-fresh-start paths per Section 10.3.
- `reeler_Stop_Motor()` (~L159): append Section 10.2 hook.
- `reeler_Move()` (~L64-82): append Section 9.2 engagement block at end.
- `reeler_Pause_Motor()` (new): per Section 10.1.
- `parse_GTron_CAN_Msg_Data` `HYBRID_TRIGGER` case (~L569-585): rename to `HYBRID_TRIGGER_INSPECTION`, fix missing `break;`, expand body per Section 9.4.
- Add `HYBRID_TRIGGER_ONE_SHOT` case immediately after, per Section 9.1.
- Add `AXC_PAUSE` op to `REELER_MOTOR` case per Section 10.4.

### 17.5 `Bring_Up/Motion/Motion.c`

Modifications:
- `left_Limit_Interrupt_Callback` (~L644): trim per Section 6.1 (LIM_LFT is the hybrid sensor -- Q18).
- `right_Limit_Interrupt_Callback` (~L657): **NOT touched** by Phase 8 (Q18).
- `check_For_Move_Done` (~L1109): add One-Shot polling at top + auto-disable block in settle path per Section 8.2.
- **No changes** to encoder-mode block at L1225-1239.
- **No changes** to `Motion.c:1128` `AXC_HOMING` reply.

### 17.6 `Bring_Up/CAN/IMM_CAN_Message_Id.h`

In `AxC_Peripherals_t`:
- Rename: `HYBRID_TRIGGER` -> `HYBRID_TRIGGER_INSPECTION` (value 8 unchanged).
- Add: `HYBRID_TRIGGER_ONE_SHOT = 9`.

In `AxC_Operations_t`:
- Add: `AXC_PAUSE = 18` (immediately after `AXC_HOMING = 17`, before the `NO_OF_AXC_OPERAITONS` sentinel).

Update all usages of the old `HYBRID_TRIGGER` name (search and adjust -- primarily `gtron_can_cmd_parser.c:569`).

### 17.7 `Macros.h` (or `Hybrid_Trigger_Cfg.h`)

Add the three constants from Section 13. If a separate `Hybrid_Trigger_Cfg.h` is created, include it from `Hybrid_Trigger.h` and from `Macros.h` if `Macros.h` is the project-wide constants hub.

### 17.8 Suggested Commit Boundaries (for the user's Stage 3)

For reviewability, group the firmware changes into roughly these commits:

1. `feat(can): add HYBRID_TRIGGER_ONE_SHOT peripheral and AXC_PAUSE op` -- enum changes only.
2. `feat(reeler): add flags.is_paused bit and hybrid substruct` -- struct extensions only; no behavior change.
3. `feat(motion): trim LIM_LFT ISR to flag+timestamp` -- ISR-only change.
4. `feat(hybrid): rewrite Hybrid_Trigger module with Inspection + One-Shot state machines` -- the bulk; new `Hybrid_Trigger.[ch]` and optional `Hybrid_Trigger_Types.h`.
5. `feat(reeler): add reeler_Pause_Motor and state-aware resume in reeler_Start_Motor` -- pause/resume mechanics.
6. `feat(parser): wire HYBRID_TRIGGER_INSPECTION/ONE_SHOT and AXC_PAUSE handlers` -- CAN dispatch; fix missing-break.
7. `feat(motion): One-Shot polling and auto-disable in check_For_Move_Done` -- One-Shot integration.
8. `feat(macros): add HYBRID_* configuration constants` -- can be folded into commit 4 if preferred.

---

## 18. Appendix B -- Decision Log (Q1-Q21)

Locked decisions from the design Q&A that shaped this plan. Cross-referenced inline.

| # | Decision |
|---|---|
| Q1 | Drop fractional-accumulator scheme. SW sends a single integer `step_size = round(offset)` via the existing `AXC_TEETH` op. Re-anchoring per sensor edge bounds the error. |
| Q2 | Rename `CONFIGURATOR` -> `ONE_SHOT` everywhere (enum, peripheral name, `cfg_armed` -> `one_shot_armed`, function names, docs). Enum value remains 9. |
| Q3 | One-Shot does not send `AXC_PRESSED` (op 14) reply. Remove legacy reply helper. |
| Q4 | One-Shot edge sequence: stop reeler with position hold -> fire camera -> suppress RHD -> auto-disable. |
| Q5 | One-Shot fire leaves motor in position-hold; exits only on next `MOVE_TO` / `MOVE_BY` or `AXC_START`. |
| Q6 | One-Shot does **not** increment `gc`. GC is Inspection-only. |
| Q7 | `AXC_PAUSE = 18`. Sent on `REELER_MOTOR`, `HYBRID_TRIGGER_INSPECTION`, `HYBRID_TRIGGER_ONE_SHOT` independently. |
| Q8 | Pause mechanism: TMC4671 -> Stopped -> set `target = actual` and `velocity_limit ~= 2 RPM` -> Position mode. |
| Q9 | `AXC_START` is state-aware: if `is_paused` resume; else fresh start. No new `AXC_RESUME` op. |
| Q10 | Add `flags.is_paused : 1` at bit 11 in `Motor_Info_t.flags`. Set by `reeler_Pause_Motor`. Cleared by `reeler_Start_Motor` and `reeler_Stop_Motor`. |
| Q11 | `AXC_STOP` while paused: free-rotation Stopped, hybrid Inspection state reset, `mode` preserved, `is_paused = false`. |
| Q12 | `HYBRID_TRIGGER_ONE_SHOT / AXC_PAUSE` during a One-Shot move: log warning, no-op. |
| Q13 | Pause sets `vel_timer = false; rotate_vel_mode = false;` to short-circuit ramp and hybrid checks. |
| Q14 | Edges seen during pause are discarded by Resume (clear `flags.sensor_trigger`). ISR is mode-blind. |
| Q15 | Resume: TMC -> Velocity mode; ramp from 0 to previously SW-set `velocity.target`. |
| Q16 | `consecutive_failures` is **preserved** across pause / resume. |
| Q17 | Slip / spurious CAN alert deferred (protocol TBD). `DBG_Printf` at threshold; `TODO` at the future `can_Write` site. |
| Q18 | LIM_LFT is the hybrid sensor. LIM_RT untouched. ISR trimmed to `flags.sensor_trigger = true; time_ms.sens_trig = millis();` only. |
| Q19 | Doc edits go to `Hybrid_Triggering_Firmware_Design - Copy.md` only. The older `Hybrid_Triggering_Firmware_Design.md` is left untouched. |
| Q20 | Pin symbol in design doc is `LIM_LFT` to match the firmware project. |
| Q21 | TMC4671 datasheet sections cited: 4.7.5 (PI clipping), 4.7.8 (P position controller), 4.7.11 (motion modes), 6.5 (modes of operation). |

---

**End of plan.**
