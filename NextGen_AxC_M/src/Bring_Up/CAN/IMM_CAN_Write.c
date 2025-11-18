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
 * \brief Writes message id and data to the CAN transmit buffer.
 *
 * @param[in] message_Id The message_Id is a 29-bit CAN identifier contains the Address, Command, Type and Motor values.
 * @param[in] data Contains the 4 byte Value and 1 byte CRC.
 * @return void
 */
void can_Write(uint32_t message_Id, int32_t data)
{
	(void)data;
	//can_tx_frame.data_64bit = data;
	//can_tx_frame.data[4] = message_Id + data;
	//can_send(&CAN_1, message_Id, EXT_ID, 6, can_tx_frame);
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