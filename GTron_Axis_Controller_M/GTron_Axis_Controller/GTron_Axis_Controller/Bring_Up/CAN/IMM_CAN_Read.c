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
	if(!hri_can_read_RXF0S_F0FL_bf( (void *)CAN1) ) {
		can_rx_int = 0;
		return;
	}
	int32_t data;
	can_rx_frame.data_64bit = 0;
	message_Id = 0;
	ad = 0; cmd = 0; typ = 0; mot = 0;
	
	can_receive(&CAN_1, &message_Id, &can_rx_frame);
	data = can_rx_frame.data_64bit;
	can_Message_Decode(message_Id, data);
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

void can_Message_Process_GTron_Message_Data()
{
	rx_can_cmd_info.id = message_Id;
	memcpy(rx_can_cmd_info.data, can_rx_frame.data, CAN_DATA_FIELD_LEN);
	rx_can_cmd_info.value = decoding_GTon_CAN_Byte_Data();
	PRINTF_DEBUG ? printf("\nMsgID = %x | CAN Data Field = 0x%x or %ld\n", rx_can_cmd_info.id, rx_can_cmd_info.value, rx_can_cmd_info.value): 0;
	parse_GTron_CAN_Msg_Data();
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
	if(can_Message_Crc_Check(message_Id, data)) {
		//can_Message_Handshake_Tmcl_Ide(message_Id, data);
	}
	switch(axis_id)
	{
		case GTRON_AXC_TOP:
			PRINTF_DEBUG && printf("\nReceived by AxC_Top: %x Data %x %x %x %x %x", message_Id, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Process_GTron_Message_Data();
		break;
		case GTRON_AXC_BOT:
			PRINTF_DEBUG && printf("\nReceived by AxC_Bot: %x Data %x %x %x %x %x", message_Id, can_rx_frame.data[0], can_rx_frame.data[1], can_rx_frame.data[2], can_rx_frame.data[3], can_rx_frame.data[4]);
			can_Message_Process_GTron_Message_Data();
		break;
		default: break;
	}
	return;
}