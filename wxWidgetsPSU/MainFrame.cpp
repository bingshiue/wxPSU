/**
 * @file MainFrame.cpp
 */
#include "MainFrame.h"
#include "MyListStoreDerivedModel.h"
#include "PMBUSCommand.h"
#include "PMBUSCMDCB.h"
#include "Acbel.xpm"
#include "sample.xpm"

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{	
	wxInitAllImageHandlers();

	CheckAndLoadConfig();

	//this->m_ioDeviceOpen = false;

	// Reset AppSettings
	//this->m_appSettings.Reset();

	// Setup IO Structure
	this->DoSetupIOAccess();

	// Current Use IO
	//this->m_CurrentUseIOInterface = IOACCESS_HID;
	this->m_CurrentUseIOInterface = IOACCESS_SERIALPORT;

	// Initializa Semaphore
	this->m_rxTxSemaphore = new wxSemaphore(0,0);
	
	//this->m_parent = new wxPanel(this, wxID_ANY);
	this->m_topVeriticalSizer = new wxBoxSizer(wxVERTICAL);
	this->m_hbox = new wxBoxSizer(wxHORIZONTAL);

	// Load Bitmaps
	this->m_monitorBitmap = new wxBitmap(wxT("MONITOR_32"), wxBITMAP_TYPE_PNG_RESOURCE);
	this->m_pauseBitmap = new wxBitmap(wxT("PAUSE_32"), wxBITMAP_TYPE_PNG_RESOURCE);

	this->m_monitor16Bitmap = new wxBitmap(wxT("MONITOR_16"), wxBITMAP_TYPE_PNG_RESOURCE);
	this->m_pause16Bitmap = new wxBitmap(wxT("PAUSE_16"), wxBITMAP_TYPE_PNG_RESOURCE);

	// Setup Icon
	SetIcon(Acbel_xpm);

	// Setup PMNBusCommand Data
	SetupPMBusCommandData();
	
	// Setup Menu
	SetupMenuBar();

	this->m_cmdListPopupMenu = new wxMenu();
	this->m_popupFontMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_FONT, wxT("Font"), wxT("Font"), wxITEM_NORMAL);
	this->m_popupPrintScreenMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_PRINT_SCREEN, wxT("Print Screen"), wxT("Print Screen"), wxITEM_NORMAL);

	this->m_popupFontMenuItem->SetBitmap(wxBITMAP_PNG(FONT_16));
	this->m_popupPrintScreenMenuItem->SetBitmap(wxBITMAP_PNG(PRINTSCREEN_16));

	this->m_cmdListPopupMenu->Append(this->m_popupFontMenuItem);
	this->m_cmdListPopupMenu->Append(this->m_popupPrintScreenMenuItem);

	// Setup ToolBar
	SetupToolBar();

	// Setup StatusBar
	SetupStatusBar();

	this->m_notebook = new wxNotebook(this, wxID_ANY);

	this->GeneralPanel = new wxPanel(m_notebook, wxID_ANY);

	m_splitterWindowTopLevel = new wxSplitterWindow(this->GeneralPanel, SplitterWindowTopLevelID);

	m_splitterWindowTopLevel->SetSashGravity(0.8);

	m_splitterWindow = new wxSplitterWindow(this->m_splitterWindowTopLevel, SplitterWindowID);

	m_splitterWindow->SetSashGravity(0.3);

	// Sub Notebook
	this->m_subNotebook = new wxNotebook(this->m_splitterWindow, wxID_ANY);
	this->CMDListPanel = new wxPanel(this->m_splitterWindow, wxID_ANY);
	this->DebugLogPanel = new wxPanel(this->m_splitterWindowTopLevel, wxID_ANY);

	this->m_stdPage = new STDPage(this->m_subNotebook);
	this->ReadPanel = new wxPanel(this->m_subNotebook, wxID_ANY);
	//this->m_writePage = new WritePage00H(this->m_subNotebook, wxString(L"00h-PAGE"));

	this->m_debugLogStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this->DebugLogPanel, wxT("Error Log"));

	// create the logging text control and a header showing the meaning of the
	// different columns
	//m_header = new wxTextCtrl(this->GeneralPanel, wxID_ANY, "",
		//wxDefaultPosition, wxDefaultSize,
		//wxTE_READONLY);
	//DoLogLine(m_header, "  Time", " Thread", "          Message");
	this->m_debugLogTC = new wxTextCtrl(this->m_debugLogStaticBoxSizer->GetStaticBox(), wxID_ANY, "",//this->DebugLogPanel, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize,
		wxTE_MULTILINE | wxTE_READONLY );
	
	// Get old logger
	m_oldLogger = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	switch (this->m_appSettings.m_logMode){

	case Log_Mode_Log_ALL:
		wxLog::SetLogLevel(wxLOG_Message);
		break;

	case Log_Mode_Log_Error_Only:
		wxLog::SetLogLevel(wxLOG_Warning);
		break;

	default:

		break;
	}


	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	//m_header->SetFont(font);
	this->m_debugLogTC->SetFont(font);
	this->m_debugLogTC->SetFocus();
	
	SetupCMDListDVL(GeneralPanel);
	SetupPMBusCommandWritePage();

	this->PMBusStatusPanel = new PMBUSStatusPanel(m_notebook);

	this->PMBusMFRPanel = new PMBUSMFRPanel(m_notebook);

	this->PMBusVerificationPanel = new PMBUSVerificationPanel(m_notebook);

	this->PMBusStatusDCHPanel = new PMBUSStatusDCHPanel(m_notebook);

	// Add each panl into notebook component
	m_notebook->AddPage(this->GeneralPanel, "General");
	m_notebook->AddPage(this->PMBusStatusPanel, "PM Bus Status");
	m_notebook->AddPage(this->PMBusMFRPanel, "PMBus MFR");
	m_notebook->AddPage(this->PMBusVerificationPanel, "Verification");
	m_notebook->AddPage(this->PMBusStatusDCHPanel, "STATUS(DCH)");

	m_infoBar = new wxInfoBar(this);
	m_infoBar->SetFont(GetFont().Bold().Larger());
	m_infoBar->SetShowHideEffects(wxSHOW_EFFECT_SLIDE_TO_LEFT, wxSHOW_EFFECT_SLIDE_TO_RIGHT);
	m_infoBar->SetEffectDuration(250);

	m_infoBarTimer = new wxTimer(this);

	//Connect(ID_Hello, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnHello));
	//Connect(ID_Monitor, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnMonitor));
	//Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnAbout));
	//Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnExit));

	this->m_topVeriticalSizer->Add(m_infoBar, wxSizerFlags().Expand());
	//this->m_topVeriticalSizer->Add(this->m_toolbar);
	//this->m_topVeriticalSizer->Add(this->m_hbox, wxSizerFlags(1).Expand());//1, wxEXPAND | (wxALL & ~wxLEFT), 1);
	//this->m_topVeriticalSizer->Add(this->m_dataViewCtrl, wxSizerFlags(1).Expand());
	this->m_topVeriticalSizer->Add(this->m_notebook, 1, wxEXPAND | wxALL, 1);
	//this->m_topVeriticalSizer->Add(header, wxSizerFlags(0).Expand());
	//this->m_topVeriticalSizer->Add(this->m_txtctrl, 2, wxEXPAND | wxALL, 1);//wxSizerFlags(1).Expand());
	//this->m_parent->SetSizer(this->m_topVeriticalSizer, true);

	SetSizer(this->m_topVeriticalSizer);
	//SetSizerAndFit(this->m_topVeriticalSizer);

	this->m_polling_time = wxAtoi(m_polling_time_combobox->GetValue());

	// Start Task System Thread

	this->m_TaskSystemThread = new TaskSystemThread();
	// If Create Thread Success
	if (this->m_TaskSystemThread->Create() != wxTHREAD_NO_ERROR){
		PSU_DEBUG_PRINT(MSG_FATAL, "Can't Create Task System Thread");
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Start Task System Thread");
		this->m_TaskSystemThread->Run();
	}

#if 0 // Test HID 
	EnumerateAvailableHIDDevice(NULL,0);
	int open = 0;
	open = OpenHIDDevice(NULL,0);

	if (open == EXIT_SUCCESS){

		unsigned char send_buff[64];
		unsigned char recv_buff[64];
		productSendBuffer(send_buff, sizeof(send_buff), 0x00, 0x02);

		int res;

		res = HIDSendData(send_buff, 64);
		PSU_DEBUG_PRINT(MSG_ALERT, "Data Write: Res = %d", res);

		res = 0;

		while (res == 0) {
			res = HIDReadData(recv_buff, sizeof(recv_buff) / sizeof(unsigned char));
			if (res == 0)
				PSU_DEBUG_PRINT(MSG_ALERT, "waiting...");
			if (res < 0)
				PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read()");
#ifdef WIN32
			Sleep(20);
#else
			usleep(500 * 1000);
#endif
		};

		PSU_DEBUG_PRINT(MSG_ALERT, "Data Read: Res = %d", res);
		// Print out the returned buffer.
		for (int i = 0; i < res; i++){
			PSU_DEBUG_PRINT(MSG_ALERT, "%02hhx ", recv_buff[i]);
		}

		CloseHIDDevice();
	}
#endif

#if 0
	// Log : Set Active Target 
	/wxLog::SetActiveTarget(new wxLogStderr());
#endif

	m_destroying = 0;
	m_sendThreadStopFlag = true;

	// Disable status bar to show help string
	this->SetStatusBarPane(-1);

	// Set Art Provider
	wxArtProvider::Push(new PMBUSArtProvider);

#if 1
	// Open IO Device
	int retval;
	retval = this->OpenIODevice();
	if (retval == EXIT_FAILURE){
		if (this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT) {
			ComportDialog* comportDialog = new ComportDialog(this, this->m_IOAccess, &this->m_appSettings, this->m_status_bar);
			comportDialog->Centre(wxCENTER_ON_SCREEN);
			comportDialog->ShowModal();

			delete comportDialog;
		}
	}
#endif
	
	// Put Window in Center
	Centre();

}

wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE, wxThreadEvent);

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(MENU_ID_Secondary_Firmware, MainFrame::OnSecondaryFirmwarwe)
EVT_MENU(MENU_ID_Monitor, MainFrame::OnMonitor)
EVT_MENU(MENU_ID_Update_Primary_Firmware, MainFrame::OnUpdatePrimaryFirmware)
EVT_MENU(MENU_ID_Update_Secondary_Firmware, MainFrame::OnUpdateSecondaryFirmware)
EVT_MENU(MENU_ID_Stop_Programming, MainFrame::OnStopProgramming)
EVT_MENU(MENU_ID_I2C_Fault_Test, MainFrame::OnI2CFaultTest)
EVT_MENU(MENU_ID_Enable_Checksum, MainFrame::OnEnableChecksum)
EVT_MENU(MENU_ID_Clear_Error_Log, MainFrame::OnClearErrorLog)
EVT_MENU(MENU_ID_Reset_MaxMin_Value, MainFrame::OnResetMaxMinValue)
EVT_MENU(MENU_ID_Reset_Run_Time, MainFrame::OnResetRunTime)
EVT_MENU(MENU_ID_EnableCalibration, MainFrame::OnEnableCalibration)
EVT_MENU(MENU_ID_DisableCalibration, MainFrame::OnDisableCalibration)
EVT_MENU(MENU_ID_Calibration, MainFrame::OnCalibration)
EVT_MENU(MENU_ID_Administrant, MainFrame::OnAdministrant)
EVT_MENU(MENU_ID_I2C_Interface, MainFrame::OnI2CInterface)
EVT_MENU(MENU_ID_Enable_ALL, MainFrame::OnEnableAll)
EVT_MENU(MENU_ID_Disable_ALL, MainFrame::OnDisableAll)
EVT_MENU(MENU_ID_Continually, MainFrame::OnContinually)
EVT_MENU(MENU_ID_Iterations, MainFrame::OnIterations)
EVT_MENU(MENU_ID_Stop_An_Error, MainFrame::OnStopAnError)
EVT_MENU(MENU_ID_ErrorLog_ALL, MainFrame::OnErrorLogALL)
EVT_MENU(MENU_ID_ErrorLog_ErrorOnly, MainFrame::OnErrorLogErrorOnly)
EVT_MENU(MENU_ID_Log_To_File, MainFrame::OnLogToFile)
EVT_MENU(MENU_ID_PMBUS_1_1, MainFrame::OnPMBus1_1)
EVT_MENU(MENU_ID_PMBUS_1_2, MainFrame::OnPMBus1_2)
EVT_MENU(MENU_ID_POPUP_FONT, MainFrame::OnPopupFont)
EVT_MENU(MENU_ID_POPUP_PRINT_SCREEN, MainFrame::OnPopupPrintScreen)
EVT_MENU(MENU_ID_ABOUT, MainFrame::OnAbout)

EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_DATAVIEW_SELECTION_CHANGED(ID_ATTR_CTRL, MainFrame::OnDVSelectionChanged)
EVT_DATAVIEW_ITEM_CONTEXT_MENU(ID_ATTR_CTRL, MainFrame::OnContextMenu)
//EVT_DATAVIEW_ITEM_VALUE_CHANGED(ID_ATTR_CTRL, MainFrame::OnValueChanged)
EVT_COMBOBOX(ID_POLLING_TIME_COMBO, MainFrame::OnPollingTimeCombo)
EVT_BUTTON(CID_SLAVE_ADDRESS_SET_BUTTON, MainFrame::OnSlaveAddressSetButton)

EVT_TIMER(wxID_ANY, MainFrame::OnInfoBarTimer)

EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE, MainFrame::OnSendThreadUpdate)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_COMPLETED, MainFrame::OnSendThreadCompletion)

EVT_CLOSE(MainFrame::OnWindowClose)
wxEND_EVENT_TABLE()

MainFrame::~MainFrame()
{		
	wxLog::SetActiveTarget(m_oldLogger);

	if (this->m_logFileFFileOutputStream) { delete this->m_logFileFFileOutputStream; }
	if (this->m_logFileTextOutputStream) { delete this->m_logFileTextOutputStream; }

	// Save Config
	this->SaveConfig();
}

void MainFrame::SetupPMBusCommandData(void){
	
	for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++){

		this->m_PMBusData[idx].m_toggle = g_PMBUSCommand[idx].m_toggle;
		sprintf(this->m_PMBusData[idx].m_label, g_PMBUSCommand[idx].m_label);
		this->m_PMBusData[idx].m_register = g_PMBUSCommand[idx].m_register;
		sprintf(this->m_PMBusData[idx].m_name, g_PMBUSCommand[idx].m_name);
		this->m_PMBusData[idx].m_access = g_PMBUSCommand[idx].m_access;
		this->m_PMBusData[idx].m_query = g_PMBUSCommand[idx].m_query;
		this->m_PMBusData[idx].m_cook = g_PMBUSCommand[idx].m_cook;
		this->m_PMBusData[idx].m_responseDataLength = g_PMBUSCommand[idx].m_responseDataLength;
		this->m_PMBusData[idx].m_cmdStatus = g_PMBUSCommand[idx].m_cmdStatus;
		this->m_PMBusData[idx].m_cmdCBFunc.m_queryCBFunc = CMDQueryCBFuncArray[idx];
		this->m_PMBusData[idx].m_cmdCBFunc.m_cookCBFunc = CMDCookCBFuncArray[idx];
		this->m_PMBusData[idx].m_cmdCBFunc.m_rawCBFunc = CMDRawCBFuncArray[idx];
	}

}

void MainFrame::SetupPMBusCommandWritePage(void){
	unsigned int cmdIndex = 0;
	wxString label("");
	
	// 00H PAGE
	cmdIndex = this->findPMBUSCMDIndex(0x00);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[0].m_writePage = new WritePage00H(this->m_subNotebook, label, &this->m_monitor_running,&this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[0].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 01H OPERATUION
	cmdIndex = this->findPMBUSCMDIndex(0x01);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[1].m_writePage = new WritePage01H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[1].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 02H ON_OFF_CONFIG
	cmdIndex = this->findPMBUSCMDIndex(0x02);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[2].m_writePage = new WritePage02H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[2].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 03H CLEAR_FAULTS
	cmdIndex = this->findPMBUSCMDIndex(0x03);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[3].m_writePage = new WritePage03H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[3].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 1BH SMRALERT_MASK
	cmdIndex = this->findPMBUSCMDIndex(0x1b);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage1BH(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 3AH FAN_CONFIG_1_2
	cmdIndex = this->findPMBUSCMDIndex(0x3a);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage3AH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 3BH FAN_COMMAND_1
	cmdIndex = this->findPMBUSCMDIndex(0x3b);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage3BH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 51H OT_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x51);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage51H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 5DH IIC_OC_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x5D);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage5DH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 6AH POUT_OP_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x6A);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage6AH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 6BH PIN_OP_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x6B);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage6BH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 99H MFR_ID
	cmdIndex = this->findPMBUSCMDIndex(0x99);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage99H(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 9AH MFR_MODEL
	cmdIndex = this->findPMBUSCMDIndex(0x9a);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage9AH(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 9BH MFR_REVISION
	cmdIndex = this->findPMBUSCMDIndex(0x9b);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage9BH(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 9CH MFR_LOCATION
	cmdIndex = this->findPMBUSCMDIndex(0x9c);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage9CH(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 9DH MFR_DATE
	cmdIndex = this->findPMBUSCMDIndex(0x9d);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage9DH(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// 9EH MFR_SERIAL
	cmdIndex = this->findPMBUSCMDIndex(0x9e);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePage9EH(this->m_subNotebook, label);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// D0H Cold_Redundancy_Config
	cmdIndex = this->findPMBUSCMDIndex(0xd0);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePageD0H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// DCH Cold_BoxSTATUS
	cmdIndex = this->findPMBUSCMDIndex(0xdc);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePageDCH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// DDH Black_BOX_Index
	cmdIndex = this->findPMBUSCMDIndex(0xdd);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePageDDH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

	// FAH Firmware_Update_Command
	cmdIndex = this->findPMBUSCMDIndex(0xfa);
	label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
	this->m_PMBusData[cmdIndex].m_writePage = new WritePageFAH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
	this->m_subNotebook->RemovePage(2);

}

void MainFrame::OnExit(wxCommandEvent& event)
{
	
#if 0
	if (this->m_monitor_running == true){

		wxMessageDialog *closeWarning = new wxMessageDialog(NULL, L"Monitor Still Running, Please Stop It !", L"Warning", wxOK | wxICON_WARNING);
		closeWarning->ShowModal();

		return;
	}
#endif
	
#if 0
	wxMessageDialog *closeWarning = new wxMessageDialog(NULL, L"OnExit !", L"Warning", wxOK | wxICON_WARNING);
	closeWarning->ShowModal();
#endif

	Close(true);
}

void MainFrame::OnWindowClose(wxCloseEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Close Window");

	if (m_destroying > 0) return;

	m_destroying++;

	// Monitor is Running
	if (this->m_monitor_running == true) {
		this->m_monitor_running = false;
		// IOPortSendCMDThread is Running
		if (this->m_IOPortSendCMDThread->m_running == true && this->m_IOPortSendCMDThread->IsRunning() == true){
			PSU_DEBUG_PRINT(MSG_ALERT, "IOPortSendCMDThread is Running");
			
			this->m_IOPortSendCMDThread->m_running = false;

			wxThread::Yield();

			Sleep(2000);

			//while (!this->m_sendThreadStopFlag) { PSU_DEBUG_PRINT(MSG_ALERT, "IOPortSendCMDThread is Running"); };

			//wxThreadError error = this->m_IOPortSendCMDThread->Delete();

			//if (error != wxTHREAD_NO_ERROR){
				//PSU_DEBUG_PRINT(MSG_ALERT, "wxThreadError = %d", error);
			//}
		}
	}

	//
	this->m_sendCMDVector.clear();

	// Check TaskSystem Have Task or Not
	int cnt = Task::GetCount();

	while (cnt != 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "cnt = %d", cnt);
		cnt = Task::GetCount();

		Sleep(1000);
	}

	// Release Task List
	TaskEx::ReleaseTaskList();


	// Close IO Device
	this->CloseIODevice();

	Destroy();
	//event.Skip();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	//wxMessageBox("Acbel PSU Tool",
		//"Acbel", wxOK | wxICON_INFORMATION);
	AboutDialog* aboutDialog = new AboutDialog(this);
	aboutDialog->Centre();
	aboutDialog->ShowModal();

	delete aboutDialog;
}

void MainFrame::OnSecondaryFirmwarwe(wxCommandEvent& event)
{
	PSU_DEBUG_PRINT(MSG_ALERT,"Not Implement");
}

void MainFrame::OnUpdatePrimaryFirmware(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnUpdateSecondaryFirmware(wxCommandEvent& event){
	
	wxFileDialog LoadHexFileDialog(this, L"Load Firmware File", "", "", "HEX Files (*.hex)|*.hex", wxFD_OPEN);
	
	LoadHexFileDialog.Centre();

	// If the user changed idea...
	if (LoadHexFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

	// Load HEX File
	wxString path = LoadHexFileDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_ALERT, "HEX File Path : %s", path.c_str());

	// Create an input stream
	ifstream TIHexInput;

	// Create a variable for the intel hex data
	TIHexInput.open(path.c_str().AsChar(), ifstream::in);

	if (!TIHexInput.good())
	{
		PSU_DEBUG_PRINT(MSG_ALERT, "Error: couldn't open file %s", path.c_str());
	}

	/* Decode file                                                            */
	TIHexInput >> m_SecondaryTIHexFileStat;

	/* Fill Blank Address                                                     */
	m_SecondaryTIHexFileStat.fillBlankAddr(0xffff);

	m_SecondaryTIHexFileStat.begin();
	unsigned long startAddress = m_SecondaryTIHexFileStat.currentAddress();

	m_SecondaryTIHexFileStat.end();
	unsigned long endAddress = m_SecondaryTIHexFileStat.currentAddress();

	PSU_DEBUG_PRINT(MSG_ALERT, "startAddress = 0x%08x", startAddress);
	PSU_DEBUG_PRINT(MSG_ALERT, "EndAddress   = 0x%08x", endAddress);
	PSU_DEBUG_PRINT(MSG_ALERT, "Address Range= %d", endAddress - startAddress + 1UL);
	PSU_DEBUG_PRINT(MSG_ALERT, "Data Bytes   = %d", m_SecondaryTIHexFileStat.size());

	if (!this->SecondaryFWUpdatePanel) this->SecondaryFWUpdatePanel = new wxPanel(m_notebook);
	this->SetupTIHexMMAPDVL(this->SecondaryFWUpdatePanel, &this->m_SecondaryTIHexFileStat);

}

void MainFrame::OnStopProgramming(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnI2CFaultTest(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnEnableChecksum(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnClearErrorLog(wxCommandEvent& event){
	this->m_debugLogTC->Clear();
}

void MainFrame::OnResetMaxMinValue(wxCommandEvent& event){
	PMBUSHelper::GetPMBusStatus()->ResetMaxMin();
}

void MainFrame::OnResetRunTime(wxCommandEvent& event){
	this->m_status_bar->getBeginDateTime() = wxDateTime::Now();
}

void MainFrame::OnEnableCalibration(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnDisableCalibration(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnCalibration(wxCommandEvent& event){
	// Show Calibration Dialog
	CalibrationDialog* calibrationDlg = new CalibrationDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_monitor_running, &this->m_sendCMDVector);
	calibrationDlg->Centre();
	calibrationDlg->ShowModal();

	delete calibrationDlg;
}

void MainFrame::OnAdministrant(wxCommandEvent& event){
	wxString password;
	
	wxPasswordEntryDialog *passwordEntryDialog = new wxPasswordEntryDialog(this, wxT("Please Input Administrator Password"));
	passwordEntryDialog->ShowModal();
	password = passwordEntryDialog->GetValue();

	if (password.compare(ADMINISTRATOR_PASSWORD) == 0){
		PSU_DEBUG_PRINT(MSG_DETAIL, "Password = %s", password.c_str());
		// Enable Update Firmware
		this->m_runMenu->Enable(MENU_ID_Update_Primary_Firmware, true);
		this->m_runMenu->Enable(MENU_ID_Update_Secondary_Firmware, true);

	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Password Not Match");
	}

	delete passwordEntryDialog;
}

void MainFrame::OnI2CInterface(wxCommandEvent& event){
	I2CInterfaceDialog* i2cIFDialog = new I2CInterfaceDialog(this, this->m_IOAccess, &this->m_appSettings, this->m_status_bar);
	i2cIFDialog->Centre();
	i2cIFDialog->ShowModal();

	delete i2cIFDialog;
}

void MainFrame::OnContinually(wxCommandEvent& event){
	this->m_appSettings.m_runMode = RunMode_Continually;

	this->m_continuallyMenuItem->Check(true);
	this->m_iterationsMenuItem->Check(false);
	this->m_stopAnErrorMenuItem->Check(false);

	this->m_iteration_input->Disable();

	this->m_status_bar->SetStatusText(wxT("Continually"), PMBUSStatusBar::Field_Run_Mode);
}

void MainFrame::OnIterations(wxCommandEvent& event){
	this->m_appSettings.m_runMode = RunMode_Iterations;

	this->m_continuallyMenuItem->Check(false);
	this->m_iterationsMenuItem->Check(true);
	this->m_stopAnErrorMenuItem->Check(false);

	this->m_iteration_input->Enable();

	this->m_status_bar->SetStatusText(wxT("Iterations"), PMBUSStatusBar::Field_Run_Mode);
}

void MainFrame::OnStopAnError(wxCommandEvent& event){
	this->m_appSettings.m_runMode = RunMode_StopAnError;

	this->m_continuallyMenuItem->Check(false);
	this->m_iterationsMenuItem->Check(false);
	this->m_stopAnErrorMenuItem->Check(true);

	this->m_iteration_input->Disable();

	this->m_status_bar->SetStatusText(wxT("Stop An Error"), PMBUSStatusBar::Field_Run_Mode);
}

void MainFrame::OnErrorLogALL(wxCommandEvent& event){

	this->m_appSettings.m_logMode = Log_Mode_Log_ALL;
	this->m_allMenuItem->Check(true);
	this->m_errorOnlyMenuItem->Check(false);
}

void MainFrame::OnErrorLogErrorOnly(wxCommandEvent& event){
	
	this->m_appSettings.m_logMode = Log_Mode_Log_Error_Only;
	this->m_allMenuItem->Check(false);
	this->m_errorOnlyMenuItem->Check(true);
}

void MainFrame::OnLogToFile(wxCommandEvent& event){

	if (this->m_appSettings.m_logToFile == Generic_Enable){
		this->m_logToFileMenuItem->Check(false);
		this->m_appSettings.m_logToFile = Generic_Disable;
	}
	else{
		this->m_logToFileMenuItem->Check(true);
		this->m_appSettings.m_logToFile = Generic_Enable;

		wxDirDialog *dirDialog = new wxDirDialog(this, wxT("Please Select A Directory"), wxT("C:\\"));
		dirDialog->Centre(wxCENTER_ON_SCREEN);
		dirDialog->ShowModal();

		// 
		wxString logFileDirPath("");
		logFileDirPath = dirDialog->GetPath();

		PSU_DEBUG_PRINT(MSG_ALERT, "%s", dirDialog->GetPath());

		// Set Log File's Save Directory Path
		this->m_appSettings.m_logFilePath = dirDialog->GetPath();

		// No more need
		delete dirDialog;
		
		// Init Output Stream
		this->ReInitLogFileOutputStream(logFileDirPath);

	}
}

void MainFrame::OnPMBus1_1(wxCommandEvent& event){
	this->m_appSettings.m_pmbusReadMethod = PMBUS_ReadMethod_1_1;

	this->m_pmBus11MenuItem->Check(true);
	this->m_pmBus12MenuItem->Check(false);
}

void MainFrame::OnPMBus1_2(wxCommandEvent& event){
	this->m_appSettings.m_pmbusReadMethod = PMBUS_ReadMethod_1_2;

	this->m_pmBus11MenuItem->Check(false);
	this->m_pmBus12MenuItem->Check(true);
}

void MainFrame::OnPopupFont(wxCommandEvent& event){
	
	wxFont font;

	font = wxGetFontFromUser();
	
	if (font.IsOk()){
		this->m_cmdListDVC->SetFont(font);
	}
}

void MainFrame::OnPopupPrintScreen(wxCommandEvent& event){

	wxString dateStr("");
	PMBUSHelper::GetNowDateTimeString(dateStr);

	wxFileDialog SaveCDMListDialog(this, L"Save To", "", dateStr, "TXT files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	SaveCDMListDialog.Centre();

	// If the user changed idea...
	if (SaveCDMListDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	// Save CMD List To File
	wxString SavePath = SaveCDMListDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_ALERT, "Save List To : %s", SavePath.c_str());

	wxFFileOutputStream fileOutStream(SavePath);

	if (!fileOutStream.IsOk()){
		wxLogError("Can not Save List To %s", SavePath);
		return;
	}

	wxTextOutputStream textOutputStream(fileOutStream);
	// Call our save function
	this->SaveCMDListToFile(textOutputStream);

	textOutputStream.Flush();
}

void MainFrame::OnInfoBarTimer(wxTimerEvent& WXUNUSED(event)){
	if (this->m_infoBar->IsShown() == true){
		this->m_infoBar->Dismiss();
	}
}

void MainFrame::OnMonitor(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG,  "Polling Time = %d", this->m_polling_time);
	PSU_DEBUG_PRINT(MSG_DETAIL, "m_monitor_running = %d", this->m_monitor_running);

	int loop = 0;

	//PSU_DEBUG_PRINT("Available = %d", this->m_list_model.get()->getAvailable()[0]);

	// If IO Device not Open, Open IO Device Here
	this->OpenIODevice();

	// Start Send Data Thread
	if (this->m_monitor_running == false){
		this->m_monitor_running = true;

		this->m_toolbar->FindById(MENU_ID_Monitor)->SetNormalBitmap(*this->m_pauseBitmap);
		this->m_monitorMenuItem->SetBitmap(*m_pause16Bitmap);
		this->m_toolbar->Realize();

		(this->m_status_bar->getTimer())->Start();
		this->m_status_bar->getBeginDateTime() = wxDateTime::Now();

		PSU_DEBUG_PRINT(MSG_DETAIL, "Start Send Data Thread");
		this->m_IOPortSendCMDThread = new IOPortSendCMDThread(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, this->m_rxTxSemaphore, &this->m_appSettings, &this->m_polling_time, this->m_PMBusData, &this->m_IOPortRecvBuff, &m_cmdListModel, this->m_status_bar, this->m_stdPage, PMBusStatusPanel, PMBusStatusDCHPanel, &this->m_sendCMDVector);
		//this->m_serialPortSendCommandThread->SetPriority(wxPRIORITY_MIN);

		// If Create Thread Success
		if (this->m_IOPortSendCMDThread->Create() != wxTHREAD_NO_ERROR){
			PSU_DEBUG_PRINT(MSG_FATAL, "Can't Create Send Command Thread");
		}
		else{
			this->m_IOPortSendCMDThread->Run();
			this->m_sendThreadStopFlag = false;
		}

	}
	else{ // One Send Command Thread is Running
		this->m_monitor_running = false;

		this->m_toolbar->FindById(MENU_ID_Monitor)->SetNormalBitmap(*this->m_monitorBitmap);
		this->m_monitorMenuItem->SetBitmap(*m_monitor16Bitmap);
		this->m_toolbar->Realize();

		(this->m_status_bar->getTimer())->Stop();
		PSU_DEBUG_PRINT(MSG_DETAIL, "Stop Send Data Thread");
		this->m_IOPortSendCMDThread->m_running = false;
	}

}

void MainFrame::DoLogLine(wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
{
	text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));

	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s %10s           %s", timestr, threadstr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
}

void MainFrame::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
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
		this->m_debugLogTC,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
	);
}

void MainFrame::OnValueChanged(wxDataViewEvent &event)
{
	/*wxString title*/ 
	unsigned int row = m_cmdListModel->GetRow(event.GetItem());//GetTitle(event.GetItem());
	PSU_DEBUG_PRINT(MSG_DETAIL, "wxEVT_DATAVIEW_ITEM_VALUE_CHANGED");// , Item Id : %s;  Column: %d",
	//title, event.GetColumn());
}

void MainFrame::OnPollingTimeCombo(wxCommandEvent& event){
	this->m_polling_time = wxAtoi(m_polling_time_combobox->GetValue());
	PSU_DEBUG_PRINT(MSG_DEBUG, "Select Polling Time is %d", this->m_polling_time);
	this->m_cmdListDVC->SetFocus();
}

void MainFrame::OnSlaveAddressSetButton(wxCommandEvent& event){
	this->m_appSettings.m_I2CSlaveAddress = PMBUSHelper::HexToDecimal(this->m_address_input->GetValue().c_str());
	PMBUSHelper::GetSlaveAddress() = this->m_appSettings.m_I2CSlaveAddress;
	wxString hex = (wxString::Format("%2x", PMBUSHelper::GetSlaveAddress())).Upper();
	PSU_DEBUG_PRINT(MSG_DEBUG, "Change Slave Address To %s", hex.c_str());

	this->m_infoBar->SetBackgroundColour(wxColour( 127, 246, 85));

	this->m_infoBar->ShowMessage(
		wxString::Format("Change Slave Address To %s", hex.c_str()), wxICON_INFORMATION
	);

	this->m_infoBarTimer->Start(3000, true);
}

void MainFrame::SetupMenuBar(void){
	// Create Menu Bar and Its Components
	// File Menu
	/*
	File
	|- Hex To Bin -> Secondary Firmware
	|------------------------------------
	|- Exit
	*/
	this->m_fileMenu = new wxMenu();
	this->m_hexToBinMenu = new wxMenu();
	this->m_hexToBinMenu->Append(MENU_ID_Secondary_Firmware, "&Secondary Firmware...\tCtrl-S",
		"Select Secondary Firmware");
	
	this->m_fileMenu->AppendSubMenu(this->m_hexToBinMenu,wxT("Hex to Bin"),wxT("Transform Hex into Bin"));
	this->m_fileMenu->AppendSeparator();

	this->m_exitMenuItem = new wxMenuItem((wxMenu*)0, wxID_EXIT, wxT("Exit"),
		wxT("Exit"), wxITEM_NORMAL);

	this->m_exitMenuItem->SetBitmap(wxBITMAP_PNG(EXIT_16));

	this->m_fileMenu->Append(m_exitMenuItem);


	// Run Menu
	/*
	Run
	|- Monitor
	|- In System Programming -> |- Update Primary Firmware
	|                           |- Update Secondary Firmware 
	|- Stop Programming
	|------------------------------------
	|- I2C Fault Test
	|- [V] Enable Checksum
	|------------------------------------
	|- Clear Error Log
	|- Reset Max./Min. Value
	|- Reset Run Time


	*/
	this->m_runMenu = new wxMenu();
	this->m_monitorMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Monitor, "&Monitor...\tCtrl-M",
		"Start Monitor", wxITEM_NORMAL);

	this->m_monitorMenuItem->SetBitmap(*m_monitor16Bitmap);

	this->m_runMenu->Append(this->m_monitorMenuItem);

	this->m_inSystemProgrammingMenuItem = new wxMenuItem((wxMenu*)0, wxID_ANY, wxT("In System Programming"), wxT("In System Programming"), wxITEM_NORMAL);

	this->m_inSystemProgrammingMenuItem->SetBitmap(wxBITMAP_PNG(CHIP_16));

	this->m_updatePrimaryFirmwareMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Update_Primary_Firmware, wxT("&Update Primary Firmware...\tCtrl-P"), "Update Primary Firmware", wxITEM_NORMAL);
	this->m_updatePrimaryFirmwareMenuItem->SetBitmap(wxBITMAP_PNG(CHIP_16));

	this->m_updateSecondaryFirmwareMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Update_Secondary_Firmware, wxT("&Update Secondary Firmware...\tCtrl-U"), "Update Secnondary Firmware", wxITEM_NORMAL);
	this->m_updateSecondaryFirmwareMenuItem->SetBitmap(wxBITMAP_PNG(CHIP_16));

	this->m_ispMenu = new wxMenu();

	this->m_ispMenu->Append(this->m_updatePrimaryFirmwareMenuItem);
	this->m_ispMenu->Append(this->m_updateSecondaryFirmwareMenuItem);

	this->m_inSystemProgrammingMenuItem->SetSubMenu(this->m_ispMenu);

	this->m_runMenu->Append(this->m_inSystemProgrammingMenuItem);

#ifdef DEFAULT_LOCK_UPDATE_FW
	this->m_runMenu->Enable(MENU_ID_Update_Secondary_Firmware, false);
	this->m_runMenu->Enable(MENU_ID_Update_Primary_Firmware, false);
#endif

	this->m_stopProgrammingMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Stop_Programming, wxT("Stop Programming"),
		"Stop Programming", wxITEM_NORMAL);

	this->m_runMenu->Append(m_stopProgrammingMenuItem);
	this->m_runMenu->AppendSeparator();

	this->m_i2cFaultTestMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_I2C_Fault_Test, wxT("I2C Fault Test"),
		wxT("I2C Fault Test"), wxITEM_NORMAL);

	this->m_EnableChecksumMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Enable_Checksum, wxT("Enable Checksum"),
		wxT("Enable Checksum"), wxITEM_CHECK);

	this->m_runMenu->Append(m_i2cFaultTestMenuItem);
	this->m_runMenu->Append(m_EnableChecksumMenuItem);
	this->m_runMenu->AppendSeparator();

	this->m_ClearErrorLogMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Clear_Error_Log, wxT("Clear Error Log"),
		wxT("Clear Error Log"), wxITEM_NORMAL);

	this->m_ClearErrorLogMenuItem->SetBitmap(wxBITMAP_PNG(CLEAR_16));

	this->m_ResetMaxMinValueMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Reset_MaxMin_Value, wxT("Reset Max./Min/ Value"),
		wxT("Reset Max./Min/ Value"), wxITEM_NORMAL);

	this->m_ResetMaxMinValueMenuItem->SetBitmap(wxBITMAP_PNG(REFRESH_16));

	this->m_ResetRunTimeMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Reset_Run_Time, wxT("Reset Run Time"),
		wxT("Reset Run Time"), wxITEM_NORMAL);

	this->m_ResetRunTimeMenuItem->SetBitmap(wxBITMAP_PNG(TIMER_16));

	this->m_runMenu->Append(this->m_ClearErrorLogMenuItem);
	this->m_runMenu->Append(this->m_ResetMaxMinValueMenuItem);
	this->m_runMenu->Append(this->m_ResetRunTimeMenuItem);

	// PSU Menu
	/*
	PSU
	|- Enable Calibration
	|- Disable Calibration
	|------------------------------------
	|- Calibration
	*/
	this->m_psuMenu = new wxMenu();

	this->m_EnableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_EnableCalibration, wxT("Enable Calibration"),
		wxT("Enable Calibration"), wxITEM_NORMAL);

	this->m_EnableCalibrationMenuItem->SetBitmap(wxBITMAP_PNG(ENABLE_16));

	this->m_DisableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_DisableCalibration, wxT("Disable Calibration"),
		wxT("Disable Calibration"), wxITEM_NORMAL);

	this->m_DisableCalibrationMenuItem->SetBitmap(wxBITMAP_PNG(DISABLE_16));

	this->m_psuMenu->Append(m_EnableCalibrationMenuItem);
	this->m_psuMenu->Append(m_DisableCalibrationMenuItem);

	this->m_psuMenu->AppendSeparator();

	this->m_CalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Calibration, wxT("Calibration"),
		wxT("Calibration Setting"), wxITEM_NORMAL);

	this->m_CalibrationMenuItem->SetBitmap(wxBITMAP_PNG(CALIBRATION_16));

	this->m_psuMenu->Append(m_CalibrationMenuItem);


	// Option Menu
	/*
	Option
	|- Administrant...
	|------------------------------------
	|- I2C  Interface...
	|------------------------------------
	|- Disable All
	|- Enable All
	|------------------------------------
	|- Run Mode          -> [V] Continually
	|                       [V] Interations
	|                       [V] Stop An Error
	|
	|- Error Log Mode    -> [V] All
	|                       [V] Error Only
	|                       ---------------
	|                       Log To File
	|
	|- PMBus Read Method -> [V] PMBus1.1 (Single Mode)
	|                       [V] PMBus1.2 (Page Plus Mode)
	|


	*/
	this->m_optionMenu = new wxMenu();

	this->m_AdministrantMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Administrant, wxT("Administrant..."),
		wxT("Administrant"), wxITEM_NORMAL);

	this->m_AdministrantMenuItem->SetBitmap(wxBITMAP_PNG(ADMIN_16));

	this->m_optionMenu->Append(this->m_AdministrantMenuItem);
	this->m_optionMenu->AppendSeparator();

	this->m_I2CInterfaceMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_I2C_Interface, wxT("I2C Interface..."),
		wxT("I2C Interface"), wxITEM_NORMAL);

	this->m_I2CInterfaceMenuItem->SetBitmap(wxBITMAP_PNG(HWINFO_16));

	this->m_optionMenu->Append(this->m_I2CInterfaceMenuItem);
	this->m_optionMenu->AppendSeparator();

	this->m_optionMenu->Append(MENU_ID_Disable_ALL, "&Disable ALL...\tCtrl-D",
		"Disable All Commands");

	this->m_optionMenu->Append(MENU_ID_Enable_ALL,  "&Enable  ALL...\tCtrl-E",
		"Enable All Commands");

	this->m_optionMenu->AppendSeparator();

	this->m_runModeMenu = new wxMenu();
	this->m_errorLogMenu = new wxMenu();
	this->m_pmbusReadMethodMenu = new wxMenu();

	this->m_continuallyMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Continually, wxT("Continually"),
		wxT("Continually"), wxITEM_CHECK);

	this->m_iterationsMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Iterations, wxT("Iterations"),
		wxT("Iterations"), wxITEM_CHECK);

	this->m_stopAnErrorMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Stop_An_Error, wxT("Stop An Error"),
		wxT("Stop An Error"), wxITEM_CHECK);

	this->m_runModeMenu->Append(this->m_continuallyMenuItem);
	this->m_runModeMenu->Append(this->m_iterationsMenuItem);
	this->m_runModeMenu->Append(this->m_stopAnErrorMenuItem);

	switch (this->m_appSettings.m_runMode){

	case RunMode_Iterations:
		this->m_iterationsMenuItem->Check(true);
		break;

	case RunMode_Continually:
		this->m_continuallyMenuItem->Check(true);
		break;

	case RunMode_StopAnError:
		this->m_stopAnErrorMenuItem->Check(true);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !");
		break;
	}

	this->m_optionMenu->AppendSubMenu(this->m_runModeMenu, wxT("Run Mode"), wxT("Run Mode"));
	
	this->m_allMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ErrorLog_ALL, wxT("All"),
		wxT("All"), wxITEM_CHECK);

	this->m_errorOnlyMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ErrorLog_ErrorOnly, wxT("Error Only"),
		wxT("Error Only"), wxITEM_CHECK);

	this->m_logToFileMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Log_To_File, wxT("Log To File"),
		wxT("Log To File"), wxITEM_CHECK);

	this->m_errorLogMenu->Append(this->m_allMenuItem);
	this->m_errorLogMenu->Append(this->m_errorOnlyMenuItem);
	this->m_errorLogMenu->AppendSeparator();
	this->m_errorLogMenu->Append(this->m_logToFileMenuItem);

	switch (this->m_appSettings.m_logMode){

	case Log_Mode_Log_ALL:
		this->m_allMenuItem->Check(true);
		this->m_errorOnlyMenuItem->Check(false);
		break;

	case Log_Mode_Log_Error_Only:
		this->m_allMenuItem->Check(false);
		this->m_errorOnlyMenuItem->Check(true);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
		break;
	}

	if (this->m_appSettings.m_logToFile == Generic_Enable){
		this->m_logToFileMenuItem->Check(true);
	}
	else{
		this->m_logToFileMenuItem->Check(false);
	}

	this->m_optionMenu->AppendSubMenu(this->m_errorLogMenu, wxT("Error Log Mode"), wxT("Error Log Mode"));
	
	this->m_pmBus11MenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_PMBUS_1_1, wxT("PMBus1.1 (Single Mode)"),
		wxT("PMBus1.1 (Single Mode)"), wxITEM_CHECK);

	this->m_pmBus12MenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_PMBUS_1_2, wxT("PMBus1.2 (Page Plus Mode)"),
		wxT("PMBus1.2 (Page Plus Mode)"), wxITEM_CHECK);

	this->m_pmbusReadMethodMenu->Append(this->m_pmBus11MenuItem);
	this->m_pmbusReadMethodMenu->Append(this->m_pmBus12MenuItem);

	switch (this->m_appSettings.m_pmbusReadMethod){

	case PMBUS_ReadMethod_1_1:
		this->m_pmBus11MenuItem->Check(true);
		this->m_pmBus12MenuItem->Check(false);
		break;

	case PMBUS_ReadMethod_1_2:
		this->m_pmBus11MenuItem->Check(false);
		this->m_pmBus12MenuItem->Check(true);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
		break;
	}

	this->m_optionMenu->AppendSubMenu(this->m_pmbusReadMethodMenu, wxT("PMBus Read Method"), wxT("PMBus Read Method"));

	// Help Menu
	/*
	Help
	|- About
	*/
	this->m_helpMenu = new wxMenu();

	this->m_aboutMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ABOUT, wxT("About"),
		wxT("About"), wxITEM_NORMAL);

	this->m_aboutMenuItem->SetBitmap(wxBITMAP_PNG(ABOUT_16));

	this->m_helpMenu->Append(this->m_aboutMenuItem);

	// Create MenuBar Instance
	this->m_menuBar = new wxMenuBar();
	this->m_menuBar->Append(this->m_fileMenu,   wxT("File"));
	this->m_menuBar->Append(this->m_runMenu,    wxT("Run"));
	this->m_menuBar->Append(this->m_psuMenu,    wxT("PSU"));
	this->m_menuBar->Append(this->m_optionMenu, wxT("Option"));
	this->m_menuBar->Append(this->m_helpMenu,   wxT("Help"));

	SetMenuBar(this->m_menuBar);

}

void MainFrame::SetupToolBar(void){
	
	// Setup Tool Bar
	long style = TOOLBAR_STYLE;
	style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);

	// Create Tool Bar Instance
	m_toolbar = CreateToolBar(style, ID_TOOLBAR);

	// Append Exit Button
	m_toolbar->AddTool(wxID_EXIT, wxEmptyString, wxBITMAP_PNG(EXIT_32), wxT("Exit Program"), wxITEM_NORMAL);

	// Append Monitor Button
	m_toolbar->AddTool(MENU_ID_Monitor, wxEmptyString, *m_monitorBitmap, wxT("Monitor"), wxITEM_NORMAL);

	// Append Enable Calibration Button
	m_toolbar->AddTool(MENU_ID_EnableCalibration, wxEmptyString, wxBITMAP_PNG(ENABLE_32), wxT("Enable Calibration"), wxITEM_NORMAL);

	// Append Reset Run Time Button
	m_toolbar->AddTool(MENU_ID_Reset_Run_Time, wxEmptyString, wxBITMAP_PNG(TIMER_32), wxT("Reset Run Time"), wxITEM_NORMAL);

	// Append Refresh MAX/MIN Button
	m_toolbar->AddTool(MENU_ID_Reset_MaxMin_Value, wxEmptyString, wxBITMAP_PNG(REFRESH_32), wxT("Reset Max/Min Value"), wxITEM_NORMAL);

	// Append Clear Error Log Button 
	m_toolbar->AddTool(MENU_ID_Clear_Error_Log, wxEmptyString, wxBITMAP_PNG(CLEAR_32), wxT("Clear Error Log"), wxITEM_NORMAL);

	// Append Separator
	m_toolbar->AddSeparator();

	// Append Interation
	m_iteration_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Iteration"));
	m_toolbar->AddControl(m_iteration_text, wxEmptyString);

	wxString iterations_times = wxString::Format("%d",this->m_appSettings.m_IterationsValue);

	m_iteration_input = new wxTextCtrl(m_toolbar, wxID_ANY);
	m_iteration_input->SetValue(iterations_times);

	wxTextValidator numberValidator;
	numberValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	numberValidator.SetCharIncludes(wxT("0123456789"));

	m_iteration_input->SetValidator(numberValidator);

	if (this->m_iterationsMenuItem->IsChecked() == false){
		m_iteration_input->Disable();
	}

	m_toolbar->AddControl(m_iteration_input, wxEmptyString);

	// Append Polling Time
	m_polling_time_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Polling Time(ms)"));
	m_toolbar->AddControl(m_polling_time_text, wxEmptyString);

	m_polling_time_combobox = new wxComboBox(m_toolbar, ID_POLLING_TIME_COMBO, wxEmptyString, wxDefaultPosition, wxSize(100, -1));
	m_polling_time_combobox->Append(wxT("0"));
	m_polling_time_combobox->Append(wxT("10"));
	m_polling_time_combobox->Append(wxT("20"));
	m_polling_time_combobox->Append(wxT("50"));
	m_polling_time_combobox->Append(wxT("100"));
	m_polling_time_combobox->Append(wxT("200"));
	m_polling_time_combobox->Append(wxT("300"));
	m_polling_time_combobox->Append(wxT("500"));
	m_polling_time_combobox->Append(wxT("1000"));
	m_polling_time_combobox->Append(wxT("1500"));

	m_polling_time_combobox->SetSelection(2);
	m_toolbar->AddControl(m_polling_time_combobox, wxEmptyString);

	// Append Separator
	m_toolbar->AddSeparator();

	// Append Address 
	m_address_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("I2C Slave Address"));
	m_toolbar->AddControl(m_address_text, wxEmptyString);

	m_address_input = new wxTextCtrl(m_toolbar, wxID_ANY);

	wxString SlaveAddressHex = (wxString::Format("%02lx", this->m_appSettings.m_I2CSlaveAddress)).Upper();
	m_address_input->SetLabel(SlaveAddressHex);

	wxTextValidator hexValidator;
	hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	hexValidator.SetCharIncludes(wxT("0123456789abcdefABCDEF"));

	m_address_input->SetValidator(hexValidator);

	m_toolbar->AddControl(m_address_input, wxEmptyString);


	// Append Address Set Button
	m_addressSetButton = new wxButton(m_toolbar, CID_SLAVE_ADDRESS_SET_BUTTON, wxT("Set"));
	m_toolbar->AddControl(m_addressSetButton, wxEmptyString);

	// Append A2 A1 A0 Check Box
	//m_a2_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A2, wxT("A2"), wxDefaultPosition, wxDefaultSize);
	//m_toolbar->AddControl(m_a2_chkbox, wxEmptyString);

	//m_a1_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A1, wxT("A1"), wxDefaultPosition, wxDefaultSize);
	//m_toolbar->AddControl(m_a1_chkbox, wxEmptyString);

	//m_a0_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A0, wxT("A0"), wxDefaultPosition, wxDefaultSize);
	//m_toolbar->AddControl(m_a0_chkbox, wxEmptyString);

	m_toolbar->Realize();
}

void MainFrame::SetupStatusBar(void){
	this->m_status_bar = new PMBUSStatusBar(this);

	SetStatusBar(this->m_status_bar);

	PositionStatusBar();
}

void MainFrame::SetupCMDListDVL(wxPanel* parent){
	
	wxASSERT(!this->m_cmdListDVC && !m_cmdListModel);
	this->m_cmdListDVC = new wxDataViewCtrl(this->CMDListPanel, ID_ATTR_CTRL, wxDefaultPosition,
		wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	m_cmdListModel = new PMBUSCMDListModel(this->m_PMBusData);
	this->m_cmdListDVC->AssociateModel(m_cmdListModel.get());

	// the various columns
	this->m_cmdListDVC->AppendToggleColumn("",
		PMBUSCMDListModel::Col_Toggle,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxDVC_TOGGLE_DEFAULT_WIDTH,
		wxALIGN_CENTER_HORIZONTAL,
		wxDATAVIEW_COL_REORDERABLE
		);

	this->m_cmdListDVC->AppendIconTextColumn("Register",
		PMBUSCMDListModel::Col_RegisterIconText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_SORTABLE);

	this->m_cmdListDVC->AppendTextColumn("Name",
		PMBUSCMDListModel::Col_NameText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

	this->m_cmdListDVC->AppendTextColumn("Access",
		PMBUSCMDListModel::Col_AccessText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_CENTER_HORIZONTAL,
		wxDATAVIEW_COL_SORTABLE);

	this->m_cmdListDVC->AppendTextColumn("Query",
		PMBUSCMDListModel::Col_QueryText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_CENTER_HORIZONTAL,
		wxDATAVIEW_COL_SORTABLE);

	this->m_cmdListDVC->AppendTextColumn("Cook",
		PMBUSCMDListModel::Col_CookText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		350,
		wxALIGN_CENTER_HORIZONTAL,
		wxCOL_RESIZABLE);

	this->m_cmdListDVC->AppendTextColumn("Raw",
		PMBUSCMDListModel::Col_RawText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_LEFT,
		wxCOL_RESIZABLE);

#if 0
	this->m_dataViewCtrl->AppendDateColumn("date",
		PSUDataViewListModel::Col_Date);

	m_attributes =
		new wxDataViewColumn("attributes",
		new wxDataViewTextRenderer,
		PSUDataViewListModel::Col_TextWithAttr,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_RIGHT,
		wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	this->m_dataViewCtrl->AppendColumn(m_attributes);

	this->m_dataViewCtrl->AppendColumn(
		new wxDataViewColumn("custom renderer",
		new MyCustomRenderer(wxDATAVIEW_CELL_EDITABLE),
		PSUDataViewListModel::Col_Custom)
		);
#endif

	this->m_subNotebook->AddPage(this->m_stdPage, "STD");
	this->m_subNotebook->AddPage(this->ReadPanel, "Read");
	//this->m_subNotebook->AddPage(this->m_PMBusData[0].m_writePage, "Write"); // Don't show write page after APP initialized
	//this->m_subNotebook->RemovePage(2);// Don't show write page after APP initialized

	this->m_subNotebook->SetMinSize(wxSize(-1, 200));
	this->m_cmdListDVC->SetMinSize(wxSize(-1, 200));

	// Setup Sizer
	GeneralPanelTopLevelSizer = new wxBoxSizer(wxVERTICAL);
	GeneralPanelSz = new wxBoxSizer(wxHORIZONTAL);
	
	// Setup CMDListPanel
	CMDListSizer = new wxBoxSizer(wxHORIZONTAL);
	CMDListSizer->Add(this->m_cmdListDVC, 1, wxEXPAND | wxALL);

	this->CMDListPanel->SetSizerAndFit(CMDListSizer);

	// Setup DebugLogPanel
	m_debugLogStaticBoxSizer->Add(this->m_debugLogTC, 1, wxEXPAND | wxALL);

	this->DebugLogPanel->SetSizerAndFit(this->m_debugLogStaticBoxSizer);

	//
	m_splitterWindow->SplitVertically(m_subNotebook, this->CMDListPanel, 0);// Add SubNoteBook & CMDListPanel to Splitter Window

	m_splitterWindowTopLevel->SplitHorizontally(m_splitterWindow, this->DebugLogPanel, 0);

	//GeneralPanelSz->Add(m_subNotebook, wxSizerFlags(2).Expand());//2, wxGROW | wxALL, 0);
	//GeneralPanelSz->Add(this->CMDListPanel, wxSizerFlags(8).Expand());//wxGROW | wxALL, 0);
	GeneralPanelSz->Add(m_splitterWindowTopLevel, 1, wxEXPAND);

	GeneralPanelTopLevelSizer->Add(GeneralPanelSz, wxSizerFlags(1).Expand());
	//GeneralPanelTopLevelSizer->Add(m_header, wxSizerFlags(0).Expand());
	//GeneralPanelTopLevelSizer->Add(this->DebugLogPanel, wxSizerFlags(2).Expand());//wxSizerFlags(1).Expand());
	
	parent->SetSizerAndFit(GeneralPanelTopLevelSizer);

}

void MainFrame::SetupTIHexMMAPDVL(wxPanel* parent, TIHexFileParser* tiHexFileParser){
	
	wxASSERT(!this->m_tiHexMMAPDVC && !this->m_tiHexMMAPModel);
	
	this->m_tiHexMMAPDVC = new wxDataViewCtrl(parent, ID_ATTR_CTRL, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	this->m_tiHexMMAPDVC->SetFont(font);

	this->m_tiHexMMAPModel = new TIHexMMAPModel( 1024, &this->m_SecondaryTIHexFileStat);
	this->m_tiHexMMAPDVC->AssociateModel(m_tiHexMMAPModel.get());

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

	this->m_secondaryFWMMAPPanelTopLevelSizer = new wxBoxSizer(wxVERTICAL);

	this->m_secondaryFWMMAPPanelTopLevelSizer->Add(this->m_tiHexMMAPDVC, wxSizerFlags(1).Expand());

	parent->SetSizerAndFit(this->m_secondaryFWMMAPPanelTopLevelSizer);

	// Add page to NoteBook
	m_notebook->AddPage(parent, "Secondary FW MMAP", true);

}

void MainFrame::OnContextMenu(wxDataViewEvent &event){
	// Show Popup Menu
	this->m_cmdListDVC->PopupMenu(this->m_cmdListPopupMenu);
}

unsigned int MainFrame::getCurrentUseIOInterface(void){
	return this->m_CurrentUseIOInterface;
}

void MainFrame::OnDVSelectionChanged(wxDataViewEvent &event)
{

#if 0
	//wxString title;// = m_list_model->GetTitle(event.GetItem());
	//if (title.empty())
		//title = "None";

	PSU_DEBUG_PRINT(MSG_DETAIL, "m_subNotebook Get PageCount: %d", this->m_subNotebook->GetPageCount());
	if (this->m_subNotebook->GetPageCount() == 3){
		this->m_subNotebook->RemovePage(2);
	}
	else{
		this->m_subNotebook->AddPage(this->WritePanel, "Write");
	}
#endif

	wxDataViewItem item = event.GetItem();

	//PSUDataViewListModel* model = (PSUDataViewListModel*)this->m_dataViewCtrl->GetModel();

	int row = m_cmdListModel->GetRow(item);

	PSU_DEBUG_PRINT(MSG_DEBUG, "Selected Row is : %d", row);
	PSU_DEBUG_PRINT(MSG_DEBUG, "CMD's RW Attribute is : %d", this->m_PMBusData[row].m_access);

	switch (this->m_PMBusData[row].m_access){

	case cmd_access_read:
	case cmd_access_br:
		if (this->m_subNotebook->GetPageCount() == 3){
			this->m_subNotebook->RemovePage(2);
		}

		this->m_subNotebook->SetSelection(0);

		break;

	case cmd_access_write:
	case cmd_access_bw:
	case cmd_access_readwrite:
	case cmd_access_brbw:

		switch (this->m_subNotebook->GetPageCount()){
		
		case 2:
			if (this->m_PMBusData[row].m_writePage != NULL){
				this->m_subNotebook->AddPage(this->m_PMBusData[row].m_writePage, "Write");
				this->m_subNotebook->SetSelection(2);
			}


			break;

		case 3:

			this->m_subNotebook->RemovePage(2);
			if (this->m_PMBusData[row].m_writePage != NULL){
				this->m_subNotebook->AddPage(this->m_PMBusData[row].m_writePage, "Write");
				this->m_subNotebook->SetSelection(2);
			}

			break;

		default:
			PSU_DEBUG_PRINT(MSG_ALERT, "Page Count = %d", this->m_subNotebook->GetPageCount());
			break;
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs, Access=%d", this->m_PMBusData[row].m_access);
		break;
	}

}

void MainFrame::OnDisableAll(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DETAIL, "Disable ALL Commands");
	// Disable ALL Command
	for (unsigned int idx = 0; idx<PMBUSCOMMAND_SIZE; idx++){
		this->m_PMBusData[idx].m_toggle = false;
	}

	wxVariant variant;
	variant = false;

	for (unsigned int idx = 0; idx<PMBUSCOMMAND_SIZE; idx++){
		this->m_cmdListModel->SetValueByRow(variant, idx, PMBUSCMDListModel::Col_Toggle);
		this->m_cmdListModel->RowValueChanged(idx, PMBUSCMDListModel::Col_Toggle);
	}
}

void MainFrame::OnEnableAll(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DETAIL, "Enable ALL Commands");
	// Enable ALL Command
	for (unsigned int idx = 0; idx<PMBUSCOMMAND_SIZE; idx++){
		this->m_PMBusData[idx].m_toggle = true;
	}

	wxVariant variant;
	variant = true;

	for (unsigned int idx = 0; idx<PMBUSCOMMAND_SIZE; idx++){
		this->m_cmdListModel->SetValueByRow(variant, idx, PMBUSCMDListModel::Col_Toggle);
		this->m_cmdListModel->RowValueChanged(idx, PMBUSCMDListModel::Col_Toggle);
	}
}

void MainFrame::DoSetupIOAccess(void){
	// Setup IOAccess Sturct Member
	// Serial Port
	this->m_IOAccess[IOACCESS_SERIALPORT].m_EnumerateAvailableDevice = EnumerateAvailableSerialPort;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_GetDeviceStatus = GetSerialPortStatus;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_GetOpenDeviceName = GetSerialPortOpenDeviceName;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_OpenDevice = OpenSerialPort;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_CloseDevice = CloseSerialPort;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_DeviceSendData = SerialSendData;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_DeviceReadData = SerialReadData;

	// HID
	this->m_IOAccess[IOACCESS_HID].m_EnumerateAvailableDevice = EnumerateAvailableHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_GetDeviceStatus = GetHIDDeviceStatus;
	this->m_IOAccess[IOACCESS_HID].m_GetOpenDeviceName = GetHIDOpenDeviceName;
	this->m_IOAccess[IOACCESS_HID].m_OpenDevice = OpenHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_CloseDevice = CloseHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_DeviceSendData = HIDSendData;
	this->m_IOAccess[IOACCESS_HID].m_DeviceReadData = HIDReadData;
}

void MainFrame::UpdateStatusBarIOSettingFiled(wxString io_string){
	this->m_status_bar->SetStatusText(io_string, PMBUSStatusBar::Field_IO_Setting);
}

int MainFrame::SetIODeviceOption(void){

	this->m_portSetting.m_comportNumber = this->m_appSettings.m_comportSetting.m_comportNumber;
	this->m_portSetting.m_buadRate = this->m_appSettings.m_comportSetting.m_buadRate;
	this->m_portSetting.m_byteSize = this->m_appSettings.m_comportSetting.m_byteSize;
	this->m_portSetting.m_parityCheck = this->m_appSettings.m_comportSetting.m_parityCheck;
	this->m_portSetting.m_stopBits = this->m_appSettings.m_comportSetting.m_stopBits;

	return EXIT_SUCCESS;
}

int MainFrame::OpenIODevice(void){
	
	int ret = EXIT_FAILURE;

	//PSU_DEBUG_PRINT(MSG_DEBUG, "m_ioDeviceOpen = %d", m_ioDeviceOpen);

	//if (this->m_ioDeviceOpen == false){
		// Open Device
		PSU_DEBUG_PRINT(MSG_DEBUG, "this->m_CurrentUseIOInterface].m_GetDeviceStatus() = %d", this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus());

		if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_CLOSE) {
			this->m_IOAccess[this->m_CurrentUseIOInterface].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);

			this->SetIODeviceOption();
			ret = this->m_IOAccess[this->m_CurrentUseIOInterface].m_OpenDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT, &this->m_portSetting);

			if (ret != EXIT_SUCCESS){
				PSU_DEBUG_PRINT(MSG_DEBUG, "Open IO Device Failed !");
			}
			else{
				//this->m_ioDeviceOpen = true;

				// Append Comport Number
				wxString openDeviceName(this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetOpenDeviceName());
				//openDeviceName += wxT("-9600-N81");
				
				// Append BuadRate
				switch (this->m_appSettings.m_comportSetting.m_buadRate){
	
				case CBR_110:
					openDeviceName += wxString::Format("-%d-", 110);
					break;

				case CBR_300:
					openDeviceName += wxString::Format("-%d-", 300);
					break;

				case CBR_600:
					openDeviceName += wxString::Format("-%d-", 600);
					break;

				case CBR_1200:
					openDeviceName += wxString::Format("-%d-", 1200);
					break;

				case CBR_2400:
					openDeviceName += wxString::Format("-%d-", 2400);
					break;

				case CBR_4800:
					openDeviceName += wxString::Format("-%d-", 4800);
					break;

				case CBR_9600:
					openDeviceName += wxString::Format("-%d-", 9600);
					break;

				case CBR_14400:
					openDeviceName += wxString::Format("-%d-", 14400);
					break;

				case CBR_19200:
					openDeviceName += wxString::Format("-%d-", 19200);
					break;

				case CBR_38400:
					openDeviceName += wxString::Format("-%d-", 38400);
					break;

				case CBR_56000:
					openDeviceName += wxString::Format("-%d-", 56000);
					break;

				case CBR_57600:
					openDeviceName += wxString::Format("-%d-", 57600);
					break;
	
				case CBR_115200:
					openDeviceName += wxString::Format("-%d-", 115200);
					break;

				default:
					PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
					break;
				}

				// Append Parity Check
				switch (this->m_appSettings.m_comportSetting.m_parityCheck){

				case NOPARITY:
					openDeviceName += wxString::Format("%s", "N");
					break;

				case ODDPARITY:
					openDeviceName += wxString::Format("%s", "O");
					break;

				case EVENPARITY:
					openDeviceName += wxString::Format("%s", "E");
					break;

				case MARKPARITY:
					openDeviceName += wxString::Format("%s", "M");
					break;
				case SPACEPARITY:
					openDeviceName += wxString::Format("%s", "S");
					break;

				default:
					PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
					break;
				}
				
				// Append Byte Bits
				openDeviceName += wxString::Format("%d", this->m_appSettings.m_comportSetting.m_byteSize);

				// Append Stop Bits
				switch (this->m_appSettings.m_comportSetting.m_stopBits){

				case ONESTOPBIT:
					openDeviceName += wxString::Format("%d", 1);
					break;

				case ONE5STOPBITS:
					openDeviceName += wxString::Format("%f", 1.5);
					break;

				case TWOSTOPBITS:
					openDeviceName += wxString::Format("%d", 2);
					break;

				default:
					PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
					break;
				}

				this->UpdateStatusBarIOSettingFiled(openDeviceName);
			}
		}
	//}

	return ret;
}

int MainFrame::CloseIODevice(void){
	
	int ret = EXIT_FAILURE;

	//if (this->m_ioDeviceOpen == true){
		// Close IO Device
		if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_OPEN){
			ret = this->m_IOAccess[this->m_CurrentUseIOInterface].m_CloseDevice();

			if (ret != EXIT_SUCCESS){
				PSU_DEBUG_PRINT(MSG_FATAL, "Close IO Device Failed !");
			}
			else{
				//this->m_ioDeviceOpen = false;
				this->UpdateStatusBarIOSettingFiled(wxString("Disconnect"));
			}
		}

	//}

	return ret;
}

unsigned int MainFrame::findPMBUSCMDIndex(unsigned int cmd_register){

	unsigned int index = 0;

	for (unsigned int idx = 0; idx < PMBUSCOMMAND_SIZE; idx++){
		if (this->m_PMBusData[idx].m_register == cmd_register){
			index = idx;
			break;
		}
	}

	return index;
}

void MainFrame::TaskInit(void){
	// Task Init 
}

void MainFrame::OnSendThreadCompletion(wxThreadEvent& event)
{
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
	this->m_sendThreadStopFlag = true;

	// Reset Monitor Parameters
	this->m_monitor_running = false;

	this->m_toolbar->FindById(MENU_ID_Monitor)->SetNormalBitmap(*this->m_monitorBitmap);
	this->m_monitorMenuItem->SetBitmap(*m_monitor16Bitmap);
	this->m_toolbar->Realize();

	(this->m_status_bar->getTimer())->Stop();
}

void MainFrame::OnSendThreadUpdate(wxThreadEvent& event)
{
	//PSU_DEBUG_PRINT(MSG_ALERT, "MYFRAME: MyThread update!");
}

int MainFrame::SaveCMDListToFile(wxTextOutputStream& textOutputStream){
	wxVariant Value;
	wxString registerValue("");
	wxString line("");
	wxDataViewItem dataViewItem;

	char* format[6] = {
		"%-12s",
		"%-30s",
		"%-9s",
		"%-8s",
		"%-140s",
		"%s"
	};

	wxString header = wxString::Format("%-12s%-30s%-9s%-8s%-140s%s", "Register", "Name", "Access", "Query", "Cook", "Raw");

	textOutputStream << header;
	textOutputStream << endl;

	for (unsigned int row_idx = 0; row_idx < PMBUSCOMMAND_SIZE; row_idx++){

		registerValue = wxString::Format("%-12s", this->m_PMBusData[row_idx].m_label);

		line += wxString::Format(format[0], registerValue);
		PSU_DEBUG_PRINT(MSG_DEBUG, "%-12s", registerValue.c_str());

		for (unsigned int column_idx = 2; column_idx < PMBUSCMDListModel::Col_Max - 3; column_idx++){
			this->m_cmdListModel->GetValueByRow(Value, row_idx, column_idx);
			
			line += wxString::Format(format[column_idx-1], Value.GetString().c_str());

			PSU_DEBUG_PRINT(MSG_DEBUG, "%s", Value.GetString().c_str());
		}

		textOutputStream << line;
		textOutputStream << endl;

		line.Clear();
	}

	return EXIT_SUCCESS;
}

void MainFrame::CheckAndLoadConfig(void){
	
	wxConfigBase::Set(new wxFileConfig(wxT(""), wxT(""), wxT("psu.ini"), wxT(""), wxCONFIG_USE_RELATIVE_PATH));

	wxConfigBase *pConfig = wxConfigBase::Get();

	pConfig->SetPath(wxT("/APP"));
	
	// I2C Slave Address
	long i2cSlaveAddr;
	if (pConfig->Read(wxT("I2CSlaveAddress"), &i2cSlaveAddr) == false){
		pConfig->Write(wxT("I2CSlaveAddress"), DEFAULT_I2C_SLAVEADDRESS);
		this->m_appSettings.m_I2CSlaveAddress = DEFAULT_I2C_SLAVEADDRESS;
	}
	else{
		this->m_appSettings.m_I2CSlaveAddress = i2cSlaveAddr;
	}
	PMBUSHelper::SetSlaveAddress(this->m_appSettings.m_I2CSlaveAddress);

	// Run Mode
	long runMode;
	if (pConfig->Read(wxT("RunMode"), &runMode) == false){
		pConfig->Write(wxT("RunMode"), DEFAULT_RUN_MODE);
		this->m_appSettings.m_runMode = DEFAULT_RUN_MODE;
	}
	else{
		this->m_appSettings.m_runMode = runMode;
	}

	// Iterations
	long iterationsValue;
	if (pConfig->Read(wxT("Iterations"), &iterationsValue) == false){
		pConfig->Write(wxT("Iterations"), DEFAULT_ITERATIONS_VALUE);
		this->m_appSettings.m_IterationsValue = DEFAULT_ITERATIONS_VALUE;
	}
	else{
		this->m_appSettings.m_IterationsValue = iterationsValue;
	}

	pConfig->SetPath(wxT("/LOG"));
	
	// Log Mode
	long logMode;
	if (pConfig->Read(wxT("LogMode"), &logMode) == false){
		pConfig->Write(wxT("LogMode"), DEFAULT_LOG_MODE);
		this->m_appSettings.m_logMode = DEFAULT_LOG_MODE;
	}
	else{
		this->m_appSettings.m_logMode = logMode;
	}

	// Log To File
	long logToFile;
	if (pConfig->Read(wxT("LogToFile"), &logToFile) == false){
		pConfig->Write(wxT("LogToFile"), DEFAULT_LOG_TO_FILE);
		this->m_appSettings.m_logToFile = DEFAULT_LOG_TO_FILE;
	}
	else{
		this->m_appSettings.m_logToFile = logToFile;
	}

	// Log File Path
	wxString logFilePath;
	if (pConfig->Read(wxT("LogFilePath"), &logFilePath) == false){
		pConfig->Write(wxT("LogFilePath"), DEFAULT_LOG_FILE_PATH);
		this->m_appSettings.m_logFilePath = wxString::Format("%s", DEFAULT_LOG_FILE_PATH);
	}
	else{
		this->m_appSettings.m_logFilePath = wxString::Format("%s", logFilePath);
	}

	if (this->m_appSettings.m_logToFile == Generic_Enable){
		this->ReInitLogFileOutputStream(this->m_appSettings.m_logFilePath);
	}

	pConfig->SetPath(wxT("/PMBUS"));
	long pmbusReadMethod;
	if (pConfig->Read(wxT("PMBUSReadMethod"), &pmbusReadMethod) == false){
		pConfig->Write(wxT("PMBUSReadMethod"), DEFAULT_PMBUS_READ_METHOD);
		this->m_appSettings.m_pmbusReadMethod = DEFAULT_PMBUS_READ_METHOD;
	}
	else{
		this->m_appSettings.m_pmbusReadMethod = pmbusReadMethod;
	}

	pConfig->SetPath(wxT("/COMPORT"));

	// Comport Number
	long comportNumber;
	if (pConfig->Read(wxT("NUMBER"), &comportNumber) == false){
		pConfig->Write(wxT("NUMBER"), DEFAULT_COMPORT_NUM);
		this->m_appSettings.m_comportSetting.m_comportNumber = DEFAULT_COMPORT_NUM;
	}
	else{
		this->m_appSettings.m_comportSetting.m_comportNumber = comportNumber;
	}

	// Buad Rate
	long buadRate;
	if (pConfig->Read(wxT("BUADRATE"), &buadRate) == false){
		pConfig->Write(wxT("BUADRATE"), DEFAULT_COMPORT_BUADRATE);
		this->m_appSettings.m_comportSetting.m_buadRate = DEFAULT_COMPORT_BUADRATE;
	}
	else{
		this->m_appSettings.m_comportSetting.m_buadRate = buadRate;
	}

	// Byte Size
	long byteSize;
	if (pConfig->Read(wxT("BYTESIZE"), &byteSize) == false){
		pConfig->Write(wxT("BYTESIZE"), DEFAULT_COMPORT_BYTESIZE);
		this->m_appSettings.m_comportSetting.m_byteSize = DEFAULT_COMPORT_BYTESIZE;
	}
	else{
		this->m_appSettings.m_comportSetting.m_byteSize = byteSize;
	}

	// Stop Bits
	long stopBits;
	if (pConfig->Read(wxT("STOPBITS"), &stopBits) == false){
		pConfig->Write(wxT("STOPBITS"), DEFAULT_COMPORT_STOPBITS);
		this->m_appSettings.m_comportSetting.m_stopBits = DEFAULT_COMPORT_STOPBITS;
	}
	else{
		this->m_appSettings.m_comportSetting.m_stopBits = stopBits;
	}

	// Parity Check
	long parityCheck;
	if (pConfig->Read(wxT("PARITYCHECK"), &parityCheck) == false){
		pConfig->Write(wxT("PARITYCHECK"), DEFAULT_COMPORT_PARITYCHECK);
		this->m_appSettings.m_comportSetting.m_parityCheck = DEFAULT_COMPORT_PARITYCHECK;
	}
	else{
		this->m_appSettings.m_comportSetting.m_parityCheck = parityCheck;
	}

	pConfig->SetPath(wxT("/MISC"));
	
	bool firstRun;
	if (pConfig->Read(wxT("First"), &firstRun) == false){
		pConfig->Write(wxT("FirstRun"), true);
		#if 0
		wxMessageBox(
		wxT("This is The Fisrt Time You Run This Program \n")
		wxT(""), wxT("INFORMATION"),
		wxICON_INFORMATION | wxOK);
		#endif
	}
}

void MainFrame::SaveConfig(void){

	wxConfigBase *pConfig = wxConfigBase::Get();

	if (pConfig==NULL) return;

	pConfig->SetPath(wxT("/APP"));

	// I2C Slave Address
	pConfig->Write(wxT("I2CSlaveAddress"), this->m_appSettings.m_I2CSlaveAddress);

	// Run Mode
	pConfig->Write(wxT("RunMode"), this->m_appSettings.m_runMode);

	// Iterations
	pConfig->Write(wxT("Iterations"), this->m_appSettings.m_IterationsValue);

	pConfig->SetPath(wxT("/LOG"));

	// Log Mode
	pConfig->Write(wxT("LogMode"), this->m_appSettings.m_logMode);
	
	// Log To File
	pConfig->Write(wxT("LogToFile"), this->m_appSettings.m_logToFile);

	// Log File Path
	pConfig->Write(wxT("LogFilePath"), this->m_appSettings.m_logFilePath);

	pConfig->SetPath(wxT("/PMBUS"));

	// PM Bus Read Method
	pConfig->Write(wxT("PMBUSReadMethod"), this->m_appSettings.m_pmbusReadMethod);

	pConfig->SetPath(wxT("/COMPORT"));

	// Comport Number
	pConfig->Write(wxT("NUMBER"), this->m_appSettings.m_comportSetting.m_comportNumber);

	// Buad Rate
	pConfig->Write(wxT("BUADRATE"), this->m_appSettings.m_comportSetting.m_buadRate);

	// Byte Size
	pConfig->Write(wxT("BYTESIZE"), this->m_appSettings.m_comportSetting.m_byteSize);

	// Stop Bits
	pConfig->Write(wxT("STOPBITS"), this->m_appSettings.m_comportSetting.m_stopBits);

	// Parity Check
	pConfig->Write(wxT("PARITYCHECK"), this->m_appSettings.m_comportSetting.m_parityCheck);

	// Delete wxConfig Object
	delete wxConfigBase::Set((wxConfigBase *)NULL);

}

void MainFrame::ReInitLogFileOutputStream(wxString dirPath){

	wxString logFilePath = dirPath;

	wxString logFileName("Log-");

	wxString dateStr("");
	PMBUSHelper::GetNowDateTimeString(dateStr);

	logFileName += dateStr;

	logFilePath += logFileName;

	logFilePath += wxT(".txt");

	//PSU_DEBUG_PRINT(MSG_ALERT, "logFilePath=%s", logFilePath.c_str());

	if (this->m_logFileFFileOutputStream) delete this->m_logFileFFileOutputStream;
	if (this->m_logFileTextOutputStream) delete this->m_logFileTextOutputStream;

	if (!this->m_logFileFFileOutputStream){
		this->m_logFileFFileOutputStream = new wxFFileOutputStream(logFilePath);

		if (!this->m_logFileFFileOutputStream->IsOk()){
			//PSU_DEBUG_PRINT(MSG_ALERT, "Cann't Open Log File : %s", logFilePath.c_str());
		}

		if (!this->m_logFileTextOutputStream){
			this->m_logFileTextOutputStream = new wxTextOutputStream(*this->m_logFileFFileOutputStream);
		}
		
		// Test
		//*this->m_logFileTextOutputStream << "TEST LOG File" << endl;
		//this->m_logFileTextOutputStream->Flush();
	}

}

