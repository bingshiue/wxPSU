/**
 * @file PBF003_00G_CBCook.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSHelper.h"
#include "PBF003_00G_CBCook.h"

static bool Check_Have_CheckSum_Error(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	bool result = false;
	const wchar_t* tmp_wchar;
	wxString wxstr("");

	// CheckSum Error ?
	if (pmbuscmd->m_cmdStatus.m_status == cmd_status_checksum_error){
		wxstr += wxString::Format("CheckSum Error");

		tmp_wchar = wxstr.wc_str();
		COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

		result = true;
		return result;
	}

	return result;
}

int PFB003_00G_Cook_Not_Implement(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);


int PFB003_00G_Cook_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Cook_Not_Implement(pmbuscmd,string,sizeOfstr); }

int PFB003_00G_Cook_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;
	unsigned short latestAdjustCommand= 0;

	wxString wxstr("");

	latestAdjustCommand = (pmbuscmd->m_recvBuff.m_dataBuff[0] << 8 ) | pmbuscmd->m_recvBuff.m_dataBuff[1];

	wxstr += wxString::Format("%04X", latestAdjustCommand);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;

}

int PFB003_00G_Cook_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;
	double inputVoltage = 0;

	wxString wxstr("");

	inputVoltage = (float)((pmbuscmd->m_recvBuff.m_dataBuff[0] << 8 ) | pmbuscmd->m_recvBuff.m_dataBuff[1]);

	inputVoltage /= 100.0f;

	PMBUSHelper::GetPMBusStatus()->SaveVIN(inputVoltage);

	wxstr += wxString::Format("%.2f(V)", inputVoltage);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;
	float inputCurrent = 0;

	wxString wxstr("");

	inputCurrent = (float)((pmbuscmd->m_recvBuff.m_dataBuff[0] << 8 ) | pmbuscmd->m_recvBuff.m_dataBuff[1]);

	inputCurrent /= 10.0f;

	PMBUSHelper::GetPMBusStatus()->SaveIIN(inputCurrent);

	wxstr += wxString::Format("%.2f(A)", inputCurrent);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;
	float outputVoltage = 0;

	wxString wxstr("");

	outputVoltage = (float)((pmbuscmd->m_recvBuff.m_dataBuff[0] << 8 ) | pmbuscmd->m_recvBuff.m_dataBuff[1]);

	outputVoltage /= 10.0f;

	PMBUSHelper::GetPMBusStatus()->SaveVOUT(outputVoltage);

	wxstr += wxString::Format("%.2f(V)", outputVoltage);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;
	float outputCurrent = 0;

	wxString wxstr("");

	outputCurrent = (float)((pmbuscmd->m_recvBuff.m_dataBuff[0] << 8 ) | pmbuscmd->m_recvBuff.m_dataBuff[1]);

	outputCurrent /= 10.0f;

	PMBUSHelper::GetPMBusStatus()->SaveIOUT(outputCurrent);

	wxstr += wxString::Format("%.2f(A)", outputCurrent);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;
	float powerThermal = 0;

	wxString wxstr("");

	powerThermal = (float)((pmbuscmd->m_recvBuff.m_dataBuff[0] << 8 ) | pmbuscmd->m_recvBuff.m_dataBuff[1]);

	powerThermal /= 10.0f;

	wxstr += wxString::Format("%.2f(C)", powerThermal);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Cook_Not_Implement(pmbuscmd,string,sizeOfstr); }

#define STATUS1_BIT_POWER_DOWN            0x08 /**< STATUS 1 BIT POWER DOWN */
#define STATUS1_BIT_THUNDER_PROTECTION    0x04 /**< STATUS 1 BIT THUNDER PROTECTION */
#define STATUS1_BIT_INPUT_OVER_VOLTAGE    0x02 /**< STATUS 1 BIT INPUT OVER VOLTAGE */
#define STATUS1_BIT_INPUT_UNDER_VOLTAGE   0x01 /**< STATUS 1 BIT INPUT UNDER VOLTAGE */

int PFB003_00G_Cook_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const unsigned char status1_array[8] = {
		0x80,
		0x40,
		0x20,
		0x10,
		STATUS1_BIT_POWER_DOWN,
		STATUS1_BIT_THUNDER_PROTECTION,
		STATUS1_BIT_INPUT_OVER_VOLTAGE,
		STATUS1_BIT_INPUT_UNDER_VOLTAGE
	};

	const char *status1_string[8] = {
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"PwD",
		"thP",
		"IOV",
		"IUV",
	};

	const wchar_t* tmp_wchar;
	unsigned char status1 = 0;
	unsigned char status2 = 0;
	static unsigned char previous_status1 = 0;
	bool bFirstError = false;

	status1 = pmbuscmd->m_recvBuff.m_dataBuff[0];
	status2 = pmbuscmd->m_recvBuff.m_dataBuff[1];

	wxString wxstr("STATUS : [ ");

	if(status1 & STATUS1_BIT_INPUT_UNDER_VOLTAGE){
		wxstr += wxString::Format(" IUV");
	}

	if(status1 & STATUS1_BIT_INPUT_OVER_VOLTAGE){
		wxstr += wxString::Format(",");
		wxstr += wxString::Format(" IOV");
	}

	if(status1 & STATUS1_BIT_THUNDER_PROTECTION){
		wxstr += wxString::Format(",");
		wxstr += wxString::Format(" thP");
	}

	if(status1 & STATUS1_BIT_POWER_DOWN){
		wxstr += wxString::Format(",");
		wxstr += wxString::Format(" PwD");
	}

	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);


	if(previous_status1 != status1){


		if (previous_status1 != 0x00){
			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				// If Previous Fail But Clear Now
				if ( ((previous_status1 & status1_array[idx]) == status1_array[idx]) && ((status1 & status1_array[idx]) == 0) ){
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status1_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status1_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%04XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}


		if (status1 != 0x00){

			// Output Fault/Warning MSG to Log
			wxString output = wxString::Format("Assert [%04XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		previous_status1 = status1;

	}


	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Cook_Not_Implement(pmbuscmd,string,sizeOfstr); }
int PFB003_00G_Cook_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return PFB003_00G_Cook_Not_Implement(pmbuscmd,string,sizeOfstr); }

int PFB003_00G_Cook_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Firmware Version : %02X.%02X", pmbuscmd->m_recvBuff.m_dataBuff[0], pmbuscmd->m_recvBuff.m_dataBuff[1]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);


	return EXIT_SUCCESS;
}

int PFB003_00G_Cook_Not_Implement(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxT("");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}
