/*****************************************************************************
** File:        WDCRC.h
**
** Author:      Tomas Karlsson
** 
** Description: Calculates a 16-bit Cyclic Redundancy Check (CRC) that is
**              compliant with the CCITT/ITU standard.
**              Synthetic polynomial = x^16 + x^12 + x^5 + 1
**              Truncated polynomial = 0x1021
**              Initial value = 0xFFFF
**
** More info:   www.bluemsx.com
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

#ifndef WDCRC_H
#define WDCRC_H

#include "msxTypes.h"

UInt16 calc_crc(UInt16 crc, UInt8 value);

#endif
