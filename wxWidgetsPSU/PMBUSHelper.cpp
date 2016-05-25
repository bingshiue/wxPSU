/**
 * @file PMBUSHelper.cpp
 */

#include "math.h"
#include "PMBUSHelper.h"

PMBUSSTATUS_t PMBUSHelper::m_pmbusStatus;

PMBUSSTATUS_t* PMBUSHelper::GetPMBusStatus(void){
	return &m_pmbusStatus;
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
		PSU_DEBUG_PRINT(MSG_ALERT, "Wrong Scale Value !");
		return 1;
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

long PMBUSHelper::HexToDecimal(wxString string){
	long decimal = strtol(string.c_str(), NULL, 16);

	return decimal;
}