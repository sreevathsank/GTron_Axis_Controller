/*
 * Hybrid_Trigger.c
 *
 * Created: 07-04-2026 12:10:50
 *  Author: sreevathsank
 */ 
#include "Hybrid_Trigger.h"

volatile int32_t prev_trig_pos = 0;
volatile uint32_t prev_trig_time_ms = 0;

/** 
 * \brief	Triggers the pin that is directly connected to Sys Ctrl to trigger the Camera.
 *
 * @param	void
 * @return	void
 **/
void trigger_Camera_Line(void) 
{
	gpio_set_pin_level(REELER_INT, HIGH);
	delay_us(1);
	gpio_toggle_pin_level(DBGLED3);
	gpio_set_pin_level(REELER_INT, LOW);
	p_reeler_info->time_ms.cam_trig = millis();
	DBG_Printf(ERR_LVL_INFO, "Camera Line REELER_INT pin toggled\n");
	return;
}

static void handle_inspection_tick( void )
{
	volatile Hybrid_t *H = &p_reeler_info->hybrid;
	uint32_t step = p_reeler_info->position.trig_step_size;
	
	if(p_reeler_info->flags.sensor_trigger) {
		int32_t new_anchor = tmc4671_getActualPosition(MOTOR);
		p_reeler_info->flags.sensor_trigger = false;
		
		if(H->first_trigger_skip) {
			H->first_trigger_skip	= false;
			H->prev_anchor_pos		= new_anchor;
			H->anchor_pos			= new_anchor;
			H->cycle_armed			= true;
			return;
		}
		
		// Slip / spurious trigger detection (anchor-to-anchor delta)
		uint32_t actual			= (uint32_t)labs(new_anchor -H->prev_anchor_pos);
		uint32_t expected		= step;
		uint32_t tolerance		= (expected * HYBRID_SLIP_TOLERANCE_PCT) / 100u;
		uint32_t deviation		= (actual > expected) ? (actual - expected) : (expected - actual);
		
		if(deviation > tolerance) {
			H->consecutive_failures += 1;
			if(H->consecutive_failures >= HYBRID_ALERT_THRESHOLD) {
				DBG_Printf(ERR_LVL_WARNING, "[HYB] slip threshold: fail=%d exp=%ld act=%ld\n", 
							H->consecutive_failures, 
							expected, actual);
				bool can_ret_status;
				//can_ret_status = can_AxC_Write( CAN_REPLY_TOP_RACK_ERR_ID,
				//								HYBRID_TRIGGER_INSPECTION,
				//								SLIP_ERR ) ;
			}
		} else {
			H->consecutive_failures = 0;
		}
		
		H->prev_anchor_pos	= new_anchor;
		H->anchor_pos		= new_anchor;
		H->cycle_armed		= true;
		return;				// do not poll and fire in the same tick.
	}
	
	// No edge in this tick. if armed, check offset and fire when reached.
	if(H->cycle_armed) {
		int32_t cur = tmc4671_getActualPosition(MOTOR);
		if((uint32_t)labs(cur - H->anchor_pos) >= step) {
			trigger_Camera_Line();
			H->gc += 1;
			H->cycle_armed = false;
		}
	}
	return;
}

static void handle_one_shot_tick()
{
	volatile Hybrid_t *H = &p_reeler_info->hybrid;
	
	if(!H->one_shot_armed) {
		// One shot mode is ON but no Move To/By is received yet.
		// Drop any stale flag so the next move starts clean.
		if(p_reeler_info->flags.sensor_trigger) {
			p_reeler_info->flags.sensor_trigger = false;
		}
		return;
	}
	
	if(p_reeler_info->flags.sensor_trigger){
		p_reeler_info->flags.sensor_trigger = false;
		
		// One shot Sequence.
		reeler_Pause_Motor();
		trigger_Camera_Line();
		check_move_done = false;
		
		H->one_shot_armed	= false;
		H->mode				= HYBRID_MODE_OFF;
		p_reeler_info->flags.is_hybrid_trig_enabled = false;
		
		DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot fired; auto-disabled\n");
	}
	return;
}

/** 
 * \brief	The function that checks motor position wrt to sensor trigger flag received from EIC whether to trigger camera or not.
 *
 * @param	void
 * @return	void
 **/
void check_For_Hybrid_Trigger(void)
{
	if(p_reeler_info->flags.is_paused) {
		return;
	}
	
	switch(p_reeler_info->hybrid.mode) {
		case HYBRID_MODE_INSPECTION: { 
			handle_inspection_tick();
			break;
		}
		case HYBRID_MODE_ONE_SHOT:{ 
			handle_one_shot_tick();
			break;
		}
		case HYBRID_MODE_OFF:
		default: 
			if(p_reeler_info->flags.sensor_trigger) {
				p_reeler_info->hybrid.unhandled_edges++;
				p_reeler_info->flags.sensor_trigger = false;
			}
		break;
	}
	return;
}
//void check_For_Hybrid_Trigger(void)
//{
//	int32_t current_pos = tmc4671_getActualPosition(MOTOR);
//	uint32_t diff_pos = abs(prev_trig_pos - current_position);
//	
//	if(p_reeler_info->flags.sensor_trigger && (diff_pos >= p_reeler_info->position.trig_step_size) ) {
//		trigger_Camera_Line();
//		p_reeler_info->flags.sensor_trigger = false;
//		prev_trig_time_ms = millis();
//		
//		DBG_Printf(ERR_LVL_INFO, "\nT%ld => Step Size = %ld | Curr - Prev Pos = %ld | Error = %ld\n", ++trig_no, p_reeler_info->position.trig_step_size, diff_pos,
//		(diff_pos - p_reeler_info->position.trig_step_size));
//		
//		prev_trig_pos = current_pos;
//	}
//	return;
//}