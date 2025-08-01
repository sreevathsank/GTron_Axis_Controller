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
		case Z_AXIS: PRINTF_DEBUG ? printf("\nAxC - Z Axis\n"): 0; break;
		case GTRON_AXC_TOP: PRINTF_DEBUG ? printf("\nAxC - GTron TOP\n"): 0; break;
		case GTRON_AXC_BOT: PRINTF_DEBUG ? printf("\nAxC - GTron BOTTOM\n"): 0; break;
		default: break;
	}
	led_Blink(2, 100);
	run_Open_Loop_Setup_Closed_Loop(50);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	
	IOXP_Write_Byte(IOXP_REG_IODIR, 0xAB);
	delay_ms(100);
	uint8_t ioxp_read_byte = 0x00;
	IOXP_Read_Byte(IOXP_REG_IODIR, &ioxp_read_byte);

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
	limit_variables.homing = (repeat_ramp == 0) ? false : true;
	if( (limit_variables.homing == true ) && (repeat_ramp > 0) )
	{
		do_homing_sequence();
	}
	else { limit_variables.switch_seq_flag = false; }	// No need for Switching Sequence if Homing Sequence is disabled...
	
	/* Replace with your application code */
	for ever
	{
		can_Read();
		check_Limit_Flags();
		if(limit_variables.homing)		{ homing_Ramp();			}
		if(check_move_done)				{ check_For_Move_Done();    }
		if(move_given_s_ramp)			{ run_S_ramp();				}
		if( (repeat_ramp != 2) && (vel_struct.knob_enabled || vel_struct.test_enabled) )
		{
			run_Velocity_Mode();
		}
	}
	return 0;
}