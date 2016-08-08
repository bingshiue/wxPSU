/**
 * @file USBSPICANPanel.h
 */
#ifndef _USBSPICANPANEL_H_
#define _USBSPICANPANEL_H_

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

class USBSPICANPanel : public wxPanel {
public:
	/**
	* @brief Constructor.
	*/
	USBSPICANPanel(wxWindow* parent);
	/**
	* @brief Deconstructor.
	*/
	~USBSPICANPanel();

	wxBoxSizer *m_topLevelSizer;
	wxFlexGridSizer* m_fgSizer1;
	wxFlexGridSizer* m_fgSizer2;
	wxStaticBoxSizer *m_spiPortSB;
	wxStaticBoxSizer *m_canPortSB;

	wxStaticText *m_spiRecvBuffSizeST;
	wxTextCtrl *m_spiRecvBuffSizeTC;

	wxStaticText *m_spiRecvTimeoutST;
	wxTextCtrl *m_spiRecvTimeoutTC;

	wxStaticText *m_spiBitRateSpeedST;
	wxComboBox *m_spiBitRateSpeedCB;

	//
	wxStaticText *m_canRecvBuffSizeST;
	wxTextCtrl *m_canRecvBuffSizeTC;

	wxStaticText *m_canRecvMSGSizeST;
	wxTextCtrl *m_canRecvMSGSizeTC;

	wxStaticText *m_canRecvTimeoutST;
	wxTextCtrl *m_canRecvTimeoutTC;

	wxStaticText *m_canBitRateSpeedST;
	wxComboBox *m_canBitRateSpeedCB;

private:

	wxDECLARE_EVENT_TABLE();

};

#endif