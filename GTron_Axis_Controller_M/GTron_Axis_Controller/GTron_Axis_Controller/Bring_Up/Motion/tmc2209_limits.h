/*
 * tmc2209_limits.h
 *
 * Created: 22-07-2026 11:18:37
 *  Author: sreevathsank
 */ 


#ifndef TMC2209_LIMITS_H_
#define TMC2209_LIMITS_H_

#include "Bring_Up/IO_Expander/spi_io_expander.h"
#include "tmc2209_uart/TMC2209.h"
#include "tmc2209_uart/TMC2209_Motion.h"
#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"
#include "tmc2209_uart/Step_Counter.h"


typedef enum { LIMIT_OPEN_RIGHT, LIMIT_CLOSE_LEFT }TMC2209_Limit_Side_t;

#endif /* TMC2209_LIMITS_H_ */