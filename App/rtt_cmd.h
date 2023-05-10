#ifndef RTT_CMD_H
#define RTT_CMD_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "SEGGER_RTT.h"

#define RTTV_DEBUG_EN     1

#if RTTV_DEBUG_EN
#define rttv_debug(format,...)   SEGGER_RTT_printf(0, format, ##__VA_ARGS__)
#endif

void RTT_CMD_Process(void);

#endif
