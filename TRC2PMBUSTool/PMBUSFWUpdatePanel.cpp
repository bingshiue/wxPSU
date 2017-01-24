/**
 * @file PMBUSFWUpdatePanel.cpp
 */

#include "PMBUSFWUpdatePanel.h"

wxDEFINE_EVENT(wxEVT_COMMAND_ISP_PROGRESS_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_RELOAD_HEX_FILE, wxThreadEvent);

PMBUSFWUpdatePanel::PMBUSFWUpdatePanel(wxNotebook* parent, wxString hexFilePath, TIHexFileParser* tiHexFileStat, IOACCESS* ioaccess, unsigned int* currentIO, bool* isMonitorRunning, unsigned char target, unsigned long developerMode) : wxPanel(parent) {

	this->m_parent = parent;

	this->m_hexFilePath = hexFilePath;
	
	this->m_tiHexFileStat = tiHexFileStat;

	this->m_CompareTiHexFileStat = *this->m_tiHexFileStat;

	this->m_ioaccess = ioaccess;

	this->m_currentIO = currentIO;

	this->m_isMonitorRunning = isMonitorRunning;

	this->m_target = target;

	this->m_developerMode = developerMode;

	this->m_pressedCloseButton = false;

	this->m_writeCount = 0;

	tiHexFileStat->begin();
    this->m_startAddress = tiHexFileStat->currentAddress();

	tiHexFileStat->end();
	this->m_endAddress = tiHexFileStat->currentAddress();

	this->m_addressRange = (this->m_endAddress - this->m_startAddress) + 1UL;

	this->m_dataBytes = tiHexFileStat->size() * 2;

	this->m_dvlRowCount = (this->m_addressRange % 16 == 0) ? this->m_addressRange / 16 : (this->m_addressRange / 16) + 1;

	PSU_DEBUG_PRINT(MSG_DEBUG, "StartAddress = 0x%08x", this->m_startAddress);
	PSU_DEBUG_PRINT(MSG_DEBUG, "EndAddress   = 0x%08x", this->m_endAddress);
	PSU_DEBUG_PRINT(MSG_DEBUG, "Address Range= %d", this->m_addressRange);
	PSU_DEBUG_PRINT(MSG_DEBUG, "Total Data Bytes   = %d", this->m_dataBytes);

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

	this->m_dataBytesST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("Total Data Bytes : "));
	this->m_dataBytesST->SetFont(font);
	wxString DataBytes = wxString::Format("%d", this->m_dataBytes);
	this->m_dataBytesTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, DataBytes);

	this->m_dataBytesTC->SetEditable(false);

	this->m_writeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_WRITE_BUTTON, wxT("WRITE"));
	this->m_writeButton->SetBitmap(wxBITMAP_PNG(MEMORY_32));

	this->m_closeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_CLOSE_BUTTON, wxT("CLOSE"));
	this->m_closeButton->SetBitmap(wxBITMAP_PNG(CLOSE_32));

#ifdef HAVE_RELOAD_BUTTON
	this->m_reloadButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_RELOAD_BUTTON, wxT("RELOAD"));
#endif

	this->m_buttonSizer->Add(this->m_writeButton, wxSizerFlags(0).Border(wxALL));
	this->m_buttonSizer->Add(this->m_closeButton, wxSizerFlags(0).Border(wxALL));

#ifdef HAVE_RELOAD_BUTTON
	this->m_buttonSizer->Add(this->m_reloadButton, wxSizerFlags(0).Border(wxALL));
#endif

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

	// Run In Test GUI Component Initialize 
	if (this->m_developerMode == Generic_Enable){

		this->m_RunInSizer = new wxBoxSizer(wxHORIZONTAL);
		this->m_RunInCheckBox = new wxCheckBox(this, CID_RUN_IN_CHECKBOX, wxT("Run In Test"));
		//this->m_RunInPaddingST = new wxStaticText(this, wxID_ANY, wxEmptyString);

		this->m_RunInTimesST = new wxStaticText(this, wxID_ANY, wxT("Run In Times :"));
		this->m_RunInTimesTC = new wxTextCtrl(this, wxID_ANY, wxString::Format("%d", DEFAULT_RUNIN_TIMES));
		this->m_RunInTimesTC->Enable(false);

		wxString DecimalCharIncludes = wxT("0123456789");
		m_runInTimesNumberValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
		m_runInTimesNumberValidator.SetCharIncludes(DecimalCharIncludes);

		this->m_RunInTimesTC->SetValidator(m_runInTimesNumberValidator);

		this->m_RunInSizer->Add(this->m_RunInCheckBox, wxSizerFlags(0).Border(wxALL).Align(wxALIGN_CENTER_VERTICAL));
		//this->m_RunInSizer->Add(this->m_RunInPaddingST, wxSizerFlags(0).Border(wxALL).Align(wxALIGN_CENTER_VERTICAL));
		this->m_RunInSizer->Add(this->m_RunInTimesST, wxSizerFlags(0).Border(wxALL).Align(wxALIGN_CENTER_VERTICAL));
		this->m_RunInSizer->Add(this->m_RunInTimesTC, wxSizerFlags(0).Border(wxALL).Align(wxALIGN_CENTER_VERTICAL));

		this->m_statisticSBS->Add(m_RunInSizer, wxSizerFlags(0).Border(wxALL).Align(wxALIGN_CENTRE_HORIZONTAL));

		// Static Line 3
		this->m_st3 = new wxStaticLine(this->m_statisticSBS->GetStaticBox());
		this->m_statisticSBS->Add(m_st3, wxSizerFlags(0).Expand().Border(wxALL));
	}

	//
	
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
#if 0
		// Initialize & Add log TextCtrl into Sizer
		this->m_logTC = new PMBUSLogTextCtrl(this, wxID_ANY);

		// use fixed width font to align output in nice columns
		wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

		this->m_logTC->SetFont(font);

		this->m_topLevelSizer->Add(this->m_logTC, wxSizerFlags(1).Expand());
#endif
	}

	this->SetSizerAndFit(this->m_topLevelSizer);

	// Initialize File System Watcher
	m_watcher = new wxFileSystemWatcher();
	m_watcher->SetOwner(this);

	Connect(wxEVT_FSWATCHER,
		wxFileSystemWatcherEventHandler(PMBUSFWUpdatePanel::OnFileSystemEvent));

	// Set HEX File Root Directory To FSWatcher
	wxFileName hexFileFullPath(this->m_hexFilePath);
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "Add %s To FSWatcher", hexFileFullPath.GetPathWithSep().c_str());
	m_watcher->Add(hexFileFullPath.GetPathWithSep());
}

PMBUSFWUpdatePanel::~PMBUSFWUpdatePanel(){
	// Free File System Watcher
	wxFileName hexFileFullPath(this->m_hexFilePath);

	m_watcher->Remove(hexFileFullPath.GetPathWithSep());

	wxDELETE(m_watcher);
}

void PMBUSFWUpdatePanel::SetupHexMMAPDVL(void){

	this->m_tiHexMMAPDVC = new wxDataViewCtrl(this, ID_HEXMMAP_DVC, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	this->m_tiHexMMAPDVC->SetFont(font);

	this->m_tiHexMMAPModel = new TIHexMMAPModel(this->m_dvlRowCount, this->m_tiHexFileStat, &this->m_CompareTiHexFileStat);
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


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error");
		break;
	}

	return active_index;
}


#define CMD_F0H_BYTES_TO_READ  6/**< Bytes To Read */
void PMBUSFWUpdatePanel::OnWriteButton(wxCommandEvent& event){

#if 0
	/*** Check if Monitor is Running ***/
	if (*this->m_isMonitorRunning == true){
		wxMessageBox(wxT("Monitor is running, Please stop monitor then try again !"),
			wxT("Monitor is running !"),  // caption
			wxOK | wxICON_INFORMATION);

		return;
	}
#endif

	/*** If I/O is Close ***/
	if (this->m_ioaccess[*this->m_currentIO].m_GetDeviceStatus() == IODEVICE_CLOSE){
		wxMessageBox(wxT("No I/O Device Found, Please Check Adaptor Card Setting !"),
			wxT("No I/O Device Found !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	/*** If User Cancel ISP Sequence Previous ***/
	if (TaskEx::GetCount(task_ID_UserCancelISPPostDelayTask) > 0){
		wxString content = wxString::Format("Need To Wait %d Seconds ! \n"
			                                "Due to Previous ISP Sequence Has been Canceled !", UserCancelISP_POST_DELAY_TIME/1000);

		wxMessageBox(content,
			wxT("Please Wait !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	/*** Check Run In Mode ***/
	if (this->m_developerMode == Generic_Enable){
		PMBUSHelper::runInMode = this->m_RunInCheckBox->GetValue()==true ? Generic_Enable : Generic_Disable;

		if (PMBUSHelper::runInMode == Generic_Enable){
			int runInTimes = wxAtoi(this->m_RunInTimesTC->GetValue());
		
			if (runInTimes <= 0){
				wxMessageBox(wxT("Run In Times <= 0 !"),
					wxT("Run In Times Setup Failed !"),  // caption
					wxOK | wxICON_WARNING);

				return;
			}
			else{
				PMBUSHelper::runInTimes = runInTimes;
			}
		}
	}
	else{
		PMBUSHelper::runInMode = Generic_Disable;
		PMBUSHelper::runInTimes = 0;
	}

	/*** Write Count For Debug Purpose ***/
	this->m_writeCount++;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Write Count = %d", this->m_writeCount);

	/*** Save Old Log Active Target ***/
	//wxLog* oldLogger = wxLog::GetActiveTarget();

#if 0
	/*** Setup New Log Active Target ***/
	if (this->m_developerMode == Generic_Disable){
		// Change Logger Target
		wxLog::SetActiveTarget(this);
	}
#endif

#if 0
	// Prepare Send Buffer
	unsigned char SendBuffer[8] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xF0, this->m_target, 0x00, 0x0D, 0x0A
	};

	unsigned char pec = 0;
	pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 3);

	SendBuffer[5] = pec;

	/*** Prpare Send Data Buffer ***/
	unsigned char SendBuffer[64];
	unsigned int sendDataLength = this->ProductSendBuffer(SendBuffer);

	PMBUSSendCOMMAND_t CMDF0H;

	CMDF0H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMDF0H.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_F0H_BYTES_TO_READ : CMD_F0H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMDF0H.m_sendData[idx] = SendBuffer[idx];
	}

	/*** Jump To Start Address of Hex File ***/
	this->m_tiHexFileStat.begin();

	/*** Initialize ISP related Parameters ***/
	unsigned char ispStatus = ISP_Status_VerifyBeforeStart;//ISP_Status_InProgress;
	double percentage = 0;
	wxString information("");
	int not_cancel;
	bool inProcess = true;
	unsigned char header_index = 0;
	unsigned int try_end = 0;
#endif

	/*** Decide Dialog Title String ***/
	wxString dialogTitle;
	if (this->m_target == UPDATE_PRIMARY_FW_TARGET){
		dialogTitle = wxString("Primary FW");
	}
	else if (this->m_target == UPDATE_SECONDARY_FW_TARGET){
		dialogTitle = wxString("Secondary FW");
	}

	dialogTitle += wxT(" ISP Progress");

	if(PMBUSHelper::runInMode == Generic_Enable){
		dialogTitle += wxString::Format(" Run In Test Times : %d", PMBUSHelper::runInTimes);
	}


#if 0
	/*** Create Progress Dialog ***/
	m_progressDialog = new wxProgressDialog(dialogTitle,
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
#endif

#if 0
	/*** Create SendISPStartCMD Task ***/
	new(TP_SendISPStartCMDTask) SendISPStartCMDTask(m_ioaccess, m_currentIO, CMDF0H, &this->m_tiHexFileStat, &ispStatus, this->m_target);
#endif
	
	/*** Send ISP Start Event To Main Thread ***/
	wxThreadEvent *threadISPStart_evt;

	threadISPStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_ISP_SEQUENCE_START);
	threadISPStart_evt->SetString(dialogTitle);
	threadISPStart_evt->SetInt(m_target);
	wxQueueEvent(this->m_parent->GetParent()->GetEventHandler(), threadISPStart_evt);

#if 0
	m_ispSequenceThread = new ISPSequenceThread(m_hexFilePath, &m_tiHexFileStat, m_ioaccess, m_currentIO, m_target, m_developerMode, this->m_parent->GetParent()->GetEventHandler(), m_progressDialog);
	// If Create Thread Success
	if (this->m_ispSequenceThread->Create() != wxTHREAD_NO_ERROR){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Create ISP Sequence Thread");
	}
	else{
		this->m_ispSequenceThread->Run();
	}
#endif

	//m_progressDialog->ShowModal();
	
	//m_progressDialog->Destroy();

#if 0
	// Wait for ISP Sequence End
	while (inProcess) {//Task::GetCount() > 0){

		information = wxString(wxT(""));

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

				if (this->m_developerMode == Generic_Enable){
					information += wxString::Format("Current Process Address : %08x", currentAddress);
					information += wxT("\n");
				}

				information += wxString::Format("Current Processed Bytes : (%d/%d)", processed_bytes, this->m_dataBytes);
			}
			else{
				percentage = 99; // Error occurs, set percentage less than 100 
			}
		}
		
		//PSU_DEBUG_PRINT(MSG_DETAIL, "Percentage = %f, Processed bytes = %d, data bytes = %d, Current Address = %08x", percentage, processed_bytes, this->m_dataBytes, currentAddress);
		//PSU_DEBUG_PRINT(MSG_ALERT, "Percentage = %.2f%%", percentage);
		
		//wxThreadEvent* threadISPProgressUpdateEvt;
		//threadISPProgressUpdateEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_ISP_PROGRESS_UPDATE);
		//threadISPProgressUpdateEvt->SetString(wxString::Format("Percentage = %.2f%%", percentage));
		//wxQueueEvent(this->GetEventHandler(), threadISPProgressUpdateEvt);

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

		//wxMilliSleep(200);
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

		case ISP_Status_UserRequestCancel:// User Cancel ISP
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
#endif

}

void PMBUSFWUpdatePanel::OnCloseButton(wxCommandEvent& event){

	unsigned int selected_index;

	selected_index = this->m_parent->GetSelection();

	wxFileName hexFileFullPath(this->m_hexFilePath);

	m_watcher->Remove(hexFileFullPath.GetPathWithSep());

	this->m_pressedCloseButton = true;

	this->m_parent->SetSelection(0);

	this->m_parent->RemovePage(selected_index);

}

void PMBUSFWUpdatePanel::OnReloadButton(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "OnReloadButton:");

	this->ReloadHexFile();
}

void PMBUSFWUpdatePanel::ReloadHexFile(void){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	// Reload HEX File Start
	// Create an input stream
	ifstream TIHexInput;

	// Create a variable for the intel hex data
	TIHexInput.open(this->m_hexFilePath.c_str().AsChar(), ifstream::in);

	if (!TIHexInput.good())
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Error: couldn't open file %s", this->m_hexFilePath.c_str());
		return;
	}

	/* Decode file (Load To m_ReloadTiHexFileStat) */
	this->m_ReloadTiHexFileStat.ClearALL();
	TIHexInput >> this->m_ReloadTiHexFileStat; //

	// Check Errors
	if (this->m_ReloadTiHexFileStat.getNoErrors() != 0){

		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Errors :");

		while (this->m_ReloadTiHexFileStat.getNoErrors() != 0){
			string error_str;
			this->m_ReloadTiHexFileStat.popNextError(error_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", error_str.c_str());
		}


		wxMessageBox(wxT("Load Hex File Has Error"),
			wxT("Error !"),
			wxOK | wxICON_ERROR);

		return;
	}

	// Check Warnings
	if (this->m_ReloadTiHexFileStat.getNoWarnings() != 0)
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Warnings :");

		while (this->m_ReloadTiHexFileStat.getNoWarnings() != 0){
			string warning_str;
			this->m_ReloadTiHexFileStat.popNextWarning(warning_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", warning_str.c_str());
		}

		wxMessageBox(wxT("Load Hex File Has Warning"),
			wxT("Warning !"),
			wxOK | wxICON_WARNING);
	}

	/* Fill Blank Address                                                     */
	this->m_ReloadTiHexFileStat.fillBlankAddr(0xffff);

	// Copy New Hex File Content
	this->m_CompareTiHexFileStat = *this->m_tiHexFileStat;

	this->m_tiHexFileStat->ClearALL();

	*this->m_tiHexFileStat = this->m_ReloadTiHexFileStat;
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

	if (this->m_tiHexFileStat->getNoWarnings() > 0 || this->m_tiHexFileStat->getNoErrors() > 0)
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Error or Warnings generated during decoding:");
		// Check Warnings
		while (this->m_tiHexFileStat->getNoErrors() > 0)
		{
			string error_message;

			this->m_tiHexFileStat->popNextError(error_message);

			PSU_DEBUG_PRINT(MSG_ERROR, "%s", error_message.c_str());

			wxMessageBox(wxT("Load Hex File Has Error"),
				wxT("Error !"),
				wxOK | wxICON_ERROR);

		}
		// Check Errors
		while (this->m_tiHexFileStat->getNoWarnings() > 0)
		{
			string warn_message;

			this->m_tiHexFileStat->popNextWarning(warn_message);

			PSU_DEBUG_PRINT(MSG_ERROR, "%s", warn_message.c_str());

			wxMessageBox(wxT("Load Hex File Has Warning"),
				wxT("Warning !"),
				wxOK | wxICON_WARNING);
		}
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "Save Hex File : %s Successfully", SavePath.c_str());
}

void PMBUSFWUpdatePanel::OnRunInCheckBox(wxCommandEvent& event){

	int runinCheckBoxStatus = this->m_RunInCheckBox->GetValue()==true ? Generic_Enable : Generic_Disable;

	switch (runinCheckBoxStatus){

	case Generic_Enable:

		this->m_RunInTimesTC->Enable(true);

		break;

	case Generic_Disable:

		this->m_RunInTimesTC->Enable(false);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Errors !");
		break;
	
	}

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

	//text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));
	text->AppendText(wxString::Format("%-8s   %s", threadstr, msg));

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
	//text->AppendText(wxString::Format("%9s           %s", timestr, msg));
	text->AppendText(wxString::Format("%-s", msg));

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

void PMBUSFWUpdatePanel::OnProgressUpdate(wxThreadEvent& event){

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", event.GetString());

	// Flush Log
	//if (this->m_developerMode == Generic_Disable){
		//wxLog::FlushActive();
	//}

}

void PMBUSFWUpdatePanel::OnReloadHexFile(wxThreadEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	wxString message = event.GetString();

	// Popup Dialog For Let User Comfirm
	int confirm;
	wxMessageDialog* confirmDialog = new wxMessageDialog(this, message, wxT("Content Of Hex File Has Been Changed !"), wxYES_NO | wxICON_INFORMATION);
	confirmDialog->CenterOnScreen();
	confirm = confirmDialog->ShowModal();

	if (confirm == wxID_YES) {
		PSU_DEBUG_PRINT(MSG_ALERT, "Reload Hex File");
		ReloadHexFile();
	}
	else{
		return;
	}

	wxDELETE(confirmDialog);

	// Compute Address
	this->CheckHexAddressRange();

	// If Develop Mode Enable
	if (this->m_developerMode == Generic_Enable){
		
		PSU_DEBUG_PRINT(MSG_DEBUG, "Refresh DataViewCtrl");
		
		// Reset Model Size
		this->m_tiHexMMAPModel->Reset(this->m_dvlRowCount);
		
		// Refresh DVC 
		this->m_tiHexMMAPDVC->Refresh();
	}

	// Update UI
	if (this->m_developerMode == Generic_Enable){
		wxString StartAddress = wxString::Format("0x%08x", this->m_startAddress);
		this->m_startAddressTC->SetValue(StartAddress);

		wxString EndAddress = wxString::Format("0x%08x", this->m_endAddress);
		this->m_endAddressTC->SetValue(EndAddress);

		wxString AddressRange = wxString::Format("%d", this->m_addressRange);
		this->m_addressRangeTC->SetValue(AddressRange);
	}

	wxString DataBytes = wxString::Format("%d", this->m_dataBytes);
	this->m_dataBytesTC->SetValue(DataBytes);

	// Popup Dialog For Notify User Reload Operation Success
	wxMessageDialog* successDialog = new wxMessageDialog(this, wxT("Reload Hex File Success !"), wxT("Reload File"), wxOK | wxICON_INFORMATION);
	successDialog->CenterOnScreen();
	(void)successDialog->ShowModal();

	wxDELETE(successDialog);
}

void PMBUSFWUpdatePanel::CheckHexAddressRange(void){
	
	this->m_tiHexFileStat->begin();
	this->m_startAddress = this->m_tiHexFileStat->currentAddress();

	this->m_tiHexFileStat->end();
	this->m_endAddress = this->m_tiHexFileStat->currentAddress();

	this->m_addressRange = (this->m_endAddress - this->m_startAddress) + 1UL;

	this->m_dataBytes = this->m_tiHexFileStat->size() * 2;

	this->m_dvlRowCount = (this->m_addressRange % 16 == 0) ? this->m_addressRange / 16 : (this->m_addressRange / 16) + 1;
}

#define INTERVAL_TICKS  20000 // Unit : Milliseconds
void PMBUSFWUpdatePanel::OnFileSystemEvent(wxFileSystemWatcherEvent& event){

	static DWORD previous_ticks = 0;
	static DWORD now_ticks = 0;

	// Get Now Ticks
	now_ticks = GetTickCount();

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnFileSystemEvent: Ticks = %d", now_ticks);
	// Get Event Type
	int type = event.GetChangeType();
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnFileSystemEvent Type is %d", type);

	// Get The Full Path
	wxString eventpath = event.GetPath().GetFullPath();
	PSU_DEBUG_PRINT(MSG_DEBUG, "eventpath = %s", eventpath);

	// If Interval Time Large Then INTERVAL_TICKS
	if ((now_ticks - previous_ticks) > INTERVAL_TICKS){

		PSU_DEBUG_PRINT(MSG_DEBUG, "now_ticks = %d, previous_ticks = %d", now_ticks, previous_ticks);
		
		// If event is wxFSW_EVENT_MODIFY
		if (type == wxFSW_EVENT_MODIFY){

			// If our watch file has been changed
			if (eventpath == this->m_hexFilePath){
				PSU_DEBUG_PRINT(MSG_ALERT, "Content of HEX File Has Been Changed !");

				// Get Now Ticks
				now_ticks = GetTickCount();

				// Emit Thread Event
				wxThreadEvent* threadReloadHexFileEvt;
				threadReloadHexFileEvt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_RELOAD_HEX_FILE);
				wxString message = wxString::Format("%s \n\nContent of %s Has Been Changed, Do you want to reload Hex file ? ", eventpath, eventpath);
				threadReloadHexFileEvt->SetString(message);
				wxQueueEvent(this->m_eventHandler, threadReloadHexFileEvt);

				// For Prevent Event Emitted Twice in Short Time
				previous_ticks = now_ticks;
			}
		}
	}
}

wxBEGIN_EVENT_TABLE(PMBUSFWUpdatePanel, wxPanel)
EVT_BUTTON(CID_WRITE_BUTTON, PMBUSFWUpdatePanel::OnWriteButton)
EVT_BUTTON(CID_CLOSE_BUTTON, PMBUSFWUpdatePanel::OnCloseButton)
EVT_BUTTON(CID_RELOAD_BUTTON, PMBUSFWUpdatePanel::OnReloadButton)
EVT_MENU(MENU_ID_POPUP_SAVEHEX, PMBUSFWUpdatePanel::OnSaveHex)
EVT_CHECKBOX(CID_RUN_IN_CHECKBOX, PMBUSFWUpdatePanel::OnRunInCheckBox)
EVT_DATAVIEW_ITEM_CONTEXT_MENU(ID_HEXMMAP_DVC, PMBUSFWUpdatePanel::OnPopUpMenu)
EVT_THREAD(wxEVT_COMMAND_ISP_PROGRESS_UPDATE, PMBUSFWUpdatePanel::OnProgressUpdate)
EVT_THREAD(wxEVT_COMMAND_RELOAD_HEX_FILE, PMBUSFWUpdatePanel::OnReloadHexFile)
wxEND_EVENT_TABLE()