#ifndef _FRU_WRITER_DIALOG_H_
#define _FRU_WRITER_DIALOG_H_

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
#include "IOACCESS.h"
#include "PMBUSHelper.h"
#include "PMBUSLogTextCtrl.h"
#include "Task.h"
#include "version.h"

#define MAX_FRU_FILE_SIZE  256 // Max FRU File Size 

class FRUWriterDialog : public wxDialog, private wxLog
{
public:
	FRUWriterDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO);

	~FRUWriterDialog();

	enum {
		CID_BTN_LOAD, /**< Load Button */
		CID_BTN_READ, /**< Read Button */
		CID_BTN_WRITE /**< Write Button */
	};

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

	bool m_outputLog;

	wxLog* m_oldLog;

	bool outputLog;
	int wirteIntervalTime;
	int readIntervalTime;

	unsigned int m_fruFileLength;

	unsigned char m_fruBinaryContent[MAX_FRU_FILE_SIZE];

	//unsigned char m_e2pRomContent[MAX_FRU_FILE_SIZE];

	bool m_preWriteBTNEnable;

	// Sizer
	wxBoxSizer *m_topLevelSizer;
	wxStaticBoxSizer *m_e2pROMSBS;
	wxBoxSizer *m_e2pROMLine1Sizer;
	wxBoxSizer *m_e2pROMLine2Sizer;
	wxBoxSizer *m_btnSizer;

	// Components
	wxStaticText *m_e2pROMSlaveAddrST;
	wxStaticText *m_fruFileST;
	wxBitmapButton *m_floppyLoadBB;

	wxTextCtrl *m_e2pROMSlaveAddrTC;
	wxTextCtrl *m_fruFileTC;

	wxStaticLine *m_stline1;
	wxStaticLine *m_stline2;

	PMBUSLogTextCtrl *m_logTC;

	// Button
	wxButton *m_btnREAD;
	wxButton *m_btnWRITE;

	// TextValidator
	wxString DecCharIncludes;
	wxString HexCharIncludes;
	wxTextValidator m_hexValidator;
	wxTextValidator m_decValidator;

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void OnBtnLOAD(wxCommandEvent& event);
	void OnBtnREAD(wxCommandEvent& event);
	void OnBtnWRITE(wxCommandEvent& event);
	void OnDialogClose(wxCloseEvent& event);

	void OnE2PRomWriteEnd(wxThreadEvent& event);
	void OnE2PRomReadEnd(wxThreadEvent& event);
	void OnE2PRomWriteInterrupt(wxThreadEvent& event);
	void OnE2PRomReadInterrupt(wxThreadEvent& event);

	wxDECLARE_EVENT_TABLE();

};

#endif