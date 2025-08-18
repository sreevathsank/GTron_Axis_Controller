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

#define VERSION_4671 0x34363731

struct io_descriptor *io;

struct io_descriptor *oi;

void led_Blink(uint32_t iteration, uint32_t time_taken);

void tx_cb_UART(const struct usart_async_descriptor *const io_descr);

void rx_cb_UART(const struct usart_async_descriptor *const io_descr);

void init_UART(void);

void enablePin_Led_Check(void);

bool check_4671_version_spi(void);

bool check_passive_flash_spi(void);

void timer_ramp_cb(void);

void init_timers(void);

void can_Rx_Cb(void);

void can_Init(void);

void define_All_Global_Variables(void);

void call_All_Init_Functions(void);

void run_Open_Loop_Setup_Closed_Loop(uint32_t time_taken);

void doEncoderDirectionCheck(void);

void reset_TMC4671(void);

void debounce_delay(uint32_t time_taken);

#endif /* DBG_BRING_UP_H_ */