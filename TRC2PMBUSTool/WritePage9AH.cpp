/**
 * @file WritePage9AH.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePage9AH::WritePage9AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"MFR_MODEL: "), wxDefaultPosition, wxSize(80, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	wxString hintSTR = wxString::Format("MFR_MODEL Maximum Input Length is (%d)", MFR_MODEL_LENGTH);
	m_hintMaxLengthST = new wxStaticText(this, wxID_ANY, hintSTR, wxDefaultPosition, wxSize(-1, -1));

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_hintName, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 5));
	this->m_horizonSizer2->Add(m_inputValue, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 5));

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);

	this->m_staticBoxlSizer->Add(m_hintMaxLengthST, wxSizerFlags(0).Border(wxALL, 5));

	// Disable Radio Button
	this->m_cookRadioButton->Enable(false);
	this->m_rawRadioButton->Enable(false);

	// Setup Text Validator Style
	this->m_textValidator.SetStyle(wxFILTER_ASCII);
	this->m_inputValue->SetValidator(this->m_textValidator);

	// Set Input Max Length & Default String
	this->m_inputValue->SetMaxLength(MFR_MODEL_LENGTH);
	this->m_inputValue->SetValue(DEF_MFR_MODEL);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage9AH::~WritePage9AH(){

}


void WritePage9AH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

void WritePage9AH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

#define CMD_9AH_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage9AH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	char mfr_model[MFR_MODEL_LENGTH + 1] = { 0 };

	wxString input_mfr_model = this->m_inputValue->GetValue();

	//mfr_model[0] = MFR_MODEL_LENGTH;//Block Size

	//strncpy(mfr_model+1, (const char*)input_mfr_model.mb_str(wxConvUTF8), MFR_MODEL_LENGTH);

	strncpy(mfr_model, (const char*)input_mfr_model.mb_str(wxConvUTF8), MFR_MODEL_LENGTH);

	// Fill ASCII Space Code '0x20'
	for (int idx = 0; idx < MFR_MODEL_LENGTH; idx++){
		if (mfr_model[idx] == '\0') { mfr_model[idx] = 0x20; }
	}

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x9A, // CMD
		(unsigned char*)mfr_model,
		(sizeof(mfr_model) / sizeof(char) - 1)
		);

	PMBUSSendCOMMAND_t CMD9AH;

	CMD9AH.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMD9AH.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_9AH_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_9AH_BYTES_TO_READ : CMD_9AH_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMD9AH.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD9AH);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD9AH);
	}

}

wxBEGIN_EVENT_TABLE(WritePage9AH, wxPanel)
//EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage9AH::OnRadioButtonCook)
//EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage9AH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage9AH::OnButtonWrite)
wxEND_EVENT_TABLE()