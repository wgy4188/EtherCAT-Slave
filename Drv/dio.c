
#include "dio.h"

uint32_t Buffer[] = {0xfffffe, 0xfffffd, 0xfffffb, 0xfffff7, 0xffffef, 0xffffdf, 0xffffbf, 0xffff7f,
										 0xfffeff, 0xfffdff, 0xfffbff, 0xfff7ff, 0xffefff, 0xffdfff, 0xffbfff, 0xff7fff,
										 0xfeffff, 0xfdffff, 0xfbffff, 0xf7ffff, 0xefffff, 0xdfffff, 0xbfffff, 0x7fffff};

uint32_t state = 0xffffff;
										 
void Din_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;

	GPIO_InitStruct.Pin = INPUT_PIN_0;
	HAL_GPIO_Init(INPUT_PORT_0, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_1;
	HAL_GPIO_Init(INPUT_PORT_1, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_2;
	HAL_GPIO_Init(INPUT_PORT_2, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_3;
	HAL_GPIO_Init(INPUT_PORT_3, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_4;
	HAL_GPIO_Init(INPUT_PORT_4, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_5;
	HAL_GPIO_Init(INPUT_PORT_5, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_6;
	HAL_GPIO_Init(INPUT_PORT_6, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_7;
	HAL_GPIO_Init(INPUT_PORT_7, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_8;
	HAL_GPIO_Init(INPUT_PORT_8, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_9;
	HAL_GPIO_Init(INPUT_PORT_9, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_10;
	HAL_GPIO_Init(INPUT_PORT_10, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_11;
	HAL_GPIO_Init(INPUT_PORT_11, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_12;
	HAL_GPIO_Init(INPUT_PORT_12, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_13;
	HAL_GPIO_Init(INPUT_PORT_13, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_14;
	HAL_GPIO_Init(INPUT_PORT_14, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = INPUT_PIN_15;
	HAL_GPIO_Init(INPUT_PORT_15, &GPIO_InitStruct);
	
	//高速输入
	GPIO_InitStruct.Pin = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);	
}

void Dout_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	GPIO_InitStruct.Pin = OUTPUT_PIN_0;
	HAL_GPIO_Init(OUTPUT_PORT_0, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_0, OUTPUT_PIN_0, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_1;
	HAL_GPIO_Init(OUTPUT_PORT_1, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_1, OUTPUT_PIN_1, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_2;
	HAL_GPIO_Init(OUTPUT_PORT_2, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_2, OUTPUT_PIN_2, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_3;
	HAL_GPIO_Init(OUTPUT_PORT_3, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_3, OUTPUT_PIN_3, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_4;
	HAL_GPIO_Init(OUTPUT_PORT_4, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_4, OUTPUT_PIN_4, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_5;
	HAL_GPIO_Init(OUTPUT_PORT_5, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_5, OUTPUT_PIN_5, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_6;
	HAL_GPIO_Init(OUTPUT_PORT_6, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_6, OUTPUT_PIN_6, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_7;
	HAL_GPIO_Init(OUTPUT_PORT_7, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_7, OUTPUT_PIN_7, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_8;
	HAL_GPIO_Init(OUTPUT_PORT_8, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_8, OUTPUT_PIN_8, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_9;
	HAL_GPIO_Init(OUTPUT_PORT_9, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_9, OUTPUT_PIN_9, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_10;
	HAL_GPIO_Init(OUTPUT_PORT_10, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_10, OUTPUT_PIN_10, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_11;
	HAL_GPIO_Init(OUTPUT_PORT_11, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_11, OUTPUT_PIN_11, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_12;
	HAL_GPIO_Init(OUTPUT_PORT_12, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_12, OUTPUT_PIN_12, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_13;
	HAL_GPIO_Init(OUTPUT_PORT_13, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_13, OUTPUT_PIN_13, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_14;
	HAL_GPIO_Init(OUTPUT_PORT_14, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_14, OUTPUT_PIN_14, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = OUTPUT_PIN_15;
	HAL_GPIO_Init(OUTPUT_PORT_15, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OUTPUT_PORT_15, OUTPUT_PIN_15, GPIO_PIN_SET);
	
	//高速输出
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
}

void ExpandIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	
	GPIO_Initure.Pull = GPIO_NOPULL;	
	GPIO_Initure.Pin = SCK_PIN;
	HAL_GPIO_Init(SCK_PORT, &GPIO_Initure);
	GPIO_Initure.Pin = SI_PIN;
	HAL_GPIO_Init(SI_PORT, &GPIO_Initure);
	GPIO_Initure.Pin = RCK_PIN;
	HAL_GPIO_Init(RCK_PORT, &GPIO_Initure);
	GPIO_Initure.Pin = EN_PIN;
	HAL_GPIO_Init(EN_PORT, &GPIO_Initure);
	
	GPIO_Initure.Pin = SO_PIN;
	GPIO_Initure.Mode = GPIO_MODE_INPUT;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	SCK_L();
	RCK_H();
	SI_H();
	EN_H();
}

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	
	GPIO_InitStruct.Pin = CPU_PIN_RUN;
	HAL_GPIO_Init(CPU_PORT_RUN, &GPIO_InitStruct);
	CpuRunled(0);
	
	GPIO_InitStruct.Pin = CPU_PIN_ERR;
	HAL_GPIO_Init(CPU_PORT_ERR, &GPIO_InitStruct);
	CpuErrled(0);
	
	GPIO_InitStruct.Pin = CAT_PIN_ERR;
	HAL_GPIO_Init(CAT_PORT_ERR, &GPIO_InitStruct);
	CatErrLed(0);
	
	GPIO_InitStruct.Pin = CAN_PIN_RUN;
	HAL_GPIO_Init(CAN_PORT_RUN, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = CAN_PIN_ERR;
	HAL_GPIO_Init(CAN_PORT_ERR, &GPIO_InitStruct);
}

uint16_t Hc_Drive(uint32_t data)
{
	uint32_t i, tmp16 = 0, outState = 0;
	RCK_L();
	/*74HC595扩展输出IO*/
	for(i = 0; i < 24; i++)
	{
		SCK_L();
		tmp16 = (data & 0x800000);
		if(tmp16)
		{
			SI_H();
		}
		else
		{
			SI_L();
		}
		data <<= 1;	
		SCK_H();
		__NOP;
		__NOP;
	}
	RCK_H();

	/*74H165扩展输入IO*/
	for(i = 0; i < 16; i++)
	{
		SCK_L();
		if(!SO_State())
		{
			outState |= 0x1<<(15 - i);
		}
		SCK_H();
		__NOP;
		__NOP;
	}
	SCK_L();
	return outState;
}

void Write_DO(uint8_t val, uint32_t index)
{
	if(0 == val)
	{
		state &= Buffer[index];
		Hc_Drive(state);
	}
	else
	{
		state |= ~Buffer[index];
		Hc_Drive(state);
	}
}

uint16_t Read_DI(uint16_t index)
{
	uint16_t DI_State;
	DI_State =	Hc_Drive(state);
	DI_State &= (0x01 << index);
	return DI_State;
}

void Dout_Update(uint32_t out_value)
{
	uint32_t out_0 = 0, out_1 = 0, out_2 = 0, out_3 = 0, out_4 = 0, out_5 = 0, out_6 = 0, out_7 = 0, out_8 = 0, out_9 = 0, out_10 = 0, out_11 = 0, out_12 = 0, out_13 = 0, out_14 = 0, out_15 = 0; 
	uint16_t out_x = 0;

	out_0  |= ((out_value&0x00000001)!=0x00000001)? OUTPUT_PIN_0  : ((uint32_t)OUTPUT_PIN_0 << 16);
	out_1  |= ((out_value&0x00000002)!=0x00000002)? OUTPUT_PIN_1  : ((uint32_t)OUTPUT_PIN_1 << 16);
	out_2  |= ((out_value&0x00000004)!=0x00000004)? OUTPUT_PIN_2  : ((uint32_t)OUTPUT_PIN_2 << 16);
	out_3  |= ((out_value&0x00000008)!=0x00000008)? OUTPUT_PIN_3  : ((uint32_t)OUTPUT_PIN_3 << 16);

	out_4  |= ((out_value&0x00000010)!=0x00000010)? OUTPUT_PIN_4  : ((uint32_t)OUTPUT_PIN_4 << 16);
	out_5  |= ((out_value&0x00000020)!=0x00000020)? OUTPUT_PIN_5  : ((uint32_t)OUTPUT_PIN_5 << 16);
	out_6  |= ((out_value&0x00000040)!=0x00000040)? OUTPUT_PIN_6  : ((uint32_t)OUTPUT_PIN_6 << 16);
	out_7  |= ((out_value&0x00000080)!=0x00000080)? OUTPUT_PIN_7  : ((uint32_t)OUTPUT_PIN_7 << 16);

	out_8  |= ((out_value&0x00000100)!=0x00000100)? OUTPUT_PIN_8  : ((uint32_t)OUTPUT_PIN_8 << 16);
	out_9  |= ((out_value&0x00000200)!=0x00000200)? OUTPUT_PIN_9  : ((uint32_t)OUTPUT_PIN_9 << 16);
	out_10 |= ((out_value&0x00000400)!=0x00000400)? OUTPUT_PIN_10 : ((uint32_t)OUTPUT_PIN_10 << 16);
	out_11 |= ((out_value&0x00000800)!=0x00000800)? OUTPUT_PIN_11 : ((uint32_t)OUTPUT_PIN_11 << 16);

	out_12 |= ((out_value&0x00001000)!=0x00001000)? OUTPUT_PIN_12 : ((uint32_t)OUTPUT_PIN_12 << 16);
	out_13 |= ((out_value&0x00002000)!=0x00002000)? OUTPUT_PIN_13 : ((uint32_t)OUTPUT_PIN_13 << 16);
	out_14 |= ((out_value&0x00004000)!=0x00004000)? OUTPUT_PIN_14 : ((uint32_t)OUTPUT_PIN_14 << 16);
	out_15 |= ((out_value&0x00008000)!=0x00008000)? OUTPUT_PIN_15 : ((uint32_t)OUTPUT_PIN_15 << 16);

	OUTPUT_PORT_0->BSRR |= out_0;
	OUTPUT_PORT_1->BSRR |= out_1;
	OUTPUT_PORT_2->BSRR |= out_2;
	OUTPUT_PORT_3->BSRR |= out_3;
	OUTPUT_PORT_4->BSRR |= out_4;
	OUTPUT_PORT_5->BSRR |= out_5;
	OUTPUT_PORT_6->BSRR |= out_6;
	OUTPUT_PORT_7->BSRR |= out_7;
	OUTPUT_PORT_8->BSRR |= out_8;
	OUTPUT_PORT_9->BSRR |= out_9;
	OUTPUT_PORT_10->BSRR |= out_10;
	OUTPUT_PORT_11->BSRR |= out_11;
	OUTPUT_PORT_12->BSRR |= out_12;
	OUTPUT_PORT_13->BSRR |= out_13;
	OUTPUT_PORT_14->BSRR |= out_14;
	OUTPUT_PORT_15->BSRR |= out_15;
	
	out_x = ~(uint16_t)(out_value >> 16);//取数据高16位
  state &= out_x;//更新扩展IO的状态
	Hc_Drive(state);
}

void Dout(uint8_t channel,uint8_t state)
{
	static uint32_t val=0;
	
	if(state==0)
	{
			val &= ~(0x1<<channel);
	}
	else
	{
			val |= 0x01<<channel;
	}

	Dout_Update(val);
}