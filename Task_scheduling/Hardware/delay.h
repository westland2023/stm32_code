#ifndef __DELAY_H
#define __DELAY_H
#include "main.h"
#define ID_DELAY 4
typedef struct _delay
{
	uint8_t flag[ID_DELAY];
	uint8_t sw[ID_DELAY];
	uint32_t count[ID_DELAY];
    uint32_t targe_time[ID_DELAY];
}delay;
extern delay list;

void TIM_Delay(delay *list);
void Delay_Init(delay *list,uint32_t id,uint32_t targetime);
void Delay_Start(delay *list,uint32_t id);
void Delay_Handle(delay *list);
#endif



