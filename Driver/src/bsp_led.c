/*@file Single_Color_LedDriver 
 *@author WGY
 *@versoin v0.0
 *@date 19-September-2018
 *@brief This file provides all the led functions.
 */

#include "bsp_led.h"


/*控制LED引脚的初始化函数*/
void LED_GPIO_Init(void)
{
  /*定义一个GPIO的初始化结构体*/
  GPIO_InitTypeDef GPIO_InitStruct;
	
  /*配置结构体的参数*/
  GPIO_InitStruct.GPIO_Pin   = LED_R_GPIO_Pin;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;        
	
  /*Enable GPIOC clocks*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//AFIO clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	   
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
  /*初始化端口*/
  GPIO_Init(LED_R_GPIO_PORT,&GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOB,&GPIO_InitStruct);

  GPIO_SetBits(GPIOA,GPIO_Pin_10|GPIO_Pin_15);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_3);
}
