// Include EXT Flash Header File
#include "ext_flash.h"
#include <stdio.h>
#include <stddef.h>

struct io_descriptor *extflash_io;

void SPI_0_transfer_block(void *wr_buf, void *rd_buf, uint8_t size)
{
    //printf("\nTMC4671 SPI Transfer Block SPI is busy before transaction.\n");
    //while(SERCOM0_SPI_IsBusy());
    SERCOM0_SPI_WriteRead((void *)wr_buf, size, rd_buf, size);
    //printf("\nTMC4671 SPI Transfer Block SPI is busy after transaction \n" );
    //while(SERCOM0_SPI_IsBusy());
        //uint8_t *w = (uint8_t *)wr_buf;
        //uint8_t *r = (uint8_t *)rd_buf;
        //
        //while (size--)
        //{
        //	hri_sercomspi_write_DATA_reg(SERCOM0, *w);
        //	while (!(hri_sercomspi_read_INTFLAG_reg(SERCOM0) & SERCOM_SPI_INTFLAG_RXC));
        //	*r = huint8_t *w = (uint8_t *)wr_buf;ri_sercomspi_read_DATA_reg(SERCOM0);
        //	r++;
        //	w++;
        //}
}

void Ext_Flash_transfer_block(void *wr_buf, void *rd_buf, size_t size)
{
    SERCOM3_SPI_WriteRead((void *)wr_buf, size, rd_buf, size);
    //uint8_t *w = (uint8_t *)wr_buf;
    //uint8_t *r = (uint8_t *)rd_buf;
      
    //uint8_t *w = (uint8_t *)wr_buf;/while (size--)
    //{
    //	//hri_sercomspi_write_DATA_reg(SERCOM3, *w);
    //	//while (!(hri_sercomspi_read_INTFLAG_reg(SERCOM3) & SERCOM_SPI_INTFLAG_RXC));
    //	//*r = hri_sercomspi_read_DATA_reg(SERCOM3);
    //	r++;
    //	w++;
    //}

}

// Supported Flash Devices
static const extFlashInfo_t flashInfo[] =
{

    {
        .manuID = MF_ADESTO,		// Adesto
        .devID = 0x01,				// Device ID
        .deviceSize = 0x100000		// 1Mbyte (8Mbit)
    },
       
    {
        .manuID = 0xEF,             // W25Q64FV
        .devID = 0x17,
        .deviceSize = 0x800000		// 8Mbyte (64 Mbit)
    },
       
    {
        .manuID = 0xEE,             // idk
        .devID = 0x18,
        .deviceSize = 0x800000
    },

    {
        .manuID = 0x20,             // ICE_Stick 
        .devID = 0x16,
        .deviceSize = 0x800000
    },

    {
        .manuID = 0xC2,	            // For FOC board #001
        .devID = 0x12,
        .deviceSize = 0x800000
    },

    {
        .manuID = 0xC2,	            // For FOC board #001
        .devID = 0x11,
        .deviceSize = 0x800000
    }

};

// Flash Information
static const extFlashInfo_t *pFlashInfo = NULL;
static uint8_t infoBuf[2];
static uint8_t rxBuff[FLASH_PROGRAM_PAGE_SIZE + FLASH_MAX_COMMAND_SIZE];

/**
 * Callback fucntion for SPI transfer completed on EXTFLASH SPI.
 *
 * @param spi_m_async_descriptor		IO descriptor for SPI object.
 *
 * @return void
 */
//static void SPI_EXTFLASH_complete_cb(const struct spi_m_async_descriptor *const io_descr)
//{
	/* Transfer Completed */
//}

/**
 * Method for initializing SPI on the EXTFLASH pins.
 *
 * @return void
 */
void EXTFLASH_init()
{	
    return;
}

/**
 * Method for Transmitting to EXTFLASH via SPI.
 *
 * @param uint8_t *wbuf					Write buffer.
 * @param uint8_t *rbuf					Read buffer.
 * @param uint16_t length				Length of bytes to transfer.
 *
 * @return bool
 */
bool EXTFLASH_transfer(const uint8_t *wbuf, uint8_t *rbuf, const uint16_t length)
{
    // Set the Initial Return Value
    bool returnVal = false;

    // Pull SS low to communicate to device.
    //gpio_set_pin_level(FLASH_SPI_nCS, 0);
    //gpio_set_pin_level(EXT_CS, 0);
    FLASH_CS_Clear();

    // Perform ASYNC Transfer (send and receive)
    Ext_Flash_transfer_block((void *)wbuf, rbuf, length);

    // Set the Return Value
    returnVal = true;

    // Pull SS high to stop communication.
    //gpio_set_pin_level(FLASH_SPI_nCS, 1);
    //gpio_set_pin_level(EXT_CS, 1);
    FLASH_CS_Set();
    // Return the Function
    return returnVal;

}

/**
 * Reads the flash information (manufacturer and device ID) from the device.
 *
 * @return bool
 */
 bool EXTFLASH_readInfo(void)
{
    // Create the Command Message
    const uint8_t wbuf[] = { FLASH_CMD_MDID, 0x00, 0x00, 0x00 };
    //const uint8_t wbuf[] = { 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool returnVal = false;

    // Send the Command
    if (EXTFLASH_transfer(wbuf, rxBuff, 4))
    {
        // Copy Vendor and Device Data into the Info Buffer
        infoBuf[0] = rxBuff[1];
        infoBuf[1] = rxBuff[3];
        
        //printf("\n");
        //for(int32_t i = 0; i < 4; i++) { printf("rx[%ld] -> 0x%x | ", i, rxBuff[i]); }
        //printf("\n");
        
        // Return True
        returnVal = true;
    }

    // Return the Function
    return returnVal;

}

/**
 * Verify that the flash component is valid.
 *
 * @return bool
 */
static bool _extFlashVerifyPart(void)
{
    // Check that we can read the info in
    if (!EXTFLASH_readInfo())
    {
        return false;
    }

    // Point pFlashInfo to FlashInfo Array
    pFlashInfo = flashInfo;
    bool id_chk = false;
    
    // Loop and Compare
    for(int32_t i = 0; i < FLASH_INFO_COUNT; i++)
    {
        if (infoBuf[0] == pFlashInfo->manuID && infoBuf[1] == pFlashInfo->devID)
        {
            id_chk = true;
            break;
        }
        pFlashInfo++;
    }

    // Return whether we found a matching device
    return id_chk;

}

/**
 * Read the status register of the flash device.
 *
 * @param uint8_t *buf						Read buffer.
 *
 * @return bool
 */
static bool EXTFLASH_readStatus(uint8_t *buf)
{
    // Build the Command for Reading Flash Status
    const uint8_t wbuf[3] = { FLASH_CMD_READ_STATUS, 0x00, 0x00 };

    // Set Initial Return Value
    bool returnVal = false;

    // Send the Command get the Response
    if (EXTFLASH_transfer(wbuf, rxBuff, 3))
    {
        // Copy the Data into the Receive Buffer
        buf[0] = rxBuff[1];
        returnVal = true;
    }

    // Return the Function
    return returnVal;

}

/**
 * Wait for the previous erase / program operation to complete.
 *
 * @return int								0 on success, < 0 on failure
 */
static int EXTFLASH_waitReady(void)
{
    // Return Value
    // //int returnValue;

    for (;;)
    {
        uint8_t buf = 0;
        // //returnValue = EXTFLASH_readStatus(&buf);

        // Check if Status Register Bit Busy
        if (!(buf & FLASH_STATUS_BIT_BUSY))
        {
            // Now Ready
            break;
        }
    }

    return 0;

}

/**
 * Enable writing on the flash device.
 *
 * @return int								0 on success, < 0 on failure
 */
static int EXTFLASH_writeEnable(void)
{
    // Command for Enabling Write Operations
    const uint8_t wbuf[] = { FLASH_CMD_WRITE_ENABLE };
    int returnValue = -3;

    // Send the Command over SPI
    if (EXTFLASH_transfer(wbuf, rxBuff, 1))
    {
        // Set our Return Value to Zero
        returnValue = 0;
    }

    // Return
    return returnValue;

}

/**
 * \brief Configures the flash device for user.
 *
 * @return bool
 */
bool EXTFLASH_open(void)
{
    // Return Value (default to FALSE)
    bool returnValue = false;

    // Buffer for the Status Register
    uint8_t buf[1];

    // Verify the manufacturer and device ID
    if (_extFlashVerifyPart())
    {
        printf("\nManu and Dev ID are in the list\n");
        // Read the Status Register
        returnValue = EXTFLASH_readStatus(buf);
    }

    // Return
    return returnValue;

}

/**
 * Send a read request using 24-bit addressing.
 *
 * @param size_t offset		The byte offset in flash to begin reading from.
 * @param size_t length		The number of bytes to read.
 * @param uint8_t *buf		The buffer where data is stored. Must be at least {length} bytes in size.
 *
 * @return bool
 */
bool EXTFLASH_read(size_t offset, size_t length, uint8_t *buf)
{
    // Write Buffer for Command
    uint8_t wbuf[4];

    // Return Value (default to FALSE)
    bool returnValue = false;

    // Wait until previous command completes
    int ret = EXTFLASH_waitReady();

    if (ret)
    {
        return false;
    }

    // SPI is driven with low frequency (1Mhz), so not necessary to use fast read.
    wbuf[0] = FLASH_CMD_READ;
    wbuf[1] = (offset >> 16) & 0xFF;
    wbuf[2] = (offset >> 8) & 0xFF;
    wbuf[3] = offset & 0xFF;

    // Send the Read Command and Get the Response
    if (EXTFLASH_transfer(wbuf, rxBuff, length + 4))
    {
        // Copy the data over
        memcpy(&buf[0], &rxBuff[4], length);

        // Set the Return Value
        returnValue = true;
    }

    // Return the Function
    return returnValue;

}

/**
 * Send a write request using 24-bit addressing.
 *
 * @param size_t offset		The byte offset in flash to begin writing to.
 * @param size_t length		The number of bytes to write.
 * @param uint8_t *buf		The buffer where data to be written is stored. Must be at least {length} bytes in size.
 *
 * @return bool
 */
bool EXTFLASH_write(size_t offset, size_t length, uint8_t *buf)
{
    // Write Buffer for Command
    uint8_t wbuf[4];

    // Status of SPI async
    //struct spi_m_async_status p_stat;

    // Begin Write Loop
    while (length > 0)
    {
        // Wait until the previous operation is completed.
        int ret = EXTFLASH_waitReady();

        // If the device isn't ready, return false
        if (ret)
        {
            return false;
        }

        // Enable Writing on the Flash Device
        ret = EXTFLASH_writeEnable();

        // If the device isn't ready, return false
        if (ret)
        {
            return false;
        }

        // Interim length per instruction
        size_t ilen;

        // Work out the Instruction Length
        ilen = FLASH_PROGRAM_PAGE_SIZE - (offset % FLASH_PROGRAM_PAGE_SIZE);

        // Bound Checking
        if (length < ilen)
        {
            ilen = length;
        }

        // Create Command and 24 bit address
        wbuf[0] = FLASH_CMD_PROGRAM;
        wbuf[1] = (offset >> 16) & 0xFF;
        wbuf[2] = (offset >> 8) & 0xFF;
        wbuf[3] = offset & 0xFF;

        // Set Counters
        offset += ilen;
        length -= ilen;

        // Start the Combined Write Sequence
        //gpio_set_pin_level(FLASH_SPI_nCS, 0);
        //gpio_set_pin_level(EXT_CS, 0);
        FLASH_CS_Clear();
        
        // First, write the page program command
        Ext_Flash_transfer_block(wbuf, rxBuff, 4);

        // Now write out the page of data
        Ext_Flash_transfer_block(buf, rxBuff, ilen);

        // Complete the combined write sequence
        //gpio_set_pin_level(FLASH_SPI_nCS, 1);
        //gpio_set_pin_level(EXT_CS, 1);
        FLASH_CS_Set();

        // Increment the Buffer
        buf += ilen;
        
    }

    // Return TRUE
    return true;

}

/**
 * Send an erase request using 24-bit addressing.
 *
 * @param size_t offset				The byte offset in flash to begin erasing from.
 * @param size_t length				The number of bytes to erase.
 *
 * @return bool
 */
bool EXTFLASH_erase(size_t offset, size_t length)
{
    // Write Buffer for Command
    uint8_t wbuf[4];
    size_t i, numsectors;

    // Set the Erase Command
    wbuf[0] = FLASH_CMD_SECTOR_ERASE;

    // Set the Offsets
    size_t endoffset = offset + length - 1;
    offset = (offset / FLASH_ERASE_SECTOR_SIZE) * FLASH_ERASE_SECTOR_SIZE;
    numsectors = (endoffset - offset + FLASH_ERASE_SECTOR_SIZE - 1) / FLASH_ERASE_SECTOR_SIZE;

    // Loop through each sector to erase
    for (i = 0; i < numsectors; i++)
    {
        // Wait until the previous operation is complete
        int ret = EXTFLASH_waitReady();

        // If not complete, return FALSE
        if (ret)
        {
            return false;
        }

        // Enable writing on the device
        ret = EXTFLASH_writeEnable();

        // If not complete, return FALSE
        if (ret)
        {
            return false;
        }

        // 24 bit sector address
        wbuf[1] = (offset >> 16) & 0xFF;
        wbuf[2] = (offset >> 8) & 0xFF;
        wbuf[3] = offset & 0xFF;

        // Send the Erase Command and Get the Response
        if (EXTFLASH_transfer(wbuf, rxBuff, 4)) {}
        
    }

    // Return TRUE
    return true;

}