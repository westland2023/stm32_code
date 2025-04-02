#include "include.h"

schedule menu;//定义结构体


void Task_Init(schedule *task,uint32_t id,uint32_t targetime,char GPIOX,uint16_t GPIO_PIN)//初始化
{
	task->count[id]=0;
	task->flag[id]=0;
	task->targe_time[id]=targetime;
	task->GPIOx[id]=GPIOX;
	task->GPIO_Pin[id]=GPIO_PIN;
}


void TIM_Scheduler(schedule *task)//任务调度计时更新
{
	for(int i=0;i<ID_SCHEDULE;i++)//遍历调度表
		if(task->count[i]<task->targe_time[i])//如果计时小于目标时间
			task->count[i]++;//计时自增
		else//如果计时大于等于目标时间
		{
			task->flag[i]=!task->flag[i];//任务调度结束标志位置1
			task->count[i]=0;//计数清空
		}
}
void Schedule_Handle(schedule *task)//调度功能处理
{
	if(mode_flag==1)
	{
		for(int i=0;i<ID_SCHEDULE;i++)//遍历调度表
		{
			if(task->flag[i]==0)//调度表中标志位为高，将对应引脚拉高
			{
				if(task->GPIOx[i]=='A')
					HAL_GPIO_WritePin(GPIOA,task->GPIO_Pin[i],GPIO_PIN_RESET);
				else if(task->GPIOx[i]=='B')
					HAL_GPIO_WritePin(GPIOB,task->GPIO_Pin[i],GPIO_PIN_RESET);
				else if(task->GPIOx[i]=='C')
					HAL_GPIO_WritePin(GPIOC,task->GPIO_Pin[i],GPIO_PIN_RESET);
			}
			else//调度表中标志位为低，将对应引脚拉低
			{		
				HAL_GPIO_WritePin(GPIOC,task->GPIO_Pin[i],GPIO_PIN_SET);
				if(task->GPIOx[i]=='A')
					HAL_GPIO_WritePin(GPIOA,task->GPIO_Pin[i],GPIO_PIN_SET);
				else if(task->GPIOx[i]=='B')
					HAL_GPIO_WritePin(GPIOB,task->GPIO_Pin[i],GPIO_PIN_SET);
				else if(task->GPIOx[i]=='C')
					HAL_GPIO_WritePin(GPIOC,task->GPIO_Pin[i],GPIO_PIN_SET);
			}
		}
	}
}



