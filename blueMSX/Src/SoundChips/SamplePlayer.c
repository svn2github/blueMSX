/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/SamplePlayer.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-05-01 00:05:18 $
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
#include "SamplePlayer.h"
#include "Board.h"
#include <stdlib.h>
#include <string.h>


#define OFFSETOF(s, a) ((int)(&((s*)0)->a))

#define BUFFER_SIZE     10000

static Int32* samplePlayerSync(SamplePlayer* samplePlayer, UInt32 count);

struct SamplePlayer
{
    Mixer* mixer;
    Int32 handle;

    Int32  enabled;
    const Int16* sampleBuffer;
    UInt32 sampleCount;
    int index;
    int loop;
    Int32  ctrlVolume;
    Int32  daVolume;

    Int32  defaultBuffer[BUFFER_SIZE];
    Int32  buffer[BUFFER_SIZE];
};

void samplePlayerReset(SamplePlayer* samplePlayer) {
    samplePlayer->ctrlVolume      = 0;
    samplePlayer->daVolume        = 0;
    samplePlayer->enabled         = 0;
}

SamplePlayer* samplePlayerCreate(Mixer* mixer)
{
    SamplePlayer* samplePlayer = (SamplePlayer*)calloc(1, sizeof(SamplePlayer));

    samplePlayer->mixer = mixer;

    samplePlayerReset(samplePlayer);

    samplePlayer->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_IO, 0, samplePlayerSync, samplePlayer);

    return samplePlayer;
}

void samplePlayerDestroy(SamplePlayer* samplePlayer)
{
    mixerUnregisterChannel(samplePlayer->mixer, samplePlayer->handle);
    free(samplePlayer);
}


void samplePlayerWrite(SamplePlayer* samplePlayer, 
                       const Int16* sampleBuffer, UInt32 sampleCount, int loop)
{
    mixerSync(samplePlayer->mixer);

    samplePlayer->enabled = sampleBuffer != NULL && sampleCount > 0;
    if (samplePlayer->enabled) {
        samplePlayer->sampleBuffer = sampleBuffer;
        samplePlayer->sampleCount = sampleCount;
        samplePlayer->loop = loop;
        samplePlayer->index = 0;
    }
}

static Int32* samplePlayerSync(SamplePlayer* samplePlayer, UInt32 count)
{
    UInt32 index = 0;

    if (!samplePlayer->enabled) {
        return samplePlayer->defaultBuffer;
    }

    for (index = 0; index < count; index++) {
        Int32 sample = samplePlayer->enabled * samplePlayer->sampleBuffer[samplePlayer->index];
        if (++samplePlayer->index == samplePlayer->sampleCount) {
            if (samplePlayer->loop) {
                samplePlayer->index = 0;
            }
            else {
                samplePlayer->enabled = 0;
            }
        }

        /* Perform simple 1 pole low pass IIR filtering */
        samplePlayer->daVolume += 2 * (sample - samplePlayer->daVolume) / 3;
        samplePlayer->buffer[index] = 6 * 9 * samplePlayer->daVolume / 10;
    }

    return samplePlayer->buffer;
}


