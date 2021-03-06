/**
 * @file PMBUSCMDCB.h
 */
#ifndef _PMBUSCMDCB_H_
#define _PMBUSCMDCB_H_

#include "PMBUSCBQuery.h"
#include "PMBUSCBCook.h"
#include "PMBUSCBRaw.h"

CMDQueryCBFunc CMDQueryCBFuncArray[62] = {
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
	Query_6aH,
	Query_6bH,
	Query_78H,
	Query_79H,
	Query_7aH,
	Query_7bH,
	Query_7cH,
	Query_7dH,
	Query_7eH,
	Query_7fH,
	Query_81H,
	Query_86H,
	Query_87H,
	Query_88H,
	Query_89H,
	Query_8aH,
	Query_8b00H,
	Query_8c00H,
	Query_8b01H,
	Query_8c01H,
	Query_8dH,
	Query_8eH,
	Query_8fH,
	Query_90H,
	Query_96H,
	Query_97H,
	Query_98H,
	Query_99H,
	Query_9aH,
	Query_9bH,
	Query_9cH,
	Query_9dH,
	Query_9eH,
	Query_a0H,
	Query_a1H,
	Query_a2H,
	Query_a3H,
	Query_a4H,
	Query_a5H,
	Query_a6H,
	Query_a7H,
	Query_a8H,
	Query_a9H,
	Query_aaH,
	Query_abH,
	Query_d0H,
	Query_dbH,
	Query_dcH,
	Query_ddH,
	Query_f5H,
	Query_faH,
	Query_fcH
};

CMDCookCBFunc CMDCookCBFuncArray[62] = {
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
	Cook_6aH,
	Cook_6bH,
	Cook_78H,
	Cook_79H,
	Cook_7aH,
	Cook_7bH,
	Cook_7cH,
	Cook_7dH,
	Cook_7eH,
	Cook_7fH,
	Cook_81H,
	Cook_86H,
	Cook_87H,
	Cook_88H,
	Cook_89H,
	Cook_8aH,
	Cook_8b00H,
	Cook_8c00H,
	Cook_8b01H,
	Cook_8c01H,
	Cook_8dH,
	Cook_8eH,
	Cook_8fH,
	Cook_90H,
	Cook_96H,
	Cook_97H,
	Cook_98H,
	Cook_99H,
	Cook_9aH,
	Cook_9bH,
	Cook_9cH,
	Cook_9dH,
	Cook_9eH,
	Cook_a0H,
	Cook_a1H,
	Cook_a2H,
	Cook_a3H,
	Cook_a4H,
	Cook_a5H,
	Cook_a6H,
	Cook_a7H,
	Cook_a8H,
	Cook_a9H,
	Cook_aaH,
	Cook_abH,
	Cook_d0H,
	Cook_dbH,
	Cook_dcH,
	Cook_ddH,
	Cook_f5H,
	Cook_faH,
	Cook_fcH
};

CMDRawCBFunc CMDRawCBFuncArray[62] = {
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
	Raw_6aH,
	Raw_6bH,
	Raw_78H,
	Raw_79H,
	Raw_7aH,
	Raw_7bH,
	Raw_7cH,
	Raw_7dH,
	Raw_7eH,
	Raw_7fH,
	Raw_81H,
	Raw_86H,
	Raw_87H,
	Raw_88H,
	Raw_89H,
	Raw_8aH,
	Raw_8b00H,
	Raw_8c00H,
	Raw_8b01H,
	Raw_8c01H,
	Raw_8dH,
	Raw_8eH,
	Raw_8fH,
	Raw_90H,
	Raw_96H,
	Raw_97H,
	Raw_98H,
	Raw_99H,
	Raw_9aH,
	Raw_9bH,
	Raw_9cH,
	Raw_9dH,
	Raw_9eH,
	Raw_a0H,
	Raw_a1H,
	Raw_a2H,
	Raw_a3H,
	Raw_a4H,
	Raw_a5H,
	Raw_a6H,
	Raw_a7H,
	Raw_a8H,
	Raw_a9H,
	Raw_aaH,
	Raw_abH,
	Raw_d0H,
	Raw_dbH,
	Raw_dcH,
	Raw_ddH,
	Raw_f5H,
	Raw_faH,
	Raw_fcH
};

#endif
