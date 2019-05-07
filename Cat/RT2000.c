/**
\addtogroup RT2000 RT2000
@{
*/

/**
\file RT2000.c
\brief Implementation

\version 1.0.0.11
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "applInterface.h"

#define _RT2000_ 1
#include "RT2000.h"
#undef _RT2000_

#include "pwm.h"
#include "dio.h"
#include "ad_da.h"
 
static UINT16  M0_Toggled=0, M1_Toggled=0, M2_Toggled=0, M3_Toggled=0;
static UINT16  AO0_State=0, AO1_State=0, AO2_State=0, AO3_State=0, AI_State=0;
static UINT16  AdcValArrayA[2]={0};
static UINT16  AdcValArrayB[2]={0};
/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                        register (0x204) when this function is succeeded. The event mask can be adapted
                        in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
		PWM0_Stop();
		PWM1_Stop();
		PWM2_Stop();
		PWM3_Stop();		
	
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;
   
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;

    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;

#else
#if _WIN32
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16* pData)
{
		UINT16 DI_X1, DI_X2;
	
#if _WIN32
   #pragma message ("Warning: Implement input (Slave -> Master) mapping")
#else
    #warning "Implement input (Slave -> Master) mapping"
#endif
	
		DigitalIn0x6000.DI0=~HAL_GPIO_ReadPin(INPUT_PORT_0, INPUT_PIN_0);
		DigitalIn0x6000.DI1=~HAL_GPIO_ReadPin(INPUT_PORT_1, INPUT_PIN_1);
		DigitalIn0x6000.DI2=~HAL_GPIO_ReadPin(INPUT_PORT_2, INPUT_PIN_2);
		DigitalIn0x6000.DI3=~HAL_GPIO_ReadPin(INPUT_PORT_3, INPUT_PIN_3);
		DigitalIn0x6000.DI4=~HAL_GPIO_ReadPin(INPUT_PORT_4, INPUT_PIN_4);	
		DigitalIn0x6000.DI5=~HAL_GPIO_ReadPin(INPUT_PORT_5, INPUT_PIN_5);
		DigitalIn0x6000.DI6=~HAL_GPIO_ReadPin(INPUT_PORT_6, INPUT_PIN_6);
		DigitalIn0x6000.DI7=~HAL_GPIO_ReadPin(INPUT_PORT_7, INPUT_PIN_7);
		DigitalIn0x6000.DI8=~HAL_GPIO_ReadPin(INPUT_PORT_8, INPUT_PIN_8);
		DigitalIn0x6000.DI9=~HAL_GPIO_ReadPin(INPUT_PORT_9, INPUT_PIN_9);
		DigitalIn0x6000.DI10=~HAL_GPIO_ReadPin(INPUT_PORT_10, INPUT_PIN_10);
		DigitalIn0x6000.DI11=~HAL_GPIO_ReadPin(INPUT_PORT_11, INPUT_PIN_11);
		DigitalIn0x6000.DI12=~HAL_GPIO_ReadPin(INPUT_PORT_12, INPUT_PIN_12);
		DigitalIn0x6000.DI13=~HAL_GPIO_ReadPin(INPUT_PORT_13, INPUT_PIN_13);
		DigitalIn0x6000.DI14=~HAL_GPIO_ReadPin(INPUT_PORT_14, INPUT_PIN_14);
		DigitalIn0x6000.DI15=~HAL_GPIO_ReadPin(INPUT_PORT_15, INPUT_PIN_15);
		
		DI_X1= (UINT16)DigitalIn0x6000.DI0  | (DigitalIn0x6000.DI1<<1)   | (DigitalIn0x6000.DI2<<2)   | (DigitalIn0x6000.DI3<<3)
					|   (DigitalIn0x6000.DI4<<4)  | (DigitalIn0x6000.DI5<<5)   | (DigitalIn0x6000.DI6<<6)   | (DigitalIn0x6000.DI7<<7)
					|   (DigitalIn0x6000.DI8<<8)  | (DigitalIn0x6000.DI9<<9)   | (DigitalIn0x6000.DI10<<10)  | (DigitalIn0x6000.DI11<<11)
					|  (DigitalIn0x6000.DI12<<12)  | (DigitalIn0x6000.DI13<<13)  | (DigitalIn0x6000.DI14<<14)  | (DigitalIn0x6000.DI15<<15);
		DI_X2=Hc_Drive(state);
		
		*pData = DI_X1;	
		 pData++;
		*pData = DI_X2;
		
		//---------------模拟输入----------------
		AnalogIn0x6010.AI0 = (INT16)(AdcValArrayA[0]*10/32768);
		AnalogIn0x6010.AI1 = (INT16)(AdcValArrayA[1]*10/32768);
		AnalogIn0x6010.AI2 = (INT16)(AdcValArrayB[0]*10/32768);
		AnalogIn0x6010.AI3 = (INT16)(AdcValArrayB[1]*10/32768);
		
		 pData++;		
		*pData = AnalogIn0x6010.AI0;//WORD3
		 pData++;
		*pData = AnalogIn0x6010.AI1;//WORD4
		 pData++;
		*pData = AnalogIn0x6010.AI2;//WORD5
		 pData++;
		*pData = AnalogIn0x6010.AI3;//WORD6
		 
		//---------------编码器输入--------------
		EncodeIn0x6020.ENCODE1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_14);
		EncodeIn0x6020.ENCODE2 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_13);
		
		 pData++;
		*pData = EncodeIn0x6020.ENCODE1;//WORD7
		 pData++;
		*pData = EncodeIn0x6020.ENCODE2;//WORD8	
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
		UINT16 GPO_X1, GPO_X2;;
	
#if _WIN32
   #pragma message ("Warning: Implement output (Master -> Slave) mapping")
#else
    #warning "Implement output (Master -> Slave) mapping"
#endif
	
		//--------------数字输出--------------
		GPO_X1 = *pData;//WORD 1
	
		pData++;
		GPO_X2 = *pData;//WORD 2
		Dout_Update((uint32_t)GPO_X2<<16 | (uint32_t)GPO_X1);
	
		//--------------电机运动--------------
		pData++;
		Motor00x7010.M0_PluseNum = (INT16)*pData;//WORD 3
	
		pData++;
		Motor00x7010.M0_Cycle = (UINT16)*pData;//WORD 4
		
		pData++;
		Motor00x7010.M0_Dir= (UINT16)*pData;//WORD 5
		
		pData++;
		Motor00x7010.M0_EN = (UINT16)*pData;//WORD 6
		
		pData++;
		Motor00x7010.M0_Toggle = (UINT16)*pData;//WORD 7
		
		///////
		pData++;
		Motor10x7020.M1_PluseNum = (INT16)*pData;//WORD 8
		
		pData++;
		Motor10x7020.M1_Cycle = (UINT16)*pData;//WORD 9
		
		pData++;
		Motor10x7020.M1_Dir = (UINT16)*pData;//WORD 10		
		
		pData++;
		Motor10x7020.M1_EN = (UINT16)*pData;//WORD 11
		
		pData++;
		Motor10x7020.M1_Toggle = (UINT16)*pData;//WORD 12
		
		///////
		pData++;
		Motor20x7030.M2_PluseNum = (INT16)*pData;//WORD 13
		
		pData++;
		Motor20x7030.M2_Cycle = (UINT16)*pData;//WORD 14
		
		pData++;
		Motor20x7030.M2_Dir = (UINT16)*pData;//WORD 15
		
		pData++;
		Motor20x7030.M2_EN = (UINT16)*pData;//WORD 16
		
		pData++;
		Motor20x7030.M2_Toggle = (UINT16)*pData;//WORD 17
		
		///////
		pData++;
		Motor30x7040.M3_PluseNum = (INT16)*pData;//WORD 18
		
		pData++;
		Motor30x7040.M3_Cycle = (UINT16)*pData;//WORD 19
		
		pData++;
		Motor30x7040.M3_Dir = (UINT16)*pData;//WORD 20
		
		pData++;
		Motor30x7040.M3_EN = (UINT16)*pData;//WORD 21
		
		pData++;
		Motor30x7040.M3_Toggle = (UINT16)*pData;//WORD 22
		
		///////
		if(Motor00x7010.M0_Toggle != M0_Toggled)
		{
				//PWM0_Start(Motor00x7010.M0_Cycle, Motor00x7010.M0_PluseNum);
				PWM0_Start(1, Motor00x7010.M0_PluseNum);
				M0_Toggled = Motor00x7010.M0_Toggle;
		}
		DIR0(Motor00x7010.M0_Dir);
		EN0(Motor00x7010.M0_EN);
		
		////////
		if(Motor10x7020.M1_Toggle != M1_Toggled)
		{
				//PWM1_Start(Motor10x7020.M1_Cycle, Motor10x7020.M1_PluseNum);
				PWM1_Start(1, Motor10x7020.M1_PluseNum);
				M1_Toggled = Motor10x7020.M1_Toggle;
		}
		DIR1(Motor10x7020.M1_Dir);
		EN1(Motor10x7020.M1_EN);
		
		/////////
		if(Motor20x7030.M2_Toggle != M2_Toggled)
		{
				//PWM2_Start(Motor20x7030.M2_Cycle, Motor20x7030.M2_PluseNum);
				PWM2_Start(1, Motor20x7030.M2_PluseNum);
				M2_Toggled = Motor20x7030.M2_Toggle;
		}
		DIR2(Motor20x7030.M2_Dir);
		EN2(Motor20x7030.M2_EN);
		
		if(Motor30x7040.M3_Toggle != M3_Toggled)
		{
				//PWM3_Start(Motor30x7040.M3_Cycle, Motor30x7040.M3_PluseNum);
				PWM3_Start(1, Motor30x7040.M3_PluseNum);
				M3_Toggled = Motor30x7040.M3_Toggle;
		}
		DIR3(Motor30x7040.M3_Dir);
		EN3(Motor30x7040.M3_EN);
		
		//--------------模拟量输出--------------
		pData++;
		AnalogOut0x7050.AO0 = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO0_Update = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO1 = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO1_Update = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO2 = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO2_Update = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO3 = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AO3_Update = (UINT16)*pData;
		pData++;
		AnalogOut0x7050.AI_Update = (UINT16)*pData;
		
		if(AO0_State != AnalogOut0x7050.AO0_Update)
		{
				AO0_State = AnalogOut0x7050.AO0_Update;
				SetDacVol(0,(float)AnalogOut0x7050.AO0);
		}
		if(AO1_State != AnalogOut0x7050.AO1_Update)
		{
				AO1_State = AnalogOut0x7050.AO1_Update;
				SetDacVol(1,(float)AnalogOut0x7050.AO1);
		}
		if(AO2_State != AnalogOut0x7050.AO2_Update)
		{
				AO2_State = AnalogOut0x7050.AO2_Update;
				SetDacVol(2,(float)AnalogOut0x7050.AO2);
		}
		if(AO3_State != AnalogOut0x7050.AO3_Update)
		{
				AO3_State = AnalogOut0x7050.AO3_Update;
				SetDacVol(3,(float)AnalogOut0x7050.AO3);
		}
		if(AI_State != AnalogOut0x7050.AI_Update)
		{
				AI_State = AnalogOut0x7050.AI_Update;
				AD7606ReadOneSample(AdcValArrayA, AdcValArrayB, 2);
		}
		
		//-------------高速IO输出--------------
		pData++;
		HighSpeedOut0x7060.HSIO0 = *pData;
		pData++;
		HighSpeedOut0x7060.HSIO1 = *pData;
		
		if(HighSpeedOut0x7060.HSIO0)
		{
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET);
		}
		else
		{
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
		}
		
		if(HighSpeedOut0x7060.HSIO1)
		{
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
		}
		else
		{
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
		}
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
#if _WIN32
   #pragma message ("Warning: Implement the slave application")
#else
    #warning "Implement the slave application"
#endif
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Calculate the Explicit Device ID
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
   #pragma message ("Warning: Implement explicit Device ID latching")
#else
    #warning "Implement explicit Device ID latching"
#endif
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif



#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*////////////////////////////////////////////////////////////////////////////////////////
#if _PIC24
int main(void)
#else
void main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
#if FC1100_HW
    if(HW_Init())
    {
        HW_Release();
        return;
    }
#else
    HW_Init();
#endif
    MainInit();

    bRunApplication = TRUE;
    do
    {
        MainLoop();
        
    } while (bRunApplication == TRUE);

    HW_Release();
#if _PIC24
    return 0;
#endif
}
#endif //#if USE_DEFAULT_MAIN
/** @} */


