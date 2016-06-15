/**
 * @file WritePage00H.cpp
 * @brief 00H PAGE.
 */

#include "PMBUSCMDWritePages.h"

#define DEFULT_PAGE 0x00

WritePage00H::WritePage00H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Page"), wxDefaultPosition, wxSize(-1, -1));
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

	wxString default_page = wxString::Format("%d", DEFULT_PAGE);
	this->m_inputValue->SetValue(default_page);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage00H::~WritePage00H(){

}


void WritePage00H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld",decimal));

}

void WritePage00H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02x", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

}

#define CMD_00H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage00H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	unsigned char cmdPageValue;

	if (this->m_rawRadioButton->GetValue() == true){
		cmdPageValue = (unsigned char)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", cmdPageValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		cmdPageValue = wxAtoi(this->m_inputValue->GetValue());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", cmdPageValue);
	}

	unsigned char changePageSendBuffer[8] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
	};

	unsigned char separate_pec = 0;;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, changePageSendBuffer + 2, 3);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	changePageSendBuffer[5] = separate_pec;

	PMBUSSendCOMMAND_t CMD00H;

	CMD00H.m_sendDataLength = sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]);
	CMD00H.m_bytesToRead = CMD_00H_BYTES_TO_READ;
	for (unsigned idx = 0; idx < sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMD00H.m_sendData[idx] = changePageSendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD00H);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD00H);
	}
	
}

wxBEGIN_EVENT_TABLE(WritePage00H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage00H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage00H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage00H::OnButtonWrite)
wxEND_EVENT_TABLE()