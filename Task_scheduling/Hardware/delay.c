#include "include.h"

delay list;

void Delay_Init(delay *list,uint32_t id,uint32_t targetime)
{
	list->count[id]=0;
	list->targe_time[id]=targetime;
}


void Delay_Start(delay *list,uint32_t id)
{
	list->flag[id]=0;
	list->sw[id]=0;
}


void TIM_Delay(delay *list)
{
	for(int i=0;i<ID_DELAY;i++)
		if(list->sw[i]==0)
		{
			if(list->count[i]<list->targe_time[i])
				list->count[i]++;
			else
			{
				list->sw[i]=1;
				list->flag[i]=1;
				list->count[i]=0;
			}
		}
}

static uint8_t log_start=1;
void Delay_Handle(delay *list)
{
	if(mode_flag==0)//�ӳ��б���
	{
		if(list->flag[0]==0)
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		else	
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		if(list->flag[1]==0)
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_RESET);
		else	
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET);
	}	
	if(list->flag[2]==1)
	{
		//��־��ӡ
		#if LOG
			if(log_start==1)
			{
				if(mode_flag==0)
				{
					user_main_info("infospeed=%d    mode_flag=%d    led:%d    buzzer:%d",list->targe_time[2],mode_flag,list->flag[0],list->flag[1]);
					//OLED_ShowString(0,0,"infospeed:",OLED_8X16);    OLED_ShowNum(90,0,list->targe_time[2],3,OLED_8X16);
					//OLED_ShowString(0,16,"mode_flag:",OLED_8X16);    OLED_ShowNum(90,16,mode_flag,3,OLED_8X16);
					//OLED_ShowString(0,32,"led:",OLED_8X16);   		OLED_ShowNum(90,32,list->flag[0],3,OLED_8X16);
					//OLED_ShowString(0,48,"buzzer:",OLED_8X16);   	OLED_ShowNum(90,48,list->flag[1],3,OLED_8X16);
				}
				else if(mode_flag==1)
				{
					user_main_info("infospeed=%d    mode_flag=%d    led:%d    buzzer:%d",list->targe_time[2],mode_flag,menu.flag[0],menu.flag[1]);
				    //OLED_ShowString(0,0,"infospeed:",OLED_8X16);    OLED_ShowNum(90,0,list->targe_time[2],3,OLED_8X16);
					//OLED_ShowString(0,16,"mode_flag:",OLED_8X16);    OLED_ShowNum(90,16,mode_flag,3,OLED_8X16);
					//OLED_ShowString(0,32,"led:",OLED_8X16);   		OLED_ShowNum(90,32,menu.flag[0],3,OLED_8X16);
					//OLED_ShowString(0,48,"buzzer:",OLED_8X16);   	OLED_ShowNum(90,48,menu.flag[1],3,OLED_8X16);
				}
			}
		#endif
		Delay_Start(list,2);//�ӳ��б�1��ʼ
	}
	if(list->flag[3]==1)
	{
		//��־����
		uint8_t data=Data_command();
		if(data==0)
		{
			log_start=1;
			mem();
		}
		else if(data==1)
		{
			log_start=0;
			mem();
		}
		else if(data==2)
		{
			list->targe_time[2]+=10;//��־���ͼ���ӳ�
			mem();
		}
		else if(data==3)
		{
			list->targe_time[2]-=10;//��־���ͼ������
			mem();
		}
		if(list->targe_time[2]<10)//���ͼ�����޼���������10ms������ռ��cpu����������
			list->targe_time[2]=10;
		Delay_Start(list,3);//�ӳ��б�1��ʼ
	}
}

