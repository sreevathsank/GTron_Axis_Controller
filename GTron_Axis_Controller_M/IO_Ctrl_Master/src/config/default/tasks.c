/*******************************************************************************
 System Tasks File

  File Name:
    tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled tasks.

  Description:
    This file contains source code necessary to maintain system's polled tasks.
    It implements the "SYS_Tasks" function that calls the individual "Tasks"
    functions for all polled MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "configuration.h"
#include "definitions.h"
#include "sys_tasks.h"


// *****************************************************************************
// *****************************************************************************
// Section: RTOS "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/* Handle for the SYSTEM_STATE_Tasks. */
TaskHandle_t xSYSTEM_STATE_Tasks;



static void lSYSTEM_STATE_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        SYSTEM_STATE_Tasks();
    }
}

/* Handle for the DEBUG_LOGGER_Tasks. */
TaskHandle_t xDEBUG_LOGGER_Tasks;



static void lDEBUG_LOGGER_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        DEBUG_LOGGER_Tasks();
    }
}

/* Handle for the CAN_Tasks. */
TaskHandle_t xCAN_Tasks;



static void lCAN_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        CAN_Tasks();
    }
}

/* Handle for the CMD_PARSER_Tasks. */
TaskHandle_t xCMD_PARSER_Tasks;



static void lCMD_PARSER_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        CMD_PARSER_Tasks();
    }
}

/* Handle for the WATCHDOG_KICKER_Tasks. */
TaskHandle_t xWATCHDOG_KICKER_Tasks;



static void lWATCHDOG_KICKER_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        WATCHDOG_KICKER_Tasks();
    }
}




// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/
void SYS_Tasks ( void )
{
    /* Maintain system services */
    


    /* Maintain Device Drivers */
    

    /* Maintain Middleware & Other Libraries */
    

    /* Maintain the application's state machine. */
    
    /* Create OS Thread for SYSTEM_STATE_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lSYSTEM_STATE_Tasks,
           "SYSTEM_STATE_Tasks",
           256,
           NULL,
           2U ,
           &xSYSTEM_STATE_Tasks);

    /* Create OS Thread for DEBUG_LOGGER_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lDEBUG_LOGGER_Tasks,
           "DEBUG_LOGGER_Tasks",
           64,
           NULL,
           1U ,
           &xDEBUG_LOGGER_Tasks);

    /* Create OS Thread for CAN_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lCAN_Tasks,
           "CAN_Tasks",
           256,
           NULL,
           2U ,
           &xCAN_Tasks);

    /* Create OS Thread for CMD_PARSER_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lCMD_PARSER_Tasks,
           "CMD_PARSER_Tasks",
           256,
           NULL,
           2U ,
           &xCMD_PARSER_Tasks);

    /* Create OS Thread for WATCHDOG_KICKER_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lWATCHDOG_KICKER_Tasks,
           "WATCHDOG_KICKER_Tasks",
           128,
           NULL,
           2U ,
           &xWATCHDOG_KICKER_Tasks);



    /* Start RTOS Scheduler. */
    
     /**********************************************************************
     * Create all Threads for APP Tasks before starting FreeRTOS Scheduler *
     ***********************************************************************/
    vTaskStartScheduler(); /* This function never returns. */

}

/*******************************************************************************
 End of File
 */

