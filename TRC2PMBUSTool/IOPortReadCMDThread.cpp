/**
 * @file IOPortReadCMDThread.cpp
 */

#include "IOPortReadCMDThread.h"

IOPortReadCMDThread::IOPortReadCMDThread(
	IOACCESS*    ioaccess,
	unsigned int* currentIO,
	wxSemaphore* semaphore, 
	PMBUSCOMMAND_t *pmBusCommand, 
	RECVBUFF_t *recvBuff, 
	unsigned int recvBuffSize, 
	unsigned int bytesToRead)
{
	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_rxTxSemaphore = semaphore;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_recvBuffSize = recvBuffSize;
	this->m_bytesToRead = bytesToRead;
}

IOPortReadCMDThread::~IOPortReadCMDThread() { }

wxThread::ExitCode IOPortReadCMDThread::Entry()
{
	int ret;
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread started (priority = %u), CMD=%02xH", GetPriority(), this->m_pmBusCommand->m_register);

	this->m_running = true;

	//while (this->m_running == true){

		PSU_DEBUG_PRINT(MSG_DEBUG, "Prepare To Read Data From I/O :");

		// Read Data From IO
		this->m_recvBuff->m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff->m_recvBuff,this->m_bytesToRead);

		PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore Post");
		// Semaphore Post
		ret = this->m_rxTxSemaphore->Post();

		if (ret != wxSEMA_NO_ERROR){
			PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore Post Failed, Error = %d", ret);
		}

	//};

		PSU_DEBUG_PRINT(MSG_DEBUG, "Thread finished.");

	return NULL;
}
