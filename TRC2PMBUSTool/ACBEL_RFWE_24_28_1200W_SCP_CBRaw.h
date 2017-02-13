/**
 * @file ACBEL_RFWE_24_28_1200W_SCP_CBRaw.h
 */
#ifndef _ACBEL_RFWE_24_28_1200W_SCP_CBRAW_H_
#define _ACBEL_RFWE_24_28_1200W_SCP_CBRAW_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "pec.h"

// Declare Raw CB Functions
int ACBEL_RFWE_24_28_1200W_SCP_Raw_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int ACBEL_RFWE_24_28_1200W_SCP_Raw_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int ACBEL_RFWE_24_28_1200W_SCP_Raw_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int ACBEL_RFWE_24_28_1200W_SCP_Raw_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

#endif