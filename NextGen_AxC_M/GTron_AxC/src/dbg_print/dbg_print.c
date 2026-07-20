/**
 * @file dbg_print.c
 * @brief Debug Print Library - Non-blocking pool+queue implementation
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
#include "task.h"

static SemaphoreHandle_t s_dbg_mutex;

#define DBG_MUTEX_LOCK()     xSemaphoreTake(s_dbg_mutex, portMAX_DELAY)
#define DBG_MUTEX_UNLOCK()   xSemaphoreGive(s_dbg_mutex)
#define DBG_ISR_YIELD()      ((void)0)

/*
 * Brief IRQ mask for preventing the DMA ISR from racing with the drain
 * kick in DBG_Printf().  Uses the port's save/restore primitives.
 */
#define DBG_IRQ_LOCK(p)    do { (p) = (uint32_t)portSET_INTERRUPT_MASK_FROM_ISR(); } while (0)
#define DBG_IRQ_UNLOCK(p)  portCLEAR_INTERRUPT_MASK_FROM_ISR(p)

static void dbg_rtos_init(void)
{
    s_dbg_mutex = xSemaphoreCreateMutex();
}

#elif defined(DBG_RTOS_NONE)

#define DBG_MUTEX_LOCK()     ((void)0)
#define DBG_MUTEX_UNLOCK()   ((void)0)
#define DBG_ISR_YIELD()      ((void)0)

static inline uint32_t dbg_get_primask(void)
{
    uint32_t result;
    __asm volatile ("mrs %0, primask" : "=r"(result));
    return result;
}
static inline void dbg_disable_irq(void)
{
    __asm volatile ("cpsid i" ::: "memory");
}
static inline void dbg_set_primask(uint32_t mask)
{
    __asm volatile ("msr primask, %0" :: "r"(mask) : "memory");
}

#define DBG_IRQ_LOCK(p)    do { (p) = dbg_get_primask(); dbg_disable_irq(); } while (0)
#define DBG_IRQ_UNLOCK(p)  dbg_set_primask(p)

static void dbg_rtos_init(void)
{
}

#else
#error "dbg_print_config.h: Define exactly one of DBG_RTOS_FREERTOS or DBG_RTOS_NONE"
#endif

/* ---- Message Pool -------------------------------------------------------- */

typedef struct {
    char     data[DBG_STAGE_SIZE];
    uint16_t len;
    uint16_t offset;
    bool     in_use;
} dbg_msg_t;

static dbg_msg_t     s_pool[DBG_MSG_POOL_SIZE];
static uint8_t       s_queue[DBG_MSG_POOL_SIZE];
static volatile uint8_t s_q_head;
static volatile uint8_t s_q_tail;
static volatile int8_t  s_active;   /* -1 = idle, else pool index being DMA'd */
static uint8_t       s_dma_buf[DBG_BUF_SIZE];

static volatile uint32_t s_dma_errors;
static volatile uint32_t s_drop_count;

/* ---- Static Data --------------------------------------------------------- */

static const dbg_transport_t *s_transport;
static volatile err_lvl_t     s_current_level;

static const char * const s_level_prefix[] = {
    "[ERR] ",
    "[WRN] ",
    "[INF] ",
    "[DBG] ",
};

/* ---- Forward Declarations ------------------------------------------------ */

static void drain(void);

/* ---- Helpers ------------------------------------------------------------- */

static int format_message(char *buf, size_t buf_size,
                          err_lvl_t msg_level, const char *fmt, va_list args)
{
    int prefix_len = snprintf(buf, buf_size, "%s",
                              s_level_prefix[msg_level]);
    if (prefix_len < 0) {
        prefix_len = 0;
    } else if ((size_t)prefix_len >= buf_size) {
        prefix_len = (int)(buf_size - 1U);
    }

    int msg_len = vsnprintf(buf + prefix_len,
                            buf_size - (size_t)prefix_len,
                            fmt, args);
    if (msg_len < 0) {
        msg_len = 0;
    }

    int total = prefix_len + msg_len;
    if ((size_t)total >= (buf_size - 1U)) {
        total = (int)(buf_size - 1U);
    }
    return total;
}

static int8_t pool_alloc(void)
{
    for (int8_t i = 0; i < (int8_t)DBG_MSG_POOL_SIZE; i++) {
        if (!s_pool[i].in_use) {
            s_pool[i].in_use = true;
            return i;
        }
    }
    return -1;
}

static inline void pool_free(int8_t idx)
{
    s_pool[idx].in_use = false;
}

/* ---- Drain Pump ----------------------------------------------------------
 *
 * Called from ISR (DBG_TransferComplete) and from task context
 * (DBG_Printf kick, under mutex + IRQ disabled).
 * Transfers the next pending chunk via DMA.
 */

static void drain(void)
{
    int8_t idx;

    if (s_active >= 0) {
        /* Continue transmitting the active message's next chunk */
        idx = s_active;
    } else {
        /* No active transfer — dequeue the next pending message */
        if (s_q_head == s_q_tail) {
            return;   /* queue empty */
        }
        idx = (int8_t)s_queue[s_q_tail];
        s_active = idx;
    }

    dbg_msg_t *msg = &s_pool[idx];
    uint16_t remaining = msg->len - msg->offset;
    if (remaining == 0U) {
        /* Should not happen — offset == len means message is done */
        pool_free(idx);
        s_q_tail = (uint8_t)((s_q_tail + 1U) % DBG_MSG_POOL_SIZE);
        s_active = -1;
        return;
    }

    uint16_t chunk = remaining;
    if (chunk > DBG_BUF_SIZE) {
        chunk = DBG_BUF_SIZE;
    }

    memcpy(s_dma_buf, msg->data + msg->offset, chunk);

    if (s_transport->send(s_dma_buf, chunk)) {
        msg->offset = (uint16_t)(msg->offset + chunk);
        /* If this chunk completed the message, the ISR will free +
           advance the queue. We keep s_active set so the ISR knows
           which message was in flight. */
    } else {
        /* send() rejected — channel unexpectedly busy.
         * Leave message in queue, mark idle, count error, retry next kick. */
        s_dma_errors++;
        s_active = -1;
    }
}

/* ---- Public Functions ---------------------------------------------------- */

void DBG_Init(const dbg_transport_t *transport)
{
    s_transport     = transport;
    s_current_level = DBG_DEFAULT_LEVEL;
    s_active        = -1;
    s_q_head        = 0U;
    s_q_tail        = 0U;
    s_dma_errors    = 0U;
    s_drop_count    = 0U;

    for (int i = 0; i < DBG_MSG_POOL_SIZE; i++) {
        s_pool[i].in_use = false;
    }

    dbg_rtos_init();
}

void DBG_TransferComplete(void)
{
    if (s_active < 0) {
        return;
    }

    int8_t idx = s_active;
    dbg_msg_t *msg = &s_pool[idx];

    /*
     * Check whether the entire message has been sent.
     * Multi-chunk messages fire multiple completions; only when
     * offset >= len is the message fully drained.
     */
    if (msg->offset >= msg->len) {
        pool_free(idx);
        s_q_tail = (uint8_t)((s_q_tail + 1U) % DBG_MSG_POOL_SIZE);
        s_active = -1;
    }

    drain();

    DBG_ISR_YIELD();
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

    /*
     * Bounds-check msg_level against the prefix array.
     * s_level_prefix has exactly 4 entries (ERR_LVL_ERROR .. ERR_LVL_DEBUG).
     */
    if (msg_level > ERR_LVL_DEBUG) {
        return;
    }

    /*
     * Format into a stack buffer first.  This keeps the mutex hold time
     * extremely short — the expensive vsnprintf happens outside the lock
     * and does not block DMA transfers in any way.
     */
    char local_buf[DBG_STAGE_SIZE];
    va_list args;
    va_start(args, fmt);
    int total_len = format_message(local_buf, sizeof(local_buf),
                                   msg_level, fmt, args);
    va_end(args);

    if (total_len <= 0) {
        return;
    }

    DBG_MUTEX_LOCK();

    int8_t slot = pool_alloc();
    if (slot < 0) {
        s_drop_count++;
        DBG_MUTEX_UNLOCK();
        return;
    }

    dbg_msg_t *msg = &s_pool[slot];
    memcpy(msg->data, local_buf, (size_t)total_len);
    msg->len    = (uint16_t)total_len;
    msg->offset = 0U;

    s_queue[s_q_head] = (uint8_t)slot;
    s_q_head = (uint8_t)((s_q_head + 1U) % DBG_MSG_POOL_SIZE);

    /*
     * Kick the drain pump if the DMA is idle.  Disable IRQ briefly
     * to prevent the ISR from racing with s_active / send().
     */
    if (s_active < 0) {
        uint32_t primask;
        DBG_IRQ_LOCK(primask);
        if (s_active < 0) {
            drain();
        }
        DBG_IRQ_UNLOCK(primask);
    }

    DBG_MUTEX_UNLOCK();
}

uint32_t DBG_GetDmaErrorCount(void)
{
    return s_dma_errors;
}

uint32_t DBG_GetDropCount(void)
{
    return s_drop_count;
}
