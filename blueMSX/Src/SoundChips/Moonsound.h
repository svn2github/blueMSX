/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/Moonsound.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-01-02 08:22:12 $
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
#ifndef MOONSOUND_H
#define MOONSOUND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "msxTypes.h"
#include "audioMixer.h"
    
typedef struct Moonsound Moonsound;

/* Constructor and destructor */
Moonsound* moonsoundCreate(Mixer* mixer, void* romData, int romSize, int sramSize);
void moonsoundDestroy(Moonsound* moonsound);
void moonsoundReset(Moonsound* moonsound);
UInt8 moonsoundRead(Moonsound* moonsound, UInt16 ioPort);
void moonsoundWrite(Moonsound* moonsound, UInt16 ioPort, UInt8 value);
void moonsoundLoadState(Moonsound* moonsound);
void moonsoundSaveState(Moonsound* moonsound);

void moonsoundTick(UInt32 elapsedTime);
void moonsoundSetOversampling(int Oversampling);

#ifdef __cplusplus
}
#endif


#endif

