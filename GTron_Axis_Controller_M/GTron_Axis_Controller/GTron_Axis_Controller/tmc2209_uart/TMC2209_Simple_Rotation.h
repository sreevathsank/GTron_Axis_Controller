/* 
 * File:   TMC2209_Simple_Rotation.h
 * Author: sreevathsank
 *
 * Created on February 25, 2025, 6:13 PM
 */

#ifndef TMC2209_SIMPLE_ROTATION_H
#define	TMC2209_SIMPLE_ROTATION_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "TMC2209.h"

void move_guide_motor( void );
void initAllMotors(uint16_t icID);
void read_Init_Registers(uint16_t icID);


#ifdef	__cplusplus
}
#endif

#endif	/* TMC2209_SIMPLE_ROTATION_H */

