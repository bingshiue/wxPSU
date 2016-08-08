/**
 * @file USBGPIOPanel.cpp
 */

#include "USBGPIOPanel.h"

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

	/* Top Left Section */
	m_autoReportCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Auto Report"));
	m_autoReportCheckBox->SetValue(true);

	m_digitalOutputSB = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Digital Output"));

	m_digiOutputLight1 = new wxStaticBitmap(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiOutputLight2 = new wxStaticBitmap(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiOutputLight3 = new wxStaticBitmap(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiOutputLight4 = new wxStaticBitmap(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiOutputLight5 = new wxStaticBitmap(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiOutputLight6 = new wxStaticBitmap(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiOutputTC = new wxTextCtrl(m_digitalOutputSB->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(40, -1));

	m_digitalOutputSB->Add(m_digiOutputLight1);
	m_digitalOutputSB->Add(m_digiOutputLight2);
	m_digitalOutputSB->Add(m_digiOutputLight3);
	m_digitalOutputSB->Add(m_digiOutputLight4);
	m_digitalOutputSB->Add(m_digiOutputLight5);
	m_digitalOutputSB->Add(m_digiOutputLight6);
	m_digitalOutputSB->Add(m_digiOutputTC, wxSizerFlags().Border());

	m_digitalInputSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Digital Input"));

	m_digiInputLight1 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight2 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight3 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight4 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight5 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight6 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight7 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight8 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));

	m_digiInputSL = new wxStaticLine(m_digitalInputSB->GetStaticBox(), wxID_ANY);

	m_digiInputLight9 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight10 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight11 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight12 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight13 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight14 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight15 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));
	m_digiInputLight16 = new wxStaticBitmap(m_digitalInputSB->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(BLUEBALL_16));

	m_digiInputUpSizer->Add(m_digiInputLight1);
	m_digiInputUpSizer->Add(m_digiInputLight2);
	m_digiInputUpSizer->Add(m_digiInputLight3);
	m_digiInputUpSizer->Add(m_digiInputLight4);
	m_digiInputUpSizer->Add(m_digiInputLight5);
	m_digiInputUpSizer->Add(m_digiInputLight6);
	m_digiInputUpSizer->Add(m_digiInputLight7);
	m_digiInputUpSizer->Add(m_digiInputLight8);

	m_digitalInputSB->Add(m_digiInputUpSizer, wxSizerFlags(1).Expand());
	m_digitalInputSB->Add(m_digiInputSL, wxSizerFlags(0).Expand().Border());

	m_digiInputDownSizer->Add(m_digiInputLight9);
	m_digiInputDownSizer->Add(m_digiInputLight10);
	m_digiInputDownSizer->Add(m_digiInputLight11);
	m_digiInputDownSizer->Add(m_digiInputLight12);
	m_digiInputDownSizer->Add(m_digiInputLight13);
	m_digiInputDownSizer->Add(m_digiInputLight14);
	m_digiInputDownSizer->Add(m_digiInputLight15);
	m_digiInputDownSizer->Add(m_digiInputLight16);

	m_digitalInputSB->Add(m_digiInputDownSizer, wxSizerFlags(1).Expand());

	m_leftSizer->Add(m_autoReportCheckBox);
	m_leftSizer->Add(m_digitalOutputSB, wxSizerFlags(1).Expand());
	m_leftSizer->Add(m_digitalInputSB, wxSizerFlags(1).Expand());

	/* Top Right Section */
	m_enablePWMCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Enable PWM (Hz)"));

	m_freqST = new wxStaticText(this, wxID_ANY, wxT("Freq(Hz)"));
	m_freqTC = new wxTextCtrl(this, wxID_ANY);

	m_dutyST = new wxStaticText(this, wxID_ANY, wxT("Duty(%)"));
	m_dutyTC = new wxTextCtrl(this, wxID_ANY);

	m_pwmFGSizer->Add(m_freqST, wxSizerFlags(7).Border().Align(wxCentreY));
	m_pwmFGSizer->Add(m_freqTC, wxSizerFlags(7).Border().Align(wxCentreY));
	m_pwmFGSizer->Add(m_dutyST, wxSizerFlags(7).Border().Align(wxCentreY));
	m_pwmFGSizer->Add(m_dutyTC, wxSizerFlags(7).Border().Align(wxCentreY));

	m_pwmWriteBB = new wxBitmapButton(this, wxID_ANY, wxBITMAP_PNG(WRITE_32));// , wxDefaultPosition, wxSize(32, 32));

	m_pwmTopLevelSizer->Add(m_pwmFGSizer, wxSizerFlags(7).Border().Align(wxCentre));
	m_pwmTopLevelSizer->Add(m_pwmWriteBB, wxSizerFlags(3).Border().Expand());

	m_clockInDI6CheckBox = new wxCheckBox(this, wxID_ANY, wxT("Clock In DI6"));
	m_clockInDI6TC = new wxTextCtrl(this, wxID_ANY);

	m_clockInDI7CheckBox = new wxCheckBox(this, wxID_ANY, wxT("Clock In DI7"));
	m_clockInDI7TC = new wxTextCtrl(this, wxID_ANY);

	m_clockInDIFGSizer->Add(m_clockInDI6CheckBox);
	m_clockInDIFGSizer->Add(m_clockInDI6TC);
	m_clockInDIFGSizer->Add(m_clockInDI7CheckBox);
	m_clockInDIFGSizer->Add(m_clockInDI7TC);

	m_rightSizer->Add(m_enablePWMCheckBox);
	m_rightSizer->Add(m_pwmTopLevelSizer);
	m_rightSizer->Add(m_clockInDIFGSizer);

	/* Section Others */
	m_DI0TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 0 Tick"));
	m_DI0TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY);

	m_DI1TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 1 Tick"));
	m_DI1TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY);

	m_DI2TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 2 Tick"));
	m_DI2TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY);

	m_DI3TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 3 Tick"));
	m_DI3TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY);

	m_DI4TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 4 Tick"));
	m_DI4TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY);

	m_DI5TickST = new wxStaticText(m_othersSB->GetStaticBox(), wxID_ANY, wxT("D/I 5 Tick"));
	m_DI5TickTC = new wxTextCtrl(m_othersSB->GetStaticBox(), wxID_ANY);

	m_fgSizerOthers->Add(m_DI0TickST);
	m_fgSizerOthers->Add(m_DI0TickTC);

	m_fgSizerOthers->Add(m_DI1TickST);
	m_fgSizerOthers->Add(m_DI1TickTC);

	m_fgSizerOthers->Add(m_DI2TickST);
	m_fgSizerOthers->Add(m_DI2TickTC);

	m_fgSizerOthers->Add(m_DI3TickST);
	m_fgSizerOthers->Add(m_DI3TickTC);

	m_fgSizerOthers->Add(m_DI4TickST);
	m_fgSizerOthers->Add(m_DI4TickTC);

	m_fgSizerOthers->Add(m_DI5TickST);
	m_fgSizerOthers->Add(m_DI5TickTC);

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


wxBEGIN_EVENT_TABLE(USBGPIOPanel, wxPanel)

wxEND_EVENT_TABLE()