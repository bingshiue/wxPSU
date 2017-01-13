/**
 * @file WritePage1BH.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_CODE  0x7a/**< Default Code */
#define DEFAULT_MASK  0x90/**< Default Mask */

WritePage1BH::WritePage1BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_code = new wxStaticText(this, wxID_ANY, wxString(L"STATUS_x CMD"), wxDefaultPosition, wxSize(-1, -1));
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

#if WRITE_PAGES_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	wxString hexString = wxString::Format("%02lx", DEFAULT_CODE);
	this->m_codeInputValue->SetValue(hexString);

	wxString hexString2 = wxString::Format("%02lx", DEFAULT_MASK);
	this->m_maskInputValue->SetValue(hexString2);

	// Set Validator
	this->m_codeInputValue->SetValidator(this->m_hexValidator);
	this->m_maskInputValue->SetValidator(this->m_hexValidator);

#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString codeSTR = wxString::Format("%d", DEFAULT_CODE);
	m_codeInputValue->SetValue(codeSTR);

	wxString maskSTR = wxString::Format("%d", DEFAULT_MASK);
	m_maskInputValue->SetValue(maskSTR);

	// Set Validator
	this->m_codeInputValue->SetValidator(this->m_numberValidator);
	this->m_maskInputValue->SetValidator(this->m_numberValidator);
#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage1BH::~WritePage1BH(){

}


void WritePage1BH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

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
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

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

#define CMD_1BH_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage1BH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	unsigned char code = 0;
	unsigned char mask = 0;

	double code_double = 0;
	double mask_double = 0;

	// Raw
	if (this->m_rawRadioButton->GetValue() == true){
		code = (unsigned char)PMBUSHelper::HexToDecimal(this->m_codeInputValue->GetValue().c_str());
		mask = (unsigned char)PMBUSHelper::HexToDecimal(this->m_maskInputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, code = %02x, mask = %02x", code, mask);
	}
	// Cook
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_codeInputValue->GetValue().ToDouble(&code_double);
		code = (unsigned char)code_double;

		this->m_maskInputValue->GetValue().ToDouble(&mask_double);
		mask = (unsigned char)mask_double;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, code = %d, mask = %d", code, mask);
	}

	unsigned char smbAlertValueArray[2];
	smbAlertValueArray[0] = code;
	smbAlertValueArray[1] = mask;

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x1B, // CMD
		smbAlertValueArray,
		sizeof(smbAlertValueArray)
		);

	PMBUSSendCOMMAND_t CMD1BH;

	CMD1BH.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMD1BH.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_1BH_BYTES_TO_READ : CMD_1BH_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD1BH.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD1BH);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD1BH);
	}

}

wxBEGIN_EVENT_TABLE(WritePage1BH, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage1BH::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage1BH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage1BH::OnButtonWrite)
wxEND_EVENT_TABLE()