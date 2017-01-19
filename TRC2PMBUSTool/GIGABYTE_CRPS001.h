/**
 * @file GIGABYTE_CRPS0001.h
 */
#ifndef _GIGABYTE_CRPS0001_H_
#define _GIGABYTE_CRPS0001_H_

#include "PMBUSCommandType.h"
#include "PMBUSCMDWritePages.h"

#define GIGABYTE_CRPS001_MODEL_NAME      L"GIGABYTE_CRPS001"

PMBUSCOMMAND_t g_GIGABYTE_CRPS001_CMDTable[] = { 
	// toggle  Label, Register  Name  Access Query  Cook  Raw  ResponseDataLength  RECVBUFF_t  CMDSTATUS_t CMDCBFUNC_t  wxPanel(Write Page) wxPanel(Read Page) DataFormat_t
	// 00H [0]
	{ true, "00H", 0x00, "PAGE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 03H [1]
	{ true, "03H", 0x03, "CLEAR_FAULTS", cmd_access_write, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 05H [2]
	{ true, "05H", 0x05, "PAGE_PLUS_WRITE", cmd_access_bw, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 06H [3]
	{ true, "06H", 0x06, "PAGE_PLUS_READ", cmd_access_bwr_read, 0, 0, { 0 }, 0x03, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x04, { 0x03, 0x00, 0x1b, 0x7a }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 19H [4]
	{ true, "19H", 0x19, "CAPABILITY", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 1AH [5]
	{ true, "1AH", 0x1a, "QUERY", cmd_access_bwr_read, 0, 0, { 0 }, 0x03, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x87 }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 1BH [6]
	{ true, "1BH", 0x1b, "SMBALERT_MASK", cmd_access_bwr_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x7a }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 20H [7]
	{ true, "20H", 0x20, "VOUT_MODE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 30H [8]
	{ true, "30H", 0x30, "COEFFICIENTS", cmd_access_bwr_read, 0, 0, { 0 }, 0x07, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x03, { 0x02, DEF_30H_READ_CMD_BYTE, DEF_30H_READ_RW_BYTE }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 31H
	//{ true, "31H", 0x31, "POUT_MAX", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL , { } },
	// 3AH [9]
	{ true, "3AH", 0x3a, "FAN_CONFIG_1_2", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 3BH [10]        
	{ true, "3BH", 0x3b, "FAN_COMMAND_1", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 46H [11]
	{ true, "46H", 0x46, "IOUT_OC_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 4AH [12]
	{ true, "4AH", 0x4a, "IOUT_OC_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 51h [13]       
	{ true, "51H", 0x51, "OT_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 5Dh [14]        
	{ true, "5DH", 0x5d, "IIN_OC_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 6Ah [15]        
	{ true, "6AH", 0x6a, "POUT_OP_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 6Bh [16]        
	{ true, "6BH", 0x6b, "PIN_OP_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 70h [17]
	{ true, "70H", 0x70, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 78h [18]        
	{ true, "78H", 0x78, "STATUS BYTE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 79h [19]        
	{ true, "79H", 0x79, "STATUS_WORD", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 7Ah [20]        
	{ true, "7AH", 0x7a, "STATUS_VOUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 7Bh [21]   
	{ true, "7BH", 0x7b, "STATUS_IOUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 7Ch [22]        
	{ true, "7CH", 0x7c, "STATUS_INPUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 7Dh [23]        
	{ true, "7DH", 0x7d, "STATUS_TEMPERATURE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 7Eh [24]       
	{ true, "7EH", 0x7e, "STATUS_CML", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 81h [25]       
	{ true, "81H", 0x81, "STATUS_FAN_1_2", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 86h [26]        
	{ true, "86H", 0x86, "READ_EIN", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 87h [27]        
	{ true, "87H", 0x87, "READ_EOUT", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 88h [28]        
	{ true, "88H", 0x88, "READ_VIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 89h [29]       
	{ true, "89H", 0x89, "READ_IIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 8Ah [30]        
	{ true, "8AH", 0x8a, "READ_VCAP", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 8Bh (00h) [31]   
	{ true, "8Bh (00h)", 0x8b, "READ_VOUT(12V)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, 0, { 0, 0 }, cmd_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 8Ch (00h) [32]  
	{ true, "8Ch (00h)", 0x8c, "READ_IOUT(12V)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, 0, { 0, 0 }, cmd_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 8Bh (01h) [33]  
	{ true, "8Bh (01h)", 0x8b, "READ_VOUT(12V_SBY)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, 0, { 0, 0 }, cmd_need_change_page, 1, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 8Ch (01h) [34]  
	{ true, "8Ch (01h)", 0x8c, "READ_IOUT(12V_SBY)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, 0, { 0, 0 }, cmd_need_change_page, 1, cmd_query_not_yet }, { 0 }, NULL, NULL, { } },
	// 8Dh [35]        
	{ true, "8DH", 0x8d, "READ_TEMPERATURE_1(Ambient)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 8Eh [36]        
	{ true, "8EH", 0x8e, "READ_TEMPERATURE_2(Second)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 8Fh [37]        
	{ true, "8FH", 0x8f, "READ_TEMPERATURE_3(Primary)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 90h [38]        
	{ true, "90H", 0x90, "READ_FAN_SPEED_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 91h [39]       
	//{ true, "91H", 0x91, "READ_FAN_SPEED_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 96h        
	{ true, "96H", 0x96, "READ_POUT", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 97h [40]        
	{ true, "97H", 0x97, "READ_PIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 98h [41]        
	{ true, "98H", 0x98, "PMBUS_REVISION", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 99h [42]        
	{ true, "99H", 0x99, "MFR_ID", cmd_access_br, 0, 0, { 0 }, 0x07, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 9Ah [43]        
	{ true, "9AH", 0x9a, "MFR_MODEL", cmd_access_br, 0, 0, { 0 }, MFR_MODEL_LENGTH+2, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 9Bh [44]       
	{ true, "9BH", 0x9b, "MFR_REVISION", cmd_access_br, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 9Ch [45]      
	{ true, "9CH", 0x9c, "MFR_LOCATION", cmd_access_br, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 9Dh [46]        
	{ true, "9DH", 0x9d, "MFR_DATE", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 9Eh [47]       
	{ true, "9EH", 0x9e, "MFR_SERIAL", cmd_access_br, 0, 0, { 0 }, 0x1c, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// 9FH [48]
	{ true, "9FH", 0x9f, "APP_PROFILE_SUPPORT", cmd_access_br, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A0h [49]       
	{ true, "A0H", 0xa0, "MFR_VIN_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A1h [50]        
	{ true, "A1H", 0xa1, "MFR_VIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A2h [51]        
	{ true, "A2H", 0xa2, "MFR_IIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A3h [52]       
	{ true, "A3H", 0xa3, "MFR_PIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A4h [53]        
	{ true, "A4H", 0xa4, "MFR_VOUT_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A5h [54]        
	{ true, "A5H", 0xa5, "MFR_VOUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A6h [55]        
	{ true, "A6H", 0xa6, "MFR_IOUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A7h [56]        
	{ true, "A7H", 0xa7, "MFR_POUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A8h [57]      
	{ true, "A8H", 0xa8, "MFR_TAMBIENT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// A9h [58]        
	{ true, "A9H", 0xa9, "MFR_TAMBIENT_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// AAh [59]        
	{ true, "AAH", 0xaa, "MFR_EFFICIENCY_LL", cmd_access_br, 0, 0, { 0 }, 0x10, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// ABh [60]        
	{ true, "ABH", 0xab, "MFR_EFFICIENCY_HL", cmd_access_br, 0, 0, { 0 }, 0x10, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// C0h [61]
	{ true, "C0H", 0xc0, "MFR_MAX_TEMP_1", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// C1h [62]
	{ true, "C1H", 0xc1, "MFR_MAX_TEMP_2", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// C2h [63]
	{ true, "C2H", 0xc2, "MFR_MAX_TEMP_3", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// D0h [64]        
	{ true, "D0H", 0xd0, "Cold_Redundancy_Config", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// D9h [65]
	{ true, "D9H", 0xd9, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// DCh [66]       
	{ true, "DCH", 0xdc, "Read_BoxSTATUS", cmd_access_br, 0, 0, { 0 }, 0x0C, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// E0h [67]        
	{ true, "E0H", 0xe0, "PFC_TEMPERATURE_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// E1h [68]        
	{ true, "E1H", 0xe1, "PFC_TEMPERATURE_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// E2h [69]        
	{ true, "E2H", 0xe2, "SR_TEMPERATURE_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },
	// E3h [70]        
	{ true, "E3H", 0xe3, "SR_TEMPERATURE_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { } },

};

#define GIGABYTE_CRPS001_CMD_TABLE_SIZE  sizeof(g_GIGABYTE_CRPS001_CMDTable)/sizeof(PMBUSCOMMAND_t)

#endif