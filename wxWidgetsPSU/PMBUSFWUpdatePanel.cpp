/**
 * @file PMBUSFWUpdatePanel.cpp
 */

#include "PMBUSFWUpdatePanel.h"

PMBUSFWUpdatePanel::PMBUSFWUpdatePanel(wxNotebook* parent, wxString hexFilePath, TIHexFileParser tiHexFileStat, IOACCESS* ioaccess, unsigned int* currentIO, bool* isMonitorRunning, unsigned char target, unsigned long developerMode) : wxPanel(parent) {

	this->m_parent = parent;

	this->m_hexFilePath = hexFilePath;
	
	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ioaccess = ioaccess;

	this->m_currentIO = currentIO;

	this->m_isMonitorRunning = isMonitorRunning;

	this->m_target = target;

	this->m_developerMode = developerMode;

	this->m_pressedCloseButton = false;

	tiHexFileStat.begin();
    this->m_startAddress = tiHexFileStat.currentAddress();

	tiHexFileStat.end();
	this->m_endAddress = tiHexFileStat.currentAddress();

	this->m_addressRange = (this->m_endAddress - this->m_startAddress) + 1UL;

	this->m_dataBytes = tiHexFileStat.size() * 2;

	this->m_dvlRowCount = (this->m_addressRange % 16 == 0) ? this->m_addressRange / 16 : (this->m_addressRange / 16) + 1;

	PSU_DEBUG_PRINT(MSG_DEBUG, "startAddress = 0x%08x", this->m_startAddress);
	PSU_DEBUG_PRINT(MSG_DEBUG, "EndAddress   = 0x%08x", this->m_endAddress);
	PSU_DEBUG_PRINT(MSG_DEBUG, "Address Range= %d", this->m_addressRange);
	PSU_DEBUG_PRINT(MSG_DEBUG, "Data Bytes   = %d", this->m_dataBytes);

	this->m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	this->m_statisticSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("File Description"));
	this->m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->m_fileStatFGS = new wxFlexGridSizer(2, 8, 5, 5);

	// File Name
	wxString fileName = wxT("File Path : ");
	fileName += this->m_hexFilePath;
	this->m_fileNameST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, fileName);
	wxFont font = this->m_fileNameST->GetFont();
	font.SetPointSize(10);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	this->m_fileNameST->SetFont(font);

	// Static Line
	this->m_st1 = new wxStaticLine(this->m_statisticSBS->GetStaticBox());
	this->m_st2 = new wxStaticLine(this->m_statisticSBS->GetStaticBox());
	//this->m_st3 = new wxStaticLine(this->m_statisticSBS->GetStaticBox());

	if (this->m_developerMode == Generic_Enable){

		// Start Address
		this->m_startAddressST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("START Address : "));
		this->m_startAddressST->SetFont(font);
		wxString StartAddress = wxString::Format("0x%08x", this->m_startAddress);
		this->m_startAddressTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, StartAddress);

		this->m_startAddressTC->SetEditable(false);

		this->m_endAddressST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("End Address : "));
		this->m_endAddressST->SetFont(font);
		wxString EndAddress = wxString::Format("0x%08x", this->m_endAddress);
		this->m_endAddressTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, EndAddress);

		this->m_endAddressTC->SetEditable(false);

		this->m_addressRangeST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("Address Range : "));
		this->m_addressRangeST->SetFont(font);
		wxString AddressRange = wxString::Format("%d", this->m_addressRange);
		this->m_addressRangeTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, AddressRange);

		this->m_addressRangeTC->SetEditable(false);

	}

	this->m_dataBytesST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("Data Bytes : "));
	this->m_dataBytesST->SetFont(font);
	wxString DataBytes = wxString::Format("%d", this->m_dataBytes);
	this->m_dataBytesTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, DataBytes);

	this->m_dataBytesTC->SetEditable(false);

	this->m_writeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_WRITE_BUTTON, wxT("WRITE"));
	this->m_writeButton->SetBitmap(wxBITMAP_PNG(MEMORY_32));

	this->m_closeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_CLOSE_BUTTON, wxT("CLOSE"));
	this->m_closeButton->SetBitmap(wxBITMAP_PNG(CLOSE_32));

	this->m_buttonSizer->Add(this->m_writeButton, wxSizerFlags(0).Border(wxALL));
	this->m_buttonSizer->Add(this->m_closeButton, wxSizerFlags(0).Border(wxALL));

	this->m_statisticSBS->Add(this->m_fileNameST, wxSizerFlags(0).Align(wxALIGN_CENTER).Border());

	this->m_statisticSBS->Add(this->m_st1, wxSizerFlags(0).Expand().Border(wxALL));

	if (this->m_developerMode == Generic_Enable){

		this->m_fileStatFGS->Add(this->m_startAddressST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
		this->m_fileStatFGS->Add(this->m_startAddressTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
		this->m_fileStatFGS->Add(this->m_endAddressST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
		this->m_fileStatFGS->Add(this->m_endAddressTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
		this->m_fileStatFGS->Add(this->m_addressRangeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
		this->m_fileStatFGS->Add(this->m_addressRangeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));

	}

	this->m_fileStatFGS->Add(this->m_dataBytesST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_dataBytesTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));

	this->m_statisticSBS->Add(this->m_fileStatFGS, wxSizerFlags(0).Align(wxALIGN_CENTER).Border());

	this->m_statisticSBS->Add(this->m_st2, wxSizerFlags(0).Expand().Border(wxALL));
	
	this->m_statisticSBS->Add(this->m_buttonSizer, wxSizerFlags(0).Align(wxALIGN_CENTER).Border());
	this->m_topLevelSizer->Add(this->m_statisticSBS, wxSizerFlags(0).Expand());

	if (this->m_developerMode == Generic_Enable){

		this->SetupHexMMAPDVL();

		this->m_topLevelSizer->Add(this->m_tiHexMMAPDVC, wxSizerFlags(1).Expand());


		// Setup Pop Up Menu
		this->m_popupMenu = new wxMenu();
		this->m_saveHexMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_SAVEHEX, wxT("Save Hex"), wxT("Save Hex"), wxITEM_NORMAL);

		this->m_saveHexMenuItem->SetBitmap(wxBITMAP_PNG(HEX_16));

		this->m_popupMenu->Append(this->m_saveHexMenuItem);
	}
	else{

		this->m_logTC = new PMBUSLogTextCtrl(this, wxID_ANY);

		this->m_topLevelSizer->Add(this->m_logTC, wxSizerFlags(1).Expand());
	}

	this->SetSizerAndFit(this->m_topLevelSizer);
}

PMBUSFWUpdatePanel::~PMBUSFWUpdatePanel(){

}

void PMBUSFWUpdatePanel::SetupHexMMAPDVL(void){

	this->m_tiHexMMAPDVC = new wxDataViewCtrl(this, ID_HEXMMAP_DVC, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	this->m_tiHexMMAPDVC->SetFont(font);

	this->m_tiHexMMAPModel = new TIHexMMAPModel(this->m_dvlRowCount, &this->m_tiHexFileStat);
	this->m_tiHexMMAPDVC->AssociateModel(this->m_tiHexMMAPModel.get());

	this->m_tiHexMMAPDVC->AppendTextColumn("ADDRESS", TIHexMMAPModel::Col_ADDRESS, wxDATAVIEW_CELL_ACTIVATABLE, 200, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("00H", TIHexMMAPModel::Col_00H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("01H", TIHexMMAPModel::Col_01H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("02H", TIHexMMAPModel::Col_02H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("03H", TIHexMMAPModel::Col_03H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("04H", TIHexMMAPModel::Col_04H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("05H", TIHexMMAPModel::Col_05H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("06H", TIHexMMAPModel::Col_06H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("07H", TIHexMMAPModel::Col_07H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("08H", TIHexMMAPModel::Col_08H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("09H", TIHexMMAPModel::Col_09H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0AH", TIHexMMAPModel::Col_0AH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0BH", TIHexMMAPModel::Col_0BH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0CH", TIHexMMAPModel::Col_0CH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0DH", TIHexMMAPModel::Col_0DH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0EH", TIHexMMAPModel::Col_0EH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0FH", TIHexMMAPModel::Col_0FH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("", TIHexMMAPModel::Col_ASCII, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
}

unsigned int PMBUSFWUpdatePanel::ProductSendBuffer(unsigned char* buffer){
	// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xF0, this->m_target, 0x00, 0x0D, 0x0A
	unsigned int active_index = 0;

	switch (*this->m_currentIO){

	case IOACCESS_SERIALPORT:
		buffer[active_index++] = 0x41;
		buffer[active_index++] = 0x54;
		buffer[active_index++] = PMBUSHelper::GetSlaveAddress();// Slave Address
		buffer[active_index++] = 0xF0; // CMD
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
		buffer[active_index++] = 0xF0; // CMD
		buffer[active_index++] = this->m_target; // Target

		buffer[active_index++] = PMBusSlave_Crc8MakeBitwise(0, 7, buffer + 4, 3); // PEC

		buffer[active_index++] = 0x0D;
		buffer[active_index++] = 0x0A;

		break;


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;
}


#define CMD_F0H_BYTES_TO_READ  6/**< Bytes To Read */
void PMBUSFWUpdatePanel::OnWriteButton(wxCommandEvent& event){

	wxLog* oldLogger = wxLog::GetActiveTarget();

	// Check if Monitor is Running
	if (*this->m_isMonitorRunning == true){
		wxMessageBox(wxT("Monitor is running, Please stop monitor then try again !"),
			wxT("Monitor is running !"),  // caption
			wxOK | wxICON_INFORMATION);

		return;
	}

	if (this->m_developerMode == Generic_Disable){
		// Change Logger Target
		wxLog::SetActiveTarget(this);
	}

	// Create Progress Dialog
	wxProgressDialog dialog(wxT("ISP is in Progress"),
		// "Reserve" enough space for the multiline
		// messages below, we'll change it anyhow
		// immediately in the loop below
		wxString(' ', 100) + "\n\n\n\n",
		100,    // range
		this,   // parent
		wxPD_CAN_ABORT |
		//wxPD_CAN_SKIP |
		wxPD_APP_MODAL |
		//wxPD_AUTO_HIDE | // -- try this as well
		wxPD_ELAPSED_TIME |
		//wxPD_ESTIMATED_TIME |
		//wxPD_REMAINING_TIME |
		wxPD_SMOOTH // - makes indeterminate mode bar on WinXP very small
		);

#if 0
	// Prepare Send Buffer
	unsigned char SendBuffer[8] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xF0, this->m_target, 0x00, 0x0D, 0x0A
	};

	unsigned char pec = 0;
	pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 3);

	SendBuffer[5] = pec;
#endif

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = this->ProductSendBuffer(SendBuffer);


	PMBUSSendCOMMAND_t CMDF0H;

	CMDF0H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMDF0H.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_F0H_BYTES_TO_READ : CMD_F0H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMDF0H.m_sendData[idx] = SendBuffer[idx];
	}

	this->m_tiHexFileStat.begin();
	unsigned char ispStatus = ISP_Status_VerifyBeforeStart;//ISP_Status_InProgress;
	double percentage = 0;
	wxString information("");

	new(TP_SendISPStartCMDTask)SendISPStartCMDTask(m_ioaccess, m_currentIO, CMDF0H, &this->m_tiHexFileStat, &ispStatus, this->m_target);

	int not_cancel;
	bool inProcess = true;
	unsigned char header_index = 0;
	unsigned int try_end = 0;

	// Wait for ISP Sequence End
	while (inProcess) {//Task::GetCount() > 0){

		if (ispStatus == ISP_Status_InProgress || ispStatus == ISP_Status_VerifyBeforeStart){

			// Header
			switch (header_index){

			case 0:
				information = wxString::Format("PC > - - - - - - - - - DSP");
				break;

			case 1:
				information = wxString::Format("PC - > - - - - - - - - DSP");
				break;

			case 2:
				information = wxString::Format("PC - - > - - - - - - - DSP");
				break;

			case 3:
				information = wxString::Format("PC - - - > - - - - - - DSP");
				break;

			case 4:
				information = wxString::Format("PC - - - - > - - - - - DSP");
				break;

			case 5:
				information = wxString::Format("PC - - - - - > - - - - DSP");
				break;

			case 6:
				information = wxString::Format("PC - - - - - - > - - - DSP");
				break;

			case 7:
				information = wxString::Format("PC - - - - - - - > - - DSP");
				break;

			case 8:
				information = wxString::Format("PC - - - - - - - - > - DSP");
				break;

			case 9:
				information = wxString::Format("PC - - - - - - - - - > DSP");
				break;

			default:
				PSU_DEBUG_PRINT(MSG_ALERT, "Something Error")
					break;
			}
			header_index++;
			header_index %= 10;

			information += wxT("\n");

		}
		else if (ispStatus == ISP_Status_ALLDone){

			information = wxT("ISP Progress Complete");

			information += wxT("\n");
		}


		// Show Current Address
		unsigned long currentAddress = this->m_tiHexFileStat.currentAddress();

		if (this->m_developerMode == Generic_Enable){
			information += wxString::Format("Current Process Address : %08x", currentAddress);
			information += wxT("\n");
		}

		// Show Processed Bytes
		unsigned long processed_bytes = ((currentAddress - this->m_startAddress) + 1UL) * 2;
		information += wxString::Format("Current Processed Bytes : (%d/%d)", processed_bytes, this->m_dataBytes);

		// Compute Percentage (Percentage = processed bytes / total bytes)
		percentage = ((double)processed_bytes / this->m_dataBytes);
		percentage *= 100;
		if (percentage >= 100) {


			while (Task::GetCount() != 0){
				PSU_DEBUG_PRINT(MSG_DEBUG, "Wait Until No Tasks");
				wxMilliSleep(200);
			}

			if ((ispStatus & 0xff) <= 0x02){
				percentage = 100;
				information = wxT("ISP Progress Complete");
				information += wxT("\n");
				information += wxString::Format("Current Process Address : %08x", currentAddress);
				information += wxT("\n");
				information += wxString::Format("Current Processed Bytes : (%d/%d)", processed_bytes, this->m_dataBytes);
			}
			else{
				percentage = 99; // Error occurs, set percentage less than 100 
			}
		}
		
		//PSU_DEBUG_PRINT(MSG_DETAIL, "Percentage = %f, Processed bytes = %d, data bytes = %d, Current Address = %08x", percentage, processed_bytes, this->m_dataBytes, currentAddress);
		PSU_DEBUG_PRINT(MSG_ALERT, "Percentage = %f%%", percentage);


		// Update Dialogs
		not_cancel = dialog.Update((int)percentage, information);

		if (not_cancel == false){
			ispStatus = ISP_Status_UserRequestCancel;
		}

		// If Error Occurs
		if ((ispStatus & 0xff) > 0x02) {

			// Flush Log
			if (this->m_developerMode == Generic_Disable){
				wxLog::FlushActive();
			}

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
		if (this->m_developerMode == Generic_Disable){
			wxLog::FlushActive();
		}

		wxMilliSleep(200);
	} // while (inProcess) 

	if (this->m_developerMode == Generic_Disable){
		// Restore Logger Target
		wxLog::SetActiveTarget(oldLogger);
	}

	// Send ISP Interrupt Event To Main Thread
	wxThreadEvent* threadISPInterrupt_evt;
	if ((ispStatus & 0xff) > 0x02) {
		switch (ispStatus){

		case ISP_Status_VerifyBeforeStart:
			// Verify Before Start

			break;

		case ISP_Status_UserRequestCancel:
			// User Cancel ISP

			break;

		case ISP_Status_SendDataFailed:
		case ISP_Status_ResponseDataError:
		case ISP_Status_RebootCheckError:

			threadISPInterrupt_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT);
			threadISPInterrupt_evt->SetInt((int)ispStatus);
			wxQueueEvent(this->m_parent->GetParent()->GetEventHandler(), threadISPInterrupt_evt);

			break;

		default:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Something Error Occurs, ispStatus = %02x", ispStatus);
			break;

		}
	}

}

void PMBUSFWUpdatePanel::OnCloseButton(wxCommandEvent& event){

	unsigned int selected_index;

	selected_index = this->m_parent->GetSelection();

	this->m_pressedCloseButton = true;

	this->m_parent->SetSelection(0);

	this->m_parent->RemovePage(selected_index);

}

void PMBUSFWUpdatePanel::OnPopUpMenu(wxDataViewEvent &event){
	// Show Pop Up Menu
	this->m_tiHexMMAPDVC->PopupMenu(this->m_popupMenu);
}

void PMBUSFWUpdatePanel::OnSaveHex(wxCommandEvent& event){
	// Save Current Hex Data As New File
	wxString SaveName(this->m_hexFilePath);
	SaveName.RemoveLast(4); // Remove ".hex"
	SaveName += wxT("-Filled");

	wxFileDialog SaveHexDialog(this, L"Save To", "", SaveName, "HEX files (*.hex)|*.hex", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	SaveHexDialog.Centre();

	// If the user changed idea...
	if (SaveHexDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	// Start Save Hex File
	wxString SavePath = SaveHexDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_DEBUG, "Save Hex To : %s", SavePath.c_str());

	// Create an output stream
	std::ofstream TIHexOutput;

	TIHexOutput.open(SavePath.c_str().AsChar(), ofstream::out);

	if (!TIHexOutput.good())
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Open %s", SavePath.c_str());
	}

	TIHexOutput << this->m_tiHexFileStat;

	if (this->m_tiHexFileStat.getNoWarnings() > 0 || this->m_tiHexFileStat.getNoErrors() > 0)
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Error or Warnings generated during decoding:");
		// Check Warnings
		while (this->m_tiHexFileStat.getNoErrors() > 0)
		{
			string error_message;

			this->m_tiHexFileStat.popNextError(error_message);

			PSU_DEBUG_PRINT(MSG_ERROR, "%s", error_message.c_str());

			wxMessageBox(wxT("Load Hex File Has Error"),
				wxT("Error !"),
				wxOK | wxICON_ERROR);

		}
		// Check Errors
		while (this->m_tiHexFileStat.getNoWarnings() > 0)
		{
			string warn_message;

			this->m_tiHexFileStat.popNextWarning(warn_message);

			PSU_DEBUG_PRINT(MSG_ERROR, "%s", warn_message.c_str());

			wxMessageBox(wxT("Load Hex File Has Warning"),
				wxT("Warning !"),
				wxOK | wxICON_WARNING);
		}
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "Save Hex File : %s Successfully", SavePath.c_str());
}


unsigned int& PMBUSFWUpdatePanel::GetIndexOfNotebook(void) {
	return this->m_indexOfNotebook; 
}

bool PMBUSFWUpdatePanel::isCloseButtonPressed(void){
	return this->m_pressedCloseButton;
}

void PMBUSFWUpdatePanel::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
{

	switch (level) {

	case wxLOG_FatalError:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
	case wxLOG_Error:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
		//case wxLOG_Warning:
		//break;
		//case wxLOG_Message:
		//break;
		//case wxLOG_Status:
		//break;
		//case wxLOG_Info:
		//break;
		//case wxLOG_Debug:
		//break;

	default:
		text->SetDefaultStyle(wxTextAttr(*wxBLUE, *wxWHITE));
		break;
	}

#ifdef _DEBUG
	text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s %10s           %s", timestr, threadstr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#else
	text->AppendText(wxString::Format("%9s           %s", timestr, msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s           %s", timestr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#endif
}

void PMBUSFWUpdatePanel::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
#if 0
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}
#endif

	DoLogLine(
		level,
		this->m_logTC,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
		);

}


wxBEGIN_EVENT_TABLE(PMBUSFWUpdatePanel, wxPanel)
EVT_BUTTON(CID_WRITE_BUTTON, PMBUSFWUpdatePanel::OnWriteButton)
EVT_BUTTON(CID_CLOSE_BUTTON, PMBUSFWUpdatePanel::OnCloseButton)
EVT_MENU(MENU_ID_POPUP_SAVEHEX, PMBUSFWUpdatePanel::OnSaveHex)
EVT_DATAVIEW_ITEM_CONTEXT_MENU(ID_HEXMMAP_DVC, PMBUSFWUpdatePanel::OnPopUpMenu)
wxEND_EVENT_TABLE()