/**
 * @file SendUSBAdaptorConfigTask.cpp
 */

#include "Task.h"

SendUSBAdaptorConfigTask::SendUSBAdaptorConfigTask(
	IOACCESS*      ioaccess,
	unsigned int*  currentUseIO,
	unsigned char  AutoReport,
	unsigned char  SMBus,
	unsigned char  PWMEnable,
	unsigned char  ClockInDI6,
	unsigned char  ClockInDI7,
	unsigned short I2CBusTimeout)
{

	this->m_id = task_ID_SendUSBAdaptorConfigTask;

	this->m_IOAccess = ioaccess;
	this->m_currentUseIO = currentUseIO;

	m_AutoReport = AutoReport;
	m_SMBus = SMBus;
	m_PWMEnable = PWMEnable;
	m_ClockInDI6 = ClockInDI6;
	m_ClockInDI7 = ClockInDI7;
	m_I2CBusTimeout = I2CBusTimeout;

}


SendUSBAdaptorConfigTask::~SendUSBAdaptorConfigTask(void){

}


#define AUTO_REPORT_MASK    0x01
#define RESERVED_MASK       0x02
#define SMBUS_MASK          0x04
#define PWM_ENABLE_MASK     0x20
#define CLOCK_IN_DI6_MASK   0x40
#define CLOCK_IN_DI7_MASK   0x80

unsigned int SendUSBAdaptorConfigTask::ProductSendBuffer(unsigned char *buffer){

	unsigned int active_index = 0;
	unsigned int config_index = 0;
	unsigned char config = 0x00;

	// Fill Data
	buffer[active_index++] = 0x0f; //  [0]
	buffer[active_index++] = 0x09; //  [1]
	buffer[active_index++] = 0x41; //  [2]
	buffer[active_index++] = 0x43; //  [3]
	buffer[active_index++] = 0x00; //  [4]

	/*** Config Byte ***/
	config_index = active_index;   //  [5]
	
	// Auto Report
	if (this->m_AutoReport == 1){
		buffer[config_index] |= AUTO_REPORT_MASK;
	}

	buffer[config_index] |= RESERVED_MASK;

	// SMBUS
	if (this->m_SMBus == 1) {
		buffer[config_index] |= SMBUS_MASK;
	}

	// PWM Enable
	if (this->m_PWMEnable == 1) {
		buffer[config_index] |= PWM_ENABLE_MASK;
	}

	// CLOCK IN DI6
	if (this->m_ClockInDI6 == 1) {
		buffer[config_index] |= CLOCK_IN_DI6_MASK;
	}

	// CLOCK IN DI7
	if (this->m_ClockInDI7 == 1) {
		buffer[config_index] |= CLOCK_IN_DI7_MASK;
	}

	++active_index;
	//

	buffer[active_index++] = 0x00; //  [6]

	buffer[active_index++] = this->m_I2CBusTimeout & (0x00ff);          //  [7]
	buffer[active_index++] = ((this->m_I2CBusTimeout & (0xff00)) >> 8); //  [8]

	// End Character
	buffer[active_index++] = 0x0d; //  [9]
	buffer[active_index++] = 0x0a; //  [10]

	// Debug Output
	wxString output;

	output += wxString::Format("Send Buffer : length=%d,", active_index);
	for (unsigned int idx = 0; idx < active_index; idx++){
		output += wxString::Format(" %02x ", buffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

	return active_index;

}


void SendUSBAdaptorConfigTask::Draw(void){

}

#define USB_ADAPTOR_CONFIG_TO_READ  7
int SendUSBAdaptorConfigTask::Main(double elapsedTime){

	unsigned char sendBuffer[64] = { 0 };
	unsigned char recvBuffer[64] = { 0 };

	this->m_elapsedTimer += elapsedTime;

	// Send 
	unsigned int sendDataLength = this->ProductSendBuffer(sendBuffer);

	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[IOACCESS_HID].m_DeviceSendData(sendBuffer, 64);
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
				PSU_DEBUG_PRINT(MSG_ERROR, "Send Write CMD Retry Times = %d", retry);
			}

		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Write CMD Success");
		}

	} while (sendResult <= 0);


#if 1
	wxMilliSleep(20);

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

#endif

	delete this;

	return 0;
}