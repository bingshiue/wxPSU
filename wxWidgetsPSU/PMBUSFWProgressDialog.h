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

	enum {
		CID_BTN_CANCELOK = 6060,
	};

	PMBUSFWProgressDialog(wxWindow *parent, wxString title, int range, unsigned char* ispStatus);

	~PMBUSFWProgressDialog();

	bool Update(int value, const wxString& newmsg = wxEmptyString, bool *skip = NULL);

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;


private:

	wxStaticText *m_infoST;

	wxLog *m_oldLog;

	wxBoxSizer *m_topLevelSizer;

	wxGauge *m_gauge;

	wxButton *m_okCancelButton;

	PMBUSLogTextCtrl *m_logTC;

	unsigned char* m_ispStatus;

#if wxUSE_TIMER
	wxTimer m_timer;
#endif

	wxDateTime m_beginTime;

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void OnISPSequenceUpdate(wxThreadEvent& event);
	void OnISPSequenceEnd(wxThreadEvent& event);

	void OnBtnCancelOK(wxCommandEvent& event);

	void OnDialogClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();

};

#endif
 