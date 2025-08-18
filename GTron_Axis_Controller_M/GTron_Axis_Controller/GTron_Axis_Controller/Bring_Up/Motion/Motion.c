/*
 * Motion.c
 *
 * Created: 16-12-2023 12:30:46
 *  Author: sreevathsank
 */ 

/** 
 * \file
 *
 * \brief Contains functions to initialise the TMC4671 registers to drive the motor, manage limits and generate ramp.
 */

#include "Bring_Up/Motion/Motion.h"

int32_t open_loop_velocity;

/**  
 * \brief Initialises the registers for the motor to be ready to run in Closed Loop Position Mode. 
 * 
 * @param[in] motor
 * @return void
 */
void init_PosMode(uint8_t motor)
{	//Set registers needed for position mode
	//tmc4671_writeInt(motor, TMC4671_VELOCITY_SELECTION, TMC4671_VELOCITY_PHI_M_ABN);
	tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_TARGET_DDT_LIMITS, 32767);  //max
	tmc4671_writeInt(motor, TMC4671_PIDOUT_UQ_UD_LIMITS, 32767); 			    //max
	tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, axis_params.torque_flux_limit);
	tmc4671_writeInt(motor, TMC4671_PID_ACCELERATION_LIMIT, 0x00000032);
	tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_LIMIT, ZERO_HEX);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_LIMIT_LOW, 0x80000001);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_LIMIT_HIGH, 0x7FFFFFFF);
	tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, 0x00000003);			  			//phi_e_abn
	tmc4671_writeInt(motor, TMC4671_VELOCITY_SELECTION, TMC4671_VELOCITY_PHI_M_ABN);
	tmc4671_writeInt(motor, TMC4671_POSITION_SELECTION, TMC4671_POSITION_PHI_M_ABN);	//phi_m_abn
	//tmc4671_writeInt(motor, TMC4671_MODE_RAMP_MODE_MOTION, POSITION_MODE);		  			//position mode
	//tmc4671_writeInt(MOTOR, TMC4671_PHI_E_SELECTION, 0x00000003);
	//The following gain-values were determined using the USB-2-RTMI and following the PI-tuning guide
	//tmc4671_setTorqueFluxPI(motor, TORQUE_FLUX_P, TORQUE_FLUX_I); //(motor, P, I)
	tmc4671_setTorquePI(motor, axis_params.torque_p, axis_params.torque_i);
	tmc4671_setFluxPI(motor, axis_params.flux_p, axis_params.flux_i);
	tmc4671_setVelocityPI(motor, axis_params.velocity_p, axis_params.velocity_i);
	tmc4671_setPositionPI(motor, axis_params.position_p, axis_params.position_i);
}

/** 
 * \brief Initializes the registers for the motor to run in open loop.
 *
 * @param[in] motor
 * @return void
 */
void init_Basics(uint8_t motor)
{
		//Configure basic registers like motor type, adc-offset
		tmc4671_writeInt(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, 0x00020032); //x0002 - Stepper, x0032 = 50 polepairs
		tmc4671_writeInt(motor, TMC4671_PWM_POLARITIES, 0x00000000);
		tmc4671_writeInt(motor, TMC4671_PWM_MAXCNT, 0x00000F9F); 			  //Maxcount of PWM-counter
		tmc4671_writeInt(motor, TMC4671_PWM_BBM_H_BBM_L, 0x00001919); 		  //Break before make times
		tmc4671_writeInt(motor, TMC4671_PWM_SV_CHOP, 0x00000007);			  //turn on PWM

		// FOC board ADC configuration
		tmc4671_writeInt(0, TMC4671_ADC_I_SELECT, 0x18000100);
		tmc4671_writeInt(0, TMC4671_dsADC_MCFG_B_MCFG_A, 0x00100010);
		tmc4671_writeInt(0, TMC4671_dsADC_MCLK_A, 0x20000000);
		tmc4671_writeInt(0, TMC4671_dsADC_MCLK_B, 0x20000000);
		tmc4671_writeInt(0, TMC4671_dsADC_MDEC_B_MDEC_A, 0x014E014E);
		tmc4671_writeInt(0, TMC4671_ADC_I0_SCALE_OFFSET, 0x00418197);
		tmc4671_writeInt(0, TMC4671_ADC_I1_SCALE_OFFSET, 0x004181C5);


		// Open loop settings
		tmc4671_writeInt(motor, TMC4671_OPENLOOP_MODE, 0x00000000);
		tmc4671_writeInt(motor, TMC4671_OPENLOOP_ACCELERATION, 0x00000000);
		tmc4671_writeInt(motor, TMC4671_OPENLOOP_VELOCITY_TARGET, 0x00000000);
		tmc4671_writeInt(motor, TMC4671_OPENLOOP_PHI, 0x00000000);

		// Feedback selection
		tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, 0x00000002);
		tmc4671_writeInt(motor, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000008);
		// Init encoder (mode 0)
		tmc4671_writeInt(0, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, 0x00000000);
		tmc4671_writeInt(0, TMC4671_PHI_E_SELECTION, 0x00000001);
		tmc4671_writeInt(0, TMC4671_PHI_E_EXT, 0x00000000);
		tmc4671_writeInt(0, TMC4671_UQ_UD_EXT, 0x00000FA0);
		delay_ms(1000);

		//if(axis_id == Z_AXIS) { tmc4671_writeInt(0, TMC4671_ABN_DECODER_MODE, 0x00001000); }		// Rotary Encoder Direction Change.
		
		//int32_t rot_enc_res = read_tlv_flash(tlv_ptr, ROTARY_ENCODER_PPR_FLASH, tlv_traversal);
		//tmc4671_writeInt(motor, TMC4671_ABN_DECODER_PPR, rot_enc_res); // 0x2000 -> 8192 | 0x4000 -> 16384	// For v3 Table.

		//Set Limits
		tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_TARGET_DDT_LIMITS, 0x7FFF); //max
		tmc4671_writeInt(motor, TMC4671_PIDOUT_UQ_UD_LIMITS, 32767); 			    //max
		tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, axis_params.torque_flux_limit);
		//tmc4671_writeInt(motor, TMC4671_PID_ACCELERATION_LIMIT, 214);7483647);
		tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_LIMIT, ZERO_HEX);
		tmc4671_writeInt(motor, TMC4671_PID_POSITION_LIMIT_LOW, 0x80000001);
		tmc4671_writeInt(motor, TMC4671_PID_POSITION_LIMIT_HIGH, 0x7FFFFFFF);
		
		tmc4671_writeInt(MOTOR, TMC4671_PID_ERROR_ADDR, PID_POSITION_ERROR);
	}

/** 
 * \brief Sets all the registers going to be used to 0.
 *
 * @param motor
 * @return void
 */
void reset_Basics(uint8_t motor)
{
	//reset registers of TMC4671 that will later be used to 0
	//delay_ms(1500);
	tmc4671_writeInt(motor, TMC4671_PWM_SV_CHOP, 0);
	tmc4671_writeInt(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, 0);
	tmc4671_writeInt(motor, TMC4671_PWM_POLARITIES, 0);
	tmc4671_writeInt(motor, TMC4671_PWM_MAXCNT, 0);
	tmc4671_writeInt(motor, TMC4671_PWM_BBM_H_BBM_L, 0);

	tmc4671_writeInt(motor, TMC4671_ADC_I_SELECT, 0);
	tmc4671_writeInt(motor, TMC4671_dsADC_MCFG_B_MCFG_A, 0);
	tmc4671_writeInt(motor, TMC4671_dsADC_MCLK_A, 0);
	tmc4671_writeInt(motor, TMC4671_dsADC_MCLK_B, 0);
	tmc4671_writeInt(motor, TMC4671_dsADC_MDEC_B_MDEC_A, 0);
	tmc4671_writeInt(motor, TMC4671_ADC_I0_SCALE_OFFSET, 0);
	tmc4671_writeInt(motor, TMC4671_ADC_I1_SCALE_OFFSET, 0);

	tmc4671_writeInt(motor, TMC4671_OPENLOOP_MODE, 0);
	tmc4671_writeInt(motor, TMC4671_OPENLOOP_ACCELERATION, 0);
	tmc4671_writeInt(motor, TMC4671_OPENLOOP_VELOCITY_TARGET, 0);
	tmc4671_writeInt(motor, TMC4671_OPENLOOP_PHI, ZERO_HEX);

	tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, 0);
	tmc4671_writeInt(motor, TMC4671_MODE_RAMP_MODE_MOTION, 0);
	tmc4671_writeInt(motor, TMC4671_UQ_UD_EXT, 0);
	tmc4671_writeInt(motor, TMC4671_ABN_DECODER_PPR, 0);
	tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_COUNT, 0x00000000);

	tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_TARGET_DDT_LIMITS, 0);
	tmc4671_writeInt(motor, TMC4671_PIDOUT_UQ_UD_LIMITS, 0);
	tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, 0);
	tmc4671_writeInt(motor, TMC4671_PID_ACCELERATION_LIMIT, 0);
	tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_TARGET, 0);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_LIMIT_LOW, 0);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_LIMIT_HIGH, 0);
	tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, 0);
	tmc4671_writeInt(motor, TMC4671_VELOCITY_SELECTION, 0);
	tmc4671_writeInt(motor, TMC4671_POSITION_SELECTION, 0);
	tmc4671_writeInt(motor, TMC4671_MODE_RAMP_MODE_MOTION, 0);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_TARGET, 0);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_ACTUAL, 0);
	tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_LIMIT, 0);
	tmc4671_setTorqueFluxPI(motor, 0, 0); //(motor, P, I)
	tmc4671_setVelocityPI(motor, 0, 0); // (motor, P, I)
	tmc4671_setPositionPI(motor, 0, 0); // (motor, P, I)

}

/** 
 * \brief Aligns the Rotary Encoder to the 0 of the mechanical angle of the motor.
 *
 * @param void
 * @return void
 */
void align_Rotor_ABNEnc(uint8_t motor, uint16_t startVoltage)
{
	delay_ms(axis_params.align_delay);
	// set ABN_DECODER_PHI_E_OFFSET to zero
	tmc4671_writeRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, 0);
	// select phi_e_ext
	tmc4671_writeRegister16BitValue(motor, TMC4671_PHI_E_SELECTION, BIT_0_TO_15, 1);
	// set an initialization voltage on UD_EXT (to the flux, not the torque!)
	tmc4671_writeRegister16BitValue(motor, TMC4671_UQ_UD_EXT, BIT_16_TO_31, 0);
	tmc4671_writeRegister16BitValue(motor, TMC4671_UQ_UD_EXT, BIT_0_TO_15, startVoltage);
	
	// set the "zero" angle
	tmc4671_writeRegister16BitValue(motor, TMC4671_PHI_E_EXT, BIT_0_TO_15, 0);
	delay_ms(500);
	
	axis_params.rot_enc_res = read_tlv_flash(tlv_ptr, ROTARY_ENCODER_PPR_FLASH, tlv_traversal);
	int32_t rot_enc_dir = (read_tlv_flash(tlv_ptr, ROTARY_ENCODER_DIRECTION_FLASH, tlv_traversal) == 0) ? ABN_ENC_REVERSE_DIRECTION : ABN_ENC_FORWARD_DIRECTION;
	axis_params.lin_enc_res = read_tlv_flash(tlv_ptr, LINEAR_ENCODER_CPR_FLASH, tlv_traversal);
	int32_t linear_enc_dir = (read_tlv_flash(tlv_ptr, LINEAR_ENCODER_DIRECTION_FLASH, tlv_traversal) == 0) ? ABN_ENC_REVERSE_DIRECTION : ABN_ENC_FORWARD_DIRECTION;
	switch(axis_id)
	{
		case X_AXIS:
			tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_MODE, rot_enc_dir);		// For v3 Table. v5 -> forward. | Proto1 -> Reverse |
			tmc4671_writeInt(motor, TMC4671_ABN_DECODER_PPR, axis_params.rot_enc_res);		// 0x2000 -> 8192 | 0x4000 -> 16384	// For v3 Table.
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_MODE, linear_enc_dir);		// For v3 Table. v5 -> forward. 
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_PPR, axis_params.lin_enc_res);
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT, ZERO_HEX);
		break;
		case Y_AXIS:
			tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_MODE, rot_enc_dir);		// For v3 Table. v5 -> forward. | Proto1 -> Reverse |
			tmc4671_writeInt(motor, TMC4671_ABN_DECODER_PPR, axis_params.rot_enc_res);		// 0x2000 -> 8192 | 0x4000 -> 16384	// For v3 Table.
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_MODE, linear_enc_dir);		// For v3 Table. v5 -> forward.
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_PPR, axis_params.lin_enc_res);
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT, ZERO_HEX);
		break;
		case Z_AXIS:
			tmc4671_writeInt(motor, TMC4671_ABN_DECODER_PPR, axis_params.rot_enc_res);		// 0x2000 -> 8192 | 0x4000 -> 16384	// For v3 Table.
			tmc4671_writeInt(motor, TMC4671_ABN_DECODER_MODE, rot_enc_dir);		// Spring Setup -> Reverse | Proto1 9030 -> Reverse | Proto2 9010 -> Forward | Proto3 9010 -> Forward | Prod 1 9010 -> 
		break;
		case GTRON_AXC_TOP:
			tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_MODE, rot_enc_dir);		// For v3 Table. v5 -> forward. | Proto1 -> Reverse |
			tmc4671_writeInt(motor, TMC4671_ABN_DECODER_PPR, axis_params.rot_enc_res);		// 0x2000 -> 8192 | 0x4000 -> 16384	// For v3 Table.
		break;
		default: break;
	}
	//After the rotor has aligned this will set the ABN_DECODER_COUNT to 0 so there is a defined 0-position
	tmc4671_writeInt(motor, TMC4671_ABN_DECODER_COUNT, 0);
	
	//doEncoderDirectionCheck();
	//Set PHI_E to 0° angle so the rotor aligns itself with it
	tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, 0x00000000);
	delay_ms(500);
	tmc4671_readRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31);
}

/** 
 * \brief Runs the motor in open loop for the given acceleration, velocity and current limit.
 *
 * @param void
 * @return void
 */
void open_loop_fb(void)
{
	// Open loop settings
	tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000008);
	tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_MODE, 0x00000000);
	tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_ACCELERATION, open_loop.acceleration);
	tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_VELOCITY_TARGET, open_loop.velocity);

	// Feedback selection
	tmc4671_writeInt(MOTOR, TMC4671_UQ_UD_EXT, open_loop.uq_ud);
	tmc4671_writeInt(MOTOR, TMC4671_PHI_E_SELECTION, 0x00000002);
	
	//gpio_set_pin_level(EN, 1);
	return;
}

/** 
 * \brief Does the Switching Sequence to find the exact position of the Home Limit.
 *
 * @param[in] switching_distance Distance to move away from the Zero Limit Position.
 * @return void
 */
void homing_Switching_Sequence(int32_t switching_distance)
{
	
}

/** 
 * \brief Does the Homing Sequence.
 *
 * @param void
 * @return void
 */
void do_homing_sequence( void )
{
	gpio_set_pin_level(EN_4671, HIGH);
 	tmc4671_setModeMotion(MOTOR, POSITION_MODE);
	
	(motor_dir_rev) ? tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_LOW) : tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_HIGH);
	
	// If RF is enabled for the current axis, return from the function, else continue with limit based homing.
	if(axis_params.rotary_axis_enabled)
	{
		homing_v = 0;
		tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, STOPPED_MODE);
		tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
		
		limit_variables.other_limit_hit = false;
		limit_variables.left_limit_position  = 0;
		limit_variables.right_limit_position = 0;
		
		tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_LOW);
		tmc4671_setModeMotion(MOTOR, POSITION_MODE);
		return;
	}
	
 	limit_variables.other_limit_hit = false;
	
	return;
}

void left_limit_high()
{
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	//vel_struct.test_enabled = false;
	vel_struct.flags.reeler_rotate = false;
	return;
}

/** 
 *	Stops motor when right reference switch goes HIGH
 *
 * @parameter Nil
 *
 * @return void
 **/
void right_limit_high()
{	
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	//vel_struct.test_enabled = false;
	vel_struct.flags.reeler_rotate = false;
	return;
}

void right_limit_homing()
{
	homing_v = 0;
	#if CLOSEDLOOP
		// Check if the other limit was hit
		if(true == limit_variables.other_limit_hit)
		{
			limit_variables.other_limit_hit = false;
			//tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, STOPPED_MODE);
			tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
			delay_ms(LIMIT_DELAY);
			
			// Setting the position values for Right and Left limits.
			limit_variables.right_limit_position = 0;
			limit_variables.left_limit_position  = abs( tmc4671_getActualPosition(MOTOR) );
			limit_variables.zero_limit_position  = limit_variables.right_limit_position;
			limit_variables.other_limit_position = limit_variables.left_limit_position; 
			
			tmc4671_setActualPosition(MOTOR, ZERO_HEX);
			tmc4671_setAbsolutTargetPosition(MOTOR, ZERO_HEX);
			
			tmc4671_setActualPosition(MOTOR, ZERO_HEX);
			tmc4671_setAbsolutTargetPosition(MOTOR, ZERO_HEX);
			tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, POSITION_MODE);
			
			//tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_COUNT, ZERO_HEX);
			// Set the Linear Encoder PPR and Rotary and Linear Encoder counts in TMC4671 to 0.
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT, ZERO_HEX);
			
			if(repeat_ramp == 2) 
			{ 
				timer_start(&TIMER_0);
				//ramp_State = DO_NOTHING;	 
				s_curve_phase = DO_REPEAT;
			}
			limit_variables.homing = false;
			move_given_s_ramp = false;
			move_given_trapezoidal_ramp = false;
			
			if(axis_id == X_AXIS) { do_Ref_Search_Ping(); }
			
			// Setting SoftLimits.
			int32_t start_range = ( read_tlv_flash(tlv_ptr, START_RANGE_FLASH, tlv_traversal) * TMC4671_ONE_MM_STEPS);
			int32_t end_range = ( read_tlv_flash(tlv_ptr, END_RANGE_FLASH, tlv_traversal) * TMC4671_ONE_MM_STEPS);
			if(motor_dir_rev)
			{
				start_range = ( (~(int32_t)start_range) + 1);
				end_range = ( (~(int32_t)end_range) + 1 );
				
				limit_variables.soft_limit_high = end_range   + SOFT_LIMIT_OFFSET_MM;
				limit_variables.soft_limit_low  = start_range - SOFT_LIMIT_OFFSET_MM;
			}
			else
			{
				limit_variables.soft_limit_high = end_range   - SOFT_LIMIT_OFFSET_MM;
				limit_variables.soft_limit_low  = start_range + SOFT_LIMIT_OFFSET_MM;
			}
			PRINTF_DEBUG && printf("\nLeft Limit Pos = %ld usteps | %.2f mm\tRight Limit Pos = %ld usteps | %.2f mm\n", limit_variables.left_limit_position, (limit_variables.left_limit_position / TMC4671_ONE_MM_STEPS),limit_variables.right_limit_position, (limit_variables.right_limit_position / TMC4671_ONE_MM_STEPS));
			PRINTF_DEBUG && printf("\nSoft Limit High = %ld usteps| %.2f mm\tSoft Limit Low = %ld usteps | %.2f mm\n", limit_variables.soft_limit_high, (limit_variables.soft_limit_high / TMC4671_ONE_MM_STEPS), limit_variables.soft_limit_low, (limit_variables.soft_limit_low / TMC4671_ONE_MM_STEPS) );
			return;
		}
		else
		{
			limit_variables.other_limit_hit = true;
			//tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, STOPPED_MODE);
			tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
			tmc4671_setActualPosition(MOTOR, ZERO_HEX);
			debounce_delay(LIMIT_DELAY);
			limit_variables.left_limit_position  = 0;
			limit_variables.right_limit_position = 0;
			switch(axis_id)
			{
				case X_AXIS:
				case Y_AXIS:
					//move_With_Trapezoidal_Ramp(POSITION_LOW, axis_params.home_search_vel);
					tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_HIGH);
					tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				break;
				case Z_AXIS:
					//move_With_Trapezoidal_Ramp(POSITION_HIGH, axis_params.home_search_vel);
					(motor_dir_rev) ? tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_HIGH) : tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_LOW);
					tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				break;
				default: break;
			}
			return;
		}
	#endif
	#if OPENLOOP
		tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, UQ_UD_MODE);
		int32_t temp_velocity = open_loop.velocity;
		open_loop.acceleration = 0;
		open_loop.velocity = 0;
		open_loop.uq_ud = 0;
		open_loop_fb();
		open_loop.acceleration = 0x320;
		open_loop.velocity = 1 * 0xc8;
		open_loop.uq_ud = 0x2770;
		open_loop_fb();
	#endif
	return;
}

void left_limit_homing()
{
	homing_v = 0;
	#if CLOSEDLOOP
		// Check if the other limit was already hit first.
		if(true == limit_variables.other_limit_hit)
		{
			if( (axis_id == X_AXIS) && (rfs_ping_rxvd == false) ) 
			{ 
				//rfs_ping_rxvd = false;
				do_Ref_Search_Ping(); 
			}
			limit_variables.other_limit_hit = false;
			tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
			delay_ms(LIMIT_DELAY);
			
			// Setting the position values for Right and Left Limits.
			limit_variables.right_limit_position = abs( tmc4671_getActualPosition(MOTOR) );
			limit_variables.left_limit_position  = 0;
			limit_variables.zero_limit_position  = limit_variables.left_limit_position;
			limit_variables.other_limit_position = limit_variables.right_limit_position;
			
			tmc4671_setActualPosition(MOTOR, ZERO_HEX);
			tmc4671_setAbsolutTargetPosition(MOTOR, ZERO_HEX);

			limit_variables.homing = false;
			move_given_s_ramp = false;
			move_given_trapezoidal_ramp = false;
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT, ZERO_HEX);
			if(repeat_ramp == 2)
			{
				timer_start(&TIMER_0);
				s_curve_phase = DO_REPEAT;
			}
			// Setting SoftLimits.
			int32_t start_range = ( read_tlv_flash(tlv_ptr, START_RANGE_FLASH, tlv_traversal) * TMC4671_ONE_MM_STEPS);
			int32_t end_range = ( read_tlv_flash(tlv_ptr, END_RANGE_FLASH, tlv_traversal) * TMC4671_ONE_MM_STEPS);
			if(motor_dir_rev)
			{
				start_range = ( (~(int32_t)start_range) + 1);
				end_range = ( (~(int32_t)end_range) + 1 );
			
				limit_variables.soft_limit_high = end_range   + SOFT_LIMIT_OFFSET_MM;
				limit_variables.soft_limit_low  = start_range - SOFT_LIMIT_OFFSET_MM;
			}
			else
			{
				limit_variables.soft_limit_high = end_range   - SOFT_LIMIT_OFFSET_MM;
				limit_variables.soft_limit_low  = start_range + SOFT_LIMIT_OFFSET_MM;
			}
			PRINTF_DEBUG && printf("\nLeft Limit Pos = %ld usteps | %.2f mm\tRight Limit Pos = %ld usteps | %.2f mm\n", limit_variables.left_limit_position, (limit_variables.left_limit_position / TMC4671_ONE_MM_STEPS),limit_variables.right_limit_position, (limit_variables.right_limit_position / TMC4671_ONE_MM_STEPS));
			PRINTF_DEBUG && printf("\nSoft Limit High = %ld usteps| %.2f mm\tSoft Limit Low = %ld usteps | %.2f mm\n", limit_variables.soft_limit_high, (limit_variables.soft_limit_high / TMC4671_ONE_MM_STEPS), limit_variables.soft_limit_low, (limit_variables.soft_limit_low / TMC4671_ONE_MM_STEPS) );
			return;
		}
		// If this limit is getting hit the first.
		else
		{
			limit_variables.other_limit_hit = true;
			tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
			tmc4671_setActualPosition(MOTOR, ZERO_HEX);
			debounce_delay(LIMIT_DELAY);
			limit_variables.left_limit_position  = 0;
			limit_variables.right_limit_position = 0;
			switch(axis_id)
			{
				case X_AXIS:
				case Y_AXIS:
					tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_LOW);
					tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				break;
				case Z_AXIS:
					tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_HIGH);
					tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				break;
				default: break;
			}
			return;
		}
	#endif
	#if OPENLOOP
		tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, UQ_UD_MODE);
		int32_t temp_velocity = open_loop.velocity;
		open_loop.acceleration = 0;
		open_loop.velocity = 0;
		open_loop.uq_ud = 0;
		open_loop_fb();
		//delay_ms(10);
		open_loop.acceleration = 0x320;
		//open_loop.velocity = -1 * temp_velocity;
		open_loop.velocity = -1 * 0xc8;
		open_loop.uq_ud = 0x2770;
		open_loop_fb();
	#endif
	return;
}

void toggle_Limit_Led(void)
{
	int32_t left_limit_state = gpio_get_pin_level(LIM_LFT) , right_limit_state = gpio_get_pin_level(LIM_RT);
	//if(false == limit_variables.right_limit_flag)
	{
		#if LIMIT_SWITCH_RISING
			gpio_set_pin_level(DBGLED1, left_limit_state);
		#elif LIMIT_SWITCH_FALLING
			gpio_set_pin_level(DBGLED1, !left_limit_state);
		#endif
	}
	//if(false == limit_variables.left_limit_position)
	{
		#if LIMIT_SWITCH_RISING
			gpio_set_pin_level(DBGLED2, right_limit_state);
		#elif LIMIT_SWITCH_FALLING
			gpio_set_pin_level(DBGLED2, !right_limit_state);
		#endif	
	}
	return;
}

/** 
 * \brief Checks the limit flags and if they were hit or not and toggles respective LEDs
 *
 * @param void 
 * @return void 
 */
void check_Limit_Flags(void)
{
	if( ( (axis_id == GTRON_AXC_TOP) || (axis_id == GTRON_AXC_BOT) ) && gtron_limits.interrupt_raised )
	{
		gtron_limits.interrupt_raised = false;
		
		for(int8_t i = 7; i >= 0; i--) { PRINTF_DEBUG ? printf(" Bit %d = %d | ", i, (gtron_limits.limit_flags >> i) & 1 ): 0; }
			
		PRINTF_DEBUG ? printf("\n"): 0;
		if( MSK_GUIDE_R_LIM(gtron_limits.limit_flags) )	// Guide Right Open Limit.
		{
			if(p_guide_info->flags.move_to_open_lim)
			{
				p_guide_info->flags.move_to_open_lim = false;
				tmc2209_set_velocity(TMC2209_GUIDE_ADDR, 0x00000000, GUIDE_STEP_COUNTER);
				
				// Write to the Guide Step Counter TCC Counter Register as 0.
				counter_Write_Count_Val(GUIDE_STEP_COUNTER, 0);
				p_guide_info->right_open_lim_pos = counter_Read_Count_Val(GUIDE_STEP_COUNTER);	
				PRINTF_DEBUG ? printf("\nMove to Open Limit Done. Setting Current Position as %ld...\n", p_guide_info->right_open_lim_pos): 0;
			}
			PRINTF_DEBUG ? printf("\nGuide Right Open Limit is Hit!\n"): 0;
		}
		else if( MSK_GUIDE_L_LIM(gtron_limits.limit_flags) )	// Guide Left Close Limit.
		{
			if(p_guide_info->flags.move_to_close_lim)
			{
				p_guide_info->flags.move_to_close_lim = false;
				tmc2209_set_velocity(TMC2209_GUIDE_ADDR, 0x00000000, GUIDE_STEP_COUNTER);
				
				// Get the current position as the stroke length of the Guide setup.
				p_guide_info->left_close_lim_pos = counter_Read_Count_Val(GUIDE_STEP_COUNTER);
				PRINTF_DEBUG ? printf("\nMove to Close Limit Done. Setting Current Position as %ld...\n", p_guide_info->left_close_lim_pos): 0;
			}
			PRINTF_DEBUG ? printf("\nGuide Left Close Limit is Hit!\n"): 0;
		}
		else if( MSK_VARREST_R_LIM(gtron_limits.limit_flags) )
		{
			PRINTF_DEBUG ? printf("\nVertical Arrestor Right Limit is Hit!\n"): 0;
		}
		else if( MSK_VARREST_L_LIM(gtron_limits.limit_flags) )
		{
			PRINTF_DEBUG ? printf("\nVertical Arrestor Left Limit is Hit!\n"): 0;
		}
	}
	return;
}

/** 
 * \brief Callback function if an edge is detected in the Rotary Encoder's Z Pulse.
 *
 * @param void
 * @return void
 */
void rot_Enc_Z_Pulse_Interrupt_Callback(void)
{
	if(limit_variables.rot_enc_z_first_hit)
	{
		tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
		tmc4671_setVelocityLimit(MOTOR, 0);
		tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_COUNT, ZERO_HEX);
		tmc4671_setActualPosition(MOTOR, ZERO_HEX);
		tmc4671_setAbsolutTargetPosition(MOTOR, ZERO_HEX);
		limit_variables.rot_enc_z_first_hit = false;
		limit_variables.homing = false;
		move_given_s_ramp = false;
		move_given_trapezoidal_ramp = false;
		ext_irq_disable(ROTENC_Z);
	}
	else if(limit_variables.rot_enc_z_first_hit == false)
	{
		tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
		tmc4671_setVelocityLimit(MOTOR, 0);
		move_given_s_ramp = false;
		move_given_trapezoidal_ramp = false;
		int32_t current_position = tmc4671_getActualPosition(MOTOR);
		
		move_With_S_Ramp(0, 30, MOVE_TO);
		
		limit_variables.rot_enc_z_first_hit = false;
		limit_variables.homing = false;
		ext_irq_disable(ROTENC_Z);
		PRINTF_DEBUG ? printf("\nReeler Homing Done\n"): 0;
	}
	
	switch(axis_id)
	{
		case X_AXIS:  printf("\nX | Rotary Encoder Z Pulse Edge Detected\n");  break;
		case Y_AXIS:  printf("\nY | Rotary Encoder Z Pulse Edge Detected\n");  break;
		case Z_AXIS:  printf("\nZ | Rotary Encoder Z Pulse Edge Detected\n");  break;
		case RF_AXIS: printf("\nRF | Rotary Encoder Z Pulse Edge Detected\n"); break;
	}
	return;
}

/** 
 * \brief Callback function if an edge is detected in the Left Limit. Toggles left limit hit flag to true.
 *
 * @param void
 * @return void
 */
void left_Limit_Interrupt_Callback(void)
{
	limit_variables.flags.left_limit_flag = 1;
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	vel_struct.flags.reeler_rotate = false;
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	
	printf("\nLeft Limit HIT!\n");
	
	timer_stop(&TIMER_0);
	return;
}

/** 
 * \brief Callback function if an edge is detected in the Right Limit. Toggles right limit hit flag to true.
 *
 * @param void
 * @return void
 */
void right_Limit_Interrupt_Callback(void)
{
	limit_variables.flags.right_limit_flag = 1;
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	vel_struct.flags.reeler_rotate = false;
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	
	printf("\nRight Limit HIT!\n");
	
	timer_stop(&TIMER_0);
	return;
}

/** 
 * \brief Initialises the external interrupt of Limits to their respective Callback functions.
 *
 * @param void
 * @return void
 */
void init_ext_irq_limits(void)
{
	//ext_irq_register(LIM_LFT, left_Limit_Interrupt_Callback);
	//ext_irq_register(LIM_RT, right_Limit_Interrupt_Callback);
	ext_irq_register(ROTENC_Z, rot_Enc_Z_Pulse_Interrupt_Callback);
	ext_irq_register(IOXP_INT, ioxp_Interrupt_Callback);
	ext_irq_register(INDEX, index_Interrupt_Callback);
	return;
}

void rotEnc_Count_Callback(void)
{
	x_axis_encoder_counters.rot_enc_cnt += x_axis_encoder_counters.direction;
	return;	
}

void rotEnc_Direction_Callback(void)
{
	x_axis_encoder_counters.direction = (gpio_get_pin_level(ROTENC_DIR) == HIGH) ? (1) : (-1);
	return;
}

void init_Enc_Cnt_Dir(void)
{
	ext_irq_register(ROTENC_COUNT, rotEnc_Count_Callback);
	ext_irq_register(ROTENC_DIR, rotEnc_Direction_Callback);
	return;
}

void homing_Ramp(void)
{
	if(homing_v < (axis_params.home_search_vel) )
	{
		homing_v += (HOMING_RAMP_DELTA * 10);
		tmc4671_setVelocityLimit(MOTOR, homing_v);
	}
	return;
}

/** 
 * \brief Generates a trapezoidal ramp by changing velocity with the calculated ramp_Parameters.
 *
 * @param void
 * @return void
 */
void run_Trapezoidal_Ramp(void)
{
	if(rParams.timer_ramp_flag)
	{
		if(tmc4671_getModeMotion(MOTOR) == STOPPED_MODE)
		{
			tmc4671_setModeMotion(MOTOR, POSITION_MODE);
		}
		rParams.timer_ramp_flag = false;
		switch(ramp_State)
		{
			case ACCEL:
				// Check for both decel point and accel  point because in triangular ramp, decel point < accel point
				switch(abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) <= rParams.distance_accel)//(abs(current_position - ramp_Parameters.initial_Position) < ramp_Parameters.distance_decel_point) | (abs(current_position - ramp_Parameters.initial_Position) < ramp_Parameters.distance_accel) )
				{
					case false:									// Acceleration done.
						ramp_State = (rParams.triangular_ramp) ? DECEL : CRUISE;
					break;
					case true:									// In Acceleration phase.
						v_temp += axis_params.acceleration_delta;
						v = v_temp;
						//Added this extra check because sometimes v_temp exceeds VELOCITY_LIMIT
						switch(v <= velocity_limit)
						{
							case true: tmc4671_setVelocityLimit(MOTOR, v); break;
							case false: break;
						}
					break;
				}
			break;
			case CRUISE:
				switch(abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) <= rParams.distance_decel_point)
				{
					case false:
						//timer_struct.interval = 1;
						ramp_State = DECEL;
					break;
					case true:												// Cruise with the given velocity limit.
						tmc4671_setVelocityLimit(MOTOR, velocity_limit);
					break;
				}
			break;
			case DECEL:
				switch( abs(tmc4671_getErrorPosition(MOTOR)) <= PID_POSITION_WINDOW )
				{
					case false:			// Motor yet to reach within the Position Error Window.
						if(v_temp > (velocity_limit / 10) && (v_temp > 10) ) { v_temp -= axis_params.acceleration_delta; }	// Decrement velocity till velocity_limit/10 instead of to 0.
						else if(v_temp < (velocity_limit / 10) && (v_temp > 10) ) { v_temp -= (axis_params.acceleration_delta / 10);  }
						else if(v_temp < (velocity_limit / 12) && (v_temp > 10) ) { v_temp -= (axis_params.acceleration_delta / 12); }
						else if(v_temp < (velocity_limit / 15) && (v_temp > 10) ) { v_temp -= (axis_params.acceleration_delta / 15); }
						else if(v_temp < (velocity_limit / 18) && (v_temp > 10) ) { v_temp -= (axis_params.acceleration_delta / 18); }
						v = v_temp;
						tmc4671_setVelocityLimit(MOTOR, v);
					break;
					case true:			// Motor is within the Position Error Window.
						ramp_State = STOP;
						timer_stop(&TIMER_0);
					break;
				}
			break;
			case DO_NOTHING:
				switch(repeat_ramp)
				{
					case 1:
						delay_ms(500);
						velocity_limit = axis_params.endurance_vel;
						move_With_Trapezoidal_Ramp(TMC4671_MOVE_MM(2), velocity_limit);
						repeat_ramp = 2;
					break;
					case 2:
						delay_ms(500);
						velocity_limit = axis_params.endurance_vel;
						switch(axis_id)
						{
							case X_AXIS: move_With_Trapezoidal_Ramp(TMC4671_MOVE_MM(145), velocity_limit); break;
							case Y_AXIS: move_With_Trapezoidal_Ramp(TMC4671_MOVE_MM(145), velocity_limit); break;
							case Z_AXIS: move_With_Trapezoidal_Ramp(TMC4671_MOVE_MM(70), velocity_limit); break;
							default: break;
						}
						repeat_ramp = 1;
					break;
					default: break;
				}
			break;
		}
	}
	return;
}

/** 
 * \brief S Ramp algorithm.
 *
 * @param void
 * @return void
 */
void run_S_ramp(void)
{		// Remove in Phase 4!
	if(rParams.timer_ramp_flag)
	{
		rParams.timer_ramp_flag = false;
		if(tmc4671_getModeMotion(MOTOR) == STOPPED_MODE) { tmc4671_setModeMotion(MOTOR, POSITION_MODE); }
		int32_t current_position;
		static bool ph7_entered = false;
		current_position = tmc4671_getActualPosition(MOTOR);
		switch(s_curve_phase)
		{
			case PHASE_1:	// Increasing Jerk Phase.
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < rParams.s_p1 )
				{
					case true:					// Yet to reach end of Phase 1.
						if(a_temp <= convert_PPS_To_RPM(rParams.s_a1) ) 
						{ 
							a_temp += axis_params.jerk_delta; 
							v_temp += a_temp; 
						}
						v = v_temp;
						if(v <= convert_PPS_To_RPM(rParams.s_v1) ) { tmc4671_setVelocityLimit(MOTOR, v); }
					break;
					case false:	
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);				// Go to Phase 2.
						rParams.phase_error = ( current_position - rParams.s_p1 );
						v_temp = convert_PPS_To_RPM(rParams.s_v1);
						PRINTF_DEBUG && printf("\nPH1 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p1, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a1), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v1), rParams.phase_error);
						if( (rParams.ramp_case == A) | (rParams.ramp_case == B) | (rParams.ramp_case == C1) | (rParams.ramp_case == C2) )
						{
							s_curve_phase = PHASE_3;
						}
						else if( (rParams.ramp_case == D1) | (rParams.ramp_case == D2) ) { s_curve_phase = PHASE_2; }
					break;
				}
			break;
			case PHASE_2:	// Max +ve Jerk and Constant Acceleration Phase.
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < (rParams.s_p2) )
				{
					case true:
						if(v <= convert_PPS_To_RPM(rParams.s_v2) ) 
						{
							v_temp += a_temp;
							v = v_temp;
							tmc4671_setVelocityLimit(MOTOR, v);
						}
					break;
					case false:
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);
						rParams.phase_error = ( current_position - rParams.s_p2 );
						v_temp = convert_PPS_To_RPM(rParams.s_v2);
						PRINTF_DEBUG && printf("\nPH2 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p2, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a2), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v2), rParams.phase_error);
						s_curve_phase = PHASE_3;
					break;
				}
			break;
			case PHASE_3:	// Decreasing Jerk Phase
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < (rParams.s_p3) )
				{
					case true:
						if(a_temp >= convert_PPS_To_RPM(rParams.s_a3) ) 
						{ 
							a_temp -= (axis_params.jerk_delta ); 
							v_temp += a_temp; 
						}
						v = v_temp;
						if(v <= convert_PPS_To_RPM(rParams.s_v3) ) { tmc4671_setVelocityLimit(MOTOR, v); }
					break;
					case false:
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);
						rParams.phase_error = ( current_position - rParams.s_p3 );
						v_temp = convert_PPS_To_RPM(rParams.s_v3);
						PRINTF_DEBUG && printf("\nPH3 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p3, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a3), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v3), rParams.phase_error);
						a_temp = 0;
						if( (rParams.ramp_case == A) | (rParams.ramp_case == C1) | (rParams.ramp_case == D1) )
						{
							s_curve_phase = PHASE_4;
						}
						else if( (rParams.ramp_case == B) | (rParams.ramp_case == C2) | (rParams.ramp_case == D2)) 
						{ 
							s_curve_phase = PHASE_5; 
						}
					break;
				}
			break;
			case PHASE_4:	// Constant Velocity Phase.
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < (rParams.s_p4) )
				{
					case true:
						a_temp = 0;
						/* Remove This!!!*/
						//velocity_limit = convert_PPS_To_RPM(rParams.s_v4);//axis_params.endurance_vel;			/* Remove This!!!*/
						//tmc4671_setVelocityLimit(MOTOR, velocity_limit);
					break;
					case false:
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);
						rParams.phase_error = ( current_position - rParams.s_p4 );
						v_temp = convert_PPS_To_RPM(rParams.s_v4);
						//v_temp = axis_params.endurance_vel;
						PRINTF_DEBUG && printf("\nPH4 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p4, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a4), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v4), rParams.phase_error);
						s_curve_phase = PHASE_5;
					break;
				}
			break;
			case PHASE_5:	// Increasing Jerk Phase.
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < (rParams.s_p5) )
				{
					case true:
						if(a_temp >= convert_PPS_To_RPM(rParams.s_a5) ) 
						{ 
							a_temp -= ( axis_params.jerk_delta ); 
							v_temp += a_temp; 
						}
						v = v_temp;
						if(v >= convert_PPS_To_RPM(rParams.s_v5) ) { tmc4671_setVelocityLimit(MOTOR, v); }
					break;
					case false:
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);
						rParams.phase_error = ( current_position - rParams.s_p5 );
						v_temp = convert_PPS_To_RPM(rParams.s_v5);
						PRINTF_DEBUG && printf("\nPH5 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p5, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a5), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v5), rParams.phase_error);
						if( (rParams.ramp_case == A) | (rParams.ramp_case == B) | (rParams.ramp_case == C1) | (rParams.ramp_case == C2) )
						{
							s_curve_phase = PHASE_7;
						}
						else if( (rParams.ramp_case == D1) | (rParams.ramp_case == D2) ) { s_curve_phase = PHASE_6; }
					break;
				}
			break;
			case PHASE_6:	// Max -ve Jerk and Constant Acceleration Phase.
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < (rParams.s_p6) )
				{
					case true:
						if(v >= convert_PPS_To_RPM(rParams.s_v6) ) 
						{ 
							v_temp += a_temp;
							v = v_temp;
							tmc4671_setVelocityLimit(MOTOR, v); 
						}
					break;
					case false:
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);
						rParams.phase_error = ( current_position - rParams.s_p6 );
						v_temp = convert_PPS_To_RPM(rParams.s_v6);
						PRINTF_DEBUG && printf("\nPH6 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p6, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a6), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v6), rParams.phase_error);
						s_curve_phase = PHASE_7;
					break;
				}
			break;
			case PHASE_7:	// Constant  Jerk and Acceleration Phase.
				switch( abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position) < (rParams.distance_total) )
				{
					case true:
						if(ph7_entered == false) { PRINTF_DEBUG && printf("\nPH - 7\n"); ph7_entered = true; }
						if(v > 10) 
						{ 
							a_temp += axis_params.jerk_delta; 
							v_temp += a_temp;
							v = v_temp;
							// REMOVE IN PHASE 4.
							tmc4671_setVelocityLimit(MOTOR, v); 
						}
						
					break;
					case false:
						current_position = abs(tmc4671_getActualPosition(MOTOR) - rParams.initial_Position);
						rParams.phase_error = ( current_position - rParams.s_p7 );
						v_temp = convert_PPS_To_RPM(rParams.s_v7);
						PRINTF_DEBUG && printf("\nPH7 %d %.2f a = %.2f %.2f v = %d %.2f err = %d\n", current_position, rParams.s_p7, a_temp * 1000, convert_PPS_To_RPM( rParams.s_a7), tmc4671_getActualVelocity(MOTOR), convert_PPS_To_RPM( rParams.s_v7), rParams.phase_error);
						rParams.phase_error = 0;
						( (repeat_ramp == 2) || (repeat_ramp == 1) ) ? s_curve_phase = DO_REPEAT : timer_stop(&TIMER_0); 
						timer_stop(&TIMER_0);
					break;
				}
			break;
			case DO_REPEAT:
				switch(repeat_ramp)
				{
					case 1:
						delay_ms(ENDURANCE_MOVE_DELAY_MS);
						velocity_limit = axis_params.endurance_vel;
						(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)TMC4671_MOVE_MM(1)) + 1, velocity_limit, MOVE_TO) : \
										move_With_S_Ramp(TMC4671_MOVE_MM(1), velocity_limit, MOVE_TO);
						repeat_ramp = 2;
					break;
					case 2:
						delay_ms(ENDURANCE_MOVE_DELAY_MS);
						velocity_limit = axis_params.endurance_vel;
						switch(axis_id)
						{	// Target Position is set to (max stroke length - 1mm).
							#if V3_TABLE
								case X_AXIS: 
									(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)(limit_variables.other_limit_position - TMC4671_MOVE_MM(3))) + 1, velocity_limit, MOVE_TO) : \
													move_With_S_Ramp((limit_variables.other_limit_position - TMC4671_MOVE_MM(3)), velocity_limit, MOVE_TO);	 
								break;
								case Y_AXIS: 
									(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)(limit_variables.other_limit_position - TMC4671_MOVE_MM(3))) + 1, velocity_limit, MOVE_TO) : \
													move_With_S_Ramp((limit_variables.other_limit_position - TMC4671_MOVE_MM(3)), velocity_limit, MOVE_BY);
								break;
							#else
								case X_AXIS: 
									(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)(limit_variables.other_limit_position - TMC4671_MOVE_MM(5))) + 1, velocity_limit, MOVE_TO) : \
													move_With_S_Ramp((limit_variables.other_limit_position - TMC4671_MOVE_MM(5)), velocity_limit, MOVE_BY);
								break;
								case Y_AXIS: 
									(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)(limit_variables.other_limit_position - TMC4671_MOVE_MM(10))) + 1, velocity_limit, MOVE_TO) : \
													move_With_S_Ramp((limit_variables.other_limit_position - TMC4671_MOVE_MM(10)), velocity_limit, MOVE_BY);
								break;
							#endif
							case Z_AXIS: 
								//move_With_S_Ramp(MOVE_MM(60), velocity_limit, MOVE_TO); 
								(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)(limit_variables.other_limit_position - TMC4671_MOVE_MM(5))) + 1, velocity_limit, MOVE_TO) : \
								move_With_S_Ramp((limit_variables.other_limit_position - TMC4671_MOVE_MM(5)), velocity_limit, MOVE_BY);
							break;
							default: break;
						}
						repeat_ramp = 1;
					break;
					default: break;
				}
			break;
		}
	}
	return;
}

/** 
 * \brief Sets the necessary flags, timer and values to drive the motor (Move To - Absolute Move) to the given Target Position.
 *
 * @param[in] target_position Absolute position to where the motor should drive to.
 * @return void
 */
void move_With_Trapezoidal_Ramp(int32_t target_position, int32_t velocity)
{
	v_temp = 0;								// Used to set the VELOCITY_LIMIT value. Setting it to Zero ensures that during the initial iteration, motor speed starts from Zero.
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setAbsolutTargetPosition(MOTOR, target_position);		// Absolute Only.
	call_all_ramp_params_functions(&rParams);
	tmc4671_setModeMotion(MOTOR, POSITION_MODE);
	ramp_State = ACCEL;
	//tmc4671_setVelocityLimit(MOTOR, HOMING_SEARCH_VELOCITY);
	move_given_trapezoidal_ramp = true;											// For Trapezoidal Ramp.
	if(limit_variables.homing == false) { check_move_done = true; }	// For Move Done. No need of Move Done for homing.
	velocity_limit = velocity;
	timer_start(&TIMER_0);											// By setting the above flags, registers and timer the ramp will automatically start as it is constantly called in the main loop. 
}

/** 
 * \brief Sets the necessary flags, timer and values to drive the motor (Move To - Absolute Move) to the given Target Position.
 *
 * @param[in] target_position Absolute position to where the motor should drive to.
 * @param[out] move_to_by To denote Move To (Absolute) or Move By (Relative) movement. true => Move To | false => Move By.
 * @return void
 */
void move_With_S_Ramp(float target_position, int32_t velocity, bool move_to_by)
{
	v_temp = 0;								// Used to set the VELOCITY_LIMIT value. Setting it to Zero ensures that during the initial iteration, motor speed starts from Zero.
	a_temp = 0;
	tmc4671_setVelocityLimit(MOTOR, 0);
	// If move_to_by is true, do Move To (Absolute) Movement, else do Move By (Relative).
	(move_to_by == true) ? tmc4671_setAbsolutTargetPosition(MOTOR, target_position) : tmc4671_setRelativeTargetPosition(MOTOR, target_position);
	velocity_limit = velocity;		
	calculate_S_Ramp_Parameters(&rParams);
	tmc4671_setModeMotion(MOTOR, POSITION_MODE);
	s_curve_phase = PHASE_1;
	move_given_s_ramp = true;											// For S Ramp.
	if( (limit_variables.homing == false) && (autofocus_variables.temp_move_change == false) ) 
	{ 
		check_move_done = true;					// For Move Done. No need of Move Done for homing.
	}
	timer_stop(&VEL_TIMER);
	timer_start(&TIMER_0);											// By setting the above flags, registers and timer the ramp will automatically start as it is constantly called in the main loop. 
}

/** 
 * \brief Toggles the interrupt pin to the System Controller to execute the Camera-Light Sequence. Used for AutoFocus.
 *
 * @param[in] void
 * @return bool
 */
bool camera_Trigger(void)
{
	//gpio_set_pin_level(INTOUT, 1);
	delay_us(1);
	//gpio_set_pin_level(INTOUT, 0);
	
	autofocus_variables.cam_trigger_count += 1;
	
	return 0;
}

/** 
 * \brief Sends a move done CAN signal to software if the motor position is within the Position Window.
 *
 * @param void
 * @return void
 */
void check_For_Move_Done(void)
{
	// For Move Done.
	if( (abs(tmc4671_getErrorPosition(MOTOR)) <= PID_POSITION_WINDOW) )
	{
		move_done_check_num += 1;
	}
	if( move_done_check_num >= NO_OF_MOVE_DONE_CHECK )
	{
		move_done_check_num = 0;
		move_done_check_num = 0;
		stop_error_position = tmc4671_getErrorPosition(MOTOR);
		check_move_done = false;
		move_given_s_ramp = false;
		move_given_trapezoidal_ramp = false;
		autofocus_variables.both_received = false;
		if(repeat_ramp == 2)
		{
			ramp_State = DO_NOTHING;
			timer_start(&TIMER_0);
			//move_given_trapezoidal_ramp = true;
			move_given_s_ramp = true;
		}
		else { timer_stop(&TIMER_0); }
		reeler_Move_Done();
	}
	return;
}

/** 
 * \brief To check if the motor is moving or not with respect to be current supplied. If current is being supplied and the motor is not moving, the current supply is to be stopped.
 * \brief This function is to be called only when the motor is commanded to move i.e., during homing, Move To and Move By.
 *
 * @param	void
 * @return	void
 */
void check_Motor_Movement(void)
{
	// For Move Done.
	if( abs(tmc4671_getErrorPosition(MOTOR)) <= PID_POSITION_WINDOW )
	{
		stop_error_position = tmc4671_getErrorPosition(MOTOR);
		check_move_done = false;
		
		// If in AF, send Cam Trigger.
		if(autofocus_variables.both_received)
		{
			//camera_Trigger();
			PRINTF_DEBUG && printf("\n-----AF Done - Camera Trigger Count = %ld -----\n", autofocus_variables.cam_trigger_count);
			autofocus_variables.cam_trigger_count = 0;
			idx = 0;
		}
		move_given_trapezoidal_ramp = false;
		//move_given_s_ramp = false;
		autofocus_variables.both_received = false;
		if(repeat_ramp > 0)
		{
			ramp_State = DO_NOTHING;
			timer_start(&TIMER_0);
			move_given_trapezoidal_ramp = true;
		}
		else { timer_stop(&TIMER_0); }
		//if(limit_variables.homing == true)
		{
			reeler_Move_Done();
		}		// Move Done CAN Message.
	}
	
	uint32_t current_limit = tmc4671_readInt(MOTOR, TMC4671_PID_TORQUE_FLUX_LIMITS);
	uint32_t torque_actual = tmc4671_readRegister16BitValue(MOTOR, TMC4671_PID_TORQUE_FLUX_ACTUAL, BIT_16_TO_31);
	// If torque_actual is greater than or equal to current_limit, we should reconfirm for some iterations if the same condition is true.
	if(torque_actual >= current_limit)
	{
		for(int32_t n = 0; n < 10; n++)
		{
			if(torque_actual >= current_limit)
			{
				tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
				tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
				PRINTF_DEBUG ? printf("\n-----STOPPED MOTOR MOVEMENT AS THE MOTOR IS STALLED OR STUCK-----\n") : 0;
				return;
			}
		}
	}
	return;
}

/** 
 * \brief Generates a simple linear slope for the Velocity Target in Velocity Mode.
 *
 * @param	void
 * @return	void
 */
void run_Velocity_Ramp(void)
{
	static float vel = 0;	// Velocity to be set.
	static bool ramping = false;
	static int32_t prev_trig_pos = 0;
	
	vel_struct.flags.reeler_vel_timer = false;
	
	// Check for the NULL pointer.
	if(!p_reeler_info) { return; }
		
	int32_t current_velocity = tmc4671_getVelocityTarget(MOTOR);
	int32_t target_velocity = p_reeler_info->velocity_limit;

	// Check if the Motor's current Mode Motion is in Velocity Mode or not.
	int32_t mode_motion = tmc4671_getModeMotion(MOTOR);
	if(mode_motion != VELOCITY_MODE)
	{
		tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
	}
	if( (abs(prev_trig_pos - tmc4671_getActualPosition(MOTOR)) >= p_reeler_info->trigger_step_size) && (p_reeler_info->trigger_step_size != 0) )
	{
		gpio_set_pin_level(REELER_INT, HIGH);
		delay_us(1);
		gpio_set_pin_level(REELER_INT, LOW);
	}
	if(!ramping)
	{
		vel = current_velocity;
		prev_trig_pos = tmc4671_getActualPosition(MOTOR);
		// This is the velocity limit threshold that cannot be crossed in Position Mode as well as Velocity Mode.
		tmc4671_setVelocityLimit(MOTOR, axis_params.endurance_vel);
		
		ramping = true;
	}
	
	// Return from the current function if the current motor velocity is equal to the Target Velocity.
	if(current_velocity == target_velocity)
	{
		ramping = false;
		timer_stop(&VEL_TIMER);
		return;
	}
	
	// Check if the current motor velocity is greater than or less than the Target Velocity.
	bool is_greater = (current_velocity > target_velocity);
	
	// Depending on the boolean is_greater, increase or decrease the value of vel.
	
	if(is_greater)
	{
		if(vel > target_velocity)
		{
			vel -= axis_params.acceleration_delta;
		}
	}
	else 
	{
		if(vel < target_velocity)
		{
			vel += axis_params.acceleration_delta;
		}	
	}
					   
	tmc4671_setVelocityTarget(MOTOR, (int32_t)vel);
	
	return;
}