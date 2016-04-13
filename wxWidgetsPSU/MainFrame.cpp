/**
 * @file MainFrame.cpp
 */

#include "CommonDef.h"
#include "MainFrame.h"
#include "SerialPortReadThread.h"
#include "SerialPort.h"
#include "PMBUSCommand.h"
#include "sample.xpm"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	//this->m_parent = new wxPanel(this, wxID_ANY);
	this->m_SendButton = new wxButton(this, CID_SEND_BUTTON, L"Send");
	this->m_topVeriticalSizer = new wxBoxSizer(wxVERTICAL);
	this->m_hbox = new wxBoxSizer(wxHORIZONTAL);

	//
	m_oldLogger = wxLog::GetActiveTarget();
	
	// Setup Icon
	SetIcon(sample_xpm);

	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuRun = new wxMenu;
	menuRun->Append(ID_Monitor, "&Monitor...\tCtrl-M",
		"Start Monitor");

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuRun,  "&Run" );
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("PSU Tool");

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

	Connect(ID_Hello, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnHello));
	Connect(ID_Monitor, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnMonitor));
	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnAbout));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnExit));
	Connect(CID_SEND_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnSend));

	this->m_hbox->Add(this->m_SendButton, wxSizerFlags(1).Expand());//1, wxEXPAND | wxALL, 1);
	this->m_topVeriticalSizer->Add(this->m_hbox, wxSizerFlags(1).Expand());//1, wxEXPAND | (wxALL & ~wxLEFT), 1);
	this->m_topVeriticalSizer->Add(header, wxSizerFlags(0).Expand());
	this->m_topVeriticalSizer->Add(this->m_txtctrl, wxSizerFlags(1).Expand());
	//this->m_parent->SetSizer(this->m_topVeriticalSizer, true);
	SetSizer(this->m_topVeriticalSizer);

#if 0
	// Log : Set Active Target 
	/wxLog::SetActiveTarget(new wxLogStderr());
#endif
}

MainFrame::~MainFrame()
{
	wxLog::SetActiveTarget(m_oldLogger);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	// Close Serial Port
	CloseSerialPort();

	Close(true);
}
void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

void MainFrame::OnMonitor(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT("On Monitor");

	int loop = 0;
	int ret;

	while (loop < 2) {
		Sleep(500);// Sleep 500ms
		wxLogMessage("loop=%d", loop);
		// Send 2 Commands in turn For Loop Test
		switch (loop % 2){
		case 0:
			SerialSendData(pmbusCommand[0].mData, CMD_DATA_SIZE);
			break;

		case 1:
			SerialSendData(pmbusCommand[1].mData, CMD_DATA_SIZE);
			break;

		};

		loop++;
		// Semaphore Wait for Read Thread Complete.
		ret = m_rxTxSemaphore.WaitTimeout(1000);
		if (ret != wxSEMA_NO_ERROR){
			PSU_DEBUG_PRINT("%s: Semaphore wait timout occurs", __FUNCTIONW__);
		}
	};

	// Work Around for txtctrl can't be focus
	this->m_txtctrl->SetFocus();

}

void MainFrame::OnSend(wxCommandEvent& event)
{
	wxLogMessage("On Send");
	int loop = 0;
	int ret;

	while (loop < 2) {
		Sleep(500);// Sleep 500ms
		wxLogMessage("loop=%d",loop);
		// Send 2 Commands in turn For Loop Test
		switch (loop%2){
		case 0:
			SerialSendData(pmbusCommand[0].mData, CMD_DATA_SIZE);
			break;

		case 1:
			SerialSendData(pmbusCommand[1].mData, CMD_DATA_SIZE);
			break;

		};

		loop++;
		// Semaphore Wait for Read Thread Complete.
		ret = m_rxTxSemaphore.WaitTimeout(1000);
		if (ret != wxSEMA_NO_ERROR){
			PSU_DEBUG_PRINT("%s: Semaphore wait timout occurs",__FUNCTIONW__);
		}
	};

	// Work Around for txtctrl can't be focus
	this->m_txtctrl->SetFocus();
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