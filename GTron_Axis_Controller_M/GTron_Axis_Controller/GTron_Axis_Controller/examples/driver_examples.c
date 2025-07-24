/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
}

static void button_on_PA17_pressed(void)
{
}

static void button_on_PA18_pressed(void)
{
}

static void button_on_PA19_pressed(void)
{
}

static void button_on_PC16_pressed(void)
{
}

static void button_on_PC17_pressed(void)
{
}

static void button_on_PC18_pressed(void)
{
}

static void button_on_PC20_pressed(void)
{
}

static void button_on_PC21_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PA17, button_on_PA17_pressed);
	ext_irq_register(PIN_PA18, button_on_PA18_pressed);
	ext_irq_register(PIN_PA19, button_on_PA19_pressed);
	ext_irq_register(PIN_PC16, button_on_PC16_pressed);
	ext_irq_register(PIN_PC17, button_on_PC17_pressed);
	ext_irq_register(PIN_PC18, button_on_PC18_pressed);
	ext_irq_register(PIN_PC20, button_on_PC20_pressed);
	ext_irq_register(PIN_PC21, button_on_PC21_pressed);
}

/**
 * Example of using SPI_0 to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_0[12] = "Hello World!";

void SPI_0_example(void)
{
	SPI_0_write_block((void *)example_SPI_0, 12);
}

/**
 * Example of using UART_0 to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_UART_0[12] = "Hello World!";

static void tx_cb_UART_0(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void UART_0_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&UART_0, USART_ASYNC_TXC_CB, tx_cb_UART_0);
	/*usart_async_register_callback(&UART_0, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&UART_0, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&UART_0, &io);
	usart_async_enable(&UART_0);

	io_write(io, example_UART_0, 12);
}

/**
 * Example of using EXT_FLASH_SPI to write "Hello World" using the IO abstraction.
 */
static uint8_t example_EXT_FLASH_SPI[12] = "Hello World!";

void EXT_FLASH_SPI_example(void)
{
	EXT_FLASH_SPI_write_block((void *)example_EXT_FLASH_SPI, 12);
}

/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 */
void TARGET_IO_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_set_parameters(&PWM_0, 10000, 5000);
	pwm_enable(&PWM_0);
}

static struct timer_task VEL_TIMER_task1, VEL_TIMER_task2;

/**
 * Example of using VEL_TIMER.
 */
static void VEL_TIMER_task1_cb(const struct timer_task *const timer_task)
{
}

static void VEL_TIMER_task2_cb(const struct timer_task *const timer_task)
{
}

void VEL_TIMER_example(void)
{
	VEL_TIMER_task1.interval = 100;
	VEL_TIMER_task1.cb       = VEL_TIMER_task1_cb;
	VEL_TIMER_task1.mode     = TIMER_TASK_REPEAT;
	VEL_TIMER_task2.interval = 200;
	VEL_TIMER_task2.cb       = VEL_TIMER_task2_cb;
	VEL_TIMER_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&VEL_TIMER, &VEL_TIMER_task1);
	timer_add_task(&VEL_TIMER, &VEL_TIMER_task2);
	timer_start(&VEL_TIMER);
}

static struct timer_task TIMER_0_task1, TIMER_0_task2;

/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

void CAN_1_tx_callback(struct can_async_descriptor *const descr)
{
	(void)descr;
}
void CAN_1_rx_callback(struct can_async_descriptor *const descr)
{
	struct can_message msg;
	uint8_t            data[64];
	msg.data = data;
	can_async_read(descr, &msg);
	return;
}

/**
 * Example of using CAN_1 to Encrypt/Decrypt datas.
 */
void CAN_1_example(void)
{
	struct can_message msg;
	struct can_filter  filter;
	uint8_t            send_data[4];
	send_data[0] = 0x00;
	send_data[1] = 0x01;
	send_data[2] = 0x02;
	send_data[3] = 0x03;

	msg.id   = 0x45A;
	msg.type = CAN_TYPE_DATA;
	msg.data = send_data;
	msg.len  = 4;
	msg.fmt  = CAN_FMT_STDID;
	can_async_register_callback(&CAN_1, CAN_ASYNC_TX_CB, (FUNC_PTR)CAN_1_tx_callback);
	can_async_enable(&CAN_1);

	/**
	 * CAN_1_tx_callback callback should be invoked after call
	 * can_async_write, and remote device should recieve message with ID=0x45A
	 */
	can_async_write(&CAN_1, &msg);

	msg.id  = 0x100000A5;
	msg.fmt = CAN_FMT_EXTID;
	/**
	 * remote device should recieve message with ID=0x100000A5
	 */
	can_async_write(&CAN_1, &msg);

	/**
	 * CAN_1_rx_callback callback should be invoked after call
	 * can_async_set_filter and remote device send CAN Message with the same
	 * content as the filter.
	 */
	can_async_register_callback(&CAN_1, CAN_ASYNC_RX_CB, (FUNC_PTR)CAN_1_rx_callback);
	filter.id   = 0x469;
	filter.mask = 0;
	can_async_set_filter(&CAN_1, 0, CAN_FMT_STDID, &filter);

	filter.id   = 0x10000096;
	filter.mask = 0;
	can_async_set_filter(&CAN_1, 1, CAN_FMT_EXTID, &filter);
}
