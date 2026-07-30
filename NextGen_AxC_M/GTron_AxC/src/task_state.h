/* 
 * File:   task_state.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 5:38 PM
 */

#ifndef TASK_STATE_H
#define	TASK_STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

typedef enum {
	HYBRID_MODE_OFF			= 0,
	HYBRID_MODE_INSPECTION	= 1,
	HYBRID_MODE_N_SHOT		= 2,
	NO_OF_HYBRID_STATES
}Hybrid_Mode_t;

// Struct containing all necessary values and flags for motor.
typedef enum {
	TOP_RACK		= 0,
	BOT_RACK		= 1,
	MOTOR_ID		= 2,
	ENCODER			= 3,
	LIMIT			= 4,
	TOP_SAG_REELER	= 5,
	BOT_SAG_REELER	= 6,
	NO_OF_RACK_ITEMS
}Rack_Enum_t;

typedef enum {
	TMC4671_MOTOR	= 0,
	TMC2209_MOTOR1	= 1,
	TMC2209_MOTOR2	= 2,
	NO_OF_MOT_INDICES
}Motor_Array_Index_t;

typedef enum {
	TMC2209_MOT_ADDR1 = 0,
	TMC2209_MOT_ADDR2 = 1,
	TMC2209_MOT_ADDR3 = 2,
	TMC2209_MOT_ADDR4 = 3,
	NO_OF_UART_MOT
}TMC2209_MOT_ADDR_t;

typedef struct {
	uint32_t id;
	uint8_t data[8];	
	int32_t value;
}Can_Cmd_Info_t;

typedef enum {
	MOTOR_GUIDE			= 0,
	MOTOR_REELER1		= 1,
	MOTOR_VARREST1		= 2,
	MOTOR_VARREST2		= 3,
	MOTOR_REELERADJ1	= 4,
	MOTOR_FRONT_CAM		= 5,
	MOTOR_REELER2		= 6,
	MOTOR_REELERADJ2	= 7,
	NO_OF_MOTOR_NAME	
}Motor_Name_Enum_t;

typedef struct {
	uint8_t uart_addr;
	uint8_t can_peripheral_byte;
}Communication_Info_t;

typedef enum {
	MOTOR_STOPPED_STATE		= 0,
	MOTOR_MOVING_STATE		= 1,
	MOTOR_MOVE_DONE_STATE	= 2
}Motor_State_t;

typedef struct {
	int32_t		target;
	int32_t		current;
	uint32_t	limit;
}Velocity_Info_t;

typedef struct {
	int32_t		target;
	int32_t		current;
	int32_t		right_open_limit;
	int32_t		left_close_limit;
	int32_t		initial;
	uint32_t	trig_step_size;				// Used for Encoder based and Hybrid based Triggering.
	uint32_t	counter_value;
}Position_Info_t;

typedef struct {
	int32_t		total_steps;
	int32_t		total_dist;
	uint16_t	prev_mscnt;
}Step_Tracker_t;

typedef struct {
	uint32_t		sens_trig;				// Time in ms when Sensor Interrupt was received.
	uint32_t		cam_trig;				// Time in ms when Camera Line was triggered.
	uint32_t		theoretical_move;
	uint32_t		move_start;
}Time_MS_t;

typedef struct {
	Hybrid_Mode_t 	mode;					// Current Hybrid Mode.
	int32_t			anchor_pos;				// Latched Reeler Position when Sensor Trigger is received.
	int32_t			prev_anchor_pos;		// For detecting Slip / Spurious Anchor-to-Anchor delta.
	uint32_t		unhandled_edges;		// diagnostic: edges seen with mode == OFF.
	uint32_t		total_n_shots;			// Total No of N Shots to execute.
	uint32_t		curr_n_shots;			// Current No of N Shots executed.
	uint32_t		term_width;				// Pitch/Width of the Terminal in usteps. Used for Slip Detection.
	
	uint16_t		total_slips;			// Total no. of tolerable slips.		
	uint16_t		consecutive_slips;		// Slip / Spurious Trigger counter.
	uint16_t		gc;						// Global Counter for Inspection.
	
	bool			cycle_armed;			// Anchor Valid; Awaiting offset to fire (Inspection).
	bool			first_trigger_skip;		// skip first edge after Inspection enable / fresh start.
	bool			one_shot_armed;			// One-Shot armed for the current Move-To / Move-By.
}Hybrid_t;

typedef struct {
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
	uint32_t is_paused				: 1;	// 11
	uint32_t is_encoder_mode		: 1;	// 12
	uint32_t is_double_limit		: 1;	// 13
	uint32_t is_tmc2209_homing		: 1;	// 14
	uint32_t first_lim_hit			: 1;	// 15
	uint32_t reserved				: 16;
}Motor_Flags_t;

typedef enum {
	DIR_NONE	= 0,
	DIR_FORWARD	= 1,
	DIR_REVERSE	= 2
}Direction_t;

typedef struct {
	Direction_t prev;
	Direction_t curr;
	Direction_t at_rlimit;	
	Direction_t at_llimit;
}Direction_Struct_t;

typedef struct {
	Motor_Name_Enum_t		mot_name;
	Communication_Info_t	comms;
	Motor_State_t			motor_state;
	Direction_Struct_t		move_dir;
	Velocity_Info_t			velocity;
	Position_Info_t			position;
	Step_Tracker_t			step_tracker;
	Time_MS_t				time_ms;
	Hybrid_t				hybrid;
	Motor_Flags_t			flags;
}Motor_Info_t;

typedef enum {
	REELER1_GUIDE_REELERADJ1	= 0,
	VARREST_1_2_SOLENOID		= 1,
	REELER2_REELERADJ2_FRONTCAM	= 2,
}SouthBridge_t;

typedef enum {
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	RF_AXIS,
	GTRON_AXC_TOP,
	GTRON_AXC_BOT,
	NO_OF_AXES
}axis_current;

// Pin configuration (set at init, read-only thereafter)
extern axis_current         g_axis_id;
extern SouthBridge_t        g_sbridge_addr;


// ISR ? task flags (volatile: written by ISR, read by exactly one task)
extern volatile bool        g_diag_pending;         // DIAG EIC ? TMC2209_TASK
extern volatile uint8_t     g_limit_flags;         // LIM EICs ? TMC4671_TASK
#define LIM_RT_BIT          0x01
#define LIM_LFT_BIT         0x02
extern volatile bool        g_ioxp_int_pending;     // IOXP EIC ? TMC2209_TASK
    
// Cross-task flags
extern volatile bool        g_flash_busy;           // SUPERVISOR (during flash ops) ? both motor tasks
extern bool                 g_2209_moving;

// Motor_Info_t instances (allocated statically, one per physical motor)
extern Motor_Info_t         g_motor_reeler1;
extern Motor_Info_t         g_motor_guide;
extern Motor_Info_t         g_motor_varrest1;
extern Motor_Info_t         g_motor_varrest2;
extern Motor_Info_t         g_motor_reeleradj1;
extern Motor_Info_t         g_motor_reeleradj2;
extern Motor_Info_t         g_motor_frontcam;
extern Motor_Info_t         g_motor_reeler2;

// Pointer array for indexed access (used by CAN parser dispatch)
extern Motor_Info_t         *mot_array[NO_OF_MOT_INDICES];

// Convenience pointers (set during init based on sbridge_addr)
extern Motor_Info_t         *p_reeler1_info;
extern Motor_Info_t         *p_guide_info;
extern Motor_Info_t         *p_varrest1_info;
extern Motor_Info_t         *p_varrest2_info;
extern Motor_Info_t         *p_reeleradj1_info;
extern Motor_Info_t         *p_reeleradj2_info;
extern Motor_Info_t         *p_frontcam_info;
extern Motor_Info_t         *p_reeler2_info;

// RTOS handles (needed to create tasks, use queues from modules)
extern QueueHandle_t        g_q_can_work;           // 16 x 16B
extern QueueHandle_t        g_q_4671_rx;            // 8 x 16B
extern QueueHandle_t        g_q_2209_rx;            // 8 x 16B
extern QueueHandle_t        g_q_sup_rx;             // 8 x 16B
extern QueueHandle_t        g_q_debug;              // 16 x 132B
extern SemaphoreHandle_t    g_m_sercom3;          // mutex for flash + IOXP SPI bus

extern TaskHandle_t         h_4671, h_can, h_2209, h_sup, h_dbg;

// Heartbeat counters
extern volatile uint32_t    g_heartbeat_can;
extern volatile uint32_t    g_heartbeat_tmc4671;
extern volatile uint32_t    g_heartbeat_tmc2209;
extern volatile uint32_t    g_heartbeat_supervisor;
extern volatile uint32_t    * const g_heartbeat_array[4];


#ifdef	__cplusplus
}
#endif

#endif	/* TASK_STATE_H */

