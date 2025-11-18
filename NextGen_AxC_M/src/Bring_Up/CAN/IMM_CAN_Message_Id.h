/*
 * IMM_CAN_Message_Id.h
 *
 * Created: 18-01-2024 11:25:47
 *  Author: sreevathsank
 */ 

#ifndef IMM_CAN_MESSAGE_ID_H_
#define IMM_CAN_MESSAGE_ID_H_

#include <stdint.h>

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
 * \name Axis Node Numbers
 * 
 * \brief Address for all the nodes.
 * @{ */
#define X_ADDR			0x01	// X Axis.
#define Y_ADDR			0x02	// Y Axis.
#define Z_ADDR			0x03	// Z Axis.
#define RF_ADDR         0x04	// Rotary Fixture Axis. 
#define FP_ADDR			0x05	// Front Panel.
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
	AxC_DEFAULT = 0,
	REELER_MOTOR = 1,
	GUIDE_MOTOR = 2,
	VERITCAL_ARRESTOR_MOTOR = 3,
	GUIDE_OPEN_LIMIT = 4,
	GUIDE_CLOSE_LIMIT = 5,
	REELER_ENCODER = 6,
	GUIDE_ENCODER = 7,
	SAG_SENSOR = 8,
	NO_OF_AXC_PERIPHERALS
}AxC_Peripherals_t;

typedef enum
{
	AXC_INITIALIZE = 0,
	AXC_START = 1,
	AXC_STOP = 2,
	AXC_ENABLE = 3,
	AXC_DISABLE = 4,
	AXC_VELOCITY = 5,
	AXC_ROTATE = 6,
	AXC_MOVE_TO = 7,
	AXC_MOVE_BY = 8,
	AXC_MOVE_TO_OPEN_LIMIT = 9,
	AXC_MOVE_TO_CLOSE_LIMIT = 10,
	AXC_MOVE_DONE = 11,
	AXC_TEETH = 12,
	AXC_INITIAL_POSITION = 13,
	AXC_PRESSED = 14,
	AXC_NOT_PRESSED = 15,
	AXC_STATUS_CHECK = 16,
	AXC_HOMING = 17,
	NO_OF_AXC_OPERAITONS
}AxC_Operations_t;

/** 
 * GTron AxC Message IDs.
 **/
#define CAN_TOP_RACK_ID							0x108
#define CAN_BOT_RACK_ID							0x109

#define CAN_REPLY_TOP_RACK_ID					0x10A
#define CAN_REPLY_BOT_RACK_ID					0x10B

#define CAN_TOP_SAG_REELER_ID					0x10C
#define CAN_BOT_SAG_REELER_ID					0x10D

#define CAN_BOARD_ACTIVE_PING_ID				0x10E
#define CAN_REPLY_BOARD_ACTIVE_PING_ID			0x10F	

/** 
 * Knob Messages
 */
#define KNOB_MOVEMENT						0x15
#define KNOB_MODE							0x18
#define KNOB_AXIS_CHANGE					0x03

/** 
 * Stroke Length Messages.
 */
#define RFS_DIST							0xC4	//	DEC 196
#define START_RANGE							0xC5	//	DEC	197
#define END_RANGE							0xC6	//	DEC 198

						
/**
 * \name v3 Messages to v5 Implementation for X-axis (MCD json)
 *
 */
// The "typ" or the 3rd parameter in CAN_ID() is the sub-command.
// Eg: Move Position (MVP) is the Command (cmd) and Absolute or Move To is (typ = 0) and Relative or Move By is (typ = 1) is the sub-command.
//#define PING_X							CAN_ID(X, 138, 1, MOTOR)		// 0x2700200(or)40894976
//#if X_AXIS_TABLE
	#define MOVE_DONE_PING_X				CAN_ID(X_ADDR, 138, 0 ,0)
	#define PING_X							CAN_ID(X_ADDR, 138, 1, 0)
	#define REF_SEARCH_PING_X				CAN_ID(X_ADDR, RFS, 2, 0)
	#define MAX_ACCEL_X						CAN_ID(X_ADDR, SAP, 5, MOTOR)		// 0x20a0a00(or)34212352
	#define MAX_DECCEL_X					CAN_ID(X_ADDR, SAP, 17, MOTOR)		// 0x20a2e00(or)34221568
	#define HOME_SEARCH_VEL_X				CAN_ID(X_ADDR, SAP, 194, MOTOR)		// 0x20b2800(or)34285568
	#define HOME_SWITCH_VEL_X				CAN_ID(X_ADDR, SAP, 195, MOTOR)		// 0x20b2a00(or)34286080
	#define HOMING_MODE_X					CAN_ID(X_ADDR, SAP, 193, MOTOR)		// 0x20b2600(or)34285056
	#define OPEN_CLOSED_LOOP_X				CAN_ID(X_ADDR, SAP, 129, MOTOR)		// 0x20a5200(or)34230784
	#define CORRECTION_VEL_P_X				CAN_ID(X_ADDR, SAP, 115, MOTOR)		// 0x20a2a00(or)34220544
	#define CORRECTION_VEL_I_X				CAN_ID(X_ADDR, SAP, 116, MOTOR)		// 0x20a2c00(or)34221056
	#define CORRECTION_VEL_I_CLIP_X			CAN_ID(X_ADDR, SAP, 117, MOTOR)		// 0x20a2e00(or)34221568
	#define CORRECTION_VEL_DV_CLK_X			CAN_ID(X_ADDR, SAP, 118, MOTOR)		// 0x20a3000(or)34222080
	#define CORRECTION_VEL_DV_CLIP_X		CAN_ID(X_ADDR, SAP, 119, MOTOR)		// 0x20a3200(or)34222592
	#define CORRECTION_POSITION_P_X			CAN_ID(X_ADDR, SAP, 124, MOTOR)		// 0x20a4800(or)34228224
	#define MAX_CORRECTION_TOLERANCE_X		CAN_ID(X_ADDR, SAP, 125, MOTOR)		// 0x20a4a00(or)34228736
	#define POSITION_WINDOW_X				CAN_ID(X_ADDR, SAP, 134, MOTOR)		// 0x20a6800(or)34236416
	#define RAMP_TYPE_X						CAN_ID(X_ADDR, SAP, 14, MOTOR)		// 0x20a2800(or)34220032
	#define BOW_1_X							CAN_ID(X_ADDR, SAP, 22, MOTOR)		// 0x20a4400(or)34227200
	#define BOW_2_X							CAN_ID(X_ADDR, SAP, 23, MOTOR)		// 0x20a4600(or)34227712
	#define BOW_3_X							CAN_ID(X_ADDR, SAP, 24, MOTOR)		// 0x20a4800(or)34228224
	#define	BOW_4_X							CAN_ID(X_ADDR, SAP, 25, MOTOR)		// 0x20a4a00(or)34228736
	#define ENABLE_SOFT_LIMITS_X			CAN_ID(X_ADDR, SAP, 28, MOTOR)		// 0x20a5000(or)34230272
	#define SET_LEFT_SOFT_LIMIT_X			CAN_ID(X_ADDR, SAP, 26, MOTOR)		// 0x20a4c00(or)34229248
	#define SET_RIGHT_SOFT_LIMIT_X			CAN_ID(X_ADDR, SAP, 27, MOTOR)		// 0x20a4e00(or)34229760
	#define TARGET_POSITION_X				CAN_ID(X_ADDR, SAP, 0, MOTOR)		// 0x20a0000(or)34209792
	#define ACTUAL_POSITION_X				CAN_ID(X_ADDR, SAP, 1, MOTOR)		// 0x20a0200(or)34210304
	#define ROTARY_ENC_POSITION_X			CAN_ID(X_ADDR, SAP, 209, MOTOR)		// 0x20e1200(or)34476544
	#define RFS_START_X						CAN_ID(X_ADDR, RFS, 0, MOTOR)		// 0x20a2600(or)34219520
	#define RFS_STOP_X						CAN_ID(X_ADDR, RFS, 1, MOTOR)
	#define MAX_POSITION_SPEED_X			CAN_ID(X_ADDR, SAP, 4, MOTOR)		// 0x20a0800(or)34211840
	#define MOVE_TO_X						CAN_ID(X_ADDR, MVP, MVP_ABS, MOTOR)		// 0x2080000(or)34078720
	#define MOVE_BY_X						CAN_ID(X_ADDR, MVP, MVP_REL, MOTOR)		// 0x2080200(or)34079232
	#define STOP_MOTION_X					CAN_ID(X_ADDR, MST, 0 ,MOTOR)		// 0x2060000(or)33947648
	#define ROTARY_ENC_X					CAN_ID(X_ADDR, GAP, 209, MOTOR)		// 0x20c1200(or)34345472
	#define RT_LIM_SW_CHECK_X				CAN_ID(X_ADDR, GAP, 0x0A, MOTOR)
	#define LFT_LIM_SW_CHECK_X				CAN_ID(X_ADDR, GAP, 0x0B, MOTOR)
	#define CAN_KNOB_MOVEMENT_X				CAN_ID(X_ADDR, 0, 0, KNOB_MOVEMENT)
	#define CAN_KNOB_MODE_X					CAN_ID(X_ADDR, 0, 0, KNOB_MODE)
	#define CAN_KNOB_AXIS_CHANGE_X			CAN_ID(X_ADDR, 0, 0, KNOB_AXIS_CHANGE)
	#define WRITE_REGISTER_X				CAN_ID(X_ADDR, 0, 0, WR_MC)
	#define READ_REGISTER_X					CAN_ID(X_ADDR, 0, 0, RD_MC)
	#define CHECK_PARAMETER_X				CAN_ID(X_ADDR, CHK_FW_PARAM, 0, 0)
	#define WRITE_PARAMETER_X				CAN_ID(X_ADDR, WR_FW_PARAM, 0, 0)
	#define READ_PARAMETER_X				CAN_ID(X_ADDR, RD_FW_PARAM, 0, 0)
	#define RFS_DISTANCE_X					CAN_ID(X_ADDR, RFS_DIST, 0, 0)
	#define START_RANGE_X					CAN_ID(X_ADDR, START_RANGE, 0, 0)
	#define END_RANGE_X						CAN_ID(X_ADDR, END_RANGE, 0, 0)
//#endif
//#if Y_AXIS_TABLE
	#define MOVE_DONE_PING_Y				CAN_ID(Y_ADDR, 138, 0, 0)
	#define PING_Y							CAN_ID(Y_ADDR, 138, 1, 0)
	#define REF_SEARCH_PING_Y				CAN_ID(Y_ADDR, RFS, 2, 0)
	#define MAX_ACCEL_Y						CAN_ID(Y_ADDR, SAP, 5, MOTOR)		// 0x20a0a00(or)34212352
	#define MAX_DECCEL_Y					CAN_ID(Y_ADDR, SAP, 17, MOTOR)		// 0x20a2e00(or)34221568
	#define HOME_SEARCH_VEL_Y				CAN_ID(Y_ADDR, SAP, 194, MOTOR)		// 0x20b2800(or)34285568
	#define HOME_SWITCH_VEL_Y				CAN_ID(Y_ADDR, SAP, 195, MOTOR)		// 0x20b2a00(or)34286080
	#define HOMING_MODE_Y					CAN_ID(Y_ADDR, SAP, 193, MOTOR)		// 0x20b2600(or)34285056
	#define OPEN_CLOSED_LOOP_Y				CAN_ID(Y_ADDR, SAP, 129, MOTOR)		// 0x20a5200(or)34230784
	#define CORRECTION_VEL_P_Y				CAN_ID(Y_ADDR, SAP, 115, MOTOR)		// 0x20a2a00(or)34220544
	#define CORRECTION_VEL_I_Y				CAN_ID(Y_ADDR, SAP, 116, MOTOR)		// 0x20a2c00(or)34221056
	#define CORRECTION_VEL_I_CLIP_Y			CAN_ID(Y_ADDR, SAP, 117, MOTOR)		// 0x20a2e00(or)34221568
	#define CORRECTION_VEL_DV_CLK_Y			CAN_ID(Y_ADDR, SAP, 118, MOTOR)		// 0x20a3000(or)34222080
	#define CORRECTION_VEL_DV_CLIP_Y		CAN_ID(Y_ADDR, SAP, 119, MOTOR)		// 0x20a3200(or)34222592
	#define CORRECTION_POSITION_P_Y			CAN_ID(Y_ADDR, SAP, 124, MOTOR)		// 0x20a4800(or)34228224
	#define MAX_CORRECTION_TOLERANCE_Y		CAN_ID(Y_ADDR, SAP, 125, MOTOR)		// 0x20a4a00(or)34228736
	#define POSITION_WINDOW_Y				CAN_ID(Y_ADDR, SAP, 134, MOTOR)		// 0x20a6800(or)34236416
	#define RAMP_TYPE_Y						CAN_ID(Y_ADDR, SAP, 14, MOTOR)		// 0x20a2800(or)34220032
	#define BOW_1_Y							CAN_ID(Y_ADDR, SAP, 22, MOTOR)		// 0x20a4400(or)34227200
	#define BOW_2_Y							CAN_ID(Y_ADDR, SAP, 23, MOTOR)		// 0x20a4600(or)34227712
	#define BOW_3_Y							CAN_ID(Y_ADDR, SAP, 24, MOTOR)		// 0x20a4800(or)34228224
	#define	BOW_4_Y							CAN_ID(Y_ADDR, SAP, 25, MOTOR)		// 0x20a4a00(or)34228736
	#define ENABLE_SOFT_LIMITS_Y			CAN_ID(Y_ADDR, SAP, 28, MOTOR)		// 0x20a5000(or)34230272
	#define SET_LEFT_SOFT_LIMIT_Y			CAN_ID(Y_ADDR, SAP, 26, MOTOR)		// 0x20a4c00(or)34229248
	#define SET_RIGHT_SOFT_LIMIT_Y			CAN_ID(Y_ADDR, SAP, 27, MOTOR)		// 0x20a4e00(or)34229760
	#define TARGET_POSITION_Y				CAN_ID(Y_ADDR, SAP, 0, MOTOR)		// 0x20a0000(or)34209792
	#define ACTUAL_POSITION_Y				CAN_ID(Y_ADDR, SAP, 1, MOTOR)		// 0x20a0200(or)34210304
	#define ROTARY_ENC_POSITION_Y			CAN_ID(Y_ADDR, SAP, 209, MOTOR)		// 0x20e1200(or)34476544
	#define RFS_START_Y						CAN_ID(Y_ADDR, RFS, 0, MOTOR)		// 0x20a2600(or)34219520
	#define RFS_STOP_Y						CAN_ID(Y_ADDR, RFS, 1, MOTOR)
	#define MAX_POSITION_SPEED_Y			CAN_ID(Y_ADDR, SAP, 4, MOTOR)		// 0x20a0800(or)34211840
	#define MOVE_TO_Y						CAN_ID(Y_ADDR, MVP, MVP_ABS, MOTOR)		// 0x2080000(or)34078720
	#define MOVE_BY_Y						CAN_ID(Y_ADDR, MVP, MVP_REL, MOTOR)		// 0x2080200(or)34079232
	#define STOP_MOTION_Y					CAN_ID(Y_ADDR, MST, 0 ,MOTOR)		// 0x2060000(or)33947648
	#define ROTARY_ENC_Y					CAN_ID(Y_ADDR, GAP, 209, MOTOR)		// 0x20c1200(or)34345472
	#define RT_LIM_SW_CHECK_Y				CAN_ID(Y_ADDR, GAP, 0x0A, MOTOR)
	#define LFT_LIM_SW_CHECK_Y				CAN_ID(Y_ADDR, GAP, 0x0B, MOTOR)
	#define CAN_KNOB_MOVEMENT_Y				CAN_ID(Y_ADDR, 0, 0, KNOB_MOVEMENT)
	#define CAN_KNOB_MODE_Y					CAN_ID(Y_ADDR, 0, 0, KNOB_MODE)
	#define CAN_KNOB_AXIS_CHANGE_Y			CAN_ID(Y_ADDR, 0, 0, KNOB_AXIS_CHANGE)
	#define WRITE_REGISTER_Y				CAN_ID(Y_ADDR, 0, 0, WR_MC)
	#define READ_REGISTER_Y					CAN_ID(Y_ADDR, 0, 0, RD_MC)
	#define CHECK_PARAMETER_Y				CAN_ID(Y_ADDR, CHK_FW_PARAM, 0, 0)
	#define WRITE_PARAMETER_Y				CAN_ID(Y_ADDR, WR_FW_PARAM, 0, 0)
	#define READ_PARAMETER_Y				CAN_ID(Y_ADDR, RD_FW_PARAM, 0, 0)
	#define RFS_DISTANCE_Y					CAN_ID(Y_ADDR, RFS_DIST, 0, 0)
	#define START_RANGE_Y					CAN_ID(Y_ADDR, START_RANGE, 0, 0)
	#define END_RANGE_Y						CAN_ID(Y_ADDR, END_RANGE, 0, 0)
//#endif
//#if Z_AXIS_PROTO
	#define MOVE_DONE_PING_Z				CAN_ID(Z_ADDR, 138, 0, 0)
	#define PING_Z							CAN_ID(Z_ADDR, 138, 1, 0)
	#define REF_SEARCH_PING_Z				CAN_ID(Z_ADDR, RFS, 2, 0)
	#define MAX_ACCEL_Z						CAN_ID(Z_ADDR, SAP, 5, MOTOR)			// 0x20a0a00(or)34212352
	#define MAX_DECCEL_Z					CAN_ID(Z_ADDR, SAP, 17, MOTOR)			// 0x20a2e00(or)34221568
	#define HOME_SEARCH_VEL_Z				CAN_ID(Z_ADDR, SAP, 194, MOTOR)			// 0x20b2800(or)34285568
	#define HOME_SWITCH_VEL_Z				CAN_ID(Z_ADDR, SAP, 195, MOTOR)			// 0x20b2a00(or)34286080
	#define HOMING_MODE_Z					CAN_ID(Z_ADDR, SAP, 193, MOTOR)			// 0x20b2600(or)34285056
	#define OPEN_CLOSED_LOOP_Z				CAN_ID(Z_ADDR, SAP, 129, MOTOR)			// 0x20a5200(or)34230784
	#define CORRECTION_VEL_P_Z				CAN_ID(Z_ADDR, SAP, 115, MOTOR)			// 0x20a2a00(or)34220544
	#define CORRECTION_VEL_I_Z				CAN_ID(Z_ADDR, SAP, 116, MOTOR)			// 0x20a2c00(or)34221056
	#define CORRECTION_VEL_I_CLIP_Z			CAN_ID(Z_ADDR, SAP, 117, MOTOR)			// 0x20a2e00(or)34221568
	#define CORRECTION_VEL_DV_CLK_Z			CAN_ID(Z_ADDR, SAP, 118, MOTOR)			// 0x20a3000(or)34222080
	#define CORRECTION_VEL_DV_CLIP_Z		CAN_ID(Z_ADDR, SAP, 119, MOTOR)			// 0x20a3200(or)34222592
	#define CORRECTION_POSITION_P_Z			CAN_ID(Z_ADDR, SAP, 124, MOTOR)			// 0x20a4800(or)34228224
	#define MAX_CORRECTION_TOLERANCE_Z		CAN_ID(Z_ADDR, SAP, 125, MOTOR)			// 0x20a4a00(or)34228736
	#define POSITION_WINDOW_Z				CAN_ID(Z_ADDR, SAP, 134, MOTOR)			// 0x20a6800(or)34236416
	#define RAMP_TYPE_Z						CAN_ID(Z_ADDR, SAP, 14, MOTOR)			// 0x20a2800(or)34220032
	#define BOW_1_Z							CAN_ID(Z_ADDR, SAP, 22, MOTOR)			// 0x20a4400(or)34227200
	#define BOW_2_Z							CAN_ID(Z_ADDR, SAP, 23, MOTOR)			// 0x20a4600(or)34227712
	#define BOW_3_Z							CAN_ID(Z_ADDR, SAP, 24, MOTOR)			// 0x20a4800(or)34228224
	#define BOW_4_Z							CAN_ID(Z_ADDR, SAP, 25, MOTOR)			// 0x20a4a00(or)34228736
	#define ENABLE_SOFT_LIMITS_Z			CAN_ID(Z_ADDR, SAP, 28, MOTOR)			// 0x20a5000(or)34230272
	#define SET_LEFT_SOFT_LIMIT_Z			CAN_ID(Z_ADDR, SAP, 26, MOTOR)			// 0x20a4c00(or)34229248
	#define SET_RIGHT_SOFT_LIMIT_Z			CAN_ID(Z_ADDR, SAP, 27, MOTOR)			// 0x20a4e00(or)34229760
	#define TARGET_POSITION_Z				CAN_ID(Z_ADDR, SAP, 0, MOTOR)			// 0x20a0000(or)34209792
	#define ACTUAL_POSITION_Z				CAN_ID(Z_ADDR, SAP, 1, MOTOR)			// 0x20a0200(or)34210304
	#define ROTARY_ENC_POSITION_Z			CAN_ID(Z_ADDR, SAP, 209, MOTOR)			// 0x20e1200(or)34476544
	#define RFS_START_Z						CAN_ID(Z_ADDR, RFS, 0, MOTOR)			// 0x20a2600(or)34219520
	#define RFS_STOP_Z						CAN_ID(Z_ADDR, RFS, 1, MOTOR)
	#define MAX_POSITION_SPEED_Z			CAN_ID(Z_ADDR, SAP, 4, MOTOR)			// 0x20a0800(or)34211840
	#define MOVE_TO_Z						CAN_ID(Z_ADDR, MVP, MVP_ABS, MOTOR)			// 0x2080000(or)34078720
	#define MOVE_BY_Z						CAN_ID(Z_ADDR, MVP, MVP_REL, MOTOR)			// 0x2080200(or)34079232
	#define STOP_MOTION_Z					CAN_ID(Z_ADDR, MST, 0 ,MOTOR)			// 0x2060000(or)33947648
	#define ROTARY_ENC_Z					CAN_ID(Z_ADDR, GAP, 209, MOTOR)			// 0x20c1200(or)34345472
	#define AF_STARTPOINT_Z					CAN_ID(0, 0, 0, AF_STARTPOINT)
	#define AF_COMPARE_CNT_Z				CAN_ID(0, 0, 0, AF_COMPARE_CNT)
	#define LINEAR_ENC_CLEAR_Z				CAN_ID(Z_ADDR, LIN_ENC_CLEAR, 0, MOTOR)
	#define RT_LIM_SW_CHECK_Z				CAN_ID(Z_ADDR, GAP, 0x0A, MOTOR)
	#define LFT_LIM_SW_CHECK_Z				CAN_ID(Z_ADDR, GAP, 0x0B, MOTOR)
	#define CAN_KNOB_MOVEMENT_Z				CAN_ID(Z_ADDR, 0, 0, KNOB_MOVEMENT)
	#define CAN_KNOB_MODE_Z					CAN_ID(Z_ADDR, 0, 0, KNOB_MODE)
	#define CAN_KNOB_AXIS_CHANGE_Z			CAN_ID(Z_ADDR, 0, 0, KNOB_AXIS_CHANGE)
	#define WRITE_REGISTER_Z				CAN_ID(Z_ADDR, 0, 0, WR_MC)
	#define READ_REGISTER_Z					CAN_ID(Z_ADDR, 0, 0, RD_MC)
	#define CHECK_PARAMETER_Z				CAN_ID(Z_ADDR, CHK_FW_PARAM, 0, 0)
	#define WRITE_PARAMETER_Z				CAN_ID(Z_ADDR, WR_FW_PARAM, 0, 0)
	#define READ_PARAMETER_Z				CAN_ID(Z_ADDR, RD_FW_PARAM, 0, 0)
	#define RFS_DISTANCE_Z					CAN_ID(Z_ADDR, RFS_DIST, 0, 0)
	#define START_RANGE_Z					CAN_ID(Z_ADDR, START_RANGE, 0, 0)
	#define END_RANGE_Z						CAN_ID(Z_ADDR, END_RANGE, 0, 0)
//#endif


/** 
 * \name Linear Encoder Messages
 *
 */
#define LINEAR_ENC_ENABLE_X				CAN_ID(X_ADDR, LIN_ENC_ENABLE, 0, MOTOR)
#define LINEAR_ENC_DISABLE_X			CAN_ID(X_ADDR, LIN_ENC_DISABLE, 0, MOTOR)
#define LINEAR_ENC_CLEAR_X				CAN_ID(X_ADDR, LIN_ENC_CLEAR, 0, MOTOR)
#define	LINEAR_ENC_READ_X				CAN_ID(X_ADDR, LIN_ENC_READ, 0, MOTOR)

#define LINEAR_ENC_ENABLE_Y				CAN_ID(Y_ADDR, LIN_ENC_ENABLE, 0, MOTOR)
#define LINEAR_ENC_DISABLE_Y			CAN_ID(Y_ADDR, LIN_ENC_DISABLE, 0, MOTOR)
#define LINEAR_ENC_CLEAR_Y				CAN_ID(Y_ADDR, LIN_ENC_CLEAR, 0, MOTOR)
#define	LINEAR_ENC_READ_Y				CAN_ID(Y_ADDR, LIN_ENC_READ, 0, MOTOR)

#define LINEAR_ENC_ENABLE_Z				CAN_ID(Z_ADDR, LIN_ENC_ENABLE, 0, MOTOR)
#define LINEAR_ENC_DISABLE_Z			CAN_ID(Z_ADDR, LIN_ENC_DISABLE, 0, MOTOR)
#define LINEAR_ENC_CLEAR_Z				CAN_ID(Z_ADDR, LIN_ENC_CLEAR, 0, MOTOR)
#define	LINEAR_ENC_READ_Z				CAN_ID(Z_ADDR, LIN_ENC_READ, 0, MOTOR)

/** 
 * \name TMCL Direct Mode Messages 
 * @{ */
// Command No. for ROR (Rotate Right) is 1
#define ROR_X		CAN_ID(X_ADDR, ROR, 0, MOTOR)	// 0x2020000(or)33685504 - value of MOTOR macro is 0
#define ROR_Y		CAN_ID(Y_ADDR, ROR, 0, MOTOR)	// 0x4020000(or)67239936
#define ROR_Z		CAN_ID(Z_ADDR, ROR, 0, MOTOR)	// 0x6020000(or)100794368
#define ROR_RF		CAN_ID(RF_ADDR, ROR, 0. MOTOR)	// 0x8020000(or)134348800

// Command No. for ROL (Rotate Left) is 2
#define ROL_X		CAN_ID(X_ADDR, ROL, 0, MOTOR)	// 0x2040000(or)33816576
#define ROL_Y		CAN_ID(Y_ADDR, ROL, 0, MOTOR)	// 0x4040000(or)67371008
#define ROL_Z		CAN_ID(Z_ADDR, ROL, 0, MOTOR)	// 0x6040000(or)100925440
#define ROL_RF		CAN_ID(RF_ADDR, ROL, 0. MOTOR)	// 0x8040000(or)134479872
/** @} */

#endif /* IMM_CAN_MESSAGE_ID_H_ */