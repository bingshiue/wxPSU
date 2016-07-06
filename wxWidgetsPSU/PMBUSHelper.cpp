/**
 * @file PMBUSHelper.cpp
 */

#include "math.h"
#include "pec.h"
#include "PMBUSHelper.h"

unsigned char PMBUSHelper::m_slaveAddress;
PMBUSSTATUS_t PMBUSHelper::m_pmbusStatus;
AppSettings_t* PMBUSHelper::m_appSettings;

void PMBUSHelper::SetSlaveAddress(unsigned char slaveAddress){
	m_slaveAddress = slaveAddress;
}

unsigned char& PMBUSHelper::GetSlaveAddress(void){
	return m_slaveAddress;
}

PMBUSSTATUS_t* PMBUSHelper::GetPMBusStatus(void){
	return &m_pmbusStatus;
}

void PMBUSHelper::SetAppSettings(AppSettings_t* appSettings){
	m_appSettings = appSettings;
}

AppSettings_t* PMBUSHelper::GetAppSettings(void){
	return m_appSettings;
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
	PSU_DEBUG_PRINT(MSG_DETAIL, "Y=%d,N=%d,Result=%4.5f", Y, N, result);

	return result;

}

int PMBUSHelper::ProductFakeLinearData(unsigned char *dest, double value, double scale){
	short result = 0;

	result = (short)(value / scale);

	dest[0] = *((char*)&result);
	dest[1] = *((char*)&result+1);

	PSU_DEBUG_PRINT(MSG_ALERT, "dest[0]=%02x, dest[1]=%02x", dest[0], dest[1]);

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
			PSU_DEBUG_PRINT(MSG_DETAIL, "exponent=%d", exponent);
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

	PSU_DEBUG_PRINT(MSG_DETAIL, "save_idx = %d", save_idx);

	tempN = exponent;
	scale_sign = (tempN & (0x8000)) >> 15;
	PSU_DEBUG_PRINT(MSG_DETAIL, "scale_sign=%d", scale_sign);
	tempN &= 0x0f;
	tempN |= (scale_sign << 4);

	PSU_DEBUG_PRINT(MSG_DETAIL, "tempN=%xH", tempN);

	// Product Y
	tempY = value /= map[save_idx][1];
	PSU_DEBUG_PRINT(MSG_DETAIL, "tempY=%d", tempY);

	value_sign = (tempY & (0x8000)) >> 15;
	PSU_DEBUG_PRINT(MSG_DETAIL, "value_sign=%d", value_sign);
	tempY &= (0x03ff);//Y_VALUE_MASK;
	tempY |= (value_sign << 10);

	PSU_DEBUG_PRINT(MSG_DETAIL, "tempY=%xH(%d)", tempY, tempY);

	result = ((tempN << 11) | tempY);

	PSU_DEBUG_PRINT(MSG_DETAIL, "result=%04xH", result);

	// Copy Result To Destination Buffer
	// low byte
	dest[0] = *(&result);
	// High byte
	dest[1] = *(((char*)&result + 1));

	return 0;
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
		buff[pec_start_index++] = 0x0D;
		buff[pec_start_index++] = 0x0A;

		// Fill Length
		buff[1] = pec_start_index - 2;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return pec_start_index;
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

unsigned char PMBUSHelper::IsResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer){
	// 0x0d, 0x0a, 0x4f, 0x4b, 0x0d, 0x0a
	// 0x15  0x07  0x41  0x43  0x02  0x4f  0x4b  0x0d  0x0a <- If OK
	// 0x15  0x07  0x41  0x43  0x02  0x4e  0x47  0x0d  0x0a <- If NG
	unsigned char ok_buffer[6] = { 0x0d, 0x0a, 0x4f, 0x4b, 0x0d, 0x0a };
	unsigned char ok_hid_buffer[9] = { 0x15, 0x07, 0x41, 0x43, 0x02, 0x4f, 0x4b, 0x0d, 0x0a };
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
	
	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

#endif

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