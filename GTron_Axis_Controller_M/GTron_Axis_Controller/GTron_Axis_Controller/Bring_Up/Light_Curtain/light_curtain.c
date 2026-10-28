/*
 * light_curtain.c
 *
 * Created: 27-10-2026 15:14:46
 *  Author: sreevathsank
 */ 

#include "light_curtain.h"

static Light_Curtain_t lc_struct = {
	.min_threshold = LC_MIN_ADC_VAL + LC_ADC_THRESHOLD,
	.max_threshold = LC_MAX_ADC_VAL - LC_ADC_THRESHOLD,
};

uint16_t get_lc_adc_16bitVal(void)
{
	return lc_struct.adc.val_16bit;
}

uint32_t get_lc_rd_time(void)
{
	return lc_struct.rd_time_ms;
}

void update_lc_rd_time_to_millis(void)
{
	lc_struct.rd_time_ms = millis();
}

uint16_t get_light_curtain_adc_value(void)
{
	set_adc_channel(LIGHT_CURTAIN_SAG_ADC);
	adc_sync_read_channel(&ADC_0, ADC_CHANNEL, lc_struct.adc.val_8bit, LC_ADC_RD_LENGTH);
	//DBG_Printf(ERR_LVL_INFO, "ADC = %d\n", lc_struct.adc.val_16bit);
	return lc_struct.adc.val_16bit;
}

void light_curtain_service(void)
{
	static bool max_exe_last = false;
	static bool min_exe_last = false;
	(void)get_light_curtain_adc_value();
	if ((lc_struct.adc.val_16bit <= lc_struct.min_threshold) && !min_exe_last) {
		min_exe_last						= true;
		max_exe_last						= false;
		lc_struct.is_insp_run				= true;
		p_reeler1_info->flags.sag_enabled	= true;
		if(p_reeler1_info->flags.sag_enabled & p_reeler1_info->flags.rotate_vel_mode) {
			trig_no = 0;
			prev_trig_no = 0;
			timer_start(&VEL_TIMER);
			tmc4671_setVelocityLimit(MOTOR, p_reeler1_info->velocity.limit);
			tmc4671_setVelocityTarget(MOTOR, p_reeler1_info->velocity.limit);
			DBG_Printf(ERR_LVL_INFO, "Light_Curtain_Service: ADC -> Current = %d | Threshold = %d | Reeler Start with velocity = %ld rpm\n",
			lc_struct.min_threshold, lc_struct.adc.val_16bit, p_reeler1_info->velocity.limit);
			// Send Sag ON CAN reply or something.
		}
	} else if ((lc_struct.adc.val_16bit >= lc_struct.max_threshold) && !max_exe_last) {
		max_exe_last						= true;
		min_exe_last						= false;
		lc_struct.is_insp_run				= false;
		p_reeler1_info->flags.sag_enabled	= false;
		reeler_Sag_Pause_Motor();
		DBG_Printf(ERR_LVL_INFO, "light_curtain_service: ADC -> Current = %d | Threshold = %d | Reeler Stop\n",
		lc_struct.max_threshold, lc_struct.adc.val_16bit);
		// Send Sag OFF CAN reply or something.
	}
	
	return;
}