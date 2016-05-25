/**
 * @file WritePage03H.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePage03H::WritePage03H(wxWindow* parent, wxString& label) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Value"), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer2->Add(m_inputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

}

WritePage03H::~WritePage03H(){

}


void WritePage03H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

}

void WritePage03H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

}

void WritePage03H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");
}

wxBEGIN_EVENT_TABLE(WritePage03H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage03H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage03H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage03H::OnButtonWrite)
wxEND_EVENT_TABLE()