/**
 * @file WritePage1BH.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePage1BH::WritePage1BH(wxWindow* parent, wxString& label) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_code = new wxStaticText(this, wxID_ANY, wxString(L"Code"), wxDefaultPosition, wxSize(-1, -1));
	m_codeInputValue = new wxTextCtrl(this, wxID_ANY);

	m_mask = new wxStaticText(this, wxID_ANY, wxString(L"Mask"), wxDefaultPosition, wxSize(-1, -1));
	m_maskInputValue = new wxTextCtrl(this, wxID_ANY);

	m_padding = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_horizonSizer3 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_code, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer2->Add(m_codeInputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_horizonSizer3->Add(m_mask, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer3->Add(m_maskInputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);
	this->m_staticBoxlSizer->Add(this->m_padding);
	this->m_staticBoxlSizer->Add(this->m_horizonSizer3);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	// Set Validator
	this->m_codeInputValue->SetValidator(this->m_numberValidator);
	this->m_maskInputValue->SetValidator(this->m_numberValidator);

}

WritePage1BH::~WritePage1BH(){

}


void WritePage1BH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_codeInputValue->SetValidator(this->m_numberValidator);

	if (this->m_codeInputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_codeInputValue->GetValue().c_str());

	this->m_codeInputValue->SetValue(wxString::Format("%ld", decimal));

	/* ------------------- */

	this->m_maskInputValue->SetValidator(this->m_numberValidator);

	if (this->m_maskInputValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_maskInputValue->GetValue().c_str());

	this->m_maskInputValue->SetValue(wxString::Format("%ld", decimal2));

}

void WritePage1BH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_codeInputValue->SetValidator(this->m_hexValidator);

	if (this->m_codeInputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_codeInputValue->GetValue()));
	this->m_codeInputValue->SetValue(hexString);

	/* ------------------- */

	this->m_maskInputValue->SetValidator(this->m_hexValidator);

	if (this->m_maskInputValue->GetValue() == wxEmptyString) return;

	wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_maskInputValue->GetValue()));
	this->m_maskInputValue->SetValue(hexString2);

}

void WritePage1BH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");
}

wxBEGIN_EVENT_TABLE(WritePage1BH, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage1BH::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage1BH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage1BH::OnButtonWrite)
wxEND_EVENT_TABLE()