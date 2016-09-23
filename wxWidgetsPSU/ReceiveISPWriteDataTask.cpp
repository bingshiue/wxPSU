/**
 * @brief ReceiveISPWriteDataTask.cpp
 */

#include "Task.h"

ReceiveISPWriteDataTask::ReceiveISPWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_ReceiveISPWriteDataTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ispStatus = ispStatus;
}

ReceiveISPWriteDataTask::~ReceiveISPWriteDataTask(void){

}

void ReceiveISPWriteDataTask::Draw(void){

}

#define ISP_WRITEDATA_BYTES_TO_READ  6
int ReceiveISPWriteDataTask::Main(double elapsedTime){
	// Receive Data 
	unsigned int ispDataBytesToRead = 0;

	ispDataBytesToRead = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? ISP_WRITEDATA_BYTES_TO_READ : ISP_WRITEDATA_BYTES_TO_READ+1;

	unsigned long hexStartAddr = 0;
	this->m_tiHexFileStat->startAddress(&hexStartAddr);
	//PSU_DEBUG_PRINT(MSG_DEBUG, "Hex Start Address = %08x", hexStartAddr);

	if (hexStartAddr == (this->m_tiHexFileStat->currentAddress() - 8)){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Delay 200 ms after sent data of the start address");
		// Need To Delay 200 ms after sent data of the start address
		wxMilliSleep(200);
	}


	//PSU_DEBUG_PRINT(MSG_DEBUG, "Current Address = %08x", this->m_tiHexFileStat->currentAddress());

	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data From I/O, Bytes To Read = %d", ispDataBytesToRead);

#ifndef ISP_DONT_WAIT_RESPONSE
	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, ispDataBytesToRead);

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
	if (PMBUSHelper::IsResponseOK(this->m_CurrentIO, this->m_recvBuff.m_recvBuff, sizeof(this->m_recvBuff.m_recvBuff) / sizeof(this->m_recvBuff.m_recvBuff[0])) == PMBUSHelper::response_ok){
        
#ifdef ISP_F3_CMD_DELAY
		// If ISP Target is Primary, 
		if (UPDATE_PRIMARY_FW_TARGET == PMBUSHelper::getCurrentISPTarget()){
			
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
		}
#endif

		new(TP_SendISPCheckStatusTask) SendISPCheckStatusTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);

#if 0
		if (this->m_tiHexFileStat->endOfData()){
			PSU_DEBUG_PRINT(MSG_ALERT, "End of Data : Current Address = 0x%08x", this->m_tiHexFileStat->currentAddress());
			new(TP_SendISPEndCMDTask) SendISPEndCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
		}
		else{
			new(TP_SendISPWriteDataTask) SendISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
		}
#endif

	}
	else{
		PSU_DEBUG_PRINT(MSG_ERROR, "ISP Response Data Not OK");
		*this->m_ispStatus = ISP_Status_ResponseDataError;
	}

	delete this;

	return 0;
}