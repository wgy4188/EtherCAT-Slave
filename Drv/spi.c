#include "spi.h"

SPI_HandleTypeDef SPI1_Handler;
//SPI1口初始化
void spi_init(void)
{
	uint16_t TxData;
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();			//使能GPIOB时钟
	__HAL_RCC_SPI1_CLK_ENABLE();			//使能SPI1时钟
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;											//复用推挽输出
	GPIO_Initure.Pull = GPIO_PULLUP;													//上拉
	GPIO_Initure.Speed = GPIO_SPEED_FAST;											//快速
	GPIO_Initure.Alternate = GPIO_AF5_SPI1;										//复用为SPI1
	
	GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	GPIO_Initure.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	SPI1_Handler.Instance = SPI1;																			//SPI1
	SPI1_Handler.Init.Mode = SPI_MODE_MASTER;													//设置SPI工作模式，为主模式
	SPI1_Handler.Init.Direction = SPI_DIRECTION_2LINES;								//SPI设置为双线模式
	SPI1_Handler.Init.DataSize = SPI_DATASIZE_16BIT;									//SPI发送接收16位帧结构
	SPI1_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;									//同步时钟空闲状态为高电平
	SPI1_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;											//同步时钟第2个跳变沿开始数据采样
	SPI1_Handler.Init.NSS = SPI_NSS_SOFT;											//NSS信号由软件控制
	SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;		//波特率预分频值为2
	SPI1_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;										//指定数据传输从MSB位开始
	SPI1_Handler.Init.TIMode = SPI_TIMODE_DISABLE;										//关闭TI模式
	SPI1_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;		//关闭CRC
	SPI1_Handler.Init.CRCPolynomial = 7;															//CRC计算多项式
	if(HAL_OK != HAL_SPI_Init(&SPI1_Handler))		//初始化
	{
		while(1);
	}
	
//	__HAL_SPI_DISABLE(&SPI1_Handler);																//关闭SPI1
//	SPI1_Handler.Instance->CR1 &= 0XFFC7;														//位3-5清零，用来设置波特率
//	SPI1_Handler.Instance->CR1 |= 0<<3;															//设置SPI速度,二分频
	
	__HAL_SPI_ENABLE(&SPI1_Handler);//使能SPI1
//	TxData = 0xffff;
//	HAL_SPI_Transmit(&SPI1_Handler, (uint8_t*)&TxData, 2, 1000);				//启动传输
//	printf("\r\nHAL_SPI_Transmit: %x\r\n", HAL_SPI_Transmit(&SPI1_Handler, (uint8_t*)&TxData, 2, 1000));
}

uint16_t SPI1_ReadWriteByte(uint16_t TxData)
{
	uint16_t Rxdata;
	CS_L();
	HAL_SPI_TransmitReceive(&SPI1_Handler, (uint8_t*)&TxData, (uint8_t*)&Rxdata, 1, 1000);
	CS_H();
	printf("\r\nRxData = %x, TxData = %x\r\n", Rxdata, TxData);
	return Rxdata;
}
