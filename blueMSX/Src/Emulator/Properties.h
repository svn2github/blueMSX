/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Properties.h,v $
**
** $Revision: 1.14 $
**
** $Date: 2005-01-29 00:28:49 $
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
#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "AudioMixer.h"
#include "VideoRender.h"
#include "Language.h"
#include "RomMapper.h"

#define CARTNAME_SNATCHER    "The Snatcher Cartridge"
#define CARTNAME_SDSNATCHER  "SD-Snatcher Cartridge"
#define CARTNAME_SCCMIRRORED "SCC Mirrored Cartridge"
#define CARTNAME_SCCEXPANDED "SCC Expanded Cartridge"
#define CARTNAME_SCC         "SCC Cartridge"
#define CARTNAME_SCCPLUS     "SCC+ Cartridge"
#define CARTNAME_FMPAC       "FM-PAC Cartridge"
#define CARTNAME_PAC         "PAC Cartridge"
#define CARTNAME_SONYHBI55   "Sony HBI-55"
#define CARTNAME_EXTRAM512KB "512kB External RAM"
#define CARTNAME_EXTRAM1MB   "1MB External RAM"
#define CARTNAME_EXTRAM2MB   "2MB External RAM"
#define CARTNAME_EXTRAM4MB   "4MB External RAM"
#define CARTNAME_MEGARAM128  "128kB MegaRAM"
#define CARTNAME_MEGARAM256  "256kB MegaRAM"
#define CARTNAME_MEGARAM512  "512kB MegaRAM"
#define CARTNAME_MEGARAM768  "768kB MegaRAM"
#define CARTNAME_MEGARAM2M   "2MB MegaRAM"

typedef enum { PROP_EMULATION = 0, PROP_VIDEO, PROP_SOUND, PROP_CONTROLS, PROP_PERFORMANCE, PROP_SETTINGS, PROP_APEARANCE, PROP_PORTS } PropPage;

typedef enum { P_EMU_SYNC1MS = 0, P_EMU_SYNCAUTO, P_EMU_SYNCNONE } PropEmuSync;
typedef enum { P_VDP_SYNCAUTO = 0, P_VDP_SYNC50HZ, P_VDP_SYNC60HZ } PropVdpSync; 
typedef enum { P_VIDEO_COLOR = 0, P_VIDEO_BW, P_VIDEO_GREEN, P_VIDEO_AMBER, P_VIDEO_MONCOUNT } PropVideoMon;
typedef enum { P_VIDEO_PALNONE = 0, P_VIDEO_PALMON, P_VIDEO_PALYC, P_VIDEO_PALNYC, P_VIDEO_PALCOMP, P_VIDEO_PALNCOMP, P_VIDEO_PALSCALE2X, P_VIDEO_PALHQ2X, P_VIDEO_PALCOUNT } PropVideoPalEmu;
typedef enum { P_VIDEO_SIZEX1 = 0, P_VIDEO_SIZEX2, P_VIDEO_SIZEFULLSCREEN } PropVideoSize;
typedef enum { P_VIDEO_DRVDIRECTX_VIDEO = 0, P_VIDEO_DRVDIRECTX, P_VIDEO_DRVGDI } PropVideoDriver;
typedef enum { P_VIDEO_FSKIP0 = 0, P_VIDEO_FSKIP1, P_VIDEO_FSKIP2, P_VIDEO_FSKIP3, P_VIDEO_FSKIP4, P_VIDEO_FSKIP5 } PropVideoFrameSkip;
typedef enum { P_VIDEO_FREQ_AUTO, P_VIDEO_FREQ_50HZ, P_VIDEO_FREQ_60HZ } PropVideoFrequency;
typedef enum { P_SOUND_DRVNONE = 0, P_SOUND_DRVWMM, P_SOUND_DRVDIRECTX } PropSoundDriver;
typedef enum { P_SOUND_FREQ11 = 0, P_SOUND_FREQ22, P_SOUND_FREQ44 } PropSoundFrequency;
typedef enum { P_SOUND_SYNCFAST = 0, P_SOUND_SYNCQADJUST, P_SOUND_SYNCEADJUST } PropSoundSync;
typedef enum { P_JOY_NONE = 0, P_JOY_MOUSE, P_JOY_NUMPAD, P_JOY_KEYSET, P_JOY_HW } PropControlsJoy;
typedef enum { P_JOY_AFOFF = 0, P_JOY_AFSLOW, P_JOY_AFMEDIUM, P_JOY_AFFAST } PropControlsAutofire;
typedef enum { P_CHAR_EUROPEAN = 0, P_CHAR_RUSSIAN, P_CHAR_JAPANESE, P_CHAR_KOREAN } PropControlsLanguage;


#define MAX_HISTORY 30

typedef struct {
    char          statsDefDir[MAX_PATH];
    char          machineName[MAX_PATH];
    char          shortcutProfile[MAX_PATH];
    int           enableFdcTiming;
    int           frontSwitch;
    int           audioSwitch;
    int           pauseSwitch;
    int           speed;
    int           registerFileTypes;
    int           disableWinKeys;
    int           priorityBoost;
    PropEmuSync   syncMethod;
    PropVdpSync   vdpSyncMode;
} EmulationProperties;

typedef struct {
    PropVideoMon        monType;
    PropVideoPalEmu     palEmu;
    PropVideoSize       size;
    PropVideoDriver     driver;
    PropVideoFrameSkip  frameSkip;
    struct {
        int width;
        int height;
        int bitDepth;
    } fullscreen;
    PropVideoFrequency  frequency;
    int                 deInterlace;
    int                 horizontalStretch;
    int                 verticalStretch;
    int                 contrast;
    int                 brightness;
    int                 saturation;
    int                 scanlinesEnable;
    int                 scanlinesPct;
    int                 colorSaturationEnable;
    int                 colorSaturationWidth;
    int                 gamma;
} VideoProperties;

typedef struct {
    int enable;
    int volume;
    int pan;
} MixerChannel;

typedef struct {
    int enableY8950;
    int enableYM2413;
    int enableMoonsound;
    int moonsoundSRAM;
    int ym2413Oversampling;
    int y8950Oversampling;
    int moonsoundOversampling;
} SoundChip;

typedef struct {
    PropSoundDriver     driver;
    PropSoundFrequency  frequency;
    int                 bufSize;
    PropSoundSync       syncMethod;
    SoundChip           chip;
    int                 stereo;
    int                 masterVolume;
    int                 masterEnable;
    MixerChannel        mixerChannel[MIXER_CHANNEL_TYPE_COUNT];
    char                log[MAX_PATH];
} SoundProperties;

typedef struct {
    int id;
    PropControlsJoy      type;
    PropControlsAutofire autofire;
    int  hwType;
    int  hwButtonA;
    int  hwButtonB;
    char hwName[128];
    int  hwIndex;
    int  keyUp;
    int  keyDown;
    int  keyLeft;
    int  keyRight;
    int  button1;
    int  button2;
}  JoystickProperties;

typedef struct {
    char    configFile[MAX_PATH];
    PropControlsLanguage keySet;
} KeyboardProperties;

typedef struct {
    RomType defaultType;
    char    defDir[MAX_PATH];
    char    slotA[MAX_PATH];
    char    slotB[MAX_PATH];
    char    slotAZip[MAX_PATH];
    char    slotBZip[MAX_PATH];
    int     slotAFilter;
    int     slotBFilter;
    RomType slotAType;
    RomType slotBType;
    int     autoReset;
    int     quickStartDrive;
} CartridgeProperties;

typedef struct {
    char defDir[MAX_PATH];
    char slotA[MAX_PATH];
    char slotB[MAX_PATH];
    char slotAZip[MAX_PATH];
    char slotBZip[MAX_PATH];
    char slotADir[MAX_PATH];
    char slotBDir[MAX_PATH];
    int  slotAFilter;
    int  slotBFilter;
    int  autostartA;
    int  quickStartDrive;
} DiskdriveProperties;

typedef struct {
    char defDir[MAX_PATH];
    char tape[MAX_PATH];
    char tapeZip[MAX_PATH];
    int  filter;
    int showCustomFiles;
    int readOnly;
    int autoRewind;
} CassetteProperties;

typedef struct {
    int     count;
    char    cartridgeA[MAX_HISTORY][MAX_PATH];
    RomType cartridgeTypeA[MAX_HISTORY];
    char    cartridgeB[MAX_HISTORY][MAX_PATH];
    RomType cartridgeTypeB[MAX_HISTORY];
    char    diskdriveA[MAX_HISTORY][MAX_PATH];
    char    diskdriveB[MAX_HISTORY][MAX_PATH];
    char    cassette[MAX_HISTORY][MAX_PATH];
    char    quicksave[MAX_PATH];
} FileHistory;

#define DLG_MAX_ID 32

typedef struct {
    int disableScreensaver;
    char themeName[128];
    struct {  
        long left; 
        long top; 
        long right; 
        long bottom; 
    } windowPos[DLG_MAX_ID];
} Settings;

typedef struct {
    EmulationProperties emulation;
    VideoProperties     video;
    SoundProperties     sound;
    JoystickProperties  joy1;
    JoystickProperties  joy2;
    KeyboardProperties  keyboard;
    CartridgeProperties cartridge;
    DiskdriveProperties diskdrive;
    CassetteProperties  cassette;
    FileHistory         filehistory;
    EmuLanguageType     language;
    Settings            settings;
} Properties;

Properties* propCreate(int useDefault);
void propSave(Properties* pProperties);
void propDestroy(Properties* pProperties);

Properties* propGetGlobalProperties();

#endif
