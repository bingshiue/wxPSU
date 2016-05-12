/**
 * @file MainFrame.h
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

#include "CommonDef.h"
#include "main.h"
#include "IOPortReadCMDThread.h"
#include "IOPortSendCMDThread.h"
#include "SerialPort.h"
#include "HID.h"
#include "IOAccess.h"
#include "PMBusDataViewListModel.h"
#include "PSUStatusBar.h"
#include "PMBUSCommandType.h"

#define DEFAULT_WINDOW_WIDTH   864
#define DEFAULT_WINDOW_HEIGHT  660

#define SERIALPORT_RECV_BUFF_SIZE  256

enum {
	CID_SEND_BUTTON = 101,
};

enum
{
	ID_HEX_TO_BIN = 1,
	ID_Monitor,

	ID_Enable_ALL,
	ID_Disable_ALL,

	ID_ATTR_CTRL = 51,

	ID_TOOLBAR = 500,
	CID_CHECKBOX_A2,
	CID_CHECKBOX_A1,
	CID_CHECKBOX_A0,

	ID_POLLING_TIME_COMBO = 1000
};

class MainFrame : public wxFrame, private wxLog
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MainFrame();

	IOACCESS m_IOAccess[IO_SIZE];
	PMBUSCOMMAND_t m_PMBusData[PMBUSCOMMAND_SIZE];/**< PM Bus Data */

	bool m_monitor_running;/**< Indicator for mobitor is running */

	unsigned int m_runMode = RunMode_Continally;

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

	IOPortReadCMDThread *m_IOPortReadCMDThread;/**< Handle for IO Port Read Command Thread */
	IOPortSendCMDThread *m_IOPortSendCMDThread;/**< Handle for IO Port Send Command Thread */

	RECVBUFF_t m_IOPortRecvBuff;/**< Receive Data Buffer */

	//wxPanel* m_parent;/**< Parent Panel */
	wxSizer* m_topVeriticalSizer;/**< Top Level Sizer */
	wxSizer* m_hbox;/**< Horizontal Sizer */

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

	// just some place to put our messages in
	wxTextCtrl *m_txtctrl;

	// Note Book
	wxNotebook *m_notebook;
	wxNotebook *m_subNotebook;

	// Panel
	wxPanel    *GeneralPanel;
	wxPanel    *PMBusStatusPanel;
	wxPanel    *PMBusMFR;
	wxPanel    *VerificationPanel;
	wxPanel    *STATUSPanel;

	wxPanel    *STDPanel;
	wxPanel    *ReadPanel;
	wxPanel    *WritePanel;


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
	PSUStatusBar  *m_status_bar;

	// old log target, we replace it with one using m_txtctrl during this
	// frame life time
	wxLog *m_oldLogger;

	/**
	* @brief Semaphore used for synchronize RX/TX.
	*/
	wxSemaphore *m_rxTxSemaphore;

	unsigned int getCurrentUseIOInterface(void);

protected:
	virtual void DoLogRecord(wxLogLevel level,
		const wxString& msg,
		const wxLogRecordInfo& info) wxOVERRIDE;

private:

	unsigned int m_CurrentUseIOInterface;/**< Current Use IO Interface */
	unsigned int m_polling_time;/**< Polling Time for Running PM Bus Command */

	void SetupPMBusCommandData(void);

	void SetupMenuBar(void);
	void SetupToolBar(void);
	void SetupStatusBar(void);
	void SetupPSUDataView(wxPanel* parent);

	void OnHexToBin(wxCommandEvent& event);
	void OnMonitor(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnDisableAll(wxCommandEvent& event);
	void OnEnableAll(wxCommandEvent& event);

	void OnValueChanged(wxDataViewEvent &event);
	void OnSelectionChanged(wxDataViewEvent &event);

	void OnPollingTimeCombo(wxCommandEvent& event);

	// logging helper
	void DoLogLine(wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void DoSetupIOAccess(void);

	wxDECLARE_EVENT_TABLE();

};

#endif