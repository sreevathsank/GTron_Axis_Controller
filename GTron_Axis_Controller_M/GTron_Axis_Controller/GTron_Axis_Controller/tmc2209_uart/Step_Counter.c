/*
 * Step_Counter.c
 *
 * Created: 14-08-2025 15:43:14
 *  Author: sreevathsank
 */ 

#include "tmc2209_uart/Step_Counter.h"

void index_Interrupt_Callback( void )
{
	guide_step_counter_value = (guide_direction) 
							   ? guide_step_counter_value - 1
							   : guide_step_counter_value + 1;
	return;	
}