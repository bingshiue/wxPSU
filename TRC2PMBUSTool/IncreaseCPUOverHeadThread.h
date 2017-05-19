/**
 * @file IncreaseCPUOverHeadThread.h
 */
#ifndef _INCREASECPUOVERHEADTHREAD_H_
#define _INCREASECPUOVERHEADTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifdef __GNUC__
#define wxOVERRIDE   
#endif

/**
 * @brief Increase CPU OverHead Thread.
 */
class IncreaseCPUOverHeadThread : public wxThread {
public:

	bool m_running;
	bool* m_increaseCPUOverHeadThreadStopFlag;

	IncreaseCPUOverHeadThread(bool *increaseCPUOverHeadThreadStopFlag);

	virtual ~IncreaseCPUOverHeadThread();

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif
