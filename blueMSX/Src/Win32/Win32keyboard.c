/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32keyboard.c,v $
**
** $Revision: 1.21 $
**
** $Date: 2005-06-17 19:29:33 $
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
#define DIRECTINPUT_VERSION     0x0500
#include "Win32keyboard.h"
#include "Keyboard.h"
#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
#include <dinput.h>

#define KBD_TABLE_LEN 512

static int kbdTable[KBD_TABLE_LEN];
static int kbdTableBackup[KBD_TABLE_LEN];
static int keyStatus[KBD_TABLE_LEN];
static char dikStrings[KBD_TABLE_LEN][32];
static int selectedKey;
static int selectedDikKey;
static int editEnabled;

static char keyboardConfigDir[MAX_PATH];

static char DefaultConfigName[] = "blueMSX Default";

static char currentConfigFile[MAX_PATH];

#define KEY_CODE_BUTTON1 256
#define KEY_CODE_JOYUP    (256 + 32 + 0)
#define KEY_CODE_JOYDOWN  (256 + 32 + 1)
#define KEY_CODE_JOYLEFT  (256 + 32 + 2)
#define KEY_CODE_JOYRIGHT (256 + 32 + 3)

#define INIT_DIK(val) strcpy(dikStrings[DIK_##val], #val)

static void initDikStr()
{
    int i;

    INIT_DIK(0);
    INIT_DIK(1);
    INIT_DIK(2);
    INIT_DIK(3);
    INIT_DIK(4);
    INIT_DIK(5);
    INIT_DIK(6);
    INIT_DIK(7);
    INIT_DIK(8);
    INIT_DIK(9);
    INIT_DIK(A);
    INIT_DIK(ABNT_C1);
    INIT_DIK(ABNT_C2);
    INIT_DIK(ADD);
    INIT_DIK(APOSTROPHE);
    INIT_DIK(APPS);
    INIT_DIK(AT);
    INIT_DIK(AX);
    INIT_DIK(B);
    INIT_DIK(BACK);
    INIT_DIK(BACKSLASH);
    INIT_DIK(C);
    INIT_DIK(CALCULATOR);
    INIT_DIK(CAPITAL);
    INIT_DIK(COLON);
    INIT_DIK(COMMA);
    INIT_DIK(CONVERT);
    INIT_DIK(D);
    INIT_DIK(DECIMAL);
    INIT_DIK(DELETE);
    INIT_DIK(DIVIDE);
    INIT_DIK(DOWN);
    INIT_DIK(E);
    INIT_DIK(END);
    INIT_DIK(EQUALS);
    INIT_DIK(ESCAPE);
    INIT_DIK(F);
    INIT_DIK(F1);
    INIT_DIK(F2);
    INIT_DIK(F3);
    INIT_DIK(F4);
    INIT_DIK(F5);
    INIT_DIK(F6);
    INIT_DIK(F7);
    INIT_DIK(F8);
    INIT_DIK(F9);
    INIT_DIK(F10);
    INIT_DIK(F11);
    INIT_DIK(F12);
    INIT_DIK(F13);
    INIT_DIK(F14);
    INIT_DIK(F15);
    INIT_DIK(G);
    INIT_DIK(GRAVE);
    INIT_DIK(H);
    INIT_DIK(HOME);
    INIT_DIK(I);
    INIT_DIK(INSERT);
    INIT_DIK(J);
    INIT_DIK(K);
    INIT_DIK(KANA);
    INIT_DIK(KANJI);
    INIT_DIK(L);
    INIT_DIK(LBRACKET);
    INIT_DIK(LCONTROL);
    INIT_DIK(LEFT);
    INIT_DIK(LMENU);
    INIT_DIK(LSHIFT);
    INIT_DIK(LWIN);
    INIT_DIK(M);
    INIT_DIK(MAIL);
    INIT_DIK(MEDIASELECT);
    INIT_DIK(MEDIASTOP);
    INIT_DIK(MINUS);
    INIT_DIK(MULTIPLY);
    INIT_DIK(MUTE);
    INIT_DIK(MYCOMPUTER);
    INIT_DIK(N);
    INIT_DIK(NEXT);
    INIT_DIK(NEXTTRACK);
    INIT_DIK(NOCONVERT);
    INIT_DIK(NUMLOCK);
    INIT_DIK(NUMPAD0);
    INIT_DIK(NUMPAD1);
    INIT_DIK(NUMPAD2);
    INIT_DIK(NUMPAD3);
    INIT_DIK(NUMPAD4);
    INIT_DIK(NUMPAD5);
    INIT_DIK(NUMPAD6);
    INIT_DIK(NUMPAD7);
    INIT_DIK(NUMPAD8);
    INIT_DIK(NUMPAD9);
    INIT_DIK(NUMPADCOMMA);
    INIT_DIK(NUMPADENTER);
    INIT_DIK(NUMPADEQUALS);
    INIT_DIK(O);
    INIT_DIK(OEM_102);
    INIT_DIK(P);
    INIT_DIK(PAUSE);
    INIT_DIK(PERIOD);
    INIT_DIK(PLAYPAUSE);
    INIT_DIK(POWER);
    INIT_DIK(PREVTRACK);
    INIT_DIK(PRIOR);
    INIT_DIK(Q);
    INIT_DIK(R);
    INIT_DIK(RBRACKET);
    INIT_DIK(RCONTROL);
    INIT_DIK(RETURN);
    INIT_DIK(RIGHT);
    INIT_DIK(RMENU);
    INIT_DIK(RSHIFT);
    INIT_DIK(RWIN);
    INIT_DIK(S);
    INIT_DIK(SCROLL);
    INIT_DIK(SEMICOLON);
    INIT_DIK(SLASH);
    INIT_DIK(SLEEP);
    INIT_DIK(SPACE);
    INIT_DIK(STOP);
    INIT_DIK(SUBTRACT);
    INIT_DIK(SYSRQ);
    INIT_DIK(T);
    INIT_DIK(TAB);
    INIT_DIK(U);
    INIT_DIK(UNDERLINE);
    INIT_DIK(UNLABELED);
    INIT_DIK(UP);
    INIT_DIK(V);
    INIT_DIK(VOLUMEDOWN);
    INIT_DIK(VOLUMEUP);
    INIT_DIK(W);
    INIT_DIK(WAKE);
    INIT_DIK(WEBBACK);
    INIT_DIK(WEBFAVORITES);
    INIT_DIK(WEBFORWARD);
    INIT_DIK(WEBHOME);
    INIT_DIK(WEBREFRESH);
    INIT_DIK(WEBSEARCH);
    INIT_DIK(WEBSTOP);
    INIT_DIK(X);
    INIT_DIK(Y);
    INIT_DIK(YEN);
    INIT_DIK(Z);

    for (i = 0; i < 32; i++) {
        sprintf(dikStrings[KEY_CODE_BUTTON1 + i], "BUTTON%d", i + 1);
    }

    strcpy(dikStrings[KEY_CODE_JOYLEFT],  "JOYLEFT");
    strcpy(dikStrings[KEY_CODE_JOYRIGHT], "JOYRIGHT");
    strcpy(dikStrings[KEY_CODE_JOYUP],    "JOYUP");
    strcpy(dikStrings[KEY_CODE_JOYDOWN],  "JOYDOWN");
}

char* dik2str(int dikKey) 
{
    if (dikKey < 0 || dikKey >= KBD_TABLE_LEN) {
        return "";
    }
    return dikStrings[dikKey];
}

int str2dik(char* dikString) 
{
    int i;
    for (i = 0; i < KBD_TABLE_LEN; i++) {
        if (0 == strcmp(dikString, dikStrings[i])) {
            return i;
        }
    }
    return 0;
}

// initKbdTable initializes the keyboard table with default keys
static void initKbdTable()
{
    memset (kbdTable, 0, sizeof(kbdTable));

    kbdTable[DIK_0          ] = EK_0;
    kbdTable[DIK_1          ] = EK_1;
    kbdTable[DIK_2          ] = EK_2;
    kbdTable[DIK_3          ] = EK_3;
    kbdTable[DIK_4          ] = EK_4;
    kbdTable[DIK_5          ] = EK_5;
    kbdTable[DIK_6          ] = EK_6;
    kbdTable[DIK_7          ] = EK_7;
    kbdTable[DIK_8          ] = EK_8;
    kbdTable[DIK_9          ] = EK_9;
    
    kbdTable[DIK_MINUS      ] = EK_NEG;
    kbdTable[DIK_EQUALS     ] = EK_CIRCFLX;
    kbdTable[DIK_BACKSLASH  ] = EK_BKSLASH;
    kbdTable[DIK_LBRACKET   ] = EK_AT;
    kbdTable[DIK_RBRACKET   ] = EK_LBRACK;
    kbdTable[DIK_SEMICOLON  ] = EK_SEMICOL;
    kbdTable[DIK_APOSTROPHE ] = EK_COLON;
    kbdTable[DIK_GRAVE      ] = EK_RBRACK;
    kbdTable[DIK_COMMA      ] = EK_COMMA;
    kbdTable[DIK_PERIOD     ] = EK_PERIOD;
    kbdTable[DIK_SLASH      ] = EK_DIV;
    kbdTable[DIK_RCONTROL   ] = EK_UNDSCRE;
    
    kbdTable[DIK_A          ] = EK_A;
    kbdTable[DIK_B          ] = EK_B;
    kbdTable[DIK_C          ] = EK_C;
    kbdTable[DIK_D          ] = EK_D;
    kbdTable[DIK_E          ] = EK_E;
    kbdTable[DIK_F          ] = EK_F;
    kbdTable[DIK_G          ] = EK_G;
    kbdTable[DIK_H          ] = EK_H;
    kbdTable[DIK_I          ] = EK_I;
    kbdTable[DIK_J          ] = EK_J;
    kbdTable[DIK_K          ] = EK_K;
    kbdTable[DIK_L          ] = EK_L;
    kbdTable[DIK_M          ] = EK_M;
    kbdTable[DIK_N          ] = EK_N;
    kbdTable[DIK_O          ] = EK_O;
    kbdTable[DIK_P          ] = EK_P;
    kbdTable[DIK_Q          ] = EK_Q;
    kbdTable[DIK_R          ] = EK_R;
    kbdTable[DIK_S          ] = EK_S;
    kbdTable[DIK_T          ] = EK_T;
    kbdTable[DIK_U          ] = EK_U;
    kbdTable[DIK_V          ] = EK_V;
    kbdTable[DIK_W          ] = EK_W;
    kbdTable[DIK_X          ] = EK_X;
    kbdTable[DIK_Y          ] = EK_Y;
    kbdTable[DIK_Z          ] = EK_Z;

    kbdTable[DIK_F1         ] = EK_F1;
    kbdTable[DIK_F2         ] = EK_F2;
    kbdTable[DIK_F3         ] = EK_F3;
    kbdTable[DIK_F4         ] = EK_F4;
    kbdTable[DIK_F5         ] = EK_F5;
    kbdTable[DIK_ESCAPE     ] = EK_ESC;
    kbdTable[DIK_TAB        ] = EK_TAB;
    kbdTable[DIK_PRIOR      ] = EK_STOP;
    kbdTable[DIK_BACK       ] = EK_BKSPACE;
    kbdTable[DIK_END        ] = EK_SELECT;
    kbdTable[DIK_RETURN     ] = EK_RETURN;
    kbdTable[DIK_SPACE      ] = EK_SPACE;
    kbdTable[DIK_HOME       ] = EK_CLS;
    kbdTable[DIK_INSERT     ] = EK_INS;
    kbdTable[DIK_DELETE     ] = EK_DEL;
    kbdTable[DIK_LEFT       ] = EK_LEFT;
    kbdTable[DIK_UP         ] = EK_UP;
    kbdTable[DIK_RIGHT      ] = EK_RIGHT;
    kbdTable[DIK_DOWN       ] = EK_DOWN;

    kbdTable[DIK_MULTIPLY   ] = EK_NUMMUL;
    kbdTable[DIK_ADD        ] = EK_NUMADD;
    kbdTable[DIK_DIVIDE     ] = EK_NUMDIV;
    kbdTable[DIK_SUBTRACT   ] = EK_NUMSUB;
    kbdTable[DIK_DECIMAL    ] = EK_NUMPER;
    kbdTable[DIK_NEXT       ] = EK_NUMCOM;
    kbdTable[DIK_NUMPAD0    ] = EK_NUM0;
    kbdTable[DIK_NUMPAD1    ] = EK_NUM1;
    kbdTable[DIK_NUMPAD2    ] = EK_NUM2;
    kbdTable[DIK_NUMPAD3    ] = EK_NUM3;
    kbdTable[DIK_NUMPAD4    ] = EK_NUM4;
    kbdTable[DIK_NUMPAD5    ] = EK_NUM5;
    kbdTable[DIK_NUMPAD6    ] = EK_NUM6;
    kbdTable[DIK_NUMPAD7    ] = EK_NUM7;
    kbdTable[DIK_NUMPAD8    ] = EK_NUM8;
    kbdTable[DIK_NUMPAD9    ] = EK_NUM9;

    kbdTable[DIK_LWIN       ] = EK_TORIKE;
    kbdTable[DIK_RWIN       ] = EK_JIKKOU;
    kbdTable[DIK_LSHIFT     ] = EK_LSHIFT;
    kbdTable[DIK_RSHIFT     ] = EK_RSHIFT;
    kbdTable[DIK_LCONTROL   ] = EK_CTRL;
    kbdTable[DIK_LMENU      ] = EK_GRAPH;
    kbdTable[DIK_RMENU      ] = EK_CODE;
    kbdTable[DIK_CAPITAL    ] = EK_CAPS;
    kbdTable[DIK_NUMPADENTER] = EK_PAUSE;
    kbdTable[DIK_SYSRQ      ] = EK_PRINT;

    keyboardSaveConfig(DefaultConfigName);
}





#define MAX_JOYSTICKS 8

static LPDIRECTINPUT        dinput;
static int                  dinputVersion;
static LPDIRECTINPUTDEVICE  kbdDevice = NULL;
static LPDIRECTINPUTDEVICE2 kbdDevice2 = NULL;
static HWND                 dinputWindow;
static int                  kbdModifiers;
struct JoyInfo {
    LPDIRECTINPUTDEVICE  diDevice;
    LPDIRECTINPUTDEVICE2 diDevice2;
    char                 name[128];
    int                  numButtons;
    int                  buttonA;
    int                  buttonB;
    int                  state;  
};
static struct JoyInfo joyInfo[MAX_JOYSTICKS];

static int joyCount;



#define STRUCTSIZE(x) ((dinputVersion == 0x0300) ? sizeof(x##_DX3) : sizeof(x))


static BOOL CALLBACK enumKeyboards(LPCDIDEVICEINSTANCE devInst, LPVOID ref)
{
    DIDEVCAPS kbdCaps;
    HRESULT rv;

    if (kbdDevice != NULL) {
        return DIENUM_CONTINUE;
    }

    rv = IDirectInput_CreateDevice(dinput, &devInst->guidInstance, &kbdDevice, NULL);
    if (rv != DI_OK) {
        return DIENUM_CONTINUE;
    }

    IDirectInputDevice_QueryInterface(kbdDevice, &IID_IDirectInputDevice2, (void **)&kbdDevice2);

    kbdCaps.dwSize = STRUCTSIZE(DIDEVCAPS);
    rv = IDirectInputDevice_GetCapabilities(kbdDevice, &kbdCaps);
    if (rv == DI_OK) {
        rv = IDirectInputDevice_SetDataFormat(kbdDevice, &c_dfDIKeyboard);
        if (rv == DI_OK) {
            rv = IDirectInputDevice_SetCooperativeLevel(kbdDevice, dinputWindow,
                DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
            if (rv != DI_OK) {
                if (kbdDevice2 != NULL) {
                    IDirectInputDevice_Release(kbdDevice2);
                }
                IDirectInputDevice_Release(kbdDevice);
                kbdDevice = NULL;
                kbdDevice2 = NULL;
            }
        }
    }

    return DIENUM_CONTINUE;
}

static BOOL CALLBACK enumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, void* pContext)
{
    DIPROPRANGE diprg;
    HRESULT rv;

    diprg.diph.dwSize       = sizeof(DIPROPRANGE);
    diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diprg.diph.dwHow        = DIPH_BYOFFSET;
    diprg.diph.dwObj        = pdidoi->dwOfs;
    diprg.lMin              = -100;
    diprg.lMax              = +100;
    
    rv = IDirectInputDevice_SetProperty(joyInfo[joyCount].diDevice, DIPROP_RANGE, &diprg.diph);
    
    if (rv != DI_OK) {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

static BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext)
{
    DIDEVCAPS diDevCaps;
    HRESULT rv;

    strcpy(joyInfo[joyCount].name, pdidInstance->tszInstanceName);

    rv = IDirectInput_CreateDevice(dinput, &pdidInstance->guidInstance, &joyInfo[joyCount].diDevice, NULL);
    if (rv != DI_OK) {
        return DIENUM_CONTINUE;
    }
  
    joyInfo[joyCount].diDevice2 = NULL;
    rv = IDirectInputDevice_QueryInterface(joyInfo[joyCount].diDevice, &IID_IDirectInputDevice2, (void **)&joyInfo[joyCount].diDevice2);

	rv = IDirectInputDevice_SetDataFormat(joyInfo[joyCount].diDevice, &c_dfDIJoystick);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }
    
    rv = IDirectInputDevice_SetCooperativeLevel(joyInfo[joyCount].diDevice, dinputWindow, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }

	rv = IDirectInputDevice_EnumObjects(joyInfo[joyCount].diDevice, enumAxesCallback, (void*)dinputWindow, DIDFT_AXIS);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }

    diDevCaps.dwSize = sizeof(diDevCaps);
    rv = IDirectInputDevice_GetCapabilities(joyInfo[joyCount].diDevice, &diDevCaps);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }
    joyInfo[joyCount].numButtons = diDevCaps.dwButtons;

    if (++joyCount == MAX_JOYSTICKS) {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

int inputReset(HWND hwnd)
{
    DIPROPDWORD dipdw = { { sizeof(DIPROPDWORD), sizeof(DIPROPHEADER), 0, DIPH_DEVICE }, 256 };
    HRESULT rv   = 234;
    joyCount     = 0;
    kbdModifiers = 0;

    dinputWindow = hwnd;
    dinputVersion = DIRECTINPUT_VERSION;
	rv = DirectInputCreate(GetModuleHandle(NULL), dinputVersion, &dinput, NULL);
    if (rv != DI_OK) {
        dinputVersion = 0x0300;
    	rv = DirectInputCreate(GetModuleHandle(NULL), dinputVersion, &dinput, NULL);
        if (rv != DI_OK) {
            printf("Failed to initialize DirectInput\n");
            return 0;
        }
    }

	rv = IDirectInput_EnumDevices(dinput, DIDEVTYPE_KEYBOARD, enumKeyboards, 0, DIEDFL_ATTACHEDONLY);
    if (rv != DI_OK) {
        IDirectInput_Release(dinput);
        printf("Failed to find DirectInput device\n");
        return 0;
    }

    if (kbdDevice == NULL) {
        printf("Failed to create DirectInput device\n");
        return 0;
    }

	rv = IDirectInputDevice_SetProperty(kbdDevice, DIPROP_BUFFERSIZE,&dipdw.diph);

    rv = IDirectInput_EnumDevices(dinput, DIDEVTYPE_JOYSTICK, enumJoysticksCallback, 0, DIEDFL_ATTACHEDONLY);

    return 1;
}

void inputDestroy(void)
{
    if (kbdDevice) {
        IDirectInputDevice_Release(kbdDevice);
        kbdDevice = NULL;
    }
    
    if (kbdDevice2) {
        IDirectInputDevice_Release(kbdDevice2);
        kbdDevice2 = NULL;
    }

    while (--joyCount >= 0) {
        if (joyInfo[joyCount].diDevice) {
    	    IDirectInputDevice_Unacquire(joyInfo[joyCount].diDevice);
            IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        }
        joyInfo[joyCount].diDevice = NULL;
        if (joyInfo[joyCount].diDevice2) {
            IDirectInputDevice_Release(joyInfo[joyCount].diDevice2);
            joyInfo[joyCount].diDevice2 = NULL;
        }
    }

    if (dinput) {
        IDirectInput_Release(dinput);
    }

    dinput = NULL;
}

static int joystickUpdateState(int index,  DWORD* buttonMask) {
    DIJOYSTATE js;
    HRESULT rv;
    int state = 0;
    DWORD bMask = 0;
    int i;

    *buttonMask = 0;
    if (index >= joyCount) {
        return 0;
    }

    if (joyInfo[index].diDevice2) {
        IDirectInputDevice2_Poll(joyInfo[index].diDevice2);
    }

    rv = IDirectInputDevice_GetDeviceState(joyInfo[index].diDevice, sizeof(DIJOYSTATE), &js);
    if (rv == DIERR_INPUTLOST || rv == DIERR_NOTACQUIRED) {
    	rv = IDirectInputDevice_Acquire(joyInfo[index].diDevice);
    }

    if (rv != DI_OK) {
        return 0;
    }

    if (js.lX < -50) state |= 0x04; 
    if (js.lX >  50) state |= 0x08;
    if (js.lY < -50) state |= 0x01; 
    if (js.lY >  50) state |= 0x02; 
    if (js.rgbButtons[joyInfo[index].buttonA]) state |= 0x10;
    if (js.rgbButtons[joyInfo[index].buttonB]) state |= 0x20;

    for (i = 0; i < joyInfo[index].numButtons; i++) {
        if (js.rgbButtons[i]) bMask |= 1 << i;
    }

    *buttonMask = bMask;

    return state;
}

int archJoystickGetCount() {
    return joyCount;
}

char* archJoystickGetName(int index) {
    return joyInfo[index].name;
}


int joystickGetState(int index) {
    return joyInfo[index].state;
}

int joystickNumButtons(int index) {
    return joyInfo[index].numButtons;
}

void joystickSetButtons(int index, int buttonA, int buttonB)
{
    joyInfo[index].buttonA = buttonA;
    joyInfo[index].buttonB = buttonB;
}

static void keyboardHanldeKeypress(int code, int pressed) {
    int wasPressed = keyStatus[code];
    int keyCode = kbdTable[code];
    int isEditing = editEnabled && selectedKey != 0;
    keyStatus[code] = pressed;

    if (pressed == wasPressed || (keyCode == 0 && !isEditing)) {
        return;
    }

    if (pressed) {
        if (isEditing) {
            int i;
            for (i = 0; i < KBD_TABLE_LEN; i++) {
                if (kbdTable[i] == selectedKey) {
                    kbdTable[i] = 0;
                }
            }

            kbdTable[code] = selectedKey;
            selectedKey    = 0;
            selectedDikKey = 0;

            keyboardKeyUp(keyCode);
        }
        else {
            keyboardKeyDown(keyCode);
        }
    }
    else {
        keyboardKeyUp(keyCode);
    }
}

static DWORD buttonState = 0;
static int hasFocus = 0;

void keyboardSetFocus(int handle, int focus) 
{
    if (focus) {
        hasFocus |= handle;
    }
    else {
        hasFocus &= ~handle;
    }
}

static void keyboardResetKbd() 
{
    int i;
    for (i = 0; i < KBD_TABLE_LEN; i++) {
        kbdModifiers = 0;
        keyboardHanldeKeypress(kbdTable[i], 0);
    }
    keyboardReset();
    buttonState = 0;
}

DWORD joystickGetButtonState()
{
    return buttonState;
}

void joystickUpdate()
{
    int i;
    DWORD joyMask = 0;
    DWORD mask;

    buttonState = 0;

    for (i = 0; i < joyCount; i++) {
        DWORD mask;
        joyInfo[i].state = joystickUpdateState(i, &mask);
        joyMask |= joyInfo[i].state;
        buttonState |= mask;
    }

    mask = buttonState;
    for (i = 0; i < 32; i++) {
        keyboardHanldeKeypress(KEY_CODE_BUTTON1 + i, mask & 1);
        mask >>= 1;
    }
    
    mask = joyMask;
    for (i = 0; i < 4; i++) {
        keyboardHanldeKeypress(KEY_CODE_JOYUP + i, mask & 1);
        mask >>= 1;
    }
}

void keyboardEnable(int enable)
{
    int i;
    for (i = 0; i < KBD_TABLE_LEN; i++) {
        keyboardHanldeKeypress(kbdTable[i], 0);
    }

    if (kbdDevice != NULL) {
        IDirectInputDevice_Unacquire(kbdDevice);
        if (enable) {
            IDirectInputDevice_Acquire(kbdDevice);
        }
    }
}

int keyboardGetModifiers()
{
    return kbdModifiers;
}

void keyboardUpdate() 
{ 
    if (!hasFocus) {
        keyboardResetKbd();
        return;
    }

    if (kbdDevice != NULL) {
        char buffer[256]; 
        HRESULT  rv; 
        
        if (kbdDevice2) {
			IDirectInputDevice2_Poll(kbdDevice2);
        }

        rv = IDirectInputDevice_GetDeviceState(kbdDevice, sizeof(buffer), (LPVOID)&buffer); 
        if (rv == DIERR_INPUTLOST || rv == DIERR_NOTACQUIRED) {
            rv = IDirectInputDevice_Acquire(kbdDevice);
            if (rv == DI_OK) {
                rv = IDirectInputDevice_GetDeviceState(kbdDevice, sizeof(buffer), (LPVOID)&buffer); 
            }
        }

        if (rv >= 0) { 
            kbdModifiers = ((buffer[DIK_LSHIFT]   & 0x80) >> 7) | ((buffer[DIK_RSHIFT]   & 0x80) >> 6) | 
                           ((buffer[DIK_LCONTROL] & 0x80) >> 5) | ((buffer[DIK_RCONTROL] & 0x80) >> 4) | 
                           ((buffer[DIK_LALT]     & 0x80) >> 3) | ((buffer[DIK_RALT]     & 0x80) >> 2) | 
                           ((buffer[DIK_LWIN]     & 0x80) >> 1) | ((buffer[DIK_RWIN]     & 0x80) >> 0);

            if (kbdModifiers &&
                  ((buffer[DIK_F6]  | buffer[DIK_F7]  | buffer[DIK_F8]  | buffer[DIK_F9]  | 
                    buffer[DIK_F10] | buffer[DIK_F11] | buffer[DIK_F12]) >> 7))
            {
                int i;
                for (i = 0; i < 256; i++) {
                    keyboardHanldeKeypress(i, 0);
                }
            }
            else {
                int i;
                for (i = 0; i < 256; i++) {
                    keyboardHanldeKeypress(i, buffer[i] >> 7);
                }
            }

            return;
        }
    }

    kbdModifiers = (GetAsyncKeyState(VK_LMENU)   > 1UL ? KBD_LALT     : 0) |
                   (GetAsyncKeyState(VK_MENU)    > 1UL ? KBD_LALT     : 0) |
                   (GetAsyncKeyState(VK_SHIFT)   > 1UL ? KBD_LSHIFT   : 0) |
                   (GetAsyncKeyState(VK_CONTROL) > 1UL ? KBD_LCTRL    : 0) |
                   (GetAsyncKeyState(VK_LWIN)    > 1UL ? KBD_LWIN     : 0) |
                   (GetAsyncKeyState(VK_RWIN)    > 1UL ? KBD_RWIN     : 0);
} 

char** keyboardGetConfigs()
{
    static char* keyboardNames[256];
    char         fileName[MAX_PATH];
    static char  keyboardArray[256][64];
	HANDLE       handle;
	WIN32_FIND_DATA wfd;
    int index = 0;
    BOOL cont = TRUE;

    sprintf(fileName, "%s/*.config", keyboardConfigDir);

    handle = FindFirstFile(fileName, &wfd);

    if (handle == INVALID_HANDLE_VALUE) {
        keyboardNames[0] = NULL;
        return keyboardNames;
    }

    while (cont) {
		DWORD fa = GetFileAttributes(wfd.cFileName);
        if (fa & FILE_ATTRIBUTE_DIRECTORY) {
            char buffer[128];
            int length = strlen(wfd.cFileName) - 7;
            strcpy(buffer, wfd.cFileName);
            buffer[length] = 0;
            strcpy(keyboardArray[index], buffer);
            keyboardNames[index] = keyboardArray[index];
            index++;
        }
        cont = FindNextFile(handle, &wfd);
    }

	FindClose(handle);
    
    keyboardNames[index] = NULL;

    return keyboardNames;
}

int keyboardLoadConfig(char* configName)
{
    char fileName[MAX_PATH];
    FILE* file;
    int i;

    keyboardResetKbd();

    if (configName[0] == 0) {
        sprintf(fileName, "%s/%s.config", keyboardConfigDir, DefaultConfigName);
    }
    else {
        sprintf(fileName, "%s/%s.config", keyboardConfigDir, configName);
    }

    file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);

    sprintf(currentConfigFile, *configName ? configName : DefaultConfigName);

    for (i = 0; i < EK_KEYCOUNT; i++) {
        const char* keyCode = keyboardKeyCodeToString(i);
        if (*keyCode != 0) {
            char dikName[32];
            int dikKey;

            GetPrivateProfileString("Keymapping", keyCode, "", dikName, sizeof(dikName), fileName);
            dikKey = str2dik(dikName);
            if (dikKey > 0) {
                int j;
                for (j = 0; j < KBD_TABLE_LEN; j++) {
                    if (kbdTable[j] == i) {
                        kbdTable[j] = 0;
                    }
                }
                kbdTable[dikKey] = i;
            }
        }
    }

    return 1;
}

void keyboardSaveConfig(char* configName)
{
    char fileName[MAX_PATH];
    int i;
    
    if (configName[0] == 0) {
        return;
    }

    sprintf(fileName, "%s/%s.config", keyboardConfigDir, configName);
    
    for (i = 0; i < EK_KEYCOUNT; i++) {
        const char* keyCode = keyboardKeyCodeToString(i);
        const char* dikName = "";
        int j;
        for (j = 0; j < KBD_TABLE_LEN; j++) {
            if (kbdTable[j] == i) {
                dikName = dik2str(j);
                break;
            }
        }
        WritePrivateProfileString("Keymapping", keyCode, dikName, fileName);
    }
    
    memcpy(kbdTableBackup, kbdTable, sizeof(kbdTableBackup));
    
    sprintf(currentConfigFile, configName);
}

void keyboardSetDirectory(char* directory)
{
    strcpy(keyboardConfigDir, directory);
}

char* keyboardGetCurrentConfig()
{
    return currentConfigFile;
}

int keyboardIsCurrentConfigDefault() 
{
    return strcmp(currentConfigFile, DefaultConfigName) == 0;
}

void inputInit()
{
    char fileName[MAX_PATH];
    FILE* file;

    initDikStr();
    initKbdTable();

    keyboardReset();
    
    sprintf(fileName, "%s/%s.config", keyboardConfigDir, DefaultConfigName);
    file = fopen(fileName, "r");
    if (file == NULL) {
        keyboardSaveConfig(DefaultConfigName);
        return;
    }
    sprintf(currentConfigFile, DefaultConfigName);
    fclose(file);
}

char* archGetSelectedKey()
{
    if (selectedKey != 0) {
        char* keyCode = (char*)keyboardKeyCodeToString(selectedKey);
        if (keyCode != NULL) {
            return keyCode;
        }
    }
    return "";
}

char* archGetMappedKey()
{
    if (selectedKey != 0) {
        return dik2str(selectedDikKey);
    }
    return "";
}

void keyboardSetSelectedKey(int msxKeyCode)
{
    int i;
    selectedKey = msxKeyCode;
    selectedDikKey = 0;

    for (i = 0; i < KBD_TABLE_LEN; i++) {
        if (kbdTable[i] == selectedKey) {
            selectedDikKey = i;
        }
    }
}

int archKeyboardIsKeySelected(int msxKeyCode)
{
    return editEnabled && (msxKeyCode == selectedKey);
}

int archKeyboardIsKeyConfigured(int msxKeyCode)
{
    int i;

    if (!editEnabled) {
        return 1;
    }

    for (i = 0; i < KBD_TABLE_LEN; i++) {
        if (kbdTable[i] == msxKeyCode) {
            return 1;
        }
    }
    return 0;
}

void keybardEnableEdit(int enable)
{
    editEnabled = enable;
    selectedKey = 0;
    selectedDikKey = 0;
}

void keyboardStartConfig() 
{
    memcpy(kbdTableBackup, kbdTable, sizeof(kbdTableBackup));
}

void keyboardCancelConfig() 
{
    memcpy(kbdTable, kbdTableBackup, sizeof(kbdTableBackup));
}

int  keyboardConfigIsModified()
{
    return memcmp(kbdTable, kbdTableBackup, sizeof(kbdTableBackup));
}
