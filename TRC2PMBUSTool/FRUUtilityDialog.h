/**
 * @file FRUUtilityDialog.h
 */
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
#include "FRU.h"
#include "IOACCESS.h"
#include "PMBUSHelper.h"
#include "PMBUSLogTextCtrl.h"
#include "Task.h"
#include "version.h"

#define MAX_FRU_FILE_SIZE  256 // Max FRU File Size 

class FRUUtilityDialog : public wxDialog, private wxLog
{
public:
	FRUUtilityDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO);

	~FRUUtilityDialog();

	enum {
		CID_BTN_LOAD, /**< Load Button */
		CID_BTN_WRITE,/**< Write Button */
		CID_BTN_READ, /**< Read Button */
		CID_BTN_SAVE_AS_FILE,/**< Save As File Button */
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

	unsigned char m_fruBinaryContent[MAX_FRU_FILE_SIZE];/**< Buffer for Save FRU Binary File Content */
	unsigned char m_e2pRomContent[MAX_FRU_FILE_SIZE];/**< Buffer For Save E2PRom Content */

	bool m_preWriteBTNEnable;
	bool m_preSaveAsFileBTNEnable;

	wxString m_ProductAreaSerialNumber;

	// Sizer
	wxBoxSizer *m_topLevelSizer;
	wxStaticBoxSizer *m_e2pROMSBS;
	wxStaticBoxSizer *m_fruWriteSBS;
	wxStaticBoxSizer *m_fruReadSBS;
	wxStaticBoxSizer *m_logSBS;
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
	wxButton *m_btnSaveAsFile;
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
	void OnBtnWRITE(wxCommandEvent& event);
	void OnBtnREAD(wxCommandEvent& event);
	void OnBtnSaveAsFile(wxCommandEvent& event);
	void OnDialogClose(wxCloseEvent& event);

	void OnE2PRomWriteEnd(wxThreadEvent& event);
	void OnE2PRomReadEnd(wxThreadEvent& event);
	void OnE2PRomWriteInterrupt(wxThreadEvent& event);
	void OnE2PRomReadInterrupt(wxThreadEvent& event);

	void dump_fru_field(const char * description, size_t offset, unsigned char * field);
	void dump_PRODUCT(struct PRODUCT_INFO *fru);
	void dump_MULTIRECORD(struct MULTIRECORD_INFO *fru);

	wxDECLARE_EVENT_TABLE();

};

#endif