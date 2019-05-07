
#include "qspi.h"

QSPI_HandleTypeDef hqspi;

void SQIEN (void)
{
    QSPI_CommandTypeDef sCommand;
	  UINT32_VAL CSR_CMD={0};	

		sCommand.Instruction       =0x38;                 	  
		sCommand.Address           =0;                            
		sCommand.NbData            =0;
		sCommand.DummyCycles       =0;  
		sCommand.InstructionMode   =QSPI_INSTRUCTION_1_LINE;	
		sCommand.AddressMode       =QSPI_ADDRESS_NONE;  
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS; 
		sCommand.DataMode          =QSPI_DATA_NONE;    
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;    
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE; 
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;       
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;

		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}			
		
		if(HAL_QSPI_Transmit(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		return ;
}

void SPI_SQI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

/*************************************
			PC11 --- QSPI_CS  --- AF9
			PD3  --- QSPI_CLK --- AF9
			PE7  --- QSPI_IO0 --- AF10
			PE8  --- QSPI_IO0 --- AF10
			PE9  --- QSPI_IO0 --- AF10
			PE10 --- QSPI_IO0 --- AF10
**************************************/
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QSPI;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QSPI;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QSPI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
				
		hqspi.Instance = QUADSPI;
    HAL_QSPI_DeInit(&hqspi);
		
    hqspi.Instance                = QUADSPI;
    hqspi.Init.ClockPrescaler     = 1;                                  
    hqspi.Init.FifoThreshold      = 32;                                 
    hqspi.Init.SampleShifting     = QSPI_SAMPLE_SHIFTING_HALFCYCLE;    
    hqspi.Init.FlashSize          = 11;
    hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_8_CYCLE;         
    hqspi.Init.ClockMode          = QSPI_CLOCK_MODE_0;                 
    hqspi.Init.FlashID            = QSPI_FLASH_ID_2;                   
    hqspi.Init.DualFlash          = QSPI_DUALFLASH_DISABLE;            
    HAL_QSPI_Init(&hqspi);
		
    SQIEN();
}

void SQIWriteDWord (UINT16 Address, UINT32 Val)
{
    QSPI_CommandTypeDef sCommand;
	  UINT32_VAL CSR_CMD={0};	
	
		CSR_CMD.DWord = Val;
	
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	     
		sCommand.Address           =Address;                               
		sCommand.NbData            =4;
		sCommand.DummyCycles       =0;                                   
		sCommand.InstructionMode   =QSPI_INSTRUCTION_4_LINES;				     
		sCommand.AddressMode       =QSPI_ADDRESS_4_LINES;   					   
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS;   					   
		sCommand.DataMode          =QSPI_DATA_4_LINES;             			
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;       	  
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE;           
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;           	   
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;

		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		return ;
}

UINT32 SQIReadDWord (UINT16 Address)
{
    QSPI_CommandTypeDef sCommand;
	  UINT32_VAL CSR_CMD={0};	

		sCommand.Instruction       =CMD_FAST_READ;                 	      
		sCommand.Address           =Address;                               
		sCommand.NbData            =4;
		sCommand.DummyCycles       =6;                                    
		sCommand.InstructionMode   =QSPI_INSTRUCTION_4_LINES;				       
		sCommand.AddressMode       =QSPI_ADDRESS_4_LINES;   					     
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS;   					    
		sCommand.DataMode          =QSPI_DATA_4_LINES;             				
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;       	    
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE;            
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;           	    
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;

		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)  
		{
				CatErrLed(1);
			  return 0;
		}			
		if(HAL_QSPI_Receive(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return 0;
		}
		
		return CSR_CMD.DWord;
}

UINT8 SQIReadRegUsingCSR(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count)
{
    QSPI_CommandTypeDef sCommand;
	  UINT32_VAL CSR_CMD={0};	
	
		CSR_CMD.DWord = ((UINT32)ESC_READ_BYTE<<24)|((UINT32)Count<<16)|((UINT32)Address);

		sCommand.DummyCycles       =0;                                     
		sCommand.InstructionMode   =QSPI_INSTRUCTION_4_LINES;				     
		sCommand.AddressMode       =QSPI_ADDRESS_4_LINES;   					  
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS;   					  
		sCommand.DataMode          =QSPI_DATA_4_LINES;             			
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;       	 
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE;         
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;           	  
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;

		//step1 写CSR
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	  
		sCommand.Address           =ESC_CSR_CMD_REG;                             
		sCommand.NbData            = 4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)  
		{
				CatErrLed(1);
			  return 0;
		}			
		if(HAL_QSPI_Transmit(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return 0;
		}
		
		//step2等待CSR繁忙位释放，开始接收信号
		sCommand.Instruction       =CMD_FAST_READ;                 	   
		sCommand.DummyCycles       =6;                                  
		do
		{
				if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		    {
						CatErrLed(1);
			      return 0;
		    }			
			  if(HAL_QSPI_Receive(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
					  return 0;
				}
		}while( CSR_CMD.Byte[3]& ESC_CSR_BUSY);
		
		//step3读取数据
		sCommand.Address =ESC_CSR_DATA_REG;                      
	  sCommand.NbData=Count;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return 0;
		}			
		if(HAL_QSPI_Receive(&hqspi,ReadBuffer,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return 0;
		}
		
		return 0;
}

void SQIWriteRegUsingCSR( UINT8 *WriteBuffer, UINT16 Address, UINT8 Count)
{
    QSPI_CommandTypeDef sCommand;

	  UINT32_VAL CSR_CMD={0};	
		
		sCommand.DummyCycles       =0;                                    
		sCommand.InstructionMode   =QSPI_INSTRUCTION_4_LINES;				      
		sCommand.AddressMode       =QSPI_ADDRESS_4_LINES;   					    
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS;   					    
		sCommand.DataMode          =QSPI_DATA_4_LINES;             				
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;       	   
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE;            
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;           	    
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;

		//step1 写CSR
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	
		sCommand.Address           =ESC_CSR_DATA_REG;                       
		sCommand.NbData            =4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)  
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,WriteBuffer,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step2 写数据
		CSR_CMD.DWord = ((UINT32)ESC_WRITE_BYTE<<24)|((UINT32)Count<<16)|((UINT32)Address);
		sCommand.Address           =ESC_CSR_CMD_REG;                              
		sCommand.NbData            = 4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK) 
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}	
		
		//step2等待CSR繁忙位释放,完成数据写操作
		sCommand.Instruction       =CMD_FAST_READ;                 	 
		sCommand.DummyCycles       =6;                                
		do
		{
				if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		    {
						CatErrLed(1);
			      return ;
		    }			
				if(HAL_QSPI_Receive(&hqspi,CSR_CMD.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
			      return ;
				}
		}while( CSR_CMD.Byte[3]& ESC_CSR_BUSY);
		
		return;
}

void SQIReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    QSPI_CommandTypeDef sCommand;
		UINT8 RCMD_STATUS[4]={0};
    UINT32_VAL R_ADR_LEN={0};
    UINT32_VAL RCMD_BUSY={0};
    UINT8 RCMD_ABORT[]={0,0,0,0x40};

		R_ADR_LEN.DWord=((UINT32)Count<<16)|((UINT32)Address);
		RCMD_BUSY.DWord=PRAM_RW_BUSY_32B;

		sCommand.DummyCycles       =0;                                     
		sCommand.InstructionMode   =QSPI_INSTRUCTION_4_LINES;				      
		sCommand.AddressMode       =QSPI_ADDRESS_4_LINES;   					      
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS;   					     
		sCommand.DataMode          =QSPI_DATA_4_LINES;             				
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;       	    
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE;            
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;           	    
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;
		
		//step1终止之前传输
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	 
		sCommand.Address           =PRAM_READ_CMD_REG;                  
		sCommand.NbData            = 4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,RCMD_ABORT,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step2读是否繁忙
		sCommand.Instruction       =CMD_FAST_READ;                 
		sCommand.Address           =PRAM_READ_CMD_REG;             
		sCommand.NbData            =4;
		sCommand.DummyCycles       =6;                            
		do
		{
				if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		    {
						CatErrLed(1);
			      return ;
		    }			
				if(HAL_QSPI_Receive(&hqspi,RCMD_STATUS,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
					  return ;
				}
		}while(RCMD_STATUS[3] & PRAM_RW_BUSY_8B);
		
		//step3 写CSR RAM地址和数据长度
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	  
		sCommand.Address           =PRAM_READ_ADDR_LEN_REG;                 
		sCommand.DummyCycles       =0;                                    
		sCommand.NbData            =4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,R_ADR_LEN.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step4 置CSR繁忙位为1
		sCommand.Address           =PRAM_READ_CMD_REG;                       
		sCommand.NbData            = 4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)  
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,RCMD_BUSY.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step4等待CSR繁忙位释放，开始接收信号
		sCommand.Instruction       =CMD_FAST_READ;                 	   
		sCommand.NbData            =4;
		sCommand.DummyCycles       =6;                                 
		do
		{
				if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		    {
						CatErrLed(1);
			      return ;
		    }			
				if(HAL_QSPI_Receive(&hqspi,RCMD_STATUS,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
			      return ;
				}
		}while( !(RCMD_STATUS[0] & IS_PRAM_SPACE_AVBL_MASK));
		
		//step5读取数据
		sCommand.Address =0;                         
		sCommand.NbData  =Count;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Receive(&hqspi,ReadBuffer,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
    return;
}


void SQIWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    QSPI_CommandTypeDef sCommand;
		UINT8 RCMD_STATUS[4]={0};
    UINT32_VAL R_ADR_LEN={0};
    UINT32_VAL RCMD_BUSY={0};
    UINT8 RCMD_ABORT[]={0,0,0,0x40};
		
		R_ADR_LEN.DWord=((UINT32)Count<<16)|((UINT32)Address);
		RCMD_BUSY.DWord=((UINT32)1<<31);

		sCommand.DummyCycles       =0;                                     
		sCommand.InstructionMode   =QSPI_INSTRUCTION_4_LINES;				     
		sCommand.AddressMode       =QSPI_ADDRESS_4_LINES;   					   
		sCommand.AddressSize       =QSPI_ADDRESS_16_BITS;   					   
		sCommand.DataMode          =QSPI_DATA_4_LINES;             			
		sCommand.SIOOMode          =QSPI_SIOO_INST_EVERY_CMD;       	   
		sCommand.AlternateByteMode =QSPI_ALTERNATE_BYTES_NONE;            
		sCommand.DdrMode           =QSPI_DDR_MODE_DISABLE;           	    
		sCommand.DdrHoldHalfCycle  =QSPI_DDR_HHC_ANALOG_DELAY;
		
		//step1终止之前传输
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	  
		sCommand.Address           =PRAM_WRITE_CMD_REG;                   
		sCommand.NbData            =4;
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,RCMD_ABORT,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step2读是否繁忙
		sCommand.Instruction       =CMD_FAST_READ;                 	
		sCommand.DummyCycles       =6;                               
		do
		{
				if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		    {
						CatErrLed(1);
			      return ;
		    }			
				if(HAL_QSPI_Receive(&hqspi,RCMD_STATUS,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
			      return ;
				}
		}while(RCMD_STATUS[3] & 0x80);
		
		//step3 写CSR RAM地址和数据长度
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	 
		sCommand.Address           =PRAM_WRITE_ADDR_LEN_REG;                   
		sCommand.DummyCycles       =0;                                    
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK) 
		{
				CatErrLed(1);
			  return ;
		}			
		
		if(HAL_QSPI_Transmit(&hqspi,R_ADR_LEN.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step4 置CSR繁忙位为1
		sCommand.Address           =PRAM_WRITE_CMD_REG;                     
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)  
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,RCMD_BUSY.Byte,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
		//step4等待CSR繁忙位释放，开始接收信号
		sCommand.Instruction       =CMD_FAST_READ;                 	   
		sCommand.DummyCycles       =6;                                 
		do
		{
				if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
			      return ;
		    }			
				if(HAL_QSPI_Receive(&hqspi,RCMD_STATUS,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
				{
						CatErrLed(1);
			      return ;
				}
		}while( !(RCMD_STATUS[0] & IS_PRAM_SPACE_AVBL_MASK));
		
		//step5写数据
		sCommand.Instruction       =CMD_SERIAL_WRITE;                 	  
		sCommand.Address           =0x0020;                       
		Count=(Count%4)?(4-Count%4+Count):Count;
		sCommand.NbData            = Count;
		sCommand.DummyCycles       =0;                        
		if(HAL_QSPI_Command(&hqspi,&sCommand,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK) 
		{
				CatErrLed(1);
			  return ;
		}			
		if(HAL_QSPI_Transmit(&hqspi,WriteBuffer,HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK)
		{
				CatErrLed(1);
			  return ;
		}
		
    return;
}

void SQIReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    DISABLE_GLOBAL_INT;
    if (Address >= 0x1000)
    {
         SQIReadPDRamRegister(ReadBuffer, Address,Count);
    }
    else
    {
         SQIReadRegUsingCSR(ReadBuffer, Address,Count);
    }
		
		ENABLE_GLOBAL_INT;
}

void SQIWriteRegister( UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
	 DISABLE_GLOBAL_INT;
	 if (Address >= 0x1000)
	 {
		SQIWritePDRamRegister(WriteBuffer, Address,Count);
	 }
	 else
	 {
		SQIWriteRegUsingCSR(WriteBuffer, Address,Count);
	 }
	 ENABLE_GLOBAL_INT;
}
