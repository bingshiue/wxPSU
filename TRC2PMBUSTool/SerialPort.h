/**
 * @file SerialPort.h
 * @brief Serial Port Access Function.
 */
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#ifdef _WIN32
#include<Windows.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include "CommonDef.h"
#include "IOAccess.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/**
 * @brief Enumerate Available SerialPort.
 */
int EnumerateAvailableSerialPort(BOOL *array, unsigned int sizeofArray);

/**
 * @brief Get Serial Port Status.
 */
int GetSerialPortStatus(void);

/**
 * @brief Get Serial Port Open Device Name.
 */
wchar_t* GetSerialPortOpenDeviceName(void);

/**
 * @brief Open Serial Port
 */
int OpenSerialPort(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting);

/**
 * @brief Serial Port Send Data
 */
int SerialSendData(unsigned char* buff, unsigned int size);

/**
 * @brief Serial Port Send Data Extra
 */
int SerialSendDataExtra(unsigned char* buff, unsigned int size, void* ptr);

/**
 * @brief Serial Port Read Data
 */
int SerialReadData(unsigned char* buff, unsigned int bytesToRead);

/**
 * @brief Serial Port Read Data
 */
int SerialReadDataExtra(unsigned char* buff, unsigned int bytesToRead, void* ptr);

/**
 * @brief Close Serial Port
 */
int CloseSerialPort(void);

#endif
