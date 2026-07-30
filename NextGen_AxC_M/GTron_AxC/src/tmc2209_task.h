#ifndef _TMC2209_TASK_H
#define _TMC2209_TASK_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "FreeRTOS.h"
#include "semphr.h"

#include "can_state.h"
#include "task_state.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

void TMC2209_TASK_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _TMC2209_TASK_H */

/*******************************************************************************
 End of File
 */

