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
	p_guide_info->position.counter_value += (p_guide_info->flags.direction) ? -1 : 1;
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

void update_TMC2209_Step_Tracking(Motor_Info_t *motor_info)
{
	if(motor_info == NULL) { return; }
	
	uint16_t current_mscnt = 0;
	//if(motor_info->motor_name == GUIDE_STRUCT)
	{
		current_mscnt = read_TMC2209_mscnt(TMC2209_GUIDE_ADDR);
	}
	//if(motor_info->motor_name == VARREST_STRUCT)
	{
		//current_mscnt = read_TMC2209_mscnt(TMC2209_VERT_ARREST_ADDR);
	}
	
	// Skip calculation on the first reading.
	if(motor_info->flags.mscnt_first_reading)
	{
		motor_info->step_tracker.prev_mscnt = current_mscnt;
		motor_info->flags.mscnt_first_reading = false;
		return;
	}
	
	// Calculate the difference.
	int16_t diff = (int16_t)current_mscnt - (int16_t)motor_info->step_tracker.prev_mscnt;
	
	// Detect and handle wraparound.
	if( diff > MSCNT_WRAP_THRESHOLD )
	{
		// Wrrapped backward (from 0 to 1023), reverse direction of motion.
		diff -= MSCNT_MAX;
	}
	else if( diff < -MSCNT_WRAP_THRESHOLD )
	{
		// Wrapped forward (from 1023 to 0), forward direction of motion.
		diff += MSCNT_MAX;
	}
	
	// Calculate magnitude of change
	int32_t step_delta = abs(diff);

	// Update totals based on commanded direction to ensure coordinate alignment
	if (motor_info->flags.direction == COUNT_UP)
	{
		motor_info->step_tracker.total_steps += step_delta;
	}
	else
	{
		motor_info->step_tracker.total_steps -= step_delta;
	}
	
	motor_info->step_tracker.total_dist += step_delta;
	
	// Store the current reading for next iteration.
	motor_info->step_tracker.prev_mscnt = current_mscnt;
	
	//printf("\ntarget pos = %ld | current_pos = %ld\n", motor_info->position.target, motor_info->step_tracker.total_steps, abs(motor_info->position.target - motor_info->step_tracker.total_steps));
	if(motor_info->flags.move_given)
	{
		int32_t pos_diff = motor_info->position.target - motor_info->step_tracker.total_steps;
		bool diff_zero = false;
		if( (motor_info->flags.direction == COUNT_UP ) && (pos_diff <= 0) )
		{
			diff_zero = true;
		}
		else if( (motor_info->flags.direction == COUNT_DOWN ) && (pos_diff >= 0) )
		{
			diff_zero = true;
		}
		
		//printf("\n%ld\n", pos_diff );
		if( diff_zero )
		{
			
		}
		if( diff_zero )
		{
			motor_info->flags.move_given = false;
			tmc2209_set_velocity(TMC2209_GUIDE_ADDR, motor_info, ZERO_HEX);
			motor_info->position.current = motor_info->step_tracker.total_steps;
			message_Id = CAN_REPLY_TOP_RACK_ID;
			can_tx_frame.data[0] = GUIDE_MOTOR;
			can_tx_frame.data[1] = AXC_MOVE_DONE;
			can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
			PRINTF_DEBUG ? printf("\nGuide Move Done. Current Position = %ld usteps\n", \
			motor_info->position.current): 0;
		}
	}
	
	//PRINTF_DEBUG ? printf("\nguide_step_counter Val = %ld\n", p_guide_info->position.counter_value): 0;
	//PRINTF_DEBUG ? printf("\nCurrent Pos = %ld\n", p_guide_info->step_tracker.total_steps): 0;
	
	return;
}

void check_tmc2209_move_done(Motor_Info_t *motor_info)
{
	
	return;
}

void tmc2209_set_velocity(uint16_t icID, Motor_Info_t *motor_info, int32_t velocity)
{
	// Set the direction of motion according the velocity given.
	if( velocity > 0 ) 
	{ 
		motor_info->flags.direction = COUNT_UP; 
		PRINTF_DEBUG?printf("\nVelocity > 0 | Count UP + 1\n"):0;
	}
	else if( velocity < 0 ) 
	{ 
		motor_info->flags.direction = COUNT_DOWN; 
		PRINTF_DEBUG?printf("\nVelocity < 0 | Count DOWN - 1\n"):0;
	}
	
	tmc2209_writeRegister(icID, TMC2209_VACTUAL, velocity);
	
	return;
}

