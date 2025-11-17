/*
 * TMCL_IDE_reply.c
 *
 * Created: 31-01-2024 13:15:00
 *  Author: sreevathsank
 */ 

/** 
 * \file
 *
 * \brief Contains the functions required to read, write and reply to TMCL-IDE commands which includes Direct Mode and Register Browser.
 */

#include "Bring_Up/CAN/TMCL_IDE_reply.h"

/** 
 * \brief Calculates the CRC and returns it.
 * 
 * @param[in] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in] data Contains the 4 byte Value and 1 byte CRC.
 * @return crc unsigned 8-bit value of CRC.
 */
uint8_t can_Message_Calculate_Crc(uint32_t msg_Id, int32_t value)
{
	ad = (msg_Id >> 25) & 0x0F;
	cmd = (msg_Id >> 17) & 0xFF;
	typ = (msg_Id >> 9) & 0xFF;
	mot = msg_Id & 0x1FF;

	
	/*crc = ad + cmd + typ + mot +	
	      ((value >> 24) & 0xFF) +	
		  ((value >> 16) & 0xFF) +	
		  ((value >> 8) ) +	
		  (value & 0xFF);
		  */
	crc = ad + cmd + typ + mot +
		  can_tx_frame.data[0] +
		  can_tx_frame.data[1] +
		  can_tx_frame.data[2] +
		  can_tx_frame.data[3];
	
	return crc;
}


/** 
 * \brief Assigns each byte of a 4 byte value to the can_tx_frame's 8 byte data.
 * 
 * @param[in] value 
 * @return void
 */ 
void encoding_CAN_Byte_Data(int32_t value)
{
	can_tx_frame.data[0] = (uint8_t)((value >> 24) & 0xFF);
	can_tx_frame.data[1] = (uint8_t)((value >> 16) & 0xFF);
	can_tx_frame.data[2] = (uint8_t)((value >> 8) & 0xFF);
	can_tx_frame.data[3] = (uint8_t)(value & 0xFF);
	return;
}

/** 
 * \brief Decodes the data from the CAN receive frame and returns it as a 32-bit integer.
 *
 * @param void
 * @return ret_value The decoded value.
 */
int32_t decoding_CAN_Byte_Data(void)
{
	int32_t ret_value = 0;
	ret_value |= (int32_t)(can_rx_frame.data[0] << 24);
	ret_value |= (int32_t)(can_rx_frame.data[1] << 16);
	ret_value |= (int32_t)(can_rx_frame.data[2] << 8);
	ret_value |= (int32_t)can_rx_frame.data[3];
	return ret_value;
}

/** 
 * \brief Assigns each byte of a 4 byte value to the can_tx_frame's 8 byte data.
 * 
 * @param[in] value 
 * @return void
 */ 
void encoding_GTron_CAN_Byte_Data(uint8_t peripheral_byte, uint8_t operation_byte, int32_t value)
{
	can_tx_frame.data[0] = (uint8_t)peripheral_byte;
	can_tx_frame.data[1] = (uint8_t)operation_byte;
	can_tx_frame.data[2] = (uint8_t)((value >> 24) & 0xFF);
	can_tx_frame.data[3] = (uint8_t)((value >> 16) & 0xFF);
	can_tx_frame.data[4] = (uint8_t)((value >> 8) & 0xFF);
	can_tx_frame.data[5] = (uint8_t)(value & 0xFF);
	return;
}

/** 
 * \brief Decodes the data from the GTron CAN receive frame and returns it as a 32-bit integer.
 *
 * @param void
 * @return ret_value The decoded value.
 */
int32_t decoding_GTon_CAN_Byte_Data(void)
{
	int32_t ret_value = 0;
	ret_value |= (int32_t)(can_rx_frame.data[2] << 24);
	ret_value |= (int32_t)(can_rx_frame.data[3] << 16);
	ret_value |= (int32_t)(can_rx_frame.data[4] << 8);
	ret_value |= (int32_t)can_rx_frame.data[5];
	return ret_value;
}

/** 
 * \brief Assigns the message id and data as 0.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void zero_MessageID_Data(uint32_t message_Id, int32_t data)
{
	message_Id = 0;
	data = 0;
	
	return;
}

/** 
 * \brief TMCL-IDE function that replies hard coded values for the Value command.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_Version(uint32_t message_Id, int32_t data)
{
	switch(typ)
	{
		case 0x00:
			zero_MessageID_Data(message_Id, data);
// 			#if X_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x30, 0x30, 0x31);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_Y, 0x30, 0x30, 0x31);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			message_Id = CAN_ID(REPLY_ID_Z, 0x30, 0x30, 0x31);
// 			#end	
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x30, 0x30, 0x31);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x30, 0x30, 0x31);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x30, 0x30, 0x31);
				break;
				default: break;
			}	
			data = 0x30335632;									// Hardcoded value.
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = 0x39;
			can_Write(message_Id, data);
		break;
		case 0x01:
			zero_MessageID_Data(message_Id, data);
// 			#if X_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, 0x88);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, 0x88);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, 0x88);
// 			#end
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, 0x88);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, 0x88);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, 0x88);
				break;
				default: break;
			}
			data = 0x09030C00;									// Hardcoded value.
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = 0x07;
			can_Write(message_Id, data);
		break;
		case 0x05:
			zero_MessageID_Data(message_Id, data);
// 			#if X_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, 0x88);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, 0x88);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, 0x88);
// 			#end
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, 0x88);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, 0x88);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, 0x88);
				break;
				default: break;
			}
			data = 0x180C0000;									// Hardcoded value.
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = 0x13;
			can_Write(message_Id, data);
		break;
	}	
	return;
}

/** 
 * \brief TMCL-IDE function that replies hard coded values for the Get Global Parameter(GGP) command from Direct Mode.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_GGP(uint32_t msg_Id, int32_t value)
{
	switch(typ)
	{
		case 0x01:
			zero_MessageID_Data(msg_Id, value);
// 			#if X_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
// 			#end
			switch(axis_id)
			{
				case X_AXIS:
					msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
				break;
				case Y_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
				break;
				case Z_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
				break;
				default: break;
			}
			value = 0x40000000;							// Hardcoded value.
			can_tx_frame.data_64bit = value;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(msg_Id, value);
			can_Write(msg_Id, value);
		break;
		case 0x02:
			zero_MessageID_Data(msg_Id, value);
// 			#if X_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
// 			#end
			switch(axis_id)
			{
				case X_AXIS:
					msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
				break;
				case Y_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
				break;
				case Z_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
				break;	
				default: break;
			}
			value = 0x01000000;							// Hardcoded value.
			can_tx_frame.data_64bit = value;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(msg_Id, value);
			can_Write(msg_Id, value);
		break;
		case 0x04:
			zero_MessageID_Data(msg_Id, value);
// 			#if X_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
// 			#endif
			switch(axis_id)
			{
				case X_AXIS:
					msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
				break;
				case Y_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
				break;
				case Z_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
				break;
				default: break;
			}
			value = 0x0D020006;							// Hardcoded value.
			can_tx_frame.data_64bit = value;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(msg_Id, value);
			can_Write(msg_Id, value);
		break;
		case 0x05:
			zero_MessageID_Data(msg_Id, value);
// 			#if X_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
// 			#endif
			switch(axis_id)
			{
				case X_AXIS:
					msg_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GGP);
				break;
				case Y_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GGP);
				break;
				case Z_AXIS:
					msg_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GGP);
				break;
				default: break;
			}
			value = 0x02000000;							// Hardcoded value.
			can_tx_frame.data_64bit = value;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(msg_Id, value);
			can_Write(msg_Id, value);
		break;
	}
	return;
}

/** 
 * \brief TMCL-IDE function that replies hard coded values for the Assignment command from Direct Mode.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_Assignment(uint32_t message_Id, int32_t data)
{
	switch(typ)
	{
		case 0x03:
			zero_MessageID_Data(message_Id, data);
// 			#if X_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
// 			#endif
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
				break;
				default: break;
			}
			
			data = 0x0D000000;					// Hardcoded value.
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = 0x03;
			can_Write(message_Id, data);
		break;
		case 0x04:
			zero_MessageID_Data(message_Id, data);
// 			#if X_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
// 			#endif
// 			#if Y_AXIS_TABLE
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
// 			#endif
// 			#if Z_AXIS_PROTO
// 			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
// 			#endif
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ASSIGNMENT);
				break;
				default: break;
			}
			data = 0x0D020006;					// Hardcoded value.
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = 0x0B;
			can_Write(message_Id, data);
		break;
	}
	return;
}


/** 
 * \brief TMCL-IDE function that replies hard coded values for the Get Axis Parameter(GAP) command from Direct Mode.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_GAP(uint32_t message_Id, int32_t data)
{
	switch(typ)
	{
		case GAP_TORQUE_P:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_TORQUE_P_TORQUE_I);
			data = (int32_t)((data >> 16) & 0xFFFF);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_TORQUE_I:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_TORQUE_P_TORQUE_I);
			data = (int32_t)(data & 0xFFFF);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_VELOCITY_P:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_P_VELOCITY_I);
			data = (int32_t)((data >> 16) & 0xFFFF);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_VELOCITY_I:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_TORQUE_P_TORQUE_I);
			data = (int32_t)(data & 0xFFFF);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;	
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_POSITION_P:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_P_POSITION_I);
			data = (int32_t)((data >> 16) & 0xFFFF);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_ACCELERATION:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_ACCELERATION_LIMIT);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;	
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_EN_VELOCITY_RAMP:
			zero_MessageID_Data(message_Id, data);
			data = 0x01;
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_MAX_CURRENT:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_TORQUE_FLUX_LIMITS);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case GAP_MAX_SPEED:
			zero_MessageID_Data(message_Id, data);
			data = tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT);
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GAP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GAP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GAP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
	}
	return;
}

/** 
 * \brief TMCL-IDE function that replies hard coded values for the GIO command from Direct Mode.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_GIO(uint32_t message_Id, int32_t data)
{
	switch(typ)
	{
		case 0x05:
			zero_MessageID_Data(message_Id, data);
			data = ZERO_HEX;
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, GIO);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, GIO);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, GIO);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = data;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
	}
	return;
}

/** 
 * \brief TMCL-IDE function for Rotate Right(ROR) and rotates the motor for the given speed.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_ROR(uint32_t message_Id, int32_t data)
{
	int32_t velocity_limit = decoding_CAN_Byte_Data();
	tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, POSITION_MODE);
	tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_HIGH);
	tmc4671_writeInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT, velocity_limit);
	switch(axis_id)
	{
		case X_AXIS:
			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ROR);
		break;
		case Y_AXIS:
			message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, ROR);
		break;
		case Z_AXIS:
			message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, ROR);
		break;
		default: break;
	}
	encoding_CAN_Byte_Data(velocity_limit);
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, velocity_limit);
	can_Write(message_Id, velocity_limit);
	
	return;
}

/** 
 * \brief TMCL-IDE function for Rotate Left(ROL) and rotates the motor for the given speed.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_ROL(uint32_t message_Id, int32_t data)
{
	int32_t velocity_limit = decoding_CAN_Byte_Data();
	tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, POSITION_MODE);
	tmc4671_setAbsolutTargetPosition(MOTOR, POSITION_LOW);
	tmc4671_writeInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT, velocity_limit);
	switch(axis_id)
	{
		case X_AXIS:
			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, ROL);
		break;
		case Y_AXIS:
			message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, ROL);
		break;
		case Z_AXIS:
			message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, ROL);
		break;
		default: break;
	}
	encoding_CAN_Byte_Data(velocity_limit);
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, velocity_limit);
	can_Write(message_Id, velocity_limit);
	
	return;
}

/** 
 * \brief TMCL-IDE function for Motor Stop(MST) which halts the motor.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_MST(uint32_t message_Id, int32_t data)
{
	tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, STOPPED_MODE);
	zero_MessageID_Data(message_Id, data);
	switch(axis_id)
	{
		case X_AXIS:
			message_Id = CAN_ID(REPLY_ID_X, X, 0x64, MST);
		break;
		case Y_AXIS:
			message_Id = CAN_ID(REPLY_ID_Y, Y, 0x64, MST);
		break;
		case Z_AXIS:
			message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, MST);
		break;
		default: break;
	}
	data = ZERO_HEX;
	can_tx_frame.data_64bit = data;
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
	can_Write(message_Id, data);
	
	return;
}

/** 
 * \brief TMCL-IDE function for Move Position (MVP) moves the motor to the desired position either relatively(Move By) or absolutely(Move To).
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_MVP(uint32_t message_Id, int32_t data)
{
	check_move_done = true;
	int32_t target_position = decoding_CAN_Byte_Data();
	switch(typ)
	{
		case MVP_ABS:
			tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, POSITION_MODE);
			set_TargetVelocity(velocity_limit);
			tmc4671_setAbsolutTargetPosition(MOTOR, target_position);
			//call_all_ramp_params_functions(&ramp_Parameters);
			//run_Trapezoidal_Ramp();
			zero_MessageID_Data(message_Id, data);
			data = target_position;
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, MVP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, MVP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, MVP);
				break;
			}
			can_tx_frame.data_64bit = target_position;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
		case MVP_REL:
			tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, POSITION_MODE);
			set_TargetVelocity(velocity_limit);
			tmc4671_setRelativeTargetPosition(MOTOR, target_position);
			//timer_start(&TIMER_0);
			//call_all_ramp_params_functions(&ramp_Parameters);
			//run_Trapezoidal_Ramp();
			zero_MessageID_Data(message_Id, data);
			data = target_position;
			switch(axis_id)
			{
				case X_AXIS:
					message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, MVP);
				break;
				case Y_AXIS:
					message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, MVP);
				break;
				case Z_AXIS:
					message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, MVP);
				break;
				default: break;
			}
			can_tx_frame.data_64bit = target_position;
			can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
			can_Write(message_Id, data);
		break;
	}
	return;
}

/** 
 * \brief Common function used for writing values to the TMC4671's register via the Register Browser in the TMCL-IDE.
 * 
 * @param[in] address Register's address to be written to.
 * @param[in] value Value to written to the register.
 * @return void
 */
void write_MC_common(int32_t address, int32_t value)
{
	tmc4671_writeInt(MOTOR, address, value);
	zero_MessageID_Data(message_Id, data);
	encoding_CAN_Byte_Data(value);
	switch(axis_id)
	{
		case X_AXIS:
			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, WR_MC);
		break;
		case Y_AXIS:
			message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, WR_MC);
		break;
		case Z_AXIS:
			message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, WR_MC);
		break;
		default: break;
	}
	//can_tx_frame.data_64bit = data;
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
	can_Write(message_Id, data);
	
	return;
}

/** 
 * This function has all the registers of TMC4671 with write access and calls the function to write the value to a register.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_WR_MC(uint32_t message_Id, int32_t data)
{
	int32_t value = decoding_CAN_Byte_Data();
	switch(typ)
	{
		//case TMC4671_CHIPINFO_DATA:
		case TMC4671_CHIPINFO_ADDR:
		//case TMC4671_ADC_RAW_DATA:
		case TMC4671_ADC_RAW_ADDR:
		case TMC4671_dsADC_MCFG_B_MCFG_A:
		case TMC4671_dsADC_MCLK_A:
		case TMC4671_dsADC_MCLK_B:
		case TMC4671_dsADC_MDEC_B_MDEC_A:
		case TMC4671_ADC_I1_SCALE_OFFSET:
		case TMC4671_ADC_I0_SCALE_OFFSET:
		case TMC4671_ADC_I_SELECT:
		case TMC4671_ADC_I1_I0_EXT:
		case TMC4671_DS_ANALOG_INPUT_STAGE_CFG:
		case TMC4671_AENC_0_SCALE_OFFSET:
		case TMC4671_AENC_1_SCALE_OFFSET:
		case TMC4671_AENC_2_SCALE_OFFSET:
		case TMC4671_AENC_SELECT:
		//case TMC4671_ADC_IWY_IUX:
		//case TMC4671_ADC_IV:
		//case TMC4671_AENC_WY_UX:
		//case TMC4671_AENC_VN:
		case TMC4671_PWM_POLARITIES:
		case TMC4671_PWM_MAXCNT:
		case TMC4671_PWM_BBM_H_BBM_L:
		case TMC4671_PWM_SV_CHOP:
		case TMC4671_MOTOR_TYPE_N_POLE_PAIRS:
		case TMC4671_PHI_E_EXT:
		case TMC4671_PHI_M_EXT:
		case TMC4671_POSITION_EXT:
		case TMC4671_OPENLOOP_MODE:
		case TMC4671_OPENLOOP_ACCELERATION:
		case TMC4671_OPENLOOP_VELOCITY_TARGET:
		case TMC4671_OPENLOOP_VELOCITY_ACTUAL:
		case TMC4671_OPENLOOP_PHI:
		case TMC4671_UQ_UD_EXT:
		case TMC4671_ABN_DECODER_MODE:
		case TMC4671_ABN_DECODER_PPR:
		case TMC4671_ABN_DECODER_COUNT:
		case TMC4671_ABN_DECODER_COUNT_N:
		case TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET:
		//case TMC4671_ABN_DECODER_PHI_E_PHI_M:
		case TMC4671_ABN_2_DECODER_MODE:
		case TMC4671_ABN_2_DECODER_PPR:
		case TMC4671_ABN_2_DECODER_COUNT:
		case TMC4671_ABN_2_DECODER_COUNT_N:
		case TMC4671_ABN_2_DECODER_PHI_M_OFFSET:
		//case TMC4671_ABN_2_DECODER_PHI_M:
		case TMC4671_HALL_MODE:
		case TMC4671_HALL_POSITION_060_000:
		case TMC4671_HALL_POSITION_180_120:
		case TMC4671_HALL_POSITION_300_240:
		case TMC4671_HALL_PHI_E_PHI_M_OFFSET:
		case TMC4671_HALL_DPHI_MAX:
		//case TMC4671_HALL_PHI_E_INTERPOLATED_PHI_E:
		//case TMC4671_HALL_PHI_M:
		case TMC4671_AENC_DECODER_MODE:
		case TMC4671_AENC_DECODER_N_MASK_N_THRESHOLD:
		//case TMC4671_AENC_DECODER_PHI_A_RAW:
		case TMC4671_AENC_DECODER_PHI_A_OFFSET:
		//case TMC4671_AENC_DECODER_PHI_A:
		case TMC4671_AENC_DECODER_PPR:
		//case TMC4671_AENC_DECODER_COUNT:
		case TMC4671_AENC_DECODER_COUNT_N:
		case TMC4671_AENC_DECODER_PHI_E_PHI_M_OFFSET:
		//case TMC4671_AENC_DECODER_PHI_E_PHI_M:
		case TMC4671_AENC_DECODER_POSITION:
		case TMC4671_CONFIG_DATA:
		case TMC4671_CONFIG_ADDR:
		case TMC4671_VELOCITY_SELECTION:
		case TMC4671_POSITION_SELECTION:
		case TMC4671_PHI_E_SELECTION:
		//case TMC4671_PHI_E:
		case TMC4671_PID_FLUX_P_FLUX_I:
		case TMC4671_PID_TORQUE_P_TORQUE_I:
		case TMC4671_PID_VELOCITY_P_VELOCITY_I:
		case TMC4671_PID_POSITION_P_POSITION_I:
		case TMC4671_PID_TORQUE_FLUX_TARGET_DDT_LIMITS:
		case TMC4671_PIDOUT_UQ_UD_LIMITS:
		case TMC4671_PID_TORQUE_FLUX_LIMITS:
		case TMC4671_PID_ACCELERATION_LIMIT:
		case TMC4671_PID_VELOCITY_LIMIT:
		case TMC4671_PID_POSITION_LIMIT_LOW:
		case TMC4671_PID_POSITION_LIMIT_HIGH:
		case TMC4671_MODE_RAMP_MODE_MOTION:
		case TMC4671_PID_TORQUE_FLUX_TARGET:
		case TMC4671_PID_TORQUE_FLUX_OFFSET:
		case TMC4671_PID_VELOCITY_TARGET:
		case TMC4671_PID_VELOCITY_OFFSET:
		case TMC4671_PID_POSITION_TARGET:
		//case TMC4671_PID_TORQUE_FLUX_ACTUAL:
		//case TMC4671_PID_VELOCITY_ACTUAL:
		case TMC4671_PID_POSITION_ACTUAL:
		//case TMC4671_PID_ERROR_DATA:
		case TMC4671_PID_ERROR_ADDR:
		case TMC4671_INTERIM_DATA:
		case TMC4671_INTERIM_ADDR:
		case TMC4671_WATCHDOG_CFG:
		case TMC4671_ADC_VM_LIMITS:
		//case TMC4671_INPUTS_RAW:
		//case TMC4671_OUTPUTS_RAW:
		case TMC4671_STEP_WIDTH:
			write_MC_common(typ, value);
		break;
		default:
			// error
		break;
	}
	return;
} 

/** 
 * \brief Reads the value stored in the register and sends it to the CAN transmit buffer. 
 *
 * @param[in] address Address of the register to read from.
 * @return void
 */
void read_MC_common(int32_t address)
{
	zero_MessageID_Data(message_Id, data);
	int32_t value = tmc4671_readInt(MOTOR, address);
	encoding_CAN_Byte_Data(value);
	switch(axis_id)
	{
		case X_AXIS:
			message_Id = CAN_ID(REPLY_ID_X, 0x01, 0x64, RD_MC);
		break;
		case Y_AXIS:
			message_Id = CAN_ID(REPLY_ID_Y, 0x01, 0x64, RD_MC);
		break;
		case Z_AXIS:
			message_Id = CAN_ID(REPLY_ID_Z, 0x01, 0x64, RD_MC);
		break;
		default: break;
	}
	//can_tx_frame.data_64bit = data;
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
	can_Write(message_Id, data);
	
	return;
}

/** 
 * \brief This function has cases for all the registers of TMC4671 with read access and calls the function to read the register.
 *
 * @param[out] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[out] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void reply_RD_MC(uint32_t message_Id, int32_t data)
{
	//int32_t value = decoding_Byte_Data();
	switch(typ)
	{
		case TMC4671_CHIPINFO_DATA:
		case TMC4671_CHIPINFO_ADDR:
		case TMC4671_ADC_RAW_DATA:
		case TMC4671_ADC_RAW_ADDR:
		case TMC4671_dsADC_MCFG_B_MCFG_A:
		case TMC4671_dsADC_MCLK_A:
		case TMC4671_dsADC_MCLK_B:
		case TMC4671_dsADC_MDEC_B_MDEC_A:
		case TMC4671_ADC_I1_SCALE_OFFSET:
		case TMC4671_ADC_I0_SCALE_OFFSET:
		case TMC4671_ADC_I_SELECT:
		case TMC4671_ADC_I1_I0_EXT:
		case TMC4671_DS_ANALOG_INPUT_STAGE_CFG:
		case TMC4671_AENC_0_SCALE_OFFSET:
		case TMC4671_AENC_1_SCALE_OFFSET:
		case TMC4671_AENC_2_SCALE_OFFSET:
		case TMC4671_AENC_SELECT:
		case TMC4671_ADC_IWY_IUX:
		case TMC4671_ADC_IV:
		case TMC4671_AENC_WY_UX:
		case TMC4671_AENC_VN:
		case TMC4671_PWM_POLARITIES:
		case TMC4671_PWM_MAXCNT:
		case TMC4671_PWM_BBM_H_BBM_L:
		case TMC4671_PWM_SV_CHOP:
		case TMC4671_MOTOR_TYPE_N_POLE_PAIRS:
		case TMC4671_PHI_E_EXT:
		case TMC4671_PHI_M_EXT:
		case TMC4671_POSITION_EXT:
		case TMC4671_OPENLOOP_MODE:
		case TMC4671_OPENLOOP_ACCELERATION:
		case TMC4671_OPENLOOP_VELOCITY_TARGET:
		case TMC4671_OPENLOOP_VELOCITY_ACTUAL:
		case TMC4671_OPENLOOP_PHI:
		case TMC4671_UQ_UD_EXT:
		case TMC4671_ABN_DECODER_MODE:
		case TMC4671_ABN_DECODER_PPR:
		case TMC4671_ABN_DECODER_COUNT:
		case TMC4671_ABN_DECODER_COUNT_N:
		case TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET:
		case TMC4671_ABN_DECODER_PHI_E_PHI_M:
		case TMC4671_ABN_2_DECODER_MODE:
		case TMC4671_ABN_2_DECODER_PPR:
		case TMC4671_ABN_2_DECODER_COUNT:
		case TMC4671_ABN_2_DECODER_COUNT_N:
		case TMC4671_ABN_2_DECODER_PHI_M_OFFSET:
		case TMC4671_ABN_2_DECODER_PHI_M:
		case TMC4671_HALL_MODE:
		case TMC4671_HALL_POSITION_060_000:
		case TMC4671_HALL_POSITION_180_120:
		case TMC4671_HALL_POSITION_300_240:
		case TMC4671_HALL_PHI_E_PHI_M_OFFSET:
		case TMC4671_HALL_DPHI_MAX:
		case TMC4671_HALL_PHI_E_INTERPOLATED_PHI_E:
		case TMC4671_HALL_PHI_M:
		case TMC4671_AENC_DECODER_MODE:
		case TMC4671_AENC_DECODER_N_MASK_N_THRESHOLD:
		case TMC4671_AENC_DECODER_PHI_A_RAW:
		case TMC4671_AENC_DECODER_PHI_A_OFFSET:
		case TMC4671_AENC_DECODER_PHI_A:
		case TMC4671_AENC_DECODER_PPR:
		case TMC4671_AENC_DECODER_COUNT:
		case TMC4671_AENC_DECODER_COUNT_N:
		case TMC4671_AENC_DECODER_PHI_E_PHI_M_OFFSET:
		case TMC4671_AENC_DECODER_PHI_E_PHI_M:
		case TMC4671_AENC_DECODER_POSITION:
		case TMC4671_CONFIG_DATA:
		case TMC4671_CONFIG_ADDR:
		case TMC4671_VELOCITY_SELECTION:
		case TMC4671_POSITION_SELECTION:
		case TMC4671_PHI_E_SELECTION:
		case TMC4671_PHI_E:
		case TMC4671_PID_FLUX_P_FLUX_I:
		case TMC4671_PID_TORQUE_P_TORQUE_I:
		case TMC4671_PID_VELOCITY_P_VELOCITY_I:
		case TMC4671_PID_POSITION_P_POSITION_I:
		case TMC4671_PID_TORQUE_FLUX_TARGET_DDT_LIMITS:
		case TMC4671_PIDOUT_UQ_UD_LIMITS:
		case TMC4671_PID_TORQUE_FLUX_LIMITS:
		case TMC4671_PID_ACCELERATION_LIMIT:
		case TMC4671_PID_VELOCITY_LIMIT:
		case TMC4671_PID_POSITION_LIMIT_LOW:
		case TMC4671_PID_POSITION_LIMIT_HIGH:
		case TMC4671_MODE_RAMP_MODE_MOTION:
		case TMC4671_PID_TORQUE_FLUX_TARGET:
		case TMC4671_PID_TORQUE_FLUX_OFFSET:
		case TMC4671_PID_VELOCITY_TARGET:
		case TMC4671_PID_VELOCITY_OFFSET:
		case TMC4671_PID_POSITION_TARGET:
		case TMC4671_PID_TORQUE_FLUX_ACTUAL:
		case TMC4671_PID_VELOCITY_ACTUAL:
		case TMC4671_PID_POSITION_ACTUAL:
		case TMC4671_PID_ERROR_DATA:
		case TMC4671_PID_ERROR_ADDR:
		case TMC4671_INTERIM_DATA:
		case TMC4671_INTERIM_ADDR:
		case TMC4671_WATCHDOG_CFG:
		case TMC4671_ADC_VM_LIMITS:
		case TMC4671_INPUTS_RAW:
		case TMC4671_OUTPUTS_RAW:
		case TMC4671_STEP_WIDTH:
			read_MC_common(typ);
		break;
		default:
			// error
		break;
	}
	return;
}