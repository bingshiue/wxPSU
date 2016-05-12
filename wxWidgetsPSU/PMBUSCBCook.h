/**
 * @file PMBUSCBCook.h
 */
#ifndef _PMBUSCBCOOK_H_
#define _PMBUSCBCOOK_H_

#include "PMBUSCommandType.h"

// Declare Cook CB Functions
int Cook_00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_02H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_03H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_1bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_20H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_3aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_3bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_51H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_5dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_6aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_6bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_78H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_79H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_7aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_7bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_7cH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_7dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_7eH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_7fH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_81H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_86H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_87H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_88H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_89H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8c00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8b00H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8c01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8d01H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8eH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_8fH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_90H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_96H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_97H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_98H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_99H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_9aH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_9bH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_9cH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_9dH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_9eH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a0H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a1H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a2H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a3H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a4H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a5H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a6H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a7H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a8H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_a9H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_aaH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_abH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_d0H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_dbH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_dcH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_ddH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_f1H(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_faH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);
int Cook_fcH(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);

#endif