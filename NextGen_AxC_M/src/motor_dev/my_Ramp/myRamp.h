/*
 * myRamp.h
 *
 * Created: 30-10-2023 17:24:54
 *  Author: sreevathsank
 */ 
#include <stdlib.h>
#include <math.h>
//#include <fastmath.h>
#include <float.h>
//#include <newlib-nano/newlib.h> //for double
//#include <atmel_start.h>
#include "TMC-API/tmc/ramp/LinearRamp1.h"
#include "TMC-API/tmc/helpers/Functions.h"
#include "All_Headers.h"
#include "Global_Vars.h"
//#include "Vars.h"

#ifndef MYRAMP_H_
#define MYRAMP_H_

#define NO_OF_PLOTS 1000

typedef struct
{
	uint32_t maxVelocity;
	int32_t targetPosition;
	int32_t rampPosition;
	int32_t targetVelocity;
	int32_t rampVelocity;
	int32_t acceleration;
	bool rampEnabled;
	int32_t accumulatorVelocity;
	int32_t accumulatorPosition;
	TMC_LinearRamp_Mode rampMode;
	TMC_LinearRamp_State state;
	int32_t accelerationSteps;
	uint32_t precision;
	uint32_t homingDistance;
	uint32_t stopVelocity;
} myRamp;



double_t custom_abs(double_t x);
void ramp();
void ramp_init(myRamp *structRamp);
void my_ramp_linear_set_enabled(myRamp *structRamp, bool enabled);
void my_ramp_linear_set_maxVelocity(myRamp *structRamp, uint32_t maxVelocity);
void set_TargetPosition(int32_t targetPosition);
void set_RampPosition(int32_t rampPosition);
void set_TargetVelocity(int32_t targetVelocity);
void set_RampVelocity(int32_t rampVelocity);
void my_ramp_linear_set_acceleration(myRamp *structRamp, int32_t acceleration);
void my_ramp_linear_set_mode(myRamp *structRamp, TMC_LinearRamp_Mode mode);
void my_ramp_linear_set_precision(myRamp * structRamp, uint32_t precision);
void my_ramp_linear_set_homingDistance(myRamp *structRamp, uint32_t homingDistance);
void my_ramp_linear_set_stopVelocity(myRamp *structRamp, uint32_t stopVelocity);
bool my_ramp_linear_get_enabled(myRamp *structRamp);
uint32_t my_ramp_linear_get_maxVelocity(myRamp *structRamp);
int32_t get_TargetPosition();
int32_t get_RampPosition();
int32_t get_ErrorPosition();
int32_t get_TargetVelocity();
int32_t get_RampVelocity();
int32_t my_ramp_linear_get_acceleration(myRamp *structRamp);
TMC_LinearRamp_State my_ramp_linear_get_state(myRamp *structRamp);
TMC_LinearRamp_Mode my_ramp_linear_get_mode(myRamp *structRamp);
uint32_t my_ramp_linear_get_precision(myRamp *structRamp);
uint32_t my_ramp_linear_get_acceleration_limit(myRamp *structRamp);
uint32_t my_ramp_linear_get_velocity_limit(myRamp *structRamp);
uint32_t my_ramp_linear_get_homingDistance(myRamp *structRamp);
uint32_t my_ramp_linear_get_stopVelocity(myRamp *structRamp);

void my_ramp_compute_Position(myRamp *structRamp);
int32_t my_ramp_compute_Velocity(myRamp *structRamp);
int32_t my_ramp_compute_Ramp(myRamp *structRamp);

void adjust_S_Velocity(void);

void call_all_ramp_params_functions(rampParams *r_Params);
void calculate_S_Ramp_Parameters(rampParams *r_Params);

#endif /* MYRAMP_H_ */