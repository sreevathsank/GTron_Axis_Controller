/* 
 * File:   can_message_id.h
 * Author: sreevathsank
 *
 * Created on 17 July, 2025, 5:20 PM
 */

#ifndef CAN_MESSAGE_ID_H
#define	CAN_MESSAGE_ID_H

/** 
 * 29 bit CAN Message ID Identifier
 * ad :	Address (4bits) Most Significant.
 * cmd:	Command (8bits)
 * typ: Type	(8bits)
 * mot: Motor	(9bits) Least Significant.
 **/
#define CAN_ID(ad, cmd, typ, mot)	( (ad << 25) | (cmd << 17) | (typ << 9) | (mot) )   // Builds the Extended CAN Message ID.

#define GET_AD(msg_id)              ( (msg_id >> 25) & 0x0F )   // Gets the Most Significant 4 bits from the Extended CAN Message ID.
#define GET_CMD(msg_id)             ( (msg_id >> 17) & 0xFF )
#define GET_TYP(msg_id)             ( (msg_id >> 9) & 0xFF )
#define GET_MOT(msg_id)             ( msg_id & 0x1FF )          // Get the Least Signicant 9 bits from the Extended CAN Message ID.

#define CAN_IOCTRL_BTN_IND_TWRLMP_ID            0x102
#define CAN_IOCTRL_STATE_CHANGE_ID              0X103
#define CAN_IOCTRL_BTN_LIMIT_PRESS_ID           0x104

#define CAN_IOCTRL_TO_SYS_CTRL_ID               0x105   // Placeholder name.
#define CAN_IOCTRL_TO_TOP_AX_CTRL_ID            0x106   // Placeholder name.
#define CAN_IOCTRL_TO_BOT_AX_CTRL_ID            0x107   // Placeholder name.
#define CAN_SYSCTRL_TO_AX_CTRL_SAG_ID           0x10C

#define CAN_BOARD_ACTIVE_PING_ID				0x10E
#define CAN_REPLY_BOARD_ACTIVE_PING_ID			0x10F

// CAN Message IDs for GTron IO Controller.
//#define IOCTRL_BTN_IND_TWRLMP_ID    CAN_ID(0x00, 0x00, 0x00, BTN_IND_TWRLMP)        // To IO Ctrl.  
//#define IOCTRL_STATE_CHANGE_ID      CAN_ID(0x00, 0x00, 0x00, STATE_CHANGE)          // To IO Ctrl.
//#define IOCTRL_BTN_LIMIT_PRESS_ID   CAN_ID(0x00, 0x00, 0x00, BTN_LIMIT_PRESS)       // To MI.
//#define IOCTRL_TO_SYS_CTRL_ID       CAN_ID(0x00, 0x00, 0x00, TO_SYS_CTRL)           // To Sys Ctrl. Placeholder name.
//#define IOCTRL_TO_AX_CTRL_ID        CAN_ID(0x00, 0x00, 0x00, TO_AX_CTRL)            // To Ax Ctrl. Placeholder name.
//#define SYCTRL_TO_AX_CTRL_ID        CAN_ID(0x00, 0x00, 0x00, )


typedef enum
{
    TOP_SYSCTRL_BOARD_ID    = 0,
    TOP_AXC_BOARD_ID        = 1,
    BOT_SYSCTRL_BOARD_ID    = 2,
    BOT_AXC_BOARD_ID        = 3,
    IOCTRL_BOARD_ID         = 4,
    FRONT_PANEL_BOARD_ID    = 5,
    NO_OF_BOARD_ID
}Board_Id_t;

typedef enum
{
    IO_C_DEFAULT        = 0,
    RUN_BUTTON          = 1,
    RUN_LED             = 2,
    PAUSE_BUTTON        = 3,
    PAUSE_LED           = 4, 
    STOP_BUTTON         = 5,
    STOP_LED            = 6,
    BUZZ_OFF_BUTTON     = 7,
    BUZZ_OFF_LED        = 8,
    TWRLMP1_RED         = 9,
    TWRLMP2_YELLOW      = 10,
    TWRLMP3_GREEN       = 11,
    TWRLMP4_BLUE        = 12,
    TWRLMP5_BUZZER      = 13,
    FRONT_DOOR_LIMIT    = 14,
    BACK_DOOR_LIMIT     = 15,
    E_PANEL_DOOR_LIMIT  = 16,
    PRESSURE_SWITCH     = 17,
    CLEANING_UNIT_SOL   = 18,
    STAMPING_RELAY      = 19,
    WINDING_RELAY       = 20,
    IO_C_NO_OF_PERIPHERALS
}IOCTRL_PERIPHERALS_t;

typedef enum
{
    IO_C_INITIALIZE = 0,
    IO_C_ENABLE = 1,
    IO_C_DISABLE = 2,
    IO_C_PIN_ON = 3,
    IO_C_PIN_OFF = 4,
    IO_C_CHECK_STATUS = 5,
    IO_C_START = 6,
    IO_C_STOP = 7,
    IO_C_PRESSED = 8,
    IO_C_NOT_PRESSED = 9,
    IO_C_NO_OF_OPERATIONS
}IOCTRL_OPERATIONS_t;

typedef enum
{
    SELECT_STATE = 0,
    RUN_STATE = 1,
    PASS_STATE = 2,
    PAUSE_STATE = 3,
    FAIL_STATE = 4,
    BUZZ_OFF_DR_STATE = 5,
    BUZZ_OFF_ER_STATE = 6,
    DISABLE_ALL_STATE = 7,
    DISABLE_HW_BTNS = 8,
    IO_C_NO_OF_STATES
}IOCTRL_STATES_t;


#endif	/* CAN_MESSAGE_ID_H */