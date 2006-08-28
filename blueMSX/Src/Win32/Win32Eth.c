/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-28 03:32:41 $
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
#include "ArchEth.h"
#include "Win32Eth.h"

#include <stdio.h>

void archEthCreate() {}
void archEthDestroy() {}

int archEthSendPacket(UInt8* buffer, UInt32 length) {
    printf("Sending to %.2x:%.2x:%.2x:%.2x:%.2x:%.2x from %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
        buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6],
        buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);

    return 0;
}

int archEthRecvPacket(UInt8** buffer, UInt32* length) {
    return 0;
}

void archEthGetMacAddress(UInt8* macAddress) { memcpy(macAddress, "\0ABCDE", 6); }
