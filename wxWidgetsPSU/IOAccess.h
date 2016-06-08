 /**
  * @file IOAccess.h
  */
#ifndef _IOACCESS_H_
#define _IOACCESS_H_

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include "CommonDef.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

typedef int (*EnumerateAvailableDevice)(BOOL *, unsigned int);/**< Funtion Pointer Type For Enumerate Available Device */

typedef int (*GetDeviceStatus)(void);/**< Get Device Status (Open/Close) */

typedef wchar_t* (*GetOpenDeviceName)(void);/**< Get Open Device Name */

typedef int (*OpenDevice)(BOOL *, unsigned int);/**< Funtion Pointer Type For Open Device */

typedef int (*DeviceSendData)(unsigned char*, unsigned int);/**< Funtion Pointer Type For Device Send Data */

typedef int (*DeviceReadData)(unsigned char*, unsigned int);/**< Funtion Pointer Type For Device Read Data */

typedef int (*CloseDevice)(void);/**< Funtion Pointer Type For Close Device */

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
	CloseDevice m_CloseDevice;
}IOACCESS;

#endif