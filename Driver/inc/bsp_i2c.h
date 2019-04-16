/********************************************************************************
*    Muti-include-prevent Section  
********************************************************************************/
#ifndef _BSP_I2C_H_
#define _BSP_I2C_H_
/********************************************************************************
*    Include File Section
********************************************************************************/
#include "stm32f10x.h"

/********************************************************************************
*    Macro Define Section
********************************************************************************/
#define I2C_GPIO_MODE    GPIO_Mode_AF_OD

/* I2C1 Configuration */
#define I2C1_RCC_ClockCmd         RCC_APB1PeriphClockCmd
#define I2C1_RCC_GPIO_ClockCmd    RCC_APB2PeriphClockCmd

#define I2C1_RCC_APB_Periph_GPIO  RCC_APB2Periph_GPIOB

#define I2C1_PORT                 GPIOB
#define I2C1_GPIO_Speed           GPIO_Speed_50MHz
#define I2C1_SCL_GPIO_Pin         GPIO_Pin_6
#define I2C1_SDA_GPIO_Pin         GPIO_Pin_7 

#define I2C1_Mode                 I2C_Mode_I2C
#define I2C1_ClockSpeed           100000
#define I2C1_I2C_OwnAddress1      0xaa
#define I2C1_AcknowledgedAddress  I2C_AcknowledgedAddress_7bit
#define I2C1_DutyCycle            I2C_DutyCycle_2
#define I2C1_Ack                  I2C_Ack_Enable 

/* I2C2 Configuration */
#define I2C2_RCC_ClockCmd         RCC_APB1PeriphClockCmd
#define I2C2_RCC_GPIO_ClockCmd    RCC_APB2PeriphClockCmd

#define I2C2_RCC_APB_Periph_GPIO  RCC_APB2Periph_GPIOB

#define I2C2_PORT                 GPIOB
#define I2C2_GPIO_Speed           GPIO_Speed_50MHz
#define I2C2_SCL_GPIO_Pin         GPIO_Pin_10
#define I2C2_SDA_GPIO_Pin         GPIO_Pin_11

#define I2C2_Mode                 I2C_Mode_I2C
#define I2C2_ClockSpeed           100000
#define I2C2_I2C_OwnAddress1      0xaa
#define I2C2_AcknowledgedAddress  I2C_AcknowledgedAddress_7bit
#define I2C2_DutyCycle            I2C_DutyCycle_2
#define I2C2_Ack                  I2C_Ack_Enable 

/********************************************************************************
*    Prototype Declare Section
********************************************************************************/
//I2C1
void I2C_Conf(void);

//I2C1
void I2C1_WrSr(void);/* Master send Start Bit */
void I2C1_WrStp(void);/* Master send Stop Bit */
void I2C1_WrAddr(uint8_t page_addr,uint8_t column_addr);/* Write the Slave's addr include w/r bit */

//I2C2
void I2C2_WrSr(void);
void I2C2_WrStp(void);
void I2C2_WrAddr(uint8_t addr1,uint8_t addr2);

//
void I2C2_W_Data(uint8_t AD_W,uint8_t RA,uint8_t data);
uint8_t ST_Sensors_I2C2_ReadRegister( uint8_t slave_addr, uint8_t reg_addr);

#endif
