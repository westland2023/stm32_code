#ifndef __OLED_H_
#define __OLED_H_

#include "i2c.h"

void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_WriteData(uint8_t Data);
void OLED_WriteCommand(uint8_t Command);


void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
uint32_t OLED_Pow(uint32_t X, uint32_t Y);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowNumber_bmp(uint8_t Line,uint8_t Column,uint8_t Number);

extern uint8_t buffer[8][128];
extern uint8_t ling[10][4][32];

#endif
