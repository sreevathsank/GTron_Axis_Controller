/*
 * ejection.h
 *
 * Created: 10-08-2026 12:14:05
 *  Author: sreevathsank
 */

/**
 * \file
 *
 * \brief	Ejection module: per-bin ring-buffer queues for delayed part ejection.
 *
 * The Host SW matches each camera-trigger GC to an inspected image and sends
 * back a target GC (inspection GC + bin offset) for each part. This module
 * enqueues those targets per bin and fires ejection commands when the motor
 * position reaches them.
 */

#ifndef EJECTION_H_
#define EJECTION_H_

#include "All_Headers.h"

/** \brief	Compile-time maximum number of ejector bins. */
#define NUM_EJECTORS        2u

/** \brief	Ring-buffer depth per queue (must be power of two).
 *  Usable slots = QUEUE_DEPTH - 1 (one slot reserved for empty/full
 *  discrimination). */
#define QUEUE_DEPTH         32u

/** \brief	Bitmask for power-of-two wraparound (QUEUE_DEPTH - 1u). */
#define QUEUE_MASK          (QUEUE_DEPTH - 1u)

#if (QUEUE_DEPTH == 0u) || ((QUEUE_DEPTH & QUEUE_MASK) != 0u)
#error "QUEUE_DEPTH in ejection.h must be a non-zero power of two"
#endif

/**
 * \brief	Fault codes raised by the ejection module.
 */
typedef enum {
	FAULT_NONE             = 0,	/**< \brief	No fault. */
	FAULT_QUEUE_OVERFLOW   = 1,	/**< \brief	Enqueue failed - queue is full. */
	FAULT_BAD_EJECTOR_ID   = 2		/**< \brief	Enqueue called with out-of-range ejector_id. */
} ejection_fault_code_t;

void fault_raise(ejection_fault_code_t code);

/**
 * \brief	Per-bin ring-buffer queue of pending ejection GC targets.
 *
 * A single-producer (CAN ISR), single-consumer (main loop) lock-free queue
 * implemented as a power-of-two sized circular buffer. head == tail means
 * empty; advancing tail into head means full.
 */
typedef struct {
	int32_t             target_gc[QUEUE_DEPTH];		/**< \brief	Monotonic GC positions at which to fire this ejector. */
	volatile uint16_t   head;						/**< \brief	Oldest pending target index (consumer reads here). */
	volatile uint16_t   tail;						/**< \brief	Next free slot index (producer writes here). */
	uint32_t            fired;						/**< \brief	Telemetry: total ejection commands sent. */
	uint32_t            stale_misses;				/**< \brief	Telemetry: targets already passed at enqueue time (reserved). */
	uint32_t            overflows;					/**< \brief	Telemetry: enqueue attempts rejected due to full queue. */
} Ejector_Queue_t;

/** \brief	Global per-bin ejector queues. Indexed directly by ejector/bin number. */
extern Ejector_Queue_t g_ejectors[NUM_EJECTORS];

/**
 * \brief	Initialises all ejector queues to empty and zeros telemetry counters.
 *
 * @param[in]	void
 * @return		void
 */
void ejection_init(void);

/**
 * \brief	Flushes all ejector queues to empty (head = tail).
 *
 * @param[in]	void
 * @return		void
 */
void ejection_flush_all(void);

/**
 * \brief	Enqueues a target GC onto the given ejector's ring buffer.
 *
 * Called from CAN RX context when the Host sends an ejection target.
 *
 * @param[in]	ejector_id	Bin number (0 ... NUM_EJECTORS - 1).
 * @param[in]	target_gc	Motor microstep position at which to trigger ejection.
 * @return		true if enqueued successfully, false if queue full or bad ID.
 */
bool ejection_enqueue(uint8_t ejector_id, int32_t target_gc);

/**
 * \brief	Drains all reached targets from every bin and fires ejection commands.
 *
 * Must be called periodically from the main loop.
 *
 * @param[in]	current_gc	Current motor microstep position (from TMC4671).
 * @return		void
 */
void ejection_service(int32_t current_gc);

/**
 * \brief	Sends a CAN frame to the pneumatic board to fire the given bin.
 *
 * @param[in]	bin	Bin number to actuate.
 * @return		void
 */
void ejection_send_ejection_cmd(uint8_t bin);

/**
 * \brief	Sends the current GC to the Host PC over CAN at camera trigger time.
 *
 * @param[in]	gc	Motor microstep position at the instant of camera trigger.
 * @return		void
 */
void ejection_send_gc(int32_t gc);


#endif /* EJECTION_H_ */