/**
 * @brief ReceiveISPCheckStatusTask.cpp
 */

#include "Task.h"

ReceiveISPCheckStatusTask::ReceiveISPCheckStatusTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_ReceiveISPCheckStatusTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;
}

ReceiveISPCheckStatusTask::~ReceiveISPCheckStatusTask(void){

}

void ReceiveISPCheckStatusTask::Draw(void){

}

#define ISP_ENDDATA_BYTES_TO_READ  8
int ReceiveISPCheckStatusTask::Main(double elapsedTime){
	
	static unsigned char isp_send_data_repeat = 0;
	bool isp_response_error = false;

	// Receive Data 
	unsigned int ispEndDataBytesToRead = ISP_ENDDATA_BYTES_TO_READ;//(*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_ENDDATA_BYTES_TO_READ : ISP_ENDDATA_BYTES_TO_READ + 2;

#ifndef ISP_DONT_WAIT_RESPONSE
	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data From I/O, Bytes To Read = %d", (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_ENDDATA_BYTES_TO_READ : ISP_ENDDATA_BYTES_TO_READ + 2);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, ispEndDataBytesToRead);

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
	if (PMBUSHelper::IsISPCheckStatusResponseOK(this->m_CurrentIO, this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0])) == PMBUSHelper::response_ok){
		
		PSU_DEBUG_PRINT(MSG_DEBUG, "ISP Check Status OK");

		PMBUSHelper::IspErrRetry = 0;

		//new(TP_SendISPCheckStatusTask) SendISPCheckStatusTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);

		switch (*this->m_ispStatus){

		case ISP_Status_VerifyBeforeStart: // Verify Before Start

			// Start Send Data
			*this->m_ispStatus = ISP_Status_InProgress;
			this->m_tiHexFileStat->begin();
			PSU_DEBUG_PRINT(MSG_DEBUG, "ISP Start Send HEX Data, Start Address = 0x%08lx", this->m_tiHexFileStat->currentAddress());
			new(TP_SendISPWriteDataTask) SendISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);

			break;

		case ISP_Status_InProgress: // In Progress

			if (this->m_tiHexFileStat->endOfData()){
				PSU_DEBUG_PRINT(MSG_DEBUG, "ISP Latest HEX Data Has Been Sent : Current Address = 0x%08lx", this->m_tiHexFileStat->currentAddress());
				new(TP_SendISPEndCMDTask) SendISPEndCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "ISP Sending HEX Data : Current Address = 0x%08lx", this->m_tiHexFileStat->currentAddress());

				PSU_DEBUG_PRINT(MSG_DEBUG, "isp_send_data_repeat = %d", isp_send_data_repeat);

				// Repeat Send ISP Data for Test, Send 1 Address Twice
				isp_send_data_repeat++;
				isp_send_data_repeat%=2;
				if(isp_send_data_repeat%2 == 1){
					this->m_tiHexFileStat->jumpTo(this->m_tiHexFileStat->currentAddress()-8);
				}

				PSU_DEBUG_PRINT(MSG_ALERT, "Repeat Send Address = 0x%08lx", this->m_tiHexFileStat->currentAddress());

				new(TP_SendISPWriteDataTask) SendISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
			}

			break;

		case ISP_Status_UserRequestCancel:// User Request Cancel
			PSU_DEBUG_PRINT(MSG_ERROR, "User Request Cancel");
			break;


		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error, ISP Status = %x", *this->m_ispStatus);
			break;
		}


	}
	else{

		PMBUSHelper::IspErrRetry++;

		if (PMBUSHelper::IspErrRetry <= ISP_CHECK_STATUS_RETRY){
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Check Status Retry : %d", PMBUSHelper::IspErrRetry);

#ifdef	ISP_F3_CMD_FAILED_RETRY_SLEEP
			wxMilliSleep(ISP_F3_CMD_FAILED_RETRY_SLEEP_TIME);
#endif
			new(TP_SendISPCheckStatusTask) SendISPCheckStatusTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
		}
		else{
			PSU_DEBUG_PRINT(MSG_ERROR, "ISP Check Status Failed");
			*this->m_ispStatus = ISP_Status_ResponseDataError;
			PMBUSHelper::IspErrRetry = 0;
		}
	}

	delete this;

	return 0;
}
