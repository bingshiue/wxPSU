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
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
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
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;

	case IOACCESS_PICKIT:

		// 0x03 [0x06] 0x81 0x84 [0x05] [0xB6] [0xEC] [0x00] [0x08] [0xE0] 0x82 0x1f 0x77
		buffer[active_index++] = 0x00;
		buffer[active_index++] = 0x03;
		buffer[active_index++] = 0x00; // Total Length, Determine Later
		buffer[active_index++] = 0x81;
		buffer[active_index++] = 0x84;
		buffer[active_index++] = 1 + 3;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target

		// Compute PEC
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 6, 3);

		// Fill Last 3
		buffer[active_index++] = 0x82;
		buffer[active_index++] = 0x1f;
		buffer[active_index++] = 0x77;

		// Fill Total Length
		buffer[2] = active_index - 3;

		break;

	case IOACCESS_TOTALPHASE:

		buffer[active_index++] = 2; // Write Bytes
		buffer[active_index++] = 0; // Read Bytes
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target;
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 3); // PEC

		// Update Write Bytes For Write CMD
		buffer[0] = active_index - 3;

		break;

	case IOACCESS_TRC2_I2C_ADAPTER:

		buffer[active_index++] = 0x00;
		buffer[active_index++] = 0x02;// Group
		buffer[active_index++] = 0x01;// Interface
		buffer[active_index++] = 0x51;// Action : Write
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Data Package Start, Slave Address
		buffer[active_index++] = 1+1+1;//    Write Length 1+1+ : slave command + pec
		buffer[active_index++] = 0x00;//    Read Length
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD();// Write Data Start
		buffer[active_index++] = this->m_target;

		// Compute PEC
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwiseDiscont(&PMBUSHelper::GetSlaveAddress(), 1, buffer+7, 1+1);
				//PMBusSlave_Crc8MakeBitwise(0, 7, sendBuffer + 4, 2 + pmBusWriteCMD->m_numOfSendBytes);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", buffer[active_index-1]);

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
	if (PMBUSHelper::IsISPStartVerifyResponseOK(this->m_CurrentIO, this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0]),this->m_target) == PMBUSHelper::response_ok){

		PMBUSHelper::IspStartVerifyRetry = 0;
		
		PSU_DEBUG_PRINT(MSG_ALERT, "ISP Verify Start CMD Success");

#ifdef ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY
		if (this->m_target == UPDATE_PRIMARY_FW_TARGET){
			//PSU_DEBUG_PRINT(MSG_ALERT, "ISP Wait %.1f Sec For Start Update Primary FW", (double)ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY_TIME/1000);
			//wxMilliSleep(ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY_TIME);
			PSU_DEBUG_PRINT(MSG_ALERT, "ISP Wait %.1f Sec For Start Update PFC FW", (double)(PMBUSHelper::GetAppSettings()->m_ISPPFCStartVerifySuccessDelayTime)/1000);
			wxMilliSleep(PMBUSHelper::GetAppSettings()->m_ISPPFCStartVerifySuccessDelayTime);
		}
#endif

#ifdef PFC_ISP_F3_CMD_DELAY
		// If ISP Target is Primary, 
		if (UPDATE_PRIMARY_FW_TARGET == PMBUSHelper::getCurrentISPTarget()){

			
			switch (*this->m_CurrentIO){

			case IOACCESS_SERIALPORT:
			case IOACCESS_HID:
			case IOACCESS_PICKIT:

				if (PMBUSHelper::GetAppSettings()->m_pfcIspF3CMDDelayTime > 0){
					// Sleep (For wait primary chip return correct reponse ) 
					PSU_DEBUG_PRINT(MSG_DEBUG, "Sleep %d ms for Delay F3 CMD", PMBUSHelper::GetAppSettings()->m_pfcIspF3CMDDelayTime);
					wxMilliSleep(PMBUSHelper::GetAppSettings()->m_pfcIspF3CMDDelayTime);
				}

				break;

			case IOACCESS_TOTALPHASE:

				if (PMBUSHelper::GetAppSettings()->m_pfcIspF3CMDTotalPhaseDelayTime > 0){
					// Sleep (For wait primary chip return correct reponse ) 
					PSU_DEBUG_PRINT(MSG_DEBUG, "Sleep %d ms for Delay F3 CMD", PMBUSHelper::GetAppSettings()->m_pfcIspF3CMDTotalPhaseDelayTime);
					wxMilliSleep(PMBUSHelper::GetAppSettings()->m_pfcIspF3CMDTotalPhaseDelayTime);
				}

				break;

			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs !");
				break;
			}
			
#if 0
			// If Current Use I/O is Serial Port
			if (*this->m_CurrentIO == IOACCESS_SERIALPORT){

				// If Buad Rate large than '9600'
				if (PMBUSHelper::GetAppSettings()->m_comportSetting.m_buadRate > CBR_9600){

					if (PMBUSHelper::GetAppSettings()->m_ispF3CMDDelayTime > 0){
						// Sleep (For wait primary chip return correct reponse ) 
						PSU_DEBUG_PRINT(MSG_DEBUG, "Sleep %d ms for Delay F3 CMD", PMBUSHelper::GetAppSettings()->m_ispF3CMDDelayTime);
						wxMilliSleep(PMBUSHelper::GetAppSettings()->m_ispF3CMDDelayTime);
					}
				}
			}
#endif

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
