/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/YM2413.cpp,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 08:00:54 $
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
    Int32  Oversampling;
    Int32  deviceHandle;
    OpenYM2413 ym2413;
    UInt8  address;
    UInt8  registers[256];
    Int32  buffer[BUFFER_SIZE];
    Int32  defaultBuffer[BUFFER_SIZE];
};

static YM_2413* theYm2413 = NULL;

extern "C" static void destroy(void* ref) {
    YM_2413* ym2413 = (YM_2413*)ref;

    theYm2413 = NULL;

    deviceManagerUnregister(ym2413->deviceHandle);

    ioPortUnregister(0x7c);
    ioPortUnregister(0x7d);

    mixerUnregisterChannel(ym2413->mixer, MIXER_CHANNEL_MSXMUSIC);
    delete ym2413;
}

extern "C" static void saveState(void* ref)
{
    YM_2413* ym2413 = (YM_2413*)ref;
    SaveState* state = saveStateOpenForWrite("msxmusic");

    saveStateSetBuffer(state, "regs", ym2413->registers, 256);

    saveStateClose(state);

    ym2413->ym2413.saveState();
}

extern "C" static void loadState(void* ref)
{
    YM_2413* ym2413 = (YM_2413*)ref;
    SaveState* state = saveStateOpenForRead("msxmusic");

    saveStateGetBuffer(state, "regs", ym2413->registers, 256);

    saveStateClose(state);

    ym2413->ym2413.loadState();
}

extern "C" static void reset(void* ref)
{
    YM_2413* ym2413 = (YM_2413*)ref;

    ym2413->ym2413.reset(msxSystemTime());
}


extern "C" void ym2413WriteAddress(YM_2413* ym2413, UInt16 ioPort, UInt8 address)
{
    ym2413->address = address;
}

extern "C" void ym2413WriteData(YM_2413* ym2413, UInt16 ioPort, UInt8 data)
{
    UInt32 systemTime = boardSystemTime();
    mixerSync(ym2413->mixer);
    ym2413->registers[ym2413->address & 0xff] = data;
    ym2413->ym2413.writeReg(ym2413->address, data, systemTime);
}

extern "C" static Int32* sync(void* ref, UInt32 count) 
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

extern "C" void ym2413SetOversampling(int Oversampling)
{
    if (theYm2413 && Oversampling > 0) {
        theYm2413->Oversampling = Oversampling;
        
        theYm2413->ym2413.setSampleRate(SAMPLERATE, theYm2413->Oversampling);
    }
}

extern "C" int ym2413Create(Mixer* mixer)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    YM_2413* ym2413 = new YM_2413;

    theYm2413 = ym2413;

    ym2413->mixer = mixer;
    ym2413->Oversampling = 1;
    ym2413->deviceHandle = deviceManagerRegister(AUDIO_YM2413, &callbacks, ym2413);

    mixerRegisterChannel(mixer, MIXER_CHANNEL_MSXMUSIC, 0, sync, ym2413);

    ym2413->ym2413.setSampleRate(SAMPLERATE, ym2413->Oversampling);
	ym2413->ym2413.setVolume(32767);
    
    ioPortRegister(0x7c, NULL, (IoPortWrite)ym2413WriteAddress, ym2413);
    ioPortRegister(0x7d, NULL, (IoPortWrite)ym2413WriteData,    ym2413);

    return 1;
}
