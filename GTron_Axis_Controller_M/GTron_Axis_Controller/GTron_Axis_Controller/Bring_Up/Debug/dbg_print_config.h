/**
 * @file dbg_print_config.h
 * @brief Debug Print Library - Project Configuration (GTron AxC firmware)
 *
 * Per dbg_print_Integration_Plan.md decisions:
 *   - DBG_BUF_SIZE   = 128  (DMA chunk size)
 *   - DBG_STAGE_SIZE = 512  (max single message length, prefix+text)
 *   - Default level  = ERR_LVL_DEBUG (verbose) for bring-up; promoted later.
 *   - RTOS           = NONE (bare-metal main loop)
 */

#ifndef DBG_PRINT_CONFIG_H
#define DBG_PRINT_CONFIG_H

/* ---- Buffer Sizes -------------------------------------------------------- */

#define DBG_BUF_SIZE        128
#define DBG_STAGE_SIZE      512

/* ---- Default Error Level ------------------------------------------------- */

#define DBG_DEFAULT_LEVEL   ERR_LVL_DEBUG

/* ---- RTOS Selection ------------------------------------------------------ */

/* #define DBG_RTOS_FREERTOS   1 */
#define DBG_RTOS_NONE       1

#endif /* DBG_PRINT_CONFIG_H */
