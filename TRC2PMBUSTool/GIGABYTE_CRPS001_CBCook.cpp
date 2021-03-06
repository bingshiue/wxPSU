/**
 * @file GIGABYTE_CRPS001_CBCook.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSHelper.h"
#include "GIGABYTE_CRPS001_CBCook.h"

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

int GB_CRPS_Cook_Not_Implement(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int GB_CRPS_Cook_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	char page = 0;

	wxString wxstr("");

	page = pmbuscmd->m_recvBuff.m_dataBuff[0];
	wxstr += wxString::Format("%d", page);
	PMBUSHelper::GetPMBusStatus()->m_currentPage = page;

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	unsigned char operation = 0;

	wxString wxstr("");

	operation = pmbuscmd->m_recvBuff.m_dataBuff[0];
	wxstr += wxString::Format("%d", operation);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Don't show anything, Due To This Commad's Attribute is 'Write'

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_04H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_07H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_08H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_09H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_0aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_0bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_0cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_0dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_0eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_0fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_10H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_11H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_12H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_13H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_14H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_15H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_16H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_17H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_18H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

#define CMD_SUPPORT_MASK         (0x80)
#define CMD_ACCSSS_WRITE_MASK    (0x40)
#define CMD_ACCSSS_READ_MASK     (0x20)
#define CMD_ACCSSS_FORMAT_MASK   (0x1C)
#define CMD_ACCSSS_RESERVED_MASK (0x03)

int GB_CRPS_Cook_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Bits     Value                 Meaning
	//  7         1           Command is supported
	//	          0           Command is not supported
	//  6         1           Command is supported for write
	//            0           Command is not supported for write
	//  5         1           Command is supported for read
	//	          0           Command is not supported for read
	// 4:2       000          Linear Data Format used
	//           001          16 bit signed number
	//           010          Reserved
	//           011          Direct Mode Format used
	//           100          8 bit unsigned number
	//           101          VID Mode Format used
	//           110          Manufacturer specific format used
	//           111          Command does not return numeric data.This is also used for commands that return blocks of data.
	// 1:0       XXX          Reserved for future use
	unsigned char support = 0;
	unsigned char write = 0;
	unsigned char read = 0;
	unsigned char format = 0;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("CMD:%02xH ", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);
	wxstr.UpperCase();

	// Support
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_SUPPORT_MASK){
		wxstr += wxString::Format("Support, ");
	}
	else{
		wxstr += wxString::Format("Not Support ");

		tmp_wchar = wxstr.wc_str();
		COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

		return EXIT_SUCCESS;
	}

	// Write 
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_READ_MASK){
		wxstr += wxString::Format("Read");
	}
	else{
		wxstr += wxString::Format("");
	}

	// for "/"
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_READ_MASK){
		if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_WRITE_MASK){
			wxstr += wxString::Format("/");
		}
	}

	// Read 
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_WRITE_MASK){
		wxstr += wxString::Format("Write ");
	}
	else{
		wxstr += wxString::Format("");
	}

	wxstr += wxString::Format(",");

	// Data Format
	/* Update Data Format in CMD */
	PSU_DEBUG_PRINT(MSG_DEBUG, "Start Update Data Format in CMD");
	// Get Query CMD
	int queryCMD;
	queryCMD = pmbuscmd->m_cmdStatus.m_AddtionalData[1];

	// Get Index of Query CMD 
	int queryCMDIndex = -1;
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == queryCMD){
			queryCMDIndex = idx;
			break;
		}
	}

	if (queryCMDIndex < 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
		return EXIT_FAILURE;
	}

	// Set Direct Data Fomat Coefficient
	pmbuscmd_t* target;
	target = PMBUSHelper::getPMBUSCMDData();

	PSU_DEBUG_PRINT(MSG_DEBUG, "format=%02x", (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_FORMAT_MASK) >> 2);
	switch ((pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_FORMAT_MASK) >> 2){

	case 0:
		wxstr += wxString::Format("Linear");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_LinearData_Format;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 1:
		wxstr += wxString::Format("16 bit signed");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_16bit_Signed_Number;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 2:
		wxstr += wxString::Format("Reserved");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_Reserved;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 3:
		wxstr += wxString::Format("Direct");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_DirectData_Format;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 4:
		wxstr += wxString::Format("8 bit unsigned");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_8bit_Unsigned_Number;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 5:
		wxstr += wxString::Format("VID Mode");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_VID_Mode;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 6:
		wxstr += wxString::Format("Manufacturer specific format");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_Manufacturer_Specific;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 7:
		wxstr += wxString::Format("Return block datas or Don't return numeric data");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_Don_t_Return_Numeric_Data;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "End Update Data Format in CMD");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	// Call Query Command's Query CB Function
	//wchar_t QueryStr[256];
	//target->m_cmdCBFunc.m_queryCBFunc(&target->m_recvBuff, QueryStr, sizeOfstr);

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	if (pmbuscmd->m_register == 0x1b){
		PSU_DEBUG_PRINT(MSG_DEBUG, "0x1b");
		wxstr += wxString::Format("CMD:%02xH MASK:%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[1], pmbuscmd->m_recvBuff.m_dataBuff[1]);
	}
	else if (pmbuscmd->m_register == 0x06){
		PSU_DEBUG_PRINT(MSG_DEBUG, "0x06");
		wxstr += wxString::Format("CMD:%02xH MASK:%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[3], pmbuscmd->m_recvBuff.m_dataBuff[1]);
	}
	else{
		PSU_DEBUG_PRINT(MSG_ERROR, "Unknow Error Occurs");
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_1cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_1dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_1eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_1fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

#define MODE_MASK (0xE0)// 11100000b
#define EXPONENT_MASK (0x1F)// 00011111b
#define SIGN_BIT (0x10) // 00010000b
int GB_CRPS_Cook_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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
	Linear   000b          Five bit two��s complement exponent for the mantissa
	delivered as the data bytes for an output voltage related command.

	VID      001b          Five bit VID code identifier per

	Direct   010b          Always set to 00000b
	*/
	unsigned char mode = 0;
	char parameter = 0;

	mode = pmbuscmd->m_recvBuff.m_dataBuff[0] & MODE_MASK;

	sign = pmbuscmd->m_recvBuff.m_dataBuff[0] & SIGN_BIT;

	if (sign == 0){// positive
		parameter = pmbuscmd->m_recvBuff.m_dataBuff[0] & 0x0f;
	}
	else{ // negative
		parameter = (pmbuscmd->m_recvBuff.m_dataBuff[0] & 0x0f) | 0xf0;
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "Mode=%d, sign=%d, parameter=%d", mode, sign, parameter);

	PMBUSHelper::GetPMBusStatus()->m_vout_mode_exponent = pow(2.0f, parameter);
	wxstr += wxString::Format("Mode=%s, Exponent:=%d", Mode_Name[mode], parameter);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_21H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_22H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_23H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_24H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_25H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_26H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_27H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_28H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_29H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_2AH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_2BH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_2CH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_2DH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_2EH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_2FH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_32H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_33H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_34H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_35H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_36H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_37H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_38H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_39H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

#define FAN1_INSTALL_MASK (0x80)
#define FAN1_COMMANDED (0x40)
#define FAN1_REVOLUTION (0x30)

#define FAN2_INSTALL_MASK (0x08)
#define FAN2_COMMANDED (0x04)
#define FAN2_REVOLUTION (0x03)
int GB_CRPS_Cook_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	unsigned char* previous_status = &(PMBUSHelper::cmd_3AH_previous);

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
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;
	wxString output_msg("Assert [3AH]: ");
	if (*previous_status != pmbuscmd->m_recvBuff.m_dataBuff[0]){
		output_msg += wxstr;
		PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_msg.c_str());

		*previous_status = pmbuscmd->m_recvBuff.m_dataBuff[0];
	}

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double rpm = 0;

	wxString wxstr("");

	rpm = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%ld (RPM)", (long)rpm);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_3cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_3dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_3eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_3fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_40H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_41H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_42H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_43H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_44H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_45H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iin = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:
		
		iin = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);
		
		break;

	case cmd_data_format_DirectData_Format:

		iin = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%ldA", (long)iin);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}
int GB_CRPS_Cook_47H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_48H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_49H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_4bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_4cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_4dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_4eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_4fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_50H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%4.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}
int GB_CRPS_Cook_52H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_53H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_54H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_55H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_56H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_57H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_58H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_59H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_5aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_5bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_5cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iin = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		iin = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		iin = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%4.4fA", iin);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}
int GB_CRPS_Cook_5eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_5fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_60H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_61H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_62H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_63H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_64H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_65H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_66H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_67H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_68H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_69H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double pout = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		pout = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		pout = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%ldW", (long)pout);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());


	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double pin = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		pin = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		pin = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("Value : %5.2f(W)", pin);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}
int GB_CRPS_Cook_6cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_6dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_6eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_6fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_71H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_72H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_73H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_74H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_75H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_76H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_77H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	
	static unsigned char* previous_status = &(PMBUSHelper::cmd_78H_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_BYTE_BUSY,
		STATUS_BYTE_OFF,
		STATUS_BYTE_VOUT_OV_FAULT,
		STATUS_BYTE_IOUT_OC_FAULT,
		STATUS_BYTE_VIN_UV_FAULT,
		STATUS_BYTE_TEMPERATURE,
		STATUS_BYTE_CML,
		STATUS_BYTE_NONE_OF_THE_ABOVE
	};

	const char *status_string[8] = {
		STATUS_BYTE_BUSY_STRING,
		STATUS_BYTE_OFF_STRING,
		STATUS_BYTE_VOUT_OV_FAULT_STRING,
		STATUS_BYTE_IOUT_OC_FAULT_STRING,
		STATUS_BYTE_VIN_UV_FAULT_STRING,
		STATUS_BYTE_TEMPERATURE_STRING,
		STATUS_BYTE_CML_STRING,
		STATUS_BYTE_NONE_OF_THE_ABOVE_STRING,
	};


	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_byte.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_byte.Save(0xff); // For Test Output

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_BYTE = %02x", PMBUSHelper::GetPMBusStatus()->m_status_byte.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_byte.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_byte.status != *previous_status){
		
		if (*previous_status != 0x00){
			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				// If Previous Fail But Clear Now
				if ( ((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_byte.status & status[idx]) == 0) ){
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}
		
		if (PMBUSHelper::GetPMBusStatus()->m_status_byte.status != 0x00){
			
			// Output Fault/Warning MSG to Log 
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_byte.status;
	}
#if 0
	else{

		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned short* previous_status = &(PMBUSHelper::cmd_79H_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned short status[16] = {
		STATUS_WORD_HIGH_VOUT,
		STATUS_WORD_HIGH_IOUTPOUT,
		STATUS_WORD_HIGH_INPUT,
		STATUS_WORD_HIGH_MFR_SPECIFIC,
		STATUS_WORD_HIGH_POWERGOOD,
		STATUS_WORD_HIGH_FANS,
		STATUS_WORD_HIGH_OTHER,
		STATUS_WORD_HIGH_UNKNOWN,
		STATUS_WORD_LOW_BUSY,
		STATUS_WORD_LOW_OFF,
		STATUS_WORD_LOW_VOUT_OV_FAULT,
		STATUS_WORD_LOW_IOUT_OC_FAULT,
		STATUS_WORD_LOW_VIN_UV_FAULT,
		STATUS_WORD_LOW_TEMPERATURE,
		STATUS_WORD_LOW_CML,
		STATUS_WORD_LOW_NONE_OF_THE_ABOVE
	};

	const char *status_string[16] = {
		STATUS_WORD_HIGH_VOUT_STRING,
		STATUS_WORD_HIGH_IOUTPOUT_STRING,
		STATUS_WORD_HIGH_INPUT_STRING,
		STATUS_WORD_HIGH_MFR_SPECIFIC_STRING,
		STATUS_WORD_HIGH_POWERGOOD_STRING,
		STATUS_WORD_HIGH_FANS_STRING,
		STATUS_WORD_HIGH_OTHER_STRING,
		STATUS_WORD_HIGH_UNKNOWN_STRING,
		STATUS_BYTE_BUSY_LOW_STRING,
		STATUS_BYTE_OF_LOWF_STRING,
		STATUS_BYTE_VOUT_OV_FAULT_LOW_STRING,
		STATUS_BYTE_IOUT_OC_FAULT_LOW_STRING,
		STATUS_BYTE_VIN_UV_FAULT_LOW_STRING,
		STATUS_BYTE_TEMPERATURE_LOW_STRING,
		STATUS_BYTE_CML__LOWSTRING,
		STATUS_BYTE_NONE_OF_THE_ABOVE_LOW_STRING
	};

	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_word.Save(pmbuscmd->m_recvBuff.m_dataBuff[0] | (pmbuscmd->m_recvBuff.m_dataBuff[1] << 8));
	//PMBUSHelper::GetPMBusStatus()->m_status_word.Save(0xffff); // For Test Output

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_WORD = %04x", PMBUSHelper::GetPMBusStatus()->m_status_word.status);

	for (unsigned int idx = 0; idx < 16; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_word.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_word.status != *previous_status){
		
		if (*previous_status != 0x0000){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 16; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_word.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x0000;
		}
		
		if (PMBUSHelper::GetPMBusStatus()->m_status_word.status != 0x0000){
			
			// Output Fault/Warning MSG to Log
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_word.status;
	}
#if 0
	else{

		if (previous_status != 0x0000){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 16; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x0000;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_7AH_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_VOUT_VOUT_OV_FAULT,
		STATUS_VOUT_VOUT_OV_WARNING,
		STATUS_VOUT_VOUT_UV_WARNING,
		STATUS_VOUT_VOUT_UV_FAULT,
		STATUS_VOUT_VOUT_MAX,
		STATUS_VOUT_TON_MAX_FAULT,
		STATUS_VOUT_TOFF_MAX_WARNING,
		STATUS_VOUT_VOUT_Tracking_Error
	};

	const char *status_string[8] = {
		STATUS_VOUT_VOUT_OV_FAULT_STRING,
		STATUS_VOUT_VOUT_OV_WARNING_STRING,
		STATUS_VOUT_VOUT_UV_WARNING_STRING,
		STATUS_VOUT_VOUT_UV_FAULT_STRING,
		STATUS_VOUT_VOUT_MAX_STRING,
		STATUS_VOUT_TON_MAX_FAULT_STRING,
		STATUS_VOUT_TOFF_MAX_WARNING_STRING,
		STATUS_VOUT_VOUT_Tracking_Error_STRING
	};

	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_vout.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_vout.Save(0xff); // For Test Output

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_VOUT = %02x", PMBUSHelper::GetPMBusStatus()->m_status_vout.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_vout.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_vout.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 8; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_vout.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH] : ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}
		
		if (PMBUSHelper::GetPMBusStatus()->m_status_vout.status != 0x00){
			
			// Output Fault/Warning MSG to Log
			wxString output = wxString::Format("Assert [%02XH] : ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_vout.status;
	}
#if 0
	else{

		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}

	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_7BH_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_IOUT_IOUT_OC_FAULT,
		STATUS_IOUT_IOUT_OC_LV_FAULT,
		STATUS_IOUT_IOUT_OC_WARNING,
		STATUS_IOUT_IOUT_UC_FAULT,
		STATUS_IOUT_Current_Share_Fault,
		STATUS_IOUT_In_Power_Limiting_Mode,
		STATUS_IOUT_POUT_OP_FAULT,
		STATUS_IOUT_POUT_OP_WARNING
	};

	const char *status_string[8] = {
		STATUS_IOUT_IOUT_OC_FAULT_STRING,
		STATUS_IOUT_IOUT_OC_LV_FAULT_STRING,
		STATUS_IOUT_IOUT_OC_WARNING_STRING,
		STATUS_IOUT_IOUT_UC_FAULT_STRING,
		STATUS_IOUT_Current_Share_Fault_STRING,
		STATUS_IOUT_In_Power_Limiting_Mode_STRING,
		STATUS_IOUT_POUT_OP_FAULT_STRING,
		STATUS_IOUT_POUT_OP_WARNING_STRING
	};


	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");


	PMBUSHelper::GetPMBusStatus()->m_status_iout.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_iout.Save(0xff); // For Test Output

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_IOUT = %02x", PMBUSHelper::GetPMBusStatus()->m_status_iout.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_iout.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_iout.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 8; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_iout.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}

		if (PMBUSHelper::GetPMBusStatus()->m_status_iout.status != 0x00){
			
			// Output Fault/Warning MSG to Log
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_iout.status;
	}
#if 0
	else{
		
		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_7CH_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_INPUT_VIN_OV_FAULT,
		STATUS_INPUT_VIN_OV_WARNING,
		STATUS_INPUT_VIN_UV_WARNING,
		STATUS_INPUT_VIN_UV_FAULT,
		STATUS_INPUT_Unit_Off_For_Insufficient_Input_Voltage,
		STATUS_INPUT_IIN_OC_FAULT,
		STATUS_INPUT_IIN_OC_WARNING,
		STATUS_INPUT_PIN_OP_WARNING
	};

	const char *status_string[8] = {
		STATUS_INPUT_VIN_OV_FAULT_STRING,
		STATUS_INPUT_VIN_OV_WARNING_STRING,
		STATUS_INPUT_VIN_UV_WARNING_STRING,
		STATUS_INPUT_VIN_UV_FAULT_STRING,
		STATUS_INPUT_Unit_Off_For_Insufficient_Input_Voltage_STRING,
		STATUS_INPUT_IIN_OC_FAULT_STRING,
		STATUS_INPUT_IIN_OC_WARNING_STRING,
		STATUS_INPUT_PIN_OP_WARNING_STRING
	};


	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_input.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_input.Save(0xff); // For Test Output

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_INPUT = %02x", PMBUSHelper::GetPMBusStatus()->m_status_input.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_input.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_input.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 8; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_input.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}

		
		if (PMBUSHelper::GetPMBusStatus()->m_status_input.status != 0x00){
			// Output MSG to Log 
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_input.status;
	}
#if 0
	else{
		
		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_7DH_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_TEMPERATURE_OT_FAULT,
		STATUS_TEMPERATURE_OT_WARNING,
		STATUS_TEMPERATURE_UT_WARNING,
		STATUS_TEMPERATURE_UT_FAULT,
		STATUS_TEMPERATURE_Reserved_3,
		STATUS_TEMPERATURE_Reserved_2,
		STATUS_TEMPERATURE_Reserved_1,
		STATUS_TEMPERATURE_Reserved_0
	};

	const char *status_string[8] = {
		STATUS_TEMPERATURE_OT_FAULT_STRING,
		STATUS_TEMPERATURE_OT_WARNING_STRING,
		STATUS_TEMPERATURE_UT_WARNING_STRING,
		STATUS_TEMPERATURE_UT_FAULT_STRING,
		STATUS_TEMPERATURE_Reserved_3_STRING,
		STATUS_TEMPERATURE_Reserved_2_STRING,
		STATUS_TEMPERATURE_Reserved_1_STRING,
		STATUS_TEMPERATURE_Reserved_0_STRING
	};

	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_temperature.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_temperature.Save(0xff); // For Test Output

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_TEMPERATURE = %02x", PMBUSHelper::GetPMBusStatus()->m_status_temperature.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_temperature.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_temperature.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 8; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_temperature.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}
		
		if (PMBUSHelper::GetPMBusStatus()->m_status_temperature.status != 0x00){
			
			// Output Fault/Warning MSG to Log 
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_temperature.status;
	}
#if 0
	else{

		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_7EH_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_CML_Invalid_Or_Unsupported_Command_Received,
		STATUS_CML_Invalid_Or_Unsupported_Data_Received,
		STATUS_CML_Packet_Error_Check_Failed,
		STATUS_CML_Memory_Fault_Detected,
		STATUS_CML_Processor_Fault_Detected,
		STATUS_CML_Reserved,
		STATUS_CML_A_communication_fault,
		STATUS_CML_Other_Memory_Or_Logic_Fault
	};

	const char *status_string[8] = {
		STATUS_CML_Invalid_Or_Unsupported_Command_Received_STRING,
		STATUS_CML_Invalid_Or_Unsupported_Data_Received_STRING,
		STATUS_CML_Packet_Error_Check_Failed_STRING,
		STATUS_CML_Memory_Fault_Detected_STRING,
		STATUS_CML_Processor_Fault_Detected_STRING,
		STATUS_CML_Reserved_STRING,
		STATUS_CML_A_communication_fault_STRING,
		STATUS_CML_Other_Memory_Or_Logic_Fault_STRING
	};

	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_cml.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_cml.Save(0xff);

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_CML = %02x", PMBUSHelper::GetPMBusStatus()->m_status_cml.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_cml.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_cml.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 8; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_cml.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}

		if (PMBUSHelper::GetPMBusStatus()->m_status_cml.status != 0x00){
			
			// Output Fault/Warning MSG to Log
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_cml.status;
	}
#if 0
	else{
		
		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_7FH_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_OTHER_Reserved_2,
		STATUS_OTHER_Reserved_1,
		STATUS_OTHER_Input_A_Fuse_Or_Circuit_Breaker_Fault,
		STATUS_OTHER_Input_B_Fuse_Or_Circuit_Breaker_Fault,
		STATUS_OTHER_Input_A_ORing_Device_Fault,
		STATUS_OTHER_Input_B_ORing_Device_Fault,
		STATUS_OTHER_Output_ORing_Device_Fault,
		STATUS_OTHER_Reserved_0
	};

	const char *status_string[8] = {
		STATUS_OTHER_Reserved_2_STRING,
		STATUS_OTHER_Reserved_1_STRING,
		STATUS_OTHER_Input_A_Fuse_Or_Circuit_Breaker_Fault_STRING,
		STATUS_OTHER_Input_B_Fuse_Or_Circuit_Breaker_Fault_STRING,
		STATUS_OTHER_Input_A_ORing_Device_Fault_STRING,
		STATUS_OTHER_Input_B_ORing_Device_Fault_STRING,
		STATUS_OTHER_Output_ORing_Device_Fault_STRING,
		STATUS_OTHER_Reserved_0_STRING
	};


	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Status: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_other.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_other.Save(0xff);

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_OTHER = %02x", PMBUSHelper::GetPMBusStatus()->m_status_other.status);

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_other.status & status[idx]) == status[idx]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[idx]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[idx]);
			}
		}
	}
	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_other.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("Status: [ ");
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < 8; idx++){
				if (((*previous_status & status[idx]) == status[idx]) && ((PMBUSHelper::GetPMBusStatus()->m_status_other.status & status[idx]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}

		
		if (PMBUSHelper::GetPMBusStatus()->m_status_other.status != 0x00){
			
			// Output Fault/Warning MSG to Log 
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_other.status;
	}
#if 0
	else{
		
		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			bFirstError = false;

			clear_string += wxString::Format("CLEAR Status: [ ");

			for (unsigned int idx = 0; idx < 8; idx++){
				if ((previous_status & status[idx]) == status[idx]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[idx]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[idx]);
					}
				}
			}

			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}


int GB_CRPS_Cook_80H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	static unsigned char* previous_status = &(PMBUSHelper::cmd_81H_previous);//0x00;

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const unsigned char status[8] = {
		STATUS_FAN_1_2_Fan_1_Fault,
		STATUS_FAN_1_2_Fan_2_Fault,
		STATUS_FAN_1_2_Fan_1_Warning,
		STATUS_FAN_1_2_Fan_2_Warning,
		STATUS_FAN_1_2_Fan_1_Speed_Overridden,
		STATUS_FAN_1_2_Fan_2_Speed_Overridden,
		STATUS_FAN_1_2_Airflow_Fault,
		STATUS_FAN_1_2_Airflow_Warning
	};

	const char *status_string[8] = {
		STATUS_FAN_1_2_Fan_1_Fault_STRING,
		STATUS_FAN_1_2_Fan_2_Fault_STRING,
		STATUS_FAN_1_2_Fan_1_Warning_STRING,
		STATUS_FAN_1_2_Fan_2_Warning_STRING,
		STATUS_FAN_1_2_Fan_1_Speed_Overridden_STRING,
		STATUS_FAN_1_2_Fan_2_Speed_Overridden_STRING,
		STATUS_FAN_1_2_Airflow_Fault_STRING,
		STATUS_FAN_1_2_Airflow_Warning_STRING
	};

	char fan_1_check[5] = { 0, 2, 4, 6, 7 };
	char fan_2_check[5] = { 1, 3, 5, 6, 7 };

	const wchar_t* tmp_wchar;
	wxString wxstr("");
	bool bFirstError = false;
	wxstr += wxString::Format("Fan 1: [ ");

	PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.Save(pmbuscmd->m_recvBuff.m_dataBuff[0]);
	//PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.Save(0xff); // For Test Output Meaasges

	PSU_DEBUG_PRINT(MSG_DEBUG, "STATUS_FAN_1_2 = %02x", PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status);

	for (unsigned int idx = 0; idx < sizeof(fan_1_check) / sizeof(fan_1_check[0]); idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status & status[fan_1_check[idx]]) == status[fan_1_check[idx]]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[fan_1_check[idx]]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[fan_1_check[idx]]);
			}
		}
	}

	wxstr += wxString::Format(" ], Fan 2 : [ ");

	for (unsigned int idx = 0; idx < sizeof(fan_1_check) / sizeof(fan_1_check[0]); idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status & status[fan_2_check[idx]]) == status[fan_2_check[idx]]) {
			if (bFirstError == false){
				wxstr += wxString::Format(" %s ", status_string[fan_2_check[idx]]);
				bFirstError = true;
			}
			else{
				wxstr += wxString::Format(", %s ", status_string[fan_2_check[idx]]);
			}
		}
	}

	wxstr += wxString::Format(" ]");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	if (PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status != *previous_status){
		
		if (*previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			clear_string += wxString::Format("Fan 1: [ ");
			bFirstError = false;
			// If Previous Fail But Clear Now
			for (unsigned int idx = 0; idx < sizeof(fan_1_check) / sizeof(fan_1_check[0]); idx++){
				if (((*previous_status & status[fan_1_check[idx]]) == status[fan_1_check[idx]]) && ((PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status & status[fan_1_check[idx]]) == 0)) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[fan_1_check[idx]]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[fan_1_check[idx]]);
					}
				}
			}

			wxstr += wxString::Format(" ], Fan 2 : [ ");

			for (unsigned int idx = 0; idx < sizeof(fan_1_check) / sizeof(fan_1_check[0]); idx++){
				if ((*previous_status & status[fan_2_check[idx]]) == status[fan_2_check[idx]]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[fan_2_check[idx]]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[fan_2_check[idx]]);
					}
				}
			}


			clear_string += wxString::Format(" ]");

			// Output MSG to Log If Have Clear Status
			if (bFirstError == true){
				wxString output_clear_string = wxString::Format("De-Assert [%02XH]: ", pmbuscmd->m_register);
				output_clear_string += clear_string;
				PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());
			}

			//previous_status = 0x00;
		}

		if (PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status != 0x00){
			
			// Output Fault/Warning MSG to Log 
			wxString output = wxString::Format("Assert [%02XH]: ", pmbuscmd->m_register);
			output += wxstr;
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", output.c_str());
		}

		*previous_status = PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status;
	}
#if 0
	else{
		
		if (previous_status != 0x00){

			// Print Clear XXX Messages
			wxString clear_string("");
			clear_string += wxString::Format("CLEAR Fan 1: [ ");
			bFirstError = false;

			for (unsigned int idx = 0; idx < sizeof(fan_1_check) / sizeof(fan_1_check[0]); idx++){
				if ((previous_status & status[fan_1_check[idx]]) == status[fan_1_check[idx]]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[fan_1_check[idx]]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[fan_1_check[idx]]);
					}
				}
			}

			wxstr += wxString::Format(" ], Fan 2 : [ ");

			for (unsigned int idx = 0; idx < sizeof(fan_1_check) / sizeof(fan_1_check[0]); idx++){
				if ((previous_status & status[fan_2_check[idx]]) == status[fan_2_check[idx]]) {
					if (bFirstError == false){
						clear_string += wxString::Format(" %s ", status_string[fan_2_check[idx]]);
						bFirstError = true;
					}
					else{
						clear_string += wxString::Format(", %s ", status_string[fan_2_check[idx]]);
					}
				}
			}


			clear_string += wxString::Format(" ]");

			// Output MSG to Log 
			wxString output_clear_string = wxString::Format("[%02xH]:", pmbuscmd->m_register);
			output_clear_string += clear_string;
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", output_clear_string.c_str());

			previous_status = 0x00;
		}
	}
#endif

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_82H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_83H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_84H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_85H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

//#define GB_CRPS_Cook_86H_FOLLOW_SPEC
int GB_CRPS_Cook_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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


	int Maximum_Linear_Format_Value;
	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format :
		Maximum_Linear_Format_Value = (pow(2.0f, 10) - 1) * pow(2.0f, 15);
		break;

	case cmd_data_format_DirectData_Format :
		Maximum_Linear_Format_Value = pow(2.0f, 15) - 1; // 32767
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

#if 0
#ifdef GB_CRPS_Cook_86H_FOLLOW_SPEC
	int Maximum_Linear_Format_Value = (pow(2.0f, 10) - 1) * pow(2.0f, 15);
#else
	int Maximum_Linear_Format_Value = pow(2.0f, 15) - 1; // 32767
#endif
#endif

	unsigned long long Energy_Count = 0;
	/*
	Energy Count = Rollover_Count * Maximum Linear Format Value + Accumulator Value
	Where Maximum Linear Format Value = (2^10 - 1)*(2^15) = 33,521,664
	*/

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format :
		accumulator = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
		break;

	case cmd_data_format_DirectData_Format:
		accumulator = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2, pmbuscmd);
		              //pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_dataFormat.m_formatType);
		break;
	}


#if 0
#ifdef GB_CRPS_Cook_86H_FOLLOW_SPEC
	accumulator = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
#else
	accumulator = pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
#endif
#endif

	ROLLOVER_COUNT = pmbuscmd->m_recvBuff.m_dataBuff[3];
	samples_of_input_power = pmbuscmd->m_recvBuff.m_dataBuff[4] | pmbuscmd->m_recvBuff.m_dataBuff[5] << 8 | pmbuscmd->m_recvBuff.m_dataBuff[6] << 16;

	Energy_Count = (unsigned long long)ROLLOVER_COUNT * (unsigned long long)Maximum_Linear_Format_Value + accumulator;

	PSU_DEBUG_PRINT(MSG_DEBUG, "ROLLOVER_COUNT=%d,Maximum_Linear_Format_Value =%d,accumulator=%ld,samples_of_input_power=%d", ROLLOVER_COUNT, Maximum_Linear_Format_Value, accumulator, samples_of_input_power);
	//PSU_DEBUG_PRINT(MSG_DEBUG, "%02xh", -1);

	wxstr += wxString::Format("Energy: %llu, Sample : %d", Energy_Count, samples_of_input_power);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

//#define GB_CRPS_Cook_87H_FOLLOW_SPEC
int GB_CRPS_Cook_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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

	int Maximum_Linear_Format_Value;
	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format :
		Maximum_Linear_Format_Value = (pow(2.0f, 10) - 1) * pow(2.0f, 15);
		break;

	case cmd_data_format_DirectData_Format:
		Maximum_Linear_Format_Value = pow(2.0f, 15) - 1; // 32767
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
}

#if 0
#ifdef GB_CRPS_Cook_87H_FOLLOW_SPEC
	int Maximum_Linear_Format_Value = (pow(2.0f, 10) - 1) * pow(2.0f, 15);
#else
	int Maximum_Linear_Format_Value = pow(2.0f, 15) -1; // 32767
#endif
#endif

	unsigned long long Energy_Count = 0;
	/*
	Energy Count = Rollover_Count * Maximum Linear Format Value + Accumulator Value
	Where Maximum Linear Format Value = (2^10 - 1)*(2^15) = 33,521,664
	*/

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format :
		accumulator = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
		break;

	case cmd_data_format_DirectData_Format:
		accumulator = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2, pmbuscmd);
		//pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_dataFormat.m_formatType);
		break;
}

#if 0
#ifdef GB_CRPS_Cook_87H_FOLLOW_SPEC
	accumulator = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 1, 2);
#else
	accumulator = pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
#endif
#endif

	ROLLOVER_COUNT = pmbuscmd->m_recvBuff.m_dataBuff[3];
	samples_of_input_power = pmbuscmd->m_recvBuff.m_dataBuff[4] | pmbuscmd->m_recvBuff.m_dataBuff[5] << 8 | pmbuscmd->m_recvBuff.m_dataBuff[6] << 16;

	Energy_Count = (unsigned long long)ROLLOVER_COUNT * (unsigned long long)Maximum_Linear_Format_Value + accumulator;

	PSU_DEBUG_PRINT(MSG_DEBUG, "ROLLOVER_COUNT=%d,Maximum_Linear_Format_Value =%d,accumulator=%ld,samples_of_input_power=%d", ROLLOVER_COUNT, Maximum_Linear_Format_Value, accumulator, samples_of_input_power);
	//PSU_DEBUG_PRINT(MSG_DEBUG, "%02xh", -1);

	wxstr += wxString::Format("Energy: %llu, Sample : %d", Energy_Count, samples_of_input_power);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 114.0V (Max:114.0, Min:113.5)
	const wchar_t* tmp_wchar;
	double voltage = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		voltage = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveVIN(voltage);
	//  (Max:114.0, Min:113.5)
	wxstr += wxString::Format("%4.5fV (Max:%4.1f, Min:%4.1f)", voltage, PMBUSHelper::GetPMBusStatus()->m_VIN_Max, PMBUSHelper::GetPMBusStatus()->m_VIN_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 0.06250A (Max:0.06250, Min:0.06250)
	const wchar_t* tmp_wchar;
	double current = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		current = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		current = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveIIN(current);

	wxstr += wxString::Format("%4.5fA (Max:%4.5f, Min:%4.5f)", current, PMBUSHelper::GetPMBusStatus()->m_IIN_Max, PMBUSHelper::GetPMBusStatus()->m_IIN_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 360V (Max:360, Min:360)  
	const wchar_t* tmp_wchar;
	double voltage = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		voltage = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveVCAP(voltage);

	wxstr += wxString::Format("%.2fV (Max:%.2f, Min:%.2f)", voltage, PMBUSHelper::GetPMBusStatus()->m_VCAP_Max, PMBUSHelper::GetPMBusStatus()->m_VCAP_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double voltage = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		voltage = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	voltage *= PMBUSHelper::GetPMBusStatus()->m_vout_mode_exponent;

	PMBUSHelper::GetPMBusStatus()->SaveVOUT(voltage);
	// 12.0625V (Max:12.19, Min:12.06) 
	wxstr += wxString::Format("%4.4fV (Max:%4.2f, Min:%4.2f)", voltage, PMBUSHelper::GetPMBusStatus()->m_VOUT_Max, PMBUSHelper::GetPMBusStatus()->m_VOUT_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double current = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		current = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		current = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveIOUT(current);
	// 0.000A (Max:0.484, Min:0.000) 
	wxstr += wxString::Format("%4.3fA (Max:%4.3f, Min:%4.3f)", current, PMBUSHelper::GetPMBusStatus()->m_IOUT_Max, PMBUSHelper::GetPMBusStatus()->m_IOUT_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double voltage = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		voltage = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	voltage *= PMBUSHelper::GetPMBusStatus()->m_vout_mode_exponent;

	PMBUSHelper::GetPMBusStatus()->SaveVoSBY(voltage);

	// 12.1875V (Max:12.19, Min:12.06)  
	wxstr += wxString::Format("%4.4fV (Max:%4.2f, Min:%4.2f)", voltage, PMBUSHelper::GetPMBusStatus()->m_VoSBY_Max, PMBUSHelper::GetPMBusStatus()->m_VoSBY_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double current = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		current = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		current = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveIoSBY(current);
	// 0.000A (Max:0.484, Min:0.000) 
	wxstr += wxString::Format("%4.8fA (Max:%4.3f, Min:%4.3f)", current, PMBUSHelper::GetPMBusStatus()->m_IoSBY_Max, PMBUSHelper::GetPMBusStatus()->m_IoSBY_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 26.0C (Max:26.0, Min : 26.0)
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveAMD_8D(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_AMD_8D_Max, PMBUSHelper::GetPMBusStatus()->m_AMD_8D_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 27.0C (Max:27.0, Min:27.0) 	
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveSEC_8E(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_SEC_8E_Max, PMBUSHelper::GetPMBusStatus()->m_SEC_8E_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 32C (Max:32, Min:32)
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SavePRI_8F(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_PRI_8F_Max, PMBUSHelper::GetPMBusStatus()->m_PRI_8F_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 7008RPM (Max:7008, Min:7008)
	const wchar_t* tmp_wchar;
	double rpm = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		rpm = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		rpm = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2,pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveFAN1(rpm);

	wxstr += wxString::Format("%4.0fRPM (Max:%4.0f, Min:%4.0f)", rpm, PMBUSHelper::GetPMBusStatus()->m_FAN1_Max, PMBUSHelper::GetPMBusStatus()->m_FAN1_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_92H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_93H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_94H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_95H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double watt = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		watt = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		watt = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2,pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}	
	
	PMBUSHelper::GetPMBusStatus()->SavePOUT(watt);

	wxstr += wxString::Format("%4.2fW (Max:%4.1f, Min:%4.1f)", watt, PMBUSHelper::GetPMBusStatus()->m_POUT_Max, PMBUSHelper::GetPMBusStatus()->m_POUT_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double watt = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		watt = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		watt = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SavePIN(watt);

	wxstr += wxString::Format("%4.2fW (Max:%4.1f, Min:%4.1f)", watt, PMBUSHelper::GetPMBusStatus()->m_PIN_Max, PMBUSHelper::GetPMBusStatus()->m_PIN_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

#define PART_I_MASK (0xE0)
#define PART_II_MASK (0x0F)
#define REVISION_1_0 (0x00)
#define REVISION_1_1 (0x01)
#define REVISION_1_2 (0x02)
int GB_CRPS_Cook_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	wxString wxstr("");
	/*
	Bits [7:5] Part I Revision  Bits [3:0] Part II Revision
	0000           1.0            0000         1.0
	0001           1.1            0001         1.1
	0002           1.2            0002         1.2
	*/

	// B6-98-B7-22-DE
	// Part I: 1.2, Part II: 1.2
	unsigned char part_I = 0, part_II = 0;
	part_I = pmbuscmd->m_recvBuff.m_dataBuff[0] & PART_I_MASK >> 4;

	part_II = pmbuscmd->m_recvBuff.m_dataBuff[0] & PART_II_MASK;

	PSU_DEBUG_PRINT(MSG_DETAIL, "part_I=%d, part_II= %d", part_I, part_II);

	switch (part_I){

	case REVISION_1_0:
		wxstr += wxString::Format("Part I: %s, ", "1.0");
		break;

	case REVISION_1_1:
		wxstr += wxString::Format("Part I: %s, ", "1.1");
		break;

	case REVISION_1_2:
		wxstr += wxString::Format("Part I: %s, ", "1.2");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs, part_I = %d", part_I);
		break;
	}

	switch (part_II){

	case REVISION_1_0:
		wxstr += wxString::Format("Part II: %s", "1.0");
		break;

	case REVISION_1_1:
		wxstr += wxString::Format("Part II: %s", "1.1");
		break;

	case REVISION_1_2:
		wxstr += wxString::Format("Part II: %s", "1.2");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs, part_II= %d", part_II);
		break;
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_ID
	const wchar_t* tmp_wchar;

	wxString wxstr("ID: ");

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	for (int idx = 0; idx < pmbuscmd->m_recvBuff.m_dataBuff[0]; idx++){
		// If ASCII Character ?
		if (pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] >= 0 && pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] <= 127){
			wxstr += wxString::Format("%c", pmbuscmd->m_recvBuff.m_dataBuff[1 + idx]);
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_MODEL
	const wchar_t* tmp_wchar;

	wxString wxstr(wxT("MODEL: "));

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	for (int idx = 0; idx < pmbuscmd->m_recvBuff.m_dataBuff[0]; idx++){
		// If ASCII Character ?
		if (pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] >= 0 && pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] <= 127){
			wxstr += wxString::Format("%c", pmbuscmd->m_recvBuff.m_dataBuff[1 + idx]);
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_REVISION
	const wchar_t* tmp_wchar;

	wxString wxstr("REVISION: ");

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	for (int idx = 0; idx < pmbuscmd->m_recvBuff.m_dataBuff[0]; idx++){
		// If ASCII Character ?
		if (pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] >= 0 && pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] <= 127){
			wxstr += wxString::Format("%c", pmbuscmd->m_recvBuff.m_dataBuff[1 + idx]);
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_LOCATION
	const wchar_t* tmp_wchar;

	wxString wxstr("LOCATION: ");

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	for (int idx = 0; idx < pmbuscmd->m_recvBuff.m_dataBuff[0]; idx++){
		// If ASCII Character ?
		if (pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] >= 0 && pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] <= 127){
			wxstr += wxString::Format("%c", pmbuscmd->m_recvBuff.m_dataBuff[1 + idx]);
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_DATE
	const wchar_t* tmp_wchar;

	wxString wxstr("DATE: ");

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	for (int idx = 0; idx < pmbuscmd->m_recvBuff.m_dataBuff[0]; idx++){
		// If ASCII Character ?
		if (pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] >= 0 && pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] <= 127){
			wxstr += wxString::Format("%c", pmbuscmd->m_recvBuff.m_dataBuff[1 + idx]);
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_SERIAL
	const wchar_t* tmp_wchar;

	wxString wxstr("SERIAL: ");

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	for (int idx = 0; idx < pmbuscmd->m_recvBuff.m_dataBuff[0]; idx++){
		// If ASCII Character ?
		if (pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] >= 0 && pmbuscmd->m_recvBuff.m_dataBuff[1 + idx] <= 127){
			wxstr += wxString::Format("%c", pmbuscmd->m_recvBuff.m_dataBuff[1 + idx]);
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_9fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// MFR_SERIAL
	const wchar_t* tmp_wchar;

	// APP_PROFILE_SUPPORT First Data Byte Contents
	// 00h No Application Profiles Are Supported
	// 01h Server AC-DC Power Supply [A06]
	// 02h DC-DC Converters For Microprocessor Power And Other Computer Applications[A07]
	// 03h DC-DC Converters For General Purpose Use [A08]

	// The second data byte, indicating revision shall be formatted as two four bit nibbles.
	// Bits[7:4] shall indicate the major revision and bits[3:0] shall indicate the minor
	// revision.The value 00h shall be used only when the first byte is also 00h, indicating
	// that the device does not support any application profiles.For example, revision 1.2
	// would be reported as 0102h.
	// If a device supports multiple Application Profiles, the device may report these in any order.

	wxString wxstr("APP Profile : ");
	
	// APP_PROFILE_SUPPORT
	switch (pmbuscmd->m_recvBuff.m_dataBuff[1]){

	case 0:
		wxstr += wxT("NONE");
		break;

	case 1:
		wxstr += wxT("Server AC-DC Power Supply");
		break;

	case 2:
		wxstr += wxT("DC-DC Converters For Microprocessor Power And Other Computer Applications");
		break;

	case 3:
		wxstr += wxT("DC-DC Converters For General Purpose Use");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Unknown APP PROFILE SUPPORT Type !");
		break;
	}

	wxstr += wxT(" ");
	
	// Revision
    #define APP_PROFILE_REVISON_MAJOR 0xf0
    #define APP_PROFILE_REVISON_MINOR 0x0f

	char major = (pmbuscmd->m_recvBuff.m_dataBuff[2] & APP_PROFILE_REVISON_MAJOR) >> 4;
	char minor = pmbuscmd->m_recvBuff.m_dataBuff[2] & APP_PROFILE_REVISON_MINOR;

	wxstr += wxString::Format("Rev: %d.%d", major, minor);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short voltage = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		voltage = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2,pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%dV", voltage);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short voltage = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		voltage = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		voltage = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%dV", voltage);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iin_max = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		iin_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		iin_max = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%4.4fA", iin_max);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short watt = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		watt = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		watt = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%dW", watt);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double vout_min = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		vout_min = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		vout_min = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%4.4fV", vout_min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double vout_max = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		vout_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		vout_max = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%4.4fV", vout_max);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iout_max = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		iout_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		iout_max = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%4.4fA", iout_max);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	short pout_max = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		pout_max = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		pout_max = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%dW", pout_max);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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

#if 0	
	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 15, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 17, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);
#endif

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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

#if 0	
	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 15, 2);
	wxstr += wxString::Format(" %ldW,", (long)result);

	result = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff + 17, 2);
	wxstr += wxString::Format(" %ld%%,", (long)result);
#endif

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_acH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_adH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_aeH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_afH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_b0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_b9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_baH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_bbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_bcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_bdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_beH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_bfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%.1fC", temperature);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	//PMBUSHelper::GetPMBusStatus()->m_POUT = temperature;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_c3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	wxString enable_disable("");
	unsigned char status = pmbuscmd->m_recvBuff.m_dataBuff[0];

	wxString wxstr("");

	wxstr += wxT("Pointer : ");

	// Pointer Value
	wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	// Enable / Disable
	enable_disable += (pmbuscmd->m_recvBuff.m_dataBuff[1] == 0) ? wxT(", Enable") : wxT(", Disable");

	wxstr += enable_disable;

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_c4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_c5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_c6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_c7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_c8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_c9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_caH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_cbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_ccH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_cdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_ceH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_cfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	const wchar_t* tmp_wchar;

	wxString wxstr("");

	wxstr += wxString::Format("%02xh", pmbuscmd->m_recvBuff.m_dataBuff[0]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_d1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Show FW Version
	const wchar_t* tmp_wchar;

	wxString wxstr("Current Mode : ");

	switch (pmbuscmd->m_recvBuff.m_dataBuff[0]){
	// Standard Redundant Mode
	case 0x00:
		wxstr += wxT("Standard Redundant Mode");
		break;
	// Zero Output Enable Mode
	case 0x01:
		wxstr += wxT("Zero Output Enable Mode");
		break;
	// Zero Output Sleep Mode
	case 0x03:
		wxstr += wxT("Zero Output Sleep Mode");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "%s:Something Error Occurs", __FUNCTIONW__);
		break;
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_d2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_d3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_d4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_d5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_d6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_d7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_d8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Show FW Version
	const wchar_t* tmp_wchar;

	//B6 - F1 - 04 - [1] [2] [3] [4] [pec] : PRI : [1].[2], SEC : [3].[4]
	wxString wxstr("FW Ver. PRI : ");

	wxstr += wxString::Format("%d.%d, ", pmbuscmd->m_recvBuff.m_dataBuff[1], pmbuscmd->m_recvBuff.m_dataBuff[2]);

	wxstr += wxString::Format("SEC : %d.%d", pmbuscmd->m_recvBuff.m_dataBuff[3], pmbuscmd->m_recvBuff.m_dataBuff[4]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_daH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

#define DBH_DATA_LENGTH  4
int GB_CRPS_Cook_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;
	// Status WORD : 2848h, VOUT_1 : 00h, VOUT_2 : 00h, IOUT_1 : 00h, IOUT_2 : 00h, INPUT : 10h, TEMP : 00h, CML : 00h, OTHER : 00h, FAN12 : 00h   
	// [Block Length] - 48 - 28 - 00 - 00 - 00 - 00 - 10 - 00 - 00 - 00 - 00
	// [0] : Block Length
	// [1] : WORD L [2] : WORD H [3] : VOUT1 [4] : VOUT2 [5] : IOUT1 [6] : IOUT 2
	// [7] : INPUT  [8] : TEMP   [9] : CML   [10]: OTHER [11]: FAN12
	// [12]: CRC
	const wchar_t* tmp_wchar;
	unsigned short status_word = 0;

	wxString wxstr("Status WORD :");

	status_word = pmbuscmd->m_recvBuff.m_dataBuff[1] | pmbuscmd->m_recvBuff.m_dataBuff[2] << 8;
	PMBUSHelper::GetPMBusStatus()->m_status_word.SaveDCH(status_word);
	wxstr += wxString::Format(" %04xh,", status_word);

	PMBUSHelper::GetPMBusStatus()->m_status_vout.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[3]);
	wxstr += wxString::Format(" VOUT_1 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[3]);

	PMBUSHelper::GetPMBusStatus()->m_status_vout2.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[4]);
	wxstr += wxString::Format(" VOUT_2 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[4]);

	PMBUSHelper::GetPMBusStatus()->m_status_iout.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[5]);
	wxstr += wxString::Format(" IOUT_1 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[5]);

	PMBUSHelper::GetPMBusStatus()->m_status_iout2.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[6]);
	wxstr += wxString::Format(" IOUT_2 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[6]);

	PMBUSHelper::GetPMBusStatus()->m_status_input.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[7]);
	wxstr += wxString::Format(" INPUT : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[7]);

	PMBUSHelper::GetPMBusStatus()->m_status_temperature.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[8]);
	wxstr += wxString::Format(" TEMP : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[8]);

	PMBUSHelper::GetPMBusStatus()->m_status_cml.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[9]);
	wxstr += wxString::Format(" CML : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[9]);

	PMBUSHelper::GetPMBusStatus()->m_status_other.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[10]);
	wxstr += wxString::Format(" OTHER : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[10]);

	PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.SaveDCH(pmbuscmd->m_recvBuff.m_dataBuff[11]);
	wxstr += wxString::Format(" FAN12 : %02xh,", pmbuscmd->m_recvBuff.m_dataBuff[11]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_deH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_dfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_e0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 26.0C (Max:26.0, Min : 26.0)
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	PMBUSHelper::GetPMBusStatus()->SavePFC1(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_PFC1_Max, PMBUSHelper::GetPMBusStatus()->m_PFC1_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_e1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 26.0C (Max:26.0, Min : 26.0)
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	PMBUSHelper::GetPMBusStatus()->SavePFC2(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_PFC2_Max, PMBUSHelper::GetPMBusStatus()->m_PFC2_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_e2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 26.0C (Max:26.0, Min : 26.0)
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	PMBUSHelper::GetPMBusStatus()->SaveSR1(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_SR1_Max, PMBUSHelper::GetPMBusStatus()->m_SR1_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_e3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 26.0C (Max:26.0, Min : 26.0)
	const wchar_t* tmp_wchar;
	double temperature = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		temperature = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		temperature = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	PMBUSHelper::GetPMBusStatus()->SaveSR2(temperature);

	wxstr += wxString::Format("%.2fC (Max:%.2f, Min:%.2f)", temperature, PMBUSHelper::GetPMBusStatus()->m_SR2_Max, PMBUSHelper::GetPMBusStatus()->m_SR2_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_e4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_e5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_e6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_e7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_e8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_e9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_eaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_ebH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_edH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_eeH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_efH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_f0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Show FW Version
	const wchar_t* tmp_wchar;

	//B6 - F1 - 04 - [1] [2] [3] [4] [pec] : PRI : [1].[2], SEC : [3].[4]
	wxString wxstr("FW Ver. PRI : ");

	wxstr += wxString::Format("%d.%d, ", pmbuscmd->m_recvBuff.m_dataBuff[1], pmbuscmd->m_recvBuff.m_dataBuff[2]);

	wxstr += wxString::Format("SEC : %d.%d", pmbuscmd->m_recvBuff.m_dataBuff[3], pmbuscmd->m_recvBuff.m_dataBuff[4]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_f6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_f9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_fbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Don't Show Anything
	const wchar_t* tmp_wchar;

	wxString wxstr("----------");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_fdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_feH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Cook_ffH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Cook_Not_Implement(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Cook_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	
	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	unsigned char tmp_buff[256] = { 0 };

	if (PMBUSHelper::getPMBUSCMDData()[PMBUSHelper::getIndexOfCMD(pmbuscmd->m_cmdStatus.m_AddtionalData[2])].m_cmdStatus.m_alsoSendWriteData != cmd_also_send_write_data){
		// Get rid of block size byte
		//PSU_DEBUG_PRINT(MSG_DEBUG, "m_recvBuff.m_length=%d", pmbuscmd->m_recvBuff.m_length);
		memcpy(tmp_buff, pmbuscmd->m_recvBuff.m_dataBuff + 1, 256 - 1);
		memcpy(pmbuscmd->m_recvBuff.m_dataBuff, tmp_buff, 256 - 1);
		pmbuscmd->m_recvBuff.m_dataBuff[255] = 0;
	}
	
	// Call Corresponding Raw Handler
	CMDCookCBFunc cookCBFunc = NULL;

	// Get Index 
	int Index = -1;
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == pmbuscmd->m_cmdStatus.m_AddtionalData[2]){
			Index = idx;
			break;
		}
	}

	if (Index < 0){
		return EXIT_SUCCESS;
	}

	if (PMBUSHelper::getPMBUSCMDData()[Index].m_cmdCBFunc.m_cookCBFunc != NULL){
		cookCBFunc = PMBUSHelper::getPMBUSCMDData()[Index].m_cmdCBFunc.m_cookCBFunc;

		return cookCBFunc(pmbuscmd, string, sizeOfstr);
	}
	else{
		return EXIT_SUCCESS;
	}

}

#define PACKET_ERROR_CHECKING_MASK   0x80
#define MAX_BUS_SPEED_MASK           0x60
#define SMBALERT_SUPPORT_MASK        0x10
int GB_CRPS_Cook_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Bits     Description           Value               Meaning
	//  7   Packet Error Checking       0       Packet Error Checking not supported
	//                                  1       Packet Error Checking is supported
	// 6:5  Maximum Bus Speed           00      Maximum supported bus speed is 100 kHz
	//                                  01      Maximum supported bus speed is 400 kHz
	//                                  10      Reserved
	//                                  11      Reserved
	//  4   SMBALERT#                   0       The device does not have a SMBALERT# pin and does not support the SMBus Alert Response protocol
	//                                  1       The device does have a SMBALERT# pin and does support the SMBus Alert Response protocol
	// 3:0  Reserved                    X       X

	const wchar_t* tmp_wchar;

	wxString wxstr("");
	wxstr = wxString::Format("Packet Error Checking:[");

	// Packet Error Checking
	if (pmbuscmd->m_recvBuff.m_dataBuff[0] & PACKET_ERROR_CHECKING_MASK){
		wxstr += wxString::Format("Support]");
	}
	else{
		wxstr += wxString::Format("UnSupport]");
	}

	wxstr += wxString::Format(" ,");
	wxstr += wxString::Format("Maximum Bus Speed:[");

	// Maximum Bus Speed
	unsigned char maxBusSpeed = (pmbuscmd->m_recvBuff.m_dataBuff[0] & MAX_BUS_SPEED_MASK) >> 5;

	switch (maxBusSpeed){

	case 0x00:
		wxstr += wxString::Format("100K]");
		break;

	case 0x01:
		wxstr += wxString::Format("400K]");
		break;

	case 0x10:
		wxstr += wxString::Format(" ]");
		break;

	case 0x11:
		wxstr += wxString::Format(" ]");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs !");
		wxstr += wxString::Format(" ]");
		break;
	}

	wxstr += wxString::Format(" ,");
	wxstr += wxString::Format("SMBALERT PIN:[");

	// SMBALERT#
	if (pmbuscmd->m_recvBuff.m_dataBuff[0] & SMBALERT_SUPPORT_MASK){
		wxstr += wxString::Format("Support]");
	}
	else{
		wxstr += wxString::Format("UnSupport]");
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	short m, b;
	char R;
	const wchar_t* tmp_wchar;

	int RW;
	RW = pmbuscmd->m_cmdStatus.m_AddtionalData[DEF_30H_READ_RW_INDEX];

	wxString wxstr("");

	switch (RW){

	case rw_write_coefficients:
		wxstr += wxString::Format("(W)");
		break;

	case rw_read_coefficients:
		wxstr += wxString::Format("(R)");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs, RW = %d", RW);
		break;
	}

	wxstr += wxString::Format(" ");
	wxstr += wxString::Format("CMD:%02xH,", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);

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
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == queryCMD){
			queryCMDIndex = idx;
			break;
		}
	}

	if (queryCMDIndex < 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
		return EXIT_FAILURE;
	}

	// Set Direct Data Fomat Coefficient
	pmbuscmd_t* target;
	target = PMBUSHelper::getPMBUSCMDData();

	switch (RW){

	case rw_write_coefficients :

		PSU_DEBUG_PRINT(MSG_DEBUG, "Get Write Coefficients");

		target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_M = m;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Write Coefficients m=%d", target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_M);
		target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_B = b;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Write Coefficients b=%d", target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_B);
		target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_R = R;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Write Coefficients R=%d", target[queryCMDIndex].m_dataFormat.m_WriteCoefficients.m_R);

		break;

	case rw_read_coefficients :

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

int GB_CRPS_Cook_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double pout = 0;

	wxString wxstr("");

	pout = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

	wxstr += wxString::Format("%dW", (long)pout);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());


	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	const wchar_t* tmp_wchar;
	double iin = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		iin = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		iin = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}

	wxstr += wxString::Format("%ldA", (long)iin);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// Show FW Version
	const wchar_t* tmp_wchar;

	//B6 - F1 - 04 - [1] [2] [3] [4] [pec] : PRI : [1].[2], SEC : [3].[4]
	wxString wxstr("FW Ver. PRI : ");

	wxstr += wxString::Format("%d.%d, ", pmbuscmd->m_recvBuff.m_dataBuff[1], pmbuscmd->m_recvBuff.m_dataBuff[2]);

	wxstr += wxString::Format("SEC : %d.%d", pmbuscmd->m_recvBuff.m_dataBuff[3], pmbuscmd->m_recvBuff.m_dataBuff[4]);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Check have checksum error ?
	if (Check_Have_CheckSum_Error(pmbuscmd, string, sizeOfstr) == true) return EXIT_FAILURE;

	// 7008RPM (Max:7008, Min:7008)
	const wchar_t* tmp_wchar;
	double rpm = 0;

	wxString wxstr("");

	switch (pmbuscmd->m_dataFormat.m_formatType){

	case cmd_data_format_LinearData_Format:

		rpm = PMBUSHelper::ParseLinearDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2);

		break;

	case cmd_data_format_DirectData_Format:

		rpm = PMBUSHelper::ParseDirectDataFormat(pmbuscmd->m_recvBuff.m_dataBuff, 2, pmbuscmd);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "CMD: %02x, pmbuscmd->m_dataFormat.m_formatType = %d", pmbuscmd->m_register, pmbuscmd->m_dataFormat.m_formatType);
		break;
	}
	
	PMBUSHelper::GetPMBusStatus()->SaveFAN2(rpm);

	wxstr += wxString::Format("%4.0fRPM (Max:%4.0f, Min:%4.0f)", rpm, PMBUSHelper::GetPMBusStatus()->m_FAN2_Max, PMBUSHelper::GetPMBusStatus()->m_FAN2_Min);

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	return EXIT_SUCCESS;
}

int GB_CRPS_Cook_Not_Implement(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){
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

