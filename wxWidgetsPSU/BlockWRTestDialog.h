/**
 * @file BlockWRTestDialog.h
 */
#ifndef _BLOCK_WR_TEST_DIALOG_H_
#define _BLOCK_WR_TEST_DIALOG_H_

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
#define MAX_WRITE_DATA_BYTES  3 /**< Max Write Data Bytes */
class BlockWRTestDialog : public wxDialog, private wxLog
{
public:
	BlockWRTestDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO);

	~BlockWRTestDialog();

	enum {
		CID_SET_COUNT_SELECT_COMBOBOX = 5801,/**< Set Count Select Combo Box */
		CID_OUTPUT_LOG_CHECKBOX,/**< Output Log CheckBox */

		CID_SET_1_WRITE_BYTES_COMBOBOX,
		CID_SET_2_WRITE_BYTES_COMBOBOX,
		CID_SET_3_WRITE_BYTES_COMBOBOX,
		CID_SET_4_WRITE_BYTES_COMBOBOX,

		CID_BTN_START,/**< Start Button */
		CID_BTN_STOP,/**< Stop Button */
	};

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

	bool m_outputLog;

	PMBUSBlockWRCMD_t m_pmbusBlockWRCMDArray[MAX_SET_COUNT];

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
	wxStaticText *m_Set1NumOfWriteBytesST;
	wxStaticText *m_Set1WriteByte1ST;
	wxStaticText *m_Set1WriteByte2ST;
	wxStaticText *m_Set1WriteByte3ST;
	wxStaticText *m_Set1NumOfReadBytesST;

	wxTextCtrl *m_Set1SlaveAddrTC;
	wxTextCtrl *m_Set1CMDTC;
	wxComboBox *m_Set1WriteBytesCB;
	wxTextCtrl *m_Set1WriteByte1TC;
	wxTextCtrl *m_Set1WriteByte2TC;
	wxTextCtrl *m_Set1WriteByte3TC;
	wxTextCtrl *m_Set1NumOfReadBytesTC;

	wxTextCtrl* m_Set1WriteByteTCArray[MAX_WRITE_DATA_BYTES];

	// Set 2
	wxStaticText *m_Set2SlaveAddrST;
	wxStaticText *m_Set2CMDST;
	wxStaticText *m_Set2NumOfWriteBytesST;
	wxStaticText *m_Set2WriteByte1ST;
	wxStaticText *m_Set2WriteByte2ST;
	wxStaticText *m_Set2WriteByte3ST;
	wxStaticText *m_Set2NumOfReadBytesST;

	wxTextCtrl *m_Set2SlaveAddrTC;
	wxTextCtrl *m_Set2CMDTC;
	wxComboBox *m_Set2WriteBytesCB;
	wxTextCtrl *m_Set2WriteByte1TC;
	wxTextCtrl *m_Set2WriteByte2TC;
	wxTextCtrl *m_Set2WriteByte3TC;
	wxTextCtrl *m_Set2NumOfReadBytesTC;

	wxTextCtrl* m_Set2WriteByteTCArray[MAX_WRITE_DATA_BYTES];

	// Set 3
	wxStaticText *m_Set3SlaveAddrST;
	wxStaticText *m_Set3CMDST;
	wxStaticText *m_Set3NumOfWriteBytesST;
	wxStaticText *m_Set3WriteByte1ST;
	wxStaticText *m_Set3WriteByte2ST;
	wxStaticText *m_Set3WriteByte3ST;
	wxStaticText *m_Set3NumOfReadBytesST;

	wxTextCtrl *m_Set3SlaveAddrTC;
	wxTextCtrl *m_Set3CMDTC;
	wxComboBox *m_Set3WriteBytesCB;
	wxTextCtrl *m_Set3WriteByte1TC;
	wxTextCtrl *m_Set3WriteByte2TC;
	wxTextCtrl *m_Set3WriteByte3TC;
	wxTextCtrl *m_Set3NumOfReadBytesTC;

	wxTextCtrl* m_Set3WriteByteTCArray[MAX_WRITE_DATA_BYTES];

	// Set 4
	wxStaticText *m_Set4SlaveAddrST;
	wxStaticText *m_Set4CMDST;
	wxStaticText *m_Set4NumOfWriteBytesST;
	wxStaticText *m_Set4WriteByte1ST;
	wxStaticText *m_Set4WriteByte2ST;
	wxStaticText *m_Set4WriteByte3ST;
	wxStaticText *m_Set4NumOfReadBytesST;

	wxTextCtrl *m_Set4SlaveAddrTC;
	wxTextCtrl *m_Set4CMDTC;
	wxComboBox *m_Set4WriteBytesCB;
	wxTextCtrl *m_Set4WriteByte1TC;
	wxTextCtrl *m_Set4WriteByte2TC;
	wxTextCtrl *m_Set4WriteByte3TC;
	wxTextCtrl *m_Set4NumOfReadBytesTC;

	wxTextCtrl* m_Set4WriteByteTCArray[MAX_WRITE_DATA_BYTES];

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
	void SetupBlockWRCMDArray(void);

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
	void OnSet1WriteBytesCB(wxCommandEvent& event);
	void OnSet2WriteBytesCB(wxCommandEvent& event);
	void OnSet3WriteBytesCB(wxCommandEvent& event);
	void OnSet4WriteBytesCB(wxCommandEvent& event);
	void OnDialogClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif