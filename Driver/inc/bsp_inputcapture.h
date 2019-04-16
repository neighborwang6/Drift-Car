/*******************************************************************************
*    File Name    :  inputcapture
*    Copyright    :
*    Module Name  :
*******************************************************************************/

#ifndef _BSP_INPUTCAPTURE_H_
#define _BSP_INPUTCAPTURE_H_

/*******************************************************************************
*    Include File
*******************************************************************************/
#include "stm32f10x.h"

/*******************************************************************************
*    Macro Define Section
*******************************************************************************/
/* PB.08-TIM4CH3 */


/* PA.01-TIM2CH2 */


/*******************************************************************************
*    Prototype Declear Section    
*******************************************************************************/

/* TIM4-CH3 */
void TIM4_init(void);

void TIM4_NVIC_Configuration(void);//Configure the nested vectored interrupt controller.
void TIM4_GPIO_Configuration(void);//Configure the GPIO Pins
void TIM4_RCC_Configuration(void);//Configurse the different system clocks. 





#endif

