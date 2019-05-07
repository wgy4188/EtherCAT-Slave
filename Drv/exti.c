#include  <stm32f4xx_hal.h>
#include "ecatappl.h"
#include "lan9252.h"
#include "exti.h"

void Init_ESC(void)	
{
    GPIO_InitTypeDef GPIO_InitStruct;
	
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	
	  GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT|GPIO_MODE_IT_FALLING; 
  	GPIO_InitStruct.Pull = GPIO_NOPULL;    
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,7, 1);
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}


void Init_SYNC0(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

		__HAL_RCC_GPIOB_CLK_ENABLE();
	
		GPIO_InitStruct.Pin = GPIO_PIN_1;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT|GPIO_MODE_IT_FALLING;
		GPIO_InitStruct.Pull = GPIO_NOPULL; 
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
    HAL_NVIC_SetPriority(EXTI1_IRQn,7, 1);
    HAL_NVIC_DisableIRQ(EXTI1_IRQn);

}


void Init_SYNC1(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

		__HAL_RCC_GPIOB_CLK_ENABLE();
	
		GPIO_InitStruct.Pin = GPIO_PIN_0;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT|GPIO_MODE_IT_FALLING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;      
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
    HAL_NVIC_SetPriority(EXTI0_IRQn,3, 1);
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}



void EXTI9_5_IRQHandler(void)
{

  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET)
  {
	  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
		PDI_Isr();
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		
#if defined (INTERRUPTS_SUPPORTED) && defined(DC_SUPPORTED)
		if(IS_SYNC0_INT_ACTIVE)
    {
        Sync0_Isr();
        /* reset the interrupt flag */
        ACK_SYNC0_INT;
    }
#endif
		
#if defined (INTERRUPTS_SUPPORTED) && defined(DC_SUPPORTED)
		if(IS_SYNC1_INT_ACTIVE)
    {
        Sync1_Isr();
        /* reset the interrupt flag */
        ACK_SYNC1_INT;
    }
#endif
  }
} 

void EXTI1_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET)
  {
	  HAL_NVIC_DisableIRQ(EXTI1_IRQn);
		Sync0_Isr();
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
		
#ifdef INTERRUPTS_SUPPORTED
    if(IS_ESC_INT_ACTIVE)
    {
        DISABLE_ESC_INT();
        PDI_Isr();
        /* reset the interrupt flag */
        ACK_ESC_INT;
    }
#endif
		
#if defined(INTERRUPTS_SUPPORTED) && defined(DC_SUPPORTED)
if(IS_SYNC1_INT_ACTIVE)
    {
        Sync1_Isr();
       /* reset the interrupt flag */
       ACK_SYNC1_INT;
    }
#endif	
  }	
}

void EXTI0_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)
  {
	  HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		Sync1_Isr();
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		
#ifdef INTERRUPTS_SUPPORTED
    if(IS_ESC_INT_ACTIVE)
    {
        DISABLE_ESC_INT();
        PDI_Isr();
        /* reset the interrupt flag */
        ACK_ESC_INT;
    }
#endif
		
#if defined(INTERRUPTS_SUPPORTED) && defined(DC_SUPPORTED)
if(IS_SYNC0_INT_ACTIVE)
    {
        Sync0_Isr();
       /* reset the interrupt flag */
       ACK_SYNC0_INT;
    }
#endif	
  }	
}

void Disable_all_int(void )
{
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	
#ifdef DC_SUPPORTED
	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	
#endif	
	
	HAL_NVIC_DisableIRQ(TIM7_IRQn);

}


void Enable_all_int(void)
{
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
#ifdef DC_SUPPORTED
	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
#endif	
	
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
}



