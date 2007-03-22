/*
 * $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/MegaSCSIsub.c,v $
 *
 * $Revision: 1.7 $
 *
 * $Date: 2007-03-22 10:55:08 $
 *
 * Copyright (C) 2007 white cat
 *
 * Drive setting parameters for MEGA-SCSI and WAVE-SCSI.
 */

#include "MegaSCSIsub.h"
#include "ScsiDefs.h"
#include "ScsiDevice.h"
#include <stdlib.h>

const SCSICREATE MegaSCSIparm[8] = {
{
    /* #0 */
    NULL, SDT_DirectAccess,
    MODE_SCSI2 | MODE_MEGASCSI | MODE_FDS120 | MODE_REMOVABLE },
{
    /* #1 */
    NULL, SDT_DirectAccess,
    MODE_SCSI2 | MODE_MEGASCSI | MODE_FDS120 | MODE_REMOVABLE },
{
    /* #2 */
    NULL, SDT_DirectAccess,
    MODE_SCSI2 | MODE_MEGASCSI | MODE_FDS120 | MODE_REMOVABLE },
{
    /* #3 */
    NULL, SDT_OpticalMemory,
    MODE_SCSI1 | MODE_MEGASCSI | MODE_FDS120 | MODE_REMOVABLE },
{
    /* #4 */
    NULL, SDT_DirectAccess,
    MODE_SCSI2 | MODE_MEGASCSI | MODE_CHECK2 | MODE_FDS120 | MODE_REMOVABLE },
{
    /* #5 */
    NULL, SDT_DirectAccess,
    MODE_SCSI2 | MODE_MEGASCSI | MODE_CHECK2 | MODE_FDS120 | MODE_REMOVABLE },
{
    /* #6 */
    NULL, SDT_CDROM,
    MODE_SCSI2 | MODE_UNITATTENTION | MODE_REMOVABLE },
{
    /* #7 */
    NULL, SDT_DirectAccess,
    MODE_SCSI3 | MODE_MEGASCSI | MODE_CHECK2 | MODE_FDS120 | MODE_REMOVABLE }
};

/*
     Sample
     0123456789ABCDEF (needs 16bytes)
    "PRODUCT NAME    ", SDT_DirectAccess,
    MODE_SCSI2 | MODE_UNITATTENTION | MODE_MEGASCSI | MODE_REMOVABLE }
*/

int EseRamSize(int size)
{
    int i = 0;
    size /= 0x20000;
    do {
        if ((size >>= 1) == 0) {
            break;
        }
        ++i;
    } while (i < 3);
    return i;
}
