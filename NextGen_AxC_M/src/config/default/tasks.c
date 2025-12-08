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

/* Handle for the HEALTH_TASK_Tasks. */
TaskHandle_t xHEALTH_TASK_Tasks;



static void lHEALTH_TASK_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        HEALTH_TASK_Tasks();
    }
}

/* Handle for the TMC4671_MOTION_Tasks. */
TaskHandle_t xTMC4671_MOTION_Tasks;



static void lTMC4671_MOTION_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        TMC4671_MOTION_Tasks();
    }
}

/* Handle for the TMC2209_MOTION_Tasks. */
TaskHandle_t xTMC2209_MOTION_Tasks;



static void lTMC2209_MOTION_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        TMC2209_MOTION_Tasks();
    }
}

/* Handle for the CAN_TASK_Tasks. */
TaskHandle_t xCAN_TASK_Tasks;



static void lCAN_TASK_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        CAN_TASK_Tasks();
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

/* Handle for the DEBUG_LOGGER_Tasks. */
TaskHandle_t xDEBUG_LOGGER_Tasks;



static void lDEBUG_LOGGER_Tasks(  void *pvParameters  )
{   
    while(true)
    {
        DEBUG_LOGGER_Tasks();
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
    
    /* Create OS Thread for HEALTH_TASK_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lHEALTH_TASK_Tasks,
           "HEALTH_TASK_Tasks",
           128,
           NULL,
           4U ,
           &xHEALTH_TASK_Tasks);

    /* Create OS Thread for TMC4671_MOTION_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lTMC4671_MOTION_Tasks,
           "TMC4671_MOTION_Tasks",
           128,
           NULL,
           3U ,
           &xTMC4671_MOTION_Tasks);

    /* Create OS Thread for TMC2209_MOTION_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lTMC2209_MOTION_Tasks,
           "TMC2209_MOTION_Tasks",
           128,
           NULL,
           3U ,
           &xTMC2209_MOTION_Tasks);

    /* Create OS Thread for CAN_TASK_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lCAN_TASK_Tasks,
           "CAN_TASK_Tasks",
           128,
           NULL,
           2U ,
           &xCAN_TASK_Tasks);

    /* Create OS Thread for CMD_PARSER_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lCMD_PARSER_Tasks,
           "CMD_PARSER_Tasks",
           128,
           NULL,
           2U ,
           &xCMD_PARSER_Tasks);

    /* Create OS Thread for DEBUG_LOGGER_Tasks. */
    (void) xTaskCreate(
           (TaskFunction_t) lDEBUG_LOGGER_Tasks,
           "DEBUG_LOGGER_Tasks",
           128,
           NULL,
           1U ,
           &xDEBUG_LOGGER_Tasks);



    /* Start RTOS Scheduler. */
    
     /**********************************************************************
     * Create all Threads for APP Tasks before starting FreeRTOS Scheduler *
     ***********************************************************************/
    vTaskStartScheduler(); /* This function never returns. */

}

/*******************************************************************************
 End of File
 */

