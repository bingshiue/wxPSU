/**
 * @file E2PRomReadDataTask.cpp
 */

#include "Task.h"

#define MAX_FRU_FILE_LOAD_LENGTH            256
#define MAX_FRU_FILE_WRITE_LENGTH           256
#define MAX_FRU_FILE_READ_LENGTH            256

#define MAX_RECV_BUFFER_LENGTH              256

#define MAX_E2PROM_WRITE_RETRY_TIMES          3
#define MAX_E2PROM_READ_RETRY_TIMES           3

E2PRomReadDataTask::E2PRomReadDataTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler, unsigned char e2pRomSlaveAddr, unsigned char* e2pRomContent, bool* outputLog, int readIntervalTime) {
	this->m_id = task_ID_E2PRomReadDataTask;

	this->m_evtHandler = evtHandler;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_e2pRomSlaveAddr = e2pRomSlaveAddr;
	this->m_targetE2pRomContent = e2pRomContent;
	this->m_outputLog = outputLog;
	this->m_readIntervalTime = readIntervalTime;
}


E2PRomReadDataTask::~E2PRomReadDataTask(void){

}


void E2PRomReadDataTask::Draw(void){

}

#define WRITE_CMD_BYTES_TO_READ  6
int E2PRomReadDataTask::Main(double elapsedTime){

	int result;

	unsigned char recvBuffer[MAX_RECV_BUFFER_LENGTH];

	// Read Data From E2PRom
	result = DumpE2PROM(recvBuffer, this->m_CurrentIO);

	// Copy Content of E2PRom Comtent To Target Buffer
	for (unsigned int idx = 0; idx<MAX_FRU_FILE_SIZE; idx++){
		this->m_targetE2pRomContent[idx] = this->m_e2pRomContent[idx];
	}

	// Print Content of E2PROM 
	//PSU_DEBUG_PRINT(MSG_ALERT, "----------------------- E2PROM CONTENT ----------------------");
	//PMBUSHelper::PrintFRUContent(this->m_e2pRomContent, 256);

	if (result < 0){

		// Emit Read Interrupt Event
		wxThreadEvent* e2pRomReadIntEvt;
		e2pRomReadIntEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_E2PROM_READ_INTERRUPT);
		wxQueueEvent(this->m_evtHandler, e2pRomReadIntEvt);

	}
	else{

		// Emit Read End Event
		wxThreadEvent* e2pRomReadEndEvt;
		e2pRomReadEndEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_E2PROM_READ_END);
		wxQueueEvent(this->m_evtHandler, e2pRomReadEndEvt);

	}

	delete this;

	return 0;
}

int E2PRomReadDataTask::DumpE2PROM(unsigned char* RecvBuffer, unsigned int* currentIO){
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
	while (offset < MAX_FRU_FILE_READ_LENGTH){//for (unsigned int offset = 0; offset < MAX_FRU_FILE_READ_LENGTH; offset++){

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

		case IOACCESS_PICKIT:
		case IOACCESS_TRC2_I2C_ADAPTER:
			sendDataLength = HID_SEND_DATA_SIZE + 1;
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
					PSU_DEBUG_PRINT(MSG_ALERT, "Retry Write");
					PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
				}

			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			}

		} while (sendResult <= 0);

		// Send Failure Occurs
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

		case IOACCESS_SERIALPORT:// Offset Of Content Data is 2
			if (recvBuffer[3] == 0x4e && recvBuffer[4] == 0x47){
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

		case IOACCESS_PICKIT:
			// 86 0a 80 10 [01] 10 ac 10 22 81 1c 77
			// 86 04 80 81 [1c]  77 for failed (May Casused By Wrong Slave Address)
			if (recvBuffer[4] == 0x1c && recvBuffer[5] == 0x77){
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

			this->m_e2pRomContent[offset] = recvBuffer[4];
			offset++;
			readRetry = 0;


			break;

		case IOACCESS_TOTALPHASE:

			if (PMBUSHelper::getTotalPhaseWriteReadLastError()!=0){
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

		case IOACCESS_TRC2_I2C_ADAPTER:

			if (recvLength == 0){
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
