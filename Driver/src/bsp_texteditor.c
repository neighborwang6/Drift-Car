#include "stm32f10x.h"


/******************************************************************************
*    Incldue File Setion
******************************************************************************/
#include "stm32f10x.h"

/********************************************************************************
*    Private Functions typedef
********************************************************************************/

/*
void Go_Stright_CD()
{
	  
	  if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_1 && F_Middle_Line_Error <= OFFTRACK_LEVEL_1)
		{
			if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_2 && F_Middle_Line_Error <= OFFTRACK_LEVEL_2)
			{
				if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_3 && F_Middle_Line_Error <= OFFTRACK_LEVEL_3)
				{
					if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_4 && F_Middle_Line_Error <= OFFTRACK_LEVEL_4)
					{
						if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_5 && F_Middle_Line_Error <= OFFTRACK_LEVEL_5)
						{
						  if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_6 && F_Middle_Line_Error <= OFFTRACK_LEVEL_6)
						  {
						    if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_7 && F_Middle_Line_Error <= OFFTRACK_LEVEL_7)
						    {
						      if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_8 && F_Middle_Line_Error <= OFFTRACK_LEVEL_8)
							    {
							      if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_9 && F_Middle_Line_Error <= OFFTRACK_LEVEL_9)
									  {
										  if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_10 && F_Middle_Line_Error <= OFFTRACK_LEVEL_10)
                      {
												if(F_Middle_Line_Error >= -OFFTRACK_LEVEL_11 && F_Middle_Line_Error <= OFFTRACK_LEVEL_11)
												{
													Set_MotorSpeed_L(600);
													Set_MotorSpeed_R(600);
													Motor_L_ForwardEnable();
													Motor_R_ForwardEnable();
												}
												else if(F_Middle_Line_Error <= -OFFTRACK_LEVEL_7)
													{
														Set_MotorSpeed_L(670);
													  Set_MotorSpeed_R(600);
													  Motor_L_ForwardEnable();
													  Motor_R_ForwardEnable();
											  }
												else
													{
													  Set_MotorSpeed_L(600);
													  Set_MotorSpeed_R(670);
													  Motor_L_ForwardEnable();
									          Motor_R_ForwardEnable();
																									
												  }
																				
										  }
											else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_6)
											{
												Set_MotorSpeed_L(700);
											  Set_MotorSpeed_R(600);
											  Motor_L_ForwardEnable();
											  Motor_R_ForwardEnable();
											
											}
											else
											{
												Set_MotorSpeed_L(600);
												Set_MotorSpeed_R(700);
												Motor_L_ForwardEnable();
									      Motor_R_ForwardEnable();
											
											}
									  }else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_7)
										{
											Set_MotorSpeed_L(600);
											Set_MotorSpeed_R(600);
											Motor_L_ForwardEnable();
											Motor_R_ForwardEnable();
										}
										else
										{
											Set_MotorSpeed_L(600);
											Set_MotorSpeed_R(600);
											Motor_L_ForwardEnable();
										  Motor_R_ForwardEnable();
										}
							    }
									else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_8)
									{
										Set_MotorSpeed_L(600);
										Set_MotorSpeed_R(600);
										Motor_L_ForwardEnable();
										Motor_R_ForwardEnable();}
										else
										{
											Set_MotorSpeed_L(OFFTRACK_LEVEL_1);
											Set_MotorSpeed_R(600);
											Motor_L_ForwardEnable();
											Motor_R_ForwardEnable();}
								}
								else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_7)
								{
									Set_MotorSpeed_L(600);
									Set_MotorSpeed_R(600);
									Motor_L_ForwardEnable();
									Motor_R_ForwardEnable();
								}
									else
									{
										Set_MotorSpeed_L(600);
										Set_MotorSpeed_R(600);
										Motor_L_ForwardEnable();
										Motor_R_ForwardEnable();
									}
							}
							else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_6)
							{
								Set_MotorSpeed_L(600);
								Set_MotorSpeed_R(OFFTRACK_LEVEL_5);
								Motor_L_ForwardEnable();
								Motor_R_ForwardEnable();
							}
              else
								{
									Set_MotorSpeed_L(600);
									Set_MotorSpeed_R(600);
									Motor_L_ForwardEnable();
									Motor_R_ForwardEnable();
								}	
						}
						else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_5)
						{
							Set_MotorSpeed_L(600);
							Set_MotorSpeed_R(600);
							Motor_L_ForwardEnable();
							Motor_R_ForwardEnable();
						}
						else
						{
							Set_MotorSpeed_L(OFFTRACK_LEVEL_6);
							Set_MotorSpeed_R(600);
							Motor_L_ForwardEnable();
							Motor_R_ForwardEnable();
						}							
          }
					else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_4)
					{
						Set_MotorSpeed_L(600);
						Set_MotorSpeed_R(OFFTRACK_LEVEL_7);
						Motor_L_ForwardEnable();
						Motor_R_ForwardEnable();
					}
            else
					  {
							Set_MotorSpeed_L(600);
							Set_MotorSpeed_R(600);
							Motor_L_ForwardEnable();
							Motor_R_ForwardEnable();
					  }

				}
				else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_3)
				{}
					else
					{}
			}
			else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_2)
      {}
				else
				{}
		}
		else if(F_Middle_Line_Error < -OFFTRACK_LEVEL_1)
		{
			Stop_Motor_L();//Stop left Motor
      Stop_Motor_R();//Stop right Motor
		}
			else
			{
				Stop_Motor_L();//Stop left Motor
        Stop_Motor_R();//Stop right Motor
			}


}



*/




