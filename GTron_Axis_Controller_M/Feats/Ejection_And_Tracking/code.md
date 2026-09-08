# Ejection & Tracking — Code to Add

Every change below is written against the current codebase. Each section states the
**file**, the **exact location**, and the **full code** to insert/replace.

Files touched:
1. `Bring_Up/CAN/IMM_CAN_Message_Id.h` — error codes (opcodes already added)
2. `Bring_Up/Motion/ejection.h` — full rewrite
3. `Bring_Up/Motion/ejection.c` — full rewrite
4. `Bring_Up/Motion/Hybrid_Trigger.c` — snapshot in `trigger_Camera_Line`
5. `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.c` — fill `EJECTOR_1`/`EJECTOR_2`
6. `Bring_Up/DBG_bring_up.c` — call `ejection_init()`

> **Opcode status:** the operation codes are already in `IMM_CAN_Message_Id.h`:
> `AXC_EJECT_BIN_OFFSET`(27), `AXC_EJECT_PARTCOUNT`(28), `AXC_EJECT_PART`(29).
> Only the **error codes** remain to be added.
>
> **Reset:** there is no dedicated reset opcode. `AXC_EJECT_PARTCOUNT` with `value == 0`
> resets runtime tracking state; `value != 0` is the normal part count.

---

## File 1: `Bring_Up/CAN/IMM_CAN_Message_Id.h`

### 1a. Add error codes

Location: inside `AxC_Errors_t`, after `AXC_ERR_TRIGGER_FAIL = 2` and before
`NO_OF_AXC_ERR`.

```c
typedef enum {
	AXC_ERR_NONE			= 0,
	AXC_ERR_SLIP			= 1,
	AXC_ERR_TRIGGER_FAIL	= 2,
	AXC_ERR_EJECT_STALE		= 3,		// Eject/pause command too late (part overwritten or already passed).
	AXC_ERR_EJECT_UNPAIRED	= 4,		// Action frame received without a preceding part-count frame.
	AXC_ERR_EJECT_OVERFLOW	= 5,		// Ejector target queue full.
	NO_OF_AXC_ERR
}AxC_Errors_t;
```

---

## File 2: `Bring_Up/Motion/ejection.h` — replace entire file

```c
/*
 * ejection.h
 *
 *  Author: sreevathsank
 */

/**
 * \file
 *
 * \brief	Ejection & tracking module: per-ejector target queues, fed by a trigger
 * 			position snapshot ring indexed by part count.
 *
 * AxC snapshots PID_POSITION_ACTUAL at every camera trigger. SW inspects the image and
 * later sends back the part count + offset + action. AxC reconstructs the absolute
 * target position (snapshot + ejector distance + offset) and fires the action when the
 * motor reaches it.
 *
 * The camera-trigger count is 1-based to match SW (first part = 1). A part count of 0
 * resets the runtime tracking state.
 */

#ifndef EJECTION_H_
#define EJECTION_H_

#include "All_Headers.h"

/** \brief	Number of ejector bins (TIM treats EJECTOR_1 as its single cut point). */
#define NUM_EJECTORS        2u

/** \brief	Depth of the trigger snapshot ring (must be power of two). */
#define TRIG_RING_DEPTH     256u
#define TRIG_RING_MASK      (TRIG_RING_DEPTH - 1u)

/** \brief	Depth of each per-ejector pending-target queue (must be power of two). */
#define QUEUE_DEPTH         256u
#define QUEUE_MASK          (QUEUE_DEPTH - 1u)

#if ((TRIG_RING_DEPTH & TRIG_RING_MASK) != 0u) || ((QUEUE_DEPTH & QUEUE_MASK) != 0u)
#error "Ejection ring/queue depths must be non-zero powers of two"
#endif

/**
 * \brief	Fault codes raised by the ejection module.
 */
typedef enum {
	FAULT_NONE             = 0,	/**< No fault. */
	FAULT_BAD_EJECTOR_ID   = 1,	/**< Command for an out-of-range ejector id. */
	FAULT_QUEUE_OVERFLOW   = 2,	/**< Target queue full. */
	FAULT_STALE_PART       = 3,	/**< Part already passed its ejector, or ring slot overwritten. */
	FAULT_UNPAIRED_ACTION  = 4	/**< Action frame without a preceding part-count frame. */
} ejection_fault_code_t;

/**
 * \brief	Action to perform when a target position is reached.
 */
typedef enum {
	EJECT_ACTION_EJECT = 0,	/**< Send CAN eject frame to SysCtrl (DIM pneumatic). */
	EJECT_ACTION_PAUSE = 1	/**< Stop the reeler (TIM cut & weld). */
} eject_action_t;

/**
 * \brief	One trigger-snapshot entry.
 */
typedef struct {
	int32_t  pos;		/**< PID_POSITION_ACTUAL at the camera-trigger instant. */
	uint32_t count;		/**< Full camera-trigger count at snapshot time (wrap-safe tag). */
} TrigEntry_t;

/**
 * \brief	Per-ejector ring of pending ejection targets.
 *
 * Single-producer (CAN RX), single-consumer (main loop). head == tail means empty.
 */
typedef struct {
	int32_t            target_gc[QUEUE_DEPTH];	/**< Absolute PID_POSITION_ACTUAL at which to act. */
	uint8_t            action[QUEUE_DEPTH];	/**< EJECT_ACTION_EJECT or EJECT_ACTION_PAUSE per entry. */
	uint32_t           part_no[QUEUE_DEPTH];	/**< Part count echoed back in the eject frame. */
	volatile uint16_t  head;					/**< Oldest pending target (consumer reads). */
	volatile uint16_t  tail;					/**< Next free slot (producer writes). */
	int32_t            distance;				/**< Camera FOV centre -> this ejector/cut point (usteps). */
	uint32_t           fired;					/**< Telemetry: actions performed. */
	uint32_t           stale;					/**< Telemetry: rejected late commands. */
	uint32_t           overflows;				/**< Telemetry: rejected full-queue enqueues. */
} Ejector_Queue_t;

/**
 * \brief	Initialises the trigger ring, queues, counters and pending latch.
 */
void ejection_init(void);

/**
 * \brief	Flushes all target queues and clears the pending part-count latch.
 */
void ejection_flush_all(void);

/**
 * \brief	Resets runtime tracking state: flushes queues/latch, zeroes the count.
 *
 * Ejector distances are NOT reset. Handles AXC_EJECT_PARTCOUNT == 0.
 */
void ejection_reset(void);

/**
 * \brief	Stores the distance of a given ejector/cut point.
 *
 * @param[in]	ejector_id	0 ... NUM_EJECTORS - 1.
 * @param[in]	distance	Camera FOV centre -> ejector (usteps).
 */
void ejection_set_distance(uint8_t ejector_id, int32_t distance);

/**
 * \brief	Latches the part count (and its ejector id) received in a part-count frame.
 *
 * A part_no of 0 resets the runtime tracking state instead of latching.
 *
 * @param[in]	ejector_id	Ejector id the count is paired with (cross-checked later).
 * @param[in]	part_no		Camera-trigger count of the part (>= 1; 0 = reset).
 */
void ejection_set_part_no(uint8_t ejector_id, uint32_t part_no);

/**
 * \brief	Computes and enqueues a target from the stored snapshot + distance + offset.
 *
 * Called from CAN RX on the action frame. Consumes the latched part count.
 *
 * @param[in]	ejector_id	0 ... NUM_EJECTORS - 1.
 * @param[in]	offset		Part position within the FOV, relative to centre (usteps, signed).
 * @param[in]	action		EJECT_ACTION_EJECT or EJECT_ACTION_PAUSE.
 */
void ejection_enqueue(uint8_t ejector_id, int32_t offset, eject_action_t action);

/**
 * \brief	Drains reached targets and fires their actions. Call from the main loop.
 *
 * @param[in]	current_gc	Current PID_POSITION_ACTUAL.
 */
void ejection_service(int32_t current_gc);

/**
 * \brief	Snapshots the current position into the trigger ring and bumps the count.
 *
 * Called from trigger_Camera_Line() at the camera-trigger instant. Count is 1-based.
 *
 * @param[in]	pos	PID_POSITION_ACTUAL at trigger.
 */
void ejection_note_trigger(int32_t pos);

/**
 * \brief	Sends a CAN frame to SysCtrl to fire the given ejector for the given part.
 *
 * @param[in]	bin		Ejector index (0/1).
 * @param[in]	part_no	Part count of the part to eject.
 */
void ejection_send_ejection_cmd(uint8_t bin, uint32_t part_no);

/**
 * \brief	Raises a fault: logs it and, where relevant, sends a CAN error to SW/SysCtrl.
 *
 * @param[in]	code	Fault code.
 */
void fault_raise(ejection_fault_code_t code);

#endif /* EJECTION_H_ */
```

---

## File 3: `Bring_Up/Motion/ejection.c` — replace entire file

```c
/*
 * ejection.c
 *
 *  Author: sreevathsank
 */
#include "ejection.h"

/* --- Module state -------------------------------------------------------- */

TrigEntry_t         g_trig_ring[TRIG_RING_DEPTH];
Ejector_Queue_t     g_ejectors[NUM_EJECTORS];

volatile uint32_t   g_cam_count;          /* AxC's camera-trigger count (1-based). */

static volatile uint32_t g_pending_part_no;   /* Latched from the part-count frame. */
static volatile uint8_t  g_pending_ejector_id;/* Ejector id paired with the latched count. */
static volatile bool     g_pending_valid;     /* true once a part-count frame is latched. */

/* --- Helpers -------------------------------------------------------------- */

static inline bool q_is_empty(const Ejector_Queue_t *q)
{
	return q->head == q->tail;
}

static inline uint16_t q_next(uint16_t i)
{
	return (uint16_t)((i + 1u) & QUEUE_MASK);
}

/* Wrap-safe "reached" check: true when current_gc has passed or reached target_gc. */
static inline bool gc_reached(int32_t current_gc, int32_t target_gc)
{
	return (int32_t)((uint32_t)current_gc - (uint32_t)target_gc) >= 0;
}

/* Map an ejector index (0/1) to its CAN peripheral byte (EJECTOR_1 / EJECTOR_2). */
static inline uint8_t ejector_peripheral(uint8_t id)
{
	return (id == 0u) ? (uint8_t)EJECTOR_1 : (uint8_t)EJECTOR_2;
}

/* --- Lifecycle ------------------------------------------------------------- */

void ejection_init(void)
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head       = 0u;
		g_ejectors[e].tail       = 0u;
		g_ejectors[e].distance   = 0;
		g_ejectors[e].fired      = 0u;
		g_ejectors[e].stale      = 0u;
		g_ejectors[e].overflows  = 0u;
	}
	g_cam_count          = 0u;
	g_pending_part_no    = 0u;
	g_pending_ejector_id = 0u;
	g_pending_valid      = false;
}

void ejection_flush_all(void)
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head = g_ejectors[e].tail;
	}
	g_pending_part_no    = 0u;
	g_pending_ejector_id = 0u;
	g_pending_valid      = false;
}

void ejection_reset(void)
{
	ejection_flush_all();
	g_cam_count = 0u;   /* next trigger becomes part 1 */
}

/* --- Configuration ---------------------------------------------------------- */

void ejection_set_distance(uint8_t ejector_id, int32_t distance)
{
	if (ejector_id >= NUM_EJECTORS) {
		fault_raise(FAULT_BAD_EJECTOR_ID);
		return;
	}
	g_ejectors[ejector_id].distance = distance;
}

/* --- Trigger snapshot (producer: main loop) -------------------------------- */

void ejection_note_trigger(int32_t pos)
{
	uint32_t c   = g_cam_count + 1u;   /* 1-based: first trigger -> 1 */
	uint32_t idx = c & TRIG_RING_MASK;

	g_trig_ring[idx].pos   = pos;   /* Write data first... */
	g_trig_ring[idx].count = c;     /* ...then the tag.   */
	__asm__ volatile("" ::: "memory"); /* Compiler barrier. */
	g_cam_count = c;                /* Publish the new count last. */
}

/* --- Part-count latch (producer: CAN RX) ------------------------------------ */

void ejection_set_part_no(uint8_t ejector_id, uint32_t part_no)
{
	if (part_no == 0u) {
		/* Reserved sentinel: reset runtime tracking state. */
		ejection_reset();
		return;
	}

	g_pending_part_no    = part_no;
	g_pending_ejector_id = ejector_id;
	g_pending_valid      = true;
}

/* --- Enqueue (consumer of latch, producer of target queue; CAN RX) ---------- */

void ejection_enqueue(uint8_t ejector_id, int32_t offset, eject_action_t action)
{
	if (ejector_id >= NUM_EJECTORS) {
		fault_raise(FAULT_BAD_EJECTOR_ID);
		return;
	}

	/* An action frame must be preceded by a part-count frame. */
	if (!g_pending_valid) {
		fault_raise(FAULT_UNPAIRED_ACTION);
		return;
	}

	/* Cross-check that the latched count belongs to the same ejector. */
	if (ejector_id != g_pending_ejector_id) {
		fault_raise(FAULT_UNPAIRED_ACTION);
		return;
	}

	uint32_t part_no = g_pending_part_no;
	g_pending_valid  = false;   /* Consume the latch. */

	/* Look up the snapshot; the full-count tag rejects overwritten/aliased slots. */
	uint32_t    idx = part_no & TRIG_RING_MASK;
	TrigEntry_t *e  = &g_trig_ring[idx];
	if (e->count != part_no) {
		fault_raise(FAULT_STALE_PART);
		return;
	}

	Ejector_Queue_t *q = &g_ejectors[ejector_id];

	int32_t target = e->pos + q->distance + offset;

	/* If the part has already physically passed the ejector, this is a stale command. */
	int32_t now = tmc4671_getActualPosition(MOTOR);
	if (gc_reached(now, target)) {
		q->stale++;
		fault_raise(FAULT_STALE_PART);
		return;
	}

	uint16_t n = q_next(q->tail);
	if (n == q->head) {
		q->overflows++;
		fault_raise(FAULT_QUEUE_OVERFLOW);
		return;
	}

	q->target_gc[q->tail] = target;
	q->action[q->tail]    = (uint8_t)action;
	q->part_no[q->tail]   = part_no;
	__asm__ volatile("" ::: "memory");
	q->tail = n;
}

/* --- Service (consumer; main loop) ------------------------------------------ */

void ejection_service(int32_t current_gc)
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		Ejector_Queue_t *q = &g_ejectors[e];

		while (!q_is_empty(q) && gc_reached(current_gc, q->target_gc[q->head])) {
			if (q->action[q->head] == EJECT_ACTION_EJECT) {
				ejection_send_ejection_cmd(e, q->part_no[q->head]);
			} else {
				reeler_Pause_Motor();
			}
			q->fired++;
			q->head = q_next(q->head);
		}
	}
}

/* --- Actuation ---------------------------------------------------------------- */

void ejection_send_ejection_cmd(uint8_t bin, uint32_t part_no)
{
	can_AxC_Write(CAN_TOP_AXC_TO_SYSCTRL_ID,
				  ejector_peripheral(bin),
				  AXC_EJECT_PART,
				  (int32_t)part_no);
}

/* --- Fault handling ----------------------------------------------------------- */

void fault_raise(ejection_fault_code_t code)
{
	switch (code) {
		case FAULT_BAD_EJECTOR_ID:
			DBG_Printf(ERR_LVL_ERROR, "[EJT] bad ejector id\n");
			break;

		case FAULT_STALE_PART:
			DBG_Printf(ERR_LVL_ERROR, "[EJT] stale part (late eject/pause)\n");
			can_AxC_Write(CAN_ERR_REPLY_TOP_RACK_ID,
						  EJECTOR_1,
						  AXC_ERR_EJECT_STALE,
						  0);
			break;

		case FAULT_UNPAIRED_ACTION:
			DBG_Printf(ERR_LVL_ERROR, "[EJT] action frame without part count\n");
			can_AxC_Write(CAN_ERR_REPLY_TOP_RACK_ID,
						  EJECTOR_1,
						  AXC_ERR_EJECT_UNPAIRED,
						  0);
			break;

		case FAULT_QUEUE_OVERFLOW:
			DBG_Printf(ERR_LVL_ERROR, "[EJT] target queue overflow\n");
			can_AxC_Write(CAN_ERR_REPLY_TOP_RACK_ID,
						  EJECTOR_1,
						  AXC_ERR_EJECT_OVERFLOW,
						  0);
			break;

		case FAULT_NONE:
		default:
			break;
	}
}
```

> **Notes:**
> - The `EJECTOR_1` peripheral byte inside `fault_raise`'s error frames is a placeholder —
>   adjust if SW/SysCtrl expects a different peripheral for ejection errors.
> - `DBG_Printf` levels (`ERR_LVL_ERROR`, etc.) follow existing usage in this codebase.
> - `reeler_Pause_Motor()` and `tmc4671_getActualPosition(MOTOR)` are already declared
>   via `All_Headers.h`.

---

## File 4: `Bring_Up/Motion/Hybrid_Trigger.c`

Replace the body of `trigger_Camera_Line()` (lines 18–27). Change this line:

```c
	ejection_send_gc(tmc4671_getActualPosition(MOTOR));
```

to:

```c
	ejection_note_trigger(tmc4671_getActualPosition(MOTOR));
```

Full function after change:

```c
void trigger_Camera_Line(void)
{
	ejection_note_trigger(tmc4671_getActualPosition(MOTOR));   // snapshot + count (was ejection_send_gc)
	gpio_set_pin_level(REELER_INT, HIGH);
	delay_us(1);
	gpio_toggle_pin_level(DBGLED3);
	gpio_set_pin_level(REELER_INT, LOW);
	p_reeler1_info->time_ms.cam_trig = millis();
	return;
}
```

> `ejection_send_gc()` is removed entirely (see File 3: it no longer exists). Delete its
> declaration from the old `ejection.h` too (already done by the File 2 rewrite).

---

## File 5: `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.c`

Fill the two `case EJECTOR_1:` / `case EJECTOR_2:` blocks. The `AXC_EJECT_PARTCOUNT`
case handles both reset (`value == 0`) and the normal part count (`value != 0`).

```c
			case EJECTOR_1: {
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX]) {
					case AXC_TRIG_STEPSIZE: {
						/* Distance from the Camera FOV centre to this ejector / cut point. */
						ejection_set_distance(0, rx_can_cmd_info.value);
						break;
					}
					case AXC_EJECT_PARTCOUNT: {
						/* value == 0 -> reset; value != 0 -> part count preceding an action frame. */
						ejection_set_part_no(0, (uint32_t)rx_can_cmd_info.value);
						break;
					}
					case AXC_EJECT_BIN_OFFSET: {
						/* Eject this part (offset = position within FOV). */
						ejection_enqueue(0, rx_can_cmd_info.value, EJECT_ACTION_EJECT);
						break;
					}
					case AXC_PAUSE: {
						/* Stop the reeler at the cut point instead of ejecting. */
						ejection_enqueue(0, rx_can_cmd_info.value, EJECT_ACTION_PAUSE);
						break;
					}
					default: break;
				}
				rack_id = MOTOR_ID;
				break;
			}
			case EJECTOR_2: {
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX]) {
					case AXC_TRIG_STEPSIZE: {
						ejection_set_distance(1, rx_can_cmd_info.value);
						break;
					}
					case AXC_EJECT_PARTCOUNT: {
						/* Same shared counter as EJECTOR_1 (reset or part count). */
						ejection_set_part_no(1, (uint32_t)rx_can_cmd_info.value);
						break;
					}
					case AXC_EJECT_BIN_OFFSET: {
						ejection_enqueue(1, rx_can_cmd_info.value, EJECT_ACTION_EJECT);
						break;
					}
					case AXC_PAUSE: {
						ejection_enqueue(1, rx_can_cmd_info.value, EJECT_ACTION_PAUSE);
						break;
					}
					default: break;
				}
				rack_id = MOTOR_ID;
				break;
			}
```

> The `AXC_EJECT_PART` (29) frame is **outbound** (AxC → SysCtrl); it is not parsed here.
> It is emitted by `ejection_send_ejection_cmd()`.

---

## File 6: `Bring_Up/DBG_bring_up.c`

Add `ejection_init()` inside `call_All_Init_Functions()`, after the motor structs are set
up (near the end of the function, before it returns).

```c
	ejection_init();
```

Suggested placement: right after the `switch(sbridge_addr)` block that initialises the
motor structs, so the ejection module is ready before the main loop starts servicing.
