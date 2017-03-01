/**
 * @file E2PRomWriteDataTask.cpp
 */

#include "Task.h"

#define MAX_FRU_FILE_LOAD_LENGTH            256
#define MAX_FRU_FILE_WRITE_LENGTH           256
#define MAX_FRU_FILE_READ_LENGTH            256

#define MAX_RECV_BUFFER_LENGTH              256

#define WRITE_CMD_INTERVAL_TIME              10 // Millisecond
#define READ_CMD_INTERVAL_TIME               10 // Millisecond

#define MAX_E2PROM_WRITE_RETRY_TIMES          3
#define MAX_E2PROM_READ_RETRY_TIMES           3

E2PRomWriteDataTask::E2PRomWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler, unsigned char e2pRomSlaveAddr, unsigned char* fruBinaryContent, unsigned int fruBinaryLength, bool* outputLog, int writeIntervalTime, int readIntervalTime){
	this->m_id = task_ID_E2PRomWriteDataTask;

	this->m_evtHandler = evtHandler;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_e2pRomSlaveAddr = e2pRomSlaveAddr;
	this->m_fruBinaryContent = fruBinaryContent;
	this->m_fruBinaryLength = fruBinaryLength;
	this->m_outputLog = outputLog;
	this->m_writeIntervalTime = writeIntervalTime;
	this->m_readIntervalTime = readIntervalTime;
}


E2PRomWriteDataTask::~E2PRomWriteDataTask(void){

}


void E2PRomWriteDataTask::Draw(void){

}

#define WRITE_CMD_BYTES_TO_READ  6
int E2PRomWriteDataTask::Main(double elapsedTime){

	unsigned char sendBuffer[MAX_FRU_FILE_WRITE_LENGTH];
	unsigned char recvBuffer[MAX_RECV_BUFFER_LENGTH];
	int sendResult;
	int retry;
	bool sendRetryStillFailed = false;
	bool validateFailed = false;
	int recvLength = 0;
	int bytesToRead;

	memset(sendBuffer, 0, sizeof(sendBuffer) / sizeof(sendBuffer[0]));

	for (int offset = 0; offset < MAX_FRU_FILE_WRITE_LENGTH; offset++){
		// Prepare Send Buffer
		int sendDataLength = 0;
		sendDataLength = PMBUSHelper::ProductE2PRomWriteBuffer(this->m_e2pRomSlaveAddr, this->m_fruBinaryContent, offset, sendBuffer, this->m_CurrentIO);

		// 
		wxString sendData("Send Data : ");
		//if (*this->m_outputLog == true){
		for (int idx = 0; idx < sendDataLength; idx++){
			sendData += wxString::Format(" %02x ", sendBuffer[idx]);
		}
		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sendData.c_str());
		//}

		// Decide Send Data Length
		switch (*this->m_CurrentIO){

		case IOACCESS_HID:
			sendDataLength = HID_SEND_DATA_SIZE;
			break;

		default:

			break;
		}

		retry = 0;

		// Send Read CMD
		do{
			sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendDataExtra(sendBuffer, sendDataLength, NULL);
			if (sendResult <= 0){
				PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Failed, sendResult=%d", sendResult);
				// Retry 
				retry++;
				if (retry >= MAX_E2PROM_WRITE_RETRY_TIMES){
					PSU_DEBUG_PRINT(MSG_ERROR, "Still Send Failed, Retry Times = %d", retry);
					sendRetryStillFailed = true;
					break;
				}
				else{
					PSU_DEBUG_PRINT(MSG_ALERT, "Retry Write");
					PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
				}

			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			}

		} while (sendResult <= 0);

		if (sendRetryStillFailed == true){
			PSU_DEBUG_PRINT(MSG_ERROR, "Retry Send Still Failed, Exit Task");

			// Emit Write Interrupt Event
			wxThreadEvent* e2pRomWriteIntEvt;
			e2pRomWriteIntEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT);
			wxQueueEvent(this->m_evtHandler, e2pRomWriteIntEvt);

			delete this;
			return -1;
		}

		wxMilliSleep(this->m_writeIntervalTime);

		// Receive Response
		bytesToRead = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? WRITE_CMD_BYTES_TO_READ : WRITE_CMD_BYTES_TO_READ + 1;
		recvLength = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadDataExtra(recvBuffer, bytesToRead, NULL);

		//if (*this->m_outputLog == true){
		PSU_DEBUG_PRINT(MSG_DEBUG, "RecvLength = %d", recvLength);
		//}

		wxString RecvData("Recv Data : ");
		//if (*this->m_outputLog == true){
		for (int idx = 0; idx < recvLength; idx++){
			RecvData += wxString::Format(" %02x ", recvBuffer[idx]);
		}
		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", RecvData.c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "------------------------------------------------------------");
		//}

	}

	PSU_DEBUG_PRINT(MSG_ALERT, "Write Operaton Complete");
	PSU_DEBUG_PRINT(MSG_ALERT, "Read E2PROM For Verify Write Operaton");

	// Read Data From E2PRom For Validate 
	DumpE2PROM(recvBuffer, this->m_CurrentIO);

	// Print Content of E2PROM 
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------- E2PROM CONTENT -------------------");
	PMBUSHelper::PrintFRUContent(this->m_e2pRomContent, 256);

	// Compare Content of E2PROM with Original FRU Binary Data
	for (unsigned int idx = 0; idx < this->m_fruBinaryLength; idx++){
		if (this->m_fruBinaryContent[idx] != this->m_e2pRomContent[idx]){
			PSU_DEBUG_PRINT(MSG_ERROR, "Offset %d Data Not The Same As Original FRU BINARY FILE !", idx);
			PSU_DEBUG_PRINT(MSG_ERROR, "Original Data is %02x, Data On E2ROM is %02x", this->m_fruBinaryContent[idx], this->m_e2pRomContent[idx]);
			validateFailed = true;
		}
	}

	if (validateFailed == false){
		PSU_DEBUG_PRINT(MSG_ALERT, "Write And Validate E2PRom Success !");
	}
	else {
		PSU_DEBUG_PRINT(MSG_ERROR, "Write And Validate E2PRom Failed !");
	}

	// Emit Write End Event
	wxThreadEvent* e2pRomWriteEndEvt;
	e2pRomWriteEndEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_E2PROM_WRITE_END);
	wxQueueEvent(this->m_evtHandler, e2pRomWriteEndEvt);

	delete this;

	return 0;
}

int E2PRomWriteDataTask::DumpE2PROM(unsigned char* RecvBuffer, unsigned int* currentIO){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	int sendResult;
	int retry;
	int readRetry = 0;
	bool sendRetryStillFailed = false;
	int recvLength = 0;
	int bytesToRead;
	unsigned offset = 0;

	unsigned char sendBuffer[MAX_FRU_FILE_WRITE_LENGTH];
	unsigned char recvBuffer[MAX_RECV_BUFFER_LENGTH];


	// Read Data From E2PRom
	while (offset < MAX_FRU_FILE_READ_LENGTH){

		// Prepare Read Operation Send Data Buffer
		int sendDataLength = 0;
		sendDataLength = PMBUSHelper::ProductE2PRomReadBuffer(this->m_e2pRomSlaveAddr, offset, sendBuffer, this->m_CurrentIO);
		//if (*this->m_outputLog == true){
		PSU_DEBUG_PRINT(MSG_DEBUG, "SendBufferLen = %d", sendDataLength);
		//}


		wxString sendData("Send Data : ");
		//if (*this->m_outputLog == true){
		for (int idx = 0; idx < sendDataLength; idx++){
			sendData += wxString::Format(" %02x ", sendBuffer[idx]);
		}
		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sendData.c_str());
		//}

		// Decide Send Data Length
		switch (*this->m_CurrentIO){

		case IOACCESS_HID:
			sendDataLength = HID_SEND_DATA_SIZE;
			break;

		default:

			break;
		}

		retry = 0;

		// Send Read CMD
		do{
			sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendDataExtra(sendBuffer, sendDataLength, NULL);
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
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			}

		} while (sendResult <= 0);

		if (sendRetryStillFailed == true){
			PSU_DEBUG_PRINT(MSG_ERROR, "Retry Send Still Failed, Exit Task");
			return -1;
		}

		wxMilliSleep(this->m_readIntervalTime);

		// Receive Response
		bytesToRead = 1 + BASE_RESPONSE_DATA_LENGTH;
		recvLength = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadDataExtra(recvBuffer, bytesToRead, NULL);

		//if (*this->m_outputLog == true){
		PSU_DEBUG_PRINT(MSG_DEBUG, "RecvLength = %d", recvLength);
		//}

		wxString RecvData("Recv Data : ");
		//if (*this->m_outputLog == true){
		for (int idx = 0; idx < recvLength; idx++){
			RecvData += wxString::Format(" %02x ", recvBuffer[idx]);
		}
		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", RecvData.c_str());
		//}

		//if (m_intervalTime > 0){
		//wxMilliSleep(m_intervalTime);
		//}

		// Copy Data To E2PROM Content Buffer
		switch (*this->m_CurrentIO){

		case IOACCESS_SERIALPORT:// // Offset Of Content Data is 2
			if (recvBuffer[2] == 0x4e && recvBuffer[3] == 0x47){
				readRetry++;
				PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From E2PRom NG, Retry %d !", readRetry);
				if (readRetry < MAX_E2PROM_READ_RETRY_TIMES){
					continue;
				}
				else{
					PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data From E2PRom Retry Still Failed !");
					offset++;
					readRetry = 0;
					continue;
				}
			}

			this->m_e2pRomContent[offset] = recvBuffer[2];
			offset++;
			readRetry = 0;
			break;

		case IOACCESS_HID: // Offset Of Content Data is 6
			if (recvBuffer[5] == 0x4e && recvBuffer[6] == 0x47){
				readRetry++;
				PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From E2PRom NG, Retry %d !", readRetry);
				if (readRetry < MAX_E2PROM_READ_RETRY_TIMES){
					continue;
				}
				else{
					PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data From E2PRom Retry Still Failed !");
					offset++;
					readRetry = 0;
					continue;
				}
			}

			this->m_e2pRomContent[offset] = recvBuffer[6];
			offset++;
			readRetry = 0;
			break;

		case IOACCESS_TOTALPHASE:

			if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
				readRetry++;
				PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From E2PRom NG, Retry %d !", readRetry);
				if (readRetry < MAX_E2PROM_READ_RETRY_TIMES){
					continue;
				}
				else{
					PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data From E2PRom Retry Still Failed !");
					offset++;
					readRetry = 0;
					continue;
				}
			}

			this->m_e2pRomContent[offset] = recvBuffer[0];
			offset++;
			readRetry = 0;
			break;

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs !");
			break;

		}

	}

	return 0;
}
