/*
*********************************************************************************************************
*                                               uC/LCD
*                                         LCD Module Driver
*
*                              (c) Copyright 2005; Micrium; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        LCD MODULE SOURCE FILE
*
* Filename      : lcd.h
* Programmer(s) : JJL
* Version       : V3.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  DISP_MODULE_PRESENT        1

#define  DISP_SEL_CMD_REG           0
#define  DISP_SEL_DATA_REG          1

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  DispChar(CPU_INT08U row, CPU_INT08U col, CPU_INT08U c);
void  DispClrLine(CPU_INT08U line);
void  DispClrScr(void);
void  DispDefChar(CPU_INT08U id, CPU_INT08U *pat);
void  DispDly_uS(CPU_INT32U us);
void  DispDummy(void);
void  DispHorBar(CPU_INT08U row, CPU_INT08U col, CPU_INT08U val);
void  DispHorBarInit(void);
void  DispVertBar(CPU_INT08U row, CPU_INT08U col, CPU_INT08U val);
void  DispVertBarInit(void);
void  DispInit(CPU_INT08U maxrows, CPU_INT08U maxcols);
void  DispStr(CPU_INT08U row, CPU_INT08U col, CPU_INT08U *s);

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*                                            HARDWARE SPECIFIC
*********************************************************************************************************
*/

#if DISP_BUS_WIDTH == 4
void  DispDataWrOneNibble(CPU_INT08U data);
#endif

void  DispDataWr(CPU_INT08U data);
void  DispInitPort(void);
void  DispSel(CPU_INT08U sel);

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*                                               OS SPECIFIC
*********************************************************************************************************
*/

void  DispInitOS(void);                       /* Initialize RTOS services                              */
void  DispLock(void);                         /* Ensure  exclusive access to the display               */
void  DispUnlock(void);                       /* Release exclusive access to the display               */
