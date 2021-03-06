 /**
  * @file HID.h
  */

#ifndef _HID_H_
#define _HID_H_

#ifdef _WIN32
#include<Windows.h>
#endif

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

void productSendBuffer(unsigned char* buffer, unsigned int lengthOfBuffer, unsigned int command, unsigned int responseLength);

/**
 * @brief Enumerate Available HID Device.
 */
int EnumerateAvailableHIDDevice(BOOL *array, unsigned int sizeofArray);

/**
 * @brief Get HID Device Status.
 */
int GetHIDDeviceStatus(void);

/**
 * @brief Get HID Open Device Name.
 */
wchar_t* GetHIDOpenDeviceName(void);

/**
 * @brief Open HID Device
 */
int OpenHIDDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting);

/**
 * @brief HID Send Data
 */
int HIDSendData(unsigned char* buff, unsigned int size);

/**
 * @brief HID Send Data Extra
 */
int HIDSendDataExtra(unsigned char* buff, unsigned int size, void* ptr);

/**
 * @brief HID Port Read Data
 */
int HIDReadData(unsigned char* buff, unsigned int sizeOfBuff);

/**
 * @brief HID Port Read Data Extra
 */
int HIDReadDataExtra(unsigned char* buff, unsigned int sizeOfBuff, void* ptr);

/**
 * @brief Close HID Device
 */
int CloseHIDDevice(void);
 
#endif
