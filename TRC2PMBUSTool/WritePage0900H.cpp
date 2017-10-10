/**
 * @file WritePage0900H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define SELF_CMD  0x0900/**< Self Command */

#define DEFAULT_TARGET_VOLTAGE    0x277/**< Default Target Voltage */

#define DEFAULT_HIGH_BYTE_VALUE   0x00/**< Default high byte Value */
#define DEFAULT_LOW_BYTE_VALUE    0x00/**< Default low  byte Value */

#define WRITE_PAGES_0900H_DEFAULT_FORMAT_HEX  FALSE//TRUE//FALSE

WritePage0900H::WritePage0900H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Vc : "), wxDefaultPosition, wxSize(80, -1));
	//m_scale = new wxStaticText(this, wxID_ANY, wxString(L"Low Byte"), wxDefaultPosition, wxSize(80, -1));

	m_computedVoltage = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(80, -1));
	m_computedVoltage->SetForegroundColour(wxColour(0,0,255));

	m_cmdDescription = new wxStaticText(this, wxID_ANY, wxString(
	    L"讀寫,單位 0.1V,高位在前,低位在後 \n"
	     "通過 I2C 控制可以調整 AC/DC 電源模塊的輸出電壓 \n"
	     "範圍為 18V~31V,與電源模塊輸出電壓 VOut 與 DAC \n"
	     "控制字 Vc 的關係為 Vout=(13/4095)*Vc + 18V \n"
	     "其中 Vc 表示 DAC 的量化植,範圍為 0~4095"),
	 wxDefaultPosition, wxSize(-1, -1));

	m_targetVoltage = new wxTextCtrl(this, CID_TEXTCTRL_TARGET_VOLTAGE, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	//m_highByteValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
	//m_lowByteValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	m_stPadding_6 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));

	this->m_numberValidator.SetCharIncludes(wxT("0123456789"));

	// Initial Sizer
	this->m_gridSizer_1 = new wxGridSizer(1, 4, 0, 0);

	// Add Components To Sizer
	this->m_gridSizer_1->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_targetVoltage, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(this->m_computedVoltage, 1, wxALIGN_CENTER_VERTICAL, 10);
	//this->m_gridSizer_1->Add(m_highByteValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	//this->m_gridSizer_1->Add(m_scale, 1, wxALIGN_CENTER_VERTICAL, 10);
	//this->m_gridSizer_1->Add(m_lowByteValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_staticBoxlSizer->Add(this->m_gridSizer_1);

	this->m_staticBoxlSizer->Add(m_stPadding_6);

	this->m_staticBoxlSizer->Add(this->m_cmdDescription);

#if WRITE_PAGES_0900H_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	//wxString hexString_high_byte = wxString::Format("%02lx", (long)DEFAULT_HIGH_BYTE_VALUE);
	//this->m_highByteValue->SetValue(hexString_high_byte);

	//wxString hexString_low_byte = wxString::Format("%02lx", (long)DEFAULT_LOW_BYTE_VALUE);
	//this->m_lowByteValue->SetValue(hexString_low_byte);

	wxString hexString_target_voltage = wxString::Format("%02lx", (long)DEFAULT_TARGET_VOLTAGE);
	this->m_targetVoltage->SetValue(hexString_target_voltage);

	// Set Validator
	//this->m_highByteValue->SetValidator(this->m_hexValidator);
	//this->m_lowByteValue->SetValidator(this->m_hexValidator);

	//this->m_highByteValue->SetMaxLength(2);
	//this->m_lowByteValue->SetMaxLength(2);

	this->m_targetVoltage->SetValidator(this->m_hexValidator);
	this->m_targetVoltage->SetMaxLength(4);


#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	//wxString default_high_byte = wxString::Format("%d", DEFAULT_HIGH_BYTE_VALUE);
	//this->m_highByteValue->SetValue(default_high_byte);

	//wxString default_low_byte = wxString::Format("%d", DEFAULT_LOW_BYTE_VALUE);
	//m_lowByteValue->SetValue(default_low_byte);

	wxString default_target_voltage = wxString::Format("%d", DEFAULT_TARGET_VOLTAGE);
	this->m_targetVoltage->SetValue(default_target_voltage);

	// Set Validator
	//this->m_highByteValue->SetValidator(this->m_numberValidator);
	//this->m_lowByteValue->SetValidator(this->m_numberValidator);

	//this->m_highByteValue->SetMaxLength(0);
	//this->m_lowByteValue->SetMaxLength(0);

	this->m_targetVoltage->SetValidator(this->m_numberValidator);
	this->m_targetVoltage->SetMaxLength(4);

#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage0900H::~WritePage0900H(){

}

void WritePage0900H::changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd){
	wxString default_scale;
	wxString CoefficientsSTR = wxT("Coefficients : ");
	wxString PageLabel;

	this->m_dataFormat = dataFormat;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Inherit Class, Data Format = %d", dataFormat);


	PageLabel = wxString::Format("%02x", pmbuscmd->m_register);
	PageLabel.UpperCase();
	PageLabel += wxString::Format("h - %s", pmbuscmd->m_name);

	switch (this->m_dataFormat){

	case cmd_data_format_LinearData_Format:
		PageLabel += wxString::Format("( %s )", wxT("Format : Linear"));

		break;

	case cmd_data_format_DirectData_Format:
		PageLabel += wxString::Format("( %s )", wxT("Format : Direct"));

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs, data format = %d", this->m_dataFormat);
		break;
	}

	this->m_staticBox->SetLabelText(PageLabel);
}


void WritePage0900H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	if (this->m_targetVoltage->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_targetVoltage->GetValue().c_str());

	this->m_targetVoltage->SetMaxLength(4);
	this->m_targetVoltage->SetValue(wxString::Format("%ld", decimal));

#if 0
	if (this->m_highByteValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_highByteValue->GetValue().c_str());

	this->m_highByteValue->SetMaxLength(3);
	this->m_highByteValue->SetValue(wxString::Format("%ld", decimal));

	/* --------------------------- */

	if (this->m_lowByteValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_lowByteValue->GetValue().c_str());

	this->m_lowByteValue->SetMaxLength(3);
	this->m_lowByteValue->SetValue(wxString::Format("%ld", decimal2));

	this->m_highByteValue->SetValidator(this->m_numberValidator);
	this->m_lowByteValue->SetValidator(this->m_numberValidator);
#endif
}

void WritePage0900H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	if (this->m_targetVoltage->GetValue() == wxEmptyString) return;

	double tmp = 0;
	this->m_targetVoltage->GetValue().ToDouble(&tmp);
	wxString hexString = wxString::Format("%02lx", (long)tmp);
	this->m_targetVoltage->SetMaxLength(4);
	this->m_targetVoltage->SetValue(hexString);

#if 0
	if (this->m_highByteValue->GetValue() == wxEmptyString) return;

	double tmp = 0;
	this->m_highByteValue->GetValue().ToDouble(&tmp);
	wxString hexString = wxString::Format("%02lx", (long)tmp);
	this->m_highByteValue->SetMaxLength(2);
	this->m_highByteValue->SetValue(hexString);

	/* --------------------------- */

	if (this->m_lowByteValue->GetValue() == wxEmptyString) return;

	double tmp2 = 0;
	this->m_lowByteValue->GetValue().ToDouble(&tmp2);
	wxString hexString2 = wxString::Format("%02lx", (long)tmp2);
	this->m_lowByteValue->SetMaxLength(2);
	this->m_lowByteValue->SetValue(hexString2);

	this->m_highByteValue->SetValidator(this->m_hexValidator);
	this->m_lowByteValue->SetValidator(this->m_hexValidator);
#endif

}

void WritePage0900H::OnTargetVoltage(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
	// Vout=(13/4095)*Vc+18V
	double inputValue = 0;
	double computedVoltage = 0;

	if (this->m_rawRadioButton->GetValue() == true){
		inputValue = (unsigned short)PMBUSHelper::HexToDecimal(this->m_targetVoltage->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", (int)inputValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_targetVoltage->GetValue().ToDouble(&inputValue);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", (int)inputValue);
	}

	if(inputValue <= 0) inputValue=0;

	if(inputValue > 4095){

		wxMessageBox(wxT("Vc Can't Large Than 4095"),
			wxT("Warning ! Vc Out of Range !"),
			wxOK | wxICON_WARNING);

		inputValue = 0x277;

		if (this->m_rawRadioButton->GetValue() == true){
			wxString hexString_target_voltage = wxString::Format("%02lx", (long)inputValue);
			this->m_targetVoltage->SetValue(hexString_target_voltage);
		}
		else if (this->m_cookRadioButton->GetValue() == true){
			wxString default_target_voltage = wxString::Format("%d", (unsigned short)inputValue);
			this->m_targetVoltage->SetValue(default_target_voltage);
		}

	}

	computedVoltage = inputValue * (13.0f/4095.0f) + 18;

	this->m_computedVoltage->SetLabel(wxString::Format("= %.1f(V)",computedVoltage));


}

#define CMD_0900H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage0900H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	double highByteValue = 0;
	double lowByteValue = 0;
	double targetVoltage = 0;
	double scale;

	if (this->m_rawRadioButton->GetValue() == true){
		targetVoltage = (unsigned short)PMBUSHelper::HexToDecimal(this->m_targetVoltage->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", (int)targetVoltage);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_targetVoltage->GetValue().ToDouble(&targetVoltage);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", (int)targetVoltage);
	}

#if 0
	if (this->m_rawRadioButton->GetValue() == true){
		highByteValue = (unsigned char)PMBUSHelper::HexToDecimal(this->m_highByteValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", (int)highByteValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_highByteValue->GetValue().ToDouble(&highByteValue);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", (int)highByteValue);
	}

	if (this->m_rawRadioButton->GetValue() == true){
		lowByteValue = (unsigned char)PMBUSHelper::HexToDecimal(this->m_highByteValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", (int)lowByteValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_highByteValue->GetValue().ToDouble(&lowByteValue);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", (int)lowByteValue);
	}
#endif

	unsigned char cmdDATA[2];

	switch (this->m_dataFormat){

	case cmd_data_format_LinearData_Format:
		// Don't Support Linear Data Format
		break;

	case cmd_data_format_DirectData_Format:
		cmdDATA[0] = (((unsigned short)targetVoltage & (0xff00)) >> 8);
		cmdDATA[1] = (unsigned short)targetVoltage & (0x00ff);

		//cmdDATA[0] = (unsigned char)highByteValue & (0x00ff);
		//cmdDATA[1] = (unsigned char)highByteValue & (0x00ff);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer2BytesLengthCMD(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		SELF_CMD, // CMD
		cmdDATA,
		sizeof(cmdDATA)
		);

	PMBUSSendCOMMAND_t CMD0900H;

	CMD0900H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMD0900H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_0900H_BYTES_TO_READ);
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD0900H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD0900H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %ld", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD0900H);
	}

}

wxBEGIN_EVENT_TABLE(WritePage0900H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage0900H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage0900H::OnRadioButtonRaw)
EVT_TEXT(CID_TEXTCTRL_TARGET_VOLTAGE, WritePage0900H::OnTargetVoltage)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage0900H::OnButtonWrite)
wxEND_EVENT_TABLE()
