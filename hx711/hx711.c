#include "include.h"

int32_t reset;
int value;
float weight;
float Weights=100.0;  //100g
int32_t Weights_100=8493860;  //100g

void HX711_Init(void)
{
	/*定义一个HX711_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*开启相关的GPIO外设时钟*/
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/*选择要控制的GPIO引脚*/
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
	//最高位取反，其他位不变
	//在HX71芯片中，count是一个32位的有符号整数，用于存储称重传感器的读数。
	//当count的最高位为1时，表示读数为负数，而HX711芯片不支持负数的读数。
	//因此，为了将负数转换为正数，需要将count的最高位取反，即将count与0x800000进行异或操作。
	//具体来说，0x800000的二进制表示为100000000000000000000000，与count进行异或操作后，
	//可以将count的最高位从1变为0，从而得到对应的正数读数。
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
