/*
 * ejection.h
 *
 * Created: 10-08-2026 12:14:05
 *  Author: sreevathsank
 */ 


#ifndef EJECTION_H_
#define EJECTION_H_

#include "All_Headers.h"

#define NUM_EJECTORS        4u
#define QUEUE_DEPTH         32u
#define QUEUE_MASK          (QUEUE_DEPTH - 1u)

#if (QUEUE_DEPTH == 0u) || ((QUEUE_DEPTH & QUEUE_MASK) != 0u)
#error "QUEUE_DEPTH in ejection.h must be a non-zero power of two"
#endif

typedef enum {
	FAULT_NONE             = 0,
	FAULT_QUEUE_OVERFLOW   = 1,
	FAULT_BAD_EJECTOR_ID   = 2
} ejection_fault_code_t;

// Platform Hooks
void fault_raise(ejection_fault_code_t code);

typedef struct {
	int32_t             target_gc[QUEUE_DEPTH]; // Monotonic GC target
	volatile uint16_t   head;
	volatile uint16_t   tail;
	uint32_t            fired;
	uint32_t            stale_misses;
	uint32_t            overflows;
} Ejector_Queue_t;

extern Ejector_Queue_t g_ejectors[NUM_EJECTORS];

void ejection_init(void);
void ejection_flush_all(void);
bool ejection_enqueue(uint8_t ejector_id, int32_t target_gc);
void ejection_service(int32_t current_gc);
void ejection_send_ejection_cmd(uint8_t bin);
void ejection_send_gc(int32_t gc);


#endif /* EJECTION_H_ */