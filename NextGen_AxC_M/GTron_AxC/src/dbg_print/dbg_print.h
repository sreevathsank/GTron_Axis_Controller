/**
 * @file dbg_print.h
 * @brief Debug Print Library - Public API
 *
 * A hardware-independent debug print utility with:
 *   - 4 runtime-configurable error levels (ERROR, WARNING, INFO, DEBUG)
 *   - printf-style variadic formatting
 *   - Truly non-blocking: DBG_Printf() enqueues a formatted message and returns
 *     immediately. A pre-allocated message pool decouples the caller from the
 *     DMA transfer latency.
 *   - ISR-driven DMA drain pump: each DMA completion interrupt starts the next
 *     chunk or dequeues the next message automatically.
 *   - Drop counting when the message pool is full.
 *   - Optional RTOS support (FreeRTOS or bare-metal).
 *   - DMA error counting.
 *
 * To use this library:
 *   1. Copy the dbg_print/ folder into your project.
 *   2. Edit dbg_print_config.h for buffer sizes and RTOS selection.
 *   3. Implement a transport layer (see dbg_transport_t) for your hardware.
 *   4. Call DBG_Init() once at startup, then use DBG_Printf() everywhere.
 */

#ifndef DBG_PRINT_H
#define DBG_PRINT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ERR_LVL_ERROR   = 0,
    ERR_LVL_WARNING = 1,
    ERR_LVL_INFO    = 2,
    ERR_LVL_DEBUG   = 3,
} err_lvl_t;

/* ---- Transport Interface ------------------------------------------------- */

typedef bool (*dbg_transport_send_fn)(const uint8_t *data, size_t len);
typedef bool (*dbg_transport_busy_fn)(void);

typedef struct {
    dbg_transport_send_fn   send;
    dbg_transport_busy_fn   is_busy;
} dbg_transport_t;

/* ---- Public API ---------------------------------------------------------- */

void        DBG_Init(const dbg_transport_t *transport);
void        DBG_TransferComplete(void);
void        DBG_SetLevel(err_lvl_t level);
err_lvl_t   DBG_GetLevel(void);

/**
 * @brief Print a formatted debug message if the level passes the current filter.
 *
 * The message is formatted into a pre-allocated pool slot and enqueued for
 * DMA transmission. This function returns immediately after enqueuing; the
 * actual UART transmission happens in the DMA completion ISR.
 *
 * When the message pool is full the message is silently dropped and counted
 * (see DBG_GetDropCount).
 *
 * Do NOT call from ISR context.
 *
 * @param msg_level  Severity level of this message.
 * @param fmt        printf-style format string.
 * @param ...        Format arguments.
 */
void DBG_Printf(err_lvl_t msg_level, const char *fmt, ...);

/**
 * @brief Get the number of DMA transfer errors since init.
 */
uint32_t DBG_GetDmaErrorCount(void);

/**
 * @brief Get the number of messages dropped due to a full pool since init.
 */
uint32_t DBG_GetDropCount(void);

#ifdef __cplusplus
}
#endif

#endif /* DBG_PRINT_H */
