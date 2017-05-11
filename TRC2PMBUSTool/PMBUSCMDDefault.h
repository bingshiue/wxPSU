#ifndef _PMBUSCMDDEFAULT_H_
#define _PMBUSCMDDEFAULT_H_

// 30H COEFFICIENTS
// INDEX
#define DEF_30H_READ_CMD_INDEX      1
#define DEF_30H_READ_RW_INDEX       2

// WRITE
#define DEF_30H_READ_CMD_BYTE    0x86
#define DEF_30H_READ_RW_BYTE     0x01

// 99 MFR_ID
#define MFR_ID_LENGTH            0x05
//#define DEF_MFR_ID               "ACBEL"

// 9A MFR_MODEL
#define MFR_MODEL_LENGTH         0x0b
//#define DEF_MFR_MODEL            "FSG003-000G"

// 9B MFR_REVISION
#define MFR_REVISION_LENGTH      0x03
//#define DEF_MFR_REVISION         "A01"

// 9C MFR_LOCATION
#define MFR_LOCATION_LENGTH      0x03
//#define DEF_MFR_LOCATION         "TWN"

// 9D MFR_DATE
#define MFR_DATE_LENGTH          0x06
//#define DEF_MFR_DATE             "170327"

// 9E MFR_SERIAL
#define MFR_SERIAL_LENGTH        0x18
//#define DEF_MFR_SERIAL           "FSF0590S37LAGT1549000001"


#endif