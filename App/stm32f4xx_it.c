/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/stm32f4xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	  OS_CPU_SR  cpu_sr;
	
		HAL_IncTick();
	
    OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    OSIntNesting++;
    OS_EXIT_CRITICAL();
	
    OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */
    OSIntExit(); 	
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

uint32_t count=0;
uint8_t stated=0;

void TIM7_IRQHandler(void)
{
  if(__HAL_TIM_GET_FLAG(&TimHandle, TIM_FLAG_UPDATE) != RESET)
  {
    if(__HAL_TIM_GET_IT_SOURCE(&TimHandle, TIM_IT_UPDATE) !=RESET)
    {		
				if(count++ > n_Count.Word)
				{
						if(stated)
						{
								CpuRunled(0);
								stated = 0;
						}
						else
						{
								CpuRunled(1);
								stated = 1;
						}
						count = 0;
				}			
				
				 ECAT_CheckTimer();	
				 __HAL_TIM_CLEAR_IT(&TimHandle, TIM_IT_UPDATE);
		}
  }
}

void USART2_IRQHandler(void)
{		
		uint8_t RecvByte = 0;
		if( (USARTx->SR & USART_SR_RXNE)||(USARTx->SR & USART_SR_ORE) )//接收数据寄存器不为空中断，硬件自动清零
		{
			 RecvByte = USARTx->DR;//取接受的数据
			 //USARTx_SendData(RecvByte);
			 FifoWriteOneByte(RecvByte);//存进缓存区
		}
}


//PWM0 定时器更新中断
volatile uint8_t Puls0_Level=0;
void TIM1_UP_TIM10_IRQHandler(void)
{
		uint16_t M0_TmpARR = 0;
	
		if(TIM1->SR & TIM_SR_UIF)
		{
				if(Puls0_Level)//周期结束
				{
						PWM_PORT_0->ODR &= ~PWM_ODR_0;
						Puls0_Level=0;
					
						//更新数据
						if((M0_Flag==1)&&(M0_Buffer != 0)&&(M0_Cycle>0))//缓冲区有新的数据
						{
								M0_Target += M0_Buffer;//更新目标值	
								if(M0_Target>0)
								{
										//DIR0(0);//正向
										M0_TmpARR = (uint16_t)(M0_Cycle*1000/M0_Target);
								}
								else
								{
										//DIR0(1);//反向
										M0_TmpARR = (uint16_t)(M0_Cycle*1000/(-M0_Target));
								}
								M0_Buffer = 0;//清楚缓存器
								M0_Cycle = 0;
								if(M0_TmpARR<1)
								{
										PWM0_Stop();
										return;
								}
								else
								{
										TIM1->ARR = M0_TmpARR; 
										TIM1->EGR |= TIM_EGR_UG;
								}	
						}
						//监控脉冲输出
						if(M0_Target>0)
						{
								M0_Target--;
						}
						else if(M0_Target<0)
						{
								M0_Target++;
						}	
						else
						{
								TIM1->BDTR &= ~TIM_BDTR_MOE;
								TIM1->CR1 &= ~TIM_CR1_CEN;
								M0_Flag = 0;
						}
				}
				else//周期一半
				{
						PWM_PORT_0->ODR |= PWM_ODR_0;
						Puls0_Level = 1;
				}
				
				TIM1->SR &= ~TIM_SR_UIF;
		}
}

//PWM1 定时器更新中断
volatile uint8_t Puls1_Level=0;
void TIM2_IRQHandler(void)
{
	  uint16_t M1_TmpARR = 0;

		if(TIM2->SR & TIM_SR_UIF)
		{
				if(Puls1_Level)
				{
						PWM_PORT_1->ODR &= ~PWM_ODR_1;
						Puls1_Level=0;
						PulsNum++;

						//更新数据
						if((M1_Flag==1)&&(M1_Buffer != 0)&&(M1_Cycle>0))//运行过程中，缓冲区有新的数据
						{
								Sum += M1_Buffer;
								M1_Target += M1_Buffer;//更新目标值
								if(M1_Target>0)
								{
										//DIR1(0);//正向
										M1_TmpARR = (uint16_t)(M1_Cycle*1000/M1_Target);
								}
								else
								{
										//DIR1(1);//反向
										M1_TmpARR = (uint16_t)(M1_Cycle*1000/(-M1_Target));
								}
								M1_Buffer = 0;//清楚缓存器
								M1_Cycle=0;
								if(M1_TmpARR<1)
								{
										PWM1_Stop();
										return;
								}
								else
								{
										TIM2->ARR = M1_TmpARR;
										TIM2->EGR |= TIM_EGR_UG;
								}
						}
						
						//监控脉冲输出
						if(M1_Target>0)
						{
								M1_Target--;
						}
						else if(M1_Target<0)
						{
								M1_Target++;
						}	
						else
						{
								TIM2->CR1 &= ~TIM_CR1_CEN;
								M1_Flag = 0;
						}
				}
				else
				{
						PWM_PORT_1->ODR |= PWM_ODR_1;
						Puls1_Level = 1;
				}
				
				TIM2->SR &= ~TIM_SR_UIF;
		}
}

//PWM2 定时器更新中断
volatile uint8_t Puls2_Level = 0;
void TIM3_IRQHandler (void)
{
    uint16_t M2_TmpARR = 0;
	
		if(TIM3->SR & TIM_SR_UIF)
		{
				if(Puls2_Level)
				{
						PWM_PORT_2->ODR &= ~PWM_ODR_2;
						Puls2_Level=0;
					
						//更新数据
						if((M2_Flag==1)&&(M2_Buffer != 0)&&(M2_Cycle>0))//缓冲区有新的数据
						{
								M2_Target += M2_Buffer;//更新目标值	
								if(M2_Target>0)
								{
										//DIR2(0);//正向
										M2_TmpARR = (uint16_t)(M2_Cycle*1000/M2_Target);
								}
								else
								{
										//DIR2(1);//反向
										M2_TmpARR = (uint16_t)(M2_Cycle*1000/(-M2_Target));
								}
								M2_Buffer = 0;//清楚缓存器
								M2_Cycle = 0;
								if(M2_TmpARR<1)
								{
										PWM2_Stop();
										return;
								}
								else
								{
										TIM3->ARR = M2_TmpARR;
										TIM3->EGR |= TIM_EGR_UG;
								}
						}
						
						//监控脉冲输出
						if(M2_Target>0)
						{
								M2_Target--;
						}
						else if(M2_Target<0)
						{
								M2_Target++;
						}	
						else
						{
								TIM3->CR1 &= ~TIM_CR1_CEN;
								M2_Flag = 0;
						}					
				}
				else
				{
						PWM_PORT_2->ODR |= PWM_ODR_2;
						Puls2_Level = 1;
				}
				
				TIM3->SR &= ~TIM_SR_UIF;
		}
}

//PWM3 定时器更新中断
volatile uint8_t Puls3_Level = 0;
void TIM4_IRQHandler(void)
{
	  uint16_t M3_TmpARR = 0;
	
		if(TIM4->SR & TIM_SR_UIF)
		{
				if(Puls3_Level)
				{
						PWM_PORT_3->ODR &= ~PWM_ODR_3;
						Puls3_Level=0;
					
						//更新数据
						if((M3_Flag==1)&&(M3_Buffer != 0)&&(M3_Cycle>0))//缓冲区有新的数据
						{
								M3_Target += M3_Buffer;//更新目标值
								if(M3_Target>0)
								{
										//DIR3(0);//正向
										M3_TmpARR = (uint16_t)(M3_Cycle*1000/M3_Target);
								}
								else
								{
										//DIR3(1);//反向
										M3_TmpARR = (uint16_t)(M3_Cycle*1000/(-M3_Target));
								}
								M3_Buffer = 0;//清楚缓存器
								M3_Cycle = 0;
								if(M3_TmpARR<1)
								{
										PWM3_Stop();
										return;
								}
								else
								{
										TIM4->ARR = M3_TmpARR;
										TIM4->EGR |= TIM_EGR_UG;
								}
						}

						//监控脉冲输出
						if(M3_Target>0)
						{
								M3_Target--;
						}
						else if(M3_Target<0)
						{
								M3_Target++;
						}	
						else
						{
								TIM4->CR1 &= ~TIM_CR1_CEN;
								M3_Flag = 0;
						}
				}
				else
				{
						PWM_PORT_3->ODR |= PWM_ODR_3;
						Puls3_Level = 1;
				}
				
				TIM4->SR &= ~TIM_SR_UIF;
		}
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
