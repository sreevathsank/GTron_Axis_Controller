/*
 * ejection.c
 *
 * Created: 10-08-2026 12:13:46
 *  Author: sreevathsank
 */
#include "ejection.h"

/* --- Module State -------------------------------------------------------- */
TrigEntry_t					g_trig_ring[TRIG_RING_DEPTH];
EjectorQueue_t				g_ejectors[NUM_EJECTORS];

volatile uint32_t			g_cam_count;					/* AxC's Camera-trigger count (1-based). */

static volatile uint32_t	g_pending_part_no;				/* Latched from the part-count frame. */
static volatile uint8_t		g_pending_ejector_id;			/* Ejector id paired with the Latched count. */
static volatile bool		g_pending_valid;				/* true once a part-count-frame is latched. */

/* --- Helpers -------------------------------------------------------------- */
static inline bool q_is_empty(const EjectorQueue_t *q)
{
	return q->head == q->tail;
}

static inline uint16_t q_next(uint16_t i)
{
	return (uint16_t)( (i + 1u) % QUEUE_DEPTH );
}

static inline uint16_t q_prev(uint16_t i)
{
	return (uint16_t)((i + QUEUE_DEPTH - 1u) % QUEUE_DEPTH);
}

/* Wrap-safe "reached" check: true when current_gc has passed or reached target_gc */
static inline uint8_t gc_reached(int32_t current_gc, int32_t target_gc)
{
	return (int32_t)((uint32_t)current_gc - (uint32_t)target_gc) >= 0;
}

/* Map an ejector index (0/1) to its CAN peripheral byte (EJECTOR1, EJECTOR2, ... ). */
static inline uint8_t ejector_peripheral(uint8_t id)
{
	return (id == 0u) ? (uint8_t)EJECTOR_1 : (uint8_t)EJECTOR_2;
}

/* --- Lifecycle ------------------------------------------------------------- */
void ejection_init(void)
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head			= 0u;
		g_ejectors[e].tail			= 0u;
		g_ejectors[e].distance		= 0;
		g_ejectors[e].fired			= 0u;
		g_ejectors[e].stale			= 0u;
		g_ejectors[e].overflows		= 0u;
	}
	g_cam_count				= 0u;
	g_pending_part_no		= 0u;
	g_pending_ejector_id	= 0u;
	g_pending_valid			= false;
	
	return;
}

void ejection_flush_all(void)
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		g_ejectors[e].head	= g_ejectors[e].tail;
	}
	for (uint32_t i = 0u; i < TRIG_RING_DEPTH; ++i) {
		g_trig_ring[i].pos		= 0;
		g_trig_ring[i].count	= 0u;
	}
	g_cam_count				= 0u;
	g_pending_part_no		= 0u;
	g_pending_ejector_id	= 0u;
	g_pending_valid			= false;
	
	DBG_Printf(ERR_LVL_INFO, "[EJT] Flushing all tracking and ejector queues, flags and variables.\n");
	
	return;
}

void ejection_reset(void)
{
	ejection_flush_all();
	
	return;
}

/* --- Configuration ---------------------------------------------------------- */
void ejection_set_distance(uint8_t ejector_id, int32_t distance)
{
	if (ejector_id >= NUM_EJECTORS) {
		ejection_fault_raise(FAULT_BAD_EJECTOR_ID);
		
		return;
	}
	g_ejectors[ejector_id].distance = distance;
	
	DBG_Printf(ERR_LVL_INFO, "[EJT] Set Ejector Distance/Delta for Ejector %d = %ld usteps\n", ejector_id, g_ejectors[ejector_id].distance);
	
	return;
}

/* --- Trigger snapshot (producer: main loop) -------------------------------- */
void ejection_note_trigger(int32_t pos)
{
	uint32_t c		= g_cam_count + 1u;		/* 1-based: first trigger -> 1 */
	uint32_t idx	= c % TRIG_RING_DEPTH;	/* Ensures that idx circles back to 0 after TRIG_RING_DEPTH */
	
	g_trig_ring[idx].pos	= pos;
	g_trig_ring[idx].count	= c;
	__asm__ volatile("" ::: "memory");		/* Compiler barrier. */
	g_cam_count	= c;
	
	DBG_Printf(ERR_LVL_DEBUG, "[EJT] Tracking Q | Index = %ld | Pos = %ld | Cam Count = %ld\n", 
								idx, g_trig_ring[idx].pos, g_trig_ring[idx].count);
	
	return;
}

/* --- Part-count latch (producer: CAN RX) ------------------------------------ */
void ejection_set_part_no(uint8_t ejector_id, uint32_t part_no, EjectAction_t action_to_do)
{
	if (part_no == 0u) {
		ejection_reset();
		return;
	}
	if (ejector_id >= NUM_EJECTORS) {
		ejection_fault_raise(FAULT_BAD_EJECTOR_ID);
		DBG_Printf(ERR_LVL_ERROR, "Ejector Id > No of Ejectors.\n");
		return;
	}
	
	g_pending_part_no						= part_no;
	g_pending_ejector_id					= ejector_id;
	g_pending_valid							= true;
	g_ejectors[ejector_id].upcoming_action	= action_to_do;
	
	DBG_Printf(ERR_LVL_INFO, "[EJT] Part Count received = %ld for Ejector %d.\n", g_pending_part_no, g_pending_ejector_id);
	
	return;
}

/* --- Enqueue (consumer of latch, producer of target queue; CAN RX) ---------- */

void ejection_execute_enqueue(uint8_t ejector_id, int32_t offset)
{
	if (ejector_id >= NUM_EJECTORS) {
		ejection_fault_raise(FAULT_BAD_EJECTOR_ID);
		DBG_Printf(ERR_LVL_ERROR, "Ejector Id > No of Ejectors.\n");
		return;
	}
	(g_ejectors[ejector_id].upcoming_action == EJECT_ACTION_EJECT)
		? ejection_enqueue(ejector_id, offset, EJECT_ACTION_EJECT)
		: ejection_enqueue(ejector_id, offset, EJECT_ACTION_PAUSE);
	
	return;
}

void ejection_enqueue(uint8_t ejector_id, int32_t offset, EjectAction_t action)
{
	if (ejector_id >= NUM_EJECTORS) {
		ejection_fault_raise(FAULT_BAD_EJECTOR_ID);
		DBG_Printf(ERR_LVL_ERROR, "Ejector Id > No of Ejectors.\n");
		return;
	}
	
	/* An action frame must be preceded by a part-count frame. */
	if (!g_pending_valid) {
		ejection_fault_raise(FAULT_UNPAIRED_ACTION);
		DBG_Printf(ERR_LVL_ERROR, "Action frame was not preceded by part-count frame.\n");
		
		return;
	} 
	
	/* Cross-check that the latched count belongs to the same ejector. */
	if (ejector_id != g_pending_ejector_id) {
		ejection_fault_raise(FAULT_UNPAIRED_ACTION);
		DBG_Printf(ERR_LVL_ERROR, "Pending (Offset + Action) ejector is not the same as the one received.\n");
		
		return;
	}
	
	uint32_t part_no	= g_pending_part_no;
	g_pending_valid		= false;
	
	/* Look up the snapshot; the full-count tag rejects overwritten/aliased slots. */
	uint32_t idx	= part_no % TRIG_RING_DEPTH;
	TrigEntry_t *e	= &g_trig_ring[idx];
	if (e->count != part_no) {
		ejection_fault_raise(FAULT_STALE_PART);
		DBG_Printf(ERR_LVL_ERROR, "Received Part count %ld != Trigger'd Part Count %ld\n",
					part_no, e->count);
					
		return;
	}
	
	EjectorQueue_t *q	= &g_ejectors[ejector_id];
	int32_t target		= e->pos + q->distance + offset;
	DBG_Printf(ERR_LVL_DEBUG, "[EJT] Ejector %d's Part No = %ld | %ld (Part Pos) + %ld (Ejt_Delta) + %ld (offset) = %ld usteps or %.2f deg(Ejt Pos)\n",
				ejector_id, part_no, e->pos, q->distance, offset, target, (float)(target / ONE_DEG_STEPS));
	
	/* If the part has already physically passed the ejector, this is a stale command. */
	int32_t now			= tmc4671_getActualPosition(MOTOR);
	if (gc_reached(now, target)) {
		q->stale++;
		ejection_fault_raise(FAULT_STALE_PART);
		DBG_Printf(ERR_LVL_ERROR, "Already physically passed s by %ld usteps. Part No = %ld | C_Pos = %ld usteps | E_pos = %ld usteps\n", 
					(now - target), part_no, now, target);
		
		return;
	}
	
	EjectorQueue_t *qA	= &g_ejectors[ejector_id];
	EjectorQueue_t *qB	= &g_ejectors[1u - ejector_id];
	
	/* Case 1: Same-ejector correction - overwrite tail-1. */
	if(!q_is_empty(qA) && qA->part_no[q_prev(qA->tail)] == part_no) {
		uint16_t p			= q_prev(qA->tail);
		qA->target_gc[p]	= target;
		qA->action[p]		= (uint8_t)action;
		qA->part_no[p]		= part_no;
		
		return;
	}
	/* Case 2: Cross-ejector correction - free stale entry from B, then append to A */
	else if(!q_is_empty(qB) && qB->part_no[q_prev(qB->tail)] == part_no) {
		qB->tail	= q_prev(qB->tail);
	}	
	
	uint16_t n	= q_next(q->tail);
	if (n == q->head) {
		q->overflows++;
		ejection_fault_raise(FAULT_QUEUE_OVERFLOW);
		
		return;
	}
	
	q->target_gc[q->tail]	= target;
	q->action[q->tail]		= (uint8_t)action;
	q->part_no[q->tail]		= part_no;
	__asm__ volatile("" ::: "memory");
	q->tail					= n;
	
	DBG_Printf(ERR_LVL_INFO, "[EJT] Enqueue Ejector %d | Part No = %ld | Curr_Pos = %ld usteps | Ejt_Pos = %ld usteps\n", ejector_id, part_no, now, target, (target - now));
	
	return;
}

/* --- Service (consumer; main loop) ------------------------------------------ */
void ejection_service(int32_t current_gc)
{
	for (uint8_t e = 0u; e < NUM_EJECTORS; e++) {
		EjectorQueue_t *q = &g_ejectors[e];
		
		while (!q_is_empty(q) && gc_reached(current_gc, q->target_gc[q->head])) {
			if (q->action[q->head] == EJECT_ACTION_EJECT) {
				ejection_send_ejection_cmd(e, q->part_no[q->head]);
				int32_t c_pos = tmc4671_getActualPosition(MOTOR);
				DBG_Printf(ERR_LVL_INFO, "[EJT] Ejection Eject Bin %d | Part No = %ld | C_Pos = %ld | Ejt_Pos = %ld | Err = %ld\n",
				e, q->part_no[q->head], c_pos, q->target_gc[q->head], (c_pos - q->target_gc[q->head]));
			} else if ( IS_DISCRETE && (q->action[q->head] == EJECT_ACTION_PAUSE) ) {
				ejection_send_pause_reply(e, q->part_no[q->head]);
				ejection_send_ejection_cmd(e, q->part_no[q->head]);
				p_reeler1_info->flags.is_paused = true;
				/* TODO: Send Stop Motor Command */
				int32_t c_pos = tmc4671_getActualPosition(MOTOR);
				DBG_Printf(ERR_LVL_INFO, "[EJT] Ejection Eject Pause Bin %d | Part No = %ld | C_Pos = %ld | Ejt_Pos = %ld | Err = %ld\n",
				e, q->part_no[q->head], c_pos, q->target_gc[q->head], (c_pos - q->target_gc[q->head]));
			} else {
				reeler_Pause_Motor();
				ejection_send_pause_reply(e, q->part_no[q->head]);
				int32_t c_pos = tmc4671_getActualPosition(MOTOR);
				DBG_Printf(ERR_LVL_INFO, "[EJT] Ejection Pause Bin %d | Part No = %ld | C_Pos = %ld | Ejt_Pos = %ld | Err = %ld\n",
							e, q->part_no[q->head], c_pos, q->target_gc[q->head], (c_pos - q->target_gc[q->head]));
			}
			q->fired++;
			q->head	= q_next(q->head);
		}
	}
	
	return;
}

/* --- Actuation ---------------------------------------------------------------- */
void ejection_send_ejection_cmd(uint8_t bin, uint32_t part_no)
{
	can_AxC_Write(	CAN_TOP_AXC_TO_SYSCTRL_ID,
					ejector_peripheral(bin),
					AXC_EJECT_BIN_OFFSET,
					(int32_t)part_no	);
	
	DBG_Printf(ERR_LVL_INFO, "[EJT] Ejection Eject() Bin %d | Part No = %ld\n", bin, part_no);
	return;
}

void ejection_send_pause_reply(uint8_t bin, uint32_t part_no)
{
	can_AxC_Write(	CAN_TOP_AXC_TO_SYSCTRL_ID,
					ejector_peripheral(bin),
					AXC_PAUSE,
					(int32_t)part_no	);				
	DBG_Printf(ERR_LVL_INFO, "[EJT] Ejection Pause Bin %d | Part No = %ld\n", bin, part_no);
	return;
}

/* --- Fault handling ----------------------------------------------------------- */
void ejection_fault_raise(EjectionFaultCode_t err_code)
{
	switch(err_code) {
		case FAULT_BAD_EJECTOR_ID: {
			DBG_Printf(ERR_LVL_ERROR, "[EJT] Bad Ejector ID\n");
			can_AxC_Write(	CAN_ERR_REPLY_TOP_RACK_ID,
							EJECTOR_1,
							AXC_ERR_EJECT_BAD_EJECTOR_ID,
							0	);
			break;
		}
		case FAULT_STALE_PART: {
			DBG_Printf(ERR_LVL_ERROR, "[EJT] Stale Part (Late eject/Pause)\n");
			can_AxC_Write(	CAN_ERR_REPLY_TOP_RACK_ID,
							EJECTOR_1,
							AXC_ERR_EJECT_STALE,
							0	);
			break;
		}
		case FAULT_UNPAIRED_ACTION: {
			DBG_Printf(ERR_LVL_ERROR, "[EJT] Action Frame without Part Count.\n");
			can_AxC_Write(	CAN_ERR_REPLY_TOP_RACK_ID,
							EJECTOR_1,
							AXC_ERR_EJECT_UNPAIRED,
							0	);
			break;
		}
		case FAULT_QUEUE_OVERFLOW: {
			DBG_Printf(ERR_LVL_ERROR, "[EJT] Target Queue Overflowed.\n");
			can_AxC_Write(	CAN_ERR_REPLY_TOP_RACK_ID,
							EJECTOR_1,
							AXC_ERR_EJECT_OVERFLOW,
							0	);
			break;
		}
		case FAULT_NONE:
		default:
			break;
	}
	
	return;
}