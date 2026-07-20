#include "init_functions.h"

//--------------- CAN1 Peripheral Definitions ---------------//

/// @brief  Initializes CAN1 Peripheral and its Callbacks.
/// @param  void
void init_CAN1( void )
{
    CAN1_MessageRAMConfigSet( Can1MessageRAM );
    CAN1_TxFifoCallbackRegister( CAN1_TxFifoCallback, (uintptr_t)NULL );
    CAN1_RxFifoCallbackRegister( CAN_RX_FIFO_0, CAN1_RxFifo0Callback, (uintptr_t)APP_STATE_CAN_RECEIVE );
    CAN1_RxFifoCallbackRegister( CAN_RX_FIFO_1, CAN1_RxFifo1Callback, (uintptr_t)APP_STATE_CAN_RECEIVE );
    return;
}

/// @brief  Initializes the DMA based DBG Print lib.
/// @param  void
void init_dbg_print( void )
{
    DBG_TransportInit();
    DBG_Init( DBG_TransportGet() );
    return;
}