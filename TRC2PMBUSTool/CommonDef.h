/**
 * @file CommonDef.h
 * @brief Common Define.
 */
#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>

#include "Preprocessor.h"
#include "CustomEvent.h"
#include "IOPortDefine.h"
#include "PMBUSCMD.h"
#include "PMBUSCMDDefault.h"
#include "PMBUSLog.h"
#include "ISPDefine.h"

#ifdef __GNUC__
#include "sys/time.h"
#include "png2c.h"
#include <vector>
#endif

#ifdef __GNUC__
#define BOOL bool
#define wxOVERRIDE 
#define __FUNCTIONW__ __FUNCTION__
#endif

#ifdef __GNUC__
#define LOAD_PNG_RESOURCE wxBITMAP_PNG_FROM_DATA
#else
#define LOAD_PNG_RESOURCE wxBITMAP_PNG
#endif

#ifndef _DEBUG
#define LOCK_UPDATE_FW /**< Lock Update FW MenuItem Default */
#endif

#define ADMINISTRATOR_PASSWORD wxT("acbelacbel") /**< Default Administrator Password */
#define DEVELOPER_PASSWORD wxT("0226217672") /**< Default Developer Password */

#define CALIBRARTION_HANDLE_0D /**< Handle '0x0d' as special character in Calibration */

#define I2C_AdaptorModuleBoard_R90000_9271_USB_PID  0x003F /**< R90000 9271 USB PID */
#define I2C_AdaptorModuleBoard_R90000_9271_USB_VID  0x04D8 /**< R90000 9271 USB VID */

#define TOTAL_PHASE_USB_PID   0xE0D0/**< Total Phase USB PID */
#define TOTAL_PHASE_USB_VID   0x0403/**< Total Phase USB VID */

#define PICKIT_SERIAL_USB_PID  0x0036 /**< PICKIT Serial USB PID */
#define PICKIT_SERIAL_USB_VID  0x04D8 /**< PICKIT Serial USB VID */

#define TRC2_I2C_ADAPTER_VID 0x1234/**< Default TRC2 I2C Adapter VID */
#define TRC2_I2C_ADAPTER_PID 0x0006/**< Default TRC2 I2C Adapter PID */

#define RELOAD_USB_ADAPTOR_SETTINGS_APP_RESTART  /**< Reload USB Adaptor's Setting when APP restart */

/**
 * @brief Success or Failure.
 */
enum {
	SUCCESS = EXIT_SUCCESS,    /**< SUCCESS */
	FAILURE = EXIT_FAILURE,    /**< FAILURE */
};


#ifdef __GNUC__
#define COPY_WIDE_CHARACTERS  wcsncpy 
#else
#define COPY_WIDE_CHARACTERS  lstrcpyn 
#endif

#ifdef __GNUC__
#define CBR_110  110
#define CBR_300  300
#define CBR_600  600
#define CBR_1200 1200
#define CBR_2400 2400
#define CBR_4800 4800
#define CBR_14400 14400
#define CBR_19200 19200
#define CBR_38400 38400
#define CBR_56000 56000
#define CBR_57600 57600
#define CBR_115200 115200

#define ODDPARITY  1
#define EVENPARITY  2
#define MARKPARITY  3
#define SPACEPARITY  4
#define ONE5STOPBITS  5
#define TWOSTOPBITS  6
#endif

#endif
