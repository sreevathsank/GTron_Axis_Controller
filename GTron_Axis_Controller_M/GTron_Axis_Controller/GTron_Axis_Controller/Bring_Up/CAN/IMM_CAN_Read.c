/*
 * IMM_CAN.c
 *
 * Created: 08-01-2024 11:17:03
 *  Author: sreevathsank
 */ 
/** 
 * \file
 *
 * \brief Contains the functions necessary for reading and processing CAN message id and data.
 */

#include "Bring_Up/CAN/IMM_CAN_Read.h"

/** 
 * \brief Checks if the receive counter is greater than 0. If so, it decrements it and reads the CAN receive buffer and calls the message id decode function.
 * 
 * @param void
 * @return void
 */
void can_Read(void)
{
	int32_t data;
	if(can_rx_int)
	{
		can_rx_int--;
		can_rx_frame.data_64bit = 0;
		message_Id = 0;
		ad = 0; cmd = 0; typ = 0; mot = 0;
		
		can_receive(&CAN_1, &message_Id, &can_rx_frame);
		data = can_rx_frame.data_64bit;
		can_Message_Decode(message_Id, data);
	}
	return;
}

void can_Message_Send(int32_t tx_message)
{
	//int32_t tx_message = rand() & 127;
	
	can_send(&CAN_1, tx_message, EXT_ID, 0, can_tx_frame);
	//printf("\nThe value sent = &x\n", tx_message);
	
	return;
}

/** 
 * \brief Checks the CRC of the incoming TMCL-IDE message id and data. The CRC is calculated by adding first 8 bytes of the TMCL datagram and storing the sum's LSB in the 9th byte(CRC).
 *
 * @param[in] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in] data Contains the 4 byte Value and 1 byte CRC.
 * @return boolean True if Checksum satisfies, False if it does not.
 */
static bool can_Message_Crc_Check(uint32_t message_Id, int32_t data)
{
	ad = (message_Id >> 25) & 0x0F;
	cmd = (message_Id >> 17) & 0xFF;
	typ = (message_Id >> 9) & 0xFF;
	mot = message_Id & 0x1FF;
	
	crc = can_rx_frame.data[4];
	
	checksum = ad + cmd + typ + mot + can_rx_frame.data[0] + can_rx_frame.data[1] + can_rx_frame.data[2] + can_rx_frame.data[3];
	
	return (crc == checksum);
}

/** 
 * \brief This function handles the spoofing of SAMC21 as Landungsbruecke by replying hardcoded values most of the time.
 *
 * @param[in] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void can_Message_Handshake_Tmcl_Ide(uint32_t message_Id, int32_t data)
{
	switch(cmd)
	{
		case VERSION:
			reply_Version(message_Id, data);
		break;
		case GGP:
			reply_GGP(message_Id, data);
		break;
		case ASSIGNMENT:
			reply_Assignment(message_Id, data);
		break;
		case GIO:
			reply_GIO(message_Id, data);
		break;
		case GAP:
			reply_GAP(message_Id, data);
		break;
		case ROR:
			reply_ROR(message_Id, data);
		break;
		case ROL:
			reply_ROL(message_Id, data);
		break;
		case MVP:
			reply_MVP(message_Id, data);
		break;
		case MST:
			reply_MST(message_Id, data);
		break;
		case RD_MC:
			reply_RD_MC(message_Id, data);
		break;
		case WR_MC:
			reply_WR_MC(message_Id, data);
		break;
	}
}

int32_t speed;

/** 
 * \brief This function is responsible for replying to MCD commands.
 * 
 * @param[in] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void can_Message_Operational_v3_XAxis(uint32_t message_Id, int32_t data)
{	/* The breakdown of reply format for v3 MCD commands. (used by the "reply_MCD_common()" function)
	 *		0C				 02			  64		   XX
	 * Reply Address | Module Address | Status | Command Number
	 *
	 * Check MCD_json for in-detail values
	 */
	switch(message_Id)
	{
		case CAN_BOOT_X_ID:
			sw_reset();
		break;
		case CAN_EXT_FLASH_ID:
			//check_cdone();
			message_Id = CAN_INIT ;
		break;
		case CAN_BIN_FILE_ERASE:
			//erase_can_flash();
			message_Id = CAN_INIT ;
		break;
		case CAN_BIN_FILE_WRITE:
			//write_can_flash();
			can_rx_frame.data_64bit = 0x00;
			message_Id = CAN_INIT ;
		break;
		case MOVE_DONE_PING_X:
			do_Move_Done_Ping();
			PRINTF_DEBUG && printf(" MOVE_DONE_PING_X\n");
		break;
		case PING_X:
			do_4671_Ping();
			PRINTF_DEBUG && printf(" PING_X\n");
		break;
		case REF_SEARCH_PING_X:
		{
			rfs_ping_rxvd = true;
			do_Ref_Search_Ping();
			PRINTF_DEBUG && printf(" REF_SEARCH_PING_X\n");	
			break;
		}
		case MAX_ACCEL_X:
		case MAX_DECCEL_X:
		case HOME_SEARCH_VEL_X:
		case HOME_SWITCH_VEL_X:
		case HOMING_MODE_X:
		case OPEN_CLOSED_LOOP_X:
		case CORRECTION_VEL_P_X:
		case CORRECTION_VEL_I_X:
		case CORRECTION_VEL_I_CLIP_X:
		case CORRECTION_VEL_DV_CLK_X:
		case CORRECTION_VEL_DV_CLIP_X:
		case CORRECTION_POSITION_P_X:
		case MAX_CORRECTION_TOLERANCE_X:
		case POSITION_WINDOW_X:
		case RAMP_TYPE_X:
		case BOW_1_X:
		case BOW_2_X:
		case BOW_3_X:
		case BOW_4_X:
		case ENABLE_SOFT_LIMITS_X:
		case SET_LEFT_SOFT_LIMIT_X:
		case SET_RIGHT_SOFT_LIMIT_X:
		case ROTARY_ENC_POSITION_X:
			reply_MCD_Common(REPLY_ID_X, X, 0x64, SAP);
			PRINTF_DEBUG && printf(" Common_X\n");
		break;
		case MAX_POSITION_SPEED_X:
			speed = decoding_CAN_Byte_Data();
			PRINTF_DEBUG && printf(" Speed = %ld ", speed);
			speed = (int32_t) convert_PPS_To_RPM(speed);
			
			// Checking if the motor is moving
			//if(move_given_ramp)
			if( move_given_trapezoidal_ramp == false || move_given_s_ramp == false ) 
			{ 
				velocity_limit = speed;
			}
			PRINTF_DEBUG && printf(" Speed rpm = %ld ", speed);
			reply_MCD_Common(REPLY_ID_X, X, 0x64, SAP);
			PRINTF_DEBUG && printf(" Max_Pos_Speed_X");
		break;
		case RFS_START_X:
			limit_variables.homing = true;
			velocity_limit = 0;
			while(tmc4671_getVelocityLimit(MOTOR) != 0x00)
			{
				tmc4671_setVelocityLimit(MOTOR, 0);
				PRINTF_DEBUG && printf("\nRFS Setting Velocity to 0\n");
			}
			delay_us(2);
			if(limit_variables.homing == true)
			{
				do_homing_sequence();
			}
			PRINTF_DEBUG && printf(" RFS_START_X\n");
			reply_MCD_Common(REPLY_ID_X, X, 0x64, RFS);
		break;
		case RFS_STOP_X:
		{
			tmc4671_setVelocityLimit(MOTOR, 0);
			tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
			move_given_trapezoidal_ramp = false;
			move_given_s_ramp = false;
			limit_variables.homing = false;
			limit_variables.other_limit_hit = false;
			limit_variables.first_limit_hit = false;
			homing_v = 0;
			timer_stop(&TIMER_0);
			PRINTF_DEBUG && printf(" RFS_STOP_X\n");
			reply_MCD_Common(REPLY_ID_X, X, 0x64, RFS);
			break;
		}
		case MOVE_TO_X:
			check_move_done = true;
			value = decoding_CAN_Byte_Data();
			(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)value) + 1, velocity_limit, MOVE_TO) : \
			                move_With_S_Ramp(value, velocity_limit, MOVE_TO);
			encoding_CAN_Byte_Data(value);
			reply_MCD_Common(REPLY_ID_X, X, 0x64, MVP);
			PRINTF_DEBUG && printf(" | X Move To | %ld steps or %.2f mm\n", value, (value / ONE_MM) );
		break;
		case MOVE_BY_X:
			check_move_done = true;
			value = decoding_CAN_Byte_Data();
			(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)value) + 1, velocity_limit, MOVE_BY) : \
			                move_With_S_Ramp(value, velocity_limit, MOVE_BY);
			encoding_CAN_Byte_Data(value);
			reply_MCD_Common(REPLY_ID_X, X, 0x64, MVP);
			PRINTF_DEBUG && printf(" | X Move By | %ld steps or %.2f mm\n", value, (value / ONE_MM) );
		break;
		case STOP_MOTION_X:
			tmc4671_setVelocityLimit(MOTOR, 0);
			tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
			move_given_trapezoidal_ramp = false;
			move_given_s_ramp = false;
			limit_variables.homing = false;
			limit_variables.other_limit_hit = false;
			limit_variables.first_limit_hit = false;
			check_move_done = false;
			homing_v = 0;
			timer_stop(&TIMER_0);
			reply_MCD_Common(REPLY_ID_X, X, 0x64, MST);
			PRINTF_DEBUG && printf(" MOTOR_STOP_X\n");
		break;
		case ROTARY_ENC_X:
			reply_MCD_Common(REPLY_ID_X, X, 0x64, GAP);
		break;
		case TARGET_POSITION_X:
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, SAP);
			int32_t target_position; //= decoding_Byte_Data();
			target_position = tmc4671_getTargetPosition(target_position);
			encoding_CAN_Byte_Data(target_position);
			can_Write(message_Id, target_position);
			PRINTF_DEBUG && printf(" Target Position Y %ld", target_position);
		break;
		case ACTUAL_POSITION_X:
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, SAP);
			int32_t actual_position = tmc4671_getActualPosition(MOTOR);//decoding_Byte_Data();
			//set_RampPosition(actual_position);
			encoding_CAN_Byte_Data(actual_position);
			can_Write(message_Id, actual_position);
		break;
		case LINEAR_ENC_ENABLE_X:
			// enable Linear Encoder counting
		break;
		case LINEAR_ENC_DISABLE_X:
			// disable Linear Encoder counting
		break;
		case LINEAR_ENC_CLEAR_X:
			// Clear Linear Encoder count
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT, ZERO_HEX);
			PRINTF_DEBUG && printf(" LINEAR_ENC_CLEAR_X\n");
		break;
		case LINEAR_ENC_READ_X:
			// Read and Send the Linear Encoder value on the CAN bus.
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, LIN_ENC_READ);
			int32_t x_actual_pos, x_enc_modulo, x_enc_count;
			uint32_t x_linear_enc_res =  read_tlv_flash(tlv_ptr, LINEAR_ENCODER_CPR_FLASH, tlv_traversal);
			x_actual_pos = (motor_dir_rev) ? (int32_t) (~tmc4671_getActualPosition(MOTOR) + 1) : (int32_t) tmc4671_getActualPosition(MOTOR);
			x_enc_modulo = (int32_t) tmc4671_readInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT);
			x_enc_count = (int32_t) ( (floor(x_actual_pos / ROTATION) * x_linear_enc_res) + x_enc_modulo );
			encoding_CAN_Byte_Data(x_enc_count);
			//itoa( x_enc_count , can_tx_frame.data, DEC );
			can_Write(message_Id, x_enc_count);
			PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot,can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
			PRINTF_DEBUG && printf(" LINEAR_ENC_READ_X | %ld usteps | %.2f mm\n", x_enc_count, (x_enc_count / (x_linear_enc_res / PITCH_MM)) );
		break;
		case RT_LIM_SW_CHECK_X: {
			// Right Limit Switch Status reply for Homing (Diagnostic Tool).
			int32_t rt_limit_state;
			rt_limit_state = (int32_t) gpio_get_pin_level(LIM_RT);
			encoding_CAN_Byte_Data(rt_limit_state);
			reply_MCD_Common(REPLY_ID_X, X, 0x64, 0x0A); }
		break;
		case LFT_LIM_SW_CHECK_X: {
			// Left Limit Switch Status reply for Homing (Diagnostic Tool).
			int32_t lft_limit_state;
			lft_limit_state = (int32_t) gpio_get_pin_level(LIM_LFT);
			encoding_CAN_Byte_Data(lft_limit_state);
			reply_MCD_Common(REPLY_ID_X, X, 0x64, 0x0B); }
		break;
		case CAN_KNOB_MODE_X:
			value = decoding_CAN_Byte_Data();
			uint8_t knob_dis_enable = can_rx_frame.data[0];
			vel_struct.vel_state = VEL_STATE_0;
			if(knob_dis_enable)
			{
				vel_struct.knob_enabled = true;
				tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
				timer_start(&VEL_TIMER);
				vel_struct.prev_lin_enc_val = 0;
			}
			else
			{
				vel_struct.knob_enabled = false;
				timer_stop(&VEL_TIMER);
				tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
				tmc4671_setAbsolutTargetPosition(MOTOR, tmc4671_getActualPosition(MOTOR) );
				tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				vel_struct.prev_lin_enc_val = 0;
			}
			PRINTF_DEBUG && printf(" KNOB_MODE_X | %d\n", knob_dis_enable);
		break;
		case CAN_KNOB_MOVEMENT_X:
			value = decoding_CAN_Byte_Data();
			uint8_t velocity_x		= can_rx_frame.data[0];
			uint8_t vel_direction	= can_rx_frame.data[1];
			vel_struct.direction = (vel_direction == 1) ? true : false;
			
			#if LIMIT_SWITCH_RISING
				// If Left Limit hit, don't move if the given velocity is anti clockwise.( -ve velocity)
				// If Right Limit hit, don't move if the given velocity is clockwise.(+ve velocity)
				if( ( gpio_get_pin_level(LIM_LFT) == HIGH ) && ( vel_struct.direction == false ) || \
				    ( gpio_get_pin_level(LIM_RT)  == HIGH ) && ( vel_struct.direction == true ) ) 
				{
					PRINTF_DEBUG && printf("\n#-----Can't move beyond the Limit! Vel Mode-----#\n"); 
					return;
				}
				//if( ( gpio_get_pin_level(LIM_RT)  == HIGH ) && ( vel_struct.direction == true ) ) {  }
			#elif LIMIT_SWITCH_FALLING
				// If Left Limit hit, don't move if the given velocity is anti clockwise.( -ve velocity)
				// If Right Limit hit, don't move if the given velocity is clockwise.(+ve velocity)
				if( ( gpio_get_pin_level(LIM_LFT) == LOW ) && ( vel_struct.direction == true ) || \
				    ( gpio_get_pin_level(LIM_RT)  == LOW ) && ( vel_struct.direction == false ) ) 
				{ 
					PRINTF_DEBUG && printf("\n#-----Can't move beyond the Limit! Vel Mode-----#\n"); 
					return;
				}
				//if( gpio_get_pin_level(LIM_RT)  == LOW) {   }
			#endif
			
			// Check the direction to set the state as positive velocity or negative velocity.
			if(vel_struct.direction)
			{
				switch(velocity_x)
				{
					case 0 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_0		: VEL_STATE_0 ; break;
					case 1 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_1	: VEL_STATE_1 ; break;
					case 2 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_2	: VEL_STATE_2 ; break;
					case 3 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_3	: VEL_STATE_3 ; break;
					case 4 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_4	: VEL_STATE_4 ; break;
					case 5 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_5	: VEL_STATE_5 ; break;
					case 6 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_6	: VEL_STATE_6 ; break;
					case 7 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_7	: VEL_STATE_7 ; break;
					case 8 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_8	: VEL_STATE_8 ; break;
					case 9 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_9	: VEL_STATE_9 ; break;
					case 10: vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_10  : VEL_STATE_10; break;
					default: break;
				}
			}
			else
			{
				switch(velocity_x)
				{
					case 0 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_0  : VEL_STATE_0     ; break;
					case 1 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_1  : VEL_STATE_neg_1 ; break;
					case 2 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_2  : VEL_STATE_neg_2 ; break;
					case 3 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_3  : VEL_STATE_neg_3 ; break;
					case 4 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_4  : VEL_STATE_neg_4 ; break;
					case 5 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_5  : VEL_STATE_neg_5 ; break;
					case 6 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_6  : VEL_STATE_neg_6 ; break;
					case 7 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_7  : VEL_STATE_neg_7 ; break;
					case 8 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_8  : VEL_STATE_neg_8 ; break;
					case 9 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_9  : VEL_STATE_neg_9 ; break;
					case 10: vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_10 : VEL_STATE_neg_10; break;
					default: break;
				}
			}
		break;
		case CAN_KNOB_AXIS_CHANGE_X:
		
		break;
		case RFS_DISTANCE_X:
		{
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, GAP);
			
			// Check what limit is not zero and set it as the limit to limit distance.
			int32_t lim_to_lim_dist = (limit_variables.left_limit_position == 0)
									  ? limit_variables.right_limit_position
									  : limit_variables.left_limit_position;
			
			encoding_CAN_Byte_Data(lim_to_lim_dist);
			can_Write(message_Id, lim_to_lim_dist);
			PRINTF_DEBUG && printf("\nLimit to Limit Distance - X | %.2f mm | %ld usteps\n", (lim_to_lim_dist / ONE_MM), lim_to_lim_dist);
			break;
		}
		case START_RANGE_X:
		{
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, SAP);
			int32_t start_range = decoding_CAN_Byte_Data();
			limit_variables.soft_limit_low = start_range + SOFT_LIMIT_OFFSET_MM;
			encoding_CAN_Byte_Data(limit_variables.soft_limit_low);
			can_Write(message_Id, limit_variables.soft_limit_low);
			PRINTF_DEBUG && printf("\nStart Range - X | %.2f mm | %ld usteps\n", (start_range / ONE_MM), start_range);
			break;
		}
		case END_RANGE_X:
		{
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, SAP);
			int32_t end_range = decoding_CAN_Byte_Data();
			limit_variables.soft_limit_high = end_range - SOFT_LIMIT_OFFSET_MM;
			encoding_CAN_Byte_Data(limit_variables.soft_limit_high);
			can_Write(message_Id, limit_variables.soft_limit_high);
			PRINTF_DEBUG && printf("\nEnd Range - X | %.2f mm | %ld usteps\n", (end_range / ONE_MM), end_range);
			break;
		}
		default:
			// error
		break;
	}
	
	// Switch case for writing directly to register. No checking of register address checking or data checking
	// withing range check is done.
	if(ad == X)
	{
		switch(cmd)
		{
			case WR_MC:
			{
				message_Id = CAN_ID(REPLY_ID_X, X, 0x64, WR_MC);
				int32_t wr_reg_data = decoding_CAN_Byte_Data();
				tmc4671_writeInt(MOTOR, typ, wr_reg_data);
				encoding_CAN_Byte_Data(wr_reg_data);
				can_Write(message_Id, wr_reg_data);
				break;
			}
			case RD_MC:
			{
				message_Id = CAN_ID(REPLY_ID_X, X, 0x64, RD_MC);
				int32_t rd_reg_data = tmc4671_readInt(MOTOR, typ);
				encoding_CAN_Byte_Data(rd_reg_data);
				can_Write(message_Id, rd_reg_data);
				break;
			}
			case RD_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
				read_tlv_flash(tlv_ptr, parameter_id, tlv_traversal);
				encoding_CAN_Byte_Data(tlv_ptr->value_32bit);
				message_Id = CAN_ID(REPLY_ID_X, X, 0x64, RD_FW_PARAM);
				can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, tlv_ptr->value_32bit);
				can_Write(message_Id, tlv_ptr->value_32bit);
				PRINTF_DEBUG && printf("READ_PARAMETER_FLASH_X - Tag = %d (or) 0x%x | Length = %d or 0x%x | Data = %ld | 0x%x \n",\
				tlv_ptr->tag, tlv_ptr->tag, tlv_ptr->length, tlv_ptr->length, tlv_ptr->value_32bit, tlv_ptr->value_32bit);
				break;
			}
			case WR_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				uint8_t parameter_len = mot;
				int32_t parameter_val = decoding_CAN_Byte_Data();
				
				write_tlv_flash(parameter_id, &parameter_val, parameter_len);
				message_Id = CAN_ID(REPLY_ID_X, X, 0x64, WR_FW_PARAM);
				encoding_CAN_Byte_Data(parameter_val);
				can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, parameter_val);
				can_Write(message_Id, parameter_val);
				PRINTF_DEBUG && printf("WRITE_PARAMETER_FLASH_X - Tag = %d (or) 0x%x | Length = %d or 0x%x | Data = %ld | 0x%x \n",\
				parameter_id, parameter_id, parameter_len, parameter_len, parameter_val, parameter_val);
				break;
			}
			case CHK_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				int32_t value_check = decoding_CAN_Byte_Data();
				check_tlv_param(tlv_ptr, parameter_id, tlv_traversal, value_check);
				PRINTF_DEBUG && printf("CHECK_PARAMETER_FLASH_X\n");
				break;
			}
			default: break;
		}
	}
	return;
}

void can_Message_Operational_v3_YAxis(uint32_t message_Id, int32_t data)
{	/* The breakdown of reply format for v3 MCD commands. (used by the "reply_MCD_common()" function)
	 *		0x0C			0x02		 0x64		  0xXX
	 * Reply Address | Module Address | Status | Command Number
	 *
	 * Check MCD_json for in-detail values
	 */
	switch(message_Id)
	{
		case CAN_BOOT_Y_ID:
			sw_reset();
		break;
		case CAN_EXT_FLASH_ID:
			//check_cdone();
			message_Id = CAN_INIT ;
		break;
		case CAN_BIN_FILE_ERASE:
			//erase_can_flash();
			message_Id = CAN_INIT ;
		break;
		case CAN_BIN_FILE_WRITE:
			//write_can_flash();
			can_rx_frame.data_64bit = 0x00;
			message_Id = CAN_INIT ;
		break;
		case MOVE_DONE_PING_Y:
			do_Move_Done_Ping();
			PRINTF_DEBUG && printf(" MOVE_DONE_PING_Y\n");
		break;
		case PING_Y:
			do_4671_Ping();
			PRINTF_DEBUG && printf(" PING_Y\n");
		break;
		case REF_SEARCH_PING_Y:
			do_Ref_Search_Ping();
			PRINTF_DEBUG && printf(" REF_SEARCH_PING_Y\n");
		break;
		case MAX_ACCEL_Y:
		case MAX_DECCEL_Y:
		case HOME_SEARCH_VEL_Y:
		case HOME_SWITCH_VEL_Y:
		case HOMING_MODE_Y:
		case OPEN_CLOSED_LOOP_Y:
		case CORRECTION_VEL_P_Y:
		case CORRECTION_VEL_I_Y:
		case CORRECTION_VEL_I_CLIP_Y:
		case CORRECTION_VEL_DV_CLK_Y:
		case CORRECTION_VEL_DV_CLIP_Y:
		case CORRECTION_POSITION_P_Y:
		case MAX_CORRECTION_TOLERANCE_Y:
		case POSITION_WINDOW_Y:
		case RAMP_TYPE_Y:
		case BOW_1_Y:
		case BOW_2_Y:
		case BOW_3_Y:
		case BOW_4_Y:
		case ENABLE_SOFT_LIMITS_Y:
		case SET_LEFT_SOFT_LIMIT_Y:
		case SET_RIGHT_SOFT_LIMIT_Y:
		case ROTARY_ENC_POSITION_Y:
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, SAP);
			PRINTF_DEBUG && printf(" Common_Y\n");
		break;
		case MAX_POSITION_SPEED_Y:
			speed = decoding_CAN_Byte_Data();
			PRINTF_DEBUG && printf(" Speed = %d ", speed);
			speed = (int32_t) convert_PPS_To_RPM(speed);
			
			// Checking if the motor is moving
			if( move_given_trapezoidal_ramp == false || move_given_s_ramp == false ) 
			{ 
				velocity_limit = speed;
			}
			PRINTF_DEBUG && printf(" Speed rpm = %d ", speed);
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, SAP);
			PRINTF_DEBUG && printf(" Max_Pos_Speed_Y");
		break;
		case RFS_START_Y:
			limit_variables.homing = true;
			velocity_limit = 0;
			while(tmc4671_getVelocityLimit(MOTOR) != 0x00)
			{
				tmc4671_setVelocityLimit(MOTOR, 0);
				PRINTF_DEBUG && printf("\nRFS Setting Velocity to 0\n");
			}
			delay_us(2);
			if(limit_variables.homing == true)
			{
				do_homing_sequence();
			}
			
			PRINTF_DEBUG && printf(" RFS_START_Y\n");
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, RFS);
		break;
		case RFS_STOP_Y:
		{
			tmc4671_setVelocityLimit(MOTOR, 0);
			tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
			move_given_trapezoidal_ramp = false;
			move_given_s_ramp = false;
			limit_variables.homing = false;
			limit_variables.other_limit_hit = false;
			limit_variables.first_limit_hit = false;
			homing_v = 0;
			timer_stop(&TIMER_0);
			PRINTF_DEBUG && printf(" RFS_STOP_Y\n");
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, RFS);
			break;
		}
		case MOVE_TO_Y:
			check_move_done = true;
			value = decoding_CAN_Byte_Data();
			(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)value) + 1, velocity_limit, MOVE_TO) : \
							move_With_S_Ramp(value, velocity_limit, MOVE_TO);
			encoding_CAN_Byte_Data(value);
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, MVP);
			PRINTF_DEBUG && printf(" | Y Move To | %ld steps or %.2f mm\n", value, (value / ONE_MM) );
		break;
		case MOVE_BY_Y:
			check_move_done = true;
			value = decoding_CAN_Byte_Data();
			(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)value) + 1, velocity_limit, MOVE_BY) : \
							move_With_S_Ramp(value, velocity_limit, MOVE_BY);
			encoding_CAN_Byte_Data(value);
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, MVP);
			PRINTF_DEBUG && printf(" | Y Move By | %ld steps or %.2f mm\n", value, (value / ONE_MM) );
		break;
		case STOP_MOTION_Y:
			tmc4671_setVelocityLimit(MOTOR, 0);
			tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
			move_given_trapezoidal_ramp = false;
			move_given_s_ramp = false;
			limit_variables.homing = false;
			limit_variables.other_limit_hit = false;
			limit_variables.first_limit_hit = false;
			check_move_done = false;
			homing_v = 0;
			timer_stop(&TIMER_0);
			reply_MCD_Common(REPLY_ID_Y, Y, 0x64, MST);
		break;
		case ROTARY_ENC_Y: {
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, GAP);
			int32_t current_position = (int32_t) tmc4671_getActualPosition(MOTOR);
			encoding_CAN_Byte_Data(current_position);
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, current_position);
			PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot,can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
			PRINTF_DEBUG && printf(" Rotary Encoder Count = %ld ROTARY_ENC_Y\n", current_position); }
		break;
		case TARGET_POSITION_Y:
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, SAP);
			int32_t target_position; //= decoding_Byte_Data();
			target_position = tmc4671_getTargetPosition(target_position);
			encoding_CAN_Byte_Data(target_position);
			can_Write(message_Id, target_position);
			PRINTF_DEBUG && printf(" Target Position Y %ld", target_position);
		break;
		case ACTUAL_POSITION_Y:
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, SAP);
			int32_t actual_position = tmc4671_getActualPosition(MOTOR);//decoding_Byte_Data();
			//set_RampPosition(actual_position);
			encoding_CAN_Byte_Data(actual_position);
			can_Write(message_Id, actual_position);
			PRINTF_DEBUG && printf("\nActual Position Y %ld\n", actual_position);
		break;
		case LINEAR_ENC_CLEAR_Y: 
			tmc4671_writeInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT, ZERO_HEX);
			//tmc4671_setActualPosition(MOTOR, ZERO_HEX);
			PRINTF_DEBUG && printf(" LINEAR_ENC_CLEAR_Y\n");
		break;
		case LINEAR_ENC_READ_Y:
			// Read and Send the Linear Encoder value on the CAN bus.
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, LIN_ENC_READ);
			int32_t y_actual_pos, y_enc_modulo, y_enc_count;
			uint32_t y_linear_enc_res = (uint32_t) read_tlv_flash(tlv_ptr, LINEAR_ENCODER_CPR_FLASH, tlv_traversal);
			y_actual_pos = (motor_dir_rev) ? (int32_t) (~tmc4671_getActualPosition(MOTOR) + 1) : (int32_t) tmc4671_getActualPosition(MOTOR);
			y_enc_modulo = (int32_t) tmc4671_readInt(MOTOR, TMC4671_ABN_2_DECODER_COUNT);
			y_enc_count = (int32_t) ( (floor(y_actual_pos / ROTATION) * y_linear_enc_res) + y_enc_modulo );
			encoding_CAN_Byte_Data(y_enc_count);
			//itoa( x_enc_count , can_tx_frame.data, DEC );
			can_Write(message_Id, y_enc_count);
			PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot,can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
			PRINTF_DEBUG && printf(" LINEAR_ENC_READ_Y | %ld usteps | %.2f mm\n", y_enc_count, (y_enc_count / (y_linear_enc_res / PITCH_MM)) );
		break;
		case RT_LIM_SW_CHECK_Y: {
			// Right Limit Switch Status reply for Homing (Diagnostic Tool).
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, 0x0A);
			int32_t rt_limit_state;
			//rt_limit_state = (int32_t) gpio_get_pin_level(LIM_RT);
			encoding_CAN_Byte_Data( gpio_get_pin_level(LIM_RT) );
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data); // Should it be added to encoding_Byte_Data() function???
			can_Write(message_Id, rt_limit_state);
			PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot,can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]); 
			PRINTF_DEBUG && printf(" state = %d RT_LIM_SW_CHECK_Y\n", gpio_get_pin_level(LIM_RT)); }
		break;
		case LFT_LIM_SW_CHECK_Y: {
			// Left Limit Switch Status reply for Homing (Diagnostic Tool).
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, 0x0B);
			int32_t lft_limit_state;
			lft_limit_state = (int32_t) gpio_get_pin_level(LIM_LFT);
			encoding_CAN_Byte_Data( gpio_get_pin_level(LIM_LFT) );
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data); // Should it be added to encoding_Byte_Data() function???
			can_Write(message_Id, lft_limit_state); 
			PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot,can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
			PRINTF_DEBUG && printf(" state = %d LFT_LIM_SW_CHECK_Y\n", gpio_get_pin_level(LIM_LFT)); }
		break;
		case CAN_KNOB_MODE_Y:
			value = decoding_CAN_Byte_Data();
			uint8_t knob_dis_enable = can_rx_frame.data[0];
			vel_struct.vel_state = VEL_STATE_0;
			if(knob_dis_enable)
			{
				vel_struct.knob_enabled = true;
				tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
				timer_start(&VEL_TIMER);
				vel_struct.prev_lin_enc_val = 0;
			}
			else
			{
				vel_struct.knob_enabled = false;
				timer_stop(&VEL_TIMER);
				tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
				tmc4671_setAbsolutTargetPosition(MOTOR, tmc4671_getActualPosition(MOTOR) );
				tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				vel_struct.prev_lin_enc_val = 0;
			}
			PRINTF_DEBUG && printf(" KNOB_MODE_Y | %d\n", knob_dis_enable);
		break;
		case CAN_KNOB_MOVEMENT_Y:
			value = decoding_CAN_Byte_Data();
			uint8_t velocity_x		= can_rx_frame.data[0];
			uint8_t vel_direction	= can_rx_frame.data[1];
			vel_struct.direction = (vel_direction == 1) ? true : false;
			
			#if LIMIT_SWITCH_RISING
				// If Left Limit hit, don't move if the given velocity is anti clockwise.( -ve velocity)
				// If Right Limit hit, don't move if the given velocity is clockwise.(+ve velocity)
				if( ( gpio_get_pin_level(LIM_LFT) == HIGH ) && ( vel_struct.direction == false ) || \
				( gpio_get_pin_level(LIM_RT)  == HIGH ) && ( vel_struct.direction == true ) )
				{
					PRINTF_DEBUG && printf("\n#-----Can't move beyond the Limit! Vel Mode-----#\n");
					return;
				}
				//if( ( gpio_get_pin_level(LIM_RT)  == HIGH ) && ( vel_struct.direction == true ) ) {  }
			#elif LIMIT_SWITCH_FALLING
				// If Left Limit hit, don't move if the given velocity is anti clockwise.( -ve velocity)
				// If Right Limit hit, don't move if the given velocity is clockwise.(+ve velocity)
				if( ( gpio_get_pin_level(LIM_LFT) == LOW ) && ( vel_struct.direction == false ) || \
				( gpio_get_pin_level(LIM_RT)  == LOW ) && ( vel_struct.direction == true ) )
				{
					PRINTF_DEBUG && printf("\n#-----Can't move beyond the Limit! Vel Mode-----#\n");
					return;
				}
				//if( gpio_get_pin_level(LIM_RT)  == LOW) {   }
			#endif
			
			// Check the direction to set the state as positive velocity or negative velocity.
			if(vel_struct.direction)
			{
				switch(velocity_x)
				{
					case 0 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_0		: VEL_STATE_0 ; break;
					case 1 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_1	: VEL_STATE_1 ; break;
					case 2 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_2	: VEL_STATE_2 ; break;
					case 3 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_3	: VEL_STATE_3 ; break;
					case 4 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_4	: VEL_STATE_4 ; break;
					case 5 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_5	: VEL_STATE_5 ; break;
					case 6 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_6	: VEL_STATE_6 ; break;
					case 7 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_7	: VEL_STATE_7 ; break;
					case 8 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_8	: VEL_STATE_8 ; break;
					case 9 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_9	: VEL_STATE_9 ; break;
					case 10: vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_10  : VEL_STATE_10; break;
					default: break;
				}
			}
			else
			{
				switch(velocity_x)
				{
					case 0 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_0  : VEL_STATE_0     ; break;
					case 1 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_1  : VEL_STATE_neg_1 ; break;
					case 2 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_2  : VEL_STATE_neg_2 ; break;
					case 3 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_3  : VEL_STATE_neg_3 ; break;
					case 4 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_4  : VEL_STATE_neg_4 ; break;
					case 5 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_5  : VEL_STATE_neg_5 ; break;
					case 6 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_6  : VEL_STATE_neg_6 ; break;
					case 7 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_7  : VEL_STATE_neg_7 ; break;
					case 8 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_8  : VEL_STATE_neg_8 ; break;
					case 9 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_9  : VEL_STATE_neg_9 ; break;
					case 10: vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_10 : VEL_STATE_neg_10; break;
					default: break;
				}
			}
			PRINTF_DEBUG && printf(" KNOB_MOVEMENT_Y SPEED = %d | Direction = %d\n", velocity_x, vel_struct.direction);
		break;
		case CAN_KNOB_AXIS_CHANGE_Y:
		
		break;
		case RFS_DISTANCE_Y:
		{
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, GAP);
			
			// Check what limit is not zero and set it as the limit to limit distance.
			int32_t lim_to_lim_dist = (limit_variables.left_limit_position == 0)
			? limit_variables.right_limit_position
			: limit_variables.left_limit_position;
			
			encoding_CAN_Byte_Data(lim_to_lim_dist);
			can_Write(message_Id, lim_to_lim_dist);
			PRINTF_DEBUG && printf("\nLimit to Limit Distance - Y | %.2f mm | %ld usteps\n", (lim_to_lim_dist / ONE_MM), lim_to_lim_dist);
			break;
		}
		case START_RANGE_Y:
		{
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, SAP);
			int32_t start_range = decoding_CAN_Byte_Data();
			limit_variables.soft_limit_low = start_range + SOFT_LIMIT_OFFSET_MM;
			encoding_CAN_Byte_Data(limit_variables.soft_limit_low);
			can_Write(message_Id, limit_variables.soft_limit_low);
			PRINTF_DEBUG && printf("\nStart Range - Y | %.2f mm | %ld usteps\n", (start_range / ONE_MM), start_range);
			break;
		}
		case END_RANGE_Y:
		{
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, SAP);
			int32_t end_range = decoding_CAN_Byte_Data();
			limit_variables.soft_limit_high = end_range - SOFT_LIMIT_OFFSET_MM;
			encoding_CAN_Byte_Data(limit_variables.soft_limit_high);
			can_Write(message_Id, limit_variables.soft_limit_high);
			PRINTF_DEBUG && printf("\nEnd Range - Y | %.2f mm | %ld usteps\n", (end_range / ONE_MM), end_range);
			break;
		}
		default:
			// error
		break;
	}
	
	// Switch case for writing directly to register. No checking of register address checking or data checking
	// withing range check is done.
	if(ad == Y)
	{
		switch(cmd)
		{
			case WR_MC:
			{
				message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, WR_MC);
				int32_t wr_reg_data = decoding_CAN_Byte_Data();
				tmc4671_writeInt(MOTOR, typ, wr_reg_data);
				encoding_CAN_Byte_Data(wr_reg_data);
				can_Write(message_Id, wr_reg_data);
				break;
			}
			case RD_MC:
			{
				message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, RD_MC);
				int32_t rd_reg_data = tmc4671_readInt(MOTOR, typ);
				encoding_CAN_Byte_Data(rd_reg_data);
				can_Write(message_Id, rd_reg_data);
				break;
			}
			case RD_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
				read_tlv_flash(tlv_ptr, parameter_id, tlv_traversal);
				encoding_CAN_Byte_Data(tlv_ptr->value_32bit);
				message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, RD_FW_PARAM);
				can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, tlv_ptr->value_32bit);
				can_Write(message_Id, tlv_ptr->value_32bit);
				PRINTF_DEBUG && printf("READ_PARAMETER_FLASH_Y - Tag = %d (or) 0x%x | Length = %d or 0x%x | Data = %ld | 0x%x \n",\
				tlv_ptr->tag, tlv_ptr->tag, tlv_ptr->length, tlv_ptr->length, tlv_ptr->value_32bit, tlv_ptr->value_32bit);
				break;
			}
			case WR_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				uint8_t parameter_len = mot;
				int32_t parameter_val = decoding_CAN_Byte_Data();
				
				write_tlv_flash(parameter_id, &parameter_val, parameter_len);
				message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, WR_FW_PARAM);
				encoding_CAN_Byte_Data(parameter_val);
				can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, parameter_val);
				can_Write(message_Id, parameter_val);
				PRINTF_DEBUG && printf("WRITE_PARAMETER_FLASH_Y - Tag = %d (or) 0x%x | Length = %d or 0x%x | Data = %ld | 0x%x \n",\
										parameter_id, parameter_id, parameter_len, parameter_len, parameter_val, parameter_val);
				break;
			}
			case CHK_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				int32_t value_check = decoding_CAN_Byte_Data();
				check_tlv_param(tlv_ptr, parameter_id, tlv_traversal, value_check);
				PRINTF_DEBUG && printf("CHECK_PARAMETER_FLASH_Y\n");
				break;
			}
			default: break;
		}
	}
	return;
}

void can_Message_Operational_v3_ZAxis(uint32_t message_Id, int32_t data)
{	/* The breakdown of reply format for v3 MCD commands. (used by the "reply_MCD_common()" function)
	 *		0C				 02			  64		   XX
	 * Reply Address | Module Address | Status | Command Number
	 *
	 * Check MCD_json for in-detail values
	 */
	switch(message_Id)
	{
		case CAN_BOOT_Z_ID:
			PRINTF_DEBUG && printf("\nRESET\n");
			sw_reset();
		break;
		case CAN_EXT_FLASH_ID:
			//check_cdone();
			message_Id = CAN_INIT ;
		break;
		case CAN_BIN_FILE_ERASE:
			//erase_can_flash();
			message_Id = CAN_INIT ;
		break;
		case CAN_BIN_FILE_WRITE:
			//write_can_flash();
			can_rx_frame.data_64bit = 0x00;
			message_Id = CAN_INIT ;
		break;
		case MOVE_DONE_PING_Z:
			do_Move_Done_Ping();
			PRINTF_DEBUG && printf(" MOVE_DONE_PING_Z\n");
		break;
		case PING_Z:
			do_4671_Ping();
			PRINTF_DEBUG && printf(" PING_Z\n");
		break;
		case REF_SEARCH_PING_Z:
			do_Ref_Search_Ping();
			PRINTF_DEBUG && printf(" REF_SEARCH_PING_Z\n");
		break;
		case MAX_ACCEL_Z:
		case MAX_DECCEL_Z:
		case HOME_SEARCH_VEL_Z:
		case HOME_SWITCH_VEL_Z:
		case HOMING_MODE_Z:
		case OPEN_CLOSED_LOOP_Z:
		case CORRECTION_VEL_P_Z:
		case CORRECTION_VEL_I_Z:
		case CORRECTION_VEL_I_CLIP_Z:
		case CORRECTION_VEL_DV_CLK_Z:
		case CORRECTION_VEL_DV_CLIP_Z:
		case CORRECTION_POSITION_P_Z:
		case MAX_CORRECTION_TOLERANCE_Z:
		case POSITION_WINDOW_Z:
		case RAMP_TYPE_Z:
		case BOW_1_Z:
		case BOW_2_Z:
		case BOW_3_Z:
		case BOW_4_Z:
		case SET_LEFT_SOFT_LIMIT_Z:
		case SET_RIGHT_SOFT_LIMIT_Z:
		case ROTARY_ENC_POSITION_Z:
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, SAP);
			PRINTF_DEBUG && printf(" Common_Z\n");
		break;
		case ENABLE_SOFT_LIMITS_Z:
			reply_MCD_Common(REPLY_ID_Z, Z, 0X64, SAP);
			PRINTF_DEBUG && printf(" EN Soft Limits_Z\n");
		break;
		case MAX_POSITION_SPEED_Z:
			speed = decoding_CAN_Byte_Data();
			PRINTF_DEBUG && printf(" Speed = %ld ", speed);
			speed = (int32_t) convert_PPS_To_RPM(speed);
			PRINTF_DEBUG && printf(" Speed rpm = %ld |", speed);
			
			// Checking if the motor is moving
			if( (move_given_trapezoidal_ramp == false) || (move_given_s_ramp == false) ) 
			{ 
				velocity_limit = speed;
			}
			if( autofocus_variables.temp_move_change )
			{
				autofocus_variables.temp_t_vel = speed;
				PRINTF_DEBUG && printf(" AF Temp Vel set to %ld rpm |", autofocus_variables.temp_t_vel);
			}
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, SAP);
			PRINTF_DEBUG && printf(" Max_Pos_Speed_Z");
		break;
		case RFS_START_Z:
			limit_variables.homing = true;
			velocity_limit = 0;
			while(tmc4671_getVelocityLimit(MOTOR) != 0x00)
			{
				tmc4671_setVelocityLimit(MOTOR, 0);	
				PRINTF_DEBUG && printf("\nRFS Setting Velocity to 0\n");
			}
			delay_us(2);
			if(limit_variables.homing == true)
			{
				do_homing_sequence();
			}
			PRINTF_DEBUG && printf(" RFS_START_Z\n");
	    	reply_MCD_Common(REPLY_ID_Z, Z, 0x64, RFS);
		break;
		case RFS_STOP_Z:
		{
			tmc4671_setVelocityLimit(MOTOR, 0);
			tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
			move_given_trapezoidal_ramp = false;
			move_given_s_ramp = false;
			limit_variables.homing = false;
			limit_variables.other_limit_hit = false;
			limit_variables.first_limit_hit = false;
			homing_v = 0;
			timer_stop(&TIMER_0);
			PRINTF_DEBUG && printf(" RFS_STOP_Z\n");
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, RFS);
			break;
		}
		case MOVE_TO_Z:
			check_move_done = true;
			value = decoding_CAN_Byte_Data();
			encoding_CAN_Byte_Data(value);
			// Check if Auto-Focus is happening.
			if( autofocus_variables.both_received )
			{	// Check if Step_Size != Start_Point.
				if( autofocus_variables.change_comp_cnt )
				{
					int32_t diff_mm = (int32_t) MOVE_MM(15);	// Distance used to determine if we need to do 2 different movements or not.
					int32_t pos_diff = abs( autofocus_variables.af_table[0] - tmc4671_getActualPosition(MOTOR) );	
					int32_t how_close_to_range_mm = (int32_t) MOVE_MM(2);
					if(pos_diff > diff_mm)	
					{
						autofocus_variables.temp_t_pos = value;
						
						value = (autofocus_variables.sign_check < 0) ? (autofocus_variables.af_table[0] + how_close_to_range_mm) \
																	 : (autofocus_variables.af_table[0] - how_close_to_range_mm);
						autofocus_variables.temp_move_change = true;
					}
				}
			}
			(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)value) + 1, velocity_limit, MOVE_TO) : \
							  move_With_S_Ramp(value, velocity_limit, MOVE_TO);
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, MVP);
			PRINTF_DEBUG && printf(" | Z Move To | %ld steps or %.2f mm\n", value, (value / ONE_MM) );
		break;
		case MOVE_BY_Z:
			check_move_done = true;
			value = decoding_CAN_Byte_Data();
			(motor_dir_rev) ? move_With_S_Ramp( (~(int32_t)value) + 1, velocity_limit, MOVE_BY) : \
							move_With_S_Ramp(value, velocity_limit, MOVE_BY);
			encoding_CAN_Byte_Data(value);
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, MVP);
			PRINTF_DEBUG && printf(" | Z Move By | %ld steps or %.2f mm\n", value, (value / ONE_MM) );
		break;
		case STOP_MOTION_Z:
			tmc4671_setVelocityLimit(MOTOR, 0);
			tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
			move_given_trapezoidal_ramp = false;
			move_given_s_ramp = false;
			limit_variables.homing = false;
			limit_variables.other_limit_hit = false;
			limit_variables.first_limit_hit = false;
			check_move_done = false;
			homing_v = 0;
			timer_stop(&TIMER_0);
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, MST);
			PRINTF_DEBUG && printf( " MST_Z\n");
		break;
		case ROTARY_ENC_Z:
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, GAP);
			int32_t rot_position = tmc4671_getActualPosition(MOTOR);//decoding_Byte_Data();
			//set_RampPosition(actual_position);
			encoding_CAN_Byte_Data(rot_position);
			can_Write(message_Id, rot_position);
			PRINTF_DEBUG && printf(" Rot ENc_Z\n");
		break;
		case TARGET_POSITION_Z:
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, SAP);
			int32_t target_position; //= decoding_Byte_Data();
			target_position = tmc4671_getTargetPosition(target_position);
			encoding_CAN_Byte_Data(target_position);
			can_Write(message_Id, target_position);
			PRINTF_DEBUG && printf(" Target Position Y %ld", target_position);
		break;
		case ACTUAL_POSITION_Z:
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, SAP);
			int32_t actual_position = tmc4671_getActualPosition(MOTOR);//decoding_Byte_Data();
			//set_RampPosition(actual_position);
			encoding_CAN_Byte_Data(actual_position);
			can_Write(message_Id, actual_position);
			PRINTF_DEBUG && printf(" Actual Pos_Z\n");
		break;
		case AF_STARTPOINT:
			autofocus_variables.combined = (int64_t)can_rx_frame.data_64bit;
			int32_t rot_enc_res = read_tlv_flash(tlv_ptr, ROTARY_ENCODER_PPR_FLASH, tlv_traversal);
			int32_t enc_mul_factor = (ROTATION / rot_enc_res);
			autofocus_variables.gQDECstepSizeCount = (int32_t) enc_mul_factor * abs(autofocus_variables.combined >> 32);
			autofocus_variables.sign_check = (int32_t) enc_mul_factor * (autofocus_variables.combined & 0xFFFFFFFF);
			autofocus_variables.startPointAF = (int) enc_mul_factor * abs(autofocus_variables.combined & 0xFFFFFFFF);
			autofocus_variables.temp_t_pos = 0;
			autofocus_variables.temp_t_vel = 0;
			idx = 0;

			PRINTF_DEBUG && printf("\n------------------------------sweep no = %d\tspeed = %d------------------------------", autofocus_variables.sweep_no + 1, velocity_limit);
			
			autofocus_variables.starting_position = tmc4671_getActualPosition(MOTOR);
			
			PRINTF_DEBUG && printf("\ngQDECstepSizeCount: %ld count(or)%ld steps(or)%.4f mm\tstartpoint: %ld count(or)%ld steps(or)%.4f mm", autofocus_variables.gQDECstepSizeCount / ENC_MUL_FACTOR,\
							autofocus_variables.gQDECstepSizeCount, autofocus_variables.gQDECstepSizeCount / ONE_MM,autofocus_variables.startPointAF / ENC_MUL_FACTOR, \
							autofocus_variables.startPointAF, autofocus_variables.startPointAF / ONE_MM);
			
			PRINTF_DEBUG && printf("\n Sign Check = %ld steps(or) %ld enc count", autofocus_variables.sign_check, \
								    autofocus_variables.sign_check / ENC_MUL_FACTOR);
			// Flag to set if both startPointAF and gQDECstepSize are received.
			autofocus_variables.both_received = true;							
			PRINTF_DEBUG && printf("\nboth_rxd true");
			autofocus_variables.cam_trigger_count = 0;
			
			// Set initial compare value as startPointAF.
			memset(autofocus_variables.af_table, 0x00, sizeof(autofocus_variables.af_table)); 
			
			if(autofocus_variables.gQDECstepSizeCount == autofocus_variables.startPointAF)
			{
				camera_Trigger();
				
				int32_t current_pos = tmc4671_getActualPosition(MOTOR);
				PRINTF_DEBUG && printf("\n idx = %ld\tcurrent Pos = %.4f mm(or)%ld steps\taf_table = %.4f mm(or)%ld steps\n", 0, current_pos / ONE_MM, current_pos, \
								autofocus_variables.startPointAF / ONE_MM, autofocus_variables.startPointAF);
				
				autofocus_variables.change_comp_cnt = false;
			}
			else
			{
				autofocus_variables.change_comp_cnt = true;
			}
			autofocus_variables.af_table[0] = autofocus_variables.starting_position + autofocus_variables.sign_check;
			
			PRINTF_DEBUG && printf("\naf_table[%ld] = %.4f mm(or)%ld steps", 0, autofocus_variables.af_table[0] / ONE_MM, \
			                autofocus_variables.af_table[0]);
										
			// Check if startPointAF is negative
			if(autofocus_variables.sign_check < 0)
			{
				for(int32_t i = 1; i < AUTOFOCUS_INDEX_LENGTH; i++)
				{
					autofocus_variables.af_table[i] = autofocus_variables.af_table[i - 1] - \
													  autofocus_variables.gQDECstepSizeCount;
					
					PRINTF_DEBUG && printf("\naf_table[%ld] = %.2f mm (or)%ld steps", i, autofocus_variables.af_table[i] / ONE_MM, \
								    autofocus_variables.af_table[i]);
				}
				PRINTF_DEBUG && printf("  | AF_STARTPOINT_Z (-)spAF \n");
			}
			else
			{
				for(int32_t i = 1; i < AUTOFOCUS_INDEX_LENGTH; i++)
				{
					autofocus_variables.af_table[i] = autofocus_variables.af_table[i - 1] + \	
													  autofocus_variables.gQDECstepSizeCount;
												  
					PRINTF_DEBUG && printf("\naf_table[%ld] = %.2f mm (or)%ld steps", i, autofocus_variables.af_table[i] / ONE_MM, \
					                autofocus_variables.af_table[i]);
				}
				PRINTF_DEBUG && printf("  | AF_STARTPOINT_Z (+)spAF\n");
			}
			autofocus_variables.sweep_no += 1;
		break;
		case LINEAR_ENC_CLEAR_Z:
			//autofocus_variables.compare_cnt = can_rx_frame.data_64bit;
			PRINTF_DEBUG && printf(" LIN_ENC_CLR_Z\n");
		break;
		case LINEAR_ENC_READ_Z:
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, LIN_ENC_READ);
			actual_position = tmc4671_getActualPosition(MOTOR);
			encoding_CAN_Byte_Data(actual_position);
			can_Write(message_Id, actual_position);
		break;
		case RT_LIM_SW_CHECK_Z: {
			// Right Limit Switch Status reply for Homing (Diagnostic Tool).
			int32_t rt_limit_state;
			rt_limit_state = (int32_t) gpio_get_pin_level(LIM_RT);
			encoding_CAN_Byte_Data(rt_limit_state);
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, 0x0A); }
		break;
		case LFT_LIM_SW_CHECK_Z: {
			// Left Limit Switch Status reply for Homing (Diagnostic Tool).
			int32_t lft_limit_state;
			lft_limit_state = (int32_t) gpio_get_pin_level(LIM_LFT);
			encoding_CAN_Byte_Data(lft_limit_state);
			reply_MCD_Common(REPLY_ID_Z, Z, 0x64, 0x0B); }
		break;
		case CAN_KNOB_MODE_Z:
			value = decoding_CAN_Byte_Data();
			uint8_t knob_dis_enable = can_rx_frame.data[0];
			vel_struct.vel_state = VEL_STATE_0;
			if(knob_dis_enable)
			{
				vel_struct.knob_enabled = true;
				tmc4671_setModeMotion(MOTOR, VELOCITY_MODE);
				timer_start(&VEL_TIMER);
				vel_struct.prev_lin_enc_val = 0;
			}
			else
			{
				vel_struct.knob_enabled = false;
				timer_stop(&VEL_TIMER);
				tmc4671_setModeMotion(MOTOR, STOPPED_MODE);
				tmc4671_setAbsolutTargetPosition(MOTOR, tmc4671_getActualPosition(MOTOR) );
				tmc4671_setModeMotion(MOTOR, POSITION_MODE);
				vel_struct.prev_lin_enc_val = 0;
			}
			PRINTF_DEBUG && printf(" KNOB_MODE_Z | %d\n", knob_dis_enable);
		break;
		case CAN_KNOB_MOVEMENT_Z:
			value = decoding_CAN_Byte_Data();
			uint8_t velocity_x		= can_rx_frame.data[0];
			uint8_t vel_direction	= can_rx_frame.data[1];
			vel_struct.direction = (vel_direction == 1) ? true : false;
			
			#if LIMIT_SWITCH_RISING
			// If Left Limit hit, don't move if the given velocity is anti clockwise.( -ve velocity)
			// If Right Limit hit, don't move if the given velocity is clockwise.(+ve velocity)
			if( ( gpio_get_pin_level(LIM_LFT) == HIGH ) && ( vel_struct.direction == false ) || \
			( gpio_get_pin_level(LIM_RT)  == HIGH ) && ( vel_struct.direction == true ) )
			{
				PRINTF_DEBUG && printf("\n#-----Can't move beyond the Limit! Vel Mode-----#\n");
				return;
			}
			//if( ( gpio_get_pin_level(LIM_RT)  == HIGH ) && ( vel_struct.direction == true ) ) {  }
			#elif LIMIT_SWITCH_FALLING
			// If Left Limit hit, don't move if the given velocity is anti clockwise.( -ve velocity)
			// If Right Limit hit, don't move if the given velocity is clockwise.(+ve velocity)
			if( ( gpio_get_pin_level(LIM_LFT) == LOW ) && ( vel_struct.direction == false ) || \
			( gpio_get_pin_level(LIM_RT)  == LOW ) && ( vel_struct.direction == true ) )
			{
				PRINTF_DEBUG && printf("\n#-----Can't move beyond the Limit! Vel Mode-----#\n");
				return;
			}
			//if( gpio_get_pin_level(LIM_RT)  == LOW) {   }
			#endif
			
			// Check the direction to set the state as positive velocity or negative velocity.
			if(vel_struct.direction)
			{
				switch(velocity_x)
				{
					case 0 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_0		: VEL_STATE_0 ; break;
					case 1 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_1	: VEL_STATE_1 ; break;
					case 2 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_2	: VEL_STATE_2 ; break;
					case 3 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_3	: VEL_STATE_3 ; break;
					case 4 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_4	: VEL_STATE_4 ; break;
					case 5 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_5	: VEL_STATE_5 ; break;
					case 6 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_6	: VEL_STATE_6 ; break;
					case 7 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_7	: VEL_STATE_7 ; break;
					case 8 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_8	: VEL_STATE_8 ; break;
					case 9 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_9	: VEL_STATE_9 ; break;
					case 10: vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_neg_10  : VEL_STATE_10; break;
					default: break;
				}
			}
			else
			{
				switch(velocity_x)
				{
					case 0 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_0  : VEL_STATE_0     ; break;
					case 1 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_1  : VEL_STATE_neg_1 ; break;
					case 2 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_2  : VEL_STATE_neg_2 ; break;
					case 3 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_3  : VEL_STATE_neg_3 ; break;
					case 4 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_4  : VEL_STATE_neg_4 ; break;
					case 5 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_5  : VEL_STATE_neg_5 ; break;
					case 6 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_6  : VEL_STATE_neg_6 ; break;
					case 7 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_7  : VEL_STATE_neg_7 ; break;
					case 8 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_8  : VEL_STATE_neg_8 ; break;
					case 9 : vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_9  : VEL_STATE_neg_9 ; break;
					case 10: vel_struct.vel_state = (motor_dir_rev) ? VEL_STATE_10 : VEL_STATE_neg_10; break;
					default: break;
				}
			}
			PRINTF_DEBUG && printf(" KNOB_MOVEMENT_Y SPEED = %d | Direction = %d\n", velocity_x, vel_struct.direction);
		break;
		case CAN_KNOB_AXIS_CHANGE_Z:
		
		break;
		case RFS_DISTANCE_Z:
		{
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, GAP);
			
			// Check what limit is not zero and set it as the limit to limit distance.
			int32_t lim_to_lim_dist = (limit_variables.left_limit_position == 0)
			? limit_variables.right_limit_position
			: limit_variables.left_limit_position;
			
			encoding_CAN_Byte_Data(lim_to_lim_dist);
			can_Write(message_Id, lim_to_lim_dist);
			PRINTF_DEBUG && printf("\nLimit to Limit Distance - Z | %.2f mm | %ld usteps\n", (lim_to_lim_dist / ONE_MM), lim_to_lim_dist);
			break;
		}
		case START_RANGE_Z:
		{
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, SAP);
			int32_t start_range = decoding_CAN_Byte_Data();
			limit_variables.soft_limit_low = start_range + SOFT_LIMIT_OFFSET_MM;
			encoding_CAN_Byte_Data(limit_variables.soft_limit_low);
			can_Write(message_Id, limit_variables.soft_limit_low);
			PRINTF_DEBUG && printf("\nStart Range - Z | %.2f mm | %ld usteps\n", (start_range / ONE_MM), start_range);
			break;
		}
		case END_RANGE_Z:
		{
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, SAP);
			int32_t end_range = decoding_CAN_Byte_Data();
			limit_variables.soft_limit_high = end_range - SOFT_LIMIT_OFFSET_MM;
			encoding_CAN_Byte_Data(limit_variables.soft_limit_high);
			can_Write(message_Id, limit_variables.soft_limit_high);
			PRINTF_DEBUG && printf("\nEnd Range - Z | %.2f mm | %ld usteps\n", (end_range / ONE_MM), end_range);
			break;
		}
		default:
			// error
		break;
	}
	// Switch case for writing directly to register. No checking of register address checking or data checking
	// withing range check is done.
	if(ad == Z)
	{
		switch(cmd)
		{
			case WR_MC:
			{
				message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, WR_MC);
				int32_t wr_reg_data = decoding_CAN_Byte_Data();
				tmc4671_writeInt(MOTOR, typ, wr_reg_data);
				encoding_CAN_Byte_Data(wr_reg_data);
				can_Write(message_Id, wr_reg_data);
				break;
			}
			case RD_MC:
			{
				message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, RD_MC);
				int32_t rd_reg_data = tmc4671_readInt(MOTOR, typ);
				encoding_CAN_Byte_Data(rd_reg_data);
				can_Write(message_Id, rd_reg_data);
				break;
			}
			case RD_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
				read_tlv_flash(tlv_ptr, parameter_id, tlv_traversal);
				encoding_CAN_Byte_Data(tlv_ptr->value_32bit);
				message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, RD_FW_PARAM);
				can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, tlv_ptr->value_32bit);
				can_Write(message_Id, tlv_ptr->value_32bit);
				PRINTF_DEBUG && printf("READ_PARAMETER_FLASH_Z - Tag = %d (or) 0x%x | Length = %d or 0x%x | Data = %ld | 0x%x \n",\
				tlv_ptr->tag, tlv_ptr->tag, tlv_ptr->length, tlv_ptr->length, tlv_ptr->value_32bit, tlv_ptr->value_32bit);
				break;
			}
			case WR_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				uint8_t parameter_len = mot;
				int32_t parameter_val = decoding_CAN_Byte_Data();
				
				write_tlv_flash(parameter_id, &parameter_val, parameter_len);
				message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, WR_FW_PARAM);
				encoding_CAN_Byte_Data(parameter_val);
				can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, parameter_val);
				can_Write(message_Id, parameter_val);
				PRINTF_DEBUG && printf("WRITE_PARAMETER_FLASH_Z - Tag = %d (or) 0x%x | Length = %d or 0x%x | Data = %ld | 0x%x \n",\
				parameter_id, parameter_id, parameter_len, parameter_len, parameter_val, parameter_val);
				break;
			}
			case CHK_FW_PARAM:
			{
				uint8_t parameter_id = typ;
				int32_t value_check = decoding_CAN_Byte_Data();
				check_tlv_param(tlv_ptr, parameter_id, tlv_traversal, value_check);
				PRINTF_DEBUG && printf("CHECK_PARAMETER_FLASH_Z\n");
				break;
			}
			default: break;
		}
	}
	return;
}

void can_Message_Parse_Reeler_Encoder_Operation( axis_current current_axis )
{
	AxC_Operations_t operation_byte = (AxC_Operations_t)can_rx_frame.data[1];
	if(current_axis == GTRON_AXC_TOP)
	{
		switch((AxC_Operations_t)operation_byte)
		{
			case AXC_INITIALIZE:
			
			break;
			case AXC_ENABLE:
			
			break;
			case AXC_DISABLE:
			
			break;
			case AXC_INITIAL_POSITION:
			
			break;
			default: break;
		}
	}
	else if(current_axis == GTRON_AXC_BOT)
	{
		switch((AxC_Operations_t)operation_byte)
		{
			case AXC_INITIALIZE:
			
			break;
			case AXC_ENABLE:
			
			break;
			case AXC_DISABLE:
			
			break;
			case AXC_INITIAL_POSITION:
			
			break;
			default: break;
		}
	}
}

void can_Message_Parse_Reeler_Motor_Operation( axis_current current_axis )
{
	AxC_Operations_t operation_byte = (AxC_Operations_t)can_rx_frame.data[1];
	if(current_axis == GTRON_AXC_TOP)
	{
		switch((AxC_Operations_t)operation_byte)
		{
			case AXC_INITIALIZE:
			
			break;
			case AXC_START:
			
			break;
			case AXC_STOP:
			
			break;
			case AXC_VELOCITY:
			
			break;
			case AXC_ROTATE:
			
			break;
			case AXC_MOVE_TO:
			
			break;
			case AXC_MOVE_BY:
			
			break;
			case AXC_TEETH:
			
			break;
			default: break;
		}
	}
	else if(current_axis == GTRON_AXC_TOP)
	{
		switch((AxC_Operations_t)operation_byte)
		{
			case AXC_INITIALIZE:
			
			break;
			case AXC_START:
			
			break;
			case AXC_STOP:
			
			break;
			case AXC_VELOCITY:
			
			break;
			case AXC_ROTATE:
			
			break;
			case AXC_MOVE_TO:
			
			break;
			case AXC_MOVE_BY:
			
			break;
			case AXC_TEETH:
			
			break;
			default: break;
		}
	}
}

void can_Message_Parse_Reeler(axis_current current_axis)
{
	
	if(current_axis == GTRON_AXC_TOP)
	{
		AxC_Top_Peripherals_t peripheral_byte = (AxC_Top_Peripherals_t)can_rx_frame.data[0];
		switch((AxC_Top_Peripherals_t)peripheral_byte)
		{
			case TOP_DEFAULT: break;
			case TOP_REELER_MOTOR: 
				can_Message_Parse_Reeler_Motor_Operation(current_axis);
			break;
			case TOP_REELER_ENCODER:
				can_Message_Parse_Reeler_Encoder_Operation(current_axis);
			break;
			default: break;
		}
	}
	else if(current_axis == GTRON_AXC_BOT)
	{
		AxC_Bot_Peripherals_t peripheral_byte = (AxC_Bot_Peripherals_t)can_rx_frame.data[0];
		switch((AxC_Bot_Peripherals_t)peripheral_byte)
		{
			case BOT_DEFAULT: break;
			case BOT_REELER_MOTOR:
				can_Message_Parse_Reeler_Motor_Operation(current_axis);
			break;
			case TOP_REELER_ENCODER:
				can_Message_Parse_Reeler_Encoder_Operation(current_axis);
			break;
			default: break;
		}
	}
	return;
}

void can_Message_Parse_Guide_Motor(axis_current current_axis, uint32_t peripheral_byte)
{
	if(current_axis == GTRON_AXC_TOP)
	{
		AxC_Top_Peripherals_t operation_byte = can_rx_frame.data[1];
		switch(operation_byte)
		{
			case AXC_INITIALIZE:
			
			break;
			case AXC_START:
			
			break;
			case AXC_STOP:
			
			break;
			case AXC_VELOCITY:
			
			break;
			case AXC_MOVE_TO:
			
			break;
			case AXC_MOVE_BY:
			
			break;
			case AXC_STATUS_CHECK:
				
			break;
			default: break;
		}
	}
	else if(current_axis == GTRON_AXC_BOT)
	{
		AxC_Bot_Peripherals_t operation_byte = can_rx_frame.data[1];
		switch(operation_byte)
		{
			case AXC_INITIALIZE:
			
			break;
			case AXC_START:
			
			break;
			case AXC_STOP:
			
			break;
			case AXC_VELOCITY:
			
			break;
			case AXC_MOVE_TO:
			
			break;
			case AXC_MOVE_BY:
			
			break;
			case AXC_STATUS_CHECK:
			
			break;
			default: break;
		}
	}
	return;
}

void can_Message_Parse_Guide_Encoder(axis_current current_axis)
{
	if(current_axis == GTRON_AXC_TOP)
	{
		
	}
	else if(current_axis == GTRON_AXC_BOT)
	{
		
	}
	return;
}

void can_Message_Parse_Guide(axis_current current_axis, int32_t data)
{
	
	if(current_axis == GTRON_AXC_TOP)
	{
		AxC_Top_Peripherals_t peripheral_byte = (AxC_Top_Peripherals_t)can_rx_frame.data[0];
		switch((AxC_Top_Peripherals_t)peripheral_byte)
		{
			case TOP_DEFAULT: break;
			case TOP_GUIDE_MOTOR:
			case TOP_VERITCAL_ARRESTOR_MOTOR:
				
			break;
			case TOP_GUIDE_ENCODER:
				
			break;
			default: break;
		}
	}
	else if(current_axis == GTRON_AXC_BOT)
	{
		AxC_Bot_Peripherals_t operation_byte = (AxC_Bot_Peripherals_t)can_rx_frame.data[0];
		switch((AxC_Top_Peripherals_t)operation_byte)
		{
			case BOT_DEFAULT: break;
			case BOT_GUIDE_MOTOR:
			case BOT_VERITCAL_ARRESTOR_MOTOR:
			
			break;
			case BOT_GUIDE_ENCODER:
			
			break;
			default: break;
		}
	}
	return;
}

void can_Message_Process_GTron_Peripheral_Byte(axis_current curr_axis, uint32_t message_Id, int32_t data)
{
	if(curr_axis == GTRON_AXC_TOP)
	{
		switch(message_Id)
		{
			case TOP_REELER_ID:
				
			break;
			case TOP_GUIDE_ID:
				
			break;
			default: break;
		}
	}
	else if(curr_axis == GTRON_AXC_BOT)
	{
		switch(message_Id)
		{
			case BOT_REELER_ID:
				
			break;
			case BOT_GUIDE_ID:
				
			break;
		}
	}
	return;
}

/** 
 * \brief Calls the necessary functions according to the message id and data.
 *
 * @param[in] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */ 
void can_Message_Decode(uint32_t message_Id, int32_t data)
{
	if(can_Message_Crc_Check(message_Id, data))
	{
		//can_Message_Handshake_Tmcl_Ide(message_Id, data);
	}
	switch(axis_id)
	{
		case X_AXIS:
			PRINTF_DEBUG && printf("\nReceived by X: %x %x %x %x Data %x %x %x %x %x", ad, cmd, typ, mot, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Operational_v3_XAxis(message_Id, data); 
		break;
		case Y_AXIS: 
			PRINTF_DEBUG && printf("\nReceived by Y: %x %x %x %x Data %x %x %x %x %x", ad, cmd, typ, mot, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Operational_v3_YAxis(message_Id, data); 
		break;
		case Z_AXIS:
			PRINTF_DEBUG && printf("\nReceived by Z: %x %x %x %x Data %x %x %x %x %x", ad, cmd, typ, mot, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Operational_v3_ZAxis(message_Id, data);
		break;
		case GTRON_AXC_TOP:
			PRINTF_DEBUG && printf("\nReceived by AxC_Top: %x %x %x %x Data %x %x %x %x %x", ad, cmd, typ, mot, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Process_GTron_Peripheral_Byte(axis_id, message_Id, data);
		break;
		case GTRON_AXC_BOT:
			PRINTF_DEBUG && printf("\nReceived by AxC_Bot: %x %x %x %x Data %x %x %x %x %x", ad, cmd, typ, mot, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Process_GTron_Peripheral_Byte(axis_id, message_Id, data);
		break;
		default: break;
	}
	//CAN_Code_Dump_Msgs(message_Id, data);
	return;
}