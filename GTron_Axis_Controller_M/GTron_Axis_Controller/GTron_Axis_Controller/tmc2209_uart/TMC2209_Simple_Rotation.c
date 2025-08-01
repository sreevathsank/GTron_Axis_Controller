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
    tmc2209_writeRegister(icID, TMC2209_GCONF, 0x00000060);         // DEC 64.
    
    /*tmc2209_writeRegister(icID, TMC2209_TPOWERDOWN, 0x00000014);    // DEC 20.
    
    tmc2209_writeRegister(icID, TMC2209_IHOLD_IRUN, 0x00071703);    // DEC 464643.
    
    tmc2209_writeRegister(icID, TMC2209_CHOPCONF, 0x10000053);      // DEC 268435539.
    
    tmc2209_writeRegister(icID, TMC2209_PWMCONF, 0xC10D0024);       // DEC 3238854692.
	*/
    
	// Generate step pulse (S/D) externally via the connected microcontroller.

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