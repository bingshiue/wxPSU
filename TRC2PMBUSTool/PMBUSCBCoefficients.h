/**
 * @file PMBUSCBCoefficients.h
 */
#ifndef _PMBUSCBCOEFFICIENTS_H_
#define _PMBUSCBCOEFFICIENTS_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "PEC.h"

// Declare Coefficients CB Functions
int Coefficients_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Coefficients_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

#endif
