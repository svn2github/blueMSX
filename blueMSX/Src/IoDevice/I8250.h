/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8250.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-02-05 06:39:19 $
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
#ifndef I8250_H
#define I8250_H

#include "MSXTypes.h"

typedef struct I8250 I8250;

UInt8 i8250Read(I8250* i8250, UInt16 port);
void i8250Write(I8250* i8250, UInt16 port, UInt8 value);

void i8250Receive(I8250* i8250, UInt8 value);

void i8250LoadState(I8250* i8250);
void i8250SaveState(I8250* i8250);

void i8250Reset(I8250* i8250);
void i8250Destroy(I8250* i8250); 
I8250* i8250Create(void);

#endif
