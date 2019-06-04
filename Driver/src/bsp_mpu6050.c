#include "bsp_mpu6050.h"

volatile short MPU6050_DATA_ARRAY[13];

short MPU6050_ID;
short MPU6050_Y_Acc_H = 0;
short MPU6050_Y_Acc_L = 0;
short MPU6050_Z_Acc_H = 0;
short MPU6050_Z_Acc_L = 0;
short MPU6050_X_Gyro_H = 0;
short MPU6050_X_Gyro_L = 0;

//MPU6050_Init
void MPU_6050_Init(void)
{
	int i,j;
	
	//��ʼ��֮ǰ����ʱ
	for(i = 1000;i>1000;i--)
	{
		for(j = 1000;j>1000;j--)
		{}
	}
	
	//�������
	I2C2_W_Data(0xd0,MPU6050_RA_PWR_MGMT_1,0x00);
	
	//�����ǲ�����
	I2C2_W_Data(0xd0,MPU6050_RA_SMPRT_DIV,0x00);
	I2C2_W_Data(0xd0,MPU6050_RA_CONFIG,0x06);
	
	//���ü��ٶȴ�����������16Gģʽ
	I2C2_W_Data(0xd0,MPU6050_RA_ACCEL_CONFIG,0x18);
  
	//���������ǲ������Լ췶Χ+-2000digree
	I2C2_W_Data(0xd0,MPU6050_RA_GYRO_CONFIG,0x18);
	
	//�����ж�
  //I2C2_W_Data(0xd0,MPU6050_RA_INT_ENABLE,0x01);
	
}

/**
  * @brief 
  * @param
  * @reval
  */


void MPU6050_ReadData(void)
{
	MPU6050_ID = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_WHO_AM_I);

	//ACC_Y
	MPU6050_Y_Acc_H = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_ACCEL_YOUT_H);
	MPU6050_Y_Acc_L = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_ACCEL_YOUT_L);
	//ACC_Z
	MPU6050_Z_Acc_H = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_ACCEL_ZOUT_H);
  MPU6050_Z_Acc_L = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_ACCEL_ZOUT_L);
	
	//GYRO_X
	MPU6050_X_Gyro_H = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_GYRO_XOUT_H);
	MPU6050_X_Gyro_L = ST_Sensors_I2C2_ReadRegister(0xD0,MPU6050_RA_GYRO_XOUT_L);


}


/**
  * @brief 
  * @param
  * @reval
  */

void MPU6050_ReadAcc(short *accData)
{
	u8 buf[6];

    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
}








