/**
 * @brief TaskSystemThread.cpp
 */

#include "TaskSystemThread.h"

TaskSystemThread::TaskSystemThread(){
	// Set m_running to ture
	this->m_running = true;
	
	// Init Task System
	TaskEx::InitTaskList();
}

TaskSystemThread::~TaskSystemThread(){ }

// thread execution starts here
wxThread::ExitCode TaskSystemThread::Entry() {
	// Run Task
	double dummy = 0;
	double delta;
	// Tick Parameter
	DWORD nowTick, previousTick;
	nowTick = previousTick = GetTickCount();

	while (this->m_running == true){

		//PSU_DEBUG_PRINT(MSG_DEBUG, "TaskCnt = %d", Task::GetCount());

		nowTick = GetTickCount();

		delta = nowTick - previousTick;
		previousTick = nowTick;

		if (Task::GetCount() > 0)
		{
			Task::GetCriticalSectionObject().Enter();
			wxMilliSleep(1);
			Task::RunTask(delta);
			Task::GetCriticalSectionObject().Leave();
		}
		else{
			wxMilliSleep(100);
		}
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "TaskSystem Thread Finish");

	return NULL;
}