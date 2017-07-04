/**
 * @file WritePageECH.cpp
 * @brief ECH PAGE.
 */

#include "PMBUSCMDWritePages.h"

#define DEFULT_SETPOINT 0x0800 // Default Set Point is 2048 (0x0800)

WritePageECH::WritePageECH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Set Point"), wxDefaultPosition, wxSize(-1, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY);

	m_confirmCB = new wxCheckBox(this, wxID_ANY, wxT("Confirm"));

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_hintName, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	this->m_horizonSizer2->Add(m_inputValue, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 20));
	this->m_horizonSizer2->Add(m_confirmCB, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);

#if WRITE_PAGES_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	wxString hexString = wxString::Format("%02x", DEFULT_SETPOINT);
	this->m_inputValue->SetValue(hexString);
	this->m_inputValue->SetMaxLength(4);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_hexValidator);

#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString default_page = wxString::Format("%d", DEFULT_PAGE);
	this->m_inputValue->SetValue(default_page);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePageECH::~WritePageECH(){

}


void WritePageECH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

}

void WritePageECH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02x", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

}

#define INPUT_SET_POINT_MAX_VALUE  0x0A7F /**< Maximum Input Value of Set Pinter */
#define INPUT_SET_POINT_MIN_VALUE  0x0600 /**< Minimum Input Value of Set Pinter */

#define CMD_ECH_BYTES_TO_READ  6/**< Bytes To Read */
void WritePageECH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	// Check confirm-checbox
	if (this->m_confirmCB->GetValue()==false){
		// Hint User Check Confirm CheckBox
		wxMessageBox(wxT("Please Check Confirm CheckBox Before You Write New Set Point Value To Device\nPractically"),
			wxT("Please Check Comfirm CheckBox !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	unsigned short setPointValue;

	if (this->m_rawRadioButton->GetValue() == true){
		setPointValue = (unsigned short)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, Value = %d", setPointValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		setPointValue = wxAtoi(this->m_inputValue->GetValue());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, Value = %d", setPointValue);
	}

	// Check Maximum & Minimum Range Of Input Set Point
	if (setPointValue > INPUT_SET_POINT_MAX_VALUE){
		wxMessageBox(wxT("Input Set Point Value Too Large ! Please Re-Input Set Point Value Then Try Again"),
			wxT("Input Set Point Value Too Large !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}
	else if (setPointValue < INPUT_SET_POINT_MIN_VALUE){
		wxMessageBox(wxT("Input Set Point Value Too Small ! Please Re-Input Set Point Value Then Try Again"),
			wxT("Input Set Point Value Too Small !"),  // caption
			wxOK | wxICON_WARNING);

		return;
	}

	unsigned char SetPointSendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SetPointSendBuffer,
		sizeof(SetPointSendBuffer),
		0xEC, // CMD
		(unsigned char*)&setPointValue,
		sizeof(setPointValue)
		);


	PMBUSSendCOMMAND_t CMDECH;

	CMDECH.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]);
	CMDECH.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_ECH_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_ECH_BYTES_TO_READ : CMD_ECH_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sendDataLength; idx++) {//sizeof(changePageSendBuffer) / sizeof(changePageSendBuffer[0]); idx++){
		CMDECH.m_sendData[idx] = SetPointSendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMDECH);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %ld", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMDECH);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "Write New Set Point Value %04x(%d) To Device", setPointValue, setPointValue);
}

wxBEGIN_EVENT_TABLE(WritePageECH, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePageECH::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePageECH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePageECH::OnButtonWrite)
wxEND_EVENT_TABLE()
