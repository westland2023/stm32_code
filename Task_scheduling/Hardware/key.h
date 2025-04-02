#ifndef __KEY_H
#define __KEY_H
#include "main.h"
typedef struct key{
	uint8_t short_press_flag;
	uint8_t long_press_flag;
	uint8_t always_press_flag;
	uint16_t count;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}KEY;

#define SHORT_KEY 50
#define LONG_KEY 500
#define ALWAYS_KEY LONG_KEY+500


extern KEY sw_enter;//外部变量声明
extern uint8_t mode_flag;
extern uint8_t start_flag;


void Key_Init(void);
void Key_Scan(KEY*key);
void TIM_Key_Scan(void);
void Key_Handle(void);

#endif

