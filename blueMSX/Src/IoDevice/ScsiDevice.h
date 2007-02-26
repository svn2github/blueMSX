/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/ScsiDevice.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2007-02-26 19:16:29 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2007 Daniel Vik, white cat
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#ifndef SCSIDEVICE_H
#define SCSIDEVICE_H

#include "MsxTypes.h"

#define SCSI_TestUnitReady  0x00    // Group 0: 6bytes cdb
#define SCSI_ReZeroUnit     0x01
#define SCSI_RequestSense   0x03
#define SCSI_FormatUnit     0x04
#define SCSI_ReassignBlocks 0x07
#define SCSI_Read6          0x08
#define SCSI_Write6         0x0a
#define SCSI_Seek6          0x0b
#define SCSI_Inquiry        0x12
#define SCSI_ReserveUnit    0x16
#define SCSI_ReleaseUnit    0x17
#define SCSI_ModeSense      0x1a
#define SCSI_StartStopUnit  0x1b
#define SCSI_SendDiagnostic 0x1d

#define SCSI_Group1         0x20    // Group 1: 10bytes cdb
#define SCSI_ReadCapacity   0x25
#define SCSI_Read10         0x28
#define SCSI_Write10        0x2a
#define SCSI_Seek10         0x2b

#define SCSI_blueMSX        0x20    // special command (vendor option)

/* TODO: CD-ROM
#define SCSI Group2                 0x40
#define SCSI_ReadSubChannel         0x42
#define SCSI_ReadToc                0x43
#define SCSI_PlayAudio              0x45
#define SCSI PlayAudioMsf           0x47
#define SCSI_PlayAudioTrackIndex    0x48
#define SCSI_PlayTrackRelative      0x49
#define SCSI_PauseResume            0x4b
*/


// SCSI device type
#define SDT_DirectAccess        0x00
#define SDT_SequencialAccess    0x01
#define SDT_Printer             0x02
#define SDT_Processor           0x03
#define SDT_WriteOnce           0x04
#define SDT_CDROM               0x05
#define SDT_Scanner             0x06
#define SDT_OpticalMemory       0x07
#define SDT_MediaChanger        0x08
#define SDT_Communications      0x09
#define SDT_Undefined           0x1f

#define BIT_SCSI2           0x0001
#define BIT_SCSI2_ONLY      0x0002
#define BIT_SCSI3           0x0004

#define MODE_SCSI1          0x0000
#define MODE_SCSI2          0x0003
#define MODE_SCSI3          0x0005
#define MODE_UNITATTENTION  0x0008  // report unit attention
#define MODE_MEGASCSI       0x0010  // report disk change when call of
                                    // 'test unit ready'
#define MODE_FDS120         0x0020  // change of inquiry when inserted floppy image
#define MODE_CHECK2         0x0040  // mask to diskchange when load state
#define MODE_REMOVABLE      0x0080
#define MODE_NOVAXIS        0x0100

#define STATUS_GOOD             0
#define STATUS_CHECK_CONDITION  2

#define BUFFER_SIZE         0x4000                  // 16KB
#define BUFFER_BLOCK_SIZE   (BUFFER_SIZE / 512)

typedef enum {
    BusFree     =  0,
    Arbitration =  1,
    Selection   =  2,
    Reselection =  3,
    Command     =  4,
    Execute     =  5,
    DataIn      =  6,
    DataOut     =  7,
    Status      =  8,
    MsgOut      =  9,
    MsgIn       = 10
} PHASE;

typedef struct SCSIDEVICE SCSIDEVICE;

SCSIDEVICE* scsiDeviceCreate(int scsiId, int diskId, UInt8* buf, char* name, int type, int mode);
void scsiDeviceDestroy(SCSIDEVICE* scsi);
void scsiDeviceReset(SCSIDEVICE* scsi);
void scsiDeviceSaveState(SCSIDEVICE* scsi);
void scsiDeviceLoadState(SCSIDEVICE* scsi);

int scsiDeviceSelection(SCSIDEVICE* scsi);
int scsiDeviceExecuteCommand(SCSIDEVICE* scsi, UInt8* cdb, PHASE* phase, int* blocks);
UInt8 scsiDeviceGetStatusCode(SCSIDEVICE* scsi);
int scsiDeviceMsgOut(SCSIDEVICE* scsi, UInt8 value);
UInt8 scsiDeviceMsgIn(SCSIDEVICE* scsi);
void scsiDeviceDisconnect(SCSIDEVICE* scsi);
void scsiDeviceBusReset(SCSIDEVICE* scsi);

int scsiDeviceDataIn(SCSIDEVICE* scsi, int* blocks);
int scsiDeviceDataOut(SCSIDEVICE* scsi, int* blocks);
void scsiDeviceEnable(SCSIDEVICE* scsi, int enable);

/*
    debug routine
*/
//#define SCSIDEBUG "scsilog.txt"

#ifdef SCSIDEBUG
#include <stdio.h>

FILE* scsiDeviceLogCreate();
void scsiDeviceLogFlush();
void scsiDeviceLogClose();
#define SCSILOG(fmt) fprintf(scsiLog, fmt)
#define SCSILOG1(fmt, arg1) fprintf(scsiLog, fmt, arg1)
#define SCSILOG2(fmt, arg1, arg2) fprintf(scsiLog, fmt, arg1, arg2)
#define SCSILOG3(fmt, arg1, arg2, arg3) fprintf(scsiLog, fmt, arg1, arg2, arg3)

#else
#define scsiDeviceLogCreate() NULL
#define scsiDeviceLogFlush()
#define scsiDeviceLogClose()
#define SCSILOG(fmt)
#define SCSILOG1(fmt, arg1)
#define SCSILOG2(fmt, arg1, arg2)
#define SCSILOG3(fmt, arg1, arg2, arg3)
#endif

#endif
