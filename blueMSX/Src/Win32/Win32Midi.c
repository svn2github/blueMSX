/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Midi.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-07-03 09:34:13 $
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

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int devId = -1;
static UInt32 enabled = 1;
static UInt32 currVolume;
static UInt32 origVolume;

void archMidiUpdateDriver()
{
    Properties* pProperties = propGetGlobalProperties();
    int num = 0;
    int i;

    if (devId != -1) {
        w32_midiOutSetVolume(devId, origVolume);
	    w32_midiOutClose(devId);
    }

	num = w32_midiOutGetVFNsNum();

    devId = -1;
    for (i = 0; i < num; i++) {
	    const char* name = w32_midiOutGetVFN(i);
        if (name != NULL) {
            if (strcmp(name, pProperties->sound.MidiOut.name) == 0) {
                devId = w32_midiOutOpen(name);
                break;
            }
        }
    }
    if (devId == -1 && num > 0) {
	    const char* name = w32_midiOutGetVFN(i);
	    const char* desc = w32_midiOutGetRDN(i);
        if (name != NULL) {
            devId = w32_midiOutOpen(name);
            strcpy(pProperties->sound.MidiOut.name, name);
            if (desc != NULL) {
                strcpy(pProperties->sound.MidiOut.desc, desc);
            }
            else {
                pProperties->sound.MidiOut.desc[0] = 0;
            }
        }
    }

    if (devId != -1) {
        origVolume = w32_midiOutGetVolume(devId);
        w32_midiOutSetVolume(devId, currVolume * enabled);
    }
}

int archMidiCreate(void) 
{
    return devId != -1;
}

void archMidiDestroy(void)
{
}

void archMidiEnable(int enable)
{
    enabled = enable;
    if (devId != -1) {
        w32_midiOutSetVolume(devId, currVolume * enabled);
    }
}

void archMidiUpdateVolume(int left, int right)
{
    currVolume = MIN(left * 100, 0xffff) | (MIN(right * 100, 0xffff) << 16);
    if (devId != -1) {
        w32_midiOutSetVolume(devId, currVolume * enabled);
    }
}

int archMidiGetNoteOn()
{
    if (devId != -1) {
        return w32_midiOutNoteOn(devId);
    }
    return 0;
}

int archMidiTransmit(unsigned char value) {
    if (devId != -1) {
    	w32_midiOutPut(value, devId);
    }
    return 1;
}


void midiInitialize()
{
	w32_midiOutInit();
    w32_midiInInit();

    archMidiUpdateDriver();
}

void midiShutdown()
{
    if (devId != -1) {
        w32_midiOutSetVolume(devId, origVolume);
	    w32_midiOutClose(devId);
    }
    w32_midiOutClean();
    w32_midiInClean();
}
