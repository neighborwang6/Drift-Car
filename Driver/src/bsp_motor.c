/********************************************************
*    File Name    :  bsp_motor.c
*    Copyright    :
*    Module Name  :
********************************************************/

/********************************************************
*    Include File Section
********************************************************/
#include "bsp_motor.h"

/* The Motor Driver State Ctrl */
static void TIM_MotoDrive_GPIO_Config(void);//Configure the GPIO Pins
static void TIM_MotoDrive_RCC_Config(void);

/**
*Configure the RCC of TIM1.
*/
static void TIM_MotoDrive_RCC_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
}

static void TIM_MotoDrive_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//5.14KHz
void TIM_MotoDrive_Config(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  TIM_OCInitTypeDef         TIM_OCInitStructure;
  //TIM_BDTRInitTypeDef       TIM_BDTRInitStructure;
  
	TIM_MotoDrive_RCC_Config();
  TIM_MotoDrive_GPIO_Config();
	
  /* Time Base configuration */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = 6;  //
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 2000;  //周期
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
  
  /* Channel 3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1000 - 1;  //占空比
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
 
 	/* PWM1 Mode configuration: Channel3 */
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_Pulse = 1000 - 1;
	 
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM4, ENABLE); 

  //Automatic Output enable
  //TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  //TIM_BDTRConfig(TIM4, &TIM_BDTRInitStructure);
	
  //TIM enable
  TIM_Cmd(TIM4, ENABLE);
 
  //Main Output Enable
  TIM_CtrlPWMOutputs(TIM4, ENABLE);

}

void GPIO_MotoDrive_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_11 | GPIO_Pin_12; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

}

/*******************************************************************************
*    Motor - App Section
*******************************************************************************/

void Motor_L_Ctrl(uint16_t Speed_DutyCycle,Driection dri)
{
	if(dri == Forward)
	{
		AIN1_L
	  AIN2_H

	}
	else if(dri == Backward)
	{
		AIN1_H
	  AIN2_L

	}
	else
	{
		AIN1_H
	  AIN2_H
	
	}
	TIM_SetCompare3(TIM4,Speed_DutyCycle);//Set the Duty Cycle 

}
void Motor_R_Ctrl(uint16_t Speed_DutyCycle,Driection dri)
{
	if(dri == Forward)
	{
		BIN1_H
	  BIN2_L
	}
	else if(dri == Backward)
	{
		BIN1_L
	  BIN2_H
		
	}
	else
	{
		BIN1_H
	  BIN2_H
	
	}
	TIM_SetCompare4(TIM4,Speed_DutyCycle);//Set the Duty Cycle;
}

//左侧刹车
void Motor_L_ShortBrake(void)
{
  AIN1_H
  AIN2_H
}
//右侧刹车
void Motor_R_ShortBrake(void)
{
	BIN1_H
	BIN2_H
	
}

/*
 * 参数 1 ：左电机的速度
 * 参数 2 ：右电机的速度
 * 参数 3 ：电机的死区补偿
*/
void MotorSpeedOut(int LeftMotorOut,int RightMotorOut,int MotorDeadVal)
{
	//Left motor Ctrl
  if(LeftMotorOut > 0)
	 Motor_L_Ctrl(LeftMotorOut + MotorDeadVal,Backward);
  else 
		Motor_L_Ctrl(-LeftMotorOut + MotorDeadVal,Forward);

	//Right motor Ctrl
  if(RightMotorOut > 0)
    Motor_R_Ctrl(RightMotorOut + MotorDeadVal,Backward);
  else
    Motor_R_Ctrl(-RightMotorOut + MotorDeadVal,Forward);

}
