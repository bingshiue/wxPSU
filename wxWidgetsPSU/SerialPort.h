/**
 * @file SerialPort.h
 * @brief Serial Port Access Function.
 */
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include "CommonDef.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/**
* @brief Enumerate Available SerialPort.
*/
int EnumerateAvailableSerialPort(BOOL *array, unsigned int sizeofArray);

/**
* @brief Open Serial Port
*/
int OpenSerialPort(BOOL *array, unsigned int sizeofArray);//int PortNum)

/**
* @brief Serial Port Send Data
*/
int SerialSendData(unsigned char* buff, unsigned int size);

/**
* @brief Serial Port Read Data
*/
int SerialReadData(unsigned char* buff, unsigned int bytesToRead);

/**
* @brief Close Serial Port
*/
int CloseSerialPort(void);

#endif