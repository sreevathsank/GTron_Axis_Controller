# Ejection & Tracking — Firmware Test Cases

Status: Draft v1.0
Scope: Firmware-side bench verification of the Ejection & Tracking module on the GTron
AxC (ATSAMC21N18A). Covers trigger snapshots (1-based), reset-via-part-count-zero,
part-count pairing, eject/pause target computation, stale/unpaired/overflow handling,
wrap behaviour, and lifecycle flush.

Companion documents:
- `Ejection_And_Tracking/workflow.md` (design)
- `Ejection_And_Tracking/code.md` (implementation)

Executed by a firmware engineer with a CAN traffic generator (Kvaser/PCAN/TMCL-IDE bridge)
and an in-circuit debugger. Symbols referenced are defined in `code.md` and
`IMM_CAN_Message_Id.h`.

---

## Conventions

### CAN frame shorthand

A frame is written as `peripheral=<P>, op=<O>, value=<V>`, where `P`, `O` come from
`AxC_Peripherals_t` / `AxC_Operations_t`, and `V` is the 32-bit signed payload.

Peripheral IDs used here:

| Name        | ID |
|-------------|----|
| `EJECTOR_1` | 15 |
| `EJECTOR_2` | 16 |

Operation IDs used here:

| Name                    | Op | Notes                                          |
|-------------------------|----|------------------------------------------------|
| `AXC_TRIG_STEPSIZE`     | 12 | distance: camera FOV centre -> ejector         |
| `AXC_PAUSE`             | 21 | action = PAUSE                                 |
| `AXC_EJECT_BIN_OFFSET`  | 27 | action = EJECT, payload = offset               |
| `AXC_EJECT_PARTCOUNT`   | 28 | value==0 -> reset; value!=0 -> part count      |
| `AXC_EJECT_PART`        | 29 | AxC -> SysCtrl eject actuation (outbound)      |

Error reply IDs: `AXC_ERR_EJECT_STALE`(3), `AXC_ERR_EJECT_UNPAIRED`(4),
`AXC_ERR_EJECT_OVERFLOW`(5), sent on `CAN_ERR_REPLY_TOP_RACK_ID`(0x402).

---

## Test equipment & setup

1. AxC board, debugger on `g_cam_count`, `g_trig_ring`, `g_ejectors[]`,
   `g_pending_valid`, `g_pending_part_no`, `g_pending_ejector_id`.
2. CAN traffic generator to inject frames and observe replies.
3. A way to drive `PID_POSITION_ACTUAL` (rotate the reeler or use the TMC4671 directly).

For determinism, before each test send `AXC_EJECT_PARTCOUNT` with `value=0` (or call
`ejection_init()`) to establish a known `g_cam_count == 0`.

---

## 1. Lifecycle & configuration

### TC-1.1 — Init zeroes everything
| | |
|---|---|
| Stimulus | Power on / `ejection_init()` |
| Expected | `g_cam_count==0`; every ejector `head==tail`, `distance==0`, `fired==0`, `stale==0`, `overflows==0`; `g_pending_valid==false` |

### TC-1.2 — Distance stored per ejector
| | |
|---|---|
| Stimulus | `peripheral=EJECTOR_1, op=AXC_TRIG_STEPSIZE, value=100000`; then `EJECTOR_2 … value=200000` |
| Expected | `g_ejectors[0].distance==100000`, `g_ejectors[1].distance==200000` |

### TC-1.3 — Bad ejector id rejected
| | |
|---|---|
| Stimulus | Directly call `ejection_set_distance(2, 5)` via debugger |
| Expected | `FAULT_BAD_EJECTOR_ID` logged; no state mutation |

### TC-1.4 — Reset via PARTCOUNT==0 clears count and queues
| | |
|---|---|
| Setup | Seed `g_cam_count=12345`, enqueue a pending target, latch a part count |
| Stimulus | `peripheral=EJECTOR_1, op=AXC_EJECT_PARTCOUNT, value=0` |
| Expected | `g_cam_count==0`; all queues empty; `g_pending_valid==false` |

### TC-1.5 — Reset does not clear distances
| | |
|---|---|
| Setup | `AXC_TRIG_STEPSIZE` sets `distance[0]=100000` |
| Stimulus | `AXC_EJECT_PARTCOUNT, value=0` |
| Expected | `g_ejectors[0].distance==100000` (persists); only runtime state reset |

### TC-1.6 — Reset via either ejector resets shared counter
| | |
|---|---|
| Setup | Seed `g_cam_count=100` |
| Stimulus | `EJECTOR_2, AXC_EJECT_PARTCOUNT, value=0` |
| Expected | `g_cam_count==0` (shared counter, regardless of which ejector carried it) |

---

## 2. Trigger snapshot (1-based)

### TC-2.1 — First trigger is part 1
| | |
|---|---|
| Stimulus | With motor at position P, fire one camera trigger (`trigger_Camera_Line`) |
| Expected | `g_cam_count==1`; `g_trig_ring[1].pos==P`, `g_trig_ring[1].count==1` |

### TC-2.2 — Consecutive triggers land in consecutive slots
| | |
|---|---|
| Stimulus | Fire 3 triggers at positions P1, P2, P3 |
| Expected | `ring[1].pos==P1, ring[2].pos==P2, ring[3].pos==P3`; counts 1,2,3; `g_cam_count==3` |

### TC-2.3 — Ring wraps at 256
| | |
|---|---|
| Stimulus | Fire 257 triggers |
| Expected | `ring[1].count==257` (overwritten); `ring[1].pos` == position of trigger #257; `g_cam_count==257`; no fault |

### TC-2.4 — Reset mid-run re-anchors to part 1
| | |
|---|---|
| Stimulus | Fire 3 triggers (count now 3); `AXC_EJECT_PARTCOUNT, value=0`; fire 1 more trigger at position Q |
| Expected | `g_cam_count==1`; the new trigger lands at `ring[1]` with `count==1` |

---

## 3. Part-count pairing

### TC-3.1 — Action without part count -> unpaired fault
| | |
|---|---|
| Stimulus | `peripheral=EJECTOR_1, op=AXC_EJECT_BIN_OFFSET, value=50` (no preceding part count) |
| Expected | `FAULT_UNPAIRED_ACTION`; `AXC_ERR_EJECT_UNPAIRED` reply on 0x402; nothing enqueued |

### TC-3.2 — Part count then action on same ejector -> enqueued
| | |
|---|---|
| Stimulus | `EJECTOR_1, op=AXC_EJECT_PARTCOUNT, value=7` then `EJECTOR_1, op=AXC_EJECT_BIN_OFFSET, value=50` |
| Expected | `g_pending_valid` consumed; target `= ring[7].pos + distance[0] + 50` enqueued in `g_ejectors[0]` with `part_no[tail]==7` |

### TC-3.3 — Part count on ejector 1, action on ejector 2 -> mismatch fault
| | |
|---|---|
| Stimulus | `EJECTOR_1, AXC_EJECT_PARTCOUNT, value=7`; then `EJECTOR_2, AXC_EJECT_BIN_OFFSET, value=50` |
| Expected | `FAULT_UNPAIRED_ACTION`; nothing enqueued; latch not consumed |

### TC-3.4 — Two part-count frames, one action -> latest wins
| | |
|---|---|
| Stimulus | `PARTCOUNT=5`, `PARTCOUNT=9`, then `EJECTOR_1, EJECT_BIN_OFFSET=50` |
| Expected | Action uses part_no 9 (latest latch); target based on `ring[9]` |

---

## 4. Stale handling

### TC-4.1 — Part overwritten (>256 triggers late)
| | |
|---|---|
| Setup | Note part_no=N, then fire >256 triggers so slot `N & 0xFF` is overwritten |
| Stimulus | `PARTCOUNT=N` then `EJECT_BIN_OFFSET` |
| Expected | `FAULT_STALE_PART`; `AXC_ERR_EJECT_STALE` reply; `stale` not incremented (no enqueue attempted) |

### TC-4.2 — Part already passed the ejector
| | |
|---|---|
| Setup | With motor at position P and a fresh part count for the current trigger, set `distance[0]` small so `target < P` |
| Stimulus | `PARTCOUNT` then `EJECT_BIN_OFFSET` |
| Expected | `FAULT_STALE_PART`; `AXC_ERR_EJECT_STALE` reply; `g_ejectors[0].stale` incremented |

### TC-4.3 — Count wrap does not alias (part 70000 vs part 4464)
| | |
|---|---|
| Setup | Simulate: seed `ring[112].count=70000`, `ring[112].pos=X` |
| Stimulus | `PARTCOUNT=4464` (same `&0xFF == 112`) then action |
| Expected | `ring[112].count(70000) != 4464` -> `FAULT_STALE_PART` (no false match) |

---

## 5. Target computation & service

### TC-5.1 — Eject fires at exact position (DIM), echoing part count
| | |
|---|---|
| Setup | `distance[0]=100000`; trigger at P (part 1); `PARTCOUNT=1`; `EJECT_BIN_OFFSET=0` |
| Expected | target `= P + 100000`; drive motor past it; one `AXC_EJECT_PART` frame on 0x110 with `peripheral=EJECTOR_1`, `value=1` (part count); `fired==1` |

### TC-5.2 — Offset shifts target (negative offset = earlier)
| | |
|---|---|
| Setup | trigger at P; `EJECT_BIN_OFFSET=-500` |
| Expected | target `= P + distance[0] - 500`; fires 500 usteps earlier than TC-5.1 |

### TC-5.3 — Pause action stops reeler (TIM)
| | |
|---|---|
| Setup | `distance[0]=cut_distance`; trigger at P; `PARTCOUNT` then `AXC_PAUSE, value=0` |
| Expected | target `= P + cut_distance`; on reaching it, `reeler_Pause_Motor()` called (motor stops, `is_paused==true`); no `AXC_EJECT_PART` frame |

### TC-5.4 — Multiple pending targets drain in order
| | |
|---|---|
| Setup | Enqueue targets T1 < T2 < T3 in one ejector |
| Stimulus | Drive motor past T1 then T2 then T3 |
| Expected | three actions fire in order; queue empties; `fired==3` |

### TC-5.5 — Per-ejector independence (near bin not blocked by far bin)
| | |
|---|---|
| Setup | EJECTOR_1 target far, EJECTOR_2 target near (triggered later but reaches earlier) |
| Expected | EJECTOR_2 fires before EJECTOR_1; neither queue blocks the other |

---

## 6. Overflow

### TC-6.1 — Queue overflow when 256 targets pending
| | |
|---|---|
| Setup | Enqueue 256 targets without servicing (keep motor parked) |
| Stimulus | Enqueue a 257th valid target |
| Expected | `FAULT_QUEUE_OVERFLOW`; `AXC_ERR_EJECT_OVERFLOW` reply; `overflows==1` |

---

## 7. Lifecycle flush

### TC-7.1 — Motor stop flushes pending targets
| | |
|---|---|
| Setup | Enqueue a pending target |
| Stimulus | `reeler_Stop_Motor()` (with flush wired) |
| Expected | all queues empty |

### TC-7.2 — Reset (PARTCOUNT==0) flushes + zeroes count
| | |
|---|---|
| Stimulus | `AXC_EJECT_PARTCOUNT, value=0` after seeding state |
| Expected | `g_cam_count==0`, queues empty, latch cleared (same as TC-1.4) |

---

## 8. Negative / robustness

### TC-8.1 — Eject with distance never configured
| | |
|---|---|
| Setup | `distance[0]==0` (fresh init), valid part count + action |
| Expected | target `= ring[].pos + 0 + offset`; fires almost immediately (this is the A4 gap — confirm whether to reject unconfigured ejectors) |

### TC-8.2 — Rapid command burst does not lose targets
| | |
|---|---|
| Stimulus | Send 50 valid `[part_count -> action]` pairs back-to-back |
| Expected | 50 targets enqueued; no unpaired faults; no overflow |

### TC-8.3 — Action frame immediately after reset (no part count yet)
| | |
|---|---|
| Stimulus | `AXC_EJECT_PARTCOUNT, value=0` then `EJECT_BIN_OFFSET` with no `PARTCOUNT` |
| Expected | `FAULT_UNPAIRED_ACTION`; nothing enqueued |
