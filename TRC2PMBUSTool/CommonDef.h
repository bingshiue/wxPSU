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

#include "Preprocessor.h"
#include "CustomEvent.h"
#include "IOPortDefine.h"
#include "PMBUSCMD.h"
#include "PMBUSCMDDefault.h"
#include "PMBUSLog.h"
#include "ISPDefine.h"

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

#define RELOAD_USB_ADAPTOR_SETTINGS_APP_RESTART  /**< Reload USB Adaptor's Setting when APP restart */

/**
 * @brief Success or Failure.
 */
enum {
	SUCCESS = EXIT_SUCCESS,    /**< SUCCESS */
	FAILURE = EXIT_FAILURE,    /**< FAILURE */
};

#endif
