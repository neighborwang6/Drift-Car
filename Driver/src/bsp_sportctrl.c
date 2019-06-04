#include "bsp_sportctrl.h"
#include "stm32f10x.h"
#include "bsp_includes.h"
#include "Kalman.h"

//EXTERN VALUE
extern volatile int8_t MPU6050_DATA_ARRAY[];
extern short MPU6050_ID;
extern short MPU6050_Y_Acc_H;
extern short MPU6050_Y_Acc_L;
extern short MPU6050_Z_Acc_H;
extern short MPU6050_Z_Acc_L;
extern short MPU6050_X_Gyro_H;
extern short MPU6050_X_Gyro_L;

//MPU6050
double MPU6050_Y_Acc_Offset = -295.0;
double MPU6050_Z_Acc_Offset = 480.0;
double MPU6050_X_Gyro_Offset = -21.18;

int16_t Acc_Y = 0;
int16_t Acc_Z = 0;
int16_t Gyro_X = 0;

int g_nCarAcceVal = 0;
int g_nCarGyroVal = 0;
int g_nCarAngle = 0;

float CAR_ACCE_RATIO = 0.01;

int CarSigma;

//Math
double PI = 3.14159;
double Angle = 0.0;

//��ȥ������ƫ�������MPU6050��Y�ᣬX���ϵļ��ٶ�
double acc_y = 0.0;
double acc_z = 0.0;
//double acc_Angle = 0.0;

double gyro_X = 0.0;
double gyro_angle = 0.0;

//��Y-Z���������ĳ�ģ���
double Phi_Acc;

//Kalman
double Optimal_Angle = 0;
double PID_P = 230.0;
double PID_D = 9.0;

//MOTOR CONTROL
double nSpeed;

int nLeftVol = 0;
int nRightVol = 0;

int g_nLeftMotorOut = 0;
int g_nRightMotorOut = 0;

const int MOTOR_OUT_DEAD_VAL = 100;
const int MOTOR_OUT_MAX = 0;

const int MOTOR_SPEED_SET_MAX = 1950;
const int MOTOR_SPEED_SET_MIN = -1950;

//STATIC FUNCTON
static void CarAttitudeAngleGet(void);
static void CarAngleAdjust(void);


/* Tim2-IRQ-Handler-------1ms Interrupt-------------------------------------------------- */

uint16_t Tim2_temp = 0;
uint16_t Tim2_Counter = 1;

void TIM2_IRQHandler(void)
{
	//1 ms�жϵ��������
	if(Tim2_Counter == 1)
	{
		MPU6050_ReadData();
	}
	else if(Tim2_Counter ==2)
	{
		//��ȡ��̬��
		CarAttitudeAngleGet();
		
		//ֱ�������㷨����
	  CarAngleAdjust();
		
		//������
		MotorSpeedOut(g_nLeftMotorOut,g_nRightMotorOut,MOTOR_OUT_DEAD_VAL);

	}
	else if(Tim2_Counter ==3)
	{
		LED_G_TOGGLE;
		
	}
	else if(Tim2_Counter ==4)
	{}
	else if(Tim2_Counter ==5)
	{
		Tim2_Counter = 0;
	}

	//����������
	Tim2_Counter++;
	//Tim2_temp++;
	
  //����жϱ�־λ
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
}


static void CarAttitudeAngleGet(void)
{
  //int lnDeltaValue;
	int TEMP_32;

	//��ȡ���ٶȺ�������ԭʼ����
  Acc_Y = ((MPU6050_Y_Acc_H & 0x00FF) << 8) + (MPU6050_Y_Acc_L & 0x00FF);
	Acc_Z = ((MPU6050_Z_Acc_H & 0x00FF) << 8) + (MPU6050_Z_Acc_L & 0x00FF);
  Gyro_X =((MPU6050_X_Gyro_H & 0x00FF) << 8) + (MPU6050_X_Gyro_L & 0x00FF);
  
	
	//��ȡY��ʵ�ʵļ��ٶ�
  TEMP_32 = Acc_Y - MPU6050_Y_Acc_Offset;
	acc_y = (double)((double)(TEMP_32)/2048);
	
	//��ȡZ��ʵ�ʵļ��ٶ�
	TEMP_32 = Acc_Z - MPU6050_Z_Acc_Offset;
	acc_z = (double)((double)(TEMP_32)/2048);
	
	//����Z���Y����ٶ�����ĳ�ģ���
	Phi_Acc = ((atan(acc_y/acc_z))*180)/PI;
	
	//��ȡ���ٶ�
  g_nCarGyroVal = Gyro_X - MPU6050_X_Gyro_Offset;
	gyro_X = (double)((double)g_nCarGyroVal/16.4);
	
	//Kalman �˲���ȡ���ŽǶ�
  //Optimal_Angle = KalmanFilter(gyro_X,Phi_Acc);
	
	//�����˲�
  Optimal_Angle = CompFilter(gyro_X,Phi_Acc);
	
}

//ֱ�������ӳ���
static void CarAngleAdjust(void)
{
  int nLeft, nRight;
  double nP, nD;
	
  nP = Optimal_Angle * PID_P;
  nD = gyro_X * PID_D;
	
  nSpeed = nP + nD;

	//�޷�
  if(nSpeed > MOTOR_SPEED_SET_MAX)nSpeed = MOTOR_SPEED_SET_MAX;
  else if(nSpeed < MOTOR_SPEED_SET_MIN)nSpeed = MOTOR_SPEED_SET_MIN;
	
	nLeft = (int)nSpeed;
	nRight = (int)nSpeed;
	
  g_nLeftMotorOut = nLeft;
  g_nRightMotorOut = nRight;

}

/*
 * ��ʾ��Ļ�ϵ���Ϣ
 *
 *
 */
void show(void)
{
	if(Tim2_temp == 50)
	{
		Tim2_temp = 0;

	  OLED_W_Addr(0,24); OLED_W_DEC_SIX(MPU6050_ID);
		
	  if(g_nCarAcceVal >= 0)
		{
			OLED_W_Addr(1,24);
	    OLED_W_ASCII('+');
	    OLED_W_DEC_SIX(g_nCarAcceVal);
	  }
		else
    {
			OLED_W_Addr(1,24); 
	    OLED_W_ASCII('-');
	    OLED_W_DEC_SIX( -g_nCarAcceVal);
	  }
		if(Acc_Z >= 0)
    {
			OLED_W_Addr(2,24);
      OLED_W_ASCII('+');
	    OLED_W_DEC_SIX(0);
	   }
		else
    {
			OLED_W_Addr(2,24);
      OLED_W_ASCII('-');
	    OLED_W_DEC_SIX(0);
	   }
    //GYRO
	  if(g_nCarGyroVal >= 0)
          {
            OLED_W_Addr(0,86);
	    OLED_W_ASCII('+');
	    OLED_W_DEC_SIX(g_nCarGyroVal);
	   }
					else
          {
            OLED_W_Addr(0,86);
	    OLED_W_ASCII('-');
	    OLED_W_DEC_SIX( -g_nCarGyroVal);
	   }
	   //ANGLE
	   if(CarSigma >= 0)
		{
			OLED_W_Addr(1,86);
	    OLED_W_ASCII('+');
	    OLED_W_DEC_SIX(CarSigma);
	  }
		else
		{
			OLED_W_Addr(1,86);
	    OLED_W_ASCII('-');
	    OLED_W_DEC_SIX( -CarSigma);
	  }
		
	}

}
