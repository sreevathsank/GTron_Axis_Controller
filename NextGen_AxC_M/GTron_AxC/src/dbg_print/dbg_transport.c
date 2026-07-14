/*******************************************************************************
 * Debug Transport - Project-Specific Glue Layer
 *
 * Hardware: ATSAMC21N18A
 *   - SERCOM7 USART (2 Mbaud, TX on PC12/PAD0)
 *   - DMA Channel 0 (trigger source: SERCOM7 TX, beat transfer, byte-sized)
 *
 * This file is project-specific. When porting to a different project,
 * replace the function bodies with calls to your hardware's DMA/UART PLIBs.
 ******************************************************************************/

#include "dbg_transport.h"
#include "definitions.h"

/* -------------------------------------------------------------------------- */
/* Transport callbacks                                                        */
/* -------------------------------------------------------------------------- */

/**
 * Initiate a non-blocking DMA transfer of 'len' bytes to SERCOM7 DATA.
 */
static bool transport_send(const uint8_t *data, size_t len)
{
    return DMAC_ChannelTransfer(
        DMAC_CHANNEL_0,
        data,
        (const void *)&SERCOM7_REGS->USART_INT.SERCOM_DATA,
        len
    );
}

/**
 * Check if DMA Channel 0 is still transferring.
 */
static bool transport_is_busy(void)
{
    return DMAC_ChannelIsBusy(DMAC_CHANNEL_0);
}

/**
 * DMA completion/error callback. Registered with the DMAC PLIB.
 * Called from ISR context.
 */
static void dma_callback(DMAC_TRANSFER_EVENT event, uintptr_t context)
{
    (void)context;

    if ((event == DMAC_TRANSFER_EVENT_COMPLETE) ||
        (event == DMAC_TRANSFER_EVENT_ERROR))
    {
        DBG_TransferComplete();
    }
}

/* -------------------------------------------------------------------------- */
/* Transport descriptor (static const - lives for the entire application)     */
/* -------------------------------------------------------------------------- */

static const dbg_transport_t s_transport = {
    .send    = transport_send,
    .is_busy = transport_is_busy,
};

/* -------------------------------------------------------------------------- */
/* Public functions                                                           */
/* -------------------------------------------------------------------------- */

void DBG_TransportInit(void)
{
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, dma_callback, 0);
}

const dbg_transport_t *DBG_TransportGet(void)
{
    return &s_transport;
}
