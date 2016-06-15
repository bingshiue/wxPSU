/**
 * @file PMBUSCBRaw.h
 */
#ifndef _PMBUSCBRAW_H_
#define _PMBUSCBRAW_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"

// Declare Raw CB Functions
int Raw_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_f1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int Raw_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

#endif