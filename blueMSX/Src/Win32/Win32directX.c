/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32directX.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:32:02 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Laurent Halter
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
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <ddraw.h>
#include <mmsystem.h>
#include <prsht.h>
 
#include "Win32directx.h"
#include "VideoRender.h"


static LPDIRECTDRAW         lpDD = NULL;            // DirectDraw object
static LPDIRECTDRAW         lpDDinit = NULL;
static LPDIRECTDRAWSURFACE  lpDDSPrimary = NULL;    // DirectDraw primary surface
static LPDIRECTDRAWSURFACE  lpDDSBack = NULL;       // DirectDraw back surface
static LPDIRECTDRAWSURFACE  lpDDSTemp1 = NULL;       // DirectDraw temp surface
static LPDIRECTDRAWSURFACE  lpDDSTemp2 = NULL;       // DirectDraw temp surface
static LPDIRECTDRAWSURFACE  lpDDSDraw = NULL;       // DirectDraw temp surface
static LPDIRECTDRAWCLIPPER  lpClipper = NULL;       // clipper for primary
static HWND    hwndThis;
static int     MyDevice;
static int     sysMemBuffering = 0;
static char    MyDeviceName[128];
static RECT    MyDeviceRect;
static int     isFullscreen = 0;

#ifndef DDBLTFAST_DONOTWAIT
#define DDBLTFAST_DONOTWAIT 0x00000020
#endif

BOOL CALLBACK OneMonitorCallback(HMONITOR hMonitor, HDC hdc, LPRECT prc, LPARAM lParam) {
    HMONITOR *phMonitorFound = (HMONITOR *)lParam;

    if (*phMonitorFound == 0) {
        *phMonitorFound = hMonitor;
    }
    else {
        *phMonitorFound = (HMONITOR) INVALID_HANDLE_VALUE;
    }

    return TRUE;
}

HMONITOR OneMonitorFromWindow(HWND hwnd) {
    HMONITOR hMonitor = NULL;
    RECT rc;

    if (hwnd) {
        GetClientRect(hwnd, &rc);
        ClientToScreen(hwnd, (LPPOINT)&rc);
        ClientToScreen(hwnd, (LPPOINT)&rc+1);
    }
    else {
        SetRectEmpty(&rc);
    }

    EnumDisplayMonitors(NULL, &rc, OneMonitorCallback, (LPARAM)&hMonitor);
    return hMonitor;
}

int DirectDrawDeviceFromWindow(HWND hwnd, LPSTR szDevice, RECT *prc) {
    HMONITOR hMonitor;

    if (GetSystemMetrics(SM_CMONITORS) <= 1) {
        if (prc) SetRect(prc,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
        if (szDevice) lstrcpy(szDevice, "DISPLAY");
        return -1;
    }

    hMonitor = OneMonitorFromWindow(hwnd);

    if (hMonitor == NULL || hMonitor == INVALID_HANDLE_VALUE) {
        if (prc) SetRectEmpty(prc);
        if (szDevice) *szDevice=0;
        return 0;
    }
    else {
        if (prc != NULL || szDevice != NULL) {
            MONITORINFOEX mi;
            mi.cbSize = sizeof(mi);
            GetMonitorInfo(hMonitor, (LPMONITORINFO)&mi);
            if (prc) *prc = mi.rcMonitor;
            if (szDevice) lstrcpy(szDevice, mi.szDevice);
        }
        return (int)hMonitor;
    }
}

typedef struct {
    LPSTR   szDevice;
    GUID*   lpGUID;
    GUID    GUID;
    BOOL    fFound;
}   FindDeviceData;

BOOL CALLBACK FindDeviceCallback(GUID* lpGUID, LPSTR szName, LPSTR szDevice, LPVOID lParam) {
    FindDeviceData *p = (FindDeviceData*)lParam;

    if (lstrcmpi(p->szDevice, szDevice) == 0) {
    if (lpGUID) {
        p->GUID = *lpGUID;
        p->lpGUID = &p->GUID;
    }
    else {
        p->lpGUID = NULL;
    }
    p->fFound = TRUE;
    return FALSE;
    }
    return TRUE;
}

IDirectDraw * DirectDrawCreateFromDevice(LPSTR szDevice) {
    IDirectDraw*    pdd = NULL;
    FindDeviceData  find;

    find.szDevice = szDevice;
    find.fFound   = FALSE;
    DirectDrawEnumerate(FindDeviceCallback, (LPVOID)&find);

    if (find.fFound) {
        DirectDrawCreate(find.lpGUID, &pdd, NULL);
    }

    return pdd;
}

IDirectDraw* DirectDrawCreateFromWindow(HWND hwnd) {
    IDirectDraw *pdd = NULL;
    char szDevice[80];
    OSVERSIONINFO osw;
    int supportsMonitors;

    osw.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osw)) {
        return NULL;
    }

    supportsMonitors = osw.dwMajorVersion > 4 ||
                       (osw.dwMajorVersion == 4 && osw.dwMinorVersion > 0);

    if (supportsMonitors) {
        if (GetSystemMetrics(SM_CMONITORS) > 1) {
            if (DirectDrawDeviceFromWindow(hwnd, szDevice, NULL)) {
                pdd = DirectDrawCreateFromDevice(szDevice);
            }
        }
    }

    if (pdd == NULL) {
        DirectDrawCreate(NULL, &pdd, NULL);
    }

    return pdd;
}

void DirectXExitFullscreenMode()
{
    if( lpDDSPrimary != NULL ) {
        IDirectDrawSurface_Release(lpDDSPrimary);
        lpDDSPrimary = NULL;
    }
    if( lpDDSTemp1 != NULL ) {
        IDirectDrawSurface_Release(lpDDSTemp1);
        lpDDSTemp1 = NULL;
    }
    if( lpDDSTemp2 != NULL ) {
        IDirectDrawSurface_Release(lpDDSTemp2);
        lpDDSTemp2 = NULL;
    }
    if ( lpDDSDraw != NULL ) {
        IDirectDrawSurface_Release(lpDDSDraw);
        lpDDSDraw = NULL;
    }
    if( lpDD != NULL ) {
        IDirectDraw_Release(lpDD);
        lpDD = NULL;
    }
    if( lpDDinit != NULL ) {
        IDirectDraw_SetCooperativeLevel(lpDDinit, NULL, DDSCL_NORMAL);
        IDirectDraw_RestoreDisplayMode(lpDDinit);
        IDirectDraw_Release(lpDDinit);
        lpDDinit = NULL;
    }

    isFullscreen = 0;
}


int DirectXEnterFullscreenMode(HWND hwnd, int width, int height, int depth, int useVideoBackBuffer, int useSysMemBuffering)
{
    DDSURFACEDESC   ddsd;
    DDSCAPS     ddscaps;
    HRESULT     ddrval;

    DirectXExitFullscreenMode();

    sysMemBuffering = useSysMemBuffering;
    isFullscreen = 1;

    ddrval = DirectDrawCreate( NULL, &lpDDinit, NULL );
    if( ddrval != DD_OK ) {
        return DXE_DIRECTDRAWCREATE;
    }

    ddrval = IDirectDraw_SetCooperativeLevel(lpDDinit, NULL, DDSCL_NORMAL);
    ddrval = IDirectDraw_QueryInterface(lpDDinit, (GUID *)&IID_IDirectDraw, (LPVOID *)&lpDD);

    // Get exclusive mode
    ddrval = IDirectDraw_SetCooperativeLevel(lpDD, GetParent(hwnd) ? GetParent(hwnd) : hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if( ddrval != DD_OK ) {
        return DXE_SETCOOPERATIVELEVEL;
    }

    ddrval = IDirectDraw_SetDisplayMode(lpDD, width, height, depth);
    if( ddrval != DD_OK ) {
        return DXE_SETDISPLAYMODE;
    }

    // Create the primary surface with 1 back buffer
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK ) {
        return DXE_CREATESURFACE;
    }

    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = IDirectDrawSurface_GetAttachedSurface(lpDDSPrimary, &ddscaps, &lpDDSBack);
    if( ddrval != DD_OK ) {
        lpDDSBack = NULL;
    }

    ddrval = IDirectDraw_CreateClipper( lpDD, 0, &lpClipper, NULL );
    if( ddrval != DD_OK ) {
        return DXE_CREATECLIPPER;
    }

    ddrval = IDirectDrawClipper_SetHWnd(lpClipper, 0, hwnd);
    if( ddrval != DD_OK ) {
        return DXE_SETHWND;
    }

    ddrval = IDirectDrawSurface_SetClipper(lpDDSPrimary, lpClipper);
    if( ddrval != DD_OK ) {
        return DXE_SETCLIPPER;
    }

    memset(&ddsd, 0, sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof(DDSURFACEDESC);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | (useVideoBackBuffer ? DDSCAPS_VIDEOMEMORY : DDSCAPS_SYSTEMMEMORY);
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSTemp1, NULL);

    if (ddrval != DD_OK) {
        memset(&ddsd, 0, sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
        ddsd.dwWidth = width;
        ddsd.dwHeight = height;
        ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSTemp1, NULL);
        if( ddrval != DD_OK ) {
            return DXE_CREATESURFACE;
        }
    }

    if (useSysMemBuffering) {
        memset(&ddsd, 0, sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
        ddsd.dwWidth = width;
        ddsd.dwHeight = height;
        ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSTemp2, NULL);
        if( ddrval != DD_OK ) {
            return DXE_CREATESURFACE;
        }
    }

    return DXE_OK;
}



BOOL DirectXEnterWindowedMode(HWND hwnd, int width, int height, int useVideoBackBuffer, int useSysMemBuffering)
{
    DDSURFACEDESC   ddsd;
    HRESULT     ddrval;

    lpDDSBack = NULL;
    hwndThis = hwnd;
    sysMemBuffering = useSysMemBuffering;

    DirectXExitFullscreenMode();

    MyDevice = DirectDrawDeviceFromWindow(hwnd, MyDeviceName, &MyDeviceRect);

    lpDD = DirectDrawCreateFromWindow(hwnd);
    if( lpDD == NULL ) {
        return DXE_CREATEFROMWINDOW;
    }

    ddrval = IDirectDraw_SetCooperativeLevel(lpDD, NULL, DDSCL_NORMAL);
    if( ddrval != DD_OK ) {
        return DXE_SETCOOPERATIVELEVEL;
    }

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    ddrval = IDirectDraw_CreateSurface(lpDD, &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK ) {
        return DXE_CREATESURFACE;
    }

    ddrval = IDirectDraw_CreateClipper( lpDD, 0, &lpClipper, NULL );
    if( ddrval != DD_OK ) {
        return DXE_CREATECLIPPER;
    }

    ddrval = IDirectDrawClipper_SetHWnd(lpClipper, 0, hwnd);
    if( ddrval != DD_OK ) {
        return DXE_SETHWND;
    }

    ddrval = IDirectDrawSurface_SetClipper(lpDDSPrimary, lpClipper );
    if( ddrval != DD_OK ) {
        return DXE_SETCLIPPER;
    }

    memset(&ddsd, 0, sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof(DDSURFACEDESC);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | (useVideoBackBuffer ? DDSCAPS_VIDEOMEMORY : DDSCAPS_SYSTEMMEMORY);
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSTemp1, NULL);

    if (ddrval != DD_OK) {
        memset(&ddsd, 0, sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
        ddsd.dwWidth = width;
        ddsd.dwHeight = height;
        ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSTemp1, NULL);
        if( ddrval != DD_OK ) {
            return DXE_CREATESURFACE;
        }
    }

    if (useSysMemBuffering) {
        memset(&ddsd, 0, sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
        ddsd.dwWidth = width;
        ddsd.dwHeight = height;
        ddrval = IDirectDraw2_CreateSurface(lpDD, &ddsd, &lpDDSTemp2, NULL);
        if( ddrval != DD_OK ) {
            return DXE_CREATESURFACE;
        }
    }

    return DXE_OK;
}

void DirectXSetGDISurface() {
    if (isFullscreen) {
        IDirectDraw_FlipToGDISurface(lpDD);
    }
}


int DirectXUpdateWindowedMode(HWND hwnd, int width, int height, int useVideoBackBuffer, int useSysMemBuffering) {
    if (!isFullscreen) {
        if (MyDevice != DirectDrawDeviceFromWindow(hwnd, NULL, NULL)) {
            return DirectXEnterWindowedMode(hwnd, width, height, useVideoBackBuffer, useSysMemBuffering);
        }
    }
    return DXE_OK;
}

void DirectXUpdateSurface(Video* pVideo, void* srcBits, int srcWidth, int srcHeight, int* srcDoubleWidth, 
                          int noFlip, int dstPitchY, int dstOffset, int zoom, 
                          int horizontalStretch, int verticalStretch, int evenOddPage, int interlace) 
{
    DDSURFACEDESC ddsd;
    LPDIRECTDRAWSURFACE surface = NULL;
    LPDIRECTDRAWSURFACE  lpDDSTemp;
    HRESULT     ddrval;
    POINT pt = {0, 0};
    RECT destRect = {0, 0, zoom * srcWidth, zoom * srcHeight};
    RECT rcRect = {0, 0, zoom * srcWidth, zoom * srcHeight};

    if (lpDDSPrimary == NULL) {
        return;
    }

    ClientToScreen( hwndThis, &pt );

    lpDDSTemp = sysMemBuffering ? lpDDSTemp2 : lpDDSTemp1;

    if (surface == NULL && lpDDSTemp != NULL) {
        ddsd.dwSize = sizeof(ddsd);
        do {
            ddrval = IDirectDrawSurface_Lock(lpDDSTemp, NULL, &ddsd, DDLOCK_WAIT, NULL);
            if (ddrval == DDERR_SURFACELOST && IDirectDrawSurface_Restore(lpDDSTemp) != DD_OK) {
                break;
            }
        } while (ddrval == DDERR_SURFACELOST);
        if (ddrval == DD_OK) {
            surface = lpDDSTemp;
        }
    }

    if (surface == NULL) {
        ddsd.dwSize = sizeof(ddsd);
        do {
            ddrval = IDirectDrawSurface_Lock(lpDDSPrimary, NULL, &ddsd, 0, NULL);
            if (ddrval == DDERR_SURFACELOST && IDirectDrawSurface_Restore(lpDDSPrimary) != DD_OK) {
                break;
            }
        } while (ddrval == DDERR_SURFACELOST);

        if (ddrval == DD_OK) {
            surface = lpDDSPrimary;
        }
    }

    if (surface == NULL) {
        return;
    }

    videoRender(pVideo, ddsd.ddpfPixelFormat.dwRGBBitCount, zoom, evenOddPage, interlace,
                srcBits, srcWidth, srcHeight, srcDoubleWidth, ddsd.lpSurface, sizeof(DWORD) * srcWidth, ddsd.lPitch);

    if (IDirectDrawSurface_Unlock(surface, NULL) == DDERR_SURFACELOST) {
        IDirectDrawSurface_Restore(surface);
        IDirectDrawSurface_Unlock(surface, NULL);
    }

    if (sysMemBuffering) {
        do {
            ddrval = IDirectDrawSurface_BltFast(lpDDSTemp1, 0, 0, surface, NULL, DDBLTFAST_DONOTWAIT);

            if (ddrval == DDERR_SURFACELOST) {
                ddrval = IDirectDrawSurface_Restore(lpDDSTemp1);
            }
        } while (ddrval == DDERR_WASSTILLDRAWING);
        surface = lpDDSTemp1;
    }

    destRect.bottom += dstPitchY;
    if (destRect.right  < 64) destRect.right = 64;
    if (destRect.bottom < 64)  destRect.bottom = 64;

    if (horizontalStretch) {
        rcRect.left   += 47 * zoom / 2;
        rcRect.right  -= 46 * zoom / 2;
    }
    
    if (verticalStretch) {
        rcRect.top    += 7 * zoom;
        rcRect.bottom -= 7 * zoom;
    }

    pt.x -= MyDeviceRect.left;
    pt.y -= MyDeviceRect.top;
    OffsetRect(&destRect, pt.x, pt.y);

    destRect.top += dstOffset;
    destRect.bottom += dstOffset;
    
    rcRect.top -= dstPitchY;

    if (lpDDSBack != NULL && !noFlip) {
	    DDSCAPS ddscaps = { DDSCAPS_BACKBUFFER };
        do {
            ddrval = IDirectDrawSurface_Blt(lpDDSBack, &destRect, surface, &rcRect, DDBLT_ASYNC, NULL);
            if (ddrval == DDERR_SURFACELOST) {
                ddrval = IDirectDrawSurface_Restore(lpDDSBack);
            }
        } while (ddrval == DDERR_WASSTILLDRAWING);
        do {
            ddrval = IDirectDrawSurface_Flip(lpDDSPrimary, NULL, 0 );
            if (ddrval == DDERR_SURFACELOST) {
                IDirectDrawSurface_Restore(lpDDSPrimary);
                break;
            }
        } while (ddrval == DDERR_WASSTILLDRAWING);
    	IDirectDrawSurface_GetAttachedSurface(lpDDSPrimary, &ddscaps, &lpDDSBack);
    }
    else {
        ddrval = IDirectDrawSurface_Blt(lpDDSPrimary, &destRect, surface, &rcRect, DDBLT_ASYNC, NULL);

        if (ddrval == DDERR_SURFACELOST) {
            ddrval = IDirectDrawSurface_Restore(lpDDSPrimary);
        }
    }    
}
