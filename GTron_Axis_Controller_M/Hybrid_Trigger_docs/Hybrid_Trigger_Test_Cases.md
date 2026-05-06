# Hybrid Trigger - Firmware Test Cases (Phase 8)

Status: Draft v1.0
Scope: Firmware-side bench verification of Phase 8 Hybrid Triggering on the GTron AxC (ATSAMC21N18A). Covers both Inspection (continuous) and One-Shot modes, the new `AXC_PAUSE` operation, slip handling, edge-case boundaries, and negative tests.

This document is the verification companion to:

- `Hybrid_Triggering_Firmware_Design - Copy.md` (authoritative design, decisions Q1-Q21)
- `Hybrid_Trigger_Implementation_Plan.md` (Stage 2 implementation plan)
- `Hybrid_Trigger_HLD.md` (high-level overview)

It is intended to be executed by a firmware engineer with a CAN traffic generator (e.g. Kvaser, PCAN, or the existing TMCL-IDE bridge) and an in-circuit debugger attached to the AxC. No source code is reproduced here; all references are to symbols defined in the design and implementation plan.

---

## Conventions

### CAN frame shorthand

All command frames use the project's standard 11-bit ID layout. In this document a frame is written as:

> `peripheral=<P>, op=<O>, value=<V>`

where `P`, `O` are the values from `IMM_CAN_Message_Id.h` (see implementation plan, section 7) and `V` is the 32-bit signed payload (decimal unless prefixed `0x`). Reply frames from the AxC are written the same way with the suffix `(reply)`.

Peripheral IDs used in this document:

| Name                          | ID |
|-------------------------------|----|
| `REELER_MOTOR`                | 1  |
| `HYBRID_TRIGGER_INSPECTION`   | 8  |
| `HYBRID_TRIGGER_ONE_SHOT`     | 9  |

Operation IDs used in this document:

| Name           | Op | Notes                                         |
|----------------|----|-----------------------------------------------|
| `AXC_START`    | 1  | State-aware (resume if paused, else fresh)    |
| `AXC_STOP`     | 2  | Hard stop, clears pause                       |
| `AXC_ENABLE`   | 3  |                                               |
| `AXC_DISABLE`  | 4  |                                               |
| `AXC_VELOCITY` | 5  |                                               |
| `AXC_ROTATE`   | 6  |                                               |
| `AXC_MOVE_TO`  | 7  | One-Shot: arms cycle if mode enabled          |
| `AXC_MOVE_BY`  | 8  | One-Shot: arms cycle if mode enabled          |
| `AXC_TEETH`    | 12 | Sets `position.trig_step_size` (integer mm)   |
| `AXC_PRESSED`  | 14 | Inspection edge-anchor reply (not One-Shot)   |
| `AXC_HOMING`   | 17 |                                               |
| `AXC_PAUSE`    | 18 | New for Phase 8                               |

### Watch variables

Test cases reference firmware state via the names defined in the implementation plan (sections 6 and 17). Common ones:

- `flags.is_hybrid_trig_enabled`        (bit 10)
- `flags.is_paused`                     (bit 11, new)
- `flags.is_one_shot`                   (mode selector)
- `position.trig_step_size`             (integer mm, set by `AXC_TEETH`)
- `position.target_position`
- `position.current_position`
- `hybrid.gc`                           (geometric controller state)
- `hybrid.cycle_armed`                  (One-Shot)
- `hybrid.consecutive_failures`         (slip detector counter)
- `hybrid.last_anchor_position`
- `hybrid.next_trigger_position`

### Pass / fail vocabulary

- "PASS" means **every** bullet under "Pass criteria" is observed on the bench.
- A single deviation -> FAIL, log frame trace + watch dump, do not retry until root cause is understood.
- "Notes" entries are observational hints; they are not pass criteria.

### Hardware preconditions (apply to every group unless overridden)

1. AxC powered, USB debugger attached, SERCOM7 dbg log captured.
2. Reeler motor (TMC4671) wired, encoder connected, target axis free to move.
3. LIM_LFT sensor wired and verified to toggle in the IO expander snapshot.
4. Camera trigger output observable (scope on the trigger line, or downstream camera ack).
5. Firmware built from the head of `hybrid-trig-dev` with Phase 8 changes applied.
6. CAN bus quiet apart from the test injector.

---

## Group index

| Group | Theme                                  | Cases |
|-------|----------------------------------------|-------|
| G0    | Boot / smoke                           | 2     |
| G1    | Inspection - happy path                | 5     |
| G2    | Inspection - slip detection            | 4     |
| G3    | Inspection - edge / boundary           | 4     |
| G4    | One-Shot - mode A (Move-To)            | 4     |
| G5    | One-Shot - mode B (Move-By)            | 3     |
| G6    | One-Shot - edge anchor handling        | 3     |
| G7    | Pause / Resume via REELER_MOTOR        | 5     |
| G8    | Pause / Resume via hybrid peripherals  | 4     |
| G9    | Stop interactions                      | 3     |
| G10   | Negative / robustness                  | 4     |
|       | **Total**                              | **41**|

---

# G0 - Boot / smoke

### HYB-INSP-G0-01 - Cold boot defaults

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G0-01 |
| Title            | Cold boot leaves hybrid disabled and unpaused |
| Pre-conditions   | AxC just power-cycled, no CAN traffic injected yet |
| Setup CAN seq    | (none) |
| Stimulus         | Read `Motor_Info_t` flags via debugger immediately after main loop entry |
| Expected behaviour | All hybrid flags at default; no spurious trigger output |
| Pass criteria    | `flags.is_hybrid_trig_enabled == 0`; `flags.is_paused == 0`; `flags.is_one_shot == 0`; `hybrid.gc == GC_IDLE`; `hybrid.consecutive_failures == 0`; camera trigger line idle |
| Notes            | Establishes the zero state every other case starts from |

### HYB-INSP-G0-02 - AXC_TEETH stores integer step

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G0-02 |
| Title            | `AXC_TEETH` writes `position.trig_step_size` as integer mm |
| Pre-conditions   | Cold boot |
| Setup CAN seq    | (none) |
| Stimulus         | Send `peripheral=1, op=12, value=37` |
| Expected behaviour | `position.trig_step_size` = 37 (integer); no rounding/truncation drama because input is already integer |
| Pass criteria    | Watch shows `trig_step_size == 37`; no error reply on CAN; no other hybrid state mutated |
| Notes            | Q1: step_size is integer mm, set via existing `AXC_TEETH` op |

---

# G1 - Inspection happy path

### HYB-INSP-G1-01 - Enable Inspection mode

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G1-01 |
| Title            | `HYBRID_TRIGGER_INSPECTION` + `AXC_ENABLE` arms inspection |
| Pre-conditions   | Cold boot, `AXC_TEETH` sent with value 25 |
| Setup CAN seq    | `peripheral=1, op=12, value=25` |
| Stimulus         | `peripheral=8, op=3, value=0` (HYBRID_TRIGGER_INSPECTION + AXC_ENABLE) |
| Expected behaviour | Hybrid armed in inspection mode; reeler not yet running |
| Pass criteria    | `flags.is_hybrid_trig_enabled == 1`; `flags.is_one_shot == 0`; `hybrid.gc == GC_WAIT_ANCHOR`; reeler still stopped; no camera pulse |
| Notes            | Q2: peripheral 8 is the Inspection peripheral (renamed from CONFIGURATOR) |

### HYB-INSP-G1-02 - First LIM_LFT edge anchors position

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G1-02 |
| Title            | First sensor edge sets anchor and arms first trigger |
| Pre-conditions   | HYB-INSP-G1-01 has passed, reeler running at low velocity |
| Setup CAN seq    | (continued) `peripheral=1, op=5, value=200` (start reeler at 200 RPM-equivalent) |
| Stimulus         | Manually trip LIM_LFT once |
| Expected behaviour | Anchor captured, next trigger position computed |
| Pass criteria    | `hybrid.last_anchor_position` == current encoder position at edge; `hybrid.next_trigger_position == last_anchor_position + trig_step_size`; `hybrid.gc == GC_WAIT_TRIGGER`; AxC sends `AXC_PRESSED` reply on peripheral=8 |
| Notes            | Q3: `AXC_PRESSED` only emitted in Inspection mode; Q18: only LIM_LFT counts |

### HYB-INSP-G1-03 - Encoder offset fires camera

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G1-03 |
| Title            | Reaching `next_trigger_position` fires camera and rolls to next |
| Pre-conditions   | HYB-INSP-G1-02 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | Allow reeler to advance past `next_trigger_position` |
| Expected behaviour | Single camera pulse, rolling target advance |
| Pass criteria    | One pulse on camera trigger line at the moment `current_position` crosses `next_trigger_position`; `hybrid.next_trigger_position` advances by `trig_step_size`; `hybrid.gc` stays in `GC_WAIT_TRIGGER`; reeler unaffected |
| Notes            | Camera pulse width per implementation plan section 9 |

### HYB-INSP-G1-04 - Multiple consecutive triggers

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G1-04 |
| Title            | Continuous reeler motion produces N triggers at N*step_size |
| Pre-conditions   | HYB-INSP-G1-03 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | Let reeler run for at least 5 * `trig_step_size` of travel without re-tripping LIM_LFT |
| Expected behaviour | 5 evenly spaced camera pulses |
| Pass criteria    | Pulse spacing on scope == `trig_step_size` mm of encoder travel +/- one encoder count; `hybrid.consecutive_failures == 0` throughout |
| Notes            | Verifies rolling-target arithmetic and absence of fractional drift |

### HYB-INSP-G1-05 - Re-anchor on next LIM_LFT edge

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G1-05 |
| Title            | Subsequent LIM_LFT edge re-anchors and resets failure counter |
| Pre-conditions   | HYB-INSP-G1-04 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | Trip LIM_LFT again |
| Expected behaviour | Anchor refreshed, rolling target rebased |
| Pass criteria    | `hybrid.last_anchor_position` updated to new edge position; `hybrid.next_trigger_position == last_anchor_position + trig_step_size`; `hybrid.consecutive_failures` reset to 0; `AXC_PRESSED` reply emitted |
| Notes            | Confirms anchor pipeline is repeatable, not a one-time latch |

---

# G2 - Inspection slip detection

### HYB-SLIP-G2-01 - Single missed trigger increments counter

| Field            | Value |
|------------------|-------|
| ID               | HYB-SLIP-G2-01 |
| Title            | Slip increments `consecutive_failures` |
| Pre-conditions   | Inspection running per HYB-INSP-G1-04 |
| Setup CAN seq    | (continuing) |
| Stimulus         | Briefly hold the reel against motion (induce mechanical slip) so that one expected trigger window passes without a sensor edge confirming alignment per the slip rule in design doc section 8 |
| Expected behaviour | Counter increments by 1, no alert frame yet |
| Pass criteria    | `hybrid.consecutive_failures == 1`; no slip alert frame on CAN (Q17 deferred); camera continues firing on rolling target |
| Notes            | Q17: CAN slip alert is intentionally not implemented yet |

### HYB-SLIP-G2-02 - Counter resets on good edge

| Field            | Value |
|------------------|-------|
| ID               | HYB-SLIP-G2-02 |
| Title            | Healthy LIM_LFT edge clears slip counter |
| Pre-conditions   | HYB-SLIP-G2-01 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | Release the reel so it tracks normally and trip LIM_LFT |
| Expected behaviour | Counter clears |
| Pass criteria    | `hybrid.consecutive_failures == 0` after the next valid edge |
| Notes            | Confirms slip is per-cycle, not cumulative-forever |

### HYB-SLIP-G2-03 - Threshold reached: GC reaction

| Field            | Value |
|------------------|-------|
| ID               | HYB-SLIP-G2-03 |
| Title            | Reaching slip threshold transitions `gc` per design |
| Pre-conditions   | Inspection running |
| Setup CAN seq    | (continuing) |
| Stimulus         | Induce N consecutive slips where N == threshold defined in design doc section 8 |
| Expected behaviour | GC handles slip-saturation per Q17 (counter saturates, no alert, camera output behaviour as per design) |
| Pass criteria    | `hybrid.consecutive_failures` saturates at threshold (does not wrap); GC state matches design doc table for slip-saturation row; no spurious CAN alert |
| Notes            | Bench confirmation that we have not regressed on the placeholder behaviour |

### HYB-SLIP-G2-04 - Counter survives non-pause idle

| Field            | Value |
|------------------|-------|
| ID               | HYB-SLIP-G2-04 |
| Title            | Slip counter is not cleared by reeler velocity going to zero (without pause) |
| Pre-conditions   | HYB-SLIP-G2-01 (counter == 1) |
| Setup CAN seq    | (continuing) |
| Stimulus         | Send `peripheral=1, op=5, value=0` (set reeler velocity 0) without pausing |
| Expected behaviour | Counter unchanged |
| Pass criteria    | `hybrid.consecutive_failures` still == 1; flags unchanged; no GC state change beyond what the design specifies for zero velocity |
| Notes            | Q16 says counter is preserved across pause; this confirms the simpler "still running, just slow" case too |

---

# G3 - Inspection edge / boundary

### HYB-INSP-G3-01 - Step size 1 mm minimum

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G3-01 |
| Title            | Smallest legal `trig_step_size` works |
| Pre-conditions   | Cold boot |
| Setup CAN seq    | `peripheral=1, op=12, value=1`; `peripheral=8, op=3, value=0`; `peripheral=1, op=5, value=200` |
| Stimulus         | Trip LIM_LFT, allow 5 mm of travel |
| Expected behaviour | 5 camera pulses, one per millimetre |
| Pass criteria    | Pulse count == 5; pulse spacing == 1 mm of encoder travel +/- 1 count |
| Notes            | Lower bound check |

### HYB-INSP-G3-02 - Step size at integer ceiling

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G3-02 |
| Title            | Large `trig_step_size` (e.g. 500) does not overflow target arithmetic |
| Pre-conditions   | Cold boot |
| Setup CAN seq    | `peripheral=1, op=12, value=500`; `peripheral=8, op=3, value=0`; `peripheral=1, op=5, value=200` |
| Stimulus         | Trip LIM_LFT, allow 1500 mm of travel |
| Expected behaviour | 3 camera pulses |
| Pass criteria    | `hybrid.next_trigger_position` advances correctly each cycle without overflow; pulse count == 3; positions monotonically increasing |
| Notes            | Upper bound sanity (the real ceiling is encoder position width) |

### HYB-INSP-G3-03 - Trigger position exactly equals current position at enable

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G3-03 |
| Title            | No spurious trigger when arming on a position that coincidentally matches |
| Pre-conditions   | Move axis to known position, then enable hybrid |
| Setup CAN seq    | `peripheral=1, op=12, value=10`; manually drive axis so `current_position` ends at exactly the position that would later coincide with `last_anchor_position + trig_step_size`; then `peripheral=8, op=3, value=0` |
| Stimulus         | Trip LIM_LFT |
| Expected behaviour | Anchor latches at LIM_LFT moment, then needs another full step before trigger |
| Pass criteria    | No camera pulse before the next 10 mm of travel; trigger fires exactly once at +10 mm; `hybrid.gc` stays consistent |
| Notes            | Confirms anchor-then-step ordering, no off-by-zero |

### HYB-INSP-G3-04 - Encoder wrap behaviour

| Field            | Value |
|------------------|-------|
| ID               | HYB-INSP-G3-04 |
| Title            | Position arithmetic remains correct near encoder wrap (if applicable) |
| Pre-conditions   | Inspection running, axis driven near encoder limit |
| Setup CAN seq    | (continuing) |
| Stimulus         | Allow encoder counter to approach and cross its wrap boundary while inspection is active |
| Expected behaviour | Trigger spacing remains correct across the wrap, or wrap is documented as out-of-scope |
| Pass criteria    | Either (a) pulse spacing remains == `trig_step_size` across the wrap, or (b) firmware deliberately stops triggering and reports per design doc; behaviour matches design |
| Notes            | If encoder is 32-bit signed mm-equivalent, wrap is unreachable in practice; case may be marked N/A |

---

# G4 - One-Shot mode A (Move-To)

### HYB-OS-A-G4-01 - Enable One-Shot, no movement yet

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-A-G4-01 |
| Title            | Enabling One-Shot does not by itself arm a cycle |
| Pre-conditions   | Cold boot |
| Setup CAN seq    | `peripheral=1, op=12, value=20` |
| Stimulus         | `peripheral=9, op=3, value=0` (HYBRID_TRIGGER_ONE_SHOT + AXC_ENABLE) |
| Expected behaviour | Mode armed but no cycle until a Move-To/By is issued |
| Pass criteria    | `flags.is_hybrid_trig_enabled == 1`; `flags.is_one_shot == 1`; `hybrid.cycle_armed == 0`; reeler idle; no camera pulse |
| Notes            | Q2: peripheral 9 is the new One-Shot peripheral |

### HYB-OS-A-G4-02 - Move-To arms cycle

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-A-G4-02 |
| Title            | `AXC_MOVE_TO` arms the One-Shot cycle |
| Pre-conditions   | HYB-OS-A-G4-01 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=7, value=300` (move to 300 mm) |
| Expected behaviour | Cycle armed, reeler starts moving |
| Pass criteria    | `hybrid.cycle_armed == 1`; `position.target_position == 300`; reeler accelerating; `hybrid.gc == GC_WAIT_ANCHOR` |
| Notes            | Cycle is single-shot for the duration of this move |

### HYB-OS-A-G4-03 - LIM_LFT edge fires camera and stops reeler

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-A-G4-03 |
| Title            | LIM_LFT during armed cycle: trigger camera, stop reeler with position hold |
| Pre-conditions   | HYB-OS-A-G4-02 in flight (reeler still moving toward 300) |
| Setup CAN seq    | (continuing) |
| Stimulus         | Trip LIM_LFT before reeler reaches target |
| Expected behaviour | Camera fires once, reeler decelerates per Q8 sequence (Stopped -> hold@2RPM -> Position), RHD suppressed, mode auto-disables |
| Pass criteria    | One camera pulse at edge; reeler executes Stopped -> hold@2RPM -> Position transition observable on TMC4671 watch; RHD suppression observable per implementation plan section 11; `flags.is_hybrid_trig_enabled` clears to 0 (auto-disable, Q4); `hybrid.cycle_armed == 0`; no `AXC_PRESSED` reply (Q3) |
| Notes            | Core One-Shot behaviour. RHD suppression must be visible. |

### HYB-OS-A-G4-04 - Move-To completes without edge: no trigger

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-A-G4-04 |
| Title            | If LIM_LFT never trips, cycle ends silently at target |
| Pre-conditions   | One-Shot enabled, `AXC_MOVE_TO` issued for a position the axis can reach without crossing LIM_LFT |
| Setup CAN seq    | `peripheral=1, op=12, value=20`; `peripheral=9, op=3, value=0`; `peripheral=1, op=7, value=<reachable>` |
| Stimulus         | Allow move to complete naturally, do not trip LIM_LFT |
| Expected behaviour | Reeler reaches target, no camera pulse, mode remains enabled |
| Pass criteria    | No camera pulse for the duration of the move; `position.current_position` settles at target; `flags.is_hybrid_trig_enabled` still 1; `hybrid.cycle_armed == 0` (cycle consumed by completion); ready for next Move-To |
| Notes            | Confirms cycle is "one shot per move" not "one shot per enable" |

---

# G5 - One-Shot mode B (Move-By)

### HYB-OS-B-G5-01 - Move-By arms cycle

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-B-G5-01 |
| Title            | `AXC_MOVE_BY` also arms a One-Shot cycle |
| Pre-conditions   | One-Shot enabled (HYB-OS-A-G4-01 setup) |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=8, value=150` |
| Expected behaviour | Relative target computed, cycle armed, reeler moves |
| Pass criteria    | `position.target_position == position.current_position_at_command + 150`; `hybrid.cycle_armed == 1`; reeler accelerating |
| Notes            | Mirror of G4-02 for Move-By |

### HYB-OS-B-G5-02 - Edge fires camera mid-Move-By

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-B-G5-02 |
| Title            | LIM_LFT during Move-By: same auto-disable behaviour as Move-To |
| Pre-conditions   | HYB-OS-B-G5-01 in flight |
| Setup CAN seq    | (continuing) |
| Stimulus         | Trip LIM_LFT before relative move completes |
| Expected behaviour | Identical to HYB-OS-A-G4-03 |
| Pass criteria    | One camera pulse; TMC4671 hold sequence; RHD suppressed; mode auto-disables; `cycle_armed == 0` |
| Notes            | Confirms behaviour is independent of which move command armed the cycle |

### HYB-OS-B-G5-03 - Negative Move-By direction

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-B-G5-03 |
| Title            | Move-By with negative value, edge handling unchanged |
| Pre-conditions   | One-Shot enabled |
| Setup CAN seq    | `peripheral=1, op=12, value=20`; `peripheral=9, op=3, value=0`; `peripheral=1, op=8, value=-100` |
| Stimulus         | Trip LIM_LFT during the negative-direction move |
| Expected behaviour | Camera fires once; reeler stops in the direction of travel; mode auto-disables |
| Pass criteria    | Same as HYB-OS-A-G4-03 |
| Notes            | Confirms hybrid is direction-agnostic on the trigger side |

---

# G6 - One-Shot edge anchor handling

### HYB-OS-EDGE-G6-01 - LIM_LFT before move command: ignored

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-EDGE-G6-01 |
| Title            | Edge while One-Shot enabled but no cycle armed: no trigger |
| Pre-conditions   | One-Shot enabled, no Move-To/By issued |
| Setup CAN seq    | `peripheral=1, op=12, value=20`; `peripheral=9, op=3, value=0` |
| Stimulus         | Trip LIM_LFT |
| Expected behaviour | Edge ignored |
| Pass criteria    | No camera pulse; `hybrid.cycle_armed` still 0; mode still enabled; no `AXC_PRESSED` reply (Q3) |
| Notes            | Cycle must be explicitly armed by a move command |

### HYB-OS-EDGE-G6-02 - Multiple edges during one cycle

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-EDGE-G6-02 |
| Title            | Only the first LIM_LFT edge in an armed cycle fires the camera |
| Pre-conditions   | One-Shot armed, move in flight |
| Setup CAN seq    | per HYB-OS-A-G4-02 |
| Stimulus         | Trip LIM_LFT, then quickly trip it again before reeler has fully stopped |
| Expected behaviour | Only one pulse |
| Pass criteria    | Exactly one camera pulse for the cycle; second edge has no effect (cycle already disarmed); mode auto-disabled before second edge processed |
| Notes            | Q4: auto-disable closes the door immediately |

### HYB-OS-EDGE-G6-03 - Edge during deceleration phase

| Field            | Value |
|------------------|-------|
| ID               | HYB-OS-EDGE-G6-03 |
| Title            | Edge that arrives while reeler is already in Stopped->hold transition |
| Pre-conditions   | HYB-OS-EDGE-G6-02 setup but trip LIM_LFT a second time during the TMC4671 Stopped->hold@2RPM->Position window |
| Setup CAN seq    | (continuing) |
| Stimulus         | Second LIM_LFT trip during decel |
| Expected behaviour | Ignored, hold sequence completes normally |
| Pass criteria    | No second camera pulse; TMC4671 watch shows clean hold sequence with no re-entry; `flags.is_hybrid_trig_enabled == 0` throughout the second trip |
| Notes            | Confirms auto-disable is instantaneous, not after-decel |

---

# G7 - Pause / Resume via REELER_MOTOR

### HYB-PR-REEL-G7-01 - AXC_PAUSE on REELER halts motion, preserves state

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-REEL-G7-01 |
| Title            | `peripheral=1, op=18` pauses reeler with state preserved |
| Pre-conditions   | Inspection running per HYB-INSP-G1-04, slip counter >= 1 |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=18, value=0` |
| Expected behaviour | Reeler stops via TMC4671 Stopped->hold@2RPM->Position (Q8); pause flag set; hybrid state preserved |
| Pass criteria    | `flags.is_paused == 1` (bit 11); reeler at hold; `hybrid.last_anchor_position` unchanged; `hybrid.next_trigger_position` unchanged; `hybrid.consecutive_failures` unchanged (Q16); no camera pulse; no `is_hybrid_trig_enabled` change |
| Notes            | Q7, Q8, Q10, Q16 all in one case |

### HYB-PR-REEL-G7-02 - LIM_LFT during pause is suppressed

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-REEL-G7-02 |
| Title            | Edges while paused do not fire the camera |
| Pre-conditions   | HYB-PR-REEL-G7-01 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | Trip LIM_LFT while paused |
| Expected behaviour | Edge ignored |
| Pass criteria    | No camera pulse; no anchor update; `flags.is_paused` remains 1 |
| Notes            | Q14 (pause suppresses edge handling) |

### HYB-PR-REEL-G7-03 - AXC_START resumes from paused state

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-REEL-G7-03 |
| Title            | `AXC_START` while paused performs resume, not fresh start |
| Pre-conditions   | HYB-PR-REEL-G7-02 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=1, value=0` |
| Expected behaviour | Reeler resumes at prior velocity; pause flag clears; hybrid pipeline continues from where it left off |
| Pass criteria    | `flags.is_paused == 0`; reeler back at prior commanded velocity; `hybrid.last_anchor_position` unchanged; subsequent triggers fire correctly per saved `next_trigger_position` |
| Notes            | Q9: state-aware AXC_START |

### HYB-PR-REEL-G7-04 - Pause during One-Shot armed cycle

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-REEL-G7-04 |
| Title            | Pausing an armed One-Shot cycle preserves the arm bit |
| Pre-conditions   | One-Shot armed (HYB-OS-A-G4-02 setup), reeler in flight |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=18, value=0` |
| Expected behaviour | Reeler stops, cycle remains armed, no camera pulse |
| Pass criteria    | `flags.is_paused == 1`; `hybrid.cycle_armed == 1`; `flags.is_hybrid_trig_enabled == 1`; reeler at hold |
| Notes            | Confirms One-Shot arming survives pause |

### HYB-PR-REEL-G7-05 - Resume completes One-Shot cycle

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-REEL-G7-05 |
| Title            | After resuming a paused armed cycle, LIM_LFT still fires camera and auto-disables |
| Pre-conditions   | HYB-PR-REEL-G7-04 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=1, value=0`, then trip LIM_LFT |
| Expected behaviour | Cycle completes normally |
| Pass criteria    | One camera pulse at edge; auto-disable per HYB-OS-A-G4-03; `flags.is_paused == 0` throughout |
| Notes            | End-to-end pause/resume on One-Shot |

---

# G8 - Pause / Resume via hybrid peripherals

### HYB-PR-HYB-G8-01 - AXC_PAUSE on Inspection peripheral

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-HYB-G8-01 |
| Title            | `peripheral=8, op=18` produces same pause as on REELER |
| Pre-conditions   | Inspection running per HYB-INSP-G1-04 |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=8, op=18, value=0` |
| Expected behaviour | Identical effect to HYB-PR-REEL-G7-01 |
| Pass criteria    | Same pass criteria as HYB-PR-REEL-G7-01 |
| Notes            | Q7: AXC_PAUSE accepted on all three peripherals (REELER, INSPECTION, ONE_SHOT) |

### HYB-PR-HYB-G8-02 - AXC_PAUSE on One-Shot peripheral

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-HYB-G8-02 |
| Title            | `peripheral=9, op=18` works identically |
| Pre-conditions   | One-Shot armed cycle in flight |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=9, op=18, value=0` |
| Expected behaviour | Identical effect to HYB-PR-REEL-G7-04 |
| Pass criteria    | Same pass criteria as HYB-PR-REEL-G7-04 |
| Notes            | Symmetry across the three peripherals |

### HYB-PR-HYB-G8-03 - AXC_START on hybrid peripheral resumes

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-HYB-G8-03 |
| Title            | `peripheral=8, op=1` resumes a paused inspection |
| Pre-conditions   | HYB-PR-HYB-G8-01 has passed |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=8, op=1, value=0` |
| Expected behaviour | Inspection resumes |
| Pass criteria    | Same pass criteria as HYB-PR-REEL-G7-03 |
| Notes            | Q9: AXC_START is state-aware on hybrid peripherals too |

### HYB-PR-HYB-G8-04 - Double pause is idempotent

| Field            | Value |
|------------------|-------|
| ID               | HYB-PR-HYB-G8-04 |
| Title            | Sending AXC_PAUSE while already paused has no ill effect |
| Pre-conditions   | Paused per HYB-PR-HYB-G8-01 |
| Setup CAN seq    | (continuing) |
| Stimulus         | Send `peripheral=1, op=18, value=0` again |
| Expected behaviour | No change |
| Pass criteria    | `flags.is_paused` remains 1; no TMC4671 re-transition; no error reply; all hybrid state still preserved |
| Notes            | Defensive idempotency |

---

# G9 - Stop interactions

### HYB-STOP-G9-01 - AXC_STOP clears pause and disables hybrid

| Field            | Value |
|------------------|-------|
| ID               | HYB-STOP-G9-01 |
| Title            | `AXC_STOP` is a hard reset path |
| Pre-conditions   | Paused inspection per HYB-PR-REEL-G7-01 |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=1, op=2, value=0` |
| Expected behaviour | Hard stop, all hybrid state cleared |
| Pass criteria    | `flags.is_paused == 0`; `flags.is_hybrid_trig_enabled == 0`; `hybrid.gc == GC_IDLE`; `hybrid.cycle_armed == 0`; `hybrid.consecutive_failures == 0`; reeler stopped |
| Notes            | Stop is the escape hatch from any state |

### HYB-STOP-G9-02 - AXC_STOP during One-Shot armed cycle

| Field            | Value |
|------------------|-------|
| ID               | HYB-STOP-G9-02 |
| Title            | Stop disarms cycle without firing camera |
| Pre-conditions   | One-Shot armed, in flight |
| Setup CAN seq    | per HYB-OS-A-G4-02 |
| Stimulus         | `peripheral=1, op=2, value=0` before LIM_LFT trips |
| Expected behaviour | Reeler stops, no camera pulse |
| Pass criteria    | `hybrid.cycle_armed == 0`; `flags.is_hybrid_trig_enabled == 0`; no camera pulse; reeler at rest |
| Notes            | Confirms stop wins over pending arm |

### HYB-STOP-G9-03 - AXC_DISABLE on hybrid peripheral

| Field            | Value |
|------------------|-------|
| ID               | HYB-STOP-G9-03 |
| Title            | `AXC_DISABLE` cleanly tears down hybrid without touching reeler |
| Pre-conditions   | Inspection running |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=8, op=4, value=0` |
| Expected behaviour | Hybrid disabled, reeler unaffected |
| Pass criteria    | `flags.is_hybrid_trig_enabled == 0`; `hybrid.gc == GC_IDLE`; reeler velocity unchanged; no camera pulse; LIM_LFT no longer drives anything |
| Notes            | Disable != Stop. Reeler keeps running. |

---

# G10 - Negative / robustness

### HYB-NEG-G10-01 - Enable hybrid without AXC_TEETH

| Field            | Value |
|------------------|-------|
| ID               | HYB-NEG-G10-01 |
| Title            | Enabling hybrid with `trig_step_size == 0` is rejected or yields safe default |
| Pre-conditions   | Cold boot, do NOT send `AXC_TEETH` |
| Setup CAN seq    | (none) |
| Stimulus         | `peripheral=8, op=3, value=0` |
| Expected behaviour | Either rejection (recommended) or safe-default behaviour per design doc section 5 |
| Pass criteria    | `flags.is_hybrid_trig_enabled` stays 0 OR enables but never produces a trigger because `trig_step_size == 0`; no crash; no division-by-zero log |
| Notes            | Defensive check; design doc must be unambiguous here |

### HYB-NEG-G10-02 - AXC_PAUSE on idle hybrid

| Field            | Value |
|------------------|-------|
| ID               | HYB-NEG-G10-02 |
| Title            | Pause when nothing is running |
| Pre-conditions   | Cold boot, hybrid disabled |
| Setup CAN seq    | (none) |
| Stimulus         | `peripheral=1, op=18, value=0` |
| Expected behaviour | Either rejection or no-op |
| Pass criteria    | No crash; `flags.is_paused` either stays 0 (rejection) or becomes 1 with no other side effects (no-op pause) per design doc; reeler unchanged |
| Notes            | Confirm chosen behaviour from design doc section 7 |

### HYB-NEG-G10-03 - Mode flip while running

| Field            | Value |
|------------------|-------|
| ID               | HYB-NEG-G10-03 |
| Title            | Sending One-Shot enable while Inspection is running |
| Pre-conditions   | Inspection running per HYB-INSP-G1-04 |
| Setup CAN seq    | (continuing) |
| Stimulus         | `peripheral=9, op=3, value=0` |
| Expected behaviour | Either rejection (preferred) or clean re-arming as One-Shot per design doc |
| Pass criteria    | Behaviour matches design doc section 11; no inconsistent state where both `is_one_shot` flips occur mid-trigger; no spurious camera pulse |
| Notes            | Avoid undefined intermediate states |

### HYB-NEG-G10-04 - CAN flood

| Field            | Value |
|------------------|-------|
| ID               | HYB-NEG-G10-04 |
| Title            | Bursty CAN traffic does not desynchronise hybrid pipeline |
| Pre-conditions   | Inspection running |
| Setup CAN seq    | (continuing) |
| Stimulus         | Inject 1000 unrelated frames per second on the bus for 10 s while reeler runs and LIM_LFT is tripped at the design rate |
| Expected behaviour | Trigger output remains accurate |
| Pass criteria    | Pulse spacing within design tolerance throughout the burst; `hybrid.consecutive_failures` not artificially incremented; no CAN error frames from the AxC; no missed LIM_LFT edges |
| Notes            | Smoke test for parser + ISR latency under load |

---

# Q1-Q21 coverage matrix

The 21 locked design decisions (Appendix A of the design doc, Appendix B of the implementation plan) map to the test cases above as follows. Every Q has at least one direct verification.

| Q   | Decision (short)                                                  | Covering tests |
|-----|-------------------------------------------------------------------|----------------|
| Q1  | `step_size` is integer mm via existing `AXC_TEETH`                | G0-02, G1-01, G3-01, G3-02 |
| Q2  | CONFIGURATOR -> ONE_SHOT rename, peripheral 8 = INSPECTION, 9 = ONE_SHOT | G1-01, G4-01, G8-01, G8-02 |
| Q3  | `AXC_PRESSED` reply only in Inspection, not One-Shot              | G1-02, G1-05, G4-03, G6-01 |
| Q4  | One-Shot auto-disables on edge                                    | G4-03, G5-02, G5-03, G6-02 |
| Q5  | One-Shot uses LIM_LFT only                                        | G4-03, G6-01, G6-02 |
| Q6  | Camera trigger pulse is single per fire event                     | G1-03, G4-03, G6-02 |
| Q7  | `AXC_PAUSE = 18`, accepted on REELER + both hybrid peripherals    | G7-01, G8-01, G8-02 |
| Q8  | TMC4671 pause: Stopped -> hold@2RPM -> Position                   | G7-01, G6-03, G7-04 |
| Q9  | `AXC_START` is state-aware (resume vs fresh start)                | G7-03, G7-05, G8-03 |
| Q10 | `flags.is_paused` is bit 11                                       | G7-01, G7-03, G8-04, G9-01 |
| Q11 | Pause preserves `last_anchor_position` and `next_trigger_position`| G7-01, G7-03 |
| Q12 | Pause preserves One-Shot `cycle_armed`                            | G7-04, G7-05 |
| Q13 | RHD suppression on One-Shot fire                                  | G4-03, G5-02 |
| Q14 | Edges suppressed during pause                                     | G7-02 |
| Q15 | `hybrid.gc` cleanly returns to running on resume                  | G7-03, G8-03 |
| Q16 | `consecutive_failures` preserved across pause                     | G2-04, G7-01 |
| Q17 | Slip CAN alert deferred (placeholder counter behaviour)           | G2-01, G2-02, G2-03 |
| Q18 | LIM_LFT is the only sensor used                                   | G1-02, G1-05, G6-01 |
| Q19 | Older design doc kept untouched                                   | (doc-level, no FW test) |
| Q20 | Auto-disable is immediate, not after decel                        | G6-02, G6-03 |
| Q21 | Stop is the universal escape hatch                                | G9-01, G9-02 |

Q19 is a documentation-management decision and has no firmware behaviour to verify; it is listed for completeness.

---

# Execution log template

When running these cases on the bench, capture the following per case:

- Date / time, firmware git SHA, tester
- CAN trace file
- Watch dump (JSON or CSV) before stimulus and after expected behaviour settles
- Scope screenshot of camera trigger line
- Pass / fail verdict with timestamp
- Notes / deviations

Template entry:

```
Case: HYB-INSP-G1-03
Date: 2026-MM-DD HH:MM
SHA:  <git rev-parse --short HEAD>
Tester: <name>
Result: PASS | FAIL
CAN trace: traces/<case-id>.asc
Watch: watches/<case-id>.json
Scope: scope/<case-id>.png
Notes: <free text>
```

Aggregate per-group pass rate before declaring Phase 8 verified.

---

# Sign-off

Phase 8 is considered firmware-verified when:

1. All 41 cases above pass on the bench.
2. The Q1-Q21 coverage matrix shows no row with all-failing tests.
3. Pulse-spacing accuracy meets the encoder-tolerance bound stated in the design doc section 9.
4. No watchdog resets, no stack overflows, no CAN error counters non-zero during any case.

Sign-off block:

| Role            | Name | Date | Signature |
|-----------------|------|------|-----------|
| FW Engineer     |      |      |           |
| Test Engineer   |      |      |           |
| Project Lead    |      |      |           |

---

End of document.
