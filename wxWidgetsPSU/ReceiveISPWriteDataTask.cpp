/**
 * @brief ReceiveISPWriteDataTask.cpp
 */

#include "Task.h"

ReceiveISPWriteDataTask::ReceiveISPWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_ReceiveISPWriteDataTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;
}

ReceiveISPWriteDataTask::~ReceiveISPWriteDataTask(void){

}

void ReceiveISPWriteDataTask::Draw(void){

}

#define ISP_WRITEDATA_BYTES_TO_READ  6
int ReceiveISPWriteDataTask::Main(double elapsedTime){
	// Receive Data 
	unsigned int ispDataBytesToRead = 0;

	ispDataBytesToRead = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_WRITEDATA_BYTES_TO_READ : ISP_WRITEDATA_BYTES_TO_READ+1;

	PSU_DEBUG_PRINT(MSG_ALERT, "Current Address = %08x", this->m_tiHexFileStat->currentAddress());
	PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From I/O, Bytes To Read = %d", ispDataBytesToRead);

#ifndef ISP_DONT_WAIT_RESPONSE
	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, ispDataBytesToRead);

	if (this->m_recvBuff.m_length == 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);

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

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());
#endif

	// If Response is OK
	if (PMBUSHelper::IsResponseOK(this->m_CurrentIO, this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0])) == PMBUSHelper::response_ok){

		if (this->m_tiHexFileStat->endOfData()){
			PSU_DEBUG_PRINT(MSG_ALERT, "End of Data : Current Address = 0x%08x", this->m_tiHexFileStat->currentAddress());
			new(TP_SendISPEndCMDTask) SendISPEndCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
		}
		else{
			new(TP_SendISPWriteDataTask) SendISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
		}

	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "ISP Response Data Not OK");
		*this->m_ispStatus = ISP_Status_ResponseDataError;
	}

	delete this;

	return 0;
}