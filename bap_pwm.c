/********************************************************
*
********************************************************/


/********************************************************
*    Inclide File Sections
********************************************************/
#include "bsp_pwm.h"


/********************************************************
*    Function Define
********************************************************/

/* pwm init */
void pwm_init(void)
{
	//
  GPIO_InitTypeDef   GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;   

	//Open the (gpio&tim)'s clk
  PWM_TIM_GPIO_APBxClock_FUN(PWM_TIM_GPIO_CLK,ENABLE);//
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK,ENABLE);//
   
	//GPIO Cofig
	GPIO_InitStruct.GPIO_Mode  = PWM_TIM_GPIO_MODE;
  GPIO_InitStruct.GPIO_Pin   = PWM_TIM_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = PWM_TIM_GPIO_SPEED;
  GPIO_Init(PWM_TIM_GPIO_PORT,&GPIO_InitStruct);

	//Time-base unit Gonfig
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period    = 5000;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1;
  TIM_TimeBaseInit(PWM_TIM,&TIM_TimeBaseInitStruct);//TIM_TimeBaseInitStruct.TIM_RepetitionCounter
  
	//TIM_ARRPreloadConfig(PWM_TIM,ENABLE);//Enables TIMx peripheral Preload register on ARR. 
  //TIM_PrescalerConfig(PWM_TIM,2,TIM_PSCReloadMode_Immediate);//Configures the TIMx Prescaler. 
  // TIM_Cmd(PWM_TIM,ENABLE);	//Enables or disables the specified TIM peripheral. (the CEN bit is written to 1,)

  //OCx Config
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OC3PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3

  //TIM_CCxCmd(PWM_TIM,PWM_TIM_CHN,TIM_CCx_Enable);//Enables the TIM Capture Compare Channel x.

//Enables or disables the specified TIM peripheral. 
  TIM_Cmd(TIM3,ENABLE);
	


}

