/**
 * @file dbg_print.c
 * @brief Debug Print Library - Implementation
 *
 * This file contains NO hardware-specific references. All hardware interaction
 * is delegated to the user-provided transport layer (dbg_transport_t).
 */

#include "dbg_print.h"
#include "dbg_print_config.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* ---- RTOS Abstraction ---------------------------------------------------- */

#if defined(DBG_RTOS_FREERTOS)

#include "FreeRTOS.h"
#include "semphr.h"

/** @internal Binary semaphore signaled by DBG_TransferComplete(). */   
static SemaphoreHandle_t    s_dma_done_sem;

/** @internal Mutex to serialize access to DBG_Printf() from multiple tasks. */
static SemaphoreHandle_t    s_dbg_mutex;

#define DBG_SEM_WAIT()      xSemaphoreTake(s_dma_done_sem, portMAX_DELAY)
#define DBG_SEM_GIVE()      xSemaphoreGive(s_dma_done_sem)
#define DBG_SEM_GIVE_ISR()  do {                                            \
                                BaseType_t xWoken = pdFALSE;                \
                                xSemaphoreGiveFromISR(s_dma_done_sem,       \
                                                      &xWoken);             \
                                portYIELD_FROM_ISR(xWoken);                 \
                            } while (0)
#define DBG_MUTEX_TAKE()    xSemaphoreTake(s_dbg_mutex, portMAX_DELAY)
#define DBG_MUTEX_GIVE()    xSemaphoreGive(s_dbg_mutex)

/**
 * @internal
 * @brief Create FreeRTOS synchronization primitives.
 */
static void dbg_rtos_init(void)
{
    s_dma_done_sem = xSemaphoreCreateBinary();
    /* Give once so the very first transfer does not block. */
    xSemaphoreGive(s_dma_done_sem);

    s_dbg_mutex = xSemaphoreCreateMutex();
}

#elif defined(DBG_RTOS_NONE)

/** @internal Volatile flag used as a bare-metal binary semaphore. */
static volatile bool s_dma_done_flag = true;

#define DBG_SEM_WAIT()      do { while (!s_dma_done_flag) { /* spin */ } \
                                 s_dma_done_flag = false; } while (0)
#define DBG_SEM_GIVE()      (s_dma_done_flag = true)
#define DBG_SEM_GIVE_ISR()  (s_dma_done_flag = true)
#define DBG_MUTEX_TAKE()    /* no-op */
#define DBG_MUTEX_GIVE()    /* no-op */

/**
 * @internal
 * @brief Initialize bare-metal synchronization (reset flag).
 */
static void dbg_rtos_init(void)
{
    s_dma_done_flag = true;
}

#else
#error "dbg_print_config.h: Define exactly one of DBG_RTOS_FREERTOS or DBG_RTOS_NONE"
#endif

/* ---- Static Data --------------------------------------------------------- */

/**
 * @internal
 * @brief Double-buffer for DMA transfers.
 *
 * While one buffer is being transmitted by the transport, the next message
 * can be formatted into the other.
 */
static char s_dbg_buf[2][DBG_BUF_SIZE];

/**
 * @internal
 * @brief Staging buffer for vsnprintf().
 *
 * The full formatted message (prefix + user text) is written here first,
 * then copied in chunks into the DMA transfer buffers.
 */
static char s_dbg_stage[DBG_STAGE_SIZE];

/**
 * @internal
 * @brief Index of the currently active DMA buffer (0 or 1).
 */
static volatile uint8_t s_active_buf;

/**
 * @internal
 * @brief Current error level threshold.
 */
static err_lvl_t s_current_level;

/**
 * @internal
 * @brief Stored transport pointer provided by the user at initialization.
 */
static const dbg_transport_t *s_transport;

/**
 * @internal
 * @brief Level prefix strings, indexed by err_lvl_t.
 */
static const char * const s_level_prefix[] = {
    "[ERR] ",
    "[WRN] ",
    "[INF] ",
    "[DBG] ",
};

/* ---- Public Functions ---------------------------------------------------- */

void DBG_Init(const dbg_transport_t *transport)
{
    s_transport     = transport;
    s_active_buf    = 0;
    s_current_level = DBG_DEFAULT_LEVEL;

    dbg_rtos_init();
}

void DBG_TransferComplete(void)
{
    DBG_SEM_GIVE_ISR();
}

void DBG_SetLevel(err_lvl_t level)
{
    s_current_level = level;
}

err_lvl_t DBG_GetLevel(void)
{
    return s_current_level;
}

void DBG_Printf(err_lvl_t msg_level, const char *fmt, ...)
{
    /* Level filter: discard if this message is below the current threshold. */
    if (msg_level > s_current_level) {
        return;
    }

    DBG_MUTEX_TAKE();

    /* ---- Stage 1: Format the complete message into the staging buffer ---- */

    /* Write the level prefix. */
    int prefix_len = snprintf(s_dbg_stage, DBG_STAGE_SIZE, "%s",
                              s_level_prefix[msg_level]);
    if (prefix_len < 0) {
        prefix_len = 0;
    }

    /* Write the user-formatted message after the prefix. */
    va_list args;
    va_start(args, fmt);
    int msg_len = vsnprintf(s_dbg_stage + prefix_len,
                            (size_t)(DBG_STAGE_SIZE - prefix_len),
                            fmt, args);
    va_end(args);

    if (msg_len < 0) {
        msg_len = 0;
    }

    /* Compute total length, clamped to the staging buffer capacity. */
    int total_len = prefix_len + msg_len;
    if (total_len > (DBG_STAGE_SIZE - 1)) {
        total_len = DBG_STAGE_SIZE - 1;
    }

    /* ---- Stage 2: Send in chunks via the transport ----------------------- */

    int remaining  = total_len;
    int src_offset = 0;

    while (remaining > 0) {
        /* Wait for the previous DMA transfer to complete. */
        DBG_SEM_WAIT();

        /* Determine chunk size: up to DBG_BUF_SIZE bytes. */
        int chunk = remaining;
        if (chunk > DBG_BUF_SIZE) {
            chunk = DBG_BUF_SIZE;
        }

        /* Copy the chunk into the active DMA buffer. */
        memcpy(s_dbg_buf[s_active_buf], s_dbg_stage + src_offset,
               (size_t)chunk);

        /* Initiate the transfer. */
        s_transport->send((const uint8_t *)s_dbg_buf[s_active_buf],
                          (size_t)chunk);

        /* Swap to the other buffer for the next chunk. */
        s_active_buf ^= 1u;

        src_offset += chunk;
        remaining  -= chunk;
    }

    DBG_MUTEX_GIVE();
}
