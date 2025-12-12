/* 
 * File:   TMC2209_Simple_Rotation.h
 * Author: sreevathsank
 *
 * Created on 24 September, 2025, 11:26 AM
 */

#ifndef TMC2209_SIMPLE_ROTATION_H
#define	TMC2209_SIMPLE_ROTATION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "TMC2209.h"	

void move_guide_motor(uint32_t loop_count);
void init_tmc2209_motor(uint16_t icID);
void read_Init_Registers(uint16_t icID);


#ifdef	__cplusplus
}
#endif

#endif	/* TMC2209_SIMPLE_ROTATION_H */


