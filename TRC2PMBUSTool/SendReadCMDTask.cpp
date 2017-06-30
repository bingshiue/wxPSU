/**
 * @brief SendReadCMDTask.cpp
 */

#include "Task.h"

SendReadCMDTask::SendReadCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, pmbusReadCMD_t pmbusReadCommand){
	this->m_id = task_ID_SendReadCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_pmbusReadCommand = pmbusReadCommand;
}


SendReadCMDTask::~SendReadCMDTask(void){
	// De-Constructor
}


void SendReadCMDTask::Draw(void){
	// No Need To implement
}

int SendReadCMDTask::ProductReadCMDBuffer(PMBUSReadCMD_t* pmBusReadCMD, unsigned char* sendBuffer, unsigned int* currentIO){
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

		buffer_len = 64;// For HID

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

		buffer_len = 64;// For HID

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
		sendBuffer[baseIndex++] = (PMBUSHelper::GetSlaveAddress() >> 1);// Data Package Start, Slave Address
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


int SendReadCMDTask::Main(double elapsedTime){

	// Print Meaasges
	wxString msg("Send Read Command ");
	msg += (wxString::Format("%x H", this->m_pmbusReadCommand.m_cmd).Upper());
	PSU_DEBUG_PRINT(MSG_ALERT, "%s", msg.c_str());

	// Prepare Send Data Buffer
	// Declare As Static For Avoid Stack Corrupt
	static unsigned int SendLength = 0;
	static unsigned char SendBuffer[64] = { 0 };

	SendLength = this->ProductReadCMDBuffer(&this->m_pmbusReadCommand, SendBuffer, this->m_CurrentIO);
	PSU_DEBUG_PRINT(MSG_DEBUG, "SendLength=%d", SendLength);

	wxString debugStr("Send Buffer :");
	for (unsigned idx = 0; idx < SendLength; idx++){
		debugStr += wxString::Format(" %02x ", SendBuffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", debugStr.c_str());

	// Start Send
	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(SendBuffer, SendLength);
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

	new(TP_ReceiveReadCMDTask) ReceiveReadCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_pmbusReadCommand);

	delete this;


	return 0;
}
