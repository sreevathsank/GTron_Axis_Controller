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

inline void counter_Count_Up(const void *const tc)
{
	hri_tc_clear_CTRLB_DIR_bit(tc);
}

inline void counter_Count_Down(const void *const tc)
{
	hri_tc_set_CTRLB_DIR_bit(tc);
}

void index_Interrupt_Callback( void );

void tmc2209_set_velocity(uint16_t icID, int32_t value, Tcc *tcc);

void counter_Clear_Count_Val(Tcc  *tcc);

void counter_Write_Count_Val(Tcc *tcc, uint32_t counter_val);

uint32_t counter_Read_Count_Val(Tcc *tcc);

#endif /* STEP_COUNTER_H_ */