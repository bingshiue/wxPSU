/**
 * @file WritePageC2H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_DIAG_VALUE  50.0f/**< Default Diag Value */
#define DEFAULT_SCALE_VALUE  0.5/**< Defaut Scale Value */

WritePageC2H::WritePageC2H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Diag Value"), wxDefaultPosition, wxSize(80, -1));
	m_scale = new wxStaticText(this, wxID_ANY, wxString(L"Exponent"), wxDefaultPosition, wxSize(80, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
	m_scaleValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	wxString default_scale = wxString::Format("%1.1f", DEFAULT_SCALE_VALUE);
	m_scaleValue->SetValue(default_scale);

	// Initial Sizer
	this->m_gridSizer_1 = new wxGridSizer(1, 4, 0, 0);

	// Add Components To Sizer
	this->m_gridSizer_1->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_inputValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scale, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scaleValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_staticBoxlSizer->Add(this->m_gridSizer_1);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString default_value = wxString::Format("%4.1f", DEFAULT_DIAG_VALUE);
	this->m_inputValue->SetValue(default_value);

	// Set Validator
	this->m_inputValue->SetValidator(this->m_numberValidator);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePageC2H::~WritePageC2H(){

}


void WritePageC2H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%4.1f", (double)decimal));

	/* --------------------------- */

	this->m_scaleValue->SetValidator(this->m_numberValidator);

	if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	//long decimal2 = PMBUSHelper::HexToDecimal(this->m_scaleValue->GetValue().c_str());

	//this->m_scaleValue->SetValue(wxString::Format("%ld", decimal2));

}

void WritePageC2H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;


	double tmp = 0;
	this->m_inputValue->GetValue().ToDouble(&tmp);
	wxString hexString = wxString::Format("%02lx", (long)tmp);
	this->m_inputValue->SetValue(hexString);

	/* --------------------------- */

	this->m_scaleValue->SetValidator(this->m_hexValidator);

	if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	//wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_scaleValue->GetValue()));
	//this->m_scaleValue->SetValue(hexString2);

}

#define CMD_C2H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePageC2H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "");

	double mfrMaxTemp = 0;
	double scale;

	this->m_scaleValue->GetValue().ToDouble(&scale);

	if (this->m_rawRadioButton->GetValue() == true){
		mfrMaxTemp = (unsigned char)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", mfrMaxTemp);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_inputValue->GetValue().ToDouble(&mfrMaxTemp);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %4.1f", mfrMaxTemp);
	}

#if 0
	unsigned char SendBuffer[9] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x51, 0x00, 0x00, 0x00, 0x0D, 0x0A
	};

	PMBUSHelper::ProductLinearData(SendBuffer + 4, otWarnLimitValue, scale);

	unsigned char separate_pec = 0;;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 4);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	SendBuffer[6] = separate_pec;
#endif

	unsigned char mfrMaxTempArray[2];
	PMBUSHelper::ProductLinearData(mfrMaxTempArray, (double)mfrMaxTemp, scale);

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0xC2, // CMD
		mfrMaxTempArray,
		sizeof(mfrMaxTempArray)
		);

	PMBUSSendCOMMAND_t CMDC2H;

	CMDC2H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;// sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMDC2H.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_C2H_BYTES_TO_READ : CMD_C2H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMDC2H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMDC2H);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMDC2H);
	}

}

wxBEGIN_EVENT_TABLE(WritePageC2H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePageC2H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePageC2H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePageC2H::OnButtonWrite)
wxEND_EVENT_TABLE()