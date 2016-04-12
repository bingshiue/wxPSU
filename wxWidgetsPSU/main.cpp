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
#include "SerialPortReadThread.h"
#include "SerialPort.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	BOOL ret;
	
	MainFrame *mainFrame = new MainFrame("PSU Tool", wxPoint(50, 50), wxSize(450, 340));
	mainFrame->Show(true);

	// Initial Serial Port
	ret = OpenSerialPort(3);

	// If Open Serial Port Success
	if (ret==EXIT_SUCCESS){

		// Create SerialReadThread
		SerialReadThread* sprt = new SerialReadThread();

		// If Create Thread Success
		if (sprt->Create() != wxTHREAD_NO_ERROR){
			wxLogError(wxT("Can't create thread!"));
		}
		else{
			sprt->Run();
		}
	}

	return true;
}
