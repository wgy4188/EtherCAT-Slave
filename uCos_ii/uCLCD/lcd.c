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
* Filename      : lcd.c
* Programmer(s) : JJL
* Version       : V3.00
*********************************************************************************************************
*                                              DESCRIPTION
*
*
* This module provides an interface to an alphanumeric display module.
*
* The current version of this driver supports any  alphanumeric LCD module based on the:
*     Hitachi HD44780 DOT MATRIX LCD controller.
*
* This driver supports LCD displays having the following configuration:
*
*     1 line  x 16 characters     2 lines x 16 characters     4 lines x 16 characters
*     1 line  x 20 characters     2 lines x 20 characters     4 lines x 20 characters
*     1 line  x 24 characters     2 lines x 24 characters
*     1 line  x 40 characters     2 lines x 40 characters
*********************************************************************************************************
*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                            LOCAL CONSTANTS
*********************************************************************************************************
*/

                                       /* ---------------------- HD44780 COMMANDS -------------------- */
#define  DISP_CMD_CLS            0x01  /* Clr display : clears display and returns cursor home         */

#if      DISP_BUS_WIDTH == 4
#define  DISP_CMD_FNCT           0x28  /* Function Set: Set 4 bit data length, 1/16 duty, 5x8 dots     */
#else
#define  DISP_CMD_FNCT           0x38  /* Function Set: Set 8 bit data length, 1/16 duty, 5x8 dots     */
#endif

#define  DISP_CMD_FNCT_INIT8     0x30  /* Function Set: 8 bit mode, no options                         */
#define  DISP_CMD_FNCT_INIT4     0x20  /* Function Set: 4 bit mode, no options                         */

#define  DISP_CMD_MODE           0x06  /* Entry mode  : Inc. display data address when writing         */
#define  DISP_CMD_ON_OFF         0x0C  /* Disp ON/OFF : Display ON, cursor OFF and no BLINK character  */

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

static  CPU_INT08U   DispMaxCols;      /* Maximum number of columns (i.e. characters per line)         */
static  CPU_INT08U   DispMaxRows;      /* Maximum number of rows for the display                       */


static  CPU_INT08U   DispHorBar1[]  = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
static  CPU_INT08U   DispHorBar2[]  = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
static  CPU_INT08U   DispHorBar3[]  = {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
static  CPU_INT08U   DispHorBar4[]  = {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
static  CPU_INT08U   DispHorBar5[]  = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

static  CPU_INT08U   DispVertBar1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F};
static  CPU_INT08U   DispVertBar2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F};
static  CPU_INT08U   DispVertBar3[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F};
static  CPU_INT08U   DispVertBar4[] = {0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F};
static  CPU_INT08U   DispVertBar5[] = {0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
static  CPU_INT08U   DispVertBar6[] = {0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
static  CPU_INT08U   DispVertBar7[] = {0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
static  CPU_INT08U   DispVertBar8[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

/*
*********************************************************************************************************
*                                        LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void         DispCursorSet(CPU_INT08U row, CPU_INT08U col);

/*$PAGE*/
/*
*********************************************************************************************************
*                                           DISPLAY A CHARACTER
*
* Description : This function is used to display a single character on the display device
* Arguments   : 'row'   is the row    position of the cursor in the LCD Display
*                       'row' can be a value from 0 to 'DispMaxRows - 1'
*               'col'   is the column position of the cursor in the LCD Display
*                       'col' can be a value from 0 to 'DispMaxCols - 1'
*               'c'     is the character to write to the display at the current ROW/COLUMN position.
* Returns     : none
*********************************************************************************************************
*/

void  DispChar (CPU_INT08U row, CPU_INT08U col, CPU_INT08U c)
{
    if (row < DispMaxRows && col < DispMaxCols) {
        DispLock();
        DispCursorSet(row, col);            /* Position cursor at ROW/COL                              */
        DispSel(DISP_SEL_DATA_REG);
        DispDataWr(c);                      /* Send character to display                               */
        DispUnlock();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                             CLEAR LINE
*
* Description : This function clears one line on the LCD display and positions the cursor at the
*               beginning of the line.
* Arguments   : 'line'  is the line number to clear and can take the value
*                       0 to 'DispMaxRows - 1'
* Returns     : none
*********************************************************************************************************
*/

void  DispClrLine (CPU_INT08U line)
{
    CPU_INT08U i;


    if (line < DispMaxRows) {
        DispLock();
        DispCursorSet(line, 0);                  /* Position cursor at begin of the line to clear      */
        DispSel(DISP_SEL_DATA_REG);              /* Select the LCD Display DATA register               */
        for (i = 0; i < DispMaxCols; i++) {      /* Write ' ' into all column positions of that line   */
            DispDataWr(' ');                     /* Write an ASCII space at current cursor position    */
        }
        DispCursorSet(line, 0);                  /* Position cursor at begin of the line to clear      */
        DispUnlock();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                            CLEAR THE SCREEN
*
* Description : This function clears the display
* Arguments   : none
* Returns     : none
*********************************************************************************************************
*/

void  DispClrScr (void)
{
    DispLock();
    DispSel(DISP_SEL_CMD_REG);         /* Select the LCD display command register                      */
    DispDataWr(DISP_CMD_CLS);          /* Send command to LCD display to clear the display             */
    DispDly_uS(2000);                  /* Delay at least  2 mS                                         */
    DispUnlock();
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                     POSITION THE CURSOR (Internal)
*
* Description : This function positions the cursor into the LCD buffer
* Arguments   : 'row'   is the row    position of the cursor in the LCD Display
*                       'row' can be a value from 0 to 'DispMaxRows - 1'
*               'col'   is the column position of the cursor in the LCD Display
*                       'col' can be a value from 0 to 'DispMaxCols - 1'
* Returns     : none
*********************************************************************************************************
*/

static  void  DispCursorSet (CPU_INT08U row, CPU_INT08U col)
{
    DispSel(DISP_SEL_CMD_REG);                             /* Select LCD display command register      */
    switch (row) {
        case 0:
             if (DispMaxRows == 1) {                       /* Handle special case when only one line   */
                 if (col < (DispMaxCols >> 1)) {
                     DispDataWr(0x80 + col);               /* First  half of the line starts at 0x80   */
                 } else {                                  /* Second half of the line starts at 0xC0   */
                     DispDataWr(0xC0 + col - (DispMaxCols >> 1));
                 }
             } else {
                 DispDataWr(0x80 + col);                   /* Select LCD's display line 1              */
             }
             break;

        case 1:
             DispDataWr(0xC0 + col);                       /* Select LCD's display line 2              */
             break;

        case 2:
             DispDataWr(0x80 + DispMaxCols + col);         /* Select LCD's display line 3              */
             break;

        case 3:
             DispDataWr(0xC0 + DispMaxCols + col);         /* Select LCD's display line 4              */
             break;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                            DEFINE CHARACTER
*
* Description : This function defines the dot pattern for a character.
* Arguments   : 'id'    is the identifier for the desired dot pattern.
*               'pat'   is a pointer to an 8 BYTE array containing the dot pattern.
* Returns     : None.
*********************************************************************************************************
*/

void  DispDefChar (CPU_INT08U id, CPU_INT08U *pat)
{
    CPU_INT08U i;


    DispLock();
    DispSel(DISP_SEL_CMD_REG);              /* Select command register                                 */
    DispDataWr(0x40 + (id << 3));           /* Set address of CG RAM                                   */
    DispSel(DISP_SEL_DATA_REG);             /* Select the data register                                */
    for (i = 0; i < 8; i++) {
        DispDataWr(*pat++);                 /* Write pattern into CG RAM                               */
    }
    DispUnlock();
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                            DUMMY FUNCTION
*
* Description : This function doesn't do anything.  It is used to act like a NOP (i.e. No Operation) to
*               waste a few CPU cycles and thus, act as a short delay.
* Arguments   : none
* Returns     : none
*********************************************************************************************************
*/

void  DispDummy (void)
{
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                       DISPLAY A HORIZONTAL BAR
*
* Description : This function allows you to display horizontal bars (bar graphs) on the LCD module.
* Arguments   : 'row'   is the row    position of the cursor in the LCD Display
*                       'row' can be a value from 0 to 'DispMaxRows - 1'
*               'val'   is the value of the horizontal bar.  This value cannot exceed:
*                           DispMaxCols * 5
* Returns     : none
* Notes       : To use this function, you must first call DispHorBarInit()
*********************************************************************************************************
*/

void  DispHorBar (CPU_INT08U row, CPU_INT08U col, CPU_INT08U val)
{
    CPU_INT08U i;
    CPU_INT08U full;
    CPU_INT08U fract;


    full  = val / 5;                        /* Find out how many 'full' blocks to turn ON              */
    fract = val % 5;                        /* Compute portion of block                                */
    if (row < DispMaxRows && (col + full - 1) < DispMaxCols) {
        DispLock();
        i = 0;                              /* Set counter to limit column to maximum allowable column */
        DispCursorSet(row, col);            /* Position cursor at beginning of the bar graph           */
        DispSel(DISP_SEL_DATA_REG);
        while (full > 0) {                  /* Write all 'full' blocks                                 */
            DispDataWr(5);                  /* Send custom character #5 which is full block            */
            i++;                            /* Increment limit counter                                 */
            full--;
        }
        if (fract > 0) {
            DispDataWr(fract);              /* Send custom character # 'fract' (i.e. portion of block) */
        }
        DispUnlock();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      INITIALIZE HORIZONTAL BAR
*
* Description : This function is used to initialize the bar graph capability of this module.  You must
*               call this function prior to calling DispHorBar().
* Arguments   : none
* Returns     : none
*********************************************************************************************************
*/

void  DispHorBarInit (void)
{
    DispDefChar(1, &DispHorBar1[0]);
    DispDefChar(2, &DispHorBar2[0]);
    DispDefChar(3, &DispHorBar3[0]);
    DispDefChar(4, &DispHorBar4[0]);
    DispDefChar(5, &DispHorBar5[0]);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                       DISPLAY A VERTICAL BAR
*
* Description : This function allows you to display vertical bars (bar graphs) on the LCD module.
* Arguments   : 'row'   is the row    position of the cursor in the LCD Display
*                       'row' can be a value from 0 to 'DispMaxRows - 1'
*               'val'   is the value of the vertical bar.  This value cannot exceed 8 (i.e. 8 bars per character)
*
* Returns     : none
* Notes       : To use this function, you must first call DispVerBarInit()
*********************************************************************************************************
*/

void  DispVertBar (CPU_INT08U row, CPU_INT08U col, CPU_INT08U val)
{
    if (row < DispMaxRows && col < DispMaxCols) {
        DispLock();
        DispCursorSet(row, col);            /* Position cursor at beginning of the bar graph           */
        DispSel(DISP_SEL_DATA_REG);
        switch (val) {
            case 0:
                 DispDataWr(' ');           /* Display NO bars                                         */
                 break;

            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                 DispDataWr(val - 1);       /* Display between 1 and 8 bars                            */
                 break;

            default:
                 DispDataWr(7);             /* Always display 8 bars                                   */
                 break;
        }
        DispUnlock();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      INITIALIZE VERTICAL BAR
*
* Description : This function is used to initialize the bar graph capability of this module.  You must
*               call this function prior to calling DispVerBar().
* Arguments   : none
* Returns     : none
*********************************************************************************************************
*/

void  DispVertBarInit (void)
{
    DispDefChar(0, &DispVertBar1[0]);
    DispDefChar(1, &DispVertBar2[0]);
    DispDefChar(2, &DispVertBar3[0]);
    DispDefChar(3, &DispVertBar4[0]);
    DispDefChar(4, &DispVertBar5[0]);
    DispDefChar(5, &DispVertBar6[0]);
    DispDefChar(6, &DispVertBar7[0]);
    DispDefChar(7, &DispVertBar8[0]);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      DISPLAY DRIVER INITIALIZATION
*
* Description : This function initializes the display driver.
* Arguments   : maxrows      specifies the number of lines on the display (1 to 4)
*               maxcols      specified the number of characters per line
* Returns     : None.
* Notes       : - DispInit() MUST be called only when multitasking has started.  This is because
*                 DispInit() requires time delay services from the operating system.
*               - DispInit() MUST only be called once during initialization.
*********************************************************************************************************
*/

void  DispInit (CPU_INT08U maxrows, CPU_INT08U maxcols)
{
    DispInitOS();                      /* Initialize the RTOS services                                 */

    DispInitPort();                    /* Initialize I/O ports used in display driver                  */

    DispMaxRows = maxrows;
    DispMaxCols = maxcols;

                                       /* INITIALIZE THE DISPLAY MODULE                                */
    DispSel(DISP_SEL_CMD_REG);         /* Select command register.                                     */
    DispDly_uS(50000);                 /* Delay more than 15 mS after power up                         */

#if DISP_BUS_WIDTH == 4
    DispDataWrOneNibble(DISP_CMD_FNCT_INIT8);/* Function Set: 8 bit, Only writes upper nibble          */
    DispDly_uS(5000);                  /* Busy flag cannot be checked yet!  5 FNCT writes recommended! */

    DispDataWrOneNibble(DISP_CMD_FNCT_INIT8);/* Function Set: 8 bit, Only writes upper nibble          */
    DispDly_uS(5000);                        /* Busy flag cannot be checked yet!                       */

    DispDataWrOneNibble(DISP_CMD_FNCT_INIT8);/* Function Set: 8 bit, Only writes upper nibble          */
    DispDly_uS(5000);                        /* Busy flag cannot be checked yet!                       */

    DispDataWrOneNibble(DISP_CMD_FNCT_INIT4);/* Function Set: 4 bit, Only writes upper nibble          */
    DispDly_uS(5000);                        /* Busy flag cannot be checked yet!                       */
#else
   DispDataWr(DISP_CMD_FNCT_INIT8);    /* Two lines, 1/16 duty cycle, 5x8 dots, 8 bit operation        */
   DispDly_uS(2000);                   /* 4 FNCT writes recommended in Hitachi datasheet!              */

   DispDataWr(DISP_CMD_FNCT_INIT8);    /* Two lines, 1/16 duty cycle, 5x8 dots, 8 bit operation        */
   DispDly_uS(2000);                   /* Busy flag cannot be checked yet!                             */

   DispDataWr(DISP_CMD_FNCT_INIT8);    /* Two lines, 1/16 duty cycle, 5x8 dots, 8 bit operation        */
   DispDly_uS(2000);                   /* Busy flag cannot be checked yet!                             */
#endif

    DispDataWr(DISP_CMD_FNCT);         /* Two lines, 1/16 duty cycle, 5x8 dots, Operation Mode         */
    DispDly_uS(2000);                  /* Optional: Busy flag can now be checked yet                   */

    DispDataWr(DISP_CMD_ON_OFF);       /* Disp ON/OFF: Display ON, cursor OFF and no BLINK character   */
    DispDly_uS(2000);                  /* Delay at least  2 mS                                         */

    DispDataWr(DISP_CMD_CLS);          /* Send command to LCD display to clear the display             */
    DispDly_uS(2000);                  /* Delay at least  2 mS                                         */

    DispDataWr(DISP_CMD_MODE);         /* Entry mode: Inc. display data address when writing           */
    DispDly_uS(2000);                  /* Delay at least  2 mS                                         */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                         DISPLAY AN ASCII STRING
*
* Description : This function is used to display an ASCII string on a line of the LCD display
* Arguments   : 'row'   is the row    position of the cursor in the LCD Display
*                       'row' can be a value from 0 to 'DispMaxRows - 1'
*               'col'   is the column position of the cursor in the LCD Display
*                       'col' can be a value from 0 to 'DispMaxCols - 1'
*               's'     is a pointer to the string to write to the display at
*                       the desired row/col.
* Returns     : none
*********************************************************************************************************
*/

void  DispStr (CPU_INT08U row, CPU_INT08U col, CPU_INT08U *s)
{
    CPU_INT08U i;


    if (row < DispMaxRows && col < DispMaxCols) {
        DispLock();
        DispCursorSet(row, col);            /* Position cursor at ROW/COL                              */
        DispSel(DISP_SEL_DATA_REG);
        i = col;                            /* Set counter to limit column to maximum allowable column */
        while (i < DispMaxCols && *s) {     /* Write all chars within str + limit to DispMaxCols       */
            DispDataWr(*s++);               /* Send character to LCD display                           */
            i++;                            /* Increment limit counter                                 */
        }
        DispUnlock();
    }
}
