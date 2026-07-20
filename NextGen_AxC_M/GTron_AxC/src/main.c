#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>
#include "definitions.h"                // SYS function prototypes
#include "config/default/peripheral/can/plib_can1.h"
#include "FreeRTOS.h"
#include "queue.h"

#include "dbg_print/dbg_print.h"
#include "dbg_print/dbg_transport.h"
#include "init_functions.h"
#include "can_isr_callbacks.h"
#include "can_protocol.h"

static uint8_t          qbuf_can_work[16 * sizeof(Can_Frame_t)];
static StaticQueue_t    sq_can_work;
QueueHandle_t           gq_can_work;

int main ( void )
{
    SYS_Initialize ( NULL );
    
    gq_can_work = xQueueCreateStatic(16, sizeof(Can_Frame_t), qbuf_can_work, &sq_can_work);
    
    init_CAN1();
    init_dbg_print();
    
    DBG_Printf(ERR_LVL_DEBUG,
        "Init Done!\n");
    
    DBGLED1_Clear();
    DBGLED2_Clear();
    DBGLED3_Set();
    
    for(uint8_t i = 0; i <= 10; ++i) {
        DBG_Printf(ERR_LVL_DEBUG,
            "This is nise! = %u\n", i);
        for(uint8_t j = 0; j <= 100; ++j) {
            uint8_t k;
            k += 1;
        }
    }

    DBG_Printf(ERR_LVL_DEBUG,
        "This is nise!\n");
    
    for(;;) {
        SYS_Tasks ( );
    }
    return ( EXIT_FAILURE );
}