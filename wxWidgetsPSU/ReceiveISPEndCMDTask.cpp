/**
 * @brief ReceiveISPEndCMDTask.cpp
 */

#include "Task.h"

ReceiveISPEndCMDTask::ReceiveISPEndCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_ReceiveISPEndCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;
}

ReceiveISPEndCMDTask::~ReceiveISPEndCMDTask(void){

}

void ReceiveISPEndCMDTask::Draw(void){

}

#define ISP_ENDDATA_BYTES_TO_READ  6
int ReceiveISPEndCMDTask::Main(double elapsedTime){
	// Receive Data 
	int ret;

	PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From I/O, Bytes To Read = %d", ISP_ENDDATA_BYTES_TO_READ);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, ISP_ENDDATA_BYTES_TO_READ);

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
		
		PSU_DEBUG_PRINT(MSG_ALERT, "Send ISP Data Sequence All Done Without Errors");
		
		*this->m_ispStatus = ISP_Status_ALLDone;
	}

	delete this;

	return 0;
}