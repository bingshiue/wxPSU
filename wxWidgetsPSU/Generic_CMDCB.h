/**
 * @file Generic_CMDCB.h
 */
#ifndef _GENERIC_CMDCB_H_
#define _GENERIC_CMDCB_H_

#include "PMBUSCBQuery.h"
#include "PMBUSCBCook.h"
#include "PMBUSCBRaw.h"
#include "Generic_MODEL.h"

CMDQueryCBFunc g_Generic_CMDQueryCBFunc[GENERIC_CMD_TABLE_SIZE] = {
	Query_f5H,
	Query_00H,
	Query_01H,
	Query_02H,
	Query_03H,
	Query_1bH,
	Query_20H,
	Query_3aH,
	Query_3bH,
	Query_51H,
	Query_5dH,
};

CMDCookCBFunc g_Generic_CMDCookCBFunc[GENERIC_CMD_TABLE_SIZE] = {
	Cook_f5H,
	Cook_00H,
	Cook_01H,
	Cook_02H,
	Cook_03H,
	Cook_1bH,
	Cook_20H,
	Cook_3aH,
	Cook_3bH,
	Cook_51H,
	Cook_5dH,
};

CMDRawCBFunc g_Generic_CMDRawCBFunc[GENERIC_CMD_TABLE_SIZE] = {
	Raw_f5H,
	Raw_00H,
	Raw_01H,
	Raw_02H,
	Raw_03H,
	Raw_1bH,
	Raw_20H,
	Raw_3aH,
	Raw_3bH,
	Raw_51H,
	Raw_5dH,
};

#endif
