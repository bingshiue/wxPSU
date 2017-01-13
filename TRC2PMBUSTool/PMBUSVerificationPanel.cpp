/**
 * @file PMBUSVerificationPanel.cpp
 */

#include "PMBUSVerificationPanel.h"

PMBUSVerificationPanel::PMBUSVerificationPanel(wxWindow* parent) : wxScrolledWindow(parent) {
	
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_horizonBox1 = new wxBoxSizer(wxHORIZONTAL);
	m_horizonBox2 = new wxBoxSizer(wxHORIZONTAL);

	m_configurationSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Configuration"));

	m_manualRB = new wxRadioButton(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT("Manual"));
	m_automaticRB = new wxRadioButton(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT("Automatic"));

	m_timeIntervalST = new wxStaticText(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT("Time Iinterval (s)"));
	m_timeIntervalCB = new wxComboBox(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT(""));
	m_timeIntervalCB->Append("1");
	m_timeIntervalCB->Append("2");
	m_timeIntervalCB->Append("3");
	m_timeIntervalCB->Append("4");
	m_timeIntervalCB->Append("5");
	m_timeIntervalCB->Append("8");
	m_timeIntervalCB->Append("10");
	m_timeIntervalCB->Append("20");
	m_timeIntervalCB->Append("30");
	m_timeIntervalCB->Append("40");
	m_timeIntervalCB->Append("50");
	m_timeIntervalCB->Append("60");
	m_timeIntervalCB->Append("90");
	m_timeIntervalCB->Append("120");
	m_timeIntervalCB->Append("180");
	m_timeIntervalCB->Append("240");
	m_timeIntervalCB->Append("300");
	m_timeIntervalCB->SetSelection(4);

	m_userDataST = new wxStaticText(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT("User Data"));
	m_userDataTC = new wxTextCtrl(m_configurationSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(229, -1));
	m_userDataTC->SetBackgroundColour(wxColour(248, 220, 133));
	m_saveButton = new wxButton(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT("Save"));

	m_horizonBox1->Add(m_manualRB, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox1->Add(m_automaticRB, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox1->Add(m_timeIntervalST, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox1->Add(m_timeIntervalCB, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox1->Add(m_userDataST, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox1->Add(m_userDataTC, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox1->Add(m_saveButton, wxSizerFlags().Border().Align(wxCENTER));

	m_configurationSBS->Add(m_horizonBox1, wxSizerFlags().Border());

	m_sl = new wxStaticLine(m_configurationSBS->GetStaticBox(), wxID_ANY);

	m_configurationSBS->Add(m_sl, wxSizerFlags().Border().Expand());

	m_loggingFileNameST = new wxStaticText(m_configurationSBS->GetStaticBox(), wxID_ANY, wxT("Logging File Name"));
	m_loggingFileNameTC = new wxTextCtrl(m_configurationSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(600, -1));

	m_floppyLoadBB = new wxBitmapButton(m_configurationSBS->GetStaticBox(), wxID_ANY, wxBITMAP_PNG(FLOPPY_16));

	m_horizonBox2->Add(m_loggingFileNameST, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox2->Add(m_loggingFileNameTC, wxSizerFlags().Border().Align(wxCENTER));
	m_horizonBox2->Add(m_floppyLoadBB, wxSizerFlags().Border().Align(wxCENTER));

	m_configurationSBS->Add(m_horizonBox2, wxSizerFlags().Border());

	m_contentTC = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);


	/* ----------------------------------------- */
	m_topLevelSizer->Add(m_configurationSBS, wxSizerFlags().Expand());
	m_topLevelSizer->Add(m_contentTC, wxSizerFlags(1).Expand());

	// Setup Sizer
	this->SetSizer(m_topLevelSizer);
}

PMBUSVerificationPanel::~PMBUSVerificationPanel(){

}

wxBEGIN_EVENT_TABLE(PMBUSVerificationPanel, wxScrolledWindow)

wxEND_EVENT_TABLE()