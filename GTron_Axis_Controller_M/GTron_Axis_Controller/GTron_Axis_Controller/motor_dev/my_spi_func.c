/*
 * my_spi_func.c
 *
 * Created: 16-10-2023 16:27:22
 *  Author: sreevathsank
 */ 
/** 
 * Function to seperate a 32 bit data to Four 8 bit data
 * (FOR READ OPERATION ONLY)!!!
 *
 * @param 32 bit unsigned integer Data
 *
 * @return void
 **/
/*
void seperate8bit_rd(uint32_t data)
{
	uint8_t rd_1b = (data >> 24) & 0xff;
	uint8_t rd_2b = (data >> 16) & 0xff;
	uint8_t rd_3b = (data >> 8) & 0xff;
	uint8_t rd_4b = (data) & 0xff;	
}
*/
/** 
 * Function to seperate a 32 bit data to Four 8 bit data
 * (FOR WRITE OPERATION ONLY)!!!
 *
 * @param 32 bit unsigned integer Data
 *
 * @return void
 **/
/*
void seperate8bit_wr(uint32_t data)
{
	uint8_t wr_1b = (data >> 24) & 0xff;
	uint8_t wr_2b = (data >> 16) & 0xff;
	uint8_t wr_3b = (data >> 8) & 0xff;
	uint8_t wr_4b = (data) & 0xff;
}
*/
/** 
 * Function to Combine Four 8 bit data into a single 32 bit data
 * 
 * @param1 8 bit unsigned integer byte 1 (MSB)
 * @param2 8 bit unsigned integer byte 2
 * @param3 8 bit unsigned integer byte 3
 * @param4 8 bit unsigned integer byte 4 (LSB)
 *
 * @return uint32_t
 **/
/*
uint32_t combine8bit(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	uint32_t data;
	
	data |= ((uint32_t)byte1) << 24;
	data |= ((uint32_t)byte2) << 16;
	data |= ((uint32_t)byte3) << 8;
	data |= ((uint32_t)byte4);
	
	return data;
}
*/
/** 
 * Function to write data byte by byte via SPI on SERCOM1
 *
 * @param 8 bit unsigned integer Address of the register
 * @param 32 bit unsigned integer Data in hex
 *
 * @return void
 **/
/*
void SPI_wr(uint8_t addr, uint32_t data)
{
	gpio_set_pin_level(CS, 0);
	delay_ms(1);
	
	wr_addr += addr; 
	
	uint8_t wr_1b = (data >> 24) & 0xff;
	uint8_t wr_2b = (data >> 16) & 0xff;
	uint8_t wr_3b = (data >> 8) & 0xff;
	uint8_t wr_4b = (data) & 0xff;
	
	//seperate8bit_wr(data);
	
	SPI_0_exchange_block(&wr_addr, 1);
	SPI_0_exchange_block(&wr_1b, 1);
	SPI_0_exchange_block(&wr_2b, 1);
	SPI_0_exchange_block(&wr_3b, 1);
	SPI_0_exchange_block(&wr_4b, 1);
	
	gpio_set_pin_level(CS, 1);
	printf("\nWrite done\n");
}
*/
/** 
 * Function for reading the data sent to SERCOM1 via SPI
 * and prints the read value in hexadecimal and decimal.
 *
 * @param 8 bit unsigned integer Address
 * @param 32 bit unsigned integer Data in hex
 *
 * @return void
 **/
/*
void SPI_rd(uint8_t addr, uint32_t data)
{
	gpio_set_pin_level(CS, 0);
	delay_ms(1);
	
	rd_addr += addr;
	
	uint8_t rd_1b = (data >> 24) & 0xff;
	uint8_t rd_2b = (data >> 16) & 0xff;
	uint8_t rd_3b = (data >> 8) & 0xff;
	uint8_t rd_4b = (data) & 0xff;
	
	SPI_0_exchange_block(&rd_addr, 1);
	SPI_0_exchange_block(&rd_1b, 1);
	SPI_0_exchange_block(&rd_2b, 1);
	SPI_0_exchange_block(&rd_3b, 1);
	SPI_0_exchange_block(&rd_4b, 1);
	
	gpio_set_pin_level(CS, 1);
	printf("\nRead done\n");
	
	
			
	printf("\nRead values (HEX) %x %x %x %x %x\t(DEC) %d %d %d %d %d\n", rd_addr, rd_1b, rd_2b, rd_3b, rd_4b, rd_addr, rd_1b, rd_2b, rd_3b, rd_4b);
}*/