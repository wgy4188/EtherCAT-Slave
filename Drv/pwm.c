#include "pwm.h"

volatile int16_t M0_Target = 0, M1_Target = 0, M2_Target = 0, M3_Target = 0;
volatile int16_t M0_Buffer = 0, M1_Buffer = 0, M2_Buffer = 0, M3_Buffer = 0;
volatile uint8_t M0_Flag = 0, M1_Flag = 0, M2_Flag = 0, M3_Flag = 0;
volatile uint16_t M0_Cycle = 0, M1_Cycle = 0, M2_Cycle = 0, M3_Cycle = 0; 

void PWM_Config(void)
{
		//PWM0 
		PWM_PORT_0->MODER |= PWM_PORT_MODE_0;
		PWM_PORT_0->OSPEEDR |= PWM_PORT_SPEED_0;
		PWM_PORT_0->ODR &= ~PWM_ODR_0;
	
		TIM1->PSC = 0x59; //预分频到 2 MHZ
		TIM1->CR1 |= TIM_CR1_ARPE; //使能重装载
		TIM1->DIER |= TIM_DIER_UIE;//使能更新中断

		//PWM1
		PWM_PORT_1->MODER |= PWM_PORT_MODE_1;
		PWM_PORT_1->OSPEEDR |= PWM_PORT_SPEED_1;
		PWM_PORT_1->ODR &= ~PWM_ODR_1;

 		TIM2->PSC = 0x2C;
		TIM2->CR1 |= TIM_CR1_ARPE;
		TIM2->DIER |= TIM_DIER_UIE;	

		//PWM2
		PWM_PORT_2->MODER &= ~(0x3<<8);//先复位
		PWM_PORT_2->MODER |= PWM_PORT_MODE_2;//输出
		PWM_PORT_2->OSPEEDR |= PWM_PORT_SPEED_2;//快速
		PWM_PORT_2->ODR &= ~PWM_ODR_2;
		
 		TIM3->PSC = 0x2C;
		TIM3->CR1 |= TIM_CR1_ARPE;
		TIM3->DIER |= TIM_DIER_UIE;

		//PWM3
		PWM_PORT_3->MODER |= PWM_PORT_MODE_3;
		PWM_PORT_3->OSPEEDR |= PWM_PORT_SPEED_3;
		PWM_PORT_3->ODR &= ~PWM_ODR_3;

 		TIM4->PSC = 0x2C;
		TIM4->CR1 |= TIM_CR1_ARPE;
		TIM4->DIER |= TIM_DIER_UIE;

}

/*****************************PWM0控制************************************/
//nCycle 最小为1ms, 计数单个脉冲0.5uS
void PWM0_Start(uint16_t nCycle, int16_t nPulsNum)
{
		uint16_t nARRVal=0;
	
		if((nCycle>0)&&(nPulsNum != 0))
		{
				M0_Cycle=nCycle;
				if(M0_Flag==0)
				{
						M0_Cycle += nCycle;
						M0_Buffer += nPulsNum;//接收到脉冲数存入缓冲区
						if(M0_Buffer>0)
						{
								//DIR0(0);//正向
								nARRVal = (uint16_t)(nCycle*1000/M0_Buffer);//计算中断周期
								M0_Target = (M0_Buffer-1);//传递给目标值
						}
						else
						{
								//DIR0(1);//反向
								nARRVal = (uint16_t)(nCycle*1000/(-M0_Buffer));//计算中断周期
								M0_Target = (M0_Buffer+1);//传递给目标值
						}
						M0_Buffer = 0;//清除缓冲区	
						M0_Cycle = 0;
						if(nARRVal<1)
						{
								PWM0_Stop();
								return;
						}
						//设置并使能定时器
						TIM1->ARR = nARRVal; //设置预装载值
						TIM1->EGR |= TIM_EGR_UG;
						TIM1->CR1 |= TIM_CR1_CEN; //启动定时器
						TIM1->BDTR |= TIM_BDTR_MOE;
					
						NVIC->IP[25] = 0x60; //中断优先级
						NVIC->ISER[0] = (0x1UL<<25); //使能中断
						
						M0_Flag = 1;//脉冲开始输出
			  }
				else
				{
						M0_Cycle += nCycle;
						M0_Buffer += nPulsNum;
				}
		}
		else
		{
				return;
		}
}

void PWM0_Stop(void)
{
		TIM1->BDTR &= ~TIM_BDTR_MOE;
		TIM1->CR1 &= ~TIM_CR1_CEN;
		M0_Target = 0;
		M0_Buffer = 0;
		M0_Flag = 0;
		M0_Cycle = 0;
		NVIC->ICER[0] = (0x1UL<<25); //使能中断
}

/***************************PWM1控制**************************************/
volatile int32_t Sum=0;
volatile uint32_t Count=0;
volatile uint8_t Flag=0;
volatile uint32_t PulsNum=0;
void PWM1_Start(uint16_t nCycle, int16_t nPulsNum)
{
		uint16_t nARRVal=0;
		 
		if((nCycle > 0)&&(nPulsNum != 0))
		{	
				Count=0;
				Flag=1;
			
				M1_Cycle=nCycle;
				if(M1_Flag==0)//脉冲输出已结束，重新开始
				{
						M1_Cycle += nCycle;
						M1_Buffer += nPulsNum;
					
						if(M1_Buffer>0)
						{
								//DIR1(0);//正向
								nARRVal = (uint16_t)(M1_Cycle*1000/M1_Buffer);//计算中断周期
								M1_Target = (M1_Buffer-1);//传递给目标值
						}
						else
						{
								//DIR1(1);//反向
								nARRVal = (uint16_t)(M1_Cycle*1000/(-M1_Buffer));//计算中断周期
								M1_Target = (M1_Buffer+1);//传递给目标值
						}
						Sum += M1_Buffer;
						M1_Buffer=0;//清除缓冲区
						M1_Cycle=0;
						if(nARRVal<1)
						{
								PWM1_Stop(); 
								return;
						}

						//设置并使能定时器
						TIM2->ARR = nARRVal; //设置预装载值
						TIM2->EGR |= TIM_EGR_UG;
						TIM2->CR1 |= TIM_CR1_CEN; //启动定时器
					
						NVIC->IP[28] = 0x60;
						NVIC->ISER[0] = (0x1UL<<28);	
						
						M1_Flag = 1;//脉冲开始输出
				}
				else
				{
						M1_Cycle += nCycle;
						M1_Buffer += nPulsNum;
				}
		}
		else
		{
				Count++;
				if((Count>500)&&(Flag==1))
				{
						SerPrintf("Sum=%ld\n",Sum);
						SerPrintf("PulsNum=%ld\n",PulsNum);
						PulsNum = 0;
						Sum = 0;
						Flag = 0;
				}
		}
}

void PWM1_Stop(void)
{
		TIM2->CR1 &= ~TIM_CR1_CEN;
		M1_Target = 0;
		M1_Buffer = 0;
		M1_Flag = 0;
		M1_Cycle = 0;
		NVIC->ICER[0] = (0x1UL<<28);	
}

/********************************PWM2控制*********************************/
void PWM2_Start(uint16_t nCycle, int16_t nPulsNum)
{
		uint16_t nARRVal=0;
		 
		if((nCycle > 0)&&(nPulsNum != 0))
		{
				M2_Cycle=nCycle;
				if(M2_Flag==0)//脉冲输出已结束，重新开始
				{
						M2_Cycle += nCycle;
						M2_Buffer += nPulsNum;
						if(M2_Buffer>0)
						{
								//DIR2(0);//正向
								nARRVal = (uint16_t)(M2_Cycle*1000/M2_Buffer);//计算中断周期
								M2_Target = (M2_Buffer-1);//传递给目标值
						}
						else
						{
								//DIR2(1);//反向
								nARRVal = (uint16_t)(M2_Cycle*1000/(-M2_Buffer));//计算中断周期
								M2_Target = (M2_Buffer+1);//传递给目标值
						}	
						M2_Cycle = 0;
						M2_Buffer = 0;
						if(nARRVal<1)
						{
								PWM2_Stop(); 
								return;
						}
						//设置并使能定时器
						TIM3->ARR = nARRVal; //设置预装载值
						TIM3->EGR |= TIM_EGR_UG;
						TIM3->CR1 |= TIM_CR1_CEN; //启动定时器

						NVIC->IP[29] = 0x60;
						NVIC->ISER[0] = (0x1UL<<29);	
						
						M2_Flag = 1;
				}
				else
				{
						M2_Cycle += nCycle;
						M2_Buffer += nPulsNum;	
				}
		}
		else
		{
				
		}
}

void PWM2_Stop(void)
{
		TIM3->CR1 &= ~TIM_CR1_CEN;
		M2_Target = 0;
		M2_Buffer = 0;
		M2_Flag = 0;
		M2_Cycle = 0;
		NVIC->ICER[0] = (0x1UL<<29);	
}

/**********************************PWM3控制*********************************/
void PWM3_Start(uint16_t nCycle, int16_t nPulsNum)
{
		uint16_t nARRVal=0;
		 
		if((nCycle > 0)&&(nPulsNum != 0))
		{
				M3_Cycle = nCycle;
				if(M3_Flag==0)//脉冲输出已结束，重新开始
				{
						M3_Cycle += nCycle;
						M3_Buffer += nPulsNum;
						if(M3_Buffer>0)
						{
								//DIR3(0);//正向
								nARRVal = (uint16_t)(M3_Cycle*1000/M3_Buffer);//计算中断周期
								M3_Target = (M3_Buffer-1);//传递给目标值
						}
						else
						{
								//DIR3(1);//反向
								nARRVal = (uint16_t)(M3_Cycle*1000/(-M3_Buffer));//计算中断周期
								M3_Target = (M3_Buffer+1);//传递给目标值
						}
						M3_Buffer=0;
						M3_Cycle=0;
						if(nARRVal<1)
						{
								PWM3_Stop(); 			
								return;
						}
						//设置并使能定时器
						TIM4->ARR = nARRVal; //设置预装载值
						TIM4->EGR |= TIM_EGR_UG;
						TIM4->CR1 |= TIM_CR1_CEN; //启动定时器

						NVIC->IP[30] = 0x60;
						NVIC->ISER[0] = (0x1UL<<30);	
						
						M3_Flag = 1;
				}
				else
				{
						M3_Cycle += nCycle;
						M3_Buffer += nPulsNum;
				}
		}
		else
		{
				return;
		}
}

void PWM3_Stop(void)
{
		TIM4->CR1 &= ~TIM_CR1_CEN;
		M3_Target = 0;
		M3_Buffer = 0;
		M3_Flag = 0;
		M3_Cycle = 0;
		NVIC->ICER[0] = (0x1UL<<30);	
}


