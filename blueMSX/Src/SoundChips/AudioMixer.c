/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/AudioMixer.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-26 10:09:55 $
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
    Int32 volume;
    Int32 pan;
    Int32 enable;
} AudioTypeInfo;

typedef struct {
    Int32 handle;
    MixerUpdateCallback updateCallback;
    void* ref;
    MixerAudioType type;
    // User config
    Int32 volume;
    Int32 pan;
    Int32 enable;
    Int32 stereo;
    // Internal config
    Int32 volumeLeft;
    Int32 volumeRight;
    // Intermediate volume info
    Int32 volIntLeft;
    Int32 volIntRight;
    Int32 volCntLeft;
    Int32 volCntRight;
    UInt32 active;
} MixerChannel;

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
    AudioTypeInfo audioTypeInfo[MIXER_CHANNEL_TYPE_COUNT];
    MixerChannel channels[MAX_CHANNELS];
    Int32   channelCount;
    Int32   handleCount;
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


static void recalculateChannelVolume(Mixer* mixer, MixerChannel* channel);
static void updateVolumes(Mixer* mixer);


///////////////////////////////////////////////////////

static void mixerRecalculateType(Mixer* mixer, int audioType) 
{
    AudioTypeInfo* type    = mixer->audioTypeInfo + audioType;
    int i;

    for (i = 0; i < mixer->channelCount; i++) {
        MixerChannel* channel = mixer->channels + i;
        if (channel->type == audioType) {
            channel->enable         = type->enable;
            channel->volume         = type->volume;
            channel->pan            = type->pan;
            recalculateChannelVolume(mixer, channel);
        }
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

    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerRecalculateType(mixer, i);
    }
}

void mixerSetMasterVolume(Mixer* mixer, Int32 volume)
{
    int i;

    mixer->masterVolume = pow(10.0, (volume - 100) / 60.0) - pow(10.0, -100 / 60.0);
    
    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerRecalculateType(mixer, i);
    }
}

void mixerEnableMaster(Mixer* mixer, Int32 enable)
{
    int i;

    mixer->masterEnable = enable ? 1 : 0;

    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerRecalculateType(mixer, i);
    }
}

void mixerSetChannelTypeVolume(Mixer* mixer, Int32 type, Int32 volume)
{
    mixer->audioTypeInfo[type].volume = volume;
    mixerRecalculateType(mixer, type);
}

void mixerSetChannelTypePan(Mixer* mixer, Int32 type, Int32 pan)
{
    mixer->audioTypeInfo[type].pan = pan;
    mixerRecalculateType(mixer, type);
}

void mixerEnableChannelType(Mixer* mixer, Int32 type, Int32 enable) 
{
    mixer->audioTypeInfo[type].enable = enable;
    mixerRecalculateType(mixer, type);
}

Int32 mixerGetChannelTypeVolume(Mixer* mixer, Int32 type, int leftRight)
{
    int i;
    Int32 volume = 0;

    updateVolumes(mixer);

    for (i = 0; i < mixer->channelCount; i++) {
        if (mixer->channels[i].type == type) {
            Int32 channelVol = leftRight ? 
                               mixer->channels[i].volIntRight :
                               mixer->channels[i].volIntLeft;
            if (channelVol > volume) {
                volume = channelVol;
            }
        }
    }

    return volume;
}

Int32 mixerIsChannelTypeActive(Mixer* mixer, Int32 type, Int32 reset)
{
    int i;
    Int32 active = 0;

    updateVolumes(mixer);

    for (i = 0; i < mixer->channelCount; i++) {
        if (mixer->channels[i].type == type) {
            if (mixer->channels[i].active) {
                active = 1;
            }
            if (reset) {
                mixer->channels[i].active = 0;
            }
        }
    }

    return active;
}

///////////////////////////////////////////////////////

static void recalculateChannelVolume(Mixer* mixer, MixerChannel* channel)
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

        for (i = 0; i < mixer->channelCount; i++) {
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


void mixerSetWriteCallback(Mixer* mixer, MixerWriteCallback callback, void* ref, int fragmentSize)
{
    mixer->fragmentSize = fragmentSize;
    mixer->writeCallback = callback;
    mixer->writeRef = ref;
}

Int32 mixerRegisterChannel(Mixer* mixer, Int32 audioType, Int32 stereo, MixerUpdateCallback callback, void* ref)
{
    MixerChannel*  channel = mixer->channels + mixer->channelCount;
    AudioTypeInfo* type    = mixer->audioTypeInfo + audioType;

    if (mixer->channelCount == MAX_CHANNELS - 1) {
        return 0;
    }

    mixer->channelCount++;

    channel->updateCallback = callback;
    channel->ref            = ref;
    channel->type           = audioType;
    channel->stereo         = stereo;
    channel->enable         = type->enable;
    channel->volume         = type->volume;
    channel->pan            = type->pan;
    channel->handle         = ++mixer->handleCount;

    recalculateChannelVolume(mixer, channel);

    return channel->handle;
}

void mixerUnregisterChannel(Mixer* mixer, Int32 handle) 
{
    int i;

    if (mixer->channelCount == 0) {
        return;
    }

    for (i = 0; i < mixer->channelCount; i++) {
        if (mixer->channels[i].handle == handle) {
            break;
        }
    }

    if (i == mixer->channelCount) {
        return;
    }

    mixer->channelCount--;
    while (i < mixer->channelCount) {
        mixer->channels[i] = mixer->channels[i + 1];
        i++;
    }
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
    Int32* chBuff[MAX_CHANNELS];
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

    for (i = 0; i < mixer->channelCount; i++) {
        chBuff[i] = mixer->channels[i].updateCallback(mixer->channels[i].ref, count);
    }

    if (mixer->stereo) {
        while (count--) {
            Int32 left = 0;
            Int32 right = 0;

            for (i = 0; i < mixer->channelCount; i++) {
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

            for (i = 0; i < mixer->channelCount; i++) {
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

        for (i = 0; i < mixer->channelCount; i++) {
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
