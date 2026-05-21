/*
 * gtron_can_cmd_parser.c
 *
 * Created: 29-07-2025 18:51:04
 *  Author: sreevathsank
 */ 

#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

volatile Motor_Info_t guide_info;
volatile Motor_Info_t *p_guide_info = &guide_info;

volatile Motor_Info_t reeler_info;
volatile Motor_Info_t *p_reeler_info = &reeler_info;

volatile Motor_Info_t varrest_info;
volatile Motor_Info_t *p_varrest_info = &varrest_info;

Can_Cmd_Info_t rx_can_cmd_info;

uint8_t rack_id;

/************************************************************************/
/* Reeler Functions                                                     */
/************************************************************************/

/** 
 * \brief reeler_Home - Homes the Reeler Motor with Rotary Encoder Z pulse as Zero Reference Position.
 *
 * @param	void 
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
		do_homing_sequence();
		if(axis_params.rotary_axis_enabled)
		{
			limit_variables.rot_enc_z_first_hit = false;
			ext_irq_enable(ROTENC_Z);
		}
		
	}
	DBG_Printf(ERR_LVL_INFO, "\nReeler Homing Cmd Rxcvd\n");
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
	if( (abs(tmc4671_getActualPosition(MOTOR) - target_position) > MIN_DISTANCE_RAMP ) ) {
		(move_to_by == MOVE_TO) ? move_With_S_Ramp(target_position, p_reeler_info->velocity.limit, MOVE_TO) \
								: move_With_S_Ramp(target_position, p_reeler_info->velocity.limit, MOVE_BY);	
	} else {
		tmc4671_setVelocityLimit(MOTOR, p_reeler_info->velocity.limit);
		(move_to_by == MOVE_TO) ? tmc4671_setAbsolutTargetPosition(MOTOR, target_position) \
								: tmc4671_setRelativeTargetPosition(MOTOR, target_position);
	}
	
	if(p_reeler_info->hybrid.mode == HYBRID_MODE_N_SHOT) {
		p_reeler_info->flags.sensor_trigger		= false;
		p_reeler_info->hybrid.one_shot_armed	= true;
		DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot armed for this move\n");
	}
	(move_to_by == MOVE_TO) ?	DBG_Printf(ERR_LVL_INFO, "\nReeler Move To %ld steps\n", target_position) \
							:	DBG_Printf(ERR_LVL_INFO, "\nReeler Move By %ld steps\n", target_position);
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
	p_reeler_info->velocity.limit = reeler_target_velocity;
	tmc4671_setVelocityLimit(MOTOR, p_reeler_info->velocity.limit);
	p_reeler_info->position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, p_reeler_info->position.current);
	PRINTF_DEBUG ? printf("\nReeler Set Velocity %ld rpm\n", p_reeler_info->velocity.limit): 0;
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
	p_reeler_info->position.trig_step_size = trig_step_size;
	p_reeler_info->position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, p_reeler_info->position.current);
	PRINTF_DEBUG ? printf("\nReeler Set Teeth Number or Trigger Step Size as %ld\n", p_reeler_info->position.trig_step_size ): 0;
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
	p_reeler_info->position.initial = reeler_initial_position;
	reeler_Move(p_reeler_info->position.initial, MOVE_TO);
	PRINTF_DEBUG ? printf("\nReeler Set Initial Position to %ld steps\n", p_reeler_info->position.initial): 0;
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
	if(p_reeler_info->flags.is_paused)	{
		p_reeler_info->flags.sensor_trigger = false;
		tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
		p_reeler_info->flags.rotate_vel_mode = true;
		if(p_reeler_info->flags.sag_enabled && p_reeler_info->flags.rotate_vel_mode) {
			timer_start(&VEL_TIMER);
			DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled");
		}
		p_reeler_info->flags.is_paused = false;
		DBG_Printf(ERR_LVL_DEBUG, "[HYB] Reeler Resumed\n");
		return;
	}
	p_reeler_info->flags.rotate_vel_mode = true;
	p_reeler_info->flags.is_paused = false;
	if(p_reeler_info->flags.sag_enabled && p_reeler_info->flags.rotate_vel_mode) {
		timer_start(&VEL_TIMER);
		tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
		tmc4671_setVelocityTarget(MOTOR, p_reeler_info->velocity.limit);
		DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled");
	}
	if(p_reeler_info->hybrid.mode == HYBRID_MODE_INSPECTION) {
		p_reeler_info->hybrid.first_trigger_skip	= true;
		p_reeler_info->hybrid.consecutive_slips		= 0;
		p_reeler_info->hybrid.cycle_armed			= false;
		p_reeler_info->flags.sensor_trigger			= false;
	}
	
	DBG_Printf(ERR_LVL_DEBUG,"\nReeler Start Motor with Velocity %ld rpm\n", p_reeler_info->velocity.limit);
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
void reeler_Stop_Motor( void )
{
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	move_given_trapezoidal_ramp					= false;
	move_given_s_ramp							= false; 
	check_move_done								= false;
	p_reeler_info->flags.rotate_vel_mode		= false;
	p_reeler_info->flags.sag_enabled			= false;
	p_reeler_info->hybrid.one_shot_armed		= false;
	p_reeler_info->flags.is_paused				= false;
	p_reeler_info->hybrid.cycle_armed			= false;
	p_reeler_info->hybrid.first_trigger_skip	= true;
	p_reeler_info->hybrid.consecutive_slips		= 0;
	p_reeler_info->flags.is_paused				= false;
	//reeler_info.position.trig_step_size = 0;
	homing_v = 0;
	//if(!reeler_info.flags.sag_enabled || !reeler_info.flags.rotate_vel_mode)
	{
		timer_stop(&VEL_TIMER);
	}
	trig_no = 0;
	prev_trig_no = 0;
	reeler_info.position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, reeler_info.position.current);
	DBG_Printf(ERR_LVL_INFO, "\nReeler Stop Motor\n");
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
void reeler_Pause_Motor( void )
{
	tmc4671_setVelocityLimit(MOTOR, 0);
	tmc4671_setVelocityTarget(MOTOR, 0);
	tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
	move_given_trapezoidal_ramp = false;
	move_given_s_ramp = false; 
	check_move_done = false;
	reeler_info.flags.rotate_vel_mode = false;
	reeler_info.flags.sag_enabled = false;
	homing_v = 0;
	timer_stop(&VEL_TIMER);
	trig_no = 0;
	prev_trig_no = 0;
	reeler_info.position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, reeler_info.position.current);
	tmc4671_setVelocityLimit(MOTOR, 2);
	tmc4671_setModeMotion(MOTOR, POSITION_MODE);
	p_reeler_info->flags.is_paused = true;
	DBG_Printf(ERR_LVL_INFO, "Reeler Pause Motor\n");
	return;
}

static void reeler_Get_Position( void )
{
	int32_t reeler_position = tmc4671_getActualPosition(MOTOR);
	int32_t reel_pos_within_rot = reeler_position & 0xFFFF;
	DBG_Printf(ERR_LVL_DEBUG, "The current Reeler Position is = ABS %ld usteps | REL %ld usteps", reeler_position, reel_pos_within_rot);
	can_AxC_Write(CAN_REPLY_TOP_RACK_ID, REELER_MOTOR, AXC_CURRENT_POSITION, reel_pos_within_rot);
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
	p_guide_info->velocity.target  = 1000; 
	
	if(move_to_by == MOVE_TO) { p_guide_info->position.target = target_position; }					// Absolute Move.
															   
	// Check if the target position is greater or less than the current position.
	if(target_position > p_guide_info->position.current)
	{
		if(move_to_by == MOVE_BY)  
		{ p_guide_info->position.target = p_guide_info->position.current + target_position; }
			
		tmc2209_writeRegister(TMC2209_GUIDE_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
		tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, p_guide_info->velocity.target);
		PRINTF_DEBUG ? printf("\nMove To: Current Pos = %ld | Target Pos = %ld | Velocity = %ld ustep/s\n", \
								p_guide_info->position.current, target_position, p_guide_info->velocity.target): 0;
	}
	else if(target_position < p_guide_info->position.current)
	{
		if(move_to_by == MOVE_BY)
		{ p_guide_info->position.target = p_guide_info->position.current - target_position; }
		
		tmc2209_writeRegister(TMC2209_GUIDE_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
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
	uint8_t limit_status = 0;
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_status);
	if(MSK_GUIDE_R_LIM(limit_status)) {
		PRINTF_DEBUG ? printf("\nAlready in Open Limit. Not moving towards Open Limit\n"): 0;
		
		// Send the CAN Command
		message_Id = CAN_REPLY_TOP_RACK_ID;
		can_tx_frame.data[0] = GUIDE_OPEN_LIMIT;
		can_tx_frame.data[1] = AXC_PRESSED;
		can_Write(message_Id, can_tx_frame.data_64bit);
		return;
	}
	tmc2209_writeRegister(TMC2209_GUIDE_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0x00000FA0);
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
	uint8_t limit_status = 0;
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_status);
	if(MSK_GUIDE_L_LIM(limit_status)) {
		PRINTF_DEBUG ? printf("\nAlready in Close Limit. Not moving towards Close Limit\n"): 0;
		
		// Send the CAN Command
		message_Id = CAN_REPLY_TOP_RACK_ID;
		can_tx_frame.data[0] = GUIDE_CLOSE_LIMIT;
		can_tx_frame.data[1] = AXC_PRESSED;
		can_Write(message_Id, can_tx_frame.data_64bit);
		return;
	}
	tmc2209_writeRegister(TMC2209_GUIDE_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0xFFFFF060);
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
	tmc2209_writeRegister(TMC2209_GUIDE_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_reg_value);
	if(axis_id == GTRON_AXC_TOP) { message_Id = CAN_REPLY_TOP_RACK_ID; }
	else if(axis_id == GTRON_AXC_BOT) { message_Id = CAN_REPLY_BOT_RACK_ID; }
	if( (limit_reg_value >> GUIDE_R_LIM_BIT & 1) ) {
		can_tx_frame.data[0] = GUIDE_MOTOR;
		can_tx_frame.data[1] = AXC_PRESSED;
		for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
		can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
		PRINTF_DEBUG ? printf("\nGuide Open Right Limit is HIT!\n"): 0;
	} else {
		can_tx_frame.data[0] = GUIDE_MOTOR;
		can_tx_frame.data[1] = AXC_NOT_PRESSED;
		for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
		can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
		PRINTF_DEBUG ? printf("\nGuide Open Right Limit is not HIT!\n"): 0;
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
void parse_GTron_CAN_Msg_Data( void )
{
	switch(rx_can_cmd_info.id)
	{
		case CAN_TOP_RACK_ID: 
			rack_id = TOP_RACK; 
			PRINTF_DEBUG ? printf("\nTOP Rack Message ID Rxcvd from MI\n"): 0;
		break;
		case CAN_BOT_RACK_ID: 
			rack_id = BOT_RACK; 
			PRINTF_DEBUG ? printf("\nBOTTOM Rack Message ID Rxcvd from MI\n"): 0;
		break;
		case CAN_TOP_SAG_REELER_ID:
			rack_id = TOP_RACK;
			PRINTF_DEBUG ? printf("\nTOP Sag Reeler Message ID Rxcvd from Sys Ctrl\n"): 0;
			if(!reeler_info.flags.rotate_vel_mode) { break; }
			switch(rx_can_cmd_info.data[0])
			{
				case 1: {
					reeler_info.flags.sag_enabled = true;
					if(reeler_info.flags.sag_enabled & reeler_info.flags.rotate_vel_mode) {
						trig_no = 0;
						prev_trig_no = 0;
						timer_start(&VEL_TIMER);
						tmc4671_setVelocityLimit(MOTOR, reeler_info.velocity.limit);
						tmc4671_setVelocityTarget(MOTOR, reeler_info.velocity.limit);
					}
					PRINTF_DEBUG ? printf("\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Rotate.\n"): 0;
					break;
				}
				case 0: {
					reeler_info.flags.sag_enabled = false;
					if(!reeler_info.flags.sag_enabled || !reeler_info.flags.rotate_vel_mode) {
						trig_no = 0;
						prev_trig_no = 0;
						timer_stop(&VEL_TIMER);
					}
					tmc4671_setVelocityTarget(MOTOR, 0);
					PRINTF_DEBUG ? printf("\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Stop.\n"): 0;
					break;
				}
				default: PRINTF_DEBUG ? printf("\nSag Sensor Invalid Operation Rxcvd\n"): 0; break;
			}
		break;
		case CAN_BOT_SAG_REELER_ID:
			rack_id = BOT_RACK;
			PRINTF_DEBUG ? printf("\nBOTTOM Sag Reeler Message ID Rxcvd from Sys Ctrl\n"): 0;
			if(!reeler_info.flags.rotate_vel_mode) { break; }
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
			if( (axis_id == GTRON_AXC_TOP) && (can_rx_frame.data[0] == TOP_AXC_BOARD_ID) ) {
				message_Id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
				can_tx_frame.data[0] = TOP_AXC_BOARD_ID;
				can_Write(message_Id, can_tx_frame.data_64bit);
				PRINTF_DEBUG ? printf("\nGTron Top AxC Board Active Ping Rxcvd\t Board Active Ping Reply Sent\n"): 0;
			} else if( (axis_id == GTRON_AXC_BOT) && (can_rx_frame.data[0] == BOT_AXC_BOARD_ID) ) {
				message_Id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
				can_tx_frame.data[0] = BOT_AXC_BOARD_ID;
				can_Write(message_Id, can_tx_frame.data_64bit);
				PRINTF_DEBUG ? printf("\nGTron Bottom AxC Board Active Ping Rxcvd\t Board Active Ping Reply Sent\n"): 0;
			}
		break;
		case CAN_IO_TO_TOP_AXC_ID: {
			rack_id = TOP_RACK;
			PRINTF_DEBUG ? printf("\nTOP Rack Message ID Rxcvd from IO Ctrl\n"): 0;
			break;
		}
		case CAN_IO_TO_BOT_AXC_ID: {
			rack_id = BOT_RACK;
			PRINTF_DEBUG ? printf("\nBOT Rack Message ID Rxcvd from IO Ctrl\n"): 0;
			break;
		}
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
					case AXC_CURRENT_POSITION:	reeler_Get_Position();											break;
					case AXC_HOMING:			reeler_Home();													break;
					case AXC_PAUSE:				reeler_Pause_Motor();											break;
					default: DBG_Printf(ERR_LVL_DEBUG, "Reeler Motor Invalid Operation Rxcvd\n");				break;
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
					default: DBG_Printf(ERR_LVL_DEBUG,"Guide Motor Invalid Operation Rxcvd\n");									break;
				}
			break;
			case VERITCAL_ARRESTOR_MOTOR1:
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
			case HYBRID_TRIGGER_INSPECTION: {
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: {
						p_reeler_info->hybrid.mode					= HYBRID_MODE_INSPECTION;
						p_reeler_info->hybrid.first_trigger_skip	= true;
						p_reeler_info->hybrid.consecutive_slips		= 0;
						p_reeler_info->hybrid.cycle_armed			= false;
						p_reeler_info->flags.sensor_trigger			= false;
						p_reeler_info->flags.is_hybrid_trig_enabled = true;
						DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger flag Enabled\n");
						break;
					}
					case AXC_DISABLE: {
						p_reeler_info->hybrid.mode					= HYBRID_MODE_OFF;
						p_reeler_info->hybrid.cycle_armed			= false;
						p_reeler_info->flags.is_hybrid_trig_enabled = false;
						DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger flag Disabled\n");
						break;
					}
					case AXC_TOLERABLE_SLIPS: {
						p_reeler_info->hybrid.total_slips = (uint16_t)rx_can_cmd_info.value;
						DBG_Printf(ERR_LVL_INFO, "Tolerable Slips received = %d\n", p_reeler_info->hybrid.total_slips);
						break;
					}
					case AXC_PAUSE: {
						p_reeler_info->flags.is_paused = true;
						reeler_Pause_Motor();
						p_reeler_info->hybrid.mode = HYBRID_MODE_OFF;
						DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Inspection PAUSED\n");	
						break;
					}
					case AXC_N_SHOT: {
						p_reeler_info->hybrid.total_n_shots = (uint32_t)rx_can_cmd_info.value;
						if(p_reeler_info->hybrid.total_n_shots == 0) {
							DBG_Printf(ERR_LVL_INFO, "Total N Shots = %ld | Inspection\n", p_reeler_info->hybrid.total_n_shots);
							p_reeler_info->hybrid.mode					= HYBRID_MODE_INSPECTION;
							p_reeler_info->hybrid.first_trigger_skip	= true;
							p_reeler_info->hybrid.consecutive_slips		= 0;
							p_reeler_info->hybrid.cycle_armed			= false;
							p_reeler_info->flags.sensor_trigger			= false;
							p_reeler_info->flags.is_hybrid_trig_enabled = true;
							p_reeler_info->hybrid.prev_anchor_pos		= tmc4671_getActualPosition(MOTOR);
							DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger N Shot flag Enabled for Inspection\n");
							} else {
							DBG_Printf(ERR_LVL_INFO, "Hybrid Trigger N Shot flag Enabled | No of N Shots = %ld\n", p_reeler_info->hybrid.total_n_shots);
							p_reeler_info->hybrid.mode					= HYBRID_MODE_N_SHOT;
							p_reeler_info->flags.is_hybrid_trig_enabled = true;
							p_reeler_info->hybrid.consecutive_slips		= 0;
							//p_reeler_info->flags.is_paused				= false;
							p_reeler_info->flags.sag_enabled			= true;
							p_reeler_info->hybrid.cycle_armed			= false;
							p_reeler_info->flags.rotate_vel_mode		= true;
							p_reeler_info->hybrid.curr_n_shots			= 0;
							p_reeler_info->hybrid.prev_anchor_pos		= tmc4671_getActualPosition(MOTOR);
							if(p_reeler_info->flags.sag_enabled && p_reeler_info->flags.rotate_vel_mode) {
								timer_start(&VEL_TIMER);
								tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
								tmc4671_setVelocityTarget(MOTOR, reeler_info.velocity.limit);
								DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled\n");
							}
						}
						break;
					}
					case AXC_TERMINAL_WIDTH: {
						p_reeler_info->hybrid.term_width = (uint32_t)rx_can_cmd_info.value;
						DBG_Printf(ERR_LVL_INFO, "Hybrid Terminal Width received = %ld usptes", p_reeler_info->hybrid.term_width);
						break;
					}
					default: DBG_Printf(ERR_LVL_INFO, "\nHybrid Trigger Invalid Operation Rxcvd\n"); break;
				}
				break;
			}
			case HYBRID_TRIGGER_N_SHOT: {
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: {
						p_reeler_info->hybrid.total_n_shots = (uint32_t)rx_can_cmd_info.value;
						if(p_reeler_info->hybrid.total_n_shots == 0) {
							DBG_Printf(ERR_LVL_INFO, "Total N Shots = %ld | Inspection\n", p_reeler_info->hybrid.total_n_shots);
							p_reeler_info->hybrid.mode					= HYBRID_MODE_INSPECTION;
							p_reeler_info->hybrid.first_trigger_skip	= true;
							p_reeler_info->hybrid.consecutive_slips		= 0;
							p_reeler_info->hybrid.cycle_armed			= false;
							p_reeler_info->flags.sensor_trigger			= false;
							p_reeler_info->flags.is_hybrid_trig_enabled = true;
							p_reeler_info->hybrid.prev_anchor_pos		= tmc4671_getActualPosition(MOTOR);
							DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger flag Enabled for Inspection\n");
						} else {
							DBG_Printf(ERR_LVL_INFO, "Hybrid Trigger N Shot flag Enabled | No of N Shots = %ld\n", p_reeler_info->hybrid.total_n_shots);
							p_reeler_info->hybrid.mode					= HYBRID_MODE_N_SHOT;
							p_reeler_info->flags.is_hybrid_trig_enabled = true;
							p_reeler_info->hybrid.consecutive_slips		= 0;
							p_reeler_info->flags.is_paused				= false;
							p_reeler_info->flags.sag_enabled			= true;
							p_reeler_info->hybrid.cycle_armed			= false;
							p_reeler_info->flags.rotate_vel_mode		= true;
							p_reeler_info->hybrid.curr_n_shots			= 0;
							p_reeler_info->hybrid.prev_anchor_pos		= tmc4671_getActualPosition(MOTOR);
							if(p_reeler_info->flags.sag_enabled && p_reeler_info->flags.rotate_vel_mode) {
								timer_start(&VEL_TIMER);
								tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
								tmc4671_setVelocityTarget(MOTOR, reeler_info.velocity.limit);
								DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled\n");
							}
						}
						break;
					}
					case AXC_DISABLE: {
						p_reeler_info->flags.is_hybrid_trig_enabled = false;
						p_reeler_info->flags.rotate_vel_mode = false;
						DBG_Printf(ERR_LVL_INFO, "\nHybrid Trigger one shot flag Disabled\n");
						break;
					}
					case AXC_PAUSE: {
						if(p_reeler_info->hybrid.one_shot_armed) {
							DBG_Printf(ERR_LVL_INFO, "[HYB] PAUSE on ONE_SHOT ignored - One-Shot move active\n");
						} else {
							p_reeler_info->flags.is_paused = true;
						}
						break;
					}
					default: DBG_Printf(ERR_LVL_INFO, "\nHybrid Trigger Invalid Operation Rxcvd\n"); break;
				}
				break;
			}
			default: break;
		}
	}
	return;
}