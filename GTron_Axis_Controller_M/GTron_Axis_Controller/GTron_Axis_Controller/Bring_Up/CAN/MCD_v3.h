/*
 * MCD_v3.h
 *
 * Created: 06-02-2024 12:11:54
 *  Author: sreevathsank
 */ 


#ifndef MCD_V3_H_
#define MCD_V3_H_

#include "All_Headers.h"

double convert_PPS_To_RPM(double value);

void do_4671_Ping(void);

void do_Move_Done_Ping(void);

void reeler_Move_Done(void);

void do_Ref_Search_Ping(void);

void reply_MCD_Common(uint8_t ad, uint8_t cmd, uint8_t typ, uint8_t mot);

void reply_Echo(uint32_t message_Id, int32_t data);

void write_MCD_MC(int32_t address,int32_t ad, int32_t cmd, int32_t typ, int32_t mot);

#endif /* MCD_V3_H_ */