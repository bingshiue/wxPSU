/**
 * @file MainFrame.h
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

#include <iostream>
#include <iomanip>
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
#include "IOAccess.h"
#include "PMBusDataViewListModel.h"
#include "PMBUSStatusBar.h"
#include "PMBUSCommandType.h"
#include "STDPage.h"
#include "BaseWritePage.h"
#include "PMBUSCMDWritePages.h"
#include "PMBUSStatusPanel.h"
#include "PMBUSStatusDCHPanel.h"
#include "PMBUSHelper.h"
#include "CalibrationDialog.h"
#include "AboutDialog.h"

#define DEFAULT_WINDOW_WIDTH   864
#define DEFAULT_WINDOW_HEIGHT  660

#define SERIALPORT_RECV_BUFF_SIZE  256

enum {
	CID_SEND_BUTTON = 101,
};

enum
{
	MENU_ID_Secondary_Firmware = 1,
	MENU_ID_Monitor,

	MENU_ID_Update_Secondary_Firmware,
	MENU_ID_Stop_Programming,
	MENU_ID_I2C_Fault_Test,
	MENU_ID_Enable_Checksum,
	MENU_ID_Clear_Error_Log,
	MENU_ID_Reset_MaxMin_Value,
	MENU_ID_Reset_Run_Time,

	MENU_ID_EnableCalibration,
	MENU_ID_DisableCalibration,
	MENU_ID_Calibration,

	MENU_ID_Administrant,
	MENU_ID_I2C_Interface,

	MENU_ID_Enable_ALL,
	MENU_ID_Disable_ALL,

	MENU_ID_Continually,
	MENU_ID_Iterations,
	MENU_ID_Stop_An_Error,

	MENU_ID_ErrorLog_ALL,
	MENU_ID_ErrorLog_ErrorOnly ,
	MENU_ID_Log_To_File,

	MENU_ID_PMBUS_1_1,
	MENU_ID_PMBUS_1_2,

	MENU_ID_POPUP_FONT,
	MENU_ID_POPUP_PRINT_SCREEN,

	TOOLBAR_ID_RESET_RUN_TIME,
	TOOLBAR_ID_REFRESH_MAXMIN,

	ID_ATTR_CTRL = 51,

	ID_TOOLBAR = 500,
	CID_CHECKBOX_A2,
	CID_CHECKBOX_A1,
	CID_CHECKBOX_A0,

	ID_POLLING_TIME_COMBO = 1000,

	SplitterWindowID,
	SplitterWindowTopLevelID
};

class MainFrame : public wxFrame, private wxLog
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MainFrame();

	IOACCESS m_IOAccess[IO_SIZE];
	PMBUSCOMMAND_t m_PMBusData[PMBUSCOMMAND_SIZE];/**< PM Bus Data */

	AppSettings_t m_appSettings;

	bool m_ioDeviceOpen;/**< Indicator for IO Device Open */
	bool m_monitor_running;/**< Indicator for mobitor is running */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

	IOPortReadCMDThread *m_IOPortReadCMDThread;/**< Handle of IO Port Read Command Thread */
	IOPortSendCMDThread *m_IOPortSendCMDThread;/**< Handle of IO Port Send Command Thread */

	TaskSystemThread *m_TaskSystemThread;/**< Handle of Task System Thread */

	bool m_sendThreadStopFlag;

	unsigned char m_destroying;

	RECVBUFF_t m_IOPortRecvBuff;/**< Receive Data Buffer */

	vector<PMBUSSendCOMMAND_t> m_sendCMDVector; /**< Vectorfor Send Write CMD */

	// Splitter Window
	wxSplitterWindow* m_splitterWindow;
	wxSplitterWindow* m_splitterWindowTopLevel;

	// Bitmap 
	wxBitmap *m_monitorBitmap;
	wxBitmap *m_pauseBitmap;

	//wxPanel* m_parent;/**< Parent Panel */
	wxSizer* m_topVeriticalSizer;/**< Top Level Sizer */
	wxSizer* m_hbox;/**< Horizontal Sizer */

	wxSizer *GeneralPanelTopLevelSizer;
	wxSizer *GeneralPanelSz;

	wxSizer* CMDListSizer;

	wxStaticBoxSizer* m_debugLogStaticBoxSizer;

	//
#if 0
	wxGrid *m_grid;
	wxGridTableBase *m_table;
#endif
	//

	//
	wxDataViewCtrl *m_dataViewCtrl;
	wxObjectDataPtr<PSUDataViewListModel> m_list_model;

	wxDataViewColumn* m_attributes;

	// Error Log
	wxTextCtrl *m_debugLogTC;

	// Note Book
	wxNotebook *m_notebook;
	wxNotebook *m_subNotebook;

	// Panel
	wxPanel    *GeneralPanel;
	wxPanel    *CMDListPanel;
	wxPanel    *DebugLogPanel;

	PMBUSStatusPanel  *PMBusStatusPanel;
	PMBUSStatusDCHPanel  *PMBusStatusDCHPanel;

	wxPanel    *PMBusMFR;
	wxPanel    *VerificationPanel;
	wxPanel    *STATUSPanel;

	//wxPanel    *STDPanel;
	STDPage    *m_stdPage;
	wxPanel    *ReadPanel;
	BaseWritePage  *m_writePage;

	// Menu Bar
	wxMenuBar   *m_menuBar;

	wxMenu      *m_fileMenu;
	
	wxMenu      *m_hexToBinMenu;
	
	wxMenu      *m_runMenu;

	wxMenuItem  *m_monitorMenuItem;
	wxMenu      *m_inSystemProgrammingMenu;
	wxMenuItem  *m_updateSecondaryFirmwareMenuItem;
	wxMenuItem  *m_stopProgrammingMenuItem;
	wxMenuItem  *m_i2cFaultTestMenuItem;
	wxMenuItem  *m_EnableChecksumMenuItem;
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

	wxMenu      *m_helpMenu;

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

	unsigned int getCurrentUseIOInterface(void);
	unsigned int findPMBUSCMDIndex(unsigned int cmd_register);

	TASKINITFUNCTION m_taskInitFunc;
	void TaskInit(void);

protected:
	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:

	unsigned int m_CurrentUseIOInterface;/**< Current Use IO Interface */
	unsigned int m_polling_time;/**< Polling Time for Running PM Bus Command */

	void SetupPMBusCommandData(void);
	void SetupPMBusCommandWritePage(void);

	void SetupMenuBar(void);
	void SetupToolBar(void);
	void SetupStatusBar(void);
	void SetupPSUDataView(wxPanel* parent);

	void OnSecondaryFirmwarwe(wxCommandEvent& event);
	void OnMonitor(wxCommandEvent& event);
	void OnUpdateSecondaryFirmware(wxCommandEvent& event);
	void OnStopProgramming(wxCommandEvent& event);
	void OnI2CFaultTest(wxCommandEvent& event);
	void OnEnableChecksum(wxCommandEvent& event);
	void OnClearErrorLog(wxCommandEvent& event);
	void OnResetMaxMinValue(wxCommandEvent& event);
	void OnResetRunTime(wxCommandEvent& event);
	void OnEnableCalibration(wxCommandEvent& event);
	void OnDisableCalibration(wxCommandEvent& event);
	void OnCalibration(wxCommandEvent& event);

	void OnAdministrant(wxCommandEvent& event);
	void OnI2CInterface(wxCommandEvent& event);

	void OnDisableAll(wxCommandEvent& event);
	void OnEnableAll(wxCommandEvent& event);

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

	void OnAbout(wxCommandEvent& event);

	void OnValueChanged(wxDataViewEvent &event);
	void OnDVSelectionChanged(wxDataViewEvent &event);

	void OnPollingTimeCombo(wxCommandEvent& event);

	void OnContextMenu(wxDataViewEvent &event);

	void OnSendThreadCompletion(wxThreadEvent& event);

	void OnSendThreadUpdate(wxThreadEvent& event);

	// logging helper
	void DoLogLine(wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void DoSetupIOAccess(void);

	int OpenIODevice(void);
	int CloseIODevice(void);

	void UpdateStatusBarIOSettingFiled(wxString io_string);

	int SaveCMDListToFile(wxTextOutputStream& textOutputStream);

	wxDECLARE_EVENT_TABLE();

};

#endif