/**
 * @file main.cpp
 */
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/config.h"

#include "version.h"
#include "main.h"
#include "MainFrame.h"
#include "CustomerList.h"
#include "ModelList.h"

wxIMPLEMENT_APP(WXPSU);

bool WXPSU::OnInit()
{	
	/* Single Instance Check */
	this->m_singleInstanceChecker = new wxSingleInstanceChecker;

	if (this->m_singleInstanceChecker->IsAnotherRunning() == true){

		wxMessageBox(wxT("Another program instance is already running, aborting."),
			wxT("Error !"),  // caption
			wxOK | wxICON_ERROR);

		delete this->m_singleInstanceChecker;
		this->m_singleInstanceChecker = NULL;

		return false;
	}
	
	if (!wxApp::OnInit())
		return false;

	wxSize size = wxGetDisplaySize();
	size.Scale(0.75, 0.75);

	// Model Selection

	ModelSelectDialog* modelSelectDialog = new ModelSelectDialog(NULL, g_CustomerList, CUSTOMER_LIST_SIZE);
	modelSelectDialog->CenterOnScreen();
	int msRetValue = modelSelectDialog->ShowModal();
	
	if (msRetValue == wxID_CANCEL){
		delete modelSelectDialog;
		return false;
	}

	delete modelSelectDialog;

	/* Window Title */
	wxString winTitle(wxT("PSU Tool "));
	winTitle += wxT(VERSION_STRING);

	MainFrame *mainFrame = new MainFrame(winTitle, wxPoint(50, 50), size, g_CustomerList);
	
	mainFrame->Show(true);
	
	return true;
}

int WXPSU::OnExit(){

	delete this->m_singleInstanceChecker;

	return 0;

}
