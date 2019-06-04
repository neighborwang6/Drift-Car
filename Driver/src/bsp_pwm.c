/********************************************************
*    File Name    :  bsp_pwm.h
*    Copyright    :  
*    Module Name  :  pwm generate
*    
*    CPU          :  ARM-CortexM3
*    RTOS         :  NONE
********************************************************/


/********************************************************
*    Inclide File Sections
********************************************************/
#include "bsp_pwm.h"

static void RCC_Configuration(void);//Configurse the different system clocks.
static void GPIO_Configuration(void);	//Configure the GPIO Pins


/********************************************************
*    Function Define
********************************************************/

/* pwm init */
void pwm_init(void)
{
	/*------------------------------------------------------
   The Source CK_INT@ 72MHz if the TIM_Prescaler = 0
	--------------------------------------------------------*/

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;   

	//Open the (gpio&tim)'s clk  
	RCC_Configuration();//Configurse the different system clocks.
  GPIO_Configuration();	//Configure the GPIO Pins

  /* Time Base unit Gonfiguration */
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_Period        = PWM_TIM_TimeBase_Period;//The Counter work as 0\1\0\1 mode.
  TIM_TimeBaseInitStruct.TIM_Prescaler     = PWM_TIM_TimeBase_Prescaler-1;//
  
	TIM_TimeBaseInit(PWM_TIM,&TIM_TimeBaseInitStruct);//TIM_TimeBaseInitStruct.TIM_RepetitionCounter
  
  /* OCx Config : Channel 3 Configuration in pwm mode */
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  //TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = PWM_TIM_OC_Pulse_Width;
	
	/* Configure the OC1 */
  TIM_OC1Init(TIM3,&TIM_OCInitStruct);
  TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3
  TIM_CCxCmd(TIM3,TIM_Channel_1,TIM_CCx_Enable);//Enables the TIM Capture Compare Channel x.

  /* Configure the OC2 */
  TIM_OC2Init(TIM3,&TIM_OCInitStruct);
  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3
  TIM_CCxCmd(TIM3,TIM_Channel_2,TIM_CCx_Enable);//Enables the TIM Capture Compare Channel x.	
	
	/* Configure the OC3 */
  TIM_OC3Init(TIM3,&TIM_OCInitStruct);
  TIM_OC3PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3
  TIM_CCxCmd(PWM_TIM,TIM_Channel_3,TIM_CCx_Enable);//Enables the TIM Capture Compare Channel x.
	
	/* Configure the OC4 */
  TIM_OC4Init(TIM3,&TIM_OCInitStruct);
  TIM_OC4PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3
  TIM_CCxCmd(PWM_TIM,TIM_Channel_4,TIM_CCx_Enable);//Enables the TIM Capture Compare Channel x.

  
  /* Tim3 Counter Enable */ 
  TIM_Cmd(TIM3,ENABLE);


}

//Configurse the different system clocks.
void RCC_Configuration(void)
{
	 /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

   /* GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

}

//Configure the GPIO Pins
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

		/* Configure the GPIOB */
  GPIO_InitStruct.GPIO_Mode  = PWM_TIM_GPIO_MODE;
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	
  GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	  /* Configure the GPIOA */
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);


}


/* Set the Duty Cycle */

void pwm_SetDutyCycle(void)
{
	  //TIM_SetCompare3(TIM3,1);//

}


	/* Tim3 Main Output Enable(Only the Tim1/Tim8 have) */
	//TIM_CtrlPWMOutputs(TIM3, ENABLE);
























