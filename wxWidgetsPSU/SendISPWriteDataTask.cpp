/**
 * @brief SendISPWriteDataTask.cpp
 */

#include "Task.h"
#include "pec.h"

SendISPWriteDataTask::SendISPWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* tiHexFileStat, unsigned char* ispStatus){
	this->m_id = task_ID_SendISPWriteDataTask;

	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;

	this->m_tiHexFileStat = tiHexFileStat;
	this->m_ispStatus = ispStatus;
}

SendISPWriteDataTask::~SendISPWriteDataTask(void){

}

void SendISPWriteDataTask::Draw(void){

}

unsigned int SendISPWriteDataTask::ProductSendBuffer(unsigned char *buffer){

	wxString output("");
	unsigned int active_index = 0;
	unsigned long start_address;
	unsigned long address;
	unsigned short data;

	switch (*this->m_CurrentIO){
	/* Serial Port */
	case IOACCESS_SERIALPORT:

		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
		buffer[active_index++] = 0xf1; // Command
		/* Address */
		this->m_tiHexFileStat->startAddress(&start_address);
		address = this->m_tiHexFileStat->currentAddress() - start_address;

		buffer[active_index++] = (unsigned char)((address & 0xff000000) >> 24);
		buffer[active_index++] = (unsigned char)((address & 0x00ff0000) >> 16);
		buffer[active_index++] = (unsigned char)((address & 0x0000ff00) >> 8);
		buffer[active_index++] = (unsigned char)(address & 0x000000ff);

		/* Data  16 bytes (8 short datas) */
		data = 0x0000;

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		if (!this->m_tiHexFileStat->endOfData()){
			++(*this->m_tiHexFileStat);
		}

		// CheckSum Byte (PEC)
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 22);// PMBUSHelper::ComputeISPDataCheckSum(buffer, 8, 23);

		// Last 2 Bytes
		buffer[active_index++] = 0x0d;
		buffer[active_index++] = 0x0a;


		output += wxString::Format("length=%d,", active_index);
		for (unsigned int idx = 0; idx < active_index; idx++){
			output += wxString::Format(" %02x ", buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_ALERT, "%s", output.c_str());

		break;

	/* HID */
	case IOACCESS_HID:

		buffer[0] = 0x05;
		//buffer[1] = 27;
		active_index = 2;
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
		buffer[active_index++] = 0xf1; // Command
		/* Address */
		this->m_tiHexFileStat->startAddress(&start_address);
		address = this->m_tiHexFileStat->currentAddress() - start_address;

		buffer[active_index++] = (unsigned char)((address & 0xff000000) >> 24);
		buffer[active_index++] = (unsigned char)((address & 0x00ff0000) >> 16);
		buffer[active_index++] = (unsigned char)((address & 0x0000ff00) >> 8);
		buffer[active_index++] = (unsigned char)(address & 0x000000ff);

		/* Data  16 bytes (8 short datas) */
		data = 0x0000;

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		buffer[active_index++] = data & 0x00ff;

		if (!this->m_tiHexFileStat->endOfData()){
			++(*this->m_tiHexFileStat);
		}

		// CheckSum Byte (PEC)
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 22);

		// Last 2 Bytes
		buffer[active_index++] = 0x0d;
		buffer[active_index++] = 0x0a;

		// Fill Length Fields
		buffer[1] = active_index;


		output += wxString::Format("length=%d,", active_index);
		for (unsigned int idx = 0; idx < active_index; idx++){
			output += wxString::Format(" %02x ", buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_ALERT, "%s", output.c_str());

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return active_index;

#if 0
	buffer[0] = 0x41;
	buffer[1] = 0x54;
	buffer[2] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
	buffer[3] = 0xf1; // Command
	/* Address */
	unsigned long start_address;
	this->m_tiHexFileStat->startAddress(&start_address);
	unsigned long address = this->m_tiHexFileStat->currentAddress() - start_address;

	buffer[4] = (unsigned char)((address & 0xff000000) >> 24);
	buffer[5] = (unsigned char)((address & 0x00ff0000) >> 16);
	buffer[6] = (unsigned char)((address & 0x0000ff00) >> 8);
	buffer[7] = (unsigned char)(address & 0x000000ff);

	/* Data  16 bytes (8 short datas) */
	unsigned short data = 0x0000;

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[8] = (data & 0xff00) >> 8;
	buffer[9] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[10] = (data & 0xff00) >> 8;
	buffer[11] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[12] = (data & 0xff00) >> 8;
	buffer[13] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[14] = (data & 0xff00) >> 8;
	buffer[15] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[16] = (data & 0xff00) >> 8;
	buffer[17] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[18] = (data & 0xff00) >> 8;
	buffer[19] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[20] = (data & 0xff00) >> 8;
	buffer[21] = data & 0x00ff;

	++(*this->m_tiHexFileStat);

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
	buffer[22] = (data & 0xff00) >> 8;
	buffer[23] = data & 0x00ff;

	if (!this->m_tiHexFileStat->endOfData()){
		++(*this->m_tiHexFileStat);
	}

	// CheckSum Byte (PEC)
	buffer[24] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 22);// PMBUSHelper::ComputeISPDataCheckSum(buffer, 8, 23);

	// Last 2 Bytes
	buffer[25] = 0x0d;
	buffer[26] = 0x0a;

	wxString output("");

	for (unsigned int idx = 0; idx < 27; idx++){
		output += wxString::Format(" %02x ", buffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", output.c_str());
#endif
}

int SendISPWriteDataTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPWriteDataTask);
	int ret;

	PSU_DEBUG_PRINT(MSG_ALERT, "Count of Task = %d", cnt);

	PSU_DEBUG_PRINT(MSG_ALERT, "Current Address = %08x", this->m_tiHexFileStat->currentAddress());

	unsigned short data = 0x0000;

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());

	wxString str("Data : ");
	str += wxString::Format("%04x", data);
	PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());

	/*----------------------------------------------*/
	// Product Send Buffer
	unsigned int sendDataLength = this->ProductSendBuffer(this->m_sendBuff);
	/*----------------------------------------------*/

	int sendResult;
	int retry = 0;
	bool sendRetryStillFailed = false;

	do {
		// Send Data
		sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_sendBuff, (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64);
		if (sendResult <= 0){
			PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Write CMD Failed, sendResult=%d", sendResult);
			// Retry 
			retry++;
			if (retry >= 3){
				PSU_DEBUG_PRINT(MSG_ALERT, "Still Send Write CMD Failed, Retry Times = %d", retry);
				sendRetryStillFailed = true;
				break;
			}
			else{
				PSU_DEBUG_PRINT(MSG_ALERT, "Send Write CMD Retry Times = %d", retry);
			}

		}
		else{
			PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Write CMD Success");
		}

	} while (sendResult <= 0);

	if (sendRetryStillFailed == true){
		PSU_DEBUG_PRINT(MSG_ALERT, "Send Write CMD Retry Send Still Failed, Forgive to send !");
		*this->m_ispStatus = ISP_Status_SendDataFailed;
		delete this;
		return -1;
	}

	if (*this->m_ispStatus == ISP_Status_InProgress){
		new(TP_ReceiveISPWriteDataTask) ReceiveISPWriteDataTask(this->m_IOAccess, this->m_CurrentIO, this->m_tiHexFileStat, this->m_ispStatus);
	}

	delete this;

	return 0;
}
