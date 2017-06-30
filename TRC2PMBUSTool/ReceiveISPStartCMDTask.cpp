/**
 * @brief ReceiveISPStartCMDTask.cpp
 */

#include "Task.h"

ReceiveISPStartCMDTask::ReceiveISPStartCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus, unsigned char target){
	this->m_id = task_ID_ReceiveISPStartCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_pmbusSendCommand = pmbusSendCommand;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;

	this->m_target = target;
}

ReceiveISPStartCMDTask::~ReceiveISPStartCMDTask(void){

}

void ReceiveISPStartCMDTask::Draw(void){

}

int ReceiveISPStartCMDTask::Main(double elapsedTime){

	bool isp_response_error = false;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Sleep %d Milliseconds", DELAY_READ_ISP_START_VERIFY_RESPONSE);

	wxMilliSleep(DELAY_READ_ISP_START_VERIFY_RESPONSE);

	// Receive Data 

#ifndef ISP_DONT_WAIT_RESPONSE
	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data From I/O, Bytes To Read = %d", this->m_pmbusSendCommand.m_bytesToRead);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, this->m_pmbusSendCommand.m_bytesToRead);

	if (this->m_recvBuff.m_length == 0){
		
		switch (*this->m_CurrentIO){

		case IOACCESS_SERIALPORT:
		case IOACCESS_HID:
		case IOACCESS_PICKIT:
		case IOACCESS_TRC2_I2C_ADAPTER:
			PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);
			isp_response_error = true;
			break;

		case IOACCESS_TOTALPHASE:
			if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
				PSU_DEBUG_PRINT(MSG_ERROR, "I2C WriteRead Failed, Error=%d", PMBUSHelper::getTotalPhaseWriteReadLastError());
			}
			break;

		default:
			PSU_DEBUG_PRINT(MSG_ERROR,"Something Error Occurs");
			break;
		}

#ifndef IGNORE_ISP_RESPONSE_ERROR
		if (isp_response_error == true){
			*this->m_ispStatus = ISP_Status_ResponseDataError;
			delete this;
			return -1;
		}
#endif
	}

	wxString str("Receive Data :");
	for (unsigned int idx = 0; idx < this->m_recvBuff.m_length; idx++){
		str += wxString::Format(" %02x ", this->m_recvBuff.m_recvBuff[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());
#endif

	// If Response is OK
	if (PMBUSHelper::IsResponseOK(this->m_CurrentIO, this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0])) == PMBUSHelper::response_ok){
		
		PSU_DEBUG_PRINT(MSG_DEBUG, "Call SendISPStartVerifyCMDTask");
		new(TP_SendISPStartVerifyCMDTask) SendISPStartVerifyCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);

#if 0
		// Start Send Data
		this->m_tiHexFileStat->begin();
		PSU_DEBUG_PRINT(MSG_ALERT, "Start Address = %08x", this->m_tiHexFileStat->currentAddress());
		new(TP_SendISPWriteDataTask) SendISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
#endif
	}
	else{
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Response Data Not OK");
		*this->m_ispStatus = ISP_Status_ResponseDataError;
	}

	delete this;

	return 0;
}
