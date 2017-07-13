/**
 * @file PMBUSReadTestTask.cpp
 */

#include "Task.h"

PMBUSReadTestTask::PMBUSReadTestTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSReadCMD_t* pmbusReadCMD, int setsToRun, bool* outputLog, int intervalTime){
	this->m_id = task_ID_PMBUSReadTestTask;
	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusReadCMDArray = pmbusReadCMD;
	this->m_setsToRun = setsToRun;
	this->m_outputLog = outputLog;
	this->m_intervalTime = intervalTime;

	this->m_running = true;
	this->runningIndex = 0;

	this->startTick = PMBUSHelper::GetTickCountHAL();
}

PMBUSReadTestTask::~PMBUSReadTestTask(void){

}

void PMBUSReadTestTask::Draw(void){

}

int PMBUSReadTestTask::ProductReadCMDBuffer(PMBUSReadCMD_t* pmBusReadCMD, unsigned char* sendBuffer, unsigned int* currentIO){
	// Read Byte/Word , Block Read
	unsigned int baseIndex = 0;
	int buffer_len = 0;

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_cmd;

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr | 0x01;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes;

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		buffer_len = baseIndex;


		break;

	case IOACCESS_HID:

		sendBuffer[baseIndex++] = 0x05;           // Report ID is 0x05
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_cmd;        // Command

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr | 0x01;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes; // Response Data Length

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		sendBuffer[1] = (baseIndex - 2);
		buffer_len = baseIndex;

		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes; // Response Data Length
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x02;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr | 0x01;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes; // Response Data Length

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x01; //
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr | 0x01;

		for (int local = baseIndex; local<64; local++){
			sendBuffer[local] = 0;
		}

		break;

	case IOACCESS_PICKIT:

		//buf[offset++] = 0x00;
		//buf[offset++] = 0x03;
		//buf[offset++] = 0x0e;
		//buf[offset++] = 0x81;
		//buf[offset++] = 0x84;
		//buf[offset++] = 0x02;
		//buf[offset++] = 0xb6;
		//buf[offset++] = 0xec;
		//buf[offset++] = 0x83;
		//buf[offset++] = 0x84;
		//buf[offset++] = 0x01;
		//buf[offset++] = 0xb7;
		//buf[offset++] = 0x89;
		//buf[offset++] = 0x03;
		//buf[offset++] = 0x82;
		//buf[offset++] = 0x1f;
		//buf[offset++] = 0x77;

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x03;// Report ID is 0x03
		sendBuffer[baseIndex++] = 0x0e;
		sendBuffer[baseIndex++] = 0x81;
		sendBuffer[baseIndex++] = 0x84;
		sendBuffer[baseIndex++] = 0x02;// ??? (Maybe This Field Indicates Length of "Slave Address + Command")
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_cmd;// Command

		sendBuffer[baseIndex++] = 0x83;
		sendBuffer[baseIndex++] = 0x84;
		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr | 0x01;
		sendBuffer[baseIndex++] = 0x89;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes; // Response Data Length
		sendBuffer[baseIndex++] = 0x82;
		sendBuffer[baseIndex++] = 0x1f;
		sendBuffer[baseIndex++] = 0x77;

		buffer_len = baseIndex;

		for (int local = baseIndex; local<65; local++){
			sendBuffer[local] = 0;
		}

		break;

	case IOACCESS_TOTALPHASE:
		
		sendBuffer[baseIndex++] = 1;// write bytes
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes;// read bytes
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr;
		sendBuffer[baseIndex++] = pmBusReadCMD->m_cmd;

		buffer_len = baseIndex;

		break;

	case IOACCESS_TRC2_I2C_ADAPTER:

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x02;// Group
		sendBuffer[baseIndex++] = 0x01;// Interface
		sendBuffer[baseIndex++] = 0x52;// Action : Read
		sendBuffer[baseIndex++] = pmBusReadCMD->m_slaveAddr;// Data Package Start, Slave Address
		sendBuffer[baseIndex++] = 0x01;//    Write Length
		sendBuffer[baseIndex++] = pmBusReadCMD->m_numOfReadBytes;//    Read Length
		sendBuffer[baseIndex++] = pmBusReadCMD->m_cmd;// Write Data Start

		buffer_len = baseIndex;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	return buffer_len;
}

int PMBUSReadTestTask::Main(double elapsedTime){

	int sendResult;
	int retry;
	bool sendRetryStillFailed = false;
	int recvLength = 0;
	int bytesToRead;
	static int totalSendTimes = 0;

	int sendDataLength = 0;
	sendDataLength = ProductReadCMDBuffer(&this->m_pmbusReadCMDArray[runningIndex], this->m_sendBuff, this->m_CurrentIO);
	if (*this->m_outputLog == true){
		PSU_DEBUG_PRINT(MSG_ALERT, "SendBufferLen = %d", sendDataLength);
	}


	wxString sendData("Send Data : ");
	if (*this->m_outputLog == true){
		for (int idx = 0; idx < sendDataLength; idx++){
			sendData += wxString::Format(" %02x ", this->m_sendBuff[idx]);
		}
		PSU_DEBUG_PRINT(MSG_ALERT, "%s", sendData.c_str());
	}

	// Decide Send Data Length
	switch (*m_CurrentIO){

	case IOACCESS_PICKIT:
		sendDataLength = HID_SEND_DATA_SIZE + 1;
		break;

	case IOACCESS_HID:
	case IOACCESS_TRC2_I2C_ADAPTER:
		sendDataLength = HID_SEND_DATA_SIZE;
		break;

	default:

		break;
	}


	if (this->m_running){

		retry = 0;

		// Send Read CMD
		do{
			sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_sendBuff, sendDataLength);
			if (sendResult <= 0){
				PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Failed, sendResult=%d", sendResult);
				// Retry 
				retry++;
				if (retry >= 3){
					PSU_DEBUG_PRINT(MSG_ERROR, "Still Send Failed, Retry Times = %d", retry);
					sendRetryStillFailed = true;
					break;
				}
				else{
					PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
				}

			}
			else{
				totalSendTimes++;
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			}

		} while (sendResult <= 0);

		if (sendRetryStillFailed == true){
			PSU_DEBUG_PRINT(MSG_ERROR, "Retry Send Still Failed, Exit Task");
			m_running = false;
			return -1;
		}

		//wxMilliSleep(1);

		// Receive Response
		bytesToRead = this->m_pmbusReadCMDArray[runningIndex].m_numOfReadBytes + BASE_RESPONSE_DATA_LENGTH;
		recvLength = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff, bytesToRead);

		if (*this->m_outputLog == true){
			PSU_DEBUG_PRINT(MSG_ALERT, "RecvLength = %d", recvLength);
		}

		wxString RecvData("Recv Data : ");
		if (*this->m_outputLog == true){
			for (int idx = 0; idx < recvLength; idx++){
				RecvData += wxString::Format(" %02x ", this->m_recvBuff[idx]);
			}
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", RecvData.c_str());
		}

		if (m_intervalTime > 0){
			wxMilliSleep(m_intervalTime);
		}
	
	}// if (*this->m_running)
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "End To Send Read CMD");

		stopTick = PMBUSHelper::GetTickCountHAL();
		DWORD totalTime = stopTick - startTick;
		PSU_DEBUG_PRINT(MSG_ALERT, "Elapsed Time = %ld, Send %d CMDS, Average 1 Second Send %.2f CMDS", totalTime, totalSendTimes, ( (float)totalSendTimes / ((float)totalTime / 1000) ) );


		PSU_DEBUG_PRINT(MSG_DEBUG, "%s : Delete", __FUNCTIONW__);
		totalSendTimes = 0;
		delete this;
	}

	runningIndex++;
	if (runningIndex >= (this->m_setsToRun+1)){
		runningIndex %= (this->m_setsToRun + 1);
	}

	return 0;
}
