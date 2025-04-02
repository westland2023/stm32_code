#include "include.h"

KEY sw_up,sw_down,sw_left,sw_right,sw_enter;//定义按钮宏定义

void Key_Init(void)//按键初始化，将所有标志位清空 
{ 
	  sw_up.count=0;//按钮摁下计时
	  sw_up.GPIOx=GPIOC;
	  sw_up.GPIO_Pin=GPIO_PIN_13;
	  sw_up.long_press_flag=0;//长按标志位
	  sw_up.short_press_flag=0;//短按标志位
	  sw_up .always_press_flag=0;//一直按下标志位
	  
	  sw_down.count=0;
	  sw_down.GPIOx=GPIOB;
	  sw_down.GPIO_Pin=GPIO_PIN_7;
	  sw_down.long_press_flag=0;
	  sw_down.short_press_flag=0;
	  sw_down .always_press_flag=0;
	  	
	  sw_left.count=0;
	  sw_left.GPIOx=GPIOB;
	  sw_left.GPIO_Pin=GPIO_PIN_1;
	  sw_left.long_press_flag=0;
	  sw_left.short_press_flag=0;
	  sw_left .always_press_flag=0;
	  	
	  sw_right.count=0;
	  sw_right.GPIOx=GPIOB;
	  sw_right.GPIO_Pin=GPIO_PIN_6;
	  sw_right.long_press_flag=0;
	  sw_right.short_press_flag=0;
	  sw_right .always_press_flag=0;
	  
	  sw_enter.count=0;
	  sw_enter.GPIOx=GPIOB;
	  sw_enter.GPIO_Pin=GPIO_PIN_3;
	  sw_enter.long_press_flag=0;
	  sw_enter.short_press_flag=0;
	  sw_enter .always_press_flag=0;
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

void TIM_Key_Scan(void)//在定时器中更新按钮信息，定时中断周期1ms 
{
		Key_Scan(&sw_up);//将按钮参数一个一个遍历，更新计数数据
		Key_Scan(&sw_down);
		Key_Scan(&sw_left);
		Key_Scan(&sw_right);
		Key_Scan(&sw_enter);
}

void Key_Handle(void)//按钮信息处理，放于主函数中 
{	
	  //上
	  if(sw_up.short_press_flag==1)//如果短按标志位置高，执行对应程序 
	  {

		    sw_up.short_press_flag=0;//清空标志位 
      }
	  if(sw_up.long_press_flag==1)//长按 
	  {

		    sw_up.long_press_flag=0;
	  }
	  if(sw_up.always_press_flag==1)//一直按 
	  {
		
		    sw_up.always_press_flag=0;
	  }
		
		//下
		if(sw_down.short_press_flag==1)
	  {

		    sw_down.short_press_flag=0;
      }
	  if(sw_down.long_press_flag==1)
	  {

		    sw_down.long_press_flag=0;
	  }
	  if(sw_down.always_press_flag==1)
	  {
		
		    sw_down.always_press_flag=0;
	  }
		
		//左
		if(sw_left.short_press_flag==1)
	  {

		    sw_left.short_press_flag=0;
      }
	  if(sw_left.long_press_flag==1)
	  {

		    sw_left.long_press_flag=0;
	  }
	  if(sw_left.always_press_flag==1)
	  {
		
		    sw_left.always_press_flag=0;
	  }
		
		//右
	  if(sw_right.short_press_flag==1)
	  {

		    sw_right.short_press_flag=0;
      }
	  if(sw_right.long_press_flag==1)
	  {

		    sw_right.long_press_flag=0;
	  }
	  if(sw_right.always_press_flag==1)
	  {
		
		    sw_right.always_press_flag=0;
	  }
		
		//确认
		if(sw_enter.short_press_flag==1)
	  {

		    sw_enter.short_press_flag=0;
      }
	  if(sw_enter.long_press_flag==1)
	  {

		    sw_enter.long_press_flag=0;
	  }
	  if(sw_enter.always_press_flag==1)
	  {
		
		    sw_enter.always_press_flag=0;
	  }
}

