/*****************************************************************************
** File:        StrcmpNoCase.c
**
** More info:   www.bluemsx.com
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

#include "StrcmpNoCase.h"
#include <string.h>
#include <stdlib.h>


int strcmpnocase(const char* str1, const char* str2) {
    char s1[128];
    char s2[128];
    int i;

    memset(s1, 0, 128);
    memset(s2, 0, 128);

    for (i = 0; str1[i]; i++) s1[i] = toupper(str1[i]);
    for (i = 0; str2[i]; i++) s2[i] = toupper(str2[i]);

    return strcmp(s1, s2);
}