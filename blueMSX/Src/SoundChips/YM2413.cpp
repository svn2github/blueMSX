/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/YM2413.cpp,v $
**
** $Revision: 1.9 $
**
** $Date: 2005-02-08 00:48:09 $
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
#include "YM2413.h"
#include "openMsxYM2413.h"
extern "C" {
#include "Board.h"
#include "SaveState.h"
#include "IoPort.h"
#include "romMapper.h"
#include "DeviceManager.h"
}


#define FREQUENCY        3579545
#define SAMPLERATE       44100
#define BUFFER_SIZE      10000
 
struct YM_2413 {
    YM_2413() : ym2413("ym2413", 100, 0), address(0) {
        memset(defaultBuffer, 0, sizeof(defaultBuffer));
    }

    Mixer* mixer;
    Int32  handle;

    OpenYM2413 ym2413;
    UInt8  address;
    UInt8  registers[256];
    Int32  buffer[BUFFER_SIZE];
    Int32  defaultBuffer[BUFFER_SIZE];
};

extern "C" {
    
void ym2413SaveState(YM_2413* ref)
{
    YM_2413* ym2413 = (YM_2413*)ref;
    SaveState* state = saveStateOpenForWrite("msxmusic");

    saveStateSetBuffer(state, "regs", ym2413->registers, 256);

    saveStateClose(state);

    ym2413->ym2413.saveState();
}

void ym2413LoadState(YM_2413* ref)
{
    YM_2413* ym2413 = (YM_2413*)ref;
    SaveState* state = saveStateOpenForRead("msxmusic");

    saveStateGetBuffer(state, "regs", ym2413->registers, 256);

    saveStateClose(state);

    ym2413->ym2413.loadState();
}

void ym2413Reset(YM_2413* ref)
{
    YM_2413* ym2413 = (YM_2413*)ref;

    ym2413->ym2413.reset(msxSystemTime());
}

void ym2413WriteAddress(YM_2413* ym2413, UInt8 address)
{
    ym2413->address = address & 0x3f;
}

void ym2413WriteData(YM_2413* ym2413, UInt8 data)
{
    UInt32 systemTime = boardSystemTime();
    mixerSync(ym2413->mixer);
    ym2413->registers[ym2413->address & 0xff] = data;
    ym2413->ym2413.writeReg(ym2413->address, data, systemTime);
}

static Int32* sync(void* ref, UInt32 count) 
{
    YM_2413* ym2413 = (YM_2413*)ref;
    int* genBuf;
    UInt32 i;

    genBuf = ym2413->ym2413.updateBuffer(count);

    if (genBuf == NULL) {
        return ym2413->defaultBuffer;
    }

    for (i = 0; i < count; i++) {
        ym2413->buffer[i] = genBuf[i];
    }

    return ym2413->buffer;
}

YM_2413* ym2413Create(Mixer* mixer)
{
    YM_2413* ym2413;

    ym2413 = new YM_2413;

    ym2413->mixer = mixer;

    ym2413->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_MSXMUSIC, 0, sync, ym2413);

    ym2413->ym2413.setSampleRate(SAMPLERATE, boardGetYm2413Oversampling());
	ym2413->ym2413.setVolume(32767 * 9 / 10);

    return ym2413;
}

void ym2413Destroy(YM_2413* ym2413) 
{
    mixerUnregisterChannel(ym2413->mixer, ym2413->handle);
    delete ym2413;
}



}
