/******************************************************************************
*    Incldue File Setion
******************************************************************************/
#include "bsp_tim.h"

/*******************************************************************************
*    Global variable
*******************************************************************************/




/*******************************************************************************
*    Prototype Define Section
*******************************************************************************/

void TIM2_init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
  TIM2_RCC_Configuration();   //Configurse the different system clocks.
  TIM2_NVIC_Configuration();  //Configure the NVIC
	
  /* Init The TIM2 */
  //TIM Base unit configure
  TIM_TimeBaseInitStructure.TIM_Period = 36 - 1;
  TIM_TimeBaseInitStructure.TIM_Prescaler = 1000 - 1; 
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_ICPSC_DIV1;
	
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	

  //Enables TIMx peripheral Preload register on ARR. 
  TIM_ARRPreloadConfig (TIM2,ENABLE);

  /* ENABLE the counter */
  TIM_Cmd(TIM2,ENABLE);
	
  /* Interrupt Configure */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//Enable the CC1 Interrupt Request

}


//Configurse the different system clocks.
void TIM2_RCC_Configuration(void)
{
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

}

//Configure the nested vectored interrupt controller.
void TIM2_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
  /* Enable the TIM2 global Interrupt */
  
  NVIC_Init(&NVIC_InitStructure);

}  



