/*
 * IMM_CAN.h
 *
 * Created: 08-01-2024 11:16:52
 *  Author: sreevathsank
 */ 


#ifndef IMM_CAN_READ_H_
#define IMM_CAN_READ_H_

#include "Global_Vars.h"
#include "All_Headers.h"
#include "Bring_Up/CAN/IMM_CAN_Message_Id.h"
#include "Bring_Up/CAN/TMCL_IDE_reply.h"
#include "Bring_Up/CAN/IMM_CAN.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

#define SILENT					73
#define STD_ID					0
#define SENDER					1
#define RECEIVER				0

#define BOARD					RECEIVER

volatile int32_t value;

void can_Message_Read(void);

void can_Read(void);

void can_Message_Decode(uint32_t message_Id, int32_t data);

void can_Message_Operational_v3_XAxis(uint32_t message_Id, int32_t data);

void can_Message_Operational_v3_YAxis(uint32_t message_Id, int32_t data);

void can_Message_Operational_v3_ZAxis(uint32_t message_Id, int32_t data);

void can_Message_Process_GTron_Peripheral_Byte(axis_current curr_axis, uint32_t message_Id, int32_t data);

#endif /* IMM_CAN_READ_H_ */