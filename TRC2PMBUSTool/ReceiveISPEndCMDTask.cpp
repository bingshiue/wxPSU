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

	bool isp_response_error = false;

	// Receive Data 
	unsigned int ispEndDataBytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_CurrentIO, ISP_ENDDATA_BYTES_TO_READ);//(*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_ENDDATA_BYTES_TO_READ : ISP_ENDDATA_BYTES_TO_READ + 1;

#ifndef ISP_DONT_WAIT_RESPONSE
	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data From I/O, Bytes To Read = %d", ispEndDataBytesToRead);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, ispEndDataBytesToRead);

	if (this->m_recvBuff.m_length == 0){

		switch (*this->m_CurrentIO){

		case IOACCESS_SERIALPORT:
		case IOACCESS_HID:
		case IOACCESS_PICKIT:
			PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);
			isp_response_error = true;
			break;

		case IOACCESS_TOTALPHASE:
			if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
				PSU_DEBUG_PRINT(MSG_ERROR, "I2C WriteRead Failed, Error=%d", PMBUSHelper::getTotalPhaseWriteReadLastError());
			}
			break;

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
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
		
		PSU_DEBUG_PRINT(MSG_ALERT, "ISP End Command Response OK");

		switch (PMBUSHelper::getCurrentISPTarget()){

		case UPDATE_PRIMARY_FW_TARGET:// PFC
			PSU_DEBUG_PRINT(MSG_ALERT, "ISP Wait PFC Reboot, Wait %ld Milliseconds", PMBUSHelper::GetAppSettings()->m_ISPPFCWaitRootTime);
			wxMilliSleep(PMBUSHelper::GetAppSettings()->m_ISPPFCWaitRootTime);
			break;
	
		case UPDATE_SECONDARY_FW_TARGET:// DD
			PSU_DEBUG_PRINT(MSG_ALERT, "ISP Wait DD Reboot, Wait %ld Milliseconds", PMBUSHelper::GetAppSettings()->m_ISPDDWaitRootTime);
			wxMilliSleep(PMBUSHelper::GetAppSettings()->m_ISPDDWaitRootTime);
			break;

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Wrong ISP TARGET");
			break;
		}

		new(TP_SendRebootCheckTask) SendRebootCheckTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
		
		//PSU_DEBUG_PRINT(MSG_ALERT, "Send ISP Data Sequence All Done Without Errors");
		
		//*this->m_ispStatus = ISP_Status_ALLDone;
	}
	else{
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP End Command Response Failed");
		*this->m_ispStatus = ISP_Status_ResponseDataError;
	}

	delete this;

	return 0;
}
