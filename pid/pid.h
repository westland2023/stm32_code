#ifndef __PID_H
#define __PID_H
#include "main.h"

typedef struct _PID
{
	float kp,ki,kd;
	float error,lastError;
	float integral,maxIntegral;
	float output,maxOutput; 
	uint32_t i_count; 
}PID;

extern PID pid;

#define LIMIT(x,min,max) (x)=(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

void PID_Clear(PID *pid);
void PID_SingleCalc(PID *pid,float reference,float feedback);
void PID_Init(PID *pid,float p,float i,float d,float maxI,float maxOut);

#endif
