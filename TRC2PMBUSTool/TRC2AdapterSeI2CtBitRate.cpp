/**
 * @file TRC2AdapterSetI2CBitRate.cpp
 */
#include "Task.h"

TRC2AdapterSetI2CBitRateTask::TRC2AdapterSetI2CBitRateTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler) {
	this->m_id = task_ID_TRC2AdapterSetI2CBitRateTask;
	this->m_elapsedTimer = 0.0f;

	this->m_evtHandler = evtHandler;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
}


TRC2AdapterSetI2CBitRateTask::~TRC2AdapterSetI2CBitRateTask(void) {

}


void TRC2AdapterSetI2CBitRateTask::Draw(void) {

}

#define RESPONSE_BYTES_TO_READ  6
#define MAX_GET_TRC2_SET_I2C_BITRATE_RETRY_TIMES  3
int TRC2AdapterSetI2CBitRateTask::Main(double elapsedTime) {

	int sendDataLength = HID_SEND_DATA_SIZE;
	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;
	bool validateFailed = false;
	int recvLength = 0;
	int bytesToRead;
	unsigned char sendBuffer[64];
	unsigned char recvBuffer[64];

	memset(sendBuffer, 0, (sizeof(sendBuffer) / sizeof(sendBuffer[0])));
	memset(recvBuffer, 0, (sizeof(recvBuffer) / sizeof(recvBuffer[0])));

	unsigned short i2c_bitrate_setting = PMBUSHelper::GetAppSettings()->m_trc2Adapter_I2C_Bitrate;
	PSU_DEBUG_PRINT(MSG_DEBUG, "i2c_bitrate_setting = %d", i2c_bitrate_setting);

	sendBuffer[0] = 0x00;
	sendBuffer[1] = 0x02;
	sendBuffer[2] = 0x01;
	sendBuffer[3] = 0x50;
	sendBuffer[4] = i2c_bitrate_setting & 0x00ff;
	sendBuffer[5] = ((i2c_bitrate_setting & 0xff00 ) >> 8);

	// Send Write
	do {
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendDataExtra(sendBuffer, sendDataLength, NULL);
		if (sendResult <= 0) {
			PSU_DEBUG_PRINT(MSG_ALERT, "Try Set TRC2 Adapter I2C BitRate Failed");
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
			// Retry
			retry++;
			if (retry >= MAX_GET_TRC2_SET_I2C_BITRATE_RETRY_TIMES) {
				PSU_DEBUG_PRINT(MSG_ERROR, "Try Set TRC2 Adapter I2C BitRate Still Failed, Retry Times = %d", retry);
				sendRetryStillFailed = true;
				break;
			}
			else {
				PSU_DEBUG_PRINT(MSG_ALERT, "Retry Set TRC2 Adapter I2C BitRate");
				PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
			}

		}
		else {
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			sendRetryStillFailed = false;
		}

	} while (sendResult <= 0);

	if (sendRetryStillFailed == true) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Forgive To Set TRC2 Adapter I2C BitRate");
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

	if (recvBuffer[1] == 0x4f && recvBuffer[2] == 0x4b) {
		PSU_DEBUG_PRINT(MSG_ALERT, "Set TRC2 Adapter I2C BitRate To %dK", i2c_bitrate_setting);
	}
	else {
		PSU_DEBUG_PRINT(MSG_ERROR, "Set TRC2 Adapter I2C BitRate Failed");
	}

	// Delete Task
	delete this;
 
	return 0;
}