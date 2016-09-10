/**
 * @file SendUSBAdaptorParameterTask.cpp
 */

#include "Task.h"

/**
* @file SendUSBAdaptorConfigTask.cpp
*/

#include "Task.h"

SendUSBAdaptorParameterTask::SendUSBAdaptorParameterTask(
	IOACCESS*      ioaccess,
	unsigned int*  currentUseIO,
	unsigned char  digitalOutput,
	unsigned short pwmFreq,
	unsigned short pwmDuty
	)
{

	this->m_id = task_ID_SendUSBAdaptorParameterTask;

	this->m_IOAccess = ioaccess;
	this->m_currentUseIO = currentUseIO;

	this->m_digitalOutput = digitalOutput;
	this->m_pwmFreq = pwmFreq;
	this->m_pwmDuty = pwmDuty;

}


SendUSBAdaptorParameterTask::~SendUSBAdaptorParameterTask(void){

}


#define AUTO_REPORT_MASK    0x01
#define RESERVED_MASK       0x02
#define SMBUS_MASK          0x04
#define PWM_ENABLE_MASK     0x20
#define CLOCK_IN_DI6_MASK   0x40
#define CLOCK_IN_DI7_MASK   0x80

unsigned int SendUSBAdaptorParameterTask::ProductSendBuffer(unsigned char *buffer){

	unsigned int active_index = 0;

	// Fill Data
	buffer[active_index++] = 0x0f; //  [0]
	buffer[active_index++] = 0x0c; //  [1]
	buffer[active_index++] = 0x41; //  [2]
	buffer[active_index++] = 0x43; //  [3]
	buffer[active_index++] = 0x01; //  [4]

	// Digital Output
	buffer[active_index++] = this->m_digitalOutput; //  [5]

    // PWM Frequence
	buffer[active_index++] = this->m_pwmFreq & (0x00ff);           //  [6]
	buffer[active_index++] = ((this->m_pwmFreq  & (0xff00)) >> 8); //  [7]

	// PWM Duty
	buffer[active_index++] = this->m_pwmDuty & (0x00ff);           //  [8]
	buffer[active_index++] = ((this->m_pwmDuty  & (0xff00)) >> 8); //  [9]


	// Unused 2 Bytes
	buffer[active_index++] = 0;    //  [10]
	buffer[active_index++] = 0;    //  [11]

	// End Character
	buffer[active_index++] = 0x0d; //  [12]
	buffer[active_index++] = 0x0a; //  [13]

	// Debug Output
	wxString output;

	output += wxString::Format("Send Buffer : length=%d,", active_index);
	for (unsigned int idx = 0; idx < active_index; idx++){
		output += wxString::Format(" %02x ", buffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

	return active_index;

}


void SendUSBAdaptorParameterTask::Draw(void){

}

#define USB_ADAPTOR_CONFIG_TO_READ  7
int SendUSBAdaptorParameterTask::Main(double elapsedTime){

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


#if 0
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

	
	new(TP_ReceiveUSBAdaptorSettingCMDTask) ReceiveUSBAdaptorSettingCMDTask(
		this->m_IOAccess,
		this->m_currentUseIO
	);
	

	delete this;

	return 0;
}
