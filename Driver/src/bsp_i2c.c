/********************************************************************************
*    File Name    :
*    Copyright    :
*    Module Name  :
*
*    CPU          :
*    RTOS         :
*  
*    Creste Date  :
*    Author       :
*
*    Abstract Description
********************************************************************************/
#include "bsp_i2c.h"



/* Config the i2c periph:
   1.Init the GPIO periph
   2.Init the I2C Periph
*/
void I2C_Conf(void)
{
  /* GPIO Periph Init */
  GPIO_InitTypeDef GPIO_InitStruct;
  I2C_InitTypeDef  I2C_InitStruct;
  
  /* I2C1 Init */
  
#ifdef I2C1_SCL_GPIO_Pin
  
  /* I2C1 - GPIO Init */
  I2C1_RCC_ClockCmd(RCC_APB1Periph_I2C1,ENABLE);
  I2C1_RCC_GPIO_ClockCmd(I2C1_RCC_APB_Periph_GPIO,ENABLE);
	
  GPIO_InitStruct.GPIO_Mode  = I2C_GPIO_MODE;
  GPIO_InitStruct.GPIO_Pin   = I2C1_SCL_GPIO_Pin;//SCL
  GPIO_InitStruct.GPIO_Speed = I2C1_GPIO_Speed;
  GPIO_Init(I2C1_PORT,&GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = I2C1_SDA_GPIO_Pin;//SDA
  GPIO_Init(I2C1_PORT,&GPIO_InitStruct);  
  
  /* I2C1 Periph Init */
  I2C_InitStruct.I2C_Mode        = I2C1_Mode;
  I2C_InitStruct.I2C_ClockSpeed  = I2C1_ClockSpeed;
  I2C_InitStruct.I2C_OwnAddress1 = I2C1_I2C_OwnAddress1;//whatever
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C1_AcknowledgedAddress;
  I2C_InitStruct.I2C_DutyCycle           = I2C1_DutyCycle; 
  I2C_InitStruct.I2C_Ack                 = I2C1_Ack;
    
  I2C_Init(I2C1,&I2C_InitStruct);
  I2C_Cmd(I2C1,ENABLE);
		
#endif 

  /* I2C2 - Init */
  
#ifdef I2C1_SCL_GPIO_Pin
  
  /* I2C2 - GPIO Init */
  I2C2_RCC_ClockCmd(RCC_APB1Periph_I2C2,ENABLE);
  I2C2_RCC_GPIO_ClockCmd(I2C2_RCC_APB_Periph_GPIO,ENABLE);
  
  GPIO_InitStruct.GPIO_Mode  = I2C_GPIO_MODE;
  GPIO_InitStruct.GPIO_Pin   = I2C2_SCL_GPIO_Pin;//SCL
  GPIO_InitStruct.GPIO_Speed = I2C2_GPIO_Speed;
  GPIO_Init(I2C2_PORT,&GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = I2C2_SDA_GPIO_Pin;//SDA
  GPIO_Init(I2C2_PORT,&GPIO_InitStruct);  
 
  /* I2C2 Periph Init */
  I2C_InitStruct.I2C_Mode        = I2C2_Mode;
  I2C_InitStruct.I2C_ClockSpeed  = I2C2_ClockSpeed;
  I2C_InitStruct.I2C_OwnAddress1 = I2C2_I2C_OwnAddress1;//whatever
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C2_AcknowledgedAddress;
  I2C_InitStruct.I2C_DutyCycle           = I2C2_DutyCycle; 
  I2C_InitStruct.I2C_Ack                 = I2C2_Ack;
    
  I2C_Init(I2C2,&I2C_InitStruct);
  I2C_Cmd(I2C2,ENABLE);
  
#endif
  
}

/* Send the start bit */
void I2C1_WrSr(void)
{
  I2C_GenerateSTART(I2C1,ENABLE);//W_START_BIT
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //EV5
  I2C_Send7bitAddress(I2C1,0x78,I2C_Direction_Transmitter);//W_ADDR
  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}//EV6

}

/* Send the stop bit */
void I2C1_WrStp(void)
{
  I2C_GenerateSTOP(I2C1, ENABLE);//W_STOP_BIT
	
}

/**
*        
*/
void I2C2_WrSr(void)
{
	I2C_GenerateSTART(I2C2,ENABLE);
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

}

//
void I2C2_W_Data(uint8_t slave_addr,uint8_t reg_addr,uint8_t data)
{
	
	I2C_GenerateSTART(I2C2,ENABLE);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));//EV5
	//while(!(uint16_t)(I2C2->SR1) & (uint16_t)(0x0001));//SB
	//while(!((uint16_t)(I2C2->SR2) & (uint16_t)(0x0003)) == 0x0003);//BUSY + MSL
	
	I2C_Send7bitAddress(I2C2,slave_addr,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//EV6+EV8_1
  
	I2C_SendData(I2C2,reg_addr);
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING));//EV8
	
  I2C_SendData(I2C2,data);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2
	
  I2C_GenerateSTOP(I2C2,ENABLE);
	
}

//
uint8_t ST_Sensors_I2C2_ReadRegister( uint8_t slave_addr, uint8_t reg_addr)
{
	uint8_t data;
	
	I2C_GenerateSTART(I2C2,ENABLE);//S
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));//EV5
	
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);//AD+W
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//EV6+EV8_1
	
	I2C_SendData(I2C2,reg_addr);//RA
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING));//EV8
	
	I2C_GenerateSTART(I2C2,ENABLE);//S
  while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));//EV5

	I2C_Send7bitAddress(I2C2,0xD1,I2C_Direction_Receiver);//AD+R
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));//EV6

	I2C_AcknowledgeConfig  (I2C2,DISABLE);
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));//EV7
	
	data = I2C_ReceiveData(I2C2);
	
	return data;
	
}

