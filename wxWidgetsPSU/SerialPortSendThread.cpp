/**
* @file SerialPortSendThread.cpp
*/

#include "SerialPortSendThread.h"
#include "SerialPort.h"

SerialSendThread::SerialSendThread(wxSemaphore* semaphore){
	this->m_rxTxSemaphore = semaphore;
}

SerialSendThread::SerialSendThread(wxSemaphore* semaphore, unsigned int runMode, unsigned int pollingTime, PMBUSCOMMAND_t *pmBusCommand, RECVBUFF_t *recvBuff, wxObjectDataPtr<PSUDataViewListModel> *dataViewListModel){
	this->m_rxTxSemaphore = semaphore;
	this->m_runMode = runMode;
	this->m_pollingTime = pollingTime;
	this->m_pmBusCommand = pmBusCommand;
	this->m_recvBuff = recvBuff;
	this->m_dataViewListCtrl = dataViewListModel;
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

wxThread::ExitCode SerialSendThread::Entry()
{
	int ret;
	
	PSU_DEBUG_PRINT("In Send Data Thread ");
	PSU_DEBUG_PRINT("Thread started (priority = %u).", GetPriority());
	PSU_DEBUG_PRINT("m_pollingTime=%d", this->m_pollingTime);
	m_running = true;

	switch (this->m_runMode){

	case RunMode_Iteration:

		break;

	case RunMode_Continally:
		// RunMode is Continally 
		PSU_DEBUG_PRINT("RunMode is Continally ");
		while (m_running){

			for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++){
				if (this->m_pmBusCommand[idx].m_toggle == true){// If toggle is enable
					
					this->productSendBuff(this->m_pmBusCommand[idx].m_register, this->m_pmBusCommand[idx].m_responseDataLength);

					SerialSendData(this->m_sendBuff, CMD_DATA_SIZE);

					// Create SerialReadThread
					this->m_serialPortReadCommandThread = new SerialReadThread(this->m_rxTxSemaphore, this->m_pmBusCommand, this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE);

					// If Create Thread Success
					if (this->m_serialPortReadCommandThread->Create() != wxTHREAD_NO_ERROR){
						wxLogError(wxT("Can't create thread!"));
					}
					else{
						this->m_serialPortReadCommandThread->Run();
					}

					// Semaphore Wait for Read Thread Complete
					PSU_DEBUG_PRINT("Semaphore WaitTimeout : Is Semaphore OK %d", m_rxTxSemaphore->IsOk());
					ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
					if (ret != wxSEMA_NO_ERROR){
						PSU_DEBUG_PRINT("%s: Semaphore wait timout occurs : error = %d", __FUNCTIONW__, ret);
					}
					else{
						PSU_DEBUG_PRINT("%s: Receive Data of CMD %2x, Length = %d", __FUNCTIONW__, this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length);
						wxLogMessage("%s: Receive Data of CMD %2x, Length = %d", __FUNCTIONW__, this->m_pmBusCommand[idx].m_register, this->m_recvBuff->m_length);
						// copy data to PMBus Command Structure
						this->m_pmBusCommand[idx].m_recvBuff.m_length = this->m_recvBuff->m_length;
						for (unsigned int idx2 = 0; idx2 < this->m_recvBuff->m_length; idx2++){
							this->m_pmBusCommand[idx].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff->m_recvBuff[idx2];
							PSU_DEBUG_PRINT("%s: %d,%d", __FUNCTIONW__, this->m_pmBusCommand[idx].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff->m_recvBuff[idx2]);
						}

						wxString outputMsg("");
						outputMsg += wxString::Format("%s:", __FUNCTIONW__);
						for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
							outputMsg += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
						}

						// Update Data View Model
						wxVariant variant;
						variant = outputMsg;

						wxLogMessage("%s: idx = %d", __FUNCTIONW__, idx);
						this->m_dataViewListCtrl->get()->SetValueByRow(variant, idx, PSUDataViewListModel::Col_RawText);
						this->m_dataViewListCtrl->get()->RowValueChanged(idx, PSUDataViewListModel::Col_RawText);

						PSU_DEBUG_PRINT(outputMsg.c_str());
					}

					Sleep(this->m_pollingTime);////this->m_pollingTime - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);// Sleep
				}
				else{
					continue;
				}
			}
		} //while(m_running)

		break;

	case RunMode_StopAnError:

		break;

	default:

		break;
	}

	return NULL;
}