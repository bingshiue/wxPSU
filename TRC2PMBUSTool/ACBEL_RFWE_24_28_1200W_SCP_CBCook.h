/**
 * @file ACBEL_RFWE_24_28_1200W_SCP_CBCOOK.h
 */
#ifndef _ACBEL_RFWE_24_28_1200W_SCP_CBCOOK_H_
#define _ACBEL_RFWE_24_28_1200W_SCP_CBCOOK_H_

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"

// Declare Cook CB Functions
int ACBEL_RFWE_24_28_1200W_SCP_Cook_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Cook_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Cook_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif