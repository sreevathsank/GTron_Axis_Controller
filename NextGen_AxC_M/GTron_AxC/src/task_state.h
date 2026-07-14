/* 
 * File:   task_state.h
 * Author: sreevathsank
 *
 * Created on July 13, 2026, 5:38 PM
 */

#ifndef TASK_STATE_H
#define	TASK_STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

// Pin configuration (set at init, read-only thereafter)
extern axis_current         g_axis_id;
extern SouthBridge_t        g_sbridge_addr;

// ISR ? task flags (volatile: written by ISR, read by exactly one task)
extern volatile bool        g_diag_pending;         // DIAG EIC ? TMC2209_TASK
extern volatile uint8_t     g_limit_flags;         // LIM EICs ? TMC4671_TASK
#define LIM_RT_BIT          0x01
#define LIM_LFT_BIT         0x02
extern volatile bool        g_ioxp_int_pending;     // IOXP EIC ? TMC2209_TASK
    
// Cross-task flags
extern volatile bool        g_flash_busy;           // SUPERVISOR (during flash ops) ? both motor tasks

// Motor_Info_t instances (allocated statically, one per physical motor)
extern Motor_Info_t         g_motor_reeler1;
extern Motor_Info_t         g_motor_guide;
extern Motor_Info_t         g_motor_varrest1;
extern Motor_Info_t         g_motor_varrest2;
extern Motor_Info_t         g_motor_reeleradj1;
extern Motor_Info_t         g_motor_reeleradj2;
extern Motor_Info_t         g_motor_frontcam;
extern Motor_Info_t         g_motor_reeler2;

// Pointer array for indexed access (used by CAN parser dispatch)
extern Motor_Info_t         *mot_array[NO_OF_MOT_INDICES];

// Convenience pointers (set during init based on sbridge_addr)
extern Motor_Info_t         *p_reeler1_info;
extern Motor_Info_t         *p_guide_info;
extern Motor_Info_t         *p_varrest1_info;
extern Motor_Info_t         *p_varrest2_info;
extern Motor_Info_t         *p_reeleradj1_info;
extern Motor_Info_t         *p_reeleradj2_info;
extern Motor_Info_t         *p_frontcam_info;
extern Motor_Info_t         *p_reeler2_info;

// RTOS handles (needed to create tasks, use queues from modules)
extern QueueHandle_t        g_q_can_work;           // 16 x 16B
extern QueueHandle_t        g_q_4671_rx;            // 8 x 16B
extern QueueHandle_t        g_q_2209_rx;            // 8 x 16B
extern QueueHandle_t        g_q_sup_rx;             // 8 x 16B
extern QueueHandle_t        g_q_debug;              // 16 x 132B
extern SemaphoreHandle_t    g_m_sercom3;          // mutex for flash + IOXP SPI bus

extern TaskHandle_t         h_4671, h_can, h_2209, h_sup, h_dbg;

// Heartbeat counters
extern volatile uint32_t    g_heartbeat_can;
extern volatile uint32_t    g_heartbeat_tmc4671;
extern volatile uint32_t    g_heartbeat_tmc2209;
extern volatile uint32_t    g_heartbeat_supervisor;
extern volatile uint32_t    * const g_heartbeat_array[4];


#ifdef	__cplusplus
}
#endif

#endif	/* TASK_STATE_H */

