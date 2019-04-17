#include "bsp_encoder.h"

/* Private function prototypes */
static void RCC_Encoder_L_Config(void);
static void GPIO_Encoder_L_Config(void);
static void RCC_Encoder_R_Config(void);
static void GPIO_Encoder_R_Config(void);


static void RCC_Encoder_L_Config(void)
{
  //TIM_Encoder_L clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  //AFIO clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

}


static void GPIO_Encoder_L_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);

}

void TIM_Encoder_L_Config(void)
{
  RCC_Encoder_L_Config();
  GPIO_Encoder_L_Config();
	
  //TIM3
  TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); 

  //Enable the TIM
  TIM_Cmd(TIM3,ENABLE);

}

static void RCC_Encoder_R_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

}

static void GPIO_Encoder_R_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA,&GPIO_InitStructure);

}


void TIM_Encoder_R_Config(void)
{
  RCC_Encoder_R_Config();
  GPIO_Encoder_R_Config();
  //TIM1
  TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); 

  //Enable the TIM
  TIM_Cmd(TIM1,ENABLE);
	
}
