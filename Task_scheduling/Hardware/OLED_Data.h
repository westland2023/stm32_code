#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*�����ַ��ֽڿ��*/
#define OLED_CHN_CHAR_WIDTH			2		//UTF-8�����ʽ��3��GB2312�����ʽ��2

/*��ģ������Ԫ*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//��������
	uint8_t Data[32];						//��ģ����
} ChineseCell_t;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];

/*ͼ����������*/
extern const uint8_t Diode[];
extern const uint8_t huaji[];
extern const uint8_t BMP1[];//������/
extern const uint8_t BMP2[];//ǰ����/
extern const uint8_t BMP3[];//��ת��/
extern const uint8_t BMP4[];//��ת��/
extern const uint8_t BMP5[];//���������ٺ�����
extern const uint8_t BMP6[];//˯��������ͨ��/
extern const uint8_t BMP7[];//love������/
extern const uint8_t BMP8[];//��˯��������ˮ��
extern const uint8_t BMP9[];//������
extern const uint8_t BMP10[];//��Ƥ��/
extern const uint8_t BMP11[];//�Ժ��������ĵ��Ժ���
extern const uint8_t BMP12[];//èè��
/*��������ĸ�ʽ�������λ�ü����µ�ͼ����������*/
//...

#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
