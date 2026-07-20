/*******************************************************************************
 * Debug Transport - Project-Specific Glue Layer
 *
 * This file wires the generic dbg_print library to the project's hardware.
 * For this project: DMA Channel 0 + SERCOM7 USART on ATSAMC21N18A.
 *
 * SERCOM7 is exclusively owned by the debug transport (DMA-driven TX).
 * Do NOT call SERCOM7_USART_Write() on this peripheral — it will race with
 * the DMA transfers and produce corrupted output.
 *
 * When porting to a different project, replace the implementation in
 * dbg_transport.c with your hardware-specific DMA/UART/SPI calls.
 ******************************************************************************/

#ifndef DBG_TRANSPORT_H
#define DBG_TRANSPORT_H

#include "dbg_print.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the hardware transport layer.
 *
 * Registers the DMA completion callback. Must be called before DBG_Init().
 */
void DBG_TransportInit(void);

/**
 * Get a pointer to the transport descriptor for this project.
 *
 * The returned pointer is valid for the lifetime of the application
 * (points to a static const struct).
 */
const dbg_transport_t *DBG_TransportGet(void);

/**
 * Check whether the transport hardware is currently busy.
 *
 * Returns true if a DMA transfer is in progress.
 */
bool DBG_TransportIsActive(void);

#ifdef __cplusplus
}
#endif

#endif /* DBG_TRANSPORT_H */
