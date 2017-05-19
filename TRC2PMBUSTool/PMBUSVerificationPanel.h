/**
 * @file PMBUSVerificationPanel.h
 */
#ifndef _PMBUSVERIFICATIONPANEL_H_
#define _PMBUSVERIFICATIONPANEL_H_

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

class PMBUSVerificationPanel : public wxScrolledWindow {
public:
	/**
	 * @brief Constructor.
	 */
	PMBUSVerificationPanel(wxWindow* parent);
	/**
	 * @brief Deconstructor.
	 */
	~PMBUSVerificationPanel();

	wxBoxSizer *m_topLevelSizer;
	wxBoxSizer *m_horizonBox1;
	wxBoxSizer *m_horizonBox2;

	wxStaticBoxSizer *m_configurationSBS;

	wxRadioButton *m_manualRB;
	wxRadioButton *m_automaticRB;

	wxStaticText *m_timeIntervalST;
	wxComboBox *m_timeIntervalCB;

	wxStaticText *m_userDataST;
	wxTextCtrl *m_userDataTC;
	wxButton *m_saveButton;

	wxStaticLine *m_sl;

	wxStaticText *m_loggingFileNameST;
	wxTextCtrl *m_loggingFileNameTC;

	wxBitmapButton *m_floppyLoadBB;

	wxTextCtrl *m_contentTC;

private:

	wxDECLARE_EVENT_TABLE();
};

#endif
