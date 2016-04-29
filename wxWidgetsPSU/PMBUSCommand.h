/**
 * @file PMBUSCommand.h
 */
#ifndef _PMBUSCOMMAND_H_
#define _PMBUSCOMMAND_H_

#include "PMBUSCommandType.h"

PMBUSCOMMAND_t g_PMBUSCommand[PMBUSCOMMAND_SIZE] = {
// toggle  Register  Name  Access Query  Cook  Raw  Response  Data Length  RECVBUFF_t
// OOH
	{ true, 0x00, "PAGE",                            cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 } },
// 01H
	{ true, 0x01, "OPERATION",                       cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 } },
// 02H
	{ true, 0x02, "ON_OFF_CONFIG",                   cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 } },
// 03H
	{ true, 0x03, "CLEAR_FAULTS",                    cmd_access_write,     0, 0, { 0 }, 0x05, { 0 } },
// 1BH
	{ true, 0x1b, "SMRALERT_MASK",                   cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 } },
// 20H
	{ true, 0x20, "VOUT_MODE",                       cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 3AH
	{ true, 0x3a, "FAN_CONFIG_1_2",                  cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 } },
// 3BH         
	{ true, 0x3b, "FAN_COMMAND_1",                   cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 } },
// 51h         
	{ true, 0x51, "OT_WARN_LIMIT",                   cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 } },
// 5Dh         
	{ true, 0x5d, "IIN_OC_WARN_LIMIT",               cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 } },
// 6Ah         
	{ true, 0x6a, "POUT_OP_WARN_LIMIT",              cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 } },
// 6Bh         
	{ true, 0x6b, "PIN_OP_WARN_LIMIT",               cmd_access_readwrite, 0, 0, { 0 }, 0x03, { 0 } },
// 78h         
	{ true, 0x78, "STATUS BYTE",                     cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 79h         
	{ true, 0x79, "STATUS WORD",                     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 7Ah         
	{ true, 0x7a, "STATUS VOUT",                     cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 7Bh         
	{ true, 0x7b, "STATUS IOUT",                     cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 7Ch         
	{ true, 0x7c, "STATUS INPUT",                    cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 7Dh         
	{ true, 0x7d, "STATUS TEMPERATURE",              cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 7Eh         
	{ true, 0x7e, "STATUS CML ",                     cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 7Fh         
	{ true, 0x7f, "STATUS OTHER",                    cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 81h         
	{ true, 0x81, "STATUS FAN_1_2",                  cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 86h         
	{ true, 0x86, "READ EIN",                        cmd_access_read,      0, 0, { 0 }, 0x08, { 0 } },
// 87h         
	{ true, 0x87, "READ EOUT",                       cmd_access_read,      0, 0, { 0 }, 0x08, { 0 } },
// 88h         
	{ true, 0x88, "READ VIN",                        cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 89h         
	{ true, 0x89, "READ IIN",                        cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Ah         
	{ true, 0x8a, "READ VCAP",                       cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Bh (00h)   
	{ true, 0x8b, "READ_VOUT(12V)",                  cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Ch (00h)   
	{ true, 0x8c, "READ_IOUT(12V)",                  cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Bh (01h)   
	{ true, 0x8b, "READ_VOUT(12V_SBY)",              cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Ch (01h)   
	{ true, 0x8c, "READ_IOUT(12V_SBY)",              cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Dh         
	{ true, 0x8d, "READ_TEMPERATURE_1(Ambient)",     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Eh         
	{ true, 0x8e, "READ_TEMPERATURE_2(Second)",      cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 8Fh         
	{ true, 0x8f, "READ_TEMPERATURE_3(Primary)",     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 90h         
	{ true, 0x90, "READ_FAN_SPEED_1",                cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 96h         
	{ true, 0x96, "READ_POUT",                       cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 97h         
	{ true, 0x97, "READ_PIN",                        cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// 98h         
	{ true, 0x98, "PMBUS_REVISION",                  cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },
// 99h         
	{ true, 0x99, "MFR_ID",                          cmd_access_brbw,      0, 0, { 0 }, 0x07, { 0 } },
// 9Ah         
	{ true, 0x9a, "MFR_MODEL",                       cmd_access_brbw,      0, 0, { 0 }, 0x0f, { 0 } },
// 9Bh         
	{ true, 0x9b, "MFR_REVISION",                    cmd_access_brbw,      0, 0, { 0 }, 0x05, { 0 } },
// 9Ch         
	{ true, 0x9c, "MFR_LOCATION",                    cmd_access_brbw,      0, 0, { 0 }, 0x05, { 0 } },
// 9Dh         
	{ true, 0x9d, "MFR_DATE",                        cmd_access_brbw,      0, 0, { 0 }, 0x08, { 0 } },
// 9Eh         
	{ true, 0x9e, "MFR_SERIAL",                      cmd_access_brbw,      0, 0, { 0 }, 0x13, { 0 } },
// A0h         
	{ true, 0xa0, "MFR_VIN_MIN",                     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A1h         
	{ true, 0xa1, "MFR_VIN_MAX",                     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A2h         
	{ true, 0xa2, "MFR_IIN_MAX",                     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A3h         
	{ true, 0xa3, "MFR_PIN_MAX",                     cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A4h         
	{ true, 0xa4, "MFR_VOUT_MIN",                    cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A5h         
	{ true, 0xa5, "MFR_VOUT_MAX",                    cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A6h         
	{ true, 0xa6, "MFR_IOUT_MAX",                    cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A7h         
	{ true, 0xa7, "MFR_POUT_MAX",                    cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A8h         
	{ true, 0xa8, "MFR_AMBIENT_MAX",                 cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// A9h         
	{ true, 0xa9, "MFR_AMBIENT_MIN",                 cmd_access_read,      0, 0, { 0 }, 0x03, { 0 } },
// AAh         
	{ true, 0xaa, "MFR_EFFICIENCY_LL",               cmd_access_br,        0, 0, { 0 }, 0x14, { 0 } },
// ABh         
	{ true, 0xab, "MFR_EFFICIENCY_HL",               cmd_access_br,        0, 0, { 0 }, 0x14, { 0 } },
// D0h         
	{ true, 0xd0, "Cold_Redundancy_Config",          cmd_access_readwrite, 0, 0, { 0 }, 0x05, { 0 } },
// DBh         
	{ true, 0xdb, "Read_RealTime",                   cmd_access_read,      0, 0, { 0 }, 0x08, { 0 } },
// DCh         
	{ true, 0xdc, "Read_BoxSTATUS",                  cmd_access_readwrite, 0, 0, { 0 }, 0x0C, { 0 } },
// DDh         
	{ true, 0xdd, "Black_BOX_Index",                 cmd_access_readwrite, 0, 0, { 0 }, 0x05, { 0 } },
// F1h         
	{ true, 0xf1, "Firmware_Version_Command",        cmd_access_br,        0, 0, { 0 }, 0x06, { 0 } },
// FAh         
	{ true, 0xfa, "Firmware_Update_Command",         cmd_access_readwrite, 0, 0, { 0 }, 0x02, { 0 } },
// FCh         
	{ true, 0xfc, "Firmware_Update Status",          cmd_access_read,      0, 0, { 0 }, 0x02, { 0 } },

};

#endif