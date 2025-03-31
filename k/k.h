#ifndef __K_H
#define __K_H

#include "main.h"

typedef struct 
{
    float Last_P;//�ϴι���Э����
    float Now_P;//��ǰ����Э����
    float out;//�������˲������
    float Kg;//����������
    float Q;//��������Э����
    float R;//�۲�����Э����
}Kalman;

extern Kalman kfp1;

void Kalman_Init(void);//��ʼ���������ṹ����� 
float KalmanFilter(Kalman *kfp,float input);//�������˲�����

/*  eg��
int main()
{
	Kalman_Init();
	float adc1=0;
	while(1)
	{
		adc1=ADC_GET();//ʹ���Լ���װ��adc���� 
		adc1= KalmanFilter(&kfp1,adc1);
		printf("%f\n",adc1);//��ʱ�����adc1�Ѿ����������˲� 
	}
} 
*/ 

#endif

