/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/CRTC6845.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-01-17 02:36:32 $
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
#ifndef CRTC_H
#define CRTC_H

#include "MSXTypes.h"

typedef enum { CRTC_MSX, CRTC_SVI } CrtcConnector;

UInt8 crtcRead(void* dummy, UInt16 ioPort);
void crtcWrite(void* dummy, UInt16 ioPort, UInt8 value);
void crtcWriteLatch(void* dummy, UInt16 ioPort, UInt8 value);
void crtcMemEnable(void* dummy, UInt16 ioPort, UInt8 value);

void crtcMemWrite(UInt16 address, UInt8 value);
UInt8 crtcMemRead(UInt16 address);
UInt8 crtcMemBankStatus(void);

void crtcReset(void);
void crtcInit(CrtcConnector connector);

#endif
