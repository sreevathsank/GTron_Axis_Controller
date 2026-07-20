/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cmd_parser.c

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

#include "cmd_parser.h"

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
    This structure should be initialized by the CMD_PARSER_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

CMD_PARSER_DATA cmd_parserData;

uint8_t pin_no_map[IO_C_NO_OF_PERIPHERALS];

Can_Queue_t can_RdWr_queue;

uint8_t tx_can_data[2] = { 0 };

const char* state_names[] = 
{
    "\nCmdParser: State Byte -> Select State\n",
    "\nCmdParser: State Byte -> Run State\n",
    "\nCmdParser: State Byte -> Pass State\n",
    "\nCmdParser: State Byte -> Pause State\n",
    "\nCmdParser: State Byte -> Fail State\n",
    "\nCmdParser: State Byte -> BuzOffDR State\n",
    "\nCmdParser: State Byte -> BuzOffER State\n",
    "\nCmdParser: State Byte -> Disable All DHBLS State\n",
    "\nCmdParser: State Byte -> Disable All Hardware Buttons State\n",
    
};

static const Opcode_t ioctrl_opcodes[] = 
{
    {"ATBOF",  0},
    {"ATPAU",  1},
    {"ATRUN",  2},
    {"ATSTP",  3},
    {"BOFDR",  4},
    {"BOFER",  5},
    {"BZROF",  6},
    {"BZRON",  7},
    {"DHBLS",  8},
    {"DOORC",  9},
    {"DTBOF", 10},
    {"DTPAU", 11},
    {"DTRUN", 12},
    {"DTSTP", 13},
    {"HWBDB", 14},
    {"IEFAI", 15},
    {"IEPAS", 16},
    {"IEPAU", 17},
    {"IERUN", 18},
    {"IESEL", 19},
    {"PAUOF", 20},
    {"PAUON", 21},
    {"RUNOF", 22},
    {"RUNON", 23},
    {"SOLOF", 24},
    {"SOLON", 25},
    {"STMP0", 28},
    {"STMP1", 29},
    {"STPOF", 26},
    {"STPON", 27},
    {"TBZR0", 30},
    {"TBZR1", 31},
    {"TGRN0", 32},
    {"TGRN1", 33},
    {"TRED0", 34},
    {"TRED1", 35},
    {"TYEL0", 36},
    {"TYEL1", 37},
    {"WIND0", 38},
    {"WIND1", 39},
    {"HYBT0", 40},
    {"HYBT1", 41}
};

#define NUM_OPCODES (sizeof(ioctrl_opcodes) / sizeof(ioctrl_opcodes[0]))

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

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void CMD_PARSER_Initialize ( void )

  Remarks:
    See prototype in cmd_parser.h.
 */

void CMD_PARSER_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    cmd_parserData.state = CMD_PARSER_STATE_INIT;
    cmd_parserData.byte_0 = 0;
    cmd_parserData.byte_1 = 0;
    
    

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

static void send_to_CAN_Rd_Wr_Queue( int32_t msgid, uint8_t *data_to_wr, uint8_t data_length_code )
{
    if(data_length_code > 8)
    {
        // Throw error.
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "\n#####-Cmd Parser Task: CAN Write DLC > 8-#####\n");
        return;
    }
    can_RdWr_queue = (Can_Queue_t){
        .operation_flag = CAN_WRITE_FLAG,
        .msg_id = msgid,
        .dlc = data_length_code
    };
    memcpy(can_RdWr_queue.data, data_to_wr, data_length_code);
    xQueueSend(xcan_rd_wr_queue, &can_RdWr_queue, portMAX_DELAY);
    return;
}

/**
 * \brief Sets the Port Pin Number and the Group Number of the given Absolute Pin Number.
 * 
 * @param   pin_number: The absolute pin number of the IC. Range is from 0 to 93. -1 represents None of the pins.
 * @param   *port_pin_number: The address of the variable to store the port pin number.
 * @param   *group_number: The address of the variable to store the group number.
 * 
 * @return  bool:   true -> Fail | false -> Success.
 **/ 
static bool get_Pin_No_And_Group( int32_t pin_number, int32_t *port_pin_number, PORT_GROUP_t *group_number )
{
    if( (pin_number < PORT_A_START_PIN_NO) || (pin_number > PORT_C_END_PIN_NO) || (port_pin_number == NULL) || (group_number == NULL) ) { return true; }    // return true for fail.
    // Identify to what Port the pin belongs to and its number within the Port.
    if( (pin_number >= PORT_A_START_PIN_NO) && (pin_number <= PORT_A_END_PIN_NO) )
    {
        *group_number = PORT_A_GROUP;
        *port_pin_number = pin_number;
    }
    else if( (pin_number >= PORT_B_START_PIN_NO) && (pin_number <= PORT_B_END_PIN_NO) )
    {
        *group_number = PORT_B_GROUP;
        *port_pin_number = pin_number - PORT_B_START_PIN_NO;
    }
    else if( (pin_number >= PORT_C_START_PIN_NO) && (pin_number <= PORT_C_END_PIN_NO) )
    {
        *group_number = PORT_C_GROUP;
        *port_pin_number = pin_number - PORT_C_START_PIN_NO;
    }
    else
    {
        *group_number = NONE_GROUP;
        *port_pin_number = -1;
        return true;       // return true for fail.
    }
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nGroup = %ld | Pin No = %ld\n", *group_number, *port_pin_number);
    return false;       // return false for success.
}

static void parse_IOCtrl_CAN_Datafield_State( void )
{
    switch((IOCTRL_STATES_t)cmd_parserData.byte_0)  // The State Byte, Byte 0 of the CAN Data Field.
    {
        case SELECT_STATE:          
        case RUN_STATE:             
        case PASS_STATE:            
        case PAUSE_STATE:           
        case FAIL_STATE:            
        case BUZZ_OFF_DR_STATE:     
        case BUZZ_OFF_ER_STATE:     
        case DISABLE_ALL_STATE:     
        case DISABLE_HW_BTNS:       
            xEventGroupSetBits( xbtn_state_event_grp, (1 << cmd_parserData.byte_0));
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, state_names[cmd_parserData.byte_0]);
        break;
        default: break;
    }
    return;
}

static void parse_Operation_Byte( IOCTRL_OPERATIONS_t operation_byte, int32_t pin_num, int32_t *port_pin_num, PORT_GROUP_t *group_num )
{
    if( !get_Pin_No_And_Group( pin_num, port_pin_num, group_num ) )
    {
        uint32_t pin_status = 0;
        switch((IOCTRL_OPERATIONS_t)operation_byte)
        {
            case IO_C_INITIALIZE:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Initialize\n");
                // Empty for now.
            break;
            case IO_C_ENABLE:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Enable\n");
                switch(cmd_parserData.byte_0)
                {
                    case RUN_BUTTON:        xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_RUN_BTN_EN_FLAG);      break;
                    case PAUSE_BUTTON:      xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_PAUSE_BTN_EN_FLAG);    break;
                    case STOP_BUTTON:       xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_STOP_BTN_EN_FLAG);     break;
                    case BUZZ_OFF_BUTTON:   xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_BZROFF_BTN_EN_FLAG);   break;
                    default: break;
                }
            break;
            case IO_C_DISABLE:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Disable\n");
                switch(cmd_parserData.byte_0)
                {
                    case RUN_BUTTON:        xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_RUN_BTN_DIS_FLAG);      break;
                    case PAUSE_BUTTON:      xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_PAUSE_BTN_DIS_FLAG);    break;
                    case STOP_BUTTON:       xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_STOP_BTN_DIS_FLAG);     break;
                    case BUZZ_OFF_BUTTON:   xEventGroupSetBits( xbtn_state_event_grp, SET_EVENT_GRP_BZROFF_BTN_DIS_FLAG);   break;
                    default: break;
                }
            break;
            case IO_C_PIN_ON:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Pin On\n");
                PORT_REGS->GROUP[*group_num].PORT_OUTSET = ((uint32_t)1U << *port_pin_num);
            break;
            case IO_C_PIN_OFF:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Pin Off\n");
                PORT_REGS->GROUP[*group_num].PORT_OUTCLR = ((uint32_t)1U << *port_pin_num);
            break;
            case IO_C_CHECK_STATUS:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Check Status\n");
                pin_status = (((PORT_REGS->GROUP[*group_num].PORT_IN >> *port_pin_num)) & 0x01U);
                
                memcpy(tx_can_data,
                       (pin_status)
                        ? (uint8_t[2]){CMD_DOOR_PRESSED, 0}
                        : (uint8_t[2]){CMD_DOOR_NOT_PRESSED, 0},
                        sizeof(tx_can_data));
              
                send_to_CAN_Rd_Wr_Queue( CAN_ID(0x00, 0x00, 0x00, CAN_IOCTRL_BTN_LIMIT_PRESS_ID), &tx_can_data[0], 1 );
            break;
            case IO_C_START:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Start\n");
                // Empty for now. 
            break;
            case IO_C_STOP:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Stop\n");
                // Empty for now. 
            break;
            case IO_C_PRESSED:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Pressed\n");
            break;
            case IO_C_NOT_PRESSED:
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Operation Byte -> Not Pressed\n");
                // Empty for now. 
            break;
            default: break;
        }
    }
    return;
}

static void parse_IOCtrl_CAN_Datafield_Btn_Ind_Twrlmp( void )
{
    int32_t pin_no = -1;            // -1 represents none of the pins.
    int32_t port_pin_no = 0;
    PORT_GROUP_t group_no = NONE_GROUP;
    switch((IOCTRL_PERIPHERALS_t)cmd_parserData.byte_0) // The Peripheral Byte, Byte 0 of the CAN Data Field.
    {
        case IO_C_DEFAULT: break;
        case RUN_BUTTON:  
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Run Button\n");
            pin_no = RUN_BTN_PIN; 
        break;
        case RUN_LED:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Run LED\n");
            pin_no = RUN_LED_PIN;
        break;
        case PAUSE_BUTTON:       
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Pause Button\n");
            pin_no = PAUSE_BTN_PIN;
        break;
        case PAUSE_LED:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Pause LED\n");
            pin_no = PAUSE_LED_PIN;
        break;
        case STOP_BUTTON:        
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Stop Button\n");
            pin_no = STOP_BTN_PIN; 
        break;
        case STOP_LED:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Stop LED\n");
            pin_no = STOP_LED_PIN;
        break;
        case BUZZ_OFF_BUTTON:    
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Buzzer Off\n");
            pin_no = BZROFF_BTN_PIN; 
        break;
        case BUZZ_OFF_LED:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Buzzer Off LED\n");
            pin_no = BZROFF_LED_PIN;
        break;
        case TWRLMP1_RED:        
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Tower Lamp 1 - Red\n");
            pin_no = TWRLMP1_R_PIN; 
        break;
        case TWRLMP2_YELLOW:     
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Tower Lamp 2 - Yellow\n");
            pin_no = TWRLMP2_Y_PIN; 
        break;
        case TWRLMP3_GREEN:      
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Tower Lamp 3 - Green\n");
            pin_no = TWRLMP3_G_PIN; 
        break;
        case TWRLMP4_BLUE:       
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Tower Lamp 4 - Blue\n");
            pin_no = TWRLMP4_B_PIN; 
        break;
        case TWRLMP5_BUZZER:     
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Tower Lamp 5 - Buzzer\n");
            pin_no = TWRLMP5_BUZ_PIN; 
        break;
        case FRONT_DOOR_LIMIT:   
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Front Door Limit\n");
            pin_no = F_DOOR_LIM_PIN; 
        break;
        case BACK_DOOR_LIMIT:    
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Back Door Limit\n");
            pin_no = B_DOOR_LIM_PIN;
        break;
        case E_PANEL_DOOR_LIMIT: 
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> E-Panel Door Limit\n");
            pin_no = EPANEL_DOOR_LIM_PIN; 
        break;
        case PRESSURE_SWITCH:    
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Pressure Switch\n");
            pin_no = PRESS_SW1_PIN; 
        break;
        case CLEANING_UNIT_SOL:  
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Cleaning Unit Solenoid\n");
            pin_no = CLU_SOL_PIN;
        break;  
        case STAMPING_RELAY:     
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Stamping Relay\n");
            pin_no = STAMPING_PIN;
        break;
        case WINDING_RELAY:   
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Peripheral Byte -> Winding Relay\n");
            pin_no = WINDING_PIN;
        break;
        default: break;
    }
    parse_Operation_Byte((IOCTRL_OPERATIONS_t)cmd_parserData.byte_1, pin_no, &port_pin_no, &group_no);
    return;
}

static void parse_CAN_Message_ID( void )
{
    switch(cmd_parserData.id)
    {
        case CAN_IOCTRL_BTN_IND_TWRLMP_ID:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\ncCmdParser: Msg ID rxcvd = BTN TWRLMP IND\n");
            parse_IOCtrl_CAN_Datafield_Btn_Ind_Twrlmp();
        break;
        case CAN_IOCTRL_STATE_CHANGE_ID:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Msg ID rxcvd = State Change\n");
            parse_IOCtrl_CAN_Datafield_State();
        break;
        case CAN_BOARD_ACTIVE_PING_ID:
            if( cmd_parserData.byte_0 == IOCTRL_BOARD_ID )
            {
                uint32_t can_msg_id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
                uint8_t board_id = IOCTRL_BOARD_ID; //cmd_parserData.byte_0;
                send_Data_to_CAN_Queue( can_msg_id, &board_id, 1 );
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Msg ID rxcvd = Board Active Ping\nSent Board Active Ping Reply\n");
            }
        break;
        case CAN_IOCTRL_BTN_LIMIT_PRESS_ID: break;
        case CAN_IOCTRL_TO_SYS_CTRL_ID: break;
        case CAN_IOCTRL_TO_AX_CTRL_ID: break;
        default: break;
    }    
    return;
}

static void parse_Opcode( int32_t opcode_num )
{
    bool is_state = false;
    switch(opcode_num)
    {
        case 0: // ATBOF
            cmd_parserData.byte_0 = BUZZ_OFF_BUTTON;
            cmd_parserData.byte_1 = IO_C_ENABLE;
        break;
        case 1: // ATPAU
            cmd_parserData.byte_0 = PAUSE_BUTTON;
            cmd_parserData.byte_1 = IO_C_ENABLE;
        break;
        case 2: // ATRUN
            cmd_parserData.byte_0 = RUN_BUTTON;
            cmd_parserData.byte_1 = IO_C_ENABLE;
        break;
        case 3: // ATSTP
            cmd_parserData.byte_0 = STOP_BUTTON;
            cmd_parserData.byte_1 = IO_C_ENABLE;
        break;
        case 4: // BOFDR
            cmd_parserData.byte_0 = BUZZ_OFF_DR_STATE;
            is_state = true;
        break;
        case 5: // BOFER
            cmd_parserData.byte_0 = BUZZ_OFF_ER_STATE;
        break;
        case 6: // BZROF
            cmd_parserData.byte_0 = BUZZ_OFF_BUTTON;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 7: // BZRON
            cmd_parserData.byte_0 = BUZZ_OFF_BUTTON;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 8: // DHBLS
            cmd_parserData.byte_0 = DISABLE_ALL_STATE;
            is_state = true;
        break;
        case 9: // DOORC
            cmd_parserData.byte_0 = FRONT_DOOR_LIMIT;
            cmd_parserData.byte_1 = IO_C_CHECK_STATUS;
        break;
        case 10: // DTBOF
            cmd_parserData.byte_0 = BUZZ_OFF_BUTTON;
            cmd_parserData.byte_1 = IO_C_DISABLE;
        break;
        case 11: // DTPAU
            cmd_parserData.byte_0 = PAUSE_BUTTON;
            cmd_parserData.byte_1 = IO_C_DISABLE;
        break;
        case 12: // DTRUN
            cmd_parserData.byte_0 = RUN_BUTTON;
            cmd_parserData.byte_1 = IO_C_DISABLE;
        break;
        case 13: // DTSTP
            cmd_parserData.byte_0 = STOP_BUTTON;
            cmd_parserData.byte_1 = IO_C_DISABLE;
        break;
        case 14: // HWBDB
            cmd_parserData.byte_0 = DISABLE_HW_BTNS;
            is_state = true;
        break;
        case 15: // IEFAI
            cmd_parserData.byte_0 = FAIL_STATE;
            is_state = true;
        break;
        case 16: // IEPAS
            cmd_parserData.byte_0 = PASS_STATE;
            is_state = true;
        break;
        case 17: // IEPAU
            cmd_parserData.byte_0 = PAUSE_STATE;
            is_state = true;
        break;
        case 18: // IERUN
            cmd_parserData.byte_0 = RUN_STATE;
            is_state = true;
        break;
        case 19: // IESEL
            cmd_parserData.byte_0 = SELECT_STATE;
            is_state = true;
        break;
        case 20: // PAUOF
            cmd_parserData.byte_0 = PAUSE_LED;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 21: // PAUON
            cmd_parserData.byte_0 = PAUSE_LED;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 22: // RUNOF
            cmd_parserData.byte_0 = RUN_LED;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 23: // RUNON
            cmd_parserData.byte_0 = RUN_LED;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 24: // SOLOF
            cmd_parserData.byte_0 = CLEANING_UNIT_SOL;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 25: // SOLON
            cmd_parserData.byte_0 = CLEANING_UNIT_SOL;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 26: // STPOF
            cmd_parserData.byte_0 = STOP_LED;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 27: // STPON
            cmd_parserData.byte_0 = STOP_LED;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 28: // STMP0
            cmd_parserData.byte_0 = STAMPING_RELAY;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 29: // STMP1
            cmd_parserData.byte_0 = STAMPING_RELAY;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 30: // TBZR0
            cmd_parserData.byte_0 = TWRLMP5_BUZZER;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 31: // TBZR1
            cmd_parserData.byte_0 = TWRLMP5_BUZZER;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 32: // TGRN0
            cmd_parserData.byte_0 = TWRLMP3_GREEN;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 33: // TGRN1
            cmd_parserData.byte_0 = TWRLMP3_GREEN;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 34: // TRED0
            cmd_parserData.byte_0 = TWRLMP1_RED;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 35: // TRED1
            cmd_parserData.byte_0 = TWRLMP1_RED;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 36: // TYEL0
            cmd_parserData.byte_0 = TWRLMP2_YELLOW;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 37: // TYEL1
            cmd_parserData.byte_0 = TWRLMP2_YELLOW;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 38: // WIND0
            cmd_parserData.byte_0 = WINDING_RELAY;
            cmd_parserData.byte_1 = IO_C_PIN_OFF;
        break;
        case 39: // WIND1
            cmd_parserData.byte_0 = WINDING_RELAY;
            cmd_parserData.byte_1 = IO_C_PIN_ON;
        break;
        case 40: // HYBT0
        {
            cmd_parserData.byte_0 = IO_C_DEFAULT;
            uint32_t can_msg_id = CAN_IOCTRL_TO_TOP_AX_CTRL_ID;
            uint8_t hybrid_trigger = 0x08;
            uint8_t disable = 0x04;
            uint8_t can_data[2] = {hybrid_trigger, disable};
            send_Data_to_CAN_Queue( can_msg_id, can_data, 2 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Sent Disable Hybrid Trigger to AxC\n");
        }
        break;
        case 41: // HYBT1
        {
            cmd_parserData.byte_0 = IO_C_DEFAULT;
            uint32_t can_msg_id = CAN_IOCTRL_TO_TOP_AX_CTRL_ID;
            uint8_t hybrid_trigger = 0x08;
            uint8_t enable = 0x03;
            uint8_t can_data[2] = {hybrid_trigger, enable};
            send_Data_to_CAN_Queue( can_msg_id, can_data, 2 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Sent Enable Hybrid Trigger to AxC\n");
        }
        break;
        default: break;
    }
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nPeripheral Byte 0 = 0x%x | Operation Byte 1 = 0x%x\n",
                    cmd_parserData.byte_0, cmd_parserData.byte_1);
    (is_state) ? parse_IOCtrl_CAN_Datafield_State()
               : parse_IOCtrl_CAN_Datafield_Btn_Ind_Twrlmp();
    return;
}

static void parse_CAN_Msg_Opcode( void )
{
    if(cmd_parserData.id == CAN_IOCTRL_BTN_IND_TWRLMP_ID)
    {
        /*while (left <= right) 
        {
            int32_t mid = (left + right) / 2;
            int32_t cmp = memcmp(cmd_parserData.opcode, ioctrl_opcodes[mid].name, IOCTRL_OPCODE_LENGTH);
            
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nOpcode1 = %s | Opcode2 = %s", cmd_parserData.opcode, ioctrl_opcodes[mid].name);
            
            if (cmp == 0) 
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nOpcode is valid\n");
                parse_Opcode(ioctrl_opcodes[mid].num);
                break;
            } 
            else if (cmp < 0) 
            {
                right = mid - 1;
            } 
            else 
            {
                left = mid + 1;
            }
        }*/
        
        for(int32_t i = 0; i < (sizeof(ioctrl_opcodes) / sizeof(ioctrl_opcodes[0]) ); i++) {
            int32_t cmp = memcmp(cmd_parserData.opcode, ioctrl_opcodes[i].name, IOCTRL_OPCODE_LENGTH);
            if (cmp == 0) {
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nOpcode is valid\n");
                parse_Opcode(ioctrl_opcodes[i].num);
                break;
            } else {
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n##-Opcode is INVALID-##\n");
            }
        }
    }
    return;
}

/******************************************************************************
  Function:
    void CMD_PARSER_Tasks ( void )

  Remarks:
    See prototype in cmd_parser.h.
 */

void CMD_PARSER_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( cmd_parserData.state )
    {
        /* Application's initial state. */
        case CMD_PARSER_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                cmd_parserData.state = CMD_PARSER_SERVICE_STATE;
            }
            break;
        }

        case CMD_PARSER_SERVICE_STATE:
        {
            cmd_parserData.state = CMD_PARSER_SUSPEND_STATE;
            break;
        }
        case CMD_PARSER_SUSPEND_STATE:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Going to Suspend, Waiting for CAN Command from CAN Task...");
            xQueueReceive(xcmd_parser_queue, &cmd_parserData.buffer, portMAX_DELAY);
            if( (cmd_parserData.buffer.dlc == 1) || (cmd_parserData.buffer.dlc == 2) ) {
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nCmdParser: CAN Packet DLC = %d\n", cmd_parserData.buffer.dlc);
                cmd_parserData.state = CMD_PARSER_PARSE_STATE;
            } else if(cmd_parserData.buffer.dlc == 5) {
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nCmdParser: CAN Packet DLC = 5\n");
                cmd_parserData.state = CMD_PARSER_OPCODE_PARSE_STATE;
            }
            break;
        }
        case CMD_PARSER_PARSE_STATE:
        {
            cmd_parserData.id = cmd_parserData.buffer.msg_id;
            cmd_parserData.byte_0 = cmd_parserData.buffer.data[0];
            cmd_parserData.byte_1 = cmd_parserData.buffer.data[1];
            
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nCmdParser: CAN Queue Received | Msg ID = 0x%x 0x%x 0x%x 0x%x | Data[0] = 0x%x | Data[1] = 0x%x \n",
                            GET_AD(cmd_parserData.id), GET_CMD(cmd_parserData.id), GET_TYP(cmd_parserData.id), GET_MOT(cmd_parserData.id),
                            cmd_parserData.byte_0, cmd_parserData.byte_1);
        
            parse_CAN_Message_ID();
            
            cmd_parserData.state = CMD_PARSER_SUSPEND_STATE;
            
            break;
        }
        
        case CMD_PARSER_OPCODE_PARSE_STATE:
        {
            cmd_parserData.id = cmd_parserData.buffer.msg_id;
            
            // Store the 5 length Opcode.
            for(uint32_t i = 0; i < IOCTRL_OPCODE_LENGTH; i++) { 
                cmd_parserData.opcode[i] = cmd_parserData.buffer.data[i]; 
            }
            
            // Check for NULL terminating character ('\0') at the end of the Opcode.
            if(cmd_parserData.opcode[IOCTRL_OPCODE_LENGTH - 1] != '\0') { 
                cmd_parserData.opcode[IOCTRL_OPCODE_LENGTH - 1] = '\0';
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Opcode received without terminating \\0...Added \\0 at the end of the Opcode\n");
            }
            
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nCmdParser: CAN Queue Received | Msg ID = 0x%x 0x%x 0x%x 0x%x | ",
                            GET_AD(cmd_parserData.id), GET_CMD(cmd_parserData.id), GET_TYP(cmd_parserData.id), GET_MOT(cmd_parserData.id) );
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nOpcode: Data = %s\n", cmd_parserData.opcode);
            
            if(cmd_parserData.id == CAN_IOCTRL_BTN_IND_TWRLMP_ID) {
                parse_CAN_Msg_Opcode();
            } else if( (cmd_parserData.id == CAN_BOARD_ACTIVE_PING_ID) && (cmd_parserData.byte_0 == IOCTRL_BOARD_ID) ) {
                uint32_t can_msg_id = CAN_REPLY_BOARD_ACTIVE_PING_ID;
                uint8_t board_id = IOCTRL_BOARD_ID; //cmd_parserData.byte_0;
                send_Data_to_CAN_Queue( can_msg_id, &board_id, 1 );
            }
            
            cmd_parserData.state = CMD_PARSER_SUSPEND_STATE;
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
