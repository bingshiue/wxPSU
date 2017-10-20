/**
 * @file PBF003_00G.h
 */
#ifndef _PBF003_00G_H_
#define _PBF003_00G_H_

#include "PMBUSCommandType.h"
#include "PMBUSCMDWritePages.h"

#define PBF003_00G_MODEL_NAME                L"PBF003_00G"
#define PBF003_00G_DEFAULT_I2C_ADDRESS       0xA8
#define PBF003_00G_DEFAULT_CMD_POLLING_TIME  50


PMBUSCOMMAND_t g_PBF003_00G_CMDTable[] = {
	// toggle  Label, Register  Name  Access Query  Cook  Raw  ResponseDataLength  RECVBUFF_t  CMDSTATUS_t CMDCBFUNC_t  wxPanel(Write Page) wxPanel(Read Page) DataFormat_t
	// 0900h [0]
	{ true, "0900H", 0x0900, "VOLTAGE_ADJUST", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { cmd_data_format_DirectData_Format, {0,0,0}, {0,0,0} } },
	// 0902h [1]
	{ true, "0902H", 0x0902, "LATEST_ADJUSTED_COMMAND", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0904h [2]
	{ true, "0904H", 0x0904, "INPUT_VOLTAGE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0905h [3]
	{ true, "0905H", 0x0905, "INPUT_CURRENT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0906h [4]
	{ true, "0906H", 0x0906, "OUTPUT_VOLTAGE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0907h [5]
	{ true, "0907H", 0x0907, "OUTPUT_CURRENT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0908h [6]
	{ true, "0908H", 0x0908, "THERMAL", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0909h [7]
	{ true, "0909H", 0x0909, "VOLTAGE_RESET", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { cmd_data_format_DirectData_Format, {0,0,0}, {0,0,0} } },
	// 0910h [8]
	{ true, "0910H", 0x0910, "POWER_STATUS", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// 0920h [9]
	{ true, "0920H", 0x0920, "VIN_CALIBRATION", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { cmd_data_format_DirectData_Format, {0,0,0}, {0,0,0} } },
	// 0921h [10]
	{ true, "0921H", 0x0921, "VOUT_CALIBRATION", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { cmd_data_format_DirectData_Format, {0,0,0}, {0,0,0} } },
	// 0922h
	{ true, "0922H", 0x0922, "READ_SP_STATUS", cmd_access_read, 0, 0,{ 0 }, 0x02,{ 0 },{ 0 },{ 0 }, NULL, NULL, {} },
	// 0999h [11]
	{ true, "0999H", 0x0999, "FIRMWARE_VERSION", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },

};

#define PBF003_00G_CMD_TABLE_SIZE  sizeof(g_PBF003_00G_CMDTable)/sizeof(PMBUSCOMMAND_t)

#endif
