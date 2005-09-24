/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Properties.c,v $
**
** $Revision: 1.35 $
**
** $Date: 2005-09-24 00:09:49 $
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
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef USE_XMLFORMAT
#include "VeryTinyXpath.h"
#else
#ifdef USE_NATIVEINI
#include "ArchKeyStorage.h"
#else
#include "IniFileParser.h"
#endif
#endif
#include "Properties.h"
#include "Machine.h"
#include "Board.h"


/* Default property settings */
void propInitDefaults(Properties* properties, int langType, PropKeyboardLanguage kbdLang, int syncMode, const char* themeName) 
{
    int i;
    properties->language                      = langType;

    properties->settings.showStatePreview     = 1;
    properties->settings.disableScreensaver   = 0;
    
    strcpy(properties->settings.themeName, themeName);

    memset(properties->settings.windowPos, 0, sizeof(properties->settings.windowPos));

    properties->emulation.statsDefDir[0]     = 0;
    properties->emulation.shortcutProfile[0] = 0;
    strcpy(properties->emulation.machineName, "MSX2");
    properties->emulation.speed             = 50;
    properties->emulation.syncMethod        = syncMode ? P_EMU_SYNCTOVBLANK : P_EMU_SYNCAUTO;
    properties->emulation.vdpSyncMode       = P_VDP_SYNCAUTO;
    properties->emulation.enableFdcTiming   = 1;
    properties->emulation.frontSwitch       = 0;
    properties->emulation.pauseSwitch       = 0;
    properties->emulation.audioSwitch       = 0;
    properties->emulation.registerFileTypes = 0;
    properties->emulation.disableWinKeys    = 0;
    properties->emulation.priorityBoost     = 0;

    properties->video.monType               = P_VIDEO_COLOR;
    properties->video.palEmu                = P_VIDEO_PALMON;
    properties->video.size                  = P_VIDEO_SIZEX2;
    properties->video.driver                = P_VIDEO_DRVDIRECTX_VIDEO;
    properties->video.frameSkip             = P_VIDEO_FSKIP0;
    properties->video.fullscreen.width      = 640;
    properties->video.fullscreen.height     = 480;
    properties->video.fullscreen.bitDepth   = 32;
    properties->video.deInterlace           = 1;
    properties->video.horizontalStretch     = 1;
    properties->video.verticalStretch       = 0;
    properties->video.contrast              = 100;
    properties->video.brightness            = 100;
    properties->video.saturation            = 100;
    properties->video.gamma                 = 100;
    properties->video.scanlinesEnable       = 0;
    properties->video.colorSaturationEnable = 0;
    properties->video.scanlinesPct          = 92;
    properties->video.colorSaturationWidth  = 2;
    properties->video.chipAutodetect        = 1;

    properties->sound.driver           = P_SOUND_DRVDIRECTX;
    properties->sound.frequency        = P_SOUND_FREQ44;
    properties->sound.bufSize          = 100;
    properties->sound.syncMethod       = P_SOUND_SYNCQADJUST;

    properties->sound.stereo = 1;
    properties->sound.masterVolume = 75;
    properties->sound.masterEnable = 1;
    properties->sound.chip.enableYM2413 = 1;
    properties->sound.chip.enableY8950 = 1;
    properties->sound.chip.enableMoonsound = 1;
    properties->sound.chip.moonsoundSRAMSize = 640;
    
    properties->sound.chip.ym2413Oversampling = 1;
    properties->sound.chip.y8950Oversampling = 1;
    properties->sound.chip.moonsoundOversampling = 1;

    properties->sound.mixerChannel[MIXER_CHANNEL_PSG].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan = 42;
    properties->sound.mixerChannel[MIXER_CHANNEL_PSG].volume = 100;

    properties->sound.mixerChannel[MIXER_CHANNEL_SCC].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan = 58;
    properties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume = 100;

    properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan = 58;
    properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume = 95;

    properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan = 50;
    properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume = 95;

    properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan = 50;
    properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume = 95;

    properties->sound.mixerChannel[MIXER_CHANNEL_PCM].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan = 48;
    properties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume = 95;

    properties->sound.mixerChannel[MIXER_CHANNEL_IO].enable = 0;
    properties->sound.mixerChannel[MIXER_CHANNEL_IO].pan = 70;
    properties->sound.mixerChannel[MIXER_CHANNEL_IO].volume = 50;

    properties->sound.mixerChannel[MIXER_CHANNEL_MIDI].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_MIDI].pan = 50;
    properties->sound.mixerChannel[MIXER_CHANNEL_MIDI].volume = 90;

    properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].enable = 1;
    properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan = 54;
    properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume = 65;
    
    properties->sound.MidiIn.type             = P_MIDI_NONE;
    properties->sound.MidiIn.name[0]          = 0;
    strcpy(properties->sound.MidiIn.fileName, "midiin.dat");
    properties->sound.MidiIn.desc[0]          = 0;
    properties->sound.MidiOut.type            = P_MIDI_NONE;
    properties->sound.MidiOut.name[0]         = 0;
    strcpy(properties->sound.MidiOut.fileName, "midiout.dat");
    properties->sound.MidiOut.desc[0]         = 0;
    properties->sound.MidiOut.mt32ToGm        = 0;
    
    properties->joy1.type              = P_JOY_NONE;
    properties->joy1.autofire          = P_JOY_AFOFF;
    properties->joy1.keyUp             = 0xff;
    properties->joy1.keyDown           = 0xff;
    properties->joy1.keyLeft           = 0xff;
    properties->joy1.keyRight          = 0xff;
    properties->joy1.button1           = 0xff;
    properties->joy1.button2           = 0xff;
    properties->joy1.hwType            = 0;
    properties->joy1.hwName[0]         = 0;
    properties->joy1.hwIndex           = 0;
    properties->joy1.hwButtonA         = 0;
    properties->joy1.hwButtonB         = 1;
    
    properties->joy2.type              = P_JOY_NONE;
    properties->joy2.autofire          = P_JOY_AFOFF;
    properties->joy2.keyUp             = 0xff;
    properties->joy2.keyDown           = 0xff;
    properties->joy2.keyLeft           = 0xff;
    properties->joy2.keyRight          = 0xff;
    properties->joy2.button1           = 0xff;
    properties->joy2.button2           = 0xff;
    properties->joy2.hwType            = 0;
    properties->joy2.hwName[0]         = 0;
    properties->joy2.hwIndex           = 0;
    properties->joy2.hwButtonA         = 0;
    properties->joy2.hwButtonB         = 1;
    
    properties->keyboard.configFile[0] = 0;

    if (kbdLang == P_KBD_JAPANESE) {
        strcpy(properties->keyboard.configFile, "blueMSX Japanese Default");
    }

    properties->cartridge.defaultType  = ROM_UNKNOWN;
    properties->cartridge.defDir[0]    = 0;
    properties->cartridge.slotA[0]     = 0;
    properties->cartridge.slotAType    = ROM_UNKNOWN;
    properties->cartridge.slotB[0]     = 0;
    properties->cartridge.slotBType    = ROM_UNKNOWN;
    properties->cartridge.slotAZip[0]  = 0;
    properties->cartridge.slotBZip[0]  = 0;
    properties->cartridge.autoReset    = 1;
    properties->cartridge.quickStartDrive = 0;

    
    properties->diskdrive.defDir[0]    = 0;
    properties->diskdrive.slotA[0]     = 0;
    properties->diskdrive.slotB[0]     = 0;
    properties->diskdrive.slotAZip[0]  = 0;
    properties->diskdrive.slotBZip[0]  = 0;
    properties->diskdrive.slotADir[0]  = 0;
    properties->diskdrive.slotBDir[0]  = 0;
    properties->diskdrive.autostartA   = 0;
    properties->diskdrive.quickStartDrive = 0;


    properties->cassette.defDir[0]       = 0;
    properties->cassette.tape[0]         = 0;
    properties->cassette.tapeZip[0]      = 0;
    properties->cassette.showCustomFiles = 1;
    properties->cassette.readOnly        = 1;
    properties->cassette.autoRewind      = 0;

    properties->ports.Lpt.type           = P_LPT_NONE;
    properties->ports.Lpt.emulation      = P_LPT_MSXPRN;
    properties->ports.Lpt.name[0]        = 0;
    strcpy(properties->ports.Lpt.fileName, "printer.dat");
    properties->ports.Lpt.portName[0]    = 0;
    
    properties->ports.Com.type           = P_COM_NONE;
    properties->ports.Com.name[0]        = 0;
    strcpy(properties->ports.Com.fileName, "uart.dat");
    properties->ports.Com.portName[0]    = 0;

    for (i = 0; i < MAX_HISTORY; i++) {
        properties->filehistory.cartridgeA[i][0] = 0;
        properties->filehistory.cartridgeTypeA[i] = ROM_UNKNOWN;
        properties->filehistory.cartridgeB[i][0] = 0;
        properties->filehistory.cartridgeTypeB[i] = ROM_UNKNOWN;
        properties->filehistory.diskdriveA[i][0] = 0;
        properties->filehistory.diskdriveB[i][0] = 0;
        properties->filehistory.cassette[i][0] = 0;
    }

    properties->filehistory.quicksave[0] = 0;
    properties->filehistory.count        = 10;
}

#define ROOT_ELEMENT "bluemsx"

#ifdef USE_XMLFORMAT

#define GET_INT_VALUE_1(v1) {                                                           \
    int val = vtXpathGetInt(xpath, 2, ROOT_ELEMENT, #v1);                               \
    if (val != VTXPATH_INT_NOT_FOUND) properties->v1 = val;                            \
}

#define GET_INT_VALUE_2(v1, v2) {                                                       \
    int val = vtXpathGetInt(xpath, 3, ROOT_ELEMENT, #v1, #v2);                          \
    if (val != VTXPATH_INT_NOT_FOUND) properties->v1.v2 = val;                         \
}

#define GET_INT_VALUE_3(v1, v2, v3) {                                                   \
    int val = vtXpathGetInt(xpath, 4, ROOT_ELEMENT, #v1, #v2, #v3);                     \
    if (val != VTXPATH_INT_NOT_FOUND) properties->v1.v2.v3 = val;                      \
}

#define GET_INT_VALUE_2s1(v1, v2, s, a1) {                                              \
    int val = vtXpathGetInt(xpath, 5, ROOT_ELEMENT, #v1, #v2, #s, #a1);                 \
    if (val != VTXPATH_INT_NOT_FOUND) properties->v1.v2[s].a1 = val;                   \
}

#define GET_INT_VALUE_2i(v1, v2, i) {                                                   \
    int val; char s[64]; sprintf(s, "idx_%d", i);                                       \
    val = vtXpathGetInt(xpath, 4, ROOT_ELEMENT, #v1, #v2, s);                           \
    if (val != VTXPATH_INT_NOT_FOUND) properties->v1.v2[i] = val;                      \
}

#define GET_INT_VALUE_2i1(v1, v2, i, a1) {                                              \
    int val; char s[64]; sprintf(s, "idx_%d", i);                                       \
    val = vtXpathGetInt(xpath, 5, ROOT_ELEMENT, #v1, #v2, s, #a1);                      \
    if (val != VTXPATH_INT_NOT_FOUND) properties->v1.v2[i].a1 = val;                   \
}

#define GET_STR_VALUE_1(v1) {                                                           \
    const char* val = vtXpathGetString(xpath, 2, ROOT_ELEMENT, #v1);                    \
    if (val != NULL) strcpy(properties->v1, val);                                      \
}

#define GET_STR_VALUE_2(v1, v2) {                                                       \
    const char* val = vtXpathGetString(xpath, 3, ROOT_ELEMENT, #v1, #v2);               \
    if (val != NULL) strcpy(properties->v1.v2, val);                                   \
}

#define GET_STR_VALUE_3(v1, v2, v3) {                                                   \
    const char* val = vtXpathGetString(xpath, 4, ROOT_ELEMENT, #v1, #v2, #v3);          \
    if (val != NULL) strcpy(properties->v1.v2.v3, val);                                \
}

#define GET_STR_VALUE_2s1(v1, v2, s, a1) {                                              \
    const char* val = vtXpathGetString(xpath, 5, ROOT_ELEMENT, #v1, #v2, s, #a1);       \
    if (val != NULL) strcpy(properties->v1.v2[s].a1, val);                             \
}

#define GET_STR_VALUE_2i(v1, v2, i) {                                                   \
    const char* val; char s[64]; sprintf(s, "idx_%d", i);                               \
    val = vtXpathGetString(xpath, 4, ROOT_ELEMENT, #v1, #v2, s);                        \
    if (val != NULL) strcpy(properties->v1.v2[i], val);                                \
}

#define GET_STR_VALUE_2i1(v1, v2, i, a1) {                                              \
    const char* val; char s[64]; sprintf(s, "idx_%d", i);                               \
    val = vtXpathGetString(xpath, 5, ROOT_ELEMENT, #v1, #v2, s, #a1);                   \
    if (val != NULL) strcpy(properties->v1.v2[i].a1, val);                             \
}

#define SET_INT_VALUE_1(v1) {                                                           \
    vtXpathSetInt(xpath, properties->v1, 2, ROOT_ELEMENT, #v1);                        \
}

#define SET_INT_VALUE_2(v1, v2) {                                                       \
    vtXpathSetInt(xpath, properties->v1.v2, 3, ROOT_ELEMENT, #v1, #v2);                \
}

#define SET_INT_VALUE_3(v1, v2, v3) {                                                   \
    vtXpathSetInt(xpath, properties->v1.v2.v3, 4, ROOT_ELEMENT, #v1, #v2, #v3);        \
}

#define SET_INT_VALUE_2s1(v1, v2, s, a1) {                                              \
    vtXpathSetInt(xpath, properties->v1.v2[s].a1, 5, ROOT_ELEMENT, #v1, #v2, #s, #a1); \
}

#define SET_INT_VALUE_2i(v1, v2, i) {                                                   \
    char s[64]; sprintf(s, "idx_%d", i);                                                \
    vtXpathSetInt(xpath, properties->v1.v2[i], 4, ROOT_ELEMENT, #v1, #v2, s);          \
}

#define SET_INT_VALUE_2i1(v1, v2, i, a1) {                                              \
    char s[64]; sprintf(s, "idx_%d", i);                                                \
    vtXpathSetInt(xpath, properties->v1.v2[i].a1, 5, ROOT_ELEMENT, #v1, #v2, s, #a1);  \
}

#define SET_STR_VALUE_1(v1) {                                                               \
    vtXpathSetString(xpath, properties->v1, 2, ROOT_ELEMENT, #v1);                         \
}

#define SET_STR_VALUE_2(v1, v2) {                                                           \
    vtXpathSetString(xpath, properties->v1.v2, 3, ROOT_ELEMENT, #v1, #v2);                 \
}

#define SET_STR_VALUE_3(v1, v2, v3) {                                                       \
    vtXpathSetString(xpath, properties->v1.v2.v3, 4, ROOT_ELEMENT, #v1, #v2, #v3);         \
}

#define SET_STR_VALUE_2s1(v1, v2, s, a1) {                                                  \
    vtXpathSetString(xpath, properties->v1.v2[s].a1, 5, ROOT_ELEMENT, #v1, #v2, #s, #a1);  \
}

#define SET_STR_VALUE_2i(v1, v2, i) {                                                       \
    char s[64]; sprintf(s, "idx_%d", i);                                                    \
    vtXpathSetString(xpath, properties->v1.v2[i], 4, ROOT_ELEMENT, #v1, #v2, s);           \
}

#define SET_STR_VALUE_2i1(v1, v2, i, a1) {                                                  \
    char s[64]; sprintf(s, "idx_%d", i);                                                    \
    vtXpathSetString(xpath, properties->v1.v2[i].a1, 5, ROOT_ELEMENT, #v1, #v2, s, #a1);   \
}

#else

#ifndef USE_NATIVEINI

#define GET_INT_VALUE_1(v1)         properties->v1 = iniFileGetInt(ROOT_ELEMENT, #v1, properties->v1);
#define GET_INT_VALUE_2(v1,v2)      properties->v1.v2 = iniFileGetInt(ROOT_ELEMENT, #v1 "." #v2, properties->v1.v2);
#define GET_INT_VALUE_3(v1,v2,v3)   properties->v1.v2.v3 = iniFileGetInt(ROOT_ELEMENT, #v1 "." #v2 "." #v3, properties->v1.v2.v3);
#define GET_INT_VALUE_2s1(v1,v2,v3,v4) properties->v1.v2[v3].v4 = iniFileGetInt(ROOT_ELEMENT, #v1 "." #v2 "." #v3 "." #v4, properties->v1.v2[v3].v4);
#define GET_INT_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); properties->v1.v2[i] = iniFileGetInt(ROOT_ELEMENT, s, properties->v1.v2[i]); }
#define GET_INT_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); properties->v1.v2[i].a1 = iniFileGetInt(ROOT_ELEMENT, s, properties->v1.v2[i].a1); }

#define GET_STR_VALUE_1(v1)         iniFileGetString(ROOT_ELEMENT, #v1, properties->v1, properties->v1, sizeof(properties->v1));
#define GET_STR_VALUE_2(v1,v2)      iniFileGetString(ROOT_ELEMENT, #v1 "." #v2, properties->v1.v2, properties->v1.v2, sizeof(properties->v1.v2));
#define GET_STR_VALUE_3(v1,v2,v3)   iniFileGetString(ROOT_ELEMENT, #v1 "." #v2 "." #v3, properties->v1.v2.v3, properties->v1.v2.v3, sizeof(properties->v1.v2.v3));
#define GET_STR_VALUE_2s1(v1,v2,v3,v4) iniFileGetString(ROOT_ELEMENT, #v1 "." #v2 "." #v3 "." #v4, properties->v1.v2[v3].v4, properties->v1.v2[v3].v4, sizeof(properties->v1.v2[v3].v4));
#define GET_STR_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); iniFileGetString(ROOT_ELEMENT, s, properties->v1.v2[i], properties->v1.v2[i], sizeof(properties->v1.v2[i])); }
#define GET_STR_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); iniFileGetString(ROOT_ELEMENT, s, properties->v1.v2[i].a1, properties->v1.v2[i].a1, sizeof(properties->v1.v2[i].a1)); }

#define SET_INT_VALUE_1(v1)         { char v[64]; sprintf(v, "%d", properties->v1); iniFileWriteString(ROOT_ELEMENT, #v1, v); }
#define SET_INT_VALUE_2(v1,v2)      { char v[64]; sprintf(v, "%d", properties->v1.v2); iniFileWriteString(ROOT_ELEMENT, #v1 "." #v2, v); }
#define SET_INT_VALUE_3(v1,v2,v3)   { char v[64]; sprintf(v, "%d", properties->v1.v2.v3); iniFileWriteString(ROOT_ELEMENT, #v1 "." #v2 "." #v3, v); }
#define SET_INT_VALUE_2s1(v1,v2,v3,v4) { char v[64]; sprintf(v, "%d", properties->v1.v2[v3].v4); iniFileWriteString(ROOT_ELEMENT, #v1 "." #v2 "." #v3 "." #v4, v); }
#define SET_INT_VALUE_2i(v1, v2, i)      { char s[64], v[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); sprintf(v, "%d", properties->v1.v2[i]); iniFileWriteString(ROOT_ELEMENT, s, v); }
#define SET_INT_VALUE_2i1(v1, v2, i, a1) { char s[64], v[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); sprintf(v, "%d", properties->v1.v2[i].a1); iniFileWriteString(ROOT_ELEMENT, s, v); }

#define SET_STR_VALUE_1(v1)         iniFileWriteString(ROOT_ELEMENT, #v1, properties->v1);
#define SET_STR_VALUE_2(v1,v2)      iniFileWriteString(ROOT_ELEMENT, #v1 "." #v2, properties->v1.v2);
#define SET_STR_VALUE_3(v1,v2,v3)   iniFileWriteString(ROOT_ELEMENT, #v1 "." #v2 "." #v3, properties->v1.v2.v3);
#define SET_STR_VALUE_2s1(v1,v2,v3,v4) iniFileWriteString(ROOT_ELEMENT, #v1 "." #v2 "." #v3 "." #v4, properties->v1.v2[v3].v4);
#define SET_STR_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); iniFileWriteString(ROOT_ELEMENT, s, properties->v1.v2[i]); }
#define SET_STR_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); iniFileWriteString(ROOT_ELEMENT, s, properties->v1.v2[i].a1); }

#else

#define GET_INT_VALUE_1(v1)         getIntValue(properties->filename, ROOT_ELEMENT, #v1, &properties->v1)
#define GET_INT_VALUE_2(v1,v2)      getIntValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2, &properties->v1.v2)
#define GET_INT_VALUE_3(v1,v2,v3)   getIntValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #v3, &properties->v1.v2.v3)
#define GET_INT_VALUE_2s1(v1,v2,v3,v4) getIntValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #v3 "." #v4, &properties->v1.v2[v3].v4)
#define GET_INT_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); getIntValue(properties->filename, ROOT_ELEMENT, s, &properties->v1.v2[i]); }
#define GET_INT_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); getIntValue(properties->filename, ROOT_ELEMENT, s, &properties->v1.v2[i].a1); }

#define GET_STR_VALUE_1(v1)           getStrValue(properties->filename, ROOT_ELEMENT, v1, (char*)properties->v1)
#define GET_STR_VALUE_2(v1,v2)        getStrValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2, (char*)properties->v1.v2)
#define GET_STR_VALUE_3(v1,v2,v3)     getStrValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #v3, (char*)properties->v1.v2.v3)
#define GET_STR_VALUE_2s1(v1,v2,s,v3) getStrValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #s "." #v3, (char*)properties->v1.v2[s].v3)
#define GET_STR_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); getStrValue(properties->filename, ROOT_ELEMENT, s, (char*)properties->v1.v2[i]); }
#define GET_STR_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); getStrValue(properties->filename, ROOT_ELEMENT, s, (char*)properties->v1.v2[i].a1); }

#define SET_INT_VALUE_1(v1)         setIntValue(properties->filename, ROOT_ELEMENT, #v1, properties->v1)
#define SET_INT_VALUE_2(v1,v2)      setIntValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2, properties->v1.v2)
#define SET_INT_VALUE_3(v1,v2,v3)   setIntValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #v3, properties->v1.v2.v3)
#define SET_INT_VALUE_2s1(v1,v2,v3,v4) setIntValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #v3 "." #v4, properties->v1.v2[v3].v4)
#define SET_INT_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); setIntValue(properties->filename, ROOT_ELEMENT, s, properties->v1.v2[i]); }
#define SET_INT_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); setIntValue(properties->filename, ROOT_ELEMENT, s, properties->v1.v2[i].a1); }

#define SET_STR_VALUE_1(v1)           setStrValue(properties->filename, ROOT_ELEMENT, v1, (char*)properties->v1)
#define SET_STR_VALUE_2(v1,v2)        setStrValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2, (char*)properties->v1.v2)
#define SET_STR_VALUE_3(v1,v2,v3)     setStrValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #v3, (char*)properties->v1.v2.v3)
#define SET_STR_VALUE_2s1(v1,v2,s,v3) setStrValue(properties->filename, ROOT_ELEMENT, #v1 "." #v2 "." #s "." #v3, (char*)properties->v1.v2[s].v3)
#define SET_STR_VALUE_2i(v1, v2, i)      { char s[64]; sprintf(s, "%s.%s.i%d",#v1,#v2,i); setStrValue(properties->filename, ROOT_ELEMENT, s, (char*)properties->v1.v2[i]); }
#define SET_STR_VALUE_2i1(v1, v2, i, a1) { char s[64]; sprintf(s, "%s.%s.i%d.%s",#v1,#v2,i,#a1); setStrValue(properties->filename, ROOT_ELEMENT, s, (char*)properties->v1.v2[i].a1); }

#endif

#endif

static void propLoad(Properties* properties) 
{
    int i;
    
#ifdef USE_XMLFORMAT
    VtXpath* xpath = vtXpathOpenForRead(properties->filename);
#else
#ifndef USE_NATIVEINI
    iniFileOpen(properties->filename);
#endif
#endif

    GET_INT_VALUE_1(language);
    
    GET_INT_VALUE_2(settings, disableScreensaver);    
    GET_INT_VALUE_2(settings, showStatePreview);
    GET_STR_VALUE_2(settings, themeName);

    GET_INT_VALUE_2(emulation, registerFileTypes);
    GET_INT_VALUE_2(emulation, disableWinKeys);
    GET_STR_VALUE_2(emulation, statsDefDir);
    GET_STR_VALUE_2(emulation, machineName);
    GET_STR_VALUE_2(emulation, shortcutProfile);
    GET_INT_VALUE_2(emulation, speed);
    GET_INT_VALUE_2(emulation, syncMethod);
    GET_INT_VALUE_2(emulation, vdpSyncMode);
    GET_INT_VALUE_2(emulation, enableFdcTiming);
    GET_INT_VALUE_2(emulation, frontSwitch);
    GET_INT_VALUE_2(emulation, pauseSwitch);
    GET_INT_VALUE_2(emulation, audioSwitch);
    GET_INT_VALUE_2(emulation, priorityBoost);
    
    GET_INT_VALUE_2(video, monType);
    GET_INT_VALUE_2(video, palEmu);
    GET_INT_VALUE_2(video, size);
    GET_INT_VALUE_2(video, driver);
    GET_INT_VALUE_2(video, frameSkip);
    GET_INT_VALUE_3(video, fullscreen, width);
    GET_INT_VALUE_3(video, fullscreen, height);
    GET_INT_VALUE_3(video, fullscreen, bitDepth);
    GET_INT_VALUE_2(video, deInterlace);
    GET_INT_VALUE_2(video, horizontalStretch);
    GET_INT_VALUE_2(video, verticalStretch);
    GET_INT_VALUE_2(video, contrast);
    GET_INT_VALUE_2(video, brightness);
    GET_INT_VALUE_2(video, saturation);
    GET_INT_VALUE_2(video, gamma);
    GET_INT_VALUE_2(video, scanlinesEnable);
    GET_INT_VALUE_2(video, scanlinesPct);
    GET_INT_VALUE_2(video, colorSaturationEnable);
    GET_INT_VALUE_2(video, colorSaturationWidth);
    GET_INT_VALUE_2(video, chipAutodetect);

    GET_INT_VALUE_2(sound, driver);
    GET_INT_VALUE_2(sound, frequency);
    GET_INT_VALUE_2(sound, bufSize);
    GET_INT_VALUE_2(sound, syncMethod);
    GET_INT_VALUE_2(sound, stereo);
    GET_INT_VALUE_2(sound, masterVolume);
    GET_INT_VALUE_2(sound, masterEnable);
    
    GET_INT_VALUE_3(sound, chip, enableYM2413);
    GET_INT_VALUE_3(sound, chip, enableY8950);
    GET_INT_VALUE_3(sound, chip, enableMoonsound);
    GET_INT_VALUE_3(sound, chip, moonsoundSRAMSize);
    GET_INT_VALUE_3(sound, chip, ym2413Oversampling);
    GET_INT_VALUE_3(sound, chip, y8950Oversampling);
    GET_INT_VALUE_3(sound, chip, moonsoundOversampling);
    GET_INT_VALUE_3(sound, MidiIn, type);
    GET_STR_VALUE_3(sound, MidiIn, name);
    GET_STR_VALUE_3(sound, MidiIn, fileName);
    GET_STR_VALUE_3(sound, MidiIn, desc);
    GET_INT_VALUE_3(sound, MidiOut, type);
    GET_STR_VALUE_3(sound, MidiOut, name);
    GET_STR_VALUE_3(sound, MidiOut, fileName);
    GET_STR_VALUE_3(sound, MidiOut, desc);
    GET_INT_VALUE_3(sound, MidiOut, mt32ToGm);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PSG, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PSG, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PSG, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_SCC, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_SCC, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_SCC, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXMUSIC, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXMUSIC, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXMUSIC, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXAUDIO, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXAUDIO, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXAUDIO, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_KEYBOARD, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_KEYBOARD, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_KEYBOARD, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MOONSOUND, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MOONSOUND, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MOONSOUND, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PCM, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PCM, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PCM, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_IO, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_IO, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_IO, volume);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MIDI, enable);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MIDI, pan);
    GET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MIDI, volume);
    
    
    GET_INT_VALUE_2(joy1, type);
    GET_INT_VALUE_2(joy1, autofire);
    GET_INT_VALUE_2(joy1, keyUp);
    GET_INT_VALUE_2(joy1, keyDown);
    GET_INT_VALUE_2(joy1, keyLeft);
    GET_INT_VALUE_2(joy1, keyRight);
    GET_INT_VALUE_2(joy1, button1);
    GET_INT_VALUE_2(joy1, button2);
    GET_INT_VALUE_2(joy1, hwType);
    GET_STR_VALUE_2(joy1, hwName);
    GET_INT_VALUE_2(joy1, hwIndex);
    GET_INT_VALUE_2(joy1, hwButtonA);
    GET_INT_VALUE_2(joy1, hwButtonB);
    
    GET_INT_VALUE_2(joy2, type);
    GET_INT_VALUE_2(joy2, autofire);
    GET_INT_VALUE_2(joy2, keyUp);
    GET_INT_VALUE_2(joy2, keyDown);
    GET_INT_VALUE_2(joy2, keyLeft);
    GET_INT_VALUE_2(joy2, keyRight);
    GET_INT_VALUE_2(joy2, button1);
    GET_INT_VALUE_2(joy2, button2);
    GET_INT_VALUE_2(joy2, hwType);
    GET_STR_VALUE_2(joy2, hwName);
    GET_INT_VALUE_2(joy2, hwIndex);
    GET_INT_VALUE_2(joy2, hwButtonA);
    GET_INT_VALUE_2(joy2, hwButtonB);
    
    GET_STR_VALUE_2(keyboard, configFile);
    
    GET_STR_VALUE_2(cartridge, defDir);
    GET_INT_VALUE_2(cartridge, autoReset);
    GET_INT_VALUE_2(cartridge, quickStartDrive);
    GET_STR_VALUE_2(cartridge, slotA);
    GET_INT_VALUE_2(cartridge, slotAType);
    GET_STR_VALUE_2(cartridge, slotAZip);
    GET_INT_VALUE_2(cartridge, slotAFilter);
    GET_STR_VALUE_2(cartridge, slotB);
    GET_INT_VALUE_2(cartridge, slotBType);
    GET_STR_VALUE_2(cartridge, slotBZip);
    GET_INT_VALUE_2(cartridge, slotBFilter);

    GET_STR_VALUE_2(diskdrive, defDir);
    GET_INT_VALUE_2(diskdrive, autostartA);
    GET_INT_VALUE_2(diskdrive, quickStartDrive);
    GET_STR_VALUE_2(diskdrive, slotA);
    GET_STR_VALUE_2(diskdrive, slotAZip);
    GET_STR_VALUE_2(diskdrive, slotADir);
    GET_INT_VALUE_2(diskdrive, slotAFilter);
    GET_STR_VALUE_2(diskdrive, slotB);
    GET_STR_VALUE_2(diskdrive, slotBZip);
    GET_STR_VALUE_2(diskdrive, slotBDir);
    GET_INT_VALUE_2(diskdrive, slotBFilter);
    
    GET_STR_VALUE_2(cassette, defDir);
    GET_STR_VALUE_2(cassette, tape);
    GET_STR_VALUE_2(cassette, tapeZip);
    GET_INT_VALUE_2(cassette, filter);
    GET_INT_VALUE_2(cassette, showCustomFiles);
    GET_INT_VALUE_2(cassette, readOnly);
    GET_INT_VALUE_2(cassette, autoRewind);

    GET_INT_VALUE_3(ports, Lpt, type);
    GET_INT_VALUE_3(ports, Lpt, emulation);
    GET_STR_VALUE_3(ports, Lpt, name);
    GET_STR_VALUE_3(ports, Lpt, fileName);
    GET_STR_VALUE_3(ports, Lpt, portName);
    GET_INT_VALUE_3(ports, Com, type);
    GET_STR_VALUE_3(ports, Com, name);
    GET_STR_VALUE_3(ports, Com, fileName);
    GET_STR_VALUE_3(ports, Com, portName);
    
    for (i = 0; i < MAX_HISTORY; i++) {
        GET_STR_VALUE_2i(filehistory, cartridgeA, i);
        GET_INT_VALUE_2i(filehistory, cartridgeTypeA, i);
        GET_STR_VALUE_2i(filehistory, cartridgeB, i);
        GET_INT_VALUE_2i(filehistory, cartridgeTypeB, i);
        GET_STR_VALUE_2i(filehistory, diskdriveA, i);
        GET_STR_VALUE_2i(filehistory, diskdriveB, i);
        GET_STR_VALUE_2i(filehistory, cassette, i);
    }

    GET_STR_VALUE_2(filehistory, quicksave);
    GET_INT_VALUE_2(filehistory, count);

    for (i = 0; i < DLG_MAX_ID; i++) {
        GET_INT_VALUE_2i1(settings, windowPos, i, left);
        GET_INT_VALUE_2i1(settings, windowPos, i, top);
        GET_INT_VALUE_2i1(settings, windowPos, i, width);
        GET_INT_VALUE_2i1(settings, windowPos, i, height);
    }
    
#ifdef USE_XMLFORMAT
    vtXpathClose(xpath);
#else
#ifndef USE_NATIVEINI
    iniFileClose();
#endif
#endif
}

void propSave(Properties* properties) 
{
    int i;
    
#ifdef USE_XMLFORMAT
    VtXpath* xpath = vtXpathOpenForWrite(properties->filename);
#else
#ifndef USE_NATIVEINI
    iniFileOpen(properties->filename);
#endif
#endif

    SET_INT_VALUE_1(language);
    
    SET_INT_VALUE_2(settings, disableScreensaver);    
    SET_INT_VALUE_2(settings, showStatePreview);
    SET_STR_VALUE_2(settings, themeName);

    SET_INT_VALUE_2(emulation, registerFileTypes);
    SET_INT_VALUE_2(emulation, disableWinKeys);
    SET_STR_VALUE_2(emulation, statsDefDir);
    SET_STR_VALUE_2(emulation, machineName);
    SET_STR_VALUE_2(emulation, shortcutProfile);
    SET_INT_VALUE_2(emulation, speed);
    SET_INT_VALUE_2(emulation, syncMethod);
    SET_INT_VALUE_2(emulation, vdpSyncMode);
    SET_INT_VALUE_2(emulation, enableFdcTiming);
    SET_INT_VALUE_2(emulation, frontSwitch);
    SET_INT_VALUE_2(emulation, pauseSwitch);
    SET_INT_VALUE_2(emulation, audioSwitch);
    SET_INT_VALUE_2(emulation, priorityBoost);
    
    SET_INT_VALUE_2(video, monType);
    SET_INT_VALUE_2(video, palEmu);
    SET_INT_VALUE_2(video, size);
    SET_INT_VALUE_2(video, driver);
    SET_INT_VALUE_2(video, frameSkip);
    SET_INT_VALUE_3(video, fullscreen, width);
    SET_INT_VALUE_3(video, fullscreen, height);
    SET_INT_VALUE_3(video, fullscreen, bitDepth);
    SET_INT_VALUE_2(video, deInterlace);
    SET_INT_VALUE_2(video, horizontalStretch);
    SET_INT_VALUE_2(video, verticalStretch);
    SET_INT_VALUE_2(video, contrast);
    SET_INT_VALUE_2(video, brightness);
    SET_INT_VALUE_2(video, saturation);
    SET_INT_VALUE_2(video, gamma);
    SET_INT_VALUE_2(video, scanlinesEnable);
    SET_INT_VALUE_2(video, scanlinesPct);
    SET_INT_VALUE_2(video, colorSaturationEnable);
    SET_INT_VALUE_2(video, colorSaturationWidth);
    SET_INT_VALUE_2(video, chipAutodetect);

    SET_INT_VALUE_2(sound, driver);
    SET_INT_VALUE_2(sound, frequency);
    SET_INT_VALUE_2(sound, bufSize);
    SET_INT_VALUE_2(sound, syncMethod);
    SET_INT_VALUE_2(sound, stereo);
    SET_INT_VALUE_2(sound, masterVolume);
    SET_INT_VALUE_2(sound, masterEnable);
    
    SET_INT_VALUE_3(sound, chip, enableYM2413);
    SET_INT_VALUE_3(sound, chip, enableY8950);
    SET_INT_VALUE_3(sound, chip, enableMoonsound);
    SET_INT_VALUE_3(sound, chip, moonsoundSRAMSize);
    SET_INT_VALUE_3(sound, chip, ym2413Oversampling);
    SET_INT_VALUE_3(sound, chip, y8950Oversampling);
    SET_INT_VALUE_3(sound, chip, moonsoundOversampling);
    SET_INT_VALUE_3(sound, MidiIn, type);
    SET_STR_VALUE_3(sound, MidiIn, name);
    SET_STR_VALUE_3(sound, MidiIn, fileName);
    SET_STR_VALUE_3(sound, MidiIn, desc);
    SET_INT_VALUE_3(sound, MidiOut, type);
    SET_STR_VALUE_3(sound, MidiOut, name);
    SET_STR_VALUE_3(sound, MidiOut, fileName);
    SET_STR_VALUE_3(sound, MidiOut, desc);
    SET_INT_VALUE_3(sound, MidiOut, mt32ToGm);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PSG, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PSG, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PSG, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_SCC, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_SCC, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_SCC, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXMUSIC, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXMUSIC, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXMUSIC, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXAUDIO, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXAUDIO, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MSXAUDIO, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_KEYBOARD, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_KEYBOARD, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_KEYBOARD, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MOONSOUND, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MOONSOUND, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MOONSOUND, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PCM, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PCM, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_PCM, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_IO, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_IO, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_IO, volume);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MIDI, enable);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MIDI, pan);
    SET_INT_VALUE_2s1(sound, mixerChannel, MIXER_CHANNEL_MIDI, volume);
    
    
    SET_INT_VALUE_2(joy1, type);
    SET_INT_VALUE_2(joy1, autofire);
    SET_INT_VALUE_2(joy1, keyUp);
    SET_INT_VALUE_2(joy1, keyDown);
    SET_INT_VALUE_2(joy1, keyLeft);
    SET_INT_VALUE_2(joy1, keyRight);
    SET_INT_VALUE_2(joy1, button1);
    SET_INT_VALUE_2(joy1, button2);
    SET_INT_VALUE_2(joy1, hwType);
    SET_STR_VALUE_2(joy1, hwName);
    SET_INT_VALUE_2(joy1, hwIndex);
    SET_INT_VALUE_2(joy1, hwButtonA);
    SET_INT_VALUE_2(joy1, hwButtonB);
    
    SET_INT_VALUE_2(joy2, type);
    SET_INT_VALUE_2(joy2, autofire);
    SET_INT_VALUE_2(joy2, keyUp);
    SET_INT_VALUE_2(joy2, keyDown);
    SET_INT_VALUE_2(joy2, keyLeft);
    SET_INT_VALUE_2(joy2, keyRight);
    SET_INT_VALUE_2(joy2, button1);
    SET_INT_VALUE_2(joy2, button2);
    SET_INT_VALUE_2(joy2, hwType);
    SET_STR_VALUE_2(joy2, hwName);
    SET_INT_VALUE_2(joy2, hwIndex);
    SET_INT_VALUE_2(joy2, hwButtonA);
    SET_INT_VALUE_2(joy2, hwButtonB);
    
    SET_STR_VALUE_2(keyboard, configFile);
    
    SET_STR_VALUE_2(cartridge, defDir);
    SET_INT_VALUE_2(cartridge, autoReset);
    SET_INT_VALUE_2(cartridge, quickStartDrive);
    SET_STR_VALUE_2(cartridge, slotA);
    SET_INT_VALUE_2(cartridge, slotAType);
    SET_STR_VALUE_2(cartridge, slotAZip);
    SET_INT_VALUE_2(cartridge, slotAFilter);
    SET_STR_VALUE_2(cartridge, slotB);
    SET_INT_VALUE_2(cartridge, slotBType);
    SET_STR_VALUE_2(cartridge, slotBZip);
    SET_INT_VALUE_2(cartridge, slotBFilter);

    SET_STR_VALUE_2(diskdrive, defDir);
    SET_INT_VALUE_2(diskdrive, autostartA);
    SET_INT_VALUE_2(diskdrive, quickStartDrive);
    SET_STR_VALUE_2(diskdrive, slotA);
    SET_STR_VALUE_2(diskdrive, slotAZip);
    SET_STR_VALUE_2(diskdrive, slotADir);
    SET_INT_VALUE_2(diskdrive, slotAFilter);
    SET_STR_VALUE_2(diskdrive, slotB);
    SET_STR_VALUE_2(diskdrive, slotBZip);
    SET_STR_VALUE_2(diskdrive, slotBDir);
    SET_INT_VALUE_2(diskdrive, slotBFilter);
    
    SET_STR_VALUE_2(cassette, defDir);
    SET_STR_VALUE_2(cassette, tape);
    SET_STR_VALUE_2(cassette, tapeZip);
    SET_INT_VALUE_2(cassette, filter);
    SET_INT_VALUE_2(cassette, showCustomFiles);
    SET_INT_VALUE_2(cassette, readOnly);
    SET_INT_VALUE_2(cassette, autoRewind);

    SET_INT_VALUE_3(ports, Lpt, type);
    SET_INT_VALUE_3(ports, Lpt, emulation);
    SET_STR_VALUE_3(ports, Lpt, name);
    SET_STR_VALUE_3(ports, Lpt, fileName);
    SET_STR_VALUE_3(ports, Lpt, portName);
    SET_INT_VALUE_3(ports, Com, type);
    SET_STR_VALUE_3(ports, Com, name);
    SET_STR_VALUE_3(ports, Com, fileName);
    SET_STR_VALUE_3(ports, Com, portName);
    
    for (i = 0; i < MAX_HISTORY; i++) {
        SET_STR_VALUE_2i(filehistory, cartridgeA, i);
        SET_INT_VALUE_2i(filehistory, cartridgeTypeA, i);
        SET_STR_VALUE_2i(filehistory, cartridgeB, i);
        SET_INT_VALUE_2i(filehistory, cartridgeTypeB, i);
        SET_STR_VALUE_2i(filehistory, diskdriveA, i);
        SET_STR_VALUE_2i(filehistory, diskdriveB, i);
        SET_STR_VALUE_2i(filehistory, cassette, i);
    }

    SET_STR_VALUE_2(filehistory, quicksave);
    SET_INT_VALUE_2(filehistory, count);

    for (i = 0; i < DLG_MAX_ID; i++) {
        SET_INT_VALUE_2i1(settings, windowPos, i, left);
        SET_INT_VALUE_2i1(settings, windowPos, i, top);
        SET_INT_VALUE_2i1(settings, windowPos, i, width);
        SET_INT_VALUE_2i1(settings, windowPos, i, height);
    }
    
#ifdef USE_XMLFORMAT
    vtXpathClose(xpath);
#else
#ifndef USE_NATIVEINI
    iniFileClose();
#endif
#endif
}

static Properties* globalProperties = NULL;

Properties* propGetGlobalProperties()
{
    return globalProperties;
}

Properties* propCreate(const char* filename, int useDefault, int langType, PropKeyboardLanguage kbdLang, int syncMode, const char* themeName) 
{
    Properties* properties;

    properties = malloc(sizeof(Properties));

    if (globalProperties == NULL) {
        globalProperties = properties;
    }

    properties->joy1.id = 1;
    properties->joy2.id = 2;
    propInitDefaults(properties, langType, kbdLang, syncMode, themeName);

    strcpy(properties->filename, filename);
    if (!useDefault) {
        propLoad(properties);
    }

    // Verify machine name
    {
        char** machineNames = machineGetAvailable(1);
        
        while (*machineNames != NULL) {
            if (0 == strcmp(*machineNames, properties->emulation.machineName)) {
                break;
            }
            machineNames++;
        }

        if (*machineNames == NULL) {
            char** machineNames = machineGetAvailable(1);
            int foundMSX2 = 0;

            if (*machineNames != NULL) {
                strcpy(properties->emulation.machineName, *machineNames);
            }

            while (*machineNames != NULL) {
                if (0 == strcmp(*machineNames, "MSX2")) {
                    strcpy(properties->emulation.machineName, *machineNames);
                    foundMSX2 = 1;
                }
                if (!foundMSX2 && 0 == strncmp(*machineNames, "MSX2", 4)) {
                    strcpy(properties->emulation.machineName, *machineNames);
                    foundMSX2 = 1;
                }
                machineNames++;
            }
        }
    }

    return properties;
}


void propDestroy(Properties* properties) {
    propSave(properties);

    free(properties);
}

 
