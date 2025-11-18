/*******************************************************************************
* Copyright ? 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2209_Simple_Rotation.h"
#include "TMC2209_HW_Abstraction.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

//#include "hal_usart_async.h"
//#include "driver_init.h"

/*
 * Configures the registers with the right settings that are needed for rotating the motor.
 * E.g Enabling driver, setting IRUN current etc.
 */
void init_tmc2209_motor(uint16_t icID)
{
    tmc2209_writeRegister(icID, TMC2209_GCONF, 0x00000060);         // DEC 104.
    
    tmc2209_writeRegister(icID, TMC2209_TPOWERDOWN, 0x00000014);    // DEC 20.
    
    tmc2209_writeRegister(icID, TMC2209_IHOLD_IRUN, 0x00071700);    // DEC 464643. 0x71703
    
    tmc2209_writeRegister(icID, TMC2209_CHOPCONF, 0x10000053);      // DEC 268435539.
    
    tmc2209_writeRegister(icID, TMC2209_PWMCONF, 0xC10D0024);       // DEC 3238854692.
	
	tmc2209_writeRegister(icID, TMC2209_TPOWERDOWN, 0x00000002);
	
	PRINTF_DEBUG ? printf("\nTMC2209 Init Done for Guide Motor.\n"): 0;
	
	//gpio_set_pin_level(INDEX_SEL, LOW);
	
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
		tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0x000003E8);
		//delay_ms(500);
		//while(p_guide_info->step_tracker.total_steps <= TMC2209_ROTATION)
		{
			//update_TMC2209_Step_Tracking(p_guide_info);
		}
		
		update_TMC2209_Step_Tracking(p_guide_info);
		PRINTF_DEBUG ? printf("\nGuide total Steps = %ld | Total Dist = %ld\n", p_guide_info->step_tracker.total_steps, p_guide_info->step_tracker.total_dist): 0;
		tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0xFFFFFC18);
		//delay_ms(500);
		//while(p_guide_info->step_tracker.total_steps >= ZERO_HEX)
		{
			//update_TMC2209_Step_Tracking(p_guide_info);
		}
	}
	tmc2209_set_velocity(TMC2209_GUIDE_ADDR, p_guide_info, 0x00000000);
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