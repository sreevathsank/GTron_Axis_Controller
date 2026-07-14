/* 
 * File:   can_protocol.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 2:53 PM
 */

#ifndef CAN_PROTOCOL_H
#define	CAN_PROTOCOL_H

#include "third_party/rtos/FreeRTOS/Source/include/FreeRTOS.h"
#include "third_party/rtos/FreeRTOS/Source/include/queue.h"
#include "definitions.h"


#ifdef	__cplusplus
extern "C" {
#endif

// Standard identifier id[28:18].
#define WRITE_ID(id) (id << 18)
#define READ_ID(id)  (id >> 18)
    
typedef union {
   unsigned char data[8];
   int64_t data_64bit;
}Can_Data_t;

typedef enum { CAN_FROM_BUS, CAN_TO_BUS } Can_Direction_t;

typedef struct {
    uint32_t        can_id;     // 29-bit CAN ID.
    Can_Direction_t direction;  // FROM_BUS -> received from CAN ISR | TO_BUS -> To be sent.
    uint8_t         dlc;        // Data Length Code (0 - 8 bytes).
    Can_Data_t      payload;    // CAN Data as an array and 64-bit integer.
}Can_Frame_t;

#define Q_CAN_WORK_LEN  16
extern QueueHandle_t gq_can_work;      // Statically allocated queue.

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_PROTOCOL_H */

