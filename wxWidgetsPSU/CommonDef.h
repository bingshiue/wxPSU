/**
 * @file CommonDef.h
 * @brief Common Define.
 */
#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

#include <stdio.h>
#include <stdlib.h>

#define PSU_PRINT(fmt, ...)  \
		wxLogMessage(fmt,__VA_ARGS__);


enum DEBUG_MSG_LEVEL {
	MSG_FATAL = 0,
	MSG_EMERGECY,
	MSG_ALERT,
	MSG_DEBUG,
	MSG_DETAIL,
};

#define PSU_DEBUG_MSG /**< Print More Debug Messages */
#define DEFAULT_DEBUG_MSG_LEVEL  MSG_ALERT /**< Default Debug Message Level */

#ifdef PSU_DEBUG_MSG
#define PSU_DEBUG_PRINT(level,fmt, ...)  \
		if(level <= DEFAULT_DEBUG_MSG_LEVEL) \
			wxLogMessage("%s():"fmt,__FUNCTIONW__,## __VA_ARGS__);
#else
#define PSU_DEBUG_PRINT(fmt, ...)  \
		while(0) ;
#endif

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
	FAILURE = 0,/**< FAILURE */
	SUCCESS     /**< SUCCESS */
};

#endif