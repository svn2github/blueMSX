/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/MSX.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 08:05:52 $
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
#ifndef MSX_H
#define MSX_H
 
#include "MSXTypes.h"
#include "RomMapper.h"
#include "Machine.h"
#include "VDP.h"
#include "audioMixer.h"
#include <stdio.h>
#include "Board.h"

int msxRun(Machine* machine, 
           DeviceInfo* deviceInfo,
           Mixer* mixer,
           int loadState,
           int frequency);

void msxReset();

void msxInitStatistics(Machine* machine);

void msxSaveState();

void msxSetFrequency(UInt32 frequency);
int  msxGetRefreshRate();

void   msxSetInt(UInt32 irq);
void   msxClearInt(UInt32 irq);
UInt32 msxGetInt(UInt32 irq);

void msxTraceEnable(const char* fileName);
void msxTraceDisable();
int  msxTraceGetEnable();

UInt8* msxGetRamPage(int page);
UInt32 msxGetRamSize();
UInt32 msxGetVramSize();

int msxUseRom();
int msxUseMegaRom();
int msxUseMegaRam();
int msxUseFmPac();

void msxChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip);
void msxChangeDiskette(int driveId, char* fileName, const char* fileInZipFile);
void msxChangeCassette(char* name, const char* fileInZipFile);

#endif /* MSX_H */

