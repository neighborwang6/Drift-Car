/********************************************************
*    File Name    :  bsp_key.h
*    Copyright    :  
*    Module Name  :  key operation

********************************************************/
/********************************************************
*    Muti-include-prevent Section
********************************************************/
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

/********************************************************
*    Include File Section
********************************************************/
#include "stm32f10x"
/********************************************************
*    Macro Define Section
********************************************************/
#define KEY_GPIO_PORT     GPIOA
#define KEY_GPIO_CLK      RCC_APB2Periph_GPIOA
#define KEY_GPIO_PIN      GPIO_Pin_0





#endif