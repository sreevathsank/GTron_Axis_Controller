/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    can_gatekeeper_task.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "CAN_GATEKEEPER_TASK_Initialize" and "CAN_GATEKEEPER_TASK_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "CAN_GATEKEEPER_TASK_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _CAN_GATEKEEPER_TASK_H
#define _CAN_GATEKEEPER_TASK_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "config/default/peripheral/can/plib_can1.h"
#include "config/default/peripheral/can/plib_can_common.h"

#include "can_protocol.h"
#include "can_state.h"
#include "can_isr_callbacks.h"
#include "dbg_print/dbg_print.h"
#include "dbg_print/dbg_transport.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    
#define CAN_ID(ad, cmd, typ, mot)       ((ad << 25) | (cmd << 17) | (typ << 9) | (mot))
#define GET_AD(msg_id)                  ((msg_id >> 25) & 0x0F)
#define GET_CMD(msg_id)                 ((msg_id >> 17) & 0xFF)
#define GET_TYP(msg_id)                 ((msg_id >> 9) & 0xFF)
#define GET_MOT(msg_id)                 ((msg_id) & 0x1FF)
// DOM-IGNORE-END  

typedef enum {
    CAN_GATEKEEPER_TASK_STATE_INIT=0,
    CAN_GATEKEEPER_TASK_STATE_SERVICE_TASKS,
    APP_STATE_CAN_RECEIVE,
    APP_STATE_CAN_TRANSMIT,
    APP_STATE_CAN_IDLE,
    APP_STATE_CAN_XFER_SUCCESSFUL,
    APP_STATE_CAN_XFER_ERROR,
    APP_STATE_CAN_USER_INPUT
} CAN_GATEKEEPER_TASK_STATES;
extern CAN_GATEKEEPER_TASK_STATES can_state;

typedef struct {
    CAN_GATEKEEPER_TASK_STATES state;
} CAN_GATEKEEPER_TASK_DATA;

void CAN_GATEKEEPER_TASK_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _CAN_GATEKEEPER_TASK_H */

/*******************************************************************************
 End of File
 */

