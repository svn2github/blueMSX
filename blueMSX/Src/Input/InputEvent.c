/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/InputEvent.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-11-02 06:58:20 $
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
#include "InputEvent.h"
#include "ArchInput.h"

static char* eventNames[256];
int   eventMap[256];

static void initKeyNameTable()
{
    eventNames[EC_NONE   ] = "none";
    eventNames[EC_F1     ] = "f1";
    eventNames[EC_F2     ] = "f2";
    eventNames[EC_F3     ] = "f3";
    eventNames[EC_F4     ] = "f4";
    eventNames[EC_F5     ] = "f5";
    eventNames[EC_STOP   ] = "stop";
    eventNames[EC_CLS    ] = "cls";
    eventNames[EC_SELECT ] = "select";
    eventNames[EC_INS    ] = "ins";
    eventNames[EC_DEL    ] = "del";
    eventNames[EC_ESC    ] = "esc";
    eventNames[EC_1      ] = "1";
    eventNames[EC_2      ] = "2";
    eventNames[EC_3      ] = "3";
    eventNames[EC_4      ] = "4";
    eventNames[EC_5      ] = "5";
    eventNames[EC_6      ] = "6";
    eventNames[EC_7      ] = "7";
    eventNames[EC_8      ] = "8";
    eventNames[EC_9      ] = "9";
    eventNames[EC_0      ] = "0";
    eventNames[EC_NEG    ] = "neg";
    eventNames[EC_CIRCFLX] = "circomflex";
    eventNames[EC_BKSLASH] = "backslash";
    eventNames[EC_BKSPACE] = "backspace";
    eventNames[EC_TAB    ] = "tab";
    eventNames[EC_Q      ] = "q";
    eventNames[EC_W      ] = "w";
    eventNames[EC_E      ] = "e";
    eventNames[EC_R      ] = "r";
    eventNames[EC_T      ] = "t";
    eventNames[EC_Y      ] = "y";
    eventNames[EC_U      ] = "u";
    eventNames[EC_I      ] = "i";
    eventNames[EC_O      ] = "o";
    eventNames[EC_P      ] = "p";
    eventNames[EC_AT     ] = "at";
    eventNames[EC_LBRACK ] = "leftbracket";
    eventNames[EC_RETURN ] = "return";
    eventNames[EC_CTRL   ] = "ctrl";
    eventNames[EC_A      ] = "a";
    eventNames[EC_S      ] = "s";
    eventNames[EC_D      ] = "d";
    eventNames[EC_F      ] = "f";
    eventNames[EC_G      ] = "g";
    eventNames[EC_H      ] = "h";
    eventNames[EC_J      ] = "j";
    eventNames[EC_K      ] = "k";
    eventNames[EC_L      ] = "l";
    eventNames[EC_SEMICOL] = "semicolon";
    eventNames[EC_COLON  ] = "colon";
    eventNames[EC_RBRACK ] = "rightbracket";
    eventNames[EC_LSHIFT ] = "leftshift";
    eventNames[EC_Z      ] = "z";
    eventNames[EC_X      ] = "x";
    eventNames[EC_C      ] = "c";
    eventNames[EC_V      ] = "v";
    eventNames[EC_B      ] = "b";
    eventNames[EC_N      ] = "n";
    eventNames[EC_M      ] = "m";
    eventNames[EC_COMMA  ] = "comma";
    eventNames[EC_PERIOD ] = "period";
    eventNames[EC_DIV    ] = "div";
    eventNames[EC_UNDSCRE] = "underscore";
    eventNames[EC_RSHIFT ] = "rightshift";
    eventNames[EC_CAPS   ] = "caps";
    eventNames[EC_GRAPH  ] = "graph";
    eventNames[EC_TORIKE ] = "torikeshi";
    eventNames[EC_SPACE  ] = "space";
    eventNames[EC_JIKKOU ] = "jikkou";
    eventNames[EC_CODE   ] = "code";
    eventNames[EC_PAUSE  ] = "pause";
    eventNames[EC_LEFT   ] = "left";
    eventNames[EC_UP     ] = "up";
    eventNames[EC_DOWN   ] = "down";
    eventNames[EC_RIGHT  ] = "right";
    eventNames[EC_NUM7   ] = "num7";
    eventNames[EC_NUM8   ] = "num8";
    eventNames[EC_NUM9   ] = "num9";
    eventNames[EC_NUMDIV ] = "numdiv";
    eventNames[EC_NUM4   ] = "num4";
    eventNames[EC_NUM5   ] = "num5";
    eventNames[EC_NUM6   ] = "num6";
    eventNames[EC_NUMMUL ] = "nummul";
    eventNames[EC_NUM1   ] = "num1";
    eventNames[EC_NUM2   ] = "num2";
    eventNames[EC_NUM3   ] = "num3";
    eventNames[EC_NUMSUB ] = "numsub";
    eventNames[EC_NUM0   ] = "num0";
    eventNames[EC_NUMPER ] = "numperiod";
    eventNames[EC_NUMCOM ] = "numcomma";
    eventNames[EC_NUMADD ] = "numadd";
    eventNames[EC_PRINT  ] = "print";

    eventNames[EC_JOY1_UP     ] = "joy1_up";
    eventNames[EC_JOY1_DOWN   ] = "joy1_down";
    eventNames[EC_JOY1_LEFT   ] = "joy1_left";
    eventNames[EC_JOY1_RIGHT  ] = "joy1_right";
    eventNames[EC_JOY1_BUTTON1] = "joy1_button1";
    eventNames[EC_JOY1_BUTTON2] = "joy1_button2";
    eventNames[EC_JOY1_BUTTON3] = "joy1_button3";
    eventNames[EC_JOY1_BUTTON4] = "joy1_button4";
    eventNames[EC_JOY1_BUTTON5] = "joy1_button5";
    eventNames[EC_JOY1_BUTTON6] = "joy1_button6";
    
    eventNames[EC_JOY2_UP     ] = "joy2_up";
    eventNames[EC_JOY2_DOWN   ] = "joy2_down";
    eventNames[EC_JOY2_LEFT   ] = "joy2_left";
    eventNames[EC_JOY2_RIGHT  ] = "joy2_right";
    eventNames[EC_JOY2_BUTTON1] = "joy2_button1";
    eventNames[EC_JOY2_BUTTON2] = "joy2_button2";
    eventNames[EC_JOY2_BUTTON3] = "joy2_button3";
    eventNames[EC_JOY2_BUTTON4] = "joy2_button4";
    eventNames[EC_JOY2_BUTTON5] = "joy2_button5";
    eventNames[EC_JOY2_BUTTON6] = "joy2_button6";
}

int inputEventStringToCode(const char* eventName) 
{
    int i;

    for (i = 0; i < EC_KEYCOUNT; i++) {
        if (0 == strcmp(eventName, eventNames[i])) {
            return i;
        }
    }
    return 0;
}

const char* inputEventCodeToString(int eventCode) 
{
    if (eventNames[0] == 0) {
        initKeyNameTable();
    }

    if (eventCode >= EC_KEYCOUNT) {
        eventCode = 0;
    }
    return eventNames[eventCode];
}

void inputEventReset() 
{
    memset(eventMap, 0, sizeof(eventMap));
}
