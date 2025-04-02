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
}KEY;//按钮结构体 

//判定时长，单位ms 
#define SHORT_KEY 50 //短按判定时长 
#define LONG_KEY 500 //长按判定时长 
#define ALWAYS_KEY LONG_KEY+500 //一直按判定市场 

extern KEY sw_up,sw_down,sw_left,sw_right,sw_enter;//外部变量声明

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
//定时中断溢出周期1ms 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{
		TIM_Key_Scan();
	}
}
*/ 

#endif

