/**
 * @file FindAvailableSlaveI2CDeviceTask.cpp
 */
#include "Task.h"

FindAvailableSlaveI2CDeviceTask::FindAvailableSlaveI2CDeviceTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler, unsigned char* availableSlaveDevices,bool* outputLog){

	this->m_id = task_ID_FindAvailableSlaveI2CDeviceTask;

	this->m_evtHandler = evtHandler;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_outputLog = outputLog;

	this->m_running = true;
	this->m_SlaveAddr = 0x00;
	this->m_pAvailableSlaveDevices = availableSlaveDevices;
	this->m_elapsedTimer = 0.0f;

}

FindAvailableSlaveI2CDeviceTask::~FindAvailableSlaveI2CDeviceTask(void){
	// De-Constructor
}


void FindAvailableSlaveI2CDeviceTask::Draw(void){
	// No need to implement
}

#define RESPONSE_BYTES_TO_READ  6
#define MAX_I2C_WRITE_BYTE_RETRY_TIMES  3
int FindAvailableSlaveI2CDeviceTask::Main(double elapsedTime){

	unsigned char sendBuffer[64];
	unsigned char recvBuffer[64];
	int sendResult;
	int retry;
	bool sendRetryStillFailed = false;
	bool validateFailed = false;
	int recvLength = 0;
	int bytesToRead;

	memset(sendBuffer, 0, sizeof(sendBuffer) / sizeof(sendBuffer[0]));

	for (int addr = 1; addr < 128; addr++){
		// Prepare Send Buffer
		int sendDataLength = 0;
		sendDataLength = PMBUSHelper::ProductI2CWriteSingleByteBuffer(addr*2, sendBuffer, this->m_CurrentIO);

		// Prepare Send Data
		wxString sendData("Send Data : ");
		//if (*this->m_outputLog == true){
		for (int idx = 0; idx < sendDataLength; idx++){
			sendData += wxString::Format(" %02x ", sendBuffer[idx]);
		}
		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sendData.c_str());

		// Decide Send Data Length
		switch (*this->m_CurrentIO){

		case IOACCESS_HID:
		case IOACCESS_TRC2_I2C_ADAPTER:
			sendDataLength = HID_SEND_DATA_SIZE;
			break;

		default:

			break;
		}

		retry = 0;

		// Send Write
		do{
			sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendDataExtra(sendBuffer, sendDataLength, NULL);
			if (sendResult <= 0){
				PSU_DEBUG_PRINT(MSG_ALERT, "Try Slave Address %02x Failed", (addr * 2));
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
				// Retry
				retry++;
				if (retry >= MAX_I2C_WRITE_BYTE_RETRY_TIMES){
					PSU_DEBUG_PRINT(MSG_ERROR, "Try Slave Address %02x Still Failed, Retry Times = %d", (addr * 2),retry);
					sendRetryStillFailed = true;
					break;
				}
				else{
					PSU_DEBUG_PRINT(MSG_ALERT, "Retry Slave Address %02x", (addr * 2));
					PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
				}

			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
				sendRetryStillFailed = false;
			}

		} while (sendResult <= 0);

		if (sendRetryStillFailed == true){
			PSU_DEBUG_PRINT(MSG_ERROR, "Forgive To Try Slave Address %02x", (addr * 2));

			this->m_pAvailableSlaveDevices[addr] = 0;// Device Do Not Exist
			continue;

			// Emit Write Interrupt Event
			//wxThreadEvent* e2pRomWriteIntEvt;
			//e2pRomWriteIntEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT);
			//wxQueueEvent(this->m_evtHandler, e2pRomWriteIntEvt);

			//delete this;
			//return -1;
		}

		wxMilliSleep(10);

		// Receive Response
		bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_CurrentIO, RESPONSE_BYTES_TO_READ);//(*this->m_CurrentIO == IOACCESS_SERIALPORT) ? WRITE_CMD_BYTES_TO_READ : WRITE_CMD_BYTES_TO_READ + 1;
		recvLength = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadDataExtra(recvBuffer, bytesToRead, NULL);

		wxString str("Receive Data :");
		for (int idx = 0; idx < bytesToRead; idx++){
			str += wxString::Format(" %02x ", recvBuffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());

		if (recvLength == 0){

			switch (*this->m_CurrentIO){

			case IOACCESS_SERIALPORT:
			case IOACCESS_HID:
			case IOACCESS_PICKIT:
				PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data Failed, Receive Data Length = %d", recvLength);
				break;

			case IOACCESS_TOTALPHASE:
				if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
					PSU_DEBUG_PRINT(MSG_ERROR, "I2C WriteRead Failed, Error=%d", PMBUSHelper::getTotalPhaseWriteReadLastError());
				}
				else{
					// Verify Receive Data
					if (PMBUSHelper::IsResponseOK(this->m_CurrentIO, recvBuffer, 256) == PMBUSHelper::response_ok){
						PSU_DEBUG_PRINT(MSG_ALERT, "Receive Response From Slave Address [%02X] OK", (addr * 2));
						this->m_pAvailableSlaveDevices[addr] = 1;// Device Exist
					}
					else {
						PSU_DEBUG_PRINT(MSG_ERROR, "Receive Response From Slave Address [%02X] NG", (addr * 2));
						this->m_pAvailableSlaveDevices[addr] = 0;// Device Do Not Exist
					}
				}
				break;

			default:

				break;
			}

			//new(TP_SendWriteCMDTask) SendWriteCMDTask(this->m_IOAccess, this->m_CurrentIO, this->m_pmbusSendCommand);

			//delete this;
			//return -1;
		}
		else{

			// Verify Receive Data
			if (PMBUSHelper::IsResponseOK(this->m_CurrentIO, recvBuffer, 256) == PMBUSHelper::response_ok){
				PSU_DEBUG_PRINT(MSG_ALERT, "Receive Response From Slave Address [%02X] OK", (addr*2));
				this->m_pAvailableSlaveDevices[addr] = 1;// Device Exist
			}
			else {
				PSU_DEBUG_PRINT(MSG_ERROR, "Receive Response From Slave Address [%02X] NG", (addr*2));
				this->m_pAvailableSlaveDevices[addr] = 0;// Device Do Not Exist

				// Work-Around For PICKIT.
				if(*this->m_CurrentIO == IOACCESS_PICKIT){
					if( recvBuffer[4] != 0xFF){
						// Assume Device Exist
						this->m_pAvailableSlaveDevices[addr] = 1;// Just Assume
					}
				}
			}

		}

	}

	// Delete Task
	delete this;

	return 0;
}




