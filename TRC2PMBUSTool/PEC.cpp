/**
 * @file PEC.cpp
 */

#include "PEC.h"
#include "PMBUSLog.h"

unsigned short PMBusSlave_Crc8MakeBitwise(unsigned char PMBusSlave_CRC, unsigned char PMBusSlave_Poly, unsigned char *PMBusSlave_Pmsg, unsigned int PMBusSlave_MsgSize)
{
	unsigned int i, j, carry;
	unsigned char msg;

	PMBusSlave_CRC = *PMBusSlave_Pmsg++;        	// first byte loaded in "crc"
	//PSU_DEBUG_PRINT(MSG_DEBUG, "PMBusSlave_Crc8MakeBitwise Start Handle Byte = 0x%02X \n", PMBusSlave_CRC);
	for (i = 0; i < PMBusSlave_MsgSize - 1; i++)
	{
		msg = *PMBusSlave_Pmsg++;                   // next byte loaded in "msg"
		//PSU_DEBUG_PRINT(MSG_DEBUG, "PMBusSlave_Crc8MakeBitwise Lastest Handle Byte = 0x%02X \n", msg);

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

unsigned short PMBusSlave_Crc8MakeBitwiseDiscont(unsigned char* src_buffer1, unsigned char src_len1, unsigned char* src_buffer2, unsigned char src_len2){

	unsigned short pec = 0x00;
	unsigned char op_buffer[256];
	unsigned char op_buffer_idx = 0;

	for(unsigned int idx=0; idx<sizeof(op_buffer)/sizeof(op_buffer[0]); idx++){
		op_buffer[idx] = 0;
	}

	// Check Length
	if((src_len1+src_len2) > 256){
		return pec;
	}

	// Make OP Buffer
	for(unsigned int idx=0; idx<src_len1; idx++){
		op_buffer[idx] = *(src_buffer1+idx);
		op_buffer_idx = idx;
	}

	op_buffer_idx++;

	for(unsigned int idx=0; idx<src_len2; idx++,op_buffer_idx++){
		op_buffer[op_buffer_idx] = *(src_buffer2+idx);
	}

	op_buffer_idx++;

	pec = PMBusSlave_Crc8MakeBitwise(0, 7, op_buffer, (src_len1+src_len2));

	return pec;

}
