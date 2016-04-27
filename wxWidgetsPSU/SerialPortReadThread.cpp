/**
 * @file SerialPortReadThread.cpp
 */

#include "SerialPortReadThread.h"
#include "SerialPort.h"

SerialReadThread::SerialReadThread(wxSemaphore* semaphore, PMBUSCOMMAND_t *pmBusCommand, RECVBUFF_t *recvBuff, unsigned int recvBuffSize){
	this->m_rxTxSemaphore = semaphore;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_recvBuffSize = recvBuffSize;
}

SerialReadThread::~SerialReadThread() { }

wxThread::ExitCode SerialReadThread::Entry()
{
	wxLogMessage("Thread started (priority = %u).", GetPriority());

	this->m_running = true;

	while (this->m_running == true){

		wxLogMessage("Prepare To Read Data From Serisl Port :");

		// wxSleep() can't be called from non-GUI thread!
		//wxThread::Sleep(1000);

		// Read Data From Serial Port
		this->m_recvBuff->m_length = SerialReadData(this->m_recvBuff->m_recvBuff);

		wxLogMessage("Semaphore Post");
		// Semaphore Post
		this->m_rxTxSemaphore->Post();

	};

	wxLogMessage("Thread finished.");

	return NULL;
}
