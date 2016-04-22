/**
 * @file MainFrame.h
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

#include "main.h"
#include "PMBusDataViewListModel.h"
#include "PSUStatusBar.h"

#define DEFAULT_WINDOW_WIDTH   864
#define DEFAULT_WINDOW_HEIGHT  660

enum {
	CID_SEND_BUTTON = 101,
};

enum
{
	ID_Hello = 1,
	ID_Monitor,

	ID_ATTR_CTRL = 51,

	ID_TOOLBAR = 500,
	CID_CHECKBOX_A2,
	CID_CHECKBOX_A1,
	CID_CHECKBOX_A0,

	ID_COMBO = 1000
};

enum RUNMODE {
	RunMode_Iteration = 0,
	RunMode_Continally,
	RunMode_StopAnError
};

class MainFrame : public wxFrame, private wxLog
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MainFrame();
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
	wxToolBar  *m_toolbar;

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

protected:
	virtual void DoLogRecord(wxLogLevel level,
		const wxString& msg,
		const wxLogRecordInfo& info) wxOVERRIDE;

private:

	unsigned int m_polling_time;/**< Polling Time for Running PM Bus Command */

	void SetupMenuBar(void);
	void SetupToolBar(void);
	void SetupStatusBar(void);
	void SetupPSUDataView(wxPanel* parent);

	void OnHello(wxCommandEvent& event);
	void OnMonitor(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnValueChanged(wxDataViewEvent &event);

	// logging helper
	void DoLogLine(wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	wxDECLARE_EVENT_TABLE();

};

#endif