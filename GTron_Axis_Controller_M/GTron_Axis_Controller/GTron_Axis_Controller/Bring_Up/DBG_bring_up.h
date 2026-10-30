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

#define ROTARY_SWITCH_1_MAX			298u
#define ROTARY_SWITCH_1_MIN			165u

#define ROTARY_SWITCH_2_MAX			554u
#define ROTARY_SWITCH_2_MIN			422u

#define ROTARY_SWITCH_3_MAX			812u
#define ROTARY_SWITCH_3_MIN			680u

#define ROTARY_SWITCH_4_MAX			1067u
#define ROTARY_SWITCH_4_MIN			936u

#define ROTARY_SWITCH_5_MAX			1325u
#define ROTARY_SWITCH_5_MIN			1194u

#define ROTARY_SWITCH_6_MAX			1582u
#define ROTARY_SWITCH_6_MIN			1452u

#define ROTARY_SWITCH_7_MAX			1840u
#define ROTARY_SWITCH_7_MIN			1708u

#define ROTARY_SWITCH_8_MAX			2082u
#define ROTARY_SWITCH_8_MIN			1950u

#define ROTARY_SWITCH_9_MAX			2340u
#define ROTARY_SWITCH_9_MIN			2208u

#define ROTARY_SWITCH_10_MAX		2597u
#define ROTARY_SWITCH_10_MIN		2466u

#define ROTARY_SWITCH_11_MAX		2854u
#define ROTARY_SWITCH_11_MIN		2722u

#define ROTARY_SWITCH_12_MAX		3109u
#define ROTARY_SWITCH_12_MIN		2978u

#define ROTARY_SWITCH_13_MAX		3367u
#define ROTARY_SWITCH_13_MIN		3236u

#define ROTARY_SWITCH_14_MAX		3624u
#define ROTARY_SWITCH_14_MIN		3492u

#define ROTARY_SWITCH_15_MAX		3881u
#define ROTARY_SWITCH_15_MIN		3750u

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