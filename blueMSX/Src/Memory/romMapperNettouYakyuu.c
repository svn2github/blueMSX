/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperNettouYakyuu.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2008-04-27 21:30:49 $
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
#include "romMapperNettouYakyuu.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "SamplePlayer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    SamplePlayer* samplePlayer;
    int sample;
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
    UInt32 romMask;
    int romMapper[4];
} RomMapperNettouYakyuu;

static void saveState(RomMapperNettouYakyuu* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperNettouYakyuu");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        saveStateSet(state, tag, rm->romMapper[i]);
    }

    saveStateClose(state);
}

static void loadState(RomMapperNettouYakyuu* rm)
{
    SaveState* state = saveStateOpenForRead("mapperNettouYakyuu");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        rm->romMapper[i] = saveStateGet(state, tag, 0);
    }

    saveStateClose(state);

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + rm->romMapper[i] * 0x2000, 1, 0);
    }
}


#ifdef NO_EMBEDDED_SAMPLES

/* standard ASCII8 */

static void destroy(RomMapperNettouYakyuu* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static void write(RomMapperNettouYakyuu* rm, UInt16 address, UInt8 value) 
{
    int bank;

    address += 0x4000;
    
    if (address < 0x6000 || address > 0x7fff) {
        return;
    }

    bank = (address & 0x1800) >> 11;

    value &= rm->romMask;
    if (rm->romMapper[bank] != value) {
        UInt8* bankData = rm->romData + ((int)value << 13);

        rm->romMapper[bank] = value;
        
        slotMapPage(rm->slot, rm->sslot, rm->startPage + bank, bankData, 1, 0);
    }
}

int romMapperNettouYakyuuCreate(char* filename, UInt8* romData, 
                          int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperNettouYakyuu* rm;
    int i;

    int origSize = size;
    
    size = 0x8000;
    while (size < origSize) {
        size *= 2;
    }

    rm = malloc(sizeof(RomMapperNettouYakyuu));

    rm->deviceHandle = deviceManagerRegister(ROM_NETTOUYAKYUU, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, NULL, NULL, write, destroy, rm);

    rm->romData = calloc(1, size);
    memcpy(rm->romData, romData, origSize);
    rm->romMask = size / 0x2000 - 1;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    rm->romMapper[0] = 0;
    rm->romMapper[1] = 0;
    rm->romMapper[2] = 0;
    rm->romMapper[3] = 0;

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + rm->romMapper[i] * 0x2000, 1, 0);
    }

    return 1;
}

#else

#include "NettouYakyuuSamples.h"

static void destroy(RomMapperNettouYakyuu* rm)
{
    samplePlayerDestroy(rm->samplePlayer);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static void write(RomMapperNettouYakyuu* rm, UInt16 address, UInt8 value) 
{
    int bank;

    address += 0x4000;
    
	if (address==0xb000) {
		if (!(value&0x80)) return;
		if (value&0x40) {
			switch (rm->sample) {
				case 0:  samplePlayerWrite(rm->samplePlayer, nettou_0, sizeof(nettou_0) / sizeof(nettou_0[0]), NULL, 0); break;
				case 1:  samplePlayerWrite(rm->samplePlayer, nettou_1, sizeof(nettou_1) / sizeof(nettou_1[0]), NULL, 0); break;
				case 2:  samplePlayerWrite(rm->samplePlayer, nettou_2, sizeof(nettou_2) / sizeof(nettou_2[0]), NULL, 0); break;
				case 3:  samplePlayerWrite(rm->samplePlayer, nettou_3, sizeof(nettou_3) / sizeof(nettou_3[0]), NULL, 0); break;
				case 4:  samplePlayerWrite(rm->samplePlayer, nettou_4, sizeof(nettou_4) / sizeof(nettou_4[0]), NULL, 0); break;
				case 5:  samplePlayerWrite(rm->samplePlayer, nettou_5, sizeof(nettou_5) / sizeof(nettou_5[0]), NULL, 0); break;
				case 6:  samplePlayerWrite(rm->samplePlayer, nettou_6, sizeof(nettou_6) / sizeof(nettou_6[0]), NULL, 0); break;
				case 7:  samplePlayerWrite(rm->samplePlayer, nettou_7, sizeof(nettou_7) / sizeof(nettou_7[0]), NULL, 0); break;
				case 8:  samplePlayerWrite(rm->samplePlayer, nettou_8, sizeof(nettou_8) / sizeof(nettou_8[0]), NULL, 0); break;
				case 9:  samplePlayerWrite(rm->samplePlayer, nettou_9, sizeof(nettou_9) / sizeof(nettou_9[0]), NULL, 0); break;
				case 0xa:samplePlayerWrite(rm->samplePlayer, nettou_a, sizeof(nettou_a) / sizeof(nettou_a[0]), NULL, 0); break;
				case 0xb:samplePlayerWrite(rm->samplePlayer, nettou_b, sizeof(nettou_b) / sizeof(nettou_b[0]), NULL, 0); break;
				case 0xc:samplePlayerWrite(rm->samplePlayer, nettou_c, sizeof(nettou_c) / sizeof(nettou_c[0]), NULL, 0); break;
				case 0xd:samplePlayerWrite(rm->samplePlayer, nettou_d, sizeof(nettou_d) / sizeof(nettou_d[0]), NULL, 0); break;
				case 0xe:samplePlayerWrite(rm->samplePlayer, nettou_e, sizeof(nettou_e) / sizeof(nettou_e[0]), NULL, 0); break;
				case 0xf:samplePlayerWrite(rm->samplePlayer, nettou_f, sizeof(nettou_f) / sizeof(nettou_f[0]), NULL, 0); break;
				default: break;
			}
		}
		else rm->sample=value&0xf;
	}
    
    if (address < 0x6000 || address > 0x7fff) {
        return;
    }

    bank = (address & 0x1800) >> 11;

    value &= rm->romMask;
    if (rm->romMapper[bank] != value) {
        UInt8* bankData = rm->romData + ((int)value << 13);

        rm->romMapper[bank] = value;
        
        slotMapPage(rm->slot, rm->sslot, rm->startPage + bank, bankData, 1, 0);
    }
}

int romMapperNettouYakyuuCreate(char* filename, UInt8* romData, 
                          int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperNettouYakyuu* rm;
    int i;

    int origSize = size;
    
    size = 0x8000;
    while (size < origSize) {
        size *= 2;
    }

    rm = malloc(sizeof(RomMapperNettouYakyuu));
    rm->samplePlayer = samplePlayerCreate(boardGetMixer(), MIXER_CHANNEL_PCM, 8, 11025);
    rm->deviceHandle = deviceManagerRegister(ROM_NETTOUYAKYUU, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, NULL, NULL, write, destroy, rm);

    rm->romData = calloc(1, size);
    memcpy(rm->romData, romData, origSize);
    rm->romMask = size / 0x2000 - 1;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    rm->romMapper[0] = 0;
    rm->romMapper[1] = 0;
    rm->romMapper[2] = 0;
    rm->romMapper[3] = 0;

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + rm->romMapper[i] * 0x2000, 1, 0);
    }

    return 1;
}

#endif
