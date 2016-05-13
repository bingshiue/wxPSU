/**
 * @file PMBUSCBCook.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCBCook.h"

int Cook_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}


int Cook_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8d01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_f1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }
int Cook_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return EXIT_SUCCESS; }