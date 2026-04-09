/*
 * Hybrid_Trigger.c
 *
 * Created: 07-04-2026 12:10:50
 *  Author: sreevathsank
 */ 
#include "Hybrid_Trigger.h"

volatile int32_t prev_trig_pos = 0;
volatile uint32_t prev_trig_time_ms = 0;

/** 
 * \brief	Triggers the pin that is directly connected to Sys Ctrl to trigger the Camera.
 *
 * @param	void
 * @return	void
 **/
static void trigger_Camera_Line(void) 
{
	gpio_set_pin_level(REELER_INT, HIGH);
	delay_us(1);
	gpio_toggle_pin_level(DBGLED3);
	gpio_set_pin_level(REELER_INT, LOW);
	return;
}

/** 
 * \brief	The function that checks motor position wrt to sensor trigger flag received from EIC whether to trigger camera or not.
 *
 * @param	void
 * @return	void
 **/
void check_For_Hybrid_Trigger(void)
{
	int32_t current_pos = tmc4671_getActualPosition(MOTOR);
	uint32_t diff_pos = abs(prev_trig_pos - current_position);
	
	if(p_reeler_info->flags.sensor_trigger && (diff_pos >= p_reeler_info->position.trig_step_size) ) {
		trigger_Camera_Line();
		p_reeler_info->flags.sensor_trigger = false;
		prev_trig_time_ms = millis();
		
		PRINTF_DEBUG?printf("\nT%ld => Step Size = %ld | Curr - Prev Pos = %ld | Error = %ld\n", ++trig_no, p_reeler_info->position.trig_step_size, diff_pos,
		(diff_pos - p_reeler_info->position.trig_step_size)):0;
		
		prev_trig_pos = current_position;
	}
	return;
}