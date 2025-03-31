#ifndef __HX711_H
#define	__HX711_H
#include "main.h"

#define HX711_SCK_H				HAL_GPIO_WritePin(HX711_CLK_GPIO_Port,HX711_CLK_Pin,GPIO_PIN_SET);
#define HX711_SCK_L				HAL_GPIO_WritePin(HX711_CLK_GPIO_Port,HX711_CLK_Pin,GPIO_PIN_RESET);
#define HX711_DT			    HAL_GPIO_ReadPin(HX711_DT_GPIO_Port,HX711_DT_Pin)

extern int32_t reset;
extern int value;
extern float weight;
extern float Weights;
extern int32_t Weights_100;

void HX711_Init(void);
unsigned long HX711_GetData(void);
void delay_us(uint32_t time);

/* eg:
int main()
{
	HX711_Init();
	
	while(1)
	{
		value = HX711_GetData();
		weight=(float)(value-reset)*Weights/(float)(Weights_100-reset);
		weight=KalmanFilter(&kfp1,weight);
		printf("÷ÿ¡ø: %f\r\n",weight);
	}
}
*/ 

#endif

