/**
 * @file PMBUSFWProgressDialog.h
 */
#ifndef _PMBUSFWPROGRESSDIALOG_H_
#define _PMBUSFWPROGRESSDIALOG_H_

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

class PMBUSFWProgressDialog : public wxDialog, private wxLog
{
public:
	PMBUSFWProgressDialog(wxWindow *parent, wxString title, int range);

	~PMBUSFWProgressDialog();

	bool Update(int value, const wxString& newmsg = wxEmptyString, bool *skip = NULL);

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;


private:
	
	wxLog *m_oldLog;

	wxBoxSizer *m_topLevelSizer;

	wxGauge *m_gauge;

	wxButton *m_okCancelButton;

	PMBUSLogTextCtrl *m_logTC;

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	wxDECLARE_EVENT_TABLE();

};

#endif
 