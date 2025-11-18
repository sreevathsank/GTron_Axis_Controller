/*
 * TMC2209_Motion.c
 *
 * Created: 04-08-2025 16:18:53
 *  Author: sreevathsank
 */ 

#include "Bring_Up/IO_Expander/spi_io_expander.h"

/** 
 * \brief config_IOXP => Sets the initial values to the MCP23S08 registers for Guide and Vertical Arrestor Limits.
 *
 * @param void
 * @return void
 **/
void config_IOXP( void )
{
	IOXP_Write_Byte(IOXP_REG_IOCON, 0x08);	// 0b00001000 | Hardware Address Enable (HAEN) is enabled.
	IOXP_Write_Byte(IOXP_REG_IODIR, 0x30);	// 0b00110000 | IO4 and IO5 pins are set as Input.
	return;
}