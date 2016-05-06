/**
 * @file SerialPortReadThread.cpp
 */

#include "SerialPortReadThread.h"
#include "SerialPort.h"

SerialReadThread::SerialReadThread(wxSemaphore* semaphore, PMBUSCOMMAND_t *pmBusCommand, RECVBUFF_t *recvBuff, unsigned int recvBuffSize, unsigned int bytesToRead){
	this->m_rxTxSemaphore = semaphore;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_recvBuffSize = recvBuffSize;
	this->m_bytesToRead = bytesToRead;
}

SerialReadThread::~SerialReadThread() { }

wxThread::ExitCode SerialReadThread::Entry()
{
	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread started (priority = %u).", GetPriority());

	this->m_running = true;

	//while (this->m_running == true){

		PSU_DEBUG_PRINT(MSG_DEBUG, "Prepare To Read Data From Serisl Port :");

		// Read Data From Serial Port
		this->m_recvBuff->m_length = SerialReadData(this->m_recvBuff->m_recvBuff,this->m_bytesToRead);

		PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore Post");
		// Semaphore Post
		this->m_rxTxSemaphore->Post();

	//};

		PSU_DEBUG_PRINT(MSG_DEBUG, "Thread finished.");

	return NULL;
}
