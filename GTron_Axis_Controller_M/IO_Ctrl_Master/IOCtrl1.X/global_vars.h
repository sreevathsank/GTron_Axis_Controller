/* 
 * File:   global_vars.h
 * Author: sreevathsank
 *
 * Created on 30 June, 2025, 2:55 PM
 */

#ifndef GLOBAL_VARS_H
#define	GLOBAL_VARS_H

#include "all_headers.h"
#include "event_groups.h"
#include "custom_macros.h"

// Event Group for Button State Handling
extern EventGroupHandle_t xbtn_state_event_grp;

// FreeRTOS Queues.
extern QueueHandle_t xdebug_log_queue;
extern QueueHandle_t xcan_rd_wr_queue;
extern QueueHandle_t xcmd_parser_queue;

// Task IDs.
typedef enum
{
    SYSTEM_STATE_TASK_ID = 0,
    CAN_RD_WR_TASK_ID = 1,
    CAN_PARSER_TASK_ID = 2,
    DEBUG_LOGGER_TASK_ID = 3,
    NO_OF_TASK_ID                   // Stores the value of no of items in the Enum
}TaskID_t;

typedef struct
{
    uint8_t *log_data_ptr;          // Points to the message to be printed.
    TaskID_t task_id;               // ID of the task that has sent the message.
    SYS_ERROR_LEVEL error_level;    // Indicates the Error Level of the message.
}DBGLog_t;

typedef struct
{
    uint8_t operation_flag;         // Flag denoting whether to perform read or write operation.
    uint8_t dlc;                    // No. of bytes to be written. Data Length Code.
    uint8_t buffer_X;                // What buffer to read.
    uint8_t data[8];                // Data to be written on the CAN Bus. Dummy bytes are set if flag is set to read.
    uint32_t msg_id;                // Message ID. Dummy Message ID if flag is set to read.
}Can_Queue_t;

typedef struct
{
    uint8_t dlc;
    uint8_t data[8];
    uint32_t msg_id;
}CAN_Cmd_Parser_t;

extern Can_Queue_t can_queue_struct;

extern uint8_t debug_message[DBG_MSG_LEN];

typedef struct
{
    uint8_t buf_cnt;
    uint8_t no_of_msgs;
    uintptr_t context;
}CAN_Rx_Fifo_CB_Info;

extern CAN_Rx_Fifo_CB_Info can1_rx_fifo0_cb_info;

extern CAN_Rx_Fifo_CB_Info can1_rx_fifo1_cb_info;

extern uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned (32)));

#endif	/* GLOBAL_VARS_H */

