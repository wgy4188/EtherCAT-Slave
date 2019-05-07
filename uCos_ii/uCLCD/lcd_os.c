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
*                                 LCD MODULE RTOS INTERFACE SOURCE FILE
*
* Filename      : lcd_os.c
* Programmer(s) : JJL
* Version       : V2.11
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/

static  OS_EVENT   *DispSem;                /* Semaphore used to access display functions              */

/*
*********************************************************************************************************
*                                       INITIALIZE RTOS SERVICES
*
* Description : This function creates a semaphore to ensure exclusive access to the LCD module and thus
*               provide thread safe access to the display.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  DispInitOS (void)
{
#if OS_EVENT_NAME_SIZE > 11
    INT8U  err;
#endif


    DispSem  = OSSemCreate(1);              /* Create display access semaphore                         */
#if OS_EVENT_NAME_SIZE > 11
    OSEventNameSet(DispSem, (INT8U *)"uC/LCD Lock", &err);
#endif
}

/*
*********************************************************************************************************
*                              EXCLUSIVE ACCESS FUNCTIONS TO THE DISPLAY
*
* Description : These functions are used to gain and release exclusive access to the LCD display.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  DispLock (void)
{
    INT8U  err;


    OSSemPend(DispSem, 0, &err);            /* Obtain exclusive access to the display                  */
}



void  DispUnlock (void)
{
    OSSemPost(DispSem);                     /* Release access to display                               */
}
