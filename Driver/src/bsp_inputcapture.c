/*******************************************************************************
*    Include File Section
*******************************************************************************/
#include "bsp_inputcapture.h"
/*******************************************************************************
*    Global variable
*******************************************************************************/
TIM_ICInitTypeDef  TIM_ICInitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;


/*******************************************************************************
*    Prototype Define Section
*******************************************************************************/

/* Tim4 as Input Capture ---------------------------------------------------- */
/* PB.08-TIM4CH3 */
void TIM4_init(void)
{
  TIM4_RCC_Configuration();   //Configurse the different system clocks.
  TIM4_GPIO_Configuration();  //Configure the GPIO Pins	
  TIM4_NVIC_Configuration();  //Configure the nested vectored interrupt controller.
  
  /* Time Base unit Gonfiguration */
  TIM_TimeBaseInitStructure.TIM_Prescaler  = 143;//Sampling @??MHz = APB1_Clk@72MHz/(TIM_Prescaler - 1)
  TIM_TimeBaseInitStructure.TIM_Period     = 0xfffe;
  
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//TIM_TimeBaseInitStruct.TIM_RepetitionCounter
	
  TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3
	
  /* ICx Config : Channel3 of TIM4 Configuration in INPUT CAPTURE mode */
	/* Init The TIM4-CH1 */
  TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter    = 0x3;   //0011: fSAMPLING=fCK_INT, N=8

  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
  /* Init The TIM4-CH2 */
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
  /* Init The TIM4-CH3 */
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
  /* Init The TIM4-CH4 */
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  
  TIM_ICInit(TIM4,&TIM_ICInitStructure);

  /* TIM Enable Counter */
  TIM_Cmd(TIM4,ENABLE);
	
  /* Enable the CC3 Interrupt Request */
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);	
  TIM_ITConfig(TIM4,TIM_IT_CC1,ENABLE);	
  TIM_ITConfig(TIM4,TIM_IT_CC2,ENABLE);	
  TIM_ITConfig(TIM4,TIM_IT_CC3,ENABLE);	
  TIM_ITConfig(TIM4,TIM_IT_CC4,ENABLE);
	

}

/**
*  Configurse the different system clocks. 
*/
void TIM4_RCC_Configuration(void)
{
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

  /* GPIOD clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
  /* AFIO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

}

/**
*  Configure the GPIO Pins
*/
void TIM4_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM4 channel 1-4(PD.12-PD.15) configuration */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  /* TIM4 alternate function remapping */
  GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
 
}

/**
*  Configure the nested vectored interrupt controller.
*/
void TIM4_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStructure);
}


