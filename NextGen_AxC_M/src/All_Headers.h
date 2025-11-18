/*
 * Global_Vars.h
 *
 * Created: 13-12-2023 15:14:42
 *  Author: sreevathsank
 */ 

/** 
 * \file
 *
 * \brief Contains all the header files required in one place.
 */

#ifndef ALL_HEADERS_H_
#define ALL_HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
//#include <assert.h>

#include "Macros.h"
//#include "atmel_start_pins.h"
//#include "driver_init.h"
#include "system/debug/sys_debug.h"
#include "Bring_Up/DBG_bring_up.h"
#include "TMC-API/tmc/ic/TMC4671/TMC4671.h"
#include "Bring_Up/CAN/IMM_CAN.h"
#include "Bring_Up/CAN/IMM_CAN_Message_Id.h"
#include "motor_dev/my_Ramp/myRamp.h"
#include "Bring_Up/CAN/IMM_CAN_Read.h"
#include "Bring_Up/CAN/IMM_CAN_Write.h"
#include "Global_Vars.h"
#include "Bring_Up/CAN/TMCL_IDE_reply.h"
#include "Bring_Up/CAN/MCD_v3.h"
//#include "SysTick/Systick.h"
#include "Bring_Up/Motion/Motion.h"
#include "Code_Dump/McuSwReset.h"
#include "Code_Dump/tlv_flash.h"
#include "Bring_Up/IO_Expander/spi_io_expander.h"
#include "tmc2209_uart/TMC2209.h"
#include "tmc2209_uart/TMC2209_Motion.h"
#include "tmc2209_uart/Step_Counter.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"

#endif /* ALL_HEADERS_H_ */