/**
 * @file dbg_transport.h
 * @brief Debug Transport - Project-Specific Glue Layer
 *
 * Project: GTron AxC firmware (ATSAMC21N18A, Atmel Start ASF)
 * Hardware: SERCOM7 USART (TARGET_IO @ 2 Mbaud) + DMA Channel 0
 *           Trigger source: SERCOM7_DMAC_ID_TX (52)
 */

#ifndef DBG_TRANSPORT_H
#define DBG_TRANSPORT_H

#include "dbg_print.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the hardware transport layer.
 *
 * Configures DMA Channel 0 (CHCTRLB.TRIGSRC=52, TRIGACT=BEAT, beatsize=BYTE,
 * SRCINC=1, DSTINC=0), points its descriptor at SERCOM7 DATA, and registers
 * the DMA TCMPL callback so DBG_TransferComplete() runs from the DMAC ISR.
 *
 * MUST be called AFTER atmel_start_init() (which calls _dma_init()) and
 * BEFORE DBG_Init().
 */
void DBG_TransportInit(void);

/**
 * @brief Get a pointer to the transport descriptor for this project.
 *
 * The returned pointer is valid for the lifetime of the application.
 */
const dbg_transport_t *DBG_TransportGet(void);

#ifdef __cplusplus
}
#endif

#endif /* DBG_TRANSPORT_H */
