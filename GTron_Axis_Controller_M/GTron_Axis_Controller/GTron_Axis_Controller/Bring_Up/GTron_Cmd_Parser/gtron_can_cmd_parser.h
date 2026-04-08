/*
 * gtron_can_cmd_parser.h
 *
 * Created: 29-07-2025 18:51:18
 *  Author: sreevathsank
 */ 

#include "All_Headers.h"

#ifndef GTRON_CAN_CMD_PARSER_H_
#define GTRON_CAN_CMD_PARSER_H_

#define CAN_DATA_FIELD_LEN		8	// No. of bytes in the CAN Data Field.

#define PERIPHERAL_BYTE_IDX		0
#define OPERATION_BYTE_IDX		1

#define REELER_POS_MV_FLAG		0
#define REELER_VEL_MV_FLAG		1

/************************************************************************/
/* Guide Flag Bit Fields                                                */
/************************************************************************/
#define GUIDE_HOMING_FLAG		0
#define GUIDE_MOVE_FLAG			1

typedef enum
{
	GUIDE = 1,
	VARRESTOR = 2	
}Guide_or_VArrestor_t;

typedef enum
{
	TOP_RACK		= 0,
	BOT_RACK		= 1,
	MOTOR_ID		= 2,
	ENCODER			= 3,
	LIMIT			= 4,
	TOP_SAG_REELER	= 5,
	BOT_SAG_REELER	= 6,
	NO_OF_RACK_ITEMS
}Rack_Enum_t;

typedef struct
{
	uint32_t id;
	uint8_t data[8];	
	int32_t value;
}Can_Cmd_Info_t;

typedef enum {
	MOTOR_GUIDE		= 0,
	MOTOR_REELER	= 1,
	MOTOR_VARREST	= 2,
	NO_OF_MOTOR_NAME	
}Motor_Name_Enum_t;

typedef struct {
	Motor_Name_Enum_t motor_name;
	struct {
		int32_t target;
		int32_t current;
		uint32_t limit;
	}velocity;
	
	struct {
		int32_t target;
		int32_t current;
		int32_t right_open_limit;
		int32_t left_close_limit;	
		int32_t initial;
		uint32_t trig_step_size;
		uint32_t counter_value;
	}position;
	
	struct {
		int32_t total_steps;
		int32_t total_dist;
		uint16_t prev_mscnt;
	}step_tracker;
	
	struct {
		uint32_t homing					: 1;	// 0
		uint32_t move_to_open_lim		: 1;	// 1
		uint32_t move_to_close_lim		: 1;	// 2
		uint32_t move_given				: 1;	// 3
		uint32_t rotate_vel_mode		: 1;	// 4
		uint32_t sag_enabled			: 1;	// 5
		uint32_t vel_timer				: 1;	// 6
		uint32_t direction				: 1;	// 7
		uint32_t mscnt_first_reading	: 1;	// 8
		uint32_t sensor_trigger			: 1;	// 9
		uint32_t is_hybrid_trig_enabled : 1;	// 10
		uint32_t reserved				: 21;
	}flags;
}Motor_Info_t;

extern volatile Motor_Info_t *p_guide_info;

extern volatile Motor_Info_t *p_reeler_info;

extern Can_Cmd_Info_t rx_can_cmd_info;

/************************************************************************/
/* Velocity Variable Checking                                           */
/************************************************************************/
static inline bool is_Motor_At_TargetVelocity(const Motor_Info_t *motor)
{
	return ( motor->velocity.current == motor->velocity.target );
}

static inline bool is_Motor_Less_Than_Equal_TargetVelocity(const Motor_Info_t *motor)
{
	return ( motor->velocity.current <= motor->velocity.target );
}

static inline bool is_Motor_Greater_Than_Equal_TargetVelocity(const Motor_Info_t *motor)
{
	return ( motor->velocity.current >= motor->velocity.target );
}

void parse_GTron_CAN_Msg_Data( void );

#endif /* GTRON_CAN_CMD_PARSER_H_ */