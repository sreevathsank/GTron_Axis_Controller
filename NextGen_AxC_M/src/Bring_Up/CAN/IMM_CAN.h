///*
// * IMM_CAN.h
// *
// * Created: 08-01-2024 11:16:52
// *  Author: sreevathsank
// */ 
//
//
//#ifndef IMM_CAN_H_
//#define IMM_CAN_H_
//
////#include <atmel_start.h>
//#include <hal_can_async.h> // Hal can include for ASF 4 api support
//#include <hpl_can_async.h>
//#include <hpl_can_base.h>
//#include <hpl_can_config.h>
//#if (NODE == 4)
//#include <hri_can_c21.h> // for weighing
//#else
//#include <hri_can_c21n.h> // for others
//#endif
//
//#include <hpl_can.h>
//
////#include <driver_init.h>
//#include <peripheral_clk_config.h>
//#include <string.h>
//#include <inttypes.h>
////#include <zen_message_id.h>
//
///* Related IO Inclusion */
//#define DEBUG_LED		36	// PB04
//
//#include "Global_Vars.h"
//#include "All_Headers.h"
//#include "Bring_Up/CAN/IMM_CAN_Message_Id.h"
//#include "Bring_Up/CAN/IMM_CAN_Read.h"
//
//#define SILENT		73
//#define STD_ID		0
//#define SENDER		1
//#define RECEIVER	0
//
//#define BOARD RECEIVER
//
//void can_Message_Read(void);
//
//void can_rx(void);
//
//void can_tx(void);
//
//void can_init(void);
//
//void can_message_send(void);
//
//void can_message_decode(unsigned int message_Id);
///*
//Function API
//*/
////void can_init(struct can_async_descriptor * descr , void *const hw , unsigned int baud_rate , unsigned char rx_int_flag , unsigned char tx_int_flag);
//void can_begin(struct can_async_descriptor * descr, void *const hw , unsigned int baud_rate , unsigned char can_silent_pin);
//void can_set_txcb(struct can_async_descriptor * descr , FUNC_PTR cb);
//void can_set_rxcb(struct can_async_descriptor * descr , FUNC_PTR cb);
//void can_send(struct can_async_descriptor * descr , unsigned int ID, unsigned char ext_flag, unsigned char dlc, can_union_type can_frame);
//unsigned char can_receive(struct can_async_descriptor * descr , unsigned int* ID, can_union_type * can_frame);
//void can_set_filter(struct can_async_descriptor * descr , unsigned int ID, unsigned int mask, unsigned char ext);
//void can_busoff_set_cb(struct can_async_descriptor *const descr);
//
///* CAN messages call backs*/
////void can_rx_cb_fxn(); //RX Callback function
////void can_tx_cb_fxn(); //TX Callback function
//#endif /* IMM_CAN_H_ */