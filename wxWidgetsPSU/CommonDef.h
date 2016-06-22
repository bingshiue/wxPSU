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

wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE, wxThreadEvent);


//#define DEFAULT_LOCK_UPDATE_FW
#define ADMINISTRATOR_PASSWORD wxT("acbelacbel")

#define IO_PORT_MAX_COUNT  255/**< Max Count of IO Device */     

#define SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT  1000/**< Timeout of Serial Port Send Semaphore */
#define SERIAL_PORT_SEND_POLLING_INTERVAL  20/**< Interval of Serial Port Send Polling (Miliseconds) */

#define DEFAULT_WINDOW_WIDTH   864
#define DEFAULT_WINDOW_HEIGHT  660

#define SEND_BUFFER_MAX_SIZE  64/**< Send Buffer Max Size */

#define SERIALPORT_RECV_BUFF_SIZE  256

#define IO_SIZE  2/**< Current 2 Kind : Serial Port & HID */

enum {
	IOACCESS_SERIALPORT = 0,
	IOACCESS_HID
};

enum {
	IODEVICE_CLOSE = 0,
	IODEVICE_OPEN
};

enum {
	SUCCESS = EXIT_SUCCESS,    /**< SUCCESS */
	FAILURE = EXIT_FAILURE,    /**< FAILURE */
};

#endif