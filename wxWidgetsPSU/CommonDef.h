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

#define SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT  20/**< Timeout of Serial Port Send Semaphore */
#define SERIAL_PORT_SEND_POLLING_INTERVAL       30/**< Interval of Serial Port Send Polling (Miliseconds) */

enum {
	FAILURE = 0,/**< FAILURE */
	SUCCESS     /**< SUCCESS */
};

#endif