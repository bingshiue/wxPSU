/**
 * @file TRC2_I2C_Adapter.h
 */
#ifndef _TRC2_I2C_ADAPTER_H_
#define _TRC2_I2C_ADAPTER_H_

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

/**
 * @brief Enumerate Available TRC2 I2C Adapter Device.
 */
int EnumerateAvailableTRC2I2CAdapterDevice(BOOL *array, unsigned int sizeofArray);

/**
 * @brief Get TRC2 I2C Adapter Device Status.
 */
int GetTRC2I2CAdapterDeviceStatus(void);

/**
 * @brief Get TRC2 I2C Adapter Open Device Name.
 */
wchar_t* GetTRC2I2CAdapterOpenDeviceName(void);

/**
 * @brief Open TRC2 I2C Adapter Device
 */
int OpenTRC2I2CAdapterDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting);

/**
 * @brief TRC2 I2C Adapter Send Data
 */
int TRC2I2CAdapterSendData(unsigned char* buff, unsigned int size);

/**
 * @brief TRC2 I2C Adapter Send Data Extra
 */
int TRC2I2CAdapterSendDataExtra(unsigned char* buff, unsigned int size, void* ptr);

/**
 * @brief TRC2 I2C Adapter Port Read Data
 */
int TRC2I2CAdapterReadData(unsigned char* buff, unsigned int sizeOfBuff);

/**
 * @brief TRC2 I2C Adapter Port Read Data Extra
 */
int TRC2I2CAdapterReadDataExtra(unsigned char* buff, unsigned int sizeOfBuff, void* ptr);

/**
 * @brief Close TRC2 I2C Adapter Device
 */
int CloseTRC2I2CAdapterDevice(void);


#endif/* _TRC2_I2C_ADAPTER_H_ */
