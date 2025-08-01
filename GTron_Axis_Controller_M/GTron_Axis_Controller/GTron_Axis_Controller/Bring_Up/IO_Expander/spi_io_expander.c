/*
 * spi_io_expander.c
 *
 * Created: 25-07-2025 14:56:30
 *  Author: sreevathsank
 */ 
#include "spi_io_expander.h"

void IOXP_transfer_block(void *wr_buf, void *rd_buf, uint8_t size)
{
	uint8_t *w = (uint8_t *)wr_buf;
	uint8_t *r = (uint8_t *)rd_buf;

	while (size--)
	{
		hri_sercomspi_write_DATA_reg(SERCOM3, *w);
		while (!(hri_sercomspi_read_INTFLAG_reg(SERCOM3) & SERCOM_SPI_INTFLAG_RXC));
		*r = hri_sercomspi_read_DATA_reg(SERCOM3);
		r++;
		w++;
	}
	return;
}

/**
 * Method for Transmitting to MCP23S08 IO Expander via SPI.
 *
 * @param uint8_t *wbuf					Write buffer.
 * @param uint8_t *rbuf					Read buffer.
 * @param uint16_t length				Length of bytes to transfer.
 *
 * @return bool
 */
bool IOXP_transfer(const uint8_t *wbuf, uint8_t *rbuf, const uint16_t length)
{
	// Pull SS low to communicate to device.
	gpio_set_pin_level(IOXP_CS, 0);
	delay_ms(1);
	// Set the Initial Return Value
	bool returnVal = false;

	IOXP_transfer_block(wbuf, rbuf, length);
	
	// Set the Return Value
	returnVal = true;
	delay_ms(1);
	// Pull SS high to stop communication.
	gpio_set_pin_level(IOXP_CS, 1);
	
	// Return the Function
	return returnVal;
}

/**
 * Write Data to MCP23S08's Register IO Expander via SPI.
 *
 * @param uint8_t byte_to_wr					Data to Write.
 *
 * @return void
 */
void IOXP_Write_Byte( IOXP_REGISTERS_t reg_addr, uint8_t byte_to_wr )
{
	if( (reg_addr > NO_OF_IOXP_REGISTERS) ) { return; }
	
	uint8_t wr_buf[3] = { (uint8_t)IOXP_DEV_OPCODE_WR, (uint8_t)reg_addr, byte_to_wr };
	uint8_t rd_buf[3];
	
	//#ifdef EXT_CS
	//	gpio_set_pin_level(EXT_CS, HIGH);
	//#endif
	
	IOXP_transfer(wr_buf, rd_buf, 3);
	
	PRINTF_DEBUG ? printf("\nIOXP SPI WR: Dev Opcode: 0x%x | Reg Addr: 0x%x | Byte to Write: 0x%x\n", 
							wr_buf[0], wr_buf[1], wr_buf[2]): 0;
	
	return;	
}

/**
 * Read Data to MCP23S08's Register IO Expander via SPI.
 *
 * @param IOXP_REGISTERS_t reg_addr Register Address to read the 1 byte data from.
 * @param uint8_t *addr_rd_data		Address of a uint8 variable Data from the Reg Addr.
 *
 * @return void
 */
void IOXP_Read_Byte( IOXP_REGISTERS_t reg_addr, uint8_t *addr_rd_data )
{
	if( (reg_addr > NO_OF_IOXP_REGISTERS) || (addr_rd_data == NULL) ) { return; }
	
	uint8_t wr_buf[3] = { IOXP_DEV_OPCODE_RD, (uint8_t)reg_addr, 0x00 };
	uint8_t rd_buf[3];
	
	//#ifdef EXT_CS
	//	gpio_set_pin_level(EXT_CS, HIGH);
	//#endif
	
	IOXP_transfer(wr_buf, rd_buf, 3);
	
	*addr_rd_data = rd_buf[2];
	
	PRINTF_DEBUG ? printf("\nIOXP SPI RD: Dev Opcode: 0x%x | Reg Addr: 0x%x | Read Byte: 0x%x 0x%x 0x%x\n",
							wr_buf[0], wr_buf[1], rd_buf[0], rd_buf[1], rd_buf[2]): 0;
	
	return;
}