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
#include "ComportDialog.h"

class I2CInterfaceDialog : public wxDialog
{
public:
	enum {
		CID_COMPORT_BUTTOUN = 7001,
	};

	I2CInterfaceDialog(wxWindow *parent, IOACCESS* ioaccess, AppSettings_t* appSettings);

	~I2CInterfaceDialog();

	IOACCESS *m_ioaccess;
	AppSettings_t *m_appSettings;

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

	void OnComportButton(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

};

#endif