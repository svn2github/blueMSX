/*****************************************************************************
** File:        scc.c
**
** Author:      Daniel Vik
**
** Description: Emulation of the Konami SCC sound chip
**              The rotation code is partly taken from openMSX.
**
** More info:   www.bluemsx.com
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
#include "SCC.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>


#define BASE_PHASE_STEP 0x28959becUL  /* = (1 << 28) * 3579545 / 32 / 44100 */

#define ROTATE_OFF 32
#define ROTATE_ON  28

#define OFFSETOF(s, a) ((int)(&((s*)0)->a))

#define BUFFER_SIZE     10000

static Int32* sccSync(SCC* scc, UInt32 count);


struct SCC
{
    Mixer* mixer;
    Int32  buffer[BUFFER_SIZE];
    
    SccMode mode;
    UInt8 deformReg;
    Int8 wave[5][32];
    UInt32 period[5];
    UInt32 phase[5];
    UInt32 phaseStep[5];
    int  volume[5];
    UInt8 enable;
    UInt8 deformValue;
    UInt32 deformTime;
    int rotate[5];
    int readOnly[5];
    UInt8 offset[5];
    Int32  daVolume[5];
};

void sccLoadState(SCC* scc)
{
    SaveState* state = saveStateOpenForRead("scc");
    char tag[32];
    int i;

    scc->mode      =         saveStateGet(state, "mode", SCC_COMPATIBLE);
    scc->deformReg = (UInt8) saveStateGet(state, "deformReg", 0);
    
    for (i = 0; i < 5; i++) {
        int j;
        for (j = 0; j < 32; j++) {
            sprintf(tag, "wave%d%d", i, j);
            scc->wave[i][j] = (UInt8)saveStateGet(state, tag, 0);
        }

        sprintf(tag, "period%d", i);
        scc->period[i] = saveStateGet(state, tag, 0);
        
        sprintf(tag, "phase%d", i);
        scc->phase[i] = saveStateGet(state, tag, 0);
        
        sprintf(tag, "step%d", i);
        scc->phaseStep[i] = saveStateGet(state, tag, 0);
        
        sprintf(tag, "volume%d", i);
        scc->volume[i] = saveStateGet(state, tag, 0);
        
        sprintf(tag, "rotate%d", i);
        scc->rotate[i] = saveStateGet(state, tag, 0);
        
        sprintf(tag, "readOnly%d", i);
        scc->readOnly[i] = saveStateGet(state, tag, 0);
        
        sprintf(tag, "offset%d", i);
        scc->offset[i] = (UInt8)saveStateGet(state, tag, 0);
        
        sprintf(tag, "daVolume%d", i);
        scc->daVolume[i] = saveStateGet(state, tag, 0);
    }

    saveStateClose(state);
}

void sccSaveState(SCC* scc)
{
    SaveState* state = saveStateOpenForWrite("scc");
    char tag[32];
    int i;

    saveStateSet(state, "mode", scc->mode);
    saveStateSet(state, "deformReg", scc->deformReg);
    
    for (i = 0; i < 5; i++) {
        int j;
        for (j = 0; j < 32; j++) {
            sprintf(tag, "wave%d%d", i, j);
            saveStateSet(state, tag, scc->wave[i][j]);
        }

        sprintf(tag, "period%d", i);
        saveStateSet(state, tag, scc->period[i]);
        
        sprintf(tag, "phase%d", i);
        saveStateSet(state, tag, scc->phase[i]);
        
        sprintf(tag, "step%d", i);
        saveStateSet(state, tag, scc->phaseStep[i]);
        
        sprintf(tag, "volume%d", i);
        saveStateSet(state, tag, scc->volume[i]);
        
        sprintf(tag, "rotate%d", i);
        saveStateSet(state, tag, scc->rotate[i]);
        
        sprintf(tag, "readOnly%d", i);
        saveStateSet(state, tag, scc->readOnly[i]);
        
        sprintf(tag, "offset%d", i);
        saveStateSet(state, tag, scc->offset[i]);
        
        sprintf(tag, "daVolume%d", i);
        saveStateSet(state, tag, scc->daVolume[i]);
    }

    saveStateClose(state);
}

static UInt8 sccGetWave(SCC* scc, UInt8 channel, UInt8 address)
{
    if (scc->rotate[channel] == ROTATE_OFF) {
        return scc->wave[channel][address & 0x1f];
    } 
    else {
        int ticks = (boardSystemTime() - scc->deformTime) / 6; //FIXME: What is the frequency
        int period = ((channel == 3) && (scc->mode != SCC_PLUS)) ? scc->period[4] : scc->period[channel];
        int shift = ticks / (period + 1);
        return scc->wave[channel][(address + shift) & 0x1f];
    }
}

static UInt8 sccGetFreqAndVol(SCC* scc, UInt8 address)
{
    address &= 0x0f;

    if (address < 0x0a) {
        // get period
        UInt8 channel = address / 2;
        if (address & 1) {
            return (UInt8)(scc->period[channel] >> 8);
        } else {
            return (UInt8)(scc->period[channel] & 0xff);
        }
    } else if (address < 0x0f) {
        // get volume
        return scc->volume[address - 0xa];
    } else {
        // get enable-bits
        return scc->enable;
    }
}

static void sccUpdateWave(SCC* scc, UInt8 channel, UInt8 address, UInt8 value)
{
    if (!scc->readOnly[channel]) {
        UInt8 pos = address & 0x1f;

        scc->wave[channel][pos] = value;

        if ((scc->mode != SCC_PLUS) && (channel == 3)) {
            scc->wave[4][pos] = scc->wave[3][pos];
        }
    }
}

static void sccUpdateFreqAndVol(SCC* scc, UInt8 address, UInt8 value)
{
    address &= 0x0f;
    if (address < 0x0a) {
        UInt8 channel = address / 2;
        UInt32 period;

        if (address & 1) {
            scc->period[channel] = ((value & 0xf) << 8) | (scc->period[channel] & 0xff);
        } 
        else {
            scc->period[channel] = (scc->period[channel] & 0xf00) | (value & 0xff);
        }
        if (scc->deformValue & 0x20) {
            scc->phaseStep[channel] = 0;
        }
        period = scc->period[channel];

        if (scc->deformValue & 2) {
            period &= 0xff;
        }
        else if (scc->deformValue & 1) {
            period >>= 8;
        }
        
        scc->phaseStep[channel] = period > 8 ? BASE_PHASE_STEP / (1 + period) : 0;
    } 
    else if (address < 0x0f) {
        scc->volume[address - 0x0a] = value & 0x0f;
    } 
    else {
        scc->enable = value;
    }
}

static void sccUpdateDeformation(SCC* scc, UInt8 value)
{
    int channel;

    if (value == scc->deformValue) {
        return;
    }

    scc->deformValue = value;
    scc->deformTime = boardSystemTime();
    
    if (scc->mode != SCC_REAL) {
        value &= ~0x80;
    }

    switch (value & 0xc0) {
        case 0x00:
            for (channel = 0; channel < 5; channel++) {
                scc->rotate[channel]   = ROTATE_OFF;
                scc->readOnly[channel] = 0;
                scc->offset[channel]   = 0;
            }
            break;
        case 0x40:
            for (channel = 0; channel < 5; channel++) {
                scc->rotate[channel]   = ROTATE_ON;
                scc->readOnly[channel] = 1;
            }
            break;
        case 0x80:
            for (channel = 0; channel < 3; channel++) {
                scc->rotate[channel]   = ROTATE_OFF;
                scc->readOnly[channel] = 0;
            }
            for (channel = 3; channel < 5; channel++) {
                scc->rotate[channel]   = ROTATE_ON;
                scc->readOnly[channel] = 1;
            }
            break;
        case 0xC0:
            for (channel = 0; channel < 3; channel++) {
                scc->rotate[channel]   = ROTATE_ON;
                scc->readOnly[channel] = 1;
            }
            for (channel = 3; channel < 5; channel++) {
                scc->rotate[channel]   = ROTATE_OFF;
                scc->readOnly[channel] = 1;
            }
            break;
    }
}

void sccReset(SCC* scc) {
    int channel;

    if (scc->mode != SCC_REAL) {
        sccSetMode(scc, SCC_COMPATIBLE);
    }

    for (channel = 0; channel < 5; channel++) {
        scc->phase[channel]     = 0;
        scc->phaseStep[channel] = 0;
        scc->volume[channel]    = 0;
        scc->rotate[channel]    = ROTATE_OFF;
        scc->readOnly[channel]  = 0;
        scc->offset[channel]    = 0;
        scc->daVolume[channel]  = 0;
    }

    scc->deformValue = 0;
    scc->enable      = 0xFF;
}

void sccSetMode(SCC* scc, SccMode newMode)
{
    scc->mode = newMode;
}

SCC* sccCreate(Mixer* mixer)
{
    SCC* scc = (SCC*)calloc(1, sizeof(SCC));

    scc->mixer = mixer;

    mixerRegisterChannel(mixer, MIXER_CHANNEL_SCC, 0, sccSync, scc);

    return scc;
}

void sccDestroy(SCC* scc)
{
    mixerUnregisterChannel(scc->mixer, MIXER_CHANNEL_SCC);
    free(scc);
}

UInt8 sccRead(SCC* scc, UInt8 address)
{
    UInt8 result;

    switch (scc->mode) {

    case SCC_REAL:
        if (address < 0x80) {
            return sccGetWave(scc, address >> 5, address);
        } 
        
        if (address < 0xa0) {
            return sccGetFreqAndVol(scc, address);
        } 
        
        if (address < 0xe0) {
            return 0xff;
        }

        sccUpdateDeformation(scc, 0xff);

        return 0xff;

    case SCC_COMPATIBLE:
        if (address < 0x80) {
            return sccGetWave(scc, address >> 5, address);
        } 
        
        if (address < 0xa0) {
            return sccGetFreqAndVol(scc, address);
        }
        
        if (address < 0xc0) {
            result = sccGetWave(scc, 4, address);
        } 

        if (address < 0xe0) {
            sccUpdateDeformation(scc, 0xff);
            return 0xff;
        }
 
        result = 0xff;

    case SCC_PLUS:
        if (address < 0xa0) {
            return sccGetWave(scc, address >> 5, address);
        } 
        
        if (address < 0xc0) {
            return sccGetFreqAndVol(scc, address);
        } 
        
        if (address < 0xe0) {
            sccUpdateDeformation(scc, 0xff);
            return 0xff;
        }

        return 0xff;
    }

    return 0xff;
}

void sccWrite(SCC* scc, UInt8 address, UInt8 value)
{
    mixerSync(scc->mixer);

    switch (scc->mode) {
    case SCC_REAL:
        if (address < 0x80) {
            sccUpdateWave(scc, address >> 5, address, value);
            return;
        } 
        
        if (address < 0xa0) {
            sccUpdateFreqAndVol(scc, address, value);
            return;
        } 
        
        if (address < 0xe0) {
            return;
        }

        sccUpdateDeformation(scc, value);
        return;

    case SCC_COMPATIBLE:
        if (address < 0x80) {
            sccUpdateWave(scc, address >> 5, address, value);
            return;
        } 
        
        if (address < 0xa0) {
            sccUpdateFreqAndVol(scc, address, value);
            return;
        } 
        
        if (address < 0xc0) {
            return;
        } 
        
        if (address < 0xe0) {
            sccUpdateDeformation(scc, value);
            return;
        } 

        return;

    case SCC_PLUS:
        if (address < 0xa0) {
            sccUpdateWave(scc, address >> 5, address, value);
            return;
        } 
        
        if (address < 0xc0) {
            sccUpdateFreqAndVol(scc, address, value);
            return;
        } 
        
        if (address < 0xe0) {
            sccUpdateDeformation(scc, value);
            return;
        }

        return;
    }
}

static Int32* sccSync(SCC* scc, UInt32 count)
{
    Int32* buffer  = scc->buffer;
    Int32  channel;

    memset(buffer, 0, sizeof(Int32) * count);

    if ((scc->deformValue & 0xc0) == 0x00) {
        /* Add sound channel data to buffer */

        for (channel = 0; channel < 5; channel++) {
            /* Precalculate values for sample generating loop */
            Int8*  waveData  = scc->wave[channel];
            Int32  volume    = 26 * (Int32)scc->volume[channel] * scc->period[channel] / (32 + scc->period[channel]);
            Int32  phaseStep = scc->phaseStep[channel] * ((scc->enable >> channel) & 1);
            Int32  phase     = scc->phase[channel];
            UInt32 index;

            /* Add to output buffer using linear interpolation */
            for (index = 0; index < count; index++) {
                phase = (phase + phaseStep) & 0xfffffff;
                scc->daVolume[channel] += 3 * (waveData[phase >> 23] * volume - scc->daVolume[channel]) / 4;
                buffer[index] += scc->daVolume[channel];
            }

            /* Save phase */
            scc->phase[channel] = phase;
        }
    }
    else {
        /* Add sound channel data to buffer */
        
        for (channel = 0; channel < 5; channel++) {
            /* Precalculate values for sample generating loop */
            Int8*  waveData  = scc->wave[channel];
            Int32  volume    = 20 * (Int32)scc->volume[channel] * scc->period[channel] / (32 + scc->period[channel]);
            Int32  phaseStep = scc->phaseStep[channel] * ((scc->enable >> channel) & 1);
            Int32  phase     = scc->phase[channel];
            UInt8  offset    = scc->offset[channel];
            Int32  rotShift  = scc->rotate[channel];
            UInt32 index;

            /* Add to output buffer using linear interpolation */
            for (index = 0; index < count; index++) {
                phase = (phase + phaseStep);
                offset += (UInt8)(phase >> rotShift);
                phase &= 0xfffffff;
                scc->daVolume[channel] += 3 * (waveData[((phase >> 23) + offset) & 0x1f] * volume - scc->daVolume[channel]) / 4;
                buffer[index] += scc->daVolume[channel];
            }

            /* Save phase */
            scc->phase[channel]  = phase;
            scc->offset[channel] = offset;
        }
    }

    return scc->buffer;
}
