/**
 * @file ClearIOReadBufferTask.cpp
 */
#include "Task.h"

ClearIOReadBufferTask::ClearIOReadBufferTask(IOACCESS* ioaccess, unsigned int* currentIO, bool readUntilNoData){
	this->m_id = task_ID_ClearIOReadBufferTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_readUntilNoData = readUntilNoData;
}


ClearIOReadBufferTask::~ClearIOReadBufferTask(void){

}

void ClearIOReadBufferTask::Draw(void){

}

int ClearIOReadBufferTask::Main(double elapsedTime){

	int readLength = 0;
	unsigned char readBuff[256] = { 0 };

	do {
		
		PSU_DEBUG_PRINT(MSG_ALERT, "ClearIOReadBufferTask");
		
		readLength = 0;

		readLength = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(readBuff, 32);

		if (this->m_readUntilNoData == false){
			break;
		}

		wxMilliSleep(5);

	} while (readLength > 0);

	delete this;

	return 0;
}