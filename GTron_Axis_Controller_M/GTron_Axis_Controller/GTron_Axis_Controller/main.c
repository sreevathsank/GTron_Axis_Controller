// For Axis Controller V1R1

// UART baud rate - 2000000.

// SPI Lite with Flash working. ok

#include <atmel_start.h>
#include "All_Headers.h"
#include "Bring_Up/CAN/IMM_CAN_Read.h"

int main(void)
{
	atmel_start_init();
	SYSTICK_INIT();
	
	pwm_set_parameters(&PWM_0, 1, 1);
	pwm_enable(&PWM_0);
	
	reset_TMC4671();
	gpio_set_pin_level(EN_4671, LOW);
	
	define_All_Global_Variables();
	call_All_Init_Functions();
	switch(axis_id)
	{
		case X_AXIS: PRINTF_DEBUG ? printf("\nAxC - X Axis\n"): 0; break;
		case GTRON_AXC_TOP: PRINTF_DEBUG ? printf("\nAxC - GTron TOP\n"): 0; break;
		case GTRON_AXC_BOT: PRINTF_DEBUG ? printf("\nAxC - GTron BOTTOM\n"): 0; break;
		default: break;
	}
	led_Blink(2, 100);
	run_Open_Loop_Setup_Closed_Loop(50);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	
	//PRINTF_DEBUG && printf("\nWriting to TMC2209 GCONF register\n");
	//tmc2209_writeRegister(0x00, TMC2209_GCONF, 0x60);
	//delay_ms(100);
	//int32_t gconf_value = tmc2209_readRegister(0x00, TMC2209_GCONF);
	//PRINTF_DEBUG && printf("\nGCONF value = %ld\n", gconf_value);
	
	/**
	 * To make the board ready for iMM Software, set repeat_ramp to 0.
	 * To enable homing and endurance run, initialize variable repeat_ramp value to 2.
	 * To enable only homing, set the repeat_ramp to 4.
	 *vvvvvvvvv*/
	repeat_ramp = read_tlv_flash(tlv_ptr, REPEAT_RAMP_FLASH, tlv_traversal);
	switch(repeat_ramp)
	{
		case 0:
			PRINTF_DEBUG && printf("\nrepeat_ramp = 0 | No Endurance Run | No Homing\n");
		break;
		case 2:
			PRINTF_DEBUG && printf("\nrepeat_ramp = 2 | Endurance Run | Homing\n");
		break;
		case 4:
			PRINTF_DEBUG && printf("\nrepeat_ramp = 4 | No Endurance Run | Homing\n");
		break;
		default: break;
	}
	if(axis_params.rotary_axis_enabled)
	{
		switch(axis_id)
		{
			case X_AXIS: PRINTF_DEBUG && printf("\nX Rotary Axis Enabled!\n"); break;
			case Y_AXIS: PRINTF_DEBUG && printf("\nY Rotary Axis Enabled!\n"); break;
			case Z_AXIS: PRINTF_DEBUG && printf("\nZ Rotary Axis Enabled!\n"); break;
			case RF_AXIS: PRINTF_DEBUG && printf("\nRF Rotary Axis Enabled!\n"); break;
			default: break;
		}
	}
	// Enable Homing Flag if RF is enabled for X, Y or Z axis or repeat_ramp is greater than 0.
	limit_variables.homing = ( (repeat_ramp > 0) || (axis_params.rotary_axis_enabled) ) ? true : false;
	
	// Check whether to do firmware limit based homing.
	if( limit_variables.homing )
	{
		do_homing_sequence();
		if(axis_params.rotary_axis_enabled)
		{
			limit_variables.rot_enc_z_first_hit = false;
			ext_irq_enable(ROTENC_Z);
		}
	}
	else { limit_variables.switch_seq_flag = false; }	// No need for Switching Sequence if Homing Sequence is disabled...
	do_Ref_Search_Ping();
	
	/* Replace with your application code */
	for ever
	{
		can_Read();
		check_Limit_Flags();
		if(limit_variables.homing)		{ homing_Ramp();			}
		if(check_move_done)				{ check_For_Move_Done();    }
		if(move_given_s_ramp)			{ run_S_ramp();				}
		if( (repeat_ramp != 2) && vel_struct.flags.reeler_rotate \
			&& vel_struct.flags.reeler_vel_timer && vel_struct.flags.sag_enabled)
		{
			run_Velocity_Ramp();
		}
	}
	return 0;
}