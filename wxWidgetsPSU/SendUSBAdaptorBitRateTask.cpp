/**
 * @file SendUSBAdaptorBitRateTask.cpp
 */

#include "Task.h"


SendUSBAdaptorBitRateTask::SendUSBAdaptorBitRateTask(IOACCESS* ioaccess, unsigned short i2cBitRate, unsigned short spiBitRate, unsigned short canBitRate, unsigned short m_i2cBusTimeOut){
	this->m_id = task_ID_SendUSBAdaptorBitRateTask;

	this->m_IOAccess = ioaccess;

	this->m_i2cBitRate = i2cBitRate;
	this->m_spiBitRate = spiBitRate;
	this->m_canBitRate = canBitRate;

	this->m_i2cBusTimeOut = m_i2cBusTimeOut;
}

SendUSBAdaptorBitRateTask::~SendUSBAdaptorBitRateTask(void){

}

#define AUTO_REPORT_MASK   0x01
#define RESERVED_BIT1_MASK 0x02
#define SMBUS_MASK         0x04
#define ENABLE_PWM_MASK    0x20
#define CLOCKIN_DI6_MASK   0x40
#define CLOCKIN_DI7_MASK   0x80

unsigned int SendUSBAdaptorBitRateTask::ProductSendBuffer(unsigned char *buffer){
	unsigned int active_index = 0;
	unsigned char chkbox_setting = 0x00;

	// Fill Data
	buffer[active_index++] = 0x0f; //  [0]
	buffer[active_index++] = 0x20; //  [1]
	buffer[active_index++] = 0x41; //  0
	buffer[active_index++] = 0x43; //  1
	buffer[active_index++] = 0x80; //  2
	
	/*** Index 3 ***/ 
	// Auto Report
	if (PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_previous_autoReport == Generic_Enable){
		chkbox_setting |= AUTO_REPORT_MASK;
	}

	// Reserved Bit 1
	chkbox_setting |= RESERVED_BIT1_MASK;

	// SMBUS
	if (PMBUSHelper::GetAppSettings()->m_usbAdaptorI2CSetting.m_smBus == Generic_Enable){
		chkbox_setting |= SMBUS_MASK;
	}
	
	// Enable PWM 
	if (PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_enablePWM == Generic_Enable){
		chkbox_setting |= ENABLE_PWM_MASK;
	}

	// Clock In DI 6
	if (PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_clockInDI6 == Generic_Enable){
		chkbox_setting |= CLOCKIN_DI6_MASK;
	}

	// Clock In DI 7
	if (PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_clockInDI7 == Generic_Enable){
		chkbox_setting |= CLOCKIN_DI7_MASK;
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "chkbox_setting = %2x", chkbox_setting);

	buffer[active_index++] = chkbox_setting; //  3
	/*** ***/

	buffer[active_index++] = 0xff; //  4
	buffer[active_index++] = 0x00; //  5
	buffer[active_index++] = 0x00; //  6
	buffer[active_index++] = 0x32; //  7
	buffer[active_index++] = 0x00; //  8
	buffer[active_index++] = 0x00; //  9
	buffer[active_index++] = 0x00; //  10
	buffer[active_index++] = 0x04; //  11
	buffer[active_index++] = 0x00; //  12
	buffer[active_index++] = 0x04; //  13
	buffer[active_index++] = 0x00; //  14
	buffer[active_index++] = 0x04; //  15

	buffer[active_index++] = 0x00; //  16
	buffer[active_index++] = 0x04; //  17
	buffer[active_index++] = 0x00; //  18

	// I2C Bit Rate
	buffer[active_index++] = this->m_i2cBitRate & (0x00ff); //  19
	buffer[active_index++] = ((this->m_i2cBitRate & (0xff00)) >> 8); //  20
	
	// SPI Bit Rate
	buffer[active_index++] = this->m_spiBitRate & (0x00ff); //  21
	buffer[active_index++] = ((this->m_spiBitRate & (0xff00)) >> 8); //  22

	// CAN Bit Rate
	buffer[active_index++] = this->m_canBitRate & (0x00ff); //  23
	buffer[active_index++] = ((this->m_canBitRate & (0xff00)) >> 8); //  24

	// I2C Bus Timeout
	buffer[active_index++] = this->m_i2cBusTimeOut & (0x00ff); //  25
	buffer[active_index++] = ((this->m_i2cBusTimeOut & (0xff00)) >> 8); //  26

	buffer[active_index++] = 0x00; //  27
	buffer[active_index++] = 0x00; //  28
	buffer[active_index++] = 0x00; //  29

	buffer[active_index++] = 0x0d; //  30
	buffer[active_index++] = 0x0a; //  31

	buffer[34] = 0xdf;
	buffer[35] = 0x18;

	wxString output;

	output += wxString::Format("Send Buffer : length=%d,", active_index);
	for (unsigned int idx = 0; idx < active_index; idx++){
		output += wxString::Format(" %02x ", buffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

	return active_index;
}

void SendUSBAdaptorBitRateTask::Draw(void){

}

#define USB_ADAPTOR_BITRATE_BYTES_TO_READ  7
int SendUSBAdaptorBitRateTask::Main(double elapsedTime){

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
	int readBytes = this->m_IOAccess[IOACCESS_HID].m_DeviceReadData(recvBuffer, USB_ADAPTOR_BITRATE_BYTES_TO_READ);

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
