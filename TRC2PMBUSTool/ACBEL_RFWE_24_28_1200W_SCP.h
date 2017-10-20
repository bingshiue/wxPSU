/**
 * @file ACBEL_RFWE_24_28_1200W_SCP.h
 */
#ifndef _ACBEL_RFWE_24_28_1200W_SCP_H_
#define _ACBEL_RFWE_24_28_1200W_SCP_H_

#include "PMBUSCommandType.h"
#include "PMBUSCMDWritePages.h"

#define ACBEL_RFWE_24_28_1200W_SCP_MODEL_NAME                L"RFWE_24_28_1200W_SCP"
#define ACBEL_RFWE_24_28_1200W_SCP_DEFAULT_I2C_ADDRESS       0xB6
#define ACBEL_RFWE_24_28_1200W_SCP_DEFAULT_CMD_POLLING_TIME  20

PMBUSCOMMAND_t g_ACBEL_RFWE_24_28_1200W_SCP_CMDTable[] = {
	// toggle  Label, Register  Name  Access Query  Cook  Raw  ResponseDataLength  RECVBUFF_t  CMDSTATUS_t CMDCBFUNC_t  wxPanel(Write Page) wxPanel(Read Page) DataFormat_t
	// D9h [0]
	{ true, "D9H", 0xd9, "F.W.Revision", cmd_access_br, 0, 0, { 0 }, 0x06, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// DBh [1]
	{ true, "DBH", 0xdb, "READ_REALTIME", cmd_access_br, 0, 0, { 0 }, 0x10, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// DCh [2]       
	{ true, "DCH", 0xdc, "Read_BoxSTATUS", cmd_access_br, 0, 0, { 0 }, 0x08, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },
	// ECh [3]        
	{ true, "ECH", 0xec, "CALIBRATION_SETPOINT", cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 }, { 0 }, { 0 }, NULL, NULL, {} },


};

#define ACBEL_RFWE_24_28_1200W_SCP_CMD_TABLE_SIZE  sizeof(g_ACBEL_RFWE_24_28_1200W_SCP_CMDTable)/sizeof(PMBUSCOMMAND_t)

#endif