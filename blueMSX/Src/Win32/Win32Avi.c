/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Avi.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-17 19:43:17 $
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
#include "Win32Avi.h"
#include <Vfw.h>
#include "VideoRender.h"
#include "Properties.h"

static PAVIFILE     aviFile;
static PAVISTREAM   aviStream;
static PAVISTREAM   aviSndStream;
static PAVISTREAM   aviVidStream;
static int          frameCount;
static int          sampleCount;
static int          aviStatusOk;
static Properties*  properties;
static Video*       video;

int aviOpen(HWND hwndOwner, char* filename, int fps)
{
    AVICOMPRESSOPTIONS options;
    AVICOMPRESSOPTIONS* optionsPtr;
    AVISTREAMINFO steamHdr;
    AVISTREAMINFO soundHdr;
    WAVEFORMATEX wfex;
    BITMAPINFOHEADER bi;

    AVIFileInit();

    frameCount = 0;
    sampleCount = 0;
    aviStatusOk  = 0;

    if (AVIFileOpen(&aviFile, filename, OF_WRITE | OF_CREATE, NULL) != 0) {
        return 0;
    }

	memset(&bi, 0, sizeof(bi));      
	bi.biSize       = 0x28;    
	bi.biPlanes     = 1;
	bi.biBitCount   = 32;
	bi.biWidth      = 640;
	bi.biHeight     = 480;
	bi.biSizeImage  = bi.biWidth * bi.biHeight * bi.biBitCount / 8;

    memset(&steamHdr, 0, sizeof(steamHdr));
    steamHdr.fccType = streamtypeVIDEO;
    steamHdr.dwScale = 1;
    steamHdr.dwRate  = fps;
    steamHdr.dwSuggestedBufferSize = bi.biSizeImage;

    if (AVIFileCreateStream(aviFile, &aviStream, &steamHdr) != 0) {
        return 0;
    }
      
    memset(&options, 0, sizeof(options));
    optionsPtr = &options;
    if (!AVISaveOptions(hwndOwner, 0, 1, &aviStream, &optionsPtr)) {
        return 0;
    }
  
    if (AVIMakeCompressedStream(&aviVidStream, aviStream, &options, NULL) != 0) {
        return 0;
    }
  
    // setup the video stream format
    if (AVIStreamSetFormat(aviVidStream, 0, &bi, bi.biSize + bi.biClrUsed * sizeof(RGBQUAD)) != 0) {
        return 0;
    }

    memset(&wfex, 0, sizeof(wfex));
    wfex.wFormatTag      = WAVE_FORMAT_PCM;
    wfex.nChannels       = 2;
    wfex.nSamplesPerSec  = 44100;
    wfex.wBitsPerSample  = 8 * sizeof(UInt16);
    wfex.nBlockAlign     = wfex.nChannels * wfex.wBitsPerSample / 8;
    wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;
    
    memset(&soundHdr, 0, sizeof(soundHdr));
    soundHdr.fccType         = streamtypeAUDIO;
    soundHdr.dwQuality       = (DWORD)-1;
    soundHdr.dwScale         = wfex.nBlockAlign;
    soundHdr.dwInitialFrames = 1;
    soundHdr.dwRate          = wfex.nAvgBytesPerSec;
    soundHdr.dwSampleSize    = wfex.nBlockAlign;

    if (AVIFileCreateStream(aviFile, &aviSndStream, &soundHdr) != 0) {
        return 0;
    }

    if (AVIStreamSetFormat(aviSndStream, 0, (void *)&wfex, sizeof(wfex)) != 0) {
        return 0;
    }

    aviStatusOk = 1;

    return 1;
}

void aviClose()
{
    if (aviSndStream != NULL) {
        AVIStreamClose(aviSndStream);
        aviSndStream = NULL;
    }

    if (aviVidStream != NULL) {
        AVIStreamClose(aviVidStream);
        aviVidStream = NULL;
    }

    if (aviStream != NULL) {
        AVIStreamClose(aviStream);
        aviStream = NULL;
    }

    if (aviFile != NULL) {
        AVIFileClose(aviFile);
        aviFile = NULL;
    }

    AVIFileExit();
}

void aviAddSound(Int16* buffer, int count)
{
    if (!aviStatusOk) {
        return;
    }

    if (AVIStreamWrite(aviSndStream, sampleCount, count, buffer, count * 4, 0, NULL, NULL) != 0) {
        aviStatusOk = 0;
    }

    sampleCount += count;
}

void aviAddFrame(void* buffer, int length)
{
    if (!aviStatusOk) {
        return;
    }

    if (AVIStreamWrite(aviVidStream, frameCount++, 1, buffer, length, AVIIF_KEYFRAME, NULL, NULL) != 0) {
        aviStatusOk = 0;
    }
}



struct AviSound {
    Mixer* mixer;
};

static Int32 aviSoundWrite(void* dummy, Int16 *buffer, UInt32 count)
{
    // Audio stream is stereo, and callback counts individual samples
    count /= 2; 

    aviAddSound(buffer, count);

    return 0;
}

AviSound* aviSoundCreate(HWND hwnd, Mixer* mixer, UInt32 sampleRate, UInt32 bufferSize, Int16 channels)
{
    AviSound* aviSound = (AviSound*)calloc(1, sizeof(AviSound));

    aviSound->mixer = mixer;

    // Force stereo
    mixerSetStereo(mixer, 1);
    mixerSetWriteCallback(mixer, aviSoundWrite, NULL, 256);

    return aviSound;
}

void aviSoundDestroy(AviSound* aviSound)
{
    mixerSetWriteCallback(aviSound->mixer, NULL, NULL, 0);
    free(aviSound);
}

void aviSoundSuspend(AviSound* aviSound)
{
}

void aviSoundResume(AviSound* aviSound)
{
}

int updateEmuDisplay(int updateAll) 
{
    FrameBuffer* frameBuffer;
    int bitDepth = 32;
    int bytesPerPixel = bitDepth / 8;
    char displayData[4 * 640 * 480];
    char* dpyData = displayData;
    int width  = 640;
    int height = 480;
    int borderWidth;
    int displayPitch = width * bitDepth / 8;

    frameBuffer = frameBufferFlipViewFrame(0); // Mix frames?
    if (frameBuffer == NULL) {
        frameBuffer = frameBufferGetWhiteNoiseFrame();
    }

    borderWidth = (320 - frameBuffer->maxWidth);

    videoRender(video, frameBuffer, bitDepth, 2, 
                dpyData + borderWidth * bytesPerPixel, 0, displayPitch, -1);

    if (borderWidth > 0) {
        int h = height;
        while (h--) {
            memset(dpyData, 0, borderWidth * bytesPerPixel);
            memset(dpyData + (width - borderWidth) * bytesPerPixel, 0, borderWidth * bytesPerPixel);
            dpyData += displayPitch;
        }
    }


    return 0; 
}
