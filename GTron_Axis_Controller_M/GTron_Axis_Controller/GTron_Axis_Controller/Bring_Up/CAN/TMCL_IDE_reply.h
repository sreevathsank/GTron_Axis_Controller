/*
 * TMCL_IDE_reply.h
 *
 * Created: 31-01-2024 13:14:48
 *  Author: sreevathsank
 */ 


#ifndef TMCL_IDE_REPLY_H_
#define TMCL_IDE_REPLY_H_

//#include "Zen_can_api/zen_can_api.h"
//#include "Zen_can_api/zen_common.h"
#include "Global_Vars.h"
#include "All_Headers.h"
#include "Bring_Up/CAN/IMM_CAN_Message_Id.h"

/******************************** TMCL-IDE Handshake Messages (Hardcoded) ********************************/
#define ROR			0x01
#define ROL			0x02
#define MST			0x03
#define MVP			0x04
#define SAP			0x05
#define GAP			0x06
#define STAP		0x07
#define RSAP		0x08
#define SGP			0x09
#define GGP			0x0A
#define STGP		0x0B
#define RSGP		0x0C
#define RFS			0x0D
#define SIO			0x0E
#define GIO			0x0F
#define SCO			0x1E
#define GCO			0x1F
#define CCO			0x20
#define WR_MC		0x92
#define RD_MC		0x94

#define VERSION		0x88
#define VERSION_1	0x3100200
#define ASSIGNMENT	0x8F

//Reply ID for each node.
#define REPLY_ID_X	0x0B	// DEC 11
#define REPLY_ID_Y	0x0C	// DEC 12
#define REPLY_ID_Z	0x0D	// DEC 13

// For Get Axis Parameter instruction (GAP)
#define GAP_TORQUE_P			0x46
#define GAP_TORQUE_I			0x47

#define GAP_VELOCITY_P			0x4A
#define GAP_VELOCITY_I			0x4B
#define GAP_POSITION_P			0x4C
#define GAP_ACCELERATION		0x0B
#define GAP_EN_VELOCITY_RAMP	0x0C
#define GAP_MAX_CURRENT			0x06
#define GAP_MAX_SPEED			0x04

// For Move Position instruction (MVP)
#define MVP_ABS		0x00
#define MVP_REL		0x01
#define MVP_COORD	0x02

/******************************** Linear Encoder Commands/Instructions ********************************/
#define LIN_ENC_CLEAR		0xE0	// 224
#define LIN_ENC_READ		0xE1	// 225
#define LIN_ENC_ENABLE		0xE2	// 226
#define LIN_ENC_DISABLE		0xE3	// 227
#define LIN_ENC_SET			0xE4	// 228

/******************************** AutoFocus Commands/Instructions ********************************/
#define AF_STARTPOINT		0xE5	// 229
#define AF_COMPARE_CNT		0xE6	// 230

uint32_t message_Id;
int32_t data;

void zero_MessageID_Data();

void encoding_CAN_Byte_Data(int32_t value);

int32_t decoding_CAN_Byte_Data(void);

void encoding_GTron_CAN_Byte_Data(uint8_t peripheral_byte, uint8_t operation_byte, int32_t value);

int32_t decoding_GTon_CAN_Byte_Data( void );

void reply_Version(uint32_t message_Id, int32_t data);

void reply_GGP(uint32_t message_Id, int32_t data);

void reply_Assignment(uint32_t message_Id, int32_t data);

uint8_t can_Message_Calculate_Crc(uint32_t message_Id, int32_t data);

void reply_GAP(uint32_t message_Id, int32_t data);

void reply_GIO(uint32_t message_Id, int32_t data);

void reply_ROR(uint32_t message_Id, int32_t data);

void reply_ROL(uint32_t message_Id, int32_t data);

void reply_MST(uint32_t message_Id, int32_t data);

void reply_MVP(uint32_t message_Id, int32_t data);

void reply_WR_MC(uint32_t message_Id, int32_t data);

void reply_RD_MC(uint32_t message_Id, int32_t data);

void read_MC_common(int32_t address);

void write_MC_common(int32_t address, int32_t value);

#endif /* TMCL_IDE_REPLY_H_ */