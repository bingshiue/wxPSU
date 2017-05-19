/**
 * @file WriteTestDialog.h
 */
#ifndef _WRITE_TEST_DIALOG_H_
#define _WRITE_TEST_DIALOG_H_

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
#include "IOAccess.h"
#include "PMBUSHelper.h"
#include "PMBUSLogTextCtrl.h"
#include "version.h"


#define MAX_SET_COUNT  4 /**< Max Set Count */
#define MAX_SEND_DATA_BYTES  5 /**< Max Send Data Bytes */
class WriteTestDialog : public wxDialog, private wxLog
{
public:
	WriteTestDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO);

	~WriteTestDialog();

	enum {
		CID_SET_COUNT_SELECT_COMBOBOX = 5801,/**< Set Count Select Combo Box */
		CID_OUTPUT_LOG_CHECKBOX,/**< Output Log CheckBox */

		CID_SET_1_SEND_BYTES_COMBOBOX,
		CID_SET_2_SEND_BYTES_COMBOBOX,
		CID_SET_3_SEND_BYTES_COMBOBOX,
		CID_SET_4_SEND_BYTES_COMBOBOX,

		CID_BTN_START,/**< Start Button */
		CID_BTN_STOP,/**< Stop Button */
	};

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

	bool m_outputLog;

	PMBUSWriteCMD_t m_pmbusWriteCMDArray[MAX_SET_COUNT];

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
	wxStaticText *m_Set1NumOfSendBytesST;
	wxStaticText *m_Set1SendByte1ST;
	wxStaticText *m_Set1SendByte2ST;
	wxStaticText *m_Set1SendByte3ST;
	wxStaticText *m_Set1SendByte4ST;
	wxStaticText *m_Set1SendByte5ST;

	wxTextCtrl *m_Set1SlaveAddrTC;
	wxTextCtrl *m_Set1CMDTC;
	wxComboBox *m_Set1SendBytesCB;
	wxTextCtrl *m_Set1SendByte1TC;
	wxTextCtrl *m_Set1SendByte2TC;
	wxTextCtrl *m_Set1SendByte3TC;
	wxTextCtrl *m_Set1SendByte4TC;
	wxTextCtrl *m_Set1SendByte5TC;

	wxTextCtrl* m_Set1SendByteTCArray[MAX_SEND_DATA_BYTES];

	// Set 2
	wxStaticText *m_Set2SlaveAddrST;
	wxStaticText *m_Set2CMDST;
	wxStaticText *m_Set2NumOfSendBytesST;
	wxStaticText *m_Set2SendByte1ST;
	wxStaticText *m_Set2SendByte2ST;
	wxStaticText *m_Set2SendByte3ST;
	wxStaticText *m_Set2SendByte4ST;
	wxStaticText *m_Set2SendByte5ST;

	wxTextCtrl *m_Set2SlaveAddrTC;
	wxTextCtrl *m_Set2CMDTC;
	wxComboBox *m_Set2SendBytesCB;
	wxTextCtrl *m_Set2SendByte1TC;
	wxTextCtrl *m_Set2SendByte2TC;
	wxTextCtrl *m_Set2SendByte3TC;
	wxTextCtrl *m_Set2SendByte4TC;
	wxTextCtrl *m_Set2SendByte5TC;

	wxTextCtrl* m_Set2SendByteTCArray[MAX_SEND_DATA_BYTES];

	// Set 3
	wxStaticText *m_Set3SlaveAddrST;
	wxStaticText *m_Set3CMDST;
	wxStaticText *m_Set3NumOfSendBytesST;
	wxStaticText *m_Set3SendByte1ST;
	wxStaticText *m_Set3SendByte2ST;
	wxStaticText *m_Set3SendByte3ST;
	wxStaticText *m_Set3SendByte4ST;
	wxStaticText *m_Set3SendByte5ST;

	wxTextCtrl *m_Set3SlaveAddrTC;
	wxTextCtrl *m_Set3CMDTC;
	wxComboBox *m_Set3SendBytesCB;
	wxTextCtrl *m_Set3SendByte1TC;
	wxTextCtrl *m_Set3SendByte2TC;
	wxTextCtrl *m_Set3SendByte3TC;
	wxTextCtrl *m_Set3SendByte4TC;
	wxTextCtrl *m_Set3SendByte5TC;

	wxTextCtrl* m_Set3SendByteTCArray[MAX_SEND_DATA_BYTES];

	// Set 4
	wxStaticText *m_Set4SlaveAddrST;
	wxStaticText *m_Set4CMDST;
	wxStaticText *m_Set4NumOfSendBytesST;
	wxStaticText *m_Set4SendByte1ST;
	wxStaticText *m_Set4SendByte2ST;
	wxStaticText *m_Set4SendByte3ST;
	wxStaticText *m_Set4SendByte4ST;
	wxStaticText *m_Set4SendByte5ST;

	wxTextCtrl *m_Set4SlaveAddrTC;
	wxTextCtrl *m_Set4CMDTC;
	wxComboBox *m_Set4SendBytesCB;
	wxTextCtrl *m_Set4SendByte1TC;
	wxTextCtrl *m_Set4SendByte2TC;
	wxTextCtrl *m_Set4SendByte3TC;
	wxTextCtrl *m_Set4SendByte4TC;
	wxTextCtrl *m_Set4SendByte5TC;

	wxTextCtrl* m_Set4SendByteTCArray[MAX_SEND_DATA_BYTES];

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
	void SetupWriteCMDArray(void);

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
	void OnSet1SendBytesCB(wxCommandEvent& event);
	void OnSet2SendBytesCB(wxCommandEvent& event);
	void OnSet3SendBytesCB(wxCommandEvent& event);
	void OnSet4SendBytesCB(wxCommandEvent& event);
	void OnDialogClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif
