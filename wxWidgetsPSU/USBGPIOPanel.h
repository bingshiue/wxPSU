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

#include "CommonDef.h"
#include "PMBUSBitmapButton.h"
#include "USBI2CRS232Panel.h"

class USBGPIOPanel : public wxPanel {
public:
	
	enum {
		CID_DIGITAL_OUTPUT_1_BUTTON = 6060,
		CID_DIGITAL_OUTPUT_2_BUTTON,
		CID_DIGITAL_OUTPUT_3_BUTTON,
		CID_DIGITAL_OUTPUT_4_BUTTON,
		CID_DIGITAL_OUTPUT_5_BUTTON,
		CID_DIGITAL_OUTPUT_6_BUTTON,
	};

	enum {
		CID_DIGITAL_INPUT_1_BUTTON = 6080,
		CID_DIGITAL_INPUT_2_BUTTON,
		CID_DIGITAL_INPUT_3_BUTTON,
		CID_DIGITAL_INPUT_4_BUTTON,
		CID_DIGITAL_INPUT_5_BUTTON,
		CID_DIGITAL_INPUT_6_BUTTON,
		CID_DIGITAL_INPUT_7_BUTTON,
		CID_DIGITAL_INPUT_8_BUTTON,
	};

	enum {
		CID_DIGITAL_INPUT_1_POLARITY_BUTTON = 6100,
		CID_DIGITAL_INPUT_2_POLARITY_BUTTON,
		CID_DIGITAL_INPUT_3_POLARITY_BUTTON,
		CID_DIGITAL_INPUT_4_POLARITY_BUTTON,
		CID_DIGITAL_INPUT_5_POLARITY_BUTTON,
		CID_DIGITAL_INPUT_6_POLARITY_BUTTON,
		CID_DIGITAL_INPUT_7_POLARITY_BUTTON,
		CID_DIGITAL_INPUT_8_POLARITY_BUTTON,
	};

	enum {
		CID_PWM_WRITE_BUTTON = 6150,
	};

	enum {
		CID_AUTO_REPORT_CHKBOX = 6160,
		CID_ENABLE_PWM_CHKBOX,
		CID_CLOCK_IN_DI6_CHKBOX,
		CID_CLOCK_IN_DI7_CHKBOX,
	};
	
	enum {
		Polarity_Negative = 0,
		Polarity_Positive
	};
	
	/**
	* @brief Constructor.
	*/
	USBGPIOPanel(wxWindow* parent, IOACCESS* ioaccess, unsigned int* currentUseIO, USBI2CRS232Panel* usbI2CRS232Panel);
	/**
	* @brief Deconstructor.
	*/
	~USBGPIOPanel();

	USBI2CRS232Panel* m_usbI2CRS232Panel;

	wxTextValidator m_decimalValidator;
	wxTextValidator m_hexValidator;

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

	PMBUSBitmapButton* m_digiOutputLight1;
	PMBUSBitmapButton* m_digiOutputLight2;
	PMBUSBitmapButton* m_digiOutputLight3;
	PMBUSBitmapButton* m_digiOutputLight4;
	PMBUSBitmapButton* m_digiOutputLight5;
	PMBUSBitmapButton* m_digiOutputLight6;

	wxTextCtrl* m_digiOutputTC;

	wxStaticBoxSizer* m_digitalInputSB;

	wxBitmapButton* m_digiInputLight1;
	wxBitmapButton* m_digiInputLight2;
	wxBitmapButton* m_digiInputLight3;
	wxBitmapButton* m_digiInputLight4;
	wxBitmapButton* m_digiInputLight5;
	wxBitmapButton* m_digiInputLight6;
	wxBitmapButton* m_digiInputLight7;
	wxBitmapButton* m_digiInputLight8;

	wxStaticLine *m_digiInputSL;

	PMBUSBitmapButton* m_digiInputLight1_Polarity;
	PMBUSBitmapButton* m_digiInputLight2_Polarity;
	PMBUSBitmapButton* m_digiInputLight3_Polarity;
	PMBUSBitmapButton* m_digiInputLight4_Polarity;
	PMBUSBitmapButton* m_digiInputLight5_Polarity;
	PMBUSBitmapButton* m_digiInputLight6_Polarity;
	PMBUSBitmapButton* m_digiInputLight7_Polarity;
	PMBUSBitmapButton* m_digiInputLight8_Polarity;

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

	unsigned char m_digitalOutput;
	unsigned char m_digitalInput;
	unsigned char m_digitalInputPolarity;

private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentUseIO;

	wxCursor down_cursor;

	wxToolTip *m_DOB1ToolTip;
	wxToolTip *m_DOB2ToolTip;
	wxToolTip *m_DOB3ToolTip;
	wxToolTip *m_DOB4ToolTip;
	wxToolTip *m_DOB5ToolTip;
	wxToolTip *m_DOB6ToolTip;

	wxToolTip *m_DIB1ToolTip;
	wxToolTip *m_DIB2ToolTip;
	wxToolTip *m_DIB3ToolTip;
	wxToolTip *m_DIB4ToolTip;
	wxToolTip *m_DIB5ToolTip;
	wxToolTip *m_DIB6ToolTip;
	wxToolTip *m_DIB7ToolTip;
	wxToolTip *m_DIB8ToolTip;

	wxToolTip *m_DIPB1ToolTip;
	wxToolTip *m_DIPB2ToolTip;
	wxToolTip *m_DIPB3ToolTip;
	wxToolTip *m_DIPB4ToolTip;
	wxToolTip *m_DIPB5ToolTip;
	wxToolTip *m_DIPB6ToolTip;
	wxToolTip *m_DIPB7ToolTip;
	wxToolTip *m_DIPB8ToolTip;

	void SendUSBAdaptorConfigAgent(void);
	void SendUSBAdaptorParameterAgent(void);

	void OnDigitalOutputButton1(wxCommandEvent& event);
	void OnDigitalOutputButton2(wxCommandEvent& event);
	void OnDigitalOutputButton3(wxCommandEvent& event);
	void OnDigitalOutputButton4(wxCommandEvent& event);
	void OnDigitalOutputButton5(wxCommandEvent& event);
	void OnDigitalOutputButton6(wxCommandEvent& event);

	void OnDigitalInputButton1(wxCommandEvent& event);
	void OnDigitalInputButton2(wxCommandEvent& event);
	void OnDigitalInputButton3(wxCommandEvent& event);
	void OnDigitalInputButton4(wxCommandEvent& event);
	void OnDigitalInputButton5(wxCommandEvent& event);
	void OnDigitalInputButton6(wxCommandEvent& event);
	void OnDigitalInputButton7(wxCommandEvent& event);
	void OnDigitalInputButton8(wxCommandEvent& event);

	void OnDigitalInputPolarityButton1(wxCommandEvent& event);
	void OnDigitalInputPolarityButton2(wxCommandEvent& event);
	void OnDigitalInputPolarityButton3(wxCommandEvent& event);
	void OnDigitalInputPolarityButton4(wxCommandEvent& event);
	void OnDigitalInputPolarityButton5(wxCommandEvent& event);
	void OnDigitalInputPolarityButton6(wxCommandEvent& event);
	void OnDigitalInputPolarityButton7(wxCommandEvent& event);
	void OnDigitalInputPolarityButton8(wxCommandEvent& event);

	void OnPWMWriteButton(wxCommandEvent& event);

	void OnAutoReportCheckBox(wxCommandEvent& event);
	void OnEnablePWMCheckBox(wxCommandEvent& event);
	void OnDI6InClockCheckBox(wxCommandEvent& event);
	void OnDI7InClockCheckBox(wxCommandEvent& event);

	void SetDigitalInputLight(unsigned int index, unsigned char polarity);

	wxDECLARE_EVENT_TABLE();

};

#endif
