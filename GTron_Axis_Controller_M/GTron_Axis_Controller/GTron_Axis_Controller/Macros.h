/*
 * Macros.h
 *
 * Created: 13-12-2023 15:15:24
 *  Author: sreevathsank
 */ 

/** 
 * \file
 *
 * \brief Contains nearly all the MACROS used all over project.
 */

#ifndef MACROS_H_
#define MACROS_H_


#define ever						(;;)			// a goof!

#define PRINTF_DEBUG				1				// 1 -> Enable Printf statements | 0 -> Disable Printf Statements.

#define V3_TABLE					false			// Testing on v3 Table?		

#define MOT_DIR_REV					false			// Motor Direction Reversed?

/**********************************
 * ADC value ranges for each axis.*
 **********************************/
#define X_AXIS_ADC_MIN				79
#define X_AXIS_ADC_MAX				92

#define Y_AXIS_ADC_MIN				121
#define Y_AXIS_ADC_MAX				135

#define Z_AXIS_ADC_MIN				164
#define Z_AXIS_ADC_MAX				177

#define GTRON_AXC_ADC_MIN			195
#define GTRON_AXC_ADC_MAX			208
/**********************************/	

#define ADC_CHANNEL					0				// ADC Channel to read from.
#define ADC_READ_LENGTH				2				// No. of bytes to read. 8 bit = 1 | 10 and 12 bits = 2.			
#define ADC_NUM_READINGS			50				// No. of ADC Readings to average.

#define ADC_RAW_NUM_READINGS		1000			// No. of ADC RAW value read from TMC4671 for ADC offset calibration.

/** 
 * TMC2209 Module Addresses.
 **/
#define TMC2209_GUIDE_ADDR			0x00			// Hardware address of TMC2209 Guide Motor Driver.
#define TMC2209_VERT_ARREST_ADDR	0x00			// Hardware address of TMC2209 Vertical Arrestor Motor Driver.

#define MOTOR_ENC					0
#define WHITE_TEST_RIG				0
#define XY_TABLE					0

#define OPENLOOP					0				// Make this 1 if running in Open Loop.
#define CLOSEDLOOP					1				// Make this 1 if running in Closed Loop.

#define NO_OF_MOVE_DONE_CHECK		10				// The number of times actual position of the motor is checked
													// before Move Done is given.

/** 
 * Boolean values to represent the given move is Move To (Absolute) or Move By (Relative).
 */
#define MOVE_TO						true			
#define MOVE_BY						false			
/**/

#define HOMING_RAMP_DELTA			0.025f			// The Acceleration delta for increasing velocity for homing sequence.

#define VELOCITY_RAMP_DELTA			0.2f			// The Acceleration delta for increasing velocity during velocity mode.

#define ONE_BY_SIX					( 1.0f / 6.0f )	

													// One Rotation = 65,536steps = 6.35mm in Z-Axis.
#define ONE_MM						10320.63f		// No. of steps required to move the Z-Axis Motor for a distance of 1mm.
#define PITCH_MM					6.35f			// Linear Distance traveled in the lead screw for 1 motor mechanical rotation in mm.
#define MOVE_MM(mm)					(ONE_MM * (mm))	// Distance mm to steps conversion. MOVE_MM(2) means 2mm or 20641.26 steps.
#define MINUTES						60.0f			// No. of seconds in a minute.

#define EULER						2.718f			// Euler's Number (e).

#ifndef MOTOR
	#define MOTOR						0				// Default MotorID
#endif

#ifndef MIN_DISTANCE_RAMP
	#define MIN_DISTANCE_RAMP		500				// If the no. of steps to move is greater than this, use ramp. Else move without ramp.
#endif

#define POSITION_LOW				0x80000001		// Min. value of the PID_POSITION register.
#define POSITION_HIGH				0x7FFFFFFF		// Max. value of the PID_POSITION register.

#define ROTATION					65536			// No. of steps in one full rotation (360 degrees) of the stepper motor.

#define RAMP_INTERVAL_MS			1				// Interval for timer to raise the interrupt. Used for Ramp Generation.

#define VEL_INTERVAL_MS				250				// Interval for timer used to send motor position via CAN during Knob Mode. 

#define ONE_MS_IN_SECONDS			0.001f			// 1 millisecond in seconds.				

#define LIMIT_DELAY					250				// Delay(ms) given after a limit is hit.

#define ENDURANCE_MOVE_DELAY_MS		0				// Delay(ms) before giving next position to move to during firmware endurance run.

#define VELOCITY_TEST_DELAY_MS		20				// Delay(ms) between every state change. Only for testing velocity mode.

#define HOMING_SWITCH_POSITION		MOVE_MM(1)		// Distance Moved by the Motor during Homing Switching Sequence. Limit-> |-------| <-Switch_Pos.

#define SOFT_LIMIT_OFFSET_MM		MOVE_MM(2)		// By how much distance should the soft limit to be from the hard limit in mm.

#define AUTOFOCUS_INDEX_LENGTH		30				// Size of the array to store the camera trigger positions during AutoFocus.

#define LIMIT_SWITCH_RISING			0				// If Limit Switch LED is ON by default, enable this.
#define LIMIT_SWITCH_FALLING		1				// If Limit Switch LED is OFF by default, enable this.

#if V3_TABLE
	#define LIN_ENC_RES				6350			// The resolution or PPR of the Linear Encoder. v3 table -> 6350, v5 table -> 13005 // For v3 Table.
#else
	#define LIN_ENC_RES				13005			// The resolution or PPR of the Linear Encoder. v3 table -> 6350, v5 table -> 13005 // For v3 Table.
#endif

#if V3_TABLE
	#define ROT_ENC_RES				0x00004000		// Rotary Encoder Pulses per Rotation (PPR) or Resolution | 0x00004000 -> 16384 counts.
#else
	#define ROT_ENC_RES				0x00002000		// Rotary Encoder Pulses per Rotation (PPR) or Resolution | 0x00002000 -> 8192 counts.
#endif


#define BROADCOM_ENCODER			1				// Encoder with resolution 8192.
#define AMT_ENCODER					0				// Encoder with resolution 16384.

#if BROADCOM_ENCODER								// This check to assign value for
	#define ENC_MUL_FACTOR			8				// ENC_MUL_FACTOR (Encoder Multiplication Factor)
#elif AMT_ENCODER									// (65536 / 8192 ) = 8
	#define ENC_MUL_FACTOR			4				// (65536 / 16384) = 4
#endif

#define HOME_POSITION_HIGH			0
#define HOME_POSITION_MIDDLE		1
#define HOME_POSITION_ZERO			0

#define HIGH						true
#define LOW							false

#define DEC							10				// Decimal notation.
#define HEX							16				// Hexadecimal notation.

#define ZERO_HEX					0x00000000

#define UQ_UD_MODE					0x00000008
#define VELOCITY_MODE				0x00000002
#define TORQUE_MODE					0x00000001
#define POSITION_MODE				0x00000003
#define STOPPED_MODE				ZERO_HEX
#define pVELOCITY_MODE				0x80000002
#define pTORQUE_MODE				0x80000001
#define pPOSITION_MODE				0x80000003
#define pSTOPPED_MODE				0x80000000
	
//mydefines
#define STATE_START_INIT			1
#define STATE_RUN_1					2
#define STATE_RUN_2					3

#define UD_EXT						3202

#define PID_POSITION_WINDOW			12				//Error Window for Move Done Signal.

#define STOP_VELOCITY				100

#define PID_POSITION_ERROR			0x00000003

#define ABN_ENC_REVERSE_DIRECTION   0x00001000		// Encoder counting direction is reverse.
#define ABN_ENC_FORWARD_DIRECTION   0x00000000		// Encoder counting direction is forward.

// For Velocity Mode
#define VELOCITY_0				0				// 0 RPM.
#define VELOCITY_1				2				// 2 RPM.
#define VELOCITY_2				5				// 10 RPM.
#define VELOCITY_3				20				// 25 RPM.
#define VELOCITY_4				50				// 50 RPM.
#define VELOCITY_5				75				// 80 RPM.
#define VELOCITY_6				100				// 100 RPM.
#define VELOCITY_7				200				// 200 RPM.
#define VELOCITY_8				300				// 300 RPM.
#define VELOCITY_9				400				// 400 RPM.
#define VELOCITY_10				500				// 500 RPM.

#define VELOCITY_neg_1			-2				// -2 RPM.
#define VELOCITY_neg_2			-5				// -10 RPM.
#define VELOCITY_neg_3			-20				// -25 RPM.
#define VELOCITY_neg_4			-50				// -50 RPM.
#define VELOCITY_neg_5			-75				// -80 RPM.
#define VELOCITY_neg_6			-100			// -100 RPM.
#define VELOCITY_neg_7			-200			// -200 RPM.
#define VELOCITY_neg_8			-300			// -300 RPM.
#define VELOCITY_neg_9			-400			// -400 RPM.
#define VELOCITY_neg_10			-500			// -500 RPM.

//     in hpl_eic_config.h                                               
#if LIMIT_SWITCH_RISING
	#define CONF_EIC_SENSE10 EIC_NMICTRL_NMISENSE_RISE_Val		// For LIM_RT.
	#define CONF_EIC_SENSE12 EIC_NMICTRL_NMISENSE_RISE_Val		// For LIM_LFT.
#elif LIMIT_SWITCH_FALLING
	#define CONF_EIC_SENSE10 EIC_NMICTRL_NMISENSE_FALL_Val		// For LIM_RT.
	#define CONF_EIC_SENSE12 EIC_NMICTRL_NMISENSE_FALL_Val		// For LIM_LFT.
#endif

#endif /* MACROS_H_ */