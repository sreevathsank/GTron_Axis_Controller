/* 
 * File:   can_isr_callbacks.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 12:46 PM
 */

#ifndef CAN_ISR_CALLBACKS_H
#define	CAN_ISR_CALLBACKS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "third_party/rtos/FreeRTOS/Source/include/FreeRTOS.h"
#include "third_party/rtos/FreeRTOS/Source/include/queue.h"
#include "peripheral/can/plib_can1.h"
#include "definitions.h"
#include "can_gatekeeper_task.h"

void CAN1_RxFifo0Callback ( uint8_t numberOfMessage, uintptr_t context );

void CAN1_RxFifo1Callback ( uint8_t numberOfMessage, uintptr_t context );

void CAN1_TxFifoCallback(uintptr_t context);

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_ISR_CALLBACKS_H */

