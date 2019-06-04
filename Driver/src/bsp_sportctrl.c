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

//减去传感器偏移量后的MPU6050的Y轴，X轴上的加速度
double acc_y = 0.0;
double acc_z = 0.0;
//double acc_Angle = 0.0;

double gyro_X = 0.0;
double gyro_angle = 0.0;

//由Y-Z轴计算出来的车模倾角
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
	//1 ms中断的任务分配
	if(Tim2_Counter == 1)
	{
		MPU6050_ReadData();
	}
	else if(Tim2_Counter ==2)
	{
		//获取姿态角
		CarAttitudeAngleGet();
		
		//直立控制算法计算
	  CarAngleAdjust();
		
		//电机输出
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

	//计数器自增
	Tim2_Counter++;
	//Tim2_temp++;
	
  //清除中断标志位
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
}


static void CarAttitudeAngleGet(void)
{
  //int lnDeltaValue;
	int TEMP_32;

	//读取加速度和陀螺仪原始数据
  Acc_Y = ((MPU6050_Y_Acc_H & 0x00FF) << 8) + (MPU6050_Y_Acc_L & 0x00FF);
	Acc_Z = ((MPU6050_Z_Acc_H & 0x00FF) << 8) + (MPU6050_Z_Acc_L & 0x00FF);
  Gyro_X =((MPU6050_X_Gyro_H & 0x00FF) << 8) + (MPU6050_X_Gyro_L & 0x00FF);
  
	
	//获取Y轴实际的加速度
  TEMP_32 = Acc_Y - MPU6050_Y_Acc_Offset;
	acc_y = (double)((double)(TEMP_32)/2048);
	
	//获取Z轴实际的加速度
	TEMP_32 = Acc_Z - MPU6050_Z_Acc_Offset;
	acc_z = (double)((double)(TEMP_32)/2048);
	
	//利用Z轴和Y轴加速度求出的车模倾角
	Phi_Acc = ((atan(acc_y/acc_z))*180)/PI;
	
	//获取角速度
  g_nCarGyroVal = Gyro_X - MPU6050_X_Gyro_Offset;
	gyro_X = (double)((double)g_nCarGyroVal/16.4);
	
	//Kalman 滤波获取最优角度
  //Optimal_Angle = KalmanFilter(gyro_X,Phi_Acc);
	
	//互补滤波
  Optimal_Angle = CompFilter(gyro_X,Phi_Acc);
	
}

//直立控制子程序
static void CarAngleAdjust(void)
{
  int nLeft, nRight;
  double nP, nD;
	
  nP = Optimal_Angle * PID_P;
  nD = gyro_X * PID_D;
	
  nSpeed = nP + nD;

	//限幅
  if(nSpeed > MOTOR_SPEED_SET_MAX)nSpeed = MOTOR_SPEED_SET_MAX;
  else if(nSpeed < MOTOR_SPEED_SET_MIN)nSpeed = MOTOR_SPEED_SET_MIN;
	
	nLeft = (int)nSpeed;
	nRight = (int)nSpeed;
	
  g_nLeftMotorOut = nLeft;
  g_nRightMotorOut = nRight;

}

/*
 * 显示屏幕上的信息
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
