#ifndef __TIMERSET__H
#define __TIMERSET__H

#include  "stm32f4xx_hal.h"
#include  "ecatappl.h"

extern TIM_HandleTypeDef  TimHandle;

void TIM7_Init(void);
void TIM7_Start(void);
void TIM7_Stop(void);

#endif

