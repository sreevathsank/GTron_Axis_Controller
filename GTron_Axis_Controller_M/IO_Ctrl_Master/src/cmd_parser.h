/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cmd_parser.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "CMD_PARSER_Initialize" and "CMD_PARSER_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "CMD_PARSER_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _CMD_PARSER_H
#define _CMD_PARSER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "can.h"
#include "io_ctrl_can_message_id.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

#define PORT_A_START_PIN_NO     0UL
#define PORT_A_END_PIN_NO       31UL
    
#define PORT_B_START_PIN_NO     32UL
#define PORT_B_END_PIN_NO       63UL
  
#define PORT_C_START_PIN_NO     64UL
#define PORT_C_END_PIN_NO       92UL
    
#define IOCTRL_OPCODE_LENGTH    6UL
    
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

typedef struct 
{
    uint8_t name[IOCTRL_OPCODE_LENGTH];  // 5 bytes + null terminator
    int32_t num;
}Opcode_t;
    
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
    CMD_PARSER_STATE_INIT=0,
    CMD_PARSER_SERVICE_STATE,
    CMD_PARSER_SUSPEND_STATE,
    CMD_PARSER_PARSE_STATE,
    CMD_PARSER_OPCODE_PARSE_STATE,
    CMD_PARSER_NO_OF_STATES
    /* TODO: Define states used by the application state machine. */

} CMD_PARSER_STATES;

typedef enum
{
    NONE_GROUP = -1,
    PORT_A_GROUP = 0,
    PORT_B_GROUP = 1,
    PORT_C_GROUP = 2,
    NO_OF_GROUPS
}PORT_GROUP_t;


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
    uint8_t dlc;
    uint8_t data[8];
    unsigned int msg_id;
}CAN_Cmd_Parser;

typedef struct
{
    uint8_t byte_1;                         // Byte 1 of the CAN Data Field.
    uint8_t byte_0;                         // Byte 0 of the CAN Data Field.
    uint8_t opcode[IOCTRL_OPCODE_LENGTH];   // String Opcode based command parsing.
    unsigned int id;                        // CAN Message ID.
    /* The application's current state */
    CMD_PARSER_STATES state;
    CAN_Cmd_Parser buffer;
    /* TODO: Define any additional data used by the application. */

} CMD_PARSER_DATA;


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
    void CMD_PARSER_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    CMD_PARSER_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    CMD_PARSER_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void CMD_PARSER_Initialize ( void );


/*******************************************************************************
  Function:
    void CMD_PARSER_Tasks ( void )

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
    CMD_PARSER_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void CMD_PARSER_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _CMD_PARSER_H */

/*******************************************************************************
 End of File
 */

