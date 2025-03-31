#include "include.h"

int32_t reset;
int value;
float weight;
float Weights=100.0;  //100g
int32_t Weights_100=8493860;  //100g

void HX711_Init(void)
{
	/*����һ��HX711_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*������ص�GPIO����ʱ��*/
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStruct.Pin = HX711_CLK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		  
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = HX711_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
	
unsigned long HX711_GetData(void)
{
	unsigned long Count;
	unsigned char i;
	HX711_SCK_L;
	delay_us(1);
	Count=0;
	while(HX711_DT);
	for (i=0;i<24;i++)
	{
		HX711_SCK_H;
		delay_us(1);
		Count=Count<<1;
		HX711_SCK_L;
		delay_us(1);
		if(HX711_DT)
			Count++;
	}
	HX711_SCK_H;
	delay_us(1);
	Count=Count^0x800000;
	//���λȡ��������λ����
	//��HX71оƬ�У�count��һ��32λ���з������������ڴ洢���ش������Ķ�����
	//��count�����λΪ1ʱ����ʾ����Ϊ��������HX711оƬ��֧�ָ����Ķ�����
	//��ˣ�Ϊ�˽�����ת��Ϊ��������Ҫ��count�����λȡ��������count��0x800000������������
	//������˵��0x800000�Ķ����Ʊ�ʾΪ100000000000000000000000����count������������
	//���Խ�count�����λ��1��Ϊ0���Ӷ��õ���Ӧ������������
	HX711_SCK_L;
	delay_us(1);
	return(Count);
}

void delay_us(uint32_t time)
{
	uint8_t i;

	while(time)
	{	  	  
		for (i = 0; i < 10; i++);
		time--;
	}
}
