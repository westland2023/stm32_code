#include "include.h"

KEY sw_up,sw_down,sw_left,sw_right,sw_enter;//���尴ť�궨��

void Key_Init(void)//������ʼ���������б�־λ��� 
{ 
	  sw_up.count=0;//��ť���¼�ʱ
	  sw_up.GPIOx=GPIOC;
	  sw_up.GPIO_Pin=GPIO_PIN_13;
	  sw_up.long_press_flag=0;//������־λ
	  sw_up.short_press_flag=0;//�̰���־λ
	  sw_up .always_press_flag=0;//һֱ���±�־λ
	  
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

uint8_t press;//��ť����״̬
void Key_Scan(KEY *key)
{
	  press=HAL_GPIO_ReadPin(key->GPIOx,key->GPIO_Pin);//��ȡָ�����ŵĵ�ƽ
	  if(press==0)//����͵�ƽ����ʾ��ť���£���ʼ���¼�ʱ
	  {
	  	  key->count++;
	  	  if(key->count>=ALWAYS_KEY)//������ʱ�䳬��ALWAYS_KEY�궨���ʱ������һֱ���±�־λ��1
						key->always_press_flag=1;
	  }
	  else//������ǵ͵�ƽ����ʾ��ť�ɿ������ݰ���ʱ���жϳ����̰�
	  {
				key->always_press_flag=0;//��ť�ɿ������һֱ���±�־λ
	  	  if(key->count>=LONG_KEY&&key->count<=ALWAYS_KEY)//�������ʱ����LONG_KEY��ALWAYS_KEY֮�䣬��ť������������־λ�øߣ����������־λ����ֹ��ͻ
	  	  {
	  	    	key->long_press_flag=1;
						key->short_press_flag=0;
	  	  }
	  	  else if(key->count>=SHORT_KEY&&key->count<=LONG_KEY)//�������ʱ����LONG_KEY��SHORT_KEY֮�䣬��ť�̰����̰���־λ�øߣ����������־λ����ֹ��ͻ
	  	  {
						key->short_press_flag=1;
						key->long_press_flag=0;
				}
				key->count=0;//��ռ�ʱ
	  }
}

void TIM_Key_Scan(void)//�ڶ�ʱ���и��°�ť��Ϣ����ʱ�ж�����1ms 
{
		Key_Scan(&sw_up);//����ť����һ��һ�����������¼�������
		Key_Scan(&sw_down);
		Key_Scan(&sw_left);
		Key_Scan(&sw_right);
		Key_Scan(&sw_enter);
}

void Key_Handle(void)//��ť��Ϣ���������������� 
{	
	  //��
	  if(sw_up.short_press_flag==1)//����̰���־λ�øߣ�ִ�ж�Ӧ���� 
	  {

		    sw_up.short_press_flag=0;//��ձ�־λ 
      }
	  if(sw_up.long_press_flag==1)//���� 
	  {

		    sw_up.long_press_flag=0;
	  }
	  if(sw_up.always_press_flag==1)//һֱ�� 
	  {
		
		    sw_up.always_press_flag=0;
	  }
		
		//��
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
		
		//��
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
		
		//��
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
		
		//ȷ��
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

