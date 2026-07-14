/* 
 * File:   interrupt_callbacks.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 10:58 AM
 */

#ifndef INTERRUPT_CALLBACKS_H
#define	INTERRUPT_CALLBACKS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "peripheral/can/plib_can1.h"
#include "definitions.h"

void CAN1_TxFifoCallback(uintptr_t context);

void CAN1_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context);

void CAN1_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context);
    
#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_CALLBACKS_H */

