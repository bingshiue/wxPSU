/**
 * @file ReadTestDialog.h
 */
#ifndef _READ_TEST_DIALOG_H_
#define _READ_TEST_DIALOG_H_

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
#include "version.h"


#define MAX_SET_COUNT  4 /**< Max Set Count */
class ReadTestDialog : public wxDialog, private wxLog
{
public:
	ReadTestDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO);

	~ReadTestDialog();

	enum {
		CID_SET_COUNT_SELECT_COMBOBOX = 5801,
		CID_OUTPUT_LOG_CHECKBOX,
		
		CID_BTN_START,
		CID_BTN_STOP,
	};

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

	bool m_outputLog;

	PMBUSReadCMD_t m_pmbusReadCMDArray[MAX_SET_COUNT];

	wxLog* m_oldLog;

	// Sizer
	wxBoxSizer *m_topLevelSizer;
	wxStaticBoxSizer *m_optionsSBS;
	wxStaticBoxSizer *m_set1SBS;
	wxStaticBoxSizer *m_set2SBS;
	wxStaticBoxSizer *m_set3SBS;
	wxStaticBoxSizer *m_set4SBS;
	wxBoxSizer *m_btnSizer;

	// Components
	wxStaticText *m_setCountSelectST;
	wxComboBox *m_setCountSelectCB;

	wxCheckBox* m_outputLogCheckBox;

	wxStaticText* m_intervalTimeST;
	wxTextCtrl* m_intervalTimeTC;
	wxStaticText* m_intervalTimeUnitST;

	// Set 1
	wxStaticText *m_Set1SlaveAddrST;
	wxStaticText *m_Set1CMDST;
	wxStaticText *m_Set1NumOfReadBytesST;

	wxTextCtrl *m_Set1SlaveAddrTC;
	wxTextCtrl *m_Set1CMDTC;
	wxTextCtrl *m_Set1NumOfReadBytesTC;

	// Set 2
	wxStaticText *m_Set2SlaveAddrST;
	wxStaticText *m_Set2CMDST;
	wxStaticText *m_Set2NumOfReadBytesST;

	wxTextCtrl *m_Set2SlaveAddrTC;
	wxTextCtrl *m_Set2CMDTC;
	wxTextCtrl *m_Set2NumOfReadBytesTC;

	// Set 3
	wxStaticText *m_Set3SlaveAddrST;
	wxStaticText *m_Set3CMDST;
	wxStaticText *m_Set3NumOfReadBytesST;

	wxTextCtrl *m_Set3SlaveAddrTC;
	wxTextCtrl *m_Set3CMDTC;
	wxTextCtrl *m_Set3NumOfReadBytesTC;

	// Set 4
	wxStaticText *m_Set4SlaveAddrST;
	wxStaticText *m_Set4CMDST;
	wxStaticText *m_Set4NumOfReadBytesST;

	wxTextCtrl *m_Set4SlaveAddrTC;
	wxTextCtrl *m_Set4CMDTC;
	wxTextCtrl *m_Set4NumOfReadBytesTC;

	wxStaticLine *m_stline1;
	wxStaticLine *m_stline2;

	PMBUSLogTextCtrl *m_logTC;

	// Button
	wxButton *m_btnSTART;
	wxButton *m_btnSTOP;

	// TextValidator
	wxString DecCharIncludes;
	wxString HexCharIncludes;
	wxTextValidator m_hexValidator;
	wxTextValidator m_decValidator;

	void EnableTextCtrlBySelect(int select);
	void DisableAllTextCtrl(void);
	void SetupReadCMDArray(void);

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void OnBtnSTART(wxCommandEvent& event);
	void OnBtnSTOP(wxCommandEvent& event);
	void OnSetCountSelectCB(wxCommandEvent& event);
	void OnOutputLogCheckBox(wxCommandEvent& event);
	void OnDialogClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif

