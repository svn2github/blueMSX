/*****************************************************************************
** File:        audioMixer.c
**
** Author:      Daniel Vik
** 
** Description: Mixer
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
#include "audioMixer.h"
#include "Board.h"
#include "ArchTimer.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SAMPLERATE        44100
#define BITSPERSAMPLE     16
#define BUFFER_SIZE       10000

#define str2ul(s) ((UInt32)s[0]<<0|(UInt32)s[1]<<8|(UInt32)s[2]<<16|(UInt32)s[3]<<24)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static int mixerCPUFrequency;

static int mixerCPUFrequency;
static int mixerConnector;

void mixerSetBoardFrequency(int CPUFrequency)
{
	mixerCPUFrequency = CPUFrequency;
}

typedef struct {
    UInt32 riff;
    UInt32 fileSize;
    UInt32 wave;
    struct {
        UInt32 fmt;
        UInt32 chunkSize;
        UInt16 formatType;
        UInt16 channels;
        UInt32 samplesPerSec;
        UInt32 avgBytesPerSec;
        UInt16 blockAlign;
        UInt16 bitsPerSample;
    } wavHeader;
    UInt32 data;
    UInt32 dataSize;
} WavHeader;

typedef struct {
    MixerUpdateCallback updateCallback;
    void* ref;
    Int32 volume;
    Int32 pan;
    Int32 enable;
    Int32 volumeLeft;
    Int32 volumeRight;
    Int32 stereo;
    Int32 volIntLeft;
    Int32 volIntRight;
    Int32 volCntLeft;
    Int32 volCntRight;
    UInt32 active;
} Channel;

struct Mixer
{ 
    MixerWriteCallback writeCallback;
    void*  writeRef;
    Int32  fragmentSize;
    UInt32 refTime;
    UInt32 refFrag;
    UInt32 index;
    UInt32 volIndex;
    Int16   buffer[BUFFER_SIZE];
    Channel channels[MIXER_CHANNEL_COUNT];
    UInt32  oldTick;
    Int32   dummyBuffer[BUFFER_SIZE];
    Int32   logging;
    Int32   stereo;
    double  masterVolume;
    Int32   masterEnable;
    Int32   volIntLeft;
    Int32   volIntRight;
    Int32   volCntLeft;
    Int32   volCntRight;
    FILE*   file;
};

Int32 mixerGetSize() {
    return sizeof(Mixer);
}

Mixer* mixerCreate()
{
    Mixer* mixer = (Mixer*)calloc(1, sizeof(Mixer));

    return mixer;
}

void mixerDestroy(Mixer* mixer)
{
    mixerStopLog(mixer);
    free(mixer);
}


static void mixerSetChannelRecalculate(Mixer* mixer, Channel* channel)
{
    double volume        = pow(10.0, (channel->volume - 100) / 60.0) - pow(10.0, -100 / 60.0);
    double panLeft       = pow(10.0, (MIN(100 - channel->pan, 50) - 50) / 30.0) - pow(10.0, -50 / 30.0);
    double panRight      = pow(10.0, (MIN(channel->pan, 50) - 50) / 30.0) - pow(10.0, -50 / 30.0);

    channel->volumeLeft  = channel->enable * mixer->masterEnable * (Int32)(1024 * mixer->masterVolume * volume * panLeft);
    channel->volumeRight = channel->enable * mixer->masterEnable * (Int32)(1024 * mixer->masterVolume * volume * panRight);

    if (!mixer->stereo) {
        Int32 tmp = (channel->volumeLeft + channel->volumeRight) / 2;
        channel->volumeLeft  = tmp;
        channel->volumeRight = tmp;
    }
}

void mixerSetStereo(Mixer* mixer, Int32 stereo)
{
    int i;

    if (mixer->logging == 1) {
        mixerStopLog(mixer);
    }
        
    mixer->stereo = stereo;
    mixer->index = 0;

    for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
        mixerSetChannelRecalculate(mixer, mixer->channels + i);
    }
}

void mixerSetMasterVolume(Mixer* mixer, Int32 volume)
{
    int i;

    
    mixer->masterVolume = pow(10.0, (volume - 100) / 60.0) - pow(10.0, -100 / 60.0);
    
    for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
        mixerSetChannelRecalculate(mixer, mixer->channels + i);
    }
}

void mixerEnableMaster(Mixer* mixer, Int32 enable)
{
    int i;

    mixer->masterEnable = enable ? 1 : 0;

    for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
        mixerSetChannelRecalculate(mixer, mixer->channels + i);
    }
}

void mixerSetChannelVolume(Mixer* mixer, Int32 channelNumber, Int32 volume)
{
    mixer->channels[channelNumber].volume = volume;
    mixerSetChannelRecalculate(mixer, mixer->channels + channelNumber);
}

void mixerSetChannelPan(Mixer* mixer, Int32 channelNumber, Int32 pan)
{
    mixer->channels[channelNumber].pan = pan;
    mixerSetChannelRecalculate(mixer, mixer->channels + channelNumber);
}

void mixerEnableChannel(Mixer* mixer, Int32 channelNumber, Int32 enable) 
{
    mixer->channels[channelNumber].enable = enable;
    mixerSetChannelRecalculate(mixer, mixer->channels + channelNumber);
}

void mixerSetWriteCallback(Mixer* mixer, MixerWriteCallback callback, void* ref, int fragmentSize)
{
    mixer->fragmentSize = fragmentSize;
    mixer->writeCallback = callback;
    mixer->writeRef = ref;
}

void mixerRegisterChannel(Mixer* mixer, Int32 channelNumber, Int32 stereo, MixerUpdateCallback callback, void* ref)
{
    mixer->channels[channelNumber].updateCallback = callback;
    mixer->channels[channelNumber].ref            = ref;
    mixer->channels[channelNumber].stereo         = stereo;
}

void mixerUnregisterChannel(Mixer* mixer, Int32 channelNumber) 
{
    mixer->channels[channelNumber].updateCallback = NULL;
    mixer->channels[channelNumber].ref = NULL;
}


static void updateVolumes(Mixer* mixer) 
{
    int i;
    int diff = archGetSystemUpTime(100) - mixer->oldTick;

    if (diff) {
        int newVol = mixer->volIntLeft - diff;
        if (newVol < 0) newVol = 0;
        mixer->volIntLeft = newVol;

        newVol = mixer->volIntRight - diff;
        if (newVol < 0) newVol = 0;
        mixer->volIntRight = newVol;

        for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
            int newVol = mixer->channels[i].volIntLeft - diff;
            if (newVol < 0) newVol = 0;
            mixer->channels[i].volIntLeft = newVol;

            newVol = mixer->channels[i].volIntRight - diff;
            if (newVol < 0) newVol = 0;
            mixer->channels[i].volIntRight = newVol;
        }
        
        mixer->oldTick += diff;
    }
}

Int32 mixerGetChannelVolume(Mixer* mixer, Int32 channelNumber, int leftRight)
{
    updateVolumes(mixer);
    return leftRight ? mixer->channels[channelNumber].volIntRight : mixer->channels[channelNumber].volIntLeft;
}

Int32 mixerIsChannelActive(Mixer* mixer, Int32 channelNumber, Int32 reset)
{
    Int32 active = mixer->channels[channelNumber].active;

    if (reset) {
        mixer->channels[channelNumber].active = 0;
    }

    return active > 0;
}


Int32 mixerGetMasterVolume(Mixer* mixer, int leftRight)
{
    updateVolumes(mixer);
    return leftRight ? mixer->volIntRight : mixer->volIntLeft;
}

void mixerReset(Mixer* mixer)
{
    mixer->refTime = boardSystemTime();
    mixer->index = 0;
}

void mixerSync(Mixer* mixer)
{
    UInt32 systemTime = boardSystemTime();
    Int16* buffer   = mixer->buffer;
    Int32* chBuff[MIXER_CHANNEL_COUNT];
    UInt32 count;
    UInt64 elapsed;
    int i;

    elapsed        = SAMPLERATE * (UInt64)(systemTime - mixer->refTime) + mixer->refFrag;
    mixer->refTime = systemTime;
    mixer->refFrag = (UInt32)(elapsed % (mixerCPUFrequency * (boardFrequency() / 3579545)));
    count          = (UInt32)(elapsed / (mixerCPUFrequency * (boardFrequency() / 3579545)));

    if (count == 0 || count > BUFFER_SIZE) {
        return;
    }

    for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
        if (mixer->channels[i].updateCallback != NULL) {
            chBuff[i] = mixer->channels[i].updateCallback(mixer->channels[i].ref, count);
        }
        else {
            chBuff[i] = mixer->dummyBuffer;
        }
    }

    if (mixer->stereo) {
        while (count--) {
            Int32 left = 0;
            Int32 right = 0;

            for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
                Int32 chanLeft;
                Int32 chanRight;

                if (mixer->channels[i].stereo) {
                    chanLeft = mixer->channels[i].volumeLeft * *chBuff[i]++;
                    chanRight = mixer->channels[i].volumeRight * *chBuff[i]++;
                }
                else {
                    Int32 tmp = *chBuff[i]++;
                    chanLeft = mixer->channels[i].volumeLeft * tmp;
                    chanRight = mixer->channels[i].volumeRight * tmp;
                }

                mixer->channels[i].volCntLeft  += (chanLeft  > 0 ? chanLeft  : -chanLeft)  / 2048;
                mixer->channels[i].volCntRight += (chanRight > 0 ? chanRight : -chanRight) / 2048;

                left  += chanLeft;
                right += chanRight;
            }

            left  /= 4096;
            right /= 4096;

            mixer->volCntLeft  += left  > 0 ? left  : -left;
            mixer->volCntRight += right > 0 ? right : -right;

            if (left  >  32767) { left  = 32767; }
            if (left  < -32767) { left  = -32767; }
            if (right >  32767) { right = 32767; }
            if (right < -32767) { right = -32767; }

            buffer[mixer->index++] = (Int16)left;
            buffer[mixer->index++] = (Int16)right;

            if (mixer->index == mixer->fragmentSize) {
                if (mixer->writeCallback != NULL) {
                    mixer->writeCallback(mixer->writeRef, buffer, mixer->fragmentSize);
                }
                if (mixer->logging) {
                    fwrite(buffer, 2 * mixer->fragmentSize, 1, mixer->file);
                }
                mixer->index = 0;
            }

            mixer->volIndex++;
        }
    }
    else {
        while (count--) {
            Int32 left = 0;

            for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
                Int32 chanLeft;

                if (mixer->channels[i].stereo) {
                    Int32 tmp = *chBuff[i]++;
                    chanLeft = mixer->channels[i].volumeLeft * (tmp + *chBuff[i]++) / 2;
                }
                else {
                    chanLeft = mixer->channels[i].volumeLeft * *chBuff[i]++;
                }
            
                mixer->channels[i].volCntLeft  += (chanLeft > 0 ? chanLeft : -chanLeft) / 2048;
                mixer->channels[i].volCntRight += (chanLeft > 0 ? chanLeft : -chanLeft) / 2048;
                left  += chanLeft;
            }

            left  /= 4096;

            mixer->volCntLeft  += left > 0 ? left : -left;
            mixer->volCntRight += left > 0 ? left : -left;

            if (left  >  32767) left  = 32767;
            if (left  < -32767) left  = -32767;

            buffer[mixer->index++] = (Int16)left;
            
            if (mixer->index == mixer->fragmentSize) {
                if (mixer->writeCallback != NULL) {
                    mixer->writeCallback(mixer->writeRef, buffer, mixer->fragmentSize);
                }
                if (mixer->logging) {
                    fwrite(buffer, 2 * mixer->fragmentSize, 1, mixer->file);
                }
                mixer->index = 0;
            }

            mixer->volIndex++;
        }
    }

    if (mixer->volIndex >= 441) {
        Int32 newVolumeLeft  = mixer->volCntLeft  / mixer->volIndex / 164;
        Int32 newVolumeRight = mixer->volCntRight / mixer->volIndex / 164;
    
        if (newVolumeLeft > 100) {
            newVolumeLeft = 100;
        }
        if (newVolumeLeft > mixer->volIntLeft) {
            mixer->volIntLeft  = newVolumeLeft;
        }

        if (newVolumeRight > 100) {
            newVolumeRight = 100;
        }
        if (newVolumeRight > mixer->volIntRight) {
            mixer->volIntRight  = newVolumeRight;
        }

        mixer->volCntLeft  = 0;
        mixer->volCntRight = 0;

        for (i = 0; i < MIXER_CHANNEL_COUNT; i++) {
            Int32 newVolumeLeft  = (Int32)(mixer->channels[i].volCntLeft  / mixer->masterVolume / mixer->volIndex / 328);
            Int32 newVolumeRight = (Int32)(mixer->channels[i].volCntRight / mixer->masterVolume / mixer->volIndex / 328);

            if (newVolumeLeft > 100) {
                newVolumeLeft = 100;
            }
            if (newVolumeLeft > mixer->channels[i].volIntLeft) {
                mixer->channels[i].volIntLeft  = newVolumeLeft;
            }

            if (newVolumeRight > 100) {
                newVolumeRight = 100;
            }
            if (newVolumeRight > mixer->channels[i].volIntRight) {
                mixer->channels[i].volIntRight  = newVolumeRight;
            }

            mixer->channels[i].volCntLeft  = 0;
            mixer->channels[i].volCntRight = 0;

            if (chBuff[i][0]) {
                mixer->channels[i].active++;
            }
        }
        mixer->volIndex = 0;
    }
}

void mixerStartLog(Mixer* mixer, char* fileName) 
{
    if (mixer->logging == 1) {
        mixerStopLog(mixer);
    }
    mixer->file = fopen(fileName, "wb");
    if (mixer->file != NULL) {
        fseek(mixer->file, sizeof(WavHeader), SEEK_SET);
        mixer->logging = 1;
    }
}

int mixerIsLogging(Mixer* mixer) {
    return mixer->logging;
}

void mixerStopLog(Mixer* mixer) 
{
    WavHeader header;
    int fileSize;

    if (mixer->logging == 0) {
        return;
    }

    mixer->logging = 0;
    
    fileSize = ftell(mixer->file);
    
    header.riff                     = str2ul("RIFF");
    header.fileSize                 = fileSize - 8;
    header.wave                     = str2ul("WAVE");
    header.wavHeader.fmt            = str2ul("fmt ");
    header.wavHeader.chunkSize      = 16;
    header.wavHeader.formatType     = 1;
    header.wavHeader.channels       = (mixer->stereo ? 2 : 1);
    header.wavHeader.samplesPerSec  = SAMPLERATE;
    header.wavHeader.avgBytesPerSec = (mixer->stereo ? 2 : 1) * SAMPLERATE * BITSPERSAMPLE / 8;
    header.wavHeader.blockAlign     = (mixer->stereo ? 2 : 1) * BITSPERSAMPLE / 8;
    header.wavHeader.bitsPerSample  = BITSPERSAMPLE;
    header.data                     = str2ul("data");
    header.dataSize                 = fileSize - sizeof(WavHeader);

    fseek(mixer->file, 0, SEEK_SET);
    fwrite(&header, 1, sizeof(WavHeader), mixer->file);
    fclose(mixer->file);
}
