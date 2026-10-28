/*
 * DBG_bring_up.h
 *
 * Created: 15-12-2023 16:41:20
 *  Author: sreevathsank
 */ 


#ifndef DBG_BRING_UP_H_
#define DBG_BRING_UP_H_

#include "All_Headers.h"
#include "Bring_Up/IO_Expander/spi_io_expander.h"
#include "Bring_Up/Light_Curtain/light_curtain.h"

#define VERSION_4671 0x34363731

/* ADC Related MACROS */
#define ADC_POS_AIN0		0x00
#define ADC_POS_AIN9		0x09
#define ADC_NEG_GND			0x18
#define ADC_RD_LENGTH		1u

typedef enum {
	ROTARY_SWITCH_ADC		= 0,
	LIGHT_CURTAIN_SAG_ADC	= 1		
}ADC_Channel_Type_t;

/* Address determination from Rotary Switch */
#define ROTARY_SWITCH_0_MAX			0u
#define ROTARY_SWITCH_0_MIN			0u

#define ROTARY_SWITCH_1_MAX			234u
#define ROTARY_SWITCH_1_MIN			229u

#define ROTARY_SWITCH_2_MAX			490u
#define ROTARY_SWITCH_2_MIN			486u

#define ROTARY_SWITCH_3_MAX			748u
#define ROTARY_SWITCH_3_MIN			744u

#define ROTARY_SWITCH_4_MAX			1003u
#define ROTARY_SWITCH_4_MIN			1000u

#define ROTARY_SWITCH_5_MAX			1261u
#define ROTARY_SWITCH_5_MIN			1258u

#define ROTARY_SWITCH_6_MAX			1518u
#define ROTARY_SWITCH_6_MIN			1516u

#define ROTARY_SWITCH_7_MAX			1776u
#define ROTARY_SWITCH_7_MIN			1772u

#define ROTARY_SWITCH_8_MAX			2018u
#define ROTARY_SWITCH_8_MIN			2014u

#define ROTARY_SWITCH_9_MAX			2276u
#define ROTARY_SWITCH_9_MIN			2272u

#define ROTARY_SWITCH_10_MAX		2533u
#define ROTARY_SWITCH_10_MIN		2530u

#define ROTARY_SWITCH_11_MAX		2790u
#define ROTARY_SWITCH_11_MIN		2786u

#define ROTARY_SWITCH_12_MAX		3045u
#define ROTARY_SWITCH_12_MIN		3042u

#define ROTARY_SWITCH_13_MAX		3303u
#define ROTARY_SWITCH_13_MIN		3300u

#define ROTARY_SWITCH_14_MAX		3560u
#define ROTARY_SWITCH_14_MIN		3556u

#define ROTARY_SWITCH_15_MAX		3817u
#define ROTARY_SWITCH_15_MIN		3814u

typedef struct {
	uint16_t	adc_min;
	uint16_t	adc_max;
	uint8_t 	position;
}RotarySwitchRange_t;


struct io_descriptor *io;

struct io_descriptor *oi;

void led_Blink(uint32_t iteration, uint32_t time_taken);

void tx_cb_UART(const struct usart_async_descriptor *const io_descr);

void rx_cb_UART(const struct usart_async_descriptor *const io_descr);

void init_UART(void);

void enablePin_Led_Check(void);

bool check_4671_version_spi(void);

bool check_passive_flash_spi(void);

void init_timers(void);

void init_wdt(void);

void pet_wdt(void);

void can_Rx_Cb(void);

void can_Init(void);

void define_All_Global_Variables(void);

void set_adc_channel(ADC_Channel_Type_t adc_peripheral);

void call_All_Init_Functions(void);

void run_Open_Loop_Setup_Closed_Loop(uint32_t time_taken);

void doEncoderDirectionCheck(void);

void reset_TMC4671(void);

void debounce_delay(uint32_t time_taken);

#endif /* DBG_BRING_UP_H_ */