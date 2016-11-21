/**
* @file SerialPortSendThread.cpp
*/

#include "IOPortSendCMDThread.h"
#include "MainFrame.h"

IOPortSendCMDThread::IOPortSendCMDThread(wxSemaphore* semaphore){
	this->m_rxTxSemaphore = semaphore;
}

IOPortSendCMDThread::IOPortSendCMDThread(
	MainFrame*   pHandler,
	IOACCESS*    ioaccess,
	unsigned int* currentIO,
	wxSemaphore* semaphore,
	AppSettings_t* appSettings,
	unsigned int* pollingTime,
	PMBUSCOMMAND_t *pmBusCommand,
	RECVBUFF_t *recvBuff,
	wxObjectDataPtr<PMBUSCMDListModel>* dataViewListModel,
	PMBUSStatusBar *status_bar,
	STDPage* stdPage,
	PMBUSStatusPanel* pmbusStatusPanel,
	PMBUSStatusDCHPanel* pmbusStatusDCHPanel,
	std::vector<PMBUSSendCOMMAND_t> *sendCMDVector
	)
{
	this->m_pHandler = pHandler;
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

IOPortSendCMDThread::~IOPortSendCMDThread() {
	this->m_pHandler->m_sendThreadStopFlag = true;
}

void IOPortSendCMDThread::productWritePageSendBuff(char cmdPageValue){

	unsigned short pec;

	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:
		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		m_writePageSendBuff[0] = 0x41;
		m_writePageSendBuff[1] = 0x54;
		m_writePageSendBuff[2] = PMBUSHelper::GetSlaveAddress(); // Slave Address
		m_writePageSendBuff[3] = 0x00;// CMD
		m_writePageSendBuff[4] = cmdPageValue;

		pec = PMBusSlave_Crc8MakeBitwise(0, 7, m_writePageSendBuff + 2, 3);
		PSU_DEBUG_PRINT(MSG_DEBUG, "pec = %02xh", pec);

		m_writePageSendBuff[5] = pec; // PEC
		m_writePageSendBuff[6] = 0x0D;
		m_writePageSendBuff[7] = 0x0A;

		break;

	case IOACCESS_HID:
		m_writePageSendBuff[0] = 0x05;
		m_writePageSendBuff[1] = 0x08;
		m_writePageSendBuff[2] = 0x41;
		m_writePageSendBuff[3] = 0x54;
		m_writePageSendBuff[4] = PMBUSHelper::GetSlaveAddress(); // Slave Address
		m_writePageSendBuff[5] = 0x00;// CMD
		m_writePageSendBuff[6] = cmdPageValue;
		
		pec = PMBusSlave_Crc8MakeBitwise(0, 7, m_writePageSendBuff + 4, 3);
		PSU_DEBUG_PRINT(MSG_DEBUG, "pec = %02xh", pec);
		
		m_writePageSendBuff[7] = pec; // PEC
		m_writePageSendBuff[8] = 0x0D;
		m_writePageSendBuff[9] = 0x0A;



		break;

	default:

		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		
		break;
	}
}

int IOPortSendCMDThread::productSendBuff(unsigned int idx, unsigned int command, unsigned int responseDataLength){
	
	unsigned int baseIndex = 0;

	switch (*this->m_CurrentIO){

	case IOACCESS_SERIALPORT:
		if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){

			this->m_sendBuff[baseIndex++] = 0x41;
			this->m_sendBuff[baseIndex++] = 0x44;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			this->m_sendBuff[baseIndex++] = command;
			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			this->m_sendBuff[baseIndex++] = responseDataLength;

			if (this->m_sendBuff[baseIndex-1] == 0x0d){
				this->m_sendBuff[baseIndex++] = 0x0d;
			}

			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;
		}
		else if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
			
			this->m_sendBuff[baseIndex++] = 0x41;
			this->m_sendBuff[baseIndex++] = 0x44;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			this->m_sendBuff[baseIndex++] = command;
			
			//this->m_sendBuff[4] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[0];// Addtional Data [0]
			//this->m_sendBuff[5] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[1];// Addtional Data [1]

			for (unsigned int len = 0; len < this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength; len++){
				this->m_sendBuff[baseIndex++] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len];// Addtional Data [len]
			}

			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			this->m_sendBuff[baseIndex++] = responseDataLength;

			if (this->m_sendBuff[baseIndex - 1] == 0x0d){
				this->m_sendBuff[baseIndex++] = 0x0d;
			}

			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;

			/*
			if (this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength > 2){
				this->m_sendBuff[6] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[2];// Addtional Data [2]
				this->m_sendBuff[7] = 0x0d;
				this->m_sendBuff[8] = 0x0a;
				this->m_sendBuff[9] = PMBUSHelper::GetSlaveAddress() | 0x01;
				this->m_sendBuff[10] = responseDataLength;
				this->m_sendBuff[11] = 0x0d;
				this->m_sendBuff[12] = 0x0a;
			}
			else{
				this->m_sendBuff[6] = 0x0d;
				this->m_sendBuff[7] = 0x0a;
				this->m_sendBuff[8] = PMBUSHelper::GetSlaveAddress() | 0x01;
				this->m_sendBuff[9] = responseDataLength;
				this->m_sendBuff[10] = 0x0d;
				this->m_sendBuff[11] = 0x0a;
			}
			*/

		}
		break;

	case IOACCESS_HID:
		if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){

			this->m_sendBuff[baseIndex++] = 0x05;           // Report ID is 0x05
			this->m_sendBuff[baseIndex++] = 0x0a;           // Total Data Length
			this->m_sendBuff[baseIndex++] = 0x41;
			this->m_sendBuff[baseIndex++] = 0x44;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			this->m_sendBuff[baseIndex++] = command;        // Command is 0x3a
			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			this->m_sendBuff[baseIndex++] = responseDataLength; // Response Data Length

			if (this->m_sendBuff[baseIndex - 1] == 0x0d){
				this->m_sendBuff[baseIndex++] = 0x0d;
			}

			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;

			this->m_sendBuff[1] = (baseIndex - 2);

			this->m_sendBuff[baseIndex++] = 0x01;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;

			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x01;
			this->m_sendBuff[baseIndex++] = responseDataLength; // Response Data Length
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x02;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			this->m_sendBuff[baseIndex++] = responseDataLength; // Response Data Length

			this->m_sendBuff[baseIndex++] = 0x00;
			this->m_sendBuff[baseIndex++] = 0x01; //
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;

			for(int local=baseIndex; local<64; local++){
				this->m_sendBuff[local] = 0;
			}

#if 0
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
#endif
		}
		else if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
			
			this->m_sendBuff[baseIndex++] = 0x05;// Report ID is 0x05
			this->m_sendBuff[baseIndex++] = 0x0c + (this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength - 2);//0x0c;// Data Length
			this->m_sendBuff[baseIndex++] = 0x41;
			this->m_sendBuff[baseIndex++] = 0x44;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress();
			this->m_sendBuff[baseIndex++] = command;        // Command is 0x3a
			
			//this->m_sendBuff[6] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[0];// Addtional Data [0]
			//this->m_sendBuff[7] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[1];// Addtional Data [1]

			for (unsigned int len = 0; len < this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength; len++){
				this->m_sendBuff[baseIndex++] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len];// Addtional Data [len]
				PSU_DEBUG_PRINT(MSG_DEBUG, "idx=%d, AddtionalData[%d]=%xH", idx, len, this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[len]);
			}

			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;
			this->m_sendBuff[baseIndex++] = PMBUSHelper::GetSlaveAddress() | 0x01;
			this->m_sendBuff[baseIndex++] = responseDataLength; // Response Data Length

			if (this->m_sendBuff[baseIndex - 1] == 0x0d){
				this->m_sendBuff[baseIndex++] = 0x0d;
			}

			this->m_sendBuff[baseIndex++] = 0x0d;
			this->m_sendBuff[baseIndex++] = 0x0a;

			this->m_sendBuff[1] = (baseIndex - 2);

			this->m_sendBuff[baseIndex++] = 0x00;

			for(unsigned int target = baseIndex; target < 25; target++){
				this->m_sendBuff[baseIndex++] = 0x00;
			}

#if 0
			if (this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength > 2){
				this->m_sendBuff[8] = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[2];// Addtional Data [2]
				this->m_sendBuff[9] = 0x0d;
				this->m_sendBuff[10] = 0x0a;
				this->m_sendBuff[11] = PMBUSHelper::GetSlaveAddress() | 0x01;
				this->m_sendBuff[12] = responseDataLength; // Response Data Length
				this->m_sendBuff[13] = 0x0d;
				this->m_sendBuff[14] = 0x0a;
			}
			else{
				this->m_sendBuff[8] = 0x0d;
				this->m_sendBuff[9] = 0x0a;
				this->m_sendBuff[10] = PMBUSHelper::GetSlaveAddress() | 0x01;
				this->m_sendBuff[11] = responseDataLength; // Response Data Length
				this->m_sendBuff[12] = 0x0d;
				this->m_sendBuff[13] = 0x0a;
				this->m_sendBuff[14] = 0x00;
			}
	
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
#endif

			this->m_sendBuff[25] = 0x01;
			this->m_sendBuff[26] = responseDataLength; // Response Data Length
			this->m_sendBuff[27] = 0x00;
			this->m_sendBuff[28] = 0x00;
			this->m_sendBuff[29] = 0x02;
			this->m_sendBuff[30] = PMBUSHelper::GetSlaveAddress() | 0x01;
			this->m_sendBuff[31] = responseDataLength; // Response Data Length

			this->m_sendBuff[32] = 0x00;
			this->m_sendBuff[33] = 0x01; //
			this->m_sendBuff[34] = PMBUSHelper::GetSlaveAddress() | 0x01;
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

	return baseIndex;
}

#define BASE_RESPONSE_DATA_LENGTH  6
#define STR_LENGTH  256
//#define PRINT_RAW_IN_FEILD
#define OUTPUT_SEND_DATA
#define OUTPUT_RECEIVE_DATA
wxThread::ExitCode IOPortSendCMDThread::Entry()
{
	int ret;
	int sendResult = 0;
	int ExpectReceiveDataLength = 0;
	int retry = 0;
	int sendDataLength = 0;
	int uartSendDataLength = 0;
	int QueryCMDIndex = 0;
	int CoefficientsCMDIndex = 0;
	int PreviousQueryCMDAdditionalCMD = 0;
	int PreviousCoefficientsCMDAdditionalCMD = 0;
	bool sendRetryStillFailed = false;
	DWORD iteration = 0;
	DWORD success = 0;
	DWORD timeout = 0;
	wchar_t QueryStr[STR_LENGTH];
	wchar_t CoefficientsStr[STR_LENGTH];
	wchar_t CookStr[STR_LENGTH];
	wchar_t RawStr[STR_LENGTH];

	PSU_DEBUG_PRINT(MSG_DEBUG, "In Send Data Thread ");
	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread started (priority = %u).", GetPriority());
	PSU_DEBUG_PRINT(MSG_DEBUG, "RunMode is Continally ");
	PSU_DEBUG_PRINT(MSG_DETAIL, "m_pollingTime=%d", this->m_pollingTime);

#if 0
	// Open IO Device
	if (this->m_IOAccess[*this->m_CurrentIO].m_GetDeviceStatus() == IODEVICE_CLOSE){
		this->m_IOAccess[*this->m_CurrentIO].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);
		ret = this->m_IOAccess[*this->m_CurrentIO].m_OpenDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);

		if (ret != EXIT_SUCCESS){
			PSU_DEBUG_PRINT(MSG_ERROR, "Open IO Device Failed ! Need add error handle mechanism here");
		}
	}
#endif

	m_running = true;

	//this->m_status_bar->getGauge()->Pulse();
	wxQueueEvent(m_pHandler->GetEventHandler(), new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_START));

	switch (this->m_appSettings->m_runMode){

	case RunMode_StopAnError:
	case RunMode_Iterations:
	case RunMode_Continually:
		// RunMode is Continally 
		while (m_running && this->TestDestroy()==false){

			for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize() && m_running == true; idx++){

				if (this->TestDestroy() == true){
					break;
				}

#if 1
				wxThreadEvent* thread_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE);
				thread_evt->SetInt(idx);
				wxQueueEvent(m_pHandler->GetEventHandler(), thread_evt);
#else
				wxQueueEvent(m_pHandler->GetEventHandler(), new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE));
#endif

				/*** If toggle is enable ***/
				if (this->m_pmBusCommand[idx].m_toggle == true){

					
					
					/*** Query Command (0x1A) ***/
					if (this->m_pmBusCommand[idx].m_cmdStatus.m_queried == cmd_query_not_yet){

						// Find Query Command (0x1A)'s Index
						QueryCMDIndex = -1;
						for (unsigned int local=0; local < PMBUSHelper::GetCurrentCMDTableSize(); local++){
							if (this->m_pmBusCommand[local].m_register == PMBUSCMD_1AH_QUERY){
								QueryCMDIndex = local;
								break;
							}
						}

						if (QueryCMDIndex >= 0){					
							// Prepare Send Buffer
							PreviousQueryCMDAdditionalCMD = this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1];
							this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1] = this->m_pmBusCommand[idx].m_register;
							uartSendDataLength = this->productSendBuff(QueryCMDIndex, this->m_pmBusCommand[QueryCMDIndex].m_register, this->m_pmBusCommand[QueryCMDIndex].m_responseDataLength);

							// Send Query Command
							retry = 0;
							do {
								// Decide Send Data Length
								if (*this->m_CurrentIO == IOACCESS_SERIALPORT){
									if (this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
										sendDataLength = uartSendDataLength;//SERIAL_SEND_DATA_SIZE;
									}
									else if (this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
										sendDataLength = uartSendDataLength;//SERIAL_SEND_DATA_SIZE + this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_AddtionalDataLength;
									}
								}
								else{// HID
									sendDataLength = HID_SEND_DATA_SIZE;
								}

								PSU_DEBUG_PRINT(MSG_DEBUG, "Send Data Length =%d", sendDataLength);

								// Send Data
								sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_sendBuff, sendDataLength);
								if (sendResult <= 0){
									PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
									// Retry 
									retry++;
									if (retry >= 3){
										PSU_DEBUG_PRINT(MSG_DEBUG, "Still Send Failed, Retry Times = %d", retry);
										sendRetryStillFailed = true;
										break;
									}
									else{
										PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
									}

								}
								else{
#ifdef OUTPUT_SEND_DATA
									wxString sentData(wxT("Sent Data : "));
									for (int idx = 0; idx < sendDataLength; idx++){
										sentData += wxString::Format(" %02x ", this->m_sendBuff[idx]);
									}
									PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sentData.c_str());
#endif
									PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
								}

							} while (sendResult <= 0);

							if (sendRetryStillFailed == true){
								PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Send Still Failed, Exit Send Thread");
								m_running = false;
								break;
							}

							// Read Query Result
							unsigned int bytesToRead = this->m_pmBusCommand[QueryCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH;
							this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_IOAccess, this->m_CurrentIO, this->m_rxTxSemaphore, &this->m_pmBusCommand[QueryCMDIndex], this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, bytesToRead);

							// If Create Thread Success
							if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
								PSU_DEBUG_PRINT(MSG_ERROR, "Can't create read thread!");
							}
							else{
								this->m_IOPortReadCMDThread->Run();
							}
						
							// Semaphore Wait for Read Thread Complete
							PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", this->m_pmBusCommand[QueryCMDIndex].m_register);
							ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
						
							if (ret != wxSEMA_NO_ERROR){
								PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d", ret);
							}
							else{

								if (this->m_recvBuff->m_length == 0){
									PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length = %d, CMD = %02xH", this->m_recvBuff->m_length, this->m_pmBusCommand[QueryCMDIndex].m_register);
									this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_status = cmd_status_failure;
									//timeout++;
								}
								else{
									// Get Expect Data Length
									ExpectReceiveDataLength = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? this->m_pmBusCommand[QueryCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH : this->m_pmBusCommand[QueryCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH + 2;
									PSU_DEBUG_PRINT(MSG_DEBUG, "ExpectReceiveDataLength=%d", ExpectReceiveDataLength);

									//
									if (this->m_recvBuff->m_length == ExpectReceiveDataLength){

										PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data of CMD %2x, Length = %d", this->m_pmBusCommand[QueryCMDIndex].m_register, this->m_recvBuff->m_length);
										//success++;

										// copy data to PMBus Command Structure
										this->m_pmBusCommand[QueryCMDIndex].m_recvBuff.m_length = this->m_recvBuff->m_length;
										for (unsigned int idx2 = 0; idx2 < this->m_recvBuff->m_length; idx2++){
											this->m_pmBusCommand[QueryCMDIndex].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff->m_recvBuff[idx2];
											PSU_DEBUG_PRINT(MSG_DETAIL, "%d,%d", this->m_pmBusCommand[QueryCMDIndex].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff->m_recvBuff[idx2]);
										}

										// Prepare Data Buffer
										this->productDataBuff(QueryCMDIndex, this->m_pmBusCommand[QueryCMDIndex].m_responseDataLength);

#ifdef OUTPUT_RECEIVE_DATA
										wxString recvBytes("");
										for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
											recvBytes += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
										}

										PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Bytes : %s", recvBytes.c_str());

#endif

										// Check I2C BUS Not Acknowledge
										unsigned char i2cBusAck = PMBUSHelper::IsI2CBusNotAcknowlwdge(this->m_CurrentIO, this->m_recvBuff->m_recvBuff, this->m_recvBuff->m_length);
										if (i2cBusAck == PMBUSHelper::response_ng){
											this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_status = cmd_status_i2c_bus_not_acknowledge;
										}

										if (this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_status != cmd_status_checksum_error && this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_status != cmd_status_i2c_bus_not_acknowledge){
											this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_status = cmd_status_success;
											//success++;
										}

										bool PreUpdateQuery = true;

										if (this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_status == cmd_status_success){

											// Get Query CMD
											int queryCMD;
											queryCMD = this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1];

											// Get Index of Query CMD 
											int queryCMDIndex = -1;
											queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

											if (queryCMDIndex < 0){
												PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
												PreUpdateQuery = false;
											}
											else{
												PSU_DEBUG_PRINT(MSG_DEBUG, "Find Index of Query CMD %02x is %d", queryCMD, queryCMDIndex);
											}

											if (PreUpdateQuery == true){
												// Call Query Data CB Function
												memset(QueryStr, 0, STR_LENGTH * sizeof(wchar_t));                                                              // CMD's Page
												this->m_pmBusCommand[queryCMDIndex].m_cmdCBFunc.m_queryCBFunc(&(this->m_pmBusCommand[QueryCMDIndex]), QueryStr, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

												wxString QueryMsg(QueryStr);

												wxThreadEvent* threadquery_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_QUERY);
												threadquery_evt->SetInt(queryCMDIndex);
												threadquery_evt->SetString(QueryMsg);
												wxQueueEvent(m_pHandler->GetEventHandler(), threadquery_evt);

												PSU_DEBUG_PRINT(MSG_DEBUG, "%s", QueryMsg.c_str());

												/*** If Data Format is Direct Data Format Type, Call Coefficients CMD¡@(0x30) To Get Coefficients ***/

												// Find Coefficients Command (0x1A)'s Index
												CoefficientsCMDIndex = -1;
												for (unsigned int local2 = 0; local2 < PMBUSHelper::GetCurrentCMDTableSize(); local2++){
													if (this->m_pmBusCommand[local2].m_register == PMBUSCMD_30H_COEFFICIENTS){
														CoefficientsCMDIndex = local2;
														break;
													}
												}

												if (this->m_pmBusCommand[idx].m_dataFormat.m_formatType == cmd_data_format_DirectData_Format 
													/* || this->m_pmBusCommand[idx].m_dataFormat.m_formatType == cmd_data_format_8bit_Unsigned_Number */){

													if (CoefficientsCMDIndex >= 0){
														// Prepare Send Buffer
														PreviousCoefficientsCMDAdditionalCMD = this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[1];
														this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[1] = this->m_pmBusCommand[idx].m_register;
														uartSendDataLength = this->productSendBuff(CoefficientsCMDIndex, this->m_pmBusCommand[CoefficientsCMDIndex].m_register, this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength);

														// Send Query Command
														retry = 0;
														do {
															// Decide Send Data Length
															if (*this->m_CurrentIO == IOACCESS_SERIALPORT){
																if (this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
																	sendDataLength = uartSendDataLength;// SERIAL_SEND_DATA_SIZE;
																}
																else if (this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
																	sendDataLength = uartSendDataLength;// SERIAL_SEND_DATA_SIZE + this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalDataLength;
																}
															}
															else{// HID
																sendDataLength = HID_SEND_DATA_SIZE;
															}

															PSU_DEBUG_PRINT(MSG_DEBUG, "Send Data Length =%d", sendDataLength);

															// Send Data
															sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_sendBuff, sendDataLength);
															if (sendResult <= 0){
																PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
																// Retry 
																retry++;
																if (retry >= 3){
																	PSU_DEBUG_PRINT(MSG_DEBUG, "Still Send Failed, Retry Times = %d", retry);
																	sendRetryStillFailed = true;
																	break;
																}
																else{
																	PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
																}

															}
															else{
#ifdef OUTPUT_SEND_DATA
																wxString sentData(wxT("Sent Data : "));
																for (int idx = 0; idx < sendDataLength; idx++){
																	sentData += wxString::Format(" %02x ", this->m_sendBuff[idx]);
																}
																PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sentData.c_str());
#endif
																PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
															}

														} while (sendResult <= 0);

														if (sendRetryStillFailed == true){
															PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Send Still Failed, Exit Send Thread");
															m_running = false;
															break;
														}

														// Read Quert Result
														unsigned int bytesToRead = this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH;
														this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_IOAccess, this->m_CurrentIO, this->m_rxTxSemaphore, &this->m_pmBusCommand[CoefficientsCMDIndex], this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, bytesToRead);

														// If Create Thread Success
														if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
															PSU_DEBUG_PRINT(MSG_ERROR, "Can't create read thread!");
														}
														else{
															this->m_IOPortReadCMDThread->Run();
														}

														// Semaphore Wait for Read Thread Complete
														PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", this->m_pmBusCommand[CoefficientsCMDIndex].m_register);
														ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);

														if (ret != wxSEMA_NO_ERROR){
															PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d", ret);
														}
														else{
															if (this->m_recvBuff->m_length == 0){
																PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length = %d, CMD = %02xH", this->m_recvBuff->m_length, this->m_pmBusCommand[CoefficientsCMDIndex].m_register);
																this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_status = cmd_status_failure;
																//timeout++;
															}
															else{
																// Get Expect Data Length
																ExpectReceiveDataLength = (*this->m_CurrentIO == IOACCESS_SERIALPORT) ? this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH : this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH + 2;
																PSU_DEBUG_PRINT(MSG_DEBUG, "ExpectReceiveDataLength=%d", ExpectReceiveDataLength);

																//
																if (this->m_recvBuff->m_length == ExpectReceiveDataLength){

																	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data of CMD %2x, Length = %d", this->m_pmBusCommand[CoefficientsCMDIndex].m_register, this->m_recvBuff->m_length);
																	//success++;

																	// copy data to PMBus Command Structure
																	this->m_pmBusCommand[CoefficientsCMDIndex].m_recvBuff.m_length = this->m_recvBuff->m_length;
																	for (unsigned int idx2 = 0; idx2 < this->m_recvBuff->m_length; idx2++){
																		this->m_pmBusCommand[CoefficientsCMDIndex].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff->m_recvBuff[idx2];
																		PSU_DEBUG_PRINT(MSG_DETAIL, "%d,%d", this->m_pmBusCommand[CoefficientsCMDIndex].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff->m_recvBuff[idx2]);
																	}

																	// Prepare Data Buffer
																	this->productDataBuff(CoefficientsCMDIndex, this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength);

#ifdef OUTPUT_RECEIVE_DATA
																	wxString recvBytes("");
																	for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
																		recvBytes += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
																	}

																	PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Bytes : %s", recvBytes.c_str());

#endif

																	// Check I2C BUS Not Acknowledge
																	unsigned char i2cBusAck = PMBUSHelper::IsI2CBusNotAcknowlwdge(this->m_CurrentIO, this->m_recvBuff->m_recvBuff, this->m_recvBuff->m_length);
																	if (i2cBusAck == PMBUSHelper::response_ng){
																		this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_status = cmd_status_i2c_bus_not_acknowledge;
																	}

																	if (this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_status != cmd_status_checksum_error && this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_status != cmd_status_i2c_bus_not_acknowledge){
																		this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_status = cmd_status_success;
																		//success++;
																	}

																	bool PreUpdateCoefficients = true;

																	if (this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_status == cmd_status_success){

																		// Get Query CMD
																		int queryCMD;
																		queryCMD = this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[1];

																		// Get Index of Query CMD 
																		int queryCMDIndex = -1;

																		queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

																		#if 0
																		for (int idx2 = 0; idx2 < (signed)PMBUSHelper::CurrentCMDTableSize; idx2++){
																			if (PMBUSHelper::getPMBUSCMDData()[idx2].m_register == queryCMD){
																				queryCMDIndex = idx2;
																				break;
																			}
																		}
                                                                        #endif

																		if (queryCMDIndex < 0){
																			PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
																			PreUpdateCoefficients = false;
																		}

																		if (PreUpdateCoefficients == true){
																			// Call Coefficients Data CB Function
																			memset(CoefficientsStr, 0, STR_LENGTH * sizeof(wchar_t));																			 // CMD's Page
																			this->m_pmBusCommand[queryCMDIndex].m_cmdCBFunc.m_coefficientsCBFunc(&(this->m_pmBusCommand[CoefficientsCMDIndex]), CoefficientsStr, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

																			wxString CoefficientsMsg(CoefficientsStr);

																			wxThreadEvent* threadcoefficients_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS);
																			threadcoefficients_evt->SetInt(queryCMDIndex);
																			threadcoefficients_evt->SetString(CoefficientsMsg);
																			wxQueueEvent(m_pHandler->GetEventHandler(), threadcoefficients_evt);

																			PSU_DEBUG_PRINT(MSG_DEBUG, "%s", CoefficientsMsg.c_str());
																		}

																	}

																}

															}

														}

														this->m_pmBusCommand[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[1] = PreviousCoefficientsCMDAdditionalCMD;

													}

												}// if (this->m_pmBusCommand[idx].m_dataFormat.m_formatType == cmd_data_format_DirectData_Format)
												else{
													wxString PaddingStr(wxT("---"));

													wxThreadEvent* threadcoefficients_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS);
													threadcoefficients_evt->SetInt(queryCMDIndex);
													threadcoefficients_evt->SetString(PaddingStr);
													wxQueueEvent(m_pHandler->GetEventHandler(), threadcoefficients_evt);
												}

											}// if (PreUpdateQuery == true)
										
										}// if (this->m_pmBusCommand[idx].m_cmdStatus.m_status == cmd_status_success)

									}// if (this->m_recvBuff->m_length == ExpectReceiveDataLength) 

								}// else (if (this->m_recvBuff->m_length == 0))

							} // else if (ret != wxSEMA_NO_ERROR)
						
							this->m_pmBusCommand[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1] = PreviousQueryCMDAdditionalCMD;

						}// if (QueryCMDIndex >= 0)
		
						// Just Doing Once in Every Send Thread Start 
						this->m_pmBusCommand[idx].m_cmdStatus.m_queried = cmd_query_done;

					}// if (this->m_pmBusCommand[idx].m_cmdStatus.m_queried == cmd_query_not_yet)


					/*** If Own Read Access (No Need To Polling If CMD Don't Have Read Access) ***/
					if (PMBUSHelper::isOwnReadAccess(this->m_pmBusCommand[idx].m_access) == true){//this->m_pmBusCommand[idx].m_access != cmd_access_write) { // If CMD's Attribute not equal cmd_access_write

						/*-------------------- Check If Need Change Page --------------------*/
						if (this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage == cmd_need_change_page){
							char cmdPageValue = this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage == 1 ? 0x01 : 0x00;
							unsigned char pec = 0;;

#if 0
							unsigned char changePageSendBuffer[8] = {
								0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
							};

							pec = PMBusSlave_Crc8MakeBitwise(0, 7, changePageSendBuffer + 2, 3);
							PSU_DEBUG_PRINT(MSG_DEBUG, "pec = %02xh", pec);

							changePageSendBuffer[5] = pec;
#endif

							this->productWritePageSendBuff(cmdPageValue);

							PSU_DEBUG_PRINT(MSG_DEBUG, "CMD %s Need To Change Page, NeedChangeage=%d, CMDPage=%d", this->m_pmBusCommand[idx].m_label, this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

							unsigned int writePageCMDWriteLength = (*this->m_CurrentIO) == IOACCESS_SERIALPORT ? 8 : HID_SEND_DATA_SIZE;

							do {
								// Send Data
								sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(m_writePageSendBuff, writePageCMDWriteLength);
								if (sendResult <= 0){
									PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Write Page CMD Failed, sendResult=%d", sendResult);
									// Retry 
									retry++;
									if (retry >= 3){
										PSU_DEBUG_PRINT(MSG_ALERT, "Still Send Write Page CMD Failed, Retry Times = %d", retry);
										sendRetryStillFailed = true;
										break;
									}
									else{
										PSU_DEBUG_PRINT(MSG_ALERT, "Send Write Page CMD Retry Times = %d", retry);
									}

								}
								else{
#ifdef OUTPUT_SEND_DATA
									wxString PageSentData(wxT("Sent Data : "));
									for (unsigned idx = 0; idx < writePageCMDWriteLength; idx++){
										PageSentData += wxString::Format(" %02x ", this->m_writePageSendBuff[idx]);
									}
									PSU_DEBUG_PRINT(MSG_DEBUG, "%s", PageSentData.c_str());
#endif
									
									
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
								PSU_DEBUG_PRINT(MSG_ERROR, "Can't create thread!");
							}
							else{
								this->m_IOPortReadCMDThread->Run();
							}

							// Semaphore Wait for Read Thread Complete
							PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", this->m_pmBusCommand[idx].m_register);
							ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
							if (ret != wxSEMA_NO_ERROR){
								PSU_DEBUG_PRINT(MSG_ERROR, "Semaphore wait timout occurs : error = %d", ret);

								// If Run Mode Setting is "Stop An Error"
								if (this->m_appSettings->m_runMode == RunMode_StopAnError){
									m_running = false;
									break;
								}

							}
							else{
								// If Receive Data Length is 0
								if (this->m_recvBuff->m_length == 0){
									PSU_DEBUG_PRINT(MSG_ERROR, "Response Length of Write Page CMD is %d", this->m_recvBuff->m_length);
								}
								else{
									PSU_DEBUG_PRINT(MSG_DEBUG, "Response Length of Write Page CMD is %d", this->m_recvBuff->m_length);
									wxString writePageRes("");
									for (unsigned int idx = 0; idx < this->m_recvBuff->m_length; idx++){
										writePageRes += wxString::Format("%02x,", this->m_recvBuff->m_recvBuff[idx]);
									}
									PSU_DEBUG_PRINT(MSG_DEBUG, "Send Write Page CMD Response : %s", writePageRes.c_str());
								}
							}

						}// if (this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage == cmd_need_change_page)

						/*-------------------- Polling Each Command --------------------*/

						iteration++;

						// Update DataView Register Field Icon
						this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_running;
						//this->m_dataViewListCtrl->get()->RowValueChanged(idx, PMBUSCMDListModel::Col_RegisterIconText);

						// Prepare Send Buffer
						uartSendDataLength = this->productSendBuff(idx, this->m_pmBusCommand[idx].m_register, this->m_pmBusCommand[idx].m_responseDataLength);

						PSU_DEBUG_PRINT(MSG_DEBUG, "Prepare To Send");
						// Sleep Polling Time
						Sleep(*this->m_pollingTime);//this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);


						retry = 0;
						do {
							// Decide Send Data Length
							if (*this->m_CurrentIO == IOACCESS_SERIALPORT){
								if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
									sendDataLength = uartSendDataLength;// SERIAL_SEND_DATA_SIZE;
								}
								else if (this->m_pmBusCommand[idx].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
									sendDataLength = uartSendDataLength;// SERIAL_SEND_DATA_SIZE + this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalDataLength;//2;
								}
							}
							else{// HID
								sendDataLength = HID_SEND_DATA_SIZE;
							}

							PSU_DEBUG_PRINT(MSG_DEBUG, "Send Data Length =%d", sendDataLength);

							// Send Data
							sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(this->m_sendBuff, sendDataLength);
							if (sendResult <= 0){
								PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
								// Retry 
								retry++;
								if (retry >= 3){
									PSU_DEBUG_PRINT(MSG_DEBUG, "Still Send Failed, Retry Times = %d", retry);
									sendRetryStillFailed = true;
									break;
								}
								else{
									PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
								}

							}
							else{
#ifdef OUTPUT_SEND_DATA
								wxString sentData(wxT("Sent Data : "));
								for (int idx = 0; idx < sendDataLength; idx++){
									sentData += wxString::Format(" %02x ", this->m_sendBuff[idx]);
								}
								PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sentData.c_str());
#endif
								PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
							}

						} while (sendResult <= 0);

						if (sendRetryStillFailed == true){
							PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Send Still Failed, Exit Send Thread");
							m_running = false;
							break;
						}

						// Create IOPortReadCMDThread
						unsigned int bytesToRead = this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH;
						this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_IOAccess, this->m_CurrentIO, this->m_rxTxSemaphore, &this->m_pmBusCommand[idx], this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, bytesToRead);

						// If Create Thread Success
						if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
							PSU_DEBUG_PRINT(MSG_ERROR, "Can't create read thread!");
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

							if (this->m_recvBuff->m_length == 0){
								PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length = %d, CMD = %02xH", this->m_recvBuff->m_length, this->m_pmBusCommand[idx].m_register);
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
									//success++;

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

#ifdef OUTPUT_RECEIVE_DATA
									wxString recvBytes("");
									for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
										recvBytes += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
									}

									PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Bytes : %s", recvBytes.c_str());

#endif

#ifdef PRINT_RAW_IN_FEILD
									wxString RawMsg("");
									for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
										RawMsg += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
									}
#else
									wxString RawMsg(RawStr);
#endif

									// Update Data View Model Raw Field
									//wxVariant variantRaw;
									//variantRaw = RawMsg;

									// Check I2C BUS Not Acknowledge
									unsigned char i2cBusAck = PMBUSHelper::IsI2CBusNotAcknowlwdge(this->m_CurrentIO, this->m_recvBuff->m_recvBuff, this->m_recvBuff->m_length);
									if (i2cBusAck == PMBUSHelper::response_ng){
										this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_i2c_bus_not_acknowledge;
										wxString NoAckStr("I2C BUS Not Acknowledge");
										RawMsg = NoAckStr;
									}

									if (this->m_pmBusCommand[idx].m_cmdStatus.m_status != cmd_status_checksum_error && this->m_pmBusCommand[idx].m_cmdStatus.m_status != cmd_status_i2c_bus_not_acknowledge){
										this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_success;
										success++;
									}
									PSU_DEBUG_PRINT(MSG_DETAIL, "idx = %d", idx);

									wxThreadEvent* threadraw_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_RAW);
									threadraw_evt->SetInt(idx);
									threadraw_evt->SetString(RawMsg);
									wxQueueEvent(m_pHandler->GetEventHandler(), threadraw_evt);

									//this->m_dataViewListCtrl->get()->SetValueByRow(variantRaw, idx, PMBUSCMDListModel::Col_RawText);
									//this->m_dataViewListCtrl->get()->RowValueChanged(idx, PMBUSCMDListModel::Col_RawText);

									PSU_DEBUG_PRINT(MSG_DEBUG, "%s", RawMsg.c_str());

									bool updateQuery = true;
									bool updateCoefficients = true;

									if (this->m_pmBusCommand[idx].m_cmdStatus.m_status == cmd_status_success){
										// Call Cook Data CB Function
										memset(CookStr, 0, STR_LENGTH);
										this->m_pmBusCommand[idx].m_cmdCBFunc.m_cookCBFunc(&(this->m_pmBusCommand[idx]), CookStr, this->m_pmBusCommand[idx].m_responseDataLength);

										// Update Data View Model Cook Field
										wxString CookMsg(CookStr);

										//wxVariant variantCook;
										//variantCook = CookMsg;

										wxThreadEvent* threadcook_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_COOK);
										threadcook_evt->SetInt(idx);
										threadcook_evt->SetString(CookMsg);
										wxQueueEvent(m_pHandler->GetEventHandler(), threadcook_evt);

										//this->m_dataViewListCtrl->get()->SetValueByRow(variantCook, idx, PMBUSCMDListModel::Col_CookText);
										//this->m_dataViewListCtrl->get()->RowValueChanged(idx, PMBUSCMDListModel::Col_CookText);

										PSU_DEBUG_PRINT(MSG_DEBUG, "%s", CookMsg.c_str());

										// If this is Query Command(0x1A), Update Query Filed
										if (this->m_pmBusCommand[idx].m_register == 0x1A){
											
											// Get Query CMD
											int queryCMD;
											queryCMD = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[1];

											// Get Index of Query CMD 
											int queryCMDIndex = -1;

											/* In Polling Each Command Section, The Secondary Parameter of getIndexOfCMD function should be
											"The Page of Query CMD not 'this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage' due to 'idx' is 0x1A's idx"
											*/
											queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

                                            #if 0
											for (int idx2 = 0; idx2 < (signed)PMBUSHelper::CurrentCMDTableSize; idx2++){
												if (PMBUSHelper::getPMBUSCMDData()[idx2].m_register == queryCMD){
													queryCMDIndex = idx2;
													break;
												}
											}
                                            #endif

											if (queryCMDIndex < 0){
												PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
												updateQuery = false;
											}
											
											if (updateQuery == true){
												// Call Query Data CB Function
												memset(QueryStr, 0, STR_LENGTH);
												                                                                                                      // CMD's Page
												this->m_pmBusCommand[queryCMDIndex].m_cmdCBFunc.m_queryCBFunc(&(this->m_pmBusCommand[idx]), QueryStr, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

												wxString QueryMsg(QueryStr);

												wxThreadEvent* threadquery_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_QUERY);
												threadquery_evt->SetInt(queryCMDIndex);
												threadquery_evt->SetString(QueryMsg);
												wxQueueEvent(m_pHandler->GetEventHandler(), threadquery_evt);

												PSU_DEBUG_PRINT(MSG_DEBUG, "%s", QueryMsg.c_str());
											}

										}// if (this->m_pmBusCommand[idx].m_register == 0x1A)

										// If this is Coefficients Command(0x30), Update Coefficients Filed
										if (this->m_pmBusCommand[idx].m_register == 0x30){

											// Get Query CMD
											int queryCMD;
											queryCMD = this->m_pmBusCommand[idx].m_cmdStatus.m_AddtionalData[1];

											// Get Index of Query CMD 
											int queryCMDIndex = -1;

											/* In Polling Each Command Section, The Secondary Parameter of getIndexOfCMD function should be
											   "The Page of Query CMD not 'this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage' due to 'idx' is 0x1A's idx"
											*/
											queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

                                            #if 0
											for (int idx3 = 0; idx3 < (signed)PMBUSHelper::CurrentCMDTableSize; idx3++){
												if (PMBUSHelper::getPMBUSCMDData()[idx3].m_register == queryCMD){
													queryCMDIndex = idx3;
													break;
												}
											}
                                            #endif

											if (queryCMDIndex < 0){
												PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
												updateCoefficients = false;
											}

											if (updateCoefficients == true){
												// Call Query Data CB Function
												memset(CoefficientsStr, 0, STR_LENGTH);
												                                                                                                                    // CMD's Page
												this->m_pmBusCommand[queryCMDIndex].m_cmdCBFunc.m_coefficientsCBFunc(&(this->m_pmBusCommand[idx]), CoefficientsStr, this->m_pmBusCommand[idx].m_cmdStatus.m_cmdPage);

												wxString CoefficientsMsg(CoefficientsStr);

												wxThreadEvent* threadcoefficients_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS);
												threadcoefficients_evt->SetInt(queryCMDIndex);
												threadcoefficients_evt->SetString(CoefficientsMsg);
												wxQueueEvent(m_pHandler->GetEventHandler(), threadcoefficients_evt);

												PSU_DEBUG_PRINT(MSG_DEBUG, "%s", CoefficientsMsg.c_str());
											}

										}// if (this->m_pmBusCommand[idx].m_register == 0x30)
									}

								}
								//
								else{
									PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length Don't As Expected CMD=%d, Length=%d(ExpectReceiveDataLength=%d)", this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length, ExpectReceiveDataLength);
									// 0d  0a  4e  47  0d  0a : May Receive Response as left when I2C Slave Address was wrong
									
									wxString receive("");
									for (unsigned int index = 0; index < this->m_recvBuff->m_length; index++){
										receive += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[index]);
									}
									PSU_DEBUG_PRINT(MSG_DEBUG, "%s", receive.c_str());

									this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_failure;

									if (this->m_recvBuff->m_recvBuff[2] == 0x4e && this->m_recvBuff->m_recvBuff[3] == 0x47) {
										wxString NotFoundMsg(wxT("(I2C BUS Not Acknowledge)"));
										this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_i2c_bus_not_acknowledge;
										//wxVariant variantNotFound = NotFoundMsg;

										wxThreadEvent* threadraw_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_RAW);
										threadraw_evt->SetInt(idx);
										threadraw_evt->SetString(NotFoundMsg);
										wxQueueEvent(m_pHandler->GetEventHandler(), threadraw_evt);

										//this->m_dataViewListCtrl->get()->SetValueByRow(variantNotFound, idx, PMBUSCMDListModel::Col_RawText);
										//this->m_dataViewListCtrl->get()->RowValueChanged(idx, PMBUSCMDListModel::Col_RawText);
									}

									if (this->m_appSettings->m_runMode == RunMode_StopAnError){
										m_running = false;
										break;
									}
								}
							}
						} // else if (ret != wxSEMA_NO_ERROR)

						//Sleep(this->m_pollingTime - 20);////this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);

					} // if (this->m_pmBusCommand[idx].m_access != cmd_access_write)
				}// if (this->m_pmBusCommand[idx].m_toggle == true)
				else{
					// Don't Do Polling So fast
					//continue;
				}

				/*-------------------- Send if user issue send CMD on write page when monitor is running  --------------------*/
				if (this->m_sendCMDVector->size() > 0){

					vector<PMBUSSendCOMMAND_t>::iterator sendCMDVector_Iterator;

					for (sendCMDVector_Iterator = this->m_sendCMDVector->begin(); sendCMDVector_Iterator != this->m_sendCMDVector->end(); sendCMDVector_Iterator++)
					{

						retry = 0;
						do {
							// Send Data
							sendResult = this->m_IOAccess[*this->m_CurrentIO].m_DeviceSendData(sendCMDVector_Iterator->m_sendData, sendCMDVector_Iterator->m_sendDataLength);
							if (sendResult <= 0){
								PSU_DEBUG_PRINT(MSG_ERROR, "IO Send Separate Write CMD Failed, sendResult=%d", sendResult);
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
							PSU_DEBUG_PRINT(MSG_ERROR, "Can't create thread! (Separate)");
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

							if (this->m_appSettings->m_runMode == RunMode_StopAnError){
								m_running = false;
								break;
							}
						}

					}// for (sendCMDVector_Iterator = this->m_sendCMDVector->begin(); sendCMDVector_Iterator != this->m_sendCMDVector->end(); sendCMDVector_Iterator++)

					// Clear Vector 
					this->m_sendCMDVector->clear();
				
				}//if (this->m_sendCMDVector->size() > 0)
				
				/*--------------------------------------------------------------------------------------------------------------*/
				
				// Set Monitoring Name / Monitoring Summary of Status Bar
				wxString monitor("Monitoring...[");
				wxString cmd(wxString::Format("%02x", this->m_pmBusCommand[idx].m_register).Upper());
				wxString hex("h]");
				//this->m_status_bar->setMonitoringCMDName(monitor + cmd + hex);

				wxThreadEvent* threadCMDName_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_CMDNAME);
				threadCMDName_evt->SetString(monitor + cmd + hex);
				wxQueueEvent(m_pHandler->GetEventHandler(), threadCMDName_evt);

				wxString summary(wxString::Format("Iteration:%ld,Success:%ld,Timeout:%ld", iteration, success, timeout));
				//this->m_status_bar->setMonitoringSummary(summary);
				wxThreadEvent* threadSummary_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_SUMMARY);
				threadSummary_evt->SetString(summary);
				wxQueueEvent(m_pHandler->GetEventHandler(), threadSummary_evt);

#if 0
				if (idx == (PMBUSHelper::GetCurrentCMDTableSize() - 1)){
					// Update StdPage
					this->UpdateSTDPage();
				}
#endif

				// Update STD Page
				this->UpdateSTDPage(idx);

				// Update Status Panel
				this->UpdateSTATUSPanel(idx);


				if (this->m_appSettings->m_runMode == RunMode_Iterations){

					this->m_appSettings->m_IterationsValue = wxAtoi(this->m_pHandler->m_iteration_input->GetValue());

					if (iteration >= this->m_appSettings->m_IterationsValue){
						PSU_DEBUG_PRINT(MSG_ALERT, "IterationsSettingValue : %d, iteration : %d", this->m_appSettings->m_IterationsValue, iteration);
						this->m_running = false;
						break;// for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++) 
					}
				}

			}//for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++)
		
		} //while(m_running && this->TestDestroy()==false)

		//this->m_status_bar->getGauge()->SetValue(0);

		break;

	default:

		break;
	}

#if 0
	// If Send Failed, Close I/O Port
	if(sendRetryStillFailed==true){
		// Close Device
		if (this->m_IOAccess[*this->m_CurrentIO].m_GetDeviceStatus() == IODEVICE_OPEN){
			this->m_IOAccess[*this->m_CurrentIO].m_CloseDevice();
		}
	}
#endif

	// Emit Thread Completed Event 
	wxThreadEvent* threadFinish_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_COMPLETED);
	threadFinish_evt->SetInt(sendRetryStillFailed == true ? TRUE : FALSE);
	wxQueueEvent(m_pHandler->GetEventHandler(), threadFinish_evt);
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread finished.");

	return (wxThread::ExitCode)1;
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

void IOPortSendCMDThread::UpdateSTDPage(unsigned int index){
	
	// PIN
	if (index == this->findPMBUSCMDIndex(0x97)){
		wxString pin = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_PIN);
		this->m_stdPage->m_tcPIN->SetValue(pin);
	}
	
	// POUT
	if (index == this->findPMBUSCMDIndex(0x96)){
		wxString pout = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_POUT);
		this->m_stdPage->m_tcPOUT->SetValue(pout);
	}

	// VIN
	if (index == this->findPMBUSCMDIndex(0x88)){
		wxString vin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VIN);
		this->m_stdPage->m_tcVIN->SetValue(vin);
	}

	// IIN
	if (index == this->findPMBUSCMDIndex(0x89)){
		wxString iin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IIN);
		this->m_stdPage->m_tcIIN->SetValue(iin);
	}

	// VOUT
	if (index == this->findPMBUSCMDIndex(0x8b,0)){
		wxString vout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VOUT);
		this->m_stdPage->m_tcVOUT->SetValue(vout);
	}

	// IOUT
	if (index == this->findPMBUSCMDIndex(0x8c, 0)){
		wxString iout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IOUT);
		this->m_stdPage->m_tcIOUT->SetValue(iout);
	}

	// VoSBY
	if (index == this->findPMBUSCMDIndex(0x8b, 1)){
		wxString vosby = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VoSBY);
		this->m_stdPage->m_tcVoSBY->SetValue(vosby);
	}

	// IoSBY
	if (index == this->findPMBUSCMDIndex(0x8c, 1)){
		wxString iosby = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IoSBY);
		this->m_stdPage->m_tcIoSBY->SetValue(iosby);
	}

	// VCAP
	if (index == this->findPMBUSCMDIndex(0x8a)){
		wxString vcap = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_VCAP);
		this->m_stdPage->m_tcVCAP->SetValue(vcap);
	}

	// AMD(8D)
	if (index == this->findPMBUSCMDIndex(0x8d)){
		wxString amd_8d = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_AMD_8D);
		this->m_stdPage->m_tcAMD8D->SetValue(amd_8d);
	}

	// SEC(8E)
	if (index == this->findPMBUSCMDIndex(0x8e)){
		wxString sec_8e = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_SEC_8E);
		this->m_stdPage->m_tcSEC8E->SetValue(sec_8e);
	}

	// PRI(8F)
	if (index == this->findPMBUSCMDIndex(0x8f)){
		wxString pri_8f = wxString::Format("%4.2f", (double)PMBUSHelper::GetPMBusStatus()->m_PRI_8F);
		this->m_stdPage->m_tcPRI8F->SetValue(pri_8f);
	}

	// FAN1
	if (index == this->findPMBUSCMDIndex(0x90)){
		wxString fan1 = wxString::Format("%-5.1f", (double)PMBUSHelper::GetPMBusStatus()->m_FAN1);
		this->m_stdPage->m_tcFAN1->SetValue(fan1);
	}

	// FAN2

	// FAN3

	// FAN4

}

unsigned int IOPortSendCMDThread::findPMBUSCMDIndex(unsigned int cmd_register, unsigned char need_changePage){

	unsigned int index = 0;

	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		if (this->m_pmBusCommand[idx].m_register == cmd_register)
		{
			if (this->m_pmBusCommand[idx].m_cmdStatus.m_NeedChangePage == need_changePage){
				index = idx;
				break;
			}
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