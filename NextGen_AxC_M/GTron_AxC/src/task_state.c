#include "task_state.h"

volatile bool       g_diag_pending          = false;
volatile bool       g_ioxp_int_pending      = false;

volatile uint8_t    g_limit_flags           = 0;

QueueHandle_t       g_q_can_work            = NULL;
QueueHandle_t       g_q_4671_rx             = NULL; 
QueueHandle_t       g_q_2209_rx             = NULL; 
QueueHandle_t       g_q_sup_rx              = NULL;  
QueueHandle_t       g_q_debug               = NULL;   

SemaphoreHandle_t   g_m_sercom3             = NULL;
