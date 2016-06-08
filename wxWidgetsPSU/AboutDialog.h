/**
 * @file AboutDialog.h
 */

#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

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

class AboutDialog : public wxDialog
{
public:
	AboutDialog(wxWindow *parent);

	~AboutDialog();

	void OnButton(wxCommandEvent& event);

	enum {
		CID_BTN_OK = 6601,
	};

private:
	
	wxBoxSizer *m_topLevelSizer;

	wxStaticBitmap *m_acbelLogoSB;

	wxStaticText *m_line1ST;
	wxStaticText *m_line2ST;
	wxStaticText *m_line3ST;
	wxStaticText *m_line4ST;
	wxStaticText *m_line5ST;
	wxStaticText *m_line6ST;

	wxStaticLine *m_sl;

	wxButton *m_btnOK;

	void OnBtnOK(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif