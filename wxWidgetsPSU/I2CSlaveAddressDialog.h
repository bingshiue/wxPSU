/**
 * @file I2CSlaveAddressDialog.h
 */
#ifndef _I2CSLAVEADDRESSDIALOG_H_
#define _I2CSLAVEADDRESSDIALOG_H_

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
#include "wx/notebook.h"

#include "CommonDef.h"

class I2CSlaveAddressDialog : public wxDialog
{
public:
	enum {
		CID_SAVE_THEN_EXIT_BUTTOUN = 7001,

		CID_B0_CHECKBOX,
		CID_B2_CHECKBOX,
		CID_B4_CHECKBOX,
		CID_B6_CHECKBOX,
		CID_B8_CHECKBOX,
		CID_BA_CHECKBOX,
		CID_BC_CHECKBOX,
		CID_BE_CHECKBOX,
	};

	I2CSlaveAddressDialog(wxWindow *parent, AppSettings_t* appSettings);

	~I2CSlaveAddressDialog();

	wxWindow *m_parent;
	AppSettings_t *m_appSettings;

	wxTextValidator m_hexValidator;
	wxString HexCharIncludes;

	wxBoxSizer *m_topLevelSizer;
	wxBoxSizer *m_addressSizer;
	wxFlexGridSizer* m_checkBoxsFGS;

	wxStaticText *m_i2cSlaveAddressST;
	wxTextCtrl *m_i2cSlaveAddressTC;

	wxCheckBox *m_b0CheckBox;
	wxCheckBox *m_b2CheckBox;
	wxCheckBox *m_b4CheckBox;
	wxCheckBox *m_b6CheckBox;
	wxCheckBox *m_b8CheckBox;
	wxCheckBox *m_baCheckBox;
	wxCheckBox *m_bcCheckBox;
	wxCheckBox *m_beCheckBox;

	wxButton *m_saveThenExitBtn;

private:

	void OnSaveThenExitButton(wxCommandEvent& event);

	void OnB0CheckBox(wxCommandEvent& event);
	void OnB2CheckBox(wxCommandEvent& event);
	void OnB4CheckBox(wxCommandEvent& event);
	void OnB6CheckBox(wxCommandEvent& event);
	void OnB8CheckBox(wxCommandEvent& event);
	void OnBaCheckBox(wxCommandEvent& event);
	void OnBcCheckBox(wxCommandEvent& event);
	void OnBeCheckBox(wxCommandEvent& event);

	void SetCheckBoxDefaultValue(void);
	void UnCheckALL(void);

	wxDECLARE_EVENT_TABLE();

};

#endif
