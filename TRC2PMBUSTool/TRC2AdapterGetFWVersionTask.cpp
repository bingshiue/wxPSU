/**
 * @file TRC2AdapterGetFWVersionTask.cpp
 */
#include "Task.h"

TRC2AdapterGetFWVersionTask::TRC2AdapterGetFWVersionTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler) {
	this->m_id = task_ID_TRC2AdapterGetFWVersionTask;
	this->m_elapsedTimer = 0.0f;

	this->m_evtHandler = evtHandler;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
}


TRC2AdapterGetFWVersionTask::~TRC2AdapterGetFWVersionTask(void) {

}


void TRC2AdapterGetFWVersionTask::Draw(void) {

}

#define RESPONSE_BYTES_TO_READ  6
#define MAX_GET_TRC2_FW_VERSION_RETRY_TIMES  3
int TRC2AdapterGetFWVersionTask::Main(double elapsedTime) {

	int sendDataLength = HID_SEND_DATA_SIZE;
	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;
	bool validateFailed = false;
	int recvLength = 0;
	int bytesToRead;
	unsigned char sendBuffer[64];
	unsigned char recvBuffer[64];

	unsigned short fw_ver = 0x0000;

	memset(sendBuffer, 0, (sizeof(sendBuffer) /sizeof(sendBuffer[0])));
	memset(recvBuffer, 0, (sizeof(recvBuffer) / sizeof(recvBuffer[0])));

	sendBuffer[0] = 0x00;
	sendBuffer[1] = 0x01;
	sendBuffer[2] = 0x01;

	// Send Write
	do {
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendDataExtra(sendBuffer, sendDataLength, NULL);
		if (sendResult <= 0) {
			PSU_DEBUG_PRINT(MSG_ALERT, "Try Get TRC2 Adapter FW Version Failed");
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
			// Retry
			retry++;
			if (retry >= MAX_GET_TRC2_FW_VERSION_RETRY_TIMES) {
				PSU_DEBUG_PRINT(MSG_ERROR, "Try Get TRC2 Adapter FW Version Still Failed, Retry Times = %d", retry);
				sendRetryStillFailed = true;
				break;
			}
			else {
				PSU_DEBUG_PRINT(MSG_ALERT, "Retry Get TRC2 Adapter FW Version");
				PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
			}

		}
		else {
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			sendRetryStillFailed = false;
		}

	} while (sendResult <= 0);

	if (sendRetryStillFailed == true) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Forgive To Get TRC2 Adapter FW Version");
		return -1;
	}

	wxMilliSleep(10);

	// Receive Response
	bytesToRead = 3 + RESPONSE_BYTES_TO_READ;
	recvLength = this->m_IOAccess[*this->m_CurrentIO].m_DeviceReadDataExtra(recvBuffer, bytesToRead, NULL);

	wxString str("Receive Data :");
	for (int idx = 0; idx < recvLength; idx++) {
		str += wxString::Format(" %02x ", recvBuffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());


	fw_ver = (recvBuffer[1] | (recvBuffer[2] << 8));

	PSU_DEBUG_PRINT(MSG_ALERT, "TRC2 Adapter FW Version : %d.%d%d(%04x)", (fw_ver >> 8), (fw_ver & 0x00f0) >> 4, fw_ver & 0x000f, fw_ver);

	new(TP_TRC2AdapterSetI2CBitRateTask) TRC2AdapterSetI2CBitRateTask(this->m_IOAccess, this->m_CurrentIO, this->m_evtHandler);


	// Delete Task
	delete this;

	return 0;
}