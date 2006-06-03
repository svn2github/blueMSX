/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Midi.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2006-06-03 17:55:54 $
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
#include "Win32Midi.h"
#include "Midi_w32.h"
#include "Properties.h"
#include "MsxTypes.h"
#include "ArchMidi.h"
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int devIdIn  = -1;
static int devIdOut = -1;
static UInt32 enabled = 1;
static UInt32 currVolume;
static UInt32 origVolume;


ArchMidiInCb midiInCb = NULL;
void*        midiInRef;

static void midiInCallback(void* ref, const char* buffer, unsigned length)
{
    if (devIdIn != -1 && midiInCb != NULL) {
        midiInCb(midiInRef, buffer, length);
    }
}

void archMidiEnable(int enable)
{
    enabled = enable;
    if (devIdOut != -1) {
        w32_midiOutSetVolume(devIdOut, currVolume * enabled);
    }
}

void archMidiUpdateDriver()
{
    Properties* pProperties = propGetGlobalProperties();
    int num = 0;
    int i;

    if (devIdOut != -1) {
        w32_midiOutSetVolume(devIdOut, origVolume);
	    w32_midiOutClose(devIdOut);
    }

	num = w32_midiOutGetVFNsNum();

    devIdOut = -1;
    for (i = 0; i < num; i++) {
	    const char* name = w32_midiOutGetVFN(i);
        if (name != NULL) {
            if (strcmp(name, pProperties->sound.MidiOut.name) == 0) {
                devIdOut = w32_midiOutOpen(name);
                break;
            }
        }
    }
    if (devIdOut == -1 && num > 0) {
	    const char* name = w32_midiOutGetVFN(0); //was i
	    const char* desc = w32_midiOutGetRDN(0); //was i
        if (name != NULL) {
            devIdOut = w32_midiOutOpen(name);
            strcpy(pProperties->sound.MidiOut.name, name);
            if (desc != NULL) {
                strcpy(pProperties->sound.MidiOut.desc, desc);
            }
            else {
                pProperties->sound.MidiOut.desc[0] = 0;
            }
        }
    }

    if (devIdOut != -1) {
        origVolume = w32_midiOutGetVolume(devIdOut);
        w32_midiOutSetVolume(devIdOut, currVolume * enabled);
        w32_midiOutEnableMt32ToGmMapping(devIdOut, pProperties->sound.MidiOut.mt32ToGm);
    }

    if (devIdIn  != -1) {
	    w32_midiInClose(devIdOut);
    }

	num = w32_midiInGetVFNsNum();

    devIdIn = -1;
    for (i = 0; i < num; i++) {
	    const char* name = w32_midiInGetVFN(i);
        if (name != NULL) {
            if (strcmp(name, pProperties->sound.MidiIn.name) == 0) {
                devIdIn = w32_midiInOpen(name, midiInCallback, NULL);
                break;
            }
        }
    }
    if (devIdIn == -1 && num > 0) {
	    const char* name = w32_midiInGetVFN(0); //was i
	    const char* desc = w32_midiInGetRDN(0); //was i
        if (name != NULL) {
            devIdIn = w32_midiInOpen(name, midiInCallback, NULL);
            strcpy(pProperties->sound.MidiIn.name, name);
            if (desc != NULL) {
                strcpy(pProperties->sound.MidiIn.desc, desc);
            }
            else {
                pProperties->sound.MidiIn.desc[0] = 0;
            }
        }
    }
}

int archMidiOutCreate(void) 
{
    w32_resetHistory();
    return devIdOut != -1;
}

void archMidiOutDestroy(void)
{
    devIdOut = -1;
}

void archMidiOutUpdateVolume(int left, int right)
{
    currVolume = MIN(left * 100, 0xffff) | (MIN(right * 100, 0xffff) << 16);
    if (devIdOut != -1) {
        w32_midiOutSetVolume(devIdOut, currVolume * enabled);
    }
}

int archMidiOutGetNoteOn()
{
    if (devIdOut != -1) {
        return w32_midiOutNoteOn(devIdOut);
    }
    return 0;
}

int archMidiOutTransmit(unsigned char value) {
    if (devIdOut != -1) {
    	w32_midiOutPut(value, devIdOut);
    }
    return 1;
}

int archMidiInCreate(ArchMidiInCb cb, void* ref) 
{
    if (devIdIn == -1) {
        midiInCb  = cb;
        midiInRef = ref;
    }
    return devIdIn != -1;
}

void archMidiInDestroy(void)
{
    midiInCb = NULL;
    devIdIn = -1;
}

void midiInitialize()
{
	w32_midiOutInit();
    w32_midiInInit();

    archMidiUpdateDriver();
}

void midiShutdown()
{
    if (devIdOut != -1) {
        w32_midiOutSetVolume(devIdOut, origVolume);
	    w32_midiOutClose(devIdOut);
    }
    w32_midiOutClean();
    w32_midiInClean();
}

// Shared methods

void archMidiLoadState(void)
{
    if (devIdOut != -1) {
        w32_midiOutLoadState(devIdOut);
    }
}

void archMidiSaveState(void)
{
    if (devIdOut != -1) {
        w32_midiOutSaveState(devIdOut);
    }
}
