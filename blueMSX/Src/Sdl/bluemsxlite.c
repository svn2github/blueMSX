#define ENABLE_OPENGL

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
#include "ArchNotifications.h"
#include "JoystickPort.h"
#include "SdlShortcuts.h"
#ifdef ENABLE_OPENGL
#include <SDL/SDL_opengl.h>
#endif

void keyboardSetDirectory(char* directory);
void keyboardInit();
void keyboardSetFocus(int handle, int focus);
void keyboardUpdate();
int keyboardGetModifiers();

static Properties* properties;
static Video* video;
static Mixer* mixer;

static Properties* properties;
static Video* video;
static Mixer* mixer;
static Shortcuts* shortcuts;

static int pendingDisplayEvents = 0;
static void* dpyUpdateAckEvent = NULL;

static SDL_Surface *surface;
static int   bitDepth;
static char* displayData = NULL;
static int   displayPitch = 0;
#ifdef ENABLE_OPENGL
static GLfloat texCoordX;
static GLfloat texCoordY;
static GLuint textureId;
#endif

#define WIDTH  640
#define HEIGHT 480

#define EVENT_UPDATE_DISPLAY 2
#define EVENT_UPDATE_WINDOW  3

void createSdlSurface(int width, int height, int bitDepth, int fullscreen)
{
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

    if (surface != NULL) {
        displayData = (char*)surface->pixels;
        displayPitch = surface->pitch;
    }
}

static int roundUpPow2(int val) {
    int rv = 1;
    while (rv < val) rv *= 2;
    return rv;
}

#ifdef ENABLE_OPENGL
void createSdlGlSurface(int width, int height, int bitDepth, int fullscreen)
{
    unsigned texW = roundUpPow2(width);
	unsigned texH = roundUpPow2(height);

    int flags = SDL_OPENGL | (fullscreen ? SDL_FULLSCREEN : 0);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// try default bpp
	surface = SDL_SetVideoMode(width, height, 0, flags);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	displayData  = (char*)malloc(bitDepth / 8 * texW * texH);
	displayPitch = width * bitDepth / 8;

	texCoordX = (GLfloat)width  / texW;
	texCoordY = (GLfloat)height / texH;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (bitDepth == 16) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texW, texH, 0,
			            GL_RGB, GL_UNSIGNED_SHORT_5_6_5, displayData);
	} 
    else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0,
			            GL_RGBA, GL_UNSIGNED_BYTE, displayData);
	}
}
#endif

int createSdlWindow(const char *title, int width, int height, int bitDepth)
{
    int fullscreen = properties->video.size == P_VIDEO_SIZEFULLSCREEN;
    
    if (fullscreen) {
        width = properties->video.fullscreen.width;
        height = properties->video.fullscreen.height;
        bitDepth = properties->video.fullscreen.bitDepth;
    }

    surface = NULL;

#ifdef ENABLE_OPENGL
    if (properties->video.driver != P_VIDEO_DRVGDI) {
        createSdlGlSurface(width, height, bitDepth, fullscreen);
        if (surface == NULL) {
            properties->video.driver = P_VIDEO_DRVGDI;
        }
    }
    // Invert 24 bit RGB in GL mode
    videoSetRgbMode(video, properties->video.driver != P_VIDEO_DRVGDI);
#endif
    if (surface == NULL) {
        createSdlSurface(width, height, bitDepth, fullscreen);
    }

    //Set the window caption
    SDL_WM_SetCaption( title, NULL );

    return 1;
}


int updateEmuDisplay() 
{
    FrameBuffer* frameBuffer;
    int bytesPerPixel = bitDepth / 8;
    char* dpyData  = displayData;
    int borderWidth;

    frameBuffer = frameBufferFlipViewFrame(1);
    if (frameBuffer == NULL) {
        frameBuffer = frameBufferGetWhiteNoiseFrame();
    }

    borderWidth = 320 - frameBuffer->maxWidth;

#ifdef ENABLE_OPENGL
    if (properties->video.driver != P_VIDEO_DRVGDI) {
        GLfloat coordX = texCoordX;
        GLfloat coordY = texCoordY;

        if (properties->video.horizontalStretch) {
            coordX = texCoordX * (WIDTH - 2 * borderWidth) / WIDTH;
            borderWidth = 0;
        }

        videoRender(video, frameBuffer, bitDepth, 2,
                    dpyData + borderWidth * bytesPerPixel, 0, displayPitch, -1);

        if (borderWidth > 0) {
            int h = HEIGHT;
            while (h--) {
                memset(dpyData, 0, borderWidth * bytesPerPixel);
                memset(dpyData + (WIDTH - borderWidth) * bytesPerPixel, 0, borderWidth * bytesPerPixel);
                dpyData += displayPitch;
            }
        }

        glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, textureId);
	    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        if (bitDepth == 16) {
		    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT,
		                    GL_RGB, GL_UNSIGNED_SHORT_5_6_5, displayData);
	    } 
        else {
		    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT,
		                    GL_RGBA, GL_UNSIGNED_BYTE, dpyData);
	    }

        glBegin(GL_QUADS);
	    glTexCoord2f(0,      coordY); glVertex2i(0,     HEIGHT);
	    glTexCoord2f(coordX, coordY); glVertex2i(WIDTH, HEIGHT);
	    glTexCoord2f(coordX, 0     ); glVertex2i(WIDTH, 0     );
	    glTexCoord2f(0,      0     ); glVertex2i(0,     0     );
	    glEnd();

        glDisable(GL_TEXTURE_2D);

	    SDL_GL_SwapBuffers();

        return 0;
    }
#endif
    videoRender(video, frameBuffer, bitDepth, 2, 
                dpyData + borderWidth * bytesPerPixel, 0, displayPitch, -1);

    if (borderWidth > 0) {
        int h = HEIGHT;
        while (h--) {
            memset(dpyData, 0, borderWidth * bytesPerPixel);
            memset(dpyData + (WIDTH - borderWidth) * bytesPerPixel, 0, borderWidth * bytesPerPixel);
            dpyData += displayPitch;
        }
    }


    if (SDL_MUSTLOCK(surface) && SDL_LockSurface(surface) < 0) {
        return 0;
    }
    SDL_UpdateRect(surface, 0, 0, WIDTH, HEIGHT);
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

    return 0; 
}

int  archUpdateEmuDisplay(int syncMode) 
{
    SDL_Event event;

    if (pendingDisplayEvents > 1) {
        return 1;
    }

    pendingDisplayEvents++;

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

void archUpdateWindow() 
{
    SDL_Event event;

    event.type = SDL_USEREVENT;
    event.user.code = EVENT_UPDATE_WINDOW;
    event.user.data1 = NULL;
    event.user.data2 = NULL;
    SDL_PushEvent(&event);
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
    
    sprintf(buffer, "%s\\Keyboard Config", rootDir);
    archCreateDirectory(buffer);
    keyboardSetDirectory(buffer);

    sprintf(buffer, "%s\\Shortcut Profiles", rootDir);
    archCreateDirectory(buffer);
    shortcutsSetDirectory(buffer);
}

static void handleEvent(SDL_Event* event) 
{
    switch (event->type) {
    case SDL_USEREVENT:
        switch (event->user.code) {
        case EVENT_UPDATE_DISPLAY:
            updateEmuDisplay();
            archEventSet(dpyUpdateAckEvent);
            pendingDisplayEvents--;
            break;
        case EVENT_UPDATE_WINDOW:
            if (!createSdlWindow("blueMSXlite", WIDTH, HEIGHT, bitDepth)) {
                exit(0);
            }
            break;
        }
        break;
    case SDL_ACTIVEEVENT:
        if (event->active.state & SDL_APPINPUTFOCUS) {
            keyboardSetFocus(1, event->active.gain);
        }
        break;
    case SDL_KEYDOWN:
        shortcutCheckDown(shortcuts, HOTKEY_TYPE_KEYBOARD, keyboardGetModifiers(), event->key.keysym.sym);
        break;
    case SDL_KEYUP:
        shortcutCheckUp(shortcuts, HOTKEY_TYPE_KEYBOARD, keyboardGetModifiers(), event->key.keysym.sym);
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
    
    video = videoCreate();
    videoSetColors(video, properties->video.saturation, properties->video.brightness, 
                  properties->video.contrast, properties->video.gamma);
    videoSetScanLines(video, properties->video.scanlinesEnable, properties->video.scanlinesPct);
    videoSetColorSaturation(video, properties->video.colorSaturationEnable, properties->video.colorSaturationWidth);
    
    bitDepth = 32;
    if (!createSdlWindow("blueMSXlite", WIDTH, HEIGHT, bitDepth)) {
        return 0;
    }
    
    dpyUpdateAckEvent = archEventCreate(0);

    keyboardInit();

    mixer = mixerCreate();
    
    emulatorInit(properties, mixer);
    actionInit(video, properties, mixer);
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

    videoUpdateAll(video, properties);
    
    shortcuts = shortcutsCreate();

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
        SDL_WaitEvent(&event);
        do {
            if( event.type == SDL_QUIT ) {
                doQuit = 1;
            }
            else {
                handleEvent(&event);
            }
        } while(SDL_PollEvent(&event));
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
