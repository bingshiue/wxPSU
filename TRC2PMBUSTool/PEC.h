 /**
  * @file PEC.h
  */
#ifndef _PEC_H_
#define _PEC_H_

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

 /**
  * @brief Compute PEC Code, For Usage Example Please See below.
  */
unsigned short PMBusSlave_Crc8MakeBitwise(unsigned char PMBusSlave_CRC, unsigned char PMBusSlave_Poly, unsigned char *PMBusSlave_Pmsg, unsigned int PMBusSlave_MsgSize);

/* Usage Example /
int main(void) {

unsigned char data[16];
unsigned char crc8 = 0;

//B6-00-B7-01-CF // For Test

data[0] = 0xB6; // Slave Address
data[1] = 0x00;
data[2] = 0xB7;
data[3] = 0x01;
//data[4] = 0xcf; // Expect PEC Code

printf("pec =%02x H \n",PMBusSlave_Crc8MakeBitwise(0,7,data,4));// 'pec' should be 0xcf

return EXIT_SUCCESS;
}
*/

#endif