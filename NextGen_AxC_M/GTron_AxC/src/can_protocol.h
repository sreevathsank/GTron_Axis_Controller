/* 
 * File:   can_protocol.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 2:53 PM
 */

#ifndef CAN_PROTOCOL_H
#define	CAN_PROTOCOL_H

#include "third_party/rtos/FreeRTOS/Source/include/FreeRTOS.h"
#include "third_party/rtos/FreeRTOS/Source/include/queue.h"
#include "definitions.h"


#ifdef	__cplusplus
extern "C" {
#endif

// Standard identifier id[28:18].
#define WRITE_ID(id) (id << 18)
#define READ_ID(id)  (id >> 18)
    
typedef union {
   unsigned char data[8];
   int64_t data_64bit;
}Can_Data_t;

/** 
 * Enums for GTron CAN Message Structure.
 **/
typedef enum
{
	TOP_SYSCTRL_BOARD_ID    = 0,
	TOP_AXC_BOARD_ID        = 1,
	BOT_SYSCTRL_BOARD_ID    = 2,
	BOT_AXC_BOARD_ID        = 3,
	IOCTRL_BOARD_ID         = 4,
	FRONT_PANEL_BOARD_ID    = 5,
	NO_OF_BOARD_ID
}Board_Id_t;

typedef enum
{
	AxC_DEFAULT					= 0,
	REELER_MOTOR_1				= 1,
	GUIDE_MOTOR					= 2,
	VERITCAL_ARRESTOR_MOTOR1	= 3,
	GUIDE_OPEN_LIMIT			= 4,
	GUIDE_CLOSE_LIMIT			= 5,
	VERITCAL_ARRESTOR_MOTOR2	= 6,
	REELER_ADJ_MOTOR1			= 7,
	REELER_ADJ_MOTOR2			= 8,
	SOLENOIDS					= 9,
	HYBRID_TRIGGER_INSPECTION	= 10,
	C_SENSOR					= 11,
	GLOBAL_COUNTER				= 12,
	FRONT_CAMERA_MOTOR			= 13,
	REELER_MOTOR_2				= 14,
	NO_OF_AXC_PERIPHERALS
}AxC_Peripherals_t;

typedef enum
{
	AXC_INITIALIZE			= 0,
	AXC_START				= 1,
	AXC_STOP				= 2,
	AXC_ENABLE				= 3,
	AXC_DISABLE				= 4,
	AXC_VELOCITY			= 5,
	AXC_ROTATE				= 6,
	AXC_MOVE_TO				= 7,
	AXC_MOVE_BY				= 8,
	AXC_MOVE_TO_OPEN_LIMIT	= 9,
	AXC_MOVE_TO_CLOSE_LIMIT	= 10,
	AXC_MOVE_DONE			= 11,
	AXC_TEETH				= 12,
	AXC_INITIAL_POSITION	= 13,
	AXC_PRESSED				= 14,
	AXC_NOT_PRESSED			= 15,
	AXC_STATUS_CHECK		= 16,
	AXC_HOMING				= 17,
	AXC_CURRENT_POSITION	= 18,
	AXC_TOLERABLE_SLIPS		= 19,
	AXC_SKIP_TRIGGER		= 20,
	AXC_PAUSE				= 21,
	AXC_N_SHOT				= 22,
	AXC_SET					= 23,
	AXC_GET					= 24,
	AXC_TERMINAL_WIDTH		= 25,
	AXC_ENCODER_MODE		= 26,
	AXC_EJECT				= 27,
	NO_OF_AXC_OPERAITONS
}AxC_Operations_t;

typedef enum {
	AXC_ERR_NONE			= 0,
	AXC_ERR_SLIP			= 1,
	AXC_ERR_TRIGGER_FAIL	= 2,
	NO_OF_AXC_ERR
}AxC_Errors_t;

/** 
 * GTron AxC Message IDs.
 **/
#define CAN_IO_TO_TOP_AXC_ID					0x106
#define CAN_IO_TO_BOT_AXC_ID					0x107

#define CAN_TOP_RACK_ID							0x108
#define CAN_BOT_RACK_ID							0x109

#define CAN_REPLY_TOP_RACK_ID					0x10A
#define CAN_REPLY_BOT_RACK_ID					0x10B

#define CAN_TOP_SAG_REELER_ID					0x10C
#define CAN_BOT_SAG_REELER_ID					0x10D

#define CAN_BOARD_ACTIVE_PING_ID				0x10E
#define CAN_REPLY_BOARD_ACTIVE_PING_ID			0x10F	

#define CAN_ERR_REPLY_TOP_RACK_ID				0x402

#define CAN_TOP_AXC_TO_SYSCTRL_ID				0x110


typedef enum { CAN_FROM_BUS, CAN_TO_BUS } Can_Direction_t;

typedef struct {
    uint32_t        can_id;     // 29-bit CAN ID.
    Can_Direction_t direction;  // FROM_BUS -> received from CAN ISR | TO_BUS -> To be sent.
    uint8_t         dlc;        // Data Length Code (0 - 8 bytes).
    Can_Data_t      payload;    // CAN Data as an array and 64-bit integer.
}Can_Frame_t;

#define Q_CAN_WORK_LEN  16
extern QueueHandle_t gq_can_work;      // Statically allocated queue.

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_PROTOCOL_H */

