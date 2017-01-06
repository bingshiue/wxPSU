/**
 * @file PMBUSBlockWRTestTask.cpp
 */

#include "Task.h"

PMBUSBlockWRTestTask::PMBUSBlockWRTestTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSBlockWRCMD_t* pmbusBlockWRCMD, int setsToRun, bool* outputLog){
	this->m_id = task_ID_PMBUSBlockWRTestTask;
	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusBlockWRCMDArray = pmbusBlockWRCMD;
	this->m_setsToRun = setsToRun;
	this->m_outputLog = outputLog;

	this->m_running = true;
	this->runningIndex = 0;

	this->startTick = GetTickCount();
}

PMBUSBlockWRTestTask::~PMBUSBlockWRTestTask(void){

}

void PMBUSBlockWRTestTask::Draw(void){

}

int PMBUSBlockWRTestTask::ProductBlockWRCMDBuffer(PMBUSBlockWRCMD_t* pmBusBlockWRCMD, unsigned char* sendBuffer, unsigned int* currentIO){
	// Read Byte/Word , Block Read
	unsigned int baseIndex = 0;
	int buffer_len = 0;

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_slaveAddr;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_cmd;

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_numOfWriteBytes;// Block Count 
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		for (unsigned int len = 0; len < pmBusBlockWRCMD->m_numOfWriteBytes; len++){
			sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_writeBytes[len];// Addtional Data [len]

			// Addidtional Data May Have Data 0x0d 
			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}
			//
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_slaveAddr | 0x01;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_numOfReadBytes;

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		buffer_len = baseIndex;


		break;

	case IOACCESS_HID:

		sendBuffer[baseIndex++] = 0x05;// Report ID is 0x05
		sendBuffer[baseIndex++] = 0x0c + (pmBusBlockWRCMD->m_numOfWriteBytes - 2);// Data Length
		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_slaveAddr;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_cmd; // Command

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_numOfWriteBytes;// Block Count 
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		for (unsigned int len = 0; len < pmBusBlockWRCMD->m_numOfWriteBytes; len++){
			sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_writeBytes[len];// Addtional Data [len]

			// Addidtional Data May Have Data 0x0d 
			if (sendBuffer[baseIndex - 1] == 0x0d){
				sendBuffer[baseIndex++] = 0x0d;
			}
			//

		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_slaveAddr | 0x01;
		sendBuffer[baseIndex++] = pmBusBlockWRCMD->m_numOfReadBytes; // Response Data Length

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		sendBuffer[1] = (baseIndex - 2);
		buffer_len = baseIndex;

		sendBuffer[baseIndex++] = 0x00;

		for (unsigned int target = baseIndex; target < 25; target++){
			sendBuffer[baseIndex++] = 0x00;
		}

		sendBuffer[25] = 0x01;
		sendBuffer[26] = pmBusBlockWRCMD->m_numOfReadBytes; // Response Data Length
		sendBuffer[27] = 0x00;
		sendBuffer[28] = 0x00;
		sendBuffer[29] = 0x02;
		sendBuffer[30] = pmBusBlockWRCMD->m_slaveAddr | 0x01;
		sendBuffer[31] = pmBusBlockWRCMD->m_numOfReadBytes; // Response Data Length

		sendBuffer[32] = 0x00;
		sendBuffer[33] = 0x01; //
		sendBuffer[34] = pmBusBlockWRCMD->m_slaveAddr | 0x01;
		sendBuffer[35] = 0x00;
		sendBuffer[36] = 0x00;
		sendBuffer[37] = 0x00;
		sendBuffer[38] = 0x00;
		sendBuffer[39] = 0x00;
		sendBuffer[40] = 0x00;
		sendBuffer[41] = 0x00;
		sendBuffer[42] = 0x00;
		sendBuffer[43] = 0x00;
		sendBuffer[44] = 0x00;
		sendBuffer[45] = 0x00;
		sendBuffer[46] = 0x00;
		sendBuffer[47] = 0x00;

		sendBuffer[48] = 0x00;
		sendBuffer[49] = 0x00;
		sendBuffer[50] = 0x00;
		sendBuffer[51] = 0x00;
		sendBuffer[52] = 0x00;
		sendBuffer[53] = 0x00;
		sendBuffer[54] = 0x00;
		sendBuffer[55] = 0x00;
		sendBuffer[56] = 0x00;
		sendBuffer[57] = 0x00;
		sendBuffer[58] = 0x00;
		sendBuffer[59] = 0x00;
		sendBuffer[60] = 0x00;
		sendBuffer[61] = 0x00;
		sendBuffer[62] = 0x00;
		sendBuffer[63] = 0x00;

		break;

	case IOACCESS_TOTALPHASE:

		sendBuffer[0] = pmBusBlockWRCMD->m_numOfWriteBytes; // Write Bytes
		sendBuffer[1] = pmBusBlockWRCMD->m_numOfReadBytes; // Read Bytes
		sendBuffer[2] = pmBusBlockWRCMD->m_slaveAddr;
		sendBuffer[3] = pmBusBlockWRCMD->m_cmd;
		sendBuffer[4] = sendBuffer[0];

		// Data start from index 5
		for (unsigned int idx = 0; idx < pmBusBlockWRCMD->m_numOfWriteBytes; idx++){
			sendBuffer[5 + idx] = pmBusBlockWRCMD->m_writeBytes[idx];
			baseIndex = (5 + idx);
		}

		baseIndex++;

		//Update Write Data Bytes Length For Block Wrire - Block Read Commands
		sendBuffer[0] = baseIndex - 3;

		buffer_len = baseIndex;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	return buffer_len;
}

int PMBUSBlockWRTestTask::Main(double elapsedTime){

	int sendResult;
	int retry;
	bool sendRetryStillFailed = false;
	int recvLength = 0;
	int bytesToRead;
	static int totalSendTimes = 0;

	int sendDataLength = 0;
	sendDataLength = ProductBlockWRCMDBuffer(&this->m_pmbusBlockWRCMDArray[runningIndex], this->m_sendBuff, this->m_CurrentIO);
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

	case IOACCESS_HID:
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
		bytesToRead = this->m_pmbusBlockWRCMDArray[runningIndex].m_numOfReadBytes + BASE_RESPONSE_DATA_LENGTH;
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

		//wxMilliSleep(1);

	}// if (*this->m_running)
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "End To Send Read CMD");

		stopTick = GetTickCount();
		DWORD totalTime = stopTick - startTick;
		PSU_DEBUG_PRINT(MSG_ALERT, "Elapsed Time = %ld, Send %d CMDS, Average 1 Second Send %.2f CMDS", totalTime, totalSendTimes, ((float)totalSendTimes / ((float)totalTime / 1000)));


		PSU_DEBUG_PRINT(MSG_DEBUG, "%s : Delete", __FUNCTIONW__);
		totalSendTimes = 0;
		delete this;
	}

	runningIndex++;
	if (runningIndex >= (this->m_setsToRun + 1)){
		runningIndex %= (this->m_setsToRun + 1);
	}

	return 0;
}