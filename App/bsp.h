#ifndef __BSP_H__
#define __BSP_H__

#include "stm32f4xx_hal.h"
#include "applInterface.h"
#include "RT2000.h"
#include "uart.h"
#include "pwm.h"
#include "dio.h"
#include "ad_da.h"

#include "os_cfg.h"
#include "os_cpu.h"
#include "cpu.h"
#include "ucos_ii.h"

void BSP_Init(void);

#endif

