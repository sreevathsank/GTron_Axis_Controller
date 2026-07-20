/* 
 * File:   init_functions.h
 * Author: sreevathsank
 *
 * Created on July 9, 2026, 5:52 PM
 */

#ifndef INIT_FUNCTIONS_H
#define	INIT_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "peripheral/can/plib_can1.h"
#include "definitions.h"
#include "can_gatekeeper_task.h"
#include "can_isr_callbacks.h"
#include "can_state.h"
#include "dbg_print/dbg_print.h"
#include "dbg_print/dbg_transport.h"

extern uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE];
    
void init_CAN1( void );
void init_dbg_print( void );

#ifdef	__cplusplus
}
#endif

#endif	/* INIT_FUNCTIONS_H */

