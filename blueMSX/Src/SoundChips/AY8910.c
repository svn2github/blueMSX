/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/AY8910.c,v $
**
** $Revision: 1.12 $
**
** $Date: 2005-02-25 22:18:04 $
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
#include "AY8910.h"
#include "IoPort.h"
#include "SaveState.h"
#include "DebugDeviceManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BASE_PHASE_STEP 0x28959becUL  /* = (1 << 28) * 3579545 / 32 / 44100 */
#define BUFFER_SIZE     10000

static const Int16 voltTable[16] = {
    0x0000, 0x004f, 0x00b4, 0x0133, 0x01d4, 0x029f, 0x03a1, 0x04e7, 
    0x0683, 0x088c, 0x0b1f, 0x0e62, 0x1281, 0x17b8, 0x1e50, 0x26a9
};

static const UInt8 regMask[16] = {
    0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0x1f, 0x3f, 
    0x1f, 0x1f, 0x1f, 0xff, 0xff, 0x0f, 0xff, 0xff
};

static Int32* ay8910Sync(void* ref, UInt32 count);
static void updateRegister(AY8910* ay8910, UInt8 address, UInt8 data);

struct AY8910 {
    Mixer* mixer;
    Int32  handle;
    Int32  debugHandle;

    AY8910ReadCb    ioPortReadCb;
    AY8910ReadCb    ioPortPollCb;
    AY8910WriteCb   ioPortWriteCb;
    void*           ioPortArg;
    Ay8910Connector connector;

    UInt8  address;
    UInt8  regs[16];

    UInt32 tonePhase[3];
    UInt32 toneStep[3];

    UInt32 noisePhase;
    UInt32 noiseStep;
    UInt32 noiseRand;
    Int16  noiseVolume;

    UInt8  envShape;
    UInt32 envStep;
    UInt32 envPhase;

    UInt8  enable;
    UInt8  ampVolume[3];
    Int32  ctrlVolume;
    Int32  oldSampleVolume;
    Int32  daVolume;

    Int32  buffer[BUFFER_SIZE];
};

void ay8910LoadState(AY8910* ay8910)
{
    SaveState* state = saveStateOpenForRead("ay8910");
    char tag[32];
    int i;

    ay8910->address          = (UInt8) saveStateGet(state, "address",         0);
    ay8910->noisePhase       =         saveStateGet(state, "noisePhase",      0);
    ay8910->noiseStep        =         saveStateGet(state, "noiseStep",       0);
    ay8910->noiseRand        =         saveStateGet(state, "noiseRand",       0);
    ay8910->noiseVolume      = (Int16) saveStateGet(state, "noiseVolume",     0);

    ay8910->envShape         = (UInt8) saveStateGet(state, "envShape",        0);
    ay8910->envStep          =         saveStateGet(state, "envStep",         0);
    ay8910->envPhase         =         saveStateGet(state, "envPhase",        0);

    ay8910->enable           = (UInt8) saveStateGet(state, "enable",          0);
    ay8910->ctrlVolume       =         saveStateGet(state, "ctrlVolume",      0);
    ay8910->oldSampleVolume  =         saveStateGet(state, "oldSampleVolume", 0);
    ay8910->daVolume         =         saveStateGet(state, "daVolume",        0);

    for (i = 0; i < 16; i++) {
        sprintf(tag, "reg%d", i);
        ay8910->regs[i] = (UInt8)saveStateGet(state, tag, 0);
    }

    for (i = 0; i < 3; i++) {
        sprintf(tag, "phase%d", i);
        ay8910->tonePhase[i] = saveStateGet(state, tag, 0);

        sprintf(tag, "toneStep%d", i);
        ay8910->toneStep[i] = saveStateGet(state, tag, 0);

        sprintf(tag, "ampVol%d", i);
        ay8910->ampVolume[i] = (UInt8)saveStateGet(state, tag, 0);
    }
    
    saveStateClose(state);
}

void ay8910SaveState(AY8910* ay8910)
{
    SaveState* state = saveStateOpenForWrite("ay8910");
    char tag[32];
    int i;

    saveStateSet(state, "address",         ay8910->address);
    saveStateSet(state, "noisePhase",      ay8910->noisePhase);
    saveStateSet(state, "noiseStep",       ay8910->noiseStep);
    saveStateSet(state, "noiseRand",       ay8910->noiseRand);
    saveStateSet(state, "noiseVolume",     ay8910->noiseVolume);

    saveStateSet(state, "envShape",        ay8910->envShape);
    saveStateSet(state, "envStep",         ay8910->envStep);
    saveStateSet(state, "envPhase",        ay8910->envPhase);

    saveStateSet(state, "enable",          ay8910->enable);
    saveStateSet(state, "ctrlVolume",      ay8910->ctrlVolume);
    saveStateSet(state, "oldSampleVolume", ay8910->oldSampleVolume);
    saveStateSet(state, "daVolume",        ay8910->daVolume);

    for (i = 0; i < 16; i++) {
        sprintf(tag, "reg%d", i);
        saveStateSet(state, tag, ay8910->regs[i]);
    }

    for (i = 0; i < 3; i++) {
        sprintf(tag, "phase%d", i);
        saveStateSet(state, tag, ay8910->tonePhase[i]);

        sprintf(tag, "toneStep%d", i);
        saveStateSet(state, tag, ay8910->toneStep[i]);

        sprintf(tag, "ampVol%d", i);
        saveStateSet(state, tag, ay8910->ampVolume[i]);
    }
    
    saveStateClose(state);
}

static void getDebugInfo(AY8910* ay8910, DbgDevice* dbgDevice)
{
    DbgRegisterBank* regBank;
    int i;

    regBank = dbgDeviceAddRegisterBank(dbgDevice, "Registers", 16);

    for (i = 0; i < 16; i++) {
        char reg[4];
        sprintf(reg, "R%d", i);
        dbgRegisterBankAddRegister(regBank,  i, reg, 8, ay8910->regs[i]);
    }
}

static int dbgWriteRegister(AY8910* ay8910, char* name, int regIndex, UInt32 value)
{
    updateRegister(ay8910, (UInt8)regIndex, (UInt8)value);

    return 1;
}

AY8910* ay8910Create(Mixer* mixer, Ay8910Connector connector)
{
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, dbgWriteRegister, NULL };
    AY8910* ay8910 = (AY8910*)calloc(1, sizeof(AY8910));
    int i;

    ay8910->mixer = mixer;
    ay8910->connector = connector;
    ay8910->noiseRand = 1;
    ay8910->noiseVolume = 1;

    ay8910->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_PSG, 0, ay8910Sync, ay8910);

    ay8910Reset(ay8910);
    for (i = 0; i < 16; i++) {
        ay8910WriteAddress(ay8910, 0xa0, i);
        ay8910WriteData(ay8910, 0xa1, 0);
    }

    switch (ay8910->connector) {
    case AY8910_MSX:
        ioPortRegister(0xa0, NULL,           ay8910WriteAddress, ay8910);
        ioPortRegister(0xa1, NULL,           ay8910WriteData,    ay8910);
        ioPortRegister(0xa2, ay8910ReadData, NULL,               ay8910);
        break;

    case AY8910_SVI:
        ioPortRegister(0x88, NULL,           ay8910WriteAddress, ay8910);
        ioPortRegister(0x8c, NULL,           ay8910WriteData,    ay8910);
        ioPortRegister(0x90, ay8910ReadData, NULL,               ay8910);
        break;
    }
    
    ay8910->debugHandle = debugDeviceRegister(DBGTYPE_AUDIO, "AY8910 PSG", &dbgCallbacks, ay8910);

    return ay8910;
}

void ay8910Reset(AY8910* ay8910)
{
    if (ay8910 != NULL) {
        int i;
    
        for (i = 0; i < 16; i++) {
            ay8910WriteAddress(ay8910, 0xa0, i);
            ay8910WriteData(ay8910, 0xa1, 0);
        }
    }
}

void ay8910Destroy(AY8910* ay8910)
{
    debugDeviceUnregister(ay8910->debugHandle);

    switch (ay8910->connector) {
    case AY8910_MSX:
        ioPortUnregister(0xa0);
        ioPortUnregister(0xa1);
        ioPortUnregister(0xa2);
        break;
        
    case AY8910_SVI:
        ioPortUnregister(0x88);
        ioPortUnregister(0x8c);
        ioPortUnregister(0x90);
        break;
    }

    mixerUnregisterChannel(ay8910->mixer, ay8910->handle);
    free(ay8910);
}

void ay8910SetIoPort(AY8910* ay8910, AY8910ReadCb readCb, AY8910ReadCb pollCb, AY8910WriteCb writeCb, void* arg)
{
    ay8910->ioPortReadCb  = readCb;
    ay8910->ioPortPollCb  = pollCb;
    ay8910->ioPortWriteCb = writeCb;
    ay8910->ioPortArg     = arg;
}

void ay8910WriteAddress(AY8910* ay8910, UInt16 ioPort, UInt8 address)
{
    ay8910->address = address & 0xf;
}

UInt8 ay8910ReadData(AY8910* ay8910, UInt16 ioPort)
{
    UInt8  address = ay8910->address;

    if (address >= 14) {
        int port = address - 14;
        if (ay8910->ioPortReadCb != NULL){// && !(ay8910->regs[7] & (1 << (port + 6)))) {
            ay8910->regs[address] = ay8910->ioPortReadCb(ay8910->ioPortArg, port);
        }
    }
    return ay8910->regs[address];
}

static void updateRegister(AY8910* ay8910, UInt8 regIndex, UInt8 data)
{
    UInt32 period;
    int port;

    if (regIndex < 14) {
        mixerSync(ay8910->mixer);
    }

    data &= regMask[regIndex];

    ay8910->regs[regIndex] = data;

    switch (regIndex) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        period = ay8910->regs[regIndex & 6] | ((Int32)(ay8910->regs[regIndex | 1]) << 8);
//        period *= (~ay8910->enable >> (address >> 1)) & 1;
        ay8910->toneStep[regIndex >> 1] = period > 4 ? BASE_PHASE_STEP / period : 1 << 31;
        break;
        
    case 6:
        period = data ? data : 1;
        ay8910->noiseStep = period > 3 ? BASE_PHASE_STEP / period : 1 << 31;
        break;
        
    case 7:
        ay8910->enable = data;
        break;
        
    case 8:
    case 9:
    case 10:
        ay8910->ampVolume[regIndex - 8] = data;
        break;

    case 11:
    case 12:
        period = 16 * (ay8910->regs[11] | ((UInt32)ay8910->regs[12] << 8));
        ay8910->envStep = BASE_PHASE_STEP / (period ? period : 8);
        break;
        
    case 13:
        if (data < 4) data = 0x09;
        if (data < 8) data = 0x0f;
        ay8910->envShape = data;
        ay8910->envPhase = 0;
        break;

    case 14:
    case 15:
        port = regIndex - 14;
        if (ay8910->ioPortWriteCb != NULL){// && (ay8910->regs[7] & (1 << (port + 6)))) {
            ay8910->ioPortWriteCb(ay8910->ioPortArg, port, data);
        }
    }
}

void ay8910WriteData(AY8910* ay8910, UInt16 ioPort, UInt8 data)
{
    updateRegister(ay8910, ay8910->address, data);
}

static Int32* ay8910Sync(void* ref, UInt32 count)
{
    AY8910* ay8910 = (AY8910*)ref;
    Int32   channel;
    UInt32  index;

    for (index = 0; index < count; index++) {
        Int32 sampleVolume = 0;
        Int16 envVolume;

        /* Update noise generator */
        ay8910->noisePhase += ay8910->noiseStep;
        while (ay8910->noisePhase >> 28) {
            ay8910->noisePhase  -= 0x10000000;
            ay8910->noiseVolume ^= ((ay8910->noiseRand + 1) >> 1) & 1;
            ay8910->noiseRand    = (ay8910->noiseRand ^ (0x28000 * (ay8910->noiseRand & 1))) >> 1;
        }

        /* Update envelope phase */
        ay8910->envPhase += ay8910->envStep;
        if ((ay8910->envShape & 1) && (ay8910->envPhase >> 28)) {
            ay8910->envPhase = 0x10000000;
        }
 
        /* Calculate envelope volume */
        envVolume = (Int16)((ay8910->envPhase >> 24) & 0x0f);
        if (((ay8910->envPhase >> 27) & (ay8910->envShape + 1) ^ (~ay8910->envShape >> 1)) & 2) {
            envVolume ^= 0x0f;
        }

        /* Calculate and add channel samples to buffer */
        for (channel = 0; channel < 3; channel++) {
            UInt32 enable = ay8910->enable >> channel;
            UInt32 noiseEnable = ((enable >> 3) | ay8910->noiseVolume) & 1;
            UInt32 phaseStep = (~enable & 1) * ay8910->toneStep[channel];
            UInt32 tonePhase = ay8910->tonePhase[channel];
            UInt32 tone = 0;
            Int32  count = 16;

            /* Perform 16x oversampling */
            while (count--) {
                /* Update phase of tone */
                tonePhase += phaseStep;
     
                /* Calculate if tone is on or off */
                tone += (enable | (tonePhase >> 31)) & noiseEnable;
            }

            /* Store phase */
            ay8910->tonePhase[channel] = tonePhase;

            /* Amplify sample using either envelope volume or channel volume */
            if (ay8910->ampVolume[channel] & 0x10) {
                sampleVolume += (Int16)tone * voltTable[envVolume] / 16;
            }
            else {
                sampleVolume += (Int16)tone * voltTable[ay8910->ampVolume[channel]] / 16;
            }
        }

        /* Perform DC offset filtering */
        ay8910->ctrlVolume = sampleVolume - ay8910->oldSampleVolume + 0x3fe7 * ay8910->ctrlVolume / 0x4000;
        ay8910->oldSampleVolume = sampleVolume;

        /* Perform simple 1 pole low pass IIR filtering */
        ay8910->daVolume += 2 * (ay8910->ctrlVolume - ay8910->daVolume) / 3;
        
        /* Store calclulated sample value */
        ay8910->buffer[index] = 9 * ay8910->daVolume;
    }

    return ay8910->buffer;
}
