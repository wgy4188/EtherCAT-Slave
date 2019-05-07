#include "ad_da.h"

long int cstr = 0;

void AD7606Initialization(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

		
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Pin = AD7606_PIN_CONVST; //输出脚
    HAL_GPIO_Init(AD7606_PORT_CONVST, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = AD7606_PIN_RESET; //输出脚
    HAL_GPIO_Init(AD7606_PORT_RESET, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = AD7606_PIN_CS; //输出脚
    HAL_GPIO_Init(AD7606_PORT_CS, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = AD7606_PIN_SCK; //输出脚
    HAL_GPIO_Init(AD7606_PORT_SCK, &GPIO_InitStruct);
			
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pin = AD7606_PIN_BUSY; //输入脚
    HAL_GPIO_Init(AD7606_PORT_BUSY, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = AD7606_PIN_DOUTA; 
    HAL_GPIO_Init(AD7606_PORT_DOUTA, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = AD7606_PIN_DOUTB; 
    HAL_GPIO_Init(AD7606_PORT_DOUTB, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = AD7606_PIN_READY; 
    HAL_GPIO_Init(AD7606_PORT_READY, &GPIO_InitStruct);
	
		AD7606_CONVST(1);
		AD7606_CS(1);
		AD7606_SCK(1);
		AD7606_RESET(0);
}

void AD7606Reset(void)
{
		AD7606_RESET(1);
		Delay_us(1);
		AD7606_RESET(0);
		Delay_us(1);
}

void Delay_us(uint32_t us)
{
		uint32_t i,j;
		for(i=0;i<us;i++)
				for(j=0;j<216;j++);
}

void AD7606ReadOneSample(uint16_t *DoutA, uint16_t *DoutB, uint8_t Channels)
{
		uint8_t j, k;
		uint16_t TempA, TempB;
		uint8_t Busy=0;
		uint8_t Ready=0;
		uint8_t dataFlag=0;
	
		//开始转换
		AD7606_CONVST(0);
		Delay_us(1);
		AD7606_CONVST(1);
		Delay_us(1);
	
		//等待转换完成
		Busy=AD7606_BUSY;
		while(Busy)
		{
				Busy=AD7606_BUSY;
				Delay_us(1);
		}
		
		//读取数据
		AD7606_CS(0);
		for(j=0; j<Channels; j++)
		{
				TempA=0;
				TempB=0;
			
				Ready = AD7606_READY;
				if(Ready&&(dataFlag==0))
				{
						dataFlag=1;
#ifdef __DEBUG
						SerPrintf("Data is ready...\n");
#endif
				}
				
				if(dataFlag)
				{
						for(k=0; k<16; k++)
						{
								AD7606_SCK(0);//上升沿,数据输出
								Delay_us(1);
								TempA=(TempA<<1) + AD7606_DOUTA;
								TempB=(TempB<<1) + AD7606_DOUTB;
								AD7606_SCK(1);
								Delay_us(1);
						}
				}
				DoutA[j]=TempA;
				DoutB[j]=TempB;
#ifdef __DEBUG
				SerPrintf("DoutA:%x, DoutB:%x\n",TempA,TempB);
#endif
		}
		dataFlag=0;
		AD7606_CS(1);
}

/*AD5754控制接口*/
void AD5754_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
	
		GPIO_InitStruct.Pin = AD5754_PIN_CS; 
    HAL_GPIO_Init(AD5754_PORT_CS, &GPIO_InitStruct);
	
		GPIO_InitStruct.Pin = AD5754_PIN_SCK; 
    HAL_GPIO_Init(AD5754_PORT_SCK, &GPIO_InitStruct);
	
		GPIO_InitStruct.Pin = AD5754_PIN_SDIN; 
    HAL_GPIO_Init(AD5754_PORT_SDIN, &GPIO_InitStruct);
	
		GPIO_InitStruct.Pin = AD5754_PIN_CLR; 
    HAL_GPIO_Init(AD5754_PORT_CLR, &GPIO_InitStruct);
	
		AD5754_CS(1);
		AD5754_SCK(1);
		AD5754_SDIN(1);
		AD5754_CLR(1);
}

void delay (int length)
{
		while (length >0)
			length--;
}

void WriteToAD5754RViaSpi(long int *RegisterData)
{
		long int ValueToWrite = *RegisterData;
		int i;
		
		AD5754_CS(1);
		delay(10);
		AD5754_CS(0);	
		delay(1);
		
		for(i=0; i<24; i++)
		{	
				AD5754_SCK(1);
				delay(5);
				if(0x800000 == (ValueToWrite & 0x800000))
				{
						AD5754_SDIN(1);
				}
				else
				{
						AD5754_SDIN(0);
				}

				delay(5);
				AD5754_SCK(0);
				delay(5);
			
				ValueToWrite <<= 1;
				delay(5);
		}
			
		AD5754_CS(1);
		delay(10);
}

void ConfigAD5754R(void)
{
		int i;
		long int *p;
		long int ins[3] = {0, 0, 0}; //配置值缓存区
		
		ins[0] = Power_Control_Register | PowerUp_ALL; // 0x10000F
		ins[1] = Output_Range_Select_Register | DAC_Channel_ALL | Range6_Select; //0x080000 | 0x040000 | 0x000005
		ins[2] = Control | TSD_Enable | Clamp_Enable | Clear_Select0 | SDO_Disable; //0x190000 | 0x00000F
		
		p = ins;
		for(i=0; i<3; i++)
		{ 
				WriteToAD5754RViaSpi(p);
				delay(200);
				p++;
		}
}

void SetDacVol(uint8_t ch, float val)
{
		uint16_t CODE=0;
		long int cstr = 0;
	
		//根据DAC转换公式，将设置电压转换成数字值
		if((val > 10.8)&&(val < -10.8))
		{
#ifdef __DEBUG
		SerPrintf("The DAC Val You Set is Too Big, The Normal Range is -10.8~10.8V\n");
#endif		
		return;
		}
		CODE = (uint16_t)((val+(8.64*2.5)/2)/(8.64*2.5)*(0xffff+1));
#ifdef __DEBUG
		SerPrintf("The DAC Code = %x\n",CODE);
#endif
//		cstr = Clear;
//		WriteToAD5754RViaSpi(&cstr);
	
		switch(ch)
		{
			case 0:
			{
#ifdef __DEBUG
		SerPrintf("Set DAC Channel A\n");		
#endif
					cstr = DAC_Register | DAC_Channel_A | CODE;
					WriteToAD5754RViaSpi(&cstr);		
			}
			break;
			
			case 1:
			{
#ifdef __DEBUG
		SerPrintf("Set DAC Channel B\n");		
#endif
					cstr = DAC_Register | DAC_Channel_B | CODE;
					WriteToAD5754RViaSpi(&cstr);		
			}
			break;
			
			case 2:
			{
#ifdef __DEBUG
		SerPrintf("Set DAC Channel C\n");		
#endif
					cstr = DAC_Register | DAC_Channel_C | CODE;
					WriteToAD5754RViaSpi(&cstr);			
			}
			break;
			
			case 3:
			{
#ifdef __DEBUG
		SerPrintf("Set DAC Channel D\n");		
#endif
					cstr = DAC_Register | DAC_Channel_D | CODE;
					WriteToAD5754RViaSpi(&cstr);			
			}
			break;
			
			case 4:
			{
					cstr = DAC_Register | DAC_Channel_ALL | CODE;
					WriteToAD5754RViaSpi(&cstr);					
			}
			break;
			
			default:
#ifdef __DEBUG
			SerPrintf("The DAC Channel You Selece is Error\n");
#endif
				break;
			
		}
	
		cstr = Load;
		WriteToAD5754RViaSpi(&cstr);
		
		return;
}

void ReadAdcVol(uint8_t ch, float* val)
{
		uint16_t DoutA[2]={0};
		uint16_t DoutB[2]={0};
		
		AD7606ReadOneSample(DoutA,DoutB,2);
		
		switch(ch)
		{
			case 0:
			{
					*val = (float)(DoutA[0]*10)/32768;
			}
			break;
			
			case 1:
			{
					*val = (float)(DoutA[1]*10)/32768;
			}
			break;
			
			case 2:
			{
					*val = (float)(DoutB[0]*10)/32768;
			}
			break;
			
			case 3:
			{
					*val = (float)(DoutB[1]*10)/32768;
			}
			break;
			
			default:
#ifdef __DEBUG
			SerPrintf("The ADC Channel You Select is Error\n");
#endif
				break;
		}
		
		return;
}
