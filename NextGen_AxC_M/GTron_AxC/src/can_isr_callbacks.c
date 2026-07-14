#include "can_isr_callbacks.h"

void CAN1_RxFifo0Callback ( uint8_t numberOfMessage, uintptr_t context )
{
    can1_rx_fifo0_cb_info.buf_cnt += 1;
    can1_rx_fifo0_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo0_cb_info.context = context;
    
    Can_Frame_t can_frame = { .direction = CAN_FROM_BUS };
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(gq_can_work, &can_frame, &woken);
    portYIELD_FROM_ISR(woken);
    return;
}

void CAN1_RxFifo1Callback ( uint8_t numberOfMessage, uintptr_t context )
{
    can1_rx_fifo1_cb_info.buf_cnt += 1;
    can1_rx_fifo1_cb_info.no_of_msgs = numberOfMessage;
    can1_rx_fifo1_cb_info.context = context;
    
    Can_Frame_t can_frame = { .direction = CAN_FROM_BUS };
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(gq_can_work, &can_frame, &woken);
    portYIELD_FROM_ISR(woken);
    return;
}

void CAN1_TxFifoCallback(uintptr_t context)
{
    xferContext = context;
    status = CAN1_ErrorGet();
    if( ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) ||
        ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC) ) {
        can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
    } else {
        can_state = APP_STATE_CAN_XFER_ERROR;
    }
    return;
}