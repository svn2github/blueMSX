/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Debugger/Debugger.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-02-12 09:30:07 $
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

#include "Debugger.h"
#include <stdlib.h>

struct Debugger {
    DebuggerEvent onEmulatorStart;
    DebuggerEvent onEmulatorStop;
    DebuggerEvent onEmulatorPause;
    DebuggerEvent onEmulatorResume;
};

#define MAX_DEVICES 64

struct DbgSnapshot {
    int count;
    DbgDevice* dbgDevice[MAX_DEVICES];
};

static void onDefault() {
}

Debugger* debuggerCreate(DebuggerEvent onEmulatorStart,
                         DebuggerEvent onEmulatorStop,
                         DebuggerEvent onEmulatorPause,
                         DebuggerEvent onEmulatorResume)
{
    Debugger* debugger = malloc(sizeof(Debugger));

    debugger->onEmulatorStart  = onEmulatorStart  ? onEmulatorStart  : onDefault;
    debugger->onEmulatorStop   = onEmulatorStop   ? onEmulatorStop   : onDefault;
    debugger->onEmulatorPause  = onEmulatorPause  ? onEmulatorPause  : onDefault;
    debugger->onEmulatorResume = onEmulatorResume ? onEmulatorResume : onDefault;

    return debugger;
}


void debuggerDestroy(Debugger* debugger)
{
    free(debugger);
}

DbgSnapshot* dbgSnapshotCreate(Debugger* debugger) 
{
    DbgSnapshot* dbgSnapshot = malloc(sizeof(DbgSnapshot));

    return dbgSnapshot;
}

void dbgSnapshotDestroy(DbgSnapshot* dbgSnapshot)
{
    free(dbgSnapshot);
}

