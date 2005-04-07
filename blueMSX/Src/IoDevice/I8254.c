/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8254.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-04-07 19:23:41 $
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

#include "I8254.h"
#include "SaveState.h"
#include <stdlib.h>


static void outDummy(void* ref, int timer, int state) {
}

struct I8254
{
    I8254Out out;

    void* ref;
};

UInt8 i8254Read(I8254* i8254, UInt16 port)
{
    return 0xff;
}

void i8254Write(I8254* i8254, UInt16 port, UInt8 value)
{
}

void i8254SaveState(I8254* i8254)
{
    SaveState* state = saveStateOpenForWrite("i8254");

    saveStateClose(state);
}

void i8254LoadState(I8254* i8254)
{
    SaveState* state = saveStateOpenForRead("i8254");

    saveStateClose(state);
}

void i8254Reset(I8254* i8254)
{
}

void i8254Destroy(I8254* i8254) 
{
    free(i8254);
}

void i8254SetGate(int timer, int state)
{
}

I8254* i8254Create(I8254Out out, void* ref)
{
    I8254* i8254 = calloc(1, sizeof(I8254));
    
    i8254->out = out ? out : outDummy;
    i8254->ref = ref;

    return i8254;
}
