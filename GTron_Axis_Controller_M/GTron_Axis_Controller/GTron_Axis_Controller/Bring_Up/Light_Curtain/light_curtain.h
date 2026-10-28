/*
 * light_curtain.h
 *
 * Created: 27-10-2026 15:15:03
 *  Author: sreevathsank
 */ 


#ifndef LIGHT_CURTAIN_H_
#define LIGHT_CURTAIN_H_


#include "All_Headers.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

/* Macros */
#define LC_ADC_RD_LENGTH	2U
#define LC_READ_DELAY_MS	100U
#define LC_MIN_ADC_VAL		116U
#define LC_MAX_ADC_VAL		2864U
#define LC_ADC_MIDPOINT		(uint16_t)(((LC_MAX_ADC_VAL - LC_MIN_ADC_VAL) / 2) + LC_MIN_ADC_VAL)
#define LC_ADC_THRESHOLD	500U
#define LC_ADC_ERROR_WINDOW	5U

#if (LC_MIN_ADC_VAL > LC_MAX_ADC_VAL)
	#error "ERROR: LC_MIN_ADC_VAL > LC_MAX_ADC_VAL"
#endif

#if (LC_ADC_THRESHOLD > LC_MAX_ADC_VAL)
	#error "ERROR: LC_ADC_THRESHOLD > LC_MAX_ADC_VAL"
#endif

/* Variables and Typedefs */
typedef union {
	uint16_t val_16bit;
	uint8_t val_8bit[2];
}LC_ADC_Values_t;

typedef struct {
	LC_ADC_Values_t		adc;
	const uint16_t		min_threshold;
	const uint16_t		max_threshold;
	uint32_t			rd_time_ms;
	uint8_t				is_insp_run	: 1;	// Bit 0.
}Light_Curtain_t;

/* Function Protoypes */
uint16_t get_lc_adc_16bitVal(void);

uint32_t get_lc_rd_time(void);

void update_lc_rd_time_to_millis(void);

uint16_t get_light_curtain_adc_value(void);

void light_curtain_service(void);

#endif /* LIGHT_CURTAIN_H_ */