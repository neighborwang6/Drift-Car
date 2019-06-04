/************************************************
*    File Name    :  bsp_ssd1306.c
*    Copyright    :  no
*    Module Name  :  basic function of the operating of ssd1306
*
*    CPU          :  Cortex-M3
*    RTOS         :  NONE
*    
*    Create Date  :  2018/11/11
*************************************************/

/************************************************
*    Include File Section
*************************************************/
#include "bsp_ssd1306.h"
/************************************************
*    Function Define Section
*************************************************/
/************************************************
*    Static Function define 
*************************************************/

/************************************************
*    Exported Function define 
*************************************************/
/* The Master HarewareInit Init and the ssd1306 as slave */
void SSD1306_HardWareInit(void)
{
  I2C_Conf();
}

/* WrSatrtBit */
void SSD1306_WrSr(void)
{
  I2C_GenerateSTART(I2C1,ENABLE);//W_START_BIT
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)){}//EV5
  I2C_Send7bitAddress(I2C1,0x78,I2C_Direction_Transmitter);//W_ADDR
  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//EV6
}

/* WrStopBit */
void SSD1306_WrStp(void)
{
  I2C_GenerateSTOP(I2C1, ENABLE);//W_STOP_BIT
}

/* Set the addr */
void SSD1306_WrAddr(uint8_t page_addr,uint8_t column_addr)
{
  SSD1306_WrSr();
	
  SSD1306_WrCmd(0xb0|page_addr);
  SSD1306_WrCmd(0x00|(column_addr&0x0f)); // Set Lower Column Start Address for Page Addressing Mode
  SSD1306_WrCmd(0x10|((column_addr&0xf0)>>4)); //Set Higher Column Start Address for Page Addressing Mode
	
  I2C_SendData(I2C1,0x40);//Send the control byte(0x80)
  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2 

}

/* Write the Command to SSD1306 in i2c protocol */
void SSD1306_WrCmd(uint8_t byte)
{
  I2C_SendData(I2C1,0x80);//Send the control byte(0x80)
  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2 		
  I2C_SendData(I2C1,byte);
  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2

}

/* Write the Data to SSD1306 in i2c protocol */
void SSD1306_WrByte(uint8_t byte)
{
  I2C_SendData(I2C1,byte);//Send the data
  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2 
	
	
	
	
	
	
}







