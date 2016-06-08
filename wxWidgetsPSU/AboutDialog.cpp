/**
 * @file AboutDialog.cpp
 */

#include "AboutDialog.h"
#include "acbel.xpm"

AboutDialog::AboutDialog(wxWindow *parent) : wxDialog(parent, wxID_ANY, wxString(wxT("About dialog")), wxDefaultPosition, wxSize(310, 280))
{
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);

	m_acbelLogoSB = new wxStaticBitmap(this, wxID_ANY, wxBitmap(Acbel_xpm));

	m_line1ST = new wxStaticText(this, wxID_ANY, wxT("PSU Monitor"), wxDefaultPosition, wxDefaultSize);
	m_line2ST = new wxStaticText(this, wxID_ANY, wxT("Version: 1.0.0.0"), wxDefaultPosition, wxDefaultSize);
	m_line3ST = new wxStaticText(this, wxID_ANY, wxT("Copyright 2015, AcBel Polytech Inc."), wxDefaultPosition, wxDefaultSize);
	m_line4ST = new wxStaticText(this, wxID_ANY, wxT("PROPRIETARY NOTICE"), wxDefaultPosition, wxDefaultSize);
	m_line5ST = new wxStaticText(this, wxID_ANY, wxT("This program is the property of ACBEL Polytech Inc."), wxDefaultPosition, wxDefaultSize);
	m_line6ST = new wxStaticText(this, wxID_ANY, wxT("and shall not be used in non-ACBEL product."), wxDefaultPosition, wxDefaultSize);

	wxStaticLine *m_sl = new wxStaticLine(this);

	m_btnOK = new wxButton(this, CID_BTN_OK, wxT("OK"));


	m_topLevelSizer->Add(m_acbelLogoSB, wxSizerFlags(0).Align(wxCENTER));

	m_topLevelSizer->Add(new wxStaticText(this, wxID_ANY, wxT(" "), wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Align(wxCENTER));

	m_topLevelSizer->Add(m_line1ST, wxSizerFlags(0).Align(wxCENTER));
	m_topLevelSizer->Add(m_line2ST, wxSizerFlags(0).Align(wxCENTER));
	m_topLevelSizer->Add(m_line3ST, wxSizerFlags(0).Align(wxCENTER));
	m_topLevelSizer->Add(m_line4ST, wxSizerFlags(0).Align(wxCENTER));
	m_topLevelSizer->Add(m_line5ST, wxSizerFlags(0).Align(wxCENTER));
	m_topLevelSizer->Add(m_line6ST, wxSizerFlags(0).Align(wxCENTER));

	m_topLevelSizer->Add(new wxStaticText(this, wxID_ANY, wxT(" "), wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Align(wxCENTER));

	m_topLevelSizer->Add(m_sl, wxSizerFlags(0).Expand());

	m_topLevelSizer->Add(new wxStaticText(this, wxID_ANY, wxT(" "), wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Align(wxCENTER));

	m_topLevelSizer->Add(m_btnOK, wxSizerFlags(0).Align(wxCENTER));

	SetSizer(m_topLevelSizer);

	SetEscapeId(wxID_CLOSE);

	m_btnOK->SetFocus();
	m_btnOK->SetDefault();
}

AboutDialog::~AboutDialog(){

}


wxBEGIN_EVENT_TABLE(AboutDialog, wxDialog)
EVT_BUTTON(CID_BTN_OK, AboutDialog::OnBtnOK)
wxEND_EVENT_TABLE()

void AboutDialog::OnBtnOK(wxCommandEvent& event){
	this->Close();
}







