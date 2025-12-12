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
#include "definitions.h"                // SYS function prototypes

#include "TMC2209_Library/TMC2209.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    printf("NextGen GTron AxC\n");
    
    // TMC2209 UART Communication Test START
    uint32_t rd_val = 0x00;
    tmc2209_writeRegister(0x00, TMC2209_GCONF, 0x00000060);         // DEC 104.
    printf("\nWritten 0x60 to GCONF\n");
    rd_val = tmc2209_readRegister(0x00, TMC2209_GCONF);
    printf("\nRead 0x%x from GCONF\n", rd_val);
    // TMC2209 UART Communication Test END
    
    while ( true )
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

