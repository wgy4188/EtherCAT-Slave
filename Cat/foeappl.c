/**
\addtogroup FoE FileTransfer over EtherCAT
@{
*/

/**
\file foeappl.c
\author EthercatSSC@beckhoff.com
\brief Implementation
This file contains an example how to use the FoE services

\version 5.11

<br>Changes to version V5.10:<br>
V5.11 FOE2: FoE_Read() check File name buffer before store the requested file name, add string terminator<br>
V5.11 TEST5: send a FoE busy on a FoE read request<br>
V5.11 TEST9: "add behaviour 0x2020.7 (SDO requests on 0x3006.0 are set to pending until an FoE read request on ""UnlockSdoResp"" is received or in case that no mbx queue is supported when a new mbx request was received)"<br>
<br>Changes to version V5.0:<br>
V5.10 FOE2: Update file handling to support File sizes greater than 0x8000 Bytes (change value of "FOE_MAXDATA")<br>
<br>Changes to version V4.20:<br>
V5.0 FOE3: Add additional file name copy operation to provide name byte swapping<br>
V5.0 FOE5: Add FoE test operation (FOE_SAVE_FILES need to be disabled). On download only the files size is save. On upload a file with incrementing content and the previous downloaded size will be created.<br>
V5.0 FOE6: Save file if MBX 16Bit access is enabled<br>
<br>Changes to version V4.11:<br>
V4.20 FOE 2: Add File store compiler switch<br>
V4.20 FOE 1: Removed FILESUPPORT<br>
V4.11 FOE 1: nFileWriteOffset is now a 32bit variable to extend the maximum file size<br>
<br>Changes to version V3.20:<br>
V4.10 FOE 1-14: Filetransfer over FoE: Files can be read and stored to harddisk<br>
                      without any filesizelimitation (FILESUPPORT must defined)
*/

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/

#include "ecat_def.h"


#include "ecatslv.h"

#include "ecatfoe.h"

#define _FOEAPPL_ 1
    #include "foeappl.h"
#undef _FOEAPPL_
#define _FOEAPPL_ 0


/*-----------------------------------------------------------------------------------------
------
------    internal Types and Defines
------
-----------------------------------------------------------------------------------------*/

#define    MAX_FILE_NAME_SIZE    16

/*-----------------------------------------------------------------------------------------
------
------    Module internal function declarations
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    Module internal variable definitions
------
-----------------------------------------------------------------------------------------*/
UINT32             nFileSize;
UINT32             nFileWriteOffset;
UINT8            DataValue = 0x00; //Used to fill upload file with dummy data
/*-----------------------------------------------------------------------------------------
------
------    Functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     pName         Pointer to the name of the file
 \param     nameSize      Length of the file name
 \param     pData         Pointer to the response data
 \param     password      Password for the file read

 \return size of the data to be sent, busy or an error code
            1..FOE_MAXBUSY-101 (size of data to be sent)
            FOE_MAXBUSY-100 (0%)    (busy)
            FOE_MAXBUSY (100%) (busy)
            ECAT_FOE_ERRCODE_NOTDEFINED (error)
            ECAT_FOE_ERRCODE_NOTFOUND (error)
            ECAT_FOE_ERRCODE_ACCESS    (error)
            ECAT_FOE_ERRCODE_DISKFULL (error)
            ECAT_FOE_ERRCODE_ILLEGAL (error)
            ECAT_FOE_ERRCODE_PACKENO (error)
            ECAT_FOE_ERRCODE_EXISTS    (error)
            ECAT_FOE_ERRCODE_NOUSER    (error)

 \brief    The function starts a file reading

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 FOE_Read(UINT16 MBXMEM * pName, UINT16 nameSize, UINT16 MBXMEM * pData, UINT32 password)
{
    UINT16 size = 0;
    UINT16 i = 0;


    if(nFileSize > 0)
    {
        if ( nFileSize >= (u16SendMbxSize-SIZEOF(TFOEHEADER)-MBX_HEADER_SIZE) )
            size = (u16SendMbxSize-SIZEOF(TFOEHEADER)-MBX_HEADER_SIZE);
        else
            size = (unsigned short) nFileSize;
        
        MBXMEMSET(pData,DataValue,size);

        DataValue++;
    }
    else
    {
        return ECAT_FOE_ERRCODE_NOTFOUND;
    }
    return size;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     pName         Pointer to the name of the file
 \param     nameSize      Length of the file name
 \param     password      Password for the file read

 \return okay, busy or an error code
            0 (okay)
            ECAT_FOE_ERRCODE_NOTDEFINED (error)
            ECAT_FOE_ERRCODE_NOTFOUND (error)
            ECAT_FOE_ERRCODE_ACCESS    (error)
            ECAT_FOE_ERRCODE_DISKFULL (error)
            ECAT_FOE_ERRCODE_ILLEGAL (error)
            ECAT_FOE_ERRCODE_PACKENO (error)
            ECAT_FOE_ERRCODE_EXISTS    (error)
            ECAT_FOE_ERRCODE_NOUSER    (error)

            (no busy response shall be returned by this function.
            If the slave stack requires some time to handle the incoming data the function FOE_Data() should return busy)

 \brief    The function starts a file writing

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 FOE_Write(UINT16 MBXMEM * pName, UINT16 nameSize, UINT32 password)
{
        DataValue = 0x00;
        nFileSize = 0;
        return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     pData         Received file data
 \param 	Size          Length of received file data

 \return okay, busy or an error code
            0 (okay)
            FOE_MAXBUSY-100 (0%)    (busy)
            FOE_MAXBUSY (100%) (busy)
            ECAT_FOE_ERRCODE_NOTDEFINED (error)
            ECAT_FOE_ERRCODE_NOTFOUND (error)
            ECAT_FOE_ERRCODE_ACCESS    (error)
            ECAT_FOE_ERRCODE_DISKFULL (error)
            ECAT_FOE_ERRCODE_ILLEGAL (error)
            ECAT_FOE_ERRCODE_PACKENO (error)
            ECAT_FOE_ERRCODE_EXISTS    (error)
            ECAT_FOE_ERRCODE_NOUSER    (error)

 \brief    The function is called to write the next part of a file

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 FOE_Data(UINT16 MBXMEM * pData, UINT16 Size)
{
        if ( Size == (u16ReceiveMbxSize - MBX_HEADER_SIZE - FOE_HEADER_SIZE) )
        {
            /* FoE-Data services will follow */
            nFileWriteOffset += Size;
            return 0;
        }
        else
        {
            /* last part of the file is written */
            nFileSize = nFileWriteOffset + Size;
            nFileWriteOffset = 0;

            return FOE_ACKFINISHED;
        }


}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     fileOffset    Offset of the next file data to be sent
 \param     pData         Buffer for file data to be sent

 \return size of the data to be sent, busy or an error code
            0 (all data was sent before)
            1..MAX_FILE_SIZE (size of data to be sent)
            FOE_MAXBUSY-100 (0%)    (busy)
            FOE_MAXBUSY (100%) (busy)
            ECAT_FOE_ERRCODE_NOTDEFINED (error)
            ECAT_FOE_ERRCODE_NOTFOUND (error)
            ECAT_FOE_ERRCODE_ACCESS    (error)
            ECAT_FOE_ERRCODE_DISKFULL (error)
            ECAT_FOE_ERRCODE_ILLEGAL (error)
            ECAT_FOE_ERRCODE_PACKENO (error)
            ECAT_FOE_ERRCODE_EXISTS    (error)
            ECAT_FOE_ERRCODE_NOUSER    (error)

 \brief    The function is called when the reading of a part of a file is acknowledged

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 FOE_Ack(UINT32 fileOffset, UINT16 MBXMEM * pData)
{
    if ( fileOffset < nFileSize )
    {
        /* send next part of the file */
        UINT32 size;
        UINT32 sendSize = nFileSize-fileOffset;

        if ( sendSize >= (u16SendMbxSize-SIZEOF(TFOEHEADER)-MBX_HEADER_SIZE) )
        {
            size = (u16SendMbxSize-SIZEOF(TFOEHEADER)-MBX_HEADER_SIZE);
        }
        else
        {
            size = sendSize;
        }
        MBXMEMSET(pData,DataValue,size);

        DataValue++;
        return ((UINT16) size);
    }
    else if ( fileOffset == nFileSize )
    {
        /* file transfer is finished */
        return 0; // size = 0
    }
    else
        return ECAT_FOE_ERRCODE_ILLEGAL;

}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     done          Indicates how much of the busy action is done
 \param     fileOffset    Offset of the next file data to be sent
 \param     pData         Buffer for file data to be sent

 \return size of the data to be sent, busy or an error code
            0 (all data was sent before)
            1..MAX_FILE_SIZE (size of data to be sent)
            FOE_MAXBUSY-100 (0%)    (busy)
            FOE_MAXBUSY (100%) (busy)
            ECAT_FOE_ERRCODE_NOTDEFINED (error)
            ECAT_FOE_ERRCODE_NOTFOUND (error)
            ECAT_FOE_ERRCODE_ACCESS    (error)
            ECAT_FOE_ERRCODE_DISKFULL (error)
            ECAT_FOE_ERRCODE_ILLEGAL (error)
            ECAT_FOE_ERRCODE_PACKENO (error)
            ECAT_FOE_ERRCODE_EXISTS    (error)
            ECAT_FOE_ERRCODE_NOUSER    (error)

 \brief    The function is called when the reading of a part of a file should be repeated

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 FOE_Busy(UINT16 done, UINT32 fileOffset, UINT16 MBXMEM * pData)
{
    /* send last part again */
    return FOE_Ack(fileOffset, pData);
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     errorCode    error code

 \brief    The function is called when a file transfer is aborted from the other station

*////////////////////////////////////////////////////////////////////////////////////////

void FOE_Error(UINT32 errorCode)
{
    if ( nFileWriteOffset )
    {
        nFileWriteOffset = 0;
        nFileSize = 0;
    }
}



/** @} */

