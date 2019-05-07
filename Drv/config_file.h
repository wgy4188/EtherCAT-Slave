#ifndef __CONFIG_FILE_H_
#define __CONFIG_FILE_H_

#include "dio.h"

/*************************************************************IO≈‰÷√************************************************************/
//DIN“˝Ω≈≈‰÷√
#define INPUT_PORT_0    GPIOC
#define INPUT_PORT_1    GPIOC
#define INPUT_PORT_2    GPIOC
#define INPUT_PORT_3    GPIOC
#define INPUT_PORT_4    GPIOC
#define INPUT_PORT_5    GPIOC
#define INPUT_PORT_6    GPIOC
#define INPUT_PORT_7    GPIOA
#define INPUT_PORT_8    GPIOA
#define INPUT_PORT_9    GPIOA
#define INPUT_PORT_10   GPIOA
#define INPUT_PORT_11   GPIOC
#define INPUT_PORT_12   GPIOB
#define INPUT_PORT_13   GPIOE
#define INPUT_PORT_14   GPIOB
#define INPUT_PORT_15   GPIOB
#define INPUT_PIN_0     GPIO_PIN_13
#define INPUT_PIN_1     GPIO_PIN_14
#define INPUT_PIN_2     GPIO_PIN_15
#define INPUT_PIN_3     GPIO_PIN_0
#define INPUT_PIN_4     GPIO_PIN_1
#define INPUT_PIN_5     GPIO_PIN_2
#define INPUT_PIN_6     GPIO_PIN_3
#define INPUT_PIN_7     GPIO_PIN_0
#define INPUT_PIN_8     GPIO_PIN_1
#define INPUT_PIN_9     GPIO_PIN_2
#define INPUT_PIN_10    GPIO_PIN_3
#define INPUT_PIN_11    GPIO_PIN_4
#define INPUT_PIN_12    GPIO_PIN_2
#define INPUT_PIN_13    GPIO_PIN_15
#define INPUT_PIN_14    GPIO_PIN_10
#define INPUT_PIN_15    GPIO_PIN_12

//DOUT“˝Ω≈≈‰÷√
#define OUTPUT_PORT_0   GPIOB
#define OUTPUT_PORT_1   GPIOB
#define OUTPUT_PORT_2   GPIOB
#define OUTPUT_PORT_3   GPIOD
#define OUTPUT_PORT_4   GPIOD
#define OUTPUT_PORT_5   GPIOD
#define OUTPUT_PORT_6   GPIOD
#define OUTPUT_PORT_7   GPIOD
#define OUTPUT_PORT_8   GPIOD
#define OUTPUT_PORT_9   GPIOD
#define OUTPUT_PORT_10  GPIOD
#define OUTPUT_PORT_11  GPIOC
#define OUTPUT_PORT_12  GPIOC
#define OUTPUT_PORT_13  GPIOC
#define OUTPUT_PORT_14  GPIOC
#define OUTPUT_PORT_15  GPIOA
#define OUTPUT_PIN_0    GPIO_PIN_13
#define OUTPUT_PIN_1    GPIO_PIN_14
#define OUTPUT_PIN_2    GPIO_PIN_15
#define OUTPUT_PIN_3    GPIO_PIN_8
#define OUTPUT_PIN_4    GPIO_PIN_9
#define OUTPUT_PIN_5    GPIO_PIN_10
#define OUTPUT_PIN_6    GPIO_PIN_11
#define OUTPUT_PIN_7    GPIO_PIN_12
#define OUTPUT_PIN_8    GPIO_PIN_13
#define OUTPUT_PIN_9    GPIO_PIN_14
#define OUTPUT_PIN_10   GPIO_PIN_15
#define OUTPUT_PIN_11   GPIO_PIN_6
#define OUTPUT_PIN_12   GPIO_PIN_7
#define OUTPUT_PIN_13   GPIO_PIN_8
#define OUTPUT_PIN_14   GPIO_PIN_9
#define OUTPUT_PIN_15   GPIO_PIN_9

//LED“˝Ω≈≈‰÷√
#define CPU_PORT_RUN		GPIOE
#define CPU_PIN_RUN			GPIO_PIN_2

#define CPU_PORT_ERR		GPIOE
#define CPU_PIN_ERR			GPIO_PIN_4

#define CAT_PORT_ERR		GPIOE
#define CAT_PIN_ERR			GPIO_PIN_5

#define CAN_PORT_RUN    GPIOE
#define CAN_PIN_RUN     GPIO_PIN_3

#define CAN_PORT_ERR    GPIOE
#define CAN_PIN_ERR     GPIO_PIN_6

//ExpandIO“˝Ω≈≈‰÷√
#define RCK_PORT				GPIOA
#define SCK_PORT				GPIOA
#define SI_PORT					GPIOA
#define SO_PORT					GPIOA
#define EN_PORT					GPIOB
#define RCK_PIN					GPIO_PIN_4
#define SCK_PIN					GPIO_PIN_5
#define SI_PIN					GPIO_PIN_7
#define SO_PIN					GPIO_PIN_6
#define EN_PIN					GPIO_PIN_9

/*************************************************************PWM≈‰÷√************************************************************/
#define PWM_PORT_0          GPIOA
#define PWM_PORT_1          GPIOB
#define PWM_PORT_2          GPIOB
#define PWM_PORT_3          GPIOB
#define PWM_ODR_0						(0x1<<8)
#define PWM_ODR_1						(0x1<<8)
#define PWM_ODR_2						(0x1<<4)
#define PWM_ODR_3						(0x1<<6)
#define PWM_PORT_MODE_0     GPIO_MODER_MODER8_0
#define PWM_PORT_MODE_1     GPIO_MODER_MODER8_0
#define PWM_PORT_MODE_2     GPIO_MODER_MODER4_0
#define PWM_PORT_MODE_3     GPIO_MODER_MODER6_0
#define PWM_PORT_SPEED_0    GPIO_OSPEEDER_OSPEEDR8_1
#define PWM_PORT_SPEED_1    GPIO_OSPEEDER_OSPEEDR8_1
#define PWM_PORT_SPEED_2    GPIO_OSPEEDER_OSPEEDR4_1
#define PWM_PORT_SPEED_3    GPIO_OSPEEDER_OSPEEDR6_1

/*************************************************************USART≈‰÷√************************************************************/
#define USARTx							USART2
#define USART_PORT_RX				GPIOD
#define USART_PORT_TX				GPIOD
#define USART_PORT_MODE_RX	GPIO_MODER_MODER6_1
#define USART_PORT_MODE_TX	GPIO_MODER_MODER5_1
#define USART_CLKEN					APB1ENR
#define USART_RCC_APBEN			RCC_APB1ENR_USART2EN
#define AFR_HILO_RX					0
#define AFR_HILO_TX					0
#define AFR_GRES_RX					(0x7<<24)
#define AFR_GRES_TX					(0x7<<20)
#define Baud_Rate						(0x124<<4)
#define NVIC_IP_NUM					38
#define ISER_NUM						1
#define EnableIRQn					(0x1UL<<6)

/*************************************************************AD_DA≈‰÷√************************************************************/
//AD7606  ˝æ›Ω”ø⁄
#define	AD7606_PORT_CONVST	GPIOA
#define	AD7606_PORT_RESET		GPIOA
#define	AD7606_PORT_BUSY		GPIOC
#define	AD7606_PORT_CS			GPIOD
#define	AD7606_PORT_SCK			GPIOD
#define	AD7606_PORT_DOUTA		GPIOD
#define	AD7606_PORT_DOUTB		GPIOD
#define	AD7606_PORT_READY		GPIOC
#define AD7606_PIN_CONVST		GPIO_PIN_10
#define AD7606_PIN_RESET		GPIO_PIN_15
#define AD7606_PIN_BUSY			GPIO_PIN_10
#define AD7606_PIN_CS				GPIO_PIN_1
#define AD7606_PIN_SCK			GPIO_PIN_0
#define AD7606_PIN_DOUTA		GPIO_PIN_2
#define AD7606_PIN_DOUTB		GPIO_PIN_4
#define AD7606_PIN_READY		GPIO_PIN_12
#define AD7606_CONVST(x)  	( (x)?(HAL_GPIO_WritePin(AD7606_PORT_CONVST, AD7606_PIN_CONVST, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD7606_PORT_CONVST, AD7606_PIN_CONVST, GPIO_PIN_RESET)) )
#define AD7606_RESET(x) 		( (x)?(HAL_GPIO_WritePin(AD7606_PORT_RESET, AD7606_PIN_RESET, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD7606_PORT_RESET, AD7606_PIN_RESET, GPIO_PIN_RESET)) )
#define AD7606_BUSY  				( HAL_GPIO_ReadPin(AD7606_PORT_BUSY, AD7606_PIN_BUSY) );
#define AD7606_CS(x)  			( (x)?(HAL_GPIO_WritePin(AD7606_PORT_CS, AD7606_PIN_CS, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD7606_PORT_CS, AD7606_PIN_CS, GPIO_PIN_RESET)) )
#define AD7606_SCK(x)  			( (x)?(HAL_GPIO_WritePin(AD7606_PORT_SCK, AD7606_PIN_SCK, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD7606_PORT_SCK, AD7606_PIN_SCK, GPIO_PIN_RESET)) )
#define AD7606_DOUTA      	( HAL_GPIO_ReadPin(AD7606_PORT_DOUTA, AD7606_PIN_DOUTA) )	
#define AD7606_DOUTB  	  	( HAL_GPIO_ReadPin(AD7606_PORT_DOUTB, AD7606_PIN_DOUTB) )
#define AD7606_READY  	  	( HAL_GPIO_ReadPin(AD7606_PORT_READY, AD7606_PIN_READY) )

//AD5754  ˝æ›Ω”ø⁄
#define AD5754_PORT_CS			GPIOD
#define AD5754_PORT_SCK			GPIOB
#define AD5754_PORT_SDIN		GPIOB
#define AD5754_PORT_CLR			GPIOB
#define AD5754_PIN_CS				GPIO_PIN_7
#define AD5754_PIN_SCK			GPIO_PIN_3
#define AD5754_PIN_SDIN			GPIO_PIN_5
#define AD5754_PIN_CLR			GPIO_PIN_7
#define AD5754_CS(x)      	( (x)?(HAL_GPIO_WritePin(AD5754_PORT_CS, AD5754_PIN_CS, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD5754_PORT_CS, AD5754_PIN_CS, GPIO_PIN_RESET)) ) 
#define AD5754_SCK(x)     	( (x)?(HAL_GPIO_WritePin(AD5754_PORT_SCK, AD5754_PIN_SCK, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD5754_PORT_SCK, AD5754_PIN_SCK, GPIO_PIN_RESET)) ) 
#define AD5754_SDIN(x)    	( (x)?(HAL_GPIO_WritePin(AD5754_PORT_SDIN, AD5754_PIN_SDIN, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD5754_PORT_SDIN, AD5754_PIN_SDIN, GPIO_PIN_RESET)) )
#define AD5754_CLR(x)     	( (x)?(HAL_GPIO_WritePin(AD5754_PORT_CLR, AD5754_PIN_CLR, GPIO_PIN_SET)):(HAL_GPIO_WritePin(AD5754_PORT_CLR,AD5754_PIN_CLR, GPIO_PIN_RESET)) )


#endif


