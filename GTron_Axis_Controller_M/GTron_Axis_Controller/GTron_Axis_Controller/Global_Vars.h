/*
 * Global_Vars.h
 *
 * Created: 20-12-2023 18:11:40
 *  Author: sreevathsank
 */

/** 
 * \name
 *
 * \brief Contains the Global Variables.
 */ 


#ifndef GLOBAL_VARS_H_
#define GLOBAL_VARS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>

#include "Macros.h"

uint8_t can_rx_int, ad, cmd, typ, mot, crc, checksum;
int32_t can_status, idx;

bool motor_dir_rev, lim_edge_detection, rfs_ping_rxvd;

/********************************************************************
 * An Enum to indicate the axis of the current Axis Controller board*
 ********************************************************************/
typedef enum
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	RF_AXIS,
	GTRON_AXC_TOP,
	GTRON_AXC_BOT,
	NO_OF_AXES
}axis_current;

typedef union
{
	uint16_t adc_16bit;
	uint8_t adc_8bit[2];
}adc_values;

struct io_descriptor *io_tmc2209;

typedef struct
{
	uint32_t start_voltage;
	uint32_t align_delay;
	uint32_t torque_flux_limit;
	uint32_t torque_p;
	uint32_t torque_i;
	uint32_t flux_p;
	uint32_t flux_i;
	uint32_t velocity_p;
	uint32_t velocity_i;
	uint32_t position_p;
	uint32_t position_i;
	int32_t  home_search_vel;
	int32_t  home_switch_vel;
	int32_t  endurance_vel;
	uint32_t acceleration;
	double acceleration_delta;
	int32_t jerk;
	double jerk_delta;
	int32_t lin_enc_res;
	int32_t rot_enc_res;
	bool rotary_axis_enabled;
}axis_parameters;

typedef struct  
{
	// Flags
	bool triangular_ramp;		// 0 -> Not a triangular ramp | 1 -> triangular ramp.
	bool on_the_fly_change;		// Denotes if a new velocity was given during the ramp.
	bool timer_ramp_flag;
	
	// Positions
	double target_Velocity;
	double target_Position;
	double initial_Position;
	double accelerations;
	double accel_delta;
	double distance_accel;
	double distance_accel_point;
	double distance_decel_point;
	double distance_start_point;
	double distance_cruise;
	double distance_total;
	double dist_mm;
	
	// S curve parameters
	double jerk;
	//double jerk_delta;
	//double s_p[8];
	double s_p1;
	double s_p2;
	double s_p3;
	double s_p4;
	double s_p5;
	double s_p6;
	double s_p7;
	//float s_acceleration;
	//float s_accel_delta;
	double s_t_j;						// Time taken in Jerk phase.
	double s_t_v;						// Time taken in constant Velocity phase.
	double s_t_a;						// Time taken in constant Acceleration phase.
	//double s_t[8];
	double s_t1;						// Time taken in Phase 1.
	double s_t2;						// Time taken in Phase 2.
	double s_t3;						// Time taken in Phase 3.
	double s_t4;						// Time taken in Phase 4.
	double s_t5;						// Time taken in Phase 5.
	double s_t6;						// Time taken in Phase 6.
	double s_t7;						// Time taken in Phase 7.
	//double s_v[8];
	double s_v1;						// Velocity at t1.
	double s_v2;						// Velocity at t2.
	double s_v3;						// Velocity at t3.
	double s_v4;						// Velocity at t4.
	double s_v5;						// Velocity at t5.
	double s_v6;						// Velocity at t6.
	double s_v7;						// Velocity at t7.
	//double s_a[8];
	double s_a1;						// Acceleration at t1.
	double s_a2;						// Acceleration at t2.
	double s_a3;						// Acceleration at t3.
	double s_a4;						// Acceleration at t4.
	double s_a5;						// Acceleration at t5.
	double s_a6;						// Acceleration at t6.
	double s_a7;						// Acceleration at t7.
	double s_accel_decel_time;
	double s_accel_decel_distance;
	double s_cruise_time;
	double s_cruise_distance;
	double s_Va;						// Max Velocity that can be reached with an S Curve Trajectory.
	double s_Sa;						// Max Distance that cab be traversed with an S Curve Trajectory.
	double s_Sv;						// Min. Distance needed for the S Curve trajectory to have an constant velocity movement.
	double s_S_min;						// Min. Distance the S Ramp requires for the given acceleration and jerk.
		
	// Case 1 or 2.
	enum
	{
		case_1 = 0,
		case_2 = 1
	}case_x;
	
	// Type of S Ramp.
	enum
	{
		A = 0,
		B = 1,
		C1 = 2,
		C2 = 3,
		D1 = 4,
		D2 = 5	
	}ramp_case;
	
	// Time
	double time_accel;
	double time_cruise;
	double time_total;
	int32_t time_ramp;
	
	// Points
	int32_t decel_start;
	int32_t accel_end;
	int32_t ramp_end;
	int32_t phase_error;
}rampParams;

typedef enum
{
	PHASE_1,
	PHASE_2,
	PHASE_3,
	PHASE_4,
	PHASE_5,
	PHASE_6,
	PHASE_7,
	DO_REPEAT	
}s_state;

typedef struct 
{
	int32_t acceleration;
	int32_t velocity;
	int32_t uq_ud;	
}OpenLoopData;

int32_t t_Position;

// Ramp States
typedef enum
{
	STOP,
	ACCEL,
	CRUISE,
	DECEL,
	DO_NOTHING,
	TRANSITIVE_ACCEL,
	TRANSITIVE_DECEL
}trapezoidal_state;

// Ramp variables
int32_t velocity_limit, prev_velocity_limit, t, p, p_time, c_time;
double v, v_temp, homing_v, a_temp;
bool timer_flag, non_rep, move_given_trapezoidal_ramp, move_given_s_ramp;
bool check_move_done, move_done;
uint8_t repeat_ramp;
uint32_t current_time, prev_time;

// External Interrupt Limit variables struct
typedef struct 
{
	// Flags
	bool left_limit_flag;
	bool right_limit_flag;
	bool homing;
	bool hit_limit_left;
	bool hit_limit_right;
	bool loop;
	bool first_limit_hit;
	bool other_limit_hit;
	bool switch_seq_flag;
	bool homing_done;
	bool lin_enc_z_first_hit;
	bool lin_enc_z_second_hit;
	
	// Positions
	int32_t	right_limit_position;
	int32_t left_limit_position;
	int32_t home_position;
	int32_t zero_limit_position;
	int32_t other_limit_position;
	int32_t middle_position;
	int32_t tpos;
	int32_t soft_limit_high;
	int32_t soft_limit_low;
	int32_t switch_seq_state;
}limitVariablesData;
#define TOWARDS_SWITCH_POS	0
#define TOWARDS_LIMIT		1
#define HIT_THE_LIMIT		2
#define SWITCH_SEQ_DONE		3
/*bool left_limit_flag, right_limit_flag;
int32_t right_limit_position, left_limit_position, zero_limit_position, other_limit_position, middle_position, tpos;
bool homing, hit_limit_left, hit_limit_right, loop, first_limit_hit;*/

// Rotary and Linear Encoder Count and Direction variables
typedef struct 
{
	// Rotary Encoder Signals Counters
	int32_t rot_enc_cnt;	// Rotary Encoder Count signal Counter
	int32_t rot_enc_dir;	// Rotary Encoder Direction signal Counter
	int32_t rot_enc_z;		// Rotary Encoder Z-pulse signal Counter
	
	// Linear Encoder Signals Counters
	int32_t lin_enc_cnt;	// Linear Encoder Count signal Counter
	int32_t lin_enc_dir;	// Linear Encoder Direction signal Counter
	int32_t lin_enc_z;		// Linear Encoder Z-pulse signal Counter
	
	int32_t direction;		// Can be +/- 1 and will increment or decrement cnt values.
}GEncoderVars;

// Timestamps
typedef struct  
{
	uint32_t move_start_time;
	uint32_t move_done_time;
	
}Timestamps;

// A structure for AutoFocus variables.
typedef struct 
{	
	int64_t combined;
	int startPointAF;				// Defined as signed integer to check if the value is negative or positive.
	int32_t gQDECstepSizeCount;
	int32_t starting_position;
	int32_t af_table[AUTOFOCUS_INDEX_LENGTH];
	int32_t sign_check;				// Variable to check the sign of startPositionAF.
	uint32_t sweep_no;
	
	uint32_t cam_trigger_count;		// Stores the camera trigger count for the current sweep.
	
	// Temporary Variables for Velocity and Position.
	int32_t temp_t_pos;
	int32_t temp_t_vel;
	
	// A Boolean to check if one of the above variables were received or not.
	bool one_received;
	bool both_received;
	bool change_comp_cnt;
	bool temp_move_change;
	
}autofocus_vars;

uint32_t move_done_check_num;

typedef struct  
{
	uint8_t limit_flags;
	bool interrupt_raised;	
}GTron_Limits_t;


typedef enum
{
	VEL_STATE_0,
	VEL_STATE_1,
	VEL_STATE_2,
	VEL_STATE_3,
	VEL_STATE_4,
	VEL_STATE_5,
	VEL_STATE_6,
	VEL_STATE_7,
	VEL_STATE_8,
	VEL_STATE_9,
	VEL_STATE_10,
	VEL_STATE_neg_1,
	VEL_STATE_neg_2,
	VEL_STATE_neg_3,
	VEL_STATE_neg_4,
	VEL_STATE_neg_5,
	VEL_STATE_neg_6,
	VEL_STATE_neg_7,
	VEL_STATE_neg_8,
	VEL_STATE_neg_9,
	VEL_STATE_neg_10,
	VEL_STATE_IDLE
}VelocityState;

typedef struct  
{
	bool knob_enabled;
	bool test_enabled;
	bool position_send;
	bool direction;			// True -> Clockwise | False -> Anti Clockwise.
	int32_t vel_state;
	int32_t prev_lin_enc_val;
}Velcoity_Struct;

int32_t current_position;
int32_t decel_error_position;
int32_t stop_error_position;
int32_t decel_velocity;
int32_t stop_velocity;

axis_current		axis_id;
adc_values			adc_reading;
axis_parameters		axis_params;
rampParams			rParams;
trapezoidal_state	ramp_State;
s_state				s_curve_phase;
OpenLoopData		open_loop;
limitVariablesData	limit_variables;
GEncoderVars		x_axis_encoder_counters;
Timestamps			timestamp;
autofocus_vars		autofocus_variables;
Velcoity_Struct		vel_struct;
VelocityState		velocity_state;

GTron_Limits_t gtron_limits;

#endif /* GLOBAL_VARS_H_ */