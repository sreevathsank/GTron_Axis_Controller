/*
 * gtron_can_cmd_parser.c
 *
 * Created: 29-07-2025 18:51:04
 *  Author: sreevathsank
 */ 

#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

Motor_Info_t guide_info;
Motor_Info_t *p_guide_info = &guide_info;

Motor_Info_t reeler_info;
Motor_Info_t *p_reeler_info = &reeler_info;

Motor_Info_t varrest_info;
Motor_Info_t *p_varrest_info = &varrest_info;

Can_Cmd_Info_t rx_can_cmd_info;

uint8_t rack_id;

/************************************************************************/
/* Reeler Functions                                                     */
/************************************************************************/

/** 
 * \brief reeler_Home - Homes the Reeler Motor with Rotary Encoder Z pulse as Zero Reference Position.
 *
 * @param	void 
 *
 * @return	void
 **/
static void reeler_Home( void )
{
	tmc4671_setActualPosition(MOTOR, 0);
	tmc4671_setAbsolutTargetPosition(MOTOR, 0);
	p_reeler_info->flags.move_given = 0;
	p_reeler_info->flags.rotate_vel_mode = 0;
	p_reeler_info->flags.sag_enabled = 0;
	limit_variables.homing = true;
	// Check whether to do firmware limit based homing.
	if( limit_variables.homing )
	{
		if(axis_params.rotary_axis_enabled)
		{
			limit_variables.rot_enc_z_first_hit = false;
			ext_irq_enable(ROTENC_Z);
		}
		do_homing_sequence();
	}
	PRINTF_DEBUG ? printf("\nReeler Homing Cmd Rxcvd\n"): 0;
	return;
}

/** 
 * \brief reeler_Move - Moves the Reeler Motor to the given Position.
 *
 * @param target_position	The target position for the Reeler motor to Move To / By.
 * @param move_to_by		Boolean value to decide whether to Move To (Absolute Move) or Move By (Relative Move).
 *
 * @return	void
 **/
static void reeler_Move(int32_t target_position, bool move_to_by)
{
	check_move_done = true;
	//reeler_info.position.trig_step_size = 0;
	if( (abs(tmc4671_getActualPosition(MOTOR) - target_position) > MIN_DISTANCE_RAMP ) )
	{
		(move_to_by == MOVE_TO) ? move_With_S_Ramp(target_position, reeler_info.velocity.limit, MOVE_TO) \
								: move_With_S_Ramp(target_position, reeler_info.velocity.limit, MOVE_BY);	
	}
	else
	{
		tmc4671_setVelocityLimit(MOTOR, reeler_info.velocity.limit);
		(move_to_by == MOVE_TO) ? tmc4671_setAbsolutTargetPosition(MOTOR, target_position) \
								: tmc4671_setRelativeTargetPosition(MOTOR, target_position);
	}
	(move_to_by == MOVE_TO) ? PRINTF_DEBUG ? printf("\nReeler Move To %ld steps\n", target_position): 0 \
	: PRINTF_DEBUG ? printf("\nReeler Move By %ld steps\n", target_position): 0;
	return;
}

/** 
 * \brief reeler_Set_Velocity - Sets the given value as the velocity limit for the position mode. The given value is also used for velocity target for velocity mode.
 *
 * @param reeler_target_velocity	The velocity limit or velocity target to rotate the reeler motor.
 *
 * @return void
 **/
static void reeler_Set_Velocity(int32_t reeler_target_velocity)
{
	reeler_info.velocity.limit = reeler_target_velocity;
	tmc4671_setVelocityLimit(MOTOR, reeler_info.velocity.limit);
	PRINTF_DEBUG ? printf("\nReeler Set Velocity %ld rpm\n", reeler_info.velocity.limit): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void reeler_Set_Teeth(uint32_t trig_step_size)
{
	reeler_info.position.trig_step_size = trig_step_size;
	PRINTF_DEBUG ? printf("\nReeler Set Teeth Number or Trigger Step Size as %ld\n", reeler_info.position.trig_step_size ): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void reeler_Set_Initial_Position(int32_t reeler_initial_position)
{
	reeler_info.position.initial = reeler_initial_position;
	reeler_Move(reeler_info.position.initial, MOVE_TO);
	PRINTF_DEBUG ? printf("\nReeler Set Initial Position to %ld steps\n", reeler_info.position.initial): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void reeler_Start_Motor( void )
{
	tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
	reeler_info.flags.rotate_vel_mode = true;
	if(reeler_info.flags.sag_enabled & reeler_info.flags.rotate_vel_mode)
	{
		timer_start(&VEL_TIMER);
	}
	PRINTF_DEBUG ? printf("\nReeler Start Motor with Velocity %ld rpm\n", reeler_info.velocity.limit): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void reeler_Stop_Motor( void )
{
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	move_given_trapezoidal_ramp = false;
	move_given_s_ramp = false; 
	check_move_done = false;
	reeler_info.flags.rotate_vel_mode = false;
	//reeler_info.position.trig_step_size = 0;
	homing_v = 0;
	//if(!reeler_info.flags.sag_enabled || !reeler_info.flags.rotate_vel_mode)
	{
		timer_stop(&VEL_TIMER);
	}
	reeler_info.position.current = tmc4671_getActualPosition(MOTOR);
	PRINTF_DEBUG ? printf("\nReeler Stop Motor\n"): 0;
	return;
}

/************************************************************************/
/* Guide Vertical Arrestor Functions                                    */
/************************************************************************/

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void guide_VArrestor_Move(Guide_or_VArrestor_t guide_varrestor, int32_t target_position, bool move_to_by)
{
	p_guide_info->flags.move_given = true;
	p_guide_info->position.current = p_guide_info->step_tracker.total_steps;
	p_guide_info->velocity.target  = 4000; 
	
	if(move_to_by == MOVE_TO) { p_guide_info->position.target = target_position; }					// Absolute Move.
															   
	// Check if the target position is greater or less than the current position.
	if(target_position > p_guide_info->position.current)
	{
		if(move_to_by == MOVE_BY)  
		{ p_guide_info->position.target = p_guide_info->position.current + target_position; }
			
		tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, p_guide_info->velocity.target);
		PRINTF_DEBUG ? printf("\nMove To: Current Pos = %ld | Target Pos = %ld | Velocity = %ld ustep/s\n", \
								p_guide_info->position.current, target_position, p_guide_info->velocity.target): 0;
	}
	else if(target_position < p_guide_info->position.current)
	{
		if(move_to_by == MOVE_BY)
		{ p_guide_info->position.target = p_guide_info->position.current - target_position; }
			
		tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, (-p_guide_info->velocity.target) );
		PRINTF_DEBUG ? printf("\nMove To: Current Pos = %ld | Target Pos = %ld | Velocity = %ld ustep/s\n", \
								p_guide_info->position.current, target_position, (-p_guide_info->velocity.target) ): 0;
	}
	else
	{
		PRINTF_DEBUG ? printf("\nTarget Position is same as Current Position. Not Moving...\n"): 0;
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
static void guide_Move_To_Open_Limit( void )
{
	tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0xFFFFF060);
	guide_info.flags.move_to_open_lim = true;
	PRINTF_DEBUG ? printf("\nGuide Move To Open Limit Cmd Rxcvd\n"): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void guide_Move_To_Close_Limit( void )
{
	tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0x00000FA0);
	guide_info.flags.move_to_close_lim = true;
	PRINTF_DEBUG ? printf("\nGuide Move to Close Limit Cmd Rxcvd\n"): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void guide_VArrestor_Set_Velocity(Guide_or_VArrestor_t guide_varrestor, int32_t target_velocity)
{
	p_guide_info->velocity.target = target_velocity;
	PRINTF_DEBUG ? printf("\nGuide Varrest Velocity Set to %ld usteps/sec\n", p_guide_info->velocity.target): 0;
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void guide_VArrestor_Set_Initial_Position(Guide_or_VArrestor_t guide_varrestor, int32_t initial_position)
{
	
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void guide_VArrestor_Stop_Motor(Guide_or_VArrestor_t guide_varrestor)
{
	switch(guide_varrestor)
	{
		case GUIDE:
			//tmc2209_set_velocity(TMC2209_GUIDE_ADDR, 0x00000000, GUIDE_STEP_COUNTER);
			tmc2209_writeRegister(TMC2209_GUIDE_ADDR, TMC2209_VACTUAL, 0x00000000);
			guide_info.flags.homing = 0;
			guide_info.flags.move_given = 0;
			guide_info.flags.move_to_open_lim = 0;
			guide_info.flags.move_to_close_lim = 0;
			PRINTF_DEBUG ? printf("\nGuide Motor Stop\n"): 0;
		break;
		
		case VARRESTOR:
		default:
		break;
	}
	
	return;
}

/************************************************************************/
/* Limit Functions                                                      */
/************************************************************************/

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void guide_Limits_Status_Check(/*uint8_t limit*/ void)
{
	uint8_t limit_reg_value = 0;
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_reg_value);
	if(axis_id == GTRON_AXC_TOP) { message_Id = CAN_REPLY_TOP_RACK_ID; }
	else if(axis_id == GTRON_AXC_BOT) { message_Id = CAN_REPLY_BOT_RACK_ID; }
	if( (limit_reg_value >> GUIDE_R_LIM_BIT & 1) )
	{
		can_tx_frame.data[0] = GUIDE_MOTOR;
		can_tx_frame.data[1] = AXC_PRESSED;
		for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
		can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
		PRINTF_DEBUG ? printf("\nGuide Open Right Limit is HIT!\n"): 0;
	}
	else
	{
		can_tx_frame.data[0] = GUIDE_MOTOR;
		can_tx_frame.data[1] = AXC_NOT_PRESSED;
		for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
		can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
		PRINTF_DEBUG ? printf("\nGuide Open Right Limit is not HIT!\n"): 0;
	}
	/*switch(limit)
	{
		case GUIDE_OPEN_LIMIT:
			IOXP_Read_Byte(IOXP_REG_GPIO, &limit_reg_value);
			if( (limit_reg_value >> GUIDE_R_LIM_BIT & 1) )
			{
				// CAN Message Reply.
				PRINTF_DEBUG ? printf("\nGuide Open Right Limit is HIT!\n"): 0;
			}
			else
			{
				// CAN Message Reply.
				PRINTF_DEBUG ? printf("\nGuide Open Right Limit is not HIT!\n"): 0;
			}
		break;
		case GUIDE_CLOSE_LIMIT:
			IOXP_Read_Byte(IOXP_REG_GPIO, &limit_reg_value);
			if( (limit_reg_value >> GUIDE_L_LIM_BIT & 1) )
			{
				// CAN Message Reply.
				PRINTF_DEBUG ? printf("\nGuide Close Left Limit is HIT!\n"): 0;
			}
			else
			{
				// CAN Message Reply.
				PRINTF_DEBUG ? printf("\nGuide Close Left Limit is not HIT!\n"): 0;
			}
		break;
		default: break;
	}*/
	return;	
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
void parse_GTron_CAN_Msg_Data( void )
{
	switch(rx_can_cmd_info.id)
	{
		case CAN_TOP_RACK_ID: 
			rack_id = TOP_RACK; 
			PRINTF_DEBUG ? printf("\nTOP Rack Message ID Rxcvd\n"): 0;
		break;
		case CAN_BOT_RACK_ID: 
			rack_id = BOT_RACK; 
			PRINTF_DEBUG ? printf("\nBOTTOM Rack Message ID Rxcvd\n"): 0;
		break;
		case CAN_TOP_SAG_REELER_ID:
			rack_id = TOP_RACK;
			PRINTF_DEBUG ? printf("\nTOP Sag Reeler Message ID Rxcvd\n"): 0;
			switch(rx_can_cmd_info.data[0])
			{
				case 1:
				reeler_info.flags.sag_enabled = true;
				if(reeler_info.flags.sag_enabled & reeler_info.flags.rotate_vel_mode)
				{
					timer_start(&VEL_TIMER);
					tmc4671_setVelocityLimit(MOTOR, reeler_info.velocity.limit);
				}
				PRINTF_DEBUG ? printf("\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Rotate.\n"): 0;
				break;
				case 0:
				reeler_info.flags.sag_enabled = false;
				if(!reeler_info.flags.sag_enabled || !reeler_info.flags.rotate_vel_mode)
				{
					timer_stop(&VEL_TIMER);
				}
				tmc4671_setVelocityTarget(MOTOR, 0);
				PRINTF_DEBUG ? printf("\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Stop.\n"): 0;
				break;
				default: PRINTF_DEBUG ? printf("\nSag Sensor Invalid Operation Rxcvd\n"): 0;					break;
			}
		break;
		case CAN_BOT_SAG_REELER_ID:
			rack_id = BOT_RACK;
			PRINTF_DEBUG ? printf("\nBOTTOM Sag Reeler Message ID Rxcvd\n"): 0;
			switch(rx_can_cmd_info.data[0])
			{
				case 1:
				reeler_info.flags.sag_enabled = true;
				if(reeler_info.flags.sag_enabled & reeler_info.flags.rotate_vel_mode)
				{
					timer_start(&VEL_TIMER);
				}
				PRINTF_DEBUG ? printf("\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Rotate.\n"): 0;
				break;
				case 0:
				reeler_info.flags.sag_enabled = false;
				//if(!reeler_info.flags.sag_enabled & !reeler_info.flags.rotate_vel_mode)
				{
					timer_stop(&VEL_TIMER);
				}
				tmc4671_setVelocityTarget(MOTOR, 0);
				PRINTF_DEBUG ? printf("\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Stop.\n"): 0;
				break;
				default: PRINTF_DEBUG ? printf("\nSag Sensor Invalid Operation Rxcvd\n"): 0;					break;
			}
		break;
		case CAN_BOARD_ACTIVE_PING_ID:
			if( (axis_id == GTRON_AXC_TOP) && (can_rx_frame.data[0] == TOP_AXC_BOARD_ID) )
			{
				message_Id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
				can_tx_frame.data[0] = TOP_AXC_BOARD_ID;
				can_Write(message_Id, can_tx_frame.data_64bit);
				PRINTF_DEBUG ? printf("\nGTron Top AxC Board Active Ping Rxcvd\t Board Active Ping Reply Sent\n"): 0;
			}
			else if( (axis_id == GTRON_AXC_BOT) && (can_rx_frame.data[0] == BOT_AXC_BOARD_ID) )
			{
				message_Id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
				can_tx_frame.data[0] = BOT_AXC_BOARD_ID;
				can_Write(message_Id, can_tx_frame.data_64bit);
				PRINTF_DEBUG ? printf("\nGTron Bottom AxC Board Active Ping Rxcvd\t Board Active Ping Reply Sent\n"): 0;
			}
		break;
		default: break;
	}	
	
	// Check if the current node and message id received are for the current node.
	if( ((rack_id == TOP_RACK) && (axis_id == GTRON_AXC_TOP)) || \
	    ((rack_id == BOT_RACK) && (axis_id == GTRON_AXC_BOT)) )
	//if( (X_AXIS == axis_id) && (TOP_RACK == rack_id) )
	{
		switch(rx_can_cmd_info.data[PERIPHERAL_BYTE_IDX])
		{
			case AxC_DEFAULT: break;
			case REELER_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_START:				reeler_Start_Motor();											break;
					case AXC_STOP:				reeler_Stop_Motor();											break;
					case AXC_VELOCITY:			reeler_Set_Velocity((int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:			reeler_Move( TMC4671_ROTATION, MOVE_BY);					    break;
					case AXC_MOVE_TO:			reeler_Move((int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_BY:			reeler_Move((int32_t)rx_can_cmd_info.value, MOVE_BY);			break;
					case AXC_TEETH:				reeler_Set_Teeth((uint32_t)rx_can_cmd_info.value);				break;
					case AXC_INITIAL_POSITION:	reeler_Set_Initial_Position((int32_t)rx_can_cmd_info.value);	break;
					case AXC_HOMING:			reeler_Home();													break;
					default: PRINTF_DEBUG ? printf("\nReeler Motor Invalid Operation Rxcvd\n"): 0;				break;
				}
			break;
			case GUIDE_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:					guide_VArrestor_Stop_Motor(GUIDE);												break;
					case AXC_VELOCITY:				guide_VArrestor_Set_Velocity(GUIDE, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:				guide_VArrestor_Move(GUIDE, (int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_TO:				guide_VArrestor_Move(GUIDE, (int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_BY:				guide_VArrestor_Move(GUIDE, (int32_t)rx_can_cmd_info.value, MOVE_BY);			break;
					case AXC_MOVE_TO_OPEN_LIMIT:	guide_Move_To_Open_Limit();														break;
					case AXC_MOVE_TO_CLOSE_LIMIT:	guide_Move_To_Close_Limit();													break;
					case AXC_INITIAL_POSITION:		guide_VArrestor_Set_Initial_Position(GUIDE, (int32_t)rx_can_cmd_info.value);	break;
					case AXC_STATUS_CHECK:			guide_Limits_Status_Check();													break;
					default: PRINTF_DEBUG ? printf("\nGuide Motor Invalid Operation Rxcvd\n"): 0;								break;
				}
			break;
			case VERITCAL_ARRESTOR_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:			   guide_VArrestor_Stop_Motor(VARRESTOR);											break;
					case AXC_VELOCITY:		   guide_VArrestor_Set_Velocity(VARRESTOR, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:		   guide_VArrestor_Move(VARRESTOR, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_TO:		   guide_VArrestor_Move(VARRESTOR, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_BY:		   guide_VArrestor_Move(VARRESTOR, (int32_t)rx_can_cmd_info.value, MOVE_BY);		break;
					case AXC_INITIAL_POSITION: guide_VArrestor_Set_Initial_Position(VARRESTOR, (int32_t)rx_can_cmd_info.value); break;
					default: PRINTF_DEBUG ? printf("\nVert Arrestor Motor Invalid Operation Rxcvd\n"): 0;						break;
				}
			break;
			case GUIDE_OPEN_LIMIT:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: break;
					case AXC_DISABLE: break;
					case AXC_STATUS_CHECK: break;
					default: PRINTF_DEBUG ? printf("\nGuide Open Limit Invalid Operation Rxcvd\n"): 0;					break;
				}
			break;
			case GUIDE_CLOSE_LIMIT:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: break;
					case AXC_DISABLE: break;
					case AXC_STATUS_CHECK: break;
					default: PRINTF_DEBUG ? printf("\nGuide Close Limit Invalid Operation Rxcvd\n"): 0;					break;
				}
			break;
			case REELER_ENCODER:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_INITIALIZE: break;
					case AXC_START: break;
					case AXC_STOP: break;
					case AXC_ENABLE: break;
					case AXC_DISABLE: break;
					default: PRINTF_DEBUG ? printf("\nReeler Encoder Invalid Operation Rxcvd\n"): 0;					break;
				}
			break;
			case GUIDE_ENCODER:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_INITIALIZE: break;
					case AXC_START: break;
					case AXC_STOP: break;
					case AXC_ENABLE: break;
					case AXC_DISABLE: break;
					default: PRINTF_DEBUG ? printf("\nGuide Encoder Invalid Operation Rxcvd\n"): 0;					break;
				}
			break;
			default: break;
		}
	}
	return;
}