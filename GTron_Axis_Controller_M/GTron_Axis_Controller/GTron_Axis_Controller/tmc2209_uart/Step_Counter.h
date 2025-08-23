/*
 * Step_Counter.h
 *
 * Created: 14-08-2025 15:43:29
 *  Author: sreevathsank
 */ 


#ifndef STEP_COUNTER_H_
#define STEP_COUNTER_H_

#include "All_Headers.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

#define READSYNC					0x04		
#define SYNCBUSY_COUNT_bit			4

typedef enum
{
	COUNT_UP	= 0,
	COUNT_DOWN	= 1	
}Count_Dir_t;

#define MSCNT_MAX				1024			// TMC2209_MSCNT register's range is 0 to 1023.
#define MSCNT_WRAP_THRESHOLD	(MSCNT_MAX / 2)	// Half of MSCNT_MAX (512) for wraparound detection.


// Convert microsteps/second to rotation/second.
float us_per_sec_to_rps(int32_t microsteps);

// Convert rotation/second to microsteps/second.
int32_t rps_to_us_per_sec(float rps);

void index_Interrupt_Callback( void );

uint16_t read_TMC2209_mscnt(uint16_t icID);

void update_TMC2209_Step_Tracking(Motor_Info_t *motor_info);

void check_tmc2209_move_done(Motor_Info_t *motor_info);

void tmc2209_set_velocity(uint16_t icID, Motor_Info_t *motor_info, int32_t velocity);


#endif /* STEP_COUNTER_H_ */