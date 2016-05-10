/**
* @file SerialPortSendThread.cpp
*/

#include "SerialPortSendThread.h"
#include "SerialPort.h"

SerialSendThread::SerialSendThread(wxSemaphore* semaphore){
	this->m_rxTxSemaphore = semaphore;
}

SerialSendThread::SerialSendThread(wxSemaphore* semaphore, unsigned int* runMode, unsigned int* pollingTime, PMBUSCOMMAND_t *pmBusCommand, RECVBUFF_t *recvBuff, wxObjectDataPtr<PSUDataViewListModel> *dataViewListModel, PSUStatusBar *status_bar){
	this->m_rxTxSemaphore = semaphore;
	this->m_runMode = runMode;
	this->m_pollingTime = pollingTime;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_dataViewListCtrl = dataViewListModel;
	this->m_status_bar = status_bar;
}

SerialSendThread::~SerialSendThread() { }


void SerialSendThread::productSendBuff(unsigned int command, unsigned int responseDataLength){
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

#define BASE_RESPONSE_DATA_LENGTH  6
wxThread::ExitCode SerialSendThread::Entry()
{
	int ret;
	int sendResult = 0;
	DWORD iteration=0;
	DWORD success=0;
	DWORD timeout = 0;
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "In Send Data Thread ");
	PSU_DEBUG_PRINT(MSG_DEBUG, "Thread started (priority = %u).", GetPriority());
	PSU_DEBUG_PRINT(MSG_DETAIL, "m_pollingTime=%d", this->m_pollingTime);
	m_running = true;

	switch (*this->m_runMode){

	case RunMode_Iteration:

		break;

	case RunMode_Continally:
		// RunMode is Continally 
		PSU_DEBUG_PRINT(MSG_DEBUG, "RunMode is Continally ");
		while (m_running){

			for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE && m_running==true; idx++){
				if (this->m_pmBusCommand[idx].m_toggle == true){// If toggle is enable

					// Update DataView Register Field Icon
					this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_running;
					this->m_dataViewListCtrl->get()->RowValueChanged(idx, PSUDataViewListModel::Col_RegisterIconText);
	                
					// Prepare Send Buffer
					this->productSendBuff(this->m_pmBusCommand[idx].m_register, this->m_pmBusCommand[idx].m_responseDataLength);

					// Create SerialReadThread
					this->m_serialPortReadCommandThread = new SerialReadThread(this->m_rxTxSemaphore, this->m_pmBusCommand, this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH);

					// If Create Thread Success
					if (this->m_serialPortReadCommandThread->Create() != wxTHREAD_NO_ERROR){
						wxLogError(wxT("Can't create thread!"));
					}
					else{
						this->m_serialPortReadCommandThread->Run();
					}

					// Sleep Polling Time
					Sleep(*this->m_pollingTime);////this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);

					// Send Data
					sendResult = SerialSendData(this->m_sendBuff, CMD_DATA_SIZE);
					if (sendResult < 0){
						PSU_DEBUG_PRINT(MSG_ALERT, "Serial Send Failed, sendResult=%d", sendResult);
					}

					// Semaphore Wait for Read Thread Complete
					PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout");
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
							//
							if (this->m_recvBuff->m_length == (this->m_pmBusCommand[idx].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH)){

								PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data of CMD %2x, Length = %d", this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length);
								success++;

								// copy data to PMBus Command Structure
								this->m_pmBusCommand[idx].m_recvBuff.m_length = this->m_recvBuff->m_length;
								for (unsigned int idx2 = 0; idx2 < this->m_recvBuff->m_length; idx2++){
									this->m_pmBusCommand[idx].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff->m_recvBuff[idx2];
									PSU_DEBUG_PRINT(MSG_DETAIL, "%d,%d", this->m_pmBusCommand[idx].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff->m_recvBuff[idx2]);
								}

								wxString outputMsg("");
								outputMsg += wxString::Format("%s:", __FUNCTIONW__);
								for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
									outputMsg += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
								}

								// Update Data View Model Raw Field
								wxVariant variant;
								variant = outputMsg;

								this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_success;
								PSU_DEBUG_PRINT(MSG_DETAIL, "idx = %d", idx);
								this->m_dataViewListCtrl->get()->SetValueByRow(variant, idx, PSUDataViewListModel::Col_RawText);
								this->m_dataViewListCtrl->get()->RowValueChanged(idx, PSUDataViewListModel::Col_RawText);

								PSU_DEBUG_PRINT(MSG_DETAIL, "%s", outputMsg.c_str());
							}
							//
							else{
								PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length Not As Expected CMD=%d, Length=%d", this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length);
								this->m_pmBusCommand[idx].m_cmdStatus.m_status = cmd_status_failure;
							}
						}
					}

					//Sleep(this->m_pollingTime - 20);////this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
				}
				else{
					continue;
				}

				// Set Monitoring Name / Monitoring Summary of Status Bar
				wxString monitor("Monitoring...[");
				wxString cmd(wxString::Format("%2x", this->m_pmBusCommand[idx].m_register).Upper());
				wxString hex("h]");
				this->m_status_bar->setMonitoringCMDName(monitor + cmd + hex);

				iteration++;
				wxString summary(wxString::Format("Iteration:%ld,Success:%ld,Timeout:%ld", iteration, success, timeout));
				this->m_status_bar->setMonitoringSummary(summary);

			}//for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++)
		} //while(m_running)

		break;

	case RunMode_StopAnError:

		break;

	default:

		break;
	}

	return NULL;
}