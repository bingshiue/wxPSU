/**
 * @brief ReceiveISPStartCMDTask.cpp
 */

#include "Task.h"

ReceiveISPStartCMDTask::ReceiveISPStartCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_ReceiveISPStartCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_pmbusSendCommand = pmbusSendCommand;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;
}

ReceiveISPStartCMDTask::~ReceiveISPStartCMDTask(void){

}

void ReceiveISPStartCMDTask::Draw(void){

}

int ReceiveISPStartCMDTask::Main(double elapsedTime){
	// Receive Data 
	int ret;

	PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From I/O, Bytes To Read = %d", this->m_pmbusSendCommand.m_bytesToRead);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, this->m_pmbusSendCommand.m_bytesToRead);

	if (this->m_recvBuff.m_length == 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);

#ifndef IGNORE_ISP_RESPONSE_ERROR
		*this->m_ispStatus = ISP_Status_ErrorOccurs;
		delete this;
		return -1;
#endif
	}

	wxString str("Receive Data :");
	for (unsigned int idx = 0; idx < this->m_recvBuff.m_length; idx++){
		str += wxString::Format(" %02x ", this->m_recvBuff.m_recvBuff[idx]);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());

	// If Response is OK
	if (PMBUSHelper::IsResponseOK(this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0])) == PMBUSHelper::response_ok){
		// Start Send Data
		this->m_tiHexFileStat->begin();
		PSU_DEBUG_PRINT(MSG_ALERT, "Start Address = %08x", this->m_tiHexFileStat->currentAddress());
		new(TP_SendISPWriteDataTask) SendISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
	}

	delete this;

	return 0;
}