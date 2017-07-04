/**
 * @file WritePage99H.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePage99H::WritePage99H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"MFR_ID: "), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	m_loadDefaultBTN = new wxButton(this, CID_BUTTON_LOADDEFAULT, wxT("Load Default"));

	wxString hintSTR = wxString::Format("MFR_ID Maximum Input Length is (%d)", MFR_ID_LENGTH);
	m_hintMaxLengthST = new wxStaticText(this, wxID_ANY, hintSTR, wxDefaultPosition, wxSize(-1, -1));

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_hintName, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 5));
	this->m_horizonSizer2->Add(m_inputValue, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 5));

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);

	this->m_staticBoxlSizer->Add(m_hintMaxLengthST, wxSizerFlags(0).Border(wxALL, 5));

	this->m_staticBoxlSizer->Add(m_loadDefaultBTN, wxSizerFlags(0).Border(wxALL, 5));

	// Disable Radio Button
	this->m_cookRadioButton->Enable(false);
	this->m_rawRadioButton->Enable(false);

	// Setup Text Validator Style
	this->m_textValidator.SetStyle(wxFILTER_ASCII);
	this->m_inputValue->SetValidator(this->m_textValidator);

	// Set Input Max Length & Default String
	this->m_inputValue->SetMaxLength(MFR_ID_LENGTH);
	this->m_inputValue->SetValue(PMBUSHelper::GetAppSettings()->m_mfr_id);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage99H::~WritePage99H(){

}


void WritePage99H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

void WritePage99H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

#define CMD_99H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage99H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	char mfr_id[MFR_ID_LENGTH + 1] = { 0 };

	wxString input_mfr_id = this->m_inputValue->GetValue();

	PMBUSHelper::GetAppSettings()->m_mfr_id = input_mfr_id;

	strncpy(mfr_id, (const char*)input_mfr_id.mb_str(wxConvUTF8), MFR_ID_LENGTH);

	// Fill ASCII Space Code '0x20'
	for (int idx = 0; idx < MFR_ID_LENGTH; idx++){
		if (mfr_id[idx] == '\0') { mfr_id[idx] = 0x20; }
	}

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x99, // CMD
		(unsigned char*)mfr_id,
		(sizeof(mfr_id) / sizeof(char) - 1)
		);

	PMBUSSendCOMMAND_t CMD99H;

	CMD99H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMD99H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_99H_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_9AH_BYTES_TO_READ : CMD_9AH_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMD99H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD99H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %ld", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD99H);
	}

}

void WritePage99H::OnButtonLoadDefault(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValue(PMBUSHelper::getDefaultMFR_ID());
}

wxBEGIN_EVENT_TABLE(WritePage99H, wxPanel)
//EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage99H::OnRadioButtonCook)
//EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage99H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage99H::OnButtonWrite)
EVT_BUTTON(CID_BUTTON_LOADDEFAULT, WritePage99H::OnButtonLoadDefault)
wxEND_EVENT_TABLE()
