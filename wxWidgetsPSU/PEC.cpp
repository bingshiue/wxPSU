/**
 * @file PEC.cpp
 */

#include "PEC.h"

unsigned short PMBusSlave_Crc8MakeBitwise(unsigned char PMBusSlave_CRC, unsigned char PMBusSlave_Poly, unsigned char *PMBusSlave_Pmsg, unsigned int PMBusSlave_MsgSize)
{
	unsigned int i, j, carry;
	unsigned char msg;

	PMBusSlave_CRC = *PMBusSlave_Pmsg++;        	// first byte loaded in "crc"
	for (i = 0; i < PMBusSlave_MsgSize - 1; i++)
	{
		msg = *PMBusSlave_Pmsg++;                   // next byte loaded in "msg"

		for (j = 0; j < 8; j++)
		{
			carry = PMBusSlave_CRC & 0x80;               			// check if MSB=1
			PMBusSlave_CRC = (PMBusSlave_CRC << 1) | (msg >> 7);    // Shift 1 bit of next byte into crc
			if (carry) PMBusSlave_CRC ^= PMBusSlave_Poly;      		// If MSB = 1, perform XOR
			msg <<= 1;                  							// Shift left msg byte by 1
			msg &= 0x00FF;
		}
	}
	// The previous loop computes the CRC of the input bit stream. To this,
	// 8 trailing zeros are padded and the CRC of the resultant value is
	// computed. This gives the final CRC of the input bit stream.
	for (j = 0; j < 8; j++)
	{
		carry = PMBusSlave_CRC & 0x80;
		PMBusSlave_CRC <<= 1;
		if (carry) PMBusSlave_CRC ^= PMBusSlave_Poly;
	}

	PMBusSlave_CRC &= 0x00FF;	//We only want one byte (lower)

	return(PMBusSlave_CRC);
}