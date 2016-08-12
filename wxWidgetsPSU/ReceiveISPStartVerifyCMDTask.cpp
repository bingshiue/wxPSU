/**
 * @brief ReceiveISPStartVerifyCMDTask.cpp
 */

#include "Task.h"

ReceiveISPStartVerifyCMDTask::ReceiveISPStartVerifyCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus, unsigned char target){
	this->m_id = task_ID_ReceiveISPStartVerifyCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;

	this->m_target = target;
}

ReceiveISPStartVerifyCMDTask::~ReceiveISPStartVerifyCMDTask(void){

}

void ReceiveISPStartVerifyCMDTask::Draw(void){

}

#define ISP_ENDDATA_BYTES_TO_READ  8
int ReceiveISPStartVerifyCMDTask::Main(double elapsedTime){
		
	// Receive Data 
	unsigned int ispEndDataBytesToRead = ISP_ENDDATA_BYTES_TO_READ;//(*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_ENDDATA_BYTES_TO_READ : ISP_ENDDATA_BYTES_TO_READ + 2;

#ifndef ISP_DONT_WAIT_RESPONSE
	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data From I/O, Bytes To Read = %d", (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_ENDDATA_BYTES_TO_READ : ISP_ENDDATA_BYTES_TO_READ + 2);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, ispEndDataBytesToRead);

	if (this->m_recvBuff.m_length == 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);

#ifndef IGNORE_ISP_RESPONSE_ERROR
		*this->m_ispStatus = ISP_Status_ResponseDataError;
		delete this;
		return -1;
#endif
	}

	wxString str("Receive Data :");
	for (unsigned int idx = 0; idx < this->m_recvBuff.m_length; idx++){
		str += wxString::Format(" %02x ", this->m_recvBuff.m_recvBuff[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());
#endif

	// If Response is OK
	if (PMBUSHelper::IsISPStartVerifyResponseOK(this->m_CurrentIO, this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0]),this->m_target) == PMBUSHelper::response_ok){

		PSU_DEBUG_PRINT(MSG_ALERT, "ISP Verify Start CMD Success");

		new(TP_SendISPCheckStatusTask) SendISPCheckStatusTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);

	}
	else{
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start CMD Verify Failed");
		*this->m_ispStatus = ISP_Status_ResponseDataError;
	}

	delete this;

	return 0;
}