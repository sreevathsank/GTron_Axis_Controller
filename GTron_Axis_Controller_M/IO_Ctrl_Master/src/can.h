/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    can.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "CAN_Initialize" and "CAN_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "CAN_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _CAN_H
#define _CAN_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdalign.h>
#include "configuration.h"
#include "config/default/peripheral/can/plib_can1.h"
#include "interrupt_callbacks.h"
#include "global_vars.h"
#include "io_ctrl_can_message_id.h"
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
    
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    CAN_STATE_INIT=0,
    CAN_STATE_SERVICE_TASKS,
    CAN_PARSE_STATE
    /* TODO: Define states used by the application state machine. */

} CAN_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    CAN_STATES state;

    /* TODO: Define any additional data used by the application. */

} CAN_DATA;

extern uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned (32)));

// Standard identifier id[28:18].
#define WRITE_ID(id) (id << 18)
#define READ_ID(id)  (id >> 18)

#define CAN_RX_FIFO_ELEMENT_COUNT       2UL

typedef union
{
    CAN_RX_BUFFER rx_can_buf;
    uint8_t can_bytes[sizeof(CAN_RX_BUFFER)];
}CAN_RX_FIFO_ELEMENT_t;

// Application's state machine enum.
typedef enum
{
    APP_STATE_CAN_RECEIVE,
    APP_STATE_CAN_TRANSMIT,
    APP_STATE_CAN_IDLE,
    APP_STATE_CAN_XFER_SUCCESSFUL,
    APP_STATE_CAN_XFER_ERROR,
    APP_STATE_CAN_USER_INPUT
} CAN_STATE;

// Variable to save Tx/Rx transfer status and context.
extern uint32_t status;
extern uint32_t xferContext;

// Variable to save Tx/Rx message.
extern uint8_t loop_count;
extern uint8_t user_input;

// Variable to save application state.
extern volatile CAN_STATE can_state;

extern uint8_t txFiFo[CAN1_TX_FIFO_BUFFER_SIZE];
extern uint8_t rxFiFo0[CAN1_RX_FIFO0_SIZE];
extern uint8_t rxFiFo1[CAN1_RX_FIFO1_SIZE];
//uint8_t rxBuffer[CAN1_RX_BUFFER_SIZE];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void CAN_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    CAN_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    CAN_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

uint32_t get_can_id_from_buffer(const uint8_t* ptr);

uint8_t get_can_dlc_from_buffer(const uint8_t* ptr);

void get_can_data_from_buffer(const uint8_t* src_ptr, uint8_t* dest_ptr, uint8_t dlc);

void CAN_Initialize ( void );

void print_message(uint8_t numberOfMessage, CAN_RX_BUFFER *rxBuf, uint8_t rxBufLen, uint8_t rxFifoBuf);

uint8_t CANDlcToLengthGet(uint8_t dlc);

uint8_t CANLengthToDlcGet(uint8_t length);

/*******************************************************************************
  Function:
    void CAN_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    CAN_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void CAN_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _CAN_H */

/*******************************************************************************
 End of File
 */

