/**
 * @file main.cpp
 */
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/config.h"

#include "main.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(WXPSU);

bool WXPSU::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	wxSize size = wxGetDisplaySize();
	size.Scale(0.75, 0.75);

	MainFrame *mainFrame = new MainFrame("PSU Tool", wxPoint(50, 50), size);//wxSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT));
	mainFrame->Show(true);

	//wxConfigBase *pConfig = wxConfigBase::Get();
	//pConfig->SetRecordDefaults();

	//bool bFirstRunChecked = false;
	//pConfig->Read(wxT("/Controls/FirstRun"), &bFirstRunChecked);

	//if (bFirstRunChecked == true) {
		//wxMessageBox(
			//wxT("This is The Fisrt Time You Run This Pogram \n")
			//wxT(""), wxT("INFORMATION"),
			//wxICON_INFORMATION | wxOK);
	//}

	return true;
}

int WXPSU::OnExit(){

	delete wxConfigBase::Set((wxConfigBase *)NULL);

	return 0;

}
