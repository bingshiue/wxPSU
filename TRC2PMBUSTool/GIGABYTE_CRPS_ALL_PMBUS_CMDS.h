/**
 * @file GIGABYTE_CRPS_ALL_PMBUS_CMDS.h
 */
#ifndef _GIGABYTE_CRPS_ALL_PMBUS_CMDS_H_
#define _GIGABYTE_CRPS_ALL_PMBUS_CMDS_H_

#include "PMBUSCommandType.h"
#include "PMBUSCMDWritePages.h"

#define GIGABYTE_CRPS_ALL_PMBUS_CMDS_MODEL_NAME      L"GIGABYTE_CRPS_ALL_PMBUS_COMMANDS"

PMBUSCOMMAND_t g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDTable[] = {
	// toggle  Label, Register  Name  Access Query  Cook  Raw  ResponseDataLength  RECVBUFF_t  CMDSTATUS_t CMDCBFUNC_t  wxPanel(Write Page) wxPanel(Read Page) DataFormat_t
	// 00H [0]
	{ true, "00H", 0x00, "PAGE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 01H [1]
	{ true, "01H", 0x01, "OPERATION", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 02H [2]
	{ true, "02H", 0x02, "ON_OFF_CONFIG", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 03H [3]
	{ true, "03H", 0x03, "CLEAR_FAULTS", cmd_access_write, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 04H [4]
	{ true, "04H", 0x04, "PHASE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 05H [5]
	{ true, "05H", 0x05, "PAGE_PLUS_WRITE", cmd_access_bw, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 06H [6]
	{ true, "06H", 0x06, "PAGE_PLUS_READ", cmd_access_bwr_read, 0, 0, { 0 }, 0x03, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x04, { 0x03, 0x00, 0x1b, 0x7a }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 07H [7]
	{ true, "07H", 0x07, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 08H [8]
	{ true, "08H", 0x08, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 09H [9]
	{ true, "09H", 0x09, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 0AH [10]
	{ true, "0AH", 0x0a, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 0BH [11]
	{ true, "0BH", 0x0b, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 0CH [12]
	{ true, "0CH", 0x0c, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 0DH [13]
	{ true, "0DH", 0x0d, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 0EH [14]
	{ true, "0EH", 0x0e, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 0FH [15]
	{ true, "0FH", 0x0f, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 10H [16]
	{ true, "10H", 0x10, "WRITE_PROTECT", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 11H [17]
	{ true, "11H", 0x11, "STORE_DEFAULT_ALL", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 12H [18]
	{ true, "12H", 0x12, "RESTORE_DEFAULT_ALL", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 13H [19]
	{ true, "13H", 0x13, "STORE_DEFAULT_CODE", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 14H [20]
	{ true, "14H", 0x14, "RESTORE_DEFAULT_CODE", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 15H [21]
	{ true, "15H", 0x15, "STORE_USER_ALL", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 16H [22]
	{ true, "16H", 0x16, "RESTORE_USER_ALL", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 17H [23]
	{ true, "17H", 0x17, "STORE_USER_CODE", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 18H [24]
	{ true, "18H", 0x18, "RESTORE_USER_CODE", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 19H [25]
	{ true, "19H", 0x19, "CAPABILITY", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 1AH [26]
	{ true, "1AH", 0x1a, "QUERY", cmd_access_bwr_read, 0, 0, { 0 }, 0x03, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x87 }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 1BH [27]
	{ true, "1BH", 0x1b, "SMBALERT_MASK", cmd_access_bwr_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x02, { 0x01, 0x7a }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 1CH [28]
	{ true, "1CH", 0x1c, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 1DH [29]
	{ true, "1DH", 0x1d, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 1EH [30]
	{ true, "1EH", 0x1e, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 1FH [31]
	{ true, "1FH", 0x1f, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 20H [32]
	{ true, "20H", 0x20, "VOUT_MODE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL },
	// 21H [33]
	{ true, "21H", 0x21, "VOUT_COMMAND", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 22H [34]
	{ true, "22H", 0x22, "VOUT_TRIM", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 23H [35]
	{ true, "23H", 0x23, "VOUT_CAL_OFFSET", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 24H [36]
	{ true, "24H", 0x24, "VOUT_MAX", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 25H [37]
	{ true, "25H", 0x25, "VOUT_MARGIN_HIGH", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 26H [38]
	{ true, "26H", 0x26, "VOUT_MARGIN_LOW", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 27H [39]
	{ true, "27H", 0x27, "VOUT_TRANSITION_RATE", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 28H [40]
	{ true, "28H", 0x28, "VOUT_DROOP", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 29H [41]
	{ true, "29H", 0x29, "VOUT_SCALE_LOOP", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 2AH [42]
	{ true, "2AH", 0x2A, "VOUT_SCALE_MONITOR", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 2BH [43]
	{ true, "2BH", 0x2B, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 2CH [44]
	{ true, "2CH", 0x2C, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 2DH [45]
	{ true, "2DH", 0x2D, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 2EH [46]
	{ true, "2EH", 0x2E, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 2FH [47]
	{ true, "2FH", 0x2F, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 30H [48]
	{ true, "30H", 0x30, "COEFFICIENTS", cmd_access_bwr_read, 0, 0, { 0 }, 0x07, { 0 }, { cmd_unsupport, cmd_status_not_run, cmd_also_send_write_data, 0x03, { 0x02, DEF_30H_READ_CMD_BYTE, DEF_30H_READ_RW_BYTE }, cmd_no_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 31H [49]
	{ true, "31H", 0x31, "POUT_MAX", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL , { 0 } },
	// 32H [50]
	{ true, "32H", 0x32, "MAX_DUTY", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 33H [51]
	{ true, "33H", 0x33, "FREQUENCY_SWITCH", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 34H [52]
	{ true, "34H", 0x34, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 35H [53]
	{ true, "35H", 0x35, "VIN_ON", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 36H [54]
	{ true, "36H", 0x36, "VIN_OFF", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 37H [55]
	{ true, "37H", 0x37, "INTERLEAVE", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 38H [56]
	{ true, "38H", 0x38, "IOUT_CAL_GAIN", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 39H [57]
	{ true, "39H", 0x39, "IOUT_CAL_OFFSET", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3AH [58]
	{ true, "3AH", 0x3a, "FAN_CONFIG_1_2", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3BH [59]        
	{ true, "3BH", 0x3b, "FAN_COMMAND_1", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3CH [60]        
	{ true, "3CH", 0x3c, "FAN_COMMAND_2", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3DH [61]
	{ true, "3DH", 0x3d, "FAN_CONFIG_3_4", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3EH [62]        
	{ true, "3EH", 0x3e, "FAN_COMMAND_3", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 3FH [63]        
	{ true, "3FH", 0x3f, "FAN_COMMAND_4", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 40H [64]
	{ true, "40H", 0x40, "VOUT_OV_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 41H [65]
	{ true, "41H", 0x41, "VOUT_OV_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 42H [66]
	{ true, "42H", 0x42, "VOUT_OV_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 43H [67]
	{ true, "43H", 0x43, "VOUT_UV_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 44H [68]
	{ true, "44H", 0x44, "VOUT_UV_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 45H [69]
	{ true, "45H", 0x45, "VOUT_UV_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 46H [70]
	{ true, "46H", 0x46, "IOUT_OC_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 47H [71]
	{ true, "47H", 0x47, "IOUT_OC_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 48H [72]
	{ true, "48H", 0x48, "IOUT_OC_LV_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 49H [71]
	{ true, "49H", 0x49, "IOUT_OC_LV_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 4AH [73]
	{ true, "4AH", 0x4a, "IOUT_OC_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 4BH [74]
	{ true, "4bH", 0x4b, "IOUT_UC_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 4CH [75]
	{ true, "4CH", 0x4c, "IOUT_UC_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 4DH [76]
	{ true, "4DH", 0x4d, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 4EH [78]
	{ true, "4EH", 0x4e, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 4FH [79]
	{ true, "4FH", 0x4f, "OT_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 50H [80]
	{ true, "50H", 0x50, "OT_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 51h [81]       
	{ true, "51H", 0x51, "OT_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 52H [82]
	{ true, "52H", 0x52, "UT_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 53H [83]
	{ true, "53H", 0x53, "UT_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 54H [84]
	{ true, "54H", 0x54, "UT_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 55H [85]
	{ true, "55H", 0x55, "VIN_OV_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 56H [86]
	{ true, "56H", 0x56, "VIN_OV_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 57H [87]
	{ true, "57H", 0x57, "VIN_OV_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 58H [88]
	{ true, "58H", 0x58, "VIN_UV_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 59H [89]
	{ true, "59H", 0x59, "VIN_UV_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5AH [90]
	{ true, "5AH", 0x5a, "VIN_UV_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5BH [91]
	{ true, "5BH", 0x5b, "IIN_OC_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5CH [92]
	{ true, "5CH", 0x5c, "IIN_OC_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5Dh [93]        
	{ true, "5DH", 0x5d, "IIN_OC_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5Eh [94]        
	{ true, "5EH", 0x5e, "POWER_GOOD_ON", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 5Fh [95]        
	{ true, "5FH", 0x5f, "POWER_GOOD_OFF", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 60h [96]        
	{ true, "60H", 0x60, "TON_DELAY", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 61h [97]        
	{ true, "61H", 0x61, "TON_RISE", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 62h [98]        
	{ true, "62H", 0x62, "TON_MAX_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 63h [99]        
	{ true, "63H", 0x63, "TON_MAX_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 64h [100]        
	{ true, "64H", 0x64, "TOFF_DELAY", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 65h [101]        
	{ true, "65H", 0x65, "TOFF_FALL", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 66h [102]        
	{ true, "66H", 0x66, "TOFF_MAX_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 67H [103]
	{ true, "67H", 0x67, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 68h [104]        
	{ true, "68H", 0x68, "POUT_OP_FAULT_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 69h [105]        
	{ true, "69H", 0x69, "POUT_OP_FAULT_RESPONSE", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 6Ah [106]        
	{ true, "6AH", 0x6a, "POUT_OP_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 6Bh [107]        
	{ true, "6BH", 0x6b, "PIN_OP_WARN_LIMIT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 6CH [108]
	{ true, "6CH", 0x6c, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 6DH [109]
	{ true, "6DH", 0x6d, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 6EH [110]
	{ true, "6EH", 0x6e, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 6FH [111]
	{ true, "6FH", 0x6f, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 70h [112]
	{ true, "70H", 0x70, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 71H [113]
	{ true, "71H", 0x71, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 72H [114]
	{ true, "72H", 0x72, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 73H [115]
	{ true, "73H", 0x73, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 74H [116]
	{ true, "74H", 0x74, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 75H [117]
	{ true, "75H", 0x75, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 76H [118]
	{ true, "76H", 0x76, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 77H [119]
	{ true, "77H", 0x77, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 78h [120]        
	{ true, "78H", 0x78, "STATUS BYTE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 79h [121]        
	{ true, "79H", 0x79, "STATUS_WORD", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 7Ah [122]        
	{ true, "7AH", 0x7a, "STATUS_VOUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 7Bh [123]   
	{ true, "7BH", 0x7b, "STATUS_IOUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 7Ch [124]        
	{ true, "7CH", 0x7c, "STATUS_INPUT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 7Dh [125]        
	{ true, "7DH", 0x7d, "STATUS_TEMPERATURE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 7Eh [126]       
	{ true, "7EH", 0x7e, "STATUS_CML", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 7Fh [127]       
	{ true, "7FH", 0x7f, "STATUS OTHER", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 80h [128]        
	{ true, "80H", 0x80, "STATUS_MFR_SPECIFIC", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 81h [129]       
	{ true, "81H", 0x81, "STATUS_FAN_1_2", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 82h [130]       
	{ true, "82H", 0x82, "STATUS_FAN_3_4", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 83H [131]
	{ true, "83H", 0x83, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 84H [132]
	{ true, "84H", 0x84, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 85H [133]
	{ true, "85H", 0x85, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 86h [134]        
	{ true, "86H", 0x86, "READ_EIN", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 87h [135]        
	{ true, "87H", 0x87, "READ_EOUT", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 88h [136]        
	{ true, "88H", 0x88, "READ_VIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 89h [137]       
	{ true, "89H", 0x89, "READ_IIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 8Ah [138]        
	{ true, "8AH", 0x8a, "READ_VCAP", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 8Bh [139]   
	{ true, "8Bh", 0x8b, "READ_VOUT(12V)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, 0, { 0, 0 }, cmd_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 8Ch [140]  
	{ true, "8Ch", 0x8c, "READ_IOUT(12V)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0, 0, 0, 0, { 0, 0 }, cmd_need_change_page, 0, cmd_query_not_yet }, { 0 }, NULL, NULL, { 0 } },
	// 8Dh [141]        
	{ true, "8DH", 0x8d, "READ_TEMPERATURE_1(Ambient)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 8Eh [142]        
	{ true, "8EH", 0x8e, "READ_TEMPERATURE_2(Second)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 8Fh [143]        
	{ true, "8FH", 0x8f, "READ_TEMPERATURE_3(Primary)", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 90h [144]        
	{ true, "90H", 0x90, "READ_FAN_SPEED_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 91h [145]       
	{ true, "91H", 0x91, "READ_FAN_SPEED_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 92h [146]       
	{ true, "92H", 0x92, "READ_FAN_SPEED_3", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 93h [147]       
	{ true, "93H", 0x93, "READ_FAN_SPEED_4", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 94h [148]       
	{ true, "94H", 0x94, "READ_DUTY_CYCLE", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 95h [149]       
	{ true, "95H", 0x95, "READ_FREQUENCY", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 96h [150]      
	{ true, "96H", 0x96, "READ_POUT", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 97h [151]        
	{ true, "97H", 0x97, "READ_PIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 98h [152]        
	{ true, "98H", 0x98, "PMBUS_REVISION", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 99h [153]        
	{ true, "99H", 0x99, "MFR_ID", cmd_access_br, 0, 0, { 0 }, 0x07, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 9Ah [154]        
	{ true, "9AH", 0x9a, "MFR_MODEL", cmd_access_br, 0, 0, { 0 }, MFR_MODEL_LENGTH + 2, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 9Bh [155]       
	{ true, "9BH", 0x9b, "MFR_REVISION", cmd_access_br, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 9Ch [156]      
	{ true, "9CH", 0x9c, "MFR_LOCATION", cmd_access_br, 0, 0, { 0 }, 0x05, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 9Dh [157]        
	{ true, "9DH", 0x9d, "MFR_DATE", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 9Eh [158]       
	{ true, "9EH", 0x9e, "MFR_SERIAL", cmd_access_br, 0, 0, { 0 }, 0x1c, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// 9FH [159]
	{ true, "9FH", 0x9f, "APP_PROFILE_SUPPORT", cmd_access_br, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A0h [160]       
	{ true, "A0H", 0xa0, "MFR_VIN_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A1h [161]        
	{ true, "A1H", 0xa1, "MFR_VIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A2h [162]        
	{ true, "A2H", 0xa2, "MFR_IIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A3h [163]       
	{ true, "A3H", 0xa3, "MFR_PIN_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A4h [164]        
	{ true, "A4H", 0xa4, "MFR_VOUT_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A5h [165]        
	{ true, "A5H", 0xa5, "MFR_VOUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A6h [166]        
	{ true, "A6H", 0xa6, "MFR_IOUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A7h [167]        
	{ true, "A7H", 0xa7, "MFR_POUT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A8h [168]      
	{ true, "A8H", 0xa8, "MFR_TAMBIENT_MAX", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// A9h [169]        
	{ true, "A9H", 0xa9, "MFR_TAMBIENT_MIN", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// AAh [170]        
	{ true, "AAH", 0xaa, "MFR_EFFICIENCY_LL", cmd_access_br, 0, 0, { 0 }, 0x10, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// ABh [171]        
	{ true, "ABH", 0xab, "MFR_EFFICIENCY_HL", cmd_access_br, 0, 0, { 0 }, 0x10, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// ACh [172]        
	{ true, "ACH", 0xac, "MFR_PIN_ACCURACY", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// ADh [173]        
	{ true, "ADH", 0xad, "IC_DEVICE_ID", cmd_access_br, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// AEh [174]       
	{ true, "AEH", 0xae, "IC_DEVICE_REV", cmd_access_br, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// AFH [175]
	{ true, "AFH", 0xaf, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B0h [176]        
	{ true, "B0H", 0xb0, "USER_DATA_00", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B1h [177]        
	{ true, "B1H", 0xb1, "USER_DATA_01", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B2h [178]        
	{ true, "B2H", 0xb2, "USER_DATA_02", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [179]        
	{ true, "B3H", 0xb3, "USER_DATA_03", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [180]        
	{ true, "B4H", 0xb4, "USER_DATA_04", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [181]        
	{ true, "B5H", 0xb5, "USER_DATA_05", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [182]        
	{ true, "B6H", 0xb6, "USER_DATA_06", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [183]        
	{ true, "B7H", 0xb7, "USER_DATA_07", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [184]        
	{ true, "B8H", 0xb8, "USER_DATA_08", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [185]        
	{ true, "B9H", 0xb9, "USER_DATA_09", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [186]        
	{ true, "BAH", 0xba, "USER_DATA_10", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [187]        
	{ true, "BBH", 0xbb, "USER_DATA_11", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [188]        
	{ true, "BCH", 0xbc, "USER_DATA_12", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [189]        
	{ true, "BDH", 0xbd, "USER_DATA_13", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [190]        
	{ true, "BEH", 0xbe, "USER_DATA_14", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// B3h [191]        
	{ true, "BFH", 0xbf, "USER_DATA_15", cmd_access_brbw, 0, 0, { 0 }, 0x04, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C0h [192]
	{ true, "C0H", 0xc0, "MFR_MAX_TEMP_1", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C1h [193]
	{ true, "C1H", 0xc1, "MFR_MAX_TEMP_2", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C2h [194]
	{ true, "C2H", 0xc2, "MFR_MAX_TEMP_3", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C3H [195]
	{ true, "C3H", 0xc3, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C4H [196]
	{ true, "C4H", 0xc4, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C5H [197]
	{ true, "C5H", 0xc5, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C6H [198]
	{ true, "C6H", 0xc6, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C7H [199]
	{ true, "C7H", 0xc7, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C8H [200]
	{ true, "C8H", 0xc8, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// C9H [201]
	{ true, "C9H", 0xc9, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// CAH [202]
	{ true, "CAH", 0xca, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// CBH [203]
	{ true, "CBH", 0xcb, "CALIBRATION_WRITE", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// CCH [204]
	{ true, "CCH", 0xcc, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// CDH [205]
	{ true, "CDH", 0xcd, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// CEH [206]
	{ true, "CEH", 0xce, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// CFH [207]
	{ true, "CFH", 0xcf, "Reserverd", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D0h [208]        
	{ true, "D0H", 0xd0, "Cold_Redundancy_Config", cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D1H [209]
	{ true, "D1H", 0xd1, "MFR_SPECIFIC_01", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D2H [210]
	{ true, "D2H", 0xd2, "MFR_SPECIFIC_02", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D3H [211]
	{ true, "D3H", 0xd3, "MFR_SPECIFIC_03", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D4H [212]
	{ true, "D4H", 0xd4, "MFR_SPECIFIC_04", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D5H [213]
	{ true, "D5H", 0xd5, "MFR_SPECIFIC_05", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D6H [214]
	{ true, "D6H", 0xd6, "FW_UPLOAD_MODE", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D7H [215]
	{ true, "D7H", 0xd7, "FW_UPLOAD", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D8H [216]
	{ true, "D8H", 0xd8, "FW_UPLOAD_STATUS", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// D9h [217]
	{ true, "D9H", 0xd9, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// DAH [218]
	{ true, "DAH", 0xda, "MFR_SPECIFIC_10", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// DBH [219]
	{ true, "DBH", 0xdb, "MFR_SPECIFIC_11", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// DCh [220]       
	{ true, "DCH", 0xdc, "Read_BoxSTATUS", cmd_access_br, 0, 0, { 0 }, 0x0C, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// DDH [221]
	{ true, "DDH", 0xdd, "MFR_SPECIFIC_13", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// DEH [222]
	{ true, "DEH", 0xde, "MFR_SPECIFIC_14", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// DFH [223]
	{ true, "DFH", 0xdf, "MFR_SPECIFIC_15", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E0h [224]        
	{ true, "E0H", 0xe0, "PFC_TEMPERATURE_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E1h [225]        
	{ true, "E1H", 0xe1, "PFC_TEMPERATURE_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E2h [226]        
	{ true, "E2H", 0xe2, "SR_TEMPERATURE_1", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E3h [227]        
	{ true, "E3H", 0xe3, "SR_TEMPERATURE_2", cmd_access_read, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E4H [228]
	{ true, "E4H", 0xe4, "MFR_SPECIFIC_20", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E5H [229]
	{ true, "E5H", 0xe5, "MFR_SPECIFIC_21", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E6H [230]
	{ true, "E6H", 0xe6, "MFR_SPECIFIC_22", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E7H [231]
	{ true, "E7H", 0xe7, "MFR_SPECIFIC_23", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E8H [232]
	{ true, "E8H", 0xe8, "MFR_SPECIFIC_24", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// E9H [233]
	{ true, "E9H", 0xe9, "MFR_SPECIFIC_25", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// EAH [234]
	{ true, "EAH", 0xea, "MFR_SPECIFIC_26", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// EBH [235]
	{ true, "EBH", 0xeb, "MFR_SPECIFIC_27", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// ECH [236]
	{ true, "ECH", 0xec, "MFR_SPECIFIC_28", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// EDH [237]
	{ true, "EDH", 0xed, "MFR_SPECIFIC_29", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// EEH [238]
	{ true, "EEH", 0xee, "MFR_SPECIFIC_30", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// EFH [239]
	{ true, "EFH", 0xef, "MFR_SPECIFIC_31", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F0H [240]
	{ true, "F0H", 0xf0, "MFR_SPECIFIC_32", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F1H [241]
	{ true, "F1H", 0xf1, "MFR_SPECIFIC_33", cmd_access_write, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F2H [242]
	{ true, "F2H", 0xf2, "MFR_SPECIFIC_34", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F3H [243]
	{ true, "F3H", 0xf3, "MFR_SPECIFIC_35", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F4H [244]
	{ true, "F4H", 0xf4, "MFR_SPECIFIC_36", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F5H [245]
	{ true, "F5H", 0xf5, "MFR_SPECIFIC_37", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F6H [246]
	{ true, "F6H", 0xf6, "MFR_SPECIFIC_38", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F7H [247]
	{ true, "F7H", 0xf7, "MFR_SPECIFIC_39", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F8H [248]
	{ true, "F8H", 0xf8, "MFR_SPECIFIC_40", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// F9H [249]
	{ true, "F9H", 0xf9, "MFR_SPECIFIC_41", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// FAH [250]
	{ true, "FAH", 0xfa, "MFR_SPECIFIC_42", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// FBH [251]
	{ true, "FBH", 0xfb, "MFR_SPECIFIC_43", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// FCH [252]
	{ true, "FCH", 0xfc, "MFR_SPECIFIC_44", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// FDH [253]
	{ true, "FDH", 0xfd, "MFR_SPECIFIC_45", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// FEH [254]
	{ true, "FEH", 0xfe, "MFR_SPECIFIC_COMMAND_EXT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
	// FFH [255]
	{ true, "FFH", 0xff, "PMBUS_COMMAND_EXT", cmd_access_read, 0, 0, { 0 }, 0x02, { 0 }, { 0 }, { 0 }, NULL, NULL, { 0 } },
};

#define GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMD_TABLE_SIZE  sizeof(g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDTable)/sizeof(PMBUSCOMMAND_t)

#endif
