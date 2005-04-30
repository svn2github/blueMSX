/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/DAC.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2005-04-30 20:56:41 $
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
#include "DAC.h"
#include "Board.h"
#include <stdlib.h>
#include <string.h>


#define OFFSETOF(s, a) ((int)(&((s*)0)->a))

#define BUFFER_SIZE     10000

static Int32* dacSync(DAC* dac, UInt32 count);

struct DAC
{
    Mixer* mixer;
    Int32 handle;

    Int32  enabled;
    Int32  sampleVolume;
    Int32  oldSampleVolume;
    Int32  sampleVolumeSum;
    Int32  count;
    Int32  ctrlVolume;
    Int32  daVolume;

    Int32  defaultBuffer[BUFFER_SIZE];
    Int32  buffer[BUFFER_SIZE];
};

void dacReset(DAC* dac) {
    dac->oldSampleVolume = 0;
    dac->sampleVolume    = 0;
    dac->ctrlVolume      = 0;
    dac->daVolume        = 0;
}

DAC* dacCreate(Mixer* mixer)
{
    DAC* dac = (DAC*)calloc(1, sizeof(DAC));

    dac->mixer = mixer;

    dacReset(dac);

    dac->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_PCM, 0, dacSync, dac);

    return dac;
}

void dacDestroy(DAC* dac)
{
    mixerUnregisterChannel(dac->mixer, dac->handle);
    free(dac);
}


void dacWrite(DAC* dac, UInt8 value)
{
    Int32 sampleVolume = ((Int32)value - 0x80) * 256;
    mixerSync(dac->mixer);
    dac->sampleVolume = sampleVolume;
    dac->sampleVolumeSum += sampleVolume;
    dac->count++;
    dac->enabled = 1;
}

static Int32* dacSync(DAC* dac, UInt32 count)
{
    UInt32 index = 0;

    if (!dac->enabled || count == 0) {
        return dac->defaultBuffer;
    }

    if (dac->count > 0) {
        Int32 sampleVolume = dac->sampleVolumeSum / dac->count;
        dac->count = 0;
        dac->sampleVolumeSum = 0;
        dac->ctrlVolume = sampleVolume - dac->oldSampleVolume + 0x3fe7 * dac->ctrlVolume / 0x4000;
        dac->oldSampleVolume = sampleVolume;
        dac->ctrlVolume = 0x3fe7 * dac->ctrlVolume / 0x4000;

        dac->daVolume += 2 * (dac->ctrlVolume - dac->daVolume) / 3;
        dac->buffer[index] = 6 * 9 * dac->daVolume / 10;
    }

    dac->ctrlVolume = dac->sampleVolume - dac->oldSampleVolume + 0x3fe7 * dac->ctrlVolume / 0x4000;
    dac->oldSampleVolume = dac->sampleVolume;

    for (; index < count; index++) {
        /* Perform DC offset filtering */
        dac->ctrlVolume = 0x3fe7 * dac->ctrlVolume / 0x4000;

        /* Perform simple 1 pole low pass IIR filtering */
        dac->daVolume += 2 * (dac->ctrlVolume - dac->daVolume) / 3;
        dac->buffer[index] = 6 * 9 * dac->daVolume / 10;
    }

    dac->enabled = dac->buffer[count - 1] != 0;

    return dac->buffer;
}
