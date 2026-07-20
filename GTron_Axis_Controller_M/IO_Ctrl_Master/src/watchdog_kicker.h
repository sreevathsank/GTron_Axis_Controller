/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    watchdog_kicker.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "WATCHDOG_KICKER_Initialize" and "WATCHDOG_KICKER_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "WATCHDOG_KICKER_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _WATCHDOG_KICKER_H
#define _WATCHDOG_KICKER_H

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
#include "definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

#define WDT_CYC8          0x00    // 8 clock cycles - 7.81 ms
#define WDT_CYC16         0x01    // 16 clock cycles - 15.63 ms
#define WDT_CYC32         0x02    // 32 clock cycles - 31.25 ms
#define WDT_CYC64         0x03    // 64 clock cycles - 62.5 ms
#define WDT_CYC128        0x04    // 128 clock cycles - 125 ms
#define WDT_CYC256        0x05    // 256 clock cycles - 250 ms
#define WDT_CYC512        0x06    // 512 clock cycles - 500 ms
#define WDT_CYC1024       0x07    // 1024 clock cycles - 1000 ms (1 second)
#define WDT_CYC2048       0x08    // 2048 clock cycles - 2000 ms (2 seconds)
#define WDT_CYC4096       0x09    // 4096 clock cycles - 4000 ms (4 seconds)
#define WDT_CYC8192       0x0A    // 8192 clock cycles - 8000 ms (8 seconds)
#define WDT_CYC16384      0x0B    // 16384 clock cycles - 16000 ms (16 seconds)
    
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
    WATCHDOG_KICKER_STATE_INIT=0,
    WATCHDOG_KICKER_STATE_SERVICE_TASKS,
    /* TODO: Define states used by the application state machine. */

} WATCHDOG_KICKER_STATES;


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
    WATCHDOG_KICKER_STATES state;

    /* TODO: Define any additional data used by the application. */

} WATCHDOG_KICKER_DATA;

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
    void WATCHDOG_KICKER_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    WATCHDOG_KICKER_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    WATCHDOG_KICKER_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void WATCHDOG_KICKER_Initialize ( void );


/*******************************************************************************
  Function:
    void WATCHDOG_KICKER_Tasks ( void )

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
    WATCHDOG_KICKER_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void WATCHDOG_KICKER_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _WATCHDOG_KICKER_H */

/*******************************************************************************
 End of File
 */

