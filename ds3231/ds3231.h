#ifndef __DS3231_H
#define	__DS3231_H
#include "main.h"

#define DS3231_ADDR 0xD0  // DS3231 I2C��ַ

typedef struct 
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;			
	uint8_t year;
	uint8_t month;
	uint8_t date;
	uint8_t week;
	uint8_t temperature;
}_calendar_obj;	

extern _calendar_obj calendar;

void ds3231_set_seconds(uint8_t year,uint8_t month,uint8_t date,uint8_t week,uint8_t hour,uint8_t minute,uint8_t second);//У׼ʱ�� 
void ds3231_get_seconds(void);//��ȡʱ�䣬��ȡ��ʱ����Ϣ������calendar�ṹ���� 

#endif


