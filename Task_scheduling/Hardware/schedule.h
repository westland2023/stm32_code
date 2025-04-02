#ifndef __SCHEDULE_H
#define __SCHEDULE_H
#include "main.h"
#define ID_SCHEDULE 2  //调度任务数量
#define A 'A'
#define B 'B'
#define C 'C'
typedef struct _schedule
{
	uint8_t flag[ID_SCHEDULE];
	uint32_t count[ID_SCHEDULE];
    uint32_t targe_time[ID_SCHEDULE];	
	char GPIOx[ID_SCHEDULE];
	uint16_t GPIO_Pin[ID_SCHEDULE];
}schedule;

extern schedule menu;
void Task_Init(schedule *task,uint32_t targetime,uint32_t id,char GPIOX,uint16_t GPIO_PIN);
void TIM_Scheduler(schedule *task);
void Schedule_Handle(schedule *task);

#endif

