#include "uart.h"

#define FIFO_SIZE 256

typedef struct
{
	uint8_t cmd;
	UINT16_VAL data;
}ComData;

ComData g_ComData;
static uint8_t cmd_flag=0;

volatile int8_t  FifoHead = 0;
volatile int8_t  FifoTail = 0;
volatile uint8_t FifoBuff[FIFO_SIZE];
volatile UINT16_VAL n_Count;

int32_t FifoWriteOneByte(uint8_t InputChar)
{
		if((FifoHead + 1)%FIFO_SIZE == FifoTail)
		{
			SerPrintf("FIFO buffer overflow\n");
			return -1;
		}
		
		FifoBuff[FifoHead] = InputChar;
		FifoHead = (FifoHead + 1)%FIFO_SIZE;
		
		return 0;
}

int32_t InquireUartRecvBuffer(uint8_t *pBuf, int8_t MaxBuffCount)
{
		int8_t i = 0;
		int8_t RcvCount = 0;

		while((FifoHead != FifoTail) && (MaxBuffCount > 0))
		{
				pBuf[i++] = FifoBuff[FifoTail];
				FifoBuff[FifoTail] = 0;
				FifoTail = (FifoTail + 1)%FIFO_SIZE;
				MaxBuffCount--;
				RcvCount++;
		}
		
		return RcvCount;
}

void USARTx_Init(void)
{
		USART_PORT_RX->MODER |= USART_PORT_MODE_RX; //设置 USART_RX/TX 为复用模式
		USART_PORT_TX->MODER |= USART_PORT_MODE_TX;
		
		USART_PORT_RX->AFR[AFR_HILO_RX] |= AFR_GRES_RX; //选择复用功能 AF7
		USART_PORT_TX->AFR[AFR_HILO_TX] |= AFR_GRES_TX;
	
		USARTx->GTPR = USART_GTPR_PSC_0;
		USARTx->BRR = Baud_Rate;
		// 默认值：起始位1位，数据位8位，停止位n位
		USARTx->CR1 |= ( USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE ); //使能USARTx
		USARTx->CR1 |= USART_CR1_UE;
	
		NVIC->IP[NVIC_IP_NUM] = 0x40; //默认16级抢占优先级，设置优先级为4	
		NVIC->ISER[ISER_NUM] |= EnableIRQn; //使能 USARTx 中断

		return;
}

void USARTx_SendData(uint8_t byte)
{
		while( (USARTx->SR & USART_SR_TC)==0 );//等待发送完成	
		USARTx->DR = byte;
}

void  SerWrStr (const char * tx_str)
{
    while ((*tx_str) != 0)
		{
				if( (*tx_str) == '\n' )
				{
						USARTx_SendData('\r');
						USARTx_SendData('\n');
				}
				else
				{
						USARTx_SendData(*tx_str);
				}
				tx_str++;
		}
}

void SerPrintf(const  char *format, ...)
{
    static	char buffer[255];
		va_list	vArgs;

    va_start(vArgs, format);
    vsprintf((char *)buffer, (char const *)format, vArgs);
    va_end(vArgs);

    SerWrStr((char*) buffer);
}

void CheckData(uint8_t byte)
{
	static uint8_t state=0;
	switch(state)
	{
		case 0:
		{
			 if(byte==0xFB)
			 {
					state=1;
			 }
			 else
			 {
					state=0;
			 }
		}
		break;

		case 1:
		{
			 g_ComData.data.Byte[1]=byte;
			 state=2;
		}
		break;
		
		case 2:
		{
			 g_ComData.data.Byte[0]=byte;
			 state=3;
		}
		break;
		
		case 3:
		{
			 g_ComData.cmd=byte;
			 cmd_flag=1; //数据开始解析
			 state=0;
		}
		break;
		
		default:
			break;
	}

	return;
}

void Dispose(void)
{
	uint8_t i=0;
	uint8_t tmp[10]={0};
	uint8_t count=0;
	float ADC_val=0;
	long int cstr = 0;
	
	count=InquireUartRecvBuffer(tmp,10);
	if(count==0)
	{
		return;
	}
	
	for(i=0;i<count;i++)
	{
		CheckData(tmp[i]);
	}
	
	if(cmd_flag == 1)
	{	
		switch(g_ComData.cmd)
		{
			case 0xE0:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					if(g_ComData.data.Word)
					{
							PWM0_Start(10,g_ComData.data.Word);
					}
					else
					{
							PWM0_Stop();
					}	
			}
			break;
			
			case 0xE1:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					if(g_ComData.data.Word)
					{
							PWM1_Start(10,g_ComData.data.Word);
					}
					else
					{	
							PWM1_Stop();
					}
			}
			break;
			
			case 0xE2:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					if(g_ComData.data.Word)
					{
							PWM2_Start(10,g_ComData.data.Word);
					}
					else
					{
							PWM2_Stop();
					}
			}
			break;
			
			case 0xE3:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					if(g_ComData.data.Word)
					{
							PWM3_Start(10,g_ComData.data.Word);
					}
					else
					{
							PWM3_Stop();
					}
			}
			break;						
			
			case 0xE4:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					ReadAdcVol(g_ComData.data.Byte[0], &ADC_val);
					SerPrintf("The ADC Val of %x is %f\n",g_ComData.data.Byte[0],ADC_val);
					if(g_ComData.data.Word)
					{
							
					}
					else
					{
							
					}
			}
			break;						
			
			case 0xE5:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					SetDacVol(g_ComData.data.Byte[0],(float)g_ComData.data.Byte[1]);
					if(g_ComData.data.Word)
					{

					}
					else
					{
							
					}
			}
			break;
			
			case 0xE6:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					Dout(g_ComData.data.Byte[1],g_ComData.data.Byte[0]);
					if(g_ComData.data.Word)
					{
						
					}
					else
					{
							
					}
			}
			break;
			
			case 0xE7:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					if(g_ComData.data.Word)
					{
							n_Count.Word = g_ComData.data.Word;
					}
					else
					{
							n_Count.Word = 0;
					}
			}
			break;
			
			case 0xE8:
			{
					SerPrintf("cmd=%x,data=%x\n",g_ComData.cmd , g_ComData.data.Word);
					if(g_ComData.data.Word)
					{
							DIR0(1);
							DIR1(1);
							DIR2(1);
							DIR3(1);
							EN0(1);
							EN1(1);
							EN2(1);
							EN3(1);
						
							SerPrintf("Test,Set Dir and En to High\n");
							
					}
					else
					{
							DIR0(0);
							DIR1(0);
							DIR2(0);
							DIR3(0);
							EN0(0);
							EN1(0);
							EN2(0);
							EN3(0);
						
							SerPrintf("Test,Set Dir and En to Low\n");
					}
			}
			break;
			
			default:
				break;	
		}
		
		cmd_flag=0;
	}
}

