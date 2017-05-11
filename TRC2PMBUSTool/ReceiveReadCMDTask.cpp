/**
 * @brief ReceiveReadCMDTask.cpp
 */

#include "Task.h"


ReceiveReadCMDTask::ReceiveReadCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, pmbusReadCMD_t pmbusReadCommand){
	this->m_id = task_ID_ReceiveReadCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_pmbusReadCommand = pmbusReadCommand;
}

ReceiveReadCMDTask::~ReceiveReadCMDTask(void){
	// De-Constructor
}


void ReceiveReadCMDTask::Draw(void){
	// No need to implement
}


int ReceiveReadCMDTask::Main(double elapsedTime){

	// Start Receive
	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data From I/O, Bytes To Read = %d", this->m_pmbusReadCommand.m_numOfReadBytes);

	// Read Data From IO
	this->m_recvBuff.m_length = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadData(this->m_recvBuff.m_recvBuff, this->m_pmbusReadCommand.m_numOfReadBytes + BASE_RESPONSE_DATA_LENGTH);

	if (this->m_recvBuff.m_length == 0){

		switch (*this->m_CurrentIO){

		case IOACCESS_SERIALPORT:
		case IOACCESS_HID:
			PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data Failed, Receive Data Length = %d", this->m_recvBuff.m_length);
			break;

		case IOACCESS_TOTALPHASE:
			if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
				PSU_DEBUG_PRINT(MSG_ERROR, "I2C WriteRead Failed, Error=%d", PMBUSHelper::getTotalPhaseWriteReadLastError());
			}

			break;

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "%s: Something Error Occurs", __FUNCTIONW__);
			break;
		}

		delete this;
		return -1;
	}

	wxString str("Receive Data :");
	for (unsigned int idx = 0; idx < this->m_recvBuff.m_length; idx++){
		str += wxString::Format(" %02x ", this->m_recvBuff.m_recvBuff[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());


	// Handle Recived Data
	unsigned char DataBuffer[64];
	memset(DataBuffer, 0, 64);
	PMBUSHelper::ProductDataBuffer(DataBuffer, this->m_CurrentIO, this->m_recvBuff.m_recvBuff, this->m_pmbusReadCommand.m_numOfReadBytes);

	PMBUSHelper::ParseCustomizedReadCMDRecvData(this->m_pmbusReadCommand.m_cmd, DataBuffer, this->m_pmbusReadCommand.m_numOfReadBytes);

	delete this;

	return 0;
}