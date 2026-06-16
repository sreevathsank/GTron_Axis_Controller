/*
 * gtron_can_cmd_parser.c
 *
 * Created: 29-07-2025 18:51:04
 *  Author: sreevathsank
 */ 

#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

volatile Motor_Info_t guide_info;
volatile Motor_Info_t *p_guide_info = &guide_info;

volatile Motor_Info_t reeler1_info;
volatile Motor_Info_t *p_reeler1_info = &reeler1_info;

volatile Motor_Info_t varrest1_info;
volatile Motor_Info_t *p_varrest1_info = &varrest1_info;

volatile Motor_Info_t varrest2_info;
volatile Motor_Info_t *p_varrest2_info = &varrest2_info;

volatile Motor_Info_t reeleradj1_info;
volatile Motor_Info_t *p_reeleradj1_info = &reeleradj1_info;

volatile Motor_Info_t reeleradj2_info;
volatile Motor_Info_t *p_reeleradj2_info = &reeleradj2_info;

volatile Motor_Info_t *mot_array[] = { NULL, NULL, NULL};

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
	p_reeler1_info->flags.move_given = 0;
	p_reeler1_info->flags.rotate_vel_mode = 0;
	p_reeler1_info->flags.sag_enabled = 0;
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
	DBG_Printf(ERR_LVL_INFO, "Reeler Homing Cmd Rxcvd\n");
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
		(move_to_by == MOVE_TO) ? move_With_S_Ramp(target_position, p_reeler1_info->velocity.limit, MOVE_TO) \
								: move_With_S_Ramp(target_position, p_reeler1_info->velocity.limit, MOVE_BY);	
	} else {
		tmc4671_setVelocityLimit(MOTOR, p_reeler1_info->velocity.limit);
		(move_to_by == MOVE_TO) ? tmc4671_setAbsolutTargetPosition(MOTOR, target_position) \
								: tmc4671_setRelativeTargetPosition(MOTOR, target_position);
	}
	
	if(p_reeler1_info->hybrid.mode == HYBRID_MODE_N_SHOT) {
		p_reeler1_info->flags.sensor_trigger		= false;
		p_reeler1_info->hybrid.one_shot_armed	= true;
		DBG_Printf(ERR_LVL_DEBUG, "[HYB] One-Shot armed for this move\n");
	}
	(move_to_by == MOVE_TO) ?	DBG_Printf(ERR_LVL_INFO, "Reeler Move To %ld steps\n", target_position) \
							:	DBG_Printf(ERR_LVL_INFO, "Reeler Move By %ld steps\n", target_position);
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
	p_reeler1_info->velocity.limit = reeler_target_velocity;
	tmc4671_setVelocityLimit(MOTOR, p_reeler1_info->velocity.limit);
	p_reeler1_info->position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, p_reeler1_info->position.current);
	DBG_Printf(ERR_LVL_DEBUG, "Reeler Set Velocity %ld rpm\n", p_reeler1_info->velocity.limit);
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
	p_reeler1_info->position.trig_step_size = trig_step_size;
	p_reeler1_info->position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, p_reeler1_info->position.current);
	DBG_Printf(ERR_LVL_DEBUG, "Reeler Set Teeth Number or Trigger Step Size as %ld\n", p_reeler1_info->position.trig_step_size );
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
	p_reeler1_info->position.initial = reeler_initial_position;
	reeler_Move(p_reeler1_info->position.initial, MOVE_TO);
	DBG_Printf(ERR_LVL_DEBUG, "Reeler Set Initial Position to %ld steps\n", p_reeler1_info->position.initial);
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
	if(p_reeler1_info->flags.is_paused)	{
		p_reeler1_info->flags.sensor_trigger = false;
		tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
		p_reeler1_info->flags.rotate_vel_mode = true;
		if(p_reeler1_info->flags.sag_enabled && p_reeler1_info->flags.rotate_vel_mode) {
			timer_start(&VEL_TIMER);
			DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled");
		}
		p_reeler1_info->flags.is_paused = false;
		DBG_Printf(ERR_LVL_DEBUG, "[HYB] Reeler Resumed\n");
		return;
	}
	p_reeler1_info->flags.rotate_vel_mode = true;
	p_reeler1_info->flags.is_paused = false;
	if(p_reeler1_info->flags.sag_enabled && p_reeler1_info->flags.rotate_vel_mode) {
		timer_start(&VEL_TIMER);
		tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
		tmc4671_setVelocityTarget(MOTOR, p_reeler1_info->velocity.limit);
		DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled");
	}
	if(p_reeler1_info->hybrid.mode == HYBRID_MODE_INSPECTION) {
		p_reeler1_info->hybrid.first_trigger_skip	= true;
		p_reeler1_info->hybrid.consecutive_slips		= 0;
		p_reeler1_info->hybrid.cycle_armed			= false;
		p_reeler1_info->flags.sensor_trigger			= false;
	}
	
	DBG_Printf(ERR_LVL_DEBUG,"\nReeler Start Motor with Velocity %ld rpm\n", p_reeler1_info->velocity.limit);
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
	p_reeler1_info->flags.rotate_vel_mode		= false;
	p_reeler1_info->flags.sag_enabled			= false;
	p_reeler1_info->hybrid.one_shot_armed		= false;
	p_reeler1_info->flags.is_paused				= false;
	p_reeler1_info->hybrid.cycle_armed			= false;
	p_reeler1_info->hybrid.first_trigger_skip	= true;
	p_reeler1_info->hybrid.consecutive_slips		= 0;
	p_reeler1_info->flags.is_hybrid_trig_enabled = false;
	//reeler_info.position.trig_step_size = 0;
	homing_v = 0;
	//if(!reeler_info.flags.sag_enabled || !reeler_info.flags.rotate_vel_mode)
	{
		timer_stop(&VEL_TIMER);
	}
	trig_no = 0;
	prev_trig_no = 0;
	p_reeler1_info->position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, p_reeler1_info->position.current);
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
	p_reeler1_info->flags.rotate_vel_mode = false;
	p_reeler1_info->flags.sag_enabled = false;
	homing_v = 0;
	timer_stop(&VEL_TIMER);
	trig_no = 0;
	prev_trig_no = 0;
	p_reeler1_info->position.current = tmc4671_getActualPosition(MOTOR);
	tmc4671_setAbsolutTargetPosition(MOTOR, p_reeler1_info->position.current);
	tmc4671_setVelocityLimit(MOTOR, 2);
	tmc4671_setModeMotion(MOTOR, POSITION_MODE);
	p_reeler1_info->flags.is_paused = true;
	DBG_Printf(ERR_LVL_INFO, "Reeler Pause Motor\n");
	return;
}


/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void reeler_Get_Position( void )
{
	int32_t reeler_position = tmc4671_getActualPosition(MOTOR);
	int32_t reel_pos_within_rot = reeler_position & 0xFFFF;
	DBG_Printf(ERR_LVL_DEBUG, "The current Reeler Position is = ABS %ld usteps | REL %ld usteps", reeler_position, reel_pos_within_rot);
	can_AxC_Write(CAN_REPLY_TOP_RACK_ID, REELER_MOTOR, AXC_CURRENT_POSITION, reel_pos_within_rot);
	return;
}


/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void reeler_Set_Encoder_Mode( int32_t enc_mode ) 
{
	p_reeler1_info->flags.is_encoder_mode = (enc_mode == 0) ? false : true;
	DBG_Printf(ERR_LVL_DEBUG, "Set Encoder Mode | val = %ld | Encoder Mode = %d", enc_mode, p_reeler1_info->flags.is_encoder_mode);
	return;
}

/************************************************************************/
/* Guide Vertical Arrestor Functions                                    */
/************************************************************************/

static bool check_Open_Right_Limit_Status( Motor_Info_t *m )
{
	if(m == NULL) {
		DBG_Printf(ERR_LVL_ERROR, "check_Open_Right_Limit_Status() m null ptr received\n");
		return false;
	}
	// Read the INTCAP register to get the pin states and clear the register.
	if( IOXP_Read_Byte(IOXP_REG_INTCAP_RD_ONLY, &gtron_limits.limit_flags) == IOXP_TRANSFER_FAIL ) {
		DBG_Printf(ERR_LVL_ERROR, "check_Open_Right_Limit_Status() IOXP comms failed\n");
		return false;
	}
	
	if(m->comms.uart_addr == TMC2209_MOT_ADDR1)
	{
		if(MSK_MOT1_R_LIM(gtron_limits.limit_flags))
		{
			DBG_Printf(ERR_LVL_DEBUG, "Inside MSK_MOT1_R_LIM\n");
			if( (m->mot_name == MOTOR_VARREST1) ||
			(m->mot_name == MOTOR_REELERADJ1) ||
			(m->mot_name == MOTOR_FRONT_CAM) )
			{
				DBG_Printf(ERR_LVL_ERROR, "Single Limit Motor Open Right Limit Hit!\n");
			} else {
				DBG_Printf(ERR_LVL_ERROR, "Double Limit Motor Open Right Limit Hit!\n");
			}
			return true;
		} 
		else 
		{
			return false;
		}
	} 
	else if(m->comms.uart_addr == TMC2209_MOT_ADDR3)
	{
		if(MSK_MOT2_R_LIM(gtron_limits.limit_flags))
		{
			DBG_Printf(ERR_LVL_DEBUG, "Inside MSK_MOT2_R_LIM\n");
			if( (m->mot_name == MOTOR_VARREST2) ||
			(m->mot_name == MOTOR_REELERADJ2) ||
			(m->mot_name == MOTOR_FRONT_CAM) )
			{
				DBG_Printf(ERR_LVL_ERROR, "Single Limit Motor Open Right Limit Hit!\n");
			} else {
				DBG_Printf(ERR_LVL_ERROR, "Double Limit Motor Open Right Limit Hit!\n");
			}
			return true;
		}
		else 
		{
			return false;
		}
	}
	else 
	{
		DBG_Printf(ERR_LVL_ERROR, "UART Address not part of current config -> %d\n", m->comms.uart_addr);
		return false;
	}
	return false;
}

static bool check_Close_Left_Limit_Status( Motor_Info_t *m )
{
	if(m == NULL) {
		DBG_Printf(ERR_LVL_ERROR, "check_Close_Left_Limit_Status() m null ptr received\n");
		return false;
	}
	// Read the INTCAP register to get the pin states and clear the register.
	if( IOXP_Read_Byte(IOXP_REG_INTCAP_RD_ONLY, &gtron_limits.limit_flags) == IOXP_TRANSFER_FAIL ) {
		DBG_Printf(ERR_LVL_ERROR, "check_Close_Left_Limit_Status() IOXP comms failed\n");
		return false;
	}
	
	if(m->comms.uart_addr == TMC2209_MOT_ADDR1)
	{
		if(MSK_MOT1_L_LIM(gtron_limits.limit_flags))
		{
			DBG_Printf(ERR_LVL_DEBUG, "Inside MSK_MOT1_R_LIM\n");
			if( (m->mot_name == MOTOR_VARREST1) ||
			(m->mot_name == MOTOR_REELERADJ1) ||
			(m->mot_name == MOTOR_FRONT_CAM) )
			{
				DBG_Printf(ERR_LVL_ERROR, "Single Limit Motor Close Left Limit Hit!\n");
			} else {
				DBG_Printf(ERR_LVL_ERROR, "Double Limit Motor Close Left Limit Hit!\n");
			}
			return true;
		}
		else
		{
			return false;
		}
	} 
	else if(m->comms.uart_addr == TMC2209_MOT_ADDR3) 
	{
		if(MSK_MOT2_R_LIM(gtron_limits.limit_flags))
		{
			DBG_Printf(ERR_LVL_DEBUG, "Inside MSK_MOT2_R_LIM\n");
			if( (m->mot_name == MOTOR_VARREST2) ||
			(m->mot_name == MOTOR_REELERADJ2) ||
			(m->mot_name == MOTOR_FRONT_CAM) )
			{
				DBG_Printf(ERR_LVL_ERROR, "Single Limit Motor Close Left Limit Hit!\n");
			} else {
				DBG_Printf(ERR_LVL_ERROR, "Double Limit Motor Close Left Limit Hit!\n");
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		DBG_Printf(ERR_LVL_ERROR, "UART Address not part of current config -> %d\n", m->comms.uart_addr);
		return false;
	}
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void tmc2209_Move(Motor_Info_t *motor_info, int32_t target_position, bool move_to_by)
{
	motor_info->flags.move_given = true;
	motor_info->position.current = motor_info->step_tracker.total_steps;
	motor_info->velocity.target  = 1000; 
	is_tmc2209_mot_moving = true;
	
	if(move_to_by == MOVE_TO) { motor_info->position.target = target_position; }					// Absolute Move.
															   
	// Check if the target position is greater or less than the current position.
	if(target_position > motor_info->position.current) {
		if(move_to_by == MOVE_BY)  
		{ motor_info->position.target = motor_info->position.current + target_position; }
			
		//tmc2209_writeRegister(TMC2209_MOTOR1_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
		tmc2209_set_velocity(motor_info->comms.uart_addr, motor_info, motor_info->velocity.target);
		DBG_Printf(ERR_LVL_DEBUG, "\nMove To: Current Pos = %ld | Target Pos = %ld | Velocity = %ld ustep/s\n", \
								motor_info->position.current, target_position, motor_info->velocity.target);
		motor_info->motor_state = MOTOR_MOVING_STATE;
		if( !(motor_info->position.target == motor_info->position.current) ) {
			motor_info->time_ms.theoretical_move = (abs(motor_info->position.target - motor_info->position.current) / motor_info->velocity.target) * 1000;
			DBG_Printf(ERR_LVL_DEBUG, "Theoretical Move time = %ld ms\n", motor_info->time_ms.theoretical_move);
			motor_info->time_ms.move_start		 = millis();
		}
	} else if(target_position < motor_info->position.current) {
		if(move_to_by == MOVE_BY)
		{ motor_info->position.target = motor_info->position.current - target_position; }
		
		//tmc2209_writeRegister(TMC2209_MOTOR1_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
		tmc2209_set_velocity(motor_info->comms.uart_addr, motor_info, (-motor_info->velocity.target) );
		DBG_Printf(ERR_LVL_DEBUG, "\nMove To: Current Pos = %ld | Target Pos = %ld | Velocity = %ld ustep/s\n", \
								motor_info->position.current, target_position, (-motor_info->velocity.target) );
		motor_info->motor_state = MOTOR_MOVING_STATE;
		if( !(motor_info->position.target == motor_info->position.current) ) {
			motor_info->time_ms.theoretical_move = (abs(motor_info->position.target - motor_info->position.current) / motor_info->velocity.target) * 1000;
			DBG_Printf(ERR_LVL_DEBUG, "Theoretical Move time = %ld ms\n", motor_info->time_ms.theoretical_move);
			motor_info->time_ms.move_start		 = millis();
		}
	} else {
		DBG_Printf(ERR_LVL_DEBUG, "\nTarget Position is same as Current Position. Not Moving...\n");
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
static void tmc2209_Move_To_Open_Limit(Motor_Info_t *motor_info )
{
	uint8_t limit_status = 0;
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_status);
	if(MSK_MOT1_R_LIM(limit_status)) {
		DBG_Printf(ERR_LVL_DEBUG, "\nAlready in Open Limit. Not moving towards Open Limit\n");
		
		// Send the CAN Command
		message_Id = CAN_REPLY_TOP_RACK_ID;
		can_tx_frame.data[0] = GUIDE_OPEN_LIMIT;
		can_tx_frame.data[1] = AXC_PRESSED;
		can_Write(message_Id, can_tx_frame.data_64bit);
		return;
	}
	//tmc2209_writeRegister(motor_info->comms.uart_addr, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	tmc2209_set_velocity(motor_info->comms.uart_addr, motor_info, 0x00000FA0);
	motor_info->flags.move_to_open_lim = true;
	motor_info->flags.is_tmc2209_homing = true;
	DBG_Printf(ERR_LVL_DEBUG, "\nGuide Move To Open Limit Cmd Rxcvd\n");
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void tmc2209_Move_To_Close_Limit(Motor_Info_t *motor_info )
{
	uint8_t limit_status = 0;
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_status);
	
	motor_info->flags.is_tmc2209_homing = true;
	
	if(motor_info->comms.uart_addr == TMC2209_MOT_ADDR1) {
		if(MSK_MOT1_L_LIM(limit_status)) {
			DBG_Printf( ERR_LVL_DEBUG, "Already in Close Limit. Not moving towards Close Limit\n");
			
			// Send the CAN Command
			message_Id = CAN_REPLY_TOP_RACK_ID;
			can_tx_frame.data[0] = GUIDE_CLOSE_LIMIT;
			can_tx_frame.data[1] = AXC_PRESSED;
			can_Write(message_Id, can_tx_frame.data_64bit);
			return;
		}
	}
	//tmc2209_writeRegister(motor_info->comms.uart_addr, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	tmc2209_set_velocity(motor_info->comms.uart_addr, motor_info, 0xFFFFF060);
	//tmc2209_set_velocity(motor_info->comms.uart_addr, motor_info, 0xFFFFF060);
	motor_info->flags.move_to_close_lim = true;
	DBG_Printf(ERR_LVL_DEBUG, "\nGuide Move to Close Limit Cmd Rxcvd\n");
	return;
}

static void tmc2209_Reference_Search( Motor_Info_t *m )
{
	m->flags.homing = true;
	m->flags.move_to_close_lim = true;
	bool close_lim_status = check_Close_Left_Limit_Status(m);
	DBG_Printf(ERR_LVL_DEBUG, "Close Limit Status = %d\n", close_lim_status);
	
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void tmc2209_Set_Velocity(Motor_Info_t *motor_info, int32_t target_velocity)
{
	motor_info->velocity.target = target_velocity;
	DBG_Printf(ERR_LVL_DEBUG, "\nGuide Varrest Velocity Set to %ld usteps/sec\n", motor_info->velocity.target);
	return;
}

/** 
 * \brief
 *
 * @param
 *
 * @return
 **/
static void tmc2209_Set_Initial_Position(Motor_Info_t *motor_info, int32_t initial_position)
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
void tmc2209_Stop_Motor(Motor_Info_t *m)
{
	tmc2209_writeRegister(m->comms.uart_addr, TMC2209_VACTUAL, 0x00000000);
	is_tmc2209_mot_moving = false;
	m->motor_state = MOTOR_STOPPED_STATE;
	m->flags.homing = 0;
	m->flags.move_given = 0;
	m->flags.move_to_open_lim = 0;
	m->flags.move_to_close_lim = 0;
	DBG_Printf(ERR_LVL_DEBUG, "\nGuide Motor Stop\n");
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
static void tmc2209_Limits_Status_Check(Motor_Info_t *motor_info)
{
	uint8_t limit_reg_value = 0;
	//tmc2209_writeRegister(TMC2209_MOTOR1_ADDR, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	IOXP_Read_Byte(IOXP_REG_GPIO, &limit_reg_value);
	if(axis_id == GTRON_AXC_TOP) { message_Id = CAN_REPLY_TOP_RACK_ID; }
	else if(axis_id == GTRON_AXC_BOT) { message_Id = CAN_REPLY_BOT_RACK_ID; }
	if( (limit_reg_value >> MOT1_R_LIM_BIT & 1) ) {
		can_tx_frame.data[0] = GUIDE_MOTOR;
		can_tx_frame.data[1] = AXC_PRESSED;
		for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
		can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
		DBG_Printf(ERR_LVL_DEBUG, "\nGuide Open Right Limit is HIT!\n");
	} else {
		can_tx_frame.data[0] = GUIDE_MOTOR;
		can_tx_frame.data[1] = AXC_NOT_PRESSED;
		for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
		can_Write(message_Id, (int32_t)can_tx_frame.data_64bit);
		DBG_Printf(ERR_LVL_DEBUG, "\nGuide Open Right Limit is not HIT!\n");
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
		case 200: {
			if(sbridge_addr == VARREST_1_2_SOLENOID) {
				rack_id = TOP_RACK;
				DBG_Printf(ERR_LVL_DEBUG, "TOP VARREST 1 2 Message ID Rxcvd from MI - 200\n");
			} else {
				DBG_Printf(ERR_LVL_DEBUG, "TOP Invalid Message ID Rxcvd from MI - 200\n");
			}
			break;
		}
		case CAN_TOP_RACK_ID: {
			if(sbridge_addr == REELER1_GUIDE_REELERADJ1) {
				rack_id = TOP_RACK; 
				DBG_Printf(ERR_LVL_DEBUG, "TOP Rack REELER1_GUIDE_REELADJ1 Message ID Rxcvd from MI\n");
			}
			break;
		}
		case CAN_BOT_RACK_ID: {
			rack_id = BOT_RACK; 
			DBG_Printf(ERR_LVL_DEBUG, "BOT Rack Message ID Rxcvd from MI\n");
			break;
		}
		case CAN_TOP_SAG_REELER_ID: {
			if(sbridge_addr == REELER1_GUIDE_REELERADJ1) {
				rack_id = TOP_RACK;
				DBG_Printf(ERR_LVL_DEBUG, "TOP Sag Reeler Message ID Rxcvd from Sys Ctrl\n");
				if(!p_reeler1_info->flags.rotate_vel_mode) { break; }
				switch(rx_can_cmd_info.data[0])
				{
					case 1: {
						p_reeler1_info->flags.sag_enabled = true;
						if(p_reeler1_info->flags.sag_enabled & p_reeler1_info->flags.rotate_vel_mode) {
							trig_no = 0;
							prev_trig_no = 0;
							timer_start(&VEL_TIMER);
							tmc4671_setVelocityLimit(MOTOR, p_reeler1_info->velocity.limit);
							tmc4671_setVelocityTarget(MOTOR, p_reeler1_info->velocity.limit);
						}
						DBG_Printf(ERR_LVL_DEBUG, "\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Rotate.\n");
						break;
					}
					case 0: {
						p_reeler1_info->flags.sag_enabled = false;
						if(!p_reeler1_info->flags.sag_enabled || !p_reeler1_info->flags.rotate_vel_mode) {
							trig_no = 0;
							prev_trig_no = 0;
							timer_stop(&VEL_TIMER);
						}
						tmc4671_setVelocityTarget(MOTOR, 0);
						DBG_Printf(ERR_LVL_DEBUG, "\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Stop.\n");
						break;
					}
					default: DBG_Printf(ERR_LVL_DEBUG, "\nSag Sensor Invalid Operation Rxcvd\n"); break;
				}
			}
			break;
		}
		case CAN_BOT_SAG_REELER_ID: {
			rack_id = BOT_RACK;
			DBG_Printf(ERR_LVL_DEBUG, "\nBOTTOM Sag Reeler Message ID Rxcvd from Sys Ctrl\n");
			if(!p_reeler1_info->flags.rotate_vel_mode) { break; }
			switch(rx_can_cmd_info.data[0])
			{
				case 1:
					p_reeler1_info->flags.sag_enabled = true;
					if(p_reeler1_info->flags.sag_enabled & p_reeler1_info->flags.rotate_vel_mode)
					{
						timer_start(&VEL_TIMER);
					}
					DBG_Printf(ERR_LVL_DEBUG, "\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Rotate.\n");
				break;
				case 0:
					p_reeler1_info->flags.sag_enabled = false;
					//if(!reeler_info.flags.sag_enabled & !reeler_info.flags.rotate_vel_mode)
					{
						timer_stop(&VEL_TIMER);
					}
					tmc4671_setVelocityTarget(MOTOR, 0);
					DBG_Printf(ERR_LVL_DEBUG, "\nSag Sensor Enable Operation Rxcvd. Reeler Motor is ready to Stop.\n");
				break;
				default: DBG_Printf(ERR_LVL_DEBUG, "\nSag Sensor Invalid Operation Rxcvd\n");					break;
			}
			break;
		}
		case CAN_BOARD_ACTIVE_PING_ID: {
			if( (axis_id == GTRON_AXC_TOP) && (can_rx_frame.data[0] == TOP_AXC_BOARD_ID) ) {
				message_Id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
				can_tx_frame.data[0] = TOP_AXC_BOARD_ID;
				can_Write(message_Id, can_tx_frame.data_64bit);
				DBG_Printf(ERR_LVL_DEBUG, "\nGTron Top AxC Board Active Ping Rxcvd\t Board Active Ping Reply Sent\n");
			} else if( (axis_id == GTRON_AXC_BOT) && (can_rx_frame.data[0] == BOT_AXC_BOARD_ID) ) {
				message_Id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
				can_tx_frame.data[0] = BOT_AXC_BOARD_ID;
				can_Write(message_Id, can_tx_frame.data_64bit);
				DBG_Printf(ERR_LVL_DEBUG, "\nGTron Bottom AxC Board Active Ping Rxcvd\t Board Active Ping Reply Sent\n");
			}
			break;
		}
		case CAN_IO_TO_TOP_AXC_ID: {
			rack_id = TOP_RACK;
			DBG_Printf(ERR_LVL_DEBUG, "\nTOP Rack Message ID Rxcvd from IO Ctrl\n");
			break;
		}
		case CAN_IO_TO_BOT_AXC_ID: {
			rack_id = BOT_RACK;
			DBG_Printf(ERR_LVL_DEBUG, "\nBOT Rack Message ID Rxcvd from IO Ctrl\n");
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
					case AXC_VELOCITY:			reeler_Set_Velocity( (int32_t)rx_can_cmd_info.value );			break;
					case AXC_ROTATE:			reeler_Move( TMC4671_ROTATION, MOVE_BY );					    break;
					case AXC_MOVE_TO:			reeler_Move( (int32_t)rx_can_cmd_info.value, MOVE_TO );			break;
					case AXC_MOVE_BY:			reeler_Move( (int32_t)rx_can_cmd_info.value, MOVE_BY );			break;
					case AXC_TEETH:				reeler_Set_Teeth( (uint32_t)rx_can_cmd_info.value );			break;
					case AXC_INITIAL_POSITION:	reeler_Set_Initial_Position( (int32_t)rx_can_cmd_info.value );	break;
					case AXC_CURRENT_POSITION:	reeler_Get_Position();											break;
					case AXC_HOMING:			reeler_Home();													break;
					case AXC_PAUSE:				reeler_Pause_Motor();											break;
					case AXC_ENCODER_MODE:		reeler_Set_Encoder_Mode( (int32_t)rx_can_cmd_info.value );		break;
					default: DBG_Printf(ERR_LVL_DEBUG, "Reeler Motor Invalid Operation Rxcvd\n");				break;
				}
			break;
			case GUIDE_MOTOR:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:					tmc2209_Stop_Motor(p_guide_info);											break;
					case AXC_VELOCITY:				tmc2209_Set_Velocity(p_guide_info, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:				tmc2209_Move(p_guide_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_TO:				tmc2209_Move(p_guide_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_BY:				tmc2209_Move(p_guide_info, (int32_t)rx_can_cmd_info.value, MOVE_BY);break;
					case AXC_MOVE_TO_OPEN_LIMIT:	tmc2209_Move_To_Open_Limit(p_guide_info);									break;
					case AXC_MOVE_TO_CLOSE_LIMIT:	tmc2209_Move_To_Close_Limit(p_guide_info);									break;
					case AXC_INITIAL_POSITION:		tmc2209_Set_Initial_Position(p_guide_info, (int32_t)rx_can_cmd_info.value);	break;
					case AXC_STATUS_CHECK:			tmc2209_Limits_Status_Check(p_guide_info);									break;
					default: DBG_Printf(ERR_LVL_DEBUG,"Guide Motor Invalid Operation Rxcvd\n");									break;
				}
			break;
			case VERITCAL_ARRESTOR_MOTOR1:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:				tmc2209_Stop_Motor(p_varrest1_info);											break;
					case AXC_VELOCITY:			tmc2209_Set_Velocity(p_varrest1_info, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:			tmc2209_Move(p_varrest1_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_TO:			tmc2209_Move(p_varrest1_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_BY:			tmc2209_Move(p_varrest1_info,(int32_t)rx_can_cmd_info.value, MOVE_BY);			break;
					case AXC_INITIAL_POSITION:	tmc2209_Set_Initial_Position(p_varrest1_info, (int32_t)rx_can_cmd_info.value);	break;
					case AXC_HOMING:			tmc2209_Reference_Search(p_varrest1_info);										break;
					default: DBG_Printf(ERR_LVL_DEBUG, "\nVert Arrestor Motor Invalid Operation Rxcvd\n");						break;
				}
			break;
			case GUIDE_OPEN_LIMIT:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: break;
					case AXC_DISABLE: break;
					case AXC_STATUS_CHECK: break;
					default: DBG_Printf(ERR_LVL_DEBUG, "Guide Open Limit Invalid Operation Rxcvd\n");					break;
				}
			break;
			case GUIDE_CLOSE_LIMIT:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: break;
					case AXC_DISABLE: break;
					case AXC_STATUS_CHECK: break;
					default: DBG_Printf(ERR_LVL_DEBUG, "Guide Close Limit Invalid Operation Rxcvd\n");					break;
				}
			break;
			case VERITCAL_ARRESTOR_MOTOR2:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:			   tmc2209_Stop_Motor(p_varrest2_info);												break;
					case AXC_VELOCITY:		   tmc2209_Set_Velocity(p_varrest2_info, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:		   tmc2209_Move(p_varrest2_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_TO:		   tmc2209_Move(p_varrest2_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);			break;
					case AXC_MOVE_BY:		   tmc2209_Move(p_varrest2_info, (int32_t)rx_can_cmd_info.value, MOVE_BY);			break;
					case AXC_INITIAL_POSITION: tmc2209_Set_Initial_Position(p_varrest2_info, (int32_t)rx_can_cmd_info.value);	break;
					default: DBG_Printf(ERR_LVL_DEBUG, "\nVert Arrestor Motor Invalid Operation Rxcvd\n");						break;
				}	
			break;
			case REELER_ADJ_MOTOR1:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:			   tmc2209_Stop_Motor(p_reeleradj1_info);											break;
					case AXC_VELOCITY:		   tmc2209_Set_Velocity(p_reeleradj1_info, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:		   tmc2209_Move(p_reeleradj1_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_TO:		   tmc2209_Move(p_reeleradj1_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_BY:		   tmc2209_Move(p_reeleradj1_info,(int32_t)rx_can_cmd_info.value, MOVE_BY);			break;
					case AXC_INITIAL_POSITION: tmc2209_Set_Initial_Position(p_reeleradj1_info, (int32_t)rx_can_cmd_info.value);	break;
					default: DBG_Printf(ERR_LVL_DEBUG, "\nVert Arrestor Motor Invalid Operation Rxcvd\n");						break;
				}
			break;
			case REELER_ADJ_MOTOR2:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_STOP:			   tmc2209_Stop_Motor(p_reeleradj2_info);											break;
					case AXC_VELOCITY:		   tmc2209_Set_Velocity(p_reeleradj2_info, (int32_t)rx_can_cmd_info.value);			break;
					case AXC_ROTATE:		   tmc2209_Move(p_reeleradj2_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_TO:		   tmc2209_Move(p_reeleradj2_info, (int32_t)rx_can_cmd_info.value, MOVE_TO);		break;
					case AXC_MOVE_BY:		   tmc2209_Move(p_reeleradj2_info, (int32_t)rx_can_cmd_info.value, MOVE_BY);		break;
					case AXC_INITIAL_POSITION: tmc2209_Set_Initial_Position(p_reeleradj2_info, (int32_t)rx_can_cmd_info.value); break;
					default: DBG_Printf(ERR_LVL_DEBUG, "\nVert Arrestor Motor Invalid Operation Rxcvd\n");						break;
				}
			break;
			case SOLENOIDS:
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					default: break;
				}
			break;
			case HYBRID_TRIGGER_INSPECTION: {
				switch(rx_can_cmd_info.data[OPERATION_BYTE_IDX])
				{
					case AXC_ENABLE: {
						p_reeler1_info->hybrid.mode						= HYBRID_MODE_INSPECTION;
						p_reeler1_info->hybrid.first_trigger_skip		= true;
						p_reeler1_info->hybrid.consecutive_slips		= 0;
						p_reeler1_info->hybrid.cycle_armed				= false;
						p_reeler1_info->flags.sensor_trigger			= false;
						p_reeler1_info->flags.is_hybrid_trig_enabled	= true;
						DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger flag Enabled\n");
						break;
					}
					case AXC_DISABLE: {
						p_reeler1_info->hybrid.mode						= HYBRID_MODE_OFF;
						p_reeler1_info->hybrid.cycle_armed				= false;
						p_reeler1_info->flags.is_hybrid_trig_enabled	= false;
						DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger flag Disabled\n");
						break;
					}
					case AXC_TOLERABLE_SLIPS: {
						p_reeler1_info->hybrid.total_slips = (uint16_t)rx_can_cmd_info.value;
						DBG_Printf(ERR_LVL_INFO, "Tolerable Slips received = %d\n", p_reeler1_info->hybrid.total_slips);
						break;
					}
					case AXC_PAUSE: {
						p_reeler1_info->flags.is_paused = true;
						reeler_Pause_Motor();
						p_reeler1_info->hybrid.mode = HYBRID_MODE_OFF;
						DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Inspection PAUSED\n");	
						break;
					}
					case AXC_N_SHOT: {
						p_reeler1_info->hybrid.total_n_shots = (uint32_t)rx_can_cmd_info.value;
						p_reeler1_info->flags.is_paused = false;
						if(p_reeler1_info->hybrid.total_n_shots == 0) {
							if(p_reeler1_info->flags.is_encoder_mode) {
								DBG_Printf(ERR_LVL_INFO, "[ENC] Total N Shots = %ld | Inspection\n", p_reeler1_info->hybrid.total_n_shots);
							} else {
								DBG_Printf(ERR_LVL_INFO, "[HYB] Total N Shots = %ld | Inspection\n", p_reeler1_info->hybrid.total_n_shots);
							}
							
							p_reeler1_info->hybrid.mode						= HYBRID_MODE_INSPECTION;
							p_reeler1_info->hybrid.first_trigger_skip		= true;
							p_reeler1_info->hybrid.consecutive_slips		= 0;
							p_reeler1_info->hybrid.cycle_armed				= false;
							p_reeler1_info->flags.sensor_trigger			= false;
							p_reeler1_info->flags.is_hybrid_trig_enabled	= true;
							p_reeler1_info->hybrid.prev_anchor_pos			= tmc4671_getActualPosition(MOTOR);
							if(p_reeler1_info->flags.is_encoder_mode) {
								DBG_Printf(ERR_LVL_INFO, "[ENC] Encoder Trigger flag Enabled for Inspection\n");
							} else {
								DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger flag Enabled for Inspection\n");
							}
						} else {
							if(p_reeler1_info->flags.is_encoder_mode) {
								DBG_Printf(ERR_LVL_INFO, "[ENC] Encoder Trigger N Shot flag Enabled | No of N Shots = %ld\n", p_reeler1_info->hybrid.total_n_shots);
							} else {
								DBG_Printf(ERR_LVL_INFO, "[HYB] Hybrid Trigger N Shot flag Enabled | No of N Shots = %ld\n", p_reeler1_info->hybrid.total_n_shots);
							}
							p_reeler1_info->hybrid.mode						= HYBRID_MODE_N_SHOT;
							p_reeler1_info->flags.is_hybrid_trig_enabled	= true;
							p_reeler1_info->hybrid.consecutive_slips		= 0;
							p_reeler1_info->flags.sag_enabled				= true;
							p_reeler1_info->hybrid.cycle_armed				= false;
							p_reeler1_info->flags.rotate_vel_mode			= true;
							p_reeler1_info->hybrid.curr_n_shots				= 0;
							p_reeler1_info->hybrid.prev_anchor_pos			= tmc4671_getActualPosition(MOTOR);
							if(p_reeler1_info->flags.sag_enabled && p_reeler1_info->flags.rotate_vel_mode) {
								timer_start(&VEL_TIMER);
								tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
								tmc4671_setVelocityTarget(MOTOR, p_reeler1_info->velocity.limit);
								DBG_Printf(ERR_LVL_DEBUG, "Reeler Start: VEL_TIMER Started | Sag and Rotate Vel Mode Enabled\n");
							}
						}
						p_reeler1_info->hybrid.total_slips = (p_reeler1_info->hybrid.total_slips == 0)
															? HYBRID_ALERT_THRESHOLD
															: p_reeler1_info->hybrid.total_slips;
						DBG_Printf(ERR_LVL_DEBUG, "Total Tolerable Continuous Slips set as %d\n", p_reeler1_info->hybrid.total_slips);
						break;
					}
					case AXC_TERMINAL_WIDTH: {
						p_reeler1_info->hybrid.term_width = (uint32_t)rx_can_cmd_info.value;
						DBG_Printf(ERR_LVL_INFO, "Hybrid Terminal Width received = %ld usteps", p_reeler1_info->hybrid.term_width);
						break;
					}
					default: DBG_Printf(ERR_LVL_INFO, "\nHybrid Trigger Invalid Operation Rxcvd\n"); break;
				}
				break;
			}
		}
	}
	return;
}