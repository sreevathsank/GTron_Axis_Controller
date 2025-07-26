/*
 * spi_io_expander.h
 *
 * Created: 25-07-2025 14:56:50
 *  Author: sreevathsank
 */ 


#ifndef SPI_IO_EXPANDER_H_
#define SPI_IO_EXPANDER_H_

#include "All_Headers.h"

typedef enum
{
	IOXP_REG_IODIR = 0,
	IOXP_REG_IPOL = 1,
	IOXP_REG_GPINTEN = 2,
	IOXP_REG_DEFVAL = 3,
	IOXP_REG_INTCON = 4,
	IOXP_REG_IOCON = 5,
	IOXP_REG_GPPU = 6,
	IOXP_REG_INTF = 7,
	IOXP_REG_INTCAP_RD_ONLY = 8,
	IOXP_REG_GPIO = 9,
	IOXP_REG_OLAT = 10,
	NO_OF_IOXP_REGISTERS
}IOXP_REGISTERS_t;

#define IOXP_READ_BIT		0x01			// Bit 0: 1 => Read Operation.
#define IOXP_WRITE_BIT		0x00			// Bit 0: 0 => Write Operation.

#define IOXP_DEV_ADDR		0x00			// A0 => 0 , A1 => 0.

#define IOXP_NIBBLE			(1UL << 6)		// The Sync Nibble.

#define IOXP_DEV_OPCODE_RD	( IOXP_NIBBLE | IOXP_DEV_ADDR | IOXP_READ_BIT )

#define IOXP_DEV_OPCODE_WR	( IOXP_NIBBLE | IOXP_DEV_ADDR | IOXP_WRITE_BIT ) 


void IOXP_Write_Byte( IOXP_REGISTERS_t reg_addr, uint8_t byte_to_wr );

void IOXP_Read_Byte( IOXP_REGISTERS_t reg_addr, uint8_t *addr_rd_data );

#endif /* SPI_IO_EXPANDER_H_ */