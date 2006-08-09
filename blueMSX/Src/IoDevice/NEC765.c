/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/NEC765.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-09 14:09:48 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
******************************************************************************
*/
#include "NEC765.h"
#include "Board.h"
#include "SaveState.h"
#include "Disk.h"
#include "Led.h"
#include "FdcAudio.h"
#include <stdlib.h>
#include <string.h>


extern int diskOffset;

struct NEC765 {
    UInt8 drive;

    UInt8 mainStatus;
    UInt8 status0;
    UInt8 status1;
    UInt8 status2;
    UInt8 status3;
    UInt8 commandCode;

    int command;
    int phase;
    int phaseStep;

    UInt8 cylinderNumber;
    UInt8 side;
    UInt8 sectorNumber;
    UInt8 number;
    UInt8 currentTrack;
    UInt8 sectorsPerCylinder;

    UInt8 fillerByte;

    int    sectorSize;
    int    sectorOffset;
    UInt32 dataTransferTime;

    int    interrupt;

    UInt8  sectorBuf[4096];

    FdcAudio* fdcAudio;
};


#define CMD_UNKNOWN                 0
#define CMD_READ_DATA               1
#define CMD_WRITE_DATA              2
#define CMD_WRITE_DELETED_DATA      3
#define CMD_READ_DELETED_DATA       4
#define CMD_READ_DIAGNOSTIC         5
#define CMD_READ_ID                 6
#define CMD_FORMAT                  7
#define CMD_SCAN_EQUAL              8
#define CMD_SCAN_LOW_OR_EQUAL       9
#define CMD_SCAN_HIGH_OR_EQUAL      10
#define CMD_SEEK                    11
#define CMD_RECALIBRATE             12
#define CMD_SENSE_INTERRUPT_STATUS  13
#define CMD_SPECIFY                 14
#define CMD_SENSE_DEVICE_STATUS     15


#define PHASE_IDLE                  0
#define PHASE_COMMAND               1
#define PHASE_DATATRANSFER          2
#define PHASE_RESULT                3

#define STM_DB0    0x01
#define STM_DB1    0x02
#define STM_DB2    0x04
#define STM_DB3    0x08
#define STM_CB     0x10
#define STM_NDM    0x20
#define STM_DIO    0x40
#define STM_RQM    0x80

#define ST0_DS0    0x01
#define ST0_DS1    0x02
#define ST0_HD     0x04
#define ST0_NR     0x08
#define ST0_EC     0x10
#define ST0_SE     0x20
#define ST0_IC0    0x40
#define ST0_IC1    0x80

#define ST1_MA     0x01
#define ST1_NW     0x02
#define ST1_ND     0x04
#define ST1_OR     0x10
#define ST1_DE     0x20
#define ST1_EN     0x80

#define ST2_MD     0x01
#define ST2_BC     0x02
#define ST2_SN     0x04
#define ST2_SH     0x08
#define ST2_NC     0x10
#define ST2_DD     0x20
#define ST2_CM     0x40

#define ST3_DS0    0x01
#define ST3_DS1    0x02
#define ST3_HD     0x04
#define ST3_2S     0x08
#define ST3_TK0    0x10
#define ST3_RDY    0x20
#define ST3_WP     0x40
#define ST3_FLT    0x80

static UInt8 nec765ExecutionPhasePeek(NEC765* fdc)
{
	switch (fdc->command) {
	case CMD_READ_DATA:
		if (fdc->sectorOffset < fdc->sectorSize) {
			return fdc->sectorBuf[fdc->sectorOffset];
        }
        break;
    }
    return 0xff;
}


static UInt8 nec765ExecutionPhaseRead(NEC765* fdc)
{
	switch (fdc->command) {
	case CMD_READ_DATA:
		if (fdc->sectorOffset < fdc->sectorSize) {
			UInt8 value = fdc->sectorBuf[fdc->sectorOffset++];
    		if (fdc->sectorOffset == fdc->sectorSize) {
                fdc->phase = PHASE_RESULT;
                fdc->phaseStep = 0;
                fdc->interrupt = 1;
            }
            return value;
        }
        break;
    }

    return 0xff;
}

static UInt8 nec765ResultsPhasePeek(NEC765* fdc)
{
	switch (fdc->command) {
	case CMD_READ_DATA:
	case CMD_WRITE_DATA:
    case CMD_FORMAT:
		switch(fdc->phaseStep) {
		case 0:
            return fdc->status0;
		case 1:
            return fdc->status1;
		case 2:
            return fdc->status2;
		case 3:
            return fdc->cylinderNumber;
		case 4:
            return fdc->side;
		case 5:
            return fdc->sectorNumber;
		case 6:
            return fdc->number;
		}
		break;

    case CMD_SENSE_INTERRUPT_STATUS:
		switch (fdc->phaseStep) {
		case 0:
            return fdc->status0;
		case 1:
            return fdc->currentTrack;
		}
		break;

    case CMD_SENSE_DEVICE_STATUS:
		switch (fdc->phaseStep) {
		case 0:
            return fdc->status3;
		}
		break;
    }

    return 0xff;
}

static UInt8 nec765ResultsPhaseRead(NEC765* fdc)
{
	switch (fdc->command) {
	case CMD_READ_DATA:
	case CMD_WRITE_DATA:
    case CMD_FORMAT:
		switch	(fdc->phaseStep++) {
		case 0:
            return fdc->status0;
		case 1:
            return fdc->status1;
		case 2:
            return fdc->status2;
		case 3:
            return fdc->cylinderNumber;
		case 4:
            return fdc->side;
		case 5:
            return fdc->sectorNumber;
		case 6:
			fdc->phase       = PHASE_IDLE;
            fdc->mainStatus &= ~STM_CB;
            fdc->mainStatus &= ~STM_DIO;

            return fdc->number;
		}
		break;

    case CMD_SENSE_INTERRUPT_STATUS:
		switch (fdc->phaseStep++) {
		case 0:
            return fdc->status0;
		case 1:
			fdc->phase       = PHASE_IDLE;
            fdc->mainStatus &= ~(STM_CB | STM_DIO);

            return fdc->currentTrack;
		}
		break;

    case CMD_SENSE_DEVICE_STATUS:
		switch (fdc->phaseStep++) {
		case 0:
			fdc->phase       = PHASE_IDLE;
            fdc->mainStatus &= ~(STM_CB | STM_DIO);
            
            return fdc->status3;
		}
		break;
    }

    return 0xff;
}

void nec765IdlePhaseWrite(NEC765* fdc, UInt8 value)
{
	fdc->command = CMD_UNKNOWN;
	if ((value & 0x1f) == 0x06) fdc->command = CMD_READ_DATA;
	if ((value & 0x3f) == 0x05) fdc->command = CMD_WRITE_DATA;
	if ((value & 0x3f) == 0x09) fdc->command = CMD_WRITE_DELETED_DATA;
	if ((value & 0x1f) == 0x0c) fdc->command = CMD_READ_DELETED_DATA;
	if ((value & 0xbf) == 0x02) fdc->command = CMD_READ_DIAGNOSTIC;
	if ((value & 0xbf) == 0x0a) fdc->command = CMD_READ_ID;
	if ((value & 0xbf) == 0x0d) fdc->command = CMD_FORMAT;
	if ((value & 0x1f) == 0x11) fdc->command = CMD_SCAN_EQUAL;
	if ((value & 0x1f) == 0x19) fdc->command = CMD_SCAN_LOW_OR_EQUAL;
	if ((value & 0x1f) == 0x1d) fdc->command = CMD_SCAN_HIGH_OR_EQUAL;
	if ((value & 0xff) == 0x0f) fdc->command = CMD_SEEK;
	if ((value & 0xff) == 0x07) fdc->command = CMD_RECALIBRATE;
	if ((value & 0xff) == 0x08) fdc->command = CMD_SENSE_INTERRUPT_STATUS;
	if ((value & 0xff) == 0x03) fdc->command = CMD_SPECIFY;
	if ((value & 0xff) == 0x04) fdc->command = CMD_SENSE_DEVICE_STATUS;

    fdc->commandCode = value;

	fdc->phase       = PHASE_COMMAND;
	fdc->phaseStep   = 1;
    fdc->mainStatus |= STM_CB;
    
    switch (fdc->command) {
	case CMD_READ_DATA:
	case CMD_WRITE_DATA:
	case CMD_FORMAT:
        fdc->status0 &= ~(ST0_IC0 | ST0_IC1);
        fdc->status1 &= ~(ST1_ND | ST1_NW);
		break;

	case CMD_RECALIBRATE:
        fdc->status0 &= ~ST0_SE;
		break;

	case CMD_SENSE_INTERRUPT_STATUS:
        fdc->mainStatus |= STM_DIO;
		fdc->phase       = PHASE_RESULT;
        fdc->interrupt   = 1;
        break;

    case CMD_SEEK:
	case CMD_SPECIFY:
	case CMD_SENSE_DEVICE_STATUS:
        break;

    default:
        fdc->mainStatus &= ~STM_CB;
		fdc->phase       = PHASE_IDLE;
        fdc->interrupt   = 1;
    }
}

static void nec765CommandPhaseWrite(NEC765* fdc, UInt8 value)
{
    switch (fdc->command) {
	case CMD_READ_DATA:
	case CMD_WRITE_DATA:
		switch (fdc->phaseStep++) {
		case 0:
			break;
        case 1:
            fdc->drive = value & 0x03;
            fdc->side = (value >> 2)& 1;
            fdc->sectorSize = diskGetSectorSize(fdc->drive, fdc->side, fdc->currentTrack, 0);
            
            fdc->status0 &= ~(ST0_DS0 | ST0_DS1 | ST0_IC0 | ST0_IC1);
            fdc->status0 |= (diskPresent(fdc->drive) ? 0 : ST0_DS0) | (value & (ST0_DS0 | ST0_DS1)) |
                           (diskEnabled(fdc->drive) ? 0 : ST0_IC1);
            fdc->status3  = (value & (ST3_DS0 | ST3_DS1)) | 
                           (fdc->currentTrack == 0        ? ST3_TK0 : 0) | 
                           (diskGetSides(fdc->drive) == 2 ? ST3_HD  : 0) | 
                           (diskReadOnly(fdc->drive)      ? ST3_WP  : 0) |
                           (diskPresent(fdc->drive)       ? ST3_RDY : 0);
            break;
		case 2:
            fdc->cylinderNumber = value;
			break;
		case 4:
            fdc->sectorNumber = value;
			break;
		case 5:
            fdc->number = value;
            fdc->sectorOffset = (value == 1 && (fdc->commandCode & 0xc0) == 0x40) ? 0 : fdc->sectorSize; // FIXME
			break;
		case 8:
            if (fdc->command == CMD_READ_DATA) {
                int sectorSize;
    
        		int rv = diskReadSector(fdc->drive, fdc->sectorBuf, fdc->sectorNumber, fdc->side, 
                                        fdc->currentTrack, 0, &sectorSize);
                
                fdcAudioSetReadWrite(fdc->fdcAudio);
                boardSetFdcActive();
                if (!rv) {
                    fdc->status0 |= ST0_IC0;
                    fdc->status1 |= ST1_ND;
                }
                fdc->mainStatus |= STM_DIO;
            }
            else {
                fdc->mainStatus &= ~STM_DIO;
            }
			fdc->phase = PHASE_DATATRANSFER;
			fdc->phaseStep = 0;
            fdc->interrupt = 1;
			break;
		}
		break;

	case CMD_FORMAT:
		switch (fdc->phaseStep++) {
		case 0:
			break;
        case 1:
            fdc->drive = value & 0x03;
            fdc->side = (value >> 2)& 1;
            fdc->sectorSize = diskGetSectorSize(fdc->drive, fdc->side, fdc->currentTrack, 0);
            
            fdc->status0 &= ~(ST0_DS0 | ST0_DS1 | ST0_IC0 | ST0_IC1);
            fdc->status0 |= (diskPresent(fdc->drive) ? 0 : ST0_DS0) | (value & (ST0_DS0 | ST0_DS1)) |
                           (diskEnabled(fdc->drive) ? 0 : ST0_IC1);
            fdc->status3  = (value & (ST3_DS0 | ST3_DS1)) | 
                           (fdc->currentTrack == 0        ? ST3_TK0 : 0) | 
                           (diskGetSides(fdc->drive) == 2 ? ST3_HD  : 0) |  
                           (diskReadOnly(fdc->drive)      ? ST3_WP  : 0) |
                           (diskPresent(fdc->drive)       ? ST3_RDY : 0);
            break;
		case 2:
            fdc->number = value;
			break;
		case 3:
            fdc->sectorsPerCylinder = value;
            fdc->sectorNumber       = value;
			break;
		case 5:
            fdc->fillerByte   = value;
            fdc->sectorOffset = 0;
            fdc->mainStatus  &= ~STM_DIO;
			fdc->phase        = PHASE_DATATRANSFER;
			fdc->phaseStep    = 0;
            fdc->interrupt    = 1;
			break;
        }
        break;

	case CMD_SEEK:
		switch (fdc->phaseStep++) {
		case 0:
			break;
        case 1:
            fdc->drive = value & 0x03;
            fdc->side = (value >>2)& 1;
            
            fdc->status0 &= ~(ST0_DS0 | ST0_DS1 | ST0_IC0 | ST0_IC1);
            fdc->status0 |= (diskPresent(fdc->drive) ? 0 : ST0_DS0) | (value & (ST0_DS0 | ST0_DS1)) |
                           (diskEnabled(fdc->drive) ? 0 : ST0_IC1);
            fdc->status3  = (value & (ST3_DS0 | ST3_DS1)) | 
                           (fdc->currentTrack == 0        ? ST3_TK0 : 0) | 
                           (diskGetSides(fdc->drive) == 2 ? ST3_HD  : 0) |  
                           (diskReadOnly(fdc->drive)      ? ST3_WP  : 0) |
                           (diskPresent(fdc->drive)       ? ST3_RDY : 0);
            break;
		case 2: 
            fdc->currentTrack = value;
            fdc->status0     |= ST0_SE;
            fdc->mainStatus  &= ~STM_CB;
			fdc->phase        = PHASE_IDLE;
            fdc->interrupt    = 1;
			break;
		}
		break;

	case CMD_RECALIBRATE:
		switch (fdc->phaseStep++) {
		case 0: 
            break;
        case 1:
            fdc->drive = value & 0x03;
            
            fdc->status0 &= ~(ST0_DS0 | ST0_DS1 | ST0_IC0 | ST0_IC1);
            fdc->status0 |= (diskPresent(fdc->drive) ? 0 : ST0_DS0) | (value & (ST0_DS0 | ST0_DS1)) |
                           (diskEnabled(fdc->drive) ? 0 : ST0_IC1);
            fdc->status3  = (value & (ST3_DS0 | ST3_DS1)) | 
                           (fdc->currentTrack == 0        ? ST3_TK0 : 0) | 
                           (diskGetSides(fdc->drive) == 2 ? ST3_HD  : 0) |  
                           (diskReadOnly(fdc->drive)      ? ST3_WP  : 0) |
                           (diskPresent(fdc->drive)       ? ST3_RDY : 0);
            
            fdc->currentTrack = 0;
            fdc->status0     |= ST0_SE;
            fdc->mainStatus  &= ~STM_CB;
			fdc->phase        = PHASE_IDLE;
            fdc->interrupt    = 1;
			break;
		}
		break;

	case CMD_SPECIFY:
		switch (fdc->phaseStep++) {
		case 2:
            fdc->mainStatus &= ~STM_CB;
			fdc->phase       = PHASE_IDLE;
            fdc->interrupt   = 1;
			break;
		}
		break;

	case CMD_SENSE_DEVICE_STATUS:
		switch (fdc->phaseStep++) {
		case 1:
            fdc->drive = value & 0x03;
            fdc->side = (value >>2)& 1;
            
            fdc->status0 &= ~(ST0_DS0 | ST0_DS1 | ST0_IC0 | ST0_IC1);
            fdc->status0 |= (diskPresent(fdc->drive) ? 0 : ST0_DS0) | (value & (ST0_DS0 | ST0_DS1)) |
                           (diskEnabled(fdc->drive) ? 0 : ST0_IC1);
            fdc->status3  = (value & (ST3_DS0 | ST3_DS1)) | 
                           (fdc->currentTrack == 0        ? ST3_TK0 : 0) | 
                           (diskGetSides(fdc->drive) == 2 ? ST3_HD  : 0) |  
                           (diskReadOnly(fdc->drive)      ? ST3_WP  : 0) |
                           (diskPresent(fdc->drive)       ? ST3_RDY : 0);
            
            fdc->mainStatus |= STM_DIO;
		    fdc->phase       = PHASE_RESULT;
            fdc->phaseStep   = 0;
            fdc->interrupt   = 1;
			break;
		}
		break;
	}
}

static void nec765ExecutionPhaseWrite(NEC765* fdc, UInt8 value)
{
    int rv;

	switch (fdc->command) {
	case CMD_WRITE_DATA:
		if (fdc->sectorOffset < fdc->sectorSize) {
			fdc->sectorBuf[fdc->sectorOffset++] = value;
            
    		if (fdc->sectorOffset == fdc->sectorSize) {
                rv = diskWriteSector(fdc->drive, fdc->sectorBuf, fdc->sectorNumber, fdc->side, 
                                     fdc->currentTrack, 0);
                if (!rv) {
                    fdc->status1 |= ST1_NW;
                }

                fdcAudioSetReadWrite(fdc->fdcAudio);

                boardSetFdcActive();

                fdc->phase       = PHASE_RESULT;
                fdc->phaseStep   = 0;
                fdc->mainStatus |= STM_DIO;
            }
        }
		break;

    case CMD_FORMAT:
        switch(fdc->phaseStep & 3) {
        case 0:
            fdc->currentTrack = value;
            break;
        case 1:
            memset(fdc->sectorBuf, fdc->fillerByte, fdc->sectorSize);
            rv = diskWrite(fdc->drive, fdc->sectorBuf, fdc->sectorNumber - 1 +
                      diskGetSectorsPerTrack(fdc->drive) * (fdc->currentTrack * diskGetSides(fdc->drive) + value));
            if (!rv) {
                fdc->status1 |= ST1_NW;
            }
            boardSetFdcActive();
            break;
        case 2:
            fdc->sectorNumber = value;
            break;
        }

        if (++fdc->phaseStep == 4 * fdc->sectorsPerCylinder - 2) {
            fdc->phase       = PHASE_RESULT;
            fdc->phaseStep   = 0;
            fdc->mainStatus |= STM_DIO;
        }
        break;
	}
}

NEC765* nec765Create()
{
    NEC765* fdc = malloc(sizeof(NEC765));

    fdc->fdcAudio = fdcAudioCreate(FA_PANASONIC);

    nec765Reset(fdc);

    return fdc;
}

void nec765Destroy(NEC765* fdc)
{
    fdcAudioDestroy(fdc->fdcAudio);
    free(fdc);
}

void nec765Reset(NEC765* fdc)
{
    FdcAudio* fdcAudio = fdc->fdcAudio;
    memset(fdc, 0, sizeof(NEC765));
    fdc->fdcAudio = fdcAudio;

    fdc->mainStatus = STM_NDM | STM_RQM;

    fdc->interrupt = 0;

    ledSetFdd1(0); /* 10:10 2004/10/09 FDD LED PATCH */ 
    ledSetFdd2(0); /* 10:10 2004/10/09 FDD LED PATCH */ 

    fdcAudioReset(fdc->fdcAudio);
}

UInt8 nec765Read(NEC765* fdc)
{
    UInt8 value;
    
    fdc->interrupt = 0;

    switch (fdc->phase) {            
	case PHASE_DATATRANSFER:
        value = nec765ExecutionPhaseRead(fdc);
        fdc->dataTransferTime = boardSystemTime();
        fdc->mainStatus &= ~STM_RQM;
        return value;

	case PHASE_RESULT:
        return nec765ResultsPhaseRead(fdc);
    }
    return 0xff;
}

UInt8 nec765Peek(NEC765* fdc)
{
    switch (fdc->phase) {            
	case PHASE_DATATRANSFER:
        return nec765ExecutionPhasePeek(fdc);
	case PHASE_RESULT:
        return nec765ResultsPhasePeek(fdc);
    }
    return 0xff;
}

UInt8 nec765ReadStatus(NEC765* fdc)
{
    if (~fdc->mainStatus & STM_RQM) {
        UInt32 elapsed = boardSystemTime() - fdc->dataTransferTime;
        if (elapsed > boardFrequency() * 60 / 1000000) {
            fdc->mainStatus |= STM_RQM;
        } 
    }
    return fdc->mainStatus;
}

UInt8 nec765PeekStatus(NEC765* fdc)
{
    return fdc->mainStatus;
}

void nec765Write(NEC765* fdc, UInt8 value)
{
    //ledSetFdd1((value & 0x10) && diskEnabled(0)); /* 10:10 2004/10/09 FDD LED PATCH */ 
    //ledSetFdd2((value & 0x20) && diskEnabled(1)); /* 10:10 2004/10/09 FDD LED PATCH */ 

    switch (fdc->phase) {
	case PHASE_IDLE:
        nec765IdlePhaseWrite(fdc, value);
        break;

    case PHASE_COMMAND:
        nec765CommandPhaseWrite(fdc, value);
        break;
        
	case PHASE_DATATRANSFER:
        nec765ExecutionPhaseWrite(fdc, value);
        fdc->dataTransferTime = boardSystemTime();
        fdc->mainStatus &= ~STM_RQM;
        break;
    }
}

int nec765GetInt(NEC765* fdc)
{
    return fdc->interrupt;
}

int nec765GetIndex(NEC765* fdc)
{
    if (diskEnabled(fdc->drive)) {
        if (diskPresent(fdc->drive)) {
            if ((UInt64)160 * boardSystemTime() / boardFrequency() & 0x1e) {
			    return 1;
		    }
        }
    }
    return 0;
}

int nec765DiskChanged(NEC765* fdc, int drive)
{
    return diskChanged(drive);
}

void nec765LoadState(NEC765* fdc)
{
    SaveState* state = saveStateOpenForRead("nec765");

    fdc->drive               = (UInt8) saveStateGet(state, "drive",              0);
    fdc->mainStatus          = (UInt8) saveStateGet(state, "mainStatus",         STM_NDM | STM_RQM);
    fdc->status0             = (UInt8) saveStateGet(state, "status0",            0);
    fdc->status1             = (UInt8) saveStateGet(state, "status1",            0);
    fdc->status2             = (UInt8) saveStateGet(state, "status2",            0);
    fdc->status3             = (UInt8) saveStateGet(state, "status3",            0);
    fdc->commandCode         = (UInt8) saveStateGet(state, "commandCode",        0);
    fdc->command             =         saveStateGet(state, "command",            0);
    fdc->phase               =         saveStateGet(state, "phase",              0);
    fdc->phaseStep           =         saveStateGet(state, "phaseStep",          0);
    fdc->cylinderNumber      = (UInt8) saveStateGet(state, "cylinderNumber",     0);
    fdc->side                = (UInt8) saveStateGet(state, "side",               0);
    fdc->sectorNumber        = (UInt8) saveStateGet(state, "sectorNumber",       0);
    fdc->number              = (UInt8) saveStateGet(state, "number",             0);
    fdc->currentTrack        = (UInt8) saveStateGet(state, "currentTrack",       0);
    fdc->sectorsPerCylinder  = (UInt8) saveStateGet(state, "sectorsPerCylinder", 0);
    fdc->sectorOffset        =         saveStateGet(state, "sectorOffset",       0);
    fdc->dataTransferTime    =         saveStateGet(state, "dataTransferTime",   0);
    
    saveStateGetBuffer(state, "sectorBuf", fdc->sectorBuf, 512);

    saveStateClose(state);
}

void nec765SaveState(NEC765* fdc)
{
    SaveState* state = saveStateOpenForWrite("nec765");

    saveStateSet(state, "drive",              fdc->drive);
    saveStateSet(state, "mainStatus",         fdc->mainStatus);
    saveStateSet(state, "status0",            fdc->status0);
    saveStateSet(state, "status1",            fdc->status1);
    saveStateSet(state, "status2",            fdc->status2);
    saveStateSet(state, "status3",            fdc->status3);
    saveStateSet(state, "commandCode",        fdc->commandCode);
    saveStateSet(state, "command",            fdc->command);
    saveStateSet(state, "phase",              fdc->phase);
    saveStateSet(state, "phaseStep",          fdc->phaseStep);
    saveStateSet(state, "cylinderNumber",     fdc->cylinderNumber);
    saveStateSet(state, "side",               fdc->side);
    saveStateSet(state, "sectorNumber",       fdc->sectorNumber);
    saveStateSet(state, "number",             fdc->number);
    saveStateSet(state, "currentTrack",       fdc->currentTrack);
    saveStateSet(state, "sectorsPerCylinder", fdc->sectorsPerCylinder);
    saveStateSet(state, "sectorOffset",       fdc->sectorOffset);
    saveStateSet(state, "dataTransferTime",   fdc->dataTransferTime);
    
    saveStateSetBuffer(state, "sectorBuf", fdc->sectorBuf, 512);

    saveStateClose(state);
}

#if 0

/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/NEC765.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-09 14:09:48 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
******************************************************************************
*/

#include "NEC765.h"
#include "Board.h"
#include "SaveState.h"
#include "Disk.h"
#include "Led.h"
#include "FdcAudio.h"
#include <stdlib.h>
#include <string.h>


struct NEC765 {
    UInt8 mainStatus;
    UInt8 status0;
    UInt8 status1;
    UInt8 status2;
    UInt8 status3;

    int    phase;

    int    drive;
    int    side;

    int    sectorNumber;
    int    sectorOffset;
    int    sectorSize;
    int    commandOffset;
    int    resultOffset;
    int    resultCount;

    int    currentTrack;

    UInt8  commandRegs[9];
    UInt8  resultRegs[7];

    int    interrupt;

    UInt8  sectorBuf[0x8000];
};


#define PHASE_IDLE                  0
#define PHASE_COMMAND               1
#define PHASE_DATATRANSFER          2
#define PHASE_RESULT                3



#define CMD_READ_TRACK              2
#define CMD_SPECIFY                 3
#define CMD_SENSE_DRIVE_STATUS      4
#define CMD_WRITE_DATA              5
#define CMD_READ_DATA               6
#define CMD_RECALIBRATE             7
#define CMD_SENSE_INTERRUPT         8
#define CMD_WRITE_DELETED_DATA      9
#define CMD_READ_SECTOR_ID          10
#define CMD_READ_DELETED_DATA       12
#define CMD_FORMAT_TRACK            13
#define CMD_SEEK                    15
#define CMD_SCAN_EQUAL              17
#define CMD_SCAN_LOW_OR_EQUAL       25
#define CMD_SCAN_HIGH_OR_EQUAL      30

const UInt8 commandLength[32] =
{
    1,  // none
	1,  // none
	9,  // CMD_READ_TRACK
	3,  // CMD_SPECIFY
	2,  // CMD_SENSE_DRIVE_STATUS
	9,  // CMD_WRITE_DATA
	9,  // CMD_READ_DATA
	2,  // CMD_RECALIBRATE
	1,  // CMD_SENSE_INTERRUPT
	9,  // CMD_WRITE_DELETED_DATA
	2,  // CMD_READ_SECTOR_ID
	1,  // none
	9,  // CMD_READ_DELETED_DATA
	6,  // CMD_FORMAT_TRACK
	1,  // none
	3,  // CMD_SEEK
	1,  // none
	9,  // CMD_SCAN_EQUAL
	1,  // none
	1,  // none
	1,  // none
	1,  // none
	1,  // none
	1,  // none
	1,  // none
	9,  // CMD_SCAN_LOW_OR_EQUAL
	1,  // none
	1,  // none
	1,  // none
	1,  // none
	9,  // CMD_SCAN_HIGH_OR_EQUAL
	1   // none
};



static void createResult(NEC765* fdc)
{
    fdc->resultRegs[0] = fdc->status0;
    fdc->resultRegs[1] = fdc->status1;
    fdc->resultRegs[2] = fdc->status2;
    fdc->resultRegs[3] = fdc->commandRegs[2];
    fdc->resultRegs[4] = fdc->commandRegs[3];
    fdc->resultRegs[5] = fdc->commandRegs[4];
    fdc->resultRegs[6] = fdc->commandRegs[5];

    fdc->resultOffset = 0;
    fdc->resultCount = 7;

    fdc->mainStatus = 0xd0;
    fdc->status0 = 0;
    fdc->status1 = 0;
    fdc->status2 = 0;

    fdc->phase = PHASE_RESULT;
}

static UInt8 nec765ExecuteReadCommand(NEC765* fdc) 
{
    UInt8 value = 0;

    switch(fdc->commandRegs[0]) {
    case CMD_READ_TRACK:
        value = fdc->sectorBuf[fdc->sectorOffset++];
        if (fdc->sectorOffset == fdc->sectorSize) {
            fdc->status0 = (fdc->commandRegs[1] & 7) | 0x40;
            fdc->status1 = 0x80;
            createResult(fdc);
        }
        break;

    case CMD_READ_DATA:
        value = fdc->sectorBuf[fdc->sectorOffset++];
        if (fdc->sectorOffset == fdc->sectorSize) {
            fdc->status0 = (fdc->commandRegs[1] & 7) | 0x40;
            fdc->status1 = 0x80;
            createResult(fdc);
        }
        break;

    default:
        break;
    }

    return value;
}

static void nec765ExecuteWriteCommand(NEC765* fdc, UInt8 value)
{
    switch(fdc->commandRegs[0]) {
    case CMD_READ_TRACK:
        fdc->drive = fdc->commandRegs[1] & 3;
        fdc->side  = (fdc->commandRegs[1] >> 2) & 1;
        fdc->currentTrack = fdc->commandRegs[2];
        if (!diskPresent(fdc->drive)) {
            fdc->status0 = fdc->drive | 0xd8;
            createResult(fdc);
        }
        else {
            int sector;

            fdc->phase = PHASE_COMMAND;

            fdc->sectorSize = diskGetSectorSize(fdc->drive, fdc->side, fdc->currentTrack, 0);
            
            for (sector = 0; sector < diskGetSectorsPerTrack(fdc->drive); sector++) {
                diskReadSector(fdc->drive, fdc->sectorBuf + sector * fdc->sectorSize, sector, fdc->side, 
                            fdc->currentTrack, 0, NULL);
            }

            fdc->sectorSize *= sector;
            fdc->sectorOffset = 0;
            fdc->mainStatus = 0xf0;
        }
        break;

    case CMD_SPECIFY:
        break;

    case CMD_SENSE_DRIVE_STATUS:
        fdc->drive = fdc->commandRegs[1] & 3;
        fdc->status3 = (fdc->commandRegs[1] & 7) |
                       (fdc->commandRegs[1] & 4  ? 0x08 : 0) |
                       (fdc->currentTrack == 0   ? 0x10 : 0) |
                       (diskPresent(fdc->drive)  ? 0x20 : 0) |
                       (diskReadOnly(fdc->drive) ? 0x40 : 0);
        fdc->resultCount  = 1;
        fdc->resultOffset = 0;

        fdc->resultRegs[0] = fdc->status3;
        fdc->phase = PHASE_RESULT;
        fdc->mainStatus = 0xd0;
        break;

    case CMD_WRITE_DATA:
        if (fdc->phase != PHASE_COMMAND) { //FIXME
            fdc->drive = fdc->commandRegs[1] & 3;
            fdc->side  = (fdc->commandRegs[1] >> 2) & 1;
            fdc->currentTrack = fdc->commandRegs[2];

            fdc->phase = PHASE_COMMAND;
            if (!diskPresent(fdc->drive)) {
                fdc->status0 = fdc->drive | 0xd8;
                createResult(fdc);
            }
            else {
                fdc->sectorSize = diskGetSectorSize(fdc->drive, fdc->side, fdc->currentTrack, 0);
                fdc->sectorNumber = (fdc->commandRegs[4] - fdc->commandRegs[6]) & 0x0f;
                fdc->sectorOffset = 0;
                fdc->mainStatus = 0xb0;
            }
        }
        else {
            fdc->sectorBuf[fdc->sectorOffset++] = value;
            if (fdc->sectorOffset == fdc->sectorSize) {
                fdc->status0 = fdc->commandRegs[1] & 7;

                diskWriteSector(fdc->drive, fdc->sectorBuf, fdc->sectorNumber, fdc->side, 
                                fdc->currentTrack, 0);

                // FIXME: Check Failure
                createResult(fdc);
            }
        }
        break;

    case CMD_READ_DATA:
        fdc->drive = fdc->commandRegs[1] & 3;
        fdc->side  = (fdc->commandRegs[1] >> 2) & 1;
        fdc->currentTrack = fdc->commandRegs[2];

        if (!diskPresent(fdc->drive)) {
            fdc->status0 = fdc->drive | 0xd8;
            createResult(fdc);
        }
        else {
            fdc->phase = PHASE_COMMAND;

            fdc->sectorSize = diskGetSectorSize(fdc->drive, fdc->side, fdc->currentTrack, 0);
            fdc->sectorNumber = (fdc->commandRegs[4]) & 0x0f;
            
            diskReadSector(fdc->drive, fdc->sectorBuf, fdc->sectorNumber, fdc->side, 
                           fdc->currentTrack, 0, NULL);

            fdc->sectorOffset = 0;
            fdc->mainStatus = 0xf0;
        }
        break;

    case CMD_RECALIBRATE:
        fdc->status0 = (fdc->commandRegs[1] & 7);
        fdc->status1 = 0;
        fdc->status2 = 0;
        fdc->drive = fdc->commandRegs[1] & 3;

        if (!diskPresent(fdc->drive)) {
            fdc->status0 |= 0xd8;
        }
        else {
            if (fdc->currentTrack > 77) {
                fdc->currentTrack -= 77;
                fdc->status0 |= 0x30;
            }
            else
            {
                fdc->currentTrack = 0;
                fdc->status0 |= 0x20;
            }
        }

        fdc->mainStatus = 0x80 | (1 << (fdc->commandRegs[1] & 3));
        fdc->phase = PHASE_IDLE;
        break;

    case CMD_SENSE_INTERRUPT:
        fdc->mainStatus = 0xd0;
        fdc->resultCount = 2;
        fdc->resultOffset = 0;

//        fdc->status0 = (fdc->commandRegs[1] & 7);
        if (!diskPresent(fdc->drive)) {
            fdc->status0 |= 0x08;
        }

        if (!fdc->status0 & 0x38) {
            fdc->status0 |= 0x80;
        }

        fdc->resultRegs[0] = fdc->status0 & 0x3f; 
        fdc->status0 = 0x00;
        fdc->resultRegs[1] = fdc->currentTrack;

        fdc->phase = PHASE_RESULT;
        break;

    case CMD_READ_SECTOR_ID:
        fdc->drive = fdc->commandRegs[1] & 3;
        fdc->side  = (fdc->commandRegs[1] >> 2) & 1;

        if (!diskPresent(fdc->drive)) {
            fdc->status0 = fdc->drive | 0xd8;
            createResult(fdc);
        }
        else {
#if 0
            TrackIndex = FDCCurrTrack[FDCCurrDrv] * dsk[FDCCurrDrv].Header.nbof_heads + FDCCurrSide[FDCCurrDrv];
#endif
            fdc->status0 = fdc->commandRegs[1] & 7;
            createResult(fdc);
            fdc->resultRegs[5] = 0x41;
        }
        break;

    case CMD_SEEK:
        fdc->mainStatus = 0x80 | (1 << (fdc->commandRegs[1] & 3));
        fdc->drive = fdc->commandRegs[1] & 3;
        fdc->side  = (fdc->commandRegs[1] >> 2) & 1;
        if (!diskPresent(fdc->drive)) {
            fdc->status0 = fdc->drive | 0xd8;
            createResult(fdc);
        }
        else {
            fdc->currentTrack = fdc->commandRegs[2];
            fdc->status0 = 0x08 | (fdc->commandRegs[1] & 7);
            fdc->phase = PHASE_IDLE;
        }
        break;

    default:
        break;
    }
}


NEC765* nec765Create()
{
    NEC765* fdc = malloc(sizeof(NEC765));

    nec765Reset(fdc);

    return fdc;
}

void nec765Destroy(NEC765* fdc)
{
}

void nec765Reset(NEC765* fdc)
{
    fdc->mainStatus = 0x80;

    fdc->phase = PHASE_IDLE;
    fdc->sectorOffset = 0;
    fdc->commandOffset = 0;
    fdc->interrupt = 1;
    fdc->currentTrack = 0;
    fdc->drive = 0;

    memset(fdc->commandRegs, 0, sizeof(fdc->commandRegs));
}

UInt8 nec765ReadStatus(NEC765* fdc)
{
    return fdc->mainStatus;
}

UInt8 nec765Read(NEC765* fdc)
{
    fdc->interrupt = 0;

    if (fdc->phase == PHASE_COMMAND) {
        return nec765ExecuteReadCommand(fdc);
    }

    if (fdc->phase == PHASE_RESULT) {
        UInt8 value = fdc->resultRegs[fdc->resultOffset++];
 
        if (fdc->resultOffset == fdc->resultCount) {
            fdc->phase = PHASE_IDLE;
            fdc->mainStatus = 0x80;
        }
        return value;
    }
    return 0;
}

UInt8 nec765Peek(NEC765* fdc)
{
}

void nec765Write(NEC765* fdc, UInt8 value)
{
    if (fdc->phase == PHASE_COMMAND) {
        nec765ExecuteWriteCommand(fdc, value);
    }
    else {
        if (fdc->commandOffset == 0) {
            fdc->commandRegs[fdc->commandOffset++] = value & 0x1f;
            fdc->mainStatus |= 0x10;
        }
        else {
            if (fdc->commandOffset < commandLength[fdc->commandRegs[0]]) {
                fdc->commandRegs[fdc->commandOffset++] = value;
            }
            if (fdc->commandOffset == commandLength[fdc->commandRegs[0]]) {
                fdc->commandOffset = 0;
                fdc->mainStatus |= 0x20;
                nec765ExecuteWriteCommand(fdc, value);
                fdc->interrupt = 1;
            }
        }
    }
}

int nec765GetInt(NEC765* fdc)
{
    return fdc->interrupt;
}

#endif
