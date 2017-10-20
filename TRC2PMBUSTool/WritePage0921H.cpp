/**
 * @file WritePage0921H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define SELF_CMD  0x0921/**< Self Command */

#define DEFAULT_HIGH_BYTE_VALUE    445/**< Default high byte Value */
#define DEFAULT_LOW_BYTE_VALUE    0x00/**< Default low  byte Value */

#define WRITE_PAGES_0921H_DEFAULT_FORMAT_HEX  FALSE//TRUE//FALSE

#define MAX_INPUT_VALUE   1000/**< Max Input Value */
#define MIN_INPUT_VALUE    100/**< Min Input Value */

WritePage0921H::WritePage0921H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Value"), wxDefaultPosition, wxSize(80, -1));
	//m_scale = new wxStaticText(this, wxID_ANY, wxString(L"Low Byte"), wxDefaultPosition, wxSize(80, -1));

	wxString descriptionStr = wxString::Format(L"¿é¤J½d³ò : %d(0x%04X) ~ %d(0x%04X)", 
		PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMin, PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMin, 
		PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMax, PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMax);
	m_cmdDescription = new wxStaticText(this, wxID_ANY, descriptionStr, wxDefaultPosition, wxSize(-1, -1));

	m_highByteValue = new wxTextCtrl(this, CID_TEXTCTRL_TARGET_VALUE, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
	//m_lowByteValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	m_stPadding_6 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));

	this->m_numberValidator.SetCharIncludes(wxT("0123456789"));

	// Initial Sizer
	this->m_gridSizer_1 = new wxGridSizer(1, 4, 0, 0);

	// Add Components To Sizer
	this->m_gridSizer_1->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_highByteValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	//this->m_gridSizer_1->Add(m_scale, 1, wxALIGN_CENTER_VERTICAL, 10);
	//this->m_gridSizer_1->Add(m_lowByteValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_staticBoxlSizer->Add(this->m_gridSizer_1);

	this->m_staticBoxlSizer->Add(m_stPadding_6);

	this->m_staticBoxlSizer->Add(this->m_cmdDescription);

#if WRITE_PAGES_0921H_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	wxString hexString_high_byte = wxString::Format("%02lx", (long)PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageInput);//DEFAULT_HIGH_BYTE_VALUE);
	this->m_highByteValue->SetValue(hexString_high_byte);

	//wxString hexString_low_byte = wxString::Format("%02lx", (long)DEFAULT_LOW_BYTE_VALUE);
	//this->m_lowByteValue->SetValue(hexString_low_byte);

	// Set Validator
	this->m_highByteValue->SetValidator(this->m_hexValidator);
	//this->m_lowByteValue->SetValidator(this->m_hexValidator);

	this->m_highByteValue->SetMaxLength(4);
	//this->m_lowByteValue->SetMaxLength(2);

#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString default_high_byte = wxString::Format("%d", PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageInput);//DEFAULT_HIGH_BYTE_VALUE);
	this->m_highByteValue->SetValue(default_high_byte);

	//wxString default_low_byte = wxString::Format("%d", DEFAULT_LOW_BYTE_VALUE);
	//m_lowByteValue->SetValue(default_low_byte);

	// Set Validator
	this->m_highByteValue->SetValidator(this->m_numberValidator);
	//this->m_lowByteValue->SetValidator(this->m_numberValidator);

	this->m_highByteValue->SetMaxLength(5);
	//this->m_lowByteValue->SetMaxLength(0);
#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage0921H::~WritePage0921H(){

}

void WritePage0921H::changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd){
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


void WritePage0921H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	if (this->m_highByteValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_highByteValue->GetValue().c_str());

	this->m_highByteValue->SetMaxLength(5);
	this->m_highByteValue->SetValue(wxString::Format("%ld", decimal));

	/* --------------------------- */

	//if (this->m_lowByteValue->GetValue() == wxEmptyString) return;

	//long decimal2 = PMBUSHelper::HexToDecimal(this->m_lowByteValue->GetValue().c_str());

	//this->m_lowByteValue->SetMaxLength(3);
	//this->m_lowByteValue->SetValue(wxString::Format("%ld", decimal2));

	this->m_highByteValue->SetValidator(this->m_numberValidator);
	//this->m_lowByteValue->SetValidator(this->m_numberValidator);

}

void WritePage0921H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	if (this->m_highByteValue->GetValue() == wxEmptyString) return;

	double tmp = 0;
	this->m_highByteValue->GetValue().ToDouble(&tmp);
	wxString hexString = wxString::Format("%02lx", (long)tmp);
	this->m_highByteValue->SetMaxLength(4);
	this->m_highByteValue->SetValue(hexString);

	/* --------------------------- */

	//if (this->m_lowByteValue->GetValue() == wxEmptyString) return;

	//double tmp2 = 0;
	//this->m_lowByteValue->GetValue().ToDouble(&tmp2);
	//wxString hexString2 = wxString::Format("%02lx", (long)tmp2);
	//this->m_lowByteValue->SetMaxLength(2);
	//this->m_lowByteValue->SetValue(hexString2);

	this->m_highByteValue->SetValidator(this->m_hexValidator);
	//this->m_lowByteValue->SetValidator(this->m_hexValidator);

}

void WritePage0921H::OnTargetValue(wxCommandEvent& event) {
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	double inputValue = 0;

	if (this->m_rawRadioButton->GetValue() == true) {
		inputValue = (unsigned short)PMBUSHelper::HexToDecimal(this->m_highByteValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, Value = %d", (int)inputValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true) {
		this->m_highByteValue->GetValue().ToDouble(&inputValue);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, Value = %d", (int)inputValue);
	}

#if 0
	if (inputValue <= 0) inputValue = 0;

	if (inputValue > MAX_INPUT_VALUE) {

		wxString msg = wxString::Format("Input Value Can't Large Than %d", MAX_INPUT_VALUE);

		wxMessageBox(msg,
			wxT("Warning ! Input Value Out of Range !"),
			wxOK | wxICON_WARNING);

		inputValue = DEFAULT_HIGH_BYTE_VALUE;

		if (this->m_rawRadioButton->GetValue() == true) {
			wxString hexString_target_value = wxString::Format("%02lx", (long)inputValue);
			this->m_highByteValue->SetValue(hexString_target_value);
		}
		else if (this->m_cookRadioButton->GetValue() == true) {
			wxString hexString_target_value = wxString::Format("%d", (int)inputValue);
			this->m_highByteValue->SetValue(hexString_target_value);
		}

	}
#endif

}

#define CMD_0921H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage0921H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	double highByteValue = 0;
	double lowByteValue = 0;
	//double scale;

	if (this->m_rawRadioButton->GetValue() == true){
		highByteValue = (unsigned short)PMBUSHelper::HexToDecimal(this->m_highByteValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", (int)highByteValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_highByteValue->GetValue().ToDouble(&highByteValue);
		PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", (int)highByteValue);
	}

	//if (this->m_rawRadioButton->GetValue() == true){
		//lowByteValue = (unsigned char)PMBUSHelper::HexToDecimal(this->m_lowByteValue->GetValue().c_str());
		//PSU_DEBUG_PRINT(MSG_ALERT, "Select Raw, Value = %d", (int)lowByteValue);
	//}
	//else if (this->m_cookRadioButton->GetValue() == true){
		//this->m_lowByteValue->GetValue().ToDouble(&lowByteValue);
		//PSU_DEBUG_PRINT(MSG_ALERT, "Select Cook, Value = %d", (int)lowByteValue);
	//}

	if (highByteValue <= 0) highByteValue = 0;

	if (highByteValue > PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMax || highByteValue < PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMin) {

		wxString msg = wxString::Format("Warning ! \n\n Input Value Must be in Range of \n %d ~ %d", PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMin, PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageMax);

		wxMessageBox(msg,
			wxT("Warning ! Input Value Out of Range !"),
			wxOK | wxICON_WARNING);

		highByteValue = PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageDefaultInput;//DEFAULT_HIGH_BYTE_VALUE;

		if (this->m_rawRadioButton->GetValue() == true) {
			wxString hexString_target_value = wxString::Format("%02lx", (long)highByteValue);
			this->m_highByteValue->SetValue(hexString_target_value);
		}
		else if (this->m_cookRadioButton->GetValue() == true) {
			wxString hexString_target_value = wxString::Format("%d", (int)highByteValue);
			this->m_highByteValue->SetValue(hexString_target_value);
		}

	}

	PMBUSHelper::GetAppSettings()->m_pbf00300gOption.m_0921WritePageInput = highByteValue;

	unsigned char cmdDATA[2];

	switch (this->m_dataFormat){

	case cmd_data_format_LinearData_Format:
		// Don't Support Linear Data Format
		break;

	case cmd_data_format_DirectData_Format:
		cmdDATA[0] = ((unsigned short)highByteValue & 0xff00) >> 8;
		cmdDATA[1] = (unsigned short)highByteValue & (0x00ff);

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

	PMBUSSendCOMMAND_t CMD0921H;

	CMD0921H.m_sendCommand = SELF_CMD;
	CMD0921H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;
	CMD0921H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_0921H_BYTES_TO_READ);
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD0921H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD0921H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %ld", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD0921H, true);
	}

}

wxBEGIN_EVENT_TABLE(WritePage0921H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage0921H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage0921H::OnRadioButtonRaw)
EVT_TEXT(CID_TEXTCTRL_TARGET_VALUE, WritePage0921H::OnTargetValue)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage0921H::OnButtonWrite)
wxEND_EVENT_TABLE()
