/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    watchdog_kicker.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "watchdog_kicker.h"
#include "peripheral/wdt/plib_wdt.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the WATCHDOG_KICKER_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

WATCHDOG_KICKER_DATA watchdog_kickerData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void WATCHDOG_KICKER_Initialize ( void )

  Remarks:
    See prototype in watchdog_kicker.h.
 */

void WATCHDOG_KICKER_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    watchdog_kickerData.state = WATCHDOG_KICKER_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void WATCHDOG_KICKER_Tasks ( void )

  Remarks:
    See prototype in watchdog_kicker.h.
 */

void WATCHDOG_KICKER_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( watchdog_kickerData.state )
    {
        /* Application's initial state. */
        case WATCHDOG_KICKER_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                watchdog_kickerData.state = WATCHDOG_KICKER_STATE_SERVICE_TASKS;
            }
            break;
        }

        case WATCHDOG_KICKER_STATE_SERVICE_TASKS:
        {
            WDT_Clear();
            vTaskDelay( pdMS_TO_TICKS(50) );
            //SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nWDT Kicked");
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
