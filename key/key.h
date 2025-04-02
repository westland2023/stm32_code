#ifndef __KEY_H
#define __KEY_H
#include "main.h"

typedef struct key{
	uint8_t short_press_flag;
	uint8_t long_press_flag;
	uint8_t always_press_flag;
	uint16_t count;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}KEY;//��ť�ṹ�� 

//�ж�ʱ������λms 
#define SHORT_KEY 50 //�̰��ж�ʱ�� 
#define LONG_KEY 500 //�����ж�ʱ�� 
#define ALWAYS_KEY LONG_KEY+500 //һֱ���ж��г� 

extern KEY sw_up,sw_down,sw_left,sw_right,sw_enter;//�ⲿ��������

void Key_Init(void);
void Key_Scan(KEY*key);
void TIM_Key_Scan(void);
void Key_Handle(void);

/* eg:
int main()
{
	Key_Init();
	
	while(1)
	{
		Key_Handle();
	}
} 
//��ʱ�ж��������1ms 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{
		TIM_Key_Scan();
	}
}
*/ 

#endif

