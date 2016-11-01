/**
 * @file ReadPage1AH.cpp
 */
#include "PMBUSCMDReadPages.h"

#define DEFAULT_CMD   0x87/**< Default CMD */

ReadPage1AH::ReadPage1AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseReadPage(parent, label){
	// Initial Input Fields
	m_cmd = new wxStaticText(this, wxID_ANY, wxString(L"CMD"), wxDefaultPosition, wxSize(-1, -1));
	m_cmdInputValue = new wxTextCtrl(this, wxID_ANY);
	wxString maskSTR = wxString::Format("%d", DEFAULT_CMD);
	m_cmdInputValue->SetValue(maskSTR);

	//m_padding = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));

	// Initial Sizer
	//this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_horizonSizer3 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer3->Add(m_cmd, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer3->Add(m_cmdInputValue, 1, wxALIGN_CENTER_VERTICAL);

	//this->m_staticBoxlSizer->Add(this->m_horizonSizer2);
	//this->m_staticBoxlSizer->Add(this->m_padding);
	this->m_staticBoxlSizer->Add(this->m_horizonSizer3);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	// Set Validator
	this->m_cmdInputValue->SetValidator(this->m_numberValidator);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

ReadPage1AH::~ReadPage1AH(){

}


void ReadPage1AH::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	/* ------------------- */

	this->m_cmdInputValue->SetValidator(this->m_numberValidator);

	if (this->m_cmdInputValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_cmdInputValue->GetValue().c_str());

	this->m_cmdInputValue->SetValue(wxString::Format("%ld", decimal2));

}

void ReadPage1AH::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	/* ------------------- */

	this->m_cmdInputValue->SetValidator(this->m_hexValidator);

	if (this->m_cmdInputValue->GetValue() == wxEmptyString) return;

	wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_cmdInputValue->GetValue()));
	this->m_cmdInputValue->SetValue(hexString2);

}

#define SELF_CMD  0x1a
void ReadPage1AH::OnButtonSet(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%p", PMBUSHelper::getPMBUSCMDData());

	unsigned char page = 0;
	unsigned char cmd = 0;

	double page_double = 0;
	double cmd_double = 0;

	// Raw
	if (this->m_rawRadioButton->GetValue() == true){
		cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_cmdInputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, cmd = %02x", cmd);
	}
	// Cook
	else if (this->m_cookRadioButton->GetValue() == true){
		page = (unsigned char)page_double;

		this->m_cmdInputValue->GetValue().ToDouble(&cmd_double);
		cmd = (unsigned char)cmd_double;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, cmd = %d", cmd);
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

	// Setup New CMD Value
	PMBUSHelper::getPMBUSCMDData()[Index].m_cmdStatus.m_AddtionalData[1] = cmd;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Set New CMD = %02x", cmd);

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

	PSU_DEBUG_PRINT(MSG_ALERT, "Set QUERY CMD to %02xH", cmd);

}

wxBEGIN_EVENT_TABLE(ReadPage1AH, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, ReadPage1AH::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, ReadPage1AH::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_SET, ReadPage1AH::OnButtonSet)
wxEND_EVENT_TABLE()