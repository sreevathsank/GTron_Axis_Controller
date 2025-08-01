/*
 * gtron_can_cmd_parser.c
 *
 * Created: 29-07-2025 18:51:04
 *  Author: sreevathsank
 */ 

#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

Reeler_Info_t reeler_info;
Reeler_Info_t *p_reeler_info = &reeler_info;

Can_Cmd_Info_t rx_can_cmd_info;

/************************************************************************/
/* Reeler Functions                                                     */
/************************************************************************/

static void reeler_Move(int32_t target_position, bool move_to_by)
{
	check_move_done = true;
	if( (abs(tmc4671_getActualPosition(MOTOR) - target_position) > MIN_DISTANCE_RAMP ) )
	{
		(move_to_by == MOVE_TO) ? move_With_S_Ramp(target_position, reeler_info.velocity_limit, MOVE_TO) \
								: move_With_S_Ramp(target_position, reeler_info.velocity_limit, MOVE_BY);	
	}
	else
	{
		tmc4671_setVelocityLimit(MOTOR, reeler_info.velocity_limit);
		tmc4671_setAbsolutTargetPosition(MOTOR, target_position);
	}
	return;
}

static void reeler_Set_Velocity(int32_t reeler_target_velocity)
{
	reeler_info.velocity_limit = reeler_target_velocity;
	tmc4671_setVelocityLimit(MOTOR, reeler_info.velocity_limit);
	return;
}

static void reeler_Set_Teeth(uint32_t trig_step_size)
{
	reeler_info.trigger_step_size = trig_step_size;
	return;
}

static void reeler_Set_Initial_Position(int32_t reeler_initial_position)
{
	reeler_info.initial_position = reeler_initial_position;
	reeler_Move(reeler_info.initial_position, MOVE_TO);
	return;
}

static void reeler_Stop_Motor( void )
{
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	move_given_trapezoidal_ramp = false;
	move_given_s_ramp = false;
	check_move_done = false;
	homing_v = 0;
	timer_stop(&TIMER_0);
	reeler_info.current_position = tmc4671_getActualPosition(MOTOR);
	return;
}

/************************************************************************/
/* Guide Vertical Arrestor Functions                                    */
/************************************************************************/

static void guide_VArrestor_Move(Guide_or_VArrestor_t guide_varrestor, int32_t target_position, bool move_to_by)
{
	
	return;
}

static void guide_Move_To_Open_Limit( void )
{
	
	return;
}

static void guide_Move_To_Close_Limit( void )
{
	
	return;
}

static void guide_VArrestor_Set_Velocity(Guide_or_VArrestor_t guide_varrestor, int32_t target_velocity)
{
	
	return;
}

static void guide_VArrestor_Set_Initial_Position(Guide_or_VArrestor_t guide_varrestor, int32_t initial_position)
{
	
	return;
}

static void guide_VArrestor_Stop_Motor(Guide_or_VArrestor_t guide_varrestor)
{
	
	return;
}

/************************************************************************/
/* Limit Functions                                                      */
/************************************************************************/

static void guide_Limits_Status_Check(uint8_t limit)
{
	
	return;	
}

void parse_GTron_CAN_Msg_Data( void )
{
	uint8_t rack_id;
	switch(rx_can_cmd_info.id)
	{
		case CAN_TOP_RACK_ID: rack_id = TOP_RACK; break;
		case CAN_BOT_RACK_ID: rack_id = BOT_RACK; break;
	}	
	
	// Check if the current node and message id received are for the current node.
	if( ((rack_id == TOP_RACK) && (axis_id == GTRON_AXC_TOP)) || \
	    ((rack_id == BOT_RACK) && (axis_id == GTRON_AXC_BOT)) )
	{
		switch(rx_can_cmd_info.data[PERIPHERAL_BYTE_IDX])
		{
			case AxC_DEFAULT: break;
			case REELER_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:
						reeler_Stop_Motor();
					break;
					case AXC_VELOCITY:
						reeler_Set_Velocity((int32_t)rx_can_cmd_info.value);
					break;
					case AXC_ROTATE:
						reeler_Move((int32_t)rx_can_cmd_info.value, MOVE_TO);
					break;
					case AXC_MOVE_TO:
						reeler_Move((int32_t)rx_can_cmd_info.value, MOVE_TO);
					break;
					case AXC_MOVE_BY:
						reeler_Move((int32_t)rx_can_cmd_info.value, MOVE_BY);
					break;
					case AXC_TEETH:
						reeler_Set_Teeth((uint32_t)rx_can_cmd_info.value);
					break;
					case AXC_INITIAL_POSITION:
						reeler_Set_Initial_Position((int32_t)rx_can_cmd_info.value);
					break;
					default: break;
				}
			break;
			case GUIDE_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:
						guide_VArrestor_Stop_Motor(GUIDE);
					break;
					case AXC_VELOCITY:
						guide_VArrestor_Set_Velocity(GUIDE, (int32_t)rx_can_cmd_info.value);
					break;
					case AXC_ROTATE:
						guide_VArrestor_Move(GUIDE, (int32_t)rx_can_cmd_info.value, MOVE_TO);
					break;
					case AXC_MOVE_TO:
						guide_VArrestor_Move(GUIDE, (int32_t)rx_can_cmd_info.value, MOVE_TO);
					break;
					case AXC_MOVE_BY:
						guide_VArrestor_Move(GUIDE, (int32_t)rx_can_cmd_info.value, MOVE_BY);
					break;
					case AXC_INITIAL_POSITION:
						guide_VArrestor_Set_Initial_Position(GUIDE, (int32_t)rx_can_cmd_info.value);
					break;
					default: break;
				}
			break;
			case VERITCAL_ARRESTOR_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:
						guide_VArrestor_Stop_Motor(VARRESTOR);
					break;
					case AXC_VELOCITY:
						guide_VArrestor_Set_Velocity(VARRESTOR, (int32_t)rx_can_cmd_info.value);
					break;
					case AXC_ROTATE:
						guide_VArrestor_Move(VARRESTOR, (int32_t)rx_can_cmd_info.value, MOVE_TO);
					break;
					case AXC_MOVE_TO:
						guide_VArrestor_Move(VARRESTOR, (int32_t)rx_can_cmd_info.value, MOVE_TO);
					break;
					case AXC_MOVE_BY:
						guide_VArrestor_Move(VARRESTOR, (int32_t)rx_can_cmd_info.value, MOVE_BY);
					break;
					case AXC_INITIAL_POSITION:
						guide_VArrestor_Set_Initial_Position(VARRESTOR, (int32_t)rx_can_cmd_info.value);
					break;
					default: break;
				}
			break;
			case GUIDE_OPEN_LIMIT:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE:
					
					break;
					case AXC_DISABLE:
					
					break;
					case AXC_STATUS_CHECK:
						guide_Limits_Status_Check(rx_can_cmd_info.data[PERIPHERAL_BYTE_IDX]);
					break;
					default: break;
				}
			break;
			case GUIDE_CLOSE_LIMIT:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE:
					
					break;
					case AXC_DISABLE:
					
					break;
					case AXC_STATUS_CHECK:
						guide_Limits_Status_Check(rx_can_cmd_info.data[PERIPHERAL_BYTE_IDX]);
					break;
					default: break;
				}
			break;
			case REELER_ENCODER:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_INITIALIZE:
					
					break;
					case AXC_START:
					
					break;
					case AXC_STOP:
					
					break;
					case AXC_ENABLE:
					
					break;
					case AXC_DISABLE:
					
					break;
					default: break;
				}
			break;
			case GUIDE_ENCODER:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_INITIALIZE:
					
					break;
					case AXC_START:
					
					break;
					case AXC_STOP:
					
					break;
					case AXC_ENABLE:
					
					break;
					case AXC_DISABLE:
					
					break;
					default: break;
				}
			break;
			default: break;
		}
	}
	return;
}