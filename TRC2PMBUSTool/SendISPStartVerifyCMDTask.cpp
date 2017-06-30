/**
 * @brief SendISPStartVerifyCMDTask.cpp
 */

#include "Task.h"

SendISPStartVerifyCMDTask::SendISPStartVerifyCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* tiHexFileStat, unsigned char* ispStatus, unsigned char target){
	this->m_id = task_ID_SendISPStartVerifyCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;
	this->m_ispStatus = ispStatus;

	this->m_target = target;
}

SendISPStartVerifyCMDTask::~SendISPStartVerifyCMDTask(void){

}

void SendISPStartVerifyCMDTask::Draw(void){

}

unsigned int SendISPStartVerifyCMDTask::ProductSendBuffer(unsigned char* buffer){

	unsigned int active_index = 0;

	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:

		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x44;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress() | 0x01; // Slave Address + 1

		buffer[active_index++] = 0x02;// Response Data Length 

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;

	case IOACCESS_HID:

		buffer[active_index++] = 0x05;
		buffer[active_index++] = 0x0a;
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x44;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress() | 0x01; // Slave Address + 1

		buffer[active_index++] = 0x02;// Response Data Length 

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;

	case IOACCESS_PICKIT:

		buffer[active_index++] = 0x00;
		buffer[active_index++] = 0x03;// Report ID is 0x03
		buffer[active_index++] = 0x0e;
		buffer[active_index++] = 0x81;
		buffer[active_index++] = 0x84;
		buffer[active_index++] = 0x02;// ??? (Maybe This Field Indicates Length of "Slave Address + Command")
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command

		buffer[active_index++] = 0x83;
		buffer[active_index++] = 0x84;
		buffer[active_index++] = 0x01;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress() | 0x01; // Slave Address + 1
		buffer[active_index++] = 0x89;
		buffer[active_index++] = 0x02;// Response Data Length 
		buffer[active_index++] = 0x82;
		buffer[active_index++] = 0x1f;
		buffer[active_index++] = 0x77;

		break;

	case IOACCESS_TOTALPHASE:

		buffer[active_index++] = 1;// write bytes
		buffer[active_index++] = 0x02;// read bytes
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD();

		break;

	case IOACCESS_TRC2_I2C_ADAPTER:

		buffer[active_index++] = 0x00;
		buffer[active_index++] = 0x02;// Group
		buffer[active_index++] = 0x01;// Interface
		buffer[active_index++] = 0x52;// Action : Read
		buffer[active_index++] = (PMBUSHelper::GetSlaveAddress() >> 1);// Data Package Start, Slave Address
		buffer[active_index++] = 0x01;//    Write Length
		buffer[active_index++] = 0x02;//    Read Length
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD();// Write Data Start

		break;


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;
}

int SendISPStartVerifyCMDTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPStartVerifyCMDTask);

	PSU_DEBUG_PRINT(MSG_ALERT, "ISP Send Start Verify CMD");

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

	if (*this->m_ispStatus == ISP_Status_VerifyBeforeStart){
		new(TP_ReceiveISPStartVerifyCMDTask) ReceiveISPStartVerifyCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);
	}

	delete this;

	return 0;
}
