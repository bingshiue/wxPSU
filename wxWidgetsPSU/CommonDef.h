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

#include "CustomEvent.h"
#include "PMBUSLog.h"

#define DEFAULT_WINDOW_WIDTH   864 /**< Default Window Width */
#define DEFAULT_WINDOW_HEIGHT  660 /**< Default Window Height */

//#define DONT_SUPPORT_ISP /**< Don't Support ISP (Disable Administratot Menu Item) */
#ifndef _DEBUG
#define LOCK_UPDATE_FW /**< Lock Update FW MenuItem Default */
#endif
#define ADMINISTRATOR_PASSWORD wxT("acbelacbel") /**< Default Administrator Password */
#define DEVELOPER_PASSWORD wxT("0226217672") /**< Default Developer Password */

#define IO_PORT_MAX_COUNT  255/**< Max Count of IO Device */     

#define SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT  1000/**< Timeout of Serial Port Send Semaphore */
#define SERIAL_PORT_SEND_POLLING_INTERVAL  20/**< Interval of Serial Port Send Polling (Milliseconds) */

#define SEND_BUFFER_MAX_SIZE  64/**< Send Buffer Maximum Size */

#define SERIALPORT_RECV_BUFF_SIZE  256 /**< Seroal Port Receive Buufer Maximum Size */

#define IO_SIZE  2/**< Current 2 Kind : Serial Port & HID */

#define UPDATE_PRIMARY_FW_TARGET    0x61 /**< Primary FW Update Target code */
#define UPDATE_SECONDARY_FW_TARGET  0x60 /**< Secondary FW Update Target code */

#define CALIBRARTION_HANDLE_0D /**< Handle '0x0d' as special character in Calibration */
#define ISP_HANDLE_0D /**< Handle '0x0d' as special character in ISP */

#define DELAY_READ_ISP_START_VERIFY_RESPONSE  100 /**< Delay Read ISP Start Verify Response */

//#define ISP_SLEEP /**< Sleep Between F3(F1) Command */
#ifdef ISP_SLEEP
#define ISP_SLEEP_TIME  10  /**< Sleep Time Between F3(F1) Command (MilliSecond) */
#endif

#define ISP_START_VERIFY_RETRY  5 /**< ISP Start Verify(F0) Command Fail Retry Times */

#define ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP /**< Sleep before Start Verify Command Failed Retry */
#ifdef ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP 
#define ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP_TIME 200 /**< Sleep Time before Start Verify Command Failed Retry (MilliSecond) */
#endif


#define ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY /**< Delay After Primary Firmware Receive Start Verify CMD Success */
#ifdef ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY
#define ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY_TIME  2500 /**< Delay Time After Primary Firmware Receive Start Verify CMD Success */
#endif

#define ISP_CHECK_STATUS_RETRY  5 /**< ISP Check Status(F3) Command Fail Retry Times */

#define ISP_F3_CMD_FAILED_RETRY_SLEEP /**< Sleep before F3 Command Check Failed Retry */
#ifdef ISP_F3_CMD_FAILED_RETRY_SLEEP 
#define ISP_F3_CMD_FAILED_RETRY_SLEEP_TIME 50 /**< Sleep Time before F3 Command Check Failed Retry (MilliSecond) */
#endif

#define WAIT_DSP_REBOOT_TIME  7000 /**< Wait for DSP Reboot Time (MilliSecond) */

#define UserCancelISP_POST_DELAY_TIME 7000 /**< User Cancel ISP Post Delay Time */

#define I2C_AdaptorModuleBoard_R90000_9271_USB_PID  0x003F /**< R90000 9271 USB PID */
#define I2C_AdaptorModuleBoard_R90000_9271_USB_VID  0x04D8 /**< R90000 9271 USB VID */

/* ----- Below is for debug only ------ */

//#define ISP_DONT_WAIT_RESPONSE /**< For debug, Do ISP Sequence without waiting DSP's response */
//#define IGNORE_ISP_RESPONSE_ERROR /**< For debug, Ignore ISP response error */

/* ----- Enumerate Type ------ */

/**
 * @brief IO Port Kind.
 */
enum {
	IOACCESS_SERIALPORT = 0,
	IOACCESS_HID
};

/**
 * @brief IO Port Status.
 */
enum {
	IODEVICE_CLOSE = 0,
	IODEVICE_OPEN
};

/**
 * @brief Success or Failure.
 */
enum {
	SUCCESS = EXIT_SUCCESS,    /**< SUCCESS */
	FAILURE = EXIT_FAILURE,    /**< FAILURE */
};

/**
 * @brief ISP Sequence Status.
 */
enum {
	ISP_Status_InProgress = 0x00,
	ISP_Status_VerifyBeforeStart = 0x01,
	ISP_Status_ALLDone = 0x02,
	ISP_Status_UserRequestCancel = 0x04,
	ISP_Status_SendDataFailed = 0x08,
	ISP_Status_ResponseDataError = 0x10,
	ISP_Status_RebootCheckError = 0x20,
	ISP_Status_UnknownErrorOccurs = 0x80
};

#endif
