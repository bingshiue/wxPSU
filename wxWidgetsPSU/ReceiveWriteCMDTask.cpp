/**
 * @brief ReceiveWriteCMDTask.cpp
 */

#include "Task.h"

ReceiveWriteCMDTask::ReceiveWriteCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand){
	this->m_id = task_ID_ReceiveWriteCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_pmbusSendCommand = pmbusSendCommand;
}

ReceiveWriteCMDTask::~ReceiveWriteCMDTask(void){

}

void ReceiveWriteCMDTask::Draw(void){

}

int ReceiveWriteCMDTask::Main(double elapsedTime){
	// Receive Data 
	int ret;

	PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From I/O, Bytes To Read = %d", this->m_pmbusSendCommand.m_bytesToRead);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, this->m_pmbusSendCommand.m_bytesToRead);

	if (this->m_recvBuff.m_length == 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);

		//new(TP_SendWriteCMDTask) SendWriteCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_pmbusSendCommand);

		delete this;
		return -1;
	}

	wxString str("Receive Data :");
	for (unsigned int idx = 0; idx < this->m_recvBuff.m_length; idx++){
		str += wxString::Format(" %02x ", this->m_recvBuff.m_recvBuff[idx]);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());

	delete this;

	return 0;
}