/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    system_state.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "SYSTEM_STATE_Initialize" and "SYSTEM_STATE_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "SYSTEM_STATE_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _SYSTEM_STATE_H
#define _SYSTEM_STATE_H

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
//#include "definitions.h"

#include "all_headers.h"
#include "global_vars.h"
#include "debug_logger.h"
#include "event_groups.h"
#include "io_ctrl_can_message_id.h"
#include "led_driver.h"

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

// Define only the bit positions
#define RUN_BTN_BIT                  ( 1UL << 0 )
#define PAUSE_BTN_BIT                ( 1UL << 1 )
#define STOP_BTN_BIT                 ( 1UL << 2 )
#define BZROFF_BTN_BIT               ( 1UL << 3 )
#define F_B_DOOR_LIM_BIT             ( 1UL << 4 )
#define EPANEL_DOOR_LIM_BIT          ( 1UL << 5 )

// Generic macros for bit operations
#define SET_BTN_BIT(reg, bit)            ((reg) |= (bit))
#define CLEAR_BTN_BIT(reg, bit)          ((reg) &= ~(bit))
#define TOGGLE_BTN_BIT(reg, bit)         ((reg) ^= (bit))
#define CHECK_BTN_BIT(reg, bit)          ((reg) & (bit))
    
// For Enabling and Disabling Sag Sensing during State Change.
#define SAG_ENABLE                  (uint8_t)1
#define SAG_DISABLE                 (uint8_t)0

typedef enum
{
    /* Application's state machine's initial state. */
    SYSTEM_STATE_STATE_INIT=0,
    SYSTEM_STATE_SERVICE_TASK,
    SYSTEM_STATE_SELECT,
    SYSTEM_STATE_RUN,
    SYSTEM_STATE_PASS,
    SYSTEM_STATE_PAUSE,
    SYSTEM_STATE_FAIL,
    SYSTEM_STATE_BZROFFDR,
    SYSTEM_STATE_BZROFFER,
    SYSTEM_STATE_DISABLE_ALL,
    SYSTEM_STATE_DISABLE_HW_BTNS,
    SYSTEM_STATE_EN_DIS_BTN,
    SYSTEM_STATE_BUTTON_PRESS,
    SYSTEM_STATE_ERROR,
    SYSTEM_STATE_SUSPEND,
    NO_OF_SYSTEM_STATES
    /* TODO: Define states used by the application state machine. */

} SYSTEM_STATE_t;

// enum for button commands
typedef enum {
    CMD_RUN                 = 0,
    CMD_PAUSE               = 1,
    CMD_STOP                = 2,
    CMD_BUZZER_OFF          = 3,
    CMD_DOOR_UNLOCK         = 4,
    CMD_PRESSURE_SWITCH     = 5,
    CMD_DOOR_PRESSED        = 6,
    CMD_DOOR_NOT_PRESSED    = 7,
    CMD_MAX  // Used for bounds checking
} button_command_t;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

//DBGLog_t system_state_log;

typedef struct
{
    // The application's current state.
    SYSTEM_STATE_t state;
    
    // The application's previous state.
    SYSTEM_STATE_t current_system_state;
    
    // Value of the System State Event Group after this task is unblocked.
    uint32_t event_grp_val;
    
    // What bits to wait for the task to unblock.
    uint32_t bits_to_wait_for;
    
    // Clear these bits after reading the event group.
    uint32_t bits_to_clear;
    
    bool clear_bits_after_unblock;
    
    bool wait_for_all_bits;

} SYSTEM_STATE_DATA;

typedef struct
{
    EventBits_t bit;
    SYSTEM_STATE_t state;
    const char *debug_msg;
}Event_Bit_Map_t;

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
    void SYSTEM_STATE_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    SYSTEM_STATE_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SYSTEM_STATE_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void SYSTEM_STATE_Initialize ( void );

void send_Data_to_CAN_Queue( int32_t msgid, uint8_t *data_to_wr, uint8_t data_length_code );


/*******************************************************************************
  Function:
    void SYSTEM_STATE_Tasks ( void )

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
    SYSTEM_STATE_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void SYSTEM_STATE_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _SYSTEM_STATE_H */

/*******************************************************************************
 End of File
 */

