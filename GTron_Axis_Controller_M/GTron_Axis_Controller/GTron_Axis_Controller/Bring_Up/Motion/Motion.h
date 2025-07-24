/*
 * Motion.h
 *
 * Created: 16-12-2023 12:30:34
 *  Author: sreevathsank
 */ 


#ifndef MOTION_H_
#define MOTION_H_


#include "All_Headers.h"
#include "Bring_Up/CAN/IMM_CAN_Message_Id.h"

void init_PosMode(uint8_t motor);

void init_Basics(uint8_t motor);

void reset_Basics(uint8_t motor);

void align_Rotor_ABNEnc(uint8_t motor, uint16_t startVoltage);

void open_loop_fb(void);

void run_Trapezoidal_Ramp(void);

void run_Trapezoidal_Ramp_Dynamic(void);

void move_With_Trapezoidal_Ramp(int32_t target_position, int32_t velocity);

void move_With_S_Ramp(float target_position, int32_t velocity, bool move_to_by);

void run_S_ramp(void);

bool camera_Trigger(void);

void stop_Motor_Mad(void);

void check_For_Move_Done(void);

void run_Velocity_Mode(void);

void run_Velocity_Mode(void);

void left_limit_homing(void);

void left_limit_high(void);

void right_limit_homing(void);

void right_limit_high(void);

void check_Limit_Flags(void);

void rotEnc_Count_Callback(void);

void rotEnc_Direction_Callback(void);

void init_Enc_Cnt_Dir(void);

void init_ext_irq_limits(void);

void left_Limit_Interrupt_Callback(void);

void right_Limit_Interrupt_Callback(void);

void homing_Ramp(void);

void do_homing_sequence( void );

void short_Acceleration_Ramp(int32_t velocity_limit, double_t velocity_delta);

void set_Home_Position_Limits(void);

void short_Deceleration_Ramp(double_t velocity_delta);

//void wait_For_Move_Done(void)

void check_Soft_Limits(void);

#endif /* MOTION_H_ */