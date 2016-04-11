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
	ID_Hello = 1
};

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	wxPanel* m_parent;/**< Parent Panel */
	wxSizer* m_topLevelSizer;/**< Top Level Sizer */
	wxSizer* m_hbox;/**< Horizontal Sizer */
	wxButton* m_SendButton;/**< Send Button */
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSend(wxCommandEvent& event);
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