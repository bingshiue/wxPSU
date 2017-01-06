/**
 * @brief SendWriteCMDTask.cpp
 */

#include "Task.h"

SendWriteCMDTask::SendWriteCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand){
	this->m_id = task_ID_SendWriteCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusSendCommand = pmbusSendCommand;
}

SendWriteCMDTask::~SendWriteCMDTask(void){

}

void SendWriteCMDTask::Draw(void){

}

int SendWriteCMDTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendWriteCMDTask);

	PSU_DEBUG_PRINT(MSG_DETAIL, "Count of Task = %d", cnt);

	unsigned char writeCMD; 
	
	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:
		
		writeCMD = this->m_pmbusSendCommand.m_sendData[3];

		break;

	case IOACCESS_HID:

		writeCMD = this->m_pmbusSendCommand.m_sendData[5];

		break;

	case IOACCESS_TOTALPHASE:

		writeCMD = this->m_pmbusSendCommand.m_sendData[3];

		break;

	default:

		break;
	}

	wxString msg("Send Write Command ");
	msg += (wxString::Format("%x H", writeCMD).Upper());

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", msg.c_str());

	PSU_DEBUG_PRINT(MSG_DEBUG, "Send Buffer Length = %d", this->m_pmbusSendCommand.m_sendDataLength);

	wxString str("Send Data : ");
	for (unsigned int idx = 0; idx < this->m_pmbusSendCommand.m_sendDataLength; idx++){
		str += wxString::Format(" %02x ", this->m_pmbusSendCommand.m_sendData[idx]);
	}
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());
	
	/*----------------------------------------------*/

	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_pmbusSendCommand.m_sendData, this->m_pmbusSendCommand.m_sendDataLength);
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
				PSU_DEBUG_PRINT(MSG_ALERT, "Send Write CMD Retry Times = %d", retry);
			}

		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Write CMD Success");
		}

	} while (sendResult <= 0);

	if (sendRetryStillFailed == true){
		PSU_DEBUG_PRINT(MSG_ERROR, "Send Write CMD Retry Send Still Failed, Give up send !");
		delete this;
		return -1;
	}

	new(TP_ReceiveWriteCMDTask) ReceiveWriteCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_pmbusSendCommand);

	delete this;

	return 0;
}