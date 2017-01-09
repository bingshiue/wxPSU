/**
 * @file WritePageD0H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_VALUE 0x00

WritePageD0H::WritePageD0H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Value"), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_hintName, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	this->m_horizonSizer2->Add(m_inputValue, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);

#if WRITE_PAGES_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	wxString hexString = wxString::Format("%02lx", DEFAULT_VALUE);
	this->m_inputValue->SetValue(hexString);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_hexValidator);

#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString default_value = wxString::Format("%d", DEFAULT_VALUE);
	this->m_inputValue->SetValue(default_value);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePageD0H::~WritePageD0H(){

}


void WritePageD0H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

}

void WritePageD0H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

}

#define CMD_D0H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePageD0H::OnButtonWrite(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "");

	unsigned char sendValue;

	if (this->m_rawRadioButton->GetValue() == true){
		sendValue = (unsigned char)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, Value = %d", sendValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		sendValue = wxAtoi(this->m_inputValue->GetValue());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, Value = %d", sendValue);
	}

#if 0
	unsigned char SendBuffer[8] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xD0, sendValue, 0x00, 0x0D, 0x0A
	};

	unsigned char separate_pec = 0;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 3);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	SendBuffer[5] = separate_pec;
#endif

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0xD0, // CMD
		&sendValue,
		sizeof(sendValue)
		);

	PMBUSSendCOMMAND_t CMDD0H;

	CMDD0H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMDD0H.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_D0H_BYTES_TO_READ : CMD_D0H_BYTES_TO_READ+1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMDD0H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMDD0H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		PSU_DEBUG_PRINT(MSG_DEBUG, "Task Count = %d", cnt);
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask)SendWriteCMDTask(m_ioaccess, m_currentIO, CMDD0H);
	}
}

wxBEGIN_EVENT_TABLE(WritePageD0H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePageD0H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePageD0H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePageD0H::OnButtonWrite)
wxEND_EVENT_TABLE()