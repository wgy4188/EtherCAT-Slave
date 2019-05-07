#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f4xx_hal.h"
#include "uart.h"

#define DIR0(x)    					((x)?(Write_DO(1, 16)) : (Write_DO(0, 16)) )
#define DIR1(x)    					((x)?(Write_DO(1, 18)) : (Write_DO(0, 18)) )
#define DIR2(x)    					((x)?(Write_DO(1, 20)) : (Write_DO(0, 20)) )
#define DIR3(x)    					((x)?(Write_DO(1, 22)) : (Write_DO(0, 22)) )
#define EN0(x)    					((x)?(Write_DO(1, 17)) : (Write_DO(0, 17)) )
#define EN1(x)    					((x)?(Write_DO(1, 19)) : (Write_DO(0, 19)) )
#define EN2(x)    					((x)?(Write_DO(1, 21)) : (Write_DO(0, 21)) )
#define EN3(x)    					((x)?(Write_DO(1, 23)) : (Write_DO(0, 23)) )

extern volatile int16_t M0_Target, M1_Target, M2_Target, M3_Target;
extern volatile int16_t M0_Buffer, M1_Buffer, M2_Buffer, M3_Buffer;
extern volatile uint8_t M0_Flag, M1_Flag, M2_Flag, M3_Flag;
extern volatile uint16_t M0_Cycle, M1_Cycle, M2_Cycle, M3_Cycle; 
extern volatile int32_t Sum;
extern volatile uint32_t PulsNum;

void PWM_Config(void);
void PWM0_Start(uint16_t nCycle, int16_t nPulsNum);
void PWM1_Start(uint16_t nCycle, int16_t nPulsNum);
void PWM2_Start(uint16_t nCycle, int16_t nPulsNum);
void PWM3_Start(uint16_t nCycle, int16_t nPulsNum);

void PWM0_Stop(void);
void PWM1_Stop(void);
void PWM2_Stop(void);
void PWM3_Stop(void);

#endif
