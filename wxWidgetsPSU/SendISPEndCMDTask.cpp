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
		buffer[active_index++] = 0xF0; // CMD
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
		buffer[active_index++] = 0xF0; // CMD
		buffer[active_index++] = 0x00; // End

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;


	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return active_index;
}

int SendISPEndCMDTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPEndCMDTask);

	PSU_DEBUG_PRINT(MSG_ALERT, "Count of Task = %d", cnt);

#if 0
	// Product End Command Buffer
	m_sendBuff[0] = 0x41;
	m_sendBuff[1] = 0x54;
	m_sendBuff[2] = PMBUSHelper::GetSlaveAddress(); // Slave Address
	m_sendBuff[3] = 0xf0;// Command
	m_sendBuff[4] = 0x00;// Stop
	m_sendBuff[5] = PMBusSlave_Crc8MakeBitwise(0, 7, m_sendBuff + 2, 3);;// pec
	m_sendBuff[6] = 0x0d;
	m_sendBuff[7] = 0x0a;
	//

	wxString str("Send Data : ");
	for (unsigned int idx = 0; idx < 8; idx++){
		str += wxString::Format(" %02x ", m_sendBuff[idx]);
	}
	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());
#endif

	unsigned int sendDataLength = 0;
	sendDataLength = this->ProductSendBuffer(this->m_sendBuff);


	wxString str("Send Data : ");
	for (unsigned int idx = 0; idx < sendDataLength; idx++){
		str += wxString::Format(" %02x ", m_sendBuff[idx]);
	}
	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());

	/*----------------------------------------------*/

	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(m_sendBuff, (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64);
		if (sendResult <= 0){
			PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Write CMD Failed, sendResult=%d", sendResult);
			// Retry 
			retry++;
			if (retry >= 3){
				PSU_DEBUG_PRINT(MSG_ALERT, "Still Send Write CMD Failed, Retry Times = %d", retry);
				sendRetryStillFailed = true;
				break;
			}
			else{
				PSU_DEBUG_PRINT(MSG_ALERT, "Send Write CMD Retry Times = %d", retry);
			}

		}
		else{
			PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Write CMD Success");
		}

	} while (sendResult <= 0);

	if (sendRetryStillFailed == true){
		PSU_DEBUG_PRINT(MSG_ALERT, "Send Write CMD Retry Send Still Failed, Forgive to send !");
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