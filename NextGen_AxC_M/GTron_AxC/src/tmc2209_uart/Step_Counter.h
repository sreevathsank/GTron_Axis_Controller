/*
 * Step_Counter.h
 *
 * Created: 14-08-2025 15:43:29
 *  Author: sreevathsank
 */ 


#ifndef STEP_COUNTER_H_
#define STEP_COUNTER_H_

#include <stdint.h>

#include "task_state.h"
#include "tmc2209_uart/TMC2209.h"
#include "can_protocol.h"

#define READSYNC					0x04		
#define SYNCBUSY_COUNT_bit			4

/************************************************************************/
/* TMC2209 Motor based Macros                                           */
/************************************************************************/
#define TMC2209_F_CLK				12000000.0f									// Clock frequency (fCLK) of the TMC2209 internal oscillator in Hz.

#define VACTUAL_TO_HZ_FACTOR		0.7151185789f								// Factor to convert VACTUAL to microsteps/sec (Hz).
																				// Calculated as: fCLK / 2^24 = 12,000,000 / 16,777,216.

#define HZ_TO_VACTUAL_FACTOR		1.3981013333f								// Factor to convert microsteps/sec (Hz) to VACTUAL
																				// Calculated as: 2^24 / fCLK = 16,777,216 / 12,000,000

#define TMC2209_FULLSTEPS			200.00f										// No. of Full Steps in 1 full mechanical rotation (360 deg).

#define TMC2209_MICROSTEPS			256.00f										// No. of MicroSteps in 1 full mechanical rotation (360 deg).						

#define TMC2209_ROTATION			(TMC2209_FULLSTEPS * TMC2209_MICROSTEPS)	// No. of steps in one full rotation for the TMC2209 Motor Driver. 51200 MicroSteps.

#define TMC2209_ONE_MM_STEPS		(TMC2209_ROTATION / GUIDE_PITCH_MM)			// 17066.6667 steps per MM.

#define TMC2209_MOVE_MM(mm)			(TMC2209_ONE_MM_STEPS * mm)					// MM to TMC2209 motor steps conversion.

#define TMC2209_DEFAULT_SPEED		4000UL										// Default speed set for all movements of TMC2209 Motors including homing.

#define SINGLE_LIM_MAX_DISTANCE		TMC2209_MOVE_MM(45)							// Max Distance that a TMC2209 Single Limit Motor can traverse from the Single Limit.

#define MSCNT_MAX				1024											// TMC2209_MSCNT register's range is 0 to 1023.

#define MSCNT_WRAP_THRESHOLD	(MSCNT_MAX / 2)									// Half of MSCNT_MAX (512) for wraparound detection.


typedef enum {
	COUNT_UP	= 0,
	COUNT_DOWN	= 1	
} Count_Dir_t;

// Convert microsteps/second to rotation/second.
float us_per_sec_to_rps(int32_t microsteps);

// Convert rotation/second to microsteps/second.
int32_t rps_to_us_per_sec(float rps);

void index_Interrupt_Callback( void );

void diag_Interrupt_Callback( void );

uint16_t read_TMC2209_mscnt(uint16_t icID);

void check_Which_2209_Motor_Moving(void);

void update_TMC2209_Step_Tracking(Motor_Info_t *motor_info);

void tmc2209_set_velocity(uint16_t icID, Motor_Info_t *motor_info, int32_t velocity);


#endif /* STEP_COUNTER_H_ */