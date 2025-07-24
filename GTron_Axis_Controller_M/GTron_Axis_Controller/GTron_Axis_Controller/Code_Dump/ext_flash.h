#ifndef EXT_FLASH_H_
#define EXT_FLASH_H_

// Include STD C Libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Include Files for Driver Initialisation
#include "driver_init.h"
#include <hpl/spi/spi_lite.h>
//#include <hal_spi_m_async.h>
//#include "All_Headers.h"
#include "string.h"
#include "tlv_flash.h"

//struct spi_m_async_descriptor SERIALFLASH;

// Instruction Codes
#define FLASH_CMD_MDID					0x9F	// Manufacturer Device ID.
#define FLASH_CMD_READ_STATUS			0x05	// Read Status Register.
#define FLASH_CMD_PROGRAM				0x02	// Page Program.
#define FLASH_CMD_READ					0x03	// Read Data.
#define FLASH_CMD_WRITE_ENABLE			0x06	// Write Enable.
#define FLASH_CMD_WRITE_DISABLE			0x04	// Write Disable.
#define FLASH_CMD_SECTOR_ERASE			0x20	// Sector Erase.
#define FLASH_CMD_BLOCK_SECTOR_LOCK		0x36	// Locks Block/Sector.
#define FLASH_CMD_BLOCK_SECTOR_UNLOCK	0x39	// Unlocks Block/Sector.

// Bitmask of the Status Register
#define FLASH_STATUS_BIT_BUSY			0x1		// Busy Bit of Status Register.
	
// Part Specific Constants	
#define FLASH_PROGRAM_PAGE_SIZE			0x100	// 256 bytes.
#define FLASH_ERASE_SECTOR_SIZE			0x1000	// 4096 bytes.
#define FLASH_MAX_COMMAND_SIZE			0x5		// Allow 5 bytes for a command.

// Manufacturer DID
#define MF_ADESTO					0x1F

// Structure for the Memory Device
typedef struct
{
	uint32_t deviceSize;
	uint8_t manuID;
	uint8_t devID;
} extFlashInfo_t;

// IO Descriptor for EXTFLASH SPI Comms
struct io_descriptor *extflash_io;

// Function for Initialising SPI on ExtFlash
void EXTFLASH_init(void);

// ExtFlash Methods

extern void SPI_0_transfer_block(void *wr_buf, void *rd_buf, uint8_t size);
extern void Ext_Flash_transfer_block(void *wr_buf, void *rd_buf, uint8_t size);

extern void EXTFLASH_setup(void);
extern bool EXTFLASH_open(void);
extern bool EXTFLASH_read(size_t offset, size_t length, uint8_t *buf);
extern bool EXTFLASH_write(size_t offset, size_t length, const uint8_t *buf);
extern bool EXTFLASH_erase(size_t offset, size_t length);
extern bool EXTFLASH_readInfo(void);
extern bool EXTFLASH_transfer(const uint8_t *wbuf, uint8_t *rbuf, const uint16_t length);
#endif