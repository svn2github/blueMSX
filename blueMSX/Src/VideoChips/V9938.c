/*****************************************************************************
**
** This command engine may be used in any MSX emulator. It does not matter 
** under which conditions that the emulator gets distributed. Be it open-
** source or closed-source. Be it commercially or free-of-charge.
** 
** This command engine may not be used in any other kind of softwares.
** Using this command engine is at own risk. The author is not responsible 
** nor liable for any damages that may occur intentionally or unintentionally 
** from it's usage.
**
******************************************************************************
*/
#include "V9938.h"
#include <string.h>
#include "VDP.h"
#include "Board.h"
#include "SaveState.h"

/*************************************************************
** Different compilers inline C functions differently.
**************************************************************
*/
#ifdef __GNUC__
#define INLINE inline
#else
#define INLINE static
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define VDPSTATUS_TR 0x80
#define VDPSTATUS_BO 0x10
#define VDPSTATUS_CE 0x01

/*************************************************************
** Other useful defines
**************************************************************
*/
#define VDP_VRMP5(X, Y) (VRAM + ((Y & 1023) << 7) + (((X & 255) >> 1) & vramMask))
#define VDP_VRMP6(X, Y) (VRAM + ((Y & 1023) << 7) + (((X & 511) >> 2) & vramMask))
#define VDP_VRMP7(X, Y) (VRAM + ((Y &  511) << 7) + ((((X & 511) >> 2) + ((X & 2) << 15)) & vramMask))
#define VDP_VRMP8(X, Y) (VRAM + ((Y &  511) << 7) + ((((X & 255) >> 1) + ((X & 1) << 16)) & vramMask))

#define CM_ABRT  0x0
#define CM_NOOP1 0x1
#define CM_NOOP2 0x2
#define CM_NOOP3 0x3
#define CM_POINT 0x4
#define CM_PSET  0x5
#define CM_SRCH  0x6
#define CM_LINE  0x7
#define CM_LMMV  0x8
#define CM_LMMM  0x9
#define CM_LMCM  0xA
#define CM_LMMC  0xB
#define CM_HMMV  0xC
#define CM_HMMM  0xD
#define CM_YMMM  0xE
#define CM_HMMC  0xF

/*************************************************************
** Many VDP commands are executed in some kind of loop but
** essentially, there are only a few basic loop structures
** that are re-used. We define the loop structures that are
** re-used here so that they have to be entered only once
**************************************************************
*/
#define pre_loop \
    while (cnt > 0) {

/* Loop over DX, DY */
#define post__x_y(MX) \
        ADX += TX; \
		if (--ANX == 0 || (ADX & MX)) { \
            DY += TY; \
            ADX = DX; ANX = NX; \
            if ((--NY & 1023) == 0 || DY == -1) {\
                break; \
		    } \
        } \
        cnt-=delta; \
    }

#define post__xyy(MX) \
        ADX += TX; \
        if (ADX & MX) { \
			SY += TY; DY += TY; \
			ADX = DX; \
			if ((--NY & 1023) == 0 || SY == -1 || DY == -1) { \
				break; \
			} \
		} \
        cnt-=delta; \
	}

#define post_xxyy(MX) \
		ASX += TX; ADX += TX; \
		if (--ANX == 0 || ((ASX | ADX) & MX)) { \
			SY += TY; DY += TY; \
			ASX = SX; ADX = DX; ANX = NX; \
			if ((--NY & 1023) == 0 || SY == -1 || DY == -1) { \
				break; \
			} \
		} \
        cnt-=delta; \
	}


#define pre_loop2 \
    while (MMC.VdpOpsCnt > 0) {

#define post_xxyy2(MX) \
		MMC.ASX += MMC.TX; MMC.ADX += MMC.TX; \
		if (--MMC.ANX == 0 || ((MMC.ASX | MMC.ADX) & MX)) { \
			MMC.SY += MMC.TY; MMC.DY += MMC.TY; \
			MMC.ASX = MMC.SX; MMC.ADX = MMC.DX; MMC.ANX = MMC.NX; \
			if ((--MMC.NY & 1023) == 0 || MMC.SY == -1 || MMC.DY == -1) { \
				break; \
			} \
		} \
        MMC.VdpOpsCnt -= delta; \
	}

/*************************************************************
** VdpCmd State instance
**************************************************************
*/
typedef struct {
    int   SX;
    int   SY;
    int   DX;
    int   DY;
    int   NX;
    int   NY;
    int   ASX;
    int   ADX;
    int   ANX;
    UInt8 ARG;
    UInt8 CL;
    UInt8 LO;
    UInt8 CM;
    
    UInt8 status;
    UInt16 borderX;

    int   TX;
    int   TY;
    int   MX;
    int   VdpOpsCnt;
    UInt32 systemTime;
    int    screenMode;
    int    timingMode;
} VdpCmdState;

VdpCmdState MMC;
static UInt8* VRAM;
static int vramMask;

/*************************************************************
** Forward declarations
**************************************************************
*/
static UInt8 *getVramPointer(UInt8 M, int X, int Y);

static UInt8 getPixel(UInt8 SM, int SX, int SY);
static UInt8 getPixel5(int SX, int SY);
static UInt8 getPixel6(int SX, int SY);
static UInt8 getPixel7(int SX, int SY);
static UInt8 getPixel8(int SX, int SY);

static void setPixel(UInt8 SM, int DX, int DY, UInt8 CL, UInt8 OP);
static void setPixel5(int DX, int DY, UInt8 CL, UInt8 OP);
static void setPixel6(int DX, int DY, UInt8 CL, UInt8 OP);
static void setPixel7(int DX, int DY, UInt8 CL, UInt8 OP);
static void setPixel8(int DX, int DY, UInt8 CL, UInt8 OP);

static void setPixelLow(UInt8 *P, UInt8 CL, UInt8 M, UInt8 OP);

static void SrchEngine(void);
static void LineEngine(void);
static void LmmvEngine(void);
static void LmmmEngine(void);
static void LmcmEngine(void);
static void LmmcEngine(void);
static void HmmvEngine(void);
static void HmmmEngine(void);
static void YmmmEngine(void);
static void HmmcEngine(void);


/*************************************************************
** Constants
**************************************************************
*/
static UInt8 Mask[4] = { 0x0f, 0x03, 0x0f, 0xff };
static int   PPB[4]  = { 2, 4, 2, 1 };
static int   PPL[4]  = { 256, 512, 512, 256 };


static int srch_timing[8] = { 92,  125, 92,  92  };
static int line_timing[8] = { 120, 147, 120, 132 };
static int hmmv_timing[8] = { 49,  65,  49,  62  };
static int lmmv_timing[8] = { 98,  137, 98,  124 };
static int ymmm_timing[8] = { 65,  125, 65,  68  };
static int hmmm_timing[8] = { 92,  136, 92,  97  };
static int lmmm_timing[8] = { 129, 197, 129, 132 };

/*************************************************************
** getVramPointer
**
** Description:
**      Calculate addr of a pixel in vram
**************************************************************
*/
INLINE UInt8 *getVramPointer(UInt8 M,int X,int Y)
{
    switch(M) {
    case 0: 
        return VDP_VRMP5(X,Y);
    case 1: 
        return VDP_VRMP6(X,Y);
    case 2: 
        return VDP_VRMP7(X,Y);
    case 3: 
        return VDP_VRMP8(X,Y);
    }

    return(VRAM);
}


/*************************************************************
** getPixel5
**
** Description:
**      Get a pixel on screen 5
**************************************************************
*/
INLINE UInt8 getPixel5(int SX, int SY)
{
    return (*VDP_VRMP5(SX, SY) >> (((~SX)&1)<<2))&15;
}

/*************************************************************
** getPixel6
**
** Description:
**      Get a pixel on screen 6
**************************************************************
*/
INLINE UInt8 getPixel6(int SX, int SY)
{
    return (*VDP_VRMP6(SX, SY) >>(((~SX)&3)<<1))&3;
}

/*************************************************************
** getPixel7
**
**    Get a pixel on screen 7
**************************************************************
*/
INLINE UInt8 getPixel7(int SX, int SY)
{
    return (*VDP_VRMP7(SX, SY) >>(((~SX)&1)<<2))&15;
}

/*************************************************************
** getPixel8
**
** Description:
**      Get a pixel on screen 8
**************************************************************
*/
INLINE UInt8 getPixel8(int SX, int SY)
{
    return *VDP_VRMP8(SX, SY);
}

/*************************************************************
** getPixel
**
**    Get a pixel on a screen
**************************************************************
*/
INLINE UInt8 getPixel(UInt8 SM, int SX, int SY)
{
    switch(SM) {
    case 0: 
        return getPixel5(SX,SY);
    case 1: 
        return getPixel6(SX,SY);
    case 2: 
        return getPixel7(SX,SY);
    case 3: 
        return getPixel8(SX,SY);
    }

    return(0);
}

/*************************************************************
** setPixelLow
**
** Description:
**      Low level function to set a pixel on a screen
**************************************************************
*/
INLINE void setPixelLow(UInt8 *P, UInt8 CL, UInt8 M, UInt8 OP)
{
    switch (OP) {
    case 0: 
        *P = (*P & M) | CL; 
        break;
    case 1: 
        *P = *P & (CL | M); 
        break;
    case 2: 
        *P |= CL; 
        break;
    case 3: 
        *P ^= CL; 
        break;
    case 4: 
        *P = (*P & M) | ~(CL | M); 
        break;
    case 8: 
        if (CL) *P = (*P & M) | CL; 
        break;
    case 9: 
        if (CL) *P = *P & (CL | M); 
        break;
    case 10: 
        if (CL) {
            *P |= CL; 
        }
        break;
    case 11: 
        if (CL) {
            *P ^= CL; 
        }
        break;
    case 12: 
        if (CL) {
            *P = (*P & M) | ~(CL|M); 
        }
        break;
    }
}

/*************************************************************
** setPixel5
**
** Description:
**      Set a pixel on screen 5
**************************************************************
*/
INLINE void setPixel5(int DX, int DY, UInt8 CL, UInt8 OP)
{
    UInt8 SH = ((~DX)&1)<<2;

    setPixelLow(VDP_VRMP5(DX, DY), CL << SH, ~(15<<SH), OP);
}
 
/*************************************************************
** setPixel6
**
**    Set a pixel on screen 6
**************************************************************
*/
INLINE void setPixel6(int DX, int DY, UInt8 CL, UInt8 OP)
{
    UInt8 SH = ((~DX)&3)<<1;

    setPixelLow(VDP_VRMP6(DX, DY), CL << SH, ~(3<<SH), OP);
}

/*************************************************************
** setPixel7
**
** Description:
**      Set a pixel on screen 7
**************************************************************
*/
INLINE void setPixel7(int DX, int DY, UInt8 CL, UInt8 OP)
{
    UInt8 SH = ((~DX)&1)<<2;

    setPixelLow(VDP_VRMP7(DX, DY), CL << SH, ~(15<<SH), OP);
}

/*************************************************************
** setPixel8
**
**    Set a pixel on screen 8
**************************************************************
*/
INLINE void setPixel8(int DX, int DY, UInt8 CL, UInt8 OP)
{
    setPixelLow(VDP_VRMP8(DX, DY), CL, 0, OP);
}

/*************************************************************
** setPixel
**
** Description:
**      Set a pixel on a screen
**************************************************************
*/
INLINE void setPixel(UInt8 SM, int DX, int DY, UInt8 CL, UInt8 OP)
{
    switch (SM) {
    case 0: setPixel5(DX, DY, CL, OP); break;
    case 1: setPixel6(DX, DY, CL, OP); break;
    case 2: setPixel7(DX, DY, CL, OP); break;
    case 3: setPixel8(DX, DY, CL, OP); break;
    }
}

/*************************************************************
** SrchEgine
**
** Description:
**      Search a dot
**************************************************************
*/
static void SrchEngine(void)
{
    int SX=MMC.SX;
    int SY=MMC.SY;
    int TX=MMC.TX;
    int ANX=MMC.ANX;
    UInt8 CL=MMC.CL & Mask[MMC.screenMode];
    int delta = srch_timing[MMC.timingMode];
    int cnt;

    cnt = MMC.VdpOpsCnt;

#define pre_srch \
    pre_loop \
    if ((
#define post_srch(MX) \
    ==CL) ^ANX) { \
        MMC.status|=VDPSTATUS_BO; /* Border detected */ \
        break; \
    } \
    if ((SX+=TX) & MX) { \
        MMC.status&=~VDPSTATUS_BO; /* Border not detected */ \
        break; \
    } \
    cnt-=delta; \
} 

    switch (MMC.screenMode) {
    case 0: 
        pre_srch getPixel5(SX, SY) post_srch(256)
        break;
    case 1: 
        pre_srch getPixel6(SX, SY) post_srch(512)
        break;
    case 2: 
        pre_srch getPixel7(SX, SY) post_srch(512)
        break;
    case 3: 
        pre_srch getPixel8(SX, SY) post_srch(256)
        break;
    }

    if ((MMC.VdpOpsCnt=cnt)>0) {
        /* Command execution done */
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CM=0;
        /* Update SX in VDP registers */
        MMC.borderX = 0xfe00 | SX;
    }
    else {
        MMC.SX=SX;
    }
}

/*************************************************************
** LineEgine
**
** Description:
**      Draw a line
**************************************************************
*/
static void LineEngine(void)
{
    int DX=MMC.DX;
    int DY=MMC.DY;
    int TX=MMC.TX;
    int TY=MMC.TY;
    int NX=MMC.NX;
    int NY=MMC.NY;
    int ASX=MMC.ASX;
    int ADX=MMC.ADX;
    UInt8 CL=MMC.CL & Mask[MMC.screenMode];
    UInt8 LO=MMC.LO;
    int delta = line_timing[MMC.timingMode];
    int cnt;

    cnt = MMC.VdpOpsCnt;

#define post_linexmaj(MX) \
    DX+=TX; \
    if ((ASX-=NY)<0) { \
    ASX+=NX; \
    DY+=TY; \
    } \
    ASX&=1023; /* Mask to 10 bits range */ \
    if (ADX++==NX || (DX&MX)) \
    break; \
        cnt-=delta; \
}
#define post_lineymaj(MX) \
    DY+=TY; \
    if ((ASX-=NY)<0) { \
    ASX+=NX; \
    DX+=TX; \
    } \
    ASX&=1023; /* Mask to 10 bits range */ \
    if (ADX++==NX || (DX&MX)) \
    break; \
        cnt-=delta; \
    }

    if ((MMC.ARG&0x01)==0) {
        /* X-Axis is major direction */
        switch (MMC.screenMode) {
        case 0: 
            pre_loop setPixel5(DX, DY, CL, LO); post_linexmaj(256)
            break;
        case 1: 
            pre_loop setPixel6(DX, DY, CL, LO); post_linexmaj(512)
            break;
        case 2: 
            pre_loop setPixel7(DX, DY, CL, LO); post_linexmaj(512)
            break;
        case 3: 
            pre_loop setPixel8(DX, DY, CL, LO); post_linexmaj(256)
            break;
        }
    }
    else {
        /* Y-Axis is major direction */
        switch (MMC.screenMode) {
        case 0: 
            pre_loop setPixel5(DX, DY, CL, LO); post_lineymaj(256)
            break;
        case 1: 
            pre_loop setPixel6(DX, DY, CL, LO); post_lineymaj(512)
            break;
        case 2: 
            pre_loop setPixel7(DX, DY, CL, LO); post_lineymaj(512)
            break;
        case 3: 
            pre_loop setPixel8(DX, DY, CL, LO); post_lineymaj(256)
            break;
        }
    }

    if ((MMC.VdpOpsCnt=cnt)>0) {
        /* Command execution done */
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CM=0;
        MMC.DY=DY & 0x03ff;
    }
    else {
        MMC.DX=DX;
        MMC.DY=DY;
        MMC.ASX=ASX;
        MMC.ADX=ADX;
    }
}

/*************************************************************
** LmmvEngine
**
** Description:
**      VDP -> Vram
**************************************************************
*/
static void LmmvEngine(void)
{
    int DX=MMC.DX;
    int DY=MMC.DY;
    int TX=MMC.TX;
    int TY=MMC.TY;
    int NX=MMC.NX;
    int NY=MMC.NY;
    int ADX=MMC.ADX;
    int ANX=MMC.ANX;
    UInt8 CL=MMC.CL & Mask[MMC.screenMode];
    UInt8 LO=MMC.LO;
    int delta = lmmv_timing[MMC.timingMode];
    int cnt;

    cnt = MMC.VdpOpsCnt;

    switch (MMC.screenMode) {
    case 0: 
        pre_loop setPixel5(ADX, DY, CL, LO); post__x_y(256)
        break;
    case 1: 
        pre_loop setPixel6(ADX, DY, CL, LO); post__x_y(512)
        break;
    case 2: 
        pre_loop setPixel7(ADX, DY, CL, LO); post__x_y(512)
        break;
    case 3: 
        pre_loop setPixel8(ADX, DY, CL, LO); post__x_y(256)
        break;
    }

    if ((MMC.VdpOpsCnt=cnt)>0) {
        /* Command execution done */
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CM=0;
        if (!NY)
            DY+=TY;
        MMC.DY=DY & 0x03ff;
        MMC.NY=NY & 0x03ff;
    }
    else {
        MMC.DY=DY;
        MMC.NY=NY;
        MMC.ANX=ANX;
        MMC.ADX=ADX;
    }
}

/*************************************************************
** LmmmEngine
**
** Description:
**      Vram -> Vram
**************************************************************
*/
static void LmmmEngine(void)
{
    int SX=MMC.SX;
    int SY=MMC.SY;
    int DX=MMC.DX;
    int DY=MMC.DY;
    int TX=MMC.TX;
    int TY=MMC.TY;
    int NX=MMC.NX;
    int NY=MMC.NY;
    int ASX=MMC.ASX;
    int ADX=MMC.ADX;
    int ANX=MMC.ANX;
    UInt8 LO=MMC.LO;
    int delta = lmmm_timing[MMC.timingMode];
    int cnt;

    cnt = MMC.VdpOpsCnt;

    switch (MMC.screenMode) {
    case 0: 
        pre_loop setPixel5(ADX, DY, getPixel5(ASX, SY), LO); post_xxyy(256)
        break;
    case 1: 
        pre_loop setPixel6(ADX, DY, getPixel6(ASX, SY), LO); post_xxyy(512)
        break;
    case 2: 
        pre_loop setPixel7(ADX, DY, getPixel7(ASX, SY), LO); post_xxyy(512)
        break;
    case 3: 
        pre_loop setPixel8(ADX, DY, getPixel8(ASX, SY), LO); post_xxyy(256)
        break;
    }

    if ((MMC.VdpOpsCnt=cnt)>0) {
        /* Command execution done */
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CM=0;
        if (!NY) {
            SY+=TY;
            DY+=TY;
        }
        else {
            if (SY==-1) {
                DY+=TY;
            }
        }
        MMC.DY=DY & 0x03ff;
        MMC.SY=SY & 0x03ff;
        MMC.NY=NY & 0x03ff;
    }
    else {
        MMC.SY=SY;
        MMC.DY=DY;
        MMC.NY=NY;
        MMC.ANX=ANX;
        MMC.ASX=ASX;
        MMC.ADX=ADX;
    }
}

/*************************************************************
** LmcmEngine
**
** Description:
**      Vram -> CPU
**************************************************************
*/
static void LmcmEngine()
{
    if (!(MMC.status & VDPSTATUS_TR)) {
        MMC.CL = getPixel(MMC.screenMode, MMC.ASX, MMC.SY);
        MMC.status |= VDPSTATUS_TR;

        if (!--MMC.ANX || ((MMC.ASX+=MMC.TX)&MMC.MX)) {
            if (!(--MMC.NY & 1023) || (MMC.SY+=MMC.TY)==-1) {
                MMC.status &= ~VDPSTATUS_CE;
                MMC.CM = 0;
                if (!MMC.NY)
                    MMC.DY+=MMC.TY;
            }
            else {
                MMC.ASX=MMC.SX;
                MMC.ANX=MMC.NX;
            }
        }
    }
}

/*************************************************************
** LmmcEngine
**
** Description:
**      CPU -> Vram
**************************************************************
*/
static void LmmcEngine(void)
{
    if (!(MMC.status & VDPSTATUS_TR)) {
        UInt8 SM=MMC.screenMode;

        UInt8 CL=MMC.CL & Mask[SM];
        setPixel(SM, MMC.ADX, MMC.DY, CL, MMC.LO);
        MMC.status |= VDPSTATUS_TR;

        if (!--MMC.ANX || ((MMC.ADX+=MMC.TX)&MMC.MX)) {
            if (!(--MMC.NY&1023) || (MMC.DY+=MMC.TY)==-1) {
                MMC.status &= ~VDPSTATUS_CE;
                MMC.CM = 0;
                if (!MMC.NY)
                    MMC.DY+=MMC.TY;
            }
            else {
                MMC.ADX=MMC.DX;
                MMC.ANX=MMC.NX;
            }
        }
    }
}

/*************************************************************
** HmmvEngine
**
** Description:
**      VDP --> Vram
**************************************************************
*/
static void HmmvEngine(void)
{
    int DX=MMC.DX;
    int DY=MMC.DY;
    int TX=MMC.TX;
    int TY=MMC.TY;
    int NX=MMC.NX;
    int NY=MMC.NY;
    int ADX=MMC.ADX;
    int ANX=MMC.ANX;
    UInt8 CL=MMC.CL;
    int delta = hmmv_timing[MMC.timingMode];
    int cnt;

    cnt = MMC.VdpOpsCnt;

    switch (MMC.screenMode) {
    case 0: 
        pre_loop *VDP_VRMP5(ADX, DY) = CL; post__x_y(256)
        break;
    case 1: 
        pre_loop *VDP_VRMP6(ADX, DY) = CL; post__x_y(512)
        break;
    case 2: 
        pre_loop *VDP_VRMP7(ADX, DY) = CL; post__x_y(512)
        break;
    case 3: 
        pre_loop *VDP_VRMP8(ADX, DY) = CL; post__x_y(256)
        break;
    }

    if ((MMC.VdpOpsCnt=cnt)>0) {
        /* Command execution done */
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CM = 0;
        if (!NY) {
            DY+=TY;
        }
        MMC.DY=DY & 0x03ff;
        MMC.NY=NY & 0x03ff;
    }
    else {
        MMC.DY=DY;
        MMC.NY=NY;
        MMC.ANX=ANX;
        MMC.ADX=ADX;
    }
}

/*************************************************************
** HmmmEngine
**
** Description:
**      Vram -> Vram
**************************************************************
*/
static void HmmmEngine(void)
{
    int delta = hmmm_timing[MMC.timingMode];

    switch (MMC.screenMode) {
    case 0: 
        pre_loop2 *VDP_VRMP5(MMC.ADX, MMC.DY) = *VDP_VRMP5(MMC.ASX, MMC.SY); post_xxyy2(256)
        break;
    case 1: 
        pre_loop2 *VDP_VRMP6(MMC.ADX, MMC.DY) = *VDP_VRMP6(MMC.ASX, MMC.SY); post_xxyy2(512)
        break;
    case 2: 
        pre_loop2 *VDP_VRMP7(MMC.ADX, MMC.DY) = *VDP_VRMP7(MMC.ASX, MMC.SY); post_xxyy2(512)
        break;
    case 3: 
        pre_loop2 *VDP_VRMP8(MMC.ADX, MMC.DY) = *VDP_VRMP8(MMC.ASX, MMC.SY); post_xxyy2(256)
        break;
    }

    if (MMC.VdpOpsCnt > 0) { \
        /* Command execution done */
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CM = 0;
        if (!MMC.NY) {
            MMC.SY += MMC.TY;
            MMC.DY += MMC.TY;
        }
        else {
            if (MMC.SY == -1) {
                MMC.DY += MMC.TY;
            }
        }
    }
}

/*************************************************************
** YmmmEngine
**
** Description:
**      Vram -> Vram 
**************************************************************
*/
static void YmmmEngine(void)
{
    int SY=MMC.SY;
    int DX=MMC.DX;
    int DY=MMC.DY;
    int TX=MMC.TX;
    int TY=MMC.TY;
    int NY=MMC.NY;
    int ADX=MMC.ADX;
    int delta = ymmm_timing[MMC.timingMode];
    int cnt;

    cnt = MMC.VdpOpsCnt;

    switch (MMC.screenMode) {
    case 0: 
        pre_loop *VDP_VRMP5(ADX, DY) = *VDP_VRMP5(ADX, SY); post__xyy(256)
        break;
    case 1: 
        pre_loop *VDP_VRMP6(ADX, DY) = *VDP_VRMP6(ADX, SY); post__xyy(512)
        break;
    case 2: 
        pre_loop *VDP_VRMP7(ADX, DY) = *VDP_VRMP7(ADX, SY); post__xyy(512)
        break;
    case 3: 
        pre_loop *VDP_VRMP8(ADX, DY) = *VDP_VRMP8(ADX, SY); post__xyy(256)
        break;
    }

    if ((MMC.VdpOpsCnt=cnt)>0) {
        /* Command execution done */
        MMC.status &=~VDPSTATUS_CE;
        MMC.CM = 0;
        if (!NY) {
            SY+=TY;
            DY+=TY;
        }
        else {
            if (SY==-1) {
                DY+=TY;
            }
        }
        MMC.DY=DY & 0x03ff;
        MMC.SY=SY & 0x03ff;
        MMC.NY=NY & 0x03ff;
    }
    else {
        MMC.SY=SY;
        MMC.DY=DY;
        MMC.NY=NY;
        MMC.ADX=ADX;
    }
}

/*************************************************************
** HmmcEngine
**
** Description:
**      CPU -> Vram 
**************************************************************
*/
static void HmmcEngine(void)
{
    if (!(MMC.status & VDPSTATUS_TR)) {
        *getVramPointer(MMC.screenMode, MMC.ADX, MMC.DY)=MMC.CL;
        MMC.VdpOpsCnt-=hmmv_timing[MMC.timingMode];
        MMC.status |= VDPSTATUS_TR;

        if (!--MMC.ANX || ((MMC.ADX+=MMC.TX)&MMC.MX)) {
            if (!(--MMC.NY&1023) || (MMC.DY+=MMC.TY)==-1) {
                MMC.status &= ~VDPSTATUS_CE;
                MMC.CM = 0;
                if (!MMC.NY) {
                    MMC.DY+=MMC.TY;
                }
            }
            else {
                MMC.ADX=MMC.DX;
                MMC.ANX=MMC.NX;
            }
        }
    }
}


/*************************************************************
** vdpCmdInit
**
** Description:
**      Initializes the command engine.
**************************************************************
*/
void vdpCmdInit(int vramSize, UInt8* vramPtr, UInt32 systemTime)
{
    memset(&MMC, 0, sizeof(MMC));
    MMC.systemTime = systemTime;
    VRAM = vramPtr;
    vramMask = vramSize - 1;
}


/*************************************************************
** vdpCmdSetCommand
**
** Description:
**      Set VDP command to ececute
**************************************************************
*/
static void vdpCmdSetCommand(UInt32 systemTime)
{
    MMC.SX &= 0x1ff;
    MMC.SY &= 0x3ff;
    MMC.DX &= 0x1ff;
    MMC.DY &= 0x3ff;
    MMC.NX &= 0x3ff;
    MMC.NY &= 0x3ff;

    switch (MMC.CM) {
    case CM_ABRT:
        MMC.CM = 0;
        MMC.status &= ~VDPSTATUS_CE;
        return;

    case CM_NOOP1:
    case CM_NOOP2:
    case CM_NOOP3:
        MMC.CM = 0;
        return;

    case CM_POINT:
        MMC.CM = 0;
        MMC.status &= ~VDPSTATUS_CE;
        MMC.CL = getPixel(MMC.screenMode, MMC.SX, MMC.SY);
        return;

    case CM_PSET:
        MMC.CM = 0;
        MMC.status &= ~VDPSTATUS_CE;
        setPixel(MMC.screenMode, MMC.DX, MMC.DY, MMC.CL, MMC.LO);
        return;
    }

    MMC.MX  = PPL[MMC.screenMode]; 
    MMC.TY  = MMC.ARG & 0x08? -1 : 1;

    /* Argument depends on UInt8 or dot operation */
    if ((MMC.CM & 0x0C) == 0x0C) {
        MMC.TX = MMC.ARG & 0x04 ? -PPB[MMC.screenMode] : PPB[MMC.screenMode];
        MMC.NX = MMC.NX/PPB[MMC.screenMode];
    }
    else {
        MMC.TX = MMC.ARG & 0x04 ? -1 : 1;
    }

    /* X loop variables are treated specially for LINE command */
    if (MMC.CM == CM_LINE) {
        MMC.ASX = (MMC.NX - 1) >> 1;
        MMC.ADX = 0;
    }
    else {
        MMC.ASX = MMC.SX;
        MMC.ADX = MMC.DX;
    }    

    /* NX loop variable is treated specially for SRCH command */
    if (MMC.CM == CM_SRCH)
        MMC.ANX=(MMC.ARG&0x02)!=0; /* Do we look for "==" or "!="? */
    else
        MMC.ANX = MMC.NX;

    /* Command execution started */
    MMC.status |= VDPSTATUS_CE;

    MMC.systemTime = systemTime;
}

/*************************************************************
** vdpCmdWrite
**
** Description:
**      Writes a new command to the VDP
**************************************************************
*/
void vdpCmdWrite(UInt8 reg, UInt8 value, UInt32 systemTime)
{
    reg &= 0x1f;

    switch (reg) {
	case 0x00: MMC.SX = (MMC.SX & 0xff00) | value;                 break;
	case 0x01: MMC.SX = (MMC.SX & 0x00ff) | ((value & 0x01) << 8); break;
	case 0x02: MMC.SY = (MMC.SY & 0xff00) | value;                 break;
	case 0x03: MMC.SY = (MMC.SY & 0x00ff) | ((value & 0x03) << 8); break;
	case 0x04: MMC.DX = (MMC.DX & 0xff00) | value;                 break;
	case 0x05: MMC.DX = (MMC.DX & 0x00ff) | ((value & 0x01) << 8); break;
	case 0x06: MMC.DY = (MMC.DY & 0xff00) | value;                 break;
	case 0x07: MMC.DY = (MMC.DY & 0x00ff) | ((value & 0x03) << 8); break;
	case 0x08: MMC.NX = (MMC.NX & 0xff00) | value;                 break;
	case 0x09: MMC.NX = (MMC.NX & 0x00ff) | ((value & 0x03) << 8); break;
	case 0x0a: MMC.NY = (MMC.NY & 0xff00) | value;                 break;
	case 0x0b: MMC.NY = (MMC.NY & 0x00ff) | ((value & 0x03) << 8); break;
	case 0x0c: 
        MMC.CL = value;
        MMC.status &= ~VDPSTATUS_TR;
        break;
	case 0x0d: 
        MMC.ARG = value; 
        break;
	case 0x0e: 
		MMC.LO = value & 0x0F;
		MMC.CM = value >> 4;
        if (MMC.screenMode >= 0) {
		    vdpCmdSetCommand(systemTime);
        }
		break;
    }
}

/*************************************************************
** vdpSetScreenMode
**
** Description:
**      Sets the current screen mode
**************************************************************
*/
void vdpSetScreenMode(int screenMode, int commandEnable) {
    if (screenMode > 8 && screenMode <= 12) {
        screenMode = 3;
    }
    else if (screenMode < 5 || screenMode > 12) {
        if (commandEnable) {
            screenMode = 2;
        }
        else {
            screenMode = -1;
        }
    }
    else {
        screenMode -= 5;
    }

    if (MMC.screenMode != screenMode) {
        MMC.screenMode = screenMode;
        if (screenMode == -1) {
            MMC.CM = 0;
            MMC.status &= ~VDPSTATUS_CE;
        }
    }
}

/*************************************************************
** vdpSetTimingMode
**
** Description:
**      Sets the timing mode (sprites/nosprites, ...)
**************************************************************
*/
void vdpSetTimingMode(UInt8 timingMode) {
    MMC.timingMode = timingMode;
}

/*************************************************************
** vdpGetStatus
**
** Description:
**      Gets current status
**************************************************************
*/
UInt8 vdpGetStatus() {
    return MMC.status;
}

/*************************************************************
** vdpGetBorderX
**
** Description:
**      Gets the border X value
**************************************************************
*/
UInt16 vdpGetBorderX() {
    return MMC.borderX;
}

/*************************************************************
** vdpGetColor
**
** Description:
**      Gets the color value
**************************************************************
*/
UInt8 vdpGetColor() {
    MMC.status &= ~VDPSTATUS_TR;
    return MMC.CL;
}

/*************************************************************
** vdpCmdFlush
**
** Description:
**      Flushes current VDP command
**************************************************************
*/
void vdpCmdFlush() 
{
    while (MMC.CM != 0 && !(MMC.status & VDPSTATUS_TR)) {
        int opsCnt = MMC.VdpOpsCnt += 1000000;
        vdpCmdExecute(MMC.systemTime + opsCnt);
        if (MMC.VdpOpsCnt == 0 || MMC.VdpOpsCnt == opsCnt) {
            break;
        }
    }
}

/*************************************************************
** vdpCmdExecute
**
** Description:
**      Executes command engine until the given time.
**************************************************************
*/
void vdpCmdExecute(UInt32 systemTime)
{
    MMC.VdpOpsCnt += systemTime - MMC.systemTime;
    MMC.systemTime = systemTime;
    
    if (MMC.VdpOpsCnt <= 0) {
        return;
    }

    switch (MMC.CM) {
    case CM_SRCH:
        SrchEngine();
        break;
    case CM_LINE:
        LineEngine();
        break;
    case CM_LMMV:
        LmmvEngine();
        break;
    case CM_LMMM:
        LmmmEngine();
        break;
    case CM_LMCM:
        LmcmEngine();
        break;
    case CM_LMMC:
        LmmcEngine();
        break;
    case CM_HMMV:
        HmmvEngine();
        break;
    case CM_HMMM:
        HmmmEngine();
        break;
    case CM_YMMM:
        YmmmEngine();
        break;
    case CM_HMMC:
        HmmcEngine();  
        break;
    default:
        MMC.VdpOpsCnt = 0;
    }
}

/*************************************************************
** vdpCmdLoadState
**
** Description:
**      Loads the state of the command engine. 
**************************************************************
*/
void vdpCmdLoadState()
{
    SaveState* state = saveStateOpenForRead("vdpCommandEngine");

    MMC.SX            =         saveStateGet(state, "SX",         0);
    MMC.SY            =         saveStateGet(state, "SY",         0);
    MMC.DX            =         saveStateGet(state, "DX",         0);
    MMC.DY            =         saveStateGet(state, "DY",         0);
    MMC.NX            =         saveStateGet(state, "NX",         0);
    MMC.NY            =         saveStateGet(state, "NY",         0);
    MMC.ASX           =         saveStateGet(state, "ASX",        0);
    MMC.ADX           =         saveStateGet(state, "ADX",        0);
    MMC.ANX           =         saveStateGet(state, "ANX",        0);
    MMC.ARG           = (UInt8) saveStateGet(state, "ARG",        0);
    MMC.CL            = (UInt8) saveStateGet(state, "CL",         0);
    MMC.LO            = (UInt8) saveStateGet(state, "LO",         0);
    MMC.CM            = (UInt8) saveStateGet(state, "CM",         0);
    MMC.status        = (UInt8) saveStateGet(state, "STATUS",     0);
    MMC.borderX       = (UInt16)saveStateGet(state, "BORDERX",    0);
    MMC.TX            =         saveStateGet(state, "TX",         0);
    MMC.TY            =         saveStateGet(state, "TY",         0);
    MMC.MX            =         saveStateGet(state, "MX",         0);
    MMC.VdpOpsCnt     =         saveStateGet(state, "VdpOpsCnt",  0);
    MMC.systemTime    =         saveStateGet(state, "systemTime", boardSystemTime());
    MMC.screenMode    =         saveStateGet(state, "screenMode", 0);
    MMC.timingMode    =         saveStateGet(state, "timingMode", 0);
    vramMask          =         saveStateGet(state, "vramMask",   8 << 14);
    
    saveStateClose(state);
}


/*************************************************************
** vdpCmdSaveState
**
** Description:
**      Saves the state of the command engine. 
**************************************************************
*/
void vdpCmdSaveState()
{
    SaveState* state = saveStateOpenForWrite("vdpCommandEngine");

    saveStateSet(state, "SX",         MMC.SX);
    saveStateSet(state, "SY",         MMC.SY);
    saveStateSet(state, "DX",         MMC.DX);
    saveStateSet(state, "DY",         MMC.DY);
    saveStateSet(state, "NX",         MMC.NX);
    saveStateSet(state, "NY",         MMC.NY);
    saveStateSet(state, "ASX",        MMC.ASX);
    saveStateSet(state, "ADX",        MMC.ADX);
    saveStateSet(state, "ANX",        MMC.ANX);
    saveStateSet(state, "ARG",        MMC.ARG);
    saveStateSet(state, "CL",         MMC.CL);
    saveStateSet(state, "LO",         MMC.LO);
    saveStateSet(state, "CM",         MMC.CM);
    saveStateSet(state, "STATUS",     MMC.status);
    saveStateSet(state, "BORDERX",    MMC.borderX);
    saveStateSet(state, "TX",         MMC.TX);
    saveStateSet(state, "TY",         MMC.TY);
    saveStateSet(state, "MX",         MMC.MX);
    saveStateSet(state, "VdpOpsCnt",  MMC.VdpOpsCnt);
    saveStateSet(state, "systemTime", MMC.systemTime);
    saveStateSet(state, "screenMode", MMC.screenMode);
    saveStateSet(state, "timingMode", MMC.timingMode);
    saveStateSet(state, "vramMask",   vramMask);
    
    saveStateClose(state);
}


