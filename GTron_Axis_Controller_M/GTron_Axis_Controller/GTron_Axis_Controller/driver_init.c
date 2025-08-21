/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

#include <hpl_adc_base.h>

/*! The buffer size for USART */
#define UART_0_BUFFER_SIZE 16

struct usart_async_descriptor UART_0;
struct timer_descriptor       VEL_TIMER;
struct timer_descriptor       TIMER_0;
struct can_async_descriptor   CAN_1;

static uint8_t UART_0_buffer[UART_0_BUFFER_SIZE];

struct adc_sync_descriptor ADC_0;

struct usart_sync_descriptor TARGET_IO;

struct pwm_descriptor PWM_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(DVC_ADDR, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(DVC_ADDR, PINMUX_PC01B_ADC0_AIN9);
}

void ADC_0_CLOCK_init(void)
{
	hri_mclk_set_APBCMASK_ADC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC0_GCLK_ID, CONF_GCLK_ADC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC0, _adc_get_adc_sync());
}

void EXTERNAL_IRQ_0_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, EIC_GCLK_ID, CONF_GCLK_EIC_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBAMASK_EIC_bit(MCLK);

	// Set pin direction to input
	gpio_set_pin_direction(LINENC_DIR, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(LINENC_DIR,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(LINENC_DIR, PINMUX_PA17A_EIC_EXTINT1);

	// Set pin direction to input
	gpio_set_pin_direction(LINENC_Z, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(LINENC_Z,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(LINENC_Z, PINMUX_PA18A_EIC_EXTINT2);

	// Set pin direction to input
	gpio_set_pin_direction(ROTENC_COUNT, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(ROTENC_COUNT,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(ROTENC_COUNT, PINMUX_PA19A_EIC_EXTINT3);

	// Set pin direction to input
	gpio_set_pin_direction(IOXP_INT, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(IOXP_INT,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(IOXP_INT, PINMUX_PB21A_EIC_EXTINT5);

	// Set pin direction to input
	gpio_set_pin_direction(ROTENC_DIR, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(ROTENC_DIR,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(ROTENC_DIR, PINMUX_PC16A_EIC_EXTINT8);

	// Set pin direction to input
	gpio_set_pin_direction(ROTENC_Z, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(ROTENC_Z,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(ROTENC_Z, PINMUX_PC17A_EIC_EXTINT9);

	// Set pin direction to input
	gpio_set_pin_direction(LIM_RT, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(LIM_RT,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(LIM_RT, PINMUX_PC18A_EIC_EXTINT10);

	// Set pin direction to input
	gpio_set_pin_direction(LIM_LFT, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(LIM_LFT,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(LIM_LFT, PINMUX_PC20A_EIC_EXTINT12);

	// Set pin direction to input
	gpio_set_pin_direction(DIAG, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DIAG,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DIAG, PINMUX_PC21A_EIC_EXTINT13);

	// Set pin direction to input
	gpio_set_pin_direction(INDEX, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(INDEX,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(INDEX, PINMUX_PB30A_EIC_EXTINT14);

	ext_irq_init();
}

void SPI_0_PORT_init(void)
{

	gpio_set_pin_level(SPI0_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SPI0_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SPI0_MOSI, PINMUX_PA04D_SERCOM0_PAD0);

	gpio_set_pin_level(SPI0_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SPI0_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SPI0_SCK, PINMUX_PA05D_SERCOM0_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(SPI0_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(SPI0_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(SPI0_MISO, PINMUX_PA06D_SERCOM0_PAD2);
}

void SPI_0_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBCMASK_SERCOM0_bit(MCLK);
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void UART_0_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBCMASK_SERCOM1_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void UART_0_PORT_init()
{

	gpio_set_pin_function(PA00, PINMUX_PA00D_SERCOM1_PAD0);

	gpio_set_pin_function(PA01, PINMUX_PA01D_SERCOM1_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void UART_0_init(void)
{
	UART_0_CLOCK_init();
	usart_async_init(&UART_0, SERCOM1, UART_0_buffer, UART_0_BUFFER_SIZE, (void *)NULL);
	UART_0_PORT_init();
}

void EXT_FLASH_SPI_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(EXT_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(EXT_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(EXT_MISO, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_level(EXT_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(EXT_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EXT_SCK, PINMUX_PA23C_SERCOM3_PAD1);

	gpio_set_pin_level(EXT_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(EXT_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EXT_MOSI, PINMUX_PA25C_SERCOM3_PAD3);
}

void EXT_FLASH_SPI_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM3_GCLK_ID_CORE, CONF_GCLK_SERCOM3_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM3_GCLK_ID_SLOW, CONF_GCLK_SERCOM3_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBCMASK_SERCOM3_bit(MCLK);
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void TMC2209_UART_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_SLOW, CONF_GCLK_SERCOM5_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBCMASK_SERCOM5_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void TMC2209_UART_PORT_init()
{

	gpio_set_pin_function(TMC2209_UART_TX, PINMUX_PB16C_SERCOM5_PAD0);

	gpio_set_pin_function(PB17, PINMUX_PB17C_SERCOM5_PAD1);
}

void TARGET_IO_PORT_init(void)
{

	gpio_set_pin_function(PC12, PINMUX_PC12C_SERCOM7_PAD0);

	gpio_set_pin_function(PC15, PINMUX_PC15C_SERCOM7_PAD3);
}

void TARGET_IO_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM7_GCLK_ID_CORE, CONF_GCLK_SERCOM7_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM7_GCLK_ID_SLOW, CONF_GCLK_SERCOM7_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBDMASK_SERCOM7_bit(MCLK);
}

void TARGET_IO_init(void)
{
	TARGET_IO_CLOCK_init();
	usart_sync_init(&TARGET_IO, SERCOM7, (void *)NULL);
	TARGET_IO_PORT_init();
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(CLK25M, PINMUX_PA10E_TC1_WO0);
}

void PWM_0_CLOCK_init(void)
{

	hri_mclk_set_APBCMASK_TC1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC1_GCLK_ID, CONF_GCLK_TC1_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, TC1, _tc_get_pwm());
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void VEL_TIMER_init(void)
{

	hri_mclk_set_APBCMASK_TC2_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC2_GCLK_ID, CONF_GCLK_TC2_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	timer_init(&VEL_TIMER, TC2, _tc_get_timer());
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{

	hri_mclk_set_APBCMASK_TC4_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC4_GCLK_ID, CONF_GCLK_TC4_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	timer_init(&TIMER_0, TC4, _tc_get_timer());
}

void CAN_1_PORT_init(void)
{

	gpio_set_pin_function(CAN_RX, PINMUX_PB15G_CAN1_RX);

	gpio_set_pin_function(CAN_TX, PINMUX_PB14G_CAN1_TX);
}
/**
 * \brief CAN initialization function
 *
 * Enables CAN peripheral, clocks and initializes CAN driver
 */
void CAN_1_init(void)
{
	hri_mclk_set_AHBMASK_CAN1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, CAN1_GCLK_ID, CONF_GCLK_CAN1_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	can_async_init(&CAN_1, CAN1);
	CAN_1_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA03

	gpio_set_pin_level(IOXP_CS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(IOXP_CS, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(IOXP_CS, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA07

	gpio_set_pin_level(nCS_4671,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(nCS_4671, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(nCS_4671, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA09

	gpio_set_pin_level(DBGLED1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(DBGLED1, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(DBGLED1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA14

	gpio_set_pin_level(DBGLED3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(DBGLED3, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(DBGLED3, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA15

	gpio_set_pin_level(DBGLED2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(DBGLED2, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(DBGLED2, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB07

	gpio_set_pin_level(FLASH_SPI_nCS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(FLASH_SPI_nCS, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(FLASH_SPI_nCS, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB08

	gpio_set_pin_level(EN_4671,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(EN_4671, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EN_4671, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB09

	gpio_set_pin_level(RST_4671,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(RST_4671, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(RST_4671, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB10

	gpio_set_pin_level(SWITCH_EN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SWITCH_EN, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SWITCH_EN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB11

	// Set pin direction to input
	gpio_set_pin_direction(FPGA_CDONE, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(FPGA_CDONE,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(FPGA_CDONE, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB12

	gpio_set_pin_level(FPGA_CRESET_B,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(FPGA_CRESET_B, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(FPGA_CRESET_B, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB19

	gpio_set_pin_level(INDEX_SEL,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(INDEX_SEL, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(INDEX_SEL, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB20

	gpio_set_pin_level(EXT_CS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(EXT_CS, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(EXT_CS, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB23

	gpio_set_pin_level(REELER_INT,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(REELER_INT, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(REELER_INT, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();

	EXTERNAL_IRQ_0_init();

	SPI_0_CLOCK_init();
	SPI_0_init();
	SPI_0_PORT_init();
	UART_0_init();

	EXT_FLASH_SPI_CLOCK_init();
	EXT_FLASH_SPI_init();
	EXT_FLASH_SPI_PORT_init();

	TMC2209_UART_CLOCK_init();
	TMC2209_UART_init();
	TMC2209_UART_PORT_init();

	TARGET_IO_init();

	PWM_0_init();

	VEL_TIMER_init();
	TIMER_0_init();
	CAN_1_init();
}
