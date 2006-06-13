/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/MsxAsciiLaser.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-06-13 06:24:20 $
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
#include "MsxAsciiLaser.h"
#include "InputEvent.h"
#include "ArchInput.h"
#include "FrameBuffer.h"

#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct MsxAsciiLaser {
    MsxJoystickDevice joyDevice;
    int scanlines;
};

static UInt8 read(MsxAsciiLaser* joystick) {
    FrameBuffer* frameBuffer;
    UInt8 state = (archMouseGetButtonState(0) & 1) << 5;
    int dx, dy;

    archMouseGetState(&dx, &dy);

    frameBuffer = frameBufferGetLastDrawnFrame(dy * joystick->scanlines / 0x10000);

    if (frameBuffer != NULL) {
        int width;
        int i;

        joystick->scanlines = frameBuffer->lines;

        dy = dy * frameBuffer->lines / 0x10000;
        width = (frameBuffer->line[dy].doubleWidth ? 2 : 1) * frameBuffer->maxWidth;
        dx = dx * width / 0x10000;

        for (i = MAX(dx - 0, 0); i <= MIN(dx + 0, width); i++) {
            UInt16 rgb = frameBuffer->line[dy].buffer[i];
            int R = 8 * ((rgb >> 10) & 0x01f);
            int G = 8 * ((rgb >> 5) & 0x01f);
            int B = 8 * ((rgb >> 0) & 0x01f);
            int Y = (int)(0.2989*R + 0.5866*G + 0.1145*B);
        
            if (Y > 128) {
                state |= 1 << 4;
                break;
            }
        }
    }
    
    return ~state & 0x3f;
}

MsxJoystickDevice* msxAsciiLaserCreate()
{
    MsxAsciiLaser* joystick = (MsxAsciiLaser*)calloc(1, sizeof(MsxAsciiLaser));
    joystick->joyDevice.read   = read;
    
    return (MsxJoystickDevice*)joystick;
}