/**
 * @file PMBUSCBQuery.h
 */
#ifndef _PMBUSCBQUERY_H_
#define _PMBUSCBQUERY_H_

#include "PMBUSCommandType.h"

// Declare Query CB Functions
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
int Query_8b00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8c00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8b01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8c01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_8dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
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
int Query_f5H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_faH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Query_fcH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);

#endif