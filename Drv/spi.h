#ifndef _SPI_H
#define _SPI_H
#include "stm32f4xx_hal.h"

void spi_init(void);
uint16_t SPI1_ReadWriteByte(uint16_t TxData);

#define CS_H()			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)
#define CS_L()			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)

#endif
