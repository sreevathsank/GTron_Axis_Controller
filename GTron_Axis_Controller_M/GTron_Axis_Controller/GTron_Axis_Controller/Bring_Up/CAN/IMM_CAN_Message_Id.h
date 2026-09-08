/*
 * IMM_CAN_Message_Id.h
 *
 * Created: 18-01-2024 11:25:47
 *  Author: sreevathsank
 */ 

#ifndef IMM_CAN_MESSAGE_ID_H_
#define IMM_CAN_MESSAGE_ID_H_

/**
 * \name For CAN usage
 * @{ */
#define DATA_FRAME               	1               // Data Frame identifier macro
#define REMOTE_FRAME             	2               // Remote Frame identifier macro

#define EXT_ID                   	1               // Extended Id macro
#define STD_ID                   	0                // Standard ID macro
/** @} */


typedef struct mesg_struct
{
	int64_t  value:32;
	uint64_t  crc:8;
	
}can_msg_struct;

/** 
 * \name CAN frame for Transmit and Receive 
 *
 * \brief The union is used for storing data which is about 64-bit in length. Can be stored as a unsigned character array or as a 64-bit integer.
 * @{ */
typedef union can_union
{
	unsigned char data[8]; // Array for receive data from ASF4 can API
	int64_t data_64bit;    // Received 64 bit data
}can_union_type;

can_union_type can_tx_frame;
can_union_type can_rx_frame;
/** @} */

/** 
 * \name 29 bit CAN Message ID Identifier
 *
 * 
 * \brief The Message Structure is:
 * -# ad :	Address (4b)
 * -# cmd:	Command (8b)
 * -# typ:  Type	(8b)
 * -# mot:  Motor	(9b)
 * @{ */
#define CAN_ID(ad, cmd, typ, mot)	((ad << 25) | (cmd << 17) | (typ << 9) | (mot))
#define GET_AD(msg_id)              ( (msg_id >> 25) & 0x0F )   // Gets the Most Significant 4 bits from the Extended CAN Message ID.
#define GET_CMD(msg_id)             ( (msg_id >> 17) & 0xFF )
#define GET_TYP(msg_id)             ( (msg_id >> 9) & 0xFF )
#define GET_MOT(msg_id)             ( msg_id & 0x1FF )          // Get the Least Significant 9 bits from the Extended CAN Message ID.
/** @} */

#define AXIS_CAN_MSG_ID(axis, inst) \
						message_Id = CAN_ID(REPLY_ID_##axis, ##axis, 0x64, inst);
						
/** 
 * CAN Bootloader Code Dump Message IDs
 */
#define CAN_INIT							0x00
#define CAN_BIN_FILE_ERASE					0x01
#define CAN_BIN_FILE_WRITE					0x02

#define CAN_BOOT_X_ID						0x10
#define CAN_BOOT_Y_ID						0x11
#define CAN_BOOT_Z_ID						0x12
#define CAN_EXT_FLASH_ID					0x13

/** 
 * Firmware Parameters Read / Write Commands.
 */
#define CHK_FW_PARAM						0x80
#define WR_FW_PARAM							0x82
#define RD_FW_PARAM							0x84

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
	EJECTOR_1					= 15,
	EJECTOR_2					= 16,
	NO_OF_AXC_PERIPHERALS
}AxC_Peripherals_t;

typedef enum {
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
	AXC_TRIG_STEPSIZE		= 12,
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
	AXC_GC_GET				= 23,
	AXC_GC_SET				= 24,
	AXC_TERMINAL_WIDTH		= 25,
	AXC_ENCODER_MODE		= 26,
	AXC_EJECT_BIN_OFFSET	= 27,
	AXC_EJECT_PARTCOUNT		= 28,
	AXC_EJECT_PART			= 29,
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

#endif /* IMM_CAN_MESSAGE_ID_H_ */