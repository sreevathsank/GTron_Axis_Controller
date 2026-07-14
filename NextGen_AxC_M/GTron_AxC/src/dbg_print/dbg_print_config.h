/**
 * @file dbg_print_config.h
 * @brief Debug Print Library - Project Configuration
 *
 * This file is project-specific. Edit it to match your project's requirements.
 * When porting the dbg_print library to a new project, copy the dbg_print/
 * folder and modify this file accordingly.
 */

#ifndef DBG_PRINT_CONFIG_H
#define DBG_PRINT_CONFIG_H

/* ---- Buffer Sizes -------------------------------------------------------- */

/**
 * @def DBG_BUF_SIZE
 * @brief Size of each DMA transfer buffer in bytes.
 *
 * Two buffers of this size are allocated (double-buffering). Messages longer
 * than this are sent in multiple DMA transfers automatically.
 */
#define DBG_BUF_SIZE        128

/**
 * @def DBG_STAGE_SIZE
 * @brief Maximum length of a single formatted debug message (prefix + user text).
 *
 * Messages exceeding this length are truncated. This buffer is used as a
 * staging area before chunked DMA transfer.
 */
#define DBG_STAGE_SIZE      256

/* ---- Default Error Level ------------------------------------------------- */

/**
 * @def DBG_DEFAULT_LEVEL
 * @brief The error level threshold set at startup.
 *
 * Only messages with a level numerically <= this value are printed.
 *   - @c ERR_LVL_ERROR   (0) - only errors
 *   - @c ERR_LVL_WARNING (1) - errors + warnings
 *   - @c ERR_LVL_INFO    (2) - errors + warnings + info
 *   - @c ERR_LVL_DEBUG   (3) - everything
 */
#define DBG_DEFAULT_LEVEL   ERR_LVL_DEBUG

/* ---- RTOS Selection ------------------------------------------------------ */

/**
 * @def DBG_RTOS_FREERTOS
 * @brief Use FreeRTOS mutex and binary semaphore for thread safety and
 *        DMA completion signaling.
 *
 * Define exactly one of @c DBG_RTOS_FREERTOS or @c DBG_RTOS_NONE.
 *
 * @def DBG_RTOS_NONE
 * @brief Bare-metal mode. No mutex (assumes single-threaded).
 *        DMA completion is polled via a volatile flag.
 */
#define DBG_RTOS_FREERTOS   1
/* #define DBG_RTOS_NONE    1 */

#endif /* DBG_PRINT_CONFIG_H */
