/**
 * @file GIGABYTE_CRPS001_CBQuery.h
 */
#ifndef _GIGABYTE_CRPS001_CBQUERY_H_
#define _GIGABYTE_CRPS001_CBQUERY_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "pec.h"

// Declare Query CB Functions
int GB_CRPS_Query_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int GB_CRPS_Query_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Query_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif