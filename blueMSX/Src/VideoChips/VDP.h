/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/VDP.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:48:48 $
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
#ifndef VDP_H
#define VDP_H

#include "MSXTypes.h"

extern UInt8 VDPStatus[16];            /* VDP status reg-ers  */


typedef enum { VDP_V9938, VDP_V9958, VDP_TMS9929A, VDP_TMS99x8A } VdpVersion;
typedef enum { VDP_SYNC_AUTO, VDP_SYNC_50HZ, VDP_SYNC_60HZ } VdpSyncMode; 
typedef enum { VDP_MSX, VDP_SVI, VDP_COLECO } VdpConnector;

void vdpInit(VdpConnector connector, VdpVersion version, VdpSyncMode sync, int vramPages);
void vdpDestroy();

void vdpReset();

int  vdpGetRefreshRate();

UInt8 vdpRead(void* dummy, UInt16 ioPort);
UInt8 vdpReadStatus(void* dummy, UInt16 ioPort);

void vdpWrite(void* dummy, UInt16 ioPort, UInt8 value);
void vdpWriteLatch(void* dummy, UInt16 ioPort, UInt8 value);
void vdpWritePaletteLatch(void* dummy, UInt16 ioPort, UInt8 value);
void vdpWriteRegister(void* dummy, UInt16 ioPort, UInt8 value);

int vdpRefreshLine(UInt32 systemTime);

void vdpLoadState();
void vdpSaveState();

void vdpSetSpritesEnable(int enable);
int  vdpGetSpritesEnable();
void vdpSetDisplayEnable(int enable);
int  vdpGetDisplayEnable();

/* The following methods needs target dependent implementation */
extern void SetColor(int palEntry, UInt32 rgbColor);
extern void RefreshScreen(int, int, int);


#endif

