/**
 * @file WritePage51H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_SCALE_VALUE  0.5/**< Defaut Scale Value */

WritePage51H::WritePage51H(wxWindow* parent, wxString& label) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Diag Value"), wxDefaultPosition, wxSize(80, -1));
	m_scale = new wxStaticText(this, wxID_ANY, wxString(L"Exponent"), wxDefaultPosition, wxSize(80, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
	m_scaleValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	wxString default_scale = wxString::Format("%1.1f", DEFAULT_SCALE_VALUE);
	m_scaleValue->SetValue(default_scale);

	// Initial Sizer
	this->m_gridSizer_1 = new wxGridSizer(1, 4, 0, 0);

	// Add Components To Sizer
	this->m_gridSizer_1->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_inputValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scale, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scaleValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_staticBoxlSizer->Add(this->m_gridSizer_1);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

}

WritePage51H::~WritePage51H(){

}


void WritePage51H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

	/* --------------------------- */

	this->m_scaleValue->SetValidator(this->m_numberValidator);

	if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_scaleValue->GetValue().c_str());

	this->m_scaleValue->SetValue(wxString::Format("%ld", decimal2));

}

void WritePage51H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

	/* --------------------------- */

	this->m_scaleValue->SetValidator(this->m_hexValidator);

	if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_scaleValue->GetValue()));
	this->m_scaleValue->SetValue(hexString2);

}

void WritePage51H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");
}

wxBEGIN_EVENT_TABLE(WritePage51H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage51H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage51H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage51H::OnButtonWrite)
wxEND_EVENT_TABLE()