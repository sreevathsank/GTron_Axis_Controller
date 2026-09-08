/*
 * ejection.c
 *
 * Created: 10-08-2026 12:13:46
 *  Author: sreevathsank
 */
#include "ejection.h"

/** \brief	Global per-bin ejector queues. Indexed directly by ejector/bin number. */
Ejector_Queue_t g_ejectors[NUM_EJECTORS];

/**
 * \brief	Returns true if the ring buffer is empty.
 *
 * @param[in]	q	Pointer to the queue.
 * @return		true when head == tail, false otherwise.
 */
static inline bool q_is_empty(const Ejector_Queue_t *q) 
{
	return q->head == q->tail;
}

/**
 * \brief	Advances an index with power-of-two wraparound via QUEUE_MASK.
 *
 * @param[in]	i	Current index.
 * @return		Next index (wraps to 0 at QUEUE_DEPTH).
 */
static inline uint16_t q_next(uint16_t i) 
{
	return (uint16_t)((i + 1u) & QUEUE_MASK);
}

/**
 * \brief	Wraparound-safe check: has the motor reached the target GC position?
 *
 * Uses unsigned subtraction so the comparison is correct across the full
 * int32_t range regardless of sign or wrap.
 *
 * @param[in]	current_gc	Current motor microstep position.
 * @param[in]	target_gc	Target GC position to check against.
 * @return		true if current_gc has passed or reached target_gc.
 */
static inline bool gc_reached(int32_t current_gc, int32_t target_gc) 
{
	return (int32_t)((uint32_t)current_gc - (uint32_t)target_gc) >= 0;
}

/**
 * \brief	Initialises all ejector queues to empty and zeros telemetry counters.
 *
 * @param[in]	void
 * @return		void
 */
void ejection_init(void) 
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head			= 0u;
		g_ejectors[e].tail			= 0u;
		g_ejectors[e].fired			= 0u;
		g_ejectors[e].stale_misses	= 0u;
		g_ejectors[e].overflows		= 0u;
	}
	return;
}

/**
 * \brief	Flushes all ejector queues to empty (head = tail).
 *
 * @param[in]	void
 * @return		void
 */
void ejection_flush_all(void) 
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head = g_ejectors[e].tail;
	}
	return;
}

/**
 * \brief	Enqueues a target GC onto the given ejector's ring buffer.
 *
 * Called from CAN RX context when the Host sends an ejection target.
 * If the queue is full, increments overflows and raises a fault.
 *
 * @param[in]	ejector_id	Bin number (0 ... NUM_EJECTORS - 1).
 * @param[in]	target_gc	Motor microstep position at which to trigger ejection.
 * @return		true if enqueued successfully, false if queue full or bad ID.
 */
bool ejection_enqueue(uint8_t ejector_id, int32_t target_gc) 
{
	if (ejector_id >= NUM_EJECTORS) {
		fault_raise(FAULT_BAD_EJECTOR_ID);
		return false;
	}

	Ejector_Queue_t *q = &g_ejectors[ejector_id];

	uint16_t n = q_next(q->tail);
	if (n == q->head) {
		q->overflows++;
		fault_raise(FAULT_QUEUE_OVERFLOW);
		return false;
	}

	q->target_gc[q->tail] = target_gc;
	__asm__ volatile("" ::: "memory"); /**< Compiler barrier - data written before tail published. */
	q->tail = n;

	return true;
}

/**
 * \brief	Drains all reached targets from every bin and fires ejection commands.
 *
 * Must be called periodically from the main loop. Uses a while loop (not if)
 * to absorb any multi-target overshoot from a slow loop pass.
 *
 * @param[in]	current_gc	Current motor microstep position (from TMC4671).
 * @return		void
 */
void ejection_service(int32_t current_gc) 
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		Ejector_Queue_t *q = &g_ejectors[e];

		while (!q_is_empty(q) && gc_reached(current_gc, q->target_gc[q->head])) {
			ejection_send_ejection_cmd(e);
			q->fired++;
			q->head = q_next(q->head);
		}
	}
	return;
}

/**
 * \brief	Sends a CAN frame to the pneumatic board to fire the given bin.
 *
 * @param[in]	bin	Bin number to actuate.
 * @return		void
 */
void ejection_send_ejection_cmd(uint8_t bin)
{
	/*can_AxC_Write(	CAN_TOP_AXC_TO_SYSCTRL_ID,
					GLOBAL_COUNTER,
					AXC_GC_EJECT,
					(int32_t)bin );*/
	return;
}

/**
 * \brief	Sends the current GC to the Host PC over CAN at camera trigger time.
 *
 * @param[in]	gc	Motor microstep position at the instant of camera trigger.
 * @return		void
 */
void ejection_send_gc(int32_t gc)
{
	can_AxC_Write(	CAN_REPLY_TOP_RACK_ID, 
					GLOBAL_COUNTER,
					AXC_EJECT_PARTCOUNT,
					gc );
	return;
}