/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    system_state.c

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

#include "system_state.h"

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
    This structure should be initialized by the SYSTEM_STATE_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

SYSTEM_STATE_DATA system_stateData;

static const Event_Bit_Map_t bit_map[] = {
    { SET_EVENT_GRP_SELECT_STATE_FLAG,         SYSTEM_STATE_SELECT,          " SELECT State Flag Received\n" },
    { SET_EVENT_GRP_RUN_STATE_FLAG,            SYSTEM_STATE_RUN,             " RUN State Flag Received\n" },
    { SET_EVENT_GRP_PASS_STATE_FLAG,           SYSTEM_STATE_PASS,            " PASS State Flag Received\n" },
    { SET_EVENT_GRP_PAUSE_STATE_FLAG,          SYSTEM_STATE_PAUSE,           " PAUSE State Flag Received\n" },
    { SET_EVENT_GRP_FAIL_STATE_FLAG,           SYSTEM_STATE_FAIL,            " FAIL State Flag Received\n" },
    { SET_EVENT_GRP_BUZZOFFDR_STATE_FLAG,      SYSTEM_STATE_BZROFFDR,        " BZROFFDR State Flag Received\n" },
    { SET_EVENT_GRP_BUZZOFFER_STATE_FLAG,      SYSTEM_STATE_BZROFFER,        " BZROFFER State Flag Received\n" },
    { SET_EVENT_GRP_DISABLE_ALL_STATE_FLAG,    SYSTEM_STATE_DISABLE_ALL,     " DISABLE ALL State Flag Received\n" },
    { SET_EVENT_GRP_DISABLE_HW_BTN_STATE_FLAG, SYSTEM_STATE_DISABLE_HW_BTNS, " DISABLE HW BTNS State Flag Received\n" },
    { SET_ALL_BTN_EN_DIS_FLAGS,                SYSTEM_STATE_EN_DIS_BTN,      " EN DIS BUTTONS State Flag Received\n" },
    { SET_ALL_BTN_FLAGS,                       SYSTEM_STATE_BUTTON_PRESS,    " Button Pressed "},
};

static uint32_t en_dis_able_button_tracker = 0xFF; // Used to track what buttons are enabled and disabled.

static uint8_t btn_lim_press_can_data[2] = { 0 }; // 0th Index -> Peripheral | 1st Index -> Operation.

static bool dhbls = false;     // Boolean decide whether to send Door Limit(s) opened CAN Message. true -> send | false -> don't send.

Can_Queue_t can_queue;
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
    void SYSTEM_STATE_Initialize ( void )

  Remarks:
    See prototype in system_state.h.
 */

void SYSTEM_STATE_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    system_stateData.state = SYSTEM_STATE_STATE_INIT;
    
    //memset(system_stateData.dbg_log_msg, 0x00, sizeof(system_stateData.dbg_log_msg) );
    
    //system_state_log.log_data_ptr = &system_stateData.dbg_log_msg;
    //system_state_log.task_id = SYSTEM_STATE_TASK_ID;
    
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSystem State Task initialized\n");

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

void send_Data_to_CAN_Queue( int32_t msgid, uint8_t *data_to_wr, uint8_t data_length_code )
{
    if(data_length_code > 8)
    {
        // Throw error.
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "\n#####-System State Task: CAN Write DLC > 8-#####\n");
        return;
    }
    can_queue = (Can_Queue_t){
        .operation_flag = CAN_WRITE_FLAG,
        .msg_id = msgid,
        .dlc = data_length_code
    };
    memcpy(can_queue.data, data_to_wr, data_length_code);
    xQueueSend(xcan_rd_wr_queue, &can_queue, portMAX_DELAY);
    return;
}

static void parse_Enable_Disable_Button( void )
{
    uint32_t active_event_flag = system_stateData.event_grp_val & SET_ALL_BTN_EN_DIS_FLAGS;
    
    switch(active_event_flag)
    {
        case SET_EVENT_GRP_RUN_BTN_EN_FLAG:     SET_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);       break;
        case SET_EVENT_GRP_RUN_BTN_DIS_FLAG:    CLEAR_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);     break;
        case SET_EVENT_GRP_PAUSE_BTN_EN_FLAG:   SET_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);     break;
        case SET_EVENT_GRP_PAUSE_BTN_DIS_FLAG:  CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);   break;
        case SET_EVENT_GRP_STOP_BTN_EN_FLAG:    SET_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);      break;
        case SET_EVENT_GRP_STOP_BTN_DIS_FLAG:   CLEAR_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);    break;
        case SET_EVENT_GRP_BZROFF_BTN_EN_FLAG:  SET_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);    break;
        case SET_EVENT_GRP_BZROFF_BTN_DIS_FLAG: CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);  break;
        default: break;
    }
    system_stateData.bits_to_wait_for = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_ALL_BTN_FLAGS );
    return;
}

static void process_Button_Door_Limit_Press( void )
{
    uint32_t active_button_press_event_flag = system_stateData.event_grp_val 
                                              & SET_ALL_BTN_FLAGS;
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nSST: bool DHBLS = %d\n", dhbls);
    uint32_t can_msg_id = CAN_ID(0x00, 0x00, 0x00, CAN_IOCTRL_BTN_LIMIT_PRESS_ID);
    bool btn_or_lim = false;
    if(!dhbls)
    {
        
        switch(active_button_press_event_flag)
        {
            case SET_EVENT_GRP_RUN_BUTTON_FLAG:
                if(CHECK_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT))
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Run Button Pressed Parsed\n");
                    memcpy(btn_lim_press_can_data, (uint8_t[2]){CMD_RUN, 0}, sizeof(btn_lim_press_can_data) );
                    btn_or_lim = true;
                }
                else
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Run Button Pressed Not Parsed. Run Button is Disabled\n");
                }
            break;
            case SET_EVENT_GRP_PAUSE_BUTTON_FLAG:
                if(CHECK_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT))
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Paused Button Pressed Parsed\n");
                    memcpy(btn_lim_press_can_data, (uint8_t[2]){CMD_PAUSE, 0}, sizeof(btn_lim_press_can_data) );
                    btn_or_lim = true;
                }
                else
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Pause Button Pressed Not Parsed. Pause Button is Disabled\n");
                }                      
            break;
            case SET_EVENT_GRP_STOP_BUTTON_FLAG:
                if(CHECK_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT))
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: STOP Button Pressed Parsed\n");
                    memcpy(btn_lim_press_can_data, (uint8_t[2]){CMD_STOP, 0}, sizeof(btn_lim_press_can_data) );
                    btn_or_lim = true;
                }
                else
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: STOP Button Pressed Not Parsed. STOP Button is Disabled\n");
                }                     
            break;
            case SET_EVENT_GRP_BZROFF_BUTTON_FLAG:
                if(CHECK_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT))
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Buzzer Off Button Pressed Parsed\n");
                    if( (TWRLMP5_BUZ_Get() == 1) || (system_stateData.current_system_state == SYSTEM_STATE_FAIL) )
                    {
                        TWRLMP5_BUZ_Clear();
                        CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
                        BZROFF_LED_Clear();
                        SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCleared Towerlamp Buzzer. Disabled Buzzer Off Button and cleared its LED.\n");
                    }
                    memcpy(btn_lim_press_can_data, (uint8_t[2]){CMD_BUZZER_OFF, 0}, sizeof(btn_lim_press_can_data) );
                    btn_or_lim = true;
                }
                else
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Buzzer Off Button Pressed Not Parsed. Buzzer Off Button is Disabled\n");
                }                       
            break;
            default: break;
        }
        //if( (btn_lim_press_can_data[0] != 0) && (btn_lim_press_can_data[1] != 0) )
        if(btn_or_lim)
        {
            send_Data_to_CAN_Queue( can_msg_id, &btn_lim_press_can_data[0], 1 );
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nSST: msg_id = 0x%x 0x%x 0x%x 0x%x\n", 
                    GET_AD(can_msg_id), GET_CMD(can_msg_id), GET_TYP(can_msg_id), GET_MOT(can_msg_id) );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Sent Button Pressed CAN Queue to CAN Task\n");
        }
        if(system_stateData.event_grp_val & SET_EVENT_GRP_F_B_DOOR_LIM_FLAG)
        {
            // For Front Door Limit.
            btn_lim_press_can_data[0] = CMD_DOOR_UNLOCK;   // Byte 0 -> Peripheral Byte.
            btn_lim_press_can_data[1] = 0;       // Byte 1 -> Operation Byte.
            send_Data_to_CAN_Queue( can_msg_id, &btn_lim_press_can_data[0], 1 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Front Door Limit Triggered\n");
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Back Door Limit Triggered\n");
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Sent Door Limit Pressed CAN Queue to CAN Task\n");
        }
        else if(system_stateData.event_grp_val & SET_EVENT_GRP_EPANEL_DOOR_LIM_FLAG)
        {
            // For Front Door Limit.
            btn_lim_press_can_data[0] = CMD_DOOR_UNLOCK;  // Byte 0 -> Peripheral Byte.
            btn_lim_press_can_data[1] = 0;       // Byte 1 -> Operation Byte.
            send_Data_to_CAN_Queue( can_msg_id, &btn_lim_press_can_data[0], 1 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: E-Panel Door Limit Triggered\n");
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Sent Door Limit Pressed CAN Queue to CAN Task\n");
        }
    }
    return;
}

/******************************************************************************
  Function:
    void SYSTEM_STATE_Tasks ( void )

  Remarks:
    See prototype in system_state.h.
 */

void SYSTEM_STATE_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( system_stateData.state )
    {
        /* Application's initial state. */
        case SYSTEM_STATE_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                system_stateData.state = SYSTEM_STATE_SERVICE_TASK;
                
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSystem State Init\n");
            }
            break;
        }
        case SYSTEM_STATE_SERVICE_TASK:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nIn System State Service Task.\n");
            
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = SET_ALL_EVENT_GROUP_BIT_FLAGS,
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            }; 
            //system_stateData.state = SYSTEM_STATE_SELECT;       // LED STRIP TESTING
            break;
        }
        case SYSTEM_STATE_SELECT:
        {
            // Run Button Enabled. Pause, Stop and Buzzer Off buttons disabled.
            // TWRLMP RYG LOW | Run LED High, Pause, Stop and Buzzer Off LEDs LOW.
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Select-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            // HIGH the required Outputs.
            vTaskSuspendAll();
            {
                LED_SetPixel(LED_STRIP_LENGTH - 1, 0, 0, 255);      // Blue.
                LED_Show_DMA();
            }
            xTaskResumeAll();
            RUN_LED_Set();
            STAMPING_Clear();
            // Stamping and Winding?
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS | \
                                            SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            SET_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            
            //vTaskDelay(pdMS_TO_TICKS(500));                // LED STRIP TESTING
            //system_stateData.state = SYSTEM_STATE_RUN;      // LED STRIP TESTING
            
            
            break;
        }
        case SYSTEM_STATE_RUN:
        {
            // Pause and Stop buttons are ENABLED, Run and Buzzer Off buttons are DISABLED.
            // TWRLMP Green, Pause LED and Stop LED HIGH, rest all LOW.
            // Cleaning Unit Solenoid HIGH.
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Run-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            // HIGH the required Outputs.
            PAUSE_LED_Set();
            STOP_LED_Set();
            vTaskSuspendAll();
            {
                LED_SetPixel(LED_STRIP_LENGTH - 1, 0, 255, 0);
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP3_G_Set();
            STAMPING_Clear();
            CLU_SOL_Clear();
            // Stamping and Winding?
            
            // Sending Sag Enable CAN Message to System Controller.
            uint8_t sag_enable = SAG_ENABLE;
            //vTaskDelay( pdMS_TO_TICKS(10) );
            send_Data_to_CAN_Queue( CAN_IOCTRL_TO_SYS_CTRL_ID, &sag_enable, 1 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Sent Sag Enable CAN Message to System Controller\n");
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS | \
                                            SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            CLEAR_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            SET_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            SET_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            
            //vTaskDelay(pdMS_TO_TICKS(200));                // LED STRIP TESTING
            //system_stateData.state = SYSTEM_STATE_PASS;      // LED STRIP TESTING
            
            break;
        }
        case SYSTEM_STATE_PASS:
        {
            // Pause and Stop Buttons are ENABLED, Run and Buzzer Off Buttons are DISABLED.
            // 
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Pass-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            PAUSE_LED_Set();
            STOP_LED_Set();
            vTaskSuspendAll();
            {
                LED_SetPixel(LED_STRIP_LENGTH - 1, 0, 255, 0);
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP3_G_Set();
            STAMPING_Clear();
            CLU_SOL_Clear();
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS | \
                                            SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            CLEAR_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            SET_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            SET_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            
            //vTaskDelay(pdMS_TO_TICKS(200));                // LED STRIP TESTING
            //system_stateData.state = SYSTEM_STATE_PAUSE;      // LED STRIP TESTING
            
            break;
        }
        case SYSTEM_STATE_PAUSE:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Pause-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Show_DMA();
                LED_Clear();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            RUN_LED_Set();
            STOP_LED_Set();
            vTaskSuspendAll();
            {
                LED_SetPixel(LED_STRIP_LENGTH - 1, 200, 50, 0);        // Yellow.
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP2_Y_Set();
            STAMPING_Set();
            CLU_SOL_Set();
             
            // Sending Sag Disable CAN Message to System Controller.
            uint8_t sag_disable = SAG_DISABLE;
            send_Data_to_CAN_Queue( CAN_IOCTRL_TO_SYS_CTRL_ID, &sag_disable, 1 );
            send_Data_to_CAN_Queue( CAN_SYSCTRL_TO_AX_CTRL_SAG_ID, &sag_disable, 1 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Sent Sag Disable CAN Message to System Controller and Axis Controller\n");
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS | \
                                            SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            SET_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            SET_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            
            //vTaskDelay(pdMS_TO_TICKS(200));                // LED STRIP TESTING
            //system_stateData.state = SYSTEM_STATE_FAIL;      // LED STRIP TESTING
            
            break;
        }
        case SYSTEM_STATE_FAIL:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Fail-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            RUN_LED_Set();
            STOP_LED_Set();
            BZROFF_LED_Set();
            vTaskSuspendAll();
            {
                LED_SetPixel(LED_STRIP_LENGTH - 1, 255, 0, 0);      // Red.
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Set();
            TWRLMP5_BUZ_Set();
            STAMPING_Set();
            CLU_SOL_Set();
            
            // Sending Sag Disable CAN Message to System Controller.
            uint8_t sag_disable = SAG_DISABLE;
            send_Data_to_CAN_Queue( CAN_IOCTRL_TO_SYS_CTRL_ID, &sag_disable, 1 );
            send_Data_to_CAN_Queue( CAN_SYSCTRL_TO_AX_CTRL_SAG_ID, &sag_disable, 1 );
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCmdParser: Sent Sag Disable CAN Message to System Controller and Axis Controller\n");
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS | \
                                            SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            SET_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            SET_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            //CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            
            //vTaskDelay(pdMS_TO_TICKS(200));                // LED STRIP TESTING
            //system_stateData.state = SYSTEM_STATE_SERVICE_TASK;      // LED STRIP TESTING
            
            break;
        }
        case SYSTEM_STATE_BZROFFDR:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State BZROFFDR-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            RUN_LED_Set();
            STOP_LED_Set();
            BZROFF_LED_Set();
            
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS | \
                                            SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            SET_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            break;
        }
        case SYSTEM_STATE_BZROFFER:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State BZROFFER-----\n");
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            dhbls = false;
            
            RUN_LED_Set();
            STOP_LED_Set();
            BZROFF_LED_Set();
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_DOOR_LIMITS_FLAGS
                                            | SET_ALL_BTN_FLAGS),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            //CLEAR_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            //CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            //CLEAR_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            //CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            break;
        }
        case SYSTEM_STATE_DISABLE_ALL:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Disable All-----\n");
            
            // Send CAN Message to Sys Ctrl to stop LCS and Ax Ctrl to stop all motors.
            
            // LOW all Indicator Outputs.
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            vTaskSuspendAll();
            {
                LED_Clear();
                LED_Show_DMA();
            }
            xTaskResumeAll();
            TWRLMP1_R_Clear();
            TWRLMP2_Y_Clear();
            TWRLMP3_G_Clear();
            TWRLMP4_B_Clear();
            TWRLMP5_BUZ_Clear();
            
            dhbls = true;
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            CLEAR_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            break;
        }
        case SYSTEM_STATE_DISABLE_HW_BTNS:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Disable HW Buttons-----\n");
            
            RUN_LED_Clear();
            PAUSE_LED_Clear();
            STOP_LED_Clear();
            BZROFF_LED_Clear();
            
            dhbls = false;
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = SET_ALL_STATE_FLAGS,
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            en_dis_able_button_tracker = 0xFF;
            CLEAR_BTN_BIT(en_dis_able_button_tracker, RUN_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, PAUSE_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, STOP_BTN_BIT);
            CLEAR_BTN_BIT(en_dis_able_button_tracker, BZROFF_BTN_BIT);
            break;
        }
        case SYSTEM_STATE_EN_DIS_BTN:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Enable Disable Buttons-----\n");
            
            parse_Enable_Disable_Button();
            
            system_stateData = (SYSTEM_STATE_DATA)
            {
                .clear_bits_after_unblock = pdTRUE,
                .wait_for_all_bits        = pdFALSE,
                .bits_to_wait_for         = ( SET_ALL_STATE_FLAGS | SET_ALL_BTN_EN_DIS_FLAGS | SET_ALL_BTN_FLAGS ),
                .bits_to_clear            = system_stateData.bits_to_wait_for,
                .current_system_state     = system_stateData.state,
                .state                    = SYSTEM_STATE_SUSPEND
            };
            break;
        }
        case SYSTEM_STATE_BUTTON_PRESS:
        {
            //if( (system_stateData.current_system_state == SYSTEM_STATE_SUSPEND ) \
            //    || (system_stateData.current_system_state == SYSTEM_STATE_EN_DIS_BTN ) )
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: In System State Button Press State\n");

                process_Button_Door_Limit_Press();
                
                system_stateData = (SYSTEM_STATE_DATA)
                {
                    .clear_bits_after_unblock = pdTRUE,
                    .wait_for_all_bits        = pdFALSE,
                    .bits_to_wait_for         = ( SET_ALL_EVENT_GROUP_BIT_FLAGS ),
                    .bits_to_clear            = ( SET_ALL_EVENT_GROUP_BIT_FLAGS ),
                    .current_system_state     = system_stateData.current_system_state,
                    .state                    = SYSTEM_STATE_SUSPEND
                };
            }
            break;
        }
        case SYSTEM_STATE_SUSPEND:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n-----In System State Suspend-----\n");
            
            system_stateData.event_grp_val = xEventGroupWaitBits( xbtn_state_event_grp,
                                                                  system_stateData.bits_to_wait_for,
                                                                  system_stateData.clear_bits_after_unblock,
                                                                  system_stateData.wait_for_all_bits,
                                                                  portMAX_DELAY );
            
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nSST: Suspend State Event Group received\n");
            
            for(size_t idx = 0; idx < sizeof(bit_map)/sizeof(bit_map[0]); idx++ )
            {
                if(system_stateData.event_grp_val & bit_map[idx].bit & system_stateData.bits_to_wait_for)
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, bit_map[idx].debug_msg);
                    system_stateData.state = bit_map[idx].state;
                    break;  // Get out of the loop on the first hit.
                }
            }
            taskENTER_CRITICAL();
            {
                system_stateData.bits_to_clear = SET_ALL_EVENT_GROUP_BIT_FLAGS;
                xEventGroupClearBits( xbtn_state_event_grp, system_stateData.bits_to_clear);
            }
            taskEXIT_CRITICAL();
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            //printf("\nIn System State DEFAULT\n");
            break;
        }
    }
}
/*******************************************************************************
 End of File
 */
