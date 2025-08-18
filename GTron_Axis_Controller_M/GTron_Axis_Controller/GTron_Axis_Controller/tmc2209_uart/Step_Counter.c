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

void tmc2209_set_velocity(uint16_t icID, int32_t velocity, Tcc *tcc)
{
	// If velocity is -ve, Set DIR bit to 1 to Count Down. Else Count Up.
	(velocity < 0) ? hri_tcc_write_CTRLB_DIR_bit(tcc, (bool)COUNT_DOWN)
				   : hri_tcc_write_CTRLB_DIR_bit(tcc, (bool)COUNT_UP);	
	guide_direction = (velocity < 0) ? 0 : 1;
	tmc2209_writeRegister(icID, TMC2209_VACTUAL, velocity);
	return;
}

void counter_Clear_Count_Val(Tcc  *tcc)
{
	hri_tcc_clear_COUNT_COUNT_bf(tcc, TCC_COUNT_COUNT_Msk);
	return;
}

void counter_Write_Count_Val(Tcc *tcc, uint32_t counter_val)
{
	hri_tcc_write_COUNT_COUNT_bf(tcc, counter_val);
	return;
}

uint32_t counter_Read_Count_Val(Tcc *tcc)
{
	// Write 0x04 READSYNC value to CTRLBSET.CMD register.
	hri_tcc_write_CTRLB_CMD_bf(tcc, READSYNC); //hri_tc_write_CTRLB_CMD_bf(tc, READSYNC);
	
	// Wait till CTRLB_CMD reads back 0x00...
	while(hri_tcc_read_CTRLB_CMD_bf(tcc)); //while(hri_tc_read_CTRLB_CMD_bf(tc));
	
	// Wait for SYNCBUSY.COUNT register to clear / read 0x00...
	//while(hri_tc_get_SYNCBUSY_COUNT_bit(tc));
	
	//Now, we can read the COUNT register.
	return hri_tcc_read_COUNT_COUNT_bf(tcc); //return tc->COUNT16.COUNT.bit.COUNT;
}