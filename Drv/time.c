
#include "time.h"
#include "stm32f4xx_hal_tim.h"

TIM_HandleTypeDef  TimHandle;

void TIM7_Init(void)
{
  uint32_t uwPrescalerValue = 0;

  TimHandle.Instance = TIM7;

  TimHandle.Init.Period            = 1000;
  TimHandle.Init.Prescaler         = 0x59;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP | TIM_CR1_ARPE; //递增计数 ，自动重载
	TimHandle.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&TimHandle);                                      
	
  HAL_NVIC_SetPriority(TIM7_IRQn, 6, 1);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

  HAL_TIM_Base_Start_IT(&TimHandle);                                     //开始计时
}

void TIM7_Start(void)
{
	  HAL_TIM_Base_Start_IT(&TimHandle);
}

void TIM7_Stop(void)
{
	  HAL_TIM_Base_Stop_IT(&TimHandle);
}

