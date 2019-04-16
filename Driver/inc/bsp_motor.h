/*******************************************************************************
*    File Name    :
*    Copyright    :
*    Moduel Name  :
*******************************************************************************/

/*******************************************************************************
*    Multi-Include-Provent Section
*******************************************************************************/
#ifndef _BSP_MOTOR_H_
#define _BSP_MOTOR_H_

/*******************************************************************************
*    Include File Section
*******************************************************************************/
#include "stm32f10x.h"


/********************************************************************************
*    Private define 
********************************************************************************/

//MotorCctrl(PWM)-GPIO Configuration
//GPIOC
#define  MOTOR_PWM_GPIO_Mode   GPIO_Mode_AF_PP;
#define  MOTOR_PWM_GPIO_Pin    GPIO_Pin_6 | GPIO_Pin_7;
#define  MOTOR_PWM_GPIO_Speed  GPIO_Speed_50MHz;
/********************************************************************************
*    The Hardware Device Private define 
********************************************************************************/

//GPIOE
#define  MOTOR_DRIVER_IN_GPIO  GPIOE
#define  MOTOR_DRIVER_EN_GPIO  GPIOE

#define  MOTOR_DRIVER_IN1      GPIO_Pin_7
#define  MOTOR_DRIVER_IN2      GPIO_Pin_8

#define  MOTOR_DRIVER_IN3      GPIO_Pin_9
#define  MOTOR_DRIVER_IN4      GPIO_Pin_10

#define  ENA  GPIO_Pin_13
#define  ENB  GPIO_Pin_14

/*******************************************************************************
*    Prototype Declare Section
*******************************************************************************/

void TIM1_init(void);//TIM1 init.


void Set_MotorSpeed_L(uint32_t DutyCycle);//Set the Duty Cycle of the coresponding tim
void Set_MotorSpeed_R(uint32_t DutyCycle);//Set the Duty Cycle of the coresponding tim

void Motor_L_ForwardEnable(void);//Left motor forward
void Motor_L_BackUpEnable(void);//Left motor backup

void Motor_R_ForwardEnable(void);//Left motor forward
void Motor_R_BackUpEnable(void);//Right motor backup

void Stop_Motor_L(void);//Stop left Motor
void Stop_Motor_R(void);//Stop right Motor


#endif
