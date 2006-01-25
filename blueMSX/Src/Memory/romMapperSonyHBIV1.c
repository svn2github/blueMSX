/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSonyHBIV1.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2006-01-25 11:07:15 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik, Tomas Karlsson
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

#include "romMapperSonyHbiV1.h"
#include "MediaDb.h"
#include "Board.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "ArchVideoIn.h"
#include "SaveState.h"
#include <stdlib.h>
#include <memory.h>

typedef struct {
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
	
    int command;
    int startBlockX;
    int startBlockY;
    int blockSizeX;
    int blockSizeY;
    int mode;
    UInt8 vramOffset;
    UInt8 vramLine;
    UInt8 status0;
    UInt8 delay;
    BoardTimer* timerDigitize;
    BoardTimer* timerBusy;
    UInt8 vram[256][256];
} RomMapperSonyHbiV1;

static void saveState(RomMapperSonyHbiV1* rm)
{
    SaveState* state = saveStateOpenForWrite("Vmx80");
    saveStateClose(state);
}

static void loadState(RomMapperSonyHbiV1* rm)
{
    SaveState* state = saveStateOpenForRead("Vmx80");
    saveStateClose(state);
}

static void destroy(RomMapperSonyHbiV1* rm)
{
    boardTimerDestroy(rm->timerDigitize);
    boardTimerDestroy(rm->timerBusy);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static int calcY(UInt16 c)
{
    int r = (c>>10)&0x1f;
    int g = (c>> 5)&0x1f;
    int b = (c>> 0)&0x1f;

    int y = b/2 + r / 4 + g / 8;

    if (y > 31) y = 31;
    return y;
}

static void calcJK(UInt16* c, int* J, int* K)
{
    int r = (((c[0]>>10)&0x1f) + ((c[1]>>10)&0x1f) + ((c[2]>>10)&0x1f) + ((c[3]>>10)&0x1f)) / 4;
    int g = (((c[0]>> 5)&0x1f) + ((c[1]>> 5)&0x1f) + ((c[2]>> 5)&0x1f) + ((c[3]>> 5)&0x1f)) / 4;
    int b = (((c[0]>> 0)&0x1f) + ((c[1]>> 0)&0x1f) + ((c[2]>> 0)&0x1f) + ((c[3]>> 0)&0x1f)) / 4;

    int y = b/2 + r / 4 + g / 8;
    int j = (r - y);
    int k = (g - y);

    if (j >  31) j = 31;
    if (j < -32) j = -32;
    if (j <   0) j = j + 64;
    if (k >  31) k = 31;
    if (k < -32) k = -32;
    if (k <   0) k = k + 64;

    *J = j;
    *K = k;
}

static void digitize(RomMapperSonyHbiV1* rm)
{
    int x, y;
    UInt16* img;
    int width  = 256;
    int height = 212;
    int blackWidth  = width;
    int blackHeight = height;
    int imgWidth  = 256;
    int startX = 64 * rm->startBlockX;
    int startY = 53 * rm->startBlockY;

    switch (rm->blockSizeX) {
    case 0: width = width * 1 / 1; blackWidth = width; break;
    case 1: width = width * 1 / 2; blackWidth = width; break;
    case 3: width = width * 1 / 4; blackWidth = width; break;
    case 4: width = width * 3 / 4; blackWidth = width; break;
    case 5: width = width * 2 / 2; blackWidth = width; break;
    case 7: width = width * 2 / 4; blackWidth = width; break;
    case 2: blackWidth = width * 1 / 2; width = width * 1 / 3; break;
    case 6: blackWidth = width * 3 / 4; width = width * 2 / 3; break;
    }

    switch (rm->blockSizeY) {
    case 0: height = height * 1 / 1; blackHeight = height; break;
    case 1: height = height * 1 / 2; blackHeight = height; break;
    case 3: height = height * 1 / 4; blackHeight = height; break;
    case 4: height = height * 3 / 4; blackHeight = height; break;
    case 5: height = height * 2 / 2; blackHeight = height; break;
    case 7: height = height * 2 / 4; blackHeight = height; break;
    case 2: blackHeight = height * 1 / 2; height = height * 1 / 3; break;
    case 6: blackHeight = height * 3 / 4; height = height * 2 / 3; break;
    }

    imgWidth = (width + 3) & ~3;

    img = archVideoInBufferGet(imgWidth, height);
    if (img == NULL) {
        return;
    }

    if (startX + width > 256) {
        width = 256 - startX;
    }
    if (startY + height > 212) {
        height = 212 - startY;
    }

    for (y = 0; y < height; y++) {
        int destY = startY + y;
        int j = 0;
        int k = 0;
        for (x = 0; x < width; x++) {
            int destX = startX + x;
            UInt16 color = img[x];
            UInt8  val = 0;
            switch (rm->mode) {
            case 0:
                switch (x & 3) {
                case 0:
                    calcJK(img + x, &j, &k);
                    val = (k & 7) | (calcY(color) << 3);
                    break;
                case 1:
                    val = (k >> 3) | (calcY(color) << 3);
                    break;
                case 2:
                    val = (j & 7) | (calcY(color) << 3);
                    break;
                case 3:
                    val = (j >> 3) | (calcY(color) << 3);
                    break;
                }
                break;
            case 1:
                switch (x & 3) {
                case 0:
                    calcJK(img + x, &j, &k);
                    val = (k & 7) | ((calcY(color) & 0xfe) << 3);
                    break;
                case 1:
                    val = (k >> 3) | ((calcY(color) & 0xfe) << 3);
                    break;
                case 2:
                    val = (j & 7) | ((calcY(color) & 0xfe) << 3);
                    break;
                case 3:
                    val = (j >> 3) | ((calcY(color) & 0xfe) << 3);
                    break;
                }
                break;
            case 2:
                val = (UInt8)(((color >> 10) & 0x1c) | ((color >> 2) & 0xe0) | ((color >> 3) & 0x03));
                break;
            case 3:
                val = 0;
                break;
            }
            rm->vram[destY][destX] = val;
        }
        for (; x < blackWidth; x++) {
            rm->vram[destY][startX + x] = 0;
        }
        img += imgWidth; 
    }
    for (; y < blackHeight; y++) {
        for (x = 0; x < blackWidth; x++) {
            rm->vram[startY + y][startX + x] = 0;
        }
    }
}

static void onTimerBusy(RomMapperSonyHbiV1* rm, UInt32 time)
{
    rm->status0 &= 0x7f;
}

static void onTimerDigitize(RomMapperSonyHbiV1* rm, UInt32 time)
{
    if (--rm->delay == 0) {
        rm->status0 |= 0x80;
        digitize(rm);
        boardTimerAdd(rm->timerBusy, boardSystemTime() + boardFrequency() / 60);
    }
    else {
        boardTimerAdd(rm->timerDigitize, boardSystemTime() + boardFrequency() / 60);
    }
}

static UInt8 read(RomMapperSonyHbiV1* rm, UInt16 address)
{
    UInt8 value = 0xff;

    if (address >= 0x8000) {
        return 0xff;
    }
    if (address >= 0x3e00 && address < 0x3f00) {
        UInt8 val = rm->vram[rm->vramLine][rm->vramOffset++];
        if (rm->vramOffset == 0) {
            rm->vramLine++;
            if (rm->vramLine == 212) {
                rm->vramLine = 0;
            }
        }
        return val;
    }
    if (address < 0x3ffc || address >= 0x3fff) {
        return rm->romData[address];
    }
    switch (address) {
    case 0x3ffc:
        rm->status0 ^= 060;
        value = rm->status0 | rm->command;
        break;
    case 0x3ffd:
        value = (UInt8)(((boardSystemTime() / (boardFrequency() / 60)) & 1) << 7) | 
                (archVideoInIsVideoConnected() ? 0 : 0x10) |
                (rm->startBlockY << 2) | rm->startBlockX;
        break;
    case 0x3ffe:
        value = (rm->mode << 6) | (rm->blockSizeY << 3) | rm->blockSizeX;
        break;
    case 0x3fff:
        value = rm->delay;
        break;
    }

    return value;
}

static void write(RomMapperSonyHbiV1* rm, UInt16 address, UInt8 value) 
{
    if (address >= 0x8000) {
        return;
    }
    if (address < 0x3ffc || address >= 0x4000) {
        return;
    }

    switch (address & 3) {
    case 0:
        rm->command = (value >> 0) & 3;
        rm->vramOffset = 0;
        rm->vramLine   = 0;
        switch (rm->command) {
        case 0:
            boardTimerRemove(rm->timerBusy);
            boardTimerRemove(rm->timerDigitize);
            rm->status0 &= 0x7f;
            break;
        case 1:
            digitize(rm);
            rm->status0 |= 0x80;
            boardTimerAdd(rm->timerBusy, boardSystemTime() + boardFrequency() / 60);
            break;
        case 2:
            if (rm->delay == 0) {
                rm->status0 |= 0x80;
                digitize(rm);
                boardTimerAdd(rm->timerBusy, boardSystemTime() + boardFrequency() / 60);
            }
            else
                boardTimerAdd(rm->timerDigitize, boardSystemTime() + boardFrequency() / 60);
            break;
        case 3:
            printf("HBI-V1 Command = 3\n");
        }
        break;
    case 1:
        rm->startBlockY = (value >> 2) & 3;
        rm->startBlockX = (value >> 0) & 3;
        break;
    case 2:
        rm->mode       = (value >> 6) & 3;
        rm->blockSizeY = (value >> 3) & 7;
        rm->blockSizeX = (value >> 0) & 7;
        break;
    case 3:
        rm->delay      = value;
        break;
    }
}

static void reset(RomMapperSonyHbiV1* rm)
{
    rm->command     = 0;
    rm->startBlockX = 0;
    rm->startBlockY = 0;
    rm->blockSizeX  = 0;
    rm->blockSizeY  = 0;
    rm->mode        = 0;
    rm->status0   = 0;
    rm->vramLine    = 0;
    rm->vramOffset  = 0;
    rm->delay       = 0;
}

int romMapperSonyHbiV1Create(char* filename, UInt8* romData, int size,
                             int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperSonyHbiV1* rm;
    int pages = 4;
    int i;

    if ((startPage + pages) > 8) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperSonyHbiV1));

    rm->deviceHandle = deviceManagerRegister(ROM_SONYHBIV1, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, read, read, write, destroy, rm);

    rm->romData = calloc(1, size);
    memcpy(rm->romData, romData, size);
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;
    
    rm->timerDigitize = boardTimerCreate(onTimerDigitize, rm);
    rm->timerBusy     = boardTimerCreate(onTimerBusy,     rm);

    for (i = 0; i < pages; i++) {
        slotMapPage(slot, sslot, i + startPage, NULL, 0, 0);
    }

    reset(rm);

    return 1;
}

