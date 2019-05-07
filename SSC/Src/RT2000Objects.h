/**
* \addtogroup RT2000 RT2000
* @{
*/

/**
\file RT2000Objects
\author ET9300Utilities.ApplicationHandler (Version 1.3.6.0) | EthercatSSC@beckhoff.com

\brief RT2000 specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_RT2000_) && (_RT2000_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : DigitalOut process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | DigitalOut process data mapping
* @{
* \brief Object 0x1600 (DigitalOut process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
* SubIndex 2 - Reference to 0x7000.2<br>
* SubIndex 3 - Reference to 0x7000.3<br>
* SubIndex 4 - Reference to 0x7000.4<br>
* SubIndex 5 - Reference to 0x7000.5<br>
* SubIndex 6 - Reference to 0x7000.6<br>
* SubIndex 7 - Reference to 0x7000.7<br>
* SubIndex 8 - Reference to 0x7000.8<br>
* SubIndex 9 - Reference to 0x7000.9<br>
* SubIndex 10 - Reference to 0x7000.10<br>
* SubIndex 11 - Reference to 0x7000.11<br>
* SubIndex 12 - Reference to 0x7000.12<br>
* SubIndex 13 - Reference to 0x7000.13<br>
* SubIndex 14 - Reference to 0x7000.14<br>
* SubIndex 15 - Reference to 0x7000.15<br>
* SubIndex 16 - Reference to 0x7000.16<br>
* SubIndex 17 - Reference to 0x7000.17<br>
* SubIndex 18 - Reference to 0x7000.18<br>
* SubIndex 19 - Reference to 0x7000.19<br>
* SubIndex 20 - Reference to 0x7000.20<br>
* SubIndex 21 - Reference to 0x7000.21<br>
* SubIndex 22 - Reference to 0x7000.22<br>
* SubIndex 23 - Reference to 0x7000.23<br>
* SubIndex 24 - Reference to 0x7000.24<br>
* SubIndex 25 - Reference to 0x7000.25<br>
* SubIndex 26 - Reference to 0x7000.26<br>
* SubIndex 27 - Reference to 0x7000.27<br>
* SubIndex 28 - Reference to 0x7000.28<br>
* SubIndex 29 - Reference to 0x7000.29<br>
* SubIndex 30 - Reference to 0x7000.30<br>
* SubIndex 31 - Reference to 0x7000.31<br>
* SubIndex 32 - Reference to 0x7000.32<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7000.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x7000.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x7000.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x7000.7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x7000.8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex9 - Reference to 0x7000.9 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex10 - Reference to 0x7000.10 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex11 - Reference to 0x7000.11 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex12 - Reference to 0x7000.12 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex13 - Reference to 0x7000.13 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex14 - Reference to 0x7000.14 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex15 - Reference to 0x7000.15 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex16 - Reference to 0x7000.16 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex17 - Reference to 0x7000.17 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex18 - Reference to 0x7000.18 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex19 - Reference to 0x7000.19 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex20 - Reference to 0x7000.20 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex21 - Reference to 0x7000.21 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex22 - Reference to 0x7000.22 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex23 - Reference to 0x7000.23 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex24 - Reference to 0x7000.24 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex25 - Reference to 0x7000.25 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex26 - Reference to 0x7000.26 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex27 - Reference to 0x7000.27 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex28 - Reference to 0x7000.28 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex29 - Reference to 0x7000.29 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex30 - Reference to 0x7000.30 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex31 - Reference to 0x7000.31 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex32 - Reference to 0x7000.32 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "DigitalOut process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000"
"SubIndex 014\000"
"SubIndex 015\000"
"SubIndex 016\000"
"SubIndex 017\000"
"SubIndex 018\000"
"SubIndex 019\000"
"SubIndex 020\000"
"SubIndex 021\000"
"SubIndex 022\000"
"SubIndex 023\000"
"SubIndex 024\000"
"SubIndex 025\000"
"SubIndex 026\000"
"SubIndex 027\000"
"SubIndex 028\000"
"SubIndex 029\000"
"SubIndex 030\000"
"SubIndex 031\000"
"SubIndex 032\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7000.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7000.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x7000.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x7000.7 */
UINT32 SI8; /* Subindex8 - Reference to 0x7000.8 */
UINT32 SI9; /* Subindex9 - Reference to 0x7000.9 */
UINT32 SI10; /* Subindex10 - Reference to 0x7000.10 */
UINT32 SI11; /* Subindex11 - Reference to 0x7000.11 */
UINT32 SI12; /* Subindex12 - Reference to 0x7000.12 */
UINT32 SI13; /* Subindex13 - Reference to 0x7000.13 */
UINT32 SI14; /* Subindex14 - Reference to 0x7000.14 */
UINT32 SI15; /* Subindex15 - Reference to 0x7000.15 */
UINT32 SI16; /* Subindex16 - Reference to 0x7000.16 */
UINT32 SI17; /* Subindex17 - Reference to 0x7000.17 */
UINT32 SI18; /* Subindex18 - Reference to 0x7000.18 */
UINT32 SI19; /* Subindex19 - Reference to 0x7000.19 */
UINT32 SI20; /* Subindex20 - Reference to 0x7000.20 */
UINT32 SI21; /* Subindex21 - Reference to 0x7000.21 */
UINT32 SI22; /* Subindex22 - Reference to 0x7000.22 */
UINT32 SI23; /* Subindex23 - Reference to 0x7000.23 */
UINT32 SI24; /* Subindex24 - Reference to 0x7000.24 */
UINT32 SI25; /* Subindex25 - Reference to 0x7000.25 */
UINT32 SI26; /* Subindex26 - Reference to 0x7000.26 */
UINT32 SI27; /* Subindex27 - Reference to 0x7000.27 */
UINT32 SI28; /* Subindex28 - Reference to 0x7000.28 */
UINT32 SI29; /* Subindex29 - Reference to 0x7000.29 */
UINT32 SI30; /* Subindex30 - Reference to 0x7000.30 */
UINT32 SI31; /* Subindex31 - Reference to 0x7000.31 */
UINT32 SI32; /* Subindex32 - Reference to 0x7000.32 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 DigitalOutProcessDataMapping0x1600
#if defined(_RT2000_) && (_RT2000_ == 1)
={32,0x70000101,0x70000201,0x70000301,0x70000401,0x70000501,0x70000601,0x70000701,0x70000801,0x70000901,0x70000A01,0x70000B01,0x70000C01,0x70000D01,0x70000E01,0x70000F01,0x70001001,0x70001101,0x70001201,0x70001301,0x70001401,0x70001501,0x70001601,0x70001701,0x70001801,0x70001901,0x70001A01,0x70001B01,0x70001C01,0x70001D01,0x70001E01,0x70001F01,0x70002001}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1601 : Motor0 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1601 0x1601 | Motor0 process data mapping
* @{
* \brief Object 0x1601 (Motor0 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7010.1<br>
* SubIndex 2 - Reference to 0x7010.2<br>
* SubIndex 3 - Reference to 0x7010.3<br>
* SubIndex 4 - Reference to 0x7010.4<br>
* SubIndex 5 - Reference to 0x7010.5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1601[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7010.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7010.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7010.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7010.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex5 - Reference to 0x7010.5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1601[] = "Motor0 process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7010.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7010.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7010.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7010.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7010.5 */
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1601 Motor0ProcessDataMapping0x1601
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x70100110,0x70100210,0x70100310,0x70100410,0x70100510}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1602 : Motor1 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1602 0x1602 | Motor1 process data mapping
* @{
* \brief Object 0x1602 (Motor1 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7020.1<br>
* SubIndex 2 - Reference to 0x7020.2<br>
* SubIndex 3 - Reference to 0x7020.3<br>
* SubIndex 4 - Reference to 0x7020.4<br>
* SubIndex 5 - Reference to 0x7020.5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1602[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7020.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7020.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7020.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7020.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex5 - Reference to 0x7020.5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1602[] = "Motor1 process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7020.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7020.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7020.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7020.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7020.5 */
} OBJ_STRUCT_PACKED_END
TOBJ1602;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1602 Motor1ProcessDataMapping0x1602
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x70200110,0x70200210,0x70200310,0x70200410,0x70200510}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1603 : Motor2 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1603 0x1603 | Motor2 process data mapping
* @{
* \brief Object 0x1603 (Motor2 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7030.1<br>
* SubIndex 2 - Reference to 0x7030.2<br>
* SubIndex 3 - Reference to 0x7030.3<br>
* SubIndex 4 - Reference to 0x7030.4<br>
* SubIndex 5 - Reference to 0x7030.5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1603[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7030.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7030.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7030.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7030.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex5 - Reference to 0x7030.5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1603[] = "Motor2 process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7030.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7030.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7030.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7030.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7030.5 */
} OBJ_STRUCT_PACKED_END
TOBJ1603;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1603 Motor2ProcessDataMapping0x1603
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x70300110,0x70300210,0x70300310,0x70300410,0x70300510}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1604 : Motor3 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1604 0x1604 | Motor3 process data mapping
* @{
* \brief Object 0x1604 (Motor3 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7040.1<br>
* SubIndex 2 - Reference to 0x7040.2<br>
* SubIndex 3 - Reference to 0x7040.3<br>
* SubIndex 4 - Reference to 0x7040.4<br>
* SubIndex 5 - Reference to 0x7040.5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1604[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7040.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7040.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7040.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7040.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex5 - Reference to 0x7040.5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1604[] = "Motor3 process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7040.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7040.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7040.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7040.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7040.5 */
} OBJ_STRUCT_PACKED_END
TOBJ1604;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1604 Motor3ProcessDataMapping0x1604
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x70400110,0x70400210,0x70400310,0x70400410,0x70400510}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1605 : AnalogOut process data mapping
******************************************************************************/
/**
* \addtogroup 0x1605 0x1605 | AnalogOut process data mapping
* @{
* \brief Object 0x1605 (AnalogOut process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7050.1<br>
* SubIndex 2 - Reference to 0x7050.2<br>
* SubIndex 3 - Reference to 0x7050.3<br>
* SubIndex 4 - Reference to 0x7050.4<br>
* SubIndex 5 - Reference to 0x7050.5<br>
* SubIndex 6 - Reference to 0x7050.6<br>
* SubIndex 7 - Reference to 0x7050.7<br>
* SubIndex 8 - Reference to 0x7050.8<br>
* SubIndex 9 - Reference to 0x7050.9<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1605[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7050.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7050.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7050.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7050.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x7050.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x7050.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x7050.7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x7050.8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex9 - Reference to 0x7050.9 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1605[] = "AnalogOut process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7050.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7050.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7050.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7050.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7050.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x7050.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x7050.7 */
UINT32 SI8; /* Subindex8 - Reference to 0x7050.8 */
UINT32 SI9; /* Subindex9 - Reference to 0x7050.9 */
} OBJ_STRUCT_PACKED_END
TOBJ1605;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1605 AnalogOutProcessDataMapping0x1605
#if defined(_RT2000_) && (_RT2000_ == 1)
={9,0x70500110,0x70500210,0x70500310,0x70500410,0x70500510,0x70500610,0x70500710,0x70500810,0x70500910}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1606 : HighSpeedOut process data mapping
******************************************************************************/
/**
* \addtogroup 0x1606 0x1606 | HighSpeedOut process data mapping
* @{
* \brief Object 0x1606 (HighSpeedOut process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7060.1<br>
* SubIndex 2 - Reference to 0x7060.2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1606[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7060.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex2 - Reference to 0x7060.2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1606[] = "HighSpeedOut process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7060.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7060.2 */
} OBJ_STRUCT_PACKED_END
TOBJ1606;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1606 HighSpeedOutProcessDataMapping0x1606
#if defined(_RT2000_) && (_RT2000_ == 1)
={2,0x70600110,0x70600210}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : DigitalIn process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | DigitalIn process data mapping
* @{
* \brief Object 0x1A00 (DigitalIn process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.1<br>
* SubIndex 2 - Reference to 0x6000.2<br>
* SubIndex 3 - Reference to 0x6000.3<br>
* SubIndex 4 - Reference to 0x6000.4<br>
* SubIndex 5 - Reference to 0x6000.5<br>
* SubIndex 6 - Reference to 0x6000.6<br>
* SubIndex 7 - Reference to 0x6000.7<br>
* SubIndex 8 - Reference to 0x6000.8<br>
* SubIndex 9 - Reference to 0x6000.9<br>
* SubIndex 10 - Reference to 0x6000.10<br>
* SubIndex 11 - Reference to 0x6000.11<br>
* SubIndex 12 - Reference to 0x6000.12<br>
* SubIndex 13 - Reference to 0x6000.13<br>
* SubIndex 14 - Reference to 0x6000.14<br>
* SubIndex 15 - Reference to 0x6000.15<br>
* SubIndex 16 - Reference to 0x6000.16<br>
* SubIndex 17 - Reference to 0x6000.17<br>
* SubIndex 18 - Reference to 0x6000.18<br>
* SubIndex 19 - Reference to 0x6000.19<br>
* SubIndex 20 - Reference to 0x6000.20<br>
* SubIndex 21 - Reference to 0x6000.21<br>
* SubIndex 22 - Reference to 0x6000.22<br>
* SubIndex 23 - Reference to 0x6000.23<br>
* SubIndex 24 - Reference to 0x6000.24<br>
* SubIndex 25 - Reference to 0x6000.25<br>
* SubIndex 26 - Reference to 0x6000.26<br>
* SubIndex 27 - Reference to 0x6000.27<br>
* SubIndex 28 - Reference to 0x6000.28<br>
* SubIndex 29 - Reference to 0x6000.29<br>
* SubIndex 30 - Reference to 0x6000.30<br>
* SubIndex 31 - Reference to 0x6000.31<br>
* SubIndex 32 - Reference to 0x6000.32<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6000.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6000.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x6000.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x6000.7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x6000.8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex9 - Reference to 0x6000.9 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex10 - Reference to 0x6000.10 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex11 - Reference to 0x6000.11 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex12 - Reference to 0x6000.12 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex13 - Reference to 0x6000.13 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex14 - Reference to 0x6000.14 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex15 - Reference to 0x6000.15 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex16 - Reference to 0x6000.16 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex17 - Reference to 0x6000.17 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex18 - Reference to 0x6000.18 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex19 - Reference to 0x6000.19 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex20 - Reference to 0x6000.20 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex21 - Reference to 0x6000.21 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex22 - Reference to 0x6000.22 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex23 - Reference to 0x6000.23 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex24 - Reference to 0x6000.24 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex25 - Reference to 0x6000.25 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex26 - Reference to 0x6000.26 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex27 - Reference to 0x6000.27 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex28 - Reference to 0x6000.28 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex29 - Reference to 0x6000.29 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex30 - Reference to 0x6000.30 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex31 - Reference to 0x6000.31 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex32 - Reference to 0x6000.32 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "DigitalIn process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000"
"SubIndex 014\000"
"SubIndex 015\000"
"SubIndex 016\000"
"SubIndex 017\000"
"SubIndex 018\000"
"SubIndex 019\000"
"SubIndex 020\000"
"SubIndex 021\000"
"SubIndex 022\000"
"SubIndex 023\000"
"SubIndex 024\000"
"SubIndex 025\000"
"SubIndex 026\000"
"SubIndex 027\000"
"SubIndex 028\000"
"SubIndex 029\000"
"SubIndex 030\000"
"SubIndex 031\000"
"SubIndex 032\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6000.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x6000.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x6000.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x6000.7 */
UINT32 SI8; /* Subindex8 - Reference to 0x6000.8 */
UINT32 SI9; /* Subindex9 - Reference to 0x6000.9 */
UINT32 SI10; /* Subindex10 - Reference to 0x6000.10 */
UINT32 SI11; /* Subindex11 - Reference to 0x6000.11 */
UINT32 SI12; /* Subindex12 - Reference to 0x6000.12 */
UINT32 SI13; /* Subindex13 - Reference to 0x6000.13 */
UINT32 SI14; /* Subindex14 - Reference to 0x6000.14 */
UINT32 SI15; /* Subindex15 - Reference to 0x6000.15 */
UINT32 SI16; /* Subindex16 - Reference to 0x6000.16 */
UINT32 SI17; /* Subindex17 - Reference to 0x6000.17 */
UINT32 SI18; /* Subindex18 - Reference to 0x6000.18 */
UINT32 SI19; /* Subindex19 - Reference to 0x6000.19 */
UINT32 SI20; /* Subindex20 - Reference to 0x6000.20 */
UINT32 SI21; /* Subindex21 - Reference to 0x6000.21 */
UINT32 SI22; /* Subindex22 - Reference to 0x6000.22 */
UINT32 SI23; /* Subindex23 - Reference to 0x6000.23 */
UINT32 SI24; /* Subindex24 - Reference to 0x6000.24 */
UINT32 SI25; /* Subindex25 - Reference to 0x6000.25 */
UINT32 SI26; /* Subindex26 - Reference to 0x6000.26 */
UINT32 SI27; /* Subindex27 - Reference to 0x6000.27 */
UINT32 SI28; /* Subindex28 - Reference to 0x6000.28 */
UINT32 SI29; /* Subindex29 - Reference to 0x6000.29 */
UINT32 SI30; /* Subindex30 - Reference to 0x6000.30 */
UINT32 SI31; /* Subindex31 - Reference to 0x6000.31 */
UINT32 SI32; /* Subindex32 - Reference to 0x6000.32 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 DigitalInProcessDataMapping0x1A00
#if defined(_RT2000_) && (_RT2000_ == 1)
={32,0x60000101,0x60000201,0x60000301,0x60000401,0x60000501,0x60000601,0x60000701,0x60000801,0x60000901,0x60000A01,0x60000B01,0x60000C01,0x60000D01,0x60000E01,0x60000F01,0x60001001,0x60001101,0x60001201,0x60001301,0x60001401,0x60001501,0x60001601,0x60001701,0x60001801,0x60001901,0x60001A01,0x60001B01,0x60001C01,0x60001D01,0x60001E01,0x60001F01,0x60002001}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A01 : AnalogIn process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A01 0x1A01 | AnalogIn process data mapping
* @{
* \brief Object 0x1A01 (AnalogIn process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6010.1<br>
* SubIndex 2 - Reference to 0x6010.2<br>
* SubIndex 3 - Reference to 0x6010.3<br>
* SubIndex 4 - Reference to 0x6010.4<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A01[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6010.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6010.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6010.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex4 - Reference to 0x6010.4 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A01[] = "AnalogIn process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6010.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6010.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6010.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6010.4 */
} OBJ_STRUCT_PACKED_END
TOBJ1A01;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A01 AnalogInProcessDataMapping0x1A01
#if defined(_RT2000_) && (_RT2000_ == 1)
={4,0x60100110,0x60100210,0x60100310,0x60100410}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A02 : EncodeIn process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A02 0x1A02 | EncodeIn process data mapping
* @{
* \brief Object 0x1A02 (EncodeIn process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6020.1<br>
* SubIndex 2 - Reference to 0x6020.2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A02[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6020.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex2 - Reference to 0x6020.2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A02[] = "EncodeIn process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6020.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6020.2 */
} OBJ_STRUCT_PACKED_END
TOBJ1A02;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A02 EncodeInProcessDataMapping0x1A02
#if defined(_RT2000_) && (_RT2000_ == 1)
={2,0x60200110,0x60200210}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[7];  /**< \brief Subindex 1 - 7 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_RT2000_) && (_RT2000_ == 1)
={7,{0x1600,0x1601,0x1602,0x1603,0x1604,0x1605,0x1606}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[3];  /**< \brief Subindex 1 - 3 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_RT2000_) && (_RT2000_ == 1)
={3,{0x1A00,0x1A01,0x1A02}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : DigitalIn
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | DigitalIn
* @{
* \brief Object 0x6000 (DigitalIn) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - DI0<br>
* SubIndex 2 - DI1<br>
* SubIndex 3 - DI2<br>
* SubIndex 4 - DI3<br>
* SubIndex 5 - DI4<br>
* SubIndex 6 - DI5<br>
* SubIndex 7 - DI6<br>
* SubIndex 8 - DI7<br>
* SubIndex 9 - DI8<br>
* SubIndex 10 - DI9<br>
* SubIndex 11 - DI10<br>
* SubIndex 12 - DI11<br>
* SubIndex 13 - DI12<br>
* SubIndex 14 - DI13<br>
* SubIndex 15 - DI14<br>
* SubIndex 16 - DI15<br>
* SubIndex 17 - DI16<br>
* SubIndex 18 - DI17<br>
* SubIndex 19 - DI18<br>
* SubIndex 20 - DI19<br>
* SubIndex 21 - DI20<br>
* SubIndex 22 - DI21<br>
* SubIndex 23 - DI22<br>
* SubIndex 24 - DI23<br>
* SubIndex 25 - DI24<br>
* SubIndex 26 - DI25<br>
* SubIndex 27 - DI26<br>
* SubIndex 28 - DI27<br>
* SubIndex 29 - DI28<br>
* SubIndex 30 - DI29<br>
* SubIndex 31 - DI30<br>
* SubIndex 32 - DI31<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - DI0 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - DI1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - DI2 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex4 - DI3 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex5 - DI4 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex6 - DI5 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex7 - DI6 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex8 - DI7 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex9 - DI8 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex10 - DI9 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex11 - DI10 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex12 - DI11 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex13 - DI12 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex14 - DI13 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex15 - DI14 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex16 - DI15 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex17 - DI16 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex18 - DI17 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex19 - DI18 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex20 - DI19 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex21 - DI20 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex22 - DI21 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex23 - DI22 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex24 - DI23 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex25 - DI24 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex26 - DI25 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex27 - DI26 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex28 - DI27 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex29 - DI28 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex30 - DI29 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex31 - DI30 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }}; /* Subindex32 - DI31 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "DigitalIn\000"
"DI0\000"
"DI1\000"
"DI2\000"
"DI3\000"
"DI4\000"
"DI5\000"
"DI6\000"
"DI7\000"
"DI8\000"
"DI9\000"
"DI10\000"
"DI11\000"
"DI12\000"
"DI13\000"
"DI14\000"
"DI15\000"
"DI16\000"
"DI17\000"
"DI18\000"
"DI19\000"
"DI20\000"
"DI21\000"
"DI22\000"
"DI23\000"
"DI24\000"
"DI25\000"
"DI26\000"
"DI27\000"
"DI28\000"
"DI29\000"
"DI30\000"
"DI31\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
BOOLEAN(DI0); /* Subindex1 - DI0 */
BOOLEAN(DI1); /* Subindex2 - DI1 */
BOOLEAN(DI2); /* Subindex3 - DI2 */
BOOLEAN(DI3); /* Subindex4 - DI3 */
BOOLEAN(DI4); /* Subindex5 - DI4 */
BOOLEAN(DI5); /* Subindex6 - DI5 */
BOOLEAN(DI6); /* Subindex7 - DI6 */
BOOLEAN(DI7); /* Subindex8 - DI7 */
BOOLEAN(DI8); /* Subindex9 - DI8 */
BOOLEAN(DI9); /* Subindex10 - DI9 */
BOOLEAN(DI10); /* Subindex11 - DI10 */
BOOLEAN(DI11); /* Subindex12 - DI11 */
BOOLEAN(DI12); /* Subindex13 - DI12 */
BOOLEAN(DI13); /* Subindex14 - DI13 */
BOOLEAN(DI14); /* Subindex15 - DI14 */
BOOLEAN(DI15); /* Subindex16 - DI15 */
BOOLEAN(DI16); /* Subindex17 - DI16 */
BOOLEAN(DI17); /* Subindex18 - DI17 */
BOOLEAN(DI18); /* Subindex19 - DI18 */
BOOLEAN(DI19); /* Subindex20 - DI19 */
BOOLEAN(DI20); /* Subindex21 - DI20 */
BOOLEAN(DI21); /* Subindex22 - DI21 */
BOOLEAN(DI22); /* Subindex23 - DI22 */
BOOLEAN(DI23); /* Subindex24 - DI23 */
BOOLEAN(DI24); /* Subindex25 - DI24 */
BOOLEAN(DI25); /* Subindex26 - DI25 */
BOOLEAN(DI26); /* Subindex27 - DI26 */
BOOLEAN(DI27); /* Subindex28 - DI27 */
BOOLEAN(DI28); /* Subindex29 - DI28 */
BOOLEAN(DI29); /* Subindex30 - DI29 */
BOOLEAN(DI30); /* Subindex31 - DI30 */
BOOLEAN(DI31); /* Subindex32 - DI31 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 DigitalIn0x6000
#if defined(_RT2000_) && (_RT2000_ == 1)
={32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6010 : AnalogIn
******************************************************************************/
/**
* \addtogroup 0x6010 0x6010 | AnalogIn
* @{
* \brief Object 0x6010 (AnalogIn) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - AI0<br>
* SubIndex 2 - AI1<br>
* SubIndex 3 - AI2<br>
* SubIndex 4 - AI3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6010[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - AI0 */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - AI1 */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - AI2 */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }}; /* Subindex4 - AI3 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6010[] = "AnalogIn\000"
"AI0\000"
"AI1\000"
"AI2\000"
"AI3\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT16 AI0; /* Subindex1 - AI0 */
INT16 AI1; /* Subindex2 - AI1 */
INT16 AI2; /* Subindex3 - AI2 */
INT16 AI3; /* Subindex4 - AI3 */
} OBJ_STRUCT_PACKED_END
TOBJ6010;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6010 AnalogIn0x6010
#if defined(_RT2000_) && (_RT2000_ == 1)
={4,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6020 : EncodeIn
******************************************************************************/
/**
* \addtogroup 0x6020 0x6020 | EncodeIn
* @{
* \brief Object 0x6020 (EncodeIn) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - ENCODE1<br>
* SubIndex 2 - ENCODE2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6020[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - ENCODE1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - ENCODE2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6020[] = "EncodeIn\000"
"ENCODE1\000"
"ENCODE2\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 ENCODE1; /* Subindex1 - ENCODE1 */
UINT16 ENCODE2; /* Subindex2 - ENCODE2 */
} OBJ_STRUCT_PACKED_END
TOBJ6020;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6020 EncodeIn0x6020
#if defined(_RT2000_) && (_RT2000_ == 1)
={2,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : DigitalOut
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | DigitalOut
* @{
* \brief Object 0x7000 (DigitalOut) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - DO0<br>
* SubIndex 2 - DO1<br>
* SubIndex 3 - DO2<br>
* SubIndex 4 - DO3<br>
* SubIndex 5 - DO4<br>
* SubIndex 6 - DO5<br>
* SubIndex 7 - DO6<br>
* SubIndex 8 - DO7<br>
* SubIndex 9 - DO8<br>
* SubIndex 10 - DO9<br>
* SubIndex 11 - DO10<br>
* SubIndex 12 - DO11<br>
* SubIndex 13 - DO12<br>
* SubIndex 14 - DO13<br>
* SubIndex 15 - DO14<br>
* SubIndex 16 - DO15<br>
* SubIndex 17 - DO16<br>
* SubIndex 18 - DO17<br>
* SubIndex 19 - DO18<br>
* SubIndex 20 - DO19<br>
* SubIndex 21 - DO20<br>
* SubIndex 22 - DO21<br>
* SubIndex 23 - DO22<br>
* SubIndex 24 - DO23<br>
* SubIndex 25 - DO24<br>
* SubIndex 26 - DO25<br>
* SubIndex 27 - DO26<br>
* SubIndex 28 - DO27<br>
* SubIndex 29 - DO28<br>
* SubIndex 30 - DO29<br>
* SubIndex 31 - DO30<br>
* SubIndex 32 - DO31<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - DO0 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - DO1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - DO2 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - DO3 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - DO4 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - DO5 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - DO6 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex8 - DO7 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex9 - DO8 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex10 - DO9 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex11 - DO10 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex12 - DO11 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex13 - DO12 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex14 - DO13 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex15 - DO14 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex16 - DO15 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex17 - DO16 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex18 - DO17 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex19 - DO18 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex20 - DO19 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex21 - DO20 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex22 - DO21 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex23 - DO22 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex24 - DO23 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex25 - DO24 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex26 - DO25 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex27 - DO26 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex28 - DO27 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex29 - DO28 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex30 - DO29 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex31 - DO30 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }}; /* Subindex32 - DO31 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "DigitalOut\000"
"DO0\000"
"DO1\000"
"DO2\000"
"DO3\000"
"DO4\000"
"DO5\000"
"DO6\000"
"DO7\000"
"DO8\000"
"DO9\000"
"DO10\000"
"DO11\000"
"DO12\000"
"DO13\000"
"DO14\000"
"DO15\000"
"DO16\000"
"DO17\000"
"DO18\000"
"DO19\000"
"DO20\000"
"DO21\000"
"DO22\000"
"DO23\000"
"DO24\000"
"DO25\000"
"DO26\000"
"DO27\000"
"DO28\000"
"DO29\000"
"DO30\000"
"DO31\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
BOOLEAN(DO0); /* Subindex1 - DO0 */
BOOLEAN(DO1); /* Subindex2 - DO1 */
BOOLEAN(DO2); /* Subindex3 - DO2 */
BOOLEAN(DO3); /* Subindex4 - DO3 */
BOOLEAN(DO4); /* Subindex5 - DO4 */
BOOLEAN(DO5); /* Subindex6 - DO5 */
BOOLEAN(DO6); /* Subindex7 - DO6 */
BOOLEAN(DO7); /* Subindex8 - DO7 */
BOOLEAN(DO8); /* Subindex9 - DO8 */
BOOLEAN(DO9); /* Subindex10 - DO9 */
BOOLEAN(DO10); /* Subindex11 - DO10 */
BOOLEAN(DO11); /* Subindex12 - DO11 */
BOOLEAN(DO12); /* Subindex13 - DO12 */
BOOLEAN(DO13); /* Subindex14 - DO13 */
BOOLEAN(DO14); /* Subindex15 - DO14 */
BOOLEAN(DO15); /* Subindex16 - DO15 */
BOOLEAN(DO16); /* Subindex17 - DO16 */
BOOLEAN(DO17); /* Subindex18 - DO17 */
BOOLEAN(DO18); /* Subindex19 - DO18 */
BOOLEAN(DO19); /* Subindex20 - DO19 */
BOOLEAN(DO20); /* Subindex21 - DO20 */
BOOLEAN(DO21); /* Subindex22 - DO21 */
BOOLEAN(DO22); /* Subindex23 - DO22 */
BOOLEAN(DO23); /* Subindex24 - DO23 */
BOOLEAN(DO24); /* Subindex25 - DO24 */
BOOLEAN(DO25); /* Subindex26 - DO25 */
BOOLEAN(DO26); /* Subindex27 - DO26 */
BOOLEAN(DO27); /* Subindex28 - DO27 */
BOOLEAN(DO28); /* Subindex29 - DO28 */
BOOLEAN(DO29); /* Subindex30 - DO29 */
BOOLEAN(DO30); /* Subindex31 - DO30 */
BOOLEAN(DO31); /* Subindex32 - DO31 */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 DigitalOut0x7000
#if defined(_RT2000_) && (_RT2000_ == 1)
={32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7010 : Motor0
******************************************************************************/
/**
* \addtogroup 0x7010 0x7010 | Motor0
* @{
* \brief Object 0x7010 (Motor0) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - M0_PluseNum<br>
* SubIndex 2 - M0_Cycle<br>
* SubIndex 3 - M0_Dir<br>
* SubIndex 4 - M0_EN<br>
* SubIndex 5 - M0_Toggle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7010[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - M0_PluseNum */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - M0_Cycle */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - M0_Dir */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - M0_EN */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }}; /* Subindex5 - M0_Toggle */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7010[] = "Motor0\000"
"M0_PluseNum\000"
"M0_Cycle\000"
"M0_Dir\000"
"M0_EN\000"
"M0_Toggle\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT16 M0_PluseNum; /* Subindex1 - M0_PluseNum */
UINT16 M0_Cycle; /* Subindex2 - M0_Cycle */
UINT16 M0_Dir; /* Subindex3 - M0_Dir */
UINT16 M0_EN; /* Subindex4 - M0_EN */
UINT16 M0_Toggle; /* Subindex5 - M0_Toggle */
} OBJ_STRUCT_PACKED_END
TOBJ7010;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7010 Motor00x7010
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7020 : Motor1
******************************************************************************/
/**
* \addtogroup 0x7020 0x7020 | Motor1
* @{
* \brief Object 0x7020 (Motor1) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - M1_PluseNum<br>
* SubIndex 2 - M1_Cycle<br>
* SubIndex 3 - M1_Dir<br>
* SubIndex 4 - M1_EN<br>
* SubIndex 5 - M1_Toggle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7020[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - M1_PluseNum */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - M1_Cycle */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - M1_Dir */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - M1_EN */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }}; /* Subindex5 - M1_Toggle */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7020[] = "Motor1\000"
"M1_PluseNum\000"
"M1_Cycle\000"
"M1_Dir\000"
"M1_EN\000"
"M1_Toggle\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT16 M1_PluseNum; /* Subindex1 - M1_PluseNum */
UINT16 M1_Cycle; /* Subindex2 - M1_Cycle */
UINT16 M1_Dir; /* Subindex3 - M1_Dir */
UINT16 M1_EN; /* Subindex4 - M1_EN */
UINT16 M1_Toggle; /* Subindex5 - M1_Toggle */
} OBJ_STRUCT_PACKED_END
TOBJ7020;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7020 Motor10x7020
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7030 : Motor2
******************************************************************************/
/**
* \addtogroup 0x7030 0x7030 | Motor2
* @{
* \brief Object 0x7030 (Motor2) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - M2_PluseNum<br>
* SubIndex 2 - M2_Cycle<br>
* SubIndex 3 - M2_Dir<br>
* SubIndex 4 - M2_EN<br>
* SubIndex 5 - M2_Toggle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7030[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - M2_PluseNum */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - M2_Cycle */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - M2_Dir */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - M2_EN */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }}; /* Subindex5 - M2_Toggle */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7030[] = "Motor2\000"
"M2_PluseNum\000"
"M2_Cycle\000"
"M2_Dir\000"
"M2_EN\000"
"M2_Toggle\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT16 M2_PluseNum; /* Subindex1 - M2_PluseNum */
UINT16 M2_Cycle; /* Subindex2 - M2_Cycle */
UINT16 M2_Dir; /* Subindex3 - M2_Dir */
UINT16 M2_EN; /* Subindex4 - M2_EN */
UINT16 M2_Toggle; /* Subindex5 - M2_Toggle */
} OBJ_STRUCT_PACKED_END
TOBJ7030;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7030 Motor20x7030
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7040 : Motor3
******************************************************************************/
/**
* \addtogroup 0x7040 0x7040 | Motor3
* @{
* \brief Object 0x7040 (Motor3) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - M3_PluseNum<br>
* SubIndex 2 - M3_Cycle<br>
* SubIndex 3 - M3_Dir<br>
* SubIndex 4 - M3_EN<br>
* SubIndex 5 - M3_Toggle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7040[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - M3_PluseNum */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - M3_Cycle */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - M3_Dir */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - M3_EN */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }}; /* Subindex5 - M3_Toggle */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7040[] = "Motor3\000"
"M3_PluseNum\000"
"M3_Cycle\000"
"M3_Dir\000"
"M3_EN\000"
"M3_Toggle\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT16 M3_PluseNum; /* Subindex1 - M3_PluseNum */
UINT16 M3_Cycle; /* Subindex2 - M3_Cycle */
UINT16 M3_Dir; /* Subindex3 - M3_Dir */
UINT16 M3_EN; /* Subindex4 - M3_EN */
UINT16 M3_Toggle; /* Subindex5 - M3_Toggle */
} OBJ_STRUCT_PACKED_END
TOBJ7040;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7040 Motor30x7040
#if defined(_RT2000_) && (_RT2000_ == 1)
={5,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7050 : AnalogOut
******************************************************************************/
/**
* \addtogroup 0x7050 0x7050 | AnalogOut
* @{
* \brief Object 0x7050 (AnalogOut) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - AO0<br>
* SubIndex 2 - AO0_Update<br>
* SubIndex 3 - AO1<br>
* SubIndex 4 - AO1_Update<br>
* SubIndex 5 - AO2<br>
* SubIndex 6 - AO2_Update<br>
* SubIndex 7 - AO3<br>
* SubIndex 8 - AO3_Update<br>
* SubIndex 9 - AI_Update<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7050[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - AO0 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex2 - AO0_Update */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - AO1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex4 - AO1_Update */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - AO2 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex6 - AO2_Update */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - AO3 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex8 - AO3_Update */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex9 - AI_Update */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7050[] = "AnalogOut\000"
"AO0\000"
"AO0_Update\000"
"AO1\000"
"AO1_Update\000"
"AO2\000"
"AO2_Update\000"
"AO3\000"
"AO3_Update\000"
"AI_Update\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT16 AO0; /* Subindex1 - AO0 */
UINT16 AO0_Update; /* Subindex2 - AO0_Update */
INT16 AO1; /* Subindex3 - AO1 */
UINT16 AO1_Update; /* Subindex4 - AO1_Update */
INT16 AO2; /* Subindex5 - AO2 */
UINT16 AO2_Update; /* Subindex6 - AO2_Update */
INT16 AO3; /* Subindex7 - AO3 */
UINT16 AO3_Update; /* Subindex8 - AO3_Update */
UINT16 AI_Update; /* Subindex9 - AI_Update */
} OBJ_STRUCT_PACKED_END
TOBJ7050;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7050 AnalogOut0x7050
#if defined(_RT2000_) && (_RT2000_ == 1)
={9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7060 : HighSpeedOut
******************************************************************************/
/**
* \addtogroup 0x7060 0x7060 | HighSpeedOut
* @{
* \brief Object 0x7060 (HighSpeedOut) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - HSIO0<br>
* SubIndex 2 - HSIO1<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7060[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - HSIO0 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_TXPDOMAPPING }}; /* Subindex2 - HSIO1 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7060[] = "HighSpeedOut\000"
"HSIO0\000"
"HSIO1\000\377";
#endif //#ifdef _OBJD_

#ifndef _RT2000_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 HSIO0; /* Subindex1 - HSIO0 */
UINT16 HSIO1; /* Subindex2 - HSIO1 */
} OBJ_STRUCT_PACKED_END
TOBJ7060;
#endif //#ifndef _RT2000_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7060 HighSpeedOut0x7060
#if defined(_RT2000_) && (_RT2000_ == 1)
={2,0x00,0x00}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 32 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &DigitalOutProcessDataMapping0x1600, NULL , NULL , 0x0000 },
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &Motor0ProcessDataMapping0x1601, NULL , NULL , 0x0000 },
/* Object 0x1602 */
{NULL , NULL ,  0x1602 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1602 , aName0x1602 , &Motor1ProcessDataMapping0x1602, NULL , NULL , 0x0000 },
/* Object 0x1603 */
{NULL , NULL ,  0x1603 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1603 , aName0x1603 , &Motor2ProcessDataMapping0x1603, NULL , NULL , 0x0000 },
/* Object 0x1604 */
{NULL , NULL ,  0x1604 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1604 , aName0x1604 , &Motor3ProcessDataMapping0x1604, NULL , NULL , 0x0000 },
/* Object 0x1605 */
{NULL , NULL ,  0x1605 , {DEFTYPE_PDOMAPPING , 9 | (OBJCODE_REC << 8)} , asEntryDesc0x1605 , aName0x1605 , &AnalogOutProcessDataMapping0x1605, NULL , NULL , 0x0000 },
/* Object 0x1606 */
{NULL , NULL ,  0x1606 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1606 , aName0x1606 , &HighSpeedOutProcessDataMapping0x1606, NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 32 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &DigitalInProcessDataMapping0x1A00, NULL , NULL , 0x0000 },
/* Object 0x1A01 */
{NULL , NULL ,  0x1A01 , {DEFTYPE_PDOMAPPING , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x1A01 , aName0x1A01 , &AnalogInProcessDataMapping0x1A01, NULL , NULL , 0x0000 },
/* Object 0x1A02 */
{NULL , NULL ,  0x1A02 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1A02 , aName0x1A02 , &EncodeInProcessDataMapping0x1A02, NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 7 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 3 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 32 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &DigitalIn0x6000, NULL , NULL , 0x0000 },
/* Object 0x6010 */
{NULL , NULL ,  0x6010 , {DEFTYPE_RECORD , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x6010 , aName0x6010 , &AnalogIn0x6010, NULL , NULL , 0x0000 },
/* Object 0x6020 */
{NULL , NULL ,  0x6020 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x6020 , aName0x6020 , &EncodeIn0x6020, NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 32 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &DigitalOut0x7000, NULL , NULL , 0x0000 },
/* Object 0x7010 */
{NULL , NULL ,  0x7010 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x7010 , aName0x7010 , &Motor00x7010, NULL , NULL , 0x0000 },
/* Object 0x7020 */
{NULL , NULL ,  0x7020 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x7020 , aName0x7020 , &Motor10x7020, NULL , NULL , 0x0000 },
/* Object 0x7030 */
{NULL , NULL ,  0x7030 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x7030 , aName0x7030 , &Motor20x7030, NULL , NULL , 0x0000 },
/* Object 0x7040 */
{NULL , NULL ,  0x7040 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x7040 , aName0x7040 , &Motor30x7040, NULL , NULL , 0x0000 },
/* Object 0x7050 */
{NULL , NULL ,  0x7050 , {DEFTYPE_RECORD , 9 | (OBJCODE_REC << 8)} , asEntryDesc0x7050 , aName0x7050 , &AnalogOut0x7050, NULL , NULL , 0x0000 },
/* Object 0x7060 */
{NULL , NULL ,  0x7060 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x7060 , aName0x7060 , &HighSpeedOut0x7060, NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _RT2000_OBJECTS_H_
