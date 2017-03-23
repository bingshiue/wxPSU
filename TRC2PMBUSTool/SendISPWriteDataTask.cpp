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
	wxString pec_output("");
	unsigned int active_index = 0;
	unsigned long start_address;
	unsigned long address;
	unsigned short data;
	unsigned char pec_buffer[64];// for compute pec with out additional '0x0d' byte
	unsigned int pec_active_index = 0;

	switch (*this->m_CurrentIO){
	/* Serial Port */
	case IOACCESS_SERIALPORT:

		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
		buffer[active_index++] = PMBUSHelper::getFWUploadCMD(); // FW Upload Command

		pec_buffer[pec_active_index++] = 0x41;
		pec_buffer[pec_active_index++] = 0x54;
		pec_buffer[pec_active_index++] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
		pec_buffer[pec_active_index++] = PMBUSHelper::getFWUploadCMD(); // FW Upload Command

		/* Address */
		this->m_tiHexFileStat->startAddress(&start_address);
		address = this->m_tiHexFileStat->currentAddress() - start_address;

		buffer[active_index++] = (unsigned char)((address & 0xff000000) >> 24);
		pec_buffer[pec_active_index++] = (unsigned char)((address & 0xff000000) >> 24);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = (unsigned char)((address & 0x00ff0000) >> 16);
		pec_buffer[pec_active_index++] = (unsigned char)((address & 0x00ff0000) >> 16);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = (unsigned char)((address & 0x0000ff00) >> 8);
		pec_buffer[pec_active_index++] = (unsigned char)((address & 0x0000ff00) >> 8);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = (unsigned char)(address & 0x000000ff);
		pec_buffer[pec_active_index++] = (unsigned char)(address & 0x000000ff);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		/* Data  16 bytes (8 short datas) */
		data = 0x0000;

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif
		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif
		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif
		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif
		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif
		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		if (!this->m_tiHexFileStat->endOfData()){
			++(*this->m_tiHexFileStat);
		}

		// CheckSum Byte (PEC)
		//buffer[active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 22 + ((active_index - 1) - 23));// PMBUSHelper::ComputeISPDataCheckSum(buffer, 8, 23);
		buffer[active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, pec_buffer + 2, 22);
		active_index++;

		pec_buffer[pec_active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, pec_buffer + 2, 22);
		pec_active_index++;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		// Last 2 Bytes
		buffer[active_index++] = 0x0d;
		buffer[active_index++] = 0x0a;

		pec_buffer[pec_active_index++] = 0x0d;
		pec_buffer[pec_active_index++] = 0x0a;


		output += wxString::Format("Send Buffer : length=%d,", active_index);
		for (unsigned int idx = 0; idx < active_index; idx++){
			output += wxString::Format(" %02x ", buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

		pec_output += wxString::Format("Orig Buffer : length=%d,", pec_active_index);
		for (unsigned int idx = 0; idx < pec_active_index; idx++){
			output += wxString::Format(" %02x ", pec_buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", pec_output.c_str());

		break;

	/* HID */
	case IOACCESS_HID:

		buffer[0] = 0x05;
		//buffer[1] = 27;
		active_index = 2;
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
		buffer[active_index++] = PMBUSHelper::getFWUploadCMD(); // FW Upload Command

		pec_buffer[0] = 0x05;
		//pec_buffer[1] = 27;
		pec_active_index = 2;
		pec_buffer[pec_active_index++] = 0x41;
		pec_buffer[pec_active_index++] = 0x54;
		pec_buffer[pec_active_index++] = PMBUSHelper::GetSlaveAddress(); // Slave Adress
		pec_buffer[pec_active_index++] = PMBUSHelper::getFWUploadCMD(); // FW Upload Command


		/* Address */
		this->m_tiHexFileStat->startAddress(&start_address);
		address = this->m_tiHexFileStat->currentAddress() - start_address;

		buffer[active_index++] = (unsigned char)((address & 0xff000000) >> 24);
		pec_buffer[pec_active_index++] = (unsigned char)((address & 0xff000000) >> 24);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = (unsigned char)((address & 0x00ff0000) >> 16);
		pec_buffer[pec_active_index++] = (unsigned char)((address & 0x00ff0000) >> 16);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = (unsigned char)((address & 0x0000ff00) >> 8);
		pec_buffer[pec_active_index++] = (unsigned char)((address & 0x0000ff00) >> 8);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = (unsigned char)(address & 0x000000ff);
		pec_buffer[pec_active_index++] = (unsigned char)(address & 0x000000ff);

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		/* Data  16 bytes (8 short datas) */
		data = 0x0000;

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		++(*this->m_tiHexFileStat);

		this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());
		buffer[active_index++] = (data & 0xff00) >> 8;
		pec_buffer[pec_active_index++] = (data & 0xff00) >> 8;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		buffer[active_index++] = data & 0x00ff;
		pec_buffer[pec_active_index++] = data & 0x00ff;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		if (!this->m_tiHexFileStat->endOfData()){
			++(*this->m_tiHexFileStat);
		}

		// CheckSum Byte (PEC)
		buffer[active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, pec_buffer + 4, 22);//PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 22+((active_index-1)-25));
		active_index++;

		pec_buffer[pec_active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, pec_buffer + 4, 22);// +((active_index - 1) - 25));
		pec_active_index++;

#ifdef ISP_HANDLE_0D
		if (buffer[active_index - 1] == 0x0d){
			buffer[active_index++] = 0x0d;
		}
#endif

		// Last 2 Bytes
		buffer[active_index++] = 0x0d;
		buffer[active_index++] = 0x0a;

		pec_buffer[pec_active_index++] = 0x0d;
		pec_buffer[pec_active_index++] = 0x0a;

		// Fill Length Fields
		buffer[1] = (active_index - 2);

		pec_buffer[1] = (pec_active_index - 2);


		output += wxString::Format("Send Buffer : length=%d,", active_index);
		for (unsigned int idx = 0; idx < active_index; idx++){
			output += wxString::Format(" %02x ", buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

		pec_output += wxString::Format("Orig Buffer : length=%d,", pec_active_index);
		for (unsigned int idx = 0; idx < pec_active_index; idx++){
			pec_output += wxString::Format(" %02x ", pec_buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", pec_output.c_str());

		break;

	case IOACCESS_PICKIT:

		// 0x03 [0x0B] 0x81 0x84 [0x05] [0xB6] [0xEC] [0x00] [0x08] [0xE0] 0x82 0x1f 0x77
		buffer[active_index++] = 0x00;
		buffer[active_index++] = 0x03;
		buffer[active_index++] = 0x00; // Total Length, Detemine Later
		buffer[active_index++] = 0x81;
		buffer[active_index++] = 0x84;
		buffer[active_index++] = 20 + 3;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadCMD(); // FW Upload Command

		/* Address (4 Bytes) */
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

		// Compute PEC
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 6, 22);

		// Fill Last 3
		buffer[active_index++] = 0x82;
		buffer[active_index++] = 0x1f;
		buffer[active_index++] = 0x77;

		// Fill Total Length
		buffer[2] = active_index - 3;

		output += wxString::Format("Send Buffer : length=%d,", active_index);
		for (unsigned int idx = 0; idx < active_index; idx++){
			output += wxString::Format(" %02x ", buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

		break;

	case IOACCESS_TOTALPHASE:

		buffer[active_index++] = 1; // Write Bytes
		buffer[active_index++] = 0; // Read Bytes
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();
		buffer[active_index++] = PMBUSHelper::getFWUploadCMD(); // FW Upload Command

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
		//buffer[active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 22 + ((active_index - 1) - 23));// PMBUSHelper::ComputeISPDataCheckSum(buffer, 8, 23);
		buffer[active_index] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 22);
		active_index++;


		output += wxString::Format("Send Buffer : length=%d,", active_index);
		for (unsigned int idx = 0; idx < active_index; idx++){
			output += wxString::Format(" %02x ", buffer[idx]);
		}

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", output.c_str());

		// Update Write Bytes For Write CMD
		buffer[0] = active_index - 3;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;

}

int SendISPWriteDataTask::Main(double elapsedTime){

	int cnt = this->GetCount(task_ID_SendISPWriteDataTask);

	PSU_DEBUG_PRINT(MSG_DEBUG, "Count of Task = %d", cnt);

	PSU_DEBUG_PRINT(MSG_DEBUG, "Current Address = %08x", this->m_tiHexFileStat->currentAddress());

	unsigned short data = 0x0000;

	this->m_tiHexFileStat->getData(&data, this->m_tiHexFileStat->currentAddress());

	wxString str("Data : ");
	str += wxString::Format("%04x", data);
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", str.c_str());

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

	if (sendRetryStillFailed == true){
		PSU_DEBUG_PRINT(MSG_ERROR, "Send Write CMD Retry Send Still Failed, Give up send !");
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
