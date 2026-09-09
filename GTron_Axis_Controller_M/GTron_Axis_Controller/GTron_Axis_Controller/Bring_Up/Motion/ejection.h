/*
 * ejection.h
 *
 * Created: 10-08-2026 12:14:05
 *  Author: sreevathsank
 */

/**
 * \file
 *
 * \brief	Ejection & Tracking module: per-ejector target queues, fed by a trigger
 *			position snapshot ring indexed by part count.
 *
 * AxC snapshots PID_POSITION_ACTUAL at every camera trigger . SW inspects tghe image and
 * later sends back the part count + offset + action. AxC reconstructs the absolute
 * target position (snapshot + ejector distance + offset) and fires the action when the
 * motor reaches it.
 *
 * The camera-trigger count is 1-based to match SW (first part = 1). A part count of 0
 * resets the runtine tracking state.
 */

#ifndef EJECTION_H_
#define EJECTION_H_

#include "All_Headers.h"

/** \brief	Compile-time maximum number of ejector bins. */
#define NUM_EJECTORS        2u

/** \brief Depth of the trigger snapshot ring (must be power of two). */
#define TRIG_RING_DEPTH		256u
#define TRIG_RING_MASK		(TRIG_RING_DEPTH - 1u)

/** \brief	Ring-buffer depth per queue (must be power of two).
 *  Usable slots = QUEUE_DEPTH - 1 (one slot reserved for empty/full
 *  discrimination). */
#define QUEUE_DEPTH         256u

/** \brief	Bitmask for power-of-two wraparound (QUEUE_DEPTH - 1u). */
#define QUEUE_MASK          (QUEUE_DEPTH - 1u)

#if ( ((TRIG_RING_DEPTH & TRIG_RING_MASK) != 0u) || ((QUEUE_DEPTH & QUEUE_MASK) != 0u) )
	#error "TRIG_RING_DEPTH and/or QUEUE_DEPTH in ejection.h must be a non-zero power of two"
#endif

/**
 * \brief	Fault codes raised by the ejection module.
 */
typedef enum {
	FAULT_NONE				= 0,	/**< \brief	No fault. */
	FAULT_BAD_EJECTOR_ID	= 1,	/**< Command for an out-of-range ejector id. */
	FAULT_QUEUE_OVERFLOW	= 2,	/**< Target queue full. */
	FAULT_STALE_PART		= 3,	/**< Part already passed its ejector, or ring slot overwritten. */
	FAULT_UNPAIRED_ACTION	= 4,	/**< Action frame without a preceding part-count frame. */
} EjectionFaultCode_t;

/** 
 * \brief Action to perform when a target position is reached.
 */
typedef enum {
	EJECT_ACTION_EJECT	= 0, /**< Send CAN eject frame to SysCtrl. For Discrete Machine. */
	EJECT_ACTION_PAUSE	= 1, /**< Stop the reeler. For GTron Terminal Cut & Weld. */
}EjectAction_t;

/** 
 * \brief One trigger snapshot entry.
 */
typedef struct {
	int32_t pos;	/**< PID_POSITIONACTUAL at the camera-trigger instant. */
	uint32_t count;	/**< Full camera-trigger count at snapshot time (wrap-safe tag). */
}TrigEntry_t;

/** 
 * \brief Per-ejector ring of pending ejection targets.
 *
 * Single-producer (CAN RX), single consumer (main loop). head == tail means empty.
 */
typedef struct {
	int32_t				target_gc[QUEUE_DEPTH];		/**< Absolute PID_POSITION_ACTUAL at which to act. */
	uint8_t				action[QUEUE_DEPTH];		/**< EJECT_ACTION_EJECT or EJECT_ACTION_PAUSE per act. */
	uint32_t			part_no[QUEUE_DEPTH];		/**< Part count echoed back in the eject frame. */
	volatile uint16_t	head;						/**< Oldest pending target (consumer reads). */
	volatile uint16_t	tail;						/**< Next free slot (producer writes). */
	int32_t				distance;					/**< Camera FOC centre -> an ejector/cut point in usteps. */
	uint32_t			fired;						/**< Telemetry: actions performed. */
	uint32_t			stale;						/**< Telemetry: rejected late commands. */
	uint32_t			overflows;					/**< Telemetry: rejected full-queue enqueues. */
}EjectorQueue_t;

/** 
 * \brief	Initializes the trigger ring, queues, counters and pending latch.
 */
void ejection_init(void);

/** 
 * \brief	Flushes all target queues and clears the pending part-count latch.
 */
void ejection_flush_all();

/** 
 * \brief	Resets runtime tracking state: slushes queues/latch, zeros the count.
 *
 * Ejector distances are NOT reset. Handles AXC_EJECT_PARTCOUNT == 0.
 */
void ejection_reset();

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
 * A part-no of 0 resets the runtime tracking state instead of latching.
 *
 * @param[in]	ejector_id	Ejector id the count is paired with.
 * @param[in]	part_no		Camera-trigger count of the part (>= 1; 0 = reset).
 */
 void ejection_set_part_no(uint8_t ejector_id, uint32_t part_no);
 
 /** 
  * \brief	Computes and enqueues a target from the stored snapshot + distance + offset.
  *
  * Called from CAN RX on the action frame. Consumes the latched part count.
  *
  * @param[in]	ejector_id	0 ... NUM_EJECTORs - 1.
  * @param[in]	offset		Part position within the FOV, relative to centre (usteps, signed).
  * @param[in]	action		EJECT_ACTIONEJECT or EJECT_ACTION_PAUSE.
  */
 void ejection_enqueue(uint8_t ejector_id, int32_t offset, EjectAction_t action);
 
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
  * \brief	Sends a CAN frame to SysCtrl to inform that Reeler has paused on cutting position.
  *
  * @param[in]	bin		Ejector index (0/1).
  * @param[in]	part_no	Part count of the part to eject.
  */
 void ejection_send_pause_reply(uint8_t bin, uint32_t part_no);
 
 /** 
  * \brief	Raises a fault: logs it and, where relevant, sends a CAN error to SW/SysCtrl.
  *
  * @param[in]	code	Fault code.
  */
 void ejection_fault_raise(EjectionFaultCode_t err_code);

#endif /* EJECTION_H_ */