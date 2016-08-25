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

unsigned int ReceiveISPStartVerifyCMDTask::ProductISPStartCMDSendBuffer(unsigned char* buffer){
	// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xF0, this->m_target, 0x00, 0x0D, 0x0A
	unsigned int active_index = 0;

	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = 0xF0; // CMD
		buffer[active_index++] = this->m_target; // Target

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;

	case IOACCESS_HID:
		buffer[active_index++] = 0x05;
		buffer[active_index++] = 0x08;
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = 0xF0; // CMD
		buffer[active_index++] = this->m_target; // Target

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;
}

#define ISP_ENDDATA_BYTES_TO_READ  8
#define CMD_F0H_BYTES_TO_READ  6/**< Bytes To Read */
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

		PMBUSHelper::IspStartVerifyRetry = 0;
		
		PSU_DEBUG_PRINT(MSG_ALERT, "ISP Verify Start CMD Success");

#ifdef ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY
		if (this->m_target == UPDATE_PRIMARY_FW_TARGET){
			PSU_DEBUG_PRINT(MSG_ALERT, "ISP Wait %.1f Sec For Start Update Primary FW", (double)ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY_TIME/1000);
			wxMilliSleep(ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY_TIME);
		}
#endif

		new(TP_SendISPCheckStatusTask) SendISPCheckStatusTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);

	}
	else{
		
		PMBUSHelper::IspStartVerifyRetry++;

		// Retry 
		if (PMBUSHelper::IspStartVerifyRetry <= ISP_START_VERIFY_RETRY){
			
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start Verify Retry : %d", PMBUSHelper::IspStartVerifyRetry);

#ifdef	ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP
			wxMilliSleep(ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP_TIME);
#endif
	
			// Solution 1 : Re-call SendISPStartVerifyCMDTask

			//new(TP_SendISPStartVerifyCMDTask) SendISPStartVerifyCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);


			// Solution 2: Re-call SendISPStartCMDTask
			/*** Prpare Send Data Buffer ***/
			unsigned char SendBuffer[64];
			unsigned int sendDataLength = this->ProductISPStartCMDSendBuffer(SendBuffer);

			PMBUSSendCOMMAND_t CMDF0H;

			CMDF0H.m_sendDataLength = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
			CMDF0H.m_bytesToRead = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? CMD_F0H_BYTES_TO_READ : CMD_F0H_BYTES_TO_READ + 1;
			for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
				CMDF0H.m_sendData[idx] = SendBuffer[idx];
			}

			new(TP_SendISPStartCMDTask) SendISPStartCMDTask(m_IOAccess, m_CurrentIO, CMDF0H, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);

		}
		else{
			
			PMBUSHelper::IspStartVerifyRetry=0;
			
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Start CMD Verify Failed");
			*this->m_ispStatus = ISP_Status_ResponseDataError;
		}
	}

	delete this;

	return 0;
}