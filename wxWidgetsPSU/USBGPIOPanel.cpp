/**
 * @file USBGPIOPanel.cpp
 */

#include "USBGPIOPanel.h"

#define DEFAULT_DIGITAL_OUTPUT          0xff
#define DEFAULT_DIGITAL_INPUT           0xff
#define DEFAULT_DIGITAL_INPUT_POLARITY  0xff

#define DEFAULT_PWM_FREQUENCE     0
#define DEFAULT_PWM_DUTY         50

#define DIGITAL_OUTPUT_1_MASK  0x20
#define DIGITAL_OUTPUT_2_MASK  0x10
#define DIGITAL_OUTPUT_3_MASK  0x08
#define DIGITAL_OUTPUT_4_MASK  0x04
#define DIGITAL_OUTPUT_5_MASK  0x02
#define DIGITAL_OUTPUT_6_MASK  0x01

#define DIGITAL_INPUT_1_MASK   0x80
#define DIGITAL_INPUT_2_MASK   0x40
#define DIGITAL_INPUT_3_MASK   0x20
#define DIGITAL_INPUT_4_MASK   0x10
#define DIGITAL_INPUT_5_MASK   0x08
#define DIGITAL_INPUT_6_MASK   0x04
#define DIGITAL_INPUT_7_MASK   0x02
#define DIGITAL_INPUT_8_MASK   0x01

#define DIGITAL_INPUT_POLARITY_1_MASK   0x80
#define DIGITAL_INPUT_POLARITY_2_MASK   0x40
#define DIGITAL_INPUT_POLARITY_3_MASK   0x20
#define DIGITAL_INPUT_POLARITY_4_MASK   0x10
#define DIGITAL_INPUT_POLARITY_5_MASK   0x08
#define DIGITAL_INPUT_POLARITY_6_MASK   0x04
#define DIGITAL_INPUT_POLARITY_7_MASK   0x02
#define DIGITAL_INPUT_POLARITY_8_MASK   0x01

USBGPIOPanel::USBGPIOPanel(wxWindow* parent) : wxPanel(parent){

	/* Initial Sizer */
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);

	m_topSectionSizer = new wxBoxSizer(wxHORIZONTAL);
	
	m_leftSizer = new wxBoxSizer(wxVERTICAL);

	m_digiInputUpSizer = new wxBoxSizer(wxHORIZONTAL);
	m_digiInputDownSizer = new wxBoxSizer(wxHORIZONTAL);

	m_rightSizer = new wxBoxSizer(wxVERTICAL);
	m_pwmTopLevelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pwmFGSizer = new wxFlexGridSizer(2,2,10,10);
	m_clockInDIFGSizer = new wxFlexGridSizer(2, 2, 5, 0);

	m_othersSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Others"));
	m_fgSizerOthers = new wxFlexGridSizer(6, 2, 5, 5);

	// Setup Text Validator
	wxString DecimalCharIncludes = wxT("0123456789");
	m_decimalValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decimalValidator.SetCharIncludes(DecimalCharIncludes);

	wxString hexCharIncludes = wxT("0123456789ABCDEFabcdef");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(hexCharIncludes);

	// Member Initialize
	m_digitalOutput = 0x3f;
	m_digitalInput = DEFAULT_DIGITAL_INPUT;
	m_digitalInputPolarity = DEFAULT_DIGITAL_INPUT_POLARITY;


	/* Top Left Section */
	m_autoReportCheckBox = new wxCheckBox(this, CID_AUTO_REPORT_CHKBOX, wxT("Auto Report"));
	m_autoReportCheckBox->SetValue(PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_autoReport == 0 ? false : true);

	m_digitalOutputSB = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Digital Output"));

	m_digiOutputLight1 = new PMBUSBitmapButton(m_digitalOutputSB->GetStaticBox(), CID_DIGITAL_OUTPUT_1_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DOB1ToolTip = new wxToolTip(wxT("D/O #5"));
	m_DOB1ToolTip->Enable(true);
	m_digiOutputLight1->SetToolTip(m_DOB1ToolTip);

	m_digiOutputLight2 = new PMBUSBitmapButton(m_digitalOutputSB->GetStaticBox(), CID_DIGITAL_OUTPUT_2_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DOB2ToolTip = new wxToolTip(wxT("D/O #4"));
	m_DOB2ToolTip->Enable(true);
	m_digiOutputLight2->SetToolTip(m_DOB2ToolTip);
	
	m_digiOutputLight3 = new PMBUSBitmapButton(m_digitalOutputSB->GetStaticBox(), CID_DIGITAL_OUTPUT_3_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DOB3ToolTip = new wxToolTip(wxT("D/O #3"));
	m_DOB3ToolTip->Enable(true);
	m_digiOutputLight3->SetToolTip(m_DOB3ToolTip);
	
	m_digiOutputLight4 = new PMBUSBitmapButton(m_digitalOutputSB->GetStaticBox(), CID_DIGITAL_OUTPUT_4_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DOB4ToolTip = new wxToolTip(wxT("D/O #2"));
	m_DOB4ToolTip->Enable(true);
	m_digiOutputLight4->SetToolTip(m_DOB4ToolTip);
	
	m_digiOutputLight5 = new PMBUSBitmapButton(m_digitalOutputSB->GetStaticBox(), CID_DIGITAL_OUTPUT_5_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DOB5ToolTip = new wxToolTip(wxT("D/O #1"));
	m_DOB5ToolTip->Enable(true);
	m_digiOutputLight5->SetToolTip(m_DOB5ToolTip);
	
	m_digiOutputLight6 = new PMBUSBitmapButton(m_digitalOutputSB->GetStaticBox(), CID_DIGITAL_OUTPUT_6_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DOB6ToolTip = new wxToolTip(wxT("D/O #0"));
	m_DOB6ToolTip->Enable(true);
	m_digiOutputLight6->SetToolTip(m_DOB6ToolTip);
	
	m_digiOutputTC = new wxTextCtrl(m_digitalOutputSB->GetStaticBox(), wxID_ANY, (wxString::Format("%2x", DEFAULT_DIGITAL_OUTPUT)).Upper(), wxDefaultPosition, wxSize(40, -1));
	m_digiOutputTC->SetBackgroundColour(wxColour(255,239,133));
	m_digiOutputTC->SetMaxLength(2);
	m_digiOutputTC->SetEditable(false);
	m_digiOutputTC->SetValidator(m_hexValidator);

	m_digitalOutputSB->Add(m_digiOutputLight1, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digitalOutputSB->Add(m_digiOutputLight2, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digitalOutputSB->Add(m_digiOutputLight3, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digitalOutputSB->Add(m_digiOutputLight4, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digitalOutputSB->Add(m_digiOutputLight5, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digitalOutputSB->Add(m_digiOutputLight6, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digitalOutputSB->Add(m_digiOutputTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 2));

	m_digitalInputSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Digital Input"));

	m_digiInputLight1 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_1_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB1ToolTip = new wxToolTip(wxT("D/I #7"));
	m_DIB1ToolTip->Enable(true);
	m_digiInputLight1->SetToolTip(m_DIB1ToolTip);
	
	m_digiInputLight2 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_2_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB2ToolTip = new wxToolTip(wxT("D/I #6"));
	m_DIB2ToolTip->Enable(true);
	m_digiInputLight2->SetToolTip(m_DIB2ToolTip);
	
	m_digiInputLight3 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_3_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB3ToolTip = new wxToolTip(wxT("D/I #5"));
	m_DIB3ToolTip->Enable(true);
	m_digiInputLight3->SetToolTip(m_DIB3ToolTip);
	
	m_digiInputLight4 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_4_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB4ToolTip = new wxToolTip(wxT("D/I #4"));
	m_DIB4ToolTip->Enable(true);
	m_digiInputLight4->SetToolTip(m_DIB4ToolTip);
	
	m_digiInputLight5 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_5_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB5ToolTip = new wxToolTip(wxT("D/I #3"));
	m_DIB5ToolTip->Enable(true);
	m_digiInputLight5->SetToolTip(m_DIB5ToolTip);
	
	m_digiInputLight6 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_6_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB6ToolTip = new wxToolTip(wxT("D/I #2"));
	m_DIB6ToolTip->Enable(true);
	m_digiInputLight6->SetToolTip(m_DIB6ToolTip);
	
	m_digiInputLight7 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_7_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB7ToolTip = new wxToolTip(wxT("D/I #1"));
	m_DIB7ToolTip->Enable(true);
	m_digiInputLight7->SetToolTip(m_DIB7ToolTip);
	
	m_digiInputLight8 = new wxBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_8_BUTTON, wxBITMAP_PNG(GREENBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIB8ToolTip = new wxToolTip(wxT("D/I #0"));
	m_DIB8ToolTip->Enable(true);
	m_digiInputLight8->SetToolTip(m_DIB8ToolTip);

	m_digiInputSL = new wxStaticLine(m_digitalInputSB->GetStaticBox(), wxID_ANY);

	m_digiInputLight1_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_1_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB1ToolTip = new wxToolTip(wxT("D/I Polarity #7"));
	m_DIPB1ToolTip->Enable(true);
	m_digiInputLight1_Polarity->SetToolTip(m_DIPB1ToolTip);
	
	m_digiInputLight2_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_2_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB2ToolTip = new wxToolTip(wxT("D/I Polarity #6"));
	m_DIPB2ToolTip->Enable(true);
	m_digiInputLight2_Polarity->SetToolTip(m_DIPB2ToolTip);
	
	m_digiInputLight3_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_3_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB3ToolTip = new wxToolTip(wxT("D/I Polarity #5"));
	m_DIPB3ToolTip->Enable(true);
	m_digiInputLight3_Polarity->SetToolTip(m_DIPB3ToolTip);
	
	m_digiInputLight4_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_4_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB4ToolTip = new wxToolTip(wxT("D/I Polarity #4"));
	m_DIPB4ToolTip->Enable(true);
	m_digiInputLight4_Polarity->SetToolTip(m_DIPB4ToolTip);
	
	m_digiInputLight5_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_5_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB5ToolTip = new wxToolTip(wxT("D/I Polarity #3"));
	m_DIPB5ToolTip->Enable(true);
	m_digiInputLight5_Polarity->SetToolTip(m_DIPB5ToolTip);
	
	m_digiInputLight6_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_6_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB6ToolTip = new wxToolTip(wxT("D/I Polarity #2"));
	m_DIPB6ToolTip->Enable(true);
	m_digiInputLight6_Polarity->SetToolTip(m_DIPB6ToolTip);
	
	m_digiInputLight7_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_7_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB7ToolTip = new wxToolTip(wxT("D/I Polarity #1"));
	m_DIPB7ToolTip->Enable(true);
	m_digiInputLight7_Polarity->SetToolTip(m_DIPB7ToolTip);
	
	m_digiInputLight8_Polarity = new PMBUSBitmapButton(m_digitalInputSB->GetStaticBox(), CID_DIGITAL_INPUT_8_POLARITY_BUTTON, wxBITMAP_PNG(GRAYBALL_16), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_DIPB8ToolTip = new wxToolTip(wxT("D/I Polarity #0"));
	m_DIPB8ToolTip->Enable(true);
	m_digiInputLight8_Polarity->SetToolTip(m_DIPB8ToolTip);


	m_digiInputUpSizer->Add(m_digiInputLight1, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight2, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight3, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight4, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight5, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight6, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight7, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputUpSizer->Add(m_digiInputLight8, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));

	m_digitalInputSB->Add(m_digiInputUpSizer, wxSizerFlags(1).Expand());
	m_digitalInputSB->Add(m_digiInputSL, wxSizerFlags(0).Expand().Border());

	m_digiInputDownSizer->Add(m_digiInputLight1_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight2_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight3_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight4_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight5_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight6_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight7_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));
	m_digiInputDownSizer->Add(m_digiInputLight8_Polarity, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 1));

	m_digitalInputSB->Add(m_digiInputDownSizer, wxSizerFlags(1).Expand());

	m_leftSizer->Add(m_autoReportCheckBox);
	m_leftSizer->Add(m_digitalOutputSB, wxSizerFlags(1).Expand());
	m_leftSizer->Add(m_digitalInputSB, wxSizerFlags(1).Expand());

	/* Top Right Section */
	m_enablePWMCheckBox = new wxCheckBox(this, CID_ENABLE_PWM_CHKBOX, wxT("Enable PWM (Hz)"));
	m_enablePWMCheckBox->SetValue(PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_enablePWM == 0 ? false : true);

	m_freqST = new wxStaticText(this, wxID_ANY, wxT("Freq(Hz)"));
	m_freqTC = new wxTextCtrl(this, wxID_ANY);
	m_freqTC->SetValue(wxString::Format("%d",DEFAULT_PWM_FREQUENCE));
	m_freqTC->SetValidator(m_decimalValidator);

	m_dutyST = new wxStaticText(this, wxID_ANY, wxT("Duty(%)"));
	m_dutyTC = new wxTextCtrl(this, wxID_ANY);
	m_dutyTC->SetValue(wxString::Format("%d", DEFAULT_PWM_DUTY));
	m_dutyTC->SetValidator(m_decimalValidator);

	m_pwmFGSizer->Add(m_freqST, wxSizerFlags(7).Border().Align(wxALIGN_CENTER_VERTICAL));
	m_pwmFGSizer->Add(m_freqTC, wxSizerFlags(7).Border().Align(wxALIGN_CENTER_VERTICAL));
	m_pwmFGSizer->Add(m_dutyST, wxSizerFlags(7).Border().Align(wxALIGN_CENTER_VERTICAL));
	m_pwmFGSizer->Add(m_dutyTC, wxSizerFlags(7).Border().Align(wxALIGN_CENTER_VERTICAL));

	m_pwmWriteBB = new wxBitmapButton(this, CID_PWM_WRITE_BUTTON, wxBITMAP_PNG(WRITE_32), wxDefaultPosition, wxSize(48, 48));

	m_pwmTopLevelSizer->Add(m_pwmFGSizer, wxSizerFlags(1).Border().Align(wxALIGN_CENTER_VERTICAL));
	m_pwmTopLevelSizer->Add(m_pwmWriteBB, wxSizerFlags(0).Border().Align(wxALIGN_CENTER_VERTICAL));

	m_clockInDI6CheckBox = new wxCheckBox(this, CID_CLOCK_IN_DI6_CHKBOX, wxT("Clock In DI6"));
	m_clockInDI6CheckBox->SetValue(PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_clockInDI6 == 0 ? false : true);

	m_clockInDI6TC = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_clockInDI6TC->SetValue(wxString::Format("0.0"));
	m_clockInDI6TC->SetEditable(false);
	m_clockInDI6TC->SetBackgroundColour(wxColour(255, 239, 133));

	m_clockInDI7CheckBox = new wxCheckBox(this, CID_CLOCK_IN_DI7_CHKBOX, wxT("Clock In DI7"));
	m_clockInDI7CheckBox->SetValue(PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_clockInDI7 == 0 ? false : true);

	m_clockInDI7TC = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_clockInDI7TC->SetValue(wxString::Format("0.0"));
	m_clockInDI7TC->SetEditable(false);
	m_clockInDI7TC->SetBackgroundColour(wxColour(255, 239, 133));

	m_clockInDIFGSizer->Add(m_clockInDI6CheckBox, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_clockInDIFGSizer->Add(m_clockInDI6TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_clockInDIFGSizer->Add(m_clockInDI7CheckBox, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_clockInDIFGSizer->Add(m_clockInDI7TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_rightSizer->Add(m_enablePWMCheckBox);
	m_rightSizer->Add(m_pwmTopLevelSizer);
	m_rightSizer->Add(m_clockInDIFGSizer);

	/* Section Others */
	m_DI0TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 0 Tick"));
	m_DI0TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_DI0TickTC->SetValue(wxString::Format("0/0"));
	m_DI0TickTC->SetEditable(false);
	m_DI0TickTC->SetBackgroundColour(wxColour(255, 239, 133));

	m_DI1TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 1 Tick"));
	m_DI1TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_DI1TickTC->SetValue(wxString::Format("0/0"));
	m_DI1TickTC->SetEditable(false);
	m_DI1TickTC->SetBackgroundColour(wxColour(255, 239, 133));

	m_DI2TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 2 Tick"));
	m_DI2TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_DI2TickTC->SetValue(wxString::Format("0/0"));
	m_DI2TickTC->SetEditable(false);
	m_DI2TickTC->SetBackgroundColour(wxColour(255, 239, 133));

	m_DI3TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 3 Tick"));
	m_DI3TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_DI3TickTC->SetValue(wxString::Format("0/0"));
	m_DI3TickTC->SetEditable(false);
	m_DI3TickTC->SetBackgroundColour(wxColour(255, 239, 133));

	m_DI4TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 4 Tick"));
	m_DI4TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_DI4TickTC->SetValue(wxString::Format("0/0"));
	m_DI4TickTC->SetEditable(false);
	m_DI4TickTC->SetBackgroundColour(wxColour(255, 239, 133));

	m_DI5TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 5 Tick"));
	m_DI5TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	m_DI5TickTC->SetValue(wxString::Format("0/0"));
	m_DI5TickTC->SetEditable(false);
	m_DI5TickTC->SetBackgroundColour(wxColour(255, 239, 133));

	m_fgSizerOthers->Add(m_DI0TickST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_fgSizerOthers->Add(m_DI0TickTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_fgSizerOthers->Add(m_DI1TickST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_fgSizerOthers->Add(m_DI1TickTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_fgSizerOthers->Add(m_DI2TickST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_fgSizerOthers->Add(m_DI2TickTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_fgSizerOthers->Add(m_DI3TickST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_fgSizerOthers->Add(m_DI3TickTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_fgSizerOthers->Add(m_DI4TickST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_fgSizerOthers->Add(m_DI4TickTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_fgSizerOthers->Add(m_DI5TickST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	m_fgSizerOthers->Add(m_DI5TickTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

	m_othersSB->Add(m_fgSizerOthers, wxSizerFlags(1).Expand());

	/* Add elements to topLevelSizer */
	m_topSectionSizer->Add(m_leftSizer, wxSizerFlags(1).Expand().Border());
	m_topSectionSizer->Add(m_rightSizer, wxSizerFlags(1).Expand().Border());
	m_topLevelSizer->Add(m_topSectionSizer, wxSizerFlags(0).Expand().Border());
	m_topLevelSizer->Add(m_othersSB, wxSizerFlags(1).Expand().Border());

	this->SetSizerAndFit(m_topLevelSizer);
}

USBGPIOPanel::~USBGPIOPanel(){
	
}

void USBGPIOPanel::OnDigitalOutputButton1(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
	
	if (this->m_digitalOutput & DIGITAL_OUTPUT_1_MASK){
		this->m_digitalOutput &= ~(DIGITAL_OUTPUT_1_MASK);

		this->m_digiOutputLight1->SetBitmap(wxBITMAP_PNG(REDBALL_16));
	}
	else{
		this->m_digitalOutput |= DIGITAL_OUTPUT_1_MASK;

		this->m_digiOutputLight1->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
	}

	m_digiOutputTC->SetValue(wxString::Format("%2x", this->m_digitalOutput).Upper());

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
}

void USBGPIOPanel::OnDigitalOutputButton2(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);

	if (this->m_digitalOutput & DIGITAL_OUTPUT_2_MASK){
		this->m_digitalOutput &= ~(DIGITAL_OUTPUT_2_MASK);

		this->m_digiOutputLight2->SetBitmap(wxBITMAP_PNG(REDBALL_16));
	}
	else{
		this->m_digitalOutput |= DIGITAL_OUTPUT_2_MASK;

		this->m_digiOutputLight2->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
	}

	m_digiOutputTC->SetValue(wxString::Format("%2x", this->m_digitalOutput).Upper());

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
}

void USBGPIOPanel::OnDigitalOutputButton3(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);

	if (this->m_digitalOutput & DIGITAL_OUTPUT_3_MASK){
		this->m_digitalOutput &= ~(DIGITAL_OUTPUT_3_MASK);

		this->m_digiOutputLight3->SetBitmap(wxBITMAP_PNG(REDBALL_16));
	}
	else{
		this->m_digitalOutput |= DIGITAL_OUTPUT_3_MASK;

		this->m_digiOutputLight3->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
	}

	m_digiOutputTC->SetValue(wxString::Format("%2x", this->m_digitalOutput).Upper());

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
}

void USBGPIOPanel::OnDigitalOutputButton4(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);

	if (this->m_digitalOutput & DIGITAL_OUTPUT_4_MASK){
		this->m_digitalOutput &= ~(DIGITAL_OUTPUT_4_MASK);

		this->m_digiOutputLight4->SetBitmap(wxBITMAP_PNG(REDBALL_16));
	}
	else{
		this->m_digitalOutput |= DIGITAL_OUTPUT_4_MASK;

		this->m_digiOutputLight4->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
	}

	m_digiOutputTC->SetValue(wxString::Format("%2x", this->m_digitalOutput).Upper());

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
}

void USBGPIOPanel::OnDigitalOutputButton5(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);

	if (this->m_digitalOutput & DIGITAL_OUTPUT_5_MASK){
		this->m_digitalOutput &= ~(DIGITAL_OUTPUT_5_MASK);

		this->m_digiOutputLight5->SetBitmap(wxBITMAP_PNG(REDBALL_16));
	}
	else{
		this->m_digitalOutput |= DIGITAL_OUTPUT_5_MASK;

		this->m_digiOutputLight5->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
	}

	m_digiOutputTC->SetValue(wxString::Format("%2x", this->m_digitalOutput).Upper());

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
}

void USBGPIOPanel::OnDigitalOutputButton6(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);

	if (this->m_digitalOutput & DIGITAL_OUTPUT_6_MASK){
		this->m_digitalOutput &= ~(DIGITAL_OUTPUT_6_MASK);

		this->m_digiOutputLight6->SetBitmap(wxBITMAP_PNG(REDBALL_16));
	}
	else{
		this->m_digitalOutput |= DIGITAL_OUTPUT_6_MASK;

		this->m_digiOutputLight6->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
	}

	m_digiOutputTC->SetValue(wxString::Format("%2x", this->m_digitalOutput).Upper());

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalOutput);
}


void USBGPIOPanel::OnDigitalInputButton1(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton2(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton3(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton4(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton5(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton6(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton7(wxCommandEvent& event){
	// Reserved
}

void USBGPIOPanel::OnDigitalInputButton8(wxCommandEvent& event){
	// Reserved
}


void USBGPIOPanel::OnDigitalInputPolarityButton1(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_1_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_1_MASK);

		this->m_digiInputLight1_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(0, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_1_MASK;

		this->m_digiInputLight1_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(0, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnDigitalInputPolarityButton2(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_2_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_2_MASK);

		this->m_digiInputLight2_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(1, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_2_MASK;

		this->m_digiInputLight2_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(1, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

}

void USBGPIOPanel::OnDigitalInputPolarityButton3(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_3_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_3_MASK);

		this->m_digiInputLight3_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(2, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_3_MASK;

		this->m_digiInputLight3_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(2, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnDigitalInputPolarityButton4(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_4_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_4_MASK);

		this->m_digiInputLight4_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(3, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_4_MASK;

		this->m_digiInputLight4_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(3, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnDigitalInputPolarityButton5(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_5_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_5_MASK);

		this->m_digiInputLight5_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(4, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_5_MASK;

		this->m_digiInputLight5_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(4, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnDigitalInputPolarityButton6(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_6_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_6_MASK);

		this->m_digiInputLight6_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(5, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_6_MASK;

		this->m_digiInputLight6_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(5, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnDigitalInputPolarityButton7(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_7_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_7_MASK);

		this->m_digiInputLight7_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(6, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_7_MASK;

		this->m_digiInputLight7_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(6, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnDigitalInputPolarityButton8(wxCommandEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);

	if (this->m_digitalInputPolarity & DIGITAL_INPUT_POLARITY_8_MASK){
		this->m_digitalInputPolarity &= ~(DIGITAL_INPUT_POLARITY_8_MASK);

		this->m_digiInputLight8_Polarity->SetBitmap(wxBITMAP_PNG(REDBALL_16));
		this->SetDigitalInputLight(7, Polarity_Negative);
	}
	else{
		this->m_digitalInputPolarity |= DIGITAL_INPUT_POLARITY_8_MASK;

		this->m_digiInputLight8_Polarity->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		this->SetDigitalInputLight(7, Polarity_Positive);
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "%x", this->m_digitalInputPolarity);
}

void USBGPIOPanel::OnPWMWriteButton(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void USBGPIOPanel::OnAutoReportCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void USBGPIOPanel::OnEnablePWMCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void USBGPIOPanel::OnDI6InClockCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void USBGPIOPanel::OnDI7InClockCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void USBGPIOPanel::SetDigitalInputLight(unsigned int index, unsigned char polarity){
	
	wxBitmapButton* BBArray[8] = {
		this->m_digiInputLight1, this->m_digiInputLight2, this->m_digiInputLight3, this->m_digiInputLight4,
		this->m_digiInputLight5, this->m_digiInputLight6, this->m_digiInputLight7, this->m_digiInputLight8
	};

	unsigned char digitalInputMask[8] = {
		DIGITAL_INPUT_1_MASK, DIGITAL_INPUT_2_MASK, DIGITAL_INPUT_3_MASK, DIGITAL_INPUT_4_MASK,
		DIGITAL_INPUT_5_MASK, DIGITAL_INPUT_6_MASK, DIGITAL_INPUT_7_MASK, DIGITAL_INPUT_8_MASK
	};

	switch (polarity){

	case Polarity_Negative:

		if (this->m_digitalInput & digitalInputMask[index]){
			BBArray[index]->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		}
		else{
			BBArray[index]->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
		}

		break;

	case Polarity_Positive:

		if (this->m_digitalInput & digitalInputMask[index]){
			BBArray[index]->SetBitmap(wxBITMAP_PNG(GREENBALL_16));
		}
		else{
			BBArray[index]->SetBitmap(wxBITMAP_PNG(GRAYBALL_16));
		}

		break;

	default:

		break;
	}

}

wxBEGIN_EVENT_TABLE(USBGPIOPanel, wxPanel)
EVT_BUTTON(CID_DIGITAL_OUTPUT_1_BUTTON, USBGPIOPanel::OnDigitalOutputButton1)
EVT_BUTTON(CID_DIGITAL_OUTPUT_2_BUTTON, USBGPIOPanel::OnDigitalOutputButton2)
EVT_BUTTON(CID_DIGITAL_OUTPUT_3_BUTTON, USBGPIOPanel::OnDigitalOutputButton3)
EVT_BUTTON(CID_DIGITAL_OUTPUT_4_BUTTON, USBGPIOPanel::OnDigitalOutputButton4)
EVT_BUTTON(CID_DIGITAL_OUTPUT_5_BUTTON, USBGPIOPanel::OnDigitalOutputButton5)
EVT_BUTTON(CID_DIGITAL_OUTPUT_6_BUTTON, USBGPIOPanel::OnDigitalOutputButton6)

//EVT_BUTTON(CID_DIGITAL_INPUT_1_BUTTON, USBGPIOPanel::OnDigitalInputButton1)
//EVT_BUTTON(CID_DIGITAL_INPUT_2_BUTTON, USBGPIOPanel::OnDigitalInputButton2)
//EVT_BUTTON(CID_DIGITAL_INPUT_3_BUTTON, USBGPIOPanel::OnDigitalInputButton3)
//EVT_BUTTON(CID_DIGITAL_INPUT_4_BUTTON, USBGPIOPanel::OnDigitalInputButton4)
//EVT_BUTTON(CID_DIGITAL_INPUT_5_BUTTON, USBGPIOPanel::OnDigitalInputButton5)
//EVT_BUTTON(CID_DIGITAL_INPUT_6_BUTTON, USBGPIOPanel::OnDigitalInputButton6)
//EVT_BUTTON(CID_DIGITAL_INPUT_7_BUTTON, USBGPIOPanel::OnDigitalInputButton7)
//EVT_BUTTON(CID_DIGITAL_INPUT_8_BUTTON, USBGPIOPanel::OnDigitalInputButton8)

EVT_BUTTON(CID_DIGITAL_INPUT_1_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton1)
EVT_BUTTON(CID_DIGITAL_INPUT_2_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton2)
EVT_BUTTON(CID_DIGITAL_INPUT_3_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton3)
EVT_BUTTON(CID_DIGITAL_INPUT_4_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton4)
EVT_BUTTON(CID_DIGITAL_INPUT_5_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton5)
EVT_BUTTON(CID_DIGITAL_INPUT_6_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton6)
EVT_BUTTON(CID_DIGITAL_INPUT_7_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton7)
EVT_BUTTON(CID_DIGITAL_INPUT_8_POLARITY_BUTTON, USBGPIOPanel::OnDigitalInputPolarityButton8)

EVT_BUTTON(CID_PWM_WRITE_BUTTON, USBGPIOPanel::OnPWMWriteButton)

EVT_CHECKBOX(CID_AUTO_REPORT_CHKBOX, USBGPIOPanel::OnAutoReportCheckBox)
EVT_CHECKBOX(CID_ENABLE_PWM_CHKBOX, USBGPIOPanel::OnEnablePWMCheckBox)
EVT_CHECKBOX(CID_CLOCK_IN_DI6_CHKBOX, USBGPIOPanel::OnDI6InClockCheckBox)
EVT_CHECKBOX(CID_CLOCK_IN_DI7_CHKBOX, USBGPIOPanel::OnDI7InClockCheckBox)

wxEND_EVENT_TABLE()