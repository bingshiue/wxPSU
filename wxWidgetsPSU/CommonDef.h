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

#include "PMBUSLog.h"

wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_COMPLETED, wxThreadEvent); /**< Declare Thread Compelete Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE, wxThreadEvent); /**< Declare Thread Update Event */

#define DEFAULT_WINDOW_WIDTH   864 /**< Default Window Width */
#define DEFAULT_WINDOW_HEIGHT  660 /**< Default Window Height */

#define LOCK_UPDATE_FW /**< Lock Update FW MenuItem Default */
#define ADMINISTRATOR_PASSWORD wxT("acbelacbel") /**< Default Administrator Password */

#define IO_PORT_MAX_COUNT  255/**< Max Count of IO Device */     

#define SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT  1000/**< Timeout of Serial Port Send Semaphore */
#define SERIAL_PORT_SEND_POLLING_INTERVAL  20/**< Interval of Serial Port Send Polling (Milliseconds) */

#define SEND_BUFFER_MAX_SIZE  64/**< Send Buffer Maximum Size */

#define SERIALPORT_RECV_BUFF_SIZE  256 /**< Seroal Port Receive Buufer Maximum Size */

#define IO_SIZE  2/**< Current 2 Kind : Serial Port & HID */

#define UPDATE_PRIMARY_FW_TARGET    0x61 /**< Primary FW Update Target code */
#define UPDATE_SECONDARY_FW_TARGET  0x60 /**< Secondary FW Update Target code */

#define ISP_HANDLE_OD /**< Handle '0x0d' as special character in ISP */

#define WAIT_DSP_REBOOT_TIME  3000 /**< Wait for DSP Reboot Time (MilliSecond) */

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
