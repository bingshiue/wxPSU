/**
 * @file PMBUSQUERYProgressDialog.h
 */
#ifndef _PMBUSQUERYPROGRESSDIALOG_H_
#define _PMBUSQUERYPROGRESSDIALOG_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>
#include <wx/artprov.h>
#include <wx/colordlg.h>
#include <wx/wfstream.h>
#include <wx/animate.h>
#include <wx/statline.h>

#include "CommonDef.h"
#include "PMBUSHelper.h"
#include "PMBUSLogTextCtrl.h"
#include "Task.h"

class PMBUSQUERYProgressDialog : public wxDialog
{
public:
	// Windows Component Enumeration 
	enum {
		CID_BTN_OK = 3060,
	};
	
	// Constructor 
	PMBUSQUERYProgressDialog(wxWindow *parent, wxString title, IOACCESS* ioaccess, unsigned int* currentIO);
	// Deconstructor
	~PMBUSQUERYProgressDialog();

	// Update Method
	bool Update(int value, const wxString& newmsg = wxEmptyString, bool *skip = NULL);

protected:

private:
	// Top Level Sizer
	wxBoxSizer *m_topLevelSizer;
	// Statistics Static Box Sizer
	wxStaticBoxSizer *m_statisticsSB;
	// Information Static Text
	wxStaticText *m_infoST;
	// OK Button
	wxButton *m_okButton;
	// IO Access
	IOACCESS* m_ioaccess;
	// Current Use I/O
	unsigned int* m_currentIO;

	// On QUERY Sequence Update Event Handler
	void OnQUERYSequenceUpdate(wxThreadEvent& event);
	// On QUERY Sequence Interrupt Event Handler
	void OnQUERYSequenceInterrupt(wxThreadEvent& event);
	// On QUERY Sequence End Event Handler
	void OnQUERYSequenceEnd(wxThreadEvent& event);

	// On Buttin OK Event Handler
	void OnBtnOK(wxCommandEvent& event);
	// On Dialog Close Event Handler
	void OnDialogClose(wxCloseEvent& event);

	// Declare Event Table
	wxDECLARE_EVENT_TABLE();
};

#endif
