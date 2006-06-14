/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/MsxGunstick.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-06-14 07:39:24 $
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
    int dx, dy;

    archMouseGetState(&dx, &dy);

#if 1
    dy = dy * joystick->scanlines / 0x10000;
    frameBuffer = frameBufferGetLastDrawnFrame(dy * joystick->scanlines / 0x10000);
    if (frameBuffer != NULL) {
        int i;

        joystick->scanlines = frameBuffer->lines;

        dx = dx * (frameBuffer->line[dy].doubleWidth ? 2 : 1) * frameBuffer->maxWidth / 0x10000;

        for (i = MAX(dy - 10, 0); i <= MIN(dy + 10, frameBuffer->lines); i++) {
            UInt16 rgb = frameBuffer->line[i].buffer[dx];
            int R = 8 * ((rgb >> 10) & 0x01f);
            int G = 8 * ((rgb >> 5) & 0x01f);
            int B = 8 * ((rgb >> 0) & 0x01f);
            int Y = (int)(0.2989*R + 0.5866*G + 0.1145*B);
        
            if (Y > 200) {
                state |= 1 << 1;
                break;
            }
        }
    }
#else
    frameBuffer = frameBufferGetLastDrawnFrame(dy * joystick->scanlines / 0x10000);

    if (frameBuffer != NULL) {
        int width;
        int height;
        int i;

        joystick->scanlines = frameBuffer->lines;

        dy = dy * frameBuffer->lines / 0x10000;
        width = (frameBuffer->line[dy].doubleWidth ? 2 : 1) * frameBuffer->maxWidth;
        height = frameBuffer->lines;
        dx = dx * width / 0x10000;

        for (i = MAX(dy - 10, 0); i <= MIN(dy + 10, height); i++) {
            UInt16 rgb = frameBuffer->line[i].buffer[dx];
            int R = 8 * ((rgb >> 10) & 0x01f);
            int G = 8 * ((rgb >> 5) & 0x01f);
            int B = 8 * ((rgb >> 0) & 0x01f);
            int Y = (int)(0.2989*R + 0.5866*G + 0.1145*B);
        
            if (Y > 200) {
                state |= 1 << 1;
                break;
            }
        }
    }
#endif
    
    return ~state & 0x3f;
}

MsxJoystickDevice* msxGunstickCreate()
{
    MsxGunstick* joystick = (MsxGunstick*)calloc(1, sizeof(MsxGunstick));
    joystick->joyDevice.read   = read;
    
    return (MsxJoystickDevice*)joystick;
}