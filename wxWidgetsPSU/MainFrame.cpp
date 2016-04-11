/**
 * @file MainFrame.cpp
 */

#include "MainFrame.h"
#include "SerialPortReadThread.h"
#include "SerialPort.h"

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
	char data[10] = {
		0x41, // 0x41
		0x44, // 0x44
		0xb6, // 0xb6
		0x01, // 0x01
		0x0d, // 0x0d
		0x0a, // 0x0a
		0xb7, // 0xb7
		0x02, // 0x02
		0x0d, // 0x0d
		0x0a  // 0x0a
	};
	SerialSendData(data, 10);

}