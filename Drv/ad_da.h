#ifndef _AD_DA_H_
#define _AD_DA_H_

#include "stm32f4xx_hal.h"
#include "uart.h"
#include "config_file.h"

#define Read  0x800000
#define Write 0x000000

//Channel Select
#define DAC_Channel_A    0x000000
#define DAC_Channel_B    0x010000
#define DAC_Channel_C    0x020000
#define DAC_Channel_D    0x030000
#define DAC_Channel_ALL  0x040000

//Register Select
#define DAC_Register                  0x000000
#define Output_Range_Select_Register  0x080000
#define Power_Control_Register        0x100000

// Output Range Config
#define Range1_Select 0x000000//Range1: 0~5V
#define Range2_Select 0x000001//Range1: 0~10V
#define Range3_Select 0x000002//Range1: 0~10.8V
#define Range4_Select 0x000003//Range1: -5~+5V
#define Range5_Select 0x000004//Range1: -10~+10V
#define Range6_Select 0x000005//Range1: -10.8~+10.8V

// Power Control
#define PowerUp_ALL         0x00000F

#define PowerUp_Channel_A   0x000001
#define PowerDown_Channel_A 0xFFFFFE

#define PowerUp_Channel_B   0x000002
#define PowerDown_Channel_B 0xFFFFFD

#define PowerUp_Channel_C   0x000004
#define PowerDown_Channel_C 0xFFFFFB

#define PowerUp_Channel_D   0x000008
#define PowerDown_Channel_D 0xFFFFF7

#define PowerUp_REF         0x000010
#define PowerDown_REF       0xFFFFEF

//Control Register
#define Control        0x190000

#define TSD_Enable     0x000008
#define TSD_Disable    0x000000

#define Clamp_Enable   0x000004
#define TSD_Disable    0x000000
					  
#define Clear_Select0  0x000002
#define Clear_Select1  0x000000

#define SDO_Disable    0x000001
#define SDO_Enable     0x000000

//Clear
#define Clear 0x1C0000

//Load
#define Load 0x1D0000

void AD7606Initialization(void);
void AD7606Reset(void);
void AD7606ReadOneSample(uint16_t *DoutA, uint16_t *DoutB, uint8_t Channels);
void Delay_us(uint32_t us);
void ReadAdcVol(uint8_t ch, float* val);

//functions' prototype
extern long int cstr;

void AD5754_Init(void);
void WriteToAD5754RViaSpi(long int *RegisterData);
void ReadFromAD5754RViaSpi(long int *RegisterData);
void ConfigAD5754R(void);
void delay(int length);
void SetDacVol(uint8_t ch, float val);

#endif




