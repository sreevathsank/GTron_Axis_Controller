/*
 * IMM_CAN_Write.c
 *
 * Created: 18-01-2024 08:56:31
 *  Author: sreevathsank
 */ 

/** 
 * \file 
 *
 * \brief Contains functions to Write message id and data to the CAN transmit buffer.
 */

#include "Bring_Up/CAN/IMM_CAN_Write.h"

/** 
 * \brief Abstraction over can_Write.
 *
 *@param	message_Id 29 bit CAN Message ID
 *@param	peripheral byte
 *@param	operation byte
 *@param	value 4 bytes
 *
 *@return   false/0 -> Success | true/1 ->  Failure.
 */
bool can_AxC_Write(uint32_t msg_id, uint8_t peripheral, uint8_t operation, int32_t value)
{
	can_tx_frame.data[0]	= peripheral;
	can_tx_frame.data[1]	= operation;
	can_tx_frame.data[2]	= (uint8_t)((value >>  24) & 0xFF);		// MSB
	can_tx_frame.data[3]	= (uint8_t)((value >>  16) & 0xFF);
	can_tx_frame.data[4]	= (uint8_t)((value >>   8) & 0xFF);
	can_tx_frame.data[5]	= (uint8_t)((value >>	 0) & 0xFF);	 // LSB
	return can_Write(msg_id, data);
}


/** 
 * \brief Writes message id and data to the CAN transmit buffer.
 *
 * @param[in]	message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in]	data Contains the 4 byte Value and 1 byte CRC.
 * @return   	false/0 -> Success | true/1 ->  Failure.
 */
bool can_Write(uint32_t message_Id, int32_t data)
{
	(void)data;
	//can_tx_frame.data_64bit = data;
	//can_tx_frame.data[4] = message_Id + data;
	can_send(&CAN_1, message_Id, EXT_ID, 6, can_tx_frame);
	return;
}

/** 
 * \brief Interrupt Callback function for the CAN transmit operation.
 *
 * @param void
 * @return void
 */
void can_Tx_Cb(void)
{
	return;
}