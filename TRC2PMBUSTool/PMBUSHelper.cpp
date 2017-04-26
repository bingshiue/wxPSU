/**
 * @file PMBUSHelper.cpp
 */

#include "math.h"
#include "pec.h"
#include "PMBUSHelper.h"

unsigned char PMBUSHelper::m_slaveAddress;
PMBUSSTATUS_t PMBUSHelper::m_pmbusStatus;
AppSettings_t* PMBUSHelper::m_appSettings;
unsigned int PMBUSHelper::CurrentISPTarget;
USBINFO PMBUSHelper::m_USBInfo;
unsigned int PMBUSHelper::IspErrRetry = 0;
unsigned int PMBUSHelper::IspStartVerifyRetry = 0;
wxString PMBUSHelper::m_timeString;
unsigned int PMBUSHelper::CurrentCMDTableSize;
wxString PMBUSHelper::m_winTitleBase;
PMBUSCOMMAND_t* PMBUSHelper::m_PMBusCMDData;
unsigned int PMBUSHelper::runInMode;
int PMBUSHelper::runInTimes;
unsigned char PMBUSHelper::m_FWUploadModeCMD;
unsigned char PMBUSHelper::m_FWUploadCMD;
unsigned char PMBUSHelper::m_FWUploadStatusCMD;
int PMBUSHelper::TotalPhaseWriteReadLastError;
wxString PMBUSHelper::m_default_mfr_id = wxT("");
wxString PMBUSHelper::m_default_mfr_model = wxT("");
wxString PMBUSHelper::m_default_mfr_revision = wxT("");
wxString PMBUSHelper::m_default_mfr_location = wxT("");
wxString PMBUSHelper::m_default_mfr_date = wxT("");
wxString PMBUSHelper::m_default_mfr_serial = wxT("");

void PMBUSHelper::SetSlaveAddress(unsigned char slaveAddress){
	m_slaveAddress = slaveAddress;
}

unsigned char& PMBUSHelper::GetSlaveAddress(void){
	return m_slaveAddress;
}

PMBUSSTATUS_t* PMBUSHelper::GetPMBusStatus(void){
	return &m_pmbusStatus;
}

USBINFO* PMBUSHelper::GetUSBInfo(void){
	return &m_USBInfo;
}

void PMBUSHelper::SetAppSettings(AppSettings_t* appSettings){
	m_appSettings = appSettings;
}

AppSettings_t* PMBUSHelper::GetAppSettings(void){
	return m_appSettings;
}

void PMBUSHelper::setPMBUSCMDData(PMBUSCOMMAND_t *PMBusCMDData){
	m_PMBusCMDData = PMBusCMDData;
}

PMBUSCOMMAND_t* PMBUSHelper::getPMBUSCMDData(void){
	return m_PMBusCMDData;
}

/**
 * @brief Parse Direct Data
 *
 * @param buffer Buffer contains "Y"
 * @param sizeOfBuffer Size of Buffer
 * @param PMBusCMDData PMBUS CMD Data
 * @retval Parse Result
 */
double PMBUSHelper::ParseDirectDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer, PMBUSCOMMAND_t* PMBusCMDData){
	// Direct Data Format : result = 1/m * ( (Y * 10^(-R)) - b)
	
	double result = 0;
	short Y = 0;

	if (PMBusCMDData == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "PMBusCMDData==NULL");
		return 0.0f;
	}

	if (!buffer || sizeOfBuffer < 2) {
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !");
		return -1;
	}

	Y = buffer[0] | buffer[1] << 8;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Y=%d", Y);

	PSU_DEBUG_PRINT(MSG_DEBUG, "m=%d", PMBusCMDData->m_dataFormat.m_ReadCoefficients.m_M);
	PSU_DEBUG_PRINT(MSG_DEBUG, "R=%d", PMBusCMDData->m_dataFormat.m_ReadCoefficients.m_R);
	PSU_DEBUG_PRINT(MSG_DEBUG, "b=%d", PMBusCMDData->m_dataFormat.m_ReadCoefficients.m_B);

	result = (((double)Y * (double)(pow(10, -PMBusCMDData->m_dataFormat.m_ReadCoefficients.m_R))) - PMBusCMDData->m_dataFormat.m_ReadCoefficients.m_B) / (double)PMBusCMDData->m_dataFormat.m_ReadCoefficients.m_M;

	PSU_DEBUG_PRINT(MSG_DEBUG, "result=%5.4f", result);

	return result;
}


#define N_VALUE_MASK  0xf800
#define Y_VALUE_MASK  0x07ff

#define Y_SIGN_BIT (0x0400)
#define N_SIGN_BIT (0x10)

/**
 * @brief Parse Linear Data
 *
 * @param buffer Buffer contains linear format data
 * @param sizeOfBuffer Size of Buffer
 * @retval Parse Result
 */
double PMBUSHelper::ParseLinearDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer){
	double result = 0;
	short Y = 0, tempY = 0;
	char N = 0, tempN = 0;
	char Y_sign = positive;
	char N_sign = positive;

	if (!buffer || sizeOfBuffer < 2) {
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !");
		return -1;
	}

	unsigned short rawData = buffer[0] | (buffer[1] << 8);

	Y = rawData & Y_VALUE_MASK;
	Y_sign = (Y & Y_SIGN_BIT) >> 10;

	switch (Y_sign){

	case positive:
		PSU_DEBUG_PRINT(MSG_DETAIL, "Positive Y_sign = %d", Y_sign);
		// Due to Y_sign is positive, No need to shift Y
		break;

	case negative:
		PSU_DEBUG_PRINT(MSG_DETAIL, "Negative Y_sign = %d", Y_sign);

		// If Negative
		tempY = Y | (0xfc00);
		PSU_DEBUG_PRINT(MSG_DETAIL, "Temp Y = %x", tempY);

		Y = tempY;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !");
		PSU_DEBUG_PRINT(MSG_ALERT, "Negative Y_sign = %d", Y_sign);
		break;
	}


	N = (rawData & N_VALUE_MASK) >> 11;
	N_sign = (N & N_SIGN_BIT) >> 4;

	switch (N_sign){

	case positive:
		PSU_DEBUG_PRINT(MSG_DETAIL, "Positive N_sign = %d", N_sign);
		result = (double)(Y * pow(2.0f, N));
		break;

	case negative:
		PSU_DEBUG_PRINT(MSG_DETAIL, "Negative N_sign = %d", N_sign);

		// If Negative
		tempN = N | 0xe0; // (11111 > 11111111)
		PSU_DEBUG_PRINT(MSG_DETAIL, "Temp N = %d", tempN);

		result = (double)(Y * pow(2.0f, tempN));

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !");
		PSU_DEBUG_PRINT(MSG_ALERT, "Negative N_sign = %d", N_sign);
		break;
	}


	PSU_DEBUG_PRINT(MSG_DETAIL, "buffer[0]=%02x,buffer[1]=%02x,rawData=%x", buffer[0], buffer[1], rawData);
	PSU_DEBUG_PRINT(MSG_DEBUG,  "Y=%d,N=%d,Result=%4.5f", Y, N, result);

	return result;

}

int PMBUSHelper::ProductDirectData(unsigned char *dest, double value, PMBUSCOMMAND_t* PMBusCMDData){
	// Y(result) = (mX+b) * 10^R 

	short result = 0;

	if (dest == NULL || PMBusCMDData==NULL){
		return -1;
	}

	result = ((PMBusCMDData->m_dataFormat.m_WriteCoefficients.m_M * value) + PMBusCMDData->m_dataFormat.m_WriteCoefficients.m_B) * pow(10, PMBusCMDData->m_dataFormat.m_WriteCoefficients.m_R);

	PSU_DEBUG_PRINT(MSG_DEBUG, "m=%d, b=%d, R=%d", PMBusCMDData->m_dataFormat.m_WriteCoefficients.m_M, PMBusCMDData->m_dataFormat.m_WriteCoefficients.m_B, PMBusCMDData->m_dataFormat.m_WriteCoefficients.m_R);
	PSU_DEBUG_PRINT(MSG_DEBUG, "result=%d(%xH)", result, result);

	dest[0] = result & 0x00ff;

	dest[1] = (result & 0xff00) >> 8;

	return 0;
}


int PMBUSHelper::ProductFakeLinearData(unsigned char *dest, double value, double scale){
	short result = 0;

	result = (short)(value / scale);

	dest[0] = *((char*)&result);
	dest[1] = *((char*)&result+1);

	PSU_DEBUG_PRINT(MSG_DEBUG, "dest[0]=%02x, dest[1]=%02x", dest[0], dest[1]);

	return 0;
}


/**
 * @brief ProductLinearData
 *
 * @param dest Buffer for put product result
 * @param value The Value want to product
 * @param scale The Scale value want to use
 * @retval 0 : Success , Others : Failed
 */
int PMBUSHelper::ProductLinearData(unsigned char *dest, double value, double scale){
	int idx = 0, save_idx = -1;
	unsigned short result = 0;
	short tempY = 0;
	char  tempN = 0;
	char exponent = 0;
	char scale_sign = 0;;
	char value_sign = 0;

	/*
	2 pow 15, 32768
	2 pow 14, 16384
	2 pow 13, 8192
	2 pow 12, 4096
	2 pow 11, 2048
	2 pow 10, 1024
	2 pow  9, 512
	2 pow  8, 256
	2 pow  7, 128
	2 pow  6, 64
	2 pow  5, 32
	2 pow  4, 16
	2 pow  3, 8
	2 pow  2, 4
	2 pow  1, 2
	2 pow  0, 1.0
	2 pow -1, 0.50000000
	2 pow -2, 0.25000000
	2 pow -3, 0.12500000
	2 pow -4, 0.06250000
	2 pow -5, 0.03125000
	2 pow -6, 0.01562500
	2 pow -7, 0.00781250
	2 pow -8, 0.00390625
	2 pow -9, 0.00195313
	2 pow -10,0.00097656
	2 pow -11,0.00048828
	2 pow -12,0.00024414
	2 pow -13,0.00012207
	2 pow -14,0.00006104
	2 pow -15,0.00003052
	*/
	double map[31][2] = {
		{ 15, 32768 },
		{ 14, 16384 },
		{ 13, 8192 },
		{ 12, 4096 },
		{ 11, 2048 },
		{ 10, 1024 },
		{ 9, 512 },
		{ 8, 256 },
		{ 7, 128 },
		{ 6, 64 },
		{ 5, 32 },
		{ 4, 16 },
		{ 3, 8 },
		{ 2, 4 },
		{ 1, 2 },
		{ 0, 1 },
		{ -1, 0.50000000 },
		{ -2, 0.25000000 },
		{ -3, 0.12500000 },
		{ -4, 0.06250000 },
		{ -5, 0.03125000 },
		{ -6, 0.01562500 },
		{ -7, 0.00781250 },
		{ -8, 0.00390625 },
		{ -9, 0.00195313 },
		{ -10, 0.00097656 },
		{ -11, 0.00048828 },
		{ -12, 0.00024414 },
		{ -13, 0.00012207 },
		{ -14, 0.00006104 },
		{ -15, 0.00003052 }
	};

	if (!dest) { return -1; }

	// Product N
	// Get Exponent
	for (idx = 0; idx<sizeof(map) / sizeof(map[0]); idx++){
		//PSU_DEBUG_PRINT(MSG_ALERT, "idx=%d", idx);
		if (scale == map[idx][1]){
			save_idx = idx;
			exponent = map[idx][0];
			PSU_DEBUG_PRINT(MSG_DEBUG, "exponent=%d", exponent);
			break;
		}
	}

	// If Wrong Scale Value (Scale Value Must be (2 pow 15) ~ (2 pow -15))
	if (save_idx == -1){

		// Exception : if input scale is 0, use 2^0 as default
		if (scale == 0){
			save_idx = 15;
		}
		else{
			PSU_DEBUG_PRINT(MSG_ALERT, "Wrong Scale Value !");
			return 1;
		}
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "save_idx = %d", save_idx);

	tempN = exponent;
	scale_sign = (tempN & (0x8000)) >> 15;
	PSU_DEBUG_PRINT(MSG_DEBUG, "scale_sign=%d", scale_sign);
	tempN &= 0x0f;
	tempN |= (scale_sign << 4);

	PSU_DEBUG_PRINT(MSG_DEBUG, "tempN=%xH", tempN);

	// Product Y
	tempY = value /= map[save_idx][1];
	PSU_DEBUG_PRINT(MSG_DEBUG, "tempY=%d", tempY);

	value_sign = (tempY & (0x8000)) >> 15;
	PSU_DEBUG_PRINT(MSG_DEBUG, "value_sign=%d", value_sign);
	tempY &= (0x03ff);//Y_VALUE_MASK;
	tempY |= (value_sign << 10);

	PSU_DEBUG_PRINT(MSG_DEBUG, "tempY=%xH(%d)", tempY, tempY);

	result = ((tempN << 11) | tempY);

	PSU_DEBUG_PRINT(MSG_DEBUG, "result=%04xH", result);

	// Copy Result To Destination Buffer
	// low byte
	dest[0] = *(&result);
	// High byte
	dest[1] = *(((char*)&result + 1));

	return 0;
}

int PMBUSHelper::ProductReadCMDBuffer(PMBUSCOMMAND_t* pmBusCommand, unsigned char* sendBuffer, unsigned int* currentIO, unsigned int idx, unsigned int command, unsigned int responseDataLength){

	unsigned int baseIndex = 0;
	int buffer_len = 0;

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){

			sendBuffer[baseIndex++] = 0x41;
			sendBuffer[baseIndex++] = 0x44;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			sendBuffer[baseIndex++] = command;

			// May Have 0x0d Command
			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = responseDataLength;

			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;

			buffer_len = baseIndex;
		}
		else if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){

			sendBuffer[baseIndex++] = 0x41;
			sendBuffer[baseIndex++] = 0x44;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			sendBuffer[baseIndex++] = command;

			// May Have 0x0d Command
			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			for (unsigned int len = 0; len < pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength; len++){
				sendBuffer[baseIndex++] = pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len];// Addtional Data [len]

				// Addidtional Data May Have Data 0x0d 
				if (sendBuffer[baseIndex - 1] == 0x0d){
					sendBuffer[baseIndex++] = 0x0d;
				}
				//
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = responseDataLength;

			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;

			buffer_len = baseIndex;

		}
		break;

	case IOACCESS_HID:
		if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){

			sendBuffer[baseIndex++] = 0x05;           // Report ID is 0x05
			sendBuffer[baseIndex++] = 0x0a;
			sendBuffer[baseIndex++] = 0x41;
			sendBuffer[baseIndex++] = 0x44;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			sendBuffer[baseIndex++] = command;        // Command

			// May Have 0x0d Command
			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = responseDataLength; // Response Data Length

			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;

			sendBuffer[1] = (baseIndex - 2);
			buffer_len = baseIndex;

			sendBuffer[baseIndex++] = 0x01;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;

			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x01;
			sendBuffer[baseIndex++] = responseDataLength; // Response Data Length
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x02;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = responseDataLength; // Response Data Length

			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x01; //
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;

			for (int local = baseIndex; local<64; local++){
				sendBuffer[local] = 0;
			}

#if 0
			sendBuffer[35] = 0x00;
			sendBuffer[36] = 0x00;
			sendBuffer[37] = 0x00;
			sendBuffer[38] = 0x00;
			sendBuffer[39] = 0x00;
			sendBuffer[40] = 0x00;
			sendBuffer[41] = 0x00;
			sendBuffer[42] = 0x00;
			sendBuffer[43] = 0x00;
			sendBuffer[44] = 0x00;
			sendBuffer[45] = 0x00;
			sendBuffer[46] = 0x00;
			sendBuffer[47] = 0x00;

			sendBuffer[48] = 0x00;
			sendBuffer[49] = 0x00;
			sendBuffer[50] = 0x00;
			sendBuffer[51] = 0x00;
			sendBuffer[52] = 0x00;
			sendBuffer[53] = 0x00;
			sendBuffer[54] = 0x00;
			sendBuffer[55] = 0x00;
			sendBuffer[56] = 0x00;
			sendBuffer[57] = 0x00;
			sendBuffer[58] = 0x00;
			sendBuffer[59] = 0x00;
			sendBuffer[60] = 0x00;
			sendBuffer[61] = 0x00;
			sendBuffer[62] = 0x00;
			sendBuffer[63] = 0x00;
#endif
		}
		else if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){

			sendBuffer[baseIndex++] = 0x05;// Report ID is 0x05
			sendBuffer[baseIndex++] = 0x0c + (pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength - 2);// Data Length
			sendBuffer[baseIndex++] = 0x41;
			sendBuffer[baseIndex++] = 0x44;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			sendBuffer[baseIndex++] = command; // Command

			// May Have 0x0d Command
			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			for (unsigned int len = 0; len < pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength; len++){
				sendBuffer[baseIndex++] = pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len];// Addtional Data [len]

				// Addidtional Data May Have Data 0x0d 
				if (sendBuffer[baseIndex - 1] == 0x0d){
					sendBuffer[baseIndex++] = 0x0d;
				}
				//

			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = responseDataLength; // Response Data Length

			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}

			sendBuffer[baseIndex++] = 0x0d;
			sendBuffer[baseIndex++] = 0x0a;

			sendBuffer[1] = (baseIndex - 2);
			buffer_len = baseIndex;

			sendBuffer[baseIndex++] = 0x00;

			for (unsigned int target = baseIndex; target < 25; target++){
				sendBuffer[baseIndex++] = 0x00;
			}

			sendBuffer[25] = 0x01;
			sendBuffer[26] = responseDataLength; // Response Data Length
			sendBuffer[27] = 0x00;
			sendBuffer[28] = 0x00;
			sendBuffer[29] = 0x02;
			sendBuffer[30] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[31] = responseDataLength; // Response Data Length

			sendBuffer[32] = 0x00;
			sendBuffer[33] = 0x01; //
			sendBuffer[34] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[35] = 0x00;
			sendBuffer[36] = 0x00;
			sendBuffer[37] = 0x00;
			sendBuffer[38] = 0x00;
			sendBuffer[39] = 0x00;
			sendBuffer[40] = 0x00;
			sendBuffer[41] = 0x00;
			sendBuffer[42] = 0x00;
			sendBuffer[43] = 0x00;
			sendBuffer[44] = 0x00;
			sendBuffer[45] = 0x00;
			sendBuffer[46] = 0x00;
			sendBuffer[47] = 0x00;

			sendBuffer[48] = 0x00;
			sendBuffer[49] = 0x00;
			sendBuffer[50] = 0x00;
			sendBuffer[51] = 0x00;
			sendBuffer[52] = 0x00;
			sendBuffer[53] = 0x00;
			sendBuffer[54] = 0x00;
			sendBuffer[55] = 0x00;
			sendBuffer[56] = 0x00;
			sendBuffer[57] = 0x00;
			sendBuffer[58] = 0x00;
			sendBuffer[59] = 0x00;
			sendBuffer[60] = 0x00;
			sendBuffer[61] = 0x00;
			sendBuffer[62] = 0x00;
			sendBuffer[63] = 0x00;
		}

		break;

	case IOACCESS_PICKIT:

		if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x03;// Report ID is 0x03
			sendBuffer[baseIndex++] = 0x0e;
			sendBuffer[baseIndex++] = 0x81;
			sendBuffer[baseIndex++] = 0x84;
			sendBuffer[baseIndex++] = 0x02;// ??? (Maybe This Field Indicates Length of "Slave Address + Command")
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			sendBuffer[baseIndex++] = command;// Command

			sendBuffer[baseIndex++] = 0x83;
			sendBuffer[baseIndex++] = 0x84;
			sendBuffer[baseIndex++] = 0x01;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = 0x89;
			sendBuffer[baseIndex++] = responseDataLength; // Response Data Length
			sendBuffer[baseIndex++] = 0x82;
			sendBuffer[baseIndex++] = 0x1f;
			sendBuffer[baseIndex++] = 0x77;

			buffer_len = baseIndex;

			for (int local = baseIndex; local < 65; local++){
				sendBuffer[local] = 0;
			}
		}
		else if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){

			sendBuffer[baseIndex++] = 0x00;
			sendBuffer[baseIndex++] = 0x03;// Report ID is 0x03
			sendBuffer[baseIndex++] = 0x0e + pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength;// Should be decided dynanically
			sendBuffer[baseIndex++] = 0x81;
			sendBuffer[baseIndex++] = 0x84;
			sendBuffer[baseIndex++] = pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength + 0x02;//0x02;// ??? (Maybe This Field Indicates "Slave Address + CMD")
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			sendBuffer[baseIndex++] = command;// Command

			// Write Data
			for (unsigned int len = 0; len < (pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength); len++){
				sendBuffer[baseIndex++] = pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len];
			}

			sendBuffer[baseIndex++] = 0x83;
			sendBuffer[baseIndex++] = 0x84;
			sendBuffer[baseIndex++] = 0x01;
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			sendBuffer[baseIndex++] = 0x89;
			sendBuffer[baseIndex++] = responseDataLength; // Response Data Length
			sendBuffer[baseIndex++] = 0x82;
			sendBuffer[baseIndex++] = 0x1f;
			sendBuffer[baseIndex++] = 0x77;

			for (int local = baseIndex; local<65; local++){
				sendBuffer[local] = 0;
			}

			buffer_len = baseIndex;
		}

		break;

	case IOACCESS_TOTALPHASE:

		if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
			
			sendBuffer[baseIndex++] = 1;// write bytes
			sendBuffer[baseIndex++] = responseDataLength;// Read bytes Length
			sendBuffer[baseIndex++] = PMBUSHelper::GetSlaveAddress();// Slave Address
			sendBuffer[baseIndex++] = command;// Command

			buffer_len = baseIndex;
		}
		else if (pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){

			sendBuffer[0] = pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength; // Write Bytes
			//PSU_DEBUG_PRINT(MSG_ALERT, "%s:pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength=%d", __FUNCTIONW__, pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength);
			sendBuffer[1] = responseDataLength;// Read bytes Length
			sendBuffer[2] = PMBUSHelper::GetSlaveAddress();// Slave Address
			sendBuffer[3] = command;// Command
			//sendBuffer[4] = sendBuffer[0];

			// Data start from index 4
			for (unsigned char len = 0; len < pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength; len++){
				sendBuffer[4 + len] = pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len];
				baseIndex = (4 + len);
			}

			baseIndex++;

			//PSU_DEBUG_PRINT(MSG_ALERT, "%s:baseIndex=%d", __FUNCTIONW__, baseIndex);

			//Update Write Data Bytes Length For Block Wrire - Block Read Commands
			sendBuffer[0] = baseIndex - 3;

			buffer_len = baseIndex;

		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	return buffer_len;
}

int PMBUSHelper::ProductWriteCMDBuffer(unsigned int *currentIO, unsigned char *buff, unsigned int sizeOfBuffer, unsigned char cmd, unsigned char *dataBuffer, unsigned int sizeOfDataBuffer){

	unsigned int pec_start_index = 0;

	if (buff == NULL || dataBuffer == NULL){
		PSU_DEBUG_PRINT(MSG_ALERT, "Buff or Data Buffer = NULL");
		return 0;
	}

	if (sizeOfBuffer < 64){
		PSU_DEBUG_PRINT(MSG_ALERT, "Size of Buffer Less Than 64");
		return 0;
	}

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		buff[0] = 0x41;
		buff[1] = 0x54;
		buff[2] = PMBUSHelper::GetSlaveAddress(); // Slave Address
		buff[3] = cmd; // CMD
		// Data start from index 4
		for (unsigned int idx = 0; idx < sizeOfDataBuffer; idx++){
			buff[4+idx] = dataBuffer[idx];
			pec_start_index = (4 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		buff[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buff + 2, 2 + sizeOfDataBuffer);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", buff[pec_start_index]);

		// Fill Last 2 
		pec_start_index++;

		if (buff[pec_start_index - 1] == 0x0d){
			buff[pec_start_index++] = 0x0d;
		}

		buff[pec_start_index++] = 0x0D;
		buff[pec_start_index++] = 0x0A;

		break;

	case IOACCESS_HID:

		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		buff[0] = 0x05;
		
		buff[2] = 0x41;
		buff[3] = 0x54;
		buff[4] = PMBUSHelper::GetSlaveAddress(); // Slave Address
		buff[5] = cmd; // CMD
		// Data start from index 6
		for (unsigned int idx = 0; idx < sizeOfDataBuffer; idx++){
			buff[6 + idx] = dataBuffer[idx];
			pec_start_index = (6 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		buff[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buff + 4, 2 + sizeOfDataBuffer);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", buff[pec_start_index]);

		// Fill Last 2 
		pec_start_index++;

		if (buff[pec_start_index-1]==0x0d){
			buff[pec_start_index++] = 0x0d;
		}

		buff[pec_start_index++] = 0x0D;
		buff[pec_start_index++] = 0x0A;

		// Fill Length
		buff[1] = pec_start_index - 2;

		break;

	case IOACCESS_PICKIT:

		buff[0] = 0x00;
		buff[1] = 0x03;

		buff[3] = 0x81;
		buff[4] = 0x84;
		buff[5] = sizeOfDataBuffer + 3;
		buff[6] = PMBUSHelper::GetSlaveAddress(); // Slave Address
		buff[7] = cmd; // CMD

		// Data start from index 6
		for (unsigned int idx = 0; idx < sizeOfDataBuffer; idx++){
			buff[8 + idx] = dataBuffer[idx];
			pec_start_index = (8 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		buff[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buff + 6, 2 + sizeOfDataBuffer);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", buff[pec_start_index]);

		// Fill Last 3
		pec_start_index++;
		buff[pec_start_index++] = 0x82;
		buff[pec_start_index++] = 0x1f;
		buff[pec_start_index++] = 0x77;

		// Fill Total Length
		buff[2] = pec_start_index - 3;

		break;

	case IOACCESS_TOTALPHASE:

		buff[0] = sizeOfDataBuffer; // Write Bytes
		buff[1] = 0; // Read Bytes
		buff[2] = PMBUSHelper::GetSlaveAddress();
		buff[3] = cmd;

		// Data start from index 4
		for (unsigned int idx = 0; idx < sizeOfDataBuffer; idx++){
			buff[4 + idx] = dataBuffer[idx];
			pec_start_index = (4 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		buff[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buff + 2, 2 + sizeOfDataBuffer);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", buff[pec_start_index]);

		pec_start_index++;

		// Update Write Bytes For Write CMD
		buff[0] = pec_start_index - 3;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return pec_start_index;
}

void PMBUSHelper::ProductDataBuffer(PMBUSCOMMAND_t* pmBusCommand, unsigned int* currentIO, unsigned int cmdIndex, unsigned int responseDataLength){

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		// Copy Only The Data Bytes To DataBuff
		for (unsigned int idx = 0; idx < responseDataLength; idx++){
			pmBusCommand[cmdIndex].m_recvBuff.m_dataBuff[idx] = pmBusCommand[cmdIndex].m_recvBuff.m_recvBuff[idx];
		}

		break;

	case IOACCESS_HID:
		// Copy Only The Data Bytes To DataBuff
		for (unsigned int idx = 0; idx < responseDataLength; idx++){
			pmBusCommand[cmdIndex].m_recvBuff.m_dataBuff[idx] = pmBusCommand[cmdIndex].m_recvBuff.m_recvBuff[idx + 6];
		}

		break;

	case IOACCESS_PICKIT:
		// 86 0a 80 10 [01] 10 [ac] 10 [22] 81 1c 77
		// 86 0a 80 10 [01] 10 [f0] 10 [e2] 81 1c 77
		// Copy Only The Data Bytes To DataBuff
		for (unsigned int idx = 0; idx < responseDataLength; idx++){
			pmBusCommand[cmdIndex].m_recvBuff.m_dataBuff[idx] = pmBusCommand[cmdIndex].m_recvBuff.m_recvBuff[4 + idx * 2];
		}

		break;

	case IOACCESS_TOTALPHASE:
		// Copy Only The Data Bytes To DataBuff
		for (unsigned int idx = 0; idx < responseDataLength; idx++){
			pmBusCommand[cmdIndex].m_recvBuff.m_dataBuff[idx] = pmBusCommand[cmdIndex].m_recvBuff.m_recvBuff[idx];
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Wrong !");
		break;
	}

}

long PMBUSHelper::HexToDecimal(wxString string){
	long decimal = strtol(string.c_str(), NULL, 16);

	return decimal;
}

void PMBUSHelper::GetNowDateTimeString(wxString& string){	
	wxDateTime datetime = wxDateTime::Now();

	string += wxString::Format("%d", datetime.GetYear());
	string += "-";
	string += wxString::Format("%02d", datetime.GetMonth() + 1);
	string += "-";
	string += wxString::Format("%02d", datetime.GetDay());
	string += "-";
	string += wxString::Format("%02d", datetime.GetHour());
	string += "-";
	string += wxString::Format("%02d", datetime.GetMinute());
	string += "-";
	string += wxString::Format("%02d", datetime.GetSecond());
}

void PMBUSHelper::PrintISPCheckStatusError(unsigned char error){

	switch (error){

	case 0x51:
		PSU_DEBUG_PRINT(MSG_ERROR, "Not in Programming Mode");
		break;

	case 0x31:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP CheckSum Error");
		break;

	case 0x32:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Write to Flash Memory Error");
		break;

	case 0x33:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Incorrect Image (Incorrect SOH,EOF)");
		break;

	case 0x35:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Image Checksum Error");
		break;

	case 0x36:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Busy");
		break;

	case 0x37:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Timeout");
		break;

	case 0x38:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Timeout1");
		break;

	case 0x39:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Area Erase Failed");
		break;

	case 0x3A:
		PSU_DEBUG_PRINT(MSG_ERROR, "Pass-through received checksum error");
		break;

	case 0x3B:
		PSU_DEBUG_PRINT(MSG_ERROR, "Pass-through received command incorrect");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Check Status (F3H) Something Error, error = %d", error);
		break;
	}

}

#define REBOOT_OK  0x00
unsigned char PMBUSHelper::IsISPRebootCheckResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer){

	// 0x00 0xEC 0x0D 0x0A 0x4F 0x4B 0x0D 0x0A
	// 15  08  41  54  02  00  [00]  83  0d  0a

	unsigned char result = response_ok;

#ifndef IGNORE_ISP_RESPONSE_ERROR

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		if (buffer[0] != REBOOT_OK || buffer[4] != 0x4F || buffer[5] != 0x4B ){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Reboot Check Response Data Mismatch, Return Code = %02xh", buffer[0]);
		}

		break;

	case IOACCESS_HID:

		//
		if (buffer[6] != REBOOT_OK){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Reboot Check Response Data Mismatch, Return Code = %02xh", buffer[6]);
		}

		break;

	case IOACCESS_PICKIT:

		//
		if (buffer[4] != REBOOT_OK){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Reboot Check Response Data Mismatch, Return Code = %02xh", buffer[4]);
		}

		break;

	case IOACCESS_TOTALPHASE:

		if (buffer[0] != REBOOT_OK){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Reboot Check Response Data Mismatch, Return Code = %02xh", buffer[0]);
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Reboot Check Response Something Error");
		break;
	}

#endif

	return result;
}

unsigned char PMBUSHelper::IsISPStartVerifyResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer, unsigned char target){
	
	// 0x60 0xCB 0x0D 0x0A 0x4F 0x4B 0x0D 0x0A
	// 15   08   41   54   02   00   ff   ff   0d   0a 

	unsigned char result = response_ok;

#ifndef IGNORE_ISP_RESPONSE_ERROR

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		if(buffer[0] != target){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start Verify Response Data Mismatch, Return Code = %02xh", buffer[0]);
		}

		break;

	case IOACCESS_HID:

		//
		if (buffer[6] != target){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start Verify Response Data Mismatch, Return Code = %02xh", buffer[6]);
		}

		break;

	case IOACCESS_PICKIT:

		//
		if (buffer[4] != target){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start Verify Response Data Mismatch, Return Code = %02xh", buffer[6]);
		}

		break;

	case IOACCESS_TOTALPHASE:

		if (buffer[0] != target){
			result = response_ng;
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start Verify Response Data Mismatch, Return Code = %02xh", buffer[0]);
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start Verify Something Error");
		break;
	}

#endif

	return result;
}

unsigned char PMBUSHelper::IsISPCheckStatusResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer){
	
	// 0x30 0xC1 0x0D 0x0A 0x4F 0x4B 0x0D 0x0A
	// 15   08   41   54   02   00   ff   ff   0d   0a

	unsigned char result = response_ok;

#ifndef IGNORE_ISP_RESPONSE_ERROR

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		if (buffer[0] != 0x30){
			result = response_ng;
			PrintISPCheckStatusError(buffer[0]);
		}

		break;

	case IOACCESS_HID:

		if (buffer[6] != 0x30){
			result = response_ng;
			PrintISPCheckStatusError(buffer[6]);
		}

		break;

	case IOACCESS_PICKIT:

		if (buffer[4] != 0x30){
			result = response_ng;
			PrintISPCheckStatusError(buffer[4]);
		}

		break;

	case IOACCESS_TOTALPHASE:

		if (buffer[0] != 0x30){
			result = response_ng;
			PrintISPCheckStatusError(buffer[0]);
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

#endif

	return result;
}

unsigned char PMBUSHelper::IsResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer){
	// 0x0d, 0x0a, 0x4f, 0x4b, 0x0d, 0x0a
	// 0x15  0x07  0x41  0x43  0x02  0x4f  0x4b  0x0d  0x0a <- If OK
	// 0x15  0x07  0x41  0x43  0x02  0x4e  0x47  0x0d  0x0a <- If NG
	// 86  04  80  81  1c  77 Pickit OK
	unsigned char ok_buffer[6] = { 0x0d, 0x0a, 0x4f, 0x4b, 0x0d, 0x0a };
	unsigned char ok_hid_buffer[9] = { 0x15, 0x07, 0x41, 0x43, 0x02, 0x4f, 0x4b, 0x0d, 0x0a };
	unsigned char ok_pickit_buffer[6] = { 0x86, 0x04, 0x80, 0x81, 0x1c, 0x77 };
	unsigned char result = response_ok;

#ifndef IGNORE_ISP_RESPONSE_ERROR

	switch (*currentIO){
	
	case IOACCESS_SERIALPORT:

		if (sizeOfBuffer < sizeof(ok_buffer) / sizeof(ok_buffer[0])){
			result = response_ng;
			return result;
		}

		for (int idx = 0; idx < sizeof(ok_buffer) / sizeof(ok_buffer[0]); idx++){
			if (buffer[idx] != ok_buffer[idx]){
				result = response_ng;
				break;
			}
		}

		break;

	case IOACCESS_HID:

		if (sizeOfBuffer < sizeof(ok_hid_buffer) / sizeof(ok_hid_buffer[0])){
			result = response_ng;
			return result;
		}

		for (int idx = 0; idx < sizeof(ok_hid_buffer) / sizeof(ok_hid_buffer[0]); idx++){
			if (buffer[idx] != ok_hid_buffer[idx]){
				result = response_ng;
				break;
			}
		}

		break;

	case IOACCESS_PICKIT:

		if (sizeOfBuffer < sizeof(ok_pickit_buffer) / sizeof(ok_pickit_buffer[0])){
			result = response_ng;
			return result;
		}

		for (int idx = 0; idx < sizeof(ok_pickit_buffer) / sizeof(ok_pickit_buffer[0]); idx++){
			if (buffer[idx] != ok_pickit_buffer[idx]){
				result = response_ng;
				break;
			}
		}

		break;

	case IOACCESS_TOTALPHASE:
		if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
			result = response_ng;
		}
		break;
	
	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

#endif

	return result;
}

unsigned int PMBUSHelper::IsI2CBusNotAcknowlwdge(unsigned int *currentIO, unsigned char *buffer, unsigned int SizeOfBuffer){

	unsigned int result = response_ok;
	unsigned int chk_cnt = 0;
	unsigned char usbhid_no_ack[9] = { 0x15, 0x07, 0x41, 0x43, 0x02, 0x4e, 0x47, 0x0d, 0x0a };

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		// Do Handle When I/O is Serial Port
		break;

	case IOACCESS_HID:

		for (unsigned int idx = 0; idx < sizeof(usbhid_no_ack) / sizeof(usbhid_no_ack[0]); idx++){
			if (buffer[idx] != usbhid_no_ack[idx]){
				break;
			}
			else{
				chk_cnt++;
				continue;
			}
		}

		if (chk_cnt == sizeof(usbhid_no_ack) / sizeof(usbhid_no_ack[0])){
			result = response_ng;
		}

		break;

	case IOACCESS_PICKIT:

		if (SizeOfBuffer == 0){
			result = response_ng;
		}

		break;

	case IOACCESS_TOTALPHASE:
		// Do Handle When I/O is Serial Port
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return result;
}

unsigned char PMBUSHelper::ComputeISPDataCheckSum(unsigned char *buffer, unsigned int dataStartIndex, unsigned int dataEndIndex){
	unsigned char CheckSum = 0x00;
	unsigned int Sum = 0x00;

	if (!buffer) { return CheckSum; }

	for (unsigned int idx = dataStartIndex; idx <= dataEndIndex; idx++){
		Sum += buffer[idx];
	}

	CheckSum = 0x0100 - (Sum&0x000000ff);

	return CheckSum;
}

wxString& PMBUSHelper::GetNowTimeString(void){
	// Get Now Time
	wxDateTime dateTime = wxDateTime::UNow();
	_SYSTEMTIME systemTime;
	dateTime.GetAsMSWSysTime(&systemTime);

	// Make Time String
	//timeString = wxString::Format("%d-%d %d:%d.%d", systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wMilliseconds);
	m_timeString = wxString::Format("%04d/%02d/%02d %02d:%02d:%02d.%03d", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

	return m_timeString;
}

void PMBUSHelper::GetPIDAndVIDFromString(wxString string, unsigned int* pid, unsigned int* vid){

	int pid_start_index = string.Find(wxString("PID_"));

	int vid_start_index = string.Find(wxString("VID_"));

	PSU_DEBUG_PRINT(MSG_DEBUG, "pid_start_index=%d, vid_start_index=%d", pid_start_index, vid_start_index);

	wxString sPID = string.SubString(pid_start_index + 4, pid_start_index + 4 + 3);

	wxString sVID = string.SubString(vid_start_index + 4, vid_start_index + 4 + 3);

	PSU_DEBUG_PRINT(MSG_DEBUG, "pid_string=%s, vid_string=%s", sPID.c_str(), sVID.c_str());

	*pid = PMBUSHelper::HexToDecimal(sPID);

	*vid = PMBUSHelper::HexToDecimal(sVID);

}

void PMBUSHelper::SetCurrentCMDTableSize(unsigned int size){
	CurrentCMDTableSize = size;
}

unsigned int PMBUSHelper::GetCurrentCMDTableSize(void){
	return CurrentCMDTableSize;
}

void PMBUSHelper::setWinTitleBase(wxString base){
	m_winTitleBase = base;
}

wxString& PMBUSHelper::getWinTitleBase(void){
	return m_winTitleBase;
}

unsigned int& PMBUSHelper::getCurrentISPTarget(void){
	return CurrentISPTarget;
}

int& PMBUSHelper::getTotalPhaseWriteReadLastError(void){
	return TotalPhaseWriteReadLastError;
}

bool PMBUSHelper::isOwnReadAccess(unsigned int access){
	bool ret = false;

	switch (access){

	case cmd_access_read:
	case cmd_access_br:
	case cmd_access_readwrite:
	case cmd_access_brbw:
	case cmd_access_bwr_read:
	case cmd_access_bwr_readwrite:
		ret = true;
		break;

	case cmd_access_write:
	case cmd_access_bw:
		ret = false;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs !");
		break;

	}

	return ret;
}

int PMBUSHelper::getIndexOfCMD(int cmd, int page){
	int index = -1;

	// If Page is 0
	if (page==0){
		for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
			if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == cmd){
				index = idx;
				break;
			}
		}
	}
	// Have Specified Page 
	else{
		for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
			if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == cmd){
				if (PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_cmdPage == page){
					index = idx;
					break;
				}
			}
		}
	}

	return index;
}

unsigned char& PMBUSHelper::getFWUploadModeCMD(void){
	return m_FWUploadModeCMD;
}

unsigned char& PMBUSHelper::getFWUploadCMD(void){
	return m_FWUploadCMD;
}

unsigned char& PMBUSHelper::getFWUploadStatusCMD(void){
	return m_FWUploadStatusCMD;
}

int PMBUSHelper::getExpectedDataLengthByIO(unsigned int CurrentUseIO, unsigned int CMDResponseDataLength, unsigned char BaseDataLength){

	int length;

	switch (CurrentUseIO){

	case IOACCESS_SERIALPORT:
		length = CMDResponseDataLength + BaseDataLength;
		break;

	case IOACCESS_HID:
		length = CMDResponseDataLength + BaseDataLength + 2;
		break;

	case IOACCESS_PICKIT:
		length = CMDResponseDataLength*2 + BaseDataLength;
		break;

	case IOACCESS_TOTALPHASE:
		length = CMDResponseDataLength;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}
   
	return length;
}

void PMBUSHelper::dumpReceiveBuffer(unsigned char* buffer, int bufferLength){

	if (buffer == NULL || bufferLength < 0) return;

	wxString string("Data : ");

	for (int idx = 0; idx < bufferLength; idx++){
		string += wxString::Format("%02x ", buffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", string.c_str());

}

int PMBUSHelper::ProductE2PRomWriteBuffer(unsigned char fruSlaveAddr, unsigned char* fruContentBuffer, unsigned int idx, unsigned char* sendBuffer, unsigned int* currentIO){
	unsigned int current_index = 0;

	if (sendBuffer == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "Send Buffer = NULL");
		return 0;
	}

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		sendBuffer[0] = 0x41;
		sendBuffer[1] = 0x54;
		sendBuffer[2] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[3] = idx; // Indicates Start Write Offset
		// Data start from index 4
		current_index = 4;
		sendBuffer[current_index++] = fruContentBuffer[idx];

		// Fill Last 2

		if (sendBuffer[current_index - 1] == 0x0d){
			sendBuffer[current_index++] = 0x0d;
		}
		sendBuffer[current_index++] = 0x0D;
		sendBuffer[current_index++] = 0x0A;

		break;

	case IOACCESS_HID:

		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		sendBuffer[0] = 0x05;

		sendBuffer[2] = 0x41;
		sendBuffer[3] = 0x54;
		sendBuffer[4] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[5] = idx; // Indicates Start Write Offset
		// Data start from index 6
		current_index = 6;
		sendBuffer[current_index++] = fruContentBuffer[idx];

		// Fill Last 2

		if (sendBuffer[current_index - 1] == 0x0d){
			sendBuffer[current_index++] = 0x0d;
		}
		sendBuffer[current_index++] = 0x0D;
		sendBuffer[current_index++] = 0x0A;

		sendBuffer[1] = current_index - 2;

		break;

	case IOACCESS_PICKIT:

		// 0x03 [0x06] 0x81 0x84 [0x05] [0xB6] [0xEC] [0x00] [0x08] [0xE0] 0x82 0x1f 0x77
		sendBuffer[0] = 0x00;
		sendBuffer[1] = 0x03;

		sendBuffer[3] = 0x81;
		sendBuffer[4] = 0x84;
		sendBuffer[5] = 1 + 2;
		sendBuffer[6] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[7] = idx; // Indicates Start Write Offset

		// Data start from index 8
		current_index = 8;
		sendBuffer[current_index++] = fruContentBuffer[idx];

		// Fill Last 3
		sendBuffer[current_index++] = 0x82;
		sendBuffer[current_index++] = 0x1f;
		sendBuffer[current_index++] = 0x77;

		// Fill Total Length
		sendBuffer[2] = current_index - 3;

		break;

	case IOACCESS_TOTALPHASE:

		sendBuffer[0] = 0; // Write Bytes(Would be Updated later)
		sendBuffer[1] = 0; // Read Bytes
		sendBuffer[2] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[3] = idx; // Indicates Start Write Offset

		// Data start from index 4
		current_index = 4;
		sendBuffer[current_index++] = fruContentBuffer[idx];

		// Update Write Bytes For Write CMD
		sendBuffer[0] = current_index - 3;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return current_index;
}

int PMBUSHelper::ProductE2PRomReadBuffer(unsigned char fruSlaveAddr, unsigned int idx, unsigned char* sendBuffer, unsigned int* currentIO){
	unsigned int baseIndex = 0;
	int buffer_len = 0;

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = fruSlaveAddr | 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		buffer_len = baseIndex;


		break;

	case IOACCESS_HID:

		sendBuffer[baseIndex++] = 0x05;           // Report ID is 0x05
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = fruSlaveAddr | 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		sendBuffer[1] = (baseIndex - 2);
		buffer_len = baseIndex;

		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x02;
		sendBuffer[baseIndex++] = fruSlaveAddr | 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x01; //
		sendBuffer[baseIndex++] = fruSlaveAddr | 0x01;

		for (int local = baseIndex; local<64; local++){
			sendBuffer[local] = 0;
		}

		break;

	case IOACCESS_PICKIT:

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x03;// Report ID is 0x03
		sendBuffer[baseIndex++] = 0x0e;
		sendBuffer[baseIndex++] = 0x81;
		sendBuffer[baseIndex++] = 0x84;
		sendBuffer[baseIndex++] = 0x02;// ??? (Maybe This Field Indicates Length of "Slave Address + Command")
		sendBuffer[baseIndex++] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;// Offset

		sendBuffer[baseIndex++] = 0x83;
		sendBuffer[baseIndex++] = 0x84;
		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = fruSlaveAddr | 0x01;
		sendBuffer[baseIndex++] = 0x89;
		sendBuffer[baseIndex++] = 1; // Response Data Length
		sendBuffer[baseIndex++] = 0x82;
		sendBuffer[baseIndex++] = 0x1f;
		sendBuffer[baseIndex++] = 0x77;

		buffer_len = baseIndex;

		for (int local = baseIndex; local < 65; local++){
			sendBuffer[local] = 0;
		}

		break;

	case IOACCESS_TOTALPHASE:

		sendBuffer[baseIndex++] = 1;// write bytes
		sendBuffer[baseIndex++] = 1;// read bytes
		sendBuffer[baseIndex++] = fruSlaveAddr;// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;

		buffer_len = baseIndex;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	return buffer_len;
}

void PMBUSHelper::PrintFRUContent(unsigned char* contentBuffer, unsigned int dumpSize){
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------------------------------------------------");
	wxString data("");
	unsigned int addr = 0x00;

	for (unsigned int idx = 0; idx < dumpSize; idx++){

		if (idx != 0 && idx % 0x10 == 0){
			addr = (idx - 0x10);
			PSU_DEBUG_PRINT(MSG_ALERT, "[%08x]%s", addr, data.c_str());
			data.Clear();
		}

		data += wxString::Format("%02x", contentBuffer[idx]);
		data += wxString::Format(" ");

		// Last
		if (idx == (dumpSize - 1)){
			PSU_DEBUG_PRINT(MSG_ALERT, "[%08x]%s", addr + 0x10, data.c_str());
			data.Clear();
			break;
		}
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------------------------------------------------");
}

bool PMBUSHelper::ReJudgeIOThreadSendFailure(bool failed, unsigned int CurrentUseIO){

	bool failure_occurs = failed;

	switch (CurrentUseIO){

	case IOACCESS_SERIALPORT:
	case IOACCESS_HID:
	case IOACCESS_PICKIT:
		// Don't Update Original Result
		break;

	case IOACCESS_TOTALPHASE:
		// Ingore TotalPhase Send Error  
		failure_occurs = false;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "%s:Something Error Occurs !", __FUNCTIONW__);
		break;
	}

	return failure_occurs;
}

unsigned int PMBUSHelper::GetBytesToReadOfWriteCMD(unsigned int CurrentUseIO, unsigned int BaseLength){
	unsigned int BytesToRead;

	switch (CurrentUseIO){

	case IOACCESS_SERIALPORT:
		BytesToRead = BaseLength;
		break;

	case IOACCESS_HID:
	case IOACCESS_TOTALPHASE:
		BytesToRead = BaseLength + 1;
		break;

	case IOACCESS_PICKIT:
		BytesToRead = 0;// Fill 0 If IO is Pickit
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

	return BytesToRead;
}

wxString& PMBUSHelper::getDefaultMFR_ID(void){
	return m_default_mfr_id;
}

wxString& PMBUSHelper::getDefaultMFR_MODEL(void){
	return m_default_mfr_model;
}

wxString& PMBUSHelper::getDefaultMFR_REVISION(void){
	return m_default_mfr_revision;
}

wxString& PMBUSHelper::getDefaultMFR_LOCATION(void){
	return m_default_mfr_location;
}

wxString& PMBUSHelper::getDefaultMFR_DATE(void){
	return m_default_mfr_date;
}

wxString& PMBUSHelper::getDefaultMFR_SERIAL(void){
	return m_default_mfr_serial;
}
