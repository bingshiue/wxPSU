/**
 * @file PBF003_00G_CBRaw.cpp
 */
#include "PBF003_00G_CBRaw.h"

int PFB003_00G_Raw_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

int PFB003_00G_Raw_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0922H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength) { return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }
int PFB003_00G_Raw_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){ return PFB003_00G_Raw_Common(pmbuscmd, string, dataBytesLength); }

int PFB003_00G_Raw_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength){

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

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", wxstr.c_str());

#if 0
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
#endif

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
