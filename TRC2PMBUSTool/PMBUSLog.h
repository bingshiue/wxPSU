/**
 * @file PMBUSLog.h
 */

#ifndef _PMBUSLOG_H_
#define _PMBUSLOG_H_

#include <wx/log.h>

#include "PMBUSHelper.h"

/*
wxLogError
wxLogWarning
wxLogMessage
wxLogDebug
wxLogVerbose
*/
enum DEBUG_MSG_LEVEL {
	MSG_FATAL = 0,
	MSG_ERROR,
	MSG_ALERT,
	MSG_DEBUG,
	MSG_DETAIL,
};

#define PSU_DEBUG_MSG /**< Print More Debug Messages */

#ifdef PSU_DEBUG_MSG

#ifdef _DEBUG

#define DEFAULT_DEBUG_MSG_LEVEL  MSG_DEBUG /**< Default Debug Message Level */


#define PSU_DEBUG_PRINT(level,fmt, ...)                                             \
		if(level <= DEFAULT_DEBUG_MSG_LEVEL){                                       \
				if(level == MSG_FATAL)                                              \
			wxLogFatalError("%-20s %s():%d:"fmt,PMBUSHelper::GetNowTimeString().c_str(),__FUNCTION__,__LINE__,## __VA_ARGS__);   \
                else if(level == MSG_ERROR)                                         \
		    wxLogError("%-20s %s():%d:"fmt,PMBUSHelper::GetNowTimeString().c_str(),__FUNCTION__,__LINE__,## __VA_ARGS__);        \
				else if(level == MSG_ALERT)                                         \
		    wxLogMessage("%-20s %s():%d:"fmt,PMBUSHelper::GetNowTimeString().c_str(),__FUNCTION__,__LINE__,## __VA_ARGS__);      \
				else if(level == MSG_DEBUG)                                         \
		    wxLogDebug("%-20s %s():%d:"fmt,PMBUSHelper::GetNowTimeString().c_str(),__FUNCTION__,__LINE__,## __VA_ARGS__);        \
				else if(level == MSG_DETAIL)                                        \
		    wxLogVerbose("%-20s %s():%d:"fmt,PMBUSHelper::GetNowTimeString().c_str(),__FUNCTION__,__LINE__,## __VA_ARGS__);      \
		}

#else
#define DEFAULT_DEBUG_MSG_LEVEL  MSG_ALERT /**< Default Debug Message Level */

#define PSU_DEBUG_PRINT(level,fmt, ...)         \
		if(level <= DEFAULT_DEBUG_MSG_LEVEL){   \
				if(level == MSG_FATAL)          \
			wxLogFatalError("%-20s"fmt,PMBUSHelper::GetNowTimeString().c_str(), ## __VA_ARGS__);   \
				else if(level == MSG_ERROR)     \
		    wxLogError("%-20s"fmt,PMBUSHelper::GetNowTimeString().c_str(),## __VA_ARGS__);        \
				else if(level == MSG_ALERT)     \
		    wxLogMessage("%-20s"fmt,PMBUSHelper::GetNowTimeString().c_str(),## __VA_ARGS__);      \
				else if(level == MSG_DEBUG)     \
		    wxLogDebug("%-20s"fmt,PMBUSHelper::GetNowTimeString().c_str(),## __VA_ARGS__);        \
				else if(level == MSG_DETAIL)    \
		    wxLogVerbose("%-20s"fmt,PMBUSHelper::GetNowTimeString().c_str(),## __VA_ARGS__);      \
		}

#endif // #ifdef PSU_DEBUG_MSG

#else
#define PSU_DEBUG_PRINT(fmt, ...)  \
			while(0) ;

#endif // #ifdef _DEBUG

#endif // #ifndef _PMBUSLOG_H_
