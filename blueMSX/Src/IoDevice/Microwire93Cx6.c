/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/Microwire93Cx6.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-09-22 06:18:42 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
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
#include "Microwire93Cx6.h"
#include "Board.h"
#include "SaveState.h"
#include "sramLoader.h"
#include <stdlib.h>
#include <string.h>

// Emulates the Microchip Technology Inc. 93C76/86 eeprom chips

typedef struct Microwire93Cx6
{
    UInt8* romData;
    int    romMask;
    int    word16;

    int    phase;
    UInt32 command;
    UInt32 commandIdx;
    UInt32 value;
    UInt32 valueIdx;
    int    programEnable;
    
    int Di;
    int Do;
    int Cs;
    int Clk;

    BoardTimer* timer;
    
    char sramFilename[512];
};

#define PHASE_IDLE                  0
#define PHASE_COMMAND               1
#define PHASE_DATATRANSFER_WRITE    2
#define PHASE_DATATRANSFER_READ     3
#define PHASE_PROGRAMMING           4
#define PHASE_COMMAND_DONE          5



static void romWrite(Microwire93Cx6* rm, UInt32 address, UInt32 value)
{
    if (rm->word16) {
        ((UInt16*)(rm->romData))[address & (rm->romMask / 2)] = (UInt16)value;
    }
    else {
        ((UInt8*)(rm->romData))[address & rm->romMask] = (UInt8)value;
    }
}

static UInt32 romRead(Microwire93Cx6* rm, UInt32 address)
{
    if (rm->word16) {
        return ((UInt16*)(rm->romData))[address & (rm->romMask / 2)];
    }
    else {
        return ((UInt8*)(rm->romData))[address & rm->romMask];
    }
}


void microwire93Cx6SaveState(Microwire93Cx6* rm)
{
    SaveState* state = saveStateOpenForWrite("Microwire93Cx6");

    saveStateClose(state);
}

void microwire93Cx6LoadState(Microwire93Cx6* rm)
{
    SaveState* state = saveStateOpenForRead("Microwire93Cx6");

    saveStateClose(state);
}

static void onTimer(Microwire93Cx6* rm, UInt32 time)
{
    if (rm->Do == 1) {
        rm->phase = PHASE_IDLE;
    }
    else {
        rm->phase = PHASE_COMMAND_DONE;
    }
}

Microwire93Cx6* microwire93Cx6Create(int size, int mode, void* imgData, int imgSize, char* sramFilename)
{
    Microwire93Cx6* rm = calloc(1, sizeof(Microwire93Cx6));

    if (sramFilename != NULL) {
        strcpy(rm->sramFilename, sramFilename);
    }

    // Allocate memory
    rm->romMask = (size - 1) & 0x01ff;
    rm->romData = malloc(size);
    memset(rm->romData, 0xff, size);

    // Load rom data if present
    if (imgData != NULL) {
        if (imgSize > size) {
            imgSize = size;
        }
        memcpy(rm->romData, imgData, imgSize);
    }

    // Set mode (8/16 bit)
    rm->word16 = mode == 16 ? 1 : 0;

    rm->timer = boardTimerCreate(onTimer, rm);

    microwire93Cx6Reset(rm);

    return rm;
}

void microwire93Cx6Destroy(Microwire93Cx6* rm)
{
    if (rm->sramFilename[0]) {
        sramSave(rm->sramFilename, rm->romData, rm->romMask + 1, NULL, 0);
    }

    boardTimerDestroy(rm->timer);

    free(rm->romData);
    free(rm);
}

void microwire93Cx6Reset(Microwire93Cx6* rm)
{
    rm->Cs = 0;
    rm->Do = 1;
    rm->Di = 0;

    rm->phase = PHASE_IDLE;
    rm->programEnable = 0;
}


void microwire93Cx6SetCs(Microwire93Cx6* rm, int value)
{
    rm->Cs = value ? 1 : 0;

    if (rm->Cs == 0) {
        rm->Do = 1;
        if (rm->phase == PHASE_COMMAND_DONE || rm->phase == PHASE_DATATRANSFER_READ) {
            rm->phase = PHASE_IDLE;
        }
    }
}

void microwire93Cx6SetDi(Microwire93Cx6* rm, int value)
{
    rm->Di = value ? 1 : 0;
}

int microwire93Cx6GetDo(Microwire93Cx6* rm)
{
    return rm->Do;
}

void microwire93Cx6SetClk(Microwire93Cx6* rm, int value)
{
    value = value ? 1 : 0;

    if (rm->Clk == value) {
         // No edge
        return;
    }
    
    rm->Clk = value;
    
    if (rm->Cs == 0 || rm->Clk == 0) {
         // Falling edge or chip not selected
        return;
    }

    switch (rm->phase) {
    case PHASE_IDLE:
        if (rm->Cs && rm->Di) {
            rm->phase = PHASE_COMMAND;
            rm->command = 0;
            rm->commandIdx = 12 + rm->word16;
        }
        break;

    case PHASE_COMMAND:
        rm->command |= value << --rm->commandIdx;
        if (rm->commandIdx != 0) {
            break;
        }

        switch ((rm->command >> (10 + rm->word16)) & 0x03) {
        case 0:
            switch ((rm->command >> (8 + rm->word16)) & 0x03) {
            case 0:
                // EWDS command
                rm->programEnable = 0;
                rm->phase = PHASE_COMMAND_DONE;
                break;
            case 1:
                // WRAL command
                rm->value = 0;
                rm->valueIdx = 8 + 8 * rm->word16;
                rm->phase = PHASE_DATATRANSFER_WRITE;
                break;
            case 2:
                // ERAL command
                if (rm->programEnable) {
                    memset(rm->romData, 0xff, rm->romMask + 1);
                    rm->Do = 0;
                    boardTimerAdd(rm->timer, boardSystemTime() + boardFrequency() * 8 / 1000);
                    rm->phase = PHASE_PROGRAMMING;
                }
                else {
                    rm->Do = 1;
                    rm->phase = PHASE_COMMAND_DONE;
                }
                break;
            case 3:
                // EWEN command
                rm->programEnable = 1;
                rm->phase = PHASE_COMMAND_DONE;
                break;
            }
            break;
        case 1:
            // WRITE command
            rm->value = 0;
            rm->valueIdx = 8 + 8 * rm->word16;
            rm->phase = PHASE_DATATRANSFER_WRITE;
            break;
        case 2:
            // READ command
            rm->value = romRead(rm, rm->command);
            rm->valueIdx = 8 + 8 * rm->word16;
            rm->phase = PHASE_DATATRANSFER_READ;
            break;
        case 3:
            // ERASE command
            if (rm->programEnable) {
                romWrite(rm, rm->command, 0xffff);
                rm->Do = 0;
                boardTimerAdd(rm->timer, boardSystemTime() + boardFrequency() * 3 / 1000);
                rm->phase = PHASE_PROGRAMMING;
            }
            else {
                rm->Do = 1;
                rm->phase = PHASE_COMMAND_DONE;
            }
            break;
        }
        break;

    case PHASE_DATATRANSFER_READ:
    case PHASE_DATATRANSFER_WRITE:
        switch ((rm->command >> (10 + rm->word16)) & 0x03) {
        case 0:
            if (((rm->command >> (8 + rm->word16)) & 0x03) == 1) {
                // WRAL command
                rm->value = rm->Di << --rm->valueIdx;
                
                if (rm->valueIdx == 0) {
                    if (rm->programEnable) {
                        int i;
                        for (i = 0; i <= rm->romMask; i++) {
                            romWrite(rm, i, rm->value);
                        }
                        rm->Do = 0;
                        boardTimerAdd(rm->timer, boardSystemTime() + boardFrequency() * 16 / 1000);
                        rm->phase = PHASE_PROGRAMMING;
                    }
                    else {
                        rm->Do = 1;
                        rm->phase = PHASE_COMMAND_DONE;
                    }
                }
            }
            break;
        case 1:
            // WRITE command
            rm->value = rm->Di << --rm->valueIdx;
            
            if (rm->valueIdx == 0) {
                if (rm->programEnable) {
                    romWrite(rm, rm->command, rm->value);
                    rm->Do = 0;
                    boardTimerAdd(rm->timer, boardSystemTime() + boardFrequency() * 3 / 1000);
                    rm->phase = PHASE_PROGRAMMING;
                }
                else {
                    rm->Do = 1;
                    rm->phase = PHASE_COMMAND_DONE;
                }
            }
            break;
        case 2:
            // READ command
            rm->Do = (rm->value >> --rm->valueIdx) & 1;

            if (rm->valueIdx == 0) {
                rm->command = (rm->command & 0xfe00) | ((rm->command + 1) & 0x01ff);

                rm->value    = romRead(rm, rm->command);
                rm->valueIdx = 8 + 8 * rm->word16;
            }
            break;
        }
        break;
    }
}
