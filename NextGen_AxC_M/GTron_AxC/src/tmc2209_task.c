#include "tmc2209_task.h"

void TMC2209_TASK_Tasks ( void )
{
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

  // 1. IOXP Interrupt - motor limit swithces.
  if(g_ioxp_int_pending) {
    if( xSemaphoreTake(g_m_sercom3, 0) == pdTRUE ) {
      // Got mutex - read IOXP register.
      //read_ioxp_and_detect_limits();
      xSemaphoreGive(g_m_sercom3);
      
    }
  }

  // 2. Process CAN Commands.
  Can_Cmd_t cmd;
  while( xQueueReceive(g_q_2209_rx, &cmd, 0) == pdTRUE ) {
    //dispatch_2209_cmd(&cmd);
  }

  // 3. TMC2209 DIAG pin detection.
  if(g_diag_pending) {
    // handle TMC2209 issue.
  }

  // 4. Poll MSCNT if any of the TMC2209 motors are moving. Handles Move Done too.
  if(g_2209_moving) {
    //check_Which_2209_Motor_Moving();
  }
  return;
}


/*******************************************************************************
 End of File
 */
