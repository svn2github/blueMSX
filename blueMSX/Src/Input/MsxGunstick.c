/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/MsxGunstick.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2006-06-14 21:30:29 $
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
#include "MsxGunstick.h"
#include "InputEvent.h"
#include "ArchInput.h"
#include "FrameBuffer.h"
#include "VDP.h"

#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct MsxGunstick {
    MsxJoystickDevice joyDevice;
    int scanlines;
};

static UInt8 read(MsxGunstick* joystick) {
    FrameBuffer* frameBuffer;
    UInt8 state = (archMouseGetButtonState(0) & 1) << 4;
    int mx, my;

    vdpForceSync();

    archMouseGetState(&mx, &my);

    my = my * joystick->scanlines / 0x10000;

    frameBuffer = frameBufferGetLastDrawnFrame(my);
    
    if (frameBuffer != NULL) {
        joystick->scanlines = frameBuffer->lines;

        if (my >= 0 && my < frameBuffer->lines) {
            UInt16 rgb = frameBuffer->line[my].buffer[
                mx * (frameBuffer->line[my].doubleWidth ? 2 : 1) * frameBuffer->maxWidth / 0x10000];
            int R = 8 * ((rgb >> 10) & 0x01f);
            int G = 8 * ((rgb >> 5) & 0x01f);
            int B = 8 * ((rgb >> 0) & 0x01f);
            int Y = (int)(0.2989*R + 0.5866*G + 0.1145*B);
        
            if (Y > 200) {
                state |= 1 << 1;
            }
        }
    }
    
    return ~state & 0x3f;
}

MsxJoystickDevice* msxGunstickCreate()
{
    MsxGunstick* joystick = (MsxGunstick*)calloc(1, sizeof(MsxGunstick));
    joystick->joyDevice.read   = read;
    
    return (MsxJoystickDevice*)joystick;
}