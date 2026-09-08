# Ejection & Tracking — Workflow

## 1. Overview

The AxC (Axis Controller) pulls a strip/disc of parts past a camera and one or more
ejection points. For every part that passes the camera:

1. AxC fires the camera trigger line and **snapshots the motor position** at that instant.
2. The image goes to SW (via SysCtrl), which inspects it and decides the part's fate.
3. SW sends back **which part** (its part count) and **how much offset** to eject/pause.
4. AxC reconstructs the absolute target position from the stored snapshot + ejector
   distance + offset, then fires the action when the motor reaches that position.

The key insight: **the motor keeps moving while SW processes the image**, so the target
position cannot be computed from the "current" position when the command arrives. AxC
must store the position *at camera-trigger time* and add the SW-supplied data later.

---

## 2. Two machine types, one binary

| | DIM (Discrete Inspection) | TIM (Terminal Inspection) |
|---|---|---|
| Carrier | transparent rotating disc | continuous terminal strip |
| Parts in flight | up to ~165 | one terminal at a time |
| Command coverage | **every** part (sorted into 2 bins) | **fail parts only** (pass = nothing) |
| Ejection action | pneumatic (air jet) via SysCtrl | cut + weld (operator) |
| AxC action on command | send CAN eject frame to SysCtrl | stop the reeler (`PAUSE`) |

Because TIM sends commands for *only* failed parts, the correlation cannot be FIFO.
Instead SW sends the **part count**, and AxC indexes its snapshot ring directly by
`part_no`. This works for both dense (DIM) and sparse (TIM) command traffic.

---

## 3. The two data structures

### 3.1 Trigger ring (producer: main loop, consumer: CAN RX)

```c
TrigEntry_t g_trig_ring[256];   // { int32 pos; uint32 count; }
volatile uint32_t g_cam_count;  // AxC's own camera-trigger count
```

- Written every camera trigger inside `trigger_Camera_Line()`.
- Index is `count & 0xFF`. The full `count` is stored as a **tag** to detect overwrites
  and u32 wraparound (part counts can reach 80,000, well past any 16-bit counter).

### 3.2 Per-ejector target queue (producer: CAN RX, consumer: main loop)

```c
Ejector_Queue_t g_ejectors[2];  // { target_gc[256], action[256], part_no[256], head, tail, distance, ... }
```

- Each ejector has its own 256-deep ring of pending `{target, action, part_no}`.
- `action` is either `EJECT` (send CAN to SysCtrl) or `PAUSE` (stop the reeler).
- `part_no` is remembered so the outbound eject frame can echo which part is being
  ejected.
- TIM uses `EJECTOR_1` as its single "cut point" ejector, with `PAUSE` actions only.
- Per-ejector queues (not one merged queue) so parts to a near bin never block behind
  parts to a far bin.

---

## 4. Wire protocol

CAN data field is 6 bytes: `data[0] = peripheral`, `data[1] = operation`,
`data[2..5] = value` (big-endian int32).

### 4.1 Configuration (MI → AxC), once at launch

| peripheral | operation | value |
|---|---|---|
| `EJECTOR_1` (15) | `AXC_TRIG_STEPSIZE` (12) | camera-FOV-centre → ejector-1 / cut point distance (int32) |
| `EJECTOR_2` (16) | `AXC_TRIG_STEPSIZE` (12) | camera-FOV-centre → ejector-2 distance (int32) |

Ejector distances **persist** across resets — they are re-sent only when the machine
geometry changes.

### 4.2 Reset (MI → SysCtrl + AxC), at inspection start

`AXC_EJECT_PARTCOUNT` (28) with `value == 0`. AxC resets its runtime tracking state:
flushes the trigger-ring count, all queues, and the pending-part-count latch, setting
`g_cam_count = 0` so the next trigger is part 1. Ejector distances are **not** reset.

`value != 0` is the normal part count (see 4.3). Since SW's first part is **1** (not 0),
the value 0 is reserved as the reset sentinel and never collides with a real part.

SW sends this to **both SysCtrl and AxC** at the same instant so all counters agree.

### 4.3 Command pair (MI → SysCtrl + AxC), per part — strictly ordered

SW sends `{part count, ejector id, offset}` as one serial opcode to SysCtrl. SysCtrl
parses it and relays **two** CAN frames to AxC, always in this order (SysCtrl also keeps
whatever it needs for its own LCS bookkeeping):

| frame | peripheral | operation | value |
|---|---|---|---|
| 1 (part count) | `EJECTOR_n` | `AXC_EJECT_PARTCOUNT` (28) | `part_no` (uint32, > 0) |
| 2 (action) | `EJECTOR_n` | `AXC_EJECT_BIN_OFFSET` (27) or `AXC_PAUSE` (21) | `offset` (int32, signed) |

AxC latches `part_no` (and its ejector id) from frame 1, then consumes it on frame 2.
If frame 2 arrives with no latched part count, AxC reports an error to SysCtrl.

### 4.4 Eject actuation (AxC → SysCtrl), at the target position

| ID | peripheral | operation | value |
|---|---|---|---|
| `CAN_TOP_AXC_TO_SYSCTRL_ID` (0x110) | `EJECTOR_n` | `AXC_EJECT_PART` (29) | `part_no` (uint32) |

The bin id is in `data[0]`, the part count in `data[2..5]` — SysCtrl knows which valve to
fire and which part it belongs to.

---

## 5. Step-by-step flow

### 5.1 Camera trigger (main loop, `trigger_Camera_Line`)

Count is **1-based** — the first trigger after reset is part 1, matching SW:

```
g_cam_count = g_cam_count + 1                     // 1, 2, 3, ...
idx = g_cam_count & 0xFF
g_trig_ring[idx].pos   = tmc4671_getActualPosition(MOTOR)   // snapshot
g_trig_ring[idx].count = g_cam_count                        // tag
```

### 5.2 Reset (CAN RX, `AXC_EJECT_PARTCOUNT == 0`)

```
flush_all queues + pending latch
g_cam_count = 0        // next trigger -> part 1
```

### 5.3 Command received (CAN RX, `ejection_enqueue`)

```
if ejector_id >= 2            -> FAULT_BAD_EJECTOR_ID
if !g_pending_valid           -> FAULT_UNPAIRED_ACTION, error to SysCtrl
if ejector_id != pending_id   -> mismatch, error
part_no = g_pending_part_no;  clear pending
e = &g_trig_ring[part_no & 0xFF]
if e->count != part_no        -> FAULT_STALE_PART (overwritten), error to SW
target = e->pos + distance[ejector] + offset
if target <= current_position -> FAULT_STALE_PART (already passed), error to SW
enqueue {target, action, part_no}; if full -> FAULT_QUEUE_OVERFLOW
```

### 5.4 Service (main loop, `ejection_service`, already at Motion.c:1471)

```
for each ejector:
    while !empty && current_position >= target_gc[head]:
        if action == EJECT -> ejection_send_ejection_cmd(id, part_no[head])
        if action == PAUSE -> reeler_Pause_Motor()
        head++
```

---

## 6. Edge cases & error handling

| case | detection | response |
|---|---|---|
| **Stale: part overwritten** (`count != part_no`, >256 triggers late) | tag mismatch | `FAULT_STALE_PART` → `AXC_ERR_EJECT_STALE` to SW |
| **Stale: part already passed** (target <= current) | position check | `FAULT_STALE_PART` → `AXC_ERR_EJECT_STALE` to SW |
| **Unpaired action** (frame 2 without frame 1) | `!g_pending_valid` | `FAULT_UNPAIRED_ACTION` → `AXC_ERR_EJECT_UNPAIRED` to SysCtrl |
| **Queue overflow** (>256 pending targets) | head/tail collision | `FAULT_QUEUE_OVERFLOW` → `AXC_ERR_EJECT_OVERFLOW` |
| **Bad ejector id** | `id >= 2` | `FAULT_BAD_EJECTOR_ID` (local bug, log) |
| **Count wrap** (part count > 65535) | full `uint32` tag | no aliasing; tag compare is exact |
| **Reset mid-run** | `AXC_EJECT_PARTCOUNT == 0` | `ejection_reset()` (runtime state only) |
| **Homing / motor stop mid-run** | — | `ejection_flush_all()` + reset on stop/homing |
| **Trigger ring overflow** (>256 triggers without command) | overwritten slot | caught as stale on later lookup |

---

## 7. Synchronization contract (cross-firmware)

1. **Same event counted** — both AxC and SysCtrl count the `REELER_INT` camera-trigger
   pulse (hardware), so spurious/missed *image* events do NOT cause count drift.
2. **1-based count** — SW's first part is 1; AxC's `g_cam_count` is 1-based too, so the
   two sequences match exactly (no offset).
3. **Same reset** — SW sends `AXC_EJECT_PARTCOUNT = 0` to both SysCtrl and AxC at
   inspection start; both clear their counters and the next trigger is part 1.
4. **Strict frame ordering** — SysCtrl guarantees `[part count] → [id + offset]`; any
   violation is reported back by AxC.

---

## 8. Confirmed with SysCtrl dev / product

- [x] Part count is 32-bit (max ~80,000).
- [x] First part for SW is 1, not 0.
- [x] `AXC_EJECT_PARTCOUNT = 0` resets runtime tracking state (distances persist).
- [x] `AXC_EJECT_PART` (29) is the AxC → SysCtrl eject frame (bin id + part count).
- [x] `AXC_EJECT_PARTCOUNT` (28) / `AXC_EJECT_BIN_OFFSET` (27) / `AXC_PAUSE` (21) are all
      MI-originated, relayed by SysCtrl to AxC.
