/*
 * Systick.c
 *
 * Created: 16-12-2021 12:28:34
 *  Author: rajkumark
 */ 

#include "Systick.h"

/*****************************************************************************************************
  FuncName	:  SYSTICK_INIT
  Parameter	:  None
  Brief		:  Sets the required settings for generating time in milliseconds using systick timer.
  RetVal	:  None
*****************************************************************************************************/
void SYSTICK_INIT()
{
	milliSec = 0;
	SysTick->CTRL = 0;                            // stop the timer
	SysTick->LOAD = (CONF_CPU_FREQUENCY / 1000) - 1;                    // gen int for every ms clock freq/1000 - 1
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = 0x00000007;                   // start the timer
	NVIC_EnableIRQ(SysTick_IRQn);                 // enable the interrupt IRQ
}

/*****************************************************************************************************
  FuncName	:  SysTick_Handler
  Parameter	:  None
  Brief		:  Callback for Systick timer.Calculates the milliseconds
  RetVal	:  None
*****************************************************************************************************/
void SysTick_Handler(void)
{
	milliSec++;
}

/*****************************************************************************************************
  FuncName	:  millis
  Parameter	:  None
  Brief		:  Provides the current time in milliseconds.
  RetVal	:  milliSec
*****************************************************************************************************/
uint32_t millis(void)
{
	return milliSec;
}

/*****************************************************************************************************
  FuncName	:  micros
  Parameter	:  None
  Brief		:  Provides the current time in micros.
  RetVal	:  Micros
*****************************************************************************************************/
uint32_t micros(void)
{
	//calculate the micro sec using VAL register and millis value
	uint32_t Micros = milliSec*1000 + 1000 - SysTick->VAL/48;  // where 48 represents clock frequency 48Mhz
	return Micros;
}