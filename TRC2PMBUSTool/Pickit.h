/**
 * @file Pickit.h
 */

#ifndef _PICKIT_H_
#define _PICKIT_H_

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include "hidapi.h"
#include "CommonDef.h"
#include "IOAccess.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "USBInfoType.h"

/**
 * @brief Enumerate Available Pickit Device.
 */
int EnumerateAvailablePickitDevice(BOOL *array, unsigned int sizeofArray);

/**
 * @brief Get Pickit Device Status.
 */
int GetPickitDeviceStatus(void);

/**
 * @brief Get Pickit Open Device Name.
 */
wchar_t* GetPickitOpenDeviceName(void);

/**
 * @brief Open Pickit Device
 */
int OpenPickitDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting);

/**
 * @brief Pickit Send Data
 */
int PickitSendData(unsigned char* buff, unsigned int size);

/**
 * @brief Pickit Read Data
 */
int PickitReadData(unsigned char* buff, unsigned int bytesToRead);

/**
 * @brief Pickit Send Data Extra
 */
int PickitSendDataExtra(unsigned char* buff, unsigned int size, void* ptr);

/**
 * @brief Pickit Read Data Extra
 */
int PickitReadDataExtra(unsigned char* buff, unsigned int sizeOfBuff, void* ptr);

/**
 * @brief Close Pickit Device
 */
int ClosePickitDevice(void);

#endif