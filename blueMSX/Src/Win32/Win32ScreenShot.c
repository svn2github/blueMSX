/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32ScreenShot.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2005-01-30 09:09:43 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Laurent Halter, Daniel Vik
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
#include "Win32ScreenShot.h"
#include "Language.h"
#include "FileHistory.h"
#include <stdio.h>
#include <direct.h>

static char baseDir[512];
static char basePrefix[512];

typedef struct {
	DWORD Size;
    DWORD Reserved1;
    DWORD OffRaster;
    DWORD OffBits;
    DWORD Width;
    DWORD Height;
	WORD  Planes;
    WORD  BitCount;
	DWORD Compression;
    DWORD SizeImage;
    DWORD XPelsPerMeter;
    DWORD YPelsPerMeter;
    DWORD ClrUsed;
    DWORD ClrImportant;
} BMPHeader;

static HRESULT SaveBitmap(char *strFileName, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
{
    HRESULT             hr = E_FAIL;
    HANDLE              hf;         // file handle
    BITMAPFILEHEADER    hdr;        // bitmap file-header
    PBITMAPINFOHEADER   pbih;       // bitmap info-header
    LPBYTE              lpBits;     // memorypointer
    DWORD               dwTotal;    // total count of bytes
    DWORD               cb;         // incremental count of bytes
    BYTE                *hp;        // byte pointer
    DWORD               dwTmp;      // temp-variable


    if( pbi == NULL ){
        return E_FAIL;
    }

    pbih    = ( PBITMAPINFOHEADER ) pbi;
    lpBits  = ( LPBYTE ) GlobalAlloc( GMEM_FIXED, pbih->biSizeImage );

    if( !lpBits ){
        return E_FAIL;
    }


    //
    // Retrieve the colortable ( RGBQUAD-array ) and the bits
    // ( array of palette indices ) from the DIB.
    //
    if( !GetDIBits( hDC, hBMP, 0, ( WORD )pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS ) ){
        return E_FAIL;
    }


    //
    // Create the .BMP file.
    //
    hf = CreateFile( strFileName, GENERIC_READ|GENERIC_WRITE, ( DWORD ) 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, ( HANDLE ) NULL );

    if( hf == INVALID_HANDLE_VALUE ){
        return E_FAIL;
    }

    hdr.bfType = 0x4D42;    // 0x42 = "B", 0x4D = "M"


    //
    // Compute the size of the entire file
    //
    hdr.bfSize = ( DWORD )( sizeof( BITMAPFILEHEADER ) + pbih->biSize + pbih->biClrUsed * sizeof( RGBQUAD ) + pbih->biSizeImage );
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;

    //
    // Compute the offset to the array of color indices
    //
    hdr.bfOffBits = ( DWORD ) sizeof( BITMAPFILEHEADER ) + pbih->biSize + pbih->biClrUsed * sizeof( RGBQUAD );


    //
    // Copy the BITMAPFILEHEADER into the .BMP file
    //
    if( !WriteFile( hf, ( LPVOID ) &hdr, sizeof( BITMAPFILEHEADER ), ( LPDWORD ) &dwTmp, NULL ) ){
        return E_FAIL;
    }


    //
    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file
    //
    if( !WriteFile( hf, ( LPVOID ) pbih, sizeof( BITMAPINFOHEADER ) + pbih->biClrUsed * sizeof( RGBQUAD ), ( LPDWORD ) &dwTmp, ( NULL ) ) ){
        return E_FAIL;
    }


    //
    // Copy the array of color indices into the .BMP file
    //
    dwTotal = cb = pbih->biSizeImage;
    hp      = lpBits;

    if( !WriteFile( hf, ( LPSTR ) hp, ( int ) cb, ( LPDWORD ) &dwTmp, NULL ) ){
        return E_FAIL;
    }


    //
    // Now close the .BMP file
    //
    if( !CloseHandle( hf ) ){
        return E_FAIL;
    }


    //
    // Free the memory reserved
    //
    GlobalFree( ( HGLOBAL ) lpBits );


    return S_OK;
}

static PBITMAPINFO CreateBitmapInfoStructure(HBITMAP hBmp)
{
    BITMAP      bmp;
    PBITMAPINFO pbmi;
    WORD        cClrBits;


    //
    // Get the width, height and the colordepth of the image
    //
    if( !GetObject( hBmp, sizeof( BITMAP ), (LPSTR)&bmp ) ){
        return NULL;
    }


    //
    // Convert the color format to a count of bits
    //
    cClrBits = 24;


    //
    // Allocate memory for the BITMAPINFO-structure. This structure
    // contains a BITMAPINFOHEADER-structure and an array of RGBQUAD
    // datastructures.
    //
    if( cClrBits < 24 )
        pbmi = ( PBITMAPINFO ) LocalAlloc( LPTR, sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD ) * ( 1 << cClrBits ) );
    else
        pbmi = ( PBITMAPINFO ) LocalAlloc( LPTR, sizeof( BITMAPINFOHEADER ) );

    //
    // Initialize the fields in the BITMAPINFO-structure.
    //
    pbmi->bmiHeader.biSize      = sizeof( BITMAPINFOHEADER );
    pbmi->bmiHeader.biWidth     = bmp.bmWidth;
    pbmi->bmiHeader.biHeight    = bmp.bmHeight;
    pbmi->bmiHeader.biPlanes    = bmp.bmPlanes;
    pbmi->bmiHeader.biBitCount  = cClrBits;//bmp.bmBitsPixel;

    if( cClrBits < 24 )
        pbmi->bmiHeader.biClrUsed = ( 1 << cClrBits );

    //
    // If the bitmap isn't compressed, set the BI_RGB flag
    //
    pbmi->bmiHeader.biCompression   = BI_RGB;

    //
    // Compute the number of bytes in the array of color indices
    // and store the result in biSizeImage.
    //
    pbmi->bmiHeader.biSizeImage     = ( pbmi->bmiHeader.biWidth + 7 ) / 8 * pbmi->bmiHeader.biHeight * cClrBits;

    //
    // Set biClrImportant to 0 to indicate that all of the device
    // colors are important.
    //
    pbmi->bmiHeader.biClrImportant  = 0;

    //
    // And finally return the info-structure.
    //
    return pbmi;
}

void ScreenShot(Properties* properties, HWND hwnd, int width, int height, int xOffset, int yOffset)
{
    HDC hdcScreen;
    HDC hdcCompatible;
    HBITMAP  hbmScreen;
    PBITMAPINFO pbi;
    HBITMAP hBitmapOrig;

    hdcScreen=GetDC(hwnd);
    if (hdcScreen==NULL)
    {
        MessageBox(NULL,"No hDC found!",langErrorTitle(),MB_OK);
        return;
    }
    hdcCompatible = CreateCompatibleDC(hdcScreen);
    if (hdcCompatible==NULL)
    {
        MessageBox(NULL,"Error creating Compatible DC",langErrorTitle(),MB_OK);
        return;
    }

    hbmScreen = CreateCompatibleBitmap(hdcScreen, width, height);
    if (hbmScreen==NULL)
    {
        MessageBox(NULL,"Error creating Compatible Bitmap",langErrorTitle(),MB_OK);
        return;
    }

    hBitmapOrig = (HBITMAP)SelectObject(hdcCompatible, hbmScreen);
    BitBlt(hdcCompatible, 0, 0, width, height, hdcScreen, xOffset, yOffset, SRCCOPY);

    pbi = CreateBitmapInfoStructure(hbmScreen);
    if (SaveBitmap(generateSaveFilename(properties, baseDir, basePrefix, ".bmp", 4), pbi, hbmScreen, hdcCompatible)==E_FAIL) {
        MessageBox(NULL,"Error saving bitmap!",langErrorTitle(),MB_OK);
    }
    if (pbi != NULL) {
        LocalFree(pbi);
    }

    DeleteObject(SelectObject(hdcCompatible, hBitmapOrig));
    DeleteDC(hdcCompatible);
    ReleaseDC(hwnd, hdcScreen);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void* ScreenShot2(void* src, int srcPitch, int width, int height, int* bitmapSize)
{
    DWORD* srcPtr = (DWORD*)src;
    BMPHeader hdr;
    int w;
    int h;

    int size = 2 + sizeof(hdr) + 3 * width * height;
    BYTE* bitmap = (BYTE*)malloc(size);
    BYTE* dstPtr = bitmap;

    *bitmapSize = size;

	hdr.BitCount      = 24;
	hdr.Size          = width * height * hdr.BitCount / 8 + 0x36;
	hdr.Reserved1     = 0;
	hdr.OffRaster     = 0x36;
	hdr.OffBits       = 0x28;
	hdr.Width         = width;
	hdr.Height        = height;
	hdr.Planes        = 1;
	hdr.Compression   = 0;
	hdr.SizeImage     = width * height * hdr.BitCount / 8;
	hdr.XPelsPerMeter = 0;
	hdr.YPelsPerMeter = 0;
	hdr.ClrUsed       = 0;
    hdr.ClrImportant  = 0;

    *dstPtr++ = 'B';
    *dstPtr++ = 'M';

    memcpy(dstPtr, &hdr, sizeof(hdr));
    dstPtr += sizeof(hdr);

    for (h = 0; h < height; h++) {
        for (w = 0; w < width; w++) {
            *dstPtr++ = (BYTE)(srcPtr[w] >>  0);
            *dstPtr++ = (BYTE)(srcPtr[w] >>  8);
            *dstPtr++ = (BYTE)(srcPtr[w] >> 16);
        }
        srcPtr += srcPitch;
    }

    return bitmap;
}

void ScreenShot3(Properties* properties, void* src, int srcPitch, int width, int height)
{
    int bitmapSize;
    void* bitmap = ScreenShot2(src, srcPitch, width, height, &bitmapSize);
	FILE* file = fopen(generateSaveFilename(properties, baseDir, basePrefix, ".bmp", 4), "wb");
    if (file != NULL) {
    	fwrite(bitmap, 1, bitmapSize, file);
        fclose(file);
    }
    free(bitmap);
}

void screenshotSetDirectory(char* directory, char* prefix) 
{
    strcpy(baseDir, directory);
    strcpy(basePrefix, prefix);
}


HBITMAP BitmapFromData(void* bmp) {
    char*       bitmap = (char*)bmp;
    BMPHeader*  hdr    = (BMPHeader*)(bitmap + 2);
    char*       data   = (char*)(hdr + 1);
    BITMAPINFO* bmi;
    HDC         hdc;
    HBITMAP     hbm;

    if (bitmap[0] != 'B' || bitmap[1] != 'M') {
        return INVALID_HANDLE_VALUE;
    }

    bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
    bmi->bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
    bmi->bmiHeader.biWidth        = hdr->Width;
    bmi->bmiHeader.biHeight       = hdr->Height;
    bmi->bmiHeader.biPlanes       = hdr->Planes;
    bmi->bmiHeader.biBitCount     = hdr->BitCount;
    bmi->bmiHeader.biCompression  = BI_RGB; 
    bmi->bmiHeader.biSizeImage    = hdr->SizeImage;
    bmi->bmiHeader.biClrImportant = 0; 

    hdc = GetDC(NULL);
    hbm = CreateCompatibleBitmap(hdc, hdr->Width, hdr->Height);

    SetDIBits(hdc, hbm, 0, hdr->Height, data, bmi, DIB_RGB_COLORS);

    DeleteDC(hdc);

    return hbm;
}