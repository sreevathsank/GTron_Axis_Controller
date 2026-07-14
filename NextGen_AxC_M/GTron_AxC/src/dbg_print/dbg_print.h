/**
 * @file dbg_print.h
 * @brief Debug Print Library - Public API
 *
 * A portable, hardware-independent debug print utility with:
 *   - 4 runtime-configurable error levels (ERROR, WARNING, INFO, DEBUG)
 *   - printf-style variadic formatting
 *   - Non-blocking DMA transfer via a user-provided transport layer
 *   - Double-buffered output with automatic chunking for long messages
 *   - Optional RTOS support (FreeRTOS or bare-metal)
 *
 * To use this library:
 *   1. Copy the dbg_print/ folder into your project.
 *   2. Edit dbg_print_config.h for your buffer sizes and RTOS selection.
 *   3. Implement a transport layer (see dbg_transport_t) that maps to your
 *      hardware (DMA + UART, SPI, etc.).
 *   4. Call DBG_Init() once at startup, then use DBG_Printf() everywhere.
 *
 * This file contains NO hardware-specific references.
 */

#ifndef DBG_PRINT_H
#define DBG_PRINT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup dbg_print Debug Print Library
 *  @{
 */

/* ---- Error Levels -------------------------------------------------------- */

/**
 * @brief Error level enumeration for message filtering.
 *
 * Lower numeric values represent higher severity. Messages are printed only
 * when their level is numerically less than or equal to the current threshold
 * set via DBG_SetLevel().
 */
typedef enum {
    ERR_LVL_ERROR   = 0,   /**< Highest priority - always printed. */
    ERR_LVL_WARNING = 1,   /**< Warnings. */
    ERR_LVL_INFO    = 2,   /**< Informational messages. */
    ERR_LVL_DEBUG   = 3,   /**< Lowest priority - most verbose. */
} err_lvl_t;

/* ---- Transport Interface ------------------------------------------------- */

/**
 * @brief Function pointer type for initiating a non-blocking data transfer.
 *
 * The buffer pointed to by @p data is guaranteed to remain valid until
 * DBG_TransferComplete() is called. The implementation must not modify
 * or free this buffer.
 *
 * @param[in] data  Pointer to the data to transmit.
 * @param[in] len   Number of bytes to transmit.
 * @return          true if the transfer was started successfully, false otherwise.
 */
typedef bool (*dbg_transport_send_fn)(const uint8_t *data, size_t len);

/**
 * @brief Function pointer type for checking if the transport is busy.
 *
 * @return true if a previous transfer is still in progress, false if idle.
 */
typedef bool (*dbg_transport_busy_fn)(void);

/**
 * @brief Transport descriptor.
 *
 * The user populates this structure with function pointers that map to their
 * specific hardware (DMA, interrupt-driven UART, SPI, etc.).
 */
typedef struct {
    dbg_transport_send_fn   send;       /**< Required: start a transfer. */
    dbg_transport_busy_fn   is_busy;    /**< Required: check if busy. */
} dbg_transport_t;

/* ---- Public API ---------------------------------------------------------- */

/**
 * @brief Initialize the debug print system.
 *
 * Must be called once before any other DBG_* function. Creates RTOS
 * synchronization primitives (if enabled) and stores the transport.
 *
 * @param[in] transport  Pointer to a transport descriptor. The pointed-to
 *                       struct must remain valid for the lifetime of the
 *                       application (typically a static const).
 */
void DBG_Init(const dbg_transport_t *transport);

/**
 * @brief Signal that the previous transport transfer has completed.
 *
 * This function @b MUST be called from the transport's completion callback
 * (typically a DMA ISR). It unblocks the next pending DBG_Printf() call.
 *
 * @note Safe to call from ISR context.
 */
void DBG_TransferComplete(void);

/**
 * @brief Set the runtime error level filter threshold.
 *
 * Messages with a level numerically greater than @p level are discarded.
 * For example, setting @c ERR_LVL_WARNING means only ERROR and WARNING
 * messages are printed; INFO and DEBUG are suppressed.
 *
 * @param[in] level  The new threshold level.
 */
void DBG_SetLevel(err_lvl_t level);

/**
 * @brief Get the current error level filter threshold.
 *
 * @return The current threshold level.
 */
err_lvl_t DBG_GetLevel(void);

/**
 * @brief Print a formatted debug message if the level passes the current filter.
 *
 * Behaves like @c printf(). The message is automatically prefixed with a
 * level tag (e.g., "[ERR] ", "[WRN] ", "[INF] ", "[DBG] ").
 *
 * If the formatted message (prefix + user text) exceeds the DMA buffer
 * size (@ref DBG_BUF_SIZE), it is sent in multiple DMA transfers automatically.
 * If it exceeds the staging buffer size (@ref DBG_STAGE_SIZE), it is truncated.
 *
 * This function blocks until the transport is available and the message
 * has been fully queued for transmission. Do @b NOT call from ISR context.
 *
 * @param[in] msg_level  The severity level of this message.
 * @param[in] fmt        printf-style format string.
 * @param[in] ...        Format arguments.
 */
void DBG_Printf(err_lvl_t msg_level, const char *fmt, ...);

/** @} */ /* end of dbg_print group */

#ifdef __cplusplus
}
#endif

#endif /* DBG_PRINT_H */
