/*
 * IMM_CAN_Write.h
 *
 * Created: 18-01-2024 08:56:42
 *  Author: sreevathsank
 */ 


#ifndef IMM_CAN_WRITE_H_
#define IMM_CAN_WRITE_H_

//#include "Zen_can_api/zen_can_api.h"
//#include "Zen_can_api/zen_common.h"
#include "Global_Vars.h"
#include "All_Headers.h"

/** 
 * \brief Abstraction over can_Write.
 *
 *@param	message_Id 29 bit CAN Message ID
 *@param	peripheral byte
 *@param	operation byte
 *@param	value 4 bytes
 *
 *@return   false/0 -> Success | true/1 ->  Failure.
 */
bool can_AxC_Write(uint32_t msg_id, uint8_t peripheral, uint8_t operation, int32_t value);

void can_Tx_Cb(void);
 
bool can_Write(uint32_t message_Id, int32_t data);

#endif /* IMM_CAN_WRITE_H_ */