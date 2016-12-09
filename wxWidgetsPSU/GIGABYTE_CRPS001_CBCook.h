/**
 * @file GIGABYTE_CRPS001_CBCook.h
 */
#ifndef _GIGABYTE_CRPS001_CBCOOK_H_
#define _GIGABYTE_CRPS001_CBCOOK_H_

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"

// Declare Cook CB Functions
int GB_CRPS_Cook_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_9fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int GB_CRPS_Cook_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_e0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_e1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_e2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int GB_CRPS_Cook_e3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif