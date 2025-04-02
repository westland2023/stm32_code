#ifndef __LOG_H  //�������������Ƿ�������λ����־ϵͳ
#define __LOG_H

#include "main.h"
	#define USER_MAIN_DEBUG //��������
	#ifdef  USER_MAIN_DEBUG  //��������,���������USER_MAIN_DEBUG�������ĸ��걻����ʱ���ܴ�ӡ��ͬ

	#define user_main_printf(format, ...)   printf(format "\r\n",##__VA_ARGS__)//�ɱ�����꣬##�޲�ʱ����
	#define user_main_info(format, ...)			printf("[main]info: " format "\r\n", ##__VA_ARGS__)
	#define user_main_debug(format, ...)		printf("[main]debug: " format "\r\n", ##__VA_ARGS__)
	#define user_main_error(format, ...)		printf("[main]error: " format "\r\n", ##__VA_ARGS__)

	#else    //���û�ж���USER_MAIN_DEBUG�������ӡ�κζ�������Ϊû�д���

	#define user_main_printf(format, ...)
	#define user_main_info(format, ...)
	#define user_main_debug(format, ...)
	#define user_main_error(format, ...)

	#endif

	#define LOG 1  //1Ϊ���� 0Ϊ����
	
#endif
//��־ϵͳ��delay.c�д���
