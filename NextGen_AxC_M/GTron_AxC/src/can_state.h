/* 
 * File:   can_state.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 12:48 PM
 */

#ifndef CAN_STATE_H
#define	CAN_STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "config/default/peripheral/can/plib_can1.h"

// Busy flags for move arbitration
extern bool     g_4671_busy;
extern bool     g_2209_busy;

extern uint32_t xferContext;
extern uint32_t status;

// CAN command dispatch struct
typedef struct {
    uint32_t    can_id;
    uint8_t     type;
    uint8_t     motor;
    int32_t     value;
    uint8_t     extra[4];
} Can_Cmd_t;

// CAN Decoded Frame Struct.
typedef struct {
    uint8_t     dlc;
    uint8_t     data[8];
    uint32_t    msg_id;
}Can_Cmd_Parser_t;
extern Can_Cmd_Parser_t can_cmd_parse_info;

// CAN FIFO callback tracking (from IO_Ctrl_Master global_vars.h)
typedef struct {
    uint8_t   buf_cnt;
    uint8_t   no_of_msgs;
    uintptr_t context;
} CAN_Rx_Fifo_CB_Info;
extern CAN_Rx_Fifo_CB_Info can1_rx_fifo0_cb_info;
extern CAN_Rx_Fifo_CB_Info can1_rx_fifo1_cb_info;

// CAN message RAM (aligned, from IO_Ctrl_Master pattern)
extern uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(32)));

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_STATE_H */

