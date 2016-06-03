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

	while (this->m_running == true){

		Task::RunTask(dummy);

		Sleep(1);
	}

	return NULL;
}