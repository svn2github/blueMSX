/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/MidiIO.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-09-24 00:09:49 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Tomas Karlsson
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
#include <stdlib.h>
#include <string.h>
#include "MidiIO.h"
#include "ArchUart.h"
#include "DAC.h"
#include "Board.h"
#include "ArchMidi.h"

typedef struct MidiIO {
    MidiType type;
    FILE* file;
    int  uartReady;
};

static MidiType theMidiOutType = MIDI_NONE;
static MidiIO* theMidiIO = NULL;
static char theFileName[512] = { 0 };


static void setType(MidiIO* midiIo)
{
    midiIo->type = theMidiOutType;

    switch (midiIo->type) {
    case MIDI_HOST:
        midiIo->uartReady = archMidiCreate();
        break;
    case MIDI_FILE:
        midiIo->file = fopen(theFileName, "w+");
        break;
    }
}

static void removeType(MidiIO* midiIo)
{
    switch (midiIo->type) {
    case MIDI_HOST:
        archMidiDestroy();
        midiIo->uartReady = 0;
        break;
    case MIDI_FILE:
        fclose(midiIo->file);
        break;
    }
}

void midiIoTransmit(MidiIO* midiIo, UInt8 value)
{
    switch (midiIo->type) {
    case MIDI_HOST:
        archMidiTransmit(value);
        break;
    case MIDI_FILE:
        fwrite(&value, 1, 1, midiIo->file);
        break;
    }
}

MidiIO* midiIoCreate()
{
    MidiIO* midiIo = calloc(1, sizeof(MidiIO));

    setType(midiIo);

    theMidiIO = midiIo;

    return midiIo;
}

void midiIoDestroy(MidiIO* midiIo)
{
    removeType(midiIo);

    free(midiIo);

    theMidiIO = NULL;
}

void midiIoSetMidiOutType(MidiType type, const char* fileName)
{   
    theMidiOutType = type;

    strcpy(theFileName, fileName);
    
    if (theMidiIO == NULL) {
        return;
    }

    archMidiUpdateDriver();

    removeType(theMidiIO);
    setType(theMidiIO);
}
