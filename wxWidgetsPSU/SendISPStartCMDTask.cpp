/**
 * @brief SendISPStartCMDTask.cpp
 */

#include "Task.h"

SendISPStartCMDTask::SendISPStartCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand, TIHexFileParser* tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_SendISPStartCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusSendCommand = pmbusSendCommand;

	this->m_tiHexFileStat = tiHexFileStat;
	this->m_ispStatus = ispStatus;
}

SendISPStartCMDTask::~SendISPStartCMDTask(void){

}

void SendISPStartCMDTask::Draw(void){

}


int SendISPStartCMDTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPStartCMDTask);

	PSU_DEBUG_PRINT(MSG_ALERT, "Count of Task = %d", cnt);

	PSU_DEBUG_PRINT(MSG_ALERT, "Send Buffer Length = %d", this->m_pmbusSendCommand.m_sendDataLength);

	wxString str("Send Data : ");
	for (unsigned int idx = 0; idx < this->m_pmbusSendCommand.m_sendDataLength; idx++){
		str += wxString::Format(" %02x ", this->m_pmbusSendCommand.m_sendData[idx]);
	}
	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());

	/*----------------------------------------------*/

	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_pmbusSendCommand.m_sendData, this->m_pmbusSendCommand.m_sendDataLength);
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
		new(TP_ReceiveISPStartCMDTask) ReceiveISPStartCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_pmbusSendCommand, this->m_tiHexFileStat, this->m_ispStatus);
	}

	delete this;

	return 0;
}