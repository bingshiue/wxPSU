/**
 * @file ACBEL_RFWE_24_28_1200W_SCP_CBQuery.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "ACBEL_RFWE_24_28_1200W_SCP_CBQuery.h"

int ACBEL_RFWE_24_28_1200W_SCP_Query_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int ACBEL_RFWE_24_28_1200W_SCP_Query_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return ACBEL_RFWE_24_28_1200W_SCP_Query_Common(pmbuscmd, string, sizeOfstr); }
int ACBEL_RFWE_24_28_1200W_SCP_Query_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return ACBEL_RFWE_24_28_1200W_SCP_Query_Common(pmbuscmd, string, sizeOfstr); }
int ACBEL_RFWE_24_28_1200W_SCP_Query_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return ACBEL_RFWE_24_28_1200W_SCP_Query_Common(pmbuscmd, string, sizeOfstr); }
int ACBEL_RFWE_24_28_1200W_SCP_Query_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return ACBEL_RFWE_24_28_1200W_SCP_Query_Common(pmbuscmd, string, sizeOfstr); }

#define CMD_SUPPORT_MASK         (0x80)
#define CMD_ACCSSS_WRITE_MASK    (0x40)
#define CMD_ACCSSS_READ_MASK     (0x20)
#define CMD_ACCSSS_FORMAT_MASK   (0x1C)
#define CMD_ACCSSS_RESERVED_MASK (0x03)
int ACBEL_RFWE_24_28_1200W_SCP_Query_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

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

	// Support
	if (!(pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_SUPPORT_MASK)){

		support = cmd_unsupport;

		wxstr += wxString::Format("Unsupport");

		tmp_wchar = wxstr.wc_str();
		COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

		return EXIT_SUCCESS;
	}
	else{
		support = cmd_support;
	}

	// Write 
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_READ_MASK){
		wxstr += wxString::Format("R");
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
		wxstr += wxString::Format("W");
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
		PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD, queryCMD=%02xH, CMD's page=%d", queryCMD, sizeOfstr);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "queryCMDIndex = %d", queryCMDIndex);
	}

	// Set Direct Data Fomat Coefficient
	pmbuscmd_t* target;
	target = PMBUSHelper::getPMBUSCMDData();

	// Update support field
	target[queryCMDIndex].m_cmdStatus.m_support = support;

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
		wxstr += wxString::Format("Block or None");
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


#if 0
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];

	PSU_DEBUG_PRINT(MSG_DEBUG, "GB_CRPS_Query_Common");

	wxString wxstr("");

	tmp_wchar = wxstr.wc_str();

	lstrcpyn(string, tmp_wchar, 256);
#endif

	return EXIT_SUCCESS;
}
