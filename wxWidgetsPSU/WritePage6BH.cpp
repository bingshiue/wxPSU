/**
 * @file WritePage6BH.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_VALUE        2600/**< Default Value */
#define DEFAULT_SCALE_VALUE  4/**< Defaut Scale Value */

#define WRITE_PAGES_6BH_DEFAULT_FORMAT_HEX  FASLE

WritePage6BH::WritePage6BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Value"), wxDefaultPosition, wxSize(80, -1));
	m_scale = new wxStaticText(this, wxID_ANY, wxString(L"Exponent"), wxDefaultPosition, wxSize(80, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
	m_scaleValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	wxString default_scale = wxString::Format("%d", DEFAULT_SCALE_VALUE);
	m_scaleValue->SetValue(default_scale);

	// Initial Sizer
	this->m_gridSizer_1 = new wxGridSizer(1, 4, 0, 0);

	// Add Components To Sizer
	this->m_gridSizer_1->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_inputValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scale, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scaleValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_staticBoxlSizer->Add(this->m_gridSizer_1);

#if WRITE_PAGES_6BH_DEFAULT_FORMAT_HEX == TRUE
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

WritePage6BH::~WritePage6BH(){

}


void WritePage6BH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

	/* --------------------------- */

	this->m_scaleValue->SetValidator(this->m_numberValidator);

	if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	//long decimal2 = PMBUSHelper::HexToDecimal(this->m_scaleValue->GetValue().c_str());

	//this->m_scaleValue->SetValue(wxString::Format("%ld", decimal2));

}

void WritePage6BH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

	/* --------------------------- */

	this->m_scaleValue->SetValidator(this->m_hexValidator);

	if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	//wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_scaleValue->GetValue()));
	//this->m_scaleValue->SetValue(hexString2);

}

#define CMD_6BH_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage6BH::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	double pinOPWarnValue = 0;
	double scale;

	this->m_scaleValue->GetValue().ToDouble(&scale);

	if (this->m_rawRadioButton->GetValue() == true){
		pinOPWarnValue = (unsigned int)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %f", pinOPWarnValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_inputValue->GetValue().ToDouble(&pinOPWarnValue);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %f", pinOPWarnValue);
	}

#if 0
	unsigned char SendBuffer[9] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x6B, 0x00, 0x00, 0x00, 0x0D, 0x0A
	};

	PMBUSHelper::ProductLinearData(SendBuffer + 4, pinOPWarnValue, scale);

	unsigned char separate_pec = 0;;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 4);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	SendBuffer[6] = separate_pec;
#endif

	unsigned char pinOPWarnValueArray[2];
	PMBUSHelper::ProductLinearData(pinOPWarnValueArray, (double)pinOPWarnValue, scale);

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x6B, // CMD
		pinOPWarnValueArray,
		sizeof(pinOPWarnValueArray)
		);

	PMBUSSendCOMMAND_t CMD6BH;

	CMD6BH.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMD6BH.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_6BH_BYTES_TO_READ : CMD_6BH_BYTES_TO_READ+1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD6BH.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD6BH);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask)SendWriteCMDTask(m_ioaccess, m_currentIO, CMD6BH);
	}

}

wxBEGIN_EVENT_TABLE(WritePage6BH, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage6BH::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage6BH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage6BH::OnButtonWrite)
wxEND_EVENT_TABLE()