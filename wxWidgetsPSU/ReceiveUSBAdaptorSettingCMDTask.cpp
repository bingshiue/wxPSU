/**
 * @file ReceiveUSBAdaptorSettingCMDTask.cpp
 */
#include "Task.h"

ReceiveUSBAdaptorSettingCMDTask::ReceiveUSBAdaptorSettingCMDTask(IOACCESS* ioaccess, unsigned int* currentIO){
	this->m_id = task_ID_ReceiveUSBAdaptorSettingCMDTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
}

ReceiveUSBAdaptorSettingCMDTask::~ReceiveUSBAdaptorSettingCMDTask(void){

}

void ReceiveUSBAdaptorSettingCMDTask::Draw(void){

}

#define USB_ADAPTOR_CONFIG_TO_READ  7
int ReceiveUSBAdaptorSettingCMDTask::Main(double elapsedTime){

	unsigned char recvBuffer[64] = { 0 };

	// Receive
	int readBytes = this->m_IOAccess[IOACCESS_HID].m_DeviceReadData(recvBuffer, USB_ADAPTOR_CONFIG_TO_READ);

	if (readBytes == 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data Failed, Receive Data Length = %d", readBytes);
	}

	wxString str("Receive Data :");
	for (int idx = 0; idx < readBytes; idx++){
		str += wxString::Format(" %02x ", recvBuffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());

	delete this;

	return 0;
}