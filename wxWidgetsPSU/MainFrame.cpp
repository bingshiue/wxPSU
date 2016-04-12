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
	this->m_parent = new wxPanel(this, wxID_ANY);
	this->m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	this->m_hbox = new wxBoxSizer(wxHORIZONTAL);
	this->m_SendButton = new wxButton(this->m_parent, CID_SEND_BUTTON, L"Send");

	this->m_hbox->Add(this->m_SendButton, 1, wxEXPAND | wxALL, 1);
	this->m_topLevelSizer->Add(this->m_hbox, 1, wxEXPAND | (wxALL & ~wxLEFT), 1);
	this->m_parent->SetSizer(this->m_topLevelSizer, true);

	// Setup Icon
	SetIcon(sample_xpm);

	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("PSU Tool");

	Connect(ID_Hello, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnHello));
	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnAbout));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnExit));
	Connect(CID_SEND_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnSend));

	// Log : Set Active Target 
	wxLog::SetActiveTarget(new wxLogStderr());
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

void MainFrame::OnSend(wxCommandEvent& event)
{
	wxLogMessage("On Send");
	int loop = 0;

	while (loop < 2) {
		Sleep(500);// Sleep 500ms
		wxLogMessage("loop=%d \n",loop);
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
	};
}