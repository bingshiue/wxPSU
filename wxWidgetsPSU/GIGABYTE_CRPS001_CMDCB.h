/**
 * @file GIGABYTE_CRPS0001_CMDCB.h
 */
#ifndef _GIGABYTE_CRPS0001_CMDCB_H_
#define _GIGABYTE_CRPS0001_CMDCB_H_

#include "GIGABYTE_CRPS001_CBQuery.h"
#include "GIGABYTE_CRPS001_CBCook.h"
#include "GIGABYTE_CRPS001_CBRaw.h"
#include "GIGABYTE_CRPS001.h"

CMDQueryCBFunc g_GIGABYTE_CRPS001_CMDQueryCBFunc[GIGABYTE_CRPS001_CMD_TABLE_SIZE] = {
	GB_CRPS_Query_00H,
	GB_CRPS_Query_03H,
	GB_CRPS_Query_05H, // New
	GB_CRPS_Query_06H, // New
	GB_CRPS_Query_19H, // New
	GB_CRPS_Query_1aH, // New
	GB_CRPS_Query_1bH,
	GB_CRPS_Query_20H,
	GB_CRPS_Query_30H, // New
	//GB_CRPS_Query_31H, // New
	GB_CRPS_Query_4aH, // New
	GB_CRPS_Query_51H,
	GB_CRPS_Query_70H, // New
	GB_CRPS_Query_79H,
	GB_CRPS_Query_7aH,
	GB_CRPS_Query_7bH,
	GB_CRPS_Query_7cH,
	GB_CRPS_Query_7dH,
	GB_CRPS_Query_7eH,
	GB_CRPS_Query_81H,
	GB_CRPS_Query_86H,
	GB_CRPS_Query_87H,
	GB_CRPS_Query_88H,
	GB_CRPS_Query_89H,
	GB_CRPS_Query_8b00H,
	GB_CRPS_Query_8c00H,
	GB_CRPS_Query_8b01H,
	GB_CRPS_Query_8c01H,
	GB_CRPS_Query_8dH,
	GB_CRPS_Query_8eH,
	GB_CRPS_Query_8fH,
	GB_CRPS_Query_90H,
	GB_CRPS_Query_91H, // New
	GB_CRPS_Query_96H,
	GB_CRPS_Query_97H,
	GB_CRPS_Query_98H,
	GB_CRPS_Query_9aH,
	GB_CRPS_Query_9bH,
	GB_CRPS_Query_9eH,
	GB_CRPS_Query_a0H,
	GB_CRPS_Query_a1H,
	GB_CRPS_Query_a2H,
	GB_CRPS_Query_a3H,
	GB_CRPS_Query_a4H,
	GB_CRPS_Query_a5H,
	GB_CRPS_Query_a6H,
	GB_CRPS_Query_a7H,
	GB_CRPS_Query_a8H,
	GB_CRPS_Query_a9H,
	GB_CRPS_Query_aaH,
	GB_CRPS_Query_abH,
	GB_CRPS_Query_c0H, // New
	GB_CRPS_Query_c1H, // New
	GB_CRPS_Query_c2H, // New
	GB_CRPS_Query_d9H, // New

};

CMDCookCBFunc g_GIGABYTE_CRPS001_CMDCookCBFunc[GIGABYTE_CRPS001_CMD_TABLE_SIZE] = {
	GB_CRPS_Cook_00H,
	GB_CRPS_Cook_03H,
	GB_CRPS_Cook_05H, // New
	GB_CRPS_Cook_06H, // New
	GB_CRPS_Cook_19H, // New
	GB_CRPS_Cook_1aH, // New
	GB_CRPS_Cook_1bH,
	GB_CRPS_Cook_20H,
	GB_CRPS_Cook_30H, // New
	//GB_CRPS_Cook_31H, // New
	GB_CRPS_Cook_4aH, // New
	GB_CRPS_Cook_51H,
	GB_CRPS_Cook_70H, // New
	GB_CRPS_Cook_79H,
	GB_CRPS_Cook_7aH,
	GB_CRPS_Cook_7bH,
	GB_CRPS_Cook_7cH,
	GB_CRPS_Cook_7dH,
	GB_CRPS_Cook_7eH,
	GB_CRPS_Cook_81H,
	GB_CRPS_Cook_86H,
	GB_CRPS_Cook_87H,
	GB_CRPS_Cook_88H,
	GB_CRPS_Cook_89H,
	GB_CRPS_Cook_8b00H,
	GB_CRPS_Cook_8c00H,
	GB_CRPS_Cook_8b01H,
	GB_CRPS_Cook_8c01H,
	GB_CRPS_Cook_8dH,
	GB_CRPS_Cook_8eH,
	GB_CRPS_Cook_8fH,
	GB_CRPS_Cook_90H,
	GB_CRPS_Cook_91H, // New
	GB_CRPS_Cook_96H,
	GB_CRPS_Cook_97H,
	GB_CRPS_Cook_98H,
	GB_CRPS_Cook_9aH,
	GB_CRPS_Cook_9bH,
	GB_CRPS_Cook_9eH,
	GB_CRPS_Cook_a0H,
	GB_CRPS_Cook_a1H,
	GB_CRPS_Cook_a2H,
	GB_CRPS_Cook_a3H,
	GB_CRPS_Cook_a4H,
	GB_CRPS_Cook_a5H,
	GB_CRPS_Cook_a6H,
	GB_CRPS_Cook_a7H,
	GB_CRPS_Cook_a8H,
	GB_CRPS_Cook_a9H,
	GB_CRPS_Cook_aaH,
	GB_CRPS_Cook_abH,
	GB_CRPS_Cook_c0H, // New
	GB_CRPS_Cook_c1H, // New
	GB_CRPS_Cook_c2H, // New
	GB_CRPS_Cook_d9H, // New
};

CMDRawCBFunc g_GIGABYTE_CRPS001_CMDRawCBFunc[GIGABYTE_CRPS001_CMD_TABLE_SIZE] = {
	GB_CRPS_Raw_00H,
	GB_CRPS_Raw_03H,
	GB_CRPS_Raw_05H, // New
	GB_CRPS_Raw_06H, // New
	GB_CRPS_Raw_19H, // New
	GB_CRPS_Raw_1aH, // New
	GB_CRPS_Raw_1bH,
	GB_CRPS_Raw_20H,
	GB_CRPS_Raw_30H, // New
	//GB_CRPS_Raw_31H, // New
	GB_CRPS_Raw_4aH, // New
	GB_CRPS_Raw_51H,
	GB_CRPS_Raw_70H, // New
	GB_CRPS_Raw_79H,
	GB_CRPS_Raw_7aH,
	GB_CRPS_Raw_7bH,
	GB_CRPS_Raw_7cH,
	GB_CRPS_Raw_7dH,
	GB_CRPS_Raw_7eH,
	GB_CRPS_Raw_81H,
	GB_CRPS_Raw_86H,
	GB_CRPS_Raw_87H,
	GB_CRPS_Raw_88H,
	GB_CRPS_Raw_89H,
	GB_CRPS_Raw_8b00H,
	GB_CRPS_Raw_8c00H,
	GB_CRPS_Raw_8b01H,
	GB_CRPS_Raw_8c01H,
	GB_CRPS_Raw_8dH,
	GB_CRPS_Raw_8eH,
	GB_CRPS_Raw_8fH,
	GB_CRPS_Raw_90H,
	GB_CRPS_Raw_91H, // New
	GB_CRPS_Raw_96H,
	GB_CRPS_Raw_97H,
	GB_CRPS_Raw_98H,
	GB_CRPS_Raw_9aH,
	GB_CRPS_Raw_9bH,
	GB_CRPS_Raw_9eH,
	GB_CRPS_Raw_a0H,
	GB_CRPS_Raw_a1H,
	GB_CRPS_Raw_a2H,
	GB_CRPS_Raw_a3H,
	GB_CRPS_Raw_a4H,
	GB_CRPS_Raw_a5H,
	GB_CRPS_Raw_a6H,
	GB_CRPS_Raw_a7H,
	GB_CRPS_Raw_a8H,
	GB_CRPS_Raw_a9H,
	GB_CRPS_Raw_aaH,
	GB_CRPS_Raw_abH,
	GB_CRPS_Raw_c0H, // New
	GB_CRPS_Raw_c1H, // New
	GB_CRPS_Raw_c2H, // New
	GB_CRPS_Raw_d9H, // New
};

#endif