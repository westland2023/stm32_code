#include "include.h"

schedule menu;//����ṹ��


void Task_Init(schedule *task,uint32_t id,uint32_t targetime,char GPIOX,uint16_t GPIO_PIN)//��ʼ��
{
	task->count[id]=0;
	task->flag[id]=0;
	task->targe_time[id]=targetime;
	task->GPIOx[id]=GPIOX;
	task->GPIO_Pin[id]=GPIO_PIN;
}


void TIM_Scheduler(schedule *task)//������ȼ�ʱ����
{
	for(int i=0;i<ID_SCHEDULE;i++)//�������ȱ�
		if(task->count[i]<task->targe_time[i])//�����ʱС��Ŀ��ʱ��
			task->count[i]++;//��ʱ����
		else//�����ʱ���ڵ���Ŀ��ʱ��
		{
			task->flag[i]=!task->flag[i];//������Ƚ�����־λ��1
			task->count[i]=0;//�������
		}
}
void Schedule_Handle(schedule *task)//���ȹ��ܴ���
{
	if(mode_flag==1)
	{
		for(int i=0;i<ID_SCHEDULE;i++)//�������ȱ�
		{
			if(task->flag[i]==0)//���ȱ��б�־λΪ�ߣ�����Ӧ��������
			{
				if(task->GPIOx[i]=='A')
					HAL_GPIO_WritePin(GPIOA,task->GPIO_Pin[i],GPIO_PIN_RESET);
				else if(task->GPIOx[i]=='B')
					HAL_GPIO_WritePin(GPIOB,task->GPIO_Pin[i],GPIO_PIN_RESET);
				else if(task->GPIOx[i]=='C')
					HAL_GPIO_WritePin(GPIOC,task->GPIO_Pin[i],GPIO_PIN_RESET);
			}
			else//���ȱ��б�־λΪ�ͣ�����Ӧ��������
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



