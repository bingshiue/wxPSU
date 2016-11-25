/**
 * @file WritePage46H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_VALUE        200/**< Default Value */
#define DEFAULT_SCALE_VALUE  0.25/**< Defaut Scale Value */

#define WRITE_PAGES_46H_DEFAULT_FORMAT_HEX  FALSE

WritePage46H::WritePage46H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_hintName = new wxStaticText(this, wxID_ANY, wxString(L"Value"), wxDefaultPosition, wxSize(80, -1));
	m_scale = new wxStaticText(this, wxID_ANY, wxString(L"Exponent"), wxDefaultPosition, wxSize(80, -1));
	m_inputValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
	m_scaleValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));

	wxString default_scale = wxString::Format("%.2f", DEFAULT_SCALE_VALUE);
	m_scaleValue->SetValue(default_scale);

	// Initial Sizer
	this->m_gridSizer_1 = new wxGridSizer(1, 4, 0, 0);

	// Add Components To Sizer
	this->m_gridSizer_1->Add(m_hintName, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_inputValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scale, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_gridSizer_1->Add(m_scaleValue, 1, wxALIGN_CENTER_VERTICAL, 10);
	this->m_staticBoxlSizer->Add(this->m_gridSizer_1);

#if WRITE_PAGES_46H_DEFAULT_FORMAT_HEX == TRUE
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

	this->m_scaleValue->SetValidator(this->m_numberValidator);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage46H::~WritePage46H(){

}

void WritePage46H::changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd){
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

		// Enable 'Exponent Text Ctrl'
		this->m_scaleValue->Enable(true);

		default_scale = wxString::Format("%.2f", DEFAULT_SCALE_VALUE);
		m_scaleValue->SetValue(default_scale);

		if (m_coefficientsST != NULL){
			m_coefficientsST->SetLabel(wxT(""));
		}

		break;

	case cmd_data_format_DirectData_Format:
		PageLabel += wxString::Format("( %s )", wxT("Format : Direct"));

		// Disable 'Exponent Text Ctrl'
		this->m_scaleValue->Enable(false);

		m_scaleValue->SetValue(wxT("Not Use"));

		if (m_coefficientsST == NULL){
			
			m_coefficientsST = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxDefaultSize);

			CoefficientsSTR += wxString::Format(" m=%d,  b=%d,  R=%d", pmbuscmd->m_dataFormat.m_WriteCoefficients.m_M, pmbuscmd->m_dataFormat.m_WriteCoefficients.m_B, pmbuscmd->m_dataFormat.m_WriteCoefficients.m_R);

			m_coefficientsST->SetLabel(CoefficientsSTR);

			if (m_stPadding_6 == NULL){
				m_stPadding_6 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
			}

			this->m_staticBoxlSizer->Add(m_stPadding_6);

			this->m_staticBoxlSizer->Add(this->m_coefficientsST, wxSizerFlags().Align(wxALIGN_LEFT));
		}
		else{

			CoefficientsSTR += wxString::Format(" m=%d,  b=%d,  R=%d", pmbuscmd->m_dataFormat.m_WriteCoefficients.m_M, pmbuscmd->m_dataFormat.m_WriteCoefficients.m_B, pmbuscmd->m_dataFormat.m_WriteCoefficients.m_R);

			m_coefficientsST->SetLabel(CoefficientsSTR);
		}
	

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs, data format = %d", this->m_dataFormat);
		break;
	}

	this->m_staticBox->SetLabelText(PageLabel);
}

void WritePage46H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_numberValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());

	this->m_inputValue->SetValue(wxString::Format("%ld", decimal));

	/* --------------------------- */

	//this->m_scaleValue->SetValidator(this->m_numberValidator);

	//if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	//long decimal2 = PMBUSHelper::HexToDecimal(this->m_scaleValue->GetValue().c_str());

	//this->m_scaleValue->SetValue(wxString::Format("%ld", decimal2));

}

void WritePage46H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_inputValue->SetValidator(this->m_hexValidator);

	if (this->m_inputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_inputValue->GetValue()));
	this->m_inputValue->SetValue(hexString);

	/* --------------------------- */

	//this->m_scaleValue->SetValidator(this->m_hexValidator);

	//if (this->m_scaleValue->GetValue() == wxEmptyString) return;

	//wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_scaleValue->GetValue()));
	//this->m_scaleValue->SetValue(hexString2);

}

#define CMD_46H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage46H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	double iOutOCFaultLimitValue = 0;
	double scale;

	if (this->m_rawRadioButton->GetValue() == true){
		iOutOCFaultLimitValue = (unsigned int)PMBUSHelper::HexToDecimal(this->m_inputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, Value = %f", iOutOCFaultLimitValue);
	}
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_inputValue->GetValue().ToDouble(&iOutOCFaultLimitValue);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, Value = %f", iOutOCFaultLimitValue);
	}

	// Get Scale Value
	if (this->m_dataFormat == cmd_data_format_LinearData_Format){
		this->m_scaleValue->GetValue().ToDouble(&scale);
	}

#if 0
	unsigned char SendBuffer[9] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x6A, 0x00, 0x00, 0x00, 0x0D, 0x0A
	};

	PMBUSHelper::ProductLinearData(SendBuffer + 4, poutOPWarnValue, scale);

	unsigned char separate_pec = 0;;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 4);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	SendBuffer[6] = separate_pec;
#endif

	unsigned char iOutOCFaultLimitValueArray[2];

	switch (this->m_dataFormat){

	case cmd_data_format_LinearData_Format:
		PMBUSHelper::ProductLinearData(iOutOCFaultLimitValueArray, (double)iOutOCFaultLimitValue, scale);

		break;

	case cmd_data_format_DirectData_Format:
		PMBUSHelper::ProductDirectData(iOutOCFaultLimitValueArray, (double)iOutOCFaultLimitValue, 
			&(PMBUSHelper::getPMBUSCMDData()[PMBUSHelper::getIndexOfCMD(PMBUSCMD_46H_IOUT_OC_FAULT_LIMIT)])
		);

		//PSU_DEBUG_PRINT(MSG_DETAIL, "%02xH", PMBUSHelper::getPMBUSCMDData()[PMBUSHelper::getIndexOfCMD(PMBUSCMD_46H_IOUT_OC_FAULT_LIMIT)].m_register);

		break;

	default:

		break;
	}

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x46, // CMD
		iOutOCFaultLimitValueArray,
		sizeof(iOutOCFaultLimitValueArray)
		);

	PMBUSSendCOMMAND_t CMD46H;

	CMD46H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMD46H.m_bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_46H_BYTES_TO_READ : CMD_46H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD46H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD46H);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD46H);
	}

}

wxBEGIN_EVENT_TABLE(WritePage46H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage46H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage46H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage46H::OnButtonWrite)
wxEND_EVENT_TABLE()