/**
 * @file GIGABYTE_CRPS001_CBCoefficients.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "GIGABYTE_CRPS001_CBCoefficients.h"

int GB_CRPS_Coefficients_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int GB_CRPS_Coefficients_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Coefficients_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_e0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_e1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_e2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Coefficients_e3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Coefficients_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Coefficients_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	short m, b;
	char R;

	const wchar_t* tmp_wchar;
	int RW;
	RW = pmbuscmd->m_cmdStatus.m_AddtionalData[DEF_30H_READ_RW_INDEX];

	wxString wxstr("");
	//wxstr += wxString::Format("CMD:%02xH,", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);

	switch (RW){

	case rw_write_coefficients:
		wxstr += L"(W)";
		break;

	case rw_read_coefficients:
		wxstr += L"(R)";
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs, RW = %d", RW);
		break;
	}

	wxstr += L" ";

	/*
	[1]	Lower byte of m
	[2]	Upper byte of m
	[3]	Lower byte of b
	[4]	Upper byte of b
	[5]	Single byte of R
	*/
	wxstr += L"m:";

	m = (pmbuscmd->m_recvBuff.m_dataBuff[2] << 8) | pmbuscmd->m_recvBuff.m_dataBuff[1];
	PSU_DEBUG_PRINT(MSG_DEBUG, "m=%d", m);
	wxstr += wxString::Format("%d", m);

	wxstr += L",";
	wxstr += L" b:";

	b = (pmbuscmd->m_recvBuff.m_dataBuff[4] << 8) | pmbuscmd->m_recvBuff.m_dataBuff[3];
	PSU_DEBUG_PRINT(MSG_DEBUG, "b=%d", b);
	wxstr += wxString::Format("%d", b);

	wxstr += L",";
	wxstr += L" R:";

	R = pmbuscmd->m_recvBuff.m_dataBuff[5];
	PSU_DEBUG_PRINT(MSG_DEBUG, "R=%d", R);
	wxstr += wxString::Format("%d", R);

	//
	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	/* Update Direct Data Format in CMD */
	PSU_DEBUG_PRINT(MSG_DEBUG, "Start Update Direct Data Format in CMD");
	// Get Query CMD
	int queryCMD;
	queryCMD = pmbuscmd->m_cmdStatus.m_AddtionalData[DEF_30H_READ_CMD_INDEX];

	// Get Index of Query CMD 
	int queryCMDIndex = -1;
	                                                     // CMD's Page
	queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, sizeOfstr);

#if 0
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == queryCMD){
			queryCMDIndex = idx;
			break;
		}
	}
#endif

	if (queryCMDIndex < 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD, queryCMD = % 02xH, CMD's page=%d", queryCMD, sizeOfstr);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "queryCMDIndex = %d", queryCMDIndex);
	}

	// Set Direct Data Fomat Coefficient
	pmbuscmd_t* target;
	target = PMBUSHelper::getPMBUSCMDData();

	switch (RW){

	case rw_write_coefficients:

		PSU_DEBUG_PRINT(MSG_DEBUG, "Get Write Coefficients");

		target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_M = m;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Write Coefficients m=%d", target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_M);
		target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_B = b;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Write Coefficients b=%d", target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_B);
		target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_R = R;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Write Coefficients R=%d", target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_R);

		break;

	case rw_read_coefficients:

		PSU_DEBUG_PRINT(MSG_DEBUG, "Get Read Coefficients");

		target[queryCMDIndex].m_dataFormat.m_ReadCoefficients.m_M = m;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Read Coefficients m=%d", target[queryCMDIndex].m_dataFormat.m_ReadCoefficients.m_M);
		target[queryCMDIndex].m_dataFormat.m_ReadCoefficients.m_B = b;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Read Coefficients b=%d", target[queryCMDIndex].m_dataFormat.m_ReadCoefficients.m_B);
		target[queryCMDIndex].m_dataFormat.m_ReadCoefficients.m_R = R;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Read Coefficients R=%d", target[queryCMDIndex].m_dataFormat.m_ReadCoefficients.m_R);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs, RW = %d", RW);
		break;
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "End Update Direct Data Format in CMD");

	return EXIT_SUCCESS;
}