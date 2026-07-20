/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>
#include "definitions.h"
#include "third_party/rtos/FreeRTOS/Source/include/event_groups.h"

#include "all_headers.h"
#include "interrupt_callbacks.h"
#include "init_funcs.h"
#include "led_driver.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    call_All_Init_Funcs_Vars();
    
    SYS_DEBUG_ErrorLevelSet(SYS_ERROR_DEBUG);
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----GTron Front Panel-----\n");
    
    //LED_Clear();
    //LED_Show_DMA();
    
    //LED_SetPixel(23, 255, 50, 0);
    //LED_Show_DMA();
    
    for ever
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

