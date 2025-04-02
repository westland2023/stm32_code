#include "include.h"


uint8_t mode_flag=0;//模式切换标志位
uint8_t start_flag=0;//延迟开始标志位
KEY sw_enter;//定义按钮宏定义


void Key_Init(void)//按键初始化，将所有标志位清空
{
	sw_enter.count=0;//按钮摁下计时
	sw_enter.GPIOx=GPIOC;
	sw_enter.GPIO_Pin=GPIO_PIN_15;
	sw_enter.long_press_flag=0;//长按标志位
	sw_enter.short_press_flag=0;//短按标志位
	sw_enter .always_press_flag=0;//一直按下标志位
}


uint8_t press;//按钮摁下状态
void Key_Scan(KEY *key)
{
	press=HAL_GPIO_ReadPin(key->GPIOx,key->GPIO_Pin);//读取指定引脚的电平
	if(press==0)//如果低电平，表示按钮按下，开始按下计时
	{
		key->count++;
		if(key->count>=ALWAYS_KEY)//当按下时间超过ALWAYS_KEY宏定义的时长，将一直按下标志位置1
			key->always_press_flag=1;
	}
	else//如果不是低电平，表示按钮松开，根据按下时长判断长按短按
	{
		key->always_press_flag=0;//按钮松开，清空一直按下标志位
		if(key->count>=LONG_KEY&&key->count<=ALWAYS_KEY)//如果按下时长在LONG_KEY和ALWAYS_KEY之间，按钮长按，长按标志位置高，清空其他标志位，防止冲突
		{
			key->long_press_flag=1;
			key->short_press_flag=0;
		}
		else if(key->count>=SHORT_KEY&&key->count<=LONG_KEY)//如果按下时长在LONG_KEY和SHORT_KEY之间，按钮短按，短按标志位置高，清空其他标志位，防止冲突
		{
			key->short_press_flag=1;
			key->long_press_flag=0;
		}
		key->count=0;//清空计时
	}
}


void TIM_Key_Scan(void)//在定时器中更新按钮信息
{
	Key_Scan(&sw_enter);//将按钮参数一个一个遍历，更新计数数据
}


void Key_Handle(void)//按钮信息处理
{
	if(sw_enter.short_press_flag==1)//如果sw_enter按钮短按，进行对应的操作
	{
		start_flag=1;//该标志位用于在延迟模式中启动延迟
		sw_enter.short_press_flag=0;//清空标志位
	}
	if(sw_enter.long_press_flag==1)//如果sw_enter按钮长按，进行对应的操作
	{
		mode_flag=!mode_flag;//由于只有两个模式，0和1足以表示，所以使用取反操作切换模式
		sw_enter.long_press_flag=0;//清楚标志位
	}
	if(sw_enter.always_press_flag==1)//如果sw_enter按钮一直按，进行对应的操作
	{
		sw_enter.always_press_flag=0;//清楚标志位
	}
}
