/**
 * @file I2CInterfaceDialog.h
 */
#ifndef _I2CINTERFACEDIALOG_H_
#define _I2CINTERFACEDIALOG_H_

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
#include "PMBUSStatusBar.h"
#include "ComportDialog.h"

class I2CInterfaceDialog : public wxDialog
{
public:
	enum {
		CID_OK_BUTTOUN      = 7001,
		CID_CANCEL_BUTTON,
		CID_COMPORT_BUTTOUN,
	};

	I2CInterfaceDialog(wxWindow *parent, IOACCESS* ioaccess, unsigned int* currentUseIO, AppSettings_t* appSettings, PMBUSStatusBar* pmbusStatusBar);

	~I2CInterfaceDialog();

	IOACCESS *m_ioaccess;
	unsigned int *m_currentUseIO;
	PORT_SETTING_t m_portSetting;
	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];
	AppSettings_t *m_appSettings;
	PMBUSStatusBar *m_pmbusStatusBar;

	wxBoxSizer *m_TopLevelSizer;
	wxBoxSizer *m_LeftSizer;

	wxStaticBoxSizer *m_i2cIFModuleSBS;

	wxFlexGridSizer *m_generalFlexSizer;
	wxBoxSizer *m_ButtonSizer;

	wxStaticText *m_moduleNameST;
	wxComboBox *m_moduleNameCB;

	wxNotebook *m_generalNB;
	wxPanel *m_generalPanel;

	wxStaticText *m_RegisterAddrLengthST;
	wxStaticText *m_MaxReadBytesST;
	wxStaticText *m_MaxWriteBytesST;
	wxStaticText *m_TrasmitTimeoutST;
	wxStaticText *m_WriteCycleTimeST;
	wxStaticText *m_PollingCycleTimeST;

	wxComboBox *m_RegisterAddrLengthCB;
	wxComboBox *m_MaxReadBytesCB;
	wxComboBox *m_MaxWriteBytesCB;
	wxComboBox *m_TrasmitTimeoutCB;
	wxComboBox *m_WriteCycleTimeCB;
	wxComboBox *m_PollingCycleTimeCB;

	wxButton *m_OkButton;
	wxButton *m_CancelButton;
	wxButton *m_ComportButton;
	wxButton *m_USBSettingButton;

private:

	void UpdateStatusBarIOSettingFiled(wxString io_string);
	int SetIODeviceOption(void);

	int OpenIODevice(void);
	int CloseIODevice(void);

	void OnOKButton(wxCommandEvent& event);
	void OnCancelButton(wxCommandEvent& event);
	void OnComportButton(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

};

#endif