/**
 * @file PMBUSWriteTestTask.cpp
 */

#include "Task.h"

PMBUSWriteTestTask::PMBUSWriteTestTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSWriteCMD_t* pmbusWriteCMD, int setsToRun, bool* outputLog, int intervalTime){
	this->m_id = task_ID_PMBUSWriteTestTask;
	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusWriteCMDArray = pmbusWriteCMD;
	this->m_setsToRun = setsToRun;
	this->m_outputLog = outputLog;
	this->m_intervalTime = intervalTime;

	this->m_running = true;
	this->runningIndex = 0;

	this->startTick = PMBUSHelper::GetTickCountHAL();
}

PMBUSWriteTestTask::~PMBUSWriteTestTask(void){

}

void PMBUSWriteTestTask::Draw(void){

}

int PMBUSWriteTestTask::ProductWriteCMDBuffer(PMBUSWriteCMD_t* pmBusWriteCMD, unsigned char* sendBuffer, unsigned int* currentIO){
	unsigned int pec_start_index = 0;

	if (pmBusWriteCMD == NULL || sendBuffer == NULL){
		PSU_DEBUG_PRINT(MSG_ALERT, "pmBusWriteCMD or Send Buffer = NULL");
		return 0;
	}

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		sendBuffer[0] = 0x41;
		sendBuffer[1] = 0x54;
		sendBuffer[2] = pmBusWriteCMD->m_slaveAddr; // Slave Address
		sendBuffer[3] = pmBusWriteCMD->m_cmd; // CMD
		// Data start from index 4
		for (unsigned int idx = 0; idx < pmBusWriteCMD->m_numOfSendBytes; idx++){
			sendBuffer[4 + idx] = pmBusWriteCMD->m_sendBytes[idx];
			pec_start_index = (4 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		sendBuffer[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, sendBuffer + 2, 2 + pmBusWriteCMD->m_numOfSendBytes);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", sendBuffer[pec_start_index]);

		// Fill Last 2 
		pec_start_index++;
		sendBuffer[pec_start_index++] = 0x0D;
		sendBuffer[pec_start_index++] = 0x0A;

		break;

	case IOACCESS_HID:

		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		sendBuffer[0] = 0x05;

		sendBuffer[2] = 0x41;
		sendBuffer[3] = 0x54;
		sendBuffer[4] = pmBusWriteCMD->m_slaveAddr; // Slave Address
		sendBuffer[5] = pmBusWriteCMD->m_cmd; // CMD
		// Data start from index 6
		for (unsigned int idx = 0; idx < pmBusWriteCMD->m_numOfSendBytes; idx++){
			sendBuffer[6 + idx] = pmBusWriteCMD->m_sendBytes[idx];
			pec_start_index = (6 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		sendBuffer[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, sendBuffer + 4, 2 + pmBusWriteCMD->m_numOfSendBytes);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", sendBuffer[pec_start_index]);

		// Fill Last 2 
		pec_start_index++;
		sendBuffer[pec_start_index++] = 0x0D;
		sendBuffer[pec_start_index++] = 0x0A;

		// Fill Length
		sendBuffer[1] = pec_start_index - 2;

		break;

	case IOACCESS_PICKIT:

		// 0x03 [0x06] 0x81 0x84 [0x05] [0xB6] [0xEC] [0x00] [0x08] [0xE0] 0x82 0x1f 0x77
		sendBuffer[0] = 0x00;
		sendBuffer[1] = 0x03;

		sendBuffer[3] = 0x81;
		sendBuffer[4] = 0x84;
		sendBuffer[5] = pmBusWriteCMD->m_numOfSendBytes + 3;
		sendBuffer[6] = pmBusWriteCMD->m_slaveAddr; // Slave Address
		sendBuffer[7] = pmBusWriteCMD->m_cmd; // CMD

		// Data start from index 8
		for (unsigned int idx = 0; idx < pmBusWriteCMD->m_numOfSendBytes; idx++){
			sendBuffer[8 + idx] = pmBusWriteCMD->m_sendBytes[idx];
			pec_start_index = (8 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		sendBuffer[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, sendBuffer + 6, 2 + pmBusWriteCMD->m_numOfSendBytes);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", sendBuffer[pec_start_index]);

		// Fill Last 3
		pec_start_index++;
		sendBuffer[pec_start_index++] = 0x82;
		sendBuffer[pec_start_index++] = 0x1f;
		sendBuffer[pec_start_index++] = 0x77;

		// Fill Total Length
		sendBuffer[2] = pec_start_index - 3;

		break;

	case IOACCESS_TOTALPHASE:

		sendBuffer[0] = pmBusWriteCMD->m_numOfSendBytes; // Write Bytes
		sendBuffer[1] = 0; // Read Bytes
		sendBuffer[2] = pmBusWriteCMD->m_slaveAddr;
		sendBuffer[3] = pmBusWriteCMD->m_cmd;

		// Data start from index 4
		for (unsigned int idx = 0; idx < pmBusWriteCMD->m_numOfSendBytes; idx++){
			sendBuffer[4 + idx] = pmBusWriteCMD->m_sendBytes[idx];
			pec_start_index = (4 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		sendBuffer[pec_start_index] = PMBusSlave_Crc8MakeBitwise(0, 7, sendBuffer + 2, 2 + pmBusWriteCMD->m_numOfSendBytes);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", sendBuffer[pec_start_index]);

		pec_start_index++;

		// Update Write Bytes For Write CMD
		sendBuffer[0] = pec_start_index - 3;

		break;

	case IOACCESS_TRC2_I2C_ADAPTER:

		sendBuffer[0] = 0x00;
		sendBuffer[1] = 0x02;// Group
		sendBuffer[2] = 0x01;// Interface
		sendBuffer[3] = 0x51;// Action : Write
		sendBuffer[4] = pmBusWriteCMD->m_slaveAddr;// Data Package Start, Slave Address
		sendBuffer[5] = 1+1+pmBusWriteCMD->m_numOfSendBytes;//    Write Length 1+1+ :  command + pec
		sendBuffer[6] = 0x00;//    Read Length
		sendBuffer[7] = pmBusWriteCMD->m_cmd;// Write Data Start

		// Data start from index 8
		for (unsigned int idx = 0; idx < pmBusWriteCMD->m_numOfSendBytes; idx++){
			sendBuffer[8 + idx] = pmBusWriteCMD->m_sendBytes[idx];
			pec_start_index = (8 + idx);
		}

		// Compute PEC
		pec_start_index += 1;
		sendBuffer[pec_start_index] = PMBusSlave_Crc8MakeBitwiseDiscont(&pmBusWriteCMD->m_slaveAddr, 1, sendBuffer+7, 1+pmBusWriteCMD->m_numOfSendBytes);
				//PMBusSlave_Crc8MakeBitwise(0, 7, sendBuffer + 4, 2 + pmBusWriteCMD->m_numOfSendBytes);
		PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", sendBuffer[pec_start_index]);

		pec_start_index++;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return pec_start_index;
}

#define WRITE_CMD_BYTES_TO_READ  6
int PMBUSWriteTestTask::Main(double elapsedTime){

	int sendResult;
	int retry;
	bool sendRetryStillFailed = false;
	int recvLength = 0;
	int bytesToRead;
	static int totalSendTimes = 0;

	int sendDataLength = 0;
	sendDataLength = ProductWriteCMDBuffer(&this->m_pmbusWriteCMDArray[runningIndex], this->m_sendBuff, this->m_CurrentIO);
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
		bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_CurrentIO, WRITE_CMD_BYTES_TO_READ);//(*this->m_CurrentIO == IOACCESS_SERIALPORT) ? WRITE_CMD_BYTES_TO_READ : WRITE_CMD_BYTES_TO_READ + 1;
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
		PSU_DEBUG_PRINT(MSG_ALERT, "End To Send Write CMD");

		stopTick = PMBUSHelper::GetTickCountHAL();
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
