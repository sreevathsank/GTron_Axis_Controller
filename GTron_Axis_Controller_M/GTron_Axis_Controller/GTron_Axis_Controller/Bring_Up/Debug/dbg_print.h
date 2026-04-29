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

/* ---- Error Levels -------------------------------------------------------- */

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

void      DBG_Init(const dbg_transport_t *transport);
void      DBG_TransferComplete(void);
void      DBG_SetLevel(err_lvl_t level);
err_lvl_t DBG_GetLevel(void);
void      DBG_Printf(err_lvl_t msg_level, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* DBG_PRINT_H */
