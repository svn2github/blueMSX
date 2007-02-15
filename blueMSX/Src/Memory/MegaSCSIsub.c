/*
 * $Source:
 *
 * $Revision:
 *
 * $Date:
 *
 * Author: white cat
 * File  : MegaSCSIsub.c
 * Copyright (C) 2007 white cat
 *
 * Drive setting parameters for MEGA-SCSI and WAVE-SCSI.
 */

#include "MegaSCSIsub.h"
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
	NULL, SDT_DirectAccess,
	MODE_SCSI2 | MODE_MEGASCSI | MODE_CHECK2 | MODE_FDS120 | MODE_REMOVABLE },
{
	/* #7 */
	NULL, SDT_MediaChanger,
	MODE_SCSI3 | MODE_MEGASCSI | MODE_CHECK2 | MODE_FDS120 | MODE_REMOVABLE }
};

/*
	 Sample
	 0123456789ABCDEF (needs 16bytes)
	"PRODUCT NAME    ", SDT_DirectAccess,
	MODE_SCSI2 | MODE_UNITATTNTION | MODE_MEGASCSI | MODE_REMOVABLE }
*/
