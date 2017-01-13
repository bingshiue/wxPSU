/**
 * @file I2CSlaveAddressDialog.cpp
 */

#include "I2CSlaveAddressDialog.h"

I2CSlaveAddressDialog::I2CSlaveAddressDialog(wxWindow *parent, AppSettings_t* appSettings) : wxDialog(parent, wxID_ANY, wxString(wxT("I2C Slave Address"))){
	this->m_parent = parent;
	this->m_appSettings = appSettings;

	// Initialize Sizer
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_addressSizer = new wxBoxSizer(wxHORIZONTAL);

	m_checkBoxsFGS = new wxFlexGridSizer(2,4,5,5);

	// Initialize GUI Component
	m_i2cSlaveAddressST = new wxStaticText(this, wxID_ANY, wxT("I2C Slave Address : "));
	m_i2cSlaveAddressTC = new wxTextCtrl(this, wxID_ANY);

	// Fill Slave Address Text
	unsigned long SlaveAddr = this->m_appSettings->m_I2CSlaveAddress;
	wxString SlaveAddrStr = wxString::Format("%2x", SlaveAddr);
	m_i2cSlaveAddressTC->SetValue(SlaveAddrStr.Upper());
	m_i2cSlaveAddressTC->SetEditable(false);
	m_i2cSlaveAddressTC->SetBackgroundColour(wxColour(248, 220, 133));

	m_b0CheckBox = new wxCheckBox(this, CID_B0_CHECKBOX, wxT("B0"));
	m_b2CheckBox = new wxCheckBox(this, CID_B2_CHECKBOX, wxT("B2"));
	m_b4CheckBox = new wxCheckBox(this, CID_B4_CHECKBOX, wxT("B4"));
	m_b6CheckBox = new wxCheckBox(this, CID_B6_CHECKBOX, wxT("B6"));
	m_b8CheckBox = new wxCheckBox(this, CID_B8_CHECKBOX, wxT("B8"));
	m_baCheckBox = new wxCheckBox(this, CID_BA_CHECKBOX, wxT("BA"));
	m_bcCheckBox = new wxCheckBox(this, CID_BC_CHECKBOX, wxT("BC"));
	m_beCheckBox = new wxCheckBox(this, CID_BE_CHECKBOX, wxT("BE"));

	m_saveThenExitBtn = new wxButton(this, CID_SAVE_THEN_EXIT_BUTTOUN, wxT("Save Then Exit"));

	// Add Component into Sizer
	m_addressSizer->Add(m_i2cSlaveAddressST);
	m_addressSizer->Add(m_i2cSlaveAddressTC);

	m_topLevelSizer->Add(m_addressSizer, wxSizerFlags().Align(wxALIGN_CENTRE_HORIZONTAL).Border());

	m_checkBoxsFGS->Add(m_b0CheckBox);
	m_checkBoxsFGS->Add(m_b2CheckBox);
	m_checkBoxsFGS->Add(m_b4CheckBox);
	m_checkBoxsFGS->Add(m_b6CheckBox);
	m_checkBoxsFGS->Add(m_b8CheckBox);
	m_checkBoxsFGS->Add(m_baCheckBox);
	m_checkBoxsFGS->Add(m_bcCheckBox);
	m_checkBoxsFGS->Add(m_beCheckBox);

	m_topLevelSizer->Add(m_checkBoxsFGS, wxSizerFlags().Align(wxALIGN_CENTRE_HORIZONTAL).Border());

	m_topLevelSizer->Add(m_saveThenExitBtn, wxSizerFlags().Align(wxALIGN_CENTRE_HORIZONTAL).Border());

	// Setup Sizer
	this->SetSizerAndFit(m_topLevelSizer);

	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

	m_i2cSlaveAddressTC->SetValidator(m_hexValidator);

	SetCheckBoxDefaultValue();
}

I2CSlaveAddressDialog::~I2CSlaveAddressDialog(){

}

void I2CSlaveAddressDialog::OnSaveThenExitButton(wxCommandEvent& event){

	// Try Decimal
	unsigned long SlaveAddress = wxAtol(m_i2cSlaveAddressTC->GetValue());

	// Hex ?
	if (SlaveAddress==0){
		SlaveAddress = PMBUSHelper::HexToDecimal(m_i2cSlaveAddressTC->GetValue());
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "SlaveAddress=%2x", SlaveAddress);

	// Check If Input I2C Slave Address Value Valid ??
	if (SlaveAddress <= 0 || SlaveAddress > 255){
		wxMessageBox(wxT("Input I2C Slave Address Error ! \n\n Please Input Valid I2C Slave Address"),
			wxT("Error !"),  // caption
			wxOK | wxICON_ERROR);

		return;
	}

	this->m_appSettings->m_I2CSlaveAddress = SlaveAddress;
	PMBUSHelper::GetSlaveAddress() = this->m_appSettings->m_I2CSlaveAddress;

	this->EndModal(SlaveAddress);

}

void I2CSlaveAddressDialog::OnB0CheckBox(wxCommandEvent& event){

	if (m_b0CheckBox->GetValue()==true){
		UnCheckALL();
		m_b0CheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("B0"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnB2CheckBox(wxCommandEvent& event){

	if (m_b2CheckBox->GetValue() == true){
		UnCheckALL();
		m_b2CheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("B2"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnB4CheckBox(wxCommandEvent& event){

	if (m_b4CheckBox->GetValue() == true){
		UnCheckALL();
		m_b4CheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("B4"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnB6CheckBox(wxCommandEvent& event){

	if (m_b6CheckBox->GetValue() == true){
		UnCheckALL();
		m_b6CheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("B6"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnB8CheckBox(wxCommandEvent& event){

	if (m_b8CheckBox->GetValue() == true){
		UnCheckALL();
		m_b8CheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("B8"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnBaCheckBox(wxCommandEvent& event){

	if (m_baCheckBox->GetValue() == true){
		UnCheckALL();
		m_baCheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("BA"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnBcCheckBox(wxCommandEvent& event){

	if (m_bcCheckBox->GetValue() == true){
		UnCheckALL();
		m_bcCheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("BC"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::OnBeCheckBox(wxCommandEvent& event){

	if (m_beCheckBox->GetValue() == true){
		UnCheckALL();
		m_beCheckBox->SetValue(true);

		m_i2cSlaveAddressTC->SetValue(wxT("BE"));
	}
	else{
		m_i2cSlaveAddressTC->SetValue(wxT(""));
	}
}

void I2CSlaveAddressDialog::SetCheckBoxDefaultValue(void){

	wxCheckBox* checkBoxArray[8] = {
		m_b0CheckBox, m_b2CheckBox, m_b4CheckBox, m_b6CheckBox,
		m_b8CheckBox, m_baCheckBox, m_bcCheckBox, m_beCheckBox
	};

	unsigned long SlaveAddr = this->m_appSettings->m_I2CSlaveAddress;
	wxString SlaveAddrStr = wxString::Format("%2x", SlaveAddr);
	SlaveAddrStr.UpperCase();

	for (unsigned int idx = 0; idx < sizeof(checkBoxArray) / sizeof(checkBoxArray[0]); idx++){
		if (checkBoxArray[idx]->GetLabel().Cmp(SlaveAddrStr) == 0){
			checkBoxArray[idx]->SetValue(true);
			break;
		}
	}

}

void I2CSlaveAddressDialog::UnCheckALL(void){
	wxCheckBox* checkBoxArray[8] = {
		m_b0CheckBox, m_b2CheckBox, m_b4CheckBox, m_b6CheckBox,
		m_b8CheckBox, m_baCheckBox, m_bcCheckBox, m_beCheckBox
	};

	for (unsigned int idx = 0; idx < sizeof(checkBoxArray) / sizeof(checkBoxArray[0]); idx++){
		checkBoxArray[idx]->SetValue(false);
	}
}

wxBEGIN_EVENT_TABLE(I2CSlaveAddressDialog, wxDialog)
EVT_BUTTON(CID_SAVE_THEN_EXIT_BUTTOUN, I2CSlaveAddressDialog::OnSaveThenExitButton)
EVT_CHECKBOX(CID_B0_CHECKBOX, I2CSlaveAddressDialog::OnB0CheckBox)
EVT_CHECKBOX(CID_B2_CHECKBOX, I2CSlaveAddressDialog::OnB2CheckBox)
EVT_CHECKBOX(CID_B4_CHECKBOX, I2CSlaveAddressDialog::OnB4CheckBox)
EVT_CHECKBOX(CID_B6_CHECKBOX, I2CSlaveAddressDialog::OnB6CheckBox)
EVT_CHECKBOX(CID_B8_CHECKBOX, I2CSlaveAddressDialog::OnB8CheckBox)
EVT_CHECKBOX(CID_BA_CHECKBOX, I2CSlaveAddressDialog::OnBaCheckBox)
EVT_CHECKBOX(CID_BC_CHECKBOX, I2CSlaveAddressDialog::OnBcCheckBox)
EVT_CHECKBOX(CID_BE_CHECKBOX, I2CSlaveAddressDialog::OnBeCheckBox)
wxEND_EVENT_TABLE()