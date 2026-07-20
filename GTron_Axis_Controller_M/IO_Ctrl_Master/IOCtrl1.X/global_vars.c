#include "global_vars.h"

EventGroupHandle_t xbtn_state_event_grp = NULL;

QueueHandle_t xdebug_log_queue = NULL;

QueueHandle_t xcan_rd_wr_queue = NULL;

QueueHandle_t xcmd_parser_queue = NULL;

Can_Queue_t can_queue_struct;

uint8_t debug_message[DBG_MSG_LEN] = {0};

struct DBGLog_t;

CAN_Rx_Fifo_CB_Info can1_rx_fifo0_cb_info;

CAN_Rx_Fifo_CB_Info can1_rx_fifo1_cb_info;

uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE];