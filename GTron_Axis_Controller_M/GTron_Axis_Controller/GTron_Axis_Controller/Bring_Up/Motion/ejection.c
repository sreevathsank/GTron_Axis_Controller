/*
 * ejection.c
 *
 * Created: 10-08-2026 12:13:46
 *  Author: sreevathsank
 */
#include "ejection.h"

Ejector_Queue_t g_ejectors[NUM_EJECTORS];

static inline bool q_is_empty(const Ejector_Queue_t *q) {
	return q->head == q->tail;
}

static inline uint16_t q_next(uint16_t i) {
	return (uint16_t)((i + 1u) & QUEUE_MASK);
}

static inline bool gc_reached(int32_t current_gc, int32_t target_gc) {
	return (int32_t)((uint32_t)current_gc - (uint32_t)target_gc) >= 0;
}

void ejection_init(void) {
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head			= 0u;
		g_ejectors[e].tail			= 0u;
		g_ejectors[e].fired			= 0u;
		g_ejectors[e].stale_misses	= 0u;
		g_ejectors[e].overflows		= 0u;
	}
}

void ejection_flush_all(void) {
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head = g_ejectors[e].tail;
	}
}

bool ejection_enqueue(uint8_t ejector_id, int32_t target_gc) {
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
	__asm__ volatile("" ::: "memory"); // Compiler memory barrier for atomic tail update
	q->tail = n;

	return true;
}

void ejection_service(int32_t current_gc) {
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		Ejector_Queue_t *q = &g_ejectors[e];

		while (!q_is_empty(q) && gc_reached(current_gc, q->target_gc[q->head])) {
			ejection_send_ejection_cmd(e);
			q->fired++;
			q->head = q_next(q->head);
		}
	}
}

void ejection_send_ejection_cmd(uint8_t bin)
{
	can_AxC_Write(	CAN_TOP_AXC_TO_SYSCTRL_ID,
					GLOBAL_COUNTER,
					AXC_GC_EJECT,
					(int32_t)bin );
	return;
}

void ejection_send_gc(int32_t gc)
{
	can_AxC_Write(	CAN_REPLY_TOP_RACK_ID, 
					GLOBAL_COUNTER,
					AXC_GC_COUNT,
					gc );
	return;
}