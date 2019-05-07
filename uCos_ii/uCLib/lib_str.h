/*
*********************************************************************************************************
*                                               uC/LIB
*                                       CUSTOM LIBRARY MODULES
*
*                          (c) Copyright 2004-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/LIB is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/LIB in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/LIB.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       ASCII STRING MANAGEMENT
*
* Filename      : lib_str.h
* Version       : V1.25
* Programmer(s) : ITJ
*                 JDH
*********************************************************************************************************
* Note(s)       : (1) NO compiler-supplied standard library functions are used in library or product software.
*
*                     (a) ALL standard library functions are implemented in the custom library modules :
*
*                         (1) \<Custom Library Directory>\lib*.*
*
*                         (2) \<Custom Library Directory>\Ports\<cpu>\<compiler>\lib*_a.*
*
*                               where
*                                       <Custom Library Directory>      directory path for custom library software
*                                       <cpu>                           directory name for specific processor (CPU)
*                                       <compiler>                      directory name for specific compiler
*
*                     (b) Product-specific library functions are implemented in individual products.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  LIB_STR_MODULE_PRESENT
#define  LIB_STR_MODULE_PRESENT


/*$PAGE*/
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The following common software files are located in the following directories :
*
*               (a) \<Custom Library Directory>\lib*.*
*
*               (b) (1) \<CPU-Compiler Directory>\cpu_def.h
*
*                   (2) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom   library      software
*                                   <CPU-Compiler Directory>        directory path for common   CPU-compiler software
*                                   <cpu>                           directory name for specific processor (CPU)
*                                   <compiler>                      directory name for specific compiler
*
*           (2) Compiler MUST be configured to include the '\<Custom Library Directory>\uC-LIB\',
*               '\<CPU-Compiler Directory>\' directory, & the specific CPU-compiler directory as
*               additional include path directories.
*
*           (3) NO compiler-supplied standard library functions SHOULD be used.
*
*               #### The reference to standard library header files SHOULD be removed once all custom 
*               library functions are implemented WITHOUT reference to ANY standard library function(s).
*
*               See also 'STANDARD LIBRARY MACRO'S  Note #1'.
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <app_cfg.h>

                                                                /* See Note #3.                                         */
#include  <stdlib.h>
#include  <ctype.h>
#include  <errno.h>
#include  <limits.h>
#include  <stdio.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   LIB_STR_MODULE
#define  LIB_STR_EXT
#else
#define  LIB_STR_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      MEMORY POOL CONFIGURATION
*
* Note(s) : (1) Configure LIB_STR_CFG_FP_EN to enable/disable floating point string function(s).
*********************************************************************************************************
*/
                                                                /* Configure floating point feature(s) [see Note #1] :  */
#ifndef  LIB_STR_CFG_FP_EN
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED
                                                                /*   DEF_DISABLED     Floating point functions DISABLED */
                                                                /*   DEF_ENABLED      Floating point functions ENABLED  */
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      STANDARD LIBRARY MACRO'S
*
* Note(s) : (1) NO compiler-supplied standard library functions SHOULD be used.
*
*               #### The reference to standard memory functions SHOULD be removed once all custom library 
*               functions are implemented WITHOUT reference to ANY standard library function(s).
*
*               See also 'INCLUDE FILES  Note #3'.
*********************************************************************************************************
*/

                                                                /* See Note #1.                                         */
#define  Str_IsPrint(a)                 isprint(a)

#define  Str_ToLong(a, b, c)            strtol((char *)a, (char **)b, c)
#define  Str_FmtPrint                   snprintf
#define  Str_FmtScan                    sscanf


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_SIZE_T   Str_Len      (CPU_CHAR     *pstr);



CPU_CHAR    *Str_Copy     (CPU_CHAR     *pdest,
                           CPU_CHAR     *psrc);

CPU_CHAR    *Str_Copy_N   (CPU_CHAR     *pdest,
                           CPU_CHAR     *psrc,
                           CPU_SIZE_T    len_max);


CPU_CHAR    *Str_Cat      (CPU_CHAR     *pdest,
                           CPU_CHAR     *pstr_cat);

CPU_CHAR    *Str_Cat_N    (CPU_CHAR     *pdest,
                           CPU_CHAR     *pstr_cat,
                           CPU_SIZE_T    len_max);



CPU_INT16S   Str_Cmp      (CPU_CHAR     *p1_str,
                           CPU_CHAR     *p2_str);

CPU_INT16S   Str_Cmp_N    (CPU_CHAR     *p1_str,
                           CPU_CHAR     *p2_str,
                           CPU_SIZE_T    len_max);


CPU_CHAR    *Str_Char     (CPU_CHAR     *pstr,
                           CPU_CHAR      srch_char);

CPU_CHAR    *Str_Char_N   (CPU_CHAR     *pstr,
                           CPU_SIZE_T    len_max,
                           CPU_CHAR      srch_char);

CPU_CHAR    *Str_Char_Last(CPU_CHAR     *pstr,
                           CPU_CHAR      srch_char);


CPU_CHAR    *Str_Str      (CPU_CHAR     *pstr,
                           CPU_CHAR     *srch_str);



#if (LIB_STR_CFG_FP_EN  == DEF_ENABLED)
CPU_CHAR    *Str_FmtNbr_32(CPU_FP32      nbr,
                           CPU_INT08U    nbr_dig,
                           CPU_INT08U    nbr_dp,
                           CPU_BOOLEAN   lead_zeros,
                           CPU_BOOLEAN   nul,
                           CPU_CHAR     *pstr_fmt);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  LIB_STR_CFG_FP_EN
#error  "LIB_STR_CFG_FP_EN        not #define'd in 'app_cfg.h'"
#error  "                   [MUST be  DEF_DISABLED]           "
#error  "                   [     ||  DEF_ENABLED ]           "

#elif  ((LIB_STR_CFG_FP_EN != DEF_DISABLED) && \
        (LIB_STR_CFG_FP_EN != DEF_ENABLED ))
#error  "LIB_STR_CFG_FP_EN  illegally #define'd in 'app_cfg.h'"
#error  "                   [MUST be  DEF_DISABLED]           "
#error  "                   [     ||  DEF_ENABLED ]           "
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of lib str module include.                       */

