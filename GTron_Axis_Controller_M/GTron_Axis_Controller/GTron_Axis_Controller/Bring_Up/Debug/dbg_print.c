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

static SemaphoreHandle_t s_dma_done_sem;
static SemaphoreHandle_t s_dbg_mutex;

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

static void dbg_rtos_init(void)
{
    s_dma_done_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(s_dma_done_sem);
    s_dbg_mutex = xSemaphoreCreateMutex();
}

#elif defined(DBG_RTOS_NONE)

static volatile bool s_dma_done_flag = true;

#define DBG_SEM_WAIT()      do { while (!s_dma_done_flag) { /* spin */ } \
                                 s_dma_done_flag = false; } while (0)
#define DBG_SEM_GIVE()      (s_dma_done_flag = true)
#define DBG_SEM_GIVE_ISR()  (s_dma_done_flag = true)
#define DBG_MUTEX_TAKE()    /* no-op */
#define DBG_MUTEX_GIVE()    /* no-op */

static void dbg_rtos_init(void)
{
    s_dma_done_flag = true;
}

#else
#error "dbg_print_config.h: Define exactly one of DBG_RTOS_FREERTOS or DBG_RTOS_NONE"
#endif

/* ---- Static Data --------------------------------------------------------- */

static char     s_dbg_buf[2][DBG_BUF_SIZE];
static char     s_dbg_stage[DBG_STAGE_SIZE];
static volatile uint8_t s_active_buf;
static err_lvl_t s_current_level;
static const dbg_transport_t *s_transport;

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
    if (msg_level > s_current_level) {
        return;
    }

    DBG_MUTEX_TAKE();

    int prefix_len = snprintf(s_dbg_stage, DBG_STAGE_SIZE, "%s",
                              s_level_prefix[msg_level]);
    if (prefix_len < 0) {
        prefix_len = 0;
    }

    va_list args;
    va_start(args, fmt);
    int msg_len = vsnprintf(s_dbg_stage + prefix_len,
                            (size_t)(DBG_STAGE_SIZE - prefix_len),
                            fmt, args);
    va_end(args);

    if (msg_len < 0) {
        msg_len = 0;
    }

    int total_len = prefix_len + msg_len;
    if (total_len > (DBG_STAGE_SIZE - 1)) {
        total_len = DBG_STAGE_SIZE - 1;
    }

    int remaining  = total_len;
    int src_offset = 0;

    while (remaining > 0) {
        DBG_SEM_WAIT();

        int chunk = remaining;
        if (chunk > DBG_BUF_SIZE) {
            chunk = DBG_BUF_SIZE;
        }

        memcpy(s_dbg_buf[s_active_buf], s_dbg_stage + src_offset,
               (size_t)chunk);

        s_transport->send((const uint8_t *)s_dbg_buf[s_active_buf],
                          (size_t)chunk);

        s_active_buf ^= 1u;

        src_offset += chunk;
        remaining  -= chunk;
    }

    DBG_MUTEX_GIVE();
}
