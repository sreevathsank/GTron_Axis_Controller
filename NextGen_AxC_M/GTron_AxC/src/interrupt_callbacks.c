#include "interrupt_callbacks.h"


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
    
    return;
}