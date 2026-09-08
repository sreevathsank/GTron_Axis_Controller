/*******************************************************************************
* Copyright ? 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2209_Simple_Rotation.h"
#include "driver_init.h"

/*
 * IRUN calculation for per-motor current scaling:
 *
 *   I_RMS = (IRUN/32) * Vfs / (Rsense * sqrt(2))
 *
 *   where:  Vfs    = 180mV  (VSENSE=1, low-current range)
 *           Rsense = 0.11 ohm  (Watterott SilentStepStick)
 *
 *   Solving for IRUN:
 *   IRUN = I_RMS * 32 * sqrt(2) * 0.11 / 0.180 = I_RMS * 27.66
 *
 *   Examples:
 *     NEMA 8  @ 0.6A -> IRUN = round(0.6 * 27.66) = 17  -> 0.615A RMS
 *     NEMA 11 @ 0.7A -> IRUN = round(0.7 * 27.66) = 19  -> 0.687A RMS
 *     NEMA 14 @ 1.0A -> IRUN = round(1.0 * 27.66) = 28  -> 1.012A RMS
 *
 */
static uint8_t get_irun_for_motor(Motor_Name_Enum_t mot_name)
{
	switch(mot_name) {
		case MOTOR_VARREST1:
		case MOTOR_VARREST2:
			return 23;			
		case MOTOR_GUIDE:
		case MOTOR_FRONT_CAM:
		case MOTOR_REELERADJ1:
		case MOTOR_REELERADJ2:
		default:
			return 23;
	}
}

/*
 * Configures the registers with the right settings that are needed for rotating the motor.
 * E.g Enabling driver, setting IRUN current etc.
 */
void init_tmc2209_motor(uint16_t icID, const Motor_Info_t *m)
{
	if( (m->mot_name == MOTOR_VARREST2) || 
		(m->mot_name == MOTOR_REELERADJ1) ) {
		tmc2209_writeRegister(icID, TMC2209_GCONF, 0x00000060);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	} else {
		tmc2209_writeRegister(icID, TMC2209_GCONF, 0x00000068);         // DEC 104. //0x68 for inverse shaft dir. 0x60 for forward shaft dir.
	}
	tmc2209_writeRegister(icID, TMC2209_TPOWERDOWN, 0x00000000);    // DEC 20.
	
	uint8_t irun		= get_irun_for_motor(m->mot_name);
	uint8_t ihold_delay = 0;
	uint8_t ihold		= 0;
	uint32_t ihold_irun = (ihold_delay << 16) | (irun << 8) | ihold;			// ihold_delay = 7 ticks, irun = lookup, ihold = 0;
	tmc2209_writeRegister(icID, TMC2209_IHOLD_IRUN, ihold_irun);
	
	tmc2209_writeRegister(icID, TMC2209_CHOPCONF, 0x10020054);      // DEC 268435539. // was 0x10000053
	tmc2209_writeRegister(icID, TMC2209_PWMCONF, 0xC40D0024);       // DEC 3238854692.
	
	DBG_Printf(ERR_LVL_DEBUG, "TMC2209 Init Done for Motor UART address %d.\n", icID);
	
	int32_t gconf_val = tmc2209_readRegister(icID, TMC2209_GCONF);
	DBG_Printf(ERR_LVL_DEBUG, "TMC2209 GCONF val = 0x%X\n", gconf_val);
	
	gpio_set_pin_level(INDEX_SEL, LOW);
	
    return;
}

void move_guide_motor(uint32_t loop_count)
{
	p_guide_info->step_tracker.total_steps  = 0;
	p_guide_info->step_tracker.total_dist	= 0; 
	for(int32_t i = 0; i < loop_count; i++)
	{
		update_TMC2209_Step_Tracking(p_guide_info);
		PRINTF_DEBUG ? printf("\nGuide total Steps = %ld | Total Dist = %ld\n", p_guide_info->step_tracker.total_steps, p_guide_info->step_tracker.total_dist): 0;
		tmc2209_set_velocity(TMC2209_MOTOR1_ADDR, p_guide_info, 0x000003E8);
		delay_ms(500);
		//while(p_guide_info->step_tracker.total_steps <= TMC2209_ROTATION)
		{
			//update_TMC2209_Step_Tracking(p_guide_info);
		}
		
		update_TMC2209_Step_Tracking(p_guide_info);
		PRINTF_DEBUG ? printf("\nGuide total Steps = %ld | Total Dist = %ld\n", p_guide_info->step_tracker.total_steps, p_guide_info->step_tracker.total_dist): 0;
		tmc2209_set_velocity(TMC2209_MOTOR1_ADDR, p_guide_info, 0xFFFFFC18);
		delay_ms(500);
		//while(p_guide_info->step_tracker.total_steps >= ZERO_HEX)
		{
			//update_TMC2209_Step_Tracking(p_guide_info);
		}
	}
	tmc2209_set_velocity(TMC2209_MOTOR1_ADDR, p_guide_info, 0x00000000);
	return;
}

void read_Init_Registers(uint16_t icID)
{
    int32_t gconf = tmc2209_readRegister(icID, TMC2209_GCONF);
    //while(SERCOM6_USART_ReadIsBusy());
    
    int32_t tpwrdwm = tmc2209_readRegister(icID, TMC2209_TPOWERDOWN);
    //while(SERCOM6_USART_ReadIsBusy());
    
    int32_t ihold = tmc2209_readRegister(icID, TMC2209_IHOLD_IRUN);
    //while(SERCOM6_USART_ReadIsBusy());
    
    int32_t chop = tmc2209_readRegister(icID, TMC2209_CHOPCONF);
    //while(SERCOM6_USART_ReadIsBusy());
    
    int32_t pwm = tmc2209_readRegister(icID, TMC2209_PWMCONF);
    //while(SERCOM6_USART_ReadIsBusy());
    
    printf("\nRead Values:\ngconf = %x | tpwrdwn = %x | ihold = %x | chop = %x | pwm = %x\n",
            (unsigned int)gconf, (unsigned int)tpwrdwm, (unsigned int)ihold, (unsigned int)chop, (unsigned int)pwm);
    
    return;
}