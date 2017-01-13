/**
 * @file SendUSBAdaptorUARTSettingTask.cpp
 */

#include "Task.h"

SendUSBAdaptorUARTSettingTask::SendUSBAdaptorUARTSettingTask(IOACCESS* ioaccess, unsigned int* currentUseIO, unsigned char UartPort, unsigned char BuadRate, unsigned char DataBits, unsigned char StopBits, unsigned char ParityCheck){
	this->m_id = task_ID_SendUSBAdaptorUARTSettingTask;

	this->m_IOAccess = ioaccess;
	this->m_currentUseIO = currentUseIO;

	this->m_uartPort = UartPort;
	this->m_buadRate = BuadRate;
	this->m_dataBits = DataBits;
	this->m_stopBits = StopBits;
	this->m_parityCheck = ParityCheck;

}


SendUSBAdaptorUARTSettingTask::~SendUSBAdaptorUARTSettingTask(void){

}

#define DATABITS_9_MASK 0x06
#define STOPBITS_2_MASK 0x01
#define PARITY_CHECK_E_MASK 0x02
#define PARITY_CHECK_O_MASK 0x04

unsigned int SendUSBAdaptorUARTSettingTask::ProductSendBuffer(unsigned char *buffer){

	unsigned int active_index = 0;

	// Fill Data
	buffer[active_index++] = 0x0f; //  [0]
	buffer[active_index++] = 0x07; //  [1]
	buffer[active_index++] = 0x41; //  [2]
	buffer[active_index++] = 0x43; //  [3]
	
	// UART Port
	unsigned char portCode[4] = {
		0x81,
		0x82,
		0x83,
		0x84
	};
	
	buffer[active_index++] = portCode[this->m_uartPort]; //  [4]

	// Buad Rate
	buffer[active_index++] = this->m_buadRate; //  [5]

	// Data Bits
	// Stop Bits
	// Parity Check
	
	unsigned int combined_setting_index = active_index; // [6]

	unsigned long dataBitsArray[2] = { 8, 9 };
	unsigned char dataBits = dataBitsArray[this->m_dataBits];


	typedef struct {
		char *m_label;
		unsigned long  m_value;
	} StopBitsArray;

	StopBitsArray stopBitsArray[2] = {
		{ "1", 0 },
		{ "2", 1 },
	};
	unsigned char stopBits = stopBitsArray[this->m_stopBits].m_value;

	typedef struct {
		char *m_label;
		unsigned long  m_value;
	} ParityCheckArray;

	ParityCheckArray parityCheckArray[3] = {
		{ "N", 0 },
		{ "E", 1 },
		{ "O", 2 },
	};
	unsigned char parityCheck = parityCheckArray[this->m_parityCheck].m_value;

	// Stop Bits
	if (stopBits == 1){
		buffer[combined_setting_index] |= STOPBITS_2_MASK;
	}


	// Check if Data is 9 ??
	if (dataBits == 9){
		buffer[combined_setting_index] |= DATABITS_9_MASK;
	}
	else{
		// dataBits == 8

		// Parity  Check
		if (parityCheck == 1){ // "E"
			buffer[combined_setting_index] |= PARITY_CHECK_E_MASK;
		}
		else if (parityCheck == 2){ // "O"
			buffer[combined_setting_index] |= PARITY_CHECK_O_MASK;
		}
	}
	
	++active_index;

	// End Character
	buffer[active_index++] = 0x0d; // [7]
	buffer[active_index++] = 0x0a; // [8]

	// Debug Output
	wxString output;

	output += wxString::Format("Send Buffer : length=%d,", active_index);
	for (unsigned int idx = 0; idx < active_index; idx++){
		output += wxString::Format(" %02x ", buffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

	return active_index;
}


void SendUSBAdaptorUARTSettingTask::Draw(void){

}

#define USB_ADAPTOR_UART_SETTING_BYTES_TO_READ  7
int SendUSBAdaptorUARTSettingTask::Main(double elapsedTime){

	unsigned char sendBuffer[64] = { 0 };
	unsigned char recvBuffer[64] = { 0 };


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

	// Receive
	int readBytes = this->m_IOAccess[IOACCESS_HID].m_DeviceReadData(recvBuffer, USB_ADAPTOR_UART_SETTING_BYTES_TO_READ);

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