/**
 * @brief SendISPEndCMDTask.cpp
 */

#include "Task.h"

SendISPEndCMDTask::SendISPEndCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_SendISPEndCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;
	this->m_ispStatus = ispStatus;
}

SendISPEndCMDTask::~SendISPEndCMDTask(void){

}

void SendISPEndCMDTask::Draw(void){

}

unsigned int SendISPEndCMDTask::ProductSendBuffer(unsigned char* buffer){

	unsigned int active_index = 0;

	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:

		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = 0x00; // End

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
		buffer[active_index++] = 0x00; // End

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
		buffer[active_index++] = 0x00; // End

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
		buffer[active_index++] = 0x00; // End
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 3); // PEC

		// Update Write Bytes For Write CMD
		buffer[0] = active_index - 3;

		break;


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;
}

int SendISPEndCMDTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPEndCMDTask);

	PSU_DEBUG_PRINT(MSG_DEBUG, "Count of Task = %d", cnt);

	unsigned int sendDataLength = 0;
	sendDataLength = this->ProductSendBuffer(this->m_sendBuff);


	wxString str("Send Data : ");
	for (unsigned int idx = 0; idx < sendDataLength; idx++){
		str += wxString::Format(" %02x ", m_sendBuff[idx]);
	}
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());

	/*----------------------------------------------*/

	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(m_sendBuff, (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64);
		if (sendResult <= 0){
			PSU_DEBUG_PRINT(MSG_ERROR, "IO Send Write CMD Failed, sendResult=%d", sendResult);
			// Retry 
			retry++;
			if (retry >= 3){
				PSU_DEBUG_PRINT(MSG_ERROR, "Still Send Write CMD Failed, Retry Times = %d", retry);
				sendRetryStillFailed = true;
				break;
			}
			else{
				PSU_DEBUG_PRINT(MSG_ERROR, "Send Write CMD Retry Times = %d", retry);
			}

		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Write CMD Success");
		}

	} while (sendResult <= 0);

	if (sendRetryStillFailed == true){
		PSU_DEBUG_PRINT(MSG_ERROR, "Send Write CMD Retry Send Still Failed, Give up send !");
		*this->m_ispStatus = ISP_Status_SendDataFailed;
		delete this;
		return -1;
	}

	if (*this->m_ispStatus == ISP_Status_InProgress){
		new(TP_ReceiveISPEndCMDTask) ReceiveISPEndCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
	}

	delete this;

	return 0;
}