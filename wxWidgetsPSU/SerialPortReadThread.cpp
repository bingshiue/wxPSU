/**
 * @file SerialPortReadThread.cpp
 */

#include "SerialPortReadThread.h"
#include "SerialPort.h"

SerialReadThread::SerialReadThread(){ }

SerialReadThread::~SerialReadThread() { }

wxThread::ExitCode SerialReadThread::Entry()
{
	char buffer[256];

	wxLogMessage("Thread started (priority = %u).", GetPriority());

	while (true){

		wxLogMessage("Read Data From Serisl Port");

		// wxSleep() can't be called from non-GUI thread!
		wxThread::Sleep(1000);

		// Read Data From Serial Port
		SerialReadData(buffer);

	};

	wxLogMessage("Thread finished.");

	return NULL;
}
