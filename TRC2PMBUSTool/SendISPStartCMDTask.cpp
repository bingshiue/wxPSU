/**
 * @brief SendISPStartCMDTask.cpp
 */

#include "Task.h"

SendISPStartCMDTask::SendISPStartCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand, TIHexFileParser* tiHexFileStat, unsigned char* ispStatus, unsigned char target){
	this->m_id = task_ID_SendISPStartCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusSendCommand = pmbusSendCommand;

	this->m_tiHexFileStat = tiHexFileStat;
	this->m_ispStatus = ispStatus;

	this->m_target = target;

	PMBUSHelper::getCurrentISPTarget() = target;

#ifdef ISP_F3_CMD_DELAY
	// If ISP Target is Primary, 
	if (UPDATE_PRIMARY_FW_TARGET == PMBUSHelper::getCurrentISPTarget()){

		// If Current Use I/O is Serial Port
		if (*this->m_CurrentIO == IOACCESS_SERIALPORT){

			// If Buad Rate large than '9600'
			if (PMBUSHelper::GetAppSettings()->m_comportSetting.m_buadRate > CBR_9600){

				// Sleep (For wait primary chip return correct reponse ) 
				PSU_DEBUG_PRINT(MSG_ALERT, "ISP F3 CMD Delay Time is %d ms", PMBUSHelper::GetAppSettings()->m_ispF3CMDDelayTime);				
			}
		}
	}
#endif

}

SendISPStartCMDTask::~SendISPStartCMDTask(void){

}

void SendISPStartCMDTask::Draw(void){

}


int SendISPStartCMDTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPStartCMDTask);

	if (PMBUSHelper::runInMode == Generic_Enable){
		PSU_DEBUG_PRINT(MSG_ALERT, "Run In Mode Enable");
		PSU_DEBUG_PRINT(MSG_ALERT, "Run In Times = %d", PMBUSHelper::runInTimes);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "ISP Send Start CMD");

	PSU_DEBUG_PRINT(MSG_DETAIL, "Count of Task = %d", cnt);

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
		new(TP_ReceiveISPStartCMDTask) ReceiveISPStartCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_pmbusSendCommand, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);
	}

	delete this;

	return 0;
}