/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SVI.h,v $
**
** $Revision: 1.5 $
**
** $Date: 2005-02-06 19:33:51 $
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
#ifndef SVI_H
#define SVI_H
 
#include "MSXTypes.h"
#include "Board.h"
//#include "RomMapper.h"
#include "Machine.h"
//#include "VDP.h"
#include "audioMixer.h"
#include <stdio.h>

int sviCreate(Machine* machine, 
              DeviceInfo* deviceInfo,
              int loadState,
              int frequency);
void sviDestroy();

void sviRun();
void sviStop();

void sviReset();

void sviInitStatistics(Machine* machine);

void sviSaveState();

UInt32 sviSystemTime();

void sviSetFrequency(UInt32 frequency);
int  sviGetRefreshRate();

void sviSetInt(UInt32 irq);
void sviClearInt(UInt32 irq);
UInt32 sviGetInt();

void sviSetCpuTimeout(UInt32 time);

void sviTraceEnable(const char* fileName);
void sviTraceDisable();
int  sviTraceGetEnable();

UInt8* sviGetRamPage(int page);
UInt32 sviGetRamSize();
UInt32 sviGetVramSize();

int sviUseRom();
int sviUseMegaRom();
int sviUseMegaRam();
int sviUseFmPac();

void sviChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip);
void sviChangeDiskette(int driveId, char* fileName, const char* fileInZipFile);
int  sviChangeCassette(char* name, const char* fileInZipFile);

#endif /* SVI_H */

