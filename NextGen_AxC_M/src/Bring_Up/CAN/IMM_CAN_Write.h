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

void can_Tx_Cb(void);
void can_Write(uint32_t message_Id, int32_t data);

#endif /* IMM_CAN_WRITE_H_ */