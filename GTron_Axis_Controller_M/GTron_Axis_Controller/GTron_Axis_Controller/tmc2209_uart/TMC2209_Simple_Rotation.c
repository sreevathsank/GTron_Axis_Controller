/*******************************************************************************
* Copyright ? 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2209_Simple_Rotation.h"
//#include "hal_usart_async.h"
#include "driver_init.h"

/*
 * Configures the registers with the right settings that are needed for rotating the motor.
 * E.g Enabling driver, setting IRUN current etc.
 */
void initAllMotors(uint16_t icID)
{
    tmc2209_writeRegister(icID, TMC2209_GCONF, 0x00000060);         // DEC 104.
    
    tmc2209_writeRegister(icID, TMC2209_TPOWERDOWN, 0x00000014);    // DEC 20.
    
    tmc2209_writeRegister(icID, TMC2209_IHOLD_IRUN, 0x00071703);    // DEC 464643.
    
    tmc2209_writeRegister(icID, TMC2209_CHOPCONF, 0x10000053);      // DEC 268435539.
    
    tmc2209_writeRegister(icID, TMC2209_PWMCONF, 0xC10D0024);       // DEC 3238854692.
	
	guide_step_counter_value = 0;
	
	PRINTF_DEBUG ? printf("\nTMC2209 Init Done for Guide Motor.\n"): 0;
	
	//GUIDE_STEP_COUNTER_CLOCK_init();
	//(void)GUIDE_STEP_COUNTER_init();
	
	gpio_set_pin_level(INDEX_SEL, LOW);
	
	//counter_Clear_Count_Val(GUIDE_STEP_COUNTER);
	counter_Write_Count_Val(GUIDE_STEP_COUNTER, 0x00000001);
	
	PRINTF_DEBUG ? printf("\nGuide Index Step Count = %ld\n", counter_Read_Count_Val(GUIDE_STEP_COUNTER) ): 0;
	
    return;
}

void move_guide_motor( void )
{
	uint32_t count_reg = 0;
	for(int32_t i = 0; i < 5; i++)
	{
		delay_ms(500);
		count_reg = counter_Read_Count_Val(GUIDE_STEP_COUNTER);
		PRINTF_DEBUG ? printf("\nCount Val = %ld\n", count_reg): 0;
		//tmc2209_writeRegister(0x00, TMC2209_VACTUAL,  0x000003E8);
		tmc2209_set_velocity(0x00, 0x000003E8, GUIDE_STEP_COUNTER);
		
		delay_ms(500);
		count_reg = counter_Read_Count_Val(GUIDE_STEP_COUNTER);
		PRINTF_DEBUG ? printf("\nCount Val = %ld\n", count_reg): 0;
		//tmc2209_writeRegister(0x00, TMC2209_VACTUAL,  0xFFFFFC18);
		tmc2209_set_velocity(0x00, 0xFFFFFC18, GUIDE_STEP_COUNTER);
		//tmc2209_set_velocity(0x00, 0x00000000, GUIDE_STEP_COUNTER);
	}
	tmc2209_set_velocity(0x00, 0, GUIDE_STEP_COUNTER);
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
            gconf, tpwrdwm, ihold, chop, pwm);
    
    return;
}