/**
 * @file ACBEL_RFWE_24_28_1200W_SCP_CBCoefficients.h
 */
#ifndef _ACBEL_RFWE_24_28_1200W_SCP_CBCOEFFICIENTS_H_
#define _ACBEL_RFWE_24_28_1200W_SCP_CBCOEFFICIENTS_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "pec.h"

// Declare Coefficients CB Functions
int ACBEL_RFWE_24_28_1200W_SCP_Coefficients_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Coefficients_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Coefficients_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int ACBEL_RFWE_24_28_1200W_SCP_Coefficients_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif