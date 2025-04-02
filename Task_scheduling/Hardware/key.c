#include "include.h"


uint8_t mode_flag=0;//ģʽ�л���־λ
uint8_t start_flag=0;//�ӳٿ�ʼ��־λ
KEY sw_enter;//���尴ť�궨��


void Key_Init(void)//������ʼ���������б�־λ���
{
	sw_enter.count=0;//��ť���¼�ʱ
	sw_enter.GPIOx=GPIOC;
	sw_enter.GPIO_Pin=GPIO_PIN_15;
	sw_enter.long_press_flag=0;//������־λ
	sw_enter.short_press_flag=0;//�̰���־λ
	sw_enter .always_press_flag=0;//һֱ���±�־λ
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


void TIM_Key_Scan(void)//�ڶ�ʱ���и��°�ť��Ϣ
{
	Key_Scan(&sw_enter);//����ť����һ��һ�����������¼�������
}


void Key_Handle(void)//��ť��Ϣ����
{
	if(sw_enter.short_press_flag==1)//���sw_enter��ť�̰������ж�Ӧ�Ĳ���
	{
		start_flag=1;//�ñ�־λ�������ӳ�ģʽ�������ӳ�
		sw_enter.short_press_flag=0;//��ձ�־λ
	}
	if(sw_enter.long_press_flag==1)//���sw_enter��ť���������ж�Ӧ�Ĳ���
	{
		mode_flag=!mode_flag;//����ֻ������ģʽ��0��1���Ա�ʾ������ʹ��ȡ�������л�ģʽ
		sw_enter.long_press_flag=0;//�����־λ
	}
	if(sw_enter.always_press_flag==1)//���sw_enter��ťһֱ�������ж�Ӧ�Ĳ���
	{
		sw_enter.always_press_flag=0;//�����־λ
	}
}
