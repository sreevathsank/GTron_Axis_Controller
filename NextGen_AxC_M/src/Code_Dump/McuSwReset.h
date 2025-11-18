/*
 * McuSwReset.h
 *
 * Created: 08-11-2021 10:02:02
 *  Author: rajkumark
 */ 


#ifndef MCUSWRESET_H_
#define MCUSWRESET_H_

//#include <atmel_start.h>
//#include <hal_spi_m_async.h>
#include "Bring_Up/CAN/IMM_CAN_Message_Id.h"

#define CAN_ERASE_DONE       0x03
#define CAN_ERASE_ERROR      0x04
#define CAN_SIZE_ERROR       0x05

#define CAN_WRITE_DONE       0x06

#define FLASH_START_ADDR         0x00000000
#define FLASH_END_ADDR           0x00040000
#define CAN_DATA_LENGTH          8

void sw_reset();

void check_cdone();
void fpga_off();
void fpga_on();

void erase_can_flash();
void write_can_flash();

#endif /* MCUSWRESET_H_ */