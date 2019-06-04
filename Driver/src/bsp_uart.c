/********************************************************************************
*    File Name    : bsp_uart.c
*    Copyright    : 
*    Module Name  :
*    
*    CPU/Device   : stm32f103c8t6(ARM-CM3)
*    RTOS         :
*    
*    Creat Date   : 2018/10/27
*    Author       : WGY
*--------------------Revision History--------------------
*    No Version Date 
********************************************************************************/

/********************************************************************************
*    Include File Section
********************************************************************************/
#include "bsp_uart.h"

void Usart_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	//--------定义两个时钟--------//
	RCC_APB2PeriphClockCmd(Gpio_clock,ENABLE);
	RCC_APB1PeriphClockCmd(Usart_clock,ENABLE);
	
	//-------结构体Gpio部分------ //
	GPIO_InitStructure.GPIO_Pin   = Gpio_TX ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Gpio_TX_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = Gpio_RX ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(Gpio_RX_Port,&GPIO_InitStructure);
	
	//--------结构体Usart部分----------//
	USART_InitStructure.USART_BaudRate   = Usart_baudrate;
	USART_InitStructure.USART_WordLength = Usart_bits;
	USART_InitStructure.USART_StopBits = Usart_Stopbits;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_Init(Debug_usart,&USART_InitStructure);
	
	//--------打开串口中断---配置优先级--------//
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = Nvic_channel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);
	
	//--------使能串口&中断---------//
	//USART_ITConfig(Debug_usart,USART_IT_RXNE,ENABLE);
	USART_Cmd(Debug_usart,ENABLE);
}

void Usart_sandbit_16(USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	//while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	//while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


void Usart_SendBit_8(USART_TypeDef *USARTx, uint8_t data)
{
	
	USART_SendData(USARTx,data);	
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	

}

void Usart_sandbyte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
