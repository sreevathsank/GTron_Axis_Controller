/*
 * Step_Counter.h
 *
 * Created: 14-08-2025 15:43:29
 *  Author: sreevathsank
 */ 


#ifndef STEP_COUNTER_H_
#define STEP_COUNTER_H_

#include "All_Headers.h"

#define READSYNC				0x04		
#define SYNCBUSY_COUNT_bit		4

typedef enum
{
	COUNT_UP	= 0,
	COUNT_DOWN	= 1	
}Count_Dir_t;

void index_Interrupt_Callback( void );


#endif /* STEP_COUNTER_H_ */