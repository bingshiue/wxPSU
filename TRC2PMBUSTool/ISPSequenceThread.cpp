/**
 * @file ISPSequenceThread.cpp
 */
#include "ISPSequenceThread.h"

ISPSequenceThread::ISPSequenceThread
(
	wxString hexFilePath,
	TIHexFileParser* tiHexFileStat,
	IOACCESS*    ioaccess,
	unsigned int* currentIO,
	unsigned char target,
	unsigned long developerMode,
	wxEvtHandler* evtHandlerMain,
	wxEvtHandler* evtHandler,
	unsigned char* ispStatus,
	wxProgressDialog *progressDialog
	) : wxThread(wxTHREAD_JOINABLE)
{
	this->m_hexFilePath = hexFilePath;

	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ioaccess = ioaccess;

	this->m_currentIO = currentIO;

	this->m_target = target;

	this->m_developerMode = developerMode;

	this->m_evtHandlerMain = evtHandlerMain;

	this->m_evtHandler = evtHandler;

	this->m_ispStatus = ispStatus;

	this->m_progressDialog = progressDialog;

	tiHexFileStat->begin();
	this->m_startAddress = tiHexFileStat->currentAddress();

	tiHexFileStat->end();
	this->m_endAddress = tiHexFileStat->currentAddress();

	this->m_addressRange = (this->m_endAddress - this->m_startAddress) + 1UL;

	this->m_dataBytes = tiHexFileStat->size() * 2;
}

ISPSequenceThread::~ISPSequenceThread(){

}

unsigned int ISPSequenceThread::ProductSendBuffer(unsigned char* buffer){
	// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xF0, this->m_target, 0x00, 0x0D, 0x0A
	unsigned int active_index = 0;

	switch (*this->m_currentIO){

	case IOACCESS_SERIALPORT:
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;

	case IOACCESS_HID:
		buffer[active_index++] = 0x05;
		buffer[active_index++] = 0x08;
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;

	case IOACCESS_PICKIT:
		
		// 0x03 [0x06] 0x81 0x84 [0x05] [0xB6] [0xEC] [0x00] [0x08] [0xE0] 0x82 0x1f 0x77
		buffer[active_index++] = 0x00;
		buffer[active_index++] = 0x03;
		buffer[active_index++] = 0x00; // Total Length, Detemine Later
		buffer[active_index++] = 0x81;
		buffer[active_index++] = 0x84;
		buffer[active_index++] = 1 + 3;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target

		// Compute PEC
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 6, 3);

		// Fill Last 3
		buffer[active_index++] = 0x82;
		buffer[active_index++] = 0x1f;
		buffer[active_index++] = 0x77;

		// Fill Total Length
		buffer[2] = active_index - 3;

		break;

	case IOACCESS_TOTALPHASE:

		buffer[active_index++] = 2; // Write Bytes
		buffer[active_index++] = 0; // Read Bytes
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();
		buffer[active_index++] = PMBUSHelper::getFWUploadModeCMD(); // FW Upload Mode Command
		buffer[active_index++] = this->m_target; // Target;
		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 2, 3); // PEC

		// Update Write Bytes For Write CMD
		buffer[0] = active_index - 3;

		break;


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;
}

#define CMD_F0H_BYTES_TO_READ  6/**< Bytes To Read */
wxThread::ExitCode ISPSequenceThread::Entry() {

	PSU_DEBUG_PRINT(MSG_DEBUG, "Start Address = %x", this->m_startAddress);
	PSU_DEBUG_PRINT(MSG_DEBUG, "End Address   = %x", this->m_endAddress);
	PSU_DEBUG_PRINT(MSG_DEBUG, "Address Range = %d", this->m_addressRange);
	PSU_DEBUG_PRINT(MSG_DEBUG, "Data Bytes    = %d", this->m_dataBytes);

	/*** Prpare Send Data Buffer ***/
	unsigned char SendBuffer[64];
	unsigned int sendDataLength = this->ProductSendBuffer(SendBuffer);

	PMBUSSendCOMMAND_t CMDF0H;

	CMDF0H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMDF0H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_F0H_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_F0H_BYTES_TO_READ : CMD_F0H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMDF0H.m_sendData[idx] = SendBuffer[idx];
	}

	/*** Jump To Start Address of Hex File ***/
	this->m_tiHexFileStat->begin();

	/*** Initialize ISP related Parameters ***/
	*m_ispStatus = ISP_Status_VerifyBeforeStart;//ISP_Status_InProgress;
	double percentage = 0;
	wxString information("");
	//int not_cancel;
	bool inProcess = true;
	unsigned char header_index = 0;
	unsigned int try_end = 0;


	/*** Create SendISPStartCMD Task ***/
	new(TP_SendISPStartCMDTask) SendISPStartCMDTask(m_ioaccess, m_currentIO, CMDF0H, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);

	while (inProcess) {
		information = wxString(wxT(""));

		if (*m_ispStatus == ISP_Status_InProgress || *m_ispStatus == ISP_Status_VerifyBeforeStart){
			// 
		}
		else if (*m_ispStatus == ISP_Status_ALLDone){

			information = wxT("ISP Progress Complete");

			information += wxT("\n");
		}


		// Show Current Address
		unsigned long currentAddress = this->m_tiHexFileStat->currentAddress();

#if ONLY_ENABLE_ISP_RUNIN_TEST_IN_DEVELOP_MODE == TRUE
		if (PMBUSHelper::runInMode == Generic_Enable)
		{
#endif
			if (PMBUSHelper::runInMode == Generic_Enable){
				information += wxString::Format("Run In Remain Times : %d", PMBUSHelper::runInTimes);
				information += wxT("\n");
			}

#if ONLY_ENABLE_ISP_RUNIN_TEST_IN_DEVELOP_MODE == TRUE
		}
#endif


		if (this->m_developerMode == Generic_Enable)
		{			
			information += wxString::Format("Current Process Address : %08x", currentAddress);
			information += wxT("\n");
		}

		// Show Processed Bytes
		unsigned long processed_bytes = ((currentAddress - this->m_startAddress) + 1UL) * 2;
		information += wxString::Format("Current Processed Bytes : (%d/%d)(%.2f%%)", processed_bytes, this->m_dataBytes, ((float)processed_bytes / (float)this->m_dataBytes) * 100);

		// Compute Percentage (Percentage = processed bytes / total bytes)
		percentage = ((double)processed_bytes / this->m_dataBytes);
		percentage *= 100;
		if (percentage >= 100) {


			while (Task::GetCount() != 0){
				PSU_DEBUG_PRINT(MSG_DEBUG, "Wait for DSP Reboot");
				wxMilliSleep(200);
			}

			if ((*m_ispStatus & 0xff) <= 0x02){
				
				if (PMBUSHelper::runInMode == Generic_Enable && --PMBUSHelper::runInTimes > 0){
					
					//PMBUSHelper::runInTimes--;

					// Restart ISP Sequence
					/*** Jump To Start Address of Hex File ***/
					this->m_tiHexFileStat->begin();

					/*** Initialize ISP related Parameters ***/
					*m_ispStatus = ISP_Status_VerifyBeforeStart;//ISP_Status_InProgress;
					percentage = 0;

					/*** Create SendISPStartCMD Task ***/
					new(TP_SendISPStartCMDTask) SendISPStartCMDTask(m_ioaccess, m_currentIO, CMDF0H, this->m_tiHexFileStat, this->m_ispStatus, this->m_target);

					//
				}
				else {
					percentage = 100;
					information = wxT("ISP Progress Complete");
					information += wxT("\n");

					if (this->m_developerMode == Generic_Enable){
						information += wxString::Format("Current Process Address : %08x", currentAddress);
						information += wxT("\n");
					}

					information += wxString::Format("Current Processed Bytes : (%d/%d)(%.2f%%)", processed_bytes, this->m_dataBytes, ((float)processed_bytes / (float)this->m_dataBytes) * 100);
				}
			}
			else{
				percentage = 99; // Error occurs, set percentage less than 100 
			}
		}

		if (*m_ispStatus == ISP_Status_UserRequestCancel){
			// If User Request Cancel
			break;
		}

		//PSU_DEBUG_PRINT(MSG_DETAIL, "Percentage = %f, Processed bytes = %d, data bytes = %d, Current Address = %08x", percentage, processed_bytes, this->m_dataBytes, currentAddress);
		//PSU_DEBUG_PRINT(MSG_ALERT, "Percentage = %.2f%%", percentage);

		wxThreadEvent* threadISPSequenceUpdateEvt;

		threadISPSequenceUpdateEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_ISP_SEQUENCE_UPDATE);
		threadISPSequenceUpdateEvt->SetInt((int)percentage);
		threadISPSequenceUpdateEvt->SetString(information);
		wxQueueEvent(this->m_evtHandler, threadISPSequenceUpdateEvt);
		

#if 0
		// Update Dialogs
		if (percentage < 100){
			//not_cancel = dialog.Update((int)percentage, information);
			not_cancel = m_progressDialog->Update((int)percentage, information);
		}

		if (not_cancel == false){
			*m_ispStatus = ISP_Status_UserRequestCancel;
		}
#endif

		// If Error Occurs
		if ((*m_ispStatus & 0xff) > 0x02) {

			// Flush Log
			//if (this->m_developerMode == Generic_Disable){
				wxLog::FlushActive();
			//}

			break;// while (inProcess)
		}

		// Check Still have Task
		if (Task::GetCount() == 0){
			try_end++;
			if (try_end >= 3){
				inProcess = false;
				try_end = 0;
			}
		}
		else{
			try_end = 0;
		}

		// Flush Log
		//if (this->m_developerMode == Generic_Disable){
			wxLog::FlushActive();
		//}

		wxMilliSleep(16);
	};

	//if (this->m_developerMode == Generic_Disable){
		// Restore Logger Target
		//wxLog::SetActiveTarget(oldLogger);
	//}

	wxThreadEvent* threadISPSequenceEndEvt;
	if (*m_ispStatus == ISP_Status_ALLDone){
		threadISPSequenceEndEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_ISP_SEQUENCE_END);
		wxQueueEvent(this->m_evtHandler, threadISPSequenceEndEvt);
	}

	// Send ISP Interrupt Event To Main Thread
	wxThreadEvent* threadISPInterrupt_evt;
	if ((*m_ispStatus & 0xff) > 0x02) {
		switch (*m_ispStatus){

		case ISP_Status_VerifyBeforeStart:
			// Verify Before Start

			break;

		case ISP_Status_UserRequestCancel:// User Cancel ISP
		case ISP_Status_SendDataFailed:
		case ISP_Status_ResponseDataError:
		case ISP_Status_RebootCheckError:

			//new(TP_ClearIOReadBufferTask) ClearIOReadBufferTask(this->m_ioaccess, this->m_currentIO);

			threadISPInterrupt_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT);
			threadISPInterrupt_evt->SetInt((int)*m_ispStatus);
			wxQueueEvent(this->m_evtHandler, threadISPInterrupt_evt);
			//wxQueueEvent(this->m_evtHandlerMain, threadISPInterrupt_evt);

			break;

		default:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Something Error Occurs, ispStatus = %02x", *m_ispStatus);
			break;

		}
	}

	return (wxThread::ExitCode)1;
}