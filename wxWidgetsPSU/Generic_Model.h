/**
 * @file Generic_Model.h
 */
#ifndef _GENERIC_MODEL_H_
#define _GENERIC_MODEL_H_

#include "PMBUSCommandType.h"
#include "PMBUSCMDWritePages.h"

#define GENERIC_MODEL_NAME      L"Generic_Model"

PMBUSCOMMAND_t g_Generic_CMDTable[] = {
	// toggle  Label, Register  Name  Access Query  Cook  Raw  ResponseDataLength  RECVBUFF_t  CMDSTATUS_t CMDCBFUNC_t  wxPanel(Write Page) DataFormat_t
	// F5h         
	{ true, "F5H", 0xf5, "Firmware_Version_Command", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 00H
	{ true, "00H", 0x00, "PAGE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 01H
	{ true, "01H", 0x01, "OPERATION", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 02H
	{ true, "02H", 0x02, "ON_OFF_CONFIG", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 03H
	{ true, "03H", 0x03, "CLEAR_FAULTS", cmd_access_write, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 1BH
	{ true, "1BH", 0x1b, "SMBALERT_MASK", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x78 }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 20H
	{ true, "20H", 0x20, "VOUT_MODE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3AH
	{ true, "3AH", 0x3a, "FAN_CONFIG_1_2", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3BH         
	{ true, "3BH", 0x3b, "FAN_COMMAND_1", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 51h         
	{ true, "51H", 0x51, "OT_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5Dh         
	{ true, "5DH", 0x5d, "IIN_OC_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },

};

#define GENERIC_CMD_TABLE_SIZE  sizeof(g_Generic_CMDTable)/sizeof(PMBUSCOMMAND_t)

#endif