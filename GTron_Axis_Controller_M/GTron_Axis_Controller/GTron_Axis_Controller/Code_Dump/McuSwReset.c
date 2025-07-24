/*
 * McuSwReset.c
 *
 * Created: 05-01-2022 12:59:27
 *  Author: rajkumark
 */ 
#include "Macros.h"
#include "Code_Dump/McuSwReset.h"
#include "Code_Dump/ext_flash.h"
#include "Bring_Up/CAN/TMCL_IDE_reply.h"
// bit file variables
unsigned int can_id = 0 ;

uint32_t write_addr = FLASH_START_ADDR ;
uint32_t page_size = 0, end_addr = 0 ;
uint32_t no_of_pages = 0 ;
unsigned int bin_size = 0;
int i = 0;


void sw_reset()
{	
	/* Set System reset bit */
	SCB->AIRCR = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk);
	/* Wait for System reset */
	while (1);
}
void fpga_on()
{
	gpio_set_pin_level(SWITCH_EN,false);
	gpio_set_pin_level(FPGA_CRESET_B,true);
	delay_ms(200);
	//io_write(debug_io,(uint8_t*)CDONE1,sizeof(CDONE1));
}
void fpga_off()
{
	uint8_t wbuf[3] = {0xab,0x00,0x00};    // 0xab wakeup command for flash
	uint8_t rxbuf[3] = {0} ;
	gpio_set_pin_level(SWITCH_EN,true);
	gpio_set_pin_level(FPGA_CRESET_B,false);
	//io_write(debug_io,(uint8_t*)CDONE0,sizeof(CDONE0));
	delay_ms(10);
	EXTFLASH_transfer(wbuf, rxbuf, 3);
}
void check_cdone()
{
		
	/**
	 *	check for fpga cdone status 
	 * cdone = 1 : FPGA configured properly
	 * cdone = 0 : FPGA not configured properly
	 */
	uint8_t cdone = 0;
 	cdone = gpio_get_pin_level(FPGA_CDONE);
 	gpio_set_pin_level(DBGLED3,cdone);
	if (cdone)
	{
		fpga_on();
// 		cdone = gpio_get_pin_level(FPGA_CDONE);
// 		gpio_set_pin_level(DBGLED3,cdone);
		//io_write(debug_io,(uint8_t*)CDONE1,sizeof(CDONE1));
	}
	else
	{
		fpga_off();
// 		cdone = gpio_get_pin_level(FPGA_CDONE);
// 		gpio_set_pin_level(DBGLED3,cdone);
		//io_write(debug_io,(uint8_t*)CDONE0,sizeof(CDONE0));
	}
	//return cdone;
}

void erase_can_flash()
{
	i = 0 ; bin_size = 0 ;
	no_of_pages = 0 ;
	
	while ((can_rx_frame.data[i] != '$') && (i < CAN_DATA_LENGTH) )
	{
		bin_size = bin_size * 10 + (can_rx_frame.data[i] - '0'); // covert to integer
		i++;
	}
	end_addr = FLASH_START_ADDR + bin_size ;
	//no_of_pages  = (end_addr <= FLASH_END_ADDR)?((bin_size/FLASH_PAGE_SIZE)+1) : 0 ;
	no_of_pages = (bin_size / FLASH_ERASE_SECTOR_SIZE) + 1 ;  // +1 to include the decimal in iteration 6.123 -> 7
	fpga_off();

	// Open serial flash
	if (EXTFLASH_open())
	{
		for(int i = 0 ; i < no_of_pages ;i++)
		{
			if (EXTFLASH_erase(write_addr, FLASH_ERASE_SECTOR_SIZE))
			{
				// Delay to allow erase
				delay_ms(240);
				write_addr = write_addr + FLASH_ERASE_SECTOR_SIZE ;
				//io_write(debug_io,(uint8_t*)"ERS\n", 4);
			}
		}
		write_addr = 0 ;
		// send acknowledge
		
		message_Id = CAN_ERASE_DONE ;
		can_tx_frame.data_64bit = 0x00;
		can_send(&CAN_1, message_Id, EXT_ID, 8, can_tx_frame);
		
		//io_write(debug_io,(uint8_t*)"Erase done\n", 11);
	}
	else
	{
		//io_write(debug_io,(uint8_t*)"Size error\n",12);
		
		message_Id = CAN_SIZE_ERROR ;
		can_tx_frame.data_64bit = 0x00;
		can_send(&CAN_1, message_Id, EXT_ID, 8, can_tx_frame);
	}
}
void write_can_flash()
{
	if (EXTFLASH_write(write_addr, CAN_DATA_LENGTH, (uint8_t*) can_rx_frame.data))
	{
	write_addr = write_addr + CAN_DATA_LENGTH;
		
	}
	if (write_addr >= end_addr)
	{
	//	io_write(debug_io,(uint8_t*)"Write done\n",12);
		fpga_on();
		message_Id = CAN_WRITE_DONE ;
		can_tx_frame.data_64bit = 0x00;
		can_send(&CAN_1, message_Id, EXT_ID, 8, can_tx_frame);
		//write_addr = FLASH_START_ADDR ;
		check_cdone();
	}
}

void erase_flash( void )
{
	
	
	return;
}

void read_flash( void )
{
	
	
	return;
}

void write_flash( void )
{
	
	
	return;
}