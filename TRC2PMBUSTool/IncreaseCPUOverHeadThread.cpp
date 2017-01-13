/**
* @file IncreaseCPUOverHeadThread.cpp
*/
#include "IncreaseCPUOverHeadThread.h"

IncreaseCPUOverHeadThread::IncreaseCPUOverHeadThread(bool* increaseCPUOverHeadThreadStopFlag){

	this->m_increaseCPUOverHeadThreadStopFlag = increaseCPUOverHeadThreadStopFlag;

	this->m_running = true;

}

IncreaseCPUOverHeadThread::~IncreaseCPUOverHeadThread(){
	*this->m_increaseCPUOverHeadThreadStopFlag = true;
}

#define NUM_THREADS    4 // Number Of Threads
#define THREAD_SLEEP  10 // micro seconds
wxThread::ExitCode IncreaseCPUOverHeadThread::Entry() {

	int value=0;


	*this->m_increaseCPUOverHeadThreadStopFlag = false;
	while (this->m_running == true && this->TestDestroy() == false){

		#pragma omp parallel num_threads(NUM_THREADS)
		#pragma omp parallel for
		for (int idx = 0; idx < 1000; idx++){			
			value ^= 0x01;
		}

		wxMicroSleep(THREAD_SLEEP);

	};

	return NULL;
}