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

#define POSITION_MOVE_FLAG		0
#define VELOCITY_MOVE_FLAG		1

typedef enum
{
	GUIDE = 1,
	VARRESTOR = 2	
}Guide_or_VArrestor_t;

typedef enum
{
	TOP_RACK	= 0,
	BOT_RACK	= 1,
	MOTOR_ID	= 2,
	ENCODER		= 3,
	LIMIT		= 4
}Rack_Enum_t;

typedef struct
{
	uint32_t id;
	uint8_t data[8];	
	int32_t value;
}Can_Cmd_Info_t;

typedef struct
{
	int32_t velocity_limit;
	int32_t current_position;
	int32_t initial_position;
	int32_t trigger_step_size;
	uint32_t flags;
}Reeler_Info_t;

extern Reeler_Info_t *p_reeler_info;

extern Can_Cmd_Info_t rx_can_cmd_info;

void parse_GTron_CAN_Msg_Data( void );

#endif /* GTRON_CAN_CMD_PARSER_H_ */