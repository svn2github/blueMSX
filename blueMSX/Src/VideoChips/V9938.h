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
#ifndef VDPCMD_H
#define VDPCMD_H

#include "MSXTypes.h"


/*************************************************************
** vdpCmdInit
**
** Description:
**      Initializes the command engine. A timer running at
**      21477270 Hz drives the command engine. systemTime
**      is the initial time of this timer.
**************************************************************
*/
void  vdpCmdInit(int vramSize, UInt8* vramPtr, UInt32 systemTime);


/*************************************************************
** vdpCmdWrite
**
** Description:
**      Writes a new command to the VDP
**************************************************************
*/
void  vdpCmdWrite(UInt8 reg, UInt8 value, UInt32 systemTime);


void vdpSetScreenMode(int screenMode, int commandEnable);
void vdpSetTimingMode(UInt8 timingMode);


UInt8 vdpGetStatus();
UInt16 vdpGetBorderX();
UInt8 vdpGetColor();

/*************************************************************
** vdpCmdExecute
**
** Description:
**      Executes a number of cycles of the VDP Command engine
**      (in 3579545 Hz)
**************************************************************
*/
void  vdpCmdExecute(UInt32 systemTime);


/*************************************************************
** vdpCmdFlush
**
** Description:
**      Flushes current VDP command
**************************************************************
*/
void  vdpCmdFlush();


/*************************************************************
** vdpCmdLoadState
**
** Description:
**      Loads the state of the command engine. 
**************************************************************
*/
void vdpCmdLoadState();


/*************************************************************
** vdpCmdSaveState
**
** Description:
**      Saves the state of the command engine.
**************************************************************
*/
void vdpCmdSaveState();

#endif /* VDPCMD_H */
