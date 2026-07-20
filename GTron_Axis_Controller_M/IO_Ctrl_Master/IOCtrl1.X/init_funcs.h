/* 
 * File:   init_funcs.h
 * Author: sreevathsank
 *
 * Created on 2 July, 2025, 12:04 PM
 */

#ifndef INIT_FUNCS_H
#define	INIT_FUNCS_H

#include "all_headers.h"
#include "interrupt_callbacks.h"
#include "debug_logger.h"
#include "peripheral/can/plib_can1.h"
#include "can.h"
#include "global_vars.h"
#include "definitions.h"
#include "led_driver.h"

void init_Watchdog_Timer( void );
void determine_Reset_Cause( void );
void call_All_Init_Funcs_Vars( void );

#endif	/* INIT_FUNCS_H */

