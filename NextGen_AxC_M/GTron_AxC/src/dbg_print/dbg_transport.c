/*******************************************************************************
 * Debug Transport - Project-Specific Glue Layer
 *
 * Hardware: ATSAMC21N18A
 *   - SERCOM7 USART (2 Mbaud, TX on PC12/PAD0)
 *   - DMA Channel 0 (trigger source: SERCOM7 TX, beat transfer, byte-sized)
 *
 * WARNING: SERCOM7 is exclusively owned by the debug DMA transport.
 * Do NOT call SERCOM7_USART_Write() on this peripheral while the debug
 * transport is active. The interrupt-driven ring-buffer and DMA will
 * race for the DATA register and produce corrupted output.
 *
 * This file is project-specific. When porting to a different project,
 * replace the function bodies with calls to your hardware's DMA/UART PLIBs.
 ******************************************************************************/

#include "dbg_transport.h"
#include "definitions.h"

/* -------------------------------------------------------------------------- */
/* Static state                                                               */
/* -------------------------------------------------------------------------- */

static volatile uint32_t g_dma_error_count;

/* -------------------------------------------------------------------------- */
/* Transport callbacks                                                        */
/* -------------------------------------------------------------------------- */

/**
 * Initiate a non-blocking DMA transfer of 'len' bytes to SERCOM7 DATA.
 *
 * Returns true if the transfer was successfully started.
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
 * Check whether DMA Channel 0 is currently transferring.
 */
static bool transport_is_busy(void)
{
    return DMAC_ChannelIsBusy(DMAC_CHANNEL_0);
}

/**
 * DMA completion / error callback.  Registered with the DMAC PLIB.
 * Called from ISR context.
 */
static void dma_callback(DMAC_TRANSFER_EVENT event, uintptr_t context)
{
    (void)context;

    if (event == DMAC_TRANSFER_EVENT_COMPLETE) {
        /*
         * Transfer completed successfully.
         * Signal the dbg_print drain pump to continue.
         */
        DBG_TransferComplete();
    } else if (event == DMAC_TRANSFER_EVENT_ERROR) {
        /*
         * DMA transfer error.  Count it.  Still signal completion
         * so the drain pump does not stall — the message will be
         * dropped or retried by the higher layer.
         */
        g_dma_error_count++;
        DBG_TransferComplete();
    }
}

/* -------------------------------------------------------------------------- */
/* Transport descriptor                                                       */
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
    g_dma_error_count = 0U;
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, dma_callback, 0);
}

const dbg_transport_t *DBG_TransportGet(void)
{
    return &s_transport;
}

bool DBG_TransportIsActive(void)
{
    return transport_is_busy();
}
