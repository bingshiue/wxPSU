/**
 * @file GIGABYTE_CRPS001_CBCoefficients.h
 */
#ifndef _GIGABYTE_CRPS001_CBCOEFFICIENTS_H_
#define _GIGABYTE_CRPS001_CBCOEFFICIENTS_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "pec.h"

// Declare Coefficients CB Functions
int GB_CRPS_Coefficients_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int GB_CRPS_Coefficients_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Coefficients_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif