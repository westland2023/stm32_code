#ifndef __K_H
#define __K_H

#include "main.h"

typedef struct 
{
    float Last_P;//上次估算协方差
    float Now_P;//当前估算协方差
    float out;//卡尔曼滤波器输出
    float Kg;//卡尔曼增益
    float Q;//过程噪声协方差
    float R;//观测噪声协方差
}Kalman;

extern Kalman kfp1;

void Kalman_Init(void);//初始化卡尔曼结构体参数 
float KalmanFilter(Kalman *kfp,float input);//卡尔曼滤波函数

/*  eg：
int main()
{
	Kalman_Init();
	float adc1=0;
	while(1)
	{
		adc1=ADC_GET();//使用自己封装的adc函数 
		adc1= KalmanFilter(&kfp1,adc1);
		printf("%f\n",adc1);//此时输出的adc1已经过卡尔曼滤波 
	}
} 
*/ 

#endif

