/**
 * @file MainFrame.h
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

#include "main.h"

enum {
	CID_SEND_BUTTON = 101,
};

enum
{
	ID_Hello = 1,
	ID_Monitor
};

class MainFrame : public wxFrame, private wxLog
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MainFrame();
	//wxPanel* m_parent;/**< Parent Panel */
	wxSizer* m_topVeriticalSizer;/**< Top Level Sizer */
	wxSizer* m_hbox;/**< Horizontal Sizer */
	wxButton* m_SendButton;/**< Send Button */

	//
	wxGrid *m_grid;
	wxGridTableBase *m_table;
	//

	// just some place to put our messages in
	wxTextCtrl *m_txtctrl;

	// old log target, we replace it with one using m_txtctrl during this
	// frame life time
	wxLog *m_oldLogger;

	/**
	* @brief Semaphore used for synchronize RX/TX.
	*/
	wxSemaphore m_rxTxSemaphore;

protected:
	virtual void DoLogRecord(wxLogLevel level,
		const wxString& msg,
		const wxLogRecordInfo& info) wxOVERRIDE;

private:
	void OnHello(wxCommandEvent& event);
	void OnMonitor(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSend(wxCommandEvent& event);
	// logging helper
	void DoLogLine(wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

#if 0
	wxDECLARE_EVENT_TABLE();
#endif
};

#if 0
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
#endif

#endif