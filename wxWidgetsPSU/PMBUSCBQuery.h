/**
 * @file PMBUSCBQuery.h
 */
#ifndef _PMBUSCBQUERY_H_
#define _PMBUSCBQUERY_H_

#include "PMBUSCommandType.h"

// Declare Query CB Functions
int Query_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int Query_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif