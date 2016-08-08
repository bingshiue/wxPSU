/**
 * @file USBGPIOPanel.h
 */
#ifndef _USBGPIOPANEL_H_
#define _USBGPIOPANEL_H_

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

class USBGPIOPanel : public wxPanel {
public:
	/**
	* @brief Constructor.
	*/
	USBGPIOPanel(wxWindow* parent);
	/**
	* @brief Deconstructor.
	*/
	~USBGPIOPanel();

	wxBoxSizer *m_topLevelSizer;

	wxBoxSizer *m_topSectionSizer;
	wxBoxSizer *m_leftSizer;

	wxBoxSizer* m_digiInputUpSizer;
	wxBoxSizer* m_digiInputDownSizer;

	wxBoxSizer *m_rightSizer;

	wxBoxSizer *m_pwmTopLevelSizer;
	wxFlexGridSizer *m_pwmFGSizer;
	wxFlexGridSizer *m_clockInDIFGSizer;

	wxStaticBoxSizer *m_othersSB;
	wxFlexGridSizer* m_fgSizerOthers;

	/* Top Left Section */
	wxCheckBox* m_autoReportCheckBox;
	wxStaticBoxSizer* m_digitalOutputSB;

	wxStaticBitmap* m_digiOutputLight1;
	wxStaticBitmap* m_digiOutputLight2;
	wxStaticBitmap* m_digiOutputLight3;
	wxStaticBitmap* m_digiOutputLight4;
	wxStaticBitmap* m_digiOutputLight5;
	wxStaticBitmap* m_digiOutputLight6;

	wxTextCtrl* m_digiOutputTC;

	wxStaticBoxSizer* m_digitalInputSB;

	wxStaticBitmap* m_digiInputLight1;
	wxStaticBitmap* m_digiInputLight2;
	wxStaticBitmap* m_digiInputLight3;
	wxStaticBitmap* m_digiInputLight4;
	wxStaticBitmap* m_digiInputLight5;
	wxStaticBitmap* m_digiInputLight6;
	wxStaticBitmap* m_digiInputLight7;
	wxStaticBitmap* m_digiInputLight8;

	wxStaticLine *m_digiInputSL;

	wxStaticBitmap* m_digiInputLight9;
	wxStaticBitmap* m_digiInputLight10;
	wxStaticBitmap* m_digiInputLight11;
	wxStaticBitmap* m_digiInputLight12;
	wxStaticBitmap* m_digiInputLight13;
	wxStaticBitmap* m_digiInputLight14;
	wxStaticBitmap* m_digiInputLight15;
	wxStaticBitmap* m_digiInputLight16;

	/* Top Right Section */
	wxCheckBox* m_enablePWMCheckBox;

	wxStaticText* m_freqST;
	wxTextCtrl* m_freqTC;

	wxStaticText* m_dutyST;
	wxTextCtrl* m_dutyTC;

	wxBitmapButton *m_pwmWriteBB;

	wxCheckBox* m_clockInDI6CheckBox;
	wxTextCtrl* m_clockInDI6TC;

	wxCheckBox* m_clockInDI7CheckBox;
	wxTextCtrl* m_clockInDI7TC;


	/* Others Section */
	wxStaticText *m_DI0TickST;
	wxTextCtrl *m_DI0TickTC;

	wxStaticText *m_DI1TickST;
	wxTextCtrl *m_DI1TickTC;

	wxStaticText *m_DI2TickST;
	wxTextCtrl *m_DI2TickTC;

	wxStaticText *m_DI3TickST;
	wxTextCtrl *m_DI3TickTC;

	wxStaticText *m_DI4TickST;
	wxTextCtrl *m_DI4TickTC;

	wxStaticText *m_DI5TickST;
	wxTextCtrl *m_DI5TickTC;

private:

	wxDECLARE_EVENT_TABLE();

};

#endif