#include "interrupt_callbacks.h"

void run_Button_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Run Button Pressed!\n");
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_RUN_BUTTON_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    
    return;
}

void pause_Button_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Pause Button Pressed!\n");
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_PAUSE_BUTTON_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    
    return;
}

void stop_Button_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Stop Button Pressed!\n");
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_STOP_BUTTON_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    
    return;
}


void bzroff_Button_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Buzzer Off Button Pressed!\n");
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_BZROFF_BUTTON_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    
    return;
}

void f_Door_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Front Door Limit Triggered!\n");
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_F_B_DOOR_LIM_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    
    return;
}

void b_Door_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: Back Door Limit Triggered!\n");
    
    // Front and Back Door are connected electrically in series. So if one triggers, the other one also.
    
    return;
}

void epanel_Door_Interrupt_Callback( unsigned int val )
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nISR: E-Panel Door Limit Triggered!\n");
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR( xbtn_state_event_grp, SET_EVENT_GRP_EPANEL_DOOR_LIM_FLAG, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    
    return;
}

void EIC_Init_Callbacks( void )
{
    // Run Button Callback.
    EIC_CallbackRegister( EIC_PIN_7, run_Button_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_7 );
    
    // Pause Button Callback.
    EIC_CallbackRegister( EIC_PIN_8, pause_Button_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_8 );
    
    // Stop Button Callback.
    EIC_CallbackRegister( EIC_PIN_9, stop_Button_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_9 );
    
    // Buzzer Off Button Callback.
    EIC_CallbackRegister( EIC_PIN_4, bzroff_Button_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_4 );
    
    // Front Door Limit Callback.
    EIC_CallbackRegister( EIC_PIN_6, f_Door_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_6 );
    
    // Back Door Limit Callback.
    EIC_CallbackRegister( EIC_PIN_3, b_Door_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_3 );
    
    // E Panel Button Callback.
    EIC_CallbackRegister( EIC_PIN_2, epanel_Door_Interrupt_Callback, 0 );
    EIC_InterruptEnable( EIC_PIN_2 );
    
    return;
}

// This function will be called by CAN PLIB when transfer is completed from Tx FIFO.
void CAN1_TxFifoCallback(uintptr_t context)
{
    xferContext = context;

    // Check CAN Status
    status = CAN1_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((CAN_STATE)context)
        {
            case APP_STATE_CAN_TRANSMIT:
            {
                can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
                break;
            }
            default:
                break;
        }
    }
    else
    {
        can_state = APP_STATE_CAN_XFER_ERROR;
    }
}

// This function will be called by CAN PLIB when Message received in Rx FIFO0.
void CAN1_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context)
{   
    can1_rx_fifo0_cb_info.buf_cnt += 1;
    can1_rx_fifo0_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo0_cb_info.context = context;
    can_queue_struct.operation_flag = CAN_READ_FLAG;
    can_queue_struct.buffer_X = CAN_BUFFER_FIFO_0;
    
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;
    xQueueSendFromISR(xcan_rd_wr_queue, &can_queue_struct, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    /*
    xferContext = context;

    // Check CAN Status.
    status = CAN1_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((CAN_STATE)context)
        {
            case APP_STATE_CAN_RECEIVE:
            {
                memset(rxFiFo0, 0x00, (numberOfMessage * CAN1_RX_FIFO0_ELEMENT_SIZE));
                if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, numberOfMessage, (CAN_RX_BUFFER *)rxFiFo0) == true)
                {
                    print_rx_message(numberOfMessage, (CAN_RX_BUFFER *)rxFiFo0, CAN1_RX_FIFO0_ELEMENT_SIZE, 0);
                    can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
                }
                else
                {
                    can_state = APP_STATE_CAN_XFER_ERROR;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        can_state = APP_STATE_CAN_XFER_ERROR;
    }
     */
    return;
}

// This function will be called by CAN PLIB when Message received in Rx FIFO1.
void CAN1_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context)
{
    can1_rx_fifo1_cb_info.buf_cnt += 1;
    can1_rx_fifo1_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo1_cb_info.context = context;
    can_queue_struct.operation_flag = CAN_READ_FLAG;
    can_queue_struct.buffer_X = CAN_BUFFER_FIFO_1;
    xQueueSendFromISR(xcan_rd_wr_queue, &can_queue_struct, 0);
    /*
    xferContext = context;

    // Check CAN Status.
    status = CAN1_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((CAN_STATE)context)
        {
            case APP_STATE_CAN_RECEIVE:
            {
                memset(rxFiFo1, 0x00, (numberOfMessage * CAN1_RX_FIFO1_ELEMENT_SIZE));
                if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_1, numberOfMessage, (CAN_RX_BUFFER *)rxFiFo1) == true)
                {
                    print_rx_message(numberOfMessage, (CAN_RX_BUFFER *)rxFiFo1, CAN1_RX_FIFO1_ELEMENT_SIZE, 1);
                    can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
                }
                else
                {
                    can_state = APP_STATE_CAN_XFER_ERROR;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        can_state = APP_STATE_CAN_XFER_ERROR;
    }
     */
    return;
}

/*
// This function will be called by CAN PLIB when Message received in Rx Buffer.
void CAN1_RxBufferCallback(uint8_t bufferNumber, uintptr_t context)
{
    xferContext = context;

    // Check CAN Status.
    status = CAN1_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
    {
        switch ((APP_STATES)context)
        {
            case APP_STATE_CAN_RECEIVE:
            {
                memset(rxBuffer, 0x00, CAN1_RX_BUFFER_ELEMENT_SIZE);
                if (CAN1_MessageReceive(bufferNumber, (CAN_RX_BUFFER *)rxBuffer) == true)
                {
                    print_message(1, (CAN_RX_BUFFER *)rxBuffer, CAN1_RX_BUFFER_ELEMENT_SIZE, 2);
                    state = APP_STATE_CAN_XFER_SUCCESSFUL;
                }
                else
                {
                    state = APP_STATE_CAN_XFER_ERROR;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        state = APP_STATE_CAN_XFER_ERROR;
    }
}
*/