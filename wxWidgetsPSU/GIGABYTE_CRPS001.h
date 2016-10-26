/**
 * @file GIGABYTE_CRPS0001.h
 */
#ifndef _GIGABYTE_CRPS0001_H_
#define _GIGABYTE_CRPS0001_H_

#include "PMBUSCommandType.h"
#include "PMBUSCMDWritePages.h"

#define GIGABYTE_CRPS001_MODEL_NAME      L"GIGABYTE_CRPS001"

PMBUSCOMMAND_t g_GIGABYTE_CRPS001_CMDTable[] = { 
	// toggle  Label, Register  Name  Access Query  Cook  Raw  ResponseDataLength  RECVBUFF_t  CMDSTATUS_t CMDCBFUNC_t  wxPanel(Write Page)
	// 00H [0]
	{ true, "00H", 0x00, "PAGE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 03H [1]
	{ true, "03H", 0x03, "CLEAR_FAULTS", cmd_access_write, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 05H [2]
	{ true, "05H", 0x05, "PAGE_PLUS_WRITE", cmd_access_bw, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 06H [3]
	{ true, "06H", 0x06, "PAGE_PLUS_READ", cmd_access_bwr_read, 0, 0, { 0 }, 0x03, { 0 }, { cmd_status_not_run, cmd_also_send_write_data, 0x03, { 0x02, 0x01, 0x8b }, cmd_no_need_change_page, 0 }, { 0 }, NULL, NULL },
	// 19H [4]
	{ true, "19H", 0x19, "CAPABILITY", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 1AH [5]
	{ true, "1AH", 0x1a, "QUERY", cmd_access_bwr_read, 0, 0, { 0 }, 0x03, { 0 }, { cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x87 }, cmd_no_need_change_page, 0 }, { 0 }, NULL, NULL },
	// 1BH [6]
	{ true, "1BH", 0x1b, "SMRALERT_MASK", cmd_access_bwr_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x78 }, cmd_no_need_change_page, 0 }, { 0 }, NULL, NULL },
	// 20H [7]
	{ true, "20H", 0x20, "VOUT_MODE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 30H [8]
	{ true, "30H", 0x30, "COEFFICIENTS", cmd_access_bwr_read, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 31H [9]
	//{ true, "31H", 0x31, "POUT_MAX", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 } },
	// 4AH [10]
	{ true, "4AH", 0x4a, "IOUT_OC_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 51h [11]       
	{ true, "51H", 0x51, "OT_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 70h [12]
	{ true, "70H", 0x70, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 79h [13]        
	{ true, "79H", 0x79, "STATUS WORD", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 7Ah [14]        
	{ true, "7AH", 0x7a, "STATUS VOUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 7Bh [15]   
	{ true, "7BH", 0x7b, "STATUS IOUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 7Ch [16]        
	{ true, "7CH", 0x7c, "STATUS INPUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 7Dh [17]        
	{ true, "7DH", 0x7d, "STATUS TEMPERATURE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 7Eh [18]       
	{ true, "7EH", 0x7e, "STATUS CML ", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 81h [19]       
	{ true, "81H", 0x81, "STATUS FAN_1_2", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 86h [20]        
	{ true, "86H", 0x86, "READ EIN", cmd_access_read, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 87h [21]        
	{ true, "87H", 0x87, "READ EOUT", cmd_access_read, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 88h [22]        
	{ true, "88H", 0x88, "READ VIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 89h [23]       
	{ true, "89H", 0x89, "READ IIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 8Bh (00h) [24]   
	{ true, "8Bh (00h)", 0x8b, "READ_VOUT(12V)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, { 0, 0 }, cmd_need_change_page, 0 }, { 0 }, NULL, NULL },
	// 8Ch (00h) [25]  
	{ true, "8Ch (00h)", 0x8c, "READ_IOUT(12V)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, { 0, 0 }, cmd_need_change_page, 0 }, { 0 }, NULL, NULL },
	// 8Bh (01h) [26]  
	{ true, "8Bh (01h)", 0x8b, "READ_VOUT(12V_SBY)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, { 0, 0 }, cmd_need_change_page, 1 }, { 0 }, NULL, NULL },
	// 8Ch (01h) [27]  
	{ true, "8Ch (01h)", 0x8c, "READ_IOUT(12V_SBY)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, { 0, 0 }, cmd_need_change_page, 1 }, { 0 }, NULL, NULL },
	// 8Dh [28]        
	{ true, "8DH", 0x8d, "READ_TEMPERATURE_1(Ambient)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 8Eh [29]        
	{ true, "8EH", 0x8e, "READ_TEMPERATURE_2(Second)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 8Fh [30]        
	{ true, "8FH", 0x8f, "READ_TEMPERATURE_3(Primary)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 90h [31]        
	{ true, "90H", 0x90, "READ_FAN_SPEED_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 91h [32]        
	{ true, "91H", 0x91, "READ_FAN_SPEED_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 96h [33]        
	{ true, "96H", 0x96, "READ_POUT", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 97h [34]        
	{ true, "97H", 0x97, "READ_PIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 98h [35]        
	{ true, "98H", 0x98, "PMBUS_REVISION", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 9Ah [36]        
	{ true, "9AH", 0x9a, "MFR_MODEL", cmd_access_brbw, 0, 0, { 0 }, 0x0f, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 9Bh [37]       
	{ true, "9BH", 0x9b, "MFR_REVISION", cmd_access_brbw, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 9Eh [38]       
	{ true, "9EH", 0x9e, "MFR_SERIAL", cmd_access_brbw, 0, 0, { 0 }, 0x13, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A0h [39]       
	{ true, "A0H", 0xa0, "MFR_VIN_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A1h [40]        
	{ true, "A1H", 0xa1, "MFR_VIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A2h [41]        
	{ true, "A2H", 0xa2, "MFR_IIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A3h [42]       
	{ true, "A3H", 0xa3, "MFR_PIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A4h [43]        
	{ true, "A4H", 0xa4, "MFR_VOUT_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A5h [44]        
	{ true, "A5H", 0xa5, "MFR_VOUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A6h [45]        
	{ true, "A6H", 0xa6, "MFR_IOUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A7h [46]        
	{ true, "A7H", 0xa7, "MFR_POUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A8h [47]      
	{ true, "A8H", 0xa8, "MFR_TAMBIENT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// A9h [48]        
	{ true, "A9H", 0xa9, "MFR_TAMBIENT_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// AAh [49]        
	{ true, "AAH", 0xaa, "MFR_EFFICIENCY_LL", cmd_access_br, 0, 0, { 0 }, 0x14, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// ABh [50]        
	{ true, "ABH", 0xab, "MFR_EFFICIENCY_HL", cmd_access_br, 0, 0, { 0 }, 0x14, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// C0h [51]
	{ true, "C0H", 0xc0, "MFR_MAX_TEMP_1", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// C1h [52]
	{ true, "C1H", 0xc1, "MFR_MAX_TEMP_2", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// C2h [53]
	{ true, "C2H", 0xc2, "MFR_MAX_TEMP_3", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// D9h [54]
	{ true, "D9H", 0xd9, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL },

};

#define GIGABYTE_CRPS001_CMD_TABLE_SIZE  sizeof(g_GIGABYTE_CRPS001_CMDTable)/sizeof(PMBUSCOMMAND_t) //53 + 2 - 1

#endif