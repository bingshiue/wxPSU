/**
 * @file GIGABYTE_CRPS001_CBRaw.cpp
 */

#include "GIGABYTE_CRPS001_CBRAW.h"

int GB_CRPS_Raw_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

int GB_CRPS_Raw_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

int GB_CRPS_Raw_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	// Because of this command's access attribute is write, don't show any response data in raw field
	const wchar_t* tmp_wchar;
	wxString wxstr("");

	tmp_wchar = wxstr.wc_str();
	lstrcpyn(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

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
	lstrcpyn(string, tmp_wchar, 256);

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
	lstrcpyn(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
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
int GB_CRPS_Raw_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
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
int GB_CRPS_Raw_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }
int GB_CRPS_Raw_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength); }

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
	lstrcpyn(string, tmp_wchar, 256);

	return EXIT_SUCCESS;
}

int GB_CRPS_Raw_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
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

int GB_CRPS_Raw_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}

int GB_CRPS_Raw_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

	return GB_CRPS_Raw_Common(pmbuscmd, string, dataBytesLength);
}