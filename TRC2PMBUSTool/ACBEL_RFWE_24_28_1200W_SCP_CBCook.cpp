/**
 * @file ACBEL_RFWE_24_28_1200W_SCP_CBCook.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSHelper.h"
#include "ACBEL_RFWE_24_28_1200W_SCP_CBCook.h"

static bool Check_Have_CheckSum_Error(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	bool result = false;
	const wchar_t* tmp_wchar;
	wxString wxstr("");

	// CheckSum Error ?
	if (pmbuscmd->m_cmdStatus.m_status == cmd_status_checksum_error){
		wxstr += wxString::Format("CheckSum Error");

		tmp_wchar = wxstr.wc_str();
		lstrcpyn(string, tmp_wchar, 256);

		result = true;
		return result;
	}

	return result;
}

int ACBEL_RFWE_24_28_1200W_SCP_Cook_Not_Implement(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int ACBEL_RFWE_24_28_1200W_SCP_Cook_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Show FW Version
	const wchar_t* tmp_wchar;

	//B6 - F1 - 04 - [1] [2] [3] [4] [pec] : Firmware Version : [1].[2], Reserved : [3].[4]
	wxString wxstr("FW Verion : ");

	wxstr += wxString::Format("%2x.%02x", pmbuscmd->m_recvBuff.m_dataBuff[1], pmbuscmd->m_recvBuff.m_dataBuff[2]);

	//wxstr += wxString::Format("SEC : %02x.%02x", pmbuscmd->m_recvBuff.m_dataBuff[3], pmbuscmd->m_recvBuff.m_dataBuff[4]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

#define DBH_DATA_LENGTH  15
int ACBEL_RFWE_24_28_1200W_SCP_Cook_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	const wchar_t* tmp_wchar;

	wxString wxstr("");

	// First Byte is Block Read Size, Skip
	wxstr += wxString::Format("Adc1:%x,", (pmbuscmd->m_recvBuff.m_dataBuff[1] | (pmbuscmd->m_recvBuff.m_dataBuff[2] << 8)));
	wxstr += wxString::Format("Adc2:%x,", (pmbuscmd->m_recvBuff.m_dataBuff[3] | (pmbuscmd->m_recvBuff.m_dataBuff[4] << 8)));
	wxstr += wxString::Format("Adc3:%x,", (pmbuscmd->m_recvBuff.m_dataBuff[5] | (pmbuscmd->m_recvBuff.m_dataBuff[6] << 8)));
	wxstr += wxString::Format("Adc5:%x,", (pmbuscmd->m_recvBuff.m_dataBuff[7] | (pmbuscmd->m_recvBuff.m_dataBuff[8] << 8)));
	wxstr += wxString::Format("Adc6:%x,", (pmbuscmd->m_recvBuff.m_dataBuff[9] | (pmbuscmd->m_recvBuff.m_dataBuff[10] << 8)));
	wxstr += wxString::Format("Adc7:%x,", (pmbuscmd->m_recvBuff.m_dataBuff[11] | (pmbuscmd->m_recvBuff.m_dataBuff[12] << 8)));
	wxstr += wxString::Format("Adc8:%x",  (pmbuscmd->m_recvBuff.m_dataBuff[13] | (pmbuscmd->m_recvBuff.m_dataBuff[14] << 8)));

	wxstr.UpperCase();

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int ACBEL_RFWE_24_28_1200W_SCP_Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	// Status WORD : 2848h, VOUT_1 : 00h, VOUT_2 : 00h, IOUT_1 : 00h, IOUT_2 : 00h, INPUT : 10h, TEMP : 00h, CML : 00h, OTHER : 00h, FAN12 : 00h   
	// 48 - 28 - 00 - 00 - 00 - 00 - 10 - 00 - 00 - 00 - 00
	const wchar_t* tmp_wchar;
	unsigned short M4821WritePA = (pmbuscmd->m_recvBuff.m_dataBuff[1] | (pmbuscmd->m_recvBuff.m_dataBuff[2] << 8));
	unsigned short TRIM_WRITE_CNT = (pmbuscmd->m_recvBuff.m_dataBuff[3] | (pmbuscmd->m_recvBuff.m_dataBuff[4] << 8));
	unsigned short TRIM_STEP = (pmbuscmd->m_recvBuff.m_dataBuff[5] | (pmbuscmd->m_recvBuff.m_dataBuff[6] << 8));

	wxString wxstr("");

	wxstr += wxString::Format("M4821 Write PA:%x, ", M4821WritePA);
	wxstr += wxString::Format("TRIM Write Count:%d, ", TRIM_WRITE_CNT);
	wxstr += wxString::Format("TRIM Step:%d", TRIM_STEP);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int ACBEL_RFWE_24_28_1200W_SCP_Cook_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	unsigned short SetPoint = (pmbuscmd->m_recvBuff.m_dataBuff[0] | (pmbuscmd->m_recvBuff.m_dataBuff[1] << 8));

	// Show Set Pointer Value
	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Set Point : %04x (%d)", SetPoint, SetPoint);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int ACBEL_RFWE_24_28_1200W_SCP_Cook_Not_Implement(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxT("");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

