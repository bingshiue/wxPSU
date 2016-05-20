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

#define N_SIGN_BIT (0x10)

double PMBUSHelper::ParseLinearDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer){
	double result = 0;
	int Y = 0, N = 0;
	int N_sign = positive;
	char tempN = 0;

	if (!buffer) { return -1; }

	unsigned int rawData = buffer[0] | (buffer[1] << 8);

	Y = rawData & Y_VALUE_MASK;


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
		tempN = N | 0x80 | 0x60; 
		PSU_DEBUG_PRINT(MSG_DETAIL, "Temp N = %d", tempN);

		result = (double)(Y * pow(2.0f, tempN));

		break;

	default :
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !");
		PSU_DEBUG_PRINT(MSG_ALERT, "Negative N_sign = %d", N_sign);
		break;
	}


	PSU_DEBUG_PRINT(MSG_DETAIL, "buffer[0]=%d,buffer[1]=%d,rawData=%d", buffer[0], buffer[1], rawData);
	PSU_DEBUG_PRINT(MSG_DETAIL, "Y=%d,N=%d,Result=%4.2f", Y, N, result);

	return result;
}
