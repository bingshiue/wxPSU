/**
 * @file WritePageDDH.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePageDDH::WritePageDDH(wxWindow* parent, wxString& label) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Value"), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_hintName, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	this->m_horizonSizer2->Add(m_inputValue, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

}

WritePageDDH::~WritePageDDH(){

}


void WritePageDDH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

}

void WritePageDDH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

}

void WritePageDDH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");
}

wxBEGIN_EVENT_TABLE(WritePageDDH, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePageDDH::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePageDDH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePageDDH::OnButtonWrite)
wxEND_EVENT_TABLE()