/**
 * @file ReadPage06H.cpp
 */
#include "PMBUSCMDReadPages.h"

#define DEFAULT_PAGE  0x00/**< Default Page */
#define DEFAULT_CMD   0x79/**< Default CMD */

ReadPage06H::ReadPage06H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseReadPage(parent, label){
	// Initial Input Fields
	m_page = new wxStaticText(this, wxID_ANY, wxString(L"PAGE"), wxDefaultPosition, wxSize(-1, -1));
	m_pageInputValue = new wxTextCtrl(this, wxID_ANY);
	wxString pageSTR = wxString::Format("%d", DEFAULT_PAGE);
	m_pageInputValue->SetValue(pageSTR);

	m_cmd = new wxStaticText(this, wxID_ANY, wxString(L"CMD"), wxDefaultPosition, wxSize(-1, -1));
	m_cmdInputValue = new wxTextCtrl(this, wxID_ANY);
	wxString maskSTR = wxString::Format("%d", DEFAULT_CMD);
	m_cmdInputValue->SetValue(maskSTR);

	m_padding = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));

	// Initial Sizer
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_horizonSizer3 = new wxBoxSizer(wxHORIZONTAL);

	// Add Components To Sizer
	this->m_horizonSizer2->Add(m_page, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer2->Add(m_pageInputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_horizonSizer3->Add(m_cmd, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer3->Add(m_cmdInputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);
	this->m_staticBoxlSizer->Add(this->m_padding);
	this->m_staticBoxlSizer->Add(this->m_horizonSizer3);

	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	// Set Validator
	this->m_pageInputValue->SetValidator(this->m_numberValidator);
	this->m_cmdInputValue->SetValidator(this->m_numberValidator);

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

ReadPage06H::~ReadPage06H(){

}


void ReadPage06H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_pageInputValue->SetValidator(this->m_numberValidator);

	if (this->m_pageInputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_pageInputValue->GetValue().c_str());

	this->m_pageInputValue->SetValue(wxString::Format("%ld", decimal));

	/* ------------------- */

	this->m_cmdInputValue->SetValidator(this->m_numberValidator);

	if (this->m_cmdInputValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_cmdInputValue->GetValue().c_str());

	this->m_cmdInputValue->SetValue(wxString::Format("%ld", decimal2));

}

void ReadPage06H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->m_pageInputValue->SetValidator(this->m_hexValidator);

	if (this->m_pageInputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_pageInputValue->GetValue()));
	this->m_pageInputValue->SetValue(hexString);

	/* ------------------- */

	this->m_cmdInputValue->SetValidator(this->m_hexValidator);

	if (this->m_cmdInputValue->GetValue() == wxEmptyString) return;

	wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_cmdInputValue->GetValue()));
	this->m_cmdInputValue->SetValue(hexString2);

}

#define SELF_CMD  0x06
void ReadPage06H::OnButtonSet(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%p", PMBUSHelper::getPMBUSCMDData());

	unsigned char page = 0;
	unsigned char cmd = 0;

	double page_double = 0;
	double cmd_double = 0;

	// Raw
	if (this->m_rawRadioButton->GetValue() == true){
		page = (unsigned char)PMBUSHelper::HexToDecimal(this->m_pageInputValue->GetValue().c_str());
		cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_cmdInputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, page = %02x, cmd = %02x", page, cmd);
	}
	// Cook
	else if (this->m_cookRadioButton->GetValue() == true){
		this->m_pageInputValue->GetValue().ToDouble(&page_double);
		page = (unsigned char)page_double;

		this->m_cmdInputValue->GetValue().ToDouble(&cmd_double);
		cmd = (unsigned char)cmd_double;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Cook, page = %d, cmd = %d", page, cmd);
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

	if(Index < 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not find index of CMD %02x", SELF_CMD);
		return;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Index of %02x is %d", SELF_CMD, Index);
	}

	// Setup New PAGE & CMD Value
	PMBUSHelper::getPMBUSCMDData()[Index].m_cmdStatus.m_AddtionalData[1] = page;
	PMBUSHelper::getPMBUSCMDData()[Index].m_cmdStatus.m_AddtionalData[2] = cmd;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Set New PAGE = %02x, New CMD = %02x", page, cmd);

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
	ExpectedResponseDataLength = PMBUSHelper::getPMBUSCMDData()[cmdIndex].m_responseDataLength + 1;// +1 = + Block Size Byte
	PSU_DEBUG_PRINT(MSG_DEBUG, "New Expected Response Data Length is %d", ExpectedResponseDataLength);

	// Setup New Expected Response Data Length
	PSU_DEBUG_PRINT(MSG_DEBUG, "Set New Expected Response Data Length, old=%02x mew=%02x", PMBUSHelper::getPMBUSCMDData()[Index].m_responseDataLength, ExpectedResponseDataLength);
	PMBUSHelper::getPMBUSCMDData()[Index].m_responseDataLength = ExpectedResponseDataLength;

	PSU_DEBUG_PRINT(MSG_ALERT, "Set PAGE_PLUS_READ PAGE to %02xH, CMD to %02xH", page, cmd);

}

wxBEGIN_EVENT_TABLE(ReadPage06H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, ReadPage06H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, ReadPage06H::OnRadioButtonRaw)
EVT_BUTTON(CID_BUTTON_SET, ReadPage06H::OnButtonSet)
wxEND_EVENT_TABLE()