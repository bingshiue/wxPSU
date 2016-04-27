/**
 * @file main.cpp
 */
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "main.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{

	MainFrame *mainFrame = new MainFrame("PSU Tool", wxPoint(50, 50), wxSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT));
	mainFrame->Show(true);

	return true;
}
