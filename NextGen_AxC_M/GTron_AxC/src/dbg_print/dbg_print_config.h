/**
 * @file dbg_print_config.h
 * @brief Debug Print Library - Project Configuration
 */

#ifndef DBG_PRINT_CONFIG_H
#define DBG_PRINT_CONFIG_H

#include "dbg_print.h"

/* ---- Buffer Sizes -------------------------------------------------------- */

/**
 * @def DBG_BUF_SIZE
 * @brief Size of the DMA transfer buffer in bytes.
 *
 * Messages are sent in chunks of this size. A single buffer is allocated;
 * chunks are copied into it sequentially by the ISR drain pump.
 */
#define DBG_BUF_SIZE        128

/**
 * @def DBG_STAGE_SIZE
 * @brief Maximum length of a single formatted debug message (prefix + user text).
 *
 * Messages exceeding this length are truncated. Each pool slot is this size.
 */
#define DBG_STAGE_SIZE      256

/**
 * @def DBG_MSG_POOL_SIZE
 * @brief Number of pre-allocated message slots.
 *
 * DBG_Printf() allocates a slot from this pool, copies the formatted message,
 * and returns immediately. The DMA ISR drains the pool. When the pool is
 * full, new messages are silently dropped and counted.
 */
#define DBG_MSG_POOL_SIZE   4

/* ---- Default Error Level ------------------------------------------------- */

#define DBG_DEFAULT_LEVEL   ERR_LVL_DEBUG

/* ---- RTOS Selection ------------------------------------------------------ */

/**
 * Define exactly one of DBG_RTOS_FREERTOS or DBG_RTOS_NONE.
 */
#define DBG_RTOS_FREERTOS   1
/* #define DBG_RTOS_NONE    1 */

#endif /* DBG_PRINT_CONFIG_H */
