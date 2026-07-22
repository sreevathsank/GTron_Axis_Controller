/*
 * tmc2209_limits.c
 *
 * Created: 22-07-2026 11:13:56
 *  Author: sreevathsank
 */ 
#include "tmc2209_limits.h"

static void TMC2209_Lim_Stop_Motor(Motor_Info_t *m) 
{
	tmc2209_writeRegister(m->comms.uart_addr, TMC2209_VACTUAL, 0);
	m->motor_state        = MOTOR_STOPPED_STATE;
	m->flags.move_given   = false;
	is_tmc2209_mot_moving = false;
	return;	
}

void TMC2209_Handle_Limit_Hit(Motor_Info_t *m, TMC2209_Limit_Side_t side)
{
	m->move_dir.prev		= m->move_dir.curr;
	
	TMC2209_Lim_Stop_Motor(m);
	update_TMC2209_Step_Tracking(m);
	
	switch(side) {
		case LIMIT_OPEN_RIGHT: {
			m->move_dir.at_rlimit			= m->move_dir.curr;
			m->position.right_open_limit	= m->step_tracker.total_steps;
			m->flags.move_to_open_lim		= false;
			break;
		}
		case LIMIT_CLOSE_LEFT: {
			m->move_dir.at_llimit			= m->move_dir.curr;
			m->step_tracker.total_steps		= 0;
			m->step_tracker.total_dist		= 0;
			m->position.left_close_limit	= m->step_tracker.total_steps;
			m->flags.move_to_close_lim		= false;
			break;
		}
		default: break;
	}
	return;
}