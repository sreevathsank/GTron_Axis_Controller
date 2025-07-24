/*
 * Systick.h
 *
 * Created: 16-12-2021 12:28:46
 *  Author: rajkumark
 */ 


#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <atmel_start.h>
#include "peripheral_clk_config.h"

void SYSTICK_INIT();
void SysTick_Handler(void);
uint32_t millis(void);
uint32_t micros(void);

volatile uint32_t milliSec;			// millisecond

#endif /* SYSTICK_H_ */