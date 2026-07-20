/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    can.c

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

#include "can.h"

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
    This structure should be initialized by the CAN_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

CAN_DATA canData;

// Variable to save Tx/Rx transfer status and context.
uint32_t status = 0;
uint32_t xferContext = 0;

// Variable to save Tx/Rx message.
uint8_t loop_count = 0;
uint8_t user_input = 0;

// Variable to save application state.
volatile CAN_STATE can_state = APP_STATE_CAN_USER_INPUT;

uint8_t txFiFo[CAN1_TX_FIFO_BUFFER_SIZE] = { 0 };
uint8_t rxFiFo0[CAN1_RX_FIFO0_SIZE] = { 0 };
uint8_t rxFiFo1[CAN1_RX_FIFO1_SIZE] = { 0 };

Can_Queue_t can_task_queue;

unsigned int can_message_id = 0;
//static uint8_t rx_can_data[8] = { 0 };
CAN_RX_BUFFER *rx_can_buffer;

CAN_TX_BUFFER *txBuffer = NULL;

CAN_Cmd_Parser_t can_cmd_parse_info;

//alignas(CAN_RX_FIFO_ELEMENT_t) rxFiFo0[CAN_RX_FIFO_ELEMENT_COUNT];

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

/**
 * @brief Extracts the 29-bit CAN ID from a raw FIFO buffer.
 * @param ptr Pointer to the start of the 16-byte CAN message buffer.
 * @return The 29-bit CAN ID.
 */
uint32_t get_can_id_from_buffer(const uint8_t* ptr)
{
    // Reconstruct the first 32-bit word in little-endian format
    uint32_t first_word = (uint32_t)ptr[0] |
                          ((uint32_t)ptr[1] << 8) |
                          ((uint32_t)ptr[2] << 16) |
                          ((uint32_t)ptr[3] << 24);

    // Mask to get the lower 29 bits
    return first_word & 0x1FFFFFFFU;
}

/**
 * @brief Extracts the 4-bit Data Length Code (DLC) from a raw CAN FIFO buffer.
 * @param ptr Pointer to the start of the 16-byte CAN message buffer.
 * @return The 4-bit DLC value (0-8 for Classic CAN, 0-15 for CAN FD).
 */
uint8_t get_can_dlc_from_buffer(const uint8_t* ptr)
{
    // The DLC is in the second 32-bit word, which starts at an offset of 4 bytes.
    const uint8_t* word1_ptr = ptr + 4;

    // Reconstruct the second 32-bit word in little-endian format
    uint32_t second_word = (uint32_t)word1_ptr[0] |
                           ((uint32_t)word1_ptr[1] << 8) |
                           ((uint32_t)word1_ptr[2] << 16) |
                           ((uint32_t)word1_ptr[3] << 24);

    // The DLC is in bits 16-19. Shift right by 16 to move it to the LSB position.
    uint32_t dlc_shifted = second_word >> 16;
    
    // Mask with 0xF (binary 1111) to isolate the 4 bits.
    return (uint8_t)(dlc_shifted & 0xFU);
}

/**
 * @brief Copies the 8-byte data payload from a raw CAN FIFO buffer.
 * @param src_ptr Pointer to the start of the 16-byte CAN message buffer.
 * @param dest_ptr Pointer to a destination buffer (must be at least 8 bytes).
 */
void get_can_data_from_buffer(const uint8_t* src_ptr, uint8_t* dest_ptr, uint8_t dlc)
{
    if( (dlc > 8) || (src_ptr == NULL) || (dest_ptr == NULL) ) { return; }
    // The data payload starts at an offset of 8 bytes in the source buffer.
    const uint8_t* data_payload_start = src_ptr + dlc;
    
    // Copy 8 bytes from the CAN buffer to the destination buffer.
    // memcpy is highly optimized and often the fastest way to do a block copy.
    memcpy(dest_ptr, data_payload_start, dlc);
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void CAN_Initialize ( void )

  Remarks:
    See prototype in can.h.
 */

void CAN_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    canData.state = CAN_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


// Print Rx Message.
void print_rx_message(uint8_t numberOfMessage, CAN_RX_BUFFER *rxBuf, uint8_t rxBufLen, uint8_t rxFifoBuf)
{
    //uint8_t msgLength = 0;
    //uint32_t id = 0;
    
    switch(rxFifoBuf)
    {
        case 2: SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, " Rx Buffer :"); break;
        case 0: SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, " Rx FIFO0 :");  break;
        case 1: SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, " Rx FIFO1 :");  break;
        default: break;
    }

    for (uint8_t count = 0; count < numberOfMessage; count++)
    {
        /* Print message to Console */
        SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, " New Message Received\r\n");
        can_cmd_parse_info.msg_id = rxBuf->xtd ? rxBuf->id : READ_ID(rxBuf->id);
        can_cmd_parse_info.dlc = CANDlcToLengthGet(rxBuf->dlc);
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nRcvd Message - ID : 0x%x 0x%x 0x%x 0x%x | DLC : 0x%x\n", (unsigned int)GET_AD(can_cmd_parse_info.msg_id),
                                                                                               (unsigned int)GET_CMD(can_cmd_parse_info.msg_id),
                                                                                               (unsigned int)GET_TYP(can_cmd_parse_info.msg_id),
                                                                                               (unsigned int)GET_MOT(can_cmd_parse_info.msg_id),
                                                                                               (unsigned int)can_cmd_parse_info.dlc);
        SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "Rcvd Data : ");
        for(int32_t idx = 0; idx < can_cmd_parse_info.dlc; idx++)
        {
            can_cmd_parse_info.data[idx] = rxBuf->data[idx];
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "0x%x ", can_cmd_parse_info.data[idx]);
        }
        SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n");
        rxBuf = (CAN_RX_BUFFER *)((uint8_t *)rxBuf + rxBufLen);
    }
}

// Print Tx Message.
void print_tx_message(uint8_t numberOfMessage, CAN_TX_BUFFER *txBuf, uint8_t txBufLen)
{
    uint8_t length = 0;
    uint8_t msgLength = 0;
    uint32_t id = 0;

    for (uint8_t count = 0; count < numberOfMessage; count++)
    {
        /* Print message to Console */
        id = txBuf->xtd ? txBuf->id : WRITE_ID(txBuf->id);
        msgLength = CANDlcToLengthGet(txBuf->dlc);
        length = msgLength;
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nSent Message - ID : 0x%x Length : 0x%x ", id, (unsigned int)msgLength);
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "Sent Data : ");
        while(length)
        {
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "0x%x ", txBuf->data[msgLength - length--]);
        }
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\n");
        txBuf = (CAN_TX_BUFFER *)((uint8_t *)txBuf + txBufLen);
    }
}

// Message Length to Data length code.
uint8_t CANLengthToDlcGet(uint8_t length)
{
    uint8_t dlc = 0;

    if (length <= 8U)
    {
        dlc = length;
    }
    else if (length <= 12U)
    {
        dlc = 0x9U;
    }
    else if (length <= 16U)
    {
        dlc = 0xAU;
    }
    else if (length <= 20U)
    {
        dlc = 0xBU;
    }
    else if (length <= 24U)
    {
        dlc = 0xCU;
    }
    else if (length <= 32U)
    {
        dlc = 0xDU;
    }
    else if (length <= 48U)
    {
        dlc = 0xEU;
    }
    else
    {
        dlc = 0xFU;
    }
    return dlc;
}

// Data length code to Message Length.
uint8_t CANDlcToLengthGet(uint8_t dlc)
{
    uint8_t msgLength[] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};
    return msgLength[dlc];
}

void CAN1_Write(unsigned int msg_id, uint8_t *data_to_wr, unsigned int data_length_code)
{
    memset(txFiFo, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    txBuffer = (CAN_TX_BUFFER *)txFiFo;
    txBuffer->id = msg_id;
    txBuffer->dlc = data_length_code;
    txBuffer->xtd = 1;
    for (loop_count = 0; loop_count < txBuffer->dlc; loop_count++)
    {
        txBuffer->data[loop_count] = data_to_wr[loop_count];
    }                
    //CAN1_TxFifoCallbackRegister(CAN1_TxFifoCallback, (uintptr_t)APP_STATE_CAN_TRANSMIT );
    can_state = APP_STATE_CAN_IDLE;
    if (CAN1_MessageTransmitFifo(1, txBuffer) == false)
    {
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nFailed to send CAN Message\n");
    }
    else
    {
        print_tx_message(1, txBuffer, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    }
    return;
}

void CAN1_Read( void )
{
    if(can1_rx_fifo0_cb_info.buf_cnt)
    {
        can1_rx_fifo0_cb_info.buf_cnt -= 1;
        // Check CAN Status.
        status = CAN1_ErrorGet();

        if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
        {
            switch ((CAN_STATE)can1_rx_fifo0_cb_info.context)
            {
                case APP_STATE_CAN_RECEIVE:
                {
                    memset(rxFiFo0, 0x00, (can1_rx_fifo0_cb_info.no_of_msgs * CAN1_RX_FIFO0_ELEMENT_SIZE));
                    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, can1_rx_fifo0_cb_info.no_of_msgs, (CAN_RX_BUFFER *)rxFiFo0) == true)
                    {
                        print_rx_message(can1_rx_fifo0_cb_info.no_of_msgs, (CAN_RX_BUFFER *)rxFiFo0, CAN1_RX_FIFO0_ELEMENT_SIZE, 0);
                        can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
                        canData.state = CAN_STATE_SERVICE_TASKS;
                    }
                    else
                    {
                        can_state = APP_STATE_CAN_XFER_ERROR;
                    }
                    break;
                }
                default: break;
            }
        }
        else
        {
            can_state = APP_STATE_CAN_XFER_ERROR;
        }
    }
    else if(can1_rx_fifo1_cb_info.buf_cnt)
    {
        can1_rx_fifo1_cb_info.buf_cnt -= 1;
        // Check CAN Status.
        status = CAN1_ErrorGet();

        if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) || ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC))
        {
            switch ((CAN_STATE)can1_rx_fifo1_cb_info.context)
            {
                case APP_STATE_CAN_RECEIVE:
                {
                    memset(rxFiFo1, 0x00, (can1_rx_fifo1_cb_info.no_of_msgs * CAN1_RX_FIFO1_ELEMENT_SIZE));
                    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_1, can1_rx_fifo1_cb_info.no_of_msgs, (CAN_RX_BUFFER *)rxFiFo1) == true)
                    {
                        print_rx_message(can1_rx_fifo1_cb_info.no_of_msgs, (CAN_RX_BUFFER *)rxFiFo1, CAN1_RX_FIFO1_ELEMENT_SIZE, 0);
                        can_state = APP_STATE_CAN_XFER_SUCCESSFUL;
                    }
                    else
                    {
                        can_state = APP_STATE_CAN_XFER_ERROR;
                    }
                    break;
                }
                default: break;
            }
        }
        else
        {
            can_state = APP_STATE_CAN_XFER_ERROR;
        }
    }
    return;
}

/******************************************************************************
  Function:
    void CAN_Tasks ( void )

  Remarks:
    See prototype in can.h.
 */

void CAN_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( canData.state )
    {
        /* Application's initial state. */
        case CAN_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                canData.state = CAN_STATE_SERVICE_TASKS;
            }
            break;
        }

        case CAN_STATE_SERVICE_TASKS:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nCAN State Service Task - Waiting for CAN Queue...\n");
            xQueueReceive(xcan_rd_wr_queue, &can_task_queue, portMAX_DELAY);
            switch((uint8_t)can_task_queue.operation_flag)
            {
                case CAN_READ_FLAG:
                {
                    CAN1_Read();
                    // Check in what buffer is the data received.
                    rx_can_buffer = (CAN_RX_BUFFER *)rxFiFo0;
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nCANTask: To be sent to CmdParser | Msg ID = 0x%x 0x%x 0x%x 0x%x | DLC = 0x%x | Data =",
                                    GET_AD(can_cmd_parse_info.msg_id), GET_CMD(can_cmd_parse_info.msg_id), GET_TYP(can_cmd_parse_info.msg_id), 
                                    GET_MOT(can_cmd_parse_info.msg_id), can_cmd_parse_info.dlc);
                    for(int32_t i = 0; i < 8; i ++)
                    {
                        //can_cmd_parse_info.data[i] = rx_can_buffer->data[i];
                        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, " 0x%x", can_cmd_parse_info.data[i]);
                    }
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\n");
                    xQueueSend(xcmd_parser_queue, &can_cmd_parse_info, portMAX_DELAY);
                    break;
                }
                case CAN_WRITE_FLAG:
                {
                    CAN1_Write((unsigned int)can_task_queue.msg_id,
                               (uint8_t *)&can_task_queue.data,
                               (unsigned int)can_task_queue.dlc);
                    break;
                }
            }
            break;
            canData.state = CAN_STATE_SERVICE_TASKS;
        }
        case CAN_PARSE_STATE:
        {
            
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
