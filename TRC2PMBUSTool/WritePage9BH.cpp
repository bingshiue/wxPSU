/**
 * @file WritePage9BH.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePage9BH::WritePage9BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"MFR_REVISION: "), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	m_loadDefaultBTN = new wxButton(this, CID_BUTTON_LOADDEFAULT, wxT("Load Default"));

	wxString hintSTR = wxString::Format("MFR_REVISION Maximum Input Length is (%d)", MFR_REVISION_LENGTH);
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
	this->m_inputValue->SetMaxLength(MFR_REVISION_LENGTH);
	this->m_inputValue->SetValue(PMBUSHelper::GetAppSettings()->m_mfr_revision);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage9BH::~WritePage9BH(){

}


void WritePage9BH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

void WritePage9BH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

#define CMD_9BH_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage9BH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	char mfr_revision[MFR_REVISION_LENGTH + 1] = { 0 };

	wxString input_mfr_revision = this->m_inputValue->GetValue();

	PMBUSHelper::GetAppSettings()->m_mfr_revision = input_mfr_revision;

	strncpy(mfr_revision, (const char*)input_mfr_revision.mb_str(wxConvUTF8), MFR_REVISION_LENGTH);

	// Fill ASCII Space Code '0x20'
	for (int idx = 0; idx < MFR_REVISION_LENGTH; idx++){
		if (mfr_revision[idx] == '\0') { mfr_revision[idx] = 0x20; }
	}

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x9B, // CMD
		(unsigned char*)mfr_revision,
		(sizeof(mfr_revision) / sizeof(char) - 1)
		);

	PMBUSSendCOMMAND_t CMD9BH;

	CMD9BH.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMD9BH.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_9BH_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_9AH_BYTES_TO_READ : CMD_9AH_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMD9BH.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD9BH);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %ld", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD9BH);
	}

}

void WritePage9BH::OnButtonLoadDefault(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValue(PMBUSHelper::getDefaultMFR_REVISION());
}

wxBEGIN_EVENT_TABLE(WritePage9BH, wxPanel)
//EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage9BH::OnRadioButtonCook)
//EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage9BH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage9BH::OnButtonWrite)
EVT_BUTTON(CID_BUTTON_LOADDEFAULT, WritePage9BH::OnButtonLoadDefault)
wxEND_EVENT_TABLE()
