/**
 * @file TotalPhase.h
 */
#ifndef _TOTALPHASE_H_
#define _TOTALPHASE_H_

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

#include "Aardvark/aardvark.h"

/**
 * @brief Enumerate Available Total Phase Device.
 */
int EnumerateAvailableTotalPhaseDevice(BOOL *array, unsigned int sizeofArray);

/**
 * @brief Get Total Phase Device Status.
 */
int GetTotalPhaseDeviceStatus(void);

/**
 * @brief Get Total Phase Open Device Name.
 */
wchar_t* GetTotalPhaseOpenDeviceName(void);

/**
 * @brief Open Total Phase Device
 */
int OpenTotalPhaseDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting);

/**
 * @brief Total Phase Send Data
 */
int TotalPhaseSendData(unsigned char* buff, unsigned int size);

/**
 * @brief Total Phase Send Data Extra
 */
int TotalPhaseSendDataExtra(unsigned char* buff, unsigned int size, void* ptr);

/**
 * @brief Total Phase Port Read Data
 */
int TotalPhaseReadData(unsigned char* buff, unsigned int sizeOfBuff);

/**
 * @brief Total Phase Port Read Data Extra
 */
int TotalPhaseReadDataExtra(unsigned char* buff, unsigned int sizeOfBuff, void* ptr);

/**
 * @brief Close Total Phase Device
 */
int CloseTotalPhaseDevice(void);

#endif
