/*
 * MCD_v3.c
 *
 * Created: 06-02-2024 12:12:09
 *  Author: sreevathsank
 */

/** 
 * \file
 *
 * \brief Contains the functions to reply and process MCD commands.
 */ 
#include "Bring_Up/CAN/MCD_v3.h"

double convert_PPS_To_RPM(double value)
{
	return (double)( (value * MINUTES) / TMC4671_ROTATION);		// needs review.
}

double_t convert_RPM_To_PPS(double_t value)
{
	return ( (value * TMC4671_ROTATION) / MINUTES);		// needs review.
}

/** 
 * \brief Replies to the Ping command and is hardcoded.
 *
 * @param void
 * @return void
 */
//void do_4671_Ping(void)
//{
//	//value = can_rx_frame.data_64bit;
//	tmc4671_writeInt(MOTOR, TMC4671_CHIPINFO_ADDR, ZERO_HEX);
//	//if(VERSION_4671 == tmc4671_readInt(MOTOR, TMC4671_CHIPINFO_DATA))
//	{
//		int32_t value = ZERO_HEX;
//		switch(axis_id)
//		{
//			case X_AXIS: message_Id = CAN_ID(REPLY_ID_X, X, 0x64, 0x8A); break;
//			case Y_AXIS: message_Id = CAN_ID(REPLY_ID_Y, Y_ADDR, 0x64, 0x8A); break;
//			case Z_AXIS: message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, 0x8A); break;
//			default: break;
//		}
//		encoding_CAN_Byte_Data(0x01);
//		can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
//		can_Write(message_Id, value);
//		PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot, can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
//	}
//}

//void do_Move_Done_Ping(void)
//{
//	int32_t value = 0x01;
//	switch(axis_id)
//	{
//		case X_AXIS: message_Id = CAN_ID(REPLY_ID_X, X, 0x64, 0x8A); break;
//		case Y_AXIS: message_Id = CAN_ID(REPLY_ID_Y, Y_ADDR, 0x64, 0x8A); break;
//		case Z_AXIS: message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, 0x8A); break;
//	}
//	if(limit_variables.homing)
//	{
//		encoding_CAN_Byte_Data(0x03);
//		can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
//	}
//	else if(limit_variables.homing == false)
//	{
//		encoding_CAN_Byte_Data(0x00);
//		can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, data);
//	}
//	can_Write(message_Id, value); 
//	printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot, can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
//	return;
//}

void reeler_Move_Done(void)
{
	if(axis_id == GTRON_AXC_TOP) { message_Id = CAN_REPLY_TOP_RACK_ID; }
	else if(axis_id == GTRON_AXC_BOT) { message_Id = CAN_REPLY_BOT_RACK_ID; }
	can_tx_frame.data[0] = REELER_MOTOR;
	can_tx_frame.data[1] = AXC_MOVE_DONE;
	for(int32_t i = 2; i < 8; i++) { can_tx_frame.data[i] = 0x00; }
	can_Write(message_Id, data);
	PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot, can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
	int32_t current_position = tmc4671_getActualPosition(MOTOR);
	PRINTF_DEBUG && printf(" | Reeler Move Done | current position = %ld steps or %.2f mm\n", current_position, (current_position / TMC4671_MOVE_MM(1)) );
	check_move_done = false;
	
	return;
}

/** 
 * \brief Replies to Software while Reference Search.
 * \brief Replying with non zero value means Reference Search is Active.
 * \brief Replying with zero means Reference Search is Done.
 *
 * @param void
 * @return void
 */
//void do_Ref_Search_Ping(void)
//{
//	switch(axis_id)
//	{
//		case X_AXIS: message_Id = CAN_ID(REPLY_ID_X, X, 0x64, RFS); break;
//		case Y_AXIS: message_Id = CAN_ID(REPLY_ID_Y, Y_ADDR, 0x64, RFS); break;
//		case Z_AXIS: message_Id = CAN_ID(REPLY_ID_Z, Z, 0x64, RFS); break;
//	}
//	if(limit_variables.homing)
//	{
//		can_tx_frame.data[0] = ZERO_HEX;
//		can_tx_frame.data[1] = ZERO_HEX;
//		can_tx_frame.data[2] = ZERO_HEX;
//		can_tx_frame.data[3] = 0x05;		// Some non-zero value
//	}
//	else if(limit_variables.homing == false)
//	{
//		can_tx_frame.data[0] = ZERO_HEX;
//		can_tx_frame.data[1] = ZERO_HEX;
//		can_tx_frame.data[2] = ZERO_HEX;
//		can_tx_frame.data[3] = ZERO_HEX;
//	}
//	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, can_tx_frame.data_64bit);
//	can_Write(message_Id, data);
//	switch(axis_id)
//	{
//		case X_AXIS:
//			PRINTF_DEBUG && printf("\n ad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x RFS_PING_X", ad, cmd, typ ,mot, can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
//		break;
//		case Y_AXIS:
//			PRINTF_DEBUG && printf("\n ad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x RFS_PING_Y", ad, cmd, typ ,mot, can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
//		break;
//		case Z_AXIS:
//			PRINTF_DEBUG && printf("\n ad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x RFS_PING_Z", ad, cmd, typ ,mot, can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
//		break;
//	}
//	return;	
//}

/** 
 * \brief Common function to reply to MCD commands
 *
 * @param[in] ad Address of the Motor
 * @param[in] cmd Command or Instruction
 * @param[in] typ Type of the Instruction (or) The sub-instruction
 * @param[in] mot Motor number (usually 0)
 * @return void
 */
void reply_MCD_Common(uint8_t ad, uint8_t cmd, uint8_t typ, uint8_t mot)
{
	message_Id = CAN_ID(ad, cmd, typ, mot);
	can_tx_frame.data_64bit = 0;
	encoding_CAN_Byte_Data(decoding_CAN_Byte_Data());
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, can_tx_frame.data_64bit);
	can_Write(message_Id, data);
	uint8_t print_buf[64];
	PRINTF_DEBUG && printf("\nad %x  cmd %x  typ %x mot %x Data %x %x %x %x %x", ad, cmd, typ ,mot,can_tx_frame.data[0], can_tx_frame.data[1], can_tx_frame.data[2], can_tx_frame.data[3], can_rx_frame.data[4]);
	return;
}

void reply_Echo(uint32_t message_Id, int32_t data)
{
	for(int iter = 0; iter < 4; iter++) { can_tx_frame.data[iter] = can_rx_frame.data[iter]; }
	can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, can_tx_frame.data_64bit);
	can_Write(message_Id, can_tx_frame.data_64bit);
	return;
}

/** 
 * \brief Writes the value given by the MCD command to the TMC4671 register.
 *
 * @param[in] address Address of the register to be written to
 * @param[in] ad      Address of the Motor
 * @param[in] cmd     Command or Instruction
 * @param[in] typ     Type of the Instruction (or) The sub-instruction
 * @param[in] mot     Motor number (usually 0)
 * @return void
 */
void write_MCD_MC(int32_t address, int32_t ad, int32_t cmd, int32_t typ, int32_t mot)
{
	int32_t value = decoding_CAN_Byte_Data();
	tmc4671_writeInt(MOTOR, address, value);
	reply_MCD_Common(ad, cmd, typ, mot);
}

void qdec_Clear_Counter(void)
{
	
}


