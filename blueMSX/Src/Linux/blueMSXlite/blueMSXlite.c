/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Linux/blueMSXlite/blueMSXlite.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-09-30 05:50:27 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vikl, Tomas Karlsson
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
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

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

static Properties* properties;
static Video* video;
static Mixer* mixer;

static Window window;
static Display* display; 
static Screen* screen;
static XImage* ximage;
static int bitDepth;

#define WIDTH  640
#define HEIGHT 480

int createX11Window(const char *title, int width, int height, int depth)
{
  XSetWindowAttributes windowAttributes;
  XSizeHints sizeHints;
  XWMHints xvmHints;
  XVisualInfo visualInfo;
  int i;
  int j;

  display = XOpenDisplay(NULL);
  if (!display) {
      return 0;
  }
  screen = DefaultScreenOfDisplay(display);

  windowAttributes.event_mask       = FocusChangeMask|KeyPressMask|KeyReleaseMask|StructureNotifyMask;
  windowAttributes.background_pixel = BlackPixelOfScreen(screen);
  windowAttributes.backing_store    = Always;

  window = XCreateWindow(display, RootWindowOfScreen(screen), 0, 0, width, height, 1,
                         CopyFromParent, CopyFromParent, CopyFromParent,
                         CWBackPixel|CWEventMask|CWBackingStore, &windowAttributes);
  if (!window) {
      return 0;
  }

  sizeHints.flags       = PSize|PMinSize|PMaxSize|PResizeInc;
  sizeHints.min_width   = width;
  sizeHints.max_width   = width;
  sizeHints.base_width  = width;
  sizeHints.width_inc   = sizeof(int);
  sizeHints.min_height  = height;
  sizeHints.max_height  = height;
  sizeHints.base_height = height;
  sizeHints.height_inc  = sizeof(int);
  xvmHints.input        = True;
  xvmHints.flags        = InputHint;

  XSetWMHints(display, window, &xvmHints);
  XSetWMNormalHints(display, window, &sizeHints);
  XStoreName(display, window, title);

  XMapRaised(display, window);
  XClearWindow(display, window);

  
  depth = DefaultDepthOfScreen(screen);
  i = XScreenNumberOfScreen(screen);
  for (j = 7; j >= 0 && !XMatchVisualInfo(display, i, depth, j, &visualInfo); j--);
  if (j < 0) {
      return 0;
  }

    ximage = XCreateImage(display, visualInfo.visual, depth, ZPixmap, 
                          0, NULL, width, height, 32, 0);
    if (!ximage) {
        return 0;
    }

    ximage->data = (char*)malloc(width * height * depth / 8);
  
  return 1;
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

    archUpdateEmuDisplay(1);
}

int  archUpdateEmuDisplay(int synchronous) 
{
    FrameBuffer* frameBuffer;
    int borderWidth;
    int dstOffset;

    frameBuffer = frameBufferGetViewFrame();
    if (frameBuffer == NULL) {
        frameBuffer = frameBufferGetWhiteNoiseFrame();
    }

    borderWidth = (640 - frameBuffer->maxWidth) * bitDepth / 8;
    dstOffset = borderWidth > 0 ? borderWidth / 2 : 0;

    videoRender(video, frameBuffer, bitDepth, 2, ximage->data, dstOffset, WIDTH * bitDepth / 8, -1);

    if (borderWidth > 0) {
        char* ptr  = ximage->data;                    
        int h = HEIGHT;
        while (h--) {
            memset(ptr, 0, borderWidth);
            memset(ptr + 640 - borderWidth, 0, borderWidth);
            ptr += WIDTH * bitDepth / 8;
        }
    }

    XSync(display, 0);

    return 0; 
}

void setDefaultPaths(const char* rootDir)
{   
    char buffer[512];  

    sprintf(buffer, "%s\\Audio Capture", rootDir);
    mkdir(buffer);
    actionSetAudioCaptureSetDirectory(buffer, "");

    sprintf(buffer, "%s\\QuickSave", rootDir);
    mkdir(buffer);
    actionSetQuickSaveSetDirectory(buffer, "");

    sprintf(buffer, "%s\\SRAM", rootDir);
    mkdir(buffer);
    boardSetDirectory(buffer);

    sprintf(buffer, "%s\\Casinfo", rootDir);
    mkdir(buffer);
    tapeSetDirectory(buffer, "");

    sprintf(buffer, "%s\\Databases", rootDir);
    mkdir(buffer);
    mediaDbLoad(buffer);
}


int main(int argc, char **argv)
{
    char szLine[8192] = "";
    int resetProperties;
    char path[512] = "";
    int i;

    for (i = 1; i < argc; i++) {
        strcat(szLine, argv[i]);
        strcat(szLine, " ");
    }

    resetProperties = emuCheckResetArgument(szLine);
    strcat(path, archGetCurrentDirectory());
    strcat(path, "\\bluemsx.ini");
    properties = propCreate(path, resetProperties, 0, 0, 0, "");
    
    if (resetProperties == 2) {
        propDestroy(properties);
        return 0;
    }
    
    bitDepth = 32;
    if (!createX11Window("blueMSXlite", WIDTH, HEIGHT, bitDepth)) {
        return 0;
    }

    setDefaultPaths(archGetCurrentDirectory());

    printf("%d\n", __LINE__);
    video = videoCreate();
    videoSetColors(video, properties->video.saturation, properties->video.brightness, 
                  properties->video.contrast, properties->video.gamma);
    videoSetScanLines(video, properties->video.scanlinesEnable, properties->video.scanlinesPct);
    videoSetColorSaturation(video, properties->video.colorSaturationEnable, properties->video.colorSaturationWidth);

    mixer = mixerCreate();
    
    emulatorInit(properties, mixer);
    actionInit(properties, mixer);
    tapeSetReadOnly(properties->cassette.readOnly);
    
    printerIoSetType(properties->ports.Lpt.type, properties->ports.Lpt.fileName);
    uartIoSetType(properties->ports.Com.type, properties->ports.Com.fileName);
    midiIoSetMidiOutType(properties->sound.MidiOut.type, properties->sound.MidiOut.fileName);

    emulatorRestartSound();

    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerSetChannelTypeVolume(mixer, i, properties->sound.mixerChannel[i].volume);
        mixerSetChannelTypePan(mixer, i, properties->sound.mixerChannel[i].pan);
        mixerEnableChannelType(mixer, i, properties->sound.mixerChannel[i].enable);
    }
    
    mixerSetMasterVolume(mixer, properties->sound.masterVolume);
    mixerEnableMaster(mixer, properties->sound.masterEnable);

    archUpdateEmuDisplayConfig();

    mediaDbSetDefaultRomType(properties->cartridge.defaultType);

    if (properties->cartridge.slotA[0]) insertCartridge(properties, 0, properties->cartridge.slotA, properties->cartridge.slotAZip, properties->cartridge.slotAType, -1);
    if (properties->cartridge.slotB[0]) insertCartridge(properties, 1, properties->cartridge.slotB, properties->cartridge.slotBZip, properties->cartridge.slotBType, -1);
    if (properties->diskdrive.slotA[0]) insertDiskette(properties, 0, properties->diskdrive.slotA, properties->diskdrive.slotAZip, -1);
    if (properties->diskdrive.slotB[0]) insertDiskette(properties, 1, properties->diskdrive.slotB, properties->diskdrive.slotBZip, -1);

    updateExtendedRomName(0, properties->cartridge.slotA, properties->cartridge.slotAZip);
    updateExtendedRomName(1, properties->cartridge.slotB, properties->cartridge.slotBZip);
    updateExtendedDiskName(0, properties->diskdrive.slotA, properties->diskdrive.slotAZip);
    updateExtendedDiskName(1, properties->diskdrive.slotB, properties->diskdrive.slotBZip);
    updateExtendedCasName(properties->cassette.tape, properties->cassette.tapeZip);

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

    XSync(display, 0);
    
    if (emuTryStartWithArguments(properties, szLine) < 0) {           
        return 0;
    }

    for (i = 0; i < 5000; i++) {
        archThreadSleep(10);
    }

    
    videoDestroy(video);
    propDestroy(properties);
    archSoundDestroy();
    mixerDestroy(mixer);

    return 0;
}
