/**
 * @file SerialPortReadThread.cpp
 */

#include "SerialPortReadThread.h"
#include "SerialPort.h"

SerialReadThread::SerialReadThread(wxSemaphore* semaphore){ 
	this->m_rxTxSemaphore = semaphore;
}

SerialReadThread::~SerialReadThread() { }

wxThread::ExitCode SerialReadThread::Entry()
{
	unsigned char buffer[256];

	wxLogMessage("Thread started (priority = %u).", GetPriority());

	while (true){

		wxLogMessage("Prepare To Read Data From Serisl Port :");

		// wxSleep() can't be called from non-GUI thread!
		wxThread::Sleep(1000);

		// Read Data From Serial Port
		SerialReadData(buffer);

		// Semaphore Post
		this->m_rxTxSemaphore->Post();

	};

	wxLogMessage("Thread finished.");

	return NULL;
}
