/**
 * @file dbg_transport.c
 * @brief Debug Transport - Project-Specific Glue Layer (GTron AxC firmware)
 *
 * Hardware: ATSAMC21N18A, Atmel Start ASF
 *   - SERCOM7 USART (TARGET_IO @ 2 Mbaud, configured by atmel_start_init())
 *   - DMA Channel 0 (programmatically configured here because Atmel Start
 *     GUI's SAMC21 DMAC trigger source list omits SERCOM6/7. The hardware
 *     supports it; only the GUI metadata is incomplete. CHCTRLB.TRIGSRC
 *     is a 6-bit field [0..63], SERCOM7_DMAC_ID_TX = 52 fits.)
 *
 * Sequence (must match plan dbg_print_Integration_Plan.md \xA77.3):
 *   1. atmel_start_init() runs _dma_init() which:
 *        - Enables DMAC peripheral (CTRL.DMAENABLE=1)
 *        - Writes BASEADDR/WRBADDR
 *        - Loops over channels: CHID=i, CHCTRLB=0, descriptor BTCTRL=0,
 *          DESCADDR=0. Channel 0 is left disabled (CONF_DMAC_ENABLE_0=0).
 *        - NVIC_EnableIRQ(DMAC_IRQn).
 *   2. DBG_TransportInit() (this file):
 *        - Selects channel 0 via CHID.
 *        - Writes CHCTRLB: TRIGSRC=52, TRIGACT=BEAT, LVL=0.
 *        - Writes descriptor BTCTRL: BEATSIZE=BYTE, SRCINC=1, DSTINC=0,
 *          BLOCKACT=NOACT, STEPSIZE=1, STEPSEL=SRC. (VALID set per-transfer.)
 *        - Sets descriptor DSTADDR = &SERCOM7->USART.DATA.reg (no DSTINC).
 *        - Enables CHINTEN.TCMPL.
 *        - Installs s_dbg_resource->dma_cb.transfer_done = dma_done_cb so
 *          the existing DMAC_Handler in hpl_dmac.c dispatches to us.
 *   3. transport_send(buf, len) per call:
 *        - Sets descriptor SRCADDR = buf + len  (HW reads SRC last-byte then
 *          decrements; ASF's _dma_set_data_amount handles this correctly when
 *          SRCINC=1 by writing SRC = orig + len*beat_size. We use it.)
 *        - Sets BTCNT = len, sets BTCTRL.VALID, enables channel.
 */

#include "dbg_transport.h"

#include <atmel_start.h>
#include <hpl_dma.h>
#include <hri_dmac_c21n.h>
#include <utils_assert.h>

/* _descriptor_section[] is defined (not static) in hpl/dmac/hpl_dmac.c. */
extern DmacDescriptor _descriptor_section[];

/* ATSAMC21N18A: SERCOM7_DMAC_ID_TX (samc21n/include/instance/sercom7.h:126) */
#define DBG_DMAC_CHANNEL              0u
#define DBG_DMAC_TRIGSRC_SERCOM7_TX   52u

/* -------------------------------------------------------------------------- */
/*  Local state                                                                */
/* -------------------------------------------------------------------------- */

static struct _dma_resource *s_dbg_resource;

/* -------------------------------------------------------------------------- */
/*  Internal callbacks                                                         */
/* -------------------------------------------------------------------------- */

/**
 * @brief DMAC TCMPL callback for our channel.
 *
 * Dispatched from DMAC_Handler() in hpl/dmac/hpl_dmac.c via
 * _resources[channel].dma_cb.transfer_done(resource).
 *
 * @note Runs in DMAC ISR context.
 */
static void dma_done_cb(struct _dma_resource *resource)
{
    (void)resource;
    DBG_TransferComplete();
}

static void dma_error_cb(struct _dma_resource *resource)
{
    (void)resource;
    /* On a DMA error, free the producer or it will hang. */
    DBG_TransferComplete();
}

/* -------------------------------------------------------------------------- */
/*  Transport callbacks                                                        */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initiate a non-blocking DMA transfer of @p len bytes to SERCOM7 DATA.
 *
 * @param[in] data  Pointer to source buffer (lifetime owned by dbg_print).
 * @param[in] len   Number of bytes to transmit.
 * @return          true if started.
 */
static bool transport_send(const uint8_t *data, size_t len)
{
    if ((data == NULL) || (len == 0u)) {
        return false;
    }

    /* Source = caller's buffer; destination already set in DBG_TransportInit. */
    (void)_dma_set_source_address(DBG_DMAC_CHANNEL, (const void *)data);
    /* _dma_set_data_amount() also auto-computes the descriptor SRCADDR end
       pointer (orig + len*beat_size) when SRCINC=1; that matches the hardware
       requirement that SRCADDR descriptor field holds end-of-buffer. */
    (void)_dma_set_data_amount(DBG_DMAC_CHANNEL, (uint32_t)len);
    (void)_dma_enable_transaction(DBG_DMAC_CHANNEL, false /* HW trigger */);
    return true;
}

/**
 * @brief Reports whether DMA channel 0 currently has an active transfer.
 *
 * dbg_print uses an internal flag for synchronization; this is a passive
 * status accessor for diagnostics only.
 */
static bool transport_is_busy(void)
{
    /* Read CHCTRLA.ENABLE on our channel. CHID is shared, so save/restore. */
    uint8_t saved = hri_dmac_read_CHID_reg(DMAC);
    hri_dmac_write_CHID_reg(DMAC, DBG_DMAC_CHANNEL);
    bool busy = hri_dmac_get_CHCTRLA_ENABLE_bit(DMAC);
    hri_dmac_write_CHID_reg(DMAC, saved);
    return busy;
}

/* -------------------------------------------------------------------------- */
/*  Transport descriptor                                                       */
/* -------------------------------------------------------------------------- */

static const dbg_transport_t s_transport = {
    .send    = transport_send,
    .is_busy = transport_is_busy,
};

/* -------------------------------------------------------------------------- */
/*  Public functions                                                           */
/* -------------------------------------------------------------------------- */

void DBG_TransportInit(void)
{
    /* 1. Select channel 0. */
    hri_dmac_write_CHID_reg(DMAC, DBG_DMAC_CHANNEL);

    /* 2. Make sure the channel is disabled before we reconfigure it
          (it should already be, since CONF_DMAC_ENABLE_0=0, but be safe). */
    hri_dmac_clear_CHCTRLA_ENABLE_bit(DMAC);
    while (hri_dmac_get_CHCTRLA_ENABLE_bit(DMAC)) {
        /* spin until disable takes effect */
    }

    /* 3. Channel control B:
          - TRIGSRC = SERCOM7_DMAC_ID_TX (52)
          - TRIGACT = BEAT (one trigger per beat = one byte per request)
          - LVL     = 0   (lowest priority; debug logging is non-critical)
          - EVOSE/EVIE/EVACT all zero. */
    hri_dmac_write_CHCTRLB_reg(
        DMAC,
        DMAC_CHCTRLB_TRIGSRC(DBG_DMAC_TRIGSRC_SERCOM7_TX) |
        DMAC_CHCTRLB_TRIGACT_BEAT |
        DMAC_CHCTRLB_LVL(0));

    /* 4. Channel transfer descriptor (BTCTRL):
          - VALID    = 0  (set per-transfer in _dma_enable_transaction)
          - EVOSEL   = 0
          - BLOCKACT = NOACT
          - BEATSIZE = BYTE
          - SRCINC   = 1  (walk through caller's buffer)
          - DSTINC   = 0  (DATA register is fixed)
          - STEPSEL  = SRC
          - STEPSIZE = 1  (default; with BEATSIZE=BYTE means +1 byte per beat) */
    hri_dmacdescriptor_write_BTCTRL_reg(
        &_descriptor_section[DBG_DMAC_CHANNEL],
        DMAC_BTCTRL_BEATSIZE_BYTE |
        DMAC_BTCTRL_SRCINC        |
        DMAC_BTCTRL_STEPSIZE(DMAC_BTCTRL_STEPSIZE_X1_Val));

    /* 5. Destination = SERCOM7 USART DATA register (8-bit DATA in lower byte
          of a 16-bit reg @ 0x43000428). DSTINC=0 means DSTADDR is taken
          literally; no end-of-buffer adjustment needed. */
    (void)_dma_set_destination_address(
        DBG_DMAC_CHANNEL,
        (void *)&SERCOM7->USART.DATA.reg);

    /* 6. Enable transfer-complete interrupt (ASF helper handles CHID). */
    _dma_set_irq_state(DBG_DMAC_CHANNEL, DMA_TRANSFER_COMPLETE_CB, true);
    _dma_set_irq_state(DBG_DMAC_CHANNEL, DMA_TRANSFER_ERROR_CB,    true);

    /* 7. Hook up our callbacks via the resource table; DMAC_Handler in
          hpl_dmac.c will invoke these. */
    (void)_dma_get_channel_resource(&s_dbg_resource, DBG_DMAC_CHANNEL);
    s_dbg_resource->dma_cb.transfer_done = dma_done_cb;
    s_dbg_resource->dma_cb.error         = dma_error_cb;
}

const dbg_transport_t *DBG_TransportGet(void)
{
    return &s_transport;
}

/* -------------------------------------------------------------------------- */
/*  Notes                                                                      */
/* -------------------------------------------------------------------------- */
/*
 * _descriptor_section[] is declared at file top (extern). It is defined
 * (non-static) in hpl/dmac/hpl_dmac.c:45 and lives in SECTION_DMAC_DESCRIPTOR.
 *
 * _dma_set_data_amount() will compute SRCADDR_end = SRCADDR + len*(1<<beatsize)
 * each call when SRCINC=1. Because we call _dma_set_source_address() FIRST
 * (which writes the buffer base) and _dma_set_data_amount() SECOND, the
 * SRCADDR descriptor field ends up correctly set to (base + len), which is
 * what the SAMC21 DMAC expects (it reads SRC in DESCENDING order from the
 * end-of-buffer pointer down to base).
 */

