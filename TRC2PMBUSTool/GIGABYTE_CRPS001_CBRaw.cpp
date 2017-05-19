/**
 * @file GIGABYTE_CRPS001_CBRaw.cpp
 */

#include "GIGABYTE_CRPS001_CBRaw.h"

int GB_CRPS_Raw_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

int GB_CRPS_Raw_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	// Because of this command's access attribute is write, don't show any response data in raw field
	const wchar_t* tmp_wchar;
	wxString wxstr("");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_04H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_07H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_08H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_09H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_0aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_0bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_0cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_0dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_0eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_0fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_10H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_11H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_12H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_13H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_14H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_15H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_16H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_17H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_18H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	bool checkSumError = false;
	unsigned int count = 0;
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];

	if (string == NULL) return -1;

	// Sample : B6-1A-XX-XX-B7-01(Block Count)-00(Query Data)-PEC

	wxString wxstr("");

	// I2C Address
	wxstr += wxString::Format("%2x", PMBUSHelper::GetSlaveAddress()).Upper();
	tmp_buffer[0] = PMBUSHelper::GetSlaveAddress();

	wxstr += "-";

	// Command (Register)
	wxstr += wxString::Format("%02x", pmbuscmd->m_register);
	tmp_buffer[1] = pmbuscmd->m_register;

	wxstr += "-";

	// Addtional Data
	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[0]);
	tmp_buffer[2] = pmbuscmd->m_cmdStatus.m_AddtionalData[0];
	wxstr += "-";

	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);
	tmp_buffer[3] = pmbuscmd->m_cmdStatus.m_AddtionalData[1];
	wxstr += "-";

	// Read Command
	//wxstr += L"B7";
	wxstr += wxString::Format("%02x", PMBUSHelper::GetSlaveAddress() | 0x01).Upper();
	tmp_buffer[4] = (PMBUSHelper::GetSlaveAddress() | 0x01);

	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		wxstr += "-";
		wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[idx]);
		tmp_buffer[5 + idx] = pmbuscmd->m_recvBuff.m_dataBuff[idx];
	}

	wxstr.UpperCase();

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	// Check If CheckSum Error
	unsigned char verify_pec = 0;
	if (PMBUSHelper::GetAppSettings()->m_EnableChecksum == Generic_Enable){
		verify_pec = PMBusSlave_Crc8MakeBitwise(0, 7, tmp_buffer + 0, ((dataBytesLength + 5) - 1));

		PSU_DEBUG_PRINT(MSG_DETAIL, "verify_pec = %02x, pec = %02x", verify_pec, pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]);

		if (verify_pec != pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]){
			wxstr += L" (Checksum Error)";
			pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
		}

	}

#if 0
	// At present If all the data bytes (incluing PEC) are 0xff, this data should be CheckSum Error
	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		if (pmbuscmd->m_recvBuff.m_dataBuff[idx] == 0xff){
			count++;
		}
	}

	if (count == dataBytesLength) {// CheckSum Error Occurs
		wxstr += L" (Checksum Error)";
		pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
	}
#endif

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	bool checkSumError = false;
	unsigned int count = 0;
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];

	if (string == NULL) return -1;

	// Sample : B6-1B-01-78-B7-01(Block Count)-00(Mask Byte)-97

	wxString wxstr("");

	// I2C Address
	wxstr += wxString::Format("%2x", PMBUSHelper::GetSlaveAddress()).Upper();
	tmp_buffer[0] = PMBUSHelper::GetSlaveAddress();

	wxstr += "-";

	// Command (Register)
	wxstr += wxString::Format("%02x", pmbuscmd->m_register);
	tmp_buffer[1] = pmbuscmd->m_register;

	wxstr += "-";

	// Addtional Data
	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[0]);
	tmp_buffer[2] = pmbuscmd->m_cmdStatus.m_AddtionalData[0];
	wxstr += "-";

	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);
	tmp_buffer[3] = pmbuscmd->m_cmdStatus.m_AddtionalData[1];
	wxstr += "-";

	// Read Command
	//wxstr += L"B7";
	wxstr += wxString::Format("%02x", PMBUSHelper::GetSlaveAddress() | 0x01).Upper();
	tmp_buffer[4] = (PMBUSHelper::GetSlaveAddress() | 0x01);

	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		wxstr += "-";
		wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[idx]);
		tmp_buffer[5 + idx] = pmbuscmd->m_recvBuff.m_dataBuff[idx];
	}

	wxstr.UpperCase();

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	// Check If CheckSum Error
	unsigned char verify_pec = 0;
	if (PMBUSHelper::GetAppSettings()->m_EnableChecksum == Generic_Enable){
		verify_pec = PMBusSlave_Crc8MakeBitwise(0, 7, tmp_buffer + 0, ((dataBytesLength + 5) - 1));

		PSU_DEBUG_PRINT(MSG_DETAIL, "verify_pec = %02x, pec = %02x", verify_pec, pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]);

		if (verify_pec != pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]){
			wxstr += L" (Checksum Error)";
			pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
		}

	}

#if 0
	// At present If all the data bytes (incluing PEC) are 0xff, this data should be CheckSum Error
	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		if (pmbuscmd->m_recvBuff.m_dataBuff[idx] == 0xff){
			count++;
		}
	}

	if (count == dataBytesLength) {// CheckSum Error Occurs
		wxstr += L" (Checksum Error)";
		pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
	}
#endif

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_1cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_1dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_1eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_1fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_21H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_22H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_23H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_24H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_25H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_26H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_27H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_28H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_29H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_2AH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_2BH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_2CH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_2DH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_2EH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_2FH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_32H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_33H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_34H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_35H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_36H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_37H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_38H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_39H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_40H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_41H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_42H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_43H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_44H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_45H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_47H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_48H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_49H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_4bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_4cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_4dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_4eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_4fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_50H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_52H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_53H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_54H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_55H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_56H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_57H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_58H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_59H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_60H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_61H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_62H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_63H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_64H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_65H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_66H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_67H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_68H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_69H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_71H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_72H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_73H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_74H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_75H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_76H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_77H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_80H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_82H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_83H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_84H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_85H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_92H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_93H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_94H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_95H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_acH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_adH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_aeH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_afH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_b0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_b9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_baH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_bbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_bcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_bdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_beH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_bfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}
int GB_CRPS_Raw_c3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_c4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_c5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_c6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_c7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_c8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_c9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_caH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_cbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ccH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_cdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ceH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_cfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_daH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_deH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_dfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_e0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_e9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_eaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ebH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_edH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_eeH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_efH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_f0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_fbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_fdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_feH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ffH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	bool checkSumError = false;
	unsigned int count = 0;
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];

	if (string == NULL) return -1;

	wxString wxstr("");

	// I2C Address
	wxstr += wxString::Format("%2x", PMBUSHelper::GetSlaveAddress()).Upper();
	tmp_buffer[0] = PMBUSHelper::GetSlaveAddress();

	wxstr += "-";

	// Command (Register)
	wxstr += wxString::Format("%02x", pmbuscmd->m_register);
	tmp_buffer[1] = pmbuscmd->m_register;

	wxstr += "-";

	// Read Command
	wxstr += wxString::Format("%2x", PMBUSHelper::GetSlaveAddress() | 0x01).Upper();
	tmp_buffer[2] = PMBUSHelper::GetSlaveAddress() | 0x01;

	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		wxstr += "-";
		wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[idx]);
		tmp_buffer[3 + idx] = pmbuscmd->m_recvBuff.m_dataBuff[idx];
	}

	wxstr.UpperCase();

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

	// Check If CheckSum Error
	unsigned char verify_pec = 0;
	if (PMBUSHelper::GetAppSettings()->m_EnableChecksum == Generic_Enable){
		verify_pec = PMBusSlave_Crc8MakeBitwise(0, 7, tmp_buffer + 0, ((dataBytesLength + 3) - 1));

		PSU_DEBUG_PRINT(MSG_DETAIL, "verify_pec = %02x, pec = %02x", verify_pec, pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]);

		if (verify_pec != pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]){
			wxstr += L" (Checksum Error)";
			pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
		}

	}

#if 0
	// At present If all the data bytes (incluing PEC) are 0xff, this data should be CheckSum Error
	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		if (pmbuscmd->m_recvBuff.m_dataBuff[idx] == 0xff){
			count++;
		}
	}

	if (count == dataBytesLength) {// CheckSum Error Occurs
		wxstr += L" (Checksum Error)";
		pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
	}
#endif

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){
	bool checkSumError = false;
	unsigned int count = 0;
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];
	unsigned char tmp_buffer_idx = 0;

	if (string == NULL) return -1;

	// Sample : B6-06-02-00-79-b7-XX-XX-XX-PEC

	wxString wxstr("");

	// I2C Address "B6"
	wxstr += wxString::Format("%2x", PMBUSHelper::GetSlaveAddress()).Upper();
	tmp_buffer[tmp_buffer_idx++] = PMBUSHelper::GetSlaveAddress();

	wxstr += "-";

	// Command (Register) "06"
	wxstr += wxString::Format("%02x", pmbuscmd->m_register);
	tmp_buffer[tmp_buffer_idx++] = pmbuscmd->m_register;

	wxstr += "-";

	for(unsigned int idx=0; idx<pmbuscmd->m_cmdStatus.m_AddtionalDataLength; idx++){
		wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[idx]);
		tmp_buffer[tmp_buffer_idx++] = pmbuscmd->m_cmdStatus.m_AddtionalData[idx];
		wxstr += "-";
	}

#if 0
	// Addtional Data
	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[0]);
	tmp_buffer[2] = pmbuscmd->m_cmdStatus.m_AddtionalData[0];
	wxstr += "-";

	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);
	tmp_buffer[3] = pmbuscmd->m_cmdStatus.m_AddtionalData[1];
	wxstr += "-";

	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[2]);
	tmp_buffer[4] = pmbuscmd->m_cmdStatus.m_AddtionalData[2];
	wxstr += "-";
#endif

	// Read Command
	//wxstr += L"B7";
	wxstr += wxString::Format("%02x", PMBUSHelper::GetSlaveAddress() | 0x01).Upper();
	tmp_buffer[tmp_buffer_idx++] = (PMBUSHelper::GetSlaveAddress() | 0x01);

	unsigned int dataStartIndex = tmp_buffer_idx;
	unsigned int dataStartIndex_Static = dataStartIndex;

	PSU_DEBUG_PRINT(MSG_DEBUG, "dataBytesLength = %2d", dataBytesLength);
	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		wxstr += "-";
		wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[idx]);
		tmp_buffer[dataStartIndex_Static + idx] = pmbuscmd->m_recvBuff.m_dataBuff[idx];
		dataStartIndex++;
	}

	wxstr.UpperCase();

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	PSU_DEBUG_PRINT(MSG_DEBUG, "Finally dataStartIndex = %d", dataStartIndex);

	wxString tmpStr("");
	for (unsigned int idx = 0; idx < dataStartIndex; idx++){
		tmpStr += wxString::Format("%02x ", tmp_buffer[idx]);
	}
	PSU_DEBUG_PRINT(MSG_DEBUG, "tmp_buffer = %s", tmpStr.c_str());

	// Check If CheckSum Error
	// pec compute length = 2 (B6 06) + Additional Data Length + 1 (B7) + DataBytesLength - 1(minus 1 due to latest byte is the PEC sent by DSP)  
	unsigned char pec_compute_length = 2 + pmbuscmd->m_cmdStatus.m_AddtionalDataLength + 1 + (dataBytesLength-1);
	unsigned char verify_pec = 0;
	if (PMBUSHelper::GetAppSettings()->m_EnableChecksum == Generic_Enable){
		verify_pec = PMBusSlave_Crc8MakeBitwise(0, 7, tmp_buffer + 0, pec_compute_length);//(((dataBytesLength + 5) - 1) + (dataBytesLength - 2)));

		PSU_DEBUG_PRINT(MSG_DEBUG, "verify_pec = %02x, pec = %02x, pec_compute_length = %d", verify_pec, pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1], pec_compute_length);

		if (verify_pec != pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]){
			wxstr += L" (Checksum Error)";
			pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
		}
	}

	//
	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	bool checkSumError = false;
	unsigned int count = 0;
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];

	if (string == NULL) return -1;

	// Sample : B6-06-AD1-AD2-AD3-b7-Block Size-XX-XX-XX-XX-XX-PEC

	wxString wxstr("");

	// I2C Address "B6"
	wxstr += wxString::Format("%2x", PMBUSHelper::GetSlaveAddress()).Upper();
	tmp_buffer[0] = PMBUSHelper::GetSlaveAddress();

	wxstr += "-";

	// Command (Register) "06"
	wxstr += wxString::Format("%02x", pmbuscmd->m_register);
	tmp_buffer[1] = pmbuscmd->m_register;

	wxstr += "-";

	// Addtional Data
	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[0]);
	tmp_buffer[2] = pmbuscmd->m_cmdStatus.m_AddtionalData[0];
	wxstr += "-";

	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[1]);
	tmp_buffer[3] = pmbuscmd->m_cmdStatus.m_AddtionalData[1];
	wxstr += "-";

	wxstr += wxString::Format("%02x", pmbuscmd->m_cmdStatus.m_AddtionalData[2]);
	tmp_buffer[4] = pmbuscmd->m_cmdStatus.m_AddtionalData[2];
	wxstr += "-";

	// Read Command
	//wxstr += L"B7";
	wxstr += wxString::Format("%02x", PMBUSHelper::GetSlaveAddress() | 0x01).Upper();
	tmp_buffer[5] = (PMBUSHelper::GetSlaveAddress() | 0x01);

	unsigned int dataStartIndex = 6;
	unsigned int dataStartIndex_Static = dataStartIndex;

	PSU_DEBUG_PRINT(MSG_DEBUG, "dataBytesLength = %2d", dataBytesLength);
	for (unsigned int idx = 0; idx < dataBytesLength; idx++){
		wxstr += "-";
		wxstr += wxString::Format("%02x", pmbuscmd->m_recvBuff.m_dataBuff[idx]);
		tmp_buffer[dataStartIndex_Static + idx] = pmbuscmd->m_recvBuff.m_dataBuff[idx];
		dataStartIndex++;
	}

	wxstr.UpperCase();

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());
	PSU_DEBUG_PRINT(MSG_DEBUG, "Finally dataStartIndex = %d", dataStartIndex);

	wxString tmpStr("");
	for (unsigned int idx = 0; idx < dataStartIndex; idx++){
		tmpStr += wxString::Format("%02x ", tmp_buffer[idx]);
	}
	PSU_DEBUG_PRINT(MSG_DEBUG, "tmp_buffer = %s", tmpStr.c_str());

	// Check If CheckSum Error
	// pec compute length = 2 (B6 06) + Additional Data Length + 1 (B7) + DataBytesLength - 1(minus 1 due to latest byte is the PEC sent by DSP)  
	unsigned char pec_compute_length = 2 + pmbuscmd->m_cmdStatus.m_AddtionalDataLength + 1 + (dataBytesLength - 1);
	unsigned char verify_pec = 0;
	if (PMBUSHelper::GetAppSettings()->m_EnableChecksum == Generic_Enable){
		verify_pec = PMBusSlave_Crc8MakeBitwise(0, 7, tmp_buffer + 0, pec_compute_length);//(((dataBytesLength + 5) - 1) + (dataBytesLength - 2)));

		PSU_DEBUG_PRINT(MSG_DEBUG, "verify_pec = %02x, pec = %02x, pec_compute_length = %d", verify_pec, pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1], pec_compute_length);

		if (verify_pec != pmbuscmd->m_recvBuff.m_dataBuff[dataBytesLength - 1]){
			wxstr += L" (Checksum Error)";
			pmbuscmd->m_cmdStatus.m_status = cmd_status_checksum_error;
		}
	}

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	return EXIT_SUCCESS;

}

int GB_CRPS_Raw_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}
