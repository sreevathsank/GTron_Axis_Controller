/*
 * Hybrid_Trigger.h
 *
 * Created: 07-04-2026 12:14:35
 *  Author: sreevathsank
 */ 


#ifndef HYBRID_TRIGGER_H_
#define HYBRID_TRIGGER_H_

#include <atmel_start.h>
#include "Global_Vars.h"
#include "TMC-API/tmc/ic/TMC4671/TMC4671.h"

typedef enum {
	HYBRID_MODE_OFF			= 0,
	HYBRID_MODE_INSPECTION	= 1,
	HYBRID_MODE_N_SHOT		= 2,
	NO_OF_HYBRID_STATES
}Hybrid_Mode_t;	

#include "Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.h"
/** 
 * \brief	Triggers the pin that is directly connected to Sys Ctrl to trigger the Camera.
 *
 * @param	void
 * @return	void
 **/
void trigger_Camera_Line(void);

/** 
 * \brief	The function that checks motor position wrt to sensor trigger flag received from EIC whether to trigger camera or not.
 *
 * @param	void
 * @return	void
 **/
void check_For_Hybrid_Trigger(void);

#endif /* HYBRID_TRIGGER_H_ */