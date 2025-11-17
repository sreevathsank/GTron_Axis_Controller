/*
 * IMM_CAN.c
 *
 * Created: 08-01-2024 11:17:03
 *  Author: sreevathsank
 */ 


#include "Bring_Up/CAN/IMM_CAN.h"

void can_rx(void)
{
	//gpio_toggle_pin_level(DBGLED1);
	can_rx_int++;
	return;
}

void can_tx(void)
{
	return;
}

void can_Message_Read(void)
{
	unsigned int message_id;
	if(can_rx_int)
	{
		can_rx_int--;
		can_rx_frame.data_64bit = 0;
		
		can_receive(&CAN_1, &message_id, &can_rx_frame);
		can_message_decode(message_id);
	}
	return;
}

void can_init(void)
{
	can_begin(&CAN_1, CAN1, 500, SILENT);
	can_set_txcb(&CAN_1, (FUNC_PTR)can_tx);
	can_set_rxcb(&CAN_1, (FUNC_PTR)can_rx);
	can_set_filter(&CAN_1, 0, 0, EXT_ID);
	
	return;
}

void can_message_send(void)
{
	int32_t tx_message = rand() & 127;
	
	can_send(&CAN_1, tx_message, STD_ID, 0, can_tx_frame);
	printf("\nThe value sent = %x\n", tx_message);
}

void can_message_decode(unsigned int message_Id)
{
	
}

/*
Function Name: can_begin
Task:          Initialize the descriptor and hardware 
*/
void can_begin(struct can_async_descriptor * descr, void *const hw , unsigned int baud_rate , unsigned char can_silent_pin)
{
	struct _can_async_device *const dev = &descr->dev;
	//  printf("before 0x%x \n",hri_can_read_NBTP_reg(dev->hw));
	uint32_t can_nbtp_nbrp_value;
	uint32_t can_nbtp_nsgw_value = 3, can_nbtp_ntseg1_value = 10, can_nbtp_ntseg2_value = 3;
	baud_rate = baud_rate*1000;
	//can_nbtp_nbrp_value = CONF_GCLK_CAN1_FREQUENCY / baud_rate / (3 + can_nbtp_ntseg1_value + can_nbtp_ntseg2_value);
	can_nbtp_nbrp_value = CONF_GCLK_CAN1_FREQUENCY / (baud_rate *(3 + can_nbtp_ntseg1_value + can_nbtp_ntseg2_value)) - 1;    
    
                   
	int can_btp_reg_val = CAN_NBTP_NBRP(can_nbtp_nbrp_value) | CAN_NBTP_NTSEG1(can_nbtp_ntseg1_value) | CAN_NBTP_NTSEG2(can_nbtp_ntseg2_value) | CAN_NBTP_NSJW(can_nbtp_nsgw_value);
	/*
	int can_dbtp_reg_val = 	(CONF_CAN0_DBTP_TDC << CAN_DBTP_TDC_Pos) | CAN_DBTP_DBRP(1- 1)| CAN_DBTP_DTSEG1(17 - 1) | CAN_DBTP_DTSEG2(6 - 1) | CAN_DBTP_DSJW(3- 1);
    */


	dev->hw = hw;
	hri_can_set_CCCR_INIT_bit(dev->hw);
	while (hri_can_get_CCCR_INIT_bit(dev->hw) == 0);
	hri_can_set_CCCR_CCE_bit(dev->hw);

	#ifdef CONF_CAN0_ENABLED
	if (hw == CAN0) {
		hri_can_write_NBTP_reg(dev->hw, can_btp_reg_val);
		//hri_can_write_DBTP_reg(dev->hw, can_dbtp_reg_val);
		NVIC_DisableIRQ(CAN0_IRQn);
		NVIC_ClearPendingIRQ(CAN0_IRQn);
		NVIC_EnableIRQ(CAN0_IRQn);
		hri_can_write_ILE_reg(dev->hw, CAN_ILE_EINT0);
	}
	#endif

	#ifdef CONF_CAN1_ENABLED
	if (hw == CAN1) {
		hri_can_write_NBTP_reg(dev->hw, can_btp_reg_val);
		//hri_can_write_DBTP_reg(dev->hw, can_dbtp_reg_val);
       // printf("0x%x \n",hri_can_read_NBTP_reg(dev->hw));
		NVIC_DisableIRQ(CAN1_IRQn);
		NVIC_ClearPendingIRQ(CAN1_IRQn);
		NVIC_EnableIRQ(CAN1_IRQn);
		hri_can_write_ILE_reg(dev->hw, CAN_ILE_EINT0);
	}
	#endif

	/* Disable CCE to prevent Configuration Change */
	hri_can_clear_CCCR_CCE_bit(dev->hw);
	hri_can_clear_CCCR_INIT_bit(dev->hw);
	while (hri_can_get_CCCR_INIT_bit(dev->hw)) 
	{
	};
	
	can_async_enable(descr);
	
	gpio_set_pin_direction(can_silent_pin , GPIO_DIRECTION_OUT);
	gpio_set_pin_level(can_silent_pin, 0); // Set CAN silent pin LOW
	/* CAN Bus off debug led indication */
	gpio_set_pin_direction(DEBUG_LED , GPIO_DIRECTION_OUT);
	gpio_set_pin_level(DEBUG_LED, 0); // Set CAN silent pin LOW
	// printf("0x%x \n",hri_can_read_NBTP_reg(dev->hw));
}

/*
Function Name: can_set_txcb
Task:          Initialize the descriptor and hardware
*/
void can_set_txcb(struct can_async_descriptor * descr , FUNC_PTR cb)
{
	 can_async_register_callback( descr , CAN_ASYNC_TX_CB, cb);
}

/*
Function Name: can_set_rxcb
Task:          Initialize the descriptor and hardware
*/
void can_set_rxcb(struct can_async_descriptor * descr , FUNC_PTR cb)
{
	can_async_register_callback(descr, CAN_ASYNC_RX_CB, cb);
}

/*
Function Name: can_send
Task:          Send the can frame data
*/
void can_send(struct can_async_descriptor * descr , unsigned int ID, unsigned char ext_flag, unsigned char dlc, can_union_type can_frame)
{
	struct can_message tx_msg;
	//int32_t can_status = 10 ;	
	tx_msg.id   = ID;
	tx_msg.type = CAN_TYPE_DATA;
	tx_msg.data = can_frame.data;
	tx_msg.len  = dlc;
	if(ext_flag)
		tx_msg.fmt  = CAN_FMT_EXTID;
	else	
		tx_msg.fmt  = CAN_FMT_STDID;
	
	can_status = can_async_write(descr , &tx_msg); // ASF 4 Can write API.	

}

/*
Function Name: can_receive
Task:          Receive the can frame data
*/
unsigned char  can_receive(struct can_async_descriptor * descr , unsigned int* ID, can_union_type * can_frame)
{
	struct can_message rx_msg;
	//uint8_t    data[8];
	rx_msg.data = can_frame->data;
	
	can_async_read(descr, &rx_msg);
	
	//can_frame->data = rx_msg.data;
	*ID = rx_msg.id;
	
	if(rx_msg.type == CAN_TYPE_DATA)
		return DATA_FRAME;
	else if(rx_msg.type == CAN_TYPE_REMOTE)
		return REMOTE_FRAME;
	else 
		return 0; // False Information
	
}

/*
Function Name: can_receive
Task:          Receive the can frame data
*/
void can_set_filter(struct can_async_descriptor * descr , unsigned int ID, unsigned int mask, unsigned char ext)
{
	struct can_filter  filter; // Filter ID and MASK
	filter.id   = ID;
	filter.mask = mask;
	
	if(ext) // Extended frame format
		can_async_set_filter(descr, 0, CAN_FMT_EXTID , &filter); // Index 0
	else 
		can_async_set_filter(descr, 0, CAN_FMT_STDID , &filter); // Index 0
	
	
	return;
}

/* ISR for can bus off */
void isr_can_bus_off_error_cb(struct _can_async_device *dev, enum can_async_interrupt_type type)
{
	// ON the debug led for bus off condition
	if(hri_can_get_PSR_BO_bit(dev->hw)){
		gpio_set_pin_level(DEBUG_LED , true);
	}	
}

void can_busoff_set_cb(struct can_async_descriptor *const descr)
{
	uint32_t ie;
	descr->cb.irq_handler = (void (*)(struct can_async_descriptor *const, enum can_async_interrupt_type)) isr_can_bus_off_error_cb;
	//= (cb != NULL) ? (void (*)(struct can_async_descriptor *const, enum can_async_interrupt_type))cb : NULL;
	
	ie = hri_can_get_IE_reg((&descr->dev)->hw, CAN_IE_RF0NE | CAN_IE_TCE);
	hri_can_write_IE_reg((&descr->dev)->hw, ie | ( 1 << CAN_IR_BO_Pos));
}