/**
 * @file PMBUSCBCook.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSHelper.h"
#include "PMBUSCBCook.h"

bool Check_Have_CheckSum_Error(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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

int Cook_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 

	// Don't show anything, Due To This Commad's Attribute is 'Write'

	return EXIT_SUCCESS; 
}

int Cook_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[1]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

#define MODE_MASK (0xE0)// 11100000b
#define EXPONENT_MASK (0x1F)// 00011111b
#define SIGN_BIT (0x10) // 00010000b
int Cook_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	const wchar_t* tmp_wchar;
	char *Mode_Name[3] = {
		"Linear",
		"VID",
		"Direct"
	};
	char sign = 0;

	wxString wxstr("");
	// Mode: Linear, Exponent: -4 
	/* 
	Mode     Bits [7:5]    Bits [4:0] (Parameter)
	Linear   000b          Five bit two¡¦s complement exponent for the mantissa
                           delivered as the data bytes for an output voltage related command.

	VID      001b          Five bit VID code identifier per

	Direct   010b          Always set to 00000b
	*/
	unsigned char mode = 0;
	char parameter = 0;

	PSU_DEBUG_PRINT(MSG_ALERT, "Data[0]=%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	mode = pmbuscmd->m_recvBuff.m_dataBuff[0] & MODE_MASK;

	sign = pmbuscmd->m_recvBuff.m_dataBuff[0] & SIGN_BIT;

	if (sign == 0){// positive
		parameter = pmbuscmd->m_recvBuff.m_dataBuff[0] & 0x0f;
	}
	else{ // negative
		parameter = (pmbuscmd->m_recvBuff.m_dataBuff[0] & 0x0f) | 0xf0;
	}

	PSU_DEBUG_PRINT(MSG_ALERT,"Mode=%d, sign=%d, parameter=%d",mode, sign, parameter);

	wxstr += wxString::Format("Mode=%s, Exponent:=%d", Mode_Name[mode], parameter);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	return EXIT_SUCCESS; 
}

#define FAN1_INSTALL_MASK (0x80)
#define FAN1_COMMANDED (0x40)
#define FAN1_REVOLUTION (0x30)

#define FAN2_INSTALL_MASK (0x08)
#define FAN2_COMMANDED (0x04)
#define FAN2_REVOLUTION (0x03)
int Cook_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	const wchar_t* tmp_wchar;
	wxString wxstr("");
	char *install_str[2] = { "", "Install" };
	char *commanded_str[2] = { "Duty Cycle", "RPM" };
	char revolution = 0;
	char rpm = 0;
	char installed = 0;

	// FAN_CONFIG_1_2
	// Fan 1: [2 Pluse, RPM, Install], Fan 2: [1 Pluse, RPM] 
	// B6-3A-B7-D4-8C
	/*
	Bit(s)   Value     Meaning
	7        1         A Fan Is Installed In Position 1
	         0         No Fan Is Installed In Position 1

	6        1         Fan 1 Is Commanded In RPM
	         0         Fan 1 Is Commanded In Duty Cycle

	5:4      00b-11b   Fan 1 Tachometer Pulses Per Revolution
					   00b = 1 pulse per revolution,
					   01b = 2 pulses per revolution,
					   10b = 3 pulses per revolution, and
					   11b = 4 pulses per revolution.


	3        1         A Fan Is Installed In Position 2
	         0         No Fan Is Installed In Position 2

	2        1         Fan 2 Is Commanded In RPM
	         0         Fan 2 Is Commanded In Duty Cycle

	1:0      00b-11b   Fan 2 Tachometer Pulses Per Revolution
					   00b = 1 pulse per revolution,
					   01b = 2 pulses per revolution,
					   10b = 3 pulses per revolution, and
					   11b = 4 pulses per revolution.
	*/

	// FAN1
	wxstr += L"Fan 1: [";
	revolution = (pmbuscmd->m_recvBuff.m_dataBuff[0] & FAN1_REVOLUTION) >> 4;
	wxstr += wxString::Format("%d Pluse, ", revolution + 1);
	rpm = (pmbuscmd->m_recvBuff.m_dataBuff[0] & FAN1_COMMANDED) >> 6;
	wxstr += wxString::Format("%s,", commanded_str[rpm]);
	installed = (pmbuscmd->m_recvBuff.m_dataBuff[0] & FAN1_INSTALL_MASK) >> 7;
	wxstr += wxString::Format(" %s", install_str[installed]);

	wxstr += L"]";
	wxstr += L", Fan 2: [";

	// FAN2
	revolution = (pmbuscmd->m_recvBuff.m_dataBuff[0] & FAN2_REVOLUTION);
	wxstr += wxString::Format("%d Pluse, ", revolution + 1);
	rpm = (pmbuscmd->m_recvBuff.m_dataBuff[0] & FAN2_COMMANDED) >> 2;
	wxstr += wxString::Format("%s", commanded_str[rpm]);
	installed = (pmbuscmd->m_recvBuff.m_dataBuff[0] & FAN2_INSTALL_MASK) >> 3;
	wxstr += wxString::Format(" %s", install_str[installed]);

	wxstr += L"]";

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double rpm = 0;

	wxString wxstr("");

	rpm = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%ld (RPM)", (long)rpm);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 	
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Status: [ ]");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("Fan 1: [], Fan 2 : []");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

//#define FOLLOW_SPEC
int Cook_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	// Energy: 26580, Sample : 2939
	// B6-86-B7-06-D4-67-00-7B-0B-00-05
	const wchar_t* tmp_wchar;
	/*
	The first two bytes are the output of an
	accumulator that continuously sums samples of the instantaneous input power (the
	product of the samples of the input voltage and input current).
	*/
	long accumulator = 0;
	/*
	The next data byte is a ROLLOVER_COUNT for the accumulator. This byte is an
	unsigned integer.
	*/
	unsigned char ROLLOVER_COUNT = 0;
	/*
	The other three data bytes are a 24 bit unsigned integer that counts the number of
	samples of the instantaneous input power.
	*/
	int samples_of_input_power = 0;

#ifdef FOLLOW_SPEC
	int Maximum_Linear_Format_Value = (pow(2.0f, 10) - 1) * pow(2.0f, 15);
#else
	int Maximum_Linear_Format_Value = pow(2.0f, 15); // 32768
#endif

	int Energy_Count = 0;
	/*
	Energy Count = Rollover_Count * Maximum Linear Format Value + Accumulator Value
	Where Maximum Linear Format Value = (2^10 - 1)*(2^15) = 33,521,664
	*/

	wxString wxstr("");
#ifdef FOLLOW_SPEC
	accumulator = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff+1, 2);
#else
	accumulator = pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
#endif

	ROLLOVER_COUNT = pmbuscmd->m_recvBuff.m_dataBuff[3];
	samples_of_input_power = pmbuscmd->m_recvBuff.m_dataBuff[4] | pmbuscmd->m_recvBuff.m_dataBuff[5] << 8 | pmbuscmd->m_recvBuff.m_dataBuff[6] << 16;

	Energy_Count = ROLLOVER_COUNT * Maximum_Linear_Format_Value + accumulator;

	PSU_DEBUG_PRINT(MSG_ALERT, "ROLLOVER_COUNT=%d,Maximum_Linear_Format_Value =%d,accumulator=%d,samples_of_input_power=%d", ROLLOVER_COUNT, Maximum_Linear_Format_Value, accumulator, samples_of_input_power);
	PSU_DEBUG_PRINT(MSG_ALERT, "%02xh", -1);

	wxstr += wxString::Format(" Energy: %d, Sample : %d", Energy_Count, samples_of_input_power);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Energy: 5869, Sample: 2939 
	// B6-87-B7-06-ED-16-00-7B-0B-00-43
	const wchar_t* tmp_wchar;
	/*
	The first two bytes are the output of an
	accumulator that continuously sums samples of the instantaneous input power (the
	product of the samples of the input voltage and input current).
	*/
	long accumulator = 0;
	/*
	The next data byte is a ROLLOVER_COUNT for the accumulator. This byte is an
	unsigned integer.
	*/
	unsigned char ROLLOVER_COUNT = 0;
	/*
	The other three data bytes are a 24 bit unsigned integer that counts the number of
	samples of the instantaneous input power.
	*/
	int samples_of_input_power = 0;

#ifdef FOLLOW_SPEC
	int Maximum_Linear_Format_Value = (pow(2.0f, 10) - 1) * pow(2.0f, 15);
#else
	int Maximum_Linear_Format_Value = pow(2.0f, 15); // 32768
#endif

	int Energy_Count = 0;
	/*
	Energy Count = Rollover_Count * Maximum Linear Format Value + Accumulator Value
	Where Maximum Linear Format Value = (2^10 - 1)*(2^15) = 33,521,664
	*/

	wxString wxstr("");
#ifdef FOLLOW_SPEC
	accumulator = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
#else
	accumulator = pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
#endif

	ROLLOVER_COUNT = pmbuscmd->m_recvBuff.m_dataBuff[3];
	samples_of_input_power = pmbuscmd->m_recvBuff.m_dataBuff[4] | pmbuscmd->m_recvBuff.m_dataBuff[5] << 8 | pmbuscmd->m_recvBuff.m_dataBuff[6] << 16;

	Energy_Count = ROLLOVER_COUNT * Maximum_Linear_Format_Value + accumulator;

	PSU_DEBUG_PRINT(MSG_ALERT, "ROLLOVER_COUNT=%d,Maximum_Linear_Format_Value =%d,accumulator=%d,samples_of_input_power=%d", ROLLOVER_COUNT, Maximum_Linear_Format_Value, accumulator, samples_of_input_power);
	PSU_DEBUG_PRINT(MSG_ALERT, "%02xh", -1);

	wxstr += wxString::Format(" Energy: %d, Sample : %d", Energy_Count, samples_of_input_power);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	// 114.0V (Max:114.0, Min:113.5)
	const wchar_t* tmp_wchar;
	short voltage = 0;

	wxString wxstr("");

	voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dV", voltage);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	// 0.06250A (Max:0.06250, Min:0.06250)
	const wchar_t* tmp_wchar;
	double current = 0;

	wxString wxstr("");

	current = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.5fA", current);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	// 360V (Max:360, Min:360)  
	const wchar_t* tmp_wchar;
	short voltage = 0;

	wxString wxstr("");

	voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dV", voltage);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	return EXIT_SUCCESS; 
}

int Cook_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 26.0C (Max:26.0, Min : 26.0)
	const wchar_t* tmp_wchar;
	short temperature = 0;

	wxString wxstr("");

	temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dC", temperature);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	// 27.0C (Max:27.0, Min:27.0) 	
	const wchar_t* tmp_wchar;
	short temperature = 0;

	wxString wxstr("");

	temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dC", temperature);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	
	// 32C (Max:32, Min:32)
	const wchar_t* tmp_wchar;
	short temperature = 0;

	wxString wxstr("");

	temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dC", temperature);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 7008RPM (Max:7008, Min:7008)
	const wchar_t* tmp_wchar;
	short rpm = 0;

	wxString wxstr("");

	rpm = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dRPM", rpm);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short watt = 0;

	wxString wxstr("");

	watt = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dW", watt);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PMBUSHelper::GetPMBusStatus()->m_POUT = watt;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short watt = 0;

	wxString wxstr("");

	watt = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff,2);

	wxstr += wxString::Format("%dW", watt);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PMBUSHelper::GetPMBusStatus()->m_PIN = watt;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Warning : This was not implemented completely
	// B6-98-B7-22-DE
	// Part I: 1.2, Part II: 1.2

	if (pmbuscmd->m_recvBuff.m_dataBuff[0]==0x22){

		const wchar_t* tmp_wchar;

		wxString wxstr("");

		wxstr += wxString::Format("Part I: 1.2, Part II: 1.2");

		tmp_wchar = wxstr.wc_str();
		lstrcpyn(string, tmp_wchar, 256);

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	}
	
	return EXIT_SUCCESS; 
}

int Cook_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	
	return EXIT_SUCCESS; 
}

int Cook_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short voltage = 0;

	wxString wxstr("");

	voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dV", voltage);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short voltage = 0;

	wxString wxstr("");

	voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dV", voltage);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iin_max = 0;

	wxString wxstr("");

	iin_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.4fA", iin_max);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short watt = 0;

	wxString wxstr("");

	watt = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dW", watt);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double vout_min = 0;

	wxString wxstr("");

	vout_min = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.4fV", vout_min);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double vout_max = 0;

	wxString wxstr("");

	vout_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.4fV", vout_max);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iout_max = 0;

	wxString wxstr("");

	iout_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.4fA", iout_max);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short pout_max = 0;

	wxString wxstr("");

	pout_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dW", pout_max);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int Cook_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%4.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_EFFICIENCY_LL
	// Volt: 115V, 46W, 80%, 92W, 88%, 230W, 92%, 460W, 88%

	const wchar_t* tmp_wchar;
	double result = 0;

	wxString wxstr("Volt: ");

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
	wxstr += wxString::Format(" %ldV,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 3, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 5, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 7, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 9, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 11, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 13, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 15, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 17, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_EFFICIENCY_HL
	// Volt: 230V, 46W, 82%, 92W, 90%, 230W, 94%, 460W, 91%

	const wchar_t* tmp_wchar;
	double result = 0;

	wxString wxstr("Volt: ");

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
	wxstr += wxString::Format(" %ldV,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 3, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 5, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 7, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 9, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 11, 2);

	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 13, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 15, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 17, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%02xh", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

#define DBH_DATA_LENGTH  4
int Cook_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	const wchar_t* tmp_wchar;

	wxString wxstr("");

	for (unsigned int idx = 0; idx < DBH_DATA_LENGTH; idx++){

		wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[idx]);

		if (idx + 1 < DBH_DATA_LENGTH){
			wxstr += wxString::Format("-");
		}
	}

	wxstr.UpperCase();

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	return EXIT_SUCCESS; 
}

int Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	// Status WORD : 2848h, VOUT_1 : 00h, VOUT_2 : 00h, IOUT_1 : 00h, IOUT_2 : 00h, INPUT : 10h, TEMP : 00h, CML : 00h, OTHER : 00h, FAN12 : 00h   
	// 48 - 28 - 00 - 00 - 00 - 00 - 10 - 00 - 00 - 00 - 00
	const wchar_t* tmp_wchar;
	unsigned int status_word = 0;

	wxString wxstr("Status WORD :");

	status_word = pmbuscmd->m_recvBuff.m_dataBuff[0] | pmbuscmd->m_recvBuff.m_dataBuff[1] << 8;
	wxstr += wxString::Format(" %04xh,", status_word);

	wxstr += wxString::Format(" VOUT_1 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[2]);
	wxstr += wxString::Format(" VOUT_2 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[3]);
	wxstr += wxString::Format(" IOUT_1 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[4]);
	wxstr += wxString::Format(" IOUT_2 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[5]);
	wxstr += wxString::Format(" INPUT : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[6]);
	wxstr += wxString::Format(" TEMP : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[7]);
	wxstr += wxString::Format(" CML : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[8]);
	wxstr += wxString::Format(" OTHER : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[9]);
	wxstr += wxString::Format(" FAN12 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[10]);

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());


	return EXIT_SUCCESS; 
}

int Cook_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_f1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}

int Cook_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ 
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS; 
}