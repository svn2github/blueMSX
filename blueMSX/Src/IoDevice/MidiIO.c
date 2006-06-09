/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/MidiIO.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2006-06-09 20:30:01 $
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
    MidiType inType;
    FILE* inFile;
    ArchMidi* inHost;
    MidiType outType;
    FILE* outFile;
    ArchMidi* outHost;
};

static MidiType theMidiInType = MIDI_NONE;
static MidiType theMidiOutType = MIDI_NONE;
static char theInFileName[512] = { 0 };
static char theOutFileName[512] = { 0 };

static MidiIO* theMidiIO = NULL;


static void setOutType(MidiIO* midiIo)
{
    midiIo->outType = theMidiOutType;

    switch (midiIo->outType) {
    case MIDI_HOST:
        midiIo->outHost = archMidiOutCreate(0);
        break;
    case MIDI_FILE:
        midiIo->outFile = fopen(theOutFileName, "w+");
        break;
    }
}

static void midiInCb(MidiIO* midiIO, UInt8* buffer, UInt32 length)
{
}

static void setInType(MidiIO* midiIo)
{
    midiIo->inType = theMidiInType;

    switch (midiIo->inType) {
    case MIDI_HOST:
        midiIo->inHost = archMidiInCreate(0, midiInCb, midiIo);
        break;
    case MIDI_FILE:
        midiIo->inFile = fopen(theInFileName, "w+");
        break;
    }
}

static void removeOutType(MidiIO* midiIo)
{
    switch (midiIo->outType) {
    case MIDI_HOST:
        if (midiIo->outHost != 0) {
            archMidiOutDestroy(midiIo->outHost);
        }
        midiIo->outHost = NULL;
        break;
    case MIDI_FILE:
        fclose(midiIo->outFile);
        break;
    }
}

static void removeInType(MidiIO* midiIo)
{
    switch (midiIo->inType) {
    case MIDI_HOST:
        if (midiIo->inHost != 0) {
            archMidiInDestroy(midiIo->inHost);
        }
        midiIo->inHost = 0;
        break;
    case MIDI_FILE:
        fclose(midiIo->inFile);
        break;
    }
}

void midiIoTransmit(MidiIO* midiIo, UInt8 value)
{
    switch (midiIo->outType) {
    case MIDI_HOST:
        if (midiIo->outHost) {
            archMidiOutTransmit(midiIo->outHost, value);
        }
        break;
    case MIDI_FILE:
        fwrite(&value, 1, 1, midiIo->outFile);
        break;
    }
}

MidiIO* midiIoCreate()
{
    MidiIO* midiIo = calloc(1, sizeof(MidiIO));

    setOutType(midiIo);
    setInType(midiIo);

    theMidiIO = midiIo;

    return midiIo;
}

void midiIoDestroy(MidiIO* midiIo)
{
    removeInType(midiIo);
    removeOutType(midiIo);

    free(midiIo);

    theMidiIO = NULL;
}

void midiIoSetMidiOutType(MidiType type, const char* fileName)
{   
    theMidiOutType = type;

    strcpy(theOutFileName, fileName);
    
    if (theMidiIO == NULL) {
        return;
    }

    removeOutType(theMidiIO);
    setOutType(theMidiIO);
}

void midiIoSetMidiInType(MidiType type, const char* fileName)
{
    theMidiInType = type;

    strcpy(theInFileName, fileName);
    
    if (theMidiIO == NULL) {
        return;
    }

    removeInType(theMidiIO);
    setInType(theMidiIO);
}
