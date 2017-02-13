/**
 * @file ACBEL_RFWE_24_28_1200W_SCP_CBQuery.h
 */
#ifndef _ACBEL_RFWE_24_28_1200W_SCP_CBQUERY_H_
#define _ACBEL_RFWE_24_28_1200W_SCP_CBQUERY_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "pec.h"

// Declare Query CB Functions
int ACBEL_RFWE_24_28_1200W_SCP_Query_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Query_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Query_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Query_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif