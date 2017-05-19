/**
 * @file ReadPage30H.cpp
 */
#include "PMBUSCMDReadPages.h"

#define DEFAULT_CMD   DEF_30H_READ_CMD_BYTE/**< Default CMD */
#define DEFAULT_RW    DEF_30H_READ_RW_BYTE/**< Default RW */

ReadPage30H::ReadPage30H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseReadPage(parent, label){
	// Initial Input Fields
	m_cmd = new wxStaticText(this, wxID_ANY, wxString(L"CMD"), wxDefaultPosition, wxSize(-1, -1));
	m_cmdInputValue = new wxTextCtrl(this, wxID_ANY);

	m_rw = new wxStaticText(this, wxID_ANY, wxString(L"R/W"), wxDefaultPosition, wxSize(-1, -1));
	m_rwInputValue = new wxTextCtrl(this, wxID_ANY);

	m_padding = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_horizonSizer3 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_cmd, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer2->Add(m_cmdInputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_horizonSizer3->Add(m_rw, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer3->Add(m_rwInputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);
	this->m_staticBoxlSizer->Add(this->m_padding);
	this->m_staticBoxlSizer->Add(this->m_horizonSizer3);

#if READ_PAGES_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	wxString hexString = wxString::Format("%02x", DEFAULT_CMD);
	this->m_cmdInputValue->SetValue(hexString);

	wxString hexString2 = wxString::Format("%02x", DEFAULT_RW);
	this->m_rwInputValue->SetValue(hexString2);

	// Set Validator
	this->m_cmdInputValue->SetValidator(this->m_hexValidator);
	this->m_rwInputValue->SetValidator(this->m_hexValidator);

#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString cmdSTR = wxString::Format("%d", DEFAULT_CMD);
	m_cmdInputValue->SetValue(cmdSTR);

	wxString rwSTR = wxString::Format("%d", DEFAULT_RW);
	m_rwInputValue->SetValue(rwSTR);

	// Set Validator
	this->m_cmdInputValue->SetValidator(this->m_numberValidator);
	this->m_rwInputValue->SetValidator(this->m_numberValidator);

#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

ReadPage30H::~ReadPage30H(){

}


void ReadPage30H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_cmdInputValue->SetValidator(this->m_numberValidator);

	if (this->m_cmdInputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_cmdInputValue->GetValue().c_str());

	this->m_cmdInputValue->SetValue(wxString::Format("%ld", decimal));

	/* ------------------- */

	this->m_rwInputValue->SetValidator(this->m_numberValidator);

	if (this->m_rwInputValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_rwInputValue->GetValue().c_str());

	this->m_rwInputValue->SetValue(wxString::Format("%ld", decimal2));

}

void ReadPage30H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_cmdInputValue->SetValidator(this->m_hexValidator);

	if (this->m_cmdInputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_cmdInputValue->GetValue()));
	this->m_cmdInputValue->SetValue(hexString);

	/* ------------------- */

	this->m_rwInputValue->SetValidator(this->m_hexValidator);

	if (this->m_rwInputValue->GetValue() == wxEmptyString) return;

	wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_rwInputValue->GetValue()));
	this->m_rwInputValue->SetValue(hexString2);

}

#define SELF_CMD  0x30
void ReadPage30H::OnButtonSet(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%p", PMBUSHelper::getPMBUSCMDData());

	unsigned char cmd = 0;
	unsigned char rw = 0;

	double cmd_double = 0;
	double rw_double = 0;

	// Raw
	if (this->m_rawRadioButton->GetValue() == true){
		cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_cmdInputValue->GetValue().c_str());
		rw = (unsigned char)PMBUSHelper::HexToDecimal(this->m_rwInputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, cmd = %02x, rw = %02x", cmd, rw);
	}
	// Cook
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_cmdInputValue->GetValue().ToDouble(&cmd_double);
		cmd = (unsigned char)cmd_double;

		this->m_rwInputValue->GetValue().ToDouble(&rw_double);
		rw = (unsigned char)rw_double;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, cmd = %d, rw = %d", cmd, rw);
	}

	/*** Set New PAGE & CMD Value ***/
	// Get Index 
	int Index = -1;
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == SELF_CMD){
			Index = idx;
			break;
		}
	}

	if (Index < 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not find index of CMD %02x", SELF_CMD);
		return;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Index of %02x is %d", SELF_CMD, Index);
	}

	// Setup New PAGE & CMD Value
	PMBUSHelper::getPMBUSCMDData()[Index].m_cmdStatus.m_AddtionalData[1] = cmd;
	PMBUSHelper::getPMBUSCMDData()[Index].m_cmdStatus.m_AddtionalData[2] = rw;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Set New CMD = %02x, New RW = %02x", cmd, rw);

#if 0
	// Update Expected Response Data Length
	// Find index of 'cmd'
	int cmdIndex = -1;
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == cmd){
			cmdIndex = idx;
			break;
		}
	}

	if (cmdIndex < 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not find index of New CMD %02x", cmd);
		return;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Index of New CMD is %d", cmdIndex);
	}

	int ExpectedResponseDataLength = 0;
	ExpectedResponseDataLength = PMBUSHelper::getPMBUSCMDData()[cmdIndex].m_responseDataLength;
	PSU_DEBUG_PRINT(MSG_DEBUG, "New Expected Response Data Length is %d", ExpectedResponseDataLength);

	// Setup New Expected Response Data Length
	PSU_DEBUG_PRINT(MSG_DEBUG, "Set New Expected Response Data Length, old=%02x mew=%02x", PMBUSHelper::getPMBUSCMDData()[Index].m_responseDataLength, ExpectedResponseDataLength);
	PMBUSHelper::getPMBUSCMDData()[Index].m_responseDataLength = ExpectedResponseDataLength;
#endif

	PSU_DEBUG_PRINT(MSG_ALERT, "Set COEFFICIENTS CMD to %02xH, RW to %02xH", cmd, rw);

}

wxBEGIN_EVENT_TABLE(ReadPage30H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, ReadPage30H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, ReadPage30H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_SET, ReadPage30H::OnButtonSet)
wxEND_EVENT_TABLE()
