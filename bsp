/********************************************************
*    Finle Name    :
*    Copyright    :
*    CPU          :
********************************************************/

#ifndef _BSP_PWM_H_
#define _BSP_PWM_H_

/********************************************************
*    Inclide File Sections
********************************************************/
#include "stm32f10x.h"

/*******************************************************
*    Macro Define Section
********************************************************/

//GPIO
#define PWM_TIM_GPIO_PORT            GPIOB 
#define PWM_TIM_GPIO_MODE            GPIO_Mode_AF_PP
#define PWM_TIM_GPIO_PIN             GPIO_Pin_0
#define PWM_TIM_GPIO_SPEED           GPIO_Speed_50MHz
#define PWM_TIM_GPIO_CLK             RCC_APB2Periph_GPIOB 
#define PWM_TIM_GPIO_APBxClock_FUN   RCC_APB2PeriphClockCmd

//TIM
#define PWM_TIM                 TIM3
#define PWM_TIM_CHN             TIM_Channel_3
#define PWM_TIM_OCMode          TIM_OCMode_PWM1 
#define PWM_TIM_CounterMode     TIM_CounterMode_Up
#define PWM_TIM_CLK             RCC_APB1Periph_TIM3
#define PWM_TIM_APBxClock_FUN   RCC_APB1PeriphClockCmd

//OC
#define PWM_TIM_OCxInit         TIM_OC2Init
#define PWM_TIM_OCxPerload      TIM_OC2PreloadConfig


/*******************************************************
*    	Prototype Declear Section
********************************************************/

void pwm_init(void);//pwm init
void PWM_SetPeriod();












#endif

