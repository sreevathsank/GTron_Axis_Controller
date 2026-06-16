// For Axis Controller V1R1

// DEBUG UART baud rate - 2,000,000.

#include <atmel_start.h>
#include "All_Headers.h"
#include "Bring_Up/CAN/IMM_CAN_Read.h"
#include "Bring_Up/Debug/dbg_transport.h"

int main(void)
{
	atmel_start_init();
	DBG_TransportInit();              // Configure DMA ch0 -> SERCOM7 USART.
	DBG_Init(DBG_TransportGet());     // Wire dbg_print to the transport.
	SYSTICK_INIT();
	can_Init();
	
	// REELER1_GUIDE_REELERADJ1, VARREST_1_2_SOLENOID and REELER2_REELERADJ2_FRONTCAM.
	sbridge_addr = VARREST_1_2_SOLENOID;
	step_count = 0;
	define_All_Global_Variables();
	call_All_Init_Functions();
	DBG_Printf(ERR_LVL_INFO, "AxC dbg_print online @ 2 Mbaud, axis=%d\n", axis_id);
	switch(axis_id) {
		case X_AXIS: DBG_Printf(ERR_LVL_DEBUG, "AxC - X Axis\n");				break;
		case GTRON_AXC_TOP: DBG_Printf(ERR_LVL_DEBUG, "\nAxC - GTron TOP\n");	break;
		case GTRON_AXC_BOT: DBG_Printf(ERR_LVL_DEBUG, "AxC - GTron BOTTOM\n");	break;
		default: break;
	}
	led_Blink(2, 100);
	run_Open_Loop_Setup_Closed_Loop(50);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	
	/**
	 * To make the board ready for iMM Software, set repeat_ramp to 0.
	 * To enable homing and endurance run, initialize variable repeat_ramp value to 2.
	 * To enable only homing, set the repeat_ramp to 4.
	 *vvvvvvvvv*/
	repeat_ramp = read_tlv_flash(tlv_ptr, REPEAT_RAMP_FLASH, tlv_traversal);
	switch(repeat_ramp) {
		case 0: DBG_Printf(ERR_LVL_DEBUG, "repeat_ramp = 0 | No Endurance Run | No Homing\n");	break;
		case 2: DBG_Printf(ERR_LVL_DEBUG, "repeat_ramp = 2 | Endurance Run | Homing\n");		break;
		case 4: DBG_Printf(ERR_LVL_DEBUG, "repeat_ramp = 4 | No Endurance Run | Homing\n");		break;
		default: break;
	}
	if(axis_params.rotary_axis_enabled) {
		switch(axis_id) {
			case X_AXIS:		DBG_Printf(ERR_LVL_DEBUG, "X Rotary Axis Enabled!\n");		break;
			case Y_AXIS:		DBG_Printf(ERR_LVL_DEBUG, "Y Rotary Axis Enabled!\n");		break;
			case Z_AXIS:		DBG_Printf(ERR_LVL_DEBUG, "Z Rotary Axis Enabled!\n");		break;
			case RF_AXIS:		DBG_Printf(ERR_LVL_DEBUG, "RF Rotary Axis Enabled!\n");		break;
			case GTRON_AXC_TOP: DBG_Printf(ERR_LVL_DEBUG, "Reeler Rotary Axis Enabled!\n"); break;
			case GTRON_AXC_BOT: DBG_Printf(ERR_LVL_DEBUG, "Reeler Rotary Axis Enabled!\n"); break;
			default: break;
		}
	}
	
	// Enable Homing Flag if RF is enabled for X, Y or Z axis or repeat_ramp is greater than 0.
	limit_variables.homing = ( repeat_ramp > 0 ) ? true : false;
	if(axis_params.rotary_axis_enabled) { limit_variables.homing = true; }
	// Check whether to do firmware limit based homing.
	if( limit_variables.homing ) {
		if(axis_params.rotary_axis_enabled) {
			limit_variables.rot_enc_z_first_hit = false;
			ext_irq_enable(ROTENC_Z);
		}
		do_homing_sequence();
	}
	else { limit_variables.switch_seq_flag = false; }	// No need for Switching Sequence if Homing Sequence is disabled...
	
	/* Replace with your application code */
	for(;;) {
		// TMC2209 Step Tracker and Move Done.
		//if( p_guide_info->flags.homing || p_guide_info->flags.move_given || \
		//    p_guide_info->flags.move_to_open_lim || p_guide_info->flags.move_to_close_lim \
		//	&& !gtron_limits.interrupt_raised )
		//								{ update_TMC2209_Step_Tracking(p_guide_info);	}
		if(is_tmc2209_mot_moving) {
			check_Which_2209_Motor_Moving();
		}
		
		if(gtron_limits.interrupt_raised) {
			check_Limit_Flags();
		}
		
		// TMC2209 DIAG pin interrupt raised.
		if(tmc2209_diag_flag) {
			
		}
		// For checking if the Motor has reached its target position TMC4671.
		if(check_move_done)				{ check_For_Move_Done();						}
		
		// For Generating S Ramp profile for TMC4671.
		if(move_given_s_ramp)			{ run_S_ramp();									}
			
		// For running the motor in Velocity Mode TMC4671.
		if( (repeat_ramp != 2) && p_reeler1_info->flags.rotate_vel_mode \
			&& p_reeler1_info->flags.vel_timer && p_reeler1_info->flags.sag_enabled)
										{ run_Velocity_Ramp();							}	
		
		// Check if CAN Messages were received.
		if(can_rx_int)					{ can_Read();									}
	}
	return 0;
}