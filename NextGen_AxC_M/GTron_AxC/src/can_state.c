#include "can_state.h"

// Busy Flags
bool g_4671_busy;
bool g_2209_busy;

// CAN Command dispatch struct.
Can_Cmd_Parser_t can_cmd_parse_info;

// CAN FIFO callback tracking.
CAN_Rx_Fifo_CB_Info can1_rx_fifo0_cb_info;
CAN_Rx_Fifo_CB_Info can1_rx_fifo1_cb_info;

// CAN message RAM (aligned).
uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(32)));

uint32_t xferContext = 0;
uint32_t status = 0;