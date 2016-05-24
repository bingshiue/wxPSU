/**
 * @file MainFrame.cpp
 */

#include "MainFrame.h"
#include "MyListStoreDerivedModel.h"
#include "PMBUSCommand.h"
#include "PMBUSCMDCB.h"
#include "PMBusCMDGridTable.h"
#include "sample.xpm"

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{	
	int ret;
	
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

	// Setup Icon
	SetIcon(sample_xpm);

	// Setup PMNBusCommand Data
	SetupPMBusCommandData();

	// Get old logger
	m_oldLogger = wxLog::GetActiveTarget();
	
	// Setup Menu
	SetupMenuBar();

	// Setup ToolBar
	SetupToolBar();

	// Setup StatusBar
	SetupStatusBar();

	//CreateStatusBar();
	//SetStatusText("PSU Tool");

	// create the logging text control and a header showing the meaning of the
	// different columns
	wxTextCtrl *header = new wxTextCtrl(this, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize,
		wxTE_READONLY);
	DoLogLine(header, "  Time", " Thread", "          Message");
	m_txtctrl = new wxTextCtrl(this, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize,
		wxTE_MULTILINE | wxTE_READONLY);
	wxLog::SetActiveTarget(this);

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	header->SetFont(font);
	m_txtctrl->SetFont(font);
	m_txtctrl->SetFocus();

	//
#if 0 /**< Grid */
	m_grid = new wxGrid(this, wxID_ANY);
	m_table = new PMBusCMDGridTable();
	m_table->SetAttrProvider(new MyGridCellAttrProvider);
	m_grid->SetTable(m_table, true);

	wxGridCellAttr *attrRO = new wxGridCellAttr,
		*attrRangeEditor = new wxGridCellAttr,
		*attrCombo = new wxGridCellAttr;

	attrRO->SetReadOnly();
	attrRangeEditor->SetEditor(new wxGridCellNumberEditor(1, 5));
	attrCombo->SetEditor(new wxGridCellChoiceEditor(WXSIZEOF(severities),
		severities));

	m_grid->SetColAttr(Col_Id, attrRO);
	m_grid->SetColAttr(Col_Priority, attrRangeEditor);
	m_grid->SetColAttr(Col_Severity, attrCombo);

	m_grid->Fit();
	//SetClientSize(m_grid->GetSize());
#endif

	this->m_notebook = new wxNotebook(this, wxID_ANY);

	this->GeneralPanel = new wxPanel(m_notebook, wxID_ANY);
	
	SetupPSUDataView(GeneralPanel);

	this->PMBusStatusPanel = new wxPanel(m_notebook, wxID_ANY);

	this->PMBusMFR = new wxPanel(m_notebook, wxID_ANY);

	this->VerificationPanel = new wxPanel(m_notebook, wxID_ANY);

	this->STATUSPanel = new wxPanel(m_notebook, wxID_ANY);

	// Add each panl into notebook component
	m_notebook->AddPage(this->GeneralPanel, "General");
	m_notebook->AddPage(this->PMBusStatusPanel, "PM Bus Status");
	m_notebook->AddPage(this->PMBusMFR, "PMBus MFR");
	m_notebook->AddPage(this->VerificationPanel, "Verification");
	m_notebook->AddPage(this->STATUSPanel, "STATUS(DCH)");

	//Connect(ID_Hello, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnHello));
	//Connect(ID_Monitor, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnMonitor));
	//Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnAbout));
	//Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnExit));

	//this->m_topVeriticalSizer->Add(this->m_toolbar);
	//this->m_topVeriticalSizer->Add(this->m_hbox, wxSizerFlags(1).Expand());//1, wxEXPAND | (wxALL & ~wxLEFT), 1);
	//this->m_topVeriticalSizer->Add(this->m_dataViewCtrl, wxSizerFlags(1).Expand());
	this->m_topVeriticalSizer->Add(this->m_notebook, 7, wxEXPAND | wxALL, 1);
	this->m_topVeriticalSizer->Add(header, wxSizerFlags(0).Expand());
	this->m_topVeriticalSizer->Add(this->m_txtctrl, 2, wxEXPAND | wxALL, 1);//wxSizerFlags(1).Expand());
	//this->m_parent->SetSizer(this->m_topVeriticalSizer, true);

	SetSizer(this->m_topVeriticalSizer);
	//SetSizerAndFit(this->m_topVeriticalSizer);

	// Put Window in Center
	Centre();

	this->m_polling_time = wxAtoi(m_polling_time_combobox->GetValue());


	// Open Device
	this->m_IOAccess[this->m_CurrentUseIOInterface].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);
	ret = this->m_IOAccess[this->m_CurrentUseIOInterface].m_OpenDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);

	if(ret != EXIT_SUCCESS){
		PSU_DEBUG_PRINT(MSG_FATAL, "Open IO Device Failed ! Need add error handle mechanism here");
	}

#if 0 // Open Serial Port
	// Enumerate Serial Port
	EnumerateAvailableSerialPort(this->m_enumSerialPort, SERIAL_PORT_MAX_COUNT);

	// Initial Serial Port
	ret = OpenSerialPort(this->m_enumSerialPort, SERIAL_PORT_MAX_COUNT);

	// If Open Serial Port Failed
	if (ret != EXIT_SUCCESS){
		PSU_DEBUG_PRINT(MSG_FATAL, "Open Serial Port Failed ! Need add error handle mechanism here");
	}
#endif

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
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(MENU_ID_Secondary_Firmware, MainFrame::OnSecondaryFirmwarwe)
EVT_MENU(MENU_ID_Monitor, MainFrame::OnMonitor)
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

EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_DATAVIEW_SELECTION_CHANGED(ID_ATTR_CTRL, MainFrame::OnDVSelectionChanged)
//EVT_DATAVIEW_ITEM_VALUE_CHANGED(ID_ATTR_CTRL, MainFrame::OnValueChanged)
EVT_COMBOBOX(ID_POLLING_TIME_COMBO, MainFrame::OnPollingTimeCombo)
wxEND_EVENT_TABLE()

MainFrame::~MainFrame()
{		
	wxLog::SetActiveTarget(m_oldLogger);
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

void MainFrame::OnExit(wxCommandEvent& event)
{
	if (this->m_monitor_running == true){

		wxMessageDialog *closeWarning = new wxMessageDialog(NULL, L"Monitor Still Running, Please Stop It !", L"Warning", wxOK | wxICON_WARNING);
		closeWarning->ShowModal();

		return;
	}
	
	//this->m_IOPortReadCMDThread->m_running = false;

	//this->m_IOPortReadCMDThread->Kill();
	
	// Close IO Device
	this->m_IOAccess[this->m_CurrentUseIOInterface].m_CloseDevice();

#if 0
	// Close Serial Port
	CloseSerialPort();
#endif

	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Acbel PSU Tool",
		"Acbel", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnSecondaryFirmwarwe(wxCommandEvent& event)
{
	PSU_DEBUG_PRINT(MSG_ALERT,"Not Implement");
}

void MainFrame::OnUpdateSecondaryFirmware(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
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
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnResetMaxMinValue(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnResetRunTime(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnEnableCalibration(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnDisableCalibration(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnCalibration(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnAdministrant(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnI2CInterface(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnContinually(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnIterations(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnStopAnError(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnErrorLogALL(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnErrorLogErrorOnly(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnLogToFile(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnPMBus1_1(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnPMBus1_2(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnMonitor(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG,  "Polling Time = %d", this->m_polling_time);
	PSU_DEBUG_PRINT(MSG_DETAIL, "m_monitor_running = %d", this->m_monitor_running);

	int loop = 0;

	//PSU_DEBUG_PRINT("Available = %d", this->m_list_model.get()->getAvailable()[0]);

	// Start Send Data Thread
	if (this->m_monitor_running == false){
		this->m_monitor_running = true;
		(this->m_status_bar->getTimer())->Start();
		this->m_status_bar->getBeginDateTime() = wxDateTime::Now();

		PSU_DEBUG_PRINT(MSG_DETAIL, "Start Send Data Thread");
		this->m_IOPortSendCMDThread = new IOPortSendCMDThread(this->m_IOAccess, &this->m_CurrentUseIOInterface, this->m_rxTxSemaphore, &this->m_runMode, &this->m_polling_time, this->m_PMBusData, &this->m_IOPortRecvBuff, &m_list_model, this->m_status_bar, this->m_stdPage);
		//this->m_serialPortSendCommandThread->SetPriority(wxPRIORITY_MIN);

		// If Create Thread Success
		if (this->m_IOPortSendCMDThread->Create() != wxTHREAD_NO_ERROR){
			PSU_DEBUG_PRINT(MSG_FATAL, "Can't Create Send Command Thread");
		}
		else{
			this->m_IOPortSendCMDThread->Run();
		}

	}
	else{ // One Send Command Thread is Running
		this->m_monitor_running = false;
		(this->m_status_bar->getTimer())->Stop();
		PSU_DEBUG_PRINT(MSG_DETAIL, "Stop Send Data Thread");
		this->m_IOPortSendCMDThread->m_running = false;
	}

}

void MainFrame::DoLogLine(wxTextCtrl *text,
const wxString& timestr,
const wxString& threadstr,
const wxString& msg)
{
	text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));
}

void
MainFrame::DoLogRecord(wxLogLevel level,
const wxString& msg,
const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}

	DoLogLine
		(
		m_txtctrl,
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
	unsigned int row = m_list_model->GetRow(event.GetItem());//GetTitle(event.GetItem());
	PSU_DEBUG_PRINT(MSG_DETAIL, "wxEVT_DATAVIEW_ITEM_VALUE_CHANGED");// , Item Id : %s;  Column: %d",
	//title, event.GetColumn());
}

void MainFrame::OnPollingTimeCombo(wxCommandEvent& event){
	this->m_polling_time = wxAtoi(m_polling_time_combobox->GetValue());
	PSU_DEBUG_PRINT(MSG_ALERT, "Select Polling Time is %d", this->m_polling_time);
	this->m_dataViewCtrl->SetFocus();
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
	this->m_fileMenu->Append(wxID_EXIT);

	// Run Menu
	/*
	Run
	|- Monitor
	|- In System Programming -> Update Secondary Firmware 
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

	this->m_runMenu->Append(this->m_monitorMenuItem);

	this->m_inSystemProgrammingMenu = new wxMenu();

	this->m_inSystemProgrammingMenu->Append(MENU_ID_Update_Secondary_Firmware, "&Update Secondary Firmware...\tCtrl-U",
		"Update Secondary Firmware");

	this->m_runMenu->AppendSubMenu(this->m_inSystemProgrammingMenu, wxT("In System Prpgramming"), wxT("In System Programming"));

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

	this->m_ResetMaxMinValueMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Reset_MaxMin_Value, wxT("Reset Max./Min/ Value"),
		wxT("Reset Max./Min/ Value"), wxITEM_NORMAL);

	this->m_ResetRunTimeMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Reset_Run_Time, wxT("Reset Run Time"),
		wxT("Reset Run Time"), wxITEM_NORMAL);

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

	this->m_DisableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_DisableCalibration, wxT("Disable Calibration"),
		wxT("Disable Calibration"), wxITEM_NORMAL);

	this->m_psuMenu->Append(m_EnableCalibrationMenuItem);
	this->m_psuMenu->Append(m_DisableCalibrationMenuItem);

	this->m_psuMenu->AppendSeparator();

	this->m_CalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Calibration, wxT("Calibration"),
		wxT("Calibration Setting"), wxITEM_NORMAL);

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

	this->m_AdministrantMenuItem = m_DisableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Administrant, wxT("Administrant..."),
		wxT("Administrant"), wxITEM_NORMAL);

	this->m_optionMenu->Append(this->m_AdministrantMenuItem);
	this->m_optionMenu->AppendSeparator();

	this->m_I2CInterfaceMenuItem = m_DisableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_I2C_Interface, wxT("I2C Interface..."),
		wxT("I2C Interface"), wxITEM_NORMAL);

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

	this->m_optionMenu->AppendSubMenu(this->m_runModeMenu, wxT("Run Mode"), wxT("Run Mode"));
	
	this->m_allMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ErrorLog_ALL, wxT("All"),
		wxT("All"), wxITEM_CHECK);

	this->m_errorOnlyMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ErrorLog_ErrorOnly, wxT("Error Only"),
		wxT("Error Only"), wxITEM_CHECK);

	this->m_logToFileMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Log_To_File, wxT("Log To File"),
		wxT("Log To File"), wxITEM_NORMAL);

	this->m_errorLogMenu->Append(this->m_allMenuItem);
	this->m_errorLogMenu->Append(this->m_errorOnlyMenuItem);
	this->m_errorLogMenu->Append(this->m_logToFileMenuItem);

	this->m_optionMenu->AppendSubMenu(this->m_errorLogMenu, wxT("Error Log Mode"), wxT("Error Log Mode"));
	
	this->m_pmBus11MenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_PMBUS_1_1, wxT("PMBus1.1 (Single Mode)"),
		wxT("PMBus1.1 (Single Mode)"), wxITEM_CHECK);

	this->m_pmBus12MenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_PMBUS_1_2, wxT("PMBus1.2 (Page Plus Mode)"),
		wxT("PMBus1.2 (Page Plus Mode)"), wxITEM_CHECK);

	this->m_pmbusReadMethodMenu->Append(this->m_pmBus11MenuItem);
	this->m_pmbusReadMethodMenu->Append(this->m_pmBus12MenuItem);

	this->m_optionMenu->AppendSubMenu(this->m_pmbusReadMethodMenu, wxT("PMBus Read Method"), wxT("PMBus Read Method"));

	// Help Menu
	/*
	Help
	|- About
	*/
	this->m_helpMenu = new wxMenu();
	this->m_helpMenu->Append(wxID_ABOUT);

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

	// Append Monitor Button
	m_toolbar->AddTool(MENU_ID_Monitor, wxEmptyString, wxBITMAP(MONITOR), wxT("Monitor"), wxITEM_NORMAL);

	// Append Exit Button
	m_toolbar->AddTool(wxID_EXIT, wxEmptyString, wxBITMAP(EXIT), wxT("Exit Program"), wxITEM_NORMAL);

	// Append Separator
	m_toolbar->AddSeparator();

	// Append Interation
	m_iteration_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Iteration"));
	m_toolbar->AddControl(m_iteration_text, wxEmptyString);

	m_iteration_input = new wxTextCtrl(m_toolbar, wxID_ANY);
	m_iteration_input->SetLabel(wxT("100"));
	m_toolbar->AddControl(m_iteration_input, wxEmptyString);

	// Append Polling Time
	m_polling_time_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Polling Time(ms)"));
	m_toolbar->AddControl(m_polling_time_text, wxEmptyString);

	m_polling_time_combobox = new wxComboBox(m_toolbar, ID_POLLING_TIME_COMBO, wxEmptyString, wxDefaultPosition, wxSize(100, -1));
	m_polling_time_combobox->Append(wxT("   0"));
	m_polling_time_combobox->Append(wxT("  10"));
	m_polling_time_combobox->Append(wxT("  20"));
	m_polling_time_combobox->Append(wxT("  50"));
	m_polling_time_combobox->Append(wxT(" 100"));
	m_polling_time_combobox->Append(wxT(" 200"));
	m_polling_time_combobox->Append(wxT(" 300"));
	m_polling_time_combobox->Append(wxT(" 500"));
	m_polling_time_combobox->Append(wxT("1000"));
	m_polling_time_combobox->Append(wxT("1500"));

	m_polling_time_combobox->SetSelection(2);
	m_toolbar->AddControl(m_polling_time_combobox, wxEmptyString);

	// Append Address 
	m_address_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Address"));
	m_toolbar->AddControl(m_address_text, wxEmptyString);

	m_address_input = new wxTextCtrl(m_toolbar, wxID_ANY);
	m_address_input->SetLabel(wxT("B0"));
	m_toolbar->AddControl(m_address_input, wxEmptyString);

	// Append A2 A1 A0 Check Box
	m_a2_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A2, wxT("A2"), wxDefaultPosition, wxDefaultSize);
	m_toolbar->AddControl(m_a2_chkbox, wxEmptyString);

	m_a1_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A1, wxT("A1"), wxDefaultPosition, wxDefaultSize);
	m_toolbar->AddControl(m_a1_chkbox, wxEmptyString);

	m_a0_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A0, wxT("A0"), wxDefaultPosition, wxDefaultSize);
	m_toolbar->AddControl(m_a0_chkbox, wxEmptyString);

	m_toolbar->Realize();
}

void MainFrame::SetupStatusBar(void){
	this->m_status_bar = new PSUStatusBar(this);

	SetStatusBar(this->m_status_bar);

	PositionStatusBar();

}

void MainFrame::SetupPSUDataView(wxPanel* parent){
	
	wxASSERT(!this->m_dataViewCtrl && !m_list_model);
	this->m_dataViewCtrl = new wxDataViewCtrl(parent, ID_ATTR_CTRL, wxDefaultPosition,
		wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	m_list_model = new PSUDataViewListModel(this->m_PMBusData);
	this->m_dataViewCtrl->AssociateModel(m_list_model.get());

	// the various columns
	this->m_dataViewCtrl->AppendToggleColumn("",
		PSUDataViewListModel::Col_Toggle,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxDVC_TOGGLE_DEFAULT_WIDTH,
		wxALIGN_CENTER_HORIZONTAL,
		wxDATAVIEW_COL_REORDERABLE
		);

	this->m_dataViewCtrl->AppendIconTextColumn("Register",
		PSUDataViewListModel::Col_RegisterIconText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Name",
		PSUDataViewListModel::Col_NameText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Access",
		PSUDataViewListModel::Col_AccessText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_CENTER_HORIZONTAL,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Query",
		PSUDataViewListModel::Col_QueryText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_CENTER_HORIZONTAL,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Cook",
		PSUDataViewListModel::Col_CookText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		350,
		wxALIGN_CENTER_HORIZONTAL,
		wxCOL_RESIZABLE);

	this->m_dataViewCtrl->AppendTextColumn("Raw",
		PSUDataViewListModel::Col_RawText,
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

	// Setup Sub Notebook
	this->m_subNotebook = new wxNotebook(parent, wxID_ANY);

	//this->STDPanel   = new wxPanel(this->m_subNotebook, wxID_ANY);
	this->m_stdPage = new STDPage(this->m_subNotebook);
	this->ReadPanel  = new wxPanel(this->m_subNotebook, wxID_ANY);
	this->m_writePage = new WritePage00H(this->m_subNotebook,wxString(L"00h-PAGE"));

	this->m_subNotebook->AddPage(this->m_stdPage, "STD");
	this->m_subNotebook->AddPage(this->ReadPanel, "Read");
	this->m_subNotebook->AddPage(this->m_writePage, "Write"); // Don't show write page after APP initialized
	this->m_subNotebook->RemovePage(2);// Don't show write page after APP initialized

	// Setup Sizer
	wxSizer *GeneralPanelSz = new wxBoxSizer(wxHORIZONTAL);
	this->m_subNotebook->SetMinSize(wxSize(-1, 200));
	this->m_dataViewCtrl->SetMinSize(wxSize(-1, 200));
	GeneralPanelSz->Add(m_subNotebook, 2, wxGROW | wxALL, 0);
	GeneralPanelSz->Add(this->m_dataViewCtrl,8, wxGROW | wxALL, 0);

	parent->SetSizerAndFit(GeneralPanelSz);

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

	int row = m_list_model->GetRow(item);

	PSU_DEBUG_PRINT(MSG_DEBUG, "Selected Row is : %d", row);
	PSU_DEBUG_PRINT(MSG_DEBUG, "CMD's RW Attribute is : %d", this->m_PMBusData[row].m_access);

	switch (this->m_PMBusData[row].m_access){

	case cmd_access_read://cmd_access_br
		if (this->m_subNotebook->GetPageCount() == 3){
			this->m_subNotebook->RemovePage(2);
		}
		break;

	case cmd_access_write://cmd_access_bw
	case cmd_access_readwrite://cmd_access_brbw
		if (this->m_subNotebook->GetPageCount() == 2){
			this->m_subNotebook->AddPage(this->m_writePage, "Write");
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
		this->m_list_model->SetValueByRow(variant, idx, PSUDataViewListModel::Col_Toggle);
		this->m_list_model->RowValueChanged(idx, PSUDataViewListModel::Col_Toggle);
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
		this->m_list_model->SetValueByRow(variant, idx, PSUDataViewListModel::Col_Toggle);
		this->m_list_model->RowValueChanged(idx, PSUDataViewListModel::Col_Toggle);
	}
}

void MainFrame::DoSetupIOAccess(void){
	// Setup IOAccess Sturct Member
	// Serial Port
	this->m_IOAccess[IOACCESS_SERIALPORT].m_EnumerateAvailableDevice = EnumerateAvailableSerialPort;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_OpenDevice = OpenSerialPort;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_CloseDevice = CloseSerialPort;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_DeviceSendData = SerialSendData;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_DeviceReadData = SerialReadData;

	// HID
	this->m_IOAccess[IOACCESS_HID].m_EnumerateAvailableDevice = EnumerateAvailableHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_OpenDevice = OpenHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_CloseDevice = CloseHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_DeviceSendData = HIDSendData;
	this->m_IOAccess[IOACCESS_HID].m_DeviceReadData = HIDReadData;
}
