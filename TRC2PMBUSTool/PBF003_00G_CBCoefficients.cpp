/**
 * @file PBF003_00G_CBCoefficients.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "PBF003_00G_CBCoefficients.h"

int PFB003_00G_Coefficients_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int PFB003_00G_Coefficients_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0922H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0923H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }
int PFB003_00G_Coefficients_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Coefficients_Common(pmbuscmd, string, sizeOfstr); }

int PFB003_00G_Coefficients_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

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
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

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
