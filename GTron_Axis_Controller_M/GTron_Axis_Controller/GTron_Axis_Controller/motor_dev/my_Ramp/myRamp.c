/*
 * myRamp.c
 *
 * Created: 30-10-2023 17:24:25
 *  Author: sreevathsank
 */ 
#include "motor_dev/my_Ramp/myRamp.h"
#include <math.h>

double_t mn = 0; // start point in seconds
double_t mx = 2; // total duration in seconds
double_t a1 = 7, a2 = 7; //accel and decel slope
double_t c1 = 0.2, c2 = 1.8; //half-point of slope
double_t z1, z2, z;
double_t temp; //temp var
double_t x[NO_OF_PLOTS], f[NO_OF_PLOTS]; // static allocation
int n = NO_OF_PLOTS;	//No. of point plot
int i;

double_t custom_abs(double_t x)
{
	if(x < 0) { return -x; }
	else { return x; }
}

void ramp(int32_t target_vel)
{
	for (i = 0; i < n; i++)
	{
		temp = (double_t)((mx - mn) / (n));
		f[i] = mn + temp * i;
		{
			z1 = 1/(1 + exp(-a1*(f[i]-c1)));						/* S-curve acceleration */
			z2 = 1/(1 + exp(-a2*(f[i]-c2)));						/* S-curve deceleration */
			z  = (custom_abs((z1) - z2) * target_vel) + 1;					/* absolute and *255 for scale up to PWM */
			
			printf("\ny %d = %ld\n", i, (int32_t)z);
			set_TargetVelocity(z);
			//tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_VELOCITY_TARGET, z);
			//tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_ACCELERATION, z);
		}
	}
}



void ramp_init(myRamp *structRamp)
{
	structRamp->maxVelocity         = velocity_limit;
	structRamp->targetPosition      = tmc4671_getTargetPosition(MOTOR);
	structRamp->targetVelocity      = tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT);
	structRamp->rampVelocity        = tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_ACTUAL);
	structRamp->rampPosition        = tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_ACTUAL);
	structRamp->acceleration        = 100;
	structRamp->accelerationSteps	= 1000;
	structRamp->rampEnabled         = true;
	structRamp->accumulatorVelocity = 0;
	structRamp->accumulatorPosition = 0;
	structRamp->rampMode            = TMC_RAMP_LINEAR_MODE_POSITION;
	structRamp->state               = TMC_RAMP_LINEAR_STATE_IDLE;
	structRamp->precision           = TMC_RAMP_LINEAR_DEFAULT_PRECISION;
	structRamp->homingDistance      = TMC_RAMP_LINEAR_DEFAULT_HOMING_DISTANCE;
	structRamp->stopVelocity        = TMC_RAMP_LINEAR_DEFAULT_STOP_VELOCITY;
}

void update_Ramp(myRamp *structRamp)
{
	structRamp->targetPosition      = tmc4671_getTargetPosition(MOTOR);
	structRamp->targetVelocity      = tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT);
	structRamp->rampVelocity        = tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_ACTUAL);
	structRamp->rampPosition        = tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_ACTUAL);
}

void my_ramp_linear_set_enabled(myRamp *structRamp, bool enabled)
{
	structRamp->rampEnabled = enabled;
}

void my_ramp_linear_set_maxVelocity(myRamp *structRamp, uint32_t maxVelocity)
{
	structRamp->maxVelocity = maxVelocity;
}

void set_TargetPosition(int32_t targetPosition)
{
	//tmc4671_writeInt(MOTOR, TMC4671_PID_POSITION_TARGET, targetPosition);\
	// If any of the limits are hit, dont move.
	//if( (gpio_get_pin_level(LIM_LFT) | gpio_get_pin_level(LIM_RT)) )
	{
		tmc4671_setAbsolutTargetPosition(MOTOR, targetPosition);	
	}
	return;
	//structRamp->targetPosition = targetPosition;
}

void set_RampPosition(int32_t rampPosition)
{
	//tmc4671_writeInt(MOTOR, TMC4671_PID_POSITION_ACTUAL, rampPosition);
	tmc4671_setActualPosition(MOTOR, rampPosition);
	//structRamp->rampPosition = rampPosition;
}

void set_TargetVelocity(int32_t targetVelocity)
{
	//tmc4671_writeInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT, targetVelocity);
	tmc4671_setVelocityLimit(MOTOR, targetVelocity);
	//structRamp->targetVelocity = targetVelocity;
}

void set_RampVelocity(int32_t rampVelocity)
{
	//tmc4671_writeInt(MOTOR, TMC4671_PID_VELOCITY_LIMIT, rampVelocity);
	tmc4671_setVelocityLimit(MOTOR, rampVelocity);
	//structRamp->rampVelocity = rampVelocity;
}

void my_ramp_linear_set_acceleration(myRamp *structRamp, int32_t acceleration)
{
	structRamp->acceleration = acceleration;
}

void my_ramp_linear_set_mode(myRamp *structRamp, TMC_LinearRamp_Mode mode)
{
	structRamp->rampMode = mode;
}

void my_ramp_linear_set_precision(myRamp * structRamp, uint32_t precision)
{
	structRamp->precision = precision;
}

void my_ramp_linear_set_homingDistance(myRamp *structRamp, uint32_t homingDistance)
{
	structRamp->homingDistance = homingDistance;
}

void my_ramp_linear_set_stopVelocity(myRamp *structRamp, uint32_t stopVelocity)
{
	structRamp->stopVelocity = stopVelocity;
}

bool my_ramp_linear_get_enabled(myRamp *structRamp)
{
	return structRamp->rampEnabled;
}

uint32_t my_ramp_linear_get_maxVelocity(myRamp *structRamp)
{
	return structRamp->maxVelocity;
}

int32_t get_TargetPosition()
{
	
	return tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_TARGET);
}

int32_t get_RampPosition()
{
	return tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_ACTUAL);
}

int32_t get_ErrorPosition()
{
	return tmc4671_readInt(MOTOR,TMC4671_PID_ERROR_DATA);
}

int32_t get_TargetVelocity()
{
	return tmc4671_readInt(MOTOR,TMC4671_PID_VELOCITY_LIMIT);
}

int32_t get_RampVelocity()
{
	return tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_ACTUAL);
}

int32_t my_ramp_linear_get_acceleration(myRamp *structRamp)
{
	return structRamp->acceleration;
}

TMC_LinearRamp_State my_ramp_linear_get_state(myRamp *structRamp)
{
	return structRamp->state;
}

TMC_LinearRamp_Mode my_ramp_linear_get_mode(myRamp *structRamp)
{
	return structRamp->rampMode;
}

uint32_t my_ramp_linear_get_precision(myRamp *structRamp)
{
	return structRamp->precision;
}

// The maximum acceleration depends on the precision value
uint32_t my_ramp_linear_get_acceleration_limit(myRamp *structRamp)
{
	return (0xFFFFFFFFu / structRamp->precision) * structRamp->precision;
}

uint32_t my_ramp_linear_get_velocity_limit(myRamp *structRamp)
{
	return structRamp->precision;
}

uint32_t my_ramp_linear_get_homingDistance(myRamp *structRamp)
{
	return structRamp->homingDistance;
}

uint32_t my_ramp_linear_get_stopVelocity(myRamp *structRamp)
{
	return structRamp->stopVelocity;
}

void my_ramp_compute_Position(myRamp *structRamp)
{
	if (!structRamp->rampEnabled)
	{
		return;
	}

	if (structRamp->rampMode != TMC_RAMP_LINEAR_MODE_POSITION)
	{
		return;
	}

	// Calculate steps needed to target
	int32_t diffx = 0, val = 0;

	switch(structRamp->state) 
	{
		case TMC_RAMP_LINEAR_STATE_IDLE:
			printf("\ninside idle\n");
			if(get_RampVelocity() == 0)
			{
				printf("\nrV == 0?\n");
				structRamp->accelerationSteps = 0;
			}

			if(get_RampPosition() == get_TargetPosition())
			{
				printf("\nrV = tV\n");
				break;
			}

			structRamp->state = TMC_RAMP_LINEAR_STATE_DRIVING;
			printf("\nstate = driving\n");
			break;
		case TMC_RAMP_LINEAR_STATE_DRIVING:
			printf("\ninside driving\n");
			printf("\nrVel = %ld\ttVel = %ld\trPos = %ld\ttPos = %ld\n", tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_ACTUAL), tmc4671_readInt(MOTOR, TMC4671_PID_VELOCITY_TARGET), tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_ACTUAL), tmc4671_readInt(MOTOR, TMC4671_PID_POSITION_ACTUAL));
			// Calculate distance to target (positive = driving towards target)
			if(get_RampVelocity() > 0)
			{
				printf("\nrV>0?\n");
				diffx = get_TargetPosition() - get_RampPosition();
			}
			
			else if(get_RampVelocity() < 0)
			{
				printf("\nrV<0?\n");
				diffx = -(get_TargetPosition() - get_RampPosition());
			}
			
			else
			{
				diffx = abs(get_TargetPosition() - get_RampPosition());
				printf("\ndiffx abs = %ld\n", diffx);
			}

			// Steps left required for braking?
			// (+ 1 to compensate rounding (flooring) errors of the position accumulator)
			if(structRamp->accelerationSteps + 1 >= diffx)
			{
				printf("\naccelSteps = %ld\n", structRamp->accelerationSteps);
				set_TargetVelocity(0);
				structRamp->state = TMC_RAMP_LINEAR_STATE_BRAKING;
			}
			
			else
			{	// Driving - apply VMAX (this also allows mid-ramp VMAX changes)
				printf("\nVMAX\n");
				val = (get_TargetPosition() > get_RampPosition()) ? structRamp->maxVelocity : -structRamp->maxVelocity;
				set_TargetVelocity(val);
				val = 0; 
			}
			break;
		case TMC_RAMP_LINEAR_STATE_BRAKING:
			if(get_TargetPosition() == get_RampPosition())
			{
				if(abs(get_RampVelocity()) <= structRamp->stopVelocity)
				{	// Position reached, velocity within cutoff threshold (or zero)
					set_RampVelocity(0);
					get_TargetVelocity(0);
					structRamp->state = TMC_RAMP_LINEAR_STATE_IDLE;
				}
				
				else
				{
					// We're still too fast, we're going to miss the target position
					// Let the deceleration continue until velocity is zero, then either
					// home when within homing distance or start a new ramp (RAMP_DRIVING)
					// towards the target.
				}
			}
			
			else
			{	// We're not at the target position
				if(get_RampVelocity() != 0)
				{	// Still decelerating

					// Calculate distance to target (positive = driving towards target)
					if(get_RampVelocity() > 0)
					{
						diffx = get_TargetPosition() - get_RampPosition();
					}
					
					else if(get_RampVelocity() < 0)
					{
						diffx = -(get_TargetPosition() - get_RampPosition());
					}
					
					else
					{	
						diffx = abs(get_TargetPosition() - get_RampPosition());
					}
					// Enough space to accelerate again?
					// (+ 1 to compensate rounding (flooring) errors of the position accumulator)
					if(structRamp->accelerationSteps + 1 < diffx)
					{
						structRamp->state = TMC_RAMP_LINEAR_STATE_DRIVING;
					}
				}
				
				else
				{	// Standing still (not at the target position)
					if(abs(get_TargetPosition() - get_RampPosition()) <= structRamp->homingDistance)
					{	// Within homing distance - drive with stop velocity
						val = (get_TargetPosition() > get_RampPosition()) ? structRamp->stopVelocity : -(structRamp->stopVelocity);
						get_TargetVelocity(val);
					}
					else
					{	// Not within homing distance - start a new motion by switching to RAMP_IDLE
						// Since (targetPosition != actualPosition) a new ramp will be started.
						structRamp->state = TMC_RAMP_LINEAR_STATE_IDLE;
					}
				}
			}
		break;
	}
}

int32_t my_ramp_compute_Velocity(myRamp *structRamp)
{
	int32_t val = 0;
	printf("\nInsideCOmputeVel\n");
	bool accelerating = get_RampVelocity() != get_TargetVelocity();

	if (structRamp->rampEnabled)
	{
		// Add current acceleration to accumulator
		structRamp->accumulatorVelocity += structRamp->acceleration;
	
		// Calculate the velocity delta value and keep the remainder of the velocity accumulator
		int32_t dv = structRamp->accumulatorVelocity / structRamp->precision;
		printf("\nacVel = %ld\tdV = %ld\n", structRamp->accumulatorVelocity, dv);
		structRamp->accumulatorVelocity = structRamp->accumulatorVelocity % structRamp->precision;

		// Add dv to rampVelocity, and regulate to target velocity
		if(get_RampVelocity() < get_TargetVelocity())
		{
			printf("\nrVel < tVel\n");
			set_RampVelocity(MIN(get_RampVelocity() + dv, get_TargetVelocity()));
		}
		
		else if(get_RampVelocity() > get_TargetVelocity())
		{
			printf("\nrVel > tVel\n");
			set_RampVelocity(MAX(get_RampVelocity() - dv, get_TargetVelocity()));
		}
	}
	else
	{
		// use target velocity directly
		set_RampVelocity(get_TargetVelocity());
		//printf("\nUse tVel Directly, rVel = %d\tacVel\n", get_RampVelocity(), structRamp->accumulatorVelocity);
		// Reset accumulator
		structRamp->accumulatorVelocity = 0;
	}

	// Calculate the velocity delta value and keep the remainder of the position accumulator
	structRamp->accumulatorPosition += get_RampVelocity();
	printf("\nacPos = %ld\tprecison = %ld\n", structRamp->accumulatorPosition, (int32_t) structRamp->precision);
	int32_t dx = structRamp->accumulatorPosition / (int32_t) structRamp->precision;
	structRamp->accumulatorPosition = structRamp->accumulatorPosition % (int32_t) structRamp->precision;
	printf("\ndx = %ld\n", dx);
	if(dx == 0)
	{
		printf("\nreturn dx\n");
		return dx;
	}

	// Change actual position determined by position change
	val += (dx < 0) ? (-1) : (1);
	printf("\ndx cmp, val = %ld\n", val);
	set_RampVelocity(val * 10);

	// Count acceleration steps needed for decelerating later
	structRamp->accelerationSteps += (abs(get_RampVelocity()) < abs(get_TargetVelocity())) ? accelerating : -accelerating;
	printf("\naccSteps = %ld\n", structRamp->accelerationSteps);
	if (structRamp->accelerationSteps < 0)
	{
		structRamp->accelerationSteps = 0;
	}

	return dx;	
}


int32_t my_ramp_compute_Ramp(myRamp *structRamp)
{
	my_ramp_compute_Position(structRamp);
	return my_ramp_compute_Velocity(structRamp);
}

/************************************************************************/
/* Functions to calculate all ramp parameters                           */
/************************************************************************/

void conversion_of_values(rampParams *r_Params)
{
	double temp_vel, temp_accel, temp_jerk;
	
	temp_vel					= (r_Params->target_Velocity / MINUTES) * ROTATION;
	temp_accel					= (r_Params->accelerations / MINUTES) * ROTATION;
	temp_jerk					= (r_Params->jerk / MINUTES) * ROTATION;
	r_Params->target_Velocity	= temp_vel;
	r_Params->accelerations		= temp_accel;
	r_Params->jerk				= temp_jerk;
}

void calculate_accel_decel_distance(rampParams *r_Params)
{
	r_Params->distance_accel = (r_Params->target_Velocity * r_Params->target_Velocity) / (2 * r_Params->accelerations);
}

void calculate_accel_decel_time(rampParams *r_Params)
{
	r_Params->time_accel = r_Params->target_Velocity / r_Params->accelerations;
}

void calculate_cruise_distance(rampParams *r_Params)
{
	r_Params->distance_cruise = abs((r_Params->target_Position - r_Params->initial_Position) - (2 * r_Params->distance_accel));
}

void calculate_cruise_time(rampParams *r_Params)
{
	r_Params->time_cruise = r_Params->distance_cruise / r_Params->target_Velocity;
}

void calculate_total_time_and_distance(rampParams *r_Params)
{
	r_Params->distance_start_point	= r_Params->initial_Position;
	r_Params->time_total			= (2 * r_Params->time_accel) + r_Params->time_cruise;
	r_Params->distance_total		= abs(r_Params->target_Position - r_Params->initial_Position);
}

int32_t accel_time_end = 0, decel_time_start = 0, ramp_time_end = 0;

/** 
 * \brief Calculates the Ramp Parameters required for the Linear Ramp Generation. This function should be called only after:
 * -# Setting Velocity Limit to 0.
 * -# Setting Target Position.
 * -# Enabling the Timer Interrupt.
 * -# https://www.pmdcorp.com/resources/type/articles/get/mathematics-of-motion-control-profiles-article
 *
 * @param void
 * @return void
 */
void call_all_ramp_params_functions(rampParams *r_Params)
{
	r_Params->target_Velocity	= velocity_limit;
	r_Params->target_Position	= tmc4671_getTargetPosition(MOTOR);
	r_Params->initial_Position	= tmc4671_getActualPosition(MOTOR);
	r_Params->accelerations		= axis_params.acceleration;
	
	conversion_of_values(r_Params);						
	calculate_accel_decel_distance(r_Params);
	//calculate_accel_decel_time(r_Params);
	calculate_cruise_distance(r_Params);
	//calculate_cruise_time(r_Params);
	calculate_total_time_and_distance(r_Params);
	
	// If accel point is greater than decel point, a triangular ramp will be generated. Set the triangular_ramp flag.
	if(abs(r_Params->distance_accel) > abs(r_Params->distance_decel_point))
	{
		r_Params->triangular_ramp = true;
		
		// Set the deceleration point to be half of the total steps to reach target position.
		r_Params->distance_accel = r_Params->distance_total / 2;
		r_Params->distance_decel_point = r_Params->distance_accel;
	}
	else { r_Params->triangular_ramp = false; }
	
	// On the fly velocity change.
	if(rParams.on_the_fly_change)
	{
		
	}
	
	// Variables to be used for time based ramp instead of position based ramp. (Highly inaccurate)
	r_Params-> decel_start = (int32_t)(r_Params->time_accel * 10) + (int32_t)(r_Params->time_cruise * 10);
	r_Params-> accel_end = (int32_t)(r_Params->time_accel * 10);
	r_Params-> ramp_end = (int32_t)(r_Params->time_total * 10);
	
	return;
}

/** 
 * \brief Returns the cube of the value passed to it.
 *
 * @Param[in] value Value to be cubed.
 * @return Cubed Value.
 */
double cube_Value(double value) { return (double)(value * value * value); }

/** 
 * \brief Returns the square of the value passed to it.
 *
 * @Param[in] value Value to be squared.
 * @return Squared Value.
 */
double sq_Value(double value)	{ return (double)(value * value); }
	
/** 
 * \brief Adjusts the value of velocity for S Ramp according to the distance.
 *
 */	
void adjust_S_Velocity(void)
{	
	rParams.target_Velocity = velocity_limit;
	return;	
}
	
void find_S_Ramp_Case(rampParams *r_Params)
{
	r_Params->s_Va = ( sq_Value(r_Params->accelerations) / r_Params->jerk );
	r_Params->s_Sa = ( 2 * cube_Value(r_Params->accelerations) / sq_Value(r_Params->jerk) );

	double prod_V_J = (r_Params->target_Velocity * r_Params->jerk);

	PRINTF_DEBUG && printf("\nVmax * Jerk = %.2f | accleration^2 = %.2f\n", prod_V_J, sq_Value(r_Params->accelerations));
	
	//Check if its case 1 or 2.
	if(prod_V_J < sq_Value(r_Params->accelerations))
	{
		r_Params->case_x = case_1;
		r_Params->s_Sv = 2 * r_Params->target_Velocity * ( sqrt(r_Params->target_Velocity / r_Params->jerk) );
	}
	else if(prod_V_J >= sq_Value(r_Params->accelerations))
	{
		r_Params->case_x = case_2;
		r_Params->s_Sv = r_Params->target_Velocity * ( (r_Params->target_Velocity / r_Params->accelerations) + (r_Params->accelerations / r_Params->jerk) );
	}

	// Check for Case A, B, C, D.
	if( (r_Params->target_Velocity < r_Params->s_Va) & (r_Params->distance_total > r_Params->s_Sa) )
	{
		r_Params->ramp_case = A;
	}
	else if( (r_Params->target_Velocity > r_Params->s_Va) & (r_Params->distance_total < r_Params->s_Sa) )
	{
		r_Params->ramp_case = B;
	}
	else if( (r_Params->target_Velocity < r_Params->s_Va) & (r_Params->distance_total < r_Params->s_Sa) )
	{
		if( r_Params->distance_total > r_Params->s_Sv) { r_Params->ramp_case = C1; }
		else if( r_Params->distance_total < r_Params->s_Sv) { r_Params->ramp_case = C2; }
	}
	else if( (r_Params->target_Velocity > r_Params->s_Va) & (r_Params->distance_total > r_Params->s_Sa) )
	{
		if( r_Params->distance_total > r_Params->s_Sv) { r_Params->ramp_case = D1; }
		else if( r_Params->distance_total < r_Params->s_Sv) { r_Params->ramp_case = D2; }
	}
	//r_Params->ramp_case = A;
	r_Params->s_S_min = ( (cube_Value(r_Params->accelerations) / sq_Value(r_Params->jerk)) );
	(r_Params->distance_total > r_Params->s_S_min) ? (PRINTF_DEBUG && printf("\nS > S_min\n")) : (PRINTF_DEBUG && printf("\nS < S_min\n"));
	(r_Params->distance_total == r_Params->s_S_min) ? (PRINTF_DEBUG && printf("\nS = S_min\n")) : (0);
	PRINTF_DEBUG && printf("\nCase %d\nVa = %.2f | Sa = %.2f | Sv = %.2f | S_min = %.2f", (r_Params->case_x + 1), r_Params->s_Va, r_Params->s_Sa, r_Params->s_Sv, r_Params->s_S_min);
	return;
}

void calculate_S_Time(rampParams *r_Params)
{
	switch(r_Params->ramp_case)
	{
		case A:  PRINTF_DEBUG && printf("\nCase A\n");  break;
		case B:  PRINTF_DEBUG && printf("\nCase B\n");  break;
		case C1: PRINTF_DEBUG && printf("\nCase C1\n"); break;
		case C2: PRINTF_DEBUG && printf("\nCase C2\n"); break;
		case D1: PRINTF_DEBUG && printf("\nCase D1\n"); break;
		case D2: PRINTF_DEBUG && printf("\nCase D2\n"); break;
		default: break;
	}
	switch(r_Params->ramp_case)
	{
		case A:
		case C1:
			r_Params->s_t_j = sqrt(r_Params->target_Velocity / r_Params->jerk);
			r_Params->s_t_a = r_Params->s_t_j;
			r_Params->s_t_v = (r_Params->distance_total / r_Params->target_Velocity);
		break;
		case B:
		case C2:
			r_Params->s_t_j = cbrt(r_Params->distance_total / (2 * r_Params->jerk));
			r_Params->s_t_a = r_Params->s_t_j;
			r_Params->s_t_v = 2 * r_Params->s_t_j;
		break;
		case D1:
			r_Params->s_t_j = (r_Params->accelerations / r_Params->jerk);
			r_Params->s_t_a = (r_Params->target_Velocity / r_Params->accelerations);
			r_Params->s_t_v = (r_Params->distance_total / r_Params->target_Velocity);
		break;
		case D2:
			r_Params->s_t_j = (r_Params->accelerations / r_Params->jerk);
			r_Params->s_t_a = 0.5 * ( sqrt( ( (4 * r_Params->distance_total * sq_Value(r_Params->jerk)) + cube_Value(r_Params->accelerations) ) / (r_Params->accelerations * sq_Value(r_Params->jerk)) ) - (r_Params->accelerations / r_Params->jerk) );
			r_Params->s_t_v = r_Params->s_t_j + r_Params->s_t_a;
		break;
		default: break;
	}
	r_Params->s_t1 = r_Params->s_t_j;
	r_Params->s_t2 = r_Params->s_t_a;
	r_Params->s_t3 = r_Params->s_t_j + r_Params->s_t_a;
	r_Params->s_t4 = r_Params->s_t_v;
	r_Params->s_t5 = r_Params->s_t_j + r_Params->s_t_v;
	r_Params->s_t6 = r_Params->s_t_v + r_Params->s_t_a;
	r_Params->s_t7 = r_Params->s_t_j + r_Params->s_t_a + r_Params->s_t_v;
	PRINTF_DEBUG && printf("\nTj = %.2f | Ta = %.2f | Tv = %.2f\n", r_Params->s_t_j, r_Params->s_t_a, r_Params->s_t_v);
	PRINTF_DEBUG && printf("\nt1 = %.2f | t2 = %.2f | t3 = %.2f | t4 = %.2f | t5 = %.2f | t6 = %.2f | t7 = %.2f\n", r_Params->s_t1, r_Params->s_t2, r_Params->s_t3, r_Params->s_t4, r_Params->s_t5, r_Params->s_t6, r_Params->s_t7);
	return;
}

void calculate_S_accelerations(rampParams *r_Params)
{
	r_Params->s_a1 = (r_Params->jerk * r_Params->s_t1);
	r_Params->s_a2 = r_Params->s_a1;
	r_Params->s_a3 = 0;//r_Params->s_a2 - r_Params->jerk * ( r_Params->s_t3 - r_Params->s_t2);	// a3 = 0.
	r_Params->s_a4 = 0;
	r_Params->s_a5 = -1 * r_Params->s_a1;	// a5 = -a1.
	r_Params->s_a6 = -1 * r_Params->s_a1;	// a6 = a5 = -a1.
	r_Params->s_a7 = 0;//r_Params->s_a6 + r_Params->jerk * (r_Params->s_t7 - r_Params->s_t6);	// a7 = 0.
	PRINTF_DEBUG && printf("\na1 = %.2f | a2 = %.2f | a3 = %.2f | a4 = %.2f | a5 = %.2f | a6 = %.2f | a7 = %.2f\n", convert_PPS_To_RPM(r_Params->s_a1), convert_PPS_To_RPM(r_Params->s_a2), convert_PPS_To_RPM(r_Params->s_a3), convert_PPS_To_RPM(r_Params->s_a4), convert_PPS_To_RPM(r_Params->s_a5), convert_PPS_To_RPM(r_Params->s_a6), convert_PPS_To_RPM(r_Params->s_a7));
	PRINTF_DEBUG && printf("\na1 = %.2f | a2 = %.2f | a3 = %.2f | a4 = %.2f | a5 = %.2f | a6 = %.2f | a7 = %.2f\n", r_Params->s_a1, r_Params->s_a2, r_Params->s_a3, r_Params->s_a4, r_Params->s_a5, r_Params->s_a6, r_Params->s_a7);
	return;
}

void calculate_S_velocities(rampParams *r_Params)
{
	r_Params->s_v1 = r_Params->jerk * ( (sq_Value(r_Params->s_t1) ) / 2 );
	r_Params->s_v2 = r_Params->s_v1 + r_Params->s_a1 * (r_Params->s_t2 - r_Params->s_t1);
	r_Params->s_v3 = r_Params->s_v2 + r_Params->s_a2 * (r_Params->s_t3 - r_Params->s_t2) - r_Params->jerk * ( sq_Value(r_Params->s_t3 - r_Params->s_t2) / 2);
	r_Params->s_v4 = r_Params->s_v3;
	r_Params->s_v5 = r_Params->s_v4 - r_Params->jerk * ( ( sq_Value(r_Params->s_t5 - r_Params->s_t4)) / 2 );
	r_Params->s_v6 = r_Params->s_v5 - r_Params->accelerations * (r_Params->s_t6 - r_Params->s_t5);
	r_Params->s_v7 = r_Params->s_v6 + r_Params->s_a6 * (r_Params->s_t7 - r_Params->s_t6) + r_Params->jerk * ((sq_Value(r_Params->s_t7 - r_Params->s_t6) ) / 2);
	
	(r_Params->s_v3 != r_Params->target_Velocity) ? PRINTF_DEBUG && printf("\nV3 != Vmax\n"): (0);
	PRINTF_DEBUG && printf("\nv1 = %.2f | v2 = %.2f | v3 = %.2f | v4 = %.2f | v5 = %.2f | v6 = %.2f | v7 = %.2f\n", convert_PPS_To_RPM(r_Params->s_v1), convert_PPS_To_RPM(r_Params->s_v2), convert_PPS_To_RPM(r_Params->s_v3), convert_PPS_To_RPM(r_Params->s_v4), convert_PPS_To_RPM(r_Params->s_v5), convert_PPS_To_RPM(r_Params->s_v6), convert_PPS_To_RPM(r_Params->s_v7));
	PRINTF_DEBUG && printf("\nv1 = %.2f | v2 = %.2f | v3 = %.2f | v4 = %.2f | v5 = %.2f | v6 = %.2f | v7 = %.2f\n", r_Params->s_v1, r_Params->s_v2, r_Params->s_v3, r_Params->s_v4, r_Params->s_v5, r_Params->s_v6, r_Params->s_v7);
	return;
}

void calculate_S_distances(rampParams *r_Params)
{
	r_Params->s_p1 = r_Params->jerk * ((cube_Value(r_Params->s_t1) ) / 6);
	r_Params->s_p2 = r_Params->s_p1 + r_Params->s_v1 * (r_Params->s_t2 - r_Params->s_t1) + r_Params->s_a1 * ((sq_Value(r_Params->s_t2 - r_Params->s_t1) ) / 2);
	r_Params->s_p3 = r_Params->s_p2 + r_Params->s_v2 * (r_Params->s_t3 - r_Params->s_t2) + r_Params->s_a2 * ((sq_Value(r_Params->s_t3 - r_Params->s_t2) ) / 2) - \
					 r_Params->jerk * ((cube_Value(r_Params->s_t3 - r_Params->s_t2) ) / 6);
	r_Params->s_p4 = r_Params->s_p3 + r_Params->s_v3 * (r_Params->s_t4 - r_Params->s_t3);
	r_Params->s_p5 = r_Params->s_p4 + r_Params->s_v4 * (r_Params->s_t5 - r_Params->s_t4) - r_Params->jerk * ((cube_Value(r_Params->s_t5 - r_Params->s_t4) ) / 6);
	r_Params->s_p6 = r_Params->s_p5 + r_Params->s_v5 * (r_Params->s_t6 - r_Params->s_t5) + r_Params->s_a5 * ((sq_Value(r_Params->s_t6 - r_Params->s_t5) ) / 2);
	r_Params->s_p7 = r_Params->s_p6 + r_Params->s_v6 * (r_Params->s_t7 - r_Params->s_t6) + r_Params->s_a6 * ((sq_Value(r_Params->s_t7 - r_Params->s_t6) ) / 2) + /*-?*/ \
					 r_Params->jerk * ((cube_Value(r_Params->s_t7 - r_Params->s_t6) ) / 6);
	/*r_Params->s_p5 = r_Params->s_p4 + r_Params->s_p1;
	r_Params->s_p6 = r_Params->s_p5 + (r_Params->s_p3 - (2 * r_Params->s_p1) );
	r_Params->s_p7 = r_Params->s_p6 + r_Params->s_p1;*/
	PRINTF_DEBUG && printf("\np1 = %.2f | p2 = %.2f | p3 = %.2f | p4 = %.2f | p5 = %.2f | p6 = %.2f | p7 = %.2f\n", r_Params->s_p1, r_Params->s_p2, r_Params->s_p3, r_Params->s_p4, r_Params->s_p5, r_Params->s_p6, r_Params->s_p7);
	return;
}

void calculate_S_Ramp_Parameters(rampParams *r_Params)
{
	r_Params->target_Position	= tmc4671_getTargetPosition(MOTOR);
	r_Params->initial_Position	= tmc4671_getActualPosition(MOTOR);
	r_Params->accelerations		= axis_params.acceleration;
	r_Params->jerk				= axis_params.jerk;
	r_Params->distance_total	= abs(r_Params->target_Position - r_Params->initial_Position);
	//r_Params->target_Velocity	= 30;
	r_Params->dist_mm			= r_Params->distance_total / ONE_MM;
	adjust_S_Velocity();
	conversion_of_values(&rParams);
	PRINTF_DEBUG && printf("\nTotal Distance = %.2f steps or %.2f mm\n", r_Params->distance_total, (r_Params->distance_total / ONE_MM) );
	PRINTF_DEBUG && printf("\nInitial Position = %.2f steps or %.2f mm\n", r_Params->initial_Position, (r_Params->initial_Position / ONE_MM) );
	PRINTF_DEBUG && printf("\nTarget Position = %.2f steps or %.2f mm\n", r_Params->target_Position, (r_Params->target_Position / ONE_MM) );
	PRINTF_DEBUG && printf("\nTarget Velocity = %.2f pps or %.2f rpm\n", r_Params->target_Velocity, (convert_PPS_To_RPM(r_Params->target_Velocity)) );
	PRINTF_DEBUG && printf("\nAcceleration = %.2f pps/s or %.2f rpm/s\n", r_Params->accelerations, (convert_PPS_To_RPM(r_Params->accelerations)) );
	PRINTF_DEBUG && printf("\nJerk = %.2f pps/s/s or %.2f rpm/s/s\n", r_Params->jerk, (convert_PPS_To_RPM(r_Params->jerk)) );
	find_S_Ramp_Case(&rParams);
	calculate_S_Time(&rParams);
	calculate_S_accelerations(&rParams);
	calculate_S_velocities(&rParams);
	calculate_S_distances(&rParams); 
	return;
}