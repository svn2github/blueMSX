/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/NEC765.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-08-12 17:03:15 $
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
#ifndef NEC765_H
#define NEC765_H

#include "MsxTypes.h"

typedef struct NEC765 NEC765;

NEC765* nec765Create();
void nec765Destroy(NEC765* fdc);
void nec765Reset(NEC765* fdc);

UInt8 nec765Read(NEC765* fdc);
UInt8 nec765Peek(NEC765* fdc);
UInt8 nec765ReadStatus(NEC765* fdc);
UInt8 nec765PeekStatus(NEC765* fdc);
void nec765Write(NEC765* fdc, UInt8 value);

int nec765DiskChanged(NEC765* fdc, int drive);

int nec765GetInt(NEC765* fdc);
int nec765GetIndex(NEC765* fdc);

void nec765SaveState(NEC765* fdc);
void nec765LoadState(NEC765* fdc);

#endif
