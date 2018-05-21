/**
 * @brief ReceivePollingCMDTask.cpp
 */

#include "Task.h"

ReceivePollingCMDTask::ReceivePollingCMDTask(
	IOACCESS*         ioaccess,
	unsigned int*     currentIO,
	PMBUSCOMMAND_t*   pmBusCommand,
	RECVBUFF_t*       recvBuff,
	unsigned int      recvBuffSize,
	unsigned int      bytesToRead
){
	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_recvBuffSize = recvBuffSize;
	this->m_bytesToRead = bytesToRead;

	this->m_id = task_ID_ReceivePollingCMDTask;
}


ReceivePollingCMDTask::~ReceivePollingCMDTask(void){

}

void ReceivePollingCMDTask::Draw(void){

}

int ReceivePollingCMDTask::Main(double elapsedTime){

	PSU_DEBUG_PRINT(MSG_DEBUG, "Prepare To Read Data From I/O :");

	// Read Data From IO
	this->m_recvBuff->m_length = this->m_ioaccess[*this->m_currentIO].m_DeviceReadData(this->m_recvBuff->m_recvBuff,this->m_bytesToRead);

	delete this;

	return 0;

}
