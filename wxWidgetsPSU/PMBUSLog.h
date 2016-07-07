/**
 * @file PMBUSLog.h
 */

#ifndef _PMBUSLOG_H_
#define _PMBUSLOG_H_

#define PSU_PRINT(fmt, ...)  \
		wxLogMessage(fmt,__VA_ARGS__);

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
#define DEFAULT_DEBUG_MSG_LEVEL  MSG_ALERT /**< Default Debug Message Level */

#ifdef PSU_DEBUG_MSG
#ifdef _DEBUG
#define PSU_DEBUG_PRINT(level,fmt, ...)  \
		if(level == MSG_FATAL) \
			wxLogFatalError("%s():%d:"fmt,__FUNCTIONW__,__LINE__,## __VA_ARGS__);   \
		else if(level == MSG_ERROR) \
		    wxLogError("%s():%d:"fmt,__FUNCTIONW__,__LINE__,## __VA_ARGS__); \
		else if(level == MSG_ALERT) \
		    wxLogMessage("%s():%d:"fmt,__FUNCTIONW__,__LINE__,## __VA_ARGS__); \
		else if(level == MSG_DEBUG) \
		    wxLogDebug("%s():%d:"fmt,__FUNCTIONW__,__LINE__,## __VA_ARGS__);   \
		else if(level == MSG_DETAIL) \
		    wxLogVerbose("%s():%d:"fmt,__FUNCTIONW__,__LINE__,## __VA_ARGS__);

#else
#define PSU_DEBUG_PRINT(level,fmt, ...)  \
		if(level == MSG_FATAL) \
			wxLogFatalError(fmt,__VA_ARGS__);   \
		else if(level == MSG_ERROR) \
		    wxLogError(fmt,__VA_ARGS__); \
		else if(level == MSG_ALERT) \
		    wxLogMessage(fmt,__VA_ARGS__); \
		else if(level == MSG_DEBUG) \
		    wxLogDebug(fmt,__VA_ARGS__);   \
		else if(level == MSG_DETAIL) \
		    wxLogVerbose(fmt,__VA_ARGS__);

#endif
#else
#define PSU_DEBUG_PRINT(fmt, ...)  \
			while(0) ;
#endif

#endif