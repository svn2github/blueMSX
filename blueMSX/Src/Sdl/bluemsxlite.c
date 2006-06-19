#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"

#include "CommandLine.h"
#include "Properties.h"
#include "ArchFile.h"
#include "VideoRender.h"
#include "AudioMixer.h"
#include "Casette.h"
#include "PrinterIO.h"
#include "UartIO.h"
#include "MidiIO.h"
#include "Machine.h"
#include "Board.h"
#include "Emulator.h"
#include "FileHistory.h"
#include "Actions.h"
#include "Language.h"
#include "LaunchFile.h"
#include "ArchEvent.h"
#include "ArchSound.h"
#include "JoystickPort.h"

static Properties* properties;
static Video* video;
static Mixer* mixer;

static Properties* properties;
static Video* video;
static Mixer* mixer;

static int dpyUpdateEvent = 0;
static void* dpyUpdateAckEvent = NULL;

static SDL_Surface *surface;
static int bitDepth;

#define WIDTH  640
#define HEIGHT 480

#define EVENT_UPDATE_DISPLAY 2

int createSdlWindow(const char *title, int width, int height, int bitDepth)
{
    int fullscreen = 0;
    int flags = SDL_SWSURFACE | (fullscreen ? SDL_FULLSCREEN : 0);
    int bytepp;

	// try default bpp
	surface = SDL_SetVideoMode(width, height, 0, flags);
	bytepp = (surface ? surface->format->BytesPerPixel : 0);
	if (bytepp != 2 && bytepp != 4) {
		surface = NULL;
	}

    if (!surface) { bitDepth = 32; surface = SDL_SetVideoMode(width, height, bitDepth, flags); }
    if (!surface) { bitDepth = 16; surface = SDL_SetVideoMode(width, height, bitDepth, flags); }

	if (!surface) {
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}

    //Set the window caption
    SDL_WM_SetCaption( title, NULL );

    return 1;
}

static void updateVideoRender(Video* video, Properties* properties) {
    videoSetDeInterlace(video, properties->video.deInterlace);

    switch (properties->video.monType) {
    case P_VIDEO_COLOR:
        videoSetColorMode(video, VIDEO_COLOR);
        break;
    case P_VIDEO_BW:
        videoSetColorMode(video, VIDEO_BLACKWHITE);
        break;
    case P_VIDEO_GREEN:
        videoSetColorMode(video, VIDEO_GREEN);
        break;
    case P_VIDEO_AMBER:
        videoSetColorMode(video, VIDEO_AMBER);
        break;
    }

    switch (properties->video.palEmu) {
    case P_VIDEO_PALNONE:
        videoSetPalMode(video, VIDEO_PAL_FAST);
        break;
    case P_VIDEO_PALMON:
        videoSetPalMode(video, VIDEO_PAL_MONITOR);
        break;
    case P_VIDEO_PALYC:
        videoSetPalMode(video, VIDEO_PAL_SHARP);
        break;
    case P_VIDEO_PALNYC:
        videoSetPalMode(video, VIDEO_PAL_SHARP_NOISE);
        break;
    case P_VIDEO_PALCOMP:
        videoSetPalMode(video, VIDEO_PAL_BLUR);
        break;
    case P_VIDEO_PALNCOMP:
        videoSetPalMode(video, VIDEO_PAL_BLUR_NOISE);
        break;
	case P_VIDEO_PALSCALE2X:
		videoSetPalMode(video, VIDEO_PAL_SCALE2X);
		break;
	case P_VIDEO_PALHQ2X:
		videoSetPalMode(video, VIDEO_PAL_HQ2X);
		break;
    }

    videoSetFrameSkip(video, properties->video.frameSkip);
}


void archUpdateEmuDisplayConfig() 
{
    videoSetColors(video, properties->video.saturation, properties->video.brightness, properties->video.contrast, properties->video.gamma);
    videoSetScanLines(video, properties->video.scanlinesEnable, properties->video.scanlinesPct);
    videoSetColorSaturation(video, properties->video.colorSaturationEnable, properties->video.colorSaturationWidth);
    videoSetDeInterlace(video, properties->video.deInterlace);
    videoSetFrameSkip(video, properties->video.frameSkip);
    switch (properties->video.monType) {
    case P_VIDEO_COLOR:
        videoSetColorMode(video, VIDEO_COLOR);
        break;
    case P_VIDEO_BW:
        videoSetColorMode(video, VIDEO_BLACKWHITE);
        break;
    case P_VIDEO_GREEN:
        videoSetColorMode(video, VIDEO_GREEN);
        break;
    case P_VIDEO_AMBER:
        videoSetColorMode(video, VIDEO_AMBER);
        break;
    }

    switch (properties->video.palEmu) {
    case P_VIDEO_PALNONE:
        videoSetPalMode(video, VIDEO_PAL_FAST);
        break;
    case P_VIDEO_PALMON:
        videoSetPalMode(video, VIDEO_PAL_MONITOR);
        break;
    case P_VIDEO_PALYC:
        videoSetPalMode(video, VIDEO_PAL_SHARP);
        break;
    case P_VIDEO_PALNYC:
        videoSetPalMode(video, VIDEO_PAL_SHARP_NOISE);
        break;
    case P_VIDEO_PALCOMP:
        videoSetPalMode(video, VIDEO_PAL_BLUR);
        break;
    case P_VIDEO_PALNCOMP:
        videoSetPalMode(video, VIDEO_PAL_BLUR_NOISE);
        break;
	case P_VIDEO_PALSCALE2X:
		videoSetPalMode(video, VIDEO_PAL_SCALE2X);
		break;
	case P_VIDEO_PALHQ2X:
		videoSetPalMode(video, VIDEO_PAL_HQ2X);
		break;
    }
}

int  archUpdateEmuDisplay(int syncMode) 
{
    SDL_Event event;

    event.type = SDL_USEREVENT;
    event.user.code = EVENT_UPDATE_DISPLAY;
    event.user.data1 = NULL;
    event.user.data2 = NULL;
    SDL_PushEvent(&event);

    if (properties->emulation.syncMethod == P_EMU_SYNCFRAMES) {
        archEventWait(dpyUpdateAckEvent, 500);
    }
    return 1;
}

int updateEmuDisplay() 
{
    FrameBuffer* frameBuffer;
    int bytesPerPixel = bitDepth / 8;
    char* dpyData  = (char*)surface->pixels;
	int pitch = surface->pitch;
    int borderWidth;

    frameBuffer = frameBufferGetViewFrame();
    if (frameBuffer == NULL) {
        frameBuffer = frameBufferGetWhiteNoiseFrame();
    }

    borderWidth = 320 - frameBuffer->maxWidth;

    videoRender(video, frameBuffer, bitDepth, 2, 
                dpyData + borderWidth * bytesPerPixel, 
                0, pitch, -1);

    if (borderWidth > 0) {
        int h = HEIGHT;
        while (h--) {
            memset(dpyData, 0x00, borderWidth * bytesPerPixel);
            memset(dpyData + (WIDTH - borderWidth) * bytesPerPixel, 0, borderWidth * bytesPerPixel);
            dpyData += pitch;
        }
    }

	if (SDL_MUSTLOCK(surface) && SDL_LockSurface(surface) < 0) {
        return 0;
    }
    SDL_UpdateRect(surface, 0, 0, WIDTH, HEIGHT);
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

    return 0; 
}

void setDefaultPaths(const char* rootDir)
{   
    char buffer[512];  

    propertiesSetDirectory(rootDir, rootDir);

    sprintf(buffer, "%s/Audio Capture", rootDir);
    archCreateDirectory(buffer);
    actionSetAudioCaptureSetDirectory(buffer, "");

    sprintf(buffer, "%s/QuickSave", rootDir);
    archCreateDirectory(buffer);
    actionSetQuickSaveSetDirectory(buffer, "");

    sprintf(buffer, "%s/SRAM", rootDir);
    archCreateDirectory(buffer);
    boardSetDirectory(buffer);

    sprintf(buffer, "%s/Casinfo", rootDir);
    archCreateDirectory(buffer);
    tapeSetDirectory(buffer, "");

    sprintf(buffer, "%s/Databases", rootDir);
    archCreateDirectory(buffer);
    mediaDbLoad(buffer);
}

static void handleEvent(SDL_Event* event) 
{
    switch (event->type) {
    case SDL_USEREVENT:
        switch (event->user.code) {
        case EVENT_UPDATE_DISPLAY:
            updateEmuDisplay();
            archEventSet(dpyUpdateAckEvent);
            break;
        }
        break;
    }
}

int main(int argc, char **argv)
{
    SDL_Event event;
    char szLine[8192] = "";
    int resetProperties;
    char path[512] = "";
    int i;
    int doQuit = 0;

    SDL_Init( SDL_INIT_EVERYTHING );

    for (i = 1; i < argc; i++) {
        strcat(szLine, argv[i]);
        strcat(szLine, " ");
    }

    setDefaultPaths(archGetCurrentDirectory());

    resetProperties = emuCheckResetArgument(szLine);
    strcat(path, archGetCurrentDirectory());
    strcat(path, DIR_SEPARATOR "bluemsx.ini");
    properties = propCreate(resetProperties, 0, P_KBD_EUROPEAN, 0, "");
    
    properties->emulation.syncMethod = P_EMU_SYNCTOVBLANKASYNC;

    if (resetProperties == 2) {
        propDestroy(properties);
        return 0;
    }
    
    bitDepth = 32;
    if (!createSdlWindow("blueMSXlite", WIDTH, HEIGHT, bitDepth)) {
        return 0;
    }
    
    dpyUpdateAckEvent = archEventCreate(0);

    video = videoCreate();
    videoSetColors(video, properties->video.saturation, properties->video.brightness, 
                  properties->video.contrast, properties->video.gamma);
    videoSetScanLines(video, properties->video.scanlinesEnable, properties->video.scanlinesPct);
    videoSetColorSaturation(video, properties->video.colorSaturationEnable, properties->video.colorSaturationWidth);
    
    mixer = mixerCreate();
    
    emulatorInit(properties, mixer);
    actionInit(properties, mixer);
    langInit();
    tapeSetReadOnly(properties->cassette.readOnly);
    
    langSetLanguage(properties->language);
    
    joystickPortSetType(0, properties->joy1.type);
    joystickPortSetType(1, properties->joy2.type);

    printerIoSetType(properties->ports.Lpt.type, properties->ports.Lpt.fileName);
    printerIoSetType(properties->ports.Lpt.type, properties->ports.Lpt.fileName);
    uartIoSetType(properties->ports.Com.type, properties->ports.Com.fileName);
    midiIoSetMidiOutType(properties->sound.MidiOut.type, properties->sound.MidiOut.fileName);
    midiIoSetMidiInType(properties->sound.MidiIn.type, properties->sound.MidiIn.fileName);
    ykIoSetMidiInType(properties->sound.YkIn.type, properties->sound.YkIn.fileName);

    emulatorRestartSound();

    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerSetChannelTypeVolume(mixer, i, properties->sound.mixerChannel[i].volume);
        mixerSetChannelTypePan(mixer, i, properties->sound.mixerChannel[i].pan);
        mixerEnableChannelType(mixer, i, properties->sound.mixerChannel[i].enable);
    }
    
    mixerSetMasterVolume(mixer, properties->sound.masterVolume);
    mixerEnableMaster(mixer, properties->sound.masterEnable);

    updateVideoRender(video, properties);
    archUpdateEmuDisplayConfig();

    mediaDbSetDefaultRomType(properties->cartridge.defaultType);

    for (i = 0; i < PROP_MAX_CARTS; i++) {
        if (properties->media.carts[i].fileName[0]) insertCartridge(properties, i, properties->media.carts[i].fileName, properties->media.carts[i].fileNameInZip, properties->media.carts[i].type, -1);
        updateExtendedRomName(i, properties->media.carts[i].fileName, properties->media.carts[i].fileNameInZip);
    }

    for (i = 0; i < PROP_MAX_DISKS; i++) {
        if (properties->media.disks[i].fileName[0]) insertDiskette(properties, i, properties->media.disks[i].fileName, properties->media.disks[i].fileNameInZip, -1);
        updateExtendedDiskName(i, properties->media.disks[i].fileName, properties->media.disks[i].fileNameInZip);
    }

    for (i = 0; i < PROP_MAX_TAPES; i++) {
        if (properties->media.tapes[i].fileName[0]) insertCassette(properties, i, properties->media.tapes[i].fileName, properties->media.tapes[i].fileNameInZip, 0);
        updateExtendedCasName(i, properties->media.tapes[i].fileName, properties->media.tapes[i].fileNameInZip);
    }

    {
        Machine* machine = machineCreate(properties->emulation.machineName);
        if (machine != NULL) {
            boardSetMachine(machine);
            machineDestroy(machine);
        }
    }
    boardSetFdcTimingEnable(properties->emulation.enableFdcTiming);
    boardSetY8950Enable(properties->sound.chip.enableY8950);
    boardSetYm2413Enable(properties->sound.chip.enableYM2413);
    boardSetMoonsoundEnable(properties->sound.chip.enableMoonsound);
    boardSetVideoAutodetect(properties->video.chipAutodetect);

    i = emuTryStartWithArguments(properties, szLine);
    if (i < 0) {
        printf("Failed to parse command line\n");
        return 0;
    }
    
    if (i == 0) {
        emulatorStart(NULL);
    }

    //While the user hasn't quit
    while(!doQuit) {
        SDL_WaitEvent(NULL);
        //While there's an event to handle
        while( SDL_PollEvent( &event ) ) {
            if( event.type == SDL_QUIT ) {
                doQuit = 1;
            }
            else {
                handleEvent(&event);
            }
        }
    }

    videoDestroy(video);
    propDestroy(properties);
    archSoundDestroy();
    mixerDestroy(mixer);

	// Clean up.
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) {
		SDL_Quit();
	}
    
    return 0;
}
