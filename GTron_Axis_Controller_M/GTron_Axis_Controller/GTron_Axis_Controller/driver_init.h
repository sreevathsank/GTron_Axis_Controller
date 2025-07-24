/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_adc_sync.h>

#include <hal_ext_irq.h>

#include <spi_lite.h>
#include <hal_usart_async.h>
#include <spi_lite.h>

#include <hal_usart_sync.h>
#include <hal_pwm.h>
#include <hpl_tc_base.h>
#include <hal_timer.h>
#include <hpl_tc_base.h>
#include <hal_timer.h>
#include <hpl_tc_base.h>
#include <hal_can_async.h>

extern struct adc_sync_descriptor    ADC_0;
extern struct usart_async_descriptor UART_0;

extern struct usart_sync_descriptor TARGET_IO;

extern struct pwm_descriptor       PWM_0;
extern struct timer_descriptor     VEL_TIMER;
extern struct timer_descriptor     TIMER_0;
extern struct can_async_descriptor CAN_1;

void ADC_0_PORT_init(void);
void ADC_0_CLOCK_init(void);
void ADC_0_init(void);

void   SPI_0_PORT_init(void);
void   SPI_0_CLOCK_init(void);
int8_t SPI_0_init(void);

void UART_0_PORT_init(void);
void UART_0_CLOCK_init(void);
void UART_0_init(void);

void   EXT_FLASH_SPI_PORT_init(void);
void   EXT_FLASH_SPI_CLOCK_init(void);
int8_t EXT_FLASH_SPI_init(void);

void TARGET_IO_PORT_init(void);
void TARGET_IO_CLOCK_init(void);
void TARGET_IO_init(void);

void PWM_0_PORT_init(void);
void PWM_0_CLOCK_init(void);
void PWM_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
