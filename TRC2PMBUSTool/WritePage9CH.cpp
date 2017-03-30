/**
 * @file WritePage9CH.cpp
 */

#include "PMBUSCMDWritePages.h"


WritePage9CH::WritePage9CH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"MFR_LOCATION: "), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	m_loadDefaultBTN = new wxButton(this, CID_BUTTON_LOADDEFAULT, wxT("Load Default"));

	wxString hintSTR = wxString::Format("MFR_LOCATION Maximum Input Length is (%d)", MFR_LOCATION_LENGTH);
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
	this->m_inputValue->SetMaxLength(MFR_LOCATION_LENGTH);
	this->m_inputValue->SetValue(PMBUSHelper::GetAppSettings()->m_mfr_location);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage9CH::~WritePage9CH(){

}


void WritePage9CH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

void WritePage9CH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

}

#define CMD_9CH_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage9CH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	char mfr_location[MFR_LOCATION_LENGTH + 1] = { 0 };

	wxString input_mfr_location = this->m_inputValue->GetValue();

	PMBUSHelper::GetAppSettings()->m_mfr_location = input_mfr_location;

	strncpy(mfr_location, (const char*)input_mfr_location.mb_str(wxConvUTF8), MFR_LOCATION_LENGTH);

	// Fill ASCII Space Code '0x20'
	for (int idx = 0; idx < MFR_LOCATION_LENGTH; idx++){
		if (mfr_location[idx] == '\0') { mfr_location[idx] = 0x20; }
	}

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x9C, // CMD
		(unsigned char*)mfr_location,
		(sizeof(mfr_location) / sizeof(char) - 1)
		);

	PMBUSSendCOMMAND_t CMD9CH;

	CMD9CH.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMD9CH.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_9CH_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_9AH_BYTES_TO_READ : CMD_9AH_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMD9CH.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD9CH);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD9CH);
	}

}

void WritePage9CH::OnButtonLoadDefault(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValue(PMBUSHelper::getDefaultMFR_LOCATION());
}

wxBEGIN_EVENT_TABLE(WritePage9CH, wxPanel)
//EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage9CH::OnRadioButtonCook)
//EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage9CH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage9CH::OnButtonWrite)
EVT_BUTTON(CID_BUTTON_LOADDEFAULT, WritePage9CH::OnButtonLoadDefault)
wxEND_EVENT_TABLE()