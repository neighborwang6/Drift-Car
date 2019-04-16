/**
 *@file 
 *@author WGY
 *@version v0.0
 *@date 19-September-2018
 *@brief This file is for the Led_lib
 */


#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

/*macro for led*/
#define LED_R_GPIO_PORT      GPIOC
#define LED_R_GPIO_CLK       RCC_APB2Periph_GPIOC
#define LED_R_GPIO_Pin       GPIO_Pin_13

/*Define the ctl of led with register*/
#define digitalHi(p,i)      {p->BSRR |= i;}  //Hi Level Output
#define digitalLo(p,i)      {p->BRR  |= i;}  //Lo Level Output
#define digitalToggle(p,i)  {p->ODR  ^= i;}  //Toggle the level    
 
/*Define the Statue of Led*/
#define LED_R_ON       digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_Pin)
#define LED_R_OFF      digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_Pin)
#define LED_R_TOGGLE   digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_Pin)


/*控制LED引脚的初始化函数*/
void LED_GPIO_Init(void);


#endif
