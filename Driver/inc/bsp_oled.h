/********************************************************
*    File Name:
*    Copyright:   
*    Module
********************************************************/
#ifndef _BSP_OLED_H_
#define _BSP_OLED_H_

/*******************************************************
*    Include File Section
*******************************************************/
#include "stm32f10x.h"
#include "bsp_ssd1306.h"

/********************************************************
*    Macro Define Section
********************************************************/
#define OLED_WHOLE_LIGHT   0xff
#define OLED_WHOLE_OFF     0X00
/********************************************************
*    Prototype Declear Section
********************************************************/
void OLED_Init(void);//Init the oled display
void OLED_Fill(uint8_t data);//Fill the whole panel
void OLED_W_Addr(uint8_t page,uint8_t column);//page(0 to 7),column(0 to 122)
void OLED_W_ASCII(uint8_t a);//
void OLED_W_DEC(uint32_t temp);//Display one 'Number': (0 to 65536)
void OLED_W_DEC_SIX(uint32_t temp);
void OLED_W_String(char* string);//Display a String




#endif
