/* 
 * File:   interrupt_callbacks.h
 * Author: sreevathsank
 *
 * Created on 30 June, 2025, 2:59 PM
 */

#ifndef INTERRUPT_CALLBACKS_H
#define	INTERRUPT_CALLBACKS_H

#include "all_headers.h"
#include "third_party/rtos/FreeRTOS/Source/include/event_groups.h" 
#include "event_groups.h"
#include "global_vars.h"
#include "peripheral/can/plib_can1.h"
#include "can.h"

void EIC_Init_Callbacks( void );

void CAN1_TxFifoCallback(uintptr_t context);
void CAN1_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context);
void CAN1_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context);

#endif	/* INTERRUPT_CALLBACKS_H */

