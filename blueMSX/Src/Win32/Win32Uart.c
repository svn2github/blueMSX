/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Uart.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-27 01:11:12 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vikl, Tomas Karlsson
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
#include <windows.h>
#include <tchar.h>
#include "Win32Uart.h"
#include "ArchUart.h"


static HANDLE hComPort = NULL; 
static BOOL bUartInitialized = FALSE;
static BYTE ucReceiveBuf = 0;

static BOOL uartReady(void)
{
    COMMTIMEOUTS timeouts;
    DCB    dcbConfig;

    if (bUartInitialized)
        return TRUE;

    hComPort = CreateFile(TEXT("COM1:"), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (GetCommState(hComPort,&dcbConfig) == 0)
        return FALSE;
		
    SetupComm(hComPort, 32, 32);
		
    // We got a port! now lets config it the way we want
    dcbConfig.BaudRate = CBR_9600;          // Current baud 
    dcbConfig.fBinary = TRUE;               // Binary mode; no EOF check 
    dcbConfig.fParity = TRUE;               // Enable parity checking 
    dcbConfig.fOutxCtsFlow = FALSE;         // No CTS output flow control 
    dcbConfig.fOutxDsrFlow = FALSE;         // No DSR output flow control 
    dcbConfig.fDtrControl = DTR_CONTROL_ENABLE; // DTR flow control type 
    dcbConfig.fDsrSensitivity = TRUE;      // DSR sensitivity 
    dcbConfig.fTXContinueOnXoff = FALSE;     // XOFF continues Tx 
    dcbConfig.fOutX = FALSE;                // No XON/XOFF out flow control 
    dcbConfig.fInX = FALSE;                 // No XON/XOFF in flow control 
    dcbConfig.fErrorChar = FALSE;           // Disable error replacement 
    dcbConfig.fNull = FALSE;                // Disable null stripping 
    dcbConfig.fRtsControl = RTS_CONTROL_DISABLE; //Disable RTS flow control
    dcbConfig.fAbortOnError = FALSE;        // Do not abort reads/writes on error
    dcbConfig.ByteSize = 8;                 // Number of bits/byte, 4-8 
    dcbConfig.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space 
    dcbConfig.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2 
  
    if (!SetCommState (hComPort, &dcbConfig))
        return FALSE;

    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts( hComPort, &timeouts );

    bUartInitialized = TRUE;

    return TRUE;
}

static void uartClose(void)
{
    CloseHandle (hComPort);
    bUartInitialized = FALSE;
}

static void uartTransmit(BYTE value)
{
    DWORD dwWritten = 0;

    if (!WriteFile(hComPort, &value, 1, &dwWritten, 0))
        uartClose();
}

static int uartReceiveStatus(void)
{
	DWORD dwBytesRead;
	BYTE value;	

	ReadFile(hComPort, &value, 1, &dwBytesRead, 0);
	if (dwBytesRead != 0) {
		ucReceiveBuf = value;
		return TRUE;
	}
	else
		return FALSE;
}

BYTE archUartReceive(void)
{
    if (uartReady())
        return ucReceiveBuf;
    else
        return 0;
}

int archUartReceiveStatus(void)
{
    if (uartReady())
        return uartReceiveStatus();
    else
        return FALSE;
}

void archUartTransmit(BYTE value)
{
    if (uartReady())
        uartTransmit(value);
}

int archUartReady(void)
{
    return uartReady();
}
