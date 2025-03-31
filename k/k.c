#include "k.h"

Kalman kfp1;/*�������˲��ṹ��*/

void Kalman_Init()/*��ʼֵ*/
{
        kfp1.Last_P = 1;
        kfp1.Now_P = 0;                
        kfp1.out = 0;                        
        kfp1.Kg = 0;                
        kfp1.Q = 0.002;
        kfp1.R = 0.03026;
}

float KalmanFilter(Kalman *kfp,float input)
{
   //Ԥ��Э����̣�kʱ��ϵͳ����Э���� = k-1ʱ�̵�ϵͳЭ���� + ��������Э����
   kfp->Now_P = kfp->Last_P + kfp->Q;
   //���������淽�̣����������� = kʱ��ϵͳ����Э���� / ��kʱ��ϵͳ����Э���� + �۲�����Э���
   kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
   //��������ֵ���̣�kʱ��״̬����������ֵ = ״̬������Ԥ��ֵ + ���������� * ������ֵ - ״̬������Ԥ��ֵ��
   kfp->out = kfp->out + kfp->Kg * (input -kfp->out);//��Ϊ��һ�ε�Ԥ��ֵ������һ�ε����ֵ
   //����Э�����: ���ε�ϵͳЭ����� kfp->LastP ����һ������׼����
   kfp->Last_P = (1.0-kfp->Kg) * kfp->Now_P;
   return kfp->out;
}

