/**
* @file SerialPortSendThread.cpp
*/

#include "IOPortSendCMDThread.h"

IOPortSendCMDThread::IOPortSendCMDThread(wxSemaphore* semaphore){
	this->m_rxTxSemaphore = semaphore;
}

IOPortSendCMDThread::IOPortSendCMDThread(
	IOACCESS*    ioaccess,
	unsigned int* currentIO,
	wxSemaphore* semaphore,
	AppSettings_t* appSettings,
	unsigned int* pollingTime,
	PMBUSCOMMAND_t *pmBusCommand,
	RECVBUFF_t *recvBuff,
	wxObjectDataPtr<PSUDataViewListModel>* dataViewListModel,
	PSUStatusBar *status_bar,
	STDPage* stdPage,
	PMBUSStatusPanel* pmbusStatusPanel,
	PMBUSStatusDCHPanel* pmbusStatusDCHPanel,
	std::vector<PMBUSSendCOMMAND_t> *sendCMDVector
	)
{
	this->m_IOAccess = ioaccess;
	this->m_CurrentIO = currentIO;
	this->m_rxTxSemaphore = semaphore;
	this->m_appSettings = appSettings;
	this->m_pollingTime = pollingTime;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_dataViewListCtrl = dataViewListModel;
	this->m_status_bar = status_bar;
	this->m_stdPage = stdPage;
	this->m_pmbusStatusPanel = pmbusStatusPanel;
	this->m_pmbusStatusDCHPanel = pmbusStatusDCHPanel;
	this->m_sendCMDVector = sendCMDVector;
}

IOPortSendCMDThread::~IOPortSendCMDThread() { }


void IOPortSendCMDThread::productSendBuff(unsigned int idx, unsigned int command, unsigned int responseDataLength){
	
	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:
		if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){

			this->m_sendBuff[0] = 0x41;
			this->m_sendBuff[1] = 0x44;
			this->m_sendBuff[2] = 0xb6;
			this->m_sendBuff[3] = command;
			this->m_sendBuff[4] = 0x0d;
			this->m_sendBuff[5] = 0x0a;
			this->m_sendBuff[6] = 0xb7;
			this->m_sendBuff[7] = responseDataLength;
			this->m_sendBuff[8] = 0x0d;
			this->m_sendBuff[9] = 0x0a;
		}
		else if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
			
			this->m_sendBuff[0] = 0x41;
			this->m_sendBuff[1] = 0x44;
			this->m_sendBuff[2] = 0xb6;
			this->m_sendBuff[3] = command;
			this->m_sendBuff[4] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[0];// Addtional Data [0]
			this->m_sendBuff[5] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[1];// Addtional Data [1]

			this->m_sendBuff[6] = 0x0d;
			this->m_sendBuff[7] = 0x0a;
			this->m_sendBuff[8] = 0xb7;
			this->m_sendBuff[9] = responseDataLength;
			this->m_sendBuff[10] = 0x0d;
			this->m_sendBuff[11] = 0x0a;

		}
		break;

	case IOACCESS_HID:
		if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){

			this->m_sendBuff[0] = 0x05;           // Report ID is 0x05
			this->m_sendBuff[1] = 0x0a;
			this->m_sendBuff[2] = 0x41;
			this->m_sendBuff[3] = 0x44;
			this->m_sendBuff[4] = 0xb6;
			this->m_sendBuff[5] = command;        // Command is 0x3a
			this->m_sendBuff[6] = 0x0d;
			this->m_sendBuff[7] = 0x0a;
			this->m_sendBuff[8] = 0xb7;
			this->m_sendBuff[9] = responseDataLength; // Response Data Length
			this->m_sendBuff[10] = 0x0d;
			this->m_sendBuff[11] = 0x0a;
			this->m_sendBuff[12] = 0x01;
			this->m_sendBuff[13] = 0x00;
			this->m_sendBuff[14] = 0x00;
			this->m_sendBuff[15] = 0x00;

			this->m_sendBuff[16] = 0x00;
			this->m_sendBuff[17] = 0x00;
			this->m_sendBuff[18] = 0x00;
			this->m_sendBuff[19] = 0x00;
			this->m_sendBuff[20] = 0x00;
			this->m_sendBuff[21] = 0x00;
			this->m_sendBuff[22] = 0x00;
			this->m_sendBuff[23] = 0x00;
			this->m_sendBuff[24] = 0x00;
			this->m_sendBuff[25] = 0x01;
			this->m_sendBuff[26] = responseDataLength; // Response Data Length
			this->m_sendBuff[27] = 0x00;
			this->m_sendBuff[28] = 0x00;
			this->m_sendBuff[29] = 0x02;
			this->m_sendBuff[30] = 0xb7;
			this->m_sendBuff[31] = responseDataLength; // Response Data Length

			this->m_sendBuff[32] = 0x00;
			this->m_sendBuff[33] = 0x01; //
			this->m_sendBuff[34] = 0xb7; //
			this->m_sendBuff[35] = 0x00;
			this->m_sendBuff[36] = 0x00;
			this->m_sendBuff[37] = 0x00;
			this->m_sendBuff[38] = 0x00;
			this->m_sendBuff[39] = 0x00;
			this->m_sendBuff[40] = 0x00;
			this->m_sendBuff[41] = 0x00;
			this->m_sendBuff[42] = 0x00;
			this->m_sendBuff[43] = 0x00;
			this->m_sendBuff[44] = 0x00;
			this->m_sendBuff[45] = 0x00;
			this->m_sendBuff[46] = 0x00;
			this->m_sendBuff[47] = 0x00;

			this->m_sendBuff[48] = 0x00;
			this->m_sendBuff[49] = 0x00;
			this->m_sendBuff[50] = 0x00;
			this->m_sendBuff[51] = 0x00;
			this->m_sendBuff[52] = 0x00;
			this->m_sendBuff[53] = 0x00;
			this->m_sendBuff[54] = 0x00;
			this->m_sendBuff[55] = 0x00;
			this->m_sendBuff[56] = 0x00;
			this->m_sendBuff[57] = 0x00;
			this->m_sendBuff[58] = 0x00;
			this->m_sendBuff[59] = 0x00;
			this->m_sendBuff[60] = 0x00;
			this->m_sendBuff[61] = 0x00;
			this->m_sendBuff[62] = 0x00;
			this->m_sendBuff[63] = 0x00;
		}
		else if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
			this->m_sendBuff[0] = 0x05;           // Report ID is 0x05
			this->m_sendBuff[1] = 0x0c;
			this->m_sendBuff[2] = 0x41;
			this->m_sendBuff[3] = 0x44;
			this->m_sendBuff[4] = 0xb6;
			this->m_sendBuff[5] = command;        // Command is 0x3a
			this->m_sendBuff[6] = 0x01;
			this->m_sendBuff[7] = 0x78;
			this->m_sendBuff[8] = 0x0d;
			this->m_sendBuff[9] = 0x0a;
			this->m_sendBuff[10] = 0xb7;
			this->m_sendBuff[11] = responseDataLength; // Response Data Length
			this->m_sendBuff[12] = 0x0d;
			this->m_sendBuff[13] = 0x0a;
			this->m_sendBuff[14] = 0x00;
			this->m_sendBuff[15] = 0x00;

			this->m_sendBuff[16] = 0x00;
			this->m_sendBuff[17] = 0x00;
			this->m_sendBuff[18] = 0x00;
			this->m_sendBuff[19] = 0x00;
			this->m_sendBuff[20] = 0x00;
			this->m_sendBuff[21] = 0x00;
			this->m_sendBuff[22] = 0x00;
			this->m_sendBuff[23] = 0x00;
			this->m_sendBuff[24] = 0x00;
			this->m_sendBuff[25] = 0x01;
			this->m_sendBuff[26] = responseDataLength; // Response Data Length
			this->m_sendBuff[27] = 0x00;
			this->m_sendBuff[28] = 0x00;
			this->m_sendBuff[29] = 0x02;
			this->m_sendBuff[30] = 0xb7;
			this->m_sendBuff[31] = responseDataLength; // Response Data Length

			this->m_sendBuff[32] = 0x00;
			this->m_sendBuff[33] = 0x01; //
			this->m_sendBuff[34] = 0xb7; //
			this->m_sendBuff[35] = 0x00;
			this->m_sendBuff[36] = 0x00;
			this->m_sendBuff[37] = 0x00;
			this->m_sendBuff[38] = 0x00;
			this->m_sendBuff[39] = 0x00;
			this->m_sendBuff[40] = 0x00;
			this->m_sendBuff[41] = 0x00;
			this->m_sendBuff[42] = 0x00;
			this->m_sendBuff[43] = 0x00;
			this->m_sendBuff[44] = 0x00;
			this->m_sendBuff[45] = 0x00;
			this->m_sendBuff[46] = 0x00;
			this->m_sendBuff[47] = 0x00;

			this->m_sendBuff[48] = 0x00;
			this->m_sendBuff[49] = 0x00;
			this->m_sendBuff[50] = 0x00;
			this->m_sendBuff[51] = 0x00;
			this->m_sendBuff[52] = 0x00;
			this->m_sendBuff[53] = 0x00;
			this->m_sendBuff[54] = 0x00;
			this->m_sendBuff[55] = 0x00;
			this->m_sendBuff[56] = 0x00;
			this->m_sendBuff[57] = 0x00;
			this->m_sendBuff[58] = 0x00;
			this->m_sendBuff[59] = 0x00;
			this->m_sendBuff[60] = 0x00;
			this->m_sendBuff[61] = 0x00;
			this->m_sendBuff[62] = 0x00;
			this->m_sendBuff[63] = 0x00;
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

}

#define BASE_RESPONSE_DATA_LENGTH  6
#define STR_LENGTH  256
wxThread::ExitCode IOPortSendCMDThread::Entry()
{
	int ret;
	int sendResult = 0;
	int ExpectReceiveDataLength = 0;
	int retry = 0;
	int sendDataLength = 0;
	bool sendRetryStillFailed = false;
	DWORD iteration=0;
	DWORD success=0;
	DWORD timeout = 0;
	wchar_t QueryStr[STR_LENGTH];
	wchar_t CookStr[STR_LENGTH];
	wchar_t RawStr[STR_LENGTH];
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "In Send Data Thread ");
	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread started (priority = %u).", GetPriority());
	PSU_DEBUG_PRINT(MSG_DEBUG, "RunMode is Continally ");
	PSU_DEBUG_PRINT(MSG_DETAIL,"m_pollingTime=%d", this->m_pollingTime);

#if 0
	// Open IO Device
	if (this->m_IOAccess[*this->m_CurrentIO].m_GetDeviceStatus() == IODEVICE_CLOSE){
		this->m_IOAccess[*this->m_CurrentIO].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);
		ret = this->m_IOAccess[*this->m_CurrentIO].m_OpenDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);

		if (ret != EXIT_SUCCESS){
			PSU_DEBUG_PRINT(MSG_FATAL, "Open IO Device Failed ! Need add error handle mechanism here");
		}
	}
#endif

	m_running = true;

	this->m_status_bar->getGauge()->Pulse();

	switch (this->m_appSettings->m_runMode){

	case RunMode_StopAnError:
	case RunMode_Iterations:
	case RunMode_Continually:
		// RunMode is Continally 
		while (m_running){

			for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE && m_running==true; idx++){

				PSU_DEBUG_PRINT(MSG_ALERT, "TestDestory");
				TestDestroy();

				if (this->m_pmBusCommand[idx].m_toggle == true){// If toggle is enable

					if (this->m_pmBusCommand[idx].m_access != cmd_access_write) { // If CMD's Attribute not equal cmd_access_write

						// Check If Need Chane Page
						if (this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage == cmd_need_change_page){
							char cmdPageValue = this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage == 1 ? 0x01 : 0x00;
							unsigned char pec = 0;;

							unsigned char changePageSendBuffer[8] = {
								0x41, 0x54, 0xB6, 0x00, cmdPageValue, 0x00,0x0D, 0x0A
							};

							pec = PMBusSlave_Crc8MakeBitwise(0, 7, changePageSendBuffer+2, 3);
							PSU_DEBUG_PRINT(MSG_DEBUG, "pec = %02xh", pec);

							changePageSendBuffer[5] = pec;

							PSU_DEBUG_PRINT(MSG_DEBUG, "CMD %s Need To Change Page, NeedChangeage=%d, CMDPage=%d", this->m_pmBusCommand[idx].m_label, this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

							do {
								// Send Data
								sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(changePageSendBuffer, 8);
								if (sendResult <= 0){
									PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Write Page CMD Failed, sendResult=%d", sendResult);
									// Retry 
									retry++;
									if (retry >= 3){
										PSU_DEBUG_PRINT(MSG_ALERT, "Still Send Send Write Page CMD Failed, Retry Times = %d", retry);
										sendRetryStillFailed = true;
										break;
									}
									else{
										PSU_DEBUG_PRINT(MSG_ALERT, "Send Write Page CMD Retry Times = %d", retry);
									}

								}
								else{
									PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Write Page CMD Success");
								}

							} while (sendResult <= 0);

							if (sendRetryStillFailed == true){
								PSU_DEBUG_PRINT(MSG_ALERT, "Send Write Page CMD Retry Send Still Failed, Exit Send Thread");
								m_running = false;
								break;
							}

							// Create IOPortReadCMDThread
							this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_IOAccess, this->m_CurrentIO, this->m_rxTxSemaphore, &this->m_pmBusCommand[idx], this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, BASE_RESPONSE_DATA_LENGTH);

							// If Create Thread Success
							if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
								PSU_DEBUG_PRINT(MSG_FATAL, "Can't create thread!");
							}
							else{
								this->m_IOPortReadCMDThread->Run();
							}

							// Semaphore Wait for Read Thread Complete
							PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", this->m_pmBusCommand[idx].m_register);
							ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
							if (ret != wxSEMA_NO_ERROR){
								PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d", ret);
							}
							else{
								PSU_DEBUG_PRINT(MSG_DEBUG, "Response Length of Write Page CMD is %d", this->m_recvBuff->m_length);
								wxString writePageRes("");
								for (unsigned int idx = 0; idx < this->m_recvBuff->m_length; idx++){
									writePageRes += wxString::Format("%02x,", this->m_recvBuff->m_recvBuff[idx]);
								}
								PSU_DEBUG_PRINT(MSG_DEBUG, "Send Write Page CMD Response : %s", writePageRes.c_str());
							}

						}//if (this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage == cmd_need_change_page)

						/*--------------------------------------------------------------------------------------------------------------*/

						iteration++;

						// Update DataView Register Field Icon
						this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_running;
						this->m_dataViewListCtrl->get()->RowValueChanged(idx, PSUDataViewListModel::Col_RegisterIconText);

						// Prepare Send Buffer
						this->productSendBuff(idx, this->m_pmBusCommand[idx].m_register, this->m_pmBusCommand[idx].m_responseDataLength);

						PSU_DEBUG_PRINT(MSG_DEBUG, "Prepare To Send");
						// Sleep Polling Time
						Sleep(*this->m_pollingTime);//this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);


						retry = 0;
						do {
							// Decide Send Data Length
							if (*this->m_CurrentIO == IOACCESS_SERIALPORT){
								if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
									sendDataLength = SERIAL_SEND_DATA_SIZE;
								}
								else if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
									sendDataLength = SERIAL_SEND_DATA_SIZE + 2;
								}
							}
							else{// HID
								sendDataLength = HID_SEND_DATA_SIZE;
							}

							PSU_DEBUG_PRINT(MSG_DEBUG, "Send Data Length =%d", sendDataLength);

							// Send Data
							sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_sendBuff, sendDataLength);
							if (sendResult <= 0){
								PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Failed, sendResult=%d", sendResult);
								// Retry 
								retry++;
								if (retry >= 3){
									PSU_DEBUG_PRINT(MSG_ALERT, "Still Send Failed, Retry Times = %d", retry);
									sendRetryStillFailed = true;
									break;
								}
								else{
									PSU_DEBUG_PRINT(MSG_ALERT, "Retry Times = %d", retry);
								}

							}
							else{
								PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
							}

						} while (sendResult <= 0);

						if (sendRetryStillFailed == true){
							PSU_DEBUG_PRINT(MSG_ALERT, "Retry Send Still Failed, Exit Send Thread");
							m_running = false;
							break;
						}

						// Create IOPortReadCMDThread
						this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_IOAccess, this->m_CurrentIO, this->m_rxTxSemaphore, &this->m_pmBusCommand[idx], this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH);

						// If Create Thread Success
						if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
							PSU_DEBUG_PRINT(MSG_FATAL, "Can't create thread!");
						}
						else{
							this->m_IOPortReadCMDThread->Run();
						}

						//

						// Semaphore Wait for Read Thread Complete
						PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", this->m_pmBusCommand[idx].m_register);
						ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
						if (ret != wxSEMA_NO_ERROR){
							PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d", ret);
						}
						else{

							if (this->m_recvBuff->m_length == 0){
								PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length = %d, CMD = %d", this->m_recvBuff->m_length, this->m_pmBusCommand[idx].m_register);
								this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_failure;
								timeout++;
							}
							else{
								// Get Expect Data Length
								ExpectReceiveDataLength = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH : this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH + 2;
								PSU_DEBUG_PRINT(MSG_DEBUG, "ExpectReceiveDataLength=%d", ExpectReceiveDataLength);

								//
								//if (this->m_recvBuff->m_length == (this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH))
								if (this->m_recvBuff->m_length == ExpectReceiveDataLength)
								{

									PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data of CMD %2x, Length = %d", this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length);
									success++;

									// copy data to PMBus Command Structure
									this->m_pmBusCommand[idx].m_recvBuff.m_length = this->m_recvBuff->m_length;
									for (unsigned int idx2 = 0; idx2 < this->m_recvBuff->m_length; idx2++){
										this->m_pmBusCommand[idx].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff->m_recvBuff[idx2];
										PSU_DEBUG_PRINT(MSG_DETAIL, "%d,%d", this->m_pmBusCommand[idx].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff->m_recvBuff[idx2]);
									}

									// Prepare Data Buffer
									this->productDataBuff(idx, this->m_pmBusCommand[idx].m_responseDataLength);

									// Call Raw Data CB Function
									this->m_pmBusCommand[idx].m_cmdCBFunc.m_rawCBFunc(&(this->m_pmBusCommand[idx]), RawStr, this->m_pmBusCommand[idx].m_responseDataLength);

									//#define PRINT_RAW_IN_FEILD
#ifdef PRINT_RAW_IN_FEILD
									wxString RawMsg("");
									for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
										RawMsg += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
									}
#else
									wxString RawMsg(RawStr);
#endif

									// Update Data View Model Raw Field
									wxVariant variantRaw;
									variantRaw = RawMsg;

									if (this->m_pmBusCommand[idx].m_cmdStatus.m_status != cmd_status_checksum_error){
										this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_success;
									}
									PSU_DEBUG_PRINT(MSG_DETAIL, "idx = %d", idx);
									this->m_dataViewListCtrl->get()->SetValueByRow(variantRaw, idx, PSUDataViewListModel::Col_RawText);
									this->m_dataViewListCtrl->get()->RowValueChanged(idx, PSUDataViewListModel::Col_RawText);

									PSU_DEBUG_PRINT(MSG_DEBUG, "%s", RawMsg.c_str());

									// Call Cook Data CB Function
									memset(CookStr, 0, STR_LENGTH);
									this->m_pmBusCommand[idx].m_cmdCBFunc.m_cookCBFunc(&(this->m_pmBusCommand[idx]), CookStr, this->m_pmBusCommand[idx].m_responseDataLength);

									// Update Data View Model Cook Field
									wxString CookMsg(CookStr);
									wxVariant variantCook;
									variantCook = CookMsg;

									this->m_dataViewListCtrl->get()->SetValueByRow(variantCook, idx, PSUDataViewListModel::Col_CookText);
									this->m_dataViewListCtrl->get()->RowValueChanged(idx, PSUDataViewListModel::Col_CookText);

									PSU_DEBUG_PRINT(MSG_DEBUG, "%s", CookMsg.c_str());

								}
								//
								else{
									PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length Don't As Expected CMD=%d, Length=%d", this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length);
									this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_failure;
								}
							}
						} // else if (ret != wxSEMA_NO_ERROR)

						//Sleep(this->m_pollingTime - 20);////this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
					} // if (this->m_pmBusCommand[idx].m_access != cmd_access_write)
				}// if (this->m_pmBusCommand[idx].m_toggle == true)
				else{
					//continue;
				}

				/*--------------------------------------------------------------------------------------------------------------*/
				// Send if user issue send CMD on write page when monitor is running 
				if (this->m_sendCMDVector->size() > 0){

					vector<PMBUSSendCOMMAND_t>::iterator sendCMDVector_Iterator;

					for (sendCMDVector_Iterator = this->m_sendCMDVector->begin(); sendCMDVector_Iterator != this->m_sendCMDVector->end(); sendCMDVector_Iterator++)
					{

						retry = 0;
						do {
							// Send Data
							sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(sendCMDVector_Iterator->m_sendData, sendCMDVector_Iterator->m_sendDataLength);
							if (sendResult <= 0){
								PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Separate Write CMD Failed, sendResult=%d", sendResult);
								// Retry 
								retry++;
								if (retry >= 3){
									PSU_DEBUG_PRINT(MSG_ALERT, "Still Send Separate Write CMD Failed, Retry Times = %d", retry);
									sendRetryStillFailed = true;
									break;
								}
								else{
									PSU_DEBUG_PRINT(MSG_ALERT, "Send Separate Write CMD Retry Times = %d", retry);
								}

							}
							else{
								PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Separate Write CMD Success");
							}

						} while (sendResult <= 0);

						if (sendRetryStillFailed == true){
							PSU_DEBUG_PRINT(MSG_ALERT, "Send Separate Write CMD Retry Send Still Failed, Exit Send Thread");
							m_running = false;
							break;
						}

						//
						// Create IOPortReadCMDThread
						this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_IOAccess, this->m_CurrentIO, this->m_rxTxSemaphore, &this->m_pmBusCommand[idx], this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, sendCMDVector_Iterator->m_bytesToRead);

						// If Create Thread Success
						if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
							PSU_DEBUG_PRINT(MSG_FATAL, "Can't create thread! (Separate)");
						}
						else{
							this->m_IOPortReadCMDThread->Run();
						}

						// Semaphore Wait for Read Thread Complete
						PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore WaitTimeout (Separate)");
						ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
						if (ret != wxSEMA_NO_ERROR){
							PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d(Separate)", ret);
						}
						else{
							PSU_DEBUG_PRINT(MSG_ALERT, "Response Length of Separate Write CMD is %d", this->m_recvBuff->m_length);
							wxString writePageRes("");
							for (unsigned int idx = 0; idx < this->m_recvBuff->m_length; idx++){
								writePageRes += wxString::Format("%02x,", this->m_recvBuff->m_recvBuff[idx]);
							}
							PSU_DEBUG_PRINT(MSG_ALERT, "Send Separate Write CMD Response : %s", writePageRes.c_str());
						}

					}// for (sendCMDVector_Iterator = this->m_sendCMDVector->begin(); sendCMDVector_Iterator != this->m_sendCMDVector->end(); sendCMDVector_Iterator++)

					// Clear Vector 
					this->m_sendCMDVector->clear();
				}
				/*--------------------------------------------------------------------------------------------------------------*/
				

				// Set Monitoring Name / Monitoring Summary of Status Bar
				wxString monitor("Monitoring...[");
				wxString cmd(wxString::Format("%02x", this->m_pmBusCommand[idx].m_register).Upper());
				wxString hex("h]");
				this->m_status_bar->setMonitoringCMDName(monitor + cmd + hex);

				wxString summary(wxString::Format("Iteration:%ld,Success:%ld,Timeout:%ld", iteration, success, timeout));
				this->m_status_bar->setMonitoringSummary(summary);

				if (idx == (PMBUSCOMMAND_SIZE - 1)){
					// Update StdPage
					this->UpdateSTDPage();
				}


				this->UpdateSTATUSPanel(idx);


				if (this->m_appSettings->m_runMode == RunMode_Iterations){
					if (iteration >= this->m_appSettings->m_IterationsSettingValue){
						PSU_DEBUG_PRINT(MSG_ALERT, "IterationsSettingValue : %d, iteration : %d", this->m_appSettings->m_IterationsSettingValue, iteration);
						this->m_running = false;
						break;// for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++) 
					}
				}

			}//for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++)
		} //while(m_running)

		this->m_status_bar->getGauge()->SetValue(0);

		break;

	default:

		break;
	}

#if 0
	// Close Device
	if (this->m_IOAccess[*this->m_CurrentIO].m_GetDeviceStatus() == IODEVICE_OPEN){
		this->m_IOAccess[*this->m_CurrentIO].m_CloseDevice();
	}
#endif

	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread finished.");

	return NULL;
}

void IOPortSendCMDThread::productDataBuff(unsigned int cmdIndex, unsigned int responseDataLength){

	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:
		// Copy Only The Data Bytes To DataBuff
		for (unsigned int idx = 0; idx < responseDataLength; idx++){
			this->m_pmBusCommand[cmdIndex].m_recvBuff.m_dataBuff[idx] = this->m_pmBusCommand[cmdIndex].m_recvBuff.m_recvBuff[idx];
		}

		break;

	case IOACCESS_HID:
		// Copy Only The Data Bytes To DataBuff
		for (unsigned int idx = 0; idx < responseDataLength; idx++){
			this->m_pmBusCommand[cmdIndex].m_recvBuff.m_dataBuff[idx] = this->m_pmBusCommand[cmdIndex].m_recvBuff.m_recvBuff[idx+6];
		}

		break;

	default :
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Wrong !");
		break;
	}
}


void IOPortSendCMDThread::UpdateSTDPage(void){
	// POUT
	wxString pout = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_POUT);
	this->m_stdPage->m_tcPOUT->SetValue(pout);
	// PIN
	wxString pin = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_PIN);
	this->m_stdPage->m_tcPIN->SetValue(pin);

	// VIN
	wxString vin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VIN);
	this->m_stdPage->m_tcVIN->SetValue(vin);

	// IIN
	wxString iin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IIN);
	this->m_stdPage->m_tcIIN->SetValue(iin);

	// VOUT
	wxString vout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VOUT);
	this->m_stdPage->m_tcVOUT->SetValue(vout);

	// IOUT
	wxString iout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IOUT);
	this->m_stdPage->m_tcIOUT->SetValue(iout);

	// VoSBY
	wxString vosby = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VoSBY);
	this->m_stdPage->m_tcVoSBY->SetValue(vosby);

	// IoSBY
	wxString iosby = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IoSBY);
	this->m_stdPage->m_tcIoSBY->SetValue(iosby);

	// VCAP
	wxString vcap = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_VCAP);
	this->m_stdPage->m_tcVCAP->SetValue(vcap);

	// AMD(8D)
	wxString amd_8d = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_AMD_8D);
	this->m_stdPage->m_tcAMD8D->SetValue(amd_8d);

	// SEC(8E)
	wxString sec_8e = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_SEC_8E);
	this->m_stdPage->m_tcSEC8E->SetValue(sec_8e);

	// PRI(8F)
	wxString pri_8f = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_PRI_8F);
	this->m_stdPage->m_tcPRI8F->SetValue(pri_8f);

	// FAN1
	wxString fan1 = wxString::Format("%5.1f", (double)PMBUSHelper::GetPMBusStatus()->m_FAN1);
	this->m_stdPage->m_tcFAN1->SetValue(fan1);

	// FAN2

	// FAN3

	// FAN4

}

unsigned int IOPortSendCMDThread::findPMBUSCMDIndex(unsigned int cmd_register){

	unsigned int index = 0;

	for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++){
		if (this->m_pmBusCommand[idx].m_register == cmd_register){
			index = idx;
			break;
		}
	}

	return index;
}

void IOPortSendCMDThread::UpdateSTATUSPanel(unsigned int index){
	
	if (index == this->findPMBUSCMDIndex(0x79)){
		// Update WORD Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusWORD();
	}

	if (index == this->findPMBUSCMDIndex(0x7a)){
		// Update VOUT Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusVOUT();
	}

	if (index == this->findPMBUSCMDIndex(0x7b)){
		// Update IOUT Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusIOUT();
	}

	if (index == this->findPMBUSCMDIndex(0x7c)){
		// Update INPUT Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusINPUT();
	}

	if (index == this->findPMBUSCMDIndex(0x7d)){
		// Update Temperature Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusTemperature();
	}

	if (index == this->findPMBUSCMDIndex(0x7e)){
		// Update CML Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusCML();
	}

	if (index == this->findPMBUSCMDIndex(0x7f)){
		// Update OTHER Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusOTHER();
	}

	if (index == this->findPMBUSCMDIndex(0x81)){
		// Update OTHER Filed of PMBUSStatus Panel
		this->m_pmbusStatusPanel->Update_StatusFAN12();
	}

	if (index == this->findPMBUSCMDIndex(0xdc)){
		// Update Total PMBUSStatusDCH Panel
		this->m_pmbusStatusDCHPanel->UpdatePanel();
	}

}