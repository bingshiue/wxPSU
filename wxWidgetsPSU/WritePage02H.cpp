/**
 * @file WritePage02H.cpp
 * @brief 02H ON_OFF_CONFIG.
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_VALUE 21

WritePage02H::WritePage02H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"On/Off Config"), wxDefaultPosition, wxSize(-1, -1));
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

	wxString default_value = wxString::Format("%d", DEFAULT_VALUE);
	this->m_inputValue->SetValue(default_value);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

}

WritePage02H::~WritePage02H(){

}


void WritePage02H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

}

void WritePage02H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02x", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

}

void WritePage02H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	unsigned char cmdOnOffConfigValue;

	if (this->m_rawRadioButton->GetValue() == true){
		cmdOnOffConfigValue = (unsigned char)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", cmdOnOffConfigValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		cmdOnOffConfigValue = wxAtoi(this->m_inputValue->GetValue());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", cmdOnOffConfigValue);
	}

	unsigned char SendBuffer[8] = {
		0x41, 0x54, 0xB6, 0x02, cmdOnOffConfigValue, 0x00, 0x0D, 0x0A
	};

	PMBUSSendCOMMAND_t CMD02H;

	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD02H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD02H);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
	}
}

wxBEGIN_EVENT_TABLE(WritePage02H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage02H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage02H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage02H::OnButtonWrite)
wxEND_EVENT_TABLE()