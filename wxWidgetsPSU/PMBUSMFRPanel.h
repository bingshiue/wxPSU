/**
 * @file PMBUSMFRPanel.h
 */
#ifndef _PMBUSMFRPANEL_H_
#define _PMBUSMFRPANEL_H_

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

class PMBUSMFRPanel : public wxScrolledWindow {
public:
	/**
	 * @brief Constructor.
	 */
	PMBUSMFRPanel(wxWindow* parent);
	/**
	 * @brief Deconstructor.
	 */
	~PMBUSMFRPanel();

	wxBoxSizer *m_topLevelSizer;

	wxStaticBoxSizer *m_upSBS;

	wxBoxSizer *m_buttonSizer;
	wxBoxSizer *m_barCodeLabelSNSizer;

	wxButton *m_writeButton;
	wxButton *m_readButton;
	wxButton *m_verifyButton;

	wxStaticLine *m_sl;

	wxStaticText *m_barCodeLabelSNST;
	wxTextCtrl *m_barCodeLabelSNTC;

	wxStaticBoxSizer *m_downSBS;

	wxBoxSizer *m_mfrInfoline1Sizer;
	wxBoxSizer *m_mfrInfoline2Sizer;
	wxBoxSizer *m_mfrInfoline3Sizer;
	wxBoxSizer *m_mfrInfoline4Sizer;
	wxBoxSizer *m_mfrInfoline5Sizer;
	wxBoxSizer *m_mfrInfoline6Sizer;

	wxCheckBox *m_vendorNameCB;
	wxStaticText *m_vendorNameST;
	wxTextCtrl *m_vendorNameTC;

	wxCheckBox *m_vendorPartNumberCB;
	wxStaticText *m_vendorPartNumberST;
	wxTextCtrl *m_vendorPartNumberTC;

	wxCheckBox *m_vendorAssemblyRevisionCB;
	wxStaticText *m_vendorAssemblyRevisionST;
	wxTextCtrl *m_vendorAssemblyRevisionTC;

	wxCheckBox *m_LocationOfManufactureCB;
	wxStaticText *m_LocationOfManufactureST;
	wxTextCtrl *m_LocationOfManufactureTC;

	wxCheckBox *m_DateOfManufactureCB;
	wxStaticText *m_DateOfManufactureST;
	wxTextCtrl *m_DateOfManufactureTC;

	wxCheckBox *m_vendorSerialNumberCB;
	wxStaticText *m_vendorSerialNumberST;
	wxTextCtrl *m_vendorSerialNumbereTC;

private:

	wxDECLARE_EVENT_TABLE();
	
};

#endif