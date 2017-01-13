/**
 * @file ComportDialog.h
 */
#ifndef _COMPORTDIALOG_H_
#define _COMPORTDIALOG_H_

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
#include "IOAccess.h"
#include "AppSettings.h"
#include "PMBUSStatusBar.h"

class ComportDialog : public wxDialog {
public:

	enum {
		CID_OK_BUTTOUN = 7051,
	};

	ComportDialog(wxWindow *parent, IOACCESS* ioaccess, AppSettings_t* appSettings, PMBUSStatusBar* pmbusStatusBar);

	~ComportDialog();

	wxWindow *m_parent;
	IOACCESS *m_ioaccess;
	AppSettings_t *m_appSettings;
	PMBUSStatusBar *m_pmbusStatusBar;

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];
	PORT_SETTING_t m_portSetting;

	BOOL enumArray[256];

	wxBoxSizer *m_TopLevelSizer;

	wxStaticBoxSizer *m_SettingSBS;
	wxFlexGridSizer *m_SettingFGS;

	wxBoxSizer *m_RightVerticalSizer;
	wxBoxSizer *m_ButtonSizer;
	wxBoxSizer *m_CheckBoxSizer;

	wxStaticText *m_ComportNumberST;
	wxStaticText *m_BuadRateST;
	wxStaticText *m_ParityCheckST;
	wxStaticText *m_DataBitsST;
	wxStaticText *m_StopBitsST;

	wxComboBox *m_ComportNumberCB;
	wxComboBox *m_BuadRateCB;
	wxComboBox *m_ParityCheckCB;
	wxComboBox *m_DataBitsCB;
	wxComboBox *m_StopBitsCB;

	wxButton *m_OKButton;
	wxButton *m_CancelButton;

	wxStaticText *m_paddiingST;
	wxCheckBox *m_TurnOnRTS;
	wxCheckBox *m_TurnOnDTR;

private:

	void UpdateStatusBarIOSettingFiled(wxString io_string);
	int SetIODeviceOption(void);
	int OpenIODevice(void);
	int CloseIODevice(void);

	void OnOKButton(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif