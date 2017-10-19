/**
 * @file MainFrame.h
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

#ifdef _WIN32
#include <windows.h>
#include <dbt.h>
#endif

#include <wx/busyinfo.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "TaskSystemEx.h"
#include "Task.h"
#include "CommonDef.h"
#include "AppSettings.h"
#include "main.h"
#include "IOPortReadCMDThread.h"
#include "IOPortSendCMDThread.h"
#include "TaskSystemThread.h"
#include "SerialPort.h"
#include "HID.h"
#include "TotalPhase.h"
#include "Pickit.h"
#include "TRC2_I2C_Adapter.h"
#include "IOAccess.h"
#include "PMBUSCMDListModel.h"
#include "PMBUSStatusBar.h"
#include "PMBUSCommandType.h"
#include "STDPage.h"
#include "BaseWritePage.h"
#include "BaseReadPage.h"
#include "PMBUSCMDWritePages.h"
#include "PMBUSCMDReadPages.h"
#include "PMBUSMFRPanel.h"
#include "PMBUSVerificationPanel.h"
#include "PMBUSStatusPanel.h"
#include "PMBUSStatusDCHPanel.h"
#include "PMBUSFWUpdatePanel.h"
#include "PMBUSLogTextCtrl.h"
#include "PMBUSArtProv.h"
#include "CalibrationDialog.h"
#include "I2CInterfaceDialog.h"
#include "I2CSlaveAddressDialog.h"
#include "AboutDialog.h"
#include "TIHexFileParser.h"
#include "TIHexMMAPModel.h"
#include "ISPSequenceThread.h"
#include "IncreaseCPUOverHeadThread.h"
#include "ModelSelectDialog.h"
#include "PMBUSQUERYProgressDialog.h"
#include "QUERYSequenceThread.h"
#include "ReadTestDialog.h"
#include "WriteTestDialog.h"
#include "BlockWRTestDialog.h"
#include "FRUUtilityDialog.h"
#include "FRUMakerDialog.h"
#include "MFR.h"

#define DEFAULT_WINDOW_WIDTH_SCALE   0.75f /**< Default Window Width Scale */
#define DEFAULT_WINDOW_HEIGHT_SCALE  0.75f /**< Default Window Height Scale */

class MainFrame : public wxFrame, private wxLog
{
public:

	enum
	{
		MENU_ID_Primary_Firmware = 1011,
		MENU_ID_Secondary_Firmware,
		MENU_ID_Monitor,

		MENU_ID_Update_Primary_Firmware,
		MENU_ID_Update_Secondary_Firmware,
		MENU_ID_Stop_Programming,
		MENU_ID_Query_All_Commands,
		MENU_ID_Find_Available_I2C_Slave_Device,
		MENU_ID_I2C_Fault_Test,
		MENU_ID_Enable_Checksum,
		MENU_ID_Only_Polling_Support_Command,
		MENU_ID_Auto_Query_CMD_On_IO_Open,
		MENU_ID_Query_CMD_Before_Polling,
		MENU_ID_Clear_Log_Before_Monitor_Run,
		MENU_ID_Clear_Error_Log,
		MENU_ID_Reset_MaxMin_Value,
		MENU_ID_Reset_Run_Time,

		MENU_ID_EnableCalibration,
		MENU_ID_DisableCalibration,
		MENU_ID_Calibration,

		MENU_ID_Administrant,
		MENU_ID_I2C_Interface,

		MENU_ID_I2C_SlaveAddress,

		MENU_ID_Enable_ALL,
		MENU_ID_Disable_ALL,

		MENU_ID_Increase_CPU_Overhead,

		MENU_ID_Continually,
		MENU_ID_Iterations,
		MENU_ID_Stop_An_Error,

		MENU_ID_ErrorLog_ALL,
		MENU_ID_ErrorLog_ErrorOnly,
		MENU_ID_Log_To_File,

		MENU_ID_PMBUS_1_1,
		MENU_ID_PMBUS_1_2,

		MENU_ID_READ_TEST,
		MENU_ID_WRITE_TEST,
		MENU_ID_BLOCK_WR_TEST,

		MENU_ID_FRU_MAKER,
		MENU_ID_FRU_WRITER,

		MENU_ID_ABOUT,
		MENU_ID_ACBEL_WEBSITE,

		MENU_ID_POPUP_FONT,
		MENU_ID_POPUP_PRINT_SCREEN,

		TOOLBAR_ID_RESET_RUN_TIME,
		TOOLBAR_ID_REFRESH_MAXMIN,

		CID_CMDLIST_DVC = 51,

		ID_TOOLBAR = 500,
		CID_SLAVE_ADDRESS_SET_BUTTON,
		CID_CHECKBOX_A2,
		CID_CHECKBOX_A1,
		CID_CHECKBOX_A0,

		ID_POLLING_TIME_COMBO = 1000,

		SplitterWindowID,
		SplitterWindowTopLevelID,

		ID_LOG_TEXTCTRL

	};

	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, CUSTOMER_TYPE_t* customerList);
	virtual ~MainFrame();

#ifdef _WIN32
	DEV_BROADCAST_DEVICEINTERFACE dbch;
#endif

	CUSTOMER_TYPE_t* m_customerList;/**< Support Customer List */
	MODEL_TYPE_t* m_modelList;/**< Support Model List */

	PORT_SETTING_t m_portSetting;
	IOACCESS m_IOAccess[IO_SIZE];
	PMBUSCOMMAND_t *m_PMBusData;/**< PM Bus CMD Data */

	AppSettings_t m_appSettings;

	//bool m_ioDeviceOpen;/**< Indicator for IO Device Open */
	bool m_monitor_running;/**< Indicator for monitor is running */
	bool m_monitor_pause;/**< Indicator for monitor is pause */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

	IOPortReadCMDThread *m_IOPortReadCMDThread;/**< Handle of IO Port Read Command Thread */
	IOPortSendCMDThread *m_IOPortSendCMDThread;/**< Handle of IO Port Send Command Thread */

	ISPSequenceThread* m_ispSequenceThread;

	QUERYSequenceThread* m_querySequenceThread;

	TaskSystemThread *m_TaskSystemThread;/**< Handle of Task System Thread */

	IncreaseCPUOverHeadThread* m_increaseCPUOverHeadThread;

	bool m_sendThreadStopFlag;
	bool m_increaseCPUOverHeadThreadStopFlag;
	bool m_modelChangedFlag;

	unsigned char m_destroying;

	unsigned char m_ispStatus;

	RECVBUFF_t m_IOPortRecvBuff;/**< Receive Data Buffer */

	vector<PMBUSSendCOMMAND_t> m_sendCMDVector; /**< Vector for Send Write CMD */

	unsigned char m_available_i2c_slave_devices[128];/**< Available I2C Slave Address */

	// Splitter Window
	wxSplitterWindow* m_splitterWindow;
	wxSplitterWindow* m_splitterWindowTopLevel;

	wxInfoBar *m_infoBar;
	wxTimer *m_infoBarTimer;

	// Bitmap 
	wxBitmap *m_monitorBitmap;
	wxBitmap *m_pauseBitmap;

	wxBitmap *m_monitor16Bitmap;
	wxBitmap *m_pause16Bitmap;

	wxBitmap m_monitorBitmap_Instance;
	wxBitmap m_pauseBitmap_Instance;

	wxBitmap m_monitor16Bitmap_Instance;
	wxBitmap m_pause16Bitmap_Instance;

	//wxPanel* m_parent;/**< Parent Panel */
	wxSizer* m_topVeriticalSizer;/**< Top Level Sizer */
	wxSizer* m_hbox;/**< Horizontal Sizer */

	wxSizer *GeneralPanelTopLevelSizer;
	wxSizer *GeneralPanelSz;

	wxSizer* CMDListSizer;

	wxSizer* m_primaryFWMMAPPanelTopLevelSizer;
	wxSizer* m_secondaryFWMMAPPanelTopLevelSizer;

	wxStaticBoxSizer* m_debugLogStaticBoxSizer;

	wxDataViewCtrl *m_cmdListDVC;
	wxObjectDataPtr<PMBUSCMDListModel> m_cmdListModel;

	wxDataViewCtrl *m_tiHexMMAPDVC;
	wxObjectDataPtr<TIHexMMAPModel> m_tiHexMMAPModel;

	wxDataViewColumn* m_attributes;

	// Error Log
	//wxTextCtrl *m_debugLogTC;
	PMBUSLogTextCtrl* m_debugLogTC;

	// Note Book
	wxNotebook *m_notebook;
	wxNotebook *m_subNotebook;

	// Panel
	wxPanel    *GeneralPanel;
	wxPanel    *CMDListPanel;
	wxPanel    *DebugLogPanel;

	PMBUSStatusPanel *PMBusStatusPanel;
	PMBUSStatusDCHPanel *PMBusStatusDCHPanel;

	PMBUSMFRPanel *PMBusMFRPanel;
	PMBUSVerificationPanel *PMBusVerificationPanel;

	PMBUSFWUpdatePanel *PMBusPrimaryFWUpdatePanel;
	PMBUSFWUpdatePanel *PMBusSecondaryFWUpdatePanel;

	//wxPanel *PrimaryFWUpdatePanel;
	//wxPanel *SecondaryFWUpdatePanel;

	STDPage    *m_stdPage;
	wxPanel    *ReadPanel;
	BaseWritePage  *m_writePage;

	// Menu Bar
	wxMenuBar   *m_menuBar;

	wxMenu      *m_fileMenu;
	
	wxMenu      *m_hexToBinMenu;
	wxMenuItem  *m_transFWMenuItem;
	wxMenuItem  *m_transPrimaryFWMenuItem;
	wxMenuItem  *m_transSecondaryFWMenuItem;

	wxMenuItem  *m_exitMenuItem;

	wxMenu      *m_runMenu;

	wxMenuItem  *m_monitorMenuItem;
	wxMenu      *m_ispMenu;
	wxMenuItem  *m_inSystemProgrammingMenuItem;
	wxMenuItem  *m_updatePrimaryFirmwareMenuItem;
	wxMenuItem  *m_updateSecondaryFirmwareMenuItem;
	wxMenuItem  *m_stopProgrammingMenuItem;
	wxMenuItem  *m_queryAllCommandsMenuItem;
	wxMenuItem  *m_findAvailableI2CSlaveDeviceMenuItem;
	wxMenuItem  *m_i2cFaultTestMenuItem;
	wxMenuItem  *m_EnableChecksumMenuItem;
	wxMenuItem  *m_onlyPollingSupportCMDMenuItem;
	wxMenuItem  *m_autoQueryCMDOnIOOpenMenuItem;
	wxMenuItem  *m_queryCMDBeforePollingMenuItem;
	wxMenuItem  *m_clearLogBeforeMonitorRun;
	wxMenuItem  *m_ClearErrorLogMenuItem;
	wxMenuItem  *m_ResetMaxMinValueMenuItem;
	wxMenuItem  *m_ResetRunTimeMenuItem;

	wxMenu      *m_psuMenu;

	wxMenuItem  *m_EnableCalibrationMenuItem;
	wxMenuItem  *m_DisableCalibrationMenuItem;
	wxMenuItem  *m_CalibrationMenuItem;

	wxMenu      *m_optionMenu;

	wxMenuItem  *m_AdministrantMenuItem;
	wxMenuItem  *m_I2CInterfaceMenuItem;
	wxMenuItem  *m_I2CSlaveAddressMenuItem;
	wxMenuItem  *m_IncreaseCPUOverheadMenuItem;

	wxMenu      *m_runModeMenu;

	wxMenuItem  *m_continuallyMenuItem;
	wxMenuItem  *m_iterationsMenuItem;
	wxMenuItem  *m_stopAnErrorMenuItem;

	wxMenu      *m_errorLogMenu;

	wxMenuItem  *m_allMenuItem;
	wxMenuItem  *m_errorOnlyMenuItem;
	wxMenuItem  *m_logToFileMenuItem;

	wxMenu      *m_pmbusReadMethodMenu;

	wxMenuItem  *m_pmBus11MenuItem;
	wxMenuItem  *m_pmBus12MenuItem;

	wxMenu      *m_testMenu;

	wxMenuItem  *m_readTestMenuItem;
	wxMenuItem  *m_writeTestMenuItem;
	wxMenuItem  *m_blockWRTestMenuItem;

	wxMenu      *m_utilityMenu;

	wxMenuItem  *m_fruMakerMenuItem;
	wxMenuItem  *m_fruWriterMenuItem;

	wxMenu      *m_helpMenu;

	wxMenuItem  *m_aboutMenuItem;
	wxMenuItem  *m_acbelWebSiteMenuItem;

	// CMD List Popup Menu
	wxMenu      *m_cmdListPopupMenu;

	wxMenuItem  *m_popupFontMenuItem;
	wxMenuItem  *m_popupPrintScreenMenuItem;

	// Tool Bar
	wxToolBar    *m_toolbar;

	wxStaticText *m_iteration_text;
	wxTextCtrl   *m_iteration_input;

	wxStaticText *m_address_text;
	wxTextCtrl   *m_address_input;

	wxStaticText *m_polling_time_text;
	// Combo Box
	wxComboBox   *m_polling_time_combobox;


	wxButton     *m_addressSetButton;
	wxCheckBox   *m_a2_chkbox;
	wxCheckBox   *m_a1_chkbox;
	wxCheckBox   *m_a0_chkbox;

	// Status Bar
	PMBUSStatusBar *m_status_bar;

	//
	wxTextCtrl   *m_header;

	// old log target, we replace it with one using m_txtctrl during this
	// frame life time
	wxLog *m_oldLogger;

	/**
	* @brief Semaphore used for synchronize RX/TX.
	*/
	wxSemaphore *m_rxTxSemaphore;

#ifdef _WIN32
	HDEVNOTIFY NotificationHandle;
#endif

	unsigned int getCurrentUseIOInterface(void);

	//int findPMBUSCMDIndex(unsigned int cmd_register);
	unsigned int findPMBUSCMDIndex(unsigned int cmd_register, unsigned char need_changePage = 0);

	TASKINITFUNCTION m_taskInitFunc;
	void TaskInit(void);

protected:
	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

#ifdef _WIN32
	WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) wxOVERRIDE;
#endif

	TIHexFileParser m_PrimaryTIHexFileStat;
	TIHexFileParser m_SecondaryTIHexFileStat;

	//wxProgressDialog *m_progressDialog;
	PMBUSFWProgressDialog *m_pmbusProgressDialog;

	PMBUSQUERYProgressDialog *m_pmbusQUERYProgressDialog;

private:

	wxFFileOutputStream *m_logFileFFileOutputStream;
	wxTextOutputStream *m_logFileTextOutputStream;


	unsigned int m_CurrentUseIOInterface;/**< Current Use IO Interface */
	unsigned int m_polling_time;/**< Polling Time for Running PM Bus Command */
	unsigned int m_defaultI2CAddress;/**< Default I2C Address */
	unsigned int m_defaultPollingTime;/**< Default Polling Time */

	void SetupModel(void);
	void SetupPMBusCommandData(void);
	void SetupPMBusCommandWritePage(void);
	void SetupPMBusCommandReadPage(void);
	void SetupPMBUSCommandBufferProvider(void);

	void SetupMenuBar(void);
	void SetupToolBar(void);
	void SetupStatusBar(void);
	void SetupCMDListDVL(wxPanel* parent);

	void OnPrimaryFirmware(wxCommandEvent& event);
	void OnSecondaryFirmware(wxCommandEvent& event);
	void OnMonitor(wxCommandEvent& event);
	void OnUpdatePrimaryFirmware(wxCommandEvent& event);
	void OnUpdateSecondaryFirmware(wxCommandEvent& event);
	void OnStopProgramming(wxCommandEvent& event);
	void OnQueryAllCommands(wxCommandEvent& event);
	void OnFindAvailableI2CSlaveDevice(wxCommandEvent& event);
	void OnI2CFaultTest(wxCommandEvent& event);
	void OnEnableChecksum(wxCommandEvent& event);
	void OnOnlyPollingSupportCommand(wxCommandEvent& event);
	void OnAutoQueryCMDOnIOOpen(wxCommandEvent& event);
	void OnQueryCMDBeforePolling(wxCommandEvent& event);
	void OnClearLogBeforeMonitorRun(wxCommandEvent& event);
	void OnClearErrorLog(wxCommandEvent& event);
	void OnResetMaxMinValue(wxCommandEvent& event);
	void OnResetRunTime(wxCommandEvent& event);
	void OnEnableCalibration(wxCommandEvent& event);
	void OnDisableCalibration(wxCommandEvent& event);
	void OnCalibration(wxCommandEvent& event);

	void OnAdministrant(wxCommandEvent& event);
	void OnI2CInterface(wxCommandEvent& event);
	void OnI2CSlaveAddress(wxCommandEvent& event);

	void OnDisableAll(wxCommandEvent& event);
	void OnEnableAll(wxCommandEvent& event);

	void OnIncreaseCPUOverhead(wxCommandEvent& event);

	void OnContinually(wxCommandEvent& event);
	void OnIterations(wxCommandEvent& event);
	void OnStopAnError(wxCommandEvent& event);

	void OnErrorLogALL(wxCommandEvent& event);
	void OnErrorLogErrorOnly(wxCommandEvent& event);
	void OnLogToFile(wxCommandEvent& event);

	void OnPMBus1_1(wxCommandEvent& event);
	void OnPMBus1_2(wxCommandEvent& event);

	void OnPopupFont(wxCommandEvent& event);
	void OnPopupPrintScreen(wxCommandEvent& event);

	void OnExit(wxCommandEvent& event);
	void OnWindowClose(wxCloseEvent& event);

	void OnReadTest(wxCommandEvent& event);
	void OnWriteTest(wxCommandEvent& event);
	void OnBlockWRTest(wxCommandEvent& event);

	void OnFRUMaker(wxCommandEvent& event);
	void OnFRUWriter(wxCommandEvent& event);

	void OnAbout(wxCommandEvent& event);
	void OnAcbelWebSite(wxCommandEvent& event);

	void OnDVSelectionChanged(wxDataViewEvent &event);
	void OnDVValueChanged(wxDataViewEvent &event);
	void OnDVItemActivated(wxDataViewEvent &event);

	void OnPollingTimeCombo(wxCommandEvent& event);
	void OnSlaveAddressSetButton(wxCommandEvent& event);

	void OnContextMenu(wxDataViewEvent &event);

	void OnMonitorStart(wxThreadEvent& event);

	void OnSendThreadStart(wxThreadEvent& event);
	void OnSendThreadCompletion(wxThreadEvent& event);

	void OnSendThreadUpdate(wxThreadEvent& event);
	void OnSendThreadUpdateRaw(wxThreadEvent& event);
	void OnSendThreadUpdateQuery(wxThreadEvent& event);
	void OnSendThreadUpdateCoefficients(wxThreadEvent& event);
	void OnSendThreadUpdateCook(wxThreadEvent& event);

	void OnSendThreadUpdateCMDName(wxThreadEvent& event);
	void OnSendThreadUpdateSummary(wxThreadEvent& event);
	void OnSendThreadUpdateSTDPage(wxThreadEvent& event);
	void OnSendThreadUpdateSTATUSPage(wxThreadEvent& event);

	void OnISPSequenceStart(wxThreadEvent& event);
	//void OnISPSequenceInterrupt(wxThreadEvent& event);

	void OnQUERYSequenceStart(wxThreadEvent& event);
	void OnFindI2CSlaveStart(wxThreadEvent& event);

	void OnIOThreadReqPause(wxThreadEvent& event);
	void OnIOThreadReqResume(wxThreadEvent& event);

	void OnInfoBarTimer(wxTimerEvent& WXUNUSED(event));

	void CheckIfModelChange(void);

	// logging helper
	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void DoSetupIOAccess(void);

	int SetIODeviceOption(void);
	int OpenIODevice(void);
	int CloseIODevice(void);

	void UpdateStatusBarIOSettingFiled(wxString io_string);
	void UpdateStatusBarIOSettingFiled(unsigned long i2cBitRateSpeed);

	int SaveCMDListToFile(wxTextOutputStream& textOutputStream);

	void CheckAndLoadConfig(void);

	void SaveConfig(void);

	void ReInitLogFileOutputStream(wxString dirPath);

	void StartMonitor(void);
	void StopMonitor(void);

	void HexToBin(void);

#ifdef _WIN32
	void RegisterDeviceChangeNotify(void);
	void DeviceChangeHandler(unsigned int Event, unsigned Type, unsigned int pid, unsigned int vid);
#endif

	void StartInCreaseCPUOverHeadThread(void);
	void StopInCreaseCPUOverHeadThread(void);

	void DoEnableCalibration(void);
	void DoDisableCalibration(void);

	BaseWritePage* getNewWritePage(int index, int register_number);
	BaseReadPage*  getNewReadPage(int index, int register_number);

	void UpdateSTDPage(unsigned int index);
	void UpdateSTATUSPanel(unsigned int index);

	void OnUpdateUI(wxUpdateUIEvent& event);
	void OnIdle(wxIdleEvent& event);

	wxDECLARE_EVENT_TABLE();

};

#endif
