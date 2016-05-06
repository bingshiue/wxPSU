/**
 * @file PMBUSCMDCB.h
 */
#ifndef _PMBUSCMDCB_H_
#define _PMBUSCMDCB_H_

#include "PMBUSCommandType.h"

int Query_00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_02H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_03H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_1bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_20H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_3aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_3bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_51H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_5dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_6aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_6bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_78H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_79H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_7aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_7bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_7cH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_7dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_7eH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_7fH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_81H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_86H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_87H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_88H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_89H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8c00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8b00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8c01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8d01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8eH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8fH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_90H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_96H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_97H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_98H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_99H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_9aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_9bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_9cH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_9dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_9eH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a0H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a1H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a2H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a3H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a4H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a5H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a6H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a7H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a8H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_a9H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_aaH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_abH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_d0H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_dbH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_dcH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_ddH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_f1H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_faH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_fcH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);



CMDQueryCBFunc CMDQueryCBFuncArray[PMBUSCOMMAND_SIZE] = {
	Query_00H,
	Query_01H,
	Query_02H,
	Query_03H,
	Query_1bH,
	Query_20H,
	Query_3aH,
	Query_3bH,
	Query_51H,
	Query_5dH,
	Query_6aH,
	Query_6bH,
	Query_78H,
	Query_79H,
	Query_7aH,
	Query_7bH,
	Query_7cH,
	Query_7dH,
	Query_7eH,
	Query_7fH,
	Query_81H,
	Query_86H,
	Query_87H,
	Query_88H,
	Query_89H,
	Query_8aH,
	Query_8bH,
	Query_8c00H,
	Query_8b00H,
	Query_8c01H,
	Query_8d01H,
	Query_8eH,
	Query_8fH,
	Query_90H,
	Query_96H,
	Query_97H,
	Query_98H,
	Query_99H,
	Query_9aH,
	Query_9bH,
	Query_9cH,
	Query_9dH,
	Query_9eH,
	Query_a0H,
	Query_a1H,
	Query_a2H,
	Query_a3H,
	Query_a4H,
	Query_a5H,
	Query_a6H,
	Query_a7H,
	Query_a8H,
	Query_a9H,
	Query_aaH,
	Query_abH,
	Query_d0H,
	Query_dbH,
	Query_dcH,
	Query_ddH,
	Query_f1H,
	Query_faH,
	Query_fcH
};

CMDCookCBFunc CMDCookCBFuncArray[PMBUSCOMMAND_SIZE];

CMDRawCBFunc CMDRawCBFuncArray[PMBUSCOMMAND_SIZE];

#endif
