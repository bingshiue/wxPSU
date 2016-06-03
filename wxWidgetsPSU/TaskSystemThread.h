/**
 * @brief TaskSystemThread.h
 */
#ifndef _TASKSYSTEMTHREAD_H_
#define _TASKSYSTEMTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "TaskSystem.h"
#include "TaskSystemEx.h"
#include "Task.h"

class TaskSystemThread : public wxThread {
public:
	TaskSystemThread();

	virtual ~TaskSystemThread();

	bool m_running;

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif