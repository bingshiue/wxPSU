/**
 * @file MainFrame.cpp
 */
#include "MainFrame.h"
#include "PMBUSHelper.h"
#include "PMBUSCommand.h"
#include "PMBUSCMDCB.h"
#include "Acbel.xpm"
#include "sample.xpm"
#include "appico.xpm"

wxDEFINE_EVENT(wxEVT_COMMAND_MONITOR_START, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_START, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_RAW, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_QUERY, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_COOK, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_CMDNAME, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_SUMMARY, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_STDPAGE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_STATUSPAGE, wxThreadEvent);

wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_START, wxThreadEvent);
//wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, wxThreadEvent);
//wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_UPDATE, wxThreadEvent);
//wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, wxThreadEvent);
//wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_END, wxThreadEvent);

wxDEFINE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_START, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_FIND_I2C_SLAVE_START, wxThreadEvent);

wxDEFINE_EVENT(wxEVT_IOTHREAD_REQ_PAUSE, wxThreadEvent);/**< Declare IO Thread Pause */
wxDEFINE_EVENT(wxEVT_IOTHREAD_REQ_RESUME, wxThreadEvent);/**< Declare IO Thread Resume */

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, CUSTOMER_TYPE_t* customerList) : wxFrame(NULL, wxID_ANY, title, pos, size)
{	
	wxInitAllImageHandlers();

#ifdef _WIN32
	RegisterDeviceChangeNotify();
#endif

	this->m_cmdListDVC = NULL;
	this->PMBusPrimaryFWUpdatePanel = NULL;
	this->PMBusSecondaryFWUpdatePanel = NULL;
	this->m_monitor_running = false;
	this->m_monitor_pause = false;
	this->m_pmbusProgressDialog = NULL;
	this->m_logFileFFileOutputStream = NULL;
	this->m_logFileTextOutputStream = NULL;

	CheckAndLoadConfig(customerList);

	// Setup PMBUS Command Buffer Provider
	SetupPMBUSCommandBufferProvider();

	//this->m_ioDeviceOpen = false;

	// Reset AppSettings
	//this->m_appSettings.Reset();

	// Setup IO Structure
	this->DoSetupIOAccess();

	// Initializa Semaphore
	this->m_rxTxSemaphore = new wxSemaphore(0,0);
	
	//this->m_parent = new wxPanel(this, wxID_ANY);
	this->m_topVeriticalSizer = new wxBoxSizer(wxVERTICAL);
	this->m_hbox = new wxBoxSizer(wxHORIZONTAL);

	// Load Bitmaps
#ifdef __GNUC__
	this->m_monitorBitmap_Instance = wxBITMAP_PNG_FROM_DATA(monitor_32);
	this->m_pauseBitmap_Instance = wxBITMAP_PNG_FROM_DATA(pause_32);

	this->m_monitor16Bitmap_Instance = wxBITMAP_PNG_FROM_DATA(monitor_16);
	this->m_pause16Bitmap_Instance= wxBITMAP_PNG_FROM_DATA(pause_16);

	this->m_monitorBitmap = &this->m_monitorBitmap_Instance;
	this->m_pauseBitmap = &this->m_pauseBitmap_Instance;

	this->m_monitor16Bitmap = &this->m_monitor16Bitmap_Instance;
	this->m_pause16Bitmap = &this->m_pause16Bitmap_Instance;
#else
	this->m_monitorBitmap = new wxBitmap(wxT("MONITOR_32"), wxBITMAP_TYPE_PNG_RESOURCE);
	this->m_pauseBitmap = new wxBitmap(wxT("PAUSE_32"), wxBITMAP_TYPE_PNG_RESOURCE);

	this->m_monitor16Bitmap = new wxBitmap(wxT("MONITOR_16"), wxBITMAP_TYPE_PNG_RESOURCE);
	this->m_pause16Bitmap = new wxBitmap(wxT("PAUSE_16"), wxBITMAP_TYPE_PNG_RESOURCE);
#endif

	// Setup Icon
#ifdef _WIN32
	SetIcon(wxICON(APP_ICON));//Acbel_xpm);
#else
	SetIcon(wxICON(app_ico));
#endif

	// Setup Model
	SetupModel();

	// Setup PMBusCommand Data
	SetupPMBusCommandData();
	
	// Setup Menu
	SetupMenuBar();

	// Setup CMDList Pop Up Menu
	this->m_cmdListPopupMenu = new wxMenu();
	this->m_popupFontMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_FONT, wxT("Font"), wxT("Font"), wxITEM_NORMAL);
	this->m_popupPrintScreenMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_PRINT_SCREEN, wxT("Print Screen"), wxT("Print Screen"), wxITEM_NORMAL);

	this->m_popupFontMenuItem->SetBitmap(LOAD_PNG_RESOURCE(font_16));
	this->m_popupPrintScreenMenuItem->SetBitmap(LOAD_PNG_RESOURCE(printscreen_16));

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
	m_splitterWindowTopLevel->SetMinimumPaneSize(5);

	m_splitterWindow = new wxSplitterWindow(this->m_splitterWindowTopLevel, SplitterWindowID);

	m_splitterWindow->SetSashGravity(0.3);
	m_splitterWindow->SetMinimumPaneSize(5);

	// Sub Notebook
	this->m_subNotebook = new wxNotebook(this->m_splitterWindow, wxID_ANY);
	this->CMDListPanel = new wxPanel(this->m_splitterWindow, wxID_ANY);
	this->DebugLogPanel = new wxPanel(this->m_splitterWindowTopLevel, wxID_ANY);

	this->m_stdPage = new STDPage(this->m_subNotebook);
	//this->ReadPanel = new wxPanel(this->m_subNotebook, wxID_ANY);
	//this->m_writePage = new WritePage00H(this->m_subNotebook, wxString(L"00h-PAGE"));

	this->m_debugLogStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this->DebugLogPanel, wxT("Operation Log"));

	// create the logging text control and a header showing the meaning of the
	// different columns
	//m_header = new wxTextCtrl(this->GeneralPanel, wxID_ANY, "",
		//wxDefaultPosition, wxDefaultSize,
		//wxTE_READONLY);
	//DoLogLine(m_header, "  Time", " Thread", "          Message");
	this->m_debugLogTC = new PMBUSLogTextCtrl(this->m_debugLogStaticBoxSizer->GetStaticBox(), ID_LOG_TEXTCTRL);//new wxTextCtrl(this->m_debugLogStaticBoxSizer->GetStaticBox(), wxID_ANY, "",//this->DebugLogPanel, wxID_ANY, "",
		//wxDefaultPosition, wxDefaultSize,
		//wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH);
	
	// Get old logger
	m_oldLogger = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	switch (this->m_appSettings.m_logMode){

	case Log_Mode_Log_ALL:
		wxLog::SetLogLevel(wxLOG_Debug);
		break;

	case Log_Mode_Log_Error_Only:
		wxLog::SetLogLevel(wxLOG_Warning);
		break;

	default:

		break;
	}

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize()+1, wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	//m_header->SetFont(font);
	this->m_debugLogTC->SetFont(font);
	this->m_debugLogTC->SetFocus();
	
	SetupCMDListDVL(GeneralPanel);
	SetupPMBusCommandReadPage();
	SetupPMBusCommandWritePage();

	this->PMBusStatusPanel = new PMBUSStatusPanel(m_notebook);

	this->PMBusMFRPanel = new PMBUSMFRPanel(m_notebook);

	this->PMBusVerificationPanel = new PMBUSVerificationPanel(m_notebook);

	this->PMBusStatusDCHPanel = new PMBUSStatusDCHPanel(m_notebook);

	// Add each panl into notebook component
	m_notebook->AddPage(this->GeneralPanel, "General");
	m_notebook->AddPage(this->PMBusStatusPanel, "STATUS");//"PM Bus Status");
	m_notebook->AddPage(this->PMBusStatusDCHPanel, "STATUS(DCH)");
	m_notebook->AddPage(this->PMBusMFRPanel, "PMBus MFR");
	m_notebook->AddPage(this->PMBusVerificationPanel, "Verification");
	//m_notebook->AddPage(this->PMBusStatusDCHPanel, "STATUS(DCH)");

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
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Create Task System Thread");
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Start Task System Thread");
		this->m_TaskSystemThread->SetPriority(WXTHREAD_DEFAULT_PRIORITY);
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
	m_increaseCPUOverHeadThreadStopFlag = true;
	this->m_increaseCPUOverHeadThread = NULL;

	// Disable status bar to show help string
	this->SetStatusBarPane(-1);

	// Set Art Provider
	wxArtProvider::Push(new PMBUSArtProvider);

	// Open IO Device
	wxThreadEvent *threadQueryStart_evt;
	int retval;
	retval = this->OpenIODevice();
	if (retval == EXIT_FAILURE){
		//if (this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT) {
			
			// If Find Acbel USB I2C Adaptor
			if (this->m_IOAccess[IOACCESS_HID].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT) > 0){

				// Hint User Can Use USB Adaptor Device
				wxMessageBox(wxT("Found Acbel USB I2C Adaptor Board \n\nYou Can Setup I/O to Use USB I2C Adaptor Board in Next Popup Setting Window"),
					wxT("Found Acbel USB I2C Adaptor Board !"),  // caption
					wxOK | wxICON_INFORMATION);

				// Popup I2C Interface Dialog 
				I2CInterfaceDialog* i2cIFDialog = new I2CInterfaceDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_appSettings, this->m_status_bar, true, I2C_AdaptorModuleBoard_R90000_9271_USB);
				i2cIFDialog->Centre(wxCENTER_ON_SCREEN);
				i2cIFDialog->ShowModal();

				delete i2cIFDialog;

			}
			// If Find Pickit Serial
			else if (this->m_IOAccess[IOACCESS_PICKIT].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT) > 0){

				// Hint User Can Use USB Adaptor Device
				wxMessageBox(wxT("Found Pickit Serial Analyzer \n\nYou Can Setup I/O to Use Pickit Serial Analyzer in Next Popup Setting Window"),
					wxT("Found Pickit Serial Analyzer !"),  // caption
					wxOK | wxICON_INFORMATION);

				// Popup I2C Interface Dialog 
				I2CInterfaceDialog* i2cIFDialog = new I2CInterfaceDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_appSettings, this->m_status_bar, true, I2C_AdaptorModuleBoard_PICKIT_SERIAL);
				i2cIFDialog->Centre(wxCENTER_ON_SCREEN);
				i2cIFDialog->ShowModal();

				delete i2cIFDialog;

			}
			// If Find Total Phase I2C Host Adaptor
			else if(this->m_IOAccess[IOACCESS_TOTALPHASE].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT) > 0){
				
				// Hint User Can Use TotalPhase I2C Host Adaptor Device
				wxMessageBox(wxT("Found TotalPhase I2C Host Adaptor Device \n\nYou Can Setup I/O to Use TotalPhase I2C Host Adaptor Device in Next Popup Setting Window"),
					wxT("Found TotalPhase I2C Host Adaptor Device !"),  // caption
					wxOK | wxICON_INFORMATION);

				// Popup I2C Interface Dialog 
				I2CInterfaceDialog* i2cIFDialog = new I2CInterfaceDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_appSettings, this->m_status_bar, true, I2C_AdaptorModuleBoard_TOTALPHASE);
				i2cIFDialog->Centre(wxCENTER_ON_SCREEN);
				i2cIFDialog->ShowModal();

				delete i2cIFDialog;

			}
			// If Find USB To Serial Adaptor
			else if (this->m_IOAccess[IOACCESS_SERIALPORT].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT) > 0){

				// Popup Comport Setting Dialog
				ComportDialog* comportDialog = new ComportDialog(this, this->m_IOAccess, &this->m_appSettings, this->m_status_bar);
				comportDialog->Centre(wxCENTER_ON_SCREEN);
				comportDialog->ShowModal();

				delete comportDialog;
			}
			// If Find TRC2 I2C Adapter
			else if (this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT) > 0){

				// Hint User Can Use USB Adaptor Device
				wxMessageBox(wxT("Found TRC2 I2C Adaptor Board \n\nYou Can Setup I/O to Use TRC2 I2C Adaptor Board in Next Popup Setting Window"),
					wxT("Found Acbel TRC2 I2C Adaptor Board !"),  // caption
					wxOK | wxICON_INFORMATION);

				// Popup I2C Interface Dialog
				I2CInterfaceDialog* i2cIFDialog = new I2CInterfaceDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_appSettings, this->m_status_bar, true, I2C_AdaptorModuleBoard_TRC2I2CAdapter);
				i2cIFDialog->Centre(wxCENTER_ON_SCREEN);
				i2cIFDialog->ShowModal();

				delete i2cIFDialog;

			}


			// If I/O Device Opened Success in Previous Operation
			if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_OPEN){

				/*** Send Query Start Event To Handler Function ***/
				if (this->m_appSettings.m_autoQueryCMDOnIOOpen == Generic_Enable){
					threadQueryStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_QUERY_SEQUENCE_START);
					threadQueryStart_evt->SetString(wxT("Query All Commands"));
					wxQueueEvent(this->GetEventHandler(), threadQueryStart_evt);
				}
			}

		//}
	}
	
	// Start InCreaseCPUOverHeadThread if option is enable
	if (this->m_appSettings.m_increaseCPUOverhead == Generic_Enable){
		this->StartInCreaseCPUOverHeadThread();
	}

	// Put Window in Center
	Centre();

	// Debug Print
	for(unsigned int idx=0; idx<PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		PSU_DEBUG_PRINT(MSG_DEBUG, "CMD=%02x, %p", this->m_PMBusData[idx].m_register ,this->m_PMBusData[idx].m_writePage);
	}

}

MainFrame::~MainFrame()
{		

}

void MainFrame::SetupMenuBar(void){
	
	// Create Menu Bar and Its Components
	// File Menu
	/*
	File
	|- Hex To Bin -> Transform Primary Firmware Hex To Binary
	|             -> Transform Secondary Firmware Hex To Binary
	|------------------------------------
	|- Exit
	*/
	this->m_fileMenu = new wxMenu();

	this->m_transFWMenuItem = new wxMenuItem((wxMenu*)0, wxID_ANY, wxT("Transform Hex To Binary"), wxT("Transform Hex To Binary"), wxITEM_NORMAL);
	this->m_transFWMenuItem->SetBitmap(LOAD_PNG_RESOURCE(binary_16));

	this->m_transPrimaryFWMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Primary_Firmware, wxT("Transform Primary Firmware Hex To Binary"), "Select Primary Firmware", wxITEM_NORMAL);
	this->m_transPrimaryFWMenuItem->SetBitmap(LOAD_PNG_RESOURCE(binary_16));

	this->m_transSecondaryFWMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Secondary_Firmware, wxT("Transform Secondary Firmware Hex To Binary"), "Select Secondary Firmware", wxITEM_NORMAL);
	this->m_transSecondaryFWMenuItem->SetBitmap(LOAD_PNG_RESOURCE(binary_16));

	this->m_hexToBinMenu = new wxMenu();

	this->m_hexToBinMenu->Append(this->m_transPrimaryFWMenuItem);
	this->m_hexToBinMenu->Append(this->m_transSecondaryFWMenuItem);

	this->m_transFWMenuItem->SetSubMenu(this->m_hexToBinMenu);
	this->m_fileMenu->Append(this->m_transFWMenuItem);

	this->m_fileMenu->AppendSeparator();

	this->m_exitMenuItem = new wxMenuItem((wxMenu*)0, wxID_EXIT, wxT("Exit"),
		wxT("Exit"), wxITEM_NORMAL);

	this->m_exitMenuItem->SetBitmap(LOAD_PNG_RESOURCE(exit_16));

	this->m_fileMenu->Append(m_exitMenuItem);

	// Run Menu
	/*
	Run
	|- Monitor (Accelerator CTRL+M)
	|- In System Programming -> |- Update Primary Firmware (Accelerator CTRL+P)
	|                           |- Update Secondary Firmware (Accelerator CTRL+S)
	### |- Stop Programming ###
	|- Query All PMBUS Commands
	|- Find Available I2C Slave Device
	|------------------------------------
	|- I2C Fault Test
	|- [V] Enable Checksum
	|- Only Polling Support Command
	|- Auto Query Command On I/O Open
	|- Query Command Before Polling 
	|- Clear Log Before Monitor Run
	|------------------------------------
	|- Clear Error Log
	|- Reset Max./Min. Value
	|- Reset Run Time


	*/
	this->m_runMenu = new wxMenu();
	this->m_monitorMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Monitor, wxT("Monitor...\tCTRL+M"), wxT("Start Monitor"), wxITEM_NORMAL);

	this->m_monitorMenuItem->SetBitmap(*m_monitor16Bitmap);

	this->m_runMenu->Append(this->m_monitorMenuItem);

	this->m_inSystemProgrammingMenuItem = new wxMenuItem((wxMenu*)0, wxID_ANY, wxT("In System Programming"), wxT("In System Programming"), wxITEM_NORMAL);

	this->m_inSystemProgrammingMenuItem->SetBitmap(LOAD_PNG_RESOURCE(chip_16));

	this->m_updatePrimaryFirmwareMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Update_Primary_Firmware, wxT("Load Primary Firmware...\tCTRL+P"), "Load Primary Firmware", wxITEM_NORMAL);
	this->m_updatePrimaryFirmwareMenuItem->SetBitmap(LOAD_PNG_RESOURCE(chip_16));

	this->m_updateSecondaryFirmwareMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Update_Secondary_Firmware, wxT("Load Secondary Firmware...\tCTRL+S"), "Load Secnondary Firmware", wxITEM_NORMAL);
	this->m_updateSecondaryFirmwareMenuItem->SetBitmap(LOAD_PNG_RESOURCE(chip_16));

	this->m_ispMenu = new wxMenu();

	this->m_ispMenu->Append(this->m_updatePrimaryFirmwareMenuItem);
	this->m_ispMenu->Append(this->m_updateSecondaryFirmwareMenuItem);

	this->m_inSystemProgrammingMenuItem->SetSubMenu(this->m_ispMenu);

	this->m_runMenu->Append(this->m_inSystemProgrammingMenuItem);

#ifdef LOCK_UPDATE_FW
	this->m_runMenu->Enable(MENU_ID_Update_Secondary_Firmware, false);
	this->m_runMenu->Enable(MENU_ID_Update_Primary_Firmware, false);
#endif

	//this->m_stopProgrammingMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Stop_Programming, wxT("Stop Programming"),
		//"Stop Programming", wxITEM_NORMAL);

	//this->m_runMenu->Append(m_stopProgrammingMenuItem);


	this->m_queryAllCommandsMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Query_All_Commands, wxT("Query ALL PMBUS Commands"), wxT("Query ALL PMBUS Commands"), wxITEM_NORMAL);
	this->m_queryAllCommandsMenuItem->SetBitmap(LOAD_PNG_RESOURCE(query_16));
	this->m_runMenu->Append(m_queryAllCommandsMenuItem);


	this->m_findAvailableI2CSlaveDeviceMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Find_Available_I2C_Slave_Device, wxT("Find Available I2C Slave Device"), wxT("Find Available I2C Slave Device"), wxITEM_NORMAL);
	this->m_findAvailableI2CSlaveDeviceMenuItem->SetBitmap(LOAD_PNG_RESOURCE(broadcast_16));
	this->m_runMenu->Append(m_findAvailableI2CSlaveDeviceMenuItem);

	this->m_runMenu->AppendSeparator();

	this->m_i2cFaultTestMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_I2C_Fault_Test, wxT("I2C Fault Test"), wxT("I2C Fault Test"), wxITEM_NORMAL);

	this->m_EnableChecksumMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Enable_Checksum, wxT("Enable Checksum"), wxT("Enable Checksum"), wxITEM_CHECK);

	//if (this->m_appSettings.m_EnableChecksum == Generic_Enable){
		//this->m_EnableChecksumMenuItem->Check(true);
	//}

	this->m_onlyPollingSupportCMDMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Only_Polling_Support_Command, wxT("Only Polling Support Command"), wxT("Only Polling Support Command"), wxITEM_CHECK);

	//if (this->m_appSettings.m_onlyPollingSupportCMD == Generic_Enable){
		//this->m_onlyPollingSupportCMDMenuItem->Check(true);
	//}

	this->m_autoQueryCMDOnIOOpenMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Auto_Query_CMD_On_IO_Open, wxT("Auto Query Command On I/O Open"), wxT("Auto Query Command On I/O Open"), wxITEM_CHECK);
	
	//if (this->m_appSettings.m_autoQueryCMDOnIOOpen == Generic_Enable){
		//this->m_autoQueryCMDOnIOOpenMenuItem->Check(true);
	//}

	this->m_queryCMDBeforePollingMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Query_CMD_Before_Polling, wxT("Query Command Before Polling"), wxT("Query Command Before Polling"), wxITEM_CHECK);

	//if (this->m_appSettings.m_queryCMDBeforePolling == Generic_Enable){
		//this->m_queryCMDBeforePollingMenuItem->Check(true);
	//}

	this->m_clearLogBeforeMonitorRun = new wxMenuItem((wxMenu*)0, MENU_ID_Clear_Log_Before_Monitor_Run, wxT("Clear Log Before Monitor Run"), wxT("Clear Log Before Monitor Run"), wxITEM_CHECK);


	this->m_runMenu->Append(m_i2cFaultTestMenuItem);
	this->m_runMenu->Append(m_EnableChecksumMenuItem);
	this->m_runMenu->Append(m_onlyPollingSupportCMDMenuItem);
	this->m_runMenu->Append(m_autoQueryCMDOnIOOpenMenuItem);
	this->m_runMenu->Append(m_queryCMDBeforePollingMenuItem);
	this->m_runMenu->Append(m_clearLogBeforeMonitorRun);
	this->m_runMenu->AppendSeparator();

	this->m_ClearErrorLogMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Clear_Error_Log, wxT("Clear Error Log"), wxT("Clear Error Log"), wxITEM_NORMAL);

	this->m_ClearErrorLogMenuItem->SetBitmap(LOAD_PNG_RESOURCE(clear_16));

	this->m_ResetMaxMinValueMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Reset_MaxMin_Value, wxT("Reset Max./Min/ Value"), wxT("Reset Max./Min/ Value"), wxITEM_NORMAL);

	this->m_ResetMaxMinValueMenuItem->SetBitmap(LOAD_PNG_RESOURCE(refresh_16));

	this->m_ResetRunTimeMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Reset_Run_Time, wxT("Reset Run Time"), wxT("Reset Run Time"), wxITEM_NORMAL);

	this->m_ResetRunTimeMenuItem->SetBitmap(LOAD_PNG_RESOURCE(timer_16));

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

	this->m_EnableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_EnableCalibration, wxT("Enable Calibration"), wxT("Enable Calibration"), wxITEM_NORMAL);

	this->m_EnableCalibrationMenuItem->SetBitmap(LOAD_PNG_RESOURCE(enable_16));

	this->m_DisableCalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_DisableCalibration, wxT("Disable Calibration"), wxT("Disable Calibration"), wxITEM_NORMAL);

	this->m_DisableCalibrationMenuItem->SetBitmap(LOAD_PNG_RESOURCE(disable_16));

	this->m_psuMenu->Append(m_EnableCalibrationMenuItem);
	this->m_psuMenu->Append(m_DisableCalibrationMenuItem);

	this->m_psuMenu->AppendSeparator();

	this->m_CalibrationMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Calibration, wxT("Calibration"), wxT("Calibration Setting"), wxITEM_NORMAL);

	this->m_CalibrationMenuItem->SetBitmap(LOAD_PNG_RESOURCE(calibration_16));

	this->m_psuMenu->Append(m_CalibrationMenuItem);


	// Option Menu
	/*
	Option
	|- Administrant...(Accelerator CTRL+A)
	|------------------------------------
	|- I2C  Interface...
	|------------------------------------
	|- I2C  Slave Address
	|------------------------------------
	|- Disable All (Accelerator CTRL+D)
	|- Enable All (Accelerator CTRL+E)
	|------------------------------------
	|- Increase CPU Overhead
	|------------------------------------
	|
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

	this->m_AdministrantMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Administrant, wxT("Administrant...\tCTRL+A"), wxT("Administrant"), wxITEM_NORMAL);

	this->m_AdministrantMenuItem->SetBitmap(LOAD_PNG_RESOURCE(admin_16));

#if DEFAULT_DONT_ENABLE_ISP == TRUE
	this->m_AdministrantMenuItem->Enable(false);
#endif

	this->m_optionMenu->Append(this->m_AdministrantMenuItem);
	this->m_optionMenu->AppendSeparator();

	this->m_I2CInterfaceMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_I2C_Interface, wxT("I2C Interface"), wxT("I2C Interface"), wxITEM_NORMAL);

	this->m_I2CInterfaceMenuItem->SetBitmap(LOAD_PNG_RESOURCE(hwinfo_16));

	this->m_optionMenu->Append(this->m_I2CInterfaceMenuItem);
	this->m_optionMenu->AppendSeparator();

	// I2C Slave Address
	this->m_I2CSlaveAddressMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_I2C_SlaveAddress, wxT("I2C Slave Address"), wxT("I2C Slave Address"), wxITEM_NORMAL);
	this->m_optionMenu->Append(this->m_I2CSlaveAddressMenuItem);

	this->m_optionMenu->AppendSeparator();

	this->m_optionMenu->Append(MENU_ID_Disable_ALL, wxT("Disable ALL...\tCTRL+D"), wxT("Disable All Commands"));

	this->m_optionMenu->Append(MENU_ID_Enable_ALL,  wxT("Enable  ALL...\tCTRL+E"), wxT("Enable All Commands"));

	this->m_optionMenu->AppendSeparator();

	this->m_IncreaseCPUOverheadMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Increase_CPU_Overhead, wxT("Increase CPU Overhead"), wxT("Increase CPU Overhead"), wxITEM_CHECK);
		
	this->m_optionMenu->Append(this->m_IncreaseCPUOverheadMenuItem);

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

	this->m_allMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ErrorLog_ALL, wxT("All"), wxT("All"), wxITEM_CHECK);

	this->m_errorOnlyMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ErrorLog_ErrorOnly, wxT("Error Only"), wxT("Error Only"), wxITEM_CHECK);

	this->m_logToFileMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_Log_To_File, wxT("Log To File"), wxT("Log To File"), wxITEM_CHECK);

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

	this->m_pmBus11MenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_PMBUS_1_1, wxT("PMBus1.1 (Single Mode)"), wxT("PMBus1.1 (Single Mode)"), wxITEM_CHECK);

	this->m_pmBus12MenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_PMBUS_1_2, wxT("PMBus1.2 (Page Plus Mode)"), wxT("PMBus1.2 (Page Plus Mode)"), wxITEM_CHECK);

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

	// Test Menu
	/*
	Test
	| - Read Test 
	| - Write Test
	| - Block W/R Test
	*/
	this->m_testMenu = new wxMenu();

	this->m_readTestMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_READ_TEST, wxT("Customize PMBUS Read CMD Test"), wxT("Customize PMBUS Read CMD Test"), wxITEM_NORMAL);

	this->m_writeTestMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_WRITE_TEST, wxT("Customize PMBUS Write CMD Test"), wxT("Customize PMBUS Write CMD Test"), wxITEM_NORMAL);

	this->m_blockWRTestMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_BLOCK_WR_TEST, wxT("Customize PMBUS Block WR CMD Test"), wxT("Customize PMBUS Block WR CMD Test"), wxITEM_NORMAL);

	this->m_testMenu->Append(this->m_readTestMenuItem);
	this->m_testMenu->Append(this->m_writeTestMenuItem);
	this->m_testMenu->Append(this->m_blockWRTestMenuItem);

	// Utility Menu
	/*
	| - FRU Maker
	| - FRU Writer
	*/
	this->m_utilityMenu = new wxMenu();

	this->m_fruMakerMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_FRU_MAKER, wxT("FRU Maker"), wxT("FRU Maker"), wxITEM_NORMAL);

	this->m_fruMakerMenuItem->SetBitmap(LOAD_PNG_RESOURCE(maker_16));

	this->m_utilityMenu->Append(this->m_fruMakerMenuItem);

	this->m_fruWriterMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_FRU_WRITER, wxT("FRU Utility"), wxT("FRU Utility"), wxITEM_NORMAL);

	this->m_fruWriterMenuItem->SetBitmap(LOAD_PNG_RESOURCE(e2prom_16));

	this->m_utilityMenu->Append(this->m_fruWriterMenuItem);

	// Help Menu
	/*
	Help
	|- ACBEL WebSite
	|- About
	*/
	this->m_helpMenu = new wxMenu();

	this->m_aboutMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ABOUT, wxT("About"), wxT("About"), wxITEM_NORMAL);

	this->m_aboutMenuItem->SetBitmap(LOAD_PNG_RESOURCE(about_16));

	this->m_acbelWebSiteMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_ACBEL_WEBSITE, wxT("ACBEL Website"), wxT("ACBEL Website"), wxITEM_NORMAL);

	this->m_acbelWebSiteMenuItem->SetBitmap(LOAD_PNG_RESOURCE(web_16));

	this->m_helpMenu->Append(this->m_acbelWebSiteMenuItem);

	this->m_helpMenu->Append(this->m_aboutMenuItem);

	// Create MenuBar Instance
	this->m_menuBar = new wxMenuBar();
	this->m_menuBar->Append(this->m_fileMenu, wxT("File"));
	this->m_menuBar->Append(this->m_runMenu, wxT("Run"));
	this->m_menuBar->Append(this->m_psuMenu, wxT("PSU"));
	this->m_menuBar->Append(this->m_optionMenu, wxT("Option"));
	this->m_menuBar->Append(this->m_testMenu, wxT("Test"));
	this->m_menuBar->Append(this->m_utilityMenu, wxT("Utility"));
	this->m_menuBar->Append(this->m_helpMenu, wxT("Help"));

	SetMenuBar(this->m_menuBar);

	/* Set Default Check Status */

	if (this->m_appSettings.m_clearLogBeforeMonitorRun == Generic_Enable){
		this->m_clearLogBeforeMonitorRun->Check(true);
	}


	if (this->m_appSettings.m_EnableChecksum == Generic_Enable){
		this->m_EnableChecksumMenuItem->Check(true);
	}

	if (this->m_appSettings.m_onlyPollingSupportCMD == Generic_Enable){
		this->m_onlyPollingSupportCMDMenuItem->Check(true);
	}

	if (this->m_appSettings.m_autoQueryCMDOnIOOpen == Generic_Enable){
		this->m_autoQueryCMDOnIOOpenMenuItem->Check(true);
	}

	if (this->m_appSettings.m_queryCMDBeforePolling == Generic_Enable){
		this->m_queryCMDBeforePollingMenuItem->Check(true);
	}

	if (this->m_appSettings.m_increaseCPUOverhead == Generic_Enable){
		this->m_IncreaseCPUOverheadMenuItem->Check(true);
	}
}

void MainFrame::SetupToolBar(void){

	const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;

	// Setup Tool Bar
	long style = TOOLBAR_STYLE;
	style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);

	// Create Tool Bar Instance
	m_toolbar = CreateToolBar(/*style*/wxTB_DEFAULT_STYLE, ID_TOOLBAR);

	// Append Exit Button
	m_toolbar->AddTool(wxID_EXIT, wxEmptyString, LOAD_PNG_RESOURCE(exit_32), wxT("Exit Program"), wxITEM_NORMAL);

	// Append Monitor Button
	m_toolbar->AddTool(MENU_ID_Monitor, wxEmptyString, *m_monitorBitmap, wxT("Monitor"), wxITEM_NORMAL);

	// Append Find I2C Slave Device Button
	m_toolbar->AddTool(MENU_ID_Find_Available_I2C_Slave_Device, wxEmptyString, LOAD_PNG_RESOURCE(broadcast_32), wxT("Find I2C Slave Device"), wxITEM_NORMAL);

	// Append Query All Commands Button
	m_toolbar->AddTool(MENU_ID_Query_All_Commands, wxEmptyString, LOAD_PNG_RESOURCE(query_32), wxT("Query All Commands"), wxITEM_NORMAL);

	// Append Enable Calibration Button
	m_toolbar->AddTool(MENU_ID_EnableCalibration, wxEmptyString, LOAD_PNG_RESOURCE(enable_32), wxT("Enable Calibration"), wxITEM_NORMAL);

	// Append Reset Run Time Button
	m_toolbar->AddTool(MENU_ID_Reset_Run_Time, wxEmptyString, LOAD_PNG_RESOURCE(timer_32), wxT("Reset Run Time"), wxITEM_NORMAL);

	// Append Refresh MAX/MIN Button
	m_toolbar->AddTool(MENU_ID_Reset_MaxMin_Value, wxEmptyString, LOAD_PNG_RESOURCE(refresh_32), wxT("Reset Max/Min Value"), wxITEM_NORMAL);

	// Append Clear Error Log Button 
	m_toolbar->AddTool(MENU_ID_Clear_Error_Log, wxEmptyString, LOAD_PNG_RESOURCE(clear_32), wxT("Clear Error Log"), wxITEM_NORMAL);

	// Append Separator
	m_toolbar->AddSeparator();

	// Append Interation
	m_iteration_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Iteration"));
	m_toolbar->AddControl(m_iteration_text, wxEmptyString);

	wxString iterations_times = wxString::Format("%ld", this->m_appSettings.m_IterationsValue);

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

	m_polling_time_combobox = new wxComboBox(m_toolbar, ID_POLLING_TIME_COMBO, wxEmptyString, wxDefaultPosition, wxSize(100, -1), wxArrayString(), wxCB_READONLY);

	wchar_t* pollingIntervalArray[10] = {
		L"0", L"10", L"20", L"50", L"100", L"200", L"300", L"500", L"1000", L"1500"
	};

	for (int idx = 0; idx < sizeof(pollingIntervalArray) / sizeof(pollingIntervalArray[0]);idx++){
		m_polling_time_combobox->Append(pollingIntervalArray[idx]);
	}

	int pollingIntervalValue;
	int pollingIntervalSelectdIndex = 0;
	for (int idx = 0; idx < sizeof(pollingIntervalArray) / sizeof(pollingIntervalArray[0]); idx++){
		pollingIntervalValue = wxAtoi(pollingIntervalArray[idx]);
		if (pollingIntervalValue == this->m_appSettings.m_pollingInterval){
			pollingIntervalSelectdIndex = idx;
			break;
		}
	}

	m_polling_time_combobox->SetSelection(pollingIntervalSelectdIndex);
	m_toolbar->AddControl(m_polling_time_combobox, wxEmptyString);

	//m_polling_time_combobox->Append(wxT("0"));
	//m_polling_time_combobox->Append(wxT("10"));
	//m_polling_time_combobox->Append(wxT("20"));
	//m_polling_time_combobox->Append(wxT("50"));
	//m_polling_time_combobox->Append(wxT("100"));
	//m_polling_time_combobox->Append(wxT("200"));
	//m_polling_time_combobox->Append(wxT("300"));
	//m_polling_time_combobox->Append(wxT("500"));
	//m_polling_time_combobox->Append(wxT("1000"));
	//m_polling_time_combobox->Append(wxT("1500"));

	// Append Separator
	m_toolbar->AddSeparator();

	// Append Address 
	m_address_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("I2C Slave Address"));
	m_toolbar->AddControl(m_address_text, wxEmptyString);

	m_address_input = new wxTextCtrl(m_toolbar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1));

	wxString SlaveAddressHex = (wxString::Format("%2lx", this->m_appSettings.m_I2CSlaveAddress)).Upper();
	m_address_input->SetValue(SlaveAddressHex);

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
	this->m_cmdListDVC = new wxDataViewCtrl(this->CMDListPanel, CID_CMDLIST_DVC, wxDefaultPosition,
		wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	m_cmdListModel = new PMBUSCMDListModel(this->m_PMBusData, PMBUSHelper::GetCurrentCMDTableSize());
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
		wxALIGN_LEFT,// | wxALIGN_CENTER_HORIZONTAL,//wxALIGN_NOT,
		wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_SORTABLE);

	this->m_cmdListDVC->AppendTextColumn("Name",
		PMBUSCMDListModel::Col_NameText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		//wxCOL_WIDTH_AUTOSIZE,
#ifdef __GNUC__
		150,//wxCOL_WIDTH_AUTOSIZE,
#else
		wxCOL_WIDTH_AUTOSIZE,//75,//wxCOL_WIDTH_AUTOSIZE,
#endif
		wxALIGN_CENTER_HORIZONTAL,//wxALIGN_NOT,
		wxCOL_RESIZABLE);

	this->m_cmdListDVC->AppendTextColumn("Access",
		PMBUSCMDListModel::Col_AccessText,
		wxDATAVIEW_CELL_ACTIVATABLE,
		//wxCOL_WIDTH_AUTOSIZE,
#ifdef __GNUC__
		150,//wxCOL_WIDTH_AUTOSIZE,
#else
		wxCOL_WIDTH_AUTOSIZE,//75,//wxCOL_WIDTH_AUTOSIZE,
#endif
		wxALIGN_CENTER_HORIZONTAL,
		wxCOL_RESIZABLE);//wxDATAVIEW_COL_SORTABLE);

	this->m_cmdListDVC->AppendTextColumn("Query",
		PMBUSCMDListModel::Col_QueryText,
		wxDATAVIEW_CELL_ACTIVATABLE,
#ifdef __GNUC__
		150,//wxCOL_WIDTH_AUTOSIZE,
#else
		wxCOL_WIDTH_AUTOSIZE,//75,//wxCOL_WIDTH_AUTOSIZE,
#endif
		wxALIGN_CENTER_HORIZONTAL,
		PMBUSHelper::GetCurrentUseModel()->m_isStandardPMBUSModel==true ? wxCOL_RESIZABLE : wxCOL_HIDDEN);//wxCOL_RESIZABLE);

	this->m_cmdListDVC->AppendTextColumn("Coefficients",
		PMBUSCMDListModel::Col_CoefficientsText,
		wxDATAVIEW_CELL_ACTIVATABLE,
#ifdef __GNUC__
		150,//wxCOL_WIDTH_AUTOSIZE,
#else
		wxCOL_WIDTH_AUTOSIZE,//75,//wxCOL_WIDTH_AUTOSIZE,
#endif
		wxALIGN_CENTER_HORIZONTAL,
		PMBUSHelper::GetCurrentUseModel()->m_isStandardPMBUSModel == true ? wxCOL_RESIZABLE : wxCOL_HIDDEN);// wxCOL_RESIZABLE);// wxDATAVIEW_COL_SORTABLE);

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
	//this->m_subNotebook->AddPage(this->ReadPanel, "Read");
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

void MainFrame::SetupModel(void){
	// Setup Model List
	wxString winTitle = this->GetTitle();
	winTitle += wxT("  Model : ");
	winTitle += this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelName;

#if 0
	winTitle += wxT("  Customer : ");
	winTitle += this->m_customerList[this->m_appSettings.m_currentUseCustomer].m_customerName;
#endif

	// Save Windows Title Base String
	PMBUSHelper::setWinTitleBase(winTitle);

	wxString i2cSA("");
	i2cSA = wxString::Format("%2lx", this->m_appSettings.m_I2CSlaveAddress);
	i2cSA.UpperCase();

	winTitle += wxT("  I2C Slave Address : ");
	winTitle += i2cSA;

	this->SetTitle(winTitle);

	// Set CMD Table Size
	PMBUSHelper::SetCurrentCMDTableSize(this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTableSize);

	// Init PMBusData
	this->m_PMBusData = new PMBUSCOMMAND_t[PMBUSHelper::GetCurrentCMDTableSize()];
}

void MainFrame::SetupPMBusCommandData(void){
	
	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){

		this->m_PMBusData[idx].m_toggle = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_toggle;
		sprintf(this->m_PMBusData[idx].m_label, this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_label);
		this->m_PMBusData[idx].m_register = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_register;
		sprintf(this->m_PMBusData[idx].m_name, this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_name);
		this->m_PMBusData[idx].m_access = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_access;
		this->m_PMBusData[idx].m_query = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_query;
		this->m_PMBusData[idx].m_cook = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_cook;
		this->m_PMBusData[idx].m_responseDataLength = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_responseDataLength;
		this->m_PMBusData[idx].m_cmdStatus = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable[idx].m_cmdStatus;
		this->m_PMBusData[idx].m_cmdCBFunc.m_queryCBFunc = this->m_modelList[this->m_appSettings.m_currentUseModel].m_cmdQueryCBFunc[idx];
		this->m_PMBusData[idx].m_cmdCBFunc.m_coefficientsCBFunc = this->m_modelList[this->m_appSettings.m_currentUseModel].m_cmdCoefficientsFunc[idx];
		this->m_PMBusData[idx].m_cmdCBFunc.m_cookCBFunc = this->m_modelList[this->m_appSettings.m_currentUseModel].m_cmdCookCBFunc[idx];
		this->m_PMBusData[idx].m_cmdCBFunc.m_rawCBFunc = this->m_modelList[this->m_appSettings.m_currentUseModel].m_cmdRawCBFunc[idx];
		this->m_PMBusData[idx].m_dataFormat.m_formatType = this->m_modelList[this->m_appSettings.m_currentUseModel].m_modelCMDTable->m_dataFormat.m_formatType;
	}

	PMBUSHelper::setPMBUSCMDData(this->m_PMBusData);
}

void MainFrame::SetupPMBUSCommandBufferProvider(void){
	// Setup Model's PMBUS CMD Buffer Provider
	switch (this->m_appSettings.m_currentUseCustomer){

	case Customer_GIGABYTE:

		switch (this->m_appSettings.m_currentUseModel){

		case GIGABYTE_Model_CRPS001:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup GIGABYTE_Model_CRPS001 PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer;
			break;

		case GIGABYTE_Model_CRPS001_ALL_PMBUS_COMMANDS:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup GIGABYTE_Model_CRPS001_ALL_PMBUS_COMMANDS PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer;
			break;

#if (HAVE_GENERIC_MODEL == TRUE)
		case GIGABYTE_Model_Generic:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup GIGABYTE_Model_Generic PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer;
			break;
#endif

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
			break;
		}

		break;

	case Customer_ACBEL:

		switch (this->m_appSettings.m_currentUseModel){

		case ACBEL_RFWE_24_28_1200W_SCP:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup ACBEL_RFWE_24_28_1200W_SCP PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer;
			break;

		case ACBEL_PBF003_00G:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup ACBEL_PBF003_00G PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer2BytesLengthCMD;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer2BytesLengthCMD;
			break;

#if (HAVE_GENERIC_MODEL == TRUE)
		case ACBEL__Model_Generic:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup ACBEL__Model_Generic PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer;
			break;
#endif

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
			break;
		}

		break;

#if (HAVE_GENERIC_CUSTOMER == TRUE)
	case Customer_Generic:

		switch (this->m_appSettings.m_currentUseModel){

		case GENERIC_Model_Generic:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setup GENERIC_Model_Generic PMBUSCommandBufferProvider");
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdReadCMDBufferMaker = PMBUSHelper::ProductReadCMDBuffer;
			PMBUSHelper::GetCurrentUseModel()->m_pmbusCMDbufferProvider.m_pmbusdWriteCMDBufferMaker = PMBUSHelper::ProductWriteCMDBuffer;
			break;

		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
			break;
		}

		break;
#endif

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

}

// Create Write Page Instance
#define NEW_WRITEPAGE(register_number) \
	new WritePage##register_number##H(this->m_subNotebook, label, &this->m_monitor_running,&this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);

BaseWritePage* MainFrame::getNewWritePage(int index, int register_number){
	BaseWritePage *page = NULL;
	wxString label("");
	label = wxString::Format("%02x", this->m_PMBusData[index].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[index].m_name);

	switch (register_number){

	// 00H PAGE
	case 0x00 :
		page = (BaseWritePage*)NEW_WRITEPAGE(00);
		break;
	// 01H OPERATION
	case 0x01:
		page = (BaseWritePage*)NEW_WRITEPAGE(01);
		break;
	// 02H ON_OFF_CONFIG
	case 0x02:
		page = (BaseWritePage*)NEW_WRITEPAGE(02);
		break;
	// 03H CLEAR_FAULTS
	case 0x03:
		page = (BaseWritePage*)NEW_WRITEPAGE(03);
		break;
    // 05H PAGE_PLUS_WRITE
	case 0x05:
		page = (BaseWritePage*)NEW_WRITEPAGE(05);
		break;
	// 1BH SMRALERT_MASK
	case 0x1b:
		page = (BaseWritePage*)NEW_WRITEPAGE(1B);
		break;
    // 31H POUT_MAX
	case 0x31:
		page = (BaseWritePage*)NEW_WRITEPAGE(31);
		break;
	// 3AH FAN_CONFIG_1_2
	case 0x3a:
		page = (BaseWritePage*)NEW_WRITEPAGE(3A);
		break;
	// 3BH FAN_COMMAND_1
	case 0x3b:
		page = (BaseWritePage*)NEW_WRITEPAGE(3B);
		break;
    // 46H IOUT_OC_FAULT_LIMIT
	case 0x46:
		page = (BaseWritePage*)NEW_WRITEPAGE(46);
		break;
    // 4AH IOUT_OC_WARN_LIMIT
	case 0x4a:
		page = (BaseWritePage*)NEW_WRITEPAGE(4A);
		break;
	// 51H OT_WARN_LIMIT
	case 0x51:
		page = (BaseWritePage*)NEW_WRITEPAGE(51);
		break;
	// 5DH IIC_OC_WARN_LIMIT
	case 0x5d:
		page = (BaseWritePage*)NEW_WRITEPAGE(5D);
		break;
    // 6AH POUT_OP_WARN_LIMIT
	case 0x6a:
		page = (BaseWritePage*)NEW_WRITEPAGE(6A);
		break;
	// 6BH PIN_OP_WARN_LIMIT
	case 0x6B:
		page = (BaseWritePage*)NEW_WRITEPAGE(6B);
		break;
	// 99H MFR_ID
	case 0x99:
		page = (BaseWritePage*)NEW_WRITEPAGE(99);
		break;
	// 9AH MFR_MODEL
	case 0x9a:
		page = (BaseWritePage*)NEW_WRITEPAGE(9A);
		break;
	// 9BH MFR_REVISION
	case 0x9b:
		page = (BaseWritePage*)NEW_WRITEPAGE(9B);
		break;
	// 9CH MFR_LOCATION
	case 0x9c:
		page = (BaseWritePage*)NEW_WRITEPAGE(9C);
		break;
	// 9DH MFR_DATE
	case 0x9d:
		page = (BaseWritePage*)NEW_WRITEPAGE(9D);
		break;
	// 9EH MFR_SERIAL
	case 0x9e:
		page = (BaseWritePage*)NEW_WRITEPAGE(9E);
		break;
	// C0H MFR_MAX_TEMP_1
	case 0xc0:
		page = (BaseWritePage*)NEW_WRITEPAGE(C0);
		break;
	// C1H MFR_MAX_TEMP_2
	case 0xc1:
		page = (BaseWritePage*)NEW_WRITEPAGE(C1);
		break;
	// C2H MFR_MAX_TEMP_3
	case 0xc2:
		page = (BaseWritePage*)NEW_WRITEPAGE(C2);
		break;
	// D0H Cold_Redundancy_Config
	case 0xD0:
		page = (BaseWritePage*)NEW_WRITEPAGE(D0);
		break;
	// DCH Cold_BoxSTATUS
	case 0xdc:
		page = (BaseWritePage*)NEW_WRITEPAGE(DC);
		break;
	// DDH Black_BOX_Index
	case 0xdd:
		page = (BaseWritePage*)NEW_WRITEPAGE(DD);
		break;
	case 0xec:
		page = (BaseWritePage*)NEW_WRITEPAGE(EC);
		break;
	// FAH Firmware_Update_Command
	case 0xfa:
		page = (BaseWritePage*)NEW_WRITEPAGE(FA);
		break;
	// Below were For PBF003-00G
	case 0x0900:
		page = (BaseWritePage*)NEW_WRITEPAGE(0900);
		break;
	case 0x0909:
		page = (BaseWritePage*)NEW_WRITEPAGE(0909);
		break;
	case 0x0920:
		page = (BaseWritePage*)NEW_WRITEPAGE(0920);
		break;
	case 0x0921:
		page = (BaseWritePage*)NEW_WRITEPAGE(0921);
		break;
	case 0x0923:
		page = (BaseWritePage*)NEW_WRITEPAGE(0923);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Setup Write Page of Register %02x", register_number);
		// For Avoid Crash Use WtitePage00H as Default 
		//page = (BaseWritePage*)NEW_WRITEPAGE(00);

		page = NULL;

		break;
	}

	return page;
}

void MainFrame::SetupPMBusCommandWritePage(void){

	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		if (this->m_PMBusData[idx].m_access == cmd_access_write || this->m_PMBusData[idx].m_access == cmd_access_readwrite ||
			this->m_PMBusData[idx].m_access == cmd_access_bw || this->m_PMBusData[idx].m_access == cmd_access_brbw || 
			/* this->m_PMBusData[idx].m_access == cmd_access_bwr_read || */
			this->m_PMBusData[idx].m_access == cmd_access_bwr_readwrite){

			BaseWritePage* CMDWritePage = NULL;
			CMDWritePage = getNewWritePage(idx, this->m_PMBusData[idx].m_register);

			if (CMDWritePage != NULL){
				PSU_DEBUG_PRINT(MSG_DEBUG, "Add Write Page : CMD %02x", this->m_PMBusData[idx].m_register);
				this->m_PMBusData[idx].m_writePage = CMDWritePage;// getNewPage(idx, this->m_PMBusData[idx].m_register);//new WritePage00H(this->m_subNotebook, label, &this->m_monitor_running,&this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
				this->m_subNotebook->AddPage(this->m_PMBusData[idx].m_writePage, "Write");
				this->m_subNotebook->RemovePage(1);
			}
			else{
				this->m_PMBusData[idx].m_writePage = NULL;
			}

		}
		else{
			this->m_PMBusData[idx].m_writePage = NULL;
			continue;
		}

	}

#if 0
	int cmdIndex = 0;
	wxString label("");
	
	// 00H PAGE
	cmdIndex = this->findPMBUSCMDIndex(0x00);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[0].m_writePage = getNewPage(cmdIndex, this->m_PMBusData[cmdIndex].m_register);//new WritePage00H(this->m_subNotebook, label, &this->m_monitor_running,&this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[0].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 01H OPERATION
	cmdIndex = this->findPMBUSCMDIndex(0x01);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[1].m_writePage = NEW_WRITEPAGE(01);//new WritePage01H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[1].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 02H ON_OFF_CONFIG
	cmdIndex = this->findPMBUSCMDIndex(0x02);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[2].m_writePage = NEW_WRITEPAGE(02);//new WritePage02H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[2].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 03H CLEAR_FAULTS
	cmdIndex = this->findPMBUSCMDIndex(0x03);
	if (cmdIndex >= 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Setup Write Page, cmdIndex = %d", cmdIndex);
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[3].m_writePage = NEW_WRITEPAGE(03);//new WritePage03H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[3].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 1BH SMRALERT_MASK
	cmdIndex = this->findPMBUSCMDIndex(0x1b);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(1B);//new WritePage1BH(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 3AH FAN_CONFIG_1_2
	cmdIndex = this->findPMBUSCMDIndex(0x3a);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(3A);//new WritePage3AH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 3BH FAN_COMMAND_1
	cmdIndex = this->findPMBUSCMDIndex(0x3b);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(3B);//new WritePage3BH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 51H OT_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x51);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(51);//new WritePage51H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 5DH IIC_OC_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x5D);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(5D);//new WritePage5DH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 6AH POUT_OP_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x6A);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(6A);//new WritePage6AH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 6BH PIN_OP_WARN_LIMIT
	cmdIndex = this->findPMBUSCMDIndex(0x6B);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(6B);//new WritePage6BH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 99H MFR_ID
	cmdIndex = this->findPMBUSCMDIndex(0x99);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(99);//new WritePage99H(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 9AH MFR_MODEL
	cmdIndex = this->findPMBUSCMDIndex(0x9a);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(9A);//new WritePage9AH(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 9BH MFR_REVISION
	cmdIndex = this->findPMBUSCMDIndex(0x9b);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(9B);//new WritePage9BH(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 9CH MFR_LOCATION
	cmdIndex = this->findPMBUSCMDIndex(0x9c);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(9C);//new WritePage9CH(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 9DH MFR_DATE
	cmdIndex = this->findPMBUSCMDIndex(0x9d);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(9D);//new WritePage9DH(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// 9EH MFR_SERIAL
	cmdIndex = this->findPMBUSCMDIndex(0x9e);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(9E);//new WritePage9EH(this->m_subNotebook, label);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// D0H Cold_Redundancy_Config
	cmdIndex = this->findPMBUSCMDIndex(0xd0);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(D0);//new WritePageD0H(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// DCH Cold_BoxSTATUS
	cmdIndex = this->findPMBUSCMDIndex(0xdc);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(DC);//new WritePageDCH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// DDH Black_BOX_Index
	cmdIndex = this->findPMBUSCMDIndex(0xdd);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(DD);//new WritePageDDH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}

	// FAH Firmware_Update_Command
	cmdIndex = this->findPMBUSCMDIndex(0xfa);
	if (cmdIndex >= 0){
		label = wxString::Format("%02x", this->m_PMBusData[cmdIndex].m_register);
		label.UpperCase();
		label += wxString::Format("h - %s", this->m_PMBusData[cmdIndex].m_name);
		this->m_PMBusData[cmdIndex].m_writePage = NEW_WRITEPAGE(FA);//new WritePageFAH(this->m_subNotebook, label, &this->m_monitor_running, &this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);
		this->m_subNotebook->AddPage(this->m_PMBusData[cmdIndex].m_writePage, "Write");
		this->m_subNotebook->RemovePage(2);
	}
#endif
}

// Create Read Page Instance
#define NEW_READPAGE(register_number) \
	new ReadPage##register_number##H(this->m_subNotebook, label, &this->m_monitor_running,&this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);

BaseReadPage* MainFrame::getNewReadPage(int index, int register_number){
	BaseReadPage *page = NULL;
	wxString label("");
	label = wxString::Format("%02x", this->m_PMBusData[index].m_register);
	label.UpperCase();
	label += wxString::Format("h - %s", this->m_PMBusData[index].m_name);

	switch (register_number){

	// 06H PAGE_PLUS_READ
	case 0x06:
		page = (BaseReadPage*)NEW_READPAGE(06);
		break;

	case 0x1A:
		page = (BaseReadPage*)NEW_READPAGE(1A);
		break;

	case 0x1B:
		page = (BaseReadPage*)NEW_READPAGE(1B);
		break;

	case 0x30:
		page = (BaseReadPage*)NEW_READPAGE(30);
		break;

	// Default
	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Setup Read Page of Register %02x", register_number);
		page = NULL;

		break;
	}

	return page;
}

void MainFrame::SetupPMBusCommandReadPage(void){
	
	BaseReadPage* CMDReadPage = NULL;
	
	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		if (this->m_PMBusData[idx].m_access == cmd_access_bwr_read ||
			this->m_PMBusData[idx].m_access == cmd_access_bwr_readwrite){

			CMDReadPage = NULL;
			CMDReadPage = getNewReadPage(idx, this->m_PMBusData[idx].m_register);

			if (CMDReadPage != NULL){
				PSU_DEBUG_PRINT(MSG_DEBUG, "Add Read Page : CMD %02x", this->m_PMBusData[idx].m_register);
				this->m_PMBusData[idx].m_readPage = CMDReadPage;// getNewPage(idx, this->m_PMBusData[idx].m_register);//new WritePage00H(this->m_subNotebook, label, &this->m_monitor_running,&this->m_sendCMDVector, this->m_IOAccess, &this->m_CurrentUseIOInterface);		
				this->m_subNotebook->AddPage(this->m_PMBusData[idx].m_readPage, "Read");
				this->m_subNotebook->RemovePage(1);
			}
			else{
				this->m_PMBusData[idx].m_readPage = NULL;
				
				//this->m_PMBusData[idx].m_readPage = this->ReadPanel;
				//this->m_subNotebook->AddPage(this->m_PMBusData[idx].m_readPage, "Read");
				//this->m_subNotebook->RemovePage(1);
			}

		}
		else{
			this->m_PMBusData[idx].m_readPage = NULL;
			continue;
		}

	}
}

void MainFrame::OnExit(wxCommandEvent& event)
{

	PSU_DEBUG_PRINT(MSG_ALERT, "On Exit");
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
	PSU_DEBUG_PRINT(MSG_ALERT, "Close Application");

	if (m_destroying > 0) return;

	m_destroying++;

	// Monitor is Running
	if (this->m_monitor_running == true) {
		this->m_monitor_running = false;
		// IOPortSendCMDThread is Running
		if (this->m_IOPortSendCMDThread->m_running == true && this->m_IOPortSendCMDThread->IsRunning() == true){
			
			PSU_DEBUG_PRINT(MSG_ALERT, "IOPortSendCMDThread is Running");

			wxThread::ExitCode exitCode;
			wxThreadError error = this->m_IOPortSendCMDThread->Delete(&exitCode, wxTHREAD_WAIT_YIELD);

			PSU_DEBUG_PRINT(MSG_ALERT, "IOPortSendCMDThread Exit Code = %p", ((int*)exitCode));

			if (error != wxTHREAD_NO_ERROR){
				PSU_DEBUG_PRINT(MSG_ERROR, "wxThreadError = %d", error);
			}

			// Wait Until Send Thread Complete
			while (!this->m_sendThreadStopFlag) { PSU_DEBUG_PRINT(MSG_ALERT, "Wait IOPortSendCMDThread Finish"); };
		}
	}

	// Clear Send CMD Vector
	this->m_sendCMDVector.clear();

	// Check TaskSystem Have Task or Not
	int cnt = Task::GetCount();

	wxBusyInfo *info = NULL;

	// Wait Until No Tasks
	while (cnt != 0){
		
#if wxCHECK_VERSION(3, 1, 0)
		if (info == NULL) info = new wxBusyInfo(
			wxBusyInfoFlags()
			.Parent(this)
			.Icon(wxArtProvider::GetIcon(wxART_CLOSE,
			wxART_OTHER, wxSize(64, 64)))
			.Title("<b>Close Program</b>")
			.Text("Please  wait  ...")
			.Foreground(*wxBLACK)
			.Background(*wxCYAN)
			.Transparency(wxALPHA_OPAQUE)// 4 * wxALPHA_OPAQUE / 5)
			);
#endif

		PSU_DEBUG_PRINT(MSG_ALERT, "cnt = %d", cnt);

		cnt = Task::GetCount();

		wxMilliSleep(100);

	};

	wxDELETE(info);

	// Stop Task System Thread
	if (this->m_TaskSystemThread != NULL){
		if (this->m_TaskSystemThread->m_running == true){
			this->m_TaskSystemThread->m_running = false;
		}
	}


	if (this->m_appSettings.m_increaseCPUOverhead == Generic_Enable){
		if (this->m_increaseCPUOverHeadThread != NULL){
			if (this->m_increaseCPUOverHeadThread->m_running == true){
				this->m_increaseCPUOverHeadThread->m_running = false;
			}
		}
	}

#if (INCREASE_CPU_OVERHEAD == TRUE)
	if (this->m_increaseCPUOverHeadThread != NULL){
		if (this->m_increaseCPUOverHeadThread->m_running == true){
			this->m_increaseCPUOverHeadThread->m_running = false;
		}
	}
#endif

	// Release Task List
	TaskEx::ReleaseTaskList();

	PSU_DEBUG_PRINT(MSG_ALERT, "Close IO Device");
	// Close IO Device
	this->CloseIODevice();

	// Delete Resource
	delete[] this->m_PMBusData;

	// Save Config
	this->SaveConfig();

	wxLog::SetActiveTarget(m_oldLogger);

	if (this->m_logFileFFileOutputStream) { wxDELETE(this->m_logFileFFileOutputStream); }
	if (this->m_logFileTextOutputStream) { wxDELETE(this->m_logFileTextOutputStream); }

	//Destroy();
	event.Skip();
}

void MainFrame::OnReadTest(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	ReadTestDialog* readTestDialog = new ReadTestDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	readTestDialog->Centre();
	readTestDialog->ShowModal();

	wxDELETE(readTestDialog);
}

void MainFrame::OnWriteTest(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	WriteTestDialog* writeTestDialog = new WriteTestDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	writeTestDialog->Centre();
	writeTestDialog->ShowModal();

	wxDELETE(writeTestDialog);
}

void MainFrame::OnBlockWRTest(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	BlockWRTestDialog* blockWRTestDialog = new BlockWRTestDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	blockWRTestDialog->Centre();
	blockWRTestDialog->ShowModal();

	wxDELETE(blockWRTestDialog);

}

void MainFrame::OnFRUMaker(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	FRUMakerDialog* fruMakerDialog = new FRUMakerDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	fruMakerDialog->Centre();
	fruMakerDialog->ShowModal();

	wxDELETE(fruMakerDialog);
}

void MainFrame::OnFRUWriter(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	/*** Check if Monitor is Running ***/
	if (this->m_monitor_running == true){
		wxMessageBox(wxT("Monitor is running, Please stop monitor then try again !"),
			wxT("Monitor is running !"),  // caption
			wxOK | wxICON_INFORMATION);

		return;
	}

	FRUUtilityDialog* fruUtilityDialog = new FRUUtilityDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface);
	fruUtilityDialog->Centre();
	fruUtilityDialog->ShowModal();

	wxDELETE(fruUtilityDialog);
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

void MainFrame::OnAcbelWebSite(wxCommandEvent& event){
	wxLaunchDefaultBrowser(wxT("http://www.acbel.com.tw"));
}

void MainFrame::OnPrimaryFirmware(wxCommandEvent& event){
	this->HexToBin();
}

void MainFrame::OnSecondaryFirmware(wxCommandEvent& event)
{
	this->HexToBin();
}

void MainFrame::OnUpdatePrimaryFirmware(wxCommandEvent& event){

	// Check If Model Support ISP
	int isp_support_confirm = 0;
	if (PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_isp_support == false) {
		
		wxMessageDialog* ispConfirmDialog = new wxMessageDialog(this, wxT("This Model Seems like Not support ISP, Do you want to continue anyway ?"), wxT("Model Not Support ISP"), wxYES_NO | wxICON_WARNING);
		ispConfirmDialog->Centre();
		isp_support_confirm = ispConfirmDialog->ShowModal();

		delete ispConfirmDialog;

		if (isp_support_confirm == wxID_NO) {
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel Load FW");
			return;
		}
	}

	// Delete previous primary panel instance
	if (this->PMBusPrimaryFWUpdatePanel) {
		// Get index of notebook
		unsigned int deleteIndex = this->PMBusPrimaryFWUpdatePanel->GetIndexOfNotebook();
		unsigned int currentPageCount = m_notebook->GetPageCount();
		PSU_DEBUG_PRINT(MSG_DEBUG, "currentPageCount=%d, deleteIndex=%d", currentPageCount, deleteIndex);

		if (deleteIndex > (currentPageCount - 1)){
			deleteIndex = (currentPageCount - 1);
		}

		if (deleteIndex == this->m_notebook->GetSelection()){
			this->m_notebook->SetSelection(0);
		}

		if (this->PMBusPrimaryFWUpdatePanel->isCloseButtonPressed() == false){
			this->m_notebook->RemovePage(deleteIndex);
		}

		wxDELETE(this->PMBusPrimaryFWUpdatePanel);
	}

	// If Monitor is Running
	int confirm = 0;
	if (this->m_monitor_running == true){
		wxMessageDialog* confirmDialog = new wxMessageDialog(this, wxT("Monitor is Running, Do you want to stop monitor ?"), wxT("Confirm"), wxYES_NO | wxICON_INFORMATION);
		confirmDialog->Centre();
		confirm = confirmDialog->ShowModal();

		delete confirmDialog;

		if (confirm == wxID_NO){
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel Load FW");
			return;
		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Stop Monitor");
			this->StopMonitor();
		}
	}

	// Load Hex File
	wxFileDialog LoadHexFileDialog(this, L"Load Primary Firmware File", "", "", "HEX Files (*.hex)|*.hex", wxFD_OPEN);

	LoadHexFileDialog.Centre();

	// If the user changed idea...
	if (LoadHexFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

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
	//TIHexFileParser tiHexFileStat;
	//TIHexInput >> tiHexFileStat;
	m_PrimaryTIHexFileStat.ClearALL();
	TIHexInput >> m_PrimaryTIHexFileStat; //

	// Check Errors
	if (m_PrimaryTIHexFileStat.getNoErrors() != 0){
		
		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Errors :");

		while (m_PrimaryTIHexFileStat.getNoErrors() != 0){
			string error_str;
			m_PrimaryTIHexFileStat.popNextError(error_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", error_str.c_str());
		}
		
		
		wxMessageBox(wxT("Load Hex File Has Error"),
			wxT("Error !"),
			wxOK | wxICON_ERROR);

		return;
	}

	// Check Warnings
	if (m_PrimaryTIHexFileStat.getNoWarnings() != 0)
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Warnings :");

		while (m_PrimaryTIHexFileStat.getNoWarnings() != 0){
			string warning_str;
			m_PrimaryTIHexFileStat.popNextWarning(warning_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", warning_str.c_str());
		}

		wxMessageBox(wxT("Load Hex File Has Warning"),
			wxT("Warning !"),
			wxOK | wxICON_WARNING);
	}


	/* Fill Blank Address                                                     */
	//tiHexFileStat.fillBlankAddr(0xffff);
	m_PrimaryTIHexFileStat.fillBlankAddr(0xffff);


	if (!this->PMBusPrimaryFWUpdatePanel){
		this->PMBusPrimaryFWUpdatePanel = new PMBUSFWUpdatePanel(
			m_notebook, 
			path, 
			&m_PrimaryTIHexFileStat, 
			this->m_IOAccess, 
			&this->m_CurrentUseIOInterface, 
			&this->m_monitor_running,
			UPDATE_PRIMARY_FW_TARGET, 
			this->m_appSettings.m_developerMode
		);
	}

	// Add page to NoteBook
	m_notebook->AddPage(this->PMBusPrimaryFWUpdatePanel, "Primary FW Update", true);
	// Save Index Of Notebook
	this->PMBusPrimaryFWUpdatePanel->GetIndexOfNotebook() = (m_notebook->GetPageCount() - 1);

}

void MainFrame::OnUpdateSecondaryFirmware(wxCommandEvent& event){
	
	// Check If Model Support ISP
	int isp_support_confirm = 0;
	if (PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_isp_support == false) {

		wxMessageDialog* ispConfirmDialog = new wxMessageDialog(this, wxT("This Model Seems like Not support ISP, Do you want to continue anyway ?"), wxT("Model Not Support ISP"), wxYES_NO | wxICON_WARNING);
		ispConfirmDialog->Centre();
		isp_support_confirm = ispConfirmDialog->ShowModal();

		delete ispConfirmDialog;

		if (isp_support_confirm == wxID_NO) {
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel Load FW");
			return;
		}
	}

	// Delete previous secondary panel instance
	if (this->PMBusSecondaryFWUpdatePanel) {
		// Get index of notebook
		unsigned int deleteIndex = this->PMBusSecondaryFWUpdatePanel->GetIndexOfNotebook();
		unsigned int currentPageCount = m_notebook->GetPageCount();
		PSU_DEBUG_PRINT(MSG_DEBUG, "currentPageCount=%d, deleteIndex=%d", currentPageCount, deleteIndex);

		if (deleteIndex > (currentPageCount-1)){
			deleteIndex = (currentPageCount-1);
		}

		if (deleteIndex == this->m_notebook->GetSelection()){
			this->m_notebook->SetSelection(0);
		}

		if (this->PMBusSecondaryFWUpdatePanel->isCloseButtonPressed() == false){
			this->m_notebook->RemovePage(deleteIndex);
		}

		wxDELETE(this->PMBusSecondaryFWUpdatePanel);
	}
	
	// If Monitor is Running
	int confirm = 0;
	if (this->m_monitor_running == true){
		wxMessageDialog* confirmDialog = new wxMessageDialog(this, wxT("Monitor is Running, Do you want to stop monitor ?"), wxT("Confirm"), wxYES_NO | wxICON_INFORMATION);
		confirmDialog->Centre();
		confirm = confirmDialog->ShowModal();

		delete confirmDialog;

		if (confirm == wxID_NO){
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel Load FW");
			return;
		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Stop Monitor");
			this->StopMonitor();
		}
	}

	// Load Hex File
	wxFileDialog LoadHexFileDialog(this, L"Load Secondary Firmware File", "", "", "HEX Files (*.hex)|*.hex", wxFD_OPEN);
	
	LoadHexFileDialog.Centre();

	// If the user changed idea...
	if (LoadHexFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

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
	//TIHexFileParser tiHexFileStat;
	//TIHexInput >> tiHexFileStat;
	m_SecondaryTIHexFileStat.ClearALL();
	TIHexInput >> m_SecondaryTIHexFileStat; //

	// Check Errors
	if (m_SecondaryTIHexFileStat.getNoErrors() != 0){

		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Errors :");

		while (m_SecondaryTIHexFileStat.getNoErrors() != 0){
			string error_str;
			m_SecondaryTIHexFileStat.popNextError(error_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", error_str.c_str());
		}


		wxMessageBox(wxT("Load Hex File Has Error"),
			wxT("Error !"),
			wxOK | wxICON_ERROR);

		return;
	}

	// Check Warnings
	if (m_SecondaryTIHexFileStat.getNoWarnings() != 0)
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Warnings :");

		while (m_SecondaryTIHexFileStat.getNoWarnings() != 0){
			string warning_str;
			m_SecondaryTIHexFileStat.popNextWarning(warning_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", warning_str.c_str());
		}

		wxMessageBox(wxT("Load Hex File Has Warning"),
			wxT("Warning !"),
			wxOK | wxICON_WARNING);
	}


	/* Fill Blank Address                                                     */
	//tiHexFileStat.fillBlankAddr(0xffff);
	m_SecondaryTIHexFileStat.fillBlankAddr(0xffff);


	if (!this->PMBusSecondaryFWUpdatePanel){
		this->PMBusSecondaryFWUpdatePanel = new PMBUSFWUpdatePanel(
			m_notebook, 
			path, 
			&m_SecondaryTIHexFileStat, 
			this->m_IOAccess, 
			&this->m_CurrentUseIOInterface, 
			&this->m_monitor_running,
			UPDATE_SECONDARY_FW_TARGET, 
			this->m_appSettings.m_developerMode
		);
	}
	
	// Add page to NoteBook
	m_notebook->AddPage(this->PMBusSecondaryFWUpdatePanel, "Secondary FW Update", true);
	// Save Index Of Notebook
	this->PMBusSecondaryFWUpdatePanel->GetIndexOfNotebook() = (m_notebook->GetPageCount() - 1);
}

void MainFrame::OnStopProgramming(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void MainFrame::OnQueryAllCommands(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnQueryAllCommands");

	/*** If I/O is Close ***/
	if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_CLOSE){
		wxMessageBox(wxT("No I/O Device Found, Please Check Adaptor Card Setting !"),
			wxT("No I/O Device Found !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	/*** Send Query Start Event To Handler Function ***/
	wxThreadEvent *threadQueryStart_evt;

	threadQueryStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_QUERY_SEQUENCE_START);
	threadQueryStart_evt->SetString(wxT("Query All Commands"));
	wxQueueEvent(this->GetEventHandler(), threadQueryStart_evt);


}

void MainFrame::OnFindAvailableI2CSlaveDevice(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnFindAvailableI2CSlaveDevice");

	/*** If I/O is Close ***/
	if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_CLOSE){
		wxMessageBox(wxT("No I/O Device Found, Please Check Adaptor Card Setting !"),
			wxT("No I/O Device Found !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	// If Monitor is Running
	int confirm = 0;
	if (this->m_monitor_running == true){
		wxMessageDialog* confirmDialog = new wxMessageDialog(this, wxT("Monitor is Running, Do you want to stop monitor ?"), wxT("Confirm"), wxYES_NO | wxICON_INFORMATION);
		confirmDialog->Centre();
		confirm = confirmDialog->ShowModal();

		delete confirmDialog;

		if (confirm == wxID_NO){
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel");
			return;
		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Stop Monitor");
			this->StopMonitor();
		}
	}

	/*** Trigger Find I2C Slave Start Event ***/
	wxThreadEvent *findI2CSalveStart_evt;

	findI2CSalveStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_FIND_I2C_SLAVE_START);
	findI2CSalveStart_evt->SetString(wxT("Find I2C Slave Start"));
	wxQueueEvent(this->GetEventHandler(), findI2CSalveStart_evt);

}

void MainFrame::OnI2CFaultTest(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_ALERT, "OnI2CFaultTest");
}

void MainFrame::OnEnableChecksum(wxCommandEvent& event){
	
	if (this->m_appSettings.m_EnableChecksum == Generic_Enable){
		this->m_appSettings.m_EnableChecksum = Generic_Disable;

		this->m_EnableChecksumMenuItem->Check(false);
	}
	else if (this->m_appSettings.m_EnableChecksum == Generic_Disable){
		this->m_appSettings.m_EnableChecksum = Generic_Enable;

		this->m_EnableChecksumMenuItem->Check(true);
	}
}

void MainFrame::OnOnlyPollingSupportCommand(wxCommandEvent& event){
	
	if (this->m_appSettings.m_onlyPollingSupportCMD == Generic_Enable){
		this->m_appSettings.m_onlyPollingSupportCMD = Generic_Disable;

		this->m_onlyPollingSupportCMDMenuItem->Check(false);
	}
	else if (this->m_appSettings.m_onlyPollingSupportCMD == Generic_Disable){
		this->m_appSettings.m_onlyPollingSupportCMD = Generic_Enable;

		this->m_onlyPollingSupportCMDMenuItem->Check(true);
	}
}

void MainFrame::OnAutoQueryCMDOnIOOpen(wxCommandEvent& event){

	if (this->m_appSettings.m_autoQueryCMDOnIOOpen == Generic_Enable){
		this->m_appSettings.m_autoQueryCMDOnIOOpen = Generic_Disable;

		this->m_autoQueryCMDOnIOOpenMenuItem->Check(false);
	}
	else if (this->m_appSettings.m_autoQueryCMDOnIOOpen == Generic_Disable){
		this->m_appSettings.m_autoQueryCMDOnIOOpen = Generic_Enable;

		this->m_autoQueryCMDOnIOOpenMenuItem->Check(true);
	}
}

void MainFrame::OnQueryCMDBeforePolling(wxCommandEvent& event){
	
	if (this->m_appSettings.m_queryCMDBeforePolling == Generic_Enable){
		this->m_appSettings.m_queryCMDBeforePolling = Generic_Disable;

		this->m_queryCMDBeforePollingMenuItem->Check(false);
	}
	else if (this->m_appSettings.m_queryCMDBeforePolling == Generic_Disable){
		this->m_appSettings.m_queryCMDBeforePolling = Generic_Enable;

		this->m_queryCMDBeforePollingMenuItem->Check(true);
	}
}

void MainFrame::OnClearLogBeforeMonitorRun(wxCommandEvent& event){
	
	if (this->m_appSettings.m_clearLogBeforeMonitorRun == Generic_Enable){
		this->m_appSettings.m_clearLogBeforeMonitorRun = Generic_Disable;

		this->m_clearLogBeforeMonitorRun->Check(false);
	}
	else if (this->m_appSettings.m_clearLogBeforeMonitorRun == Generic_Disable){
		this->m_appSettings.m_clearLogBeforeMonitorRun = Generic_Enable;

		this->m_clearLogBeforeMonitorRun->Check(true);
	}

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

#define CMD_C3H_BYTES_TO_READ  6/**< Bytes To Read */
void MainFrame::OnEnableCalibration(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	// Do Enable Calibration
	this->DoEnableCalibration();
}

void MainFrame::OnDisableCalibration(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	// Disable Calibration Command
	this->DoDisableCalibration();
}

void MainFrame::OnCalibration(wxCommandEvent& event){
	// Show Calibration Dialog
	CalibrationDialog* calibrationDlg = new CalibrationDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_monitor_running, &this->m_monitor_pause, &this->m_sendCMDVector);
	calibrationDlg->Centre();
	calibrationDlg->ShowModal();

	delete calibrationDlg;
}

void MainFrame::OnAdministrant(wxCommandEvent& event){
	wxString password;
	int dialog_ret = 0;

	
	wxPasswordEntryDialog *passwordEntryDialog = new wxPasswordEntryDialog(this, wxT("Please Input Administrator Password"));
	dialog_ret = passwordEntryDialog->ShowModal();

	// If user press cancel
	if (dialog_ret == wxID_CANCEL){
		delete passwordEntryDialog;
		return;
	}

	password = passwordEntryDialog->GetValue();

	if (password.compare(ADMINISTRATOR_PASSWORD) == 0){
		//PSU_DEBUG_PRINT(MSG_DEBUG, "Password = %s", password.c_str());
		// Enable Update Firmware
		this->m_runMenu->Enable(MENU_ID_Update_Primary_Firmware, true);
		this->m_runMenu->Enable(MENU_ID_Update_Secondary_Firmware, true);
	}
	else if (password.compare(DEVELOPER_PASSWORD) == 0){
		// Enable Update Firmware
		this->m_runMenu->Enable(MENU_ID_Update_Primary_Firmware, true);
		this->m_runMenu->Enable(MENU_ID_Update_Secondary_Firmware, true);

		// Enable Developer Mode
		this->m_appSettings.m_developerMode = Generic_Enable;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Password Not Match");

		wxMessageBox(wxT("Password Not Match !"),
			wxT("Password Not Match"),
			wxOK | wxICON_ERROR);
	}

	delete passwordEntryDialog;
}

void MainFrame::OnI2CInterface(wxCommandEvent& event){
	
	I2CInterfaceDialog* i2cIFDialog = new I2CInterfaceDialog(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, &this->m_appSettings, this->m_status_bar);
	i2cIFDialog->Centre();
	i2cIFDialog->ShowModal();

	delete i2cIFDialog;
}

void MainFrame::OnI2CSlaveAddress(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	I2CSlaveAddressDialog* i2cSlaveAddressDialog = new I2CSlaveAddressDialog(this, &this->m_appSettings);
	i2cSlaveAddressDialog->Centre();
	int retValue = i2cSlaveAddressDialog->ShowModal();

	PSU_DEBUG_PRINT(MSG_DEBUG, "i2cSlaveAddressDialog Return Value = %d", retValue);

	if (retValue != wxID_CANCEL){
		// Update Address Input TextCtrl in TooBar
		wxString HexSlaveAddress = wxString::Format("%2x", retValue);
		HexSlaveAddress.UpperCase();
		m_address_input->SetValue(HexSlaveAddress);

		// Update 
		// Reset Windows Title String
		wxString winTitle = PMBUSHelper::getWinTitleBase();
		winTitle += wxT("  I2C Slave Address : ");
		winTitle += HexSlaveAddress;
		this->SetTitle(winTitle);
		//

		this->m_infoBar->SetBackgroundColour(wxColour(127, 246, 85));

		this->m_infoBar->ShowMessage(
			wxString::Format("Change Slave Address To %s", HexSlaveAddress.c_str()), wxICON_INFORMATION
			);

		this->m_infoBarTimer->Start(3000, true);

	}

	wxDELETE(i2cSlaveAddressDialog);
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

	wxLog::SetLogLevel(wxLOG_Message);
}

void MainFrame::OnErrorLogErrorOnly(wxCommandEvent& event){
	
	this->m_appSettings.m_logMode = Log_Mode_Log_Error_Only;
	this->m_allMenuItem->Check(false);
	this->m_errorOnlyMenuItem->Check(true);

	wxLog::SetLogLevel(wxLOG_Warning);
}

void MainFrame::OnLogToFile(wxCommandEvent& event){

	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->SetPath(wxT("/LOG"));

	if (this->m_appSettings.m_logToFile == Generic_Enable){
		this->m_logToFileMenuItem->Check(false);
		this->m_appSettings.m_logToFile = Generic_Disable;

		// Log To File
		pConfig->Write(wxT("LogToFile"), this->m_appSettings.m_logToFile);

		pConfig->Flush();
	}
	else{
		
		//wxStandardPaths standardPath = wxStandardPaths::Get();
		wxDirDialog *dirDialog = new wxDirDialog(this, wxT("Please Select A Directory"), wxT("C:\\"));// standardPath.GetDocumentsDir());
		//dirDialog->Centre(wxCENTER_ON_SCREEN);

		if (dirDialog->ShowModal() == wxID_CANCEL){
			PSU_DEBUG_PRINT(MSG_DEBUG, "Select Dir Cancel");
			this->m_logToFileMenuItem->Check(false);
			return;
		}

		//
		this->m_logToFileMenuItem->Check(true);
		this->m_appSettings.m_logToFile = Generic_Enable;

		// 
		wxString logFileDirPath("");
		logFileDirPath = dirDialog->GetPath();
		logFileDirPath += wxT("\\");

		PSU_DEBUG_PRINT(MSG_ALERT, "%s", logFileDirPath.c_str());

		// Set Log File's Save Directory Path
		this->m_appSettings.m_logFilePath = logFileDirPath;

		// Log To File
		pConfig->Write(wxT("LogToFile"), this->m_appSettings.m_logToFile);

		// Log File Path
		pConfig->Write(wxT("LogFilePath"), this->m_appSettings.m_logFilePath);

		pConfig->Flush();

		// No more need
		delete dirDialog;
		
		// Init Output Stream
		this->ReInitLogFileOutputStream(this->m_appSettings.m_logFilePath);

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
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not Save List To %s", SavePath);
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

	this->Refresh();
}

void MainFrame::StartMonitor(void){
	
	// Select Notebook Page 0
	this->m_notebook->SetSelection(0);

	// Clear Log Before Monitor Run
	if (this->m_appSettings.m_clearLogBeforeMonitorRun == Generic_Enable){
		this->m_debugLogTC->Clear();

		PMBUSHelper::cmd_3AH_previous = 0x00;
		PMBUSHelper::cmd_78H_previous = 0x00;
		PMBUSHelper::cmd_79H_previous = 0x00;
		PMBUSHelper::cmd_7AH_previous = 0x00;
		PMBUSHelper::cmd_7BH_previous = 0x00;
		PMBUSHelper::cmd_7CH_previous = 0x00;
		PMBUSHelper::cmd_7DH_previous = 0x00;
		PMBUSHelper::cmd_7EH_previous = 0x00;
		PMBUSHelper::cmd_7FH_previous = 0x00;
		PMBUSHelper::cmd_81H_previous = 0x00;
	}

	// Check Count of Enabled CMD
	int enabledCount = 0;
	for (unsigned int idx = 0; idx<PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		if (this->m_PMBusData[idx].m_toggle == true){
			if (this->m_appSettings.m_onlyPollingSupportCMD == Generic_Enable){
				// If support
				if (this->m_PMBusData[idx].m_cmdStatus.m_support != cmd_unsupport){
					// If Own Read Access
					if (PMBUSHelper::isOwnReadAccess(this->m_PMBusData[idx].m_access) == true){
						enabledCount++;
					}
				}
			}
			else{
				// If Own Read Access
				if (PMBUSHelper::isOwnReadAccess(this->m_PMBusData[idx].m_access) == true){
					enabledCount++;
				}
			}
		}
	}

	if (enabledCount == 0){

		PSU_DEBUG_PRINT(MSG_ALERT, "No Enabled/Support CMD Selected");

		wxMessageBox(wxT("No Enabled/Support CMD ! \n\n Please Select CMD Then Try Again"),
			wxT("Warning !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}
	
	this->m_monitor_running = true;


#ifdef _WIN32
	
	this->m_toolbar->FindById(MENU_ID_Monitor)->SetNormalBitmap(*this->m_pauseBitmap);	
	
	this->m_monitorMenuItem->SetBitmap(*m_pause16Bitmap);

#else
#ifdef __GNUC__
	
	wxToolBarToolBase *tool = this->m_toolbar->RemoveTool(MENU_ID_Monitor);

	tool->SetNormalBitmap(*this->m_pauseBitmap);

	this->m_toolbar->InsertTool(1, tool);

#endif
#endif

	this->m_toolbar->Realize();

	this->m_readTestMenuItem->Enable(false);
	this->m_writeTestMenuItem->Enable(false);
	this->m_blockWRTestMenuItem->Enable(false);
	this->m_fruMakerMenuItem->Enable(false);
	this->m_fruWriterMenuItem->Enable(false);

	(this->m_status_bar->getTimer())->Start(1000);
	this->m_status_bar->getBeginDateTime() = wxDateTime::Now();


	PSU_DEBUG_PRINT(MSG_DETAIL, "Start Send Data Thread");
	this->m_IOPortSendCMDThread = new IOPortSendCMDThread(this, this->m_IOAccess, &this->m_CurrentUseIOInterface, this->m_rxTxSemaphore, &this->m_appSettings, &this->m_polling_time, this->m_PMBusData, &this->m_IOPortRecvBuff, &m_cmdListModel, this->m_status_bar, this->m_stdPage, PMBusStatusPanel, PMBusStatusDCHPanel, &this->m_sendCMDVector);
	
	//this->m_IOPortSendCMDThread->SetPriority(wxPRIORITY_MIN);

	// If Create Thread Success
	if (this->m_IOPortSendCMDThread->Create() != wxTHREAD_NO_ERROR){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Create Send Command Thread");
	}
	else{
		
		// Clear Query Filed 
		for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
			this->m_PMBusData[idx].m_cmdStatus.m_queried = cmd_query_not_yet;
		}
		
		this->m_IOPortSendCMDThread->Run();
		this->m_sendThreadStopFlag = false;
	}

}

void MainFrame::StopMonitor(void){
	this->m_monitor_running = false;

#ifdef _WIN32	
	
	this->m_toolbar->FindById(MENU_ID_Monitor)->SetNormalBitmap(*this->m_monitorBitmap);
	
	this->m_monitorMenuItem->SetBitmap(*m_monitor16Bitmap);

#else
#ifdef __GNUC__

	wxToolBarToolBase *tool = this->m_toolbar->RemoveTool(MENU_ID_Monitor);

	tool->SetNormalBitmap(*m_monitorBitmap);

	this->m_toolbar->InsertTool(1, tool);

#endif
#endif

	this->m_toolbar->Realize();

	(this->m_status_bar->getTimer())->Stop();
	PSU_DEBUG_PRINT(MSG_DETAIL, "Stop Send Data Thread");
	if(this->m_IOPortSendCMDThread != NULL) this->m_IOPortSendCMDThread->Delete();//this->m_IOPortSendCMDThread->m_running = false;
}

void MainFrame::OnMonitor(wxCommandEvent& event){
	
	/*** Send Monitor Start Event To Handler Function ***/
	wxThreadEvent *threadMonitorStart_evt;

	threadMonitorStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_MONITOR_START);
	threadMonitorStart_evt->SetString(wxT("Monitor Start"));
	wxQueueEvent(this->GetEventHandler(), threadMonitorStart_evt);

}

void MainFrame::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
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

	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%-8s   %s", threadstr, msg);//wxString::Format("%9s %10s           %s", timestr, threadstr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#else
	//text->AppendText(wxString::Format("%9s           %s", timestr, msg));
	text->AppendText(wxString::Format("%-s", msg));

	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%-s", msg);//wxString::Format("%9s           %s", timestr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif
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
		level,
		this->m_debugLogTC,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		//: wxString::Format("%lx", info.threadId),
		: wxString::Format("%04x", (int)info.threadId),
		msg + "\n"
	);

}

void MainFrame::OnPollingTimeCombo(wxCommandEvent& event){
	this->m_polling_time = wxAtoi(m_polling_time_combobox->GetValue());
	this->m_appSettings.m_pollingInterval = this->m_polling_time;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Select Polling Time is %d", this->m_polling_time);
	this->m_cmdListDVC->SetFocus();
}

void MainFrame::OnSlaveAddressSetButton(wxCommandEvent& event){
	
	unsigned long SlaveAddress = PMBUSHelper::HexToDecimal(this->m_address_input->GetValue().c_str());
	
	// Check Slave Address Valid ?
	if (SlaveAddress == 0){
		wxMessageBox(wxT("Input I2C Slave Address Error ! \n\n Please Input Valid I2C Slave Address"),
			wxT("Error !"),  // caption
			wxOK | wxICON_ERROR);

		return;
	}

	this->m_appSettings.m_I2CSlaveAddress = SlaveAddress;
	PMBUSHelper::GetSlaveAddress() = this->m_appSettings.m_I2CSlaveAddress;
	wxString hex = (wxString::Format("%2x", PMBUSHelper::GetSlaveAddress())).Upper();
	PSU_DEBUG_PRINT(MSG_DEBUG, "Change Slave Address To %s", hex.c_str());

	// Reset Windows Title String
	wxString winTitle = PMBUSHelper::getWinTitleBase();
	winTitle += wxT("  I2C Slave Address : ");
	winTitle += hex;
	this->SetTitle(winTitle);
	//

	this->m_infoBar->SetBackgroundColour(wxColour( 127, 246, 85));

	this->m_infoBar->ShowMessage(
		wxString::Format("Change Slave Address To %s", hex.c_str()), wxICON_INFORMATION
	);

	this->m_infoBarTimer->Start(3000, true);
}

void MainFrame::OnContextMenu(wxDataViewEvent &event){
	// Show Popup Menu
	this->m_cmdListDVC->PopupMenu(this->m_cmdListPopupMenu);
}

unsigned int MainFrame::getCurrentUseIOInterface(void){
	return this->m_CurrentUseIOInterface;
}

void MainFrame::OnDVItemActivated(wxDataViewEvent &event){

	/* This event is triggered by double clicking an item or pressing some special key (usually "Enter") when it is focused. */
	// Get the row position
	wxDataViewItem item = event.GetItem();
	int row = m_cmdListModel->GetRow(item);
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s : Select Row is %d", __FUNCTIONW__, row);

}

void MainFrame::OnDVSelectionChanged(wxDataViewEvent &event)
{

	wxDataViewItem item = event.GetItem();

	//PSUDataViewListModel* model = (PSUDataViewListModel*)this->m_dataViewCtrl->GetModel();

	int row = m_cmdListModel->GetRow(item);

	if (row < 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "No Row Selected");
		return;
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "Selected Row is : %d", row);
	PSU_DEBUG_PRINT(MSG_DEBUG, "CMD's RW Attribute is : %d", this->m_PMBusData[row].m_access);

	// Add Read And Write Page into Notebook Dynamically

	// Check Current Page Counts of Notebook
	unsigned int page_counts = this->m_subNotebook->GetPageCount();
	PSU_DEBUG_PRINT(MSG_DEBUG, "Current Page Counts = %d", page_counts);
	if(page_counts > 1){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Current Page Counts = %d", page_counts);
		 // Remove Current Read/Write Pages
		for(unsigned int idx=page_counts-1; idx > 0; idx--){
			this->m_subNotebook->RemovePage(idx);
		}
	}

	// Add Read Pages
	if (this->m_PMBusData[row].m_readPage != NULL){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Add Read Page");
		this->m_subNotebook->AddPage(this->m_PMBusData[row].m_readPage, "Read");
	}

	// Add Write Pages 
	if (this->m_PMBusData[row].m_writePage != NULL){
		
		PSU_DEBUG_PRINT(MSG_DEBUG, "this->m_PMBusData[row].m_dataFormat.m_formatType = %d", this->m_PMBusData[row].m_dataFormat.m_formatType);

		switch (this->m_PMBusData[row].m_dataFormat.m_formatType){

		case cmd_data_format_LinearData_Format:
			
			((BaseWritePage*)this->m_PMBusData[row].m_writePage)->changeLayOutByDataFormat(cmd_data_format_LinearData_Format, &this->m_PMBusData[row]);// cmd_data_format_LinearData_Format);

			// Test purpose only
			//#define GET_WRITEPAGE(register_number) (WritePage##register_number##H*)
			//(GET_WRITEPAGE(46)this->m_PMBusData[row].m_writePage)->m_scaleValue->Enable(false);

			break;

		case cmd_data_format_DirectData_Format:
			
			((BaseWritePage*)this->m_PMBusData[row].m_writePage)->changeLayOutByDataFormat(cmd_data_format_DirectData_Format, &this->m_PMBusData[row]);

			break;

		default:
			// Do Nothing
			break;
		}
		
		PSU_DEBUG_PRINT(MSG_DEBUG, "Add Write Page");
		this->m_subNotebook->AddPage(this->m_PMBusData[row].m_writePage, "Write");
	}

	// Select Page
	page_counts = this->m_subNotebook->GetPageCount();
	this->m_subNotebook->SetSelection(page_counts-1);

}

void MainFrame::OnDVValueChanged(wxDataViewEvent &event){

#if 0
	/*wxString title*/
	unsigned int row = m_cmdListModel->GetRow(event.GetItem());//GetTitle(event.GetItem());
	PSU_DEBUG_PRINT(MSG_DETAIL, "wxEVT_DATAVIEW_ITEM_VALUE_CHANGED");// , Item Id : %s;  Column: %d",
	//title, event.GetColumn());
#endif

	int enabledCMDCount = 0;

	if (this->m_monitor_running == true){
		//
		for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){

			if (PMBUSHelper::isOwnReadAccess(this->m_PMBusData[idx].m_access) == true){

				if (this->m_PMBusData[idx].m_toggle == true){
					enabledCMDCount++;

					if (enabledCMDCount > 0){
						PSU_DEBUG_PRINT(MSG_ALERT, "CMD %02xH is Enable", this->m_PMBusData[idx].m_register);
						break;
					}
				}

			}
		}

		if (enabledCMDCount == 0){
			PSU_DEBUG_PRINT(MSG_ALERT, "No CMD(Read Access) Enabled !");
			this->StopMonitor();
		}
	}


}

void MainFrame::OnDisableAll(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DETAIL, "Disable ALL Commands");
	// Disable ALL Command
	for (unsigned int idx = 0; idx<PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		this->m_PMBusData[idx].m_toggle = false;
	}

	wxVariant variant;
	variant = false;

	for (unsigned int idx = 0; idx<PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		this->m_cmdListModel->SetValueByRow(variant, idx, PMBUSCMDListModel::Col_Toggle);
		this->m_cmdListModel->RowValueChanged(idx, PMBUSCMDListModel::Col_Toggle);
	}
}

void MainFrame::OnEnableAll(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DETAIL, "Enable ALL Commands");
	// Enable ALL Command
	for (unsigned int idx = 0; idx<PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		this->m_PMBusData[idx].m_toggle = true;
	}

	wxVariant variant;
	variant = true;

	for (unsigned int idx = 0; idx<PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		this->m_cmdListModel->SetValueByRow(variant, idx, PMBUSCMDListModel::Col_Toggle);
		this->m_cmdListModel->RowValueChanged(idx, PMBUSCMDListModel::Col_Toggle);
	}
}

void MainFrame::OnIncreaseCPUOverhead(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnIncreaseCPUOverhead");
	
	if (this->m_appSettings.m_increaseCPUOverhead == Generic_Disable){
		this->m_appSettings.m_increaseCPUOverhead = Generic_Enable;
		this->m_IncreaseCPUOverheadMenuItem->Check(true);

		this->StartInCreaseCPUOverHeadThread();

	}
	else if (this->m_appSettings.m_increaseCPUOverhead == Generic_Enable){
		this->m_appSettings.m_increaseCPUOverhead = Generic_Disable;
		this->m_IncreaseCPUOverheadMenuItem->Check(false);

		this->StopInCreaseCPUOverHeadThread();
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
	this->m_IOAccess[IOACCESS_SERIALPORT].m_DeviceSendDataExtra = SerialSendDataExtra;
	this->m_IOAccess[IOACCESS_SERIALPORT].m_DeviceReadDataExtra = SerialReadDataExtra;

	// HID
	this->m_IOAccess[IOACCESS_HID].m_EnumerateAvailableDevice = EnumerateAvailableHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_GetDeviceStatus = GetHIDDeviceStatus;
	this->m_IOAccess[IOACCESS_HID].m_GetOpenDeviceName = GetHIDOpenDeviceName;
	this->m_IOAccess[IOACCESS_HID].m_OpenDevice = OpenHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_CloseDevice = CloseHIDDevice;
	this->m_IOAccess[IOACCESS_HID].m_DeviceSendData = HIDSendData;
	this->m_IOAccess[IOACCESS_HID].m_DeviceReadData = HIDReadData;
	this->m_IOAccess[IOACCESS_HID].m_DeviceSendDataExtra = HIDSendDataExtra;
	this->m_IOAccess[IOACCESS_HID].m_DeviceReadDataExtra = HIDReadDataExtra;

	// Pickit
	this->m_IOAccess[IOACCESS_PICKIT].m_EnumerateAvailableDevice = EnumerateAvailablePickitDevice;
	this->m_IOAccess[IOACCESS_PICKIT].m_GetDeviceStatus = GetPickitDeviceStatus;
	this->m_IOAccess[IOACCESS_PICKIT].m_GetOpenDeviceName = GetPickitOpenDeviceName;
	this->m_IOAccess[IOACCESS_PICKIT].m_OpenDevice = OpenPickitDevice;
	this->m_IOAccess[IOACCESS_PICKIT].m_CloseDevice = ClosePickitDevice;
	this->m_IOAccess[IOACCESS_PICKIT].m_DeviceSendData = PickitSendData;
	this->m_IOAccess[IOACCESS_PICKIT].m_DeviceReadData = PickitReadData;
	this->m_IOAccess[IOACCESS_PICKIT].m_DeviceSendDataExtra = PickitSendDataExtra;
	this->m_IOAccess[IOACCESS_PICKIT].m_DeviceReadDataExtra = PickitReadDataExtra;

	// TOTAL PHASE I2C Host Adaptor
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_EnumerateAvailableDevice = EnumerateAvailableTotalPhaseDevice;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_GetDeviceStatus = GetTotalPhaseDeviceStatus;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_GetOpenDeviceName = GetTotalPhaseOpenDeviceName;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_OpenDevice = OpenTotalPhaseDevice;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_CloseDevice = CloseTotalPhaseDevice;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_DeviceSendData = TotalPhaseSendData;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_DeviceReadData = TotalPhaseReadData;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_DeviceSendDataExtra = TotalPhaseSendDataExtra;
	this->m_IOAccess[IOACCESS_TOTALPHASE].m_DeviceReadDataExtra = TotalPhaseReadDataExtra;

	// TRC2 I2C Adapter
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_EnumerateAvailableDevice = EnumerateAvailableTRC2I2CAdapterDevice;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_GetDeviceStatus = GetTRC2I2CAdapterDeviceStatus;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_GetOpenDeviceName = GetTRC2I2CAdapterOpenDeviceName;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_OpenDevice = OpenTRC2I2CAdapterDevice;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_CloseDevice = CloseTRC2I2CAdapterDevice;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_DeviceSendData = TRC2I2CAdapterSendData;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_DeviceReadData = TRC2I2CAdapterReadData;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_DeviceSendDataExtra = TRC2I2CAdapterSendDataExtra;
	this->m_IOAccess[IOACCESS_TRC2_I2C_ADAPTER].m_DeviceReadDataExtra = TRC2I2CAdapterReadDataExtra;

	// Current Use IO
	switch (this->m_appSettings.m_I2CAdaptorModuleBoard){

	case I2C_AdaptorModuleBoard_PICKIT_SERIAL:

		this->m_CurrentUseIOInterface = IOACCESS_PICKIT;

		break;

	case I2C_AdaptorModuleBoard_R90000_95611:

		this->m_CurrentUseIOInterface = IOACCESS_SERIALPORT;
		
		break;

	case I2C_AdaptorModuleBoard_R90000_9271_USB:
		
		this->m_CurrentUseIOInterface = IOACCESS_HID;

		break;

	case I2C_AdaptorModuleBoard_TOTALPHASE:

		this->m_CurrentUseIOInterface = IOACCESS_TOTALPHASE;

		break;

	case I2C_AdaptorModuleBoard_TRC2I2CAdapter:

		this->m_CurrentUseIOInterface = IOACCESS_TRC2_I2C_ADAPTER;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "I2C Adaptor Module Board Setting Error");
		break;
	}
}

void MainFrame::UpdateStatusBarIOSettingFiled(wxString io_string){
	this->m_status_bar->SetStatusText(io_string, PMBUSStatusBar::Field_IO_Setting);
}

void MainFrame::UpdateStatusBarIOSettingFiled(unsigned long i2cBitRateSpeed){
	wxString i2cBitRateString = wxString::Format("%ld", i2cBitRateSpeed);
	i2cBitRateString += wxT("kHz");

	this->m_status_bar->SetStatusText(i2cBitRateString, PMBUSStatusBar::Field_I2C_Clock);
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
	
	wxThreadEvent *threadQueryStart_evt;
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

				if (this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT) {

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
				else if (this->m_CurrentUseIOInterface == IOACCESS_HID){

					wxString usbDeviceName(wxT("R90000-9271(USB)"));

					this->UpdateStatusBarIOSettingFiled(usbDeviceName);


					new(TP_ClearIOReadBufferTask) ClearIOReadBufferTask(this->m_IOAccess, &this->m_CurrentUseIOInterface, false);


					new (TP_SendUSBAdaptorBitRateTask) SendUSBAdaptorBitRateTask(
						this->m_IOAccess,
						&this->m_CurrentUseIOInterface,
						this->m_appSettings.m_usbAdaptorI2CSetting.m_bitRateSpeed,
						this->m_appSettings.m_usbAdaptorSPISetting.m_bitRateSpeed,
						this->m_appSettings.m_usbAdaptorCANSetting.m_bitRateSpeed,
						this->m_appSettings.m_usbAdaptorI2CSetting.m_busTimeout
						);

					// Update I2C Bit Rate Speed Field
					this->UpdateStatusBarIOSettingFiled(this->m_appSettings.m_usbAdaptorI2CSetting.m_bitRateSpeed);

				}
				else if (this->m_CurrentUseIOInterface == IOACCESS_TOTALPHASE){
					
					wxString totalPhaseDeviceName(wxT("TOTAL PHASE"));

					this->UpdateStatusBarIOSettingFiled(totalPhaseDeviceName);

					// Update I2C Clock Speed Field
					this->UpdateStatusBarIOSettingFiled(this->m_appSettings.m_totalPhase_I2C_Bitrate);
				}
				else if (this->m_CurrentUseIOInterface == IOACCESS_PICKIT){
					
					wxString pickitSerialDeviceName(wxT("PICKIT Serial"));

					this->UpdateStatusBarIOSettingFiled(pickitSerialDeviceName);

					// Update I2C Clock Speed Field
					this->UpdateStatusBarIOSettingFiled(100);

					// Create Pickit Config Task
					new(TP_PickitConfigTask) PickitConfigTask(this->m_IOAccess, &this->m_CurrentUseIOInterface);

					while (TaskEx::GetCount(task_ID_PickitConfigTask) != 0){
						wxMilliSleep(10);
					};

				}else if(this->m_CurrentUseIOInterface == IOACCESS_TRC2_I2C_ADAPTER){

					wxString trc2I2CAdapterDeviceName(wxT("TRC2 I2C Adapter"));

					this->UpdateStatusBarIOSettingFiled(trc2I2CAdapterDeviceName);

					// Create TRC2AdapterGetFWVersion Task
					new(TP_TRC2AdapterGetFWVersionTask) TRC2AdapterGetFWVersionTask(this->m_IOAccess, &this->m_CurrentUseIOInterface, this->m_eventHandler);

					// Update I2C Clock Speed Field
					this->UpdateStatusBarIOSettingFiled(PMBUSHelper::GetAppSettings()->m_trc2Adapter_I2C_Bitrate);

				}
		
				//
				while (TaskEx::GetCount(task_ID_SendUSBAdaptorBitRateTask) != 0){

					wxMilliSleep(200);
				}

				/*** Send Query Start Event To Handler Function ***/
				if (this->m_appSettings.m_autoQueryCMDOnIOOpen == Generic_Enable){
					threadQueryStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_QUERY_SEQUENCE_START);
					threadQueryStart_evt->SetString(wxT("Query All Commands"));
					wxQueueEvent(this->GetEventHandler(), threadQueryStart_evt);
				}

			}
		}//if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_CLOSE)

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
				PSU_DEBUG_PRINT(MSG_ERROR, "Close IO Device Failed !");
			}
			else{
				//this->m_ioDeviceOpen = false;
				this->UpdateStatusBarIOSettingFiled(wxString("Disconnect"));
			}
		}

	//}

	return ret;
}

#if 0
int MainFrame::findPMBUSCMDIndex(unsigned int cmd_register){

	int index = -1;

	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		if (this->m_PMBusData[idx].m_register == cmd_register){
			PSU_DEBUG_PRINT(MSG_DEBUG, "this->m_PMBusData[idx].m_register=%d, cmd_register = %d", this->m_PMBusData[idx].m_register, cmd_register);
			index = idx;
			break;
		}
	}

	return index;
}
#endif

unsigned int MainFrame::findPMBUSCMDIndex(unsigned int cmd_register, unsigned char need_changePage){

	unsigned int index = 0;

	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		if (this->m_PMBusData[idx].m_register == cmd_register)
		{
			if (this->m_PMBusData[idx].m_cmdStatus.m_NeedChangePage == need_changePage){
				index = idx;
				break;
			}
		}
	}

	return index;
}

void MainFrame::TaskInit(void){
	// Task Init 
}


void MainFrame::OnMonitorStart(wxThreadEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG,  "Polling Time = %d", this->m_polling_time);
	PSU_DEBUG_PRINT(MSG_DETAIL, "m_monitor_running = %d", this->m_monitor_running);
	PSU_DEBUG_PRINT(MSG_DEBUG,  "m_ispSequenceThread = %p", this->m_ispSequenceThread);

	int loop = 0;

	//PSU_DEBUG_PRINT("Available = %d", this->m_list_model.get()->getAvailable()[0]);

	/*** If User Cancel ISP Sequence Previous ***/
	if (TaskEx::GetCount(task_ID_UserCancelISPPostDelayTask) > 0){
		wxString content = wxString::Format("Need To Wait %d Seconds ! \n"
			"Due to Previous ISP Sequence Has been Canceled !", UserCancelISP_POST_DELAY_TIME / 1000);

		wxMessageBox(content,
			wxT("Please Wait !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}


	// If IO Device not Open, Open IO Device Here
	this->OpenIODevice();

	// Start Send Data Thread
	if (this->m_monitor_running == false){
		this->StartMonitor();
	}
	else{ // One Send Command Thread is Running
		this->StopMonitor();
	}

}

void MainFrame::OnSendThreadStart(wxThreadEvent& event){
	// Thread Start
	this->m_status_bar->getGauge()->Pulse();
}

void MainFrame::OnSendThreadCompletion(wxThreadEvent& event)
{
	PSU_DEBUG_PRINT(MSG_DEBUG, "Send Thread Completion");
	
	int HasSendFail = event.GetInt();

	// Close I/O Device
	if (HasSendFail == TRUE){
		this->CloseIODevice();
	}
	
	this->m_sendThreadStopFlag = true;

	// Reset Monitor Parameters
	this->m_monitor_running = false;

	this->m_toolbar->FindById(MENU_ID_Monitor)->SetNormalBitmap(*this->m_monitorBitmap);
	this->m_monitorMenuItem->SetBitmap(*m_monitor16Bitmap);
	this->m_toolbar->Realize();

	this->m_readTestMenuItem->Enable(true);
	this->m_writeTestMenuItem->Enable(true);
	this->m_blockWRTestMenuItem->Enable(true);
	this->m_fruMakerMenuItem->Enable(true);
	this->m_fruWriterMenuItem->Enable(true);

	// (Work-Around) Set Gauge To Determinate Mode, Seems If the value of gauge is the same as previous the 'SetValue' method don't work
	this->m_status_bar->getGauge()->SetValue(1);
	this->m_status_bar->getGauge()->SetValue(0);
	//

	(this->m_status_bar->getTimer())->Stop();
}

void MainFrame::OnSendThreadUpdate(wxThreadEvent& event)
{
	//PSU_DEBUG_PRINT(MSG_ALERT, "MYFRAME: MyThread update! Int = %d", event.GetInt());
	//this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_RegisterIconText);
	
	PSU_DEBUG_PRINT(MSG_DETAIL, "%s : GetInt = %d", __FUNCTIONW__, event.GetInt());

	int enabledCMDCount = 0;

	if (this->m_monitor_running == true){
		//
		for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){

			if (PMBUSHelper::isOwnReadAccess(this->m_PMBusData[idx].m_access) == true){

				if (this->m_PMBusData[idx].m_toggle == true){
					enabledCMDCount++;

					if (enabledCMDCount > 0){
						PSU_DEBUG_PRINT(MSG_DETAIL, "CMD %02xH is Enable", this->m_PMBusData[idx].m_register);
						break;
					}
				}

			}
		}

		if (enabledCMDCount == 0){
			PSU_DEBUG_PRINT(MSG_ALERT, "No CMD(Read Access) Enabled !");
			this->StopMonitor();
		}
	}

#ifndef _WIN32
	// For Update Icon Color To Yellow
	this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_RegisterIconText);
#endif

}

void MainFrame::OnSendThreadUpdateRaw(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DETAIL, "SendThreadUpdateRaw Thread Event! Int = %d, string = %s", event.GetInt(), event.GetString().c_str());
	wxVariant variantRaw;
	variantRaw = event.GetString();

	this->m_cmdListModel.get()->SetValueByRow(variantRaw, event.GetInt(), PMBUSCMDListModel::Col_RawText);
	this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_RawText);

#ifndef _WIN32
	this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_RegisterIconText);
#endif

	this->m_status_bar->getGauge()->Pulse();

}

void MainFrame::OnSendThreadUpdateQuery(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "Update Query Event! Int = %d, string = %s", event.GetInt(), event.GetString().c_str());
	wxVariant variantRaw;
	variantRaw = event.GetString();

	this->m_cmdListModel.get()->SetValueByRow(variantRaw, event.GetInt(), PMBUSCMDListModel::Col_QueryText);
	this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_QueryText);
}

void MainFrame::OnSendThreadUpdateCoefficients(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "Update Coefficients Event! Int = %d, string = %s", event.GetInt(), event.GetString().c_str());
	wxVariant variantRaw;
	variantRaw = event.GetString();

	this->m_cmdListModel.get()->SetValueByRow(variantRaw, event.GetInt(), PMBUSCMDListModel::Col_CoefficientsText);
	this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_CoefficientsText);
}

void MainFrame::OnSendThreadUpdateCook(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DETAIL, "SendThreadUpdateCook Thread Event! Int = %d, string = %s", event.GetInt(), event.GetString().c_str());

	wxVariant variantCook;
	variantCook = event.GetString();

	this->m_cmdListModel.get()->SetValueByRow(variantCook, event.GetInt(), PMBUSCMDListModel::Col_CookText);
	this->m_cmdListModel.get()->RowValueChanged(event.GetInt(), PMBUSCMDListModel::Col_CookText);

}

void MainFrame::OnSendThreadUpdateCMDName(wxThreadEvent& event){

	wxString CMDName = event.GetString();

	this->m_status_bar->setMonitoringCMDName(CMDName);
}

void MainFrame::OnSendThreadUpdateSummary(wxThreadEvent& event){

	wxString summary = event.GetString();

	this->m_status_bar->setMonitoringSummary(summary); 

}

void MainFrame::OnSendThreadUpdateSTDPage(wxThreadEvent& event){
	int indexOfCmd = event.GetInt();
	this->UpdateSTDPage(indexOfCmd);
}

void MainFrame::OnSendThreadUpdateSTATUSPage(wxThreadEvent& event){
	int indexOfCmd = event.GetInt();
	this->UpdateSTATUSPanel(indexOfCmd);
}

void MainFrame::OnISPSequenceStart(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnISPSequenceStart");

	PSU_DEBUG_PRINT(MSG_DEBUG, "Target = %d", event.GetInt());
	PSU_DEBUG_PRINT(MSG_DEBUG, "Title  = %s", event.GetString().c_str());

	tihex<> *hexFileParser = NULL;

	int target = event.GetInt();
	wxString dialogTitle = event.GetString();

#if 0
	/*** Create Progress Dialog ***/
	m_progressDialog = new wxProgressDialog(dialogTitle,
		// "Reserve" enough space for the multiline
		// messages below, we'll change it anyhow
		// immediately in the loop below
		wxString(' ', 100) + "\n\n\n\n",
		100,    // range
		this->m_notebook,  // parent
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
	/*** Create Progress Dialog ***/
	wxProgressDialog progressDialog(dialogTitle,
		// "Reserve" enough space for the multiline
		// messages below, we'll change it anyhow
		// immediately in the loop below
		wxString(' ', 100) + "\n\n\n\n",
		100,    // range
		this->m_notebook,  // parent
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

	// Check If Monitor is running
	if(this->m_monitor_running == true){
		
#if 0
		wxMessageBox(wxT("Program will stop monitor automatically !"),
			wxT("Monitor will stop"),  // caption
			wxOK | wxICON_INFORMATION);
#endif
		PSU_DEBUG_PRINT(MSG_ALERT, "Stop Monitor Automatically Before Do ISP");
		this->StopMonitor();
		wxMilliSleep(500);
	}

	m_pmbusProgressDialog = new PMBUSFWProgressDialog(this, dialogTitle, 100, &this->m_ispStatus, this->m_increaseCPUOverHeadThread, this->m_IOAccess, &this->m_CurrentUseIOInterface);

	switch (target){
	
	case UPDATE_PRIMARY_FW_TARGET:
		hexFileParser = &this->m_PrimaryTIHexFileStat;
		break;

	case UPDATE_SECONDARY_FW_TARGET:
		hexFileParser = &this->m_SecondaryTIHexFileStat;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Target Code Error !");
		break;
	}


	/*** Setup FW Upload Mode & FW Upload & FW Upload Status CMD ***/
	switch (this->m_appSettings.m_currentUseCustomer){

	// Use Gigabyte's FW Upload Command Set
	case Customer_GIGABYTE:
		
		// Gigabyte FW Upload Mode Command
		PMBUSHelper::getFWUploadModeCMD() = GIGABYTE_FW_UPLOAD_MODE_CMD;
		// Gigabyte FW Upload Command
		PMBUSHelper::getFWUploadCMD() = GIGABYTE_FW_UPLOAD_CMD;
		// Gigabyte FW Upload Status Command
		PMBUSHelper::getFWUploadStatusCMD() = GIGABYTE_FW_UPLOAD_STATUS_CMD;

		break;

	// Default Use Acbel Defined F0 F1 F3
	default:
		
		// Default FW Upload Mode Command
		PMBUSHelper::getFWUploadModeCMD() = DEFAULT_FW_UPLOAD_MODE_CMD;
		// Default FW Upload Command
		PMBUSHelper::getFWUploadCMD() = DEFAULT_FW_UPLOAD_CMD;
		// Default FW Upload Status Command
		PMBUSHelper::getFWUploadStatusCMD() = DEFAULT_FW_UPLOAD_STATUS_CMD;

		break;
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "FW Upload Mode Command : %02xH", PMBUSHelper::getFWUploadModeCMD());
	PSU_DEBUG_PRINT(MSG_ALERT, "FW Upload Command : %02xH", PMBUSHelper::getFWUploadCMD());
	PSU_DEBUG_PRINT(MSG_ALERT, "FW Upload Status Command : %02xH", PMBUSHelper::getFWUploadStatusCMD());

	/*** Start ISP Sequence Thread ***/
	m_ispSequenceThread = new ISPSequenceThread(wxString(wxT("FilePath")), hexFileParser, this->m_IOAccess, &this->m_CurrentUseIOInterface, target, this->m_appSettings.m_developerMode, this->GetEventHandler(), m_pmbusProgressDialog->GetEventHandler(), &this->m_ispStatus, NULL);
	// If Create Thread Success
	if (this->m_ispSequenceThread->Create() != wxTHREAD_NO_ERROR){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Create ISP Sequence Thread");
	}
	else{
		this->m_ispSequenceThread->Run();
		//m_ispSequenceThread->SetPriority(wxPRIORITY_MAX);

        #if (INCREASE_CPU_OVERHEAD == TRUE)
		if (this->m_CurrentUseIOInterface == IOACCESS_HID){
			if (this->m_appSettings.m_increaseCPUOverhead == Generic_Disable){
				this->StartInCreaseCPUOverHeadThread();
			}
		}
		#endif
	}

	m_pmbusProgressDialog->Centre();
	int retCode = m_pmbusProgressDialog->ShowModal();
	if (retCode == wxID_CANCEL){
		PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel ISP Sequence");
		this->m_ispStatus = ISP_Status_UserRequestCancel;
	}

	// Wait ISP Sequence Thread End
	m_ispSequenceThread->Wait();

	wxDELETE(m_ispSequenceThread);

	m_pmbusProgressDialog->Destroy();
	wxDELETE(m_pmbusProgressDialog);

	#if (INCREASE_CPU_OVERHEAD == TRUE)
	if (this->m_CurrentUseIOInterface == IOACCESS_HID){
		if (this->m_appSettings.m_increaseCPUOverhead == Generic_Disable){
			this->StopInCreaseCPUOverHeadThread();
		}
	}
	#endif
}

/*
void MainFrame::OnISPSequenceInterrupt(wxThreadEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnISPSequenceInterrupt");

	int ispStatus = event.GetInt();

	// If Error Occurs
	if ((ispStatus & 0xff) > 0x02) {

		PSU_DEBUG_PRINT(MSG_DEBUG, "ispStatus = 0x%xH", ispStatus);

		switch (ispStatus){

		case ISP_Status_VerifyBeforeStart:
			// Verify Before Start

			break;

		case ISP_Status_UserRequestCancel:
			// User Cancel ISP
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel ISP Sequence !");

			new(TP_ClearIOReadBufferTask) ClearIOReadBufferTask(this->m_IOAccess, &this->m_CurrentUseIOInterface, false);
			new(TP_UserCancelISPPostDelayTask) UserCancelISPPostDelayTask();

			break;

		case ISP_Status_SendDataFailed:
			wxMessageBox(wxT("Send Data Failed ! \n\n IO Port Send Data Failed"),
				wxT("Error !"),  // caption
				wxOK | wxICON_ERROR);

			break;

		case ISP_Status_ResponseDataError:
			wxMessageBox(wxT("Response Data Error ! \n\n This may caused by Unstable IO or Incorrect Image"),
				wxT("Error !"),  // caption
				wxOK | wxICON_ERROR);

			break;


		case ISP_Status_RebootCheckError:
			wxMessageBox(wxT("DSP Reboot Check Error ! \n\n DSP Reboot Failed"),
				wxT("Error !"),  // caption
				wxOK | wxICON_ERROR);

			break;

		default:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Something Error Occurs, ispStatus = %02x", ispStatus);
			break;

		}
	}

}
*/

void MainFrame::OnQUERYSequenceStart(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnQUERYSequenceStart");

	PSU_DEBUG_PRINT(MSG_DEBUG, "Title  = %s", event.GetString().c_str());

	// Check If Monitor is running
	if (this->m_monitor_running == true){
		wxMessageBox(wxT("Please Stop Monitor Then Try Again !"),
			wxT("Monitor is Running !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	// Select Row 1
	this->m_cmdListDVC->Select(this->m_cmdListModel->GetItem(0));

	// Call Dialog
	m_pmbusQUERYProgressDialog = new PMBUSQUERYProgressDialog(this, event.GetString(), this->m_IOAccess, &this->m_CurrentUseIOInterface);

	// Start QUERY Sequence Thread
	m_querySequenceThread = new QUERYSequenceThread(this->m_IOAccess, &this->m_CurrentUseIOInterface, this->GetEventHandler(), m_pmbusQUERYProgressDialog->GetEventHandler(), NULL);
	// If Create Thread Success
	if (m_querySequenceThread->Create() != wxTHREAD_NO_ERROR){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Create QUERY Sequence Thread");
	}
	else{
		m_querySequenceThread->Run();
	}

	m_pmbusQUERYProgressDialog->Centre();
	int retCode = m_pmbusQUERYProgressDialog->ShowModal();

	if (retCode == wxID_CANCEL){
		PSU_DEBUG_PRINT(MSG_DEBUG, "m_pmbusQUERYProgressDialog return wxID_CANCEL");
	}

	// Wait ISP Sequence Thread End
	m_querySequenceThread->Wait();

	wxDELETE(m_querySequenceThread);

	m_pmbusQUERYProgressDialog->Destroy();
	wxDELETE(m_pmbusQUERYProgressDialog);
}

void MainFrame::OnFindI2CSlaveStart(wxThreadEvent& event) {
	
	memset(this->m_available_i2c_slave_devices, 0, sizeof(m_available_i2c_slave_devices) / sizeof(m_available_i2c_slave_devices[0]));
	new(TP_FindAvailableSlaveI2CDeviceTask) FindAvailableSlaveI2CDeviceTask(this->m_IOAccess, &this->m_CurrentUseIOInterface, this->m_eventHandler, this->m_available_i2c_slave_devices, NULL);


	wxBusyInfo *info = NULL;

	while (TaskEx::GetCount(task_ID_FindAvailableSlaveI2CDeviceTask) != 0) {

#if wxCHECK_VERSION(3, 1, 0)
		if (info == NULL) info = new wxBusyInfo(
			wxBusyInfoFlags()
			.Parent(this)
			.Icon(wxArtProvider::GetIcon(wxART_FIND,
				wxART_OTHER, wxSize(64, 64)))
			.Title("<b>Finding I2C Slave Devices</b>")
			.Text("Please  wait  ...")
			.Foreground(*wxBLACK)
			.Background(*wxYELLOW)
			.Transparency(wxALPHA_OPAQUE)// 4 * wxALPHA_OPAQUE / 5)
		);
#endif

		wxMilliSleep(100);

	};

	wxDELETE(info);

	bool found = false;
	wxString no_found_msg(wxT("No I2C Slave Device Found"));
	wxString found_msg(wxT("I2C Slave Device Found : "));

	for (int idx = 0; idx<128; idx++) {
		if (this->m_available_i2c_slave_devices[idx] == 1) {
			if (found == false) {
				found = true;
			}

			found_msg += wxString::Format("[%02X] ", (idx * 2));

		}
	}


	if (found == true) {
		wxMessageBox(found_msg,
			wxT("I2C Slave Device Found !"),  // caption
			wxOK | wxICON_INFORMATION);

	}
	else {
		wxMessageBox(no_found_msg,
			wxT("No I2C Slave Device Found !"),  // caption
			wxOK | wxICON_WARNING);
	}

}

void MainFrame::OnIOThreadReqPause(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "OnIOThreadReqPause");

	if (this->m_monitor_running == true){
		if (this->m_IOPortSendCMDThread != NULL){
			this->m_IOPortSendCMDThread->m_pause = true;

			this->m_monitor_pause = true;
		}
	}

}

void MainFrame::OnIOThreadReqResume(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "OnIOThreadReqResume");

	if (this->m_monitor_running == true){
		if (this->m_IOPortSendCMDThread != NULL){
			this->m_IOPortSendCMDThread->m_pause = false;

			this->m_monitor_pause = false;
		}
	}

}

int MainFrame::SaveCMDListToFile(wxTextOutputStream& textOutputStream){
	wxVariant Value;
	wxString registerValue("");
	wxString line("");
	wxDataViewItem dataViewItem;

	char* format[7] = {
		"%-12s", // Register
		"%-30s", // Name
		"%-12s",  // Access
		"%-40s", // Query
		"%-20s", // Coefficients
		"%-140s",// Cook
		"%s"     // Raw
	};

	wxString header = wxString::Format("%-12s%-30s%-12s%-40s%-20s%-140s%s", "Register", "Name", "Access", "Query", "Coefficients", "Cook", "Raw");

	textOutputStream << header;
	textOutputStream << endl;

	for (unsigned int row_idx = 0; row_idx < PMBUSHelper::GetCurrentCMDTableSize(); row_idx++){

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

void MainFrame::CheckAndLoadConfig(CUSTOMER_TYPE_t* customerList){
	
	wxConfigBase::Set(new wxFileConfig(wxT(""), wxT(""), wxT("psu.ini"), wxT(""), wxCONFIG_USE_RELATIVE_PATH));

	wxConfigBase *pConfig = wxConfigBase::Get();

	pConfig->SetPath(wxT("/APP"));
	// Customer
	long customer;
	if (pConfig->Read(wxT("Customer"), &customer) == false){
		pConfig->Write(wxT("Customer"), DEFAULT_CUSTOMER);
		this->m_appSettings.m_currentUseCustomer = DEFAULT_CUSTOMER;
	}
	else{
		this->m_appSettings.m_currentUseCustomer = customer;
	}

	// Previous Customer
	long previousCustomer;
	if (pConfig->Read(wxT("PreviousCustomer"), &previousCustomer) == false){
		pConfig->Write(wxT("PreviousCustomer"), 0x99);// DEFAULT_CUSTOMER);
		this->m_appSettings.m_previousUseCustomer = 0x99;// DEFAULT_CUSTOMER;
	}
	else{
		this->m_appSettings.m_previousUseCustomer = previousCustomer;
	}

	// Model
	long model;
	if (pConfig->Read(wxT("Model"), &model) == false){
		pConfig->Write(wxT("Model"), DEFAULT_MODEL);
		this->m_appSettings.m_currentUseModel= DEFAULT_MODEL;
	}
	else{
		this->m_appSettings.m_currentUseModel = model;
	}

	// Precious Model
	long previousModel;
	if (pConfig->Read(wxT("PreviousModel"), &previousModel) == false){
		pConfig->Write(wxT("PreviousModel"), 0x99);// DEFAULT_MODEL);
		this->m_appSettings.m_previousUseModel = 0x99;// DEFAULT_MODEL;
	}
	else{
		this->m_appSettings.m_previousUseModel = previousModel;
	}

	// Set AppSettings
	PMBUSHelper::SetAppSettings(&this->m_appSettings);

	// Set Customer & Model List
	this->m_customerList = customerList;
	this->m_modelList = this->m_customerList[this->m_appSettings.m_currentUseCustomer].m_modelTypeList;//modelList;
	// Save Current Use Model's Structure Pointer
	PMBUSHelper::SetCurrentUseModel(
		&this->m_customerList[this->m_appSettings.m_currentUseCustomer].m_modelTypeList[PMBUSHelper::GetAppSettings()->m_currentUseModel]);


	/* Check If Model Change */
	this->CheckIfModelChange();
	
	// I2C Adaptor Module Board
	long i2cAdaptorModuleBoard;
	if (pConfig->Read(wxT("I2CAdaptorModuleBoard"), &i2cAdaptorModuleBoard) == false){
		pConfig->Write(wxT("I2CAdaptorModuleBoard"), DEFAULT_I2C_ADAPTOR_MODULE);
		this->m_appSettings.m_I2CAdaptorModuleBoard = DEFAULT_I2C_ADAPTOR_MODULE;
	}
	else{
		this->m_appSettings.m_I2CAdaptorModuleBoard = i2cAdaptorModuleBoard;
	}

	// I2C Slave Address
	long i2cSlaveAddr;
	if (pConfig->Read(wxT("I2CSlaveAddress"), &i2cSlaveAddr) == false){	
		pConfig->Write(wxT("I2CSlaveAddress"), this->m_defaultI2CAddress);
		this->m_appSettings.m_I2CSlaveAddress = this->m_defaultI2CAddress;
	}
	else{
		if (this->m_modelChangedFlag == true) {
			if (i2cSlaveAddr != PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_default_i2c_address) {
				
				int confirm = 0;
				wxString msg = wxString::Format("Model Changed ! \n\n Would You Reset I2C Adrress To %X ?", PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_default_i2c_address);

				wxMessageDialog* confirmDialog = new wxMessageDialog(this, msg, wxT("Model Changed"), wxYES_NO | wxICON_INFORMATION);
				confirmDialog->Centre();
				confirm = confirmDialog->ShowModal();

				delete confirmDialog;

				if (confirm == wxID_NO) {
					this->m_appSettings.m_I2CSlaveAddress = i2cSlaveAddr;
					PSU_DEBUG_PRINT(MSG_DEBUG, "User Don't Reset I2C Address, Current I2C Address is %X", this->m_appSettings.m_I2CSlaveAddress);
				}
				else {
					this->m_appSettings.m_I2CSlaveAddress = PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_default_i2c_address;
					PSU_DEBUG_PRINT(MSG_DEBUG, "User Reset I2C Address, Current I2C Address is %X", this->m_appSettings.m_I2CSlaveAddress);
				}
				
			}
			else {
				this->m_appSettings.m_I2CSlaveAddress = i2cSlaveAddr;
			}
		}
		else {
			this->m_appSettings.m_I2CSlaveAddress = i2cSlaveAddr;
		}
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

	// Polling Interval
	long pollingInterval;
	if (pConfig->Read(wxT("PollingInterval"), &pollingInterval) == false){
		pConfig->Write(wxT("PollingInterval"), this->m_defaultPollingTime);
		this->m_appSettings.m_pollingInterval = this->m_defaultPollingTime;
	}
	else{
		if (this->m_modelChangedFlag == true) {
			if (pollingInterval != PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_default_cmd_polling_time) {

				int confirm = 0;
				wxString msg = wxString::Format("Model Changed ! \n\n Would You Reset CMD Polling Time To %d MS ?", PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_default_cmd_polling_time);

				wxMessageDialog* confirmDialog = new wxMessageDialog(this, msg, wxT("Model Changed"), wxYES_NO | wxICON_INFORMATION);
				confirmDialog->Centre();
				confirm = confirmDialog->ShowModal();

				delete confirmDialog;

				if (confirm == wxID_NO) {
					this->m_appSettings.m_pollingInterval = pollingInterval;
					PSU_DEBUG_PRINT(MSG_DEBUG, "User Don't Reset CMD Polling Time, Current CMD Polling Time is %d MS", this->m_appSettings.m_pollingInterval);
				}
				else {
					this->m_appSettings.m_pollingInterval = PMBUSHelper::GetCurrentUseModel()->m_modelOption.m_default_cmd_polling_time;
					PSU_DEBUG_PRINT(MSG_DEBUG, "User Reset CMD Polling Times, Current I2C Address is %d", this->m_appSettings.m_pollingInterval);
				}

			}
			else {
				this->m_appSettings.m_pollingInterval = pollingInterval;
			}
		}
		else {
			this->m_appSettings.m_pollingInterval = pollingInterval;
		}
		
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

	// Enable Checksum
	long enableChecksum;
	if (pConfig->Read(wxT("EnableChecksum"), &enableChecksum) == false){
		pConfig->Write(wxT("EnableChecksum"), DEFAULT_ENABLE_CHECKSUM);
		this->m_appSettings.m_EnableChecksum = DEFAULT_ENABLE_CHECKSUM;
	}
	else{
		this->m_appSettings.m_EnableChecksum = enableChecksum;
	}

	// Only Polling Support CMD
	long onlyPollingSupportCMD;
	if (pConfig->Read(wxT("OnlyPollingSupportCMD"), &onlyPollingSupportCMD) == false){
		pConfig->Write(wxT("OnlyPollingSupportCMD"), DEFAULT_ONLY_POLLING_SUPPORT_CMD);
		this->m_appSettings.m_onlyPollingSupportCMD = DEFAULT_ONLY_POLLING_SUPPORT_CMD;
	}
	else{
		this->m_appSettings.m_onlyPollingSupportCMD = onlyPollingSupportCMD;
	}

	// Clear Log Before Monitor Run
	long clearLogBeforeMonitorRun;
	if (pConfig->Read(wxT("ClearLogBeforeMonitorRun"), &clearLogBeforeMonitorRun) == false){
		pConfig->Write(wxT("ClearLogBeforeMonitorRun"), DEFAULT_CLEAR_LOG_BEFORE_MONITOR_RUN);
		this->m_appSettings.m_clearLogBeforeMonitorRun = DEFAULT_CLEAR_LOG_BEFORE_MONITOR_RUN;
	}
	else{
		this->m_appSettings.m_clearLogBeforeMonitorRun = clearLogBeforeMonitorRun;
	}

	// Auto Query CMD on I/O Open
	long autoQueryCMDOnIOOpen;
	if (pConfig->Read(wxT("AutoQueryCMDOnIOOpen"), &autoQueryCMDOnIOOpen) == false){
		pConfig->Write(wxT("AutoQueryCMDOnIOOpen"), DEFAULT_AUTO_QUERY_CMD_ON_IO_OPEN);
		this->m_appSettings.m_autoQueryCMDOnIOOpen = DEFAULT_AUTO_QUERY_CMD_ON_IO_OPEN;
	}
	else{
		this->m_appSettings.m_autoQueryCMDOnIOOpen = autoQueryCMDOnIOOpen;
	}

	// Query CMD Before Polling
	long queryCMDBeforePolling;
	if (pConfig->Read(wxT("QueryCMDBeforePolling"), &queryCMDBeforePolling) == false){
		pConfig->Write(wxT("QueryCMDBeforePolling"), DEFAULT_QUERY_CMD_BEFORE_POLLING);
		this->m_appSettings.m_queryCMDBeforePolling = DEFAULT_QUERY_CMD_BEFORE_POLLING;
	}
	else{
		this->m_appSettings.m_queryCMDBeforePolling = queryCMDBeforePolling;
	}

	// Increase CPU Overhead
	long increaseCPUOverhead;
	if (pConfig->Read(wxT("IncreaseCPUOverhead"), &increaseCPUOverhead) == false){
		pConfig->Write(wxT("IncreaseCPUOverhead"), DEFAULT_INCREASE_CPU_OVERHEAD);
		this->m_appSettings.m_increaseCPUOverhead = DEFAULT_INCREASE_CPU_OVERHEAD;
	}
	else{
		this->m_appSettings.m_increaseCPUOverhead = increaseCPUOverhead;
	}

	// ACS Set Point Minimum
	long acsSetPointMin;
	if (pConfig->Read(wxT("AcsSetPointMin"), &acsSetPointMin) == false){
		pConfig->Write(wxT("AcsSetPointMin"), DEFAULT_ACS_SETPOINT_INPUT_MIN);
		this->m_appSettings.m_acsSetPointMin = DEFAULT_ACS_SETPOINT_INPUT_MIN;
	}
	else{
		this->m_appSettings.m_acsSetPointMin = acsSetPointMin;
	}

	// ACS Set Point Maxmum
	long acsSetPointMax;
	if (pConfig->Read(wxT("AcsSetPointMax"), &acsSetPointMax) == false){
		pConfig->Write(wxT("AcsSetPointMax"), DEFAULT_ACS_SETPOINT_INPUT_MAX);
		this->m_appSettings.m_acsSetPointMax = DEFAULT_ACS_SETPOINT_INPUT_MAX;
	}
	else{
		this->m_appSettings.m_acsSetPointMax = acsSetPointMax;
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


	pConfig->SetPath(wxT("/USBAdaptor"));

#ifndef RELOAD_USB_ADAPTOR_SETTINGS_APP_RESTART

	// I2C Bit Rate Speed
	long i2cBitRateSpeed;
	if (pConfig->Read(wxT("I2CBitRateSpeed"), &i2cBitRateSpeed) == false){
		pConfig->Write(wxT("I2CBitRateSpeed"), DEFAULT_USB_ADAPTOR_I2C_BIT_RATE_SPEED);
		this->m_appSettings.m_usbAdaptorI2CSetting.m_bitRateSpeed = DEFAULT_USB_ADAPTOR_I2C_BIT_RATE_SPEED;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_bitRateSpeed = DEFAULT_USB_ADAPTOR_I2C_BIT_RATE_SPEED;
	}
	else{
		this->m_appSettings.m_usbAdaptorI2CSetting.m_bitRateSpeed = i2cBitRateSpeed;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_bitRateSpeed = i2cBitRateSpeed;
	}

	// I2C SMBUS
	long i2cSMBUS;
	if (pConfig->Read(wxT("I2CSMBUS"), &i2cSMBUS) == false){
		pConfig->Write(wxT("I2CSMBUS"), DEFAULT_USB_ADAPTOR_I2C_SMBUS);
		this->m_appSettings.m_usbAdaptorI2CSetting.m_smBus = DEFAULT_USB_ADAPTOR_I2C_SMBUS;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_smBus = DEFAULT_USB_ADAPTOR_I2C_SMBUS;
	}
	else{
		this->m_appSettings.m_usbAdaptorI2CSetting.m_smBus = i2cSMBUS;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_smBus = i2cSMBUS;
	}

	// I2C COMM
	long i2cCOMM;
	if (pConfig->Read(wxT("I2CCOMM"), &i2cCOMM) == false){
		pConfig->Write(wxT("I2CCOMM"), DEFAULT_USB_ADAPTOR_I2C_COMM);
		this->m_appSettings.m_usbAdaptorI2CSetting.m_comm = DEFAULT_USB_ADAPTOR_I2C_COMM;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_comm = DEFAULT_USB_ADAPTOR_I2C_COMM;
	}
	else{
		this->m_appSettings.m_usbAdaptorI2CSetting.m_comm = i2cCOMM;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_comm = i2cCOMM;
	}

	// I2C Bus Timeout
	long i2cBusTimeout;
	if (pConfig->Read(wxT("I2CBusTimeOut"), &i2cBusTimeout) == false){
		pConfig->Write(wxT("I2CBusTimeOut"), DEFAULT_USB_ADAPTOR_I2C_BUS_TIMEOUT);
		this->m_appSettings.m_usbAdaptorI2CSetting.m_busTimeout = DEFAULT_USB_ADAPTOR_I2C_BUS_TIMEOUT;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_busTimeout = DEFAULT_USB_ADAPTOR_I2C_BUS_TIMEOUT;
	}
	else{
		this->m_appSettings.m_usbAdaptorI2CSetting.m_busTimeout = i2cBusTimeout;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_busTimeout = i2cBusTimeout;
	}

	// I2C Receive Buffer Size
	long i2cReceiveBufferSize;
	if (pConfig->Read(wxT("I2CReceiveBufferSize"), &i2cReceiveBufferSize) == false){
		pConfig->Write(wxT("I2CReceiveBufferSize"), DEFAULT_USB_ADAPTOR_I2C_RECEIVE_BUFFER_SIZE);
		this->m_appSettings.m_usbAdaptorI2CSetting.m_receiveBufferSize = DEFAULT_USB_ADAPTOR_I2C_RECEIVE_BUFFER_SIZE;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_receiveBufferSize = DEFAULT_USB_ADAPTOR_I2C_RECEIVE_BUFFER_SIZE;
	}
	else{
		this->m_appSettings.m_usbAdaptorI2CSetting.m_receiveBufferSize = i2cReceiveBufferSize;
		this->m_appSettings.m_usbAdaptorI2CSetting.m_previous_receiveBufferSize = i2cReceiveBufferSize;
	}

	// SPI Bit Rate Speed
	long spiBitRateSpeed;
	if (pConfig->Read(wxT("SPIBitRateSpeed"), &spiBitRateSpeed) == false){
		pConfig->Write(wxT("SPIBitRateSpeed"), DEFAULT_USB_ADAPTOR_SPI_BIT_RATE_SPEED);
		this->m_appSettings.m_usbAdaptorSPISetting.m_bitRateSpeed = DEFAULT_USB_ADAPTOR_SPI_BIT_RATE_SPEED;
		this->m_appSettings.m_usbAdaptorSPISetting.m_previous_bitRateSpeed = DEFAULT_USB_ADAPTOR_SPI_BIT_RATE_SPEED;
	}
	else{
		this->m_appSettings.m_usbAdaptorSPISetting.m_bitRateSpeed = spiBitRateSpeed;
		this->m_appSettings.m_usbAdaptorSPISetting.m_previous_bitRateSpeed = spiBitRateSpeed;
	}

	// SPI Received Timeout
	long spiReceivedTimeout;
	if (pConfig->Read(wxT("SPIReceivedTimeOut"), &spiReceivedTimeout) == false){
		pConfig->Write(wxT("SPIReceivedTimeOut"), DEFAULT_USB_ADAPTOR_SPI_RECEIVED_TIMEOUT);
		this->m_appSettings.m_usbAdaptorSPISetting.m_receivedTimeout = DEFAULT_USB_ADAPTOR_SPI_RECEIVED_TIMEOUT;
		this->m_appSettings.m_usbAdaptorSPISetting.m_previous_receivedTimeout = DEFAULT_USB_ADAPTOR_SPI_RECEIVED_TIMEOUT;
	}
	else{
		this->m_appSettings.m_usbAdaptorSPISetting.m_receivedTimeout = spiReceivedTimeout;
		this->m_appSettings.m_usbAdaptorSPISetting.m_previous_receivedTimeout = spiReceivedTimeout;
	}

	// SPI Received Buffer Size
	long spiReceiveBufferSize;
	if (pConfig->Read(wxT("SPIReceiveBufferSize"), &spiReceiveBufferSize) == false){
		pConfig->Write(wxT("SPIReceiveBufferSize"), DEFAULT_USB_ADAPTOR_SPI_RECEIVE_BUFFER_SIZE);
		this->m_appSettings.m_usbAdaptorSPISetting.m_receiveBufferSize = DEFAULT_USB_ADAPTOR_SPI_RECEIVE_BUFFER_SIZE;
		this->m_appSettings.m_usbAdaptorSPISetting.m_previous_receiveBufferSize = DEFAULT_USB_ADAPTOR_SPI_RECEIVE_BUFFER_SIZE;
	}
	else{
		this->m_appSettings.m_usbAdaptorSPISetting.m_receiveBufferSize = spiReceiveBufferSize;
		this->m_appSettings.m_usbAdaptorSPISetting.m_previous_receiveBufferSize = spiReceiveBufferSize;
	}


	// CAN Bit Rate Speed
	long canBitRateSpeed;
	if (pConfig->Read(wxT("CANBitRateSpeed"), &canBitRateSpeed) == false){
		pConfig->Write(wxT("CANBitRateSpeed"), DEFAULT_USB_ADAPTOR_CAN_BIT_RATE_SPEED);
		this->m_appSettings.m_usbAdaptorCANSetting.m_bitRateSpeed = DEFAULT_USB_ADAPTOR_CAN_BIT_RATE_SPEED;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_bitRateSpeed = DEFAULT_USB_ADAPTOR_CAN_BIT_RATE_SPEED;
	}
	else{
		this->m_appSettings.m_usbAdaptorCANSetting.m_bitRateSpeed = canBitRateSpeed;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_bitRateSpeed = canBitRateSpeed;
	}

	// CAN Received MSG Size
	long canReceivedMSGSize;
	if (pConfig->Read(wxT("CANReceivedMSGSize"), &canReceivedMSGSize) == false){
		pConfig->Write(wxT("CANReceivedMSGSize"), DEFAULT_USB_ADAPTOR_CAN_RECEIVED_MSGSIZE);
		this->m_appSettings.m_usbAdaptorCANSetting.m_receivedMSGSize = DEFAULT_USB_ADAPTOR_CAN_RECEIVED_MSGSIZE;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_receivedMSGSize = DEFAULT_USB_ADAPTOR_CAN_RECEIVED_MSGSIZE;
	}
	else{
		this->m_appSettings.m_usbAdaptorCANSetting.m_receivedMSGSize = canReceivedMSGSize;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_receivedMSGSize = canReceivedMSGSize;
	}

	// CAN Received Timeout
	long canReceivedTimeout;
	if (pConfig->Read(wxT("CANReceivedTimeOut"), &canReceivedTimeout) == false){
		pConfig->Write(wxT("CANReceivedTimeOut"), DEFAULT_USB_ADAPTOR_CAN_RECEIVED_TIMEOUT);
		this->m_appSettings.m_usbAdaptorCANSetting.m_receivedTimeout = DEFAULT_USB_ADAPTOR_CAN_RECEIVED_TIMEOUT;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_receivedTimeout = DEFAULT_USB_ADAPTOR_CAN_RECEIVED_TIMEOUT;
	}
	else{
		this->m_appSettings.m_usbAdaptorCANSetting.m_receivedTimeout = canReceivedTimeout;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_receivedTimeout = canReceivedTimeout;
	}

	// CAN Received Buffer Size
	long canReceiveBufferSize;
	if (pConfig->Read(wxT("CANReceiveBufferSize"), &canReceiveBufferSize) == false){
		pConfig->Write(wxT("CANReceiveBufferSize"), DEFAULT_USB_ADAPTOR_CAN_RECEIVE_BUFFER_SIZE);
		this->m_appSettings.m_usbAdaptorCANSetting.m_receiveBufferSize = DEFAULT_USB_ADAPTOR_CAN_RECEIVE_BUFFER_SIZE;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_receiveBufferSize = DEFAULT_USB_ADAPTOR_CAN_RECEIVE_BUFFER_SIZE;
	}
	else{
		this->m_appSettings.m_usbAdaptorCANSetting.m_receiveBufferSize = canReceiveBufferSize;
		this->m_appSettings.m_usbAdaptorCANSetting.m_previous_receiveBufferSize = canReceiveBufferSize;
	}

#endif

	pConfig->SetPath(wxT("/TOTALPHASE"));

	long totalPhaseI2CBitrate;
	if (pConfig->Read(wxT("TotalPhaseI2CBitrate"), &totalPhaseI2CBitrate) == false){
		pConfig->Write(wxT("TotalPhaseI2CBitrate"), DEFAULT_TOTALPHASE_I2C_BITRATE);
		this->m_appSettings.m_totalPhase_I2C_Bitrate = DEFAULT_TOTALPHASE_I2C_BITRATE;
	}
	else{
		this->m_appSettings.m_totalPhase_I2C_Bitrate = totalPhaseI2CBitrate;
	}

	pConfig->SetPath(wxT("/TRC2ADAPTER"));

	long trc2AdapterI2CBitrate;
	if (pConfig->Read(wxT("TRC2AdapterI2CBitrate"), &trc2AdapterI2CBitrate) == false) {
		pConfig->Write(wxT("TRC2AdapterI2CBitrate"), DEFAULT_TRC2_ADAPTER_I2C_BITRATE);
		this->m_appSettings.m_trc2Adapter_I2C_Bitrate = DEFAULT_TRC2_ADAPTER_I2C_BITRATE;
	}
	else {
		this->m_appSettings.m_trc2Adapter_I2C_Bitrate = trc2AdapterI2CBitrate;
	}

	pConfig->SetPath(wxT("/ISP"));
	
	long pfcF3CMDDelayTime;
	if (pConfig->Read(wxT("PfcF3CMDDelayTime"), &pfcF3CMDDelayTime) == false){
		pConfig->Write(wxT("PfcF3CMDDelayTime"), DEFAULT_PFC_ISP_F3_CMD_DELAY_SLEEP_TIME);
		this->m_appSettings.m_pfcIspF3CMDDelayTime = DEFAULT_PFC_ISP_F3_CMD_DELAY_SLEEP_TIME;
	}
	else{
		this->m_appSettings.m_pfcIspF3CMDDelayTime = pfcF3CMDDelayTime;
	}

	long pfcF3CMDTotalPhaseDelayTime;
	if (pConfig->Read(wxT("PfcF3CMDTotalPhaseDelayTime"), &pfcF3CMDTotalPhaseDelayTime) == false){
		pConfig->Write(wxT("PfcF3CMDTotalPhaseDelayTime"), DEFAULT_PFC_ISP_F3_CMD_TOTALPHASE_DELAY_SLEEP_TIME);
		this->m_appSettings.m_pfcIspF3CMDTotalPhaseDelayTime = DEFAULT_PFC_ISP_F3_CMD_TOTALPHASE_DELAY_SLEEP_TIME;
	}
	else{
		this->m_appSettings.m_pfcIspF3CMDTotalPhaseDelayTime = pfcF3CMDTotalPhaseDelayTime;
	}

	long pfcWaitRebootTime;
	if (pConfig->Read(wxT("PFCWaitRebootTime"), &pfcWaitRebootTime) == false){
		pConfig->Write(wxT("PFCWaitRebootTime"), WAIT_PFC_REBOOT_TIME);
		this->m_appSettings.m_ISPPFCWaitRootTime = WAIT_PFC_REBOOT_TIME;
	}
	else{
		this->m_appSettings.m_ISPPFCWaitRootTime = pfcWaitRebootTime;
	}
	

	long ddWaitRebootTime;
	if (pConfig->Read(wxT("DDWaitRebootTime"), &ddWaitRebootTime) == false){
		pConfig->Write(wxT("DDWaitRebootTime"), WAIT_DD_REBOOT_TIME);
		this->m_appSettings.m_ISPDDWaitRootTime = WAIT_DD_REBOOT_TIME;
	}
	else{
		this->m_appSettings.m_ISPDDWaitRootTime = ddWaitRebootTime;
	}

	long pfcStartVerifyDelayTime;
	if (pConfig->Read(wxT("PFCStartVerifyDelayTime"), &pfcStartVerifyDelayTime) == false) {
		pConfig->Write(wxT("PFCStartVerifyDelayTime"), ISP_PFC_START_VERIFY_DELAY_TIME);
		this->m_appSettings.m_ISPPFCStartVerifyDelayTime = ISP_PFC_START_VERIFY_DELAY_TIME;
	}
	else {
		this->m_appSettings.m_ISPPFCStartVerifyDelayTime = pfcStartVerifyDelayTime;
	}

	long ddStartVerifyDelayTime;
	if (pConfig->Read(wxT("DDStartVerifyDelayTime"), &ddStartVerifyDelayTime) == false) {
		pConfig->Write(wxT("DDStartVerifyDelayTime"), ISP_DD_START_VERIFY_DELAY_TIME);
		this->m_appSettings.m_ISPDDStartVerifyDelayTime = ISP_DD_START_VERIFY_DELAY_TIME;
	}
	else {
		this->m_appSettings.m_ISPDDStartVerifyDelayTime = ddStartVerifyDelayTime;
	}

	//pConfig->Write(wxT("PFCStartVerifySuccessDelayTime"), this->m_appSettings.m_ISPPFCStartVerifySuccessDelayTime);
	long pfcStartVerifySuccessDelayTime;
	if (pConfig->Read(wxT("PFCStartVerifySuccessDelayTime"), &pfcStartVerifySuccessDelayTime) == false) {
		pConfig->Write(wxT("PFCStartVerifySuccessDelayTime"), DEFAULT_PFC_START_VERIFY_SUCCESS_DELAY_TIME);
		this->m_appSettings.m_ISPPFCStartVerifySuccessDelayTime = DEFAULT_PFC_START_VERIFY_SUCCESS_DELAY_TIME;
	}
	else {
		this->m_appSettings.m_ISPPFCStartVerifySuccessDelayTime = pfcStartVerifySuccessDelayTime;
	}

	pConfig->SetPath(wxT("/MFR"));

	// MFR_ID
	wxString mfr_id;
	if (pConfig->Read(wxT("MFRID"), &mfr_id) == false){
		pConfig->Write(wxT("MFRID"), PMBUSHelper::getDefaultMFR_ID());
		this->m_appSettings.m_mfr_id = wxString::Format("%s", PMBUSHelper::getDefaultMFR_ID().c_str());
	}
	else{
		this->m_appSettings.m_mfr_id = wxString::Format("%s", mfr_id);
	}

	// MFR_MODEL
	wxString mfr_model;
	if (pConfig->Read(wxT("MFRMODEL"), &mfr_model) == false){
		pConfig->Write(wxT("MFRMODEL"), PMBUSHelper::getDefaultMFR_MODEL());
		this->m_appSettings.m_mfr_model = wxString::Format("%s", PMBUSHelper::getDefaultMFR_MODEL().c_str());
	}
	else{
		this->m_appSettings.m_mfr_model = wxString::Format("%s", mfr_model);
	}
	
	// MFR_REVISION
	wxString mfr_revision;
	if (pConfig->Read(wxT("MFRREVISION"), &mfr_revision) == false){
		pConfig->Write(wxT("MFRREVISION"), PMBUSHelper::getDefaultMFR_REVISION());
		this->m_appSettings.m_mfr_revision = wxString::Format("%s", PMBUSHelper::getDefaultMFR_REVISION().c_str());
	}
	else{
		this->m_appSettings.m_mfr_revision = wxString::Format("%s", mfr_revision);
	}

	// MFR_LOCATION
	wxString mfr_location;
	if (pConfig->Read(wxT("MFRLOCATION"), &mfr_location) == false){
		pConfig->Write(wxT("MFRLOCATION"), PMBUSHelper::getDefaultMFR_LOCATION());
		this->m_appSettings.m_mfr_location = wxString::Format("%s", PMBUSHelper::getDefaultMFR_LOCATION().c_str());
	}
	else{
		this->m_appSettings.m_mfr_location = wxString::Format("%s", mfr_location);
	}

	// MFR_DATE
	wxString mfr_date;
	if (pConfig->Read(wxT("MFRDATE"), &mfr_date) == false){
		pConfig->Write(wxT("MFRDATE"), PMBUSHelper::getDefaultMFR_DATE());
		this->m_appSettings.m_mfr_date = wxString::Format("%s", PMBUSHelper::getDefaultMFR_DATE().c_str());
	}
	else{
		this->m_appSettings.m_mfr_date = wxString::Format("%s", mfr_date);
	}

	// MFR_SERIAL
	wxString mfr_serial;
	if (pConfig->Read(wxT("MFRSERIAL"), &mfr_serial) == false){
		pConfig->Write(wxT("MFRSERIAL"), PMBUSHelper::getDefaultMFR_SERIAL());
		this->m_appSettings.m_mfr_serial = wxString::Format("%s", PMBUSHelper::getDefaultMFR_SERIAL().c_str());
	}
	else{
		this->m_appSettings.m_mfr_serial = wxString::Format("%s", mfr_serial);
	}


	pConfig->SetPath(wxT("/PBF00300G"));
	
	//0900 Write Page Option
	double _0900Input;
	if (pConfig->Read(wxT("0900Input"), &_0900Input) == false) {
		pConfig->Write(wxT("0900Input"), DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageInput = DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageInput = _0900Input;
	}

	double _0900DefaultInput;
	if (pConfig->Read(wxT("0900DefaultInput"), &_0900DefaultInput) == false) {
		pConfig->Write(wxT("0900DefaultInput"), DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageDefaultInput = DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageDefaultInput = _0900DefaultInput;
	}

	double _0900MaxInput;
	if (pConfig->Read(wxT("0900MaxInput"), &_0900MaxInput) == false) {
		pConfig->Write(wxT("0900MaxInput"), DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT_MAX);
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageMax = DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT_MAX;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageMax = _0900MaxInput;
	}

	double _0900MinInput;
	if (pConfig->Read(wxT("0900MinInput"), &_0900MinInput) == false) {
		pConfig->Write(wxT("0900MinInput"), DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT_MIN);
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageMin = DEFAULT_PBF00300G_WRITEPAGE_0900_INPUT_MIN;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0900WritePageMin = _0900MinInput;
	}

	//0920 Write Page Option
	long _0920Input;
	if (pConfig->Read(wxT("0920Input"), &_0920Input) == false) {
		pConfig->Write(wxT("0920Input"), DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageInput = DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageInput = _0920Input;
	}

	long _0920DefaultInput;
	if (pConfig->Read(wxT("0920DefaultInput"), &_0920DefaultInput) == false) {
		pConfig->Write(wxT("0920DefaultInput"), DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageDefaultInput = DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageDefaultInput = _0920DefaultInput;
	}

	long _0920MaxInput;
	if (pConfig->Read(wxT("0920MaxInput"), &_0920MaxInput) == false) {
		pConfig->Write(wxT("0920MaxInput"), DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT_MAX);
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageMax = DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT_MAX;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageMax = _0920MaxInput;
	}

	long _0920MinInput;
	if (pConfig->Read(wxT("0920MinInput"), &_0920MinInput) == false) {
		pConfig->Write(wxT("0920MinInput"), DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT_MIN);
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageMin = DEFAULT_PBF00300G_WRITEPAGE_0920_INPUT_MIN;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0920WritePageMin = _0920MinInput;
	}

	//0921 Write Page Option
	long _0921Input;
	if (pConfig->Read(wxT("0921Input"), &_0921Input) == false) {
		pConfig->Write(wxT("0921Input"), DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageInput = DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageInput = _0921Input;
	}

	long _0921DefaultInput;
	if (pConfig->Read(wxT("0921DefaultInput"), &_0921DefaultInput) == false) {
		pConfig->Write(wxT("0921DefaultInput"), DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageDefaultInput = DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageDefaultInput = _0921DefaultInput;
	}

	long _0921MaxInput;
	if (pConfig->Read(wxT("0921MaxInput"), &_0921MaxInput) == false) {
		pConfig->Write(wxT("0921MaxInput"), DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT_MAX);
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageMax = DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT_MAX;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageMax = _0921MaxInput;
	}

	long _0921MinInput;
	if (pConfig->Read(wxT("0921MinInput"), &_0921MinInput) == false) {
		pConfig->Write(wxT("0921MinInput"), DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT_MIN);
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageMin = DEFAULT_PBF00300G_WRITEPAGE_0921_INPUT_MIN;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0921WritePageMin = _0921MinInput;
	}

	//0923 Write Page Option
	long _0923Input;
	if (pConfig->Read(wxT("0923Input"), &_0923Input) == false) {
		pConfig->Write(wxT("0923Input"), DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageInput = DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageInput = _0923Input;
	}

	long _0923DefaultInput;
	if (pConfig->Read(wxT("0923DefaultInput"), &_0923DefaultInput) == false) {
		pConfig->Write(wxT("0923DefaultInput"), DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT);
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageDefaultInput = DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageDefaultInput = _0923DefaultInput;
	}

	long _0923MaxInput;
	if (pConfig->Read(wxT("0923MaxInput"), &_0923MaxInput) == false) {
		pConfig->Write(wxT("0923MaxInput"), DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT_MAX);
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageMax = DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT_MAX;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageMax = _0923MaxInput;
	}

	long _0923MinInput;
	if (pConfig->Read(wxT("0923MinInput"), &_0923MinInput) == false) {
		pConfig->Write(wxT("0923MinInput"), DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT_MIN);
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageMin = DEFAULT_PBF00300G_WRITEPAGE_0923_INPUT_MIN;
	}
	else {
		this->m_appSettings.m_pbf00300gOption.m_0923WritePageMin = _0923MinInput;
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

	//PMBUSHelper::SetAppSettings(&this->m_appSettings);
}

void MainFrame::CheckIfModelChange(void){

	// Reset Model Changed Flag
	this->m_modelChangedFlag = false;

	// Action : Setup Default MFR_XXX

	// Setup Default MFR_ID
	PMBUSHelper::getDefaultMFR_ID() = wxString::Format("%s", DEF_MFR_ID);

	// Setup Default MFR_MODEL
	PMBUSHelper::getDefaultMFR_MODEL() = wxString::Format("%s", DEF_MFR_MODEL);

	// Setup Default MFR_REVISION
	PMBUSHelper::getDefaultMFR_REVISION() = wxString::Format("%s", DEF_MFR_REVISION);

	// Setup Default MFR_LOCATION
	PMBUSHelper::getDefaultMFR_LOCATION() = wxString::Format("%s", DEF_MFR_LOCATION);

	// Setup Default MFR_DATE
	wxString dateString("");
	wxDateTime datetime = wxDateTime::Now();

	dateString += wxString::Format("%2d", datetime.GetYear());

	dateString.erase(0, 2);

	if (datetime.GetMonth()+1 >= 10 ){
		dateString += wxString::Format("%2d", datetime.GetMonth() + 1);
	}
	else{
		dateString += wxString::Format("0%d", datetime.GetMonth() + 1);
	}

	if (datetime.GetDay() >= 10) {
		dateString += wxString::Format("%2d", datetime.GetDay());
	}
	else {
		dateString += wxString::Format("0%d", datetime.GetDay());
	}

	PMBUSHelper::getDefaultMFR_DATE() = wxString::Format("%s", dateString.c_str());

	// Force let MFR_DATE equal to Now system Time
	this->m_appSettings.m_mfr_date = PMBUSHelper::getDefaultMFR_DATE();

	// Setup Default MFR_SERIAL
	PMBUSHelper::getDefaultMFR_SERIAL() = wxString::Format("%s", DEF_MFR_SERIAL);
	
	// Work-Around For Set Default Polling Time by Model
	this->m_defaultI2CAddress = DEFAULT_I2C_SLAVEADDRESS;
	this->m_defaultPollingTime = DEFAULT_POLLING_INTERVAL;

	// If Model or Customer Changed
	if (this->m_appSettings.m_currentUseCustomer != this->m_appSettings.m_previousUseCustomer || this->m_appSettings.m_currentUseModel != this->m_appSettings.m_previousUseModel)
	{ 
		this->m_modelChangedFlag = true;

		// Action : Setup MFR_XXX by Specified Customer And Model

		switch (this->m_appSettings.m_currentUseCustomer){
		
		case Customer_GIGABYTE:

			switch (this->m_appSettings.m_currentUseModel){

			case GIGABYTE_Model_CRPS001:

				break;

			case GIGABYTE_Model_CRPS001_ALL_PMBUS_COMMANDS:

				break;

#if (HAVE_GENERIC_MODEL == TRUE)
			case GIGABYTE_Model_Generic:

				break;
#endif

			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
				break;
			}

			break;

		case Customer_ACBEL:

			switch (this->m_appSettings.m_currentUseModel){

			case ACBEL_RFWE_24_28_1200W_SCP:

				break;

			case ACBEL_PBF003_00G:
				// Work-Around For Set Default Polling Time by Model
				this->m_defaultI2CAddress = DEFAULT_I2C_SLAVEADDRESS_PBF003_00G;
				this->m_defaultPollingTime = DEFAULT_POLLING_INTERVAL_PBF003_00G;
				
				break;

#if (HAVE_GENERIC_MODEL == TRUE)
			case ACBEL__Model_Generic:

				break;
#endif

			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
				break;
			}

			break;

#if (HAVE_GENERIC_CUSTOMER == TRUE)
		case Customer_Generic:

			switch (this->m_appSettings.m_currentUseModel){

			case GENERIC_Model_Generic:

				break;

			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
				break;
			}

			break;
#endif
		
		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
			break;
		}

		// Set Current To Previous
		this->m_appSettings.m_previousUseCustomer = this->m_appSettings.m_currentUseCustomer;
		this->m_appSettings.m_previousUseModel = this->m_appSettings.m_currentUseModel;
	}

}

void MainFrame::SaveConfig(void){

	wxConfigBase *pConfig = wxConfigBase::Get();

	if (pConfig==NULL) return;

	pConfig->SetPath(wxT("/APP"));

	// Customer
	pConfig->Write(wxT("Customer"), this->m_appSettings.m_currentUseCustomer);

	// Previous Customer
	pConfig->Write(wxT("PreviousCustomer"), this->m_appSettings.m_previousUseCustomer);

	// Model
	pConfig->Write(wxT("Model"), this->m_appSettings.m_currentUseModel);
	
	// Previous Model
	pConfig->Write(wxT("PreviousModel"), this->m_appSettings.m_previousUseModel);

	// I2C Adaptor Module Board
	pConfig->Write(wxT("I2CAdaptorModuleBoard"), this->m_appSettings.m_I2CAdaptorModuleBoard);

	// I2C Slave Address
	pConfig->Write(wxT("I2CSlaveAddress"), this->m_appSettings.m_I2CSlaveAddress);

	// Run Mode
	pConfig->Write(wxT("RunMode"), this->m_appSettings.m_runMode);

	// Polling Interval
	pConfig->Write(wxT("PollingInterval"), this->m_appSettings.m_pollingInterval);

	// Iterations
	pConfig->Write(wxT("Iterations"), this->m_appSettings.m_IterationsValue);

	// Enable Checksum
	pConfig->Write(wxT("EnableChecksum"), this->m_appSettings.m_EnableChecksum);

	// Only Polling Support CMD
	pConfig->Write(wxT("OnlyPollingSupportCMD"), this->m_appSettings.m_onlyPollingSupportCMD);

	// Clear Log Before Monitor Run
	pConfig->Write(wxT("ClearLogBeforeMonitorRun"), this->m_appSettings.m_clearLogBeforeMonitorRun);

	// Auto Query CMD On I/O Open
	pConfig->Write(wxT("AutoQueryCMDOnIOOpen"), this->m_appSettings.m_autoQueryCMDOnIOOpen);

	// Query CMD Before Polling
	pConfig->Write(wxT("QueryCMDBeforePolling"), this->m_appSettings.m_queryCMDBeforePolling);

	// Increase CPU Overhead
	pConfig->Write(wxT("IncreaseCPUOverhead"), this->m_appSettings.m_increaseCPUOverhead);


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


	pConfig->SetPath(wxT("/TOTALPHASE"));

	// Total Phase I2C Bit Rate
	pConfig->Write(wxT("TotalPhaseI2CBitrate"), this->m_appSettings.m_totalPhase_I2C_Bitrate);


	pConfig->SetPath(wxT("/TRC2ADAPTER"));

	// TRC2 Adapter Phase I2C Bit Rate
	pConfig->Write(wxT("TRC2AdapterI2CBitrate"), this->m_appSettings.m_trc2Adapter_I2C_Bitrate);

	pConfig->SetPath(wxT("/ISP"));

	// F3 CMD Delay Time
	pConfig->Write(wxT("PfcF3CMDDelayTime"), this->m_appSettings.m_pfcIspF3CMDDelayTime);

	pConfig->Write(wxT("PfcF3CMDTotalPhaseDelayTime"), this->m_appSettings.m_pfcIspF3CMDTotalPhaseDelayTime);

	pConfig->Write(wxT("PFCWaitRebootTime"), this->m_appSettings.m_ISPPFCWaitRootTime);

	pConfig->Write(wxT("DDWaitRebootTime"), this->m_appSettings.m_ISPDDWaitRootTime);

	pConfig->Write(wxT("PFCStartVerifyDelayTime"), this->m_appSettings.m_ISPPFCStartVerifyDelayTime);

	pConfig->Write(wxT("DDStartVerifyDelayTime"), this->m_appSettings.m_ISPDDStartVerifyDelayTime);

	pConfig->Write(wxT("PFCStartVerifySuccessDelayTime"), this->m_appSettings.m_ISPPFCStartVerifySuccessDelayTime);
	
	pConfig->SetPath(wxT("/MFR"));

	// MFR_ID
	pConfig->Write(wxT("MFRID"), this->m_appSettings.m_mfr_id);

	// MFR_MODEL
	pConfig->Write(wxT("MFRMODEL"), this->m_appSettings.m_mfr_model);

	// MFR_REVISION
	pConfig->Write(wxT("MFRREVISION"), this->m_appSettings.m_mfr_revision);

	// MFR_LOCATION
	pConfig->Write(wxT("MFRLOCATION"), this->m_appSettings.m_mfr_location);

	// MFR_DATE
	pConfig->Write(wxT("MFRDATE"), this->m_appSettings.m_mfr_date);

	// MFR_SERIAL
	pConfig->Write(wxT("MFRSERIAL"), this->m_appSettings.m_mfr_serial);

	pConfig->SetPath(wxT("/PBF00300G"));

	//0900 Write Page Input
	pConfig->Write(wxT("0900Input"), this->m_appSettings.m_pbf00300gOption.m_0900WritePageInput);

	//0920 Write Page Input
	pConfig->Write(wxT("0920Input"), this->m_appSettings.m_pbf00300gOption.m_0920WritePageInput);

	//0921 Write Page Input
	pConfig->Write(wxT("0921Input"), this->m_appSettings.m_pbf00300gOption.m_0921WritePageInput);

	//0923 Write Page Input
	pConfig->Write(wxT("0923Input"), this->m_appSettings.m_pbf00300gOption.m_0923WritePageInput);

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

	if (this->m_logFileTextOutputStream) {
		this->m_logFileTextOutputStream->Flush();
		delete this->m_logFileTextOutputStream;
		this->m_logFileTextOutputStream = NULL;
	}

	if (this->m_logFileFFileOutputStream) {
		delete this->m_logFileFFileOutputStream;
		this->m_logFileFFileOutputStream = NULL;
	}

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

void MainFrame::HexToBin(void){
	// Load Hex File
	wxFileDialog LoadHexFileDialog(this, L"Load Firmware File", "", "", "HEX Files (*.hex)|*.hex", wxFD_OPEN);

	LoadHexFileDialog.Centre();

	// If the user changed idea...
	if (LoadHexFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

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
	tihex<unsigned short> tiHexFileStat;
	TIHexInput >> tiHexFileStat;//m_SecondaryTIHexFileStat;

	// Check Errors
	if (tiHexFileStat.getNoErrors() != 0){

		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Errors :");

		while (tiHexFileStat.getNoErrors() != 0){
			string error_str;
			tiHexFileStat.popNextError(error_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", error_str.c_str());
		}


		wxMessageBox(wxT("Load Hex File Has Error"),
			wxT("Error !"),
			wxOK | wxICON_ERROR);

		return;
	}

	// Check Warnings
	if (tiHexFileStat.getNoWarnings() != 0)
	{
		PSU_DEBUG_PRINT(MSG_ERROR, "Read HEX File Contains Warnings :");

		while (tiHexFileStat.getNoWarnings() != 0){
			string warning_str;
			tiHexFileStat.popNextWarning(warning_str);
			PSU_DEBUG_PRINT(MSG_ERROR, "%s", warning_str.c_str());
		}

		wxMessageBox(wxT("Load Hex File Has Warning"),
			wxT("Warning !"),
			wxOK | wxICON_WARNING);
	}


	/* Fill Blank Address */
	tiHexFileStat.fillBlankAddr(0xffff);

	/* Compute Start & End Address */
	tiHexFileStat.begin();
	unsigned long StartAddress = tiHexFileStat.currentAddress();

	tiHexFileStat.end();
	unsigned long EndAddress = tiHexFileStat.currentAddress();

	/* Get Binary File Save Name */
	path.RemoveLast(4);
	path += wxT(".bin");

	// Start Save Binary File 
	wxString SavePath = path;
	PSU_DEBUG_PRINT(MSG_ALERT, "Save Binary File To : %s", SavePath.c_str());

	wxFFileOutputStream fileOutStream(SavePath);

	if (!fileOutStream.IsOk()){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not Save Binary To %s", SavePath);
		return;
	}

	wxDataOutputStream dataOutputStream(fileOutStream);


	unsigned short data = 0x0000;
	unsigned char tmp = 0x00;
	for (unsigned long currentAddress = StartAddress; currentAddress <= EndAddress; currentAddress++){

		tiHexFileStat.getData(&data, currentAddress);
		//PSU_DEBUG_PRINT(MSG_ALERT, "data=%04x", data);
		tmp = *((unsigned char*)&data);
		//PSU_DEBUG_PRINT(MSG_ALERT, "tmp=%02x", tmp);
		data >>= 8;
		//PSU_DEBUG_PRINT(MSG_ALERT, "data=%04x", data);
		*(((unsigned char*)&data) + 1) = tmp;
		//data = (tmp << 8) | data;
		//PSU_DEBUG_PRINT(MSG_ALERT, "data=%04x", data);

		wxUint16 u16(data);

		dataOutputStream.Write16(u16);
	}


	fileOutStream.Sync();
}

#ifdef _WIN32
void MainFrame::RegisterDeviceChangeNotify(void){
	
	const GUID GuidInterfaceList[] =
	{
		// USB Raw Device Interface Class GUID
		{ 0xa5dcbf10,  0x6530, 0x11d2, { 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed } },
		// Disk Device Interface Class GUID
		{ 0x53f56307,  0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
		// Human Interface Device Class GUID
		{ 0x4d1e55b2,  0xf16f, 0x11Cf, { 0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
		// COMPORT Device ???
		{ 0xad498944,  0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } },
		// FTDI_D2XX_Device Class GUID
		{ 0x219d0508,  0x57a8, 0x4ff5, { 0x97, 0xa1, 0xbd, 0x86, 0x58, 0x7c, 0x6c, 0x7e } },
		// FTDI_VCP_Device Class GUID
		{ 0x86e0d1e0L, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
	};

	//DEV_BROADCAST_DEVICEINTERFACE dbch;
	dbch.dbcc_size = sizeof(dbch);
	dbch.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	for (int i = 0; i < sizeof(GuidInterfaceList) / sizeof(GuidInterfaceList[0]); i++)
	{
		//dbch.dbcc_classguid = FTDI_D2XX_GUID;//FTDI_VCP_GUID;
		dbch.dbcc_classguid = GuidInterfaceList[i];
		dbch.dbcc_name[0] = '\0';
		NotificationHandle = RegisterDeviceNotification(this->GetHWND(), &dbch, DEVICE_NOTIFY_WINDOW_HANDLE);
	}

}

void  MainFrame::DeviceChangeHandler(unsigned int Event, unsigned Type, unsigned int pid, unsigned int vid){

	PSU_DEBUG_PRINT(MSG_DEBUG, "PID=%d, VID=%d", pid, vid);

	switch (Event) {

	case DBT_DEVICEARRIVAL:
		PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVICEARRIVAL");
		/* Device Arrival */
		// If I/O is Close
		if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_CLOSE){

			wxBusyInfo info
			(
				wxBusyInfoFlags()
				.Parent(this)
				.Icon(wxArtProvider::GetIcon(wxART_FIND,
				wxART_OTHER, wxSize(64, 64)))
				.Title("<b>Find I/O Device</b>")
				.Text("Please  wait  ...")
				.Foreground(*wxBLACK)
				.Background(*wxLIGHT_GREY)
				.Transparency(wxALPHA_OPAQUE)// 4 * wxALPHA_OPAQUE / 5)
		    );

			this->CloseIODevice();
			wxMilliSleep(200);
			this->OpenIODevice();
		}

		break;

	case DBT_DEVICEREMOVECOMPLETE:
		PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVICEREMOVECOMPLETE");
		/* Device Remove */
		// If I/O is Open
		if (this->m_IOAccess[this->m_CurrentUseIOInterface].m_GetDeviceStatus() == IODEVICE_OPEN){
			
			// If Monitor is running
			if (this->m_monitor_running == true){
				StopMonitor();
				wxMilliSleep(100);
			}
			
			this->CloseIODevice();
			
			// If ISP Not In Progress, Popup Messages Box To Notify User I/O Device Lost
			if (m_pmbusProgressDialog == NULL){
				wxMessageBox(wxT("Please Check I/O Device Connection !"),
					wxT("Lost I/O Device ! !"),  // caption
					wxOK | wxICON_ERROR);
			}

			wxMilliSleep(200);
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_DEBUG, "EVENT = %xH", Event);
		break;
	}

}
#endif

#ifdef _WIN32
WXLRESULT MainFrame::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam){
	
	bool processed = false;

	if ((DBT_DEVICEARRIVAL == wParam) || (DBT_DEVICEREMOVECOMPLETE == wParam))
	{
		PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;

		wxString devName;
		unsigned int pid, vid;

		PDEV_BROADCAST_DEVICEINTERFACE  pDevInf;
		// PDEV_BROADCAST_HANDLE    pDevHnd; 
		// PDEV_BROADCAST_OEM       pDevOem; 
		PDEV_BROADCAST_PORT      pDevPort; 
		// PDEV_BROADCAST_VOLUME    pDevVolume; 
		// PDEV_BROADCAST_DEVNODE   pDevNode;

		switch (pHdr->dbch_devicetype)
		{
		case DBT_DEVTYP_DEVICEINTERFACE:

			pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
		
			//DeviceUpdate(pDevInf, wParam);
			PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVTYP_DEVICEINTERFACE");
			PSU_DEBUG_PRINT(MSG_DEBUG, "Device Name = %s", pDevInf->dbcc_name);

			devName = wxString::Format("%s", pDevInf->dbcc_name);
			PMBUSHelper::GetPIDAndVIDFromString(devName, &pid, &vid);

			PSU_DEBUG_PRINT(MSG_DEBUG, "PID=%d, VID=%d", pid, vid);

			if (this->m_CurrentUseIOInterface == IOACCESS_HID){
				if(pid == I2C_AdaptorModuleBoard_R90000_9271_USB_PID && vid == I2C_AdaptorModuleBoard_R90000_9271_USB_VID){
					this->DeviceChangeHandler(wParam, pHdr->dbch_devicetype, pid, vid);
				}
			}
			else if (this->m_CurrentUseIOInterface == IOACCESS_TOTALPHASE){
				if(pid == TOTAL_PHASE_USB_PID && vid == TOTAL_PHASE_USB_VID){
					this->DeviceChangeHandler(wParam, pHdr->dbch_devicetype, pid, vid);
				}
			}
			else if (this->m_CurrentUseIOInterface == IOACCESS_PICKIT){
				if (pid == PICKIT_SERIAL_USB_PID && vid == PICKIT_SERIAL_USB_VID){
					this->DeviceChangeHandler(wParam, pHdr->dbch_devicetype, pid, vid);
				}
			}
			else if (this->m_CurrentUseIOInterface == IOACCESS_TRC2_I2C_ADAPTER) {
				if (pid == TRC2_I2C_ADAPTER_PID && vid == TRC2_I2C_ADAPTER_VID) {
					this->DeviceChangeHandler(wParam, pHdr->dbch_devicetype, pid, vid);
				}
			}

#if 0	
			switch (wParam){

			case DBT_DEVICEARRIVAL:
				PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVICEARRIVAL");
				// Device Arrival

				break;

			case DBT_DEVICEREMOVECOMPLETE:
				PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVICEREMOVECOMPLETE");
				// Device Remove
				
				break;

			default:
				PSU_DEBUG_PRINT(MSG_DEBUG, "EVENT = %xH", wParam);
				break;
			}
#endif

			processed = true;
			break;

		case DBT_DEVTYP_HANDLE:
			// pDevHnd = (PDEV_BROADCAST_HANDLE)pHdr;
			PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVTYP_HANDLE");
			break;

		case DBT_DEVTYP_OEM:
			// pDevOem = (PDEV_BROADCAST_OEM)pHdr;
			PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVTYP_OEM");
			break;

		case DBT_DEVTYP_PORT:
			pDevPort = (PDEV_BROADCAST_PORT)pHdr;
			PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVTYP_PORT");
			PSU_DEBUG_PRINT(MSG_DEBUG, "Device Name = %s", pDevPort->dbcp_name);

			devName = wxString::Format("%s", pDevPort->dbcp_name);
			PMBUSHelper::GetPIDAndVIDFromString(devName, &pid, &vid);

			PSU_DEBUG_PRINT(MSG_DEBUG, "PID=%d, VID=%d", pid, vid);

			if(this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT){
				this->DeviceChangeHandler(wParam, pHdr->dbch_devicetype, pid, vid);
			}

#if 0
			devName = wxString::Format("%s", pDevInf->dbcc_name);
			PMBUSHelper::GetPIDAndVIDFromString(devName, &pid, &vid);

			PSU_DEBUG_PRINT(MSG_DETAIL, "PID=%d, VID=%d", pid, vid);

			this->DeviceChangeHandler(wParam, pHdr->dbch_devicetype, pid, vid);


			switch (wParam){

			case DBT_DEVICEARRIVAL:
				PSU_DEBUG_PRINT(MSG_DETAIL, "DBT_DEVICEARRIVAL");
				break;

			case DBT_DEVICEREMOVECOMPLETE:
				PSU_DEBUG_PRINT(MSG_DETAIL, "DBT_DEVICEREMOVECOMPLETE");
				break;

			default:

				break;
			}
#endif

			break;

		case DBT_DEVTYP_VOLUME:
			// pDevVolume = (PDEV_BROADCAST_VOLUME)pHdr;
			PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVTYP_VOLUME");
			break;

		case DBT_DEVTYP_DEVNODE:
			// pDevNode = (PDEV_BROADCAST_DEVNODE)pHdr;
			PSU_DEBUG_PRINT(MSG_DEBUG, "DBT_DEVTYP_DEVNODE");
			break;
		}
	}

	if (true == processed){
		return((WXLRESULT)0);
	}
	else{
		// If message was not device insert / remove, call standard handler
		return wxFrame::MSWWindowProc(nMsg, wParam, lParam);
	}
}
#endif

void MainFrame::StartInCreaseCPUOverHeadThread(void){
	// Start IncreaseCPUOverHead Thread
	if (this->m_increaseCPUOverHeadThreadStopFlag == true){
		this->m_increaseCPUOverHeadThreadStopFlag = false;
		this->m_increaseCPUOverHeadThread = new IncreaseCPUOverHeadThread(&this->m_increaseCPUOverHeadThreadStopFlag);
		// If Create Thread Success
		if (this->m_increaseCPUOverHeadThread->Create() != wxTHREAD_NO_ERROR){
			PSU_DEBUG_PRINT(MSG_ERROR, "Can't Create IncreaseCPUOverHeadThread");
		}
		else{
			PSU_DEBUG_PRINT(MSG_ALERT, "Start Increase CPU Over Head Thread");
			this->m_increaseCPUOverHeadThread->SetPriority(WXTHREAD_DEFAULT_PRIORITY);
			this->m_increaseCPUOverHeadThread->Run();
		}
	}
}

void MainFrame::StopInCreaseCPUOverHeadThread(void){
	// Stop IncreaseCPUOverHead Thread
	wxThread::ExitCode exitCode;

	if (this->m_increaseCPUOverHeadThreadStopFlag == false){
		wxThreadError error = this->m_increaseCPUOverHeadThread->Delete(&exitCode, wxTHREAD_WAIT_YIELD);

		PSU_DEBUG_PRINT(MSG_DEBUG, "IncreaseCPUOverHeadThread Exit Code = %p", ((int*)exitCode));

		if (error != wxTHREAD_NO_ERROR){
			PSU_DEBUG_PRINT(MSG_ERROR, "wxThreadError = %d", error);
		}

		while (this->m_increaseCPUOverHeadThreadStopFlag == false){
			PSU_DEBUG_PRINT(MSG_DEBUG, "Wait IncreaseCPUOverHeadThread Finish")
			//wxMilliSleep(10);
		};

		this->m_increaseCPUOverHeadThread = NULL;
	}
}

void MainFrame::UpdateSTDPage(unsigned int index){
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

	if(index == this->findPMBUSCMDIndex(0x0904)){
		wxString vin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VIN);
		this->m_stdPage->m_tcVIN->SetValue(vin);
	}

	// IIN
	if (index == this->findPMBUSCMDIndex(0x89)){
		wxString iin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IIN);
		this->m_stdPage->m_tcIIN->SetValue(iin);
	}

	if (index == this->findPMBUSCMDIndex(0x0905)){
		wxString iin = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IIN);
		this->m_stdPage->m_tcIIN->SetValue(iin);
	}

	// VOUT
	if (index == this->findPMBUSCMDIndex(0x8b, 0)){
		wxString vout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VOUT);
		this->m_stdPage->m_tcVOUT->SetValue(vout);
	}

	if (index == this->findPMBUSCMDIndex(0x0906)){
		wxString vout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_VOUT);
		this->m_stdPage->m_tcVOUT->SetValue(vout);
	}

	// IOUT
	if (index == this->findPMBUSCMDIndex(0x8c, 0)){
		wxString iout = wxString::Format("%4.3f", (double)PMBUSHelper::GetPMBusStatus()->m_IOUT);
		this->m_stdPage->m_tcIOUT->SetValue(iout);
	}

	if (index == this->findPMBUSCMDIndex(0x0907)){
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

	if (index == this->findPMBUSCMDIndex(0x0908)) {
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
		wxString fan1 = wxString::Format("%.1f", (double)PMBUSHelper::GetPMBusStatus()->m_FAN1);
		this->m_stdPage->m_tcFAN1->SetValue(fan1);
	}

	// FAN2
	if (index == this->findPMBUSCMDIndex(0x91)){
		wxString fan2 = wxString::Format("%.1f", (double)PMBUSHelper::GetPMBusStatus()->m_FAN2);
		this->m_stdPage->m_tcFAN2->SetValue(fan2);
	}

	// FAN3

	// FAN4
}

void MainFrame::UpdateSTATUSPanel(unsigned int index){
	if (index == this->findPMBUSCMDIndex(0x79)){
		// Update WORD Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusWORD();
	}

	if (index == this->findPMBUSCMDIndex(0x7a)){
		// Update VOUT Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusVOUT();
	}

	if (index == this->findPMBUSCMDIndex(0x7b)){
		// Update IOUT Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusIOUT();
	}

	if (index == this->findPMBUSCMDIndex(0x7c)){
		// Update INPUT Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusINPUT();
	}

	if (index == this->findPMBUSCMDIndex(0x7d)){
		// Update Temperature Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusTemperature();
	}

	if (index == this->findPMBUSCMDIndex(0x7e)){
		// Update CML Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusCML();
	}

	if (index == this->findPMBUSCMDIndex(0x7f)){
		// Update OTHER Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusOTHER();
	}

	if (index == this->findPMBUSCMDIndex(0x81)){
		// Update OTHER Filed of PMBUSStatus Panel
		this->PMBusStatusPanel->Update_StatusFAN12();
	}

	if (index == this->findPMBUSCMDIndex(0xdc)){
		// Update Total PMBUSStatusDCH Panel
		this->PMBusStatusDCHPanel->UpdatePanel();
	}
}

void MainFrame::DoEnableCalibration(void){
	// Command Data For Enable Calibration
	unsigned char enableCalibration[2];
	enableCalibration[0] = 0x55;
	enableCalibration[1] = 0xAA;

	// Product Enable Calibration Command Send Buffer
	unsigned char CalibrationEnableSendBuffer[64];

	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		&this->m_CurrentUseIOInterface,
		CalibrationEnableSendBuffer,
		sizeof(CalibrationEnableSendBuffer),
		0xC3, // CMD
		enableCalibration,
		sizeof(enableCalibration)
		);

	// Fill PMBUS Command Structure
	PMBUSSendCOMMAND_t CMDC3H;

	CMDC3H.m_sendDataLength = (this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT || this->m_CurrentUseIOInterface == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMDC3H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(this->m_CurrentUseIOInterface, CMD_C3H_BYTES_TO_READ);//(this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT) ? CMD_C3H_BYTES_TO_READ : CMD_C3H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMDC3H.m_sendData[idx] = CalibrationEnableSendBuffer[idx];
	}

	// Decide how to send this command by whether monitor is running or not
	if (this->m_monitor_running == true){
		if (this->m_sendCMDVector.size() == 0){
			this->m_sendCMDVector.push_back(CMDC3H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %d", this->m_sendCMDVector.size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask)SendWriteCMDTask(this->m_IOAccess, &this->m_CurrentUseIOInterface, CMDC3H);
	}
}


void MainFrame::DoDisableCalibration(void){
	// Command Data For Disable Calibration
	unsigned char enableCalibration[2];
	enableCalibration[0] = 0x00;
	enableCalibration[1] = 0x00;

	// Product Enable Calibration Command Send Buffer
	unsigned char CalibrationEnableSendBuffer[64];

	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		&this->m_CurrentUseIOInterface,
		CalibrationEnableSendBuffer,
		sizeof(CalibrationEnableSendBuffer),
		0xC3, // CMD
		enableCalibration,
		sizeof(enableCalibration)
		);

	// Fill PMBUS Command Structure
	PMBUSSendCOMMAND_t CMDC3H;

	CMDC3H.m_sendDataLength = (this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT || this->m_CurrentUseIOInterface == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMDC3H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(this->m_CurrentUseIOInterface, CMD_C3H_BYTES_TO_READ);//(this->m_CurrentUseIOInterface == IOACCESS_SERIALPORT) ? CMD_C3H_BYTES_TO_READ : CMD_C3H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMDC3H.m_sendData[idx] = CalibrationEnableSendBuffer[idx];
	}

	// Decide how to send this command by whether monitor is running or not
	if (this->m_monitor_running == true){
		if (this->m_sendCMDVector.size() == 0){
			this->m_sendCMDVector.push_back(CMDC3H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %d", this->m_sendCMDVector.size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask)SendWriteCMDTask(this->m_IOAccess, &this->m_CurrentUseIOInterface, CMDC3H);
	}
}

void MainFrame::OnUpdateUI(wxUpdateUIEvent& event){
	event.Check(true);
}

void MainFrame::OnIdle(wxIdleEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTION__);
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(MENU_ID_Primary_Firmware, MainFrame::OnPrimaryFirmware)
EVT_MENU(MENU_ID_Secondary_Firmware, MainFrame::OnSecondaryFirmware)
EVT_MENU(MENU_ID_Monitor, MainFrame::OnMonitor)
EVT_MENU(MENU_ID_Update_Primary_Firmware, MainFrame::OnUpdatePrimaryFirmware)
EVT_MENU(MENU_ID_Update_Secondary_Firmware, MainFrame::OnUpdateSecondaryFirmware)
//EVT_MENU(MENU_ID_Stop_Programming, MainFrame::OnStopProgramming)
EVT_MENU(MENU_ID_Query_All_Commands, MainFrame::OnQueryAllCommands)
EVT_MENU(MENU_ID_Find_Available_I2C_Slave_Device, MainFrame::OnFindAvailableI2CSlaveDevice)
EVT_MENU(MENU_ID_I2C_Fault_Test, MainFrame::OnI2CFaultTest)
EVT_MENU(MENU_ID_Enable_Checksum, MainFrame::OnEnableChecksum)
EVT_MENU(MENU_ID_Only_Polling_Support_Command, MainFrame::OnOnlyPollingSupportCommand)
EVT_MENU(MENU_ID_Auto_Query_CMD_On_IO_Open, MainFrame::OnAutoQueryCMDOnIOOpen)
EVT_MENU(MENU_ID_Query_CMD_Before_Polling, MainFrame::OnQueryCMDBeforePolling)
EVT_MENU(MENU_ID_Clear_Log_Before_Monitor_Run, MainFrame::OnClearLogBeforeMonitorRun)
EVT_MENU(MENU_ID_Clear_Error_Log, MainFrame::OnClearErrorLog)
EVT_MENU(MENU_ID_Reset_MaxMin_Value, MainFrame::OnResetMaxMinValue)
EVT_MENU(MENU_ID_Reset_Run_Time, MainFrame::OnResetRunTime)
EVT_MENU(MENU_ID_EnableCalibration, MainFrame::OnEnableCalibration)
EVT_MENU(MENU_ID_DisableCalibration, MainFrame::OnDisableCalibration)
EVT_MENU(MENU_ID_Calibration, MainFrame::OnCalibration)
EVT_MENU(MENU_ID_Administrant, MainFrame::OnAdministrant)
EVT_MENU(MENU_ID_I2C_Interface, MainFrame::OnI2CInterface)
EVT_MENU(MENU_ID_I2C_SlaveAddress, MainFrame::OnI2CSlaveAddress)
EVT_MENU(MENU_ID_Enable_ALL, MainFrame::OnEnableAll)
EVT_MENU(MENU_ID_Disable_ALL, MainFrame::OnDisableAll)
EVT_MENU(MENU_ID_Increase_CPU_Overhead, MainFrame::OnIncreaseCPUOverhead)
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
EVT_MENU(MENU_ID_READ_TEST, MainFrame::OnReadTest)
EVT_MENU(MENU_ID_WRITE_TEST, MainFrame::OnWriteTest)
EVT_MENU(MENU_ID_BLOCK_WR_TEST, MainFrame::OnBlockWRTest)
EVT_MENU(MENU_ID_FRU_MAKER, MainFrame::OnFRUMaker)
EVT_MENU(MENU_ID_FRU_WRITER, MainFrame::OnFRUWriter)
EVT_MENU(MENU_ID_ABOUT, MainFrame::OnAbout)
EVT_MENU(MENU_ID_ACBEL_WEBSITE, MainFrame::OnAcbelWebSite)

EVT_MENU(wxID_EXIT, MainFrame::OnExit)
//EVT_DATAVIEW_ITEM_ACTIVATED(CID_CMDLIST_DVC, MainFrame::OnDVItemActivated)
EVT_DATAVIEW_SELECTION_CHANGED(CID_CMDLIST_DVC, MainFrame::OnDVSelectionChanged)
//EVT_DATAVIEW_ITEM_EDITING_DONE(CID_CMDLIST_DVC, MainFrame::OnDVValueChanged)
EVT_DATAVIEW_ITEM_CONTEXT_MENU(CID_CMDLIST_DVC, MainFrame::OnContextMenu)
EVT_COMBOBOX(ID_POLLING_TIME_COMBO, MainFrame::OnPollingTimeCombo)
EVT_BUTTON(CID_SLAVE_ADDRESS_SET_BUTTON, MainFrame::OnSlaveAddressSetButton)

EVT_TIMER(wxID_ANY, MainFrame::OnInfoBarTimer)

EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_START, MainFrame::OnSendThreadStart)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE, MainFrame::OnSendThreadUpdate)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_RAW, MainFrame::OnSendThreadUpdateRaw)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_QUERY, MainFrame::OnSendThreadUpdateQuery)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS, MainFrame::OnSendThreadUpdateCoefficients)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_COOK, MainFrame::OnSendThreadUpdateCook)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_COMPLETED, MainFrame::OnSendThreadCompletion)

EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_CMDNAME, MainFrame::OnSendThreadUpdateCMDName)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_SUMMARY, MainFrame::OnSendThreadUpdateSummary)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_STDPAGE, MainFrame::OnSendThreadUpdateSTDPage)
EVT_THREAD(wxEVT_COMMAND_SENDTHREAD_UPDATE_STATUSPAGE, MainFrame::OnSendThreadUpdateSTATUSPage)

EVT_THREAD(wxEVT_COMMAND_MONITOR_START, MainFrame::OnMonitorStart)
EVT_THREAD(wxEVT_COMMAND_ISP_SEQUENCE_START, MainFrame::OnISPSequenceStart)
//EVT_THREAD(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, MainFrame::OnISPSequenceInterrupt)

EVT_THREAD(wxEVT_COMMAND_QUERY_SEQUENCE_START, MainFrame::OnQUERYSequenceStart)
EVT_THREAD(wxEVT_COMMAND_FIND_I2C_SLAVE_START, MainFrame::OnFindI2CSlaveStart)

EVT_UPDATE_UI(CID_CMDLIST_DVC, MainFrame::OnUpdateUI)
EVT_IDLE(MainFrame::OnIdle)

EVT_THREAD(wxEVT_IOTHREAD_REQ_PAUSE, MainFrame::OnIOThreadReqPause)
EVT_THREAD(wxEVT_IOTHREAD_REQ_RESUME, MainFrame::OnIOThreadReqResume)

EVT_CLOSE(MainFrame::OnWindowClose)
wxEND_EVENT_TABLE()

