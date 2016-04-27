/**
 * @file CommonDef.h
 * @brief Common Define.
 */
#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

#include <stdio.h>
#include <stdlib.h>

#define PSU_DEBUG_MSG /**< Debug Messages */

#ifdef PSU_DEBUG_MSG
#define PSU_DEBUG_PRINT(fmt, ...)  \
		wxLogMessage(fmt,__VA_ARGS__);
		//printf("%s():"fmt,__func__,## __VA_ARGS__);
#else
#define PSU_DEBUG_PRINT(fmt, ...)  \
		while(0) ;
#endif

#define SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT  50/**< Timeout of Serial Port Send Semaphore */
#define SERIAL_PORT_SEND_POLLING_INTERVAL       20/**< Interval of Serial Port Send Polling (Miliseconds) */

#define DEFAULT_WINDOW_WIDTH   864
#define DEFAULT_WINDOW_HEIGHT  660

#define SERIALPORT_RECV_BUFF_SIZE  256

enum {
	FAILURE = 0,/**< FAILURE */
	SUCCESS     /**< SUCCESS */
};

enum RUNMODE {
	RunMode_Iteration = 0,
	RunMode_Continally,
	RunMode_StopAnError
};

#endif