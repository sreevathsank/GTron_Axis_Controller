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
	//DBG_Printf(ERR_LVL_INFO, "Camera Line REELER_INT pin toggled\n");
	return;
}


/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
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
		uint32_t actual			= (uint32_t)labs(new_anchor - H->prev_anchor_pos);
		uint32_t expected		= step;
		uint32_t tolerance		= (expected * HYBRID_SLIP_TOLERANCE_PCT) / 100u;
		uint32_t deviation		= (actual > expected) ? (actual - expected) : (expected - actual);
		
		if(deviation > tolerance) {
			// Slipped.
			H->consecutive_slips += 1;
			if(H->consecutive_slips >= HYBRID_ALERT_THRESHOLD) {
				DBG_Printf(ERR_LVL_WARNING, "[HYB] slip threshold: fail=%d exp=%ld act=%ld\n", 
							H->consecutive_slips, 
							expected, actual);
				bool can_ret_status;
				//can_ret_status = can_AxC_Write( CAN_REPLY_TOP_RACK_ERR_ID,
				//								HYBRID_TRIGGER_INSPECTION,
				//								SLIP_ERR ) ;
			}
		} else {
			H->consecutive_slips = 0;
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


/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
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
 * \brief
 *
 * @param
 *
 * @return
 **/
static void handle_n_shot_tick()
{
	volatile Hybrid_t *H = &p_reeler_info->hybrid;
	uint32_t step = p_reeler_info->position.trig_step_size;
	uint32_t term_pitch = H->term_width;
	
	if( H->total_slips == 0) {
		H->total_slips = HYBRID_ALERT_THRESHOLD;
	}
	
	// If no sensor trigger has happened for about (total slips x terminal width), stop the motor and inform the error.
	if( (abs(tmc4671_getActualPosition(MOTOR) - H->prev_anchor_pos) > (H->total_slips * H->term_width) ) &&
		!p_reeler_info->flags.sensor_trigger && !p_reeler_info->flags.is_encoder_mode ) 
	{
		DBG_Printf(ERR_LVL_ERROR, "No sensor trigger was received for %ld usteps.\nPausing the motor and informing the error.", (H->total_slips * H->term_width));
		can_AxC_Write(	CAN_ERR_REPLY_TOP_RACK_ID,
						HYBRID_TRIGGER_INSPECTION,
						AXC_ERR_TRIGGER_FAIL, 0);
		reeler_Pause_Motor();
	}
	
	// If sensor trigger is received but the cycle is still armed, ignore the sensor trigger.
	if(p_reeler_info->flags.sensor_trigger && H->cycle_armed && !p_reeler_info->flags.is_encoder_mode) {
		DBG_Printf(ERR_LVL_WARNING, "Spurious Sensor Trigger rxcvd while cycle armed. Ignoring...\n");
		p_reeler_info->flags.sensor_trigger = false;
	}
	
	// If sensor trigger is received while cycle is not armed, it is a valid trigger.
	if(p_reeler_info->flags.sensor_trigger && !p_reeler_info->flags.is_encoder_mode) {
		p_reeler_info->flags.sensor_trigger = false;
		int32_t new_anchor = tmc4671_getActualPosition(MOTOR);
		
		if(H->first_trigger_skip && !p_reeler_info->flags.is_paused && !p_reeler_info->flags.is_encoder_mode) {
			H->first_trigger_skip	= false;
			H->prev_anchor_pos		= new_anchor;
			H->anchor_pos			= new_anchor;
			H->cycle_armed			= true;
			DBG_Printf(ERR_LVL_DEBUG, "First Trigger Skipped | Arming for next cycle.\n");
			return;
		}
		
		p_reeler_info->flags.is_paused = false;
	
		// Slip / Spurious Trigger Detection (anchor to anchor delta).
		uint32_t actual			= (uint32_t)abs(new_anchor - H->prev_anchor_pos);
		uint32_t expected		= H->term_width;
		uint32_t tolerance		= (expected * HYBRID_SLIP_TOLERANCE_PCT) / 100u;
		uint32_t deviation		= (actual > expected) ? (actual - expected) : (expected - actual);
		
		if(deviation > tolerance) {
			// Slipped.
			if(++H->consecutive_slips >= H->total_slips) {
				DBG_Printf(ERR_LVL_WARNING, "Slipped: Fail %d | Expected Range = %ld to %ld | Actual = %ld\n", 
							H->consecutive_slips, 
							(expected - tolerance),
							(expected + tolerance),
							expected, actual);
				can_AxC_Write(	CAN_ERR_REPLY_TOP_RACK_ID,
								HYBRID_TRIGGER_INSPECTION,
								AXC_ERR_SLIP, 0 );
				reeler_Pause_Motor();
			}
		} else {
			H->consecutive_slips = 0;
		}
		
		DBG_Printf(ERR_LVL_DEBUG, "Delta of prev to curr anchor pos = %ld\n", abs(new_anchor - H->prev_anchor_pos));
		H->prev_anchor_pos		= new_anchor;
		H->anchor_pos			= new_anchor;
		H->cycle_armed			= true;
		//return;					// do not poll and fire in the same tick;
	}
	
	if(p_reeler_info->flags.is_encoder_mode && !H->cycle_armed) {
		H->cycle_armed = true;
		H->anchor_pos = tmc4671_getActualPosition(MOTOR);
	}	
	
	// Valid sensor trigger was received and the cycle is armed to execute camera line.
	if(H->cycle_armed) {
		int32_t cur_pos = tmc4671_getActualPosition(MOTOR);
		
		switch(H->total_n_shots) {
			// Inspection.
			case 0: {
				if((uint32_t)abs(cur_pos - H->anchor_pos) >= step) {
					trigger_Camera_Line();
					H->gc += 1;
					H->cycle_armed = false;
					if(p_reeler_info->flags.is_encoder_mode) {
						DBG_Printf(ERR_LVL_DEBUG, "[ENC] curr = %ld | anchor_pos = %ld | curr - anchor_pos = %ld\n", cur_pos, H->anchor_pos, abs(cur_pos - H->anchor_pos));
					} else {
						DBG_Printf(ERR_LVL_DEBUG, "[HYB] curr = %ld | anchor_pos = %ld | curr - anchor_pos = %ld\n", cur_pos, H->anchor_pos, abs(cur_pos - H->anchor_pos));
					}
				}
				break;
			}
			default: {
				if((uint32_t)abs(cur_pos - H->anchor_pos) >= step) {
					if(++H->curr_n_shots < H->total_n_shots) {
						trigger_Camera_Line();
						H->cycle_armed		= false;
						if(p_reeler_info->flags.is_encoder_mode) {
							DBG_Printf(ERR_LVL_DEBUG, "[ENC] (%ld) N-Shots fired out of %ld\n", H->curr_n_shots, H->total_n_shots);
							DBG_Printf(ERR_LVL_DEBUG, "[ENC] curr = %ld | anchor_pos = %ld | curr - anchor_pos = %ld\n", cur_pos, H->anchor_pos, abs(cur_pos - H->anchor_pos));
						} else {
							DBG_Printf(ERR_LVL_DEBUG, "[HYB] (%ld) N-Shots fired out of %ld\n", H->curr_n_shots, H->total_n_shots);
							DBG_Printf(ERR_LVL_DEBUG, "[HYB] curr = %ld | anchor_pos = %ld | curr - anchor_pos = %ld\n", cur_pos, H->anchor_pos, abs(cur_pos - H->anchor_pos));
						}
					} else {
						reeler_Pause_Motor();
						trigger_Camera_Line();
						if(p_reeler_info->flags.is_encoder_mode) {
							DBG_Printf(ERR_LVL_DEBUG, "[ENC] (%ld) N-Shots fired out of %ld | Disabling N Shot Mode\n", H->curr_n_shots, H->total_n_shots);
							p_reeler_info->flags.is_encoder_mode = false;
						} else {
							DBG_Printf(ERR_LVL_DEBUG, "[HYB] (%ld) N-Shots fired out of %ld | Disabling N Shot Mode\n", H->curr_n_shots, H->total_n_shots);
						}
						H->cycle_armed		= false;
						H->mode				= HYBRID_MODE_OFF;
						H->curr_n_shots		= 0;
						p_reeler_info->flags.is_hybrid_trig_enabled = false;
						p_reeler_info->flags.is_paused				= true;
						p_reeler_info->flags.sag_enabled			= false;
						p_reeler_info->flags.rotate_vel_mode		= false;
					}
				}
				break;
			}
		}
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
			//handle_inspection_tick();
			handle_n_shot_tick();
			break;
		}
		case HYBRID_MODE_N_SHOT: { 
			handle_n_shot_tick();
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