/**
 * @file GIGABYTE_CRPS001_CBRaw.h
 */
#ifndef _GIGABYTE_CRPS001_CBRAW_H_
#define _GIGABYTE_CRPS001_CBRAW_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "pec.h"

// Declare Raw CB Functions
int GB_CRPS_Raw_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

int GB_CRPS_Raw_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_e0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_e1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_e2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int GB_CRPS_Raw_e3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

#endif