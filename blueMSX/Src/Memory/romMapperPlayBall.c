/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperPlayBall.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-20 07:02:10 $
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
#include "romMapperPlayBall.h"
#include "Board.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SamplePlayer.h"
#include "SaveState.h"
#include "PlayballSamples.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    SamplePlayer* samplePlayer;
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
    int size;
} RomMapperPlayBall;

static void saveState(RomMapperPlayBall* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperPlayBall");

    saveStateClose(state);
}

static void loadState(RomMapperPlayBall* rm)
{
    SaveState* state = saveStateOpenForRead("mapperPlayBall");

    saveStateClose(state);
}

static void destroy(RomMapperPlayBall* rm)
{
    samplePlayerDestroy(rm->samplePlayer);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);
    free(rm->romData);
    free(rm);
}

static UInt8 read(RomMapperPlayBall* rm, UInt16 address) 
{
    if (address == 0x7fff) {
        return samplePlayerIsIdle(rm->samplePlayer) ? 1 : 0;
    }

    return rm->romData[address];
}

static void write(RomMapperPlayBall* rm, UInt16 address, UInt8 value) 
{
    if (address == 0x7fff) {
        if (samplePlayerIsIdle(rm->samplePlayer)) {
            switch (value) {
            case 0:  samplePlayerWrite(rm->samplePlayer, playball_0,  sizeof(playball_0)  / sizeof(playball_0[0]),  NULL, 0); break;
            case 1:  samplePlayerWrite(rm->samplePlayer, playball_1,  sizeof(playball_1)  / sizeof(playball_1[0]),  NULL, 0); break;
            case 2:  samplePlayerWrite(rm->samplePlayer, playball_2,  sizeof(playball_2)  / sizeof(playball_2[0]),  NULL, 0); break;
            case 3:  samplePlayerWrite(rm->samplePlayer, playball_3,  sizeof(playball_3)  / sizeof(playball_3[0]),  NULL, 0); break;
            case 4:  samplePlayerWrite(rm->samplePlayer, playball_4,  sizeof(playball_4)  / sizeof(playball_4[0]),  NULL, 0); break;
            case 5:  samplePlayerWrite(rm->samplePlayer, playball_0,  sizeof(playball_0)  / sizeof(playball_0[0]),  NULL, 0); break;
            case 6:  samplePlayerWrite(rm->samplePlayer, playball_6,  sizeof(playball_6)  / sizeof(playball_6[0]),  NULL, 0); break;
            case 7:  samplePlayerWrite(rm->samplePlayer, playball_7,  sizeof(playball_7)  / sizeof(playball_7[0]),  NULL, 0); break;
            case 8:  samplePlayerWrite(rm->samplePlayer, playball_8,  sizeof(playball_8)  / sizeof(playball_8[0]),  NULL, 0); break;
            case 9:  samplePlayerWrite(rm->samplePlayer, playball_9,  sizeof(playball_9)  / sizeof(playball_9[0]),  NULL, 0); break;
            case 10: samplePlayerWrite(rm->samplePlayer, playball_10, sizeof(playball_10) / sizeof(playball_10[0]), NULL, 0); break;
            case 11: samplePlayerWrite(rm->samplePlayer, playball_11, sizeof(playball_11) / sizeof(playball_11[0]), NULL, 0); break;
            case 12: samplePlayerWrite(rm->samplePlayer, playball_12, sizeof(playball_12) / sizeof(playball_12[0]), NULL, 0); break;
            case 13: samplePlayerWrite(rm->samplePlayer, playball_13, sizeof(playball_13) / sizeof(playball_13[0]), NULL, 0); break;
            case 14: samplePlayerWrite(rm->samplePlayer, playball_14, sizeof(playball_14) / sizeof(playball_14[0]), NULL, 0); break;
            }
        }
    }
}

int romMapperPlayBallCreate(char* filename, UInt8* romData, 
                          int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperPlayBall* rm;

    rm = malloc(sizeof(RomMapperPlayBall));

    rm->samplePlayer = samplePlayerCreate(boardGetMixer(), MIXER_CHANNEL_PCM);

    if (size > 0x8000) {
        size = 0x8000;
    }

    rm->deviceHandle = deviceManagerRegister(ROM_PLAYBALL, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, read, read, write, destroy, rm);

    rm->romData = malloc(0x8000);
    memset(rm->romData + size, 0xff, 0x8000 - size);
    memcpy(rm->romData, romData, size);
    rm->size = size;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    slotMapPage(rm->slot, rm->sslot, rm->startPage,     rm->romData + 0x0000, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, rm->romData + 0x2000, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, rm->romData + 0x4000, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 3, rm->romData + 0x6000, 0, 0);

    return 1;
}

