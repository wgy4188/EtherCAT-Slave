#ifndef _UART_H_
#define _UART_H_

#include <stdarg.h> 
#include <stdio.h>
#include "stm32f446xx.h"
#include "qspi.h"
#include "pwm.h"
#include "ad_da.h"
#include "config_file.h"

extern volatile UINT16_VAL n_Count;

int32_t FifoWriteOneByte(uint8_t InputChar);
int32_t InquireUartRecvBuffer(uint8_t *pBuf, int8_t MaxBuffCount);
void USARTx_Init(void);
void USARTx_SendData(uint8_t byte);
void SerPrintf(const  char *format, ...);
void Dispose(void);

#endif

