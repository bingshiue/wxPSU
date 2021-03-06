 /**
  * @file IOAccess.h
  */
#ifndef _IOACCESS_H_
#define _IOACCESS_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include "CommonDef.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

typedef struct port_setting_t {
	/* Comport Setting Value */
	unsigned long m_comportNumber;
	unsigned long m_buadRate;
	unsigned long m_byteSize;
	unsigned long m_stopBits;
	unsigned long m_parityCheck;

} PORT_SETTING_t;

typedef int (*EnumerateAvailableDevice)(BOOL *, unsigned int);/**< Funtion Pointer Type For Enumerate Available Device */

typedef int (*GetDeviceStatus)(void);/**< Get Device Status (Open/Close) */

typedef wchar_t* (*GetOpenDeviceName)(void);/**< Get Open Device Name */

typedef int(*OpenDevice)(BOOL *, unsigned int, PORT_SETTING_t*);/**< Funtion Pointer Type For Open Device */

typedef int (*DeviceSendData)(unsigned char*, unsigned int);/**< Funtion Pointer Type For Device Send Data */

typedef int (*DeviceReadData)(unsigned char*, unsigned int);/**< Funtion Pointer Type For Device Read Data */

typedef int (*CloseDevice)(void);/**< Funtion Pointer Type For Close Device */

typedef int(*DeviceReadDataExtra)(unsigned char*, unsigned int, void*);/**< Funtion Pointer Type For Device Read Data */

typedef int (*DeviceSendDataExtra)(unsigned char*, unsigned int, void*);/**< Funtion Pointer Type For Device Send Data Extra */

/**
 * @brief Struct For IO Access.
 */
typedef struct _IOACCESS {
	EnumerateAvailableDevice m_EnumerateAvailableDevice;
	GetDeviceStatus m_GetDeviceStatus;
	GetOpenDeviceName m_GetOpenDeviceName;
	OpenDevice m_OpenDevice;
	DeviceSendData m_DeviceSendData;
	DeviceReadData m_DeviceReadData;
	DeviceSendDataExtra m_DeviceSendDataExtra;
	DeviceReadDataExtra m_DeviceReadDataExtra;
	CloseDevice m_CloseDevice;
}IOACCESS;

#endif
