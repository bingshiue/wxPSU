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
 * @brief Open Serial Port 
 */
int OpenSerialPort(int PortNum);

/**
 * @brief Serial Port Send Data
 */
int SerialSendData(char* buff,int size);


/**
 * @brief Serial Port Read Data
 */
int SerialReadData(char* buff);

/**
 * @brief Close Serial Port
 */
int CloseSerialPort(void);

#endif