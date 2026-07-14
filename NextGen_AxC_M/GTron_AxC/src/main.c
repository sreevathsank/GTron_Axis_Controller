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
#include <stdlib.h>
#include "definitions.h"                // SYS function prototypes
#include "config/default/peripheral/can/plib_can1.h"
#include "FreeRTOS.h"
#include "queue.h"

#include "dbg_print/dbg_print.h"
#include "dbg_print/dbg_transport.h"
#include "init_functions.h"
#include "can_isr_callbacks.h"
#include "can_protocol.h"

static uint8_t          qbuf_can_work[16 * sizeof(Can_Frame_t)];
static StaticQueue_t    sq_can_work;
QueueHandle_t           gq_can_work;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    SYS_Initialize ( NULL );
    
    gq_can_work = xQueueCreateStatic(16, sizeof(Can_Frame_t), qbuf_can_work, &sq_can_work);
    
    init_CAN1();
    
    DBG_TransportInit();
    DBG_Init( DBG_TransportGet() );
    
    DBGLED1_Clear();
    DBGLED2_Set();
    DBGLED3_Clear();
    
    DBG_Printf(ERR_LVL_DEBUG,
               "This is nise!\n");
    
    for(;;) {
        SYS_Tasks ( );
    }
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

