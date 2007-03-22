/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Cdrom.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2007-03-22 20:30:48 $
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
#include "Win32Cdrom.h"
#include "ArchCdrom.h"
#include "ScsiDefs.h"
#include "Properties.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define USE_VIRTUAL_ALLOC
//#define CDROMDEBUG "cdromLog.txt"

#ifdef CDROMDEBUG
static FILE* logFd  = NULL;
static int   logCnt = 0;
#define DBGLOG(fmt) fprintf(logFd, fmt)
#define DBGLOG1(fmt, arg1) fprintf(logFd, fmt, arg1)
#define DBGLOG2(fmt, arg1, arg2) fprintf(logFd, fmt, arg1, arg2)
#define DBGLOG3(fmt, arg1, arg2, arg3) fprintf(logFd, fmt, arg1, arg2, arg3)
#else
#define DBGLOG(fmt)
#define DBGLOG1(fmt, arg1)
#define DBGLOG2(fmt, arg1, arg2)
#define DBGLOG3(fmt, arg1, arg2, arg3)
#endif

#define SCSI_IOCTL_DATA_OUT         0
#define SCSI_IOCTL_DATA_IN          1
#define SCSI_IOCTL_DATA_UNSPECIFIED 2

#define IOCTL_SCSI_PASS_THROUGH_DIRECT  0x04d014
#define IOCTL_CDROM_STOP_AUDIO          0x024008
#define IOCTL_CDROM_READ_TOC_EX         0x024054
#define CDROM_READ_TOC_EX_FORMAT_TOC    0x00

struct ArchCdrom
{
    HANDLE hDevice;
    int    keycode;
    int    cdromId;
    int    busy;
    unsigned int diskChange;
    CdromXferCompCb  xferCompCb;
    void*  ref;
};

typedef struct {
    USHORT Length;
    UCHAR  ScsiStatus;
    UCHAR  PathId;
    UCHAR  TargetId;
    UCHAR  Lun;
    UCHAR  CdbLength;
    UCHAR  SenseInfoLength;
    UCHAR  DataIn;
    ULONG  DataTransferLength;
    ULONG  TimeOutValue;
    PVOID  DataBuffer;
    ULONG  SenseInfoOffset;
    UCHAR  Cdb[16];
    ULONG  Filler;
    UCHAR  ucSenseBuf[32];
} SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER;

typedef struct {
    UCHAR  Format : 4;
    UCHAR  Reserved1 : 3; 
    UCHAR  Msf : 1;
    UCHAR  SessionTrack;
    UCHAR  Reserved2;
    UCHAR  Reserved3;
} CDROM_READ_TOC_EX;

typedef struct {
    UCHAR  Reserved;
    UCHAR  Control : 4;
    UCHAR  Adr : 4;
    UCHAR  TrackNumber;
    UCHAR  Reserved1;
    UCHAR  Address[4];
} TRACK_DATA;

typedef struct {
    UCHAR  Length[2];
    UCHAR  FirstTrack;
    UCHAR  LastTrack;
    TRACK_DATA TrackData[100];
} CDROM_TOC;

typedef struct {
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER* sptdwb;
    ArchCdrom* cdrom;
} EXECINFO;

static int driveMask      = 0;
static int driveCnt       = 0;
static int changeCnt      = 0;
static int isXferComp     = 1;
static int isBusy         = 0;
static int execId         = 0;
//static int isWinNT      = 0;
static int nBytesRead     = 0;
static int tocFlag        = 0;
static HANDLE hExecThread = NULL;
static void*      tocbuf  = NULL;
static CDROM_TOC* toc;

#ifdef CDROMDEBUG
static void winapiError(ULONG errorCode)
{
    UCHAR errorBuffer[80];
    ULONG count;

    count = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode, 0,
                          errorBuffer, sizeof(errorBuffer), NULL);

    if (count != 0) {
        DBGLOG1("%s\n", errorBuffer);
    } else {
        DBGLOG1("Format message failed.  Error: %d\n", (int)GetLastError());
    }
}
#else
#define winapiError(dmy)
#endif

void archCdromLoadState(ArchCdrom* cdrom) {}
void archCdromSaveState(ArchCdrom* cdrom) {}

/*
    Memory management for IOCTL and SCSI Pass Through Interface
    2048 bytes boundary alignment
*/
void* archCdromBufferMalloc(size_t size)
{
#ifdef USE_VIRTUAL_ALLOC
    return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
    void* ptr = calloc(1, size + 2048 + 0x10);
    void* newPtr;
    unsigned int* p;

    if (ptr == NULL) {
        return NULL;
    }
    newPtr = (void*)((unsigned int)(ptr + 2048 + 0x10) & ~2047);
    p  = (unsigned int*)(newPtr - 0x10);
    *p = (unsigned int)ptr;
    return newPtr;
#endif
}

void archCdromBufferFree(void* ptr)
{
#ifdef USE_VIRTUAL_ALLOC
    VirtualFree(ptr, 0, MEM_RELEASE);
#else
    unsigned int* p;

    if (ptr) {
        ptr = ptr - 0x10;
        p = (unsigned int*)ptr;
        free((void*)*p);
    }
#endif
}

static void threadClose()
{
    if (hExecThread) {
        WaitForSingleObject(hExecThread, INFINITE);
        CloseHandle(hExecThread);
        execId = 0;
        hExecThread = NULL;
        DBGLOG("thread close\n");
        isBusy         = 0;
        isXferComp     = 1;
        //bThreadInitialized = FALSE;
    }
}

ArchCdrom* archCdromCreate(CdromXferCompCb xferCompCb, void* ref)
{
    ArchCdrom*  cdrom;
    HANDLE      hDevice;
    DiskdriveProperties* prop;
    char        str[16];
    OSVERSIONINFO osInfo;

#ifdef CDROMDEBUG
    if (!logCnt) {
        logFd = fopen(CDROMDEBUG, "w");
    }
    logCnt++;
#endif
    driveMask = 0;
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (GetVersionEx(&osInfo) && osInfo.dwMajorVersion < 5) {
        return NULL;
    }

    //isWinNT = 1;
    DBGLOG("cdrom create\n");
    prop = &propGetGlobalProperties()->diskdrive;
    if (prop->cdromMethod != P_CDROM_DRVIOCTL) {
        return NULL;
    }

    sprintf(str, "%c:\\", prop->cdromDrive);
    if (GetDriveType(str) != DRIVE_CDROM) {
        return NULL;
    }

    sprintf(str, "\\\\.\\%c:", prop->cdromDrive);
    DBGLOG1("cdrom open: %s\n", str);

    hDevice = CreateFile(str, GENERIC_READ | GENERIC_WRITE,
                          FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    cdrom = calloc(1, sizeof(ArchCdrom));
    cdrom->hDevice = hDevice;
    driveMask = 1 << (prop->cdromDrive - 'A');

    if (driveCnt == 0) {
        tocbuf = malloc(sizeof(CDROM_TOC) + 0x10);
#if 0 // Orignial code
        // FIXME: tocbuf is of type void* so vc fails because the size of void is unknown
        toc    = (CDROM_TOC*)((unsigned int)(tocbuf + 0x10) & ~0x0f);
#else
        // Is it correct to treat the tocbuf as a char*
        toc    = (CDROM_TOC*)((unsigned int)((char*)tocbuf + 0x10) & ~0x0f);
#endif
    }

    driveCnt++;
    cdrom->diskChange = ~0;
    cdrom->cdromId    = driveCnt;
    cdrom->xferCompCb = xferCompCb;
    cdrom->ref        = ref;

    DBGLOG("open ok\n");
    return cdrom;
}

void archCdromDestroy(ArchCdrom* cdrom)
{
    if (cdrom) {
        CloseHandle(cdrom->hDevice);

        if (--driveCnt == 0) {
            free(tocbuf);
            tocbuf    = NULL;
            tocFlag   = 0;
            driveMask = 0;
        }

        if (execId == cdrom->cdromId) {
            threadClose();
        }
        free(cdrom);
    }

#ifdef CDROMDEBUG
    if (--logCnt == 0) {
        DBGLOG("cdrom destroy\n");
        fclose(logFd);
        logFd = NULL;
    }
#endif
}

void archCdromHwReset(ArchCdrom* cdrom)
{
    if (cdrom) {
        DBGLOG("hw reset\n");
        threadClose();
        cdrom->keycode = SENSE_POWER_ON;
        cdrom->busy    = 0;
        cdrom->diskChange = ~0;
    }
}

void archCdromBusReset(ArchCdrom* cdrom)
{
    if (cdrom) {
        cdrom->keycode = SENSE_POWER_ON;
        cdrom->busy    = 0;
        cdrom->diskChange = ~0;
        if (execId == cdrom->cdromId) {
            threadClose();
        }
    }
}

void archCdromDisconnect(ArchCdrom* cdrom)
{
    if (cdrom) {
        threadClose();
        cdrom->busy = 0;
        if (execId == cdrom->cdromId) {
            threadClose();
        }
    }
}

static DWORD execCmdThread(LPVOID lpvoid)
{
    BOOL   status;
    ULONG  returned;
    UCHAR* sense;
    UCHAR* cdb;
    UInt8* buf;
    int    stop = 0;
    int    lba, s, track;
    ArchCdrom* cdrom;
    EXECINFO* execInfo;
    TRACK_DATA* td;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER* sptdwb;
    CDROM_READ_TOC_EX  tocex = { CDROM_READ_TOC_EX_FORMAT_TOC, 0, 0, 1, 0, 0};

    execInfo = (EXECINFO*)lpvoid;
    sptdwb   = execInfo->sptdwb;
    cdrom    = execInfo->cdrom;
    cdb      = sptdwb->Cdb;
    buf      = sptdwb->DataBuffer;

    switch (cdb[0]) {
    case SCSIOP_REZERO_UNIT:
        stop = 1;
        break;

    case SCSIOP_START_STOP_UNIT:
        if (cdb[4] == 0) {
            stop = 1;
        }
        break;

    case SCSIOP_PLAY_AUDIO:
        {
            int i = 9;
            UCHAR* p;
            stop = 1;
            p = &cdb[1];
            while (i) {
                if (*p) {
                    stop = 0;
                    break;
                }
                p++;
                i--;
            }
        }
        break;

    // convert track to msf (some drives need this)
    case SCSIOP_PLAY_TRACK_INDEX:
        DBGLOG("play track\n");
        if (!tocFlag) {
            status = DeviceIoControl(cdrom->hDevice, IOCTL_CDROM_STOP_AUDIO,
                                     NULL, 0, NULL, 0, &returned, FALSE);
            if (!status) break;

            status = DeviceIoControl(cdrom->hDevice, IOCTL_CDROM_READ_TOC_EX,
                                     &tocex, sizeof(CDROM_READ_TOC_EX),
                                     toc, sizeof(CDROM_TOC),
                                     &returned, FALSE);
            if (!status) break;
            tocFlag = 1;
        }

        cdb[0] = SCSIOP_PLAY_AUDIO_MSF;
        track = (int)cdb[4];
        if (track == 0 || track > toc->LastTrack || track > 99) {
            track = toc->LastTrack + 1;
        }
        td = &toc->TrackData[track - 1];
        lba = (int)(td->Address[0] << 24) + (int)(td->Address[1] << 16) +
              (int)(td->Address[2] << 8)  + (int)td->Address[3] + 150;
        s = lba / 75;
        cdb[3] = (UCHAR)(s / 60 & 0xff);
        cdb[4] = s % 60;
        cdb[5] = lba % 75;

        track = (int)cdb[7];
        if (track == 0 || track > toc->LastTrack || track > 99) {
            track = toc->LastTrack;
        }
        td = &toc->TrackData[track];
        lba = (int)(td->Address[0] << 24) + (int)(td->Address[1] << 16) +
              (int)(td->Address[2] << 8)  + (int)td->Address[3] + 150 - 1;
        s = lba / 75;
        cdb[6] = (UCHAR)(s / 60 & 0xff);
        cdb[7] = s % 60;
        cdb[8] = lba % 75;

        break;
    }

    do {
        BOOL bugpatch = FALSE;

        if (stop) {
            status = DeviceIoControl(cdrom->hDevice, IOCTL_CDROM_STOP_AUDIO,
                                     NULL, 0, NULL, 0, &returned, FALSE);
            if (status == TRUE) {
                cdrom->keycode = 0;
                break;
            }
            cdrom->keycode = SENSE_INVALID_COMMAND_CODE;
            break;
        }

        // bug evasion of windows 2000 (KB259573)
        if (sptdwb->DataTransferLength == 1) {
            sptdwb->DataTransferLength = 2;
            bugpatch = TRUE;
        }

        status = DeviceIoControl(cdrom->hDevice, IOCTL_SCSI_PASS_THROUGH_DIRECT,
                                 sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER),
                                 sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER),
                                 &returned, FALSE);

        if (status == TRUE) {

            DBGLOG3("exec: read %d, ret %X, status %d\n",
                    (int)sptdwb->DataTransferLength, (int)returned, sptdwb->ScsiStatus);

            if (sptdwb->ScsiStatus == 0) {
                cdrom->keycode = 0;
                if (bugpatch && sptdwb->DataTransferLength > 0) {
                    nBytesRead = 1;
                } else {
                    nBytesRead = sptdwb->DataTransferLength;
                }

                switch (sptdwb->Cdb[0]) {
                case SCSIOP_READ_SUB_CHANNEL:
                    if (buf[1] == 0) {
                        buf[1] = 0x15;      // unknown -> stop
                        buf[5] = 0x10;
                        buf[6] = 0x01;
                        buf[7] = 0x01;
                    }
                    break;

                case SCSIOP_INQUIRY:
                    if (buf[0] == SDT_WriteOnce) {
                        buf[0] = SDT_CDROM; // WORM -> CD-ROM
                    }
                    break;
                }
                break;
            }

            sense = sptdwb->ucSenseBuf;
            DBGLOG3("sense %X %X %X\n", (int)sense[2], (int)sense[12], (int)sense[13]);
            cdrom->keycode = (int)(sense[2] << 16) | (int)(sense[12] << 8) | (int)sense[13];
            break;
        }

        winapiError(GetLastError());
        cdrom->keycode = SENSE_INVALID_COMMAND_CODE;
    } while (0);

    if (cdrom->xferCompCb) {
        cdrom->xferCompCb(cdrom->ref, nBytesRead);
    }

    isBusy = 0;
    isXferComp = 1;
    return 0;
}

// [ret] -1 = Execute phase  (CD-ROM response waiting)
//        0 = Status phase
//    other = Transfer phase (Data In), Number of bytes read.
int archCdromExecCmd(ArchCdrom* cdrom, const UInt8* cdb, UInt8* buffer, int bufferSize)
{
    static SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    static EXECINFO execInfo;
    DWORD dwThreadID;
    ULONG tl;

    if (cdrom == NULL) {
        cdrom->keycode = SENSE_INVALID_COMMAND_CODE;
        return 0;
    }

#ifdef CDROMDEBUG
    DBGLOG1("\nexec cmd: %X\n", cdb[0]);
    fprintf(logFd, "%X %X %X %X %X %X %X %X %X %X\n",
            cdb[0],cdb[1],cdb[2],cdb[3],cdb[4],cdb[5],cdb[6],cdb[7],cdb[8],cdb[9]);
#endif

    if (isBusy) {
        cdrom->busy = 1;
        return 0;
    }
    cdrom->busy = 0;

    if (cdrom->diskChange != changeCnt) {
        if (cdb[0] != SCSIOP_INQUIRY && cdb[0] != SCSIOP_REQUEST_SENSE) {
            cdrom->diskChange = changeCnt;
            cdrom->keycode    = SENSE_POWER_ON;
            DBGLOG("Unit Attention\n");
            isXferComp = 1;
            nBytesRead = 0;
            return 0;
        }
    }

    if (cdb[0] == SCSIOP_TEST_UNIT_READY) {
        // hack the command for a high-speed response
        cdrom->keycode = SENSE_NO_SENSE;
        isXferComp = 1;
        nBytesRead = 0;
        return 0;
    }

    if (cdb[0] == SCSIOP_REQUEST_SENSE) {
        int keycode = cdrom->keycode;
        int length  = cdb[4];

        DBGLOG1("Request Sense: keycode = %X\n", keycode);
        cdrom->keycode = SENSE_NO_SENSE;

        memset(buffer + 1, 0, 17);
        if (length == 0) {
            //if (cdrom->mode & CDROM_BIT_SCSI2) {...}
            buffer[0]  = (UInt8)((keycode >> 8) & 0xff);  // Sense code
            length     = 4;
        } else {
            buffer[0]  = 0x70;
            buffer[2]  = (UInt8)((keycode >> 16) & 0xff);   // Sense key
            buffer[7]  = 10;                                // Additional sense length
            buffer[12] = (UInt8)((keycode >> 8) & 0xff);    // Additional sense code
            buffer[13] = (UInt8)(keycode & 0xff);           // Additional sense code qualifier
            if (length > 18) length = 18;
        }
        isXferComp = 1;
        nBytesRead = length;
        return length;
    }

    isBusy = 1;
    memset(&sptdwb, 0, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
    memcpy(sptdwb.Cdb, cdb, 12);

    switch (cdb[0]) {

    // convert READ6 to READ10 (some drives need this)
    case SCSIOP_READ6:
        memset(sptdwb.Cdb + 2, 0, 8);
        sptdwb.Cdb[0] = SCSIOP_READ10;
        sptdwb.Cdb[1] &= 0xe0;
        sptdwb.Cdb[3] = cdb[1] & 0x1f;
        sptdwb.Cdb[4] = cdb[2];
        sptdwb.Cdb[5] = cdb[3];
        if (cdb[4] == 0) sptdwb.Cdb[7] = 1;
        sptdwb.Cdb[8] = cdb[4];
        sptdwb.Cdb[9] = cdb[5];
        break;

    // convert Format 0 to Format 1 (some drives need this)
    // this code is not complete
    case SCSIOP_READ_SUB_CHANNEL:
        if (sptdwb.Cdb[3] == 0) {
            sptdwb.Cdb[3] = 1;
        }
        break;
    }

    sptdwb.CdbLength = cdbLength(sptdwb.Cdb[0]);
    sptdwb.Length = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, Filler);
    sptdwb.PathId = 0;
    sptdwb.TargetId = 1;
    sptdwb.Lun = 0;
    sptdwb.DataIn = SCSI_IOCTL_DATA_IN;
    sptdwb.TimeOutValue = 10;
    sptdwb.DataBuffer = buffer;
    sptdwb.SenseInfoLength = 32;
    sptdwb.SenseInfoOffset =
       offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

    // calculation of transfer length (some drives need this)
    // this code isn't complete
    cdb = sptdwb.Cdb;
    switch (sptdwb.CdbLength) {
    case 6:
        tl = (ULONG)cdb[4];
        break;
    case 12:
        tl = (ULONG)(cdb[9] << 8) + (ULONG)cdb[10];
        break;
    default:
        tl = (ULONG)(cdb[7] << 8) + (ULONG)cdb[8];
        break;
    }

    switch (cdb[0]) {
    case SCSIOP_READ10:
        tl *= 2048;
        break;

    case SCSIOP_READ_CAPACITY:
    case SCSIOP_READ_HEADER:
        tl = 8;
        break;

/*  case SCSIOP_TEST_UNIT_READY: */
    case SCSIOP_REZERO_UNIT:
    case SCSIOP_START_STOP_UNIT:
    case SCSIOP_SEEK6:
    case SCSIOP_SEEK10:
    case SCSIOP_PLAY_AUDIO:
    case SCSIOP_PLAY_AUDIO_MSF:
    case SCSIOP_PLAY_TRACK_INDEX:
    case SCSIOP_PLAY_TRACK_RELATIVE:
    case SCSIOP_PAUSE_RESUME:
        tl = 0;
        break;
    }

    if (tl > bufferSize) tl = bufferSize;
    sptdwb.DataTransferLength = tl;

    execId = cdrom->cdromId;
    isXferComp = 0;
    nBytesRead = 0;

    execInfo.cdrom  = cdrom;
    execInfo.sptdwb = &sptdwb;

#if 1
    hExecThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)execCmdThread,
                               (LPVOID)&execInfo, 0, &dwThreadID);
#else
    // single thread
    execCmdThread((LPVOID)&execInfo);
#endif
    return -1;
}

// [ret] 1 = Transfer Complete
//           transferLength = 0     Status phase
//                          = other Transfer phase (Data In)
int archCdromIsXferComplete(ArchCdrom* cdrom, int* transferLength)
{
    if (cdrom) {
        if (!isXferComp) return 0;
        threadClose();
        *transferLength = nBytesRead;
        return 1;
    }
    *transferLength = 0;
    return 1;
}

UInt8 archCdromGetStatusCode(ArchCdrom* cdrom)
{
    if (cdrom) {
        if (!cdrom->busy) {
            return cdrom->keycode ? SCSIST_CHECK_CONDITION : SCSIST_GOOD;
        }
        return SCSIST_BUSY;
    }
    return SCSIST_CHECK_CONDITION;
}

int archCdromGetSenseKeyCode(ArchCdrom* cdrom)
{
    int keycode;

    if (cdrom) {
        keycode = cdrom->keycode;
        cdrom->keycode = 0;
        return keycode;
    }
    return SENSE_INVALID_COMMAND_CODE;
}

const char* cdromGetDriveListIoctl()
{
    static int flag = 0;
    static UInt8 list[32];
    UInt8* p = list;
    char drives[128];
    OSVERSIONINFO osInfo;
    int i;

    if (flag) return list;

    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (GetVersionEx(&osInfo) && osInfo.dwMajorVersion >= 5) {
        GetLogicalDriveStrings(sizeof(drives) - 1, drives);
        i = 0;
        while (drives[i] && i < sizeof(drives)) {
            if (GetDriveType(&drives[i]) == DRIVE_CDROM) {
                *p = drives[i];
                p++;
            }
            i += 4;
        }
    }
    *p = 0;
    flag = 1;
    return list;
}

/*
const char* cdromGetDriveListAspi()
{
}
*/

void cdromOnMediaChange(DWORD unitMask)
{
    if (unitMask & driveMask) {
        changeCnt++;
        tocFlag = 0;
    }
}
