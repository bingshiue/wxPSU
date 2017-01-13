/**
 * @file USBInfoPanel.h
 */

#ifndef _USBINFOPANEL_H_
#define _USBINFOPANEL_H_

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

#include "PMBUSHelper.h"

class USBInfoPanel : public wxPanel {
public:
	/**
	* @brief Constructor.
	*/
	USBInfoPanel(wxWindow* parent);
	/**
	* @brief Deconstructor.
	*/
	~USBInfoPanel();

	wxBoxSizer *m_topLevelSizer;
	wxBoxSizer *m_horizon1;
	wxBoxSizer *m_horizon2;
	wxBoxSizer *m_horizon3;
	wxBoxSizer *m_horizon4;
	wxBoxSizer *m_horizon5;
	wxFlexGridSizer* m_fgSizer1;

	wxStaticText* m_VIDST;
	wxTextCtrl* m_VIDTC;

	wxStaticText* m_PIDST;
	wxTextCtrl* m_PIDTC;

	wxStaticLine* m_st1;

	wxStaticText* m_comport0IDST;
	wxTextCtrl* m_comport0IDTC;

	wxStaticText* m_comport1IDST;
	wxTextCtrl* m_comport1IDTC;

	wxStaticText* m_comport2IDST;
	wxTextCtrl* m_comport2IDTC;

	wxStaticText* m_comport3IDST;
	wxTextCtrl* m_comport3IDTC;

	wxStaticText* m_i2cportIDST;
	wxTextCtrl* m_i2cportIDTC;

	wxStaticText* m_spiportIDST;
	wxTextCtrl* m_spiportIDTC;

	wxStaticText* m_canportIDST;
	wxTextCtrl* m_canportIDTC;

	wxStaticText* m_sdqportIDST;
	wxTextCtrl* m_sdqportIDTC;

	wxStaticText* m_gpioInST;
	wxTextCtrl* m_gpioInTC;

	wxStaticText* m_gpioOutST;
	wxTextCtrl* m_gpioOutTC;

	wxStaticLine* m_st2;

	wxStaticText* m_VendorIDST;
	wxTextCtrl* m_VendorIDTC;

	wxStaticText* m_ProductIDST;
	wxTextCtrl* m_ProductIDTC;

	wxStaticText* m_VendorNameST;
	wxTextCtrl* m_VendorNameTC;

	wxStaticText* m_ProductNameST;
	wxTextCtrl* m_ProductNameTC;

	wxStaticText* m_versionST;
	wxTextCtrl* m_versionTC;

	wxStaticLine* m_st3;


private:

	wxDECLARE_EVENT_TABLE();

};

#endif