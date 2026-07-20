/*******************************************************************************
  Board Support Package Header File.

  Company:
    Microchip Technology Inc.

  File Name:
    bsp.h

  Summary:
    Board Support Package Header File 

  Description:
    This file contains constants, macros, type definitions and function
    declarations 
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
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

#ifndef BSP_H
#define BSP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "device.h"
#include "peripheral/port/plib_port.h"

// *****************************************************************************
// *****************************************************************************
// Section: BSP Macros
// *****************************************************************************
// *****************************************************************************
#define SAMC21N_XPLAINED_PRO
#define BOARD_NAME    "SAMC21N-XPLAINED-PRO"

/*** Macros for CAN_SILENT output pin ***/ 
#define BSP_CAN_SILENT_PIN        PORT_PIN_PC9
#define BSP_CAN_SILENT_Get()      ((PORT_REGS->GROUP[2].PORT_IN >> 9U) & 0x01U)
#define BSP_CAN_SILENT_Set()      (PORT_REGS->GROUP[2].PORT_OUTSET = ((uint32_t)1U << 9U))
#define BSP_CAN_SILENT_Clear()    (PORT_REGS->GROUP[2].PORT_OUTCLR = ((uint32_t)1U << 9U))
#define BSP_CAN_SILENT_Toggle()   (PORT_REGS->GROUP[2].PORT_OUTTGL = ((uint32_t)1U << 9U))
#define BSP_CAN_SILENT_On()       BSP_CAN_SILENT_Set()
#define BSP_CAN_SILENT_Off()      BSP_CAN_SILENT_Clear() 

/*** Macros for BZROFF_LED output pin ***/ 
#define BSP_BZROFF_LED_PIN        PORT_PIN_PA13
#define BSP_BZROFF_LED_Get()      ((PORT_REGS->GROUP[0].PORT_IN >> 13U) & 0x01U)
#define BSP_BZROFF_LED_Set()      (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 13U))
#define BSP_BZROFF_LED_Clear()    (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 13U))
#define BSP_BZROFF_LED_Toggle()   (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 13U))
#define BSP_BZROFF_LED_On()       BSP_BZROFF_LED_Set()
#define BSP_BZROFF_LED_Off()      BSP_BZROFF_LED_Clear() 

/*** Macros for STOP_LED output pin ***/ 
#define BSP_STOP_LED_PIN        PORT_PIN_PA14
#define BSP_STOP_LED_Get()      ((PORT_REGS->GROUP[0].PORT_IN >> 14U) & 0x01U)
#define BSP_STOP_LED_Set()      (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 14U))
#define BSP_STOP_LED_Clear()    (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 14U))
#define BSP_STOP_LED_Toggle()   (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 14U))
#define BSP_STOP_LED_On()       BSP_STOP_LED_Set()
#define BSP_STOP_LED_Off()      BSP_STOP_LED_Clear() 

/*** Macros for PAUSE_LED output pin ***/ 
#define BSP_PAUSE_LED_PIN        PORT_PIN_PA15
#define BSP_PAUSE_LED_Get()      ((PORT_REGS->GROUP[0].PORT_IN >> 15U) & 0x01U)
#define BSP_PAUSE_LED_Set()      (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 15U))
#define BSP_PAUSE_LED_Clear()    (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 15U))
#define BSP_PAUSE_LED_Toggle()   (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 15U))
#define BSP_PAUSE_LED_On()       BSP_PAUSE_LED_Set()
#define BSP_PAUSE_LED_Off()      BSP_PAUSE_LED_Clear() 

/*** Macros for RUN_LED output pin ***/ 
#define BSP_RUN_LED_PIN        PORT_PIN_PA16
#define BSP_RUN_LED_Get()      ((PORT_REGS->GROUP[0].PORT_IN >> 16U) & 0x01U)
#define BSP_RUN_LED_Set()      (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 16U))
#define BSP_RUN_LED_Clear()    (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 16U))
#define BSP_RUN_LED_Toggle()   (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 16U))
#define BSP_RUN_LED_On()       BSP_RUN_LED_Set()
#define BSP_RUN_LED_Off()      BSP_RUN_LED_Clear() 

/*** Macros for WINDING output pin ***/ 
#define BSP_WINDING_PIN        PORT_PIN_PC18
#define BSP_WINDING_Get()      ((PORT_REGS->GROUP[2].PORT_IN >> 18U) & 0x01U)
#define BSP_WINDING_Set()      (PORT_REGS->GROUP[2].PORT_OUTSET = ((uint32_t)1U << 18U))
#define BSP_WINDING_Clear()    (PORT_REGS->GROUP[2].PORT_OUTCLR = ((uint32_t)1U << 18U))
#define BSP_WINDING_Toggle()   (PORT_REGS->GROUP[2].PORT_OUTTGL = ((uint32_t)1U << 18U))
#define BSP_WINDING_On()       BSP_WINDING_Set()
#define BSP_WINDING_Off()      BSP_WINDING_Clear() 

/*** Macros for TWRLMP1_R output pin ***/ 
#define BSP_TWRLMP1_R_PIN        PORT_PIN_PC27
#define BSP_TWRLMP1_R_Get()      ((PORT_REGS->GROUP[2].PORT_IN >> 27U) & 0x01U)
#define BSP_TWRLMP1_R_Set()      (PORT_REGS->GROUP[2].PORT_OUTSET = ((uint32_t)1U << 27U))
#define BSP_TWRLMP1_R_Clear()    (PORT_REGS->GROUP[2].PORT_OUTCLR = ((uint32_t)1U << 27U))
#define BSP_TWRLMP1_R_Toggle()   (PORT_REGS->GROUP[2].PORT_OUTTGL = ((uint32_t)1U << 27U))
#define BSP_TWRLMP1_R_On()       BSP_TWRLMP1_R_Set()
#define BSP_TWRLMP1_R_Off()      BSP_TWRLMP1_R_Clear() 

/*** Macros for TWRLMP2_Y output pin ***/ 
#define BSP_TWRLMP2_Y_PIN        PORT_PIN_PC28
#define BSP_TWRLMP2_Y_Get()      ((PORT_REGS->GROUP[2].PORT_IN >> 28U) & 0x01U)
#define BSP_TWRLMP2_Y_Set()      (PORT_REGS->GROUP[2].PORT_OUTSET = ((uint32_t)1U << 28U))
#define BSP_TWRLMP2_Y_Clear()    (PORT_REGS->GROUP[2].PORT_OUTCLR = ((uint32_t)1U << 28U))
#define BSP_TWRLMP2_Y_Toggle()   (PORT_REGS->GROUP[2].PORT_OUTTGL = ((uint32_t)1U << 28U))
#define BSP_TWRLMP2_Y_On()       BSP_TWRLMP2_Y_Set()
#define BSP_TWRLMP2_Y_Off()      BSP_TWRLMP2_Y_Clear() 

/*** Macros for TWRLMP3_G output pin ***/ 
#define BSP_TWRLMP3_G_PIN        PORT_PIN_PA27
#define BSP_TWRLMP3_G_Get()      ((PORT_REGS->GROUP[0].PORT_IN >> 27U) & 0x01U)
#define BSP_TWRLMP3_G_Set()      (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 27U))
#define BSP_TWRLMP3_G_Clear()    (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 27U))
#define BSP_TWRLMP3_G_Toggle()   (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 27U))
#define BSP_TWRLMP3_G_On()       BSP_TWRLMP3_G_Set()
#define BSP_TWRLMP3_G_Off()      BSP_TWRLMP3_G_Clear() 

/*** Macros for TWRLMP4_B output pin ***/ 
#define BSP_TWRLMP4_B_PIN        PORT_PIN_PA28
#define BSP_TWRLMP4_B_Get()      ((PORT_REGS->GROUP[0].PORT_IN >> 28U) & 0x01U)
#define BSP_TWRLMP4_B_Set()      (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 28U))
#define BSP_TWRLMP4_B_Clear()    (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 28U))
#define BSP_TWRLMP4_B_Toggle()   (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 28U))
#define BSP_TWRLMP4_B_On()       BSP_TWRLMP4_B_Set()
#define BSP_TWRLMP4_B_Off()      BSP_TWRLMP4_B_Clear() 

/*** Macros for TWRLMP5_BUZ output pin ***/ 
#define BSP_TWRLMP5_BUZ_PIN        PORT_PIN_PB31
#define BSP_TWRLMP5_BUZ_Get()      ((PORT_REGS->GROUP[1].PORT_IN >> 31U) & 0x01U)
#define BSP_TWRLMP5_BUZ_Set()      (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 31U))
#define BSP_TWRLMP5_BUZ_Clear()    (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 31U))
#define BSP_TWRLMP5_BUZ_Toggle()   (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 31U))
#define BSP_TWRLMP5_BUZ_On()       BSP_TWRLMP5_BUZ_Set()
#define BSP_TWRLMP5_BUZ_Off()      BSP_TWRLMP5_BUZ_Clear() 

/*** Macros for CLU_SOL output pin ***/ 
#define BSP_CLU_SOL_PIN        PORT_PIN_PB1
#define BSP_CLU_SOL_Get()      ((PORT_REGS->GROUP[1].PORT_IN >> 1U) & 0x01U)
#define BSP_CLU_SOL_Set()      (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 1U))
#define BSP_CLU_SOL_Clear()    (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 1U))
#define BSP_CLU_SOL_Toggle()   (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 1U))
#define BSP_CLU_SOL_On()       BSP_CLU_SOL_Set()
#define BSP_CLU_SOL_Off()      BSP_CLU_SOL_Clear() 

/*** Macros for STAMPING output pin ***/ 
#define BSP_STAMPING_PIN        PORT_PIN_PB2
#define BSP_STAMPING_Get()      ((PORT_REGS->GROUP[1].PORT_IN >> 2U) & 0x01U)
#define BSP_STAMPING_Set()      (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 2U))
#define BSP_STAMPING_Clear()    (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 2U))
#define BSP_STAMPING_Toggle()   (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 2U))
#define BSP_STAMPING_On()       BSP_STAMPING_Set()
#define BSP_STAMPING_Off()      BSP_STAMPING_Clear() 




// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void BSP_Initialize(void)

  Summary:
    Performs the necessary actions to initialize a board

  Description:
    This function initializes the LED and Switch ports on the board.  This
    function must be called by the user before using any APIs present on this
    BSP.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Example:
    <code>
    BSP_Initialize();
    </code>

  Remarks:
    None
*/

void BSP_Initialize(void);

#endif // BSP_H

/*******************************************************************************
 End of File
*/