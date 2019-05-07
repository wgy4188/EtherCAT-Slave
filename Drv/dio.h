#ifndef __dio_h__
#define __dio_h__

#include "stm32f4xx_hal.h"
#include "config_file.h"

#define CpuRunled(x) 		((x)?(CPU_PORT_RUN->BSRR |= (uint32_t)CPU_PIN_RUN<<16):(CPU_PORT_RUN->BSRR |= (uint32_t)CPU_PIN_RUN))//1µãÁÁ 0Ï¨Ãð
#define CpuErrled(x) 		((x)?(CPU_PORT_ERR->BSRR |= (uint32_t)CPU_PIN_ERR<<16):(CPU_PORT_ERR->BSRR |= (uint32_t)CPU_PIN_ERR))//1µãÁÁ 0Ï¨Ãð
#define CatErrLed(x) 		((x)?(CAT_PORT_ERR->BSRR |= (uint32_t)CAT_PIN_ERR<<16):(CAT_PORT_ERR->BSRR |= (uint32_t)CAT_PIN_ERR))//1µãÁÁ 0Ï¨Ãð
#define CanRunLed(x) 		((x)?(CAN_PORT_RUN->BSRR |= (uint32_t)CAN_PIN_RUN<<16):(CAN_PORT_RUN->BSRR |= (uint32_t)CAN_PIN_RUN))//1µãÁÁ 0Ï¨Ãð
#define CanErrLed(x) 		((x)?(CAN_PORT_ERR->BSRR |= (uint32_t)CAN_PIN_ERR<<16):(CAN_PORT_ERR->BSRR |= (uint32_t)CAN_PIN_ERR))//1µãÁÁ 0Ï¨Ãð

#define RCK_L()					HAL_GPIO_WritePin(RCK_PORT, RCK_PIN, GPIO_PIN_RESET)
#define RCK_H()					HAL_GPIO_WritePin(RCK_PORT, RCK_PIN, GPIO_PIN_SET)
#define SCK_L()					HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET)
#define SCK_H()					HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET)
#define SI_L()					HAL_GPIO_WritePin(SI_PORT, SI_PIN, GPIO_PIN_RESET)
#define SI_H()					HAL_GPIO_WritePin(SI_PORT, SI_PIN, GPIO_PIN_SET)
#define EN_H()					HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_SET)
#define EN_L()					HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_RESET)
#define SO_State()      HAL_GPIO_ReadPin(SO_PORT, SO_PIN)

extern uint32_t state;

void Din_Init(void);
void Dout_Init(void);
void Led_Init(void);
void ExpandIO_Init(void);
uint16_t Hc_Drive(uint32_t LedData);
void Write_DO(uint8_t val, uint32_t index);
uint16_t Read_DI(uint16_t index);
void Dout_Update(uint32_t out_value);
void Dout(uint8_t channel,uint8_t state);
#endif  
