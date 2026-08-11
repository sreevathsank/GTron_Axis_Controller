/*
 * Step_Counter.c
 *
 * Created: 14-08-2025 15:43:14
 *  Author: sreevathsank
 */ 

#include "tmc2209_uart/Step_Counter.h"

void index_Interrupt_Callback( void )
{
	// Inc or Dec counter value based on the Direction of Motor Motion.
	//p_guide_info->position.counter_value += (p_guide_info->flags.direction) ? -1 : 1;
	step_count += (step_dir) ? -1 : 1;
	return;	
}

void diag_Interrupt_Callback( void ) 
{
	tmc2209_diag_flag = true;
	return;
}

void check_Diag_2209( void )
{
	volatile Motor_Info_t *m1 = mot_array[TMC2209_MOTOR1];
	volatile Motor_Info_t *m2 = mot_array[TMC2209_MOTOR2];
	if(m1 == NULL) {
		DBG_Printf(ERR_LVL_ERROR, "check_Diag_2209() m1 NULL ptr\n");
	}
	if(m2 == NULL) {
		DBG_Printf(ERR_LVL_ERROR, "check_Diag_2209() m2 NULL ptr\n");
	}
	
	DBG_Printf(ERR_LVL_DEBUG, "Diag Interrupt Received!\n");
	
	return;
}

// Convert microsteps/second to rotation/second.
float us_per_sec_to_rps(int32_t microsteps)
{
	return (float)( (microsteps * VACTUAL_TO_HZ_FACTOR) / TMC2209_ROTATION );
}

// Convert rotation/second to microsteps/second.
int32_t rps_to_us_per_sec(float rps)
{
	return (int32_t)( (rps * TMC2209_ROTATION) / VACTUAL_TO_HZ_FACTOR );
}

uint16_t read_TMC2209_mscnt(uint16_t icID)
{
	int32_t mscnt_reg_val = tmc2209_readRegister(icID, TMC2209_MSCNT);
	return (uint16_t)(mscnt_reg_val & 0x3FF);
}

void check_Which_2209_Motor_Moving(void) 
{
	volatile Motor_Info_t *m = NULL;
	volatile Motor_Info_t *m1 = mot_array[TMC2209_MOTOR1];
	volatile Motor_Info_t *m2 = mot_array[TMC2209_MOTOR2];
	if(!m1) {
		DBG_Printf(ERR_LVL_ERROR, "check_Which_2209_Motor_Moving() m1 mot_array entry NULL ptr error. Motor Stoppeed\n");
		is_tmc2209_mot_moving = false;
		//tmc2209_Stop_Motor(m1);
		return;
	}
	if(!m2) {
		DBG_Printf(ERR_LVL_ERROR, "check_Which_2209_Motor_Moving() m2 mot_array entry NULL ptr error. Motor Stopped\n");
		is_tmc2209_mot_moving = false;
		//tmc2209_Stop_Motor(m2);
		return;
	}
	if( (m1->motor_state == MOTOR_MOVING_STATE) || m1->flags.is_tmc2209_homing ||
		m1->flags.move_to_open_lim || m1->flags.move_to_close_lim ) {
		m = m1;
	} else if( (m2->motor_state == MOTOR_MOVING_STATE) || m2->flags.is_tmc2209_homing ||
		m2->flags.move_to_open_lim || m2->flags.move_to_close_lim ) {
		m = m2;
	}
	if(!m) {
		DBG_Printf(ERR_LVL_ERROR, "check_Which_2209_Motor_Moving() Motor_Info_t NULL ptr error.\n");
		is_tmc2209_mot_moving = false;
		return;
	}
	
	if( m->flags.homing || m->flags.move_given || \
	    m->flags.move_to_open_lim || m->flags.move_to_close_lim \
		&& !gtron_limits.interrupt_raised ) { 
		update_TMC2209_Step_Tracking(m);
		uint32_t diff_ms = millis() - m->time_ms.move_start;
		//if( diff_ms > (m->time_ms.theoretical_move * 1.1 ) 
		//	&& ( !m->flags.is_tmc2209_homing && !m->flags.move_to_open_lim && !m->flags.move_to_close_lim ) ){
		//	tmc2209_Stop_Motor(m);
		//	DBG_Printf(ERR_LVL_ERROR, "Move Time taken more than 1.5 * theoretical time taken. Stoppping the Motor\n");
		//}
	}
	
	return;	
}

void update_TMC2209_Step_Tracking(Motor_Info_t *motor_info)
{
	if(!motor_info) { return; }
	
	//uint32_t pwm_scale = tmc2209_readRegister(motor_info->comms.uart_addr, TMC2209_PWM_SCALE);
	//uint8_t pwm_scale_sum = (pwm_scale >> TMC2209_PWM_SCALE_SUM_SHIFT) & TMC2209_PWM_SCALE_SUM_MASK;
	
	//uint32_t pwm_auto = tmc2209_readRegister(motor_info->comms.uart_addr, TMC2209_PWM_AUTO);
	//uint8_t pwm_ofs_auto = (pwm_auto >> TMC2209_PWM_OFS_AUTO_SHIFT) & TMC2209_PWM_OFS_AUTO_MASK;
	//uint8_t pwm_grad_auto = (pwm_auto >> TMC2209_PWM_GRAD_AUTO_SHIFT) & TMC2209_PWM_GRAD_AUTO_MASK;
	//DBG_Printf(ERR_LVL_DEBUG, 
	//	"pwm_scale = %ld -> pwm_scale_sum = %u | pwm_auto = %ld -> pwm_ofs_auto = %u, pwm_grad_auto = %u\n",
	//	pwm_scale, pwm_scale_sum, pwm_auto, pwm_ofs_auto, pwm_grad_auto);
	
	uint16_t current_mscnt = read_TMC2209_mscnt(motor_info->comms.uart_addr);
	DBG_Printf(ERR_LVL_DEBUG, "current_mscnt = %d\n", current_mscnt);
	
	// Skip calculation on the first reading.
	if(motor_info->flags.mscnt_first_reading) {
		motor_info->step_tracker.prev_mscnt = current_mscnt;
		motor_info->flags.mscnt_first_reading = false;
		return;
	}
	
	// Calculate the difference.
	int16_t diff = (int16_t)current_mscnt - (int16_t)motor_info->step_tracker.prev_mscnt;
	DBG_Printf(ERR_LVL_DEBUG, "diff = %d\n", diff);
	// Detect and handle wraparound.
	if( diff > MSCNT_WRAP_THRESHOLD ) {
		// Wrrapped backward (from 0 to 1023), reverse direction of motion.
		diff -= MSCNT_MAX;
	} else if( diff < -MSCNT_WRAP_THRESHOLD ) {
		// Wrapped forward (from 1023 to 0), forward direction of motion.
		diff += MSCNT_MAX;
	}
	
	// Calculate magnitude of change
	int32_t step_delta = abs(diff);

	// Update totals based on commanded direction to ensure coordinate alignment
	if (motor_info->flags.direction == COUNT_UP) {
		motor_info->step_tracker.total_steps += step_delta;
	} else {
		motor_info->step_tracker.total_steps -= step_delta;
	}
	
	motor_info->step_tracker.total_dist += step_delta;
	
	// Store the current reading for next iteration.
	motor_info->step_tracker.prev_mscnt = current_mscnt;
	
	if(motor_info->flags.move_given) {
		int32_t pos_diff = motor_info->position.target - motor_info->step_tracker.total_steps;
		bool diff_zero = false;
		if( (motor_info->flags.direction == COUNT_UP ) && (pos_diff <= 0) ) {
			diff_zero = true;
		} else if( (motor_info->flags.direction == COUNT_DOWN ) && (pos_diff >= 0) ) {
			diff_zero = true;
		}
		
		if( diff_zero ) {
			motor_info->flags.move_given = false;
			tmc2209_set_velocity(motor_info->comms.uart_addr, motor_info, 0);
			motor_info->position.current = motor_info->step_tracker.total_steps;
			is_tmc2209_mot_moving = false;
			message_Id = CAN_REPLY_TOP_RACK_ID;
			switch(motor_info->mot_name) {
				case MOTOR_GUIDE:		can_tx_frame.data[0] = GUIDE_MOTOR;					break;
				case MOTOR_REELER1:		can_tx_frame.data[0] = REELER_MOTOR_1;				break;
				case MOTOR_VARREST1:	can_tx_frame.data[0] = VERITCAL_ARRESTOR_MOTOR1;	break;
				case MOTOR_VARREST2:	can_tx_frame.data[0] = VERITCAL_ARRESTOR_MOTOR2;	break;
				case MOTOR_REELERADJ1:	can_tx_frame.data[0] = REELER_ADJ_MOTOR1;			break;
				case MOTOR_FRONT_CAM:	can_tx_frame.data[0] = FRONT_CAMERA_MOTOR;			break;
				case MOTOR_REELER2:		can_tx_frame.data[0] = REELER_MOTOR_2;				break;
				default: break;
			}
			can_tx_frame.data[1] = AXC_MOVE_DONE;
			can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
			DBG_Printf(ERR_LVL_DEBUG, "\nTMC2209 Move Done. Current Position = %ld usteps | Time Taken = %ld ms\n", \
			motor_info->position.current, millis() - motor_info->time_ms.move_start);
			motor_info->motor_state		= MOTOR_MOVE_DONE_STATE;
			motor_info->move_dir.prev	= motor_info->move_dir.curr;
		}
	}
	return;
}

void tmc2209_set_velocity(uint16_t icID, Motor_Info_t *motor_info, int32_t velocity)
{
	// Set the direction of motion according the velocity given.
	if( velocity > 0 ) { 
		motor_info->flags.direction = COUNT_UP; 
		step_dir = COUNT_UP;
		motor_info->move_dir.curr = DIR_FORWARD;
		DBG_Printf(ERR_LVL_DEBUG, "\nVelocity > 0 | Count UP + 1\n");
	} else if( velocity < 0 ) { 
		motor_info->flags.direction = COUNT_DOWN; 
		step_dir = COUNT_DOWN;
		motor_info->move_dir.curr = DIR_REVERSE;
		DBG_Printf(ERR_LVL_DEBUG, "\nVelocity < 0 | Count DOWN - 1\n");
	}
	
	tmc2209_writeRegister(icID, TMC2209_VACTUAL, velocity);
	
	return;
}

