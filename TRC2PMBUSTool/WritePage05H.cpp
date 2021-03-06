/**
 * @file WritePage05H.cpp
 */

#include "PMBUSCMDWritePages.h"

#define DEFAULT_PAGE  0x00/**< Default PAGE */
#define DEFAULT_CMD   0x1b/**< Default CMD */
#define DEFAULT_DATA1 0x7a/**< Default DATA 1 */
#define DEFAULT_DATA2 0x90/**< Default DATA 2 */

WritePage05H::WritePage05H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO) : BaseWritePage(parent, label){
	// Initial Input Fields
	m_pageST = new wxStaticText(this, wxID_ANY, wxString(L"PAGE"), wxDefaultPosition, wxSize(-1, -1));
	//m_pageTC = new wxTextCtrl(this, wxID_ANY);
	//m_pagePaddingST = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1));
	m_pageCB = new wxComboBox(this, CID_PAGE_COMBOBOX);

	wxString pageSTR = wxString::Format("%d", DEFAULT_PAGE);
	//m_pageTC->SetValue(pageSTR);
	m_pageCB->Append(wxT("0"));
	m_pageCB->Append(wxT("1"));
	m_pageCB->Select(0);

	m_cmdST = new wxStaticText(this, wxID_ANY, wxString(L"CMD"), wxDefaultPosition, wxSize(-1, -1));
	m_cmdTC = new wxTextCtrl(this, wxID_ANY);
	
	m_dataCountST = new wxStaticText(this, wxID_ANY, wxString(L"DATA BYTES"), wxDefaultPosition, wxSize(-1, -1));
	//m_dataCountPaddingST = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(41, -1));
	m_dataCountCB = new wxComboBox(this, CID_DATA_COUNT_COMBOBOX);
	m_dataCountCB->Append(wxT("1"));
	m_dataCountCB->Append(wxT("2"));
	m_dataCountCB->Select(1);

	m_data1 = new wxStaticText(this, wxID_ANY, wxString(L"DATA 1"), wxDefaultPosition, wxSize(-1, -1));
	m_data1InputValue = new wxTextCtrl(this, wxID_ANY);

	m_data2 = new wxStaticText(this, wxID_ANY, wxString(L"DATA 2"), wxDefaultPosition, wxSize(-1, -1));
	m_data2InputValue = new wxTextCtrl(this, wxID_ANY);

	if (m_dataCountCB->GetSelection() == 0){
		m_data2InputValue->Enable(false);
	}

#if 0
	m_padding = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));
	m_padding2 = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));
	m_padding3 = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));
	m_padding4 = new wxStaticText(this, wxID_ANY, wxString(L""), wxDefaultPosition, wxSize(100, 10));
#endif

	// Initial Sizer
	this->m_fieldGridSizer = new wxGridSizer(5, 2, 10, 10);

#if 0
	this->m_pageSizer = new wxBoxSizer(wxHORIZONTAL);
	this->m_cmdSizer = new wxBoxSizer(wxHORIZONTAL);
	this->m_dataCountSZ = new wxBoxSizer(wxHORIZONTAL);
	this->m_horizonSizer2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_horizonSizer3 = new wxBoxSizer(wxHORIZONTAL);
#endif

	// Add Components To Sizer
	this->m_fieldGridSizer->Add(m_pageST, 1, wxALIGN_CENTER_VERTICAL);
	this->m_fieldGridSizer->Add(m_pageCB, 1, wxALIGN_CENTER_VERTICAL);

	this->m_fieldGridSizer->Add(m_cmdST, 1, wxALIGN_CENTER_VERTICAL);
	this->m_fieldGridSizer->Add(m_cmdTC, 1, wxALIGN_CENTER_VERTICAL);

	this->m_fieldGridSizer->Add(m_dataCountST, 0, wxALIGN_CENTER_VERTICAL);
	//this->m_fieldGridSizer->Add(m_dataCountPaddingST, 0, wxALIGN_CENTER_VERTICAL);
	this->m_fieldGridSizer->Add(m_dataCountCB, 0, wxALIGN_CENTER_VERTICAL);

	this->m_fieldGridSizer->Add(m_data1, 1, wxALIGN_CENTER_VERTICAL);
	this->m_fieldGridSizer->Add(m_data1InputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_fieldGridSizer->Add(m_data2, 1, wxALIGN_CENTER_VERTICAL);
	this->m_fieldGridSizer->Add(m_data2InputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_staticBoxlSizer->Add(this->m_fieldGridSizer);

#if 0
	this->m_pageSizer->Add(m_pageST, 0, wxALIGN_CENTER_VERTICAL);
	//this->m_pageSizer->Add(m_pagePaddingST, 0, wxALIGN_CENTER_VERTICAL);
	this->m_pageSizer->Add(m_pageCB, 0, wxALIGN_CENTER_VERTICAL);

	this->m_cmdSizer->Add(m_cmdST, 1, wxALIGN_CENTER_VERTICAL);
	this->m_cmdSizer->Add(m_cmdTC, 1, wxALIGN_CENTER_VERTICAL);

	this->m_dataCountSZ->Add(m_dataCountST, 0, wxALIGN_CENTER_VERTICAL);
	this->m_dataCountSZ->Add(m_dataCountPaddingST, 0, wxALIGN_CENTER_VERTICAL);
	this->m_dataCountSZ->Add(m_dataCountCB, 0, wxALIGN_CENTER_VERTICAL);

	this->m_horizonSizer2->Add(m_data1, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer2->Add(m_data1InputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_horizonSizer3->Add(m_data2, 1, wxALIGN_CENTER_VERTICAL);
	this->m_horizonSizer3->Add(m_data2InputValue, 1, wxALIGN_CENTER_VERTICAL);

	this->m_staticBoxlSizer->Add(this->m_pageSizer);
	this->m_staticBoxlSizer->Add(this->m_padding3);
	this->m_staticBoxlSizer->Add(this->m_cmdSizer);
	this->m_staticBoxlSizer->Add(this->m_padding2);
	this->m_staticBoxlSizer->Add(this->m_dataCountSZ);
	this->m_staticBoxlSizer->Add(this->m_padding4);
	this->m_staticBoxlSizer->Add(this->m_horizonSizer2);
	this->m_staticBoxlSizer->Add(this->m_padding);
	this->m_staticBoxlSizer->Add(this->m_horizonSizer3);
#endif

#if WRITE_PAGES_DEFAULT_FORMAT_HEX == TRUE
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(false);
	this->m_rawRadioButton->SetValue(true);

	wxString hexString3 = wxString::Format("%02x", DEFAULT_CMD);
	this->m_cmdTC->SetValue(hexString3);

	wxString hexString = wxString::Format("%02x", DEFAULT_DATA1);
	this->m_data1InputValue->SetValue(hexString);

	wxString hexString2 = wxString::Format("%02x", DEFAULT_DATA2);
	this->m_data2InputValue->SetValue(hexString2);

	// Set Validator
	//this->m_pageTC->SetValidator(this->m_numberValidator);
	this->m_cmdTC->SetValidator(this->m_hexValidator);
	this->m_data1InputValue->SetValidator(this->m_hexValidator);
	this->m_data2InputValue->SetValidator(this->m_hexValidator);

#else
	// Set Default Value of Radio Buttons
	this->m_cookRadioButton->SetValue(true);
	this->m_rawRadioButton->SetValue(false);

	wxString cmdSTR = wxString::Format("%d", DEFAULT_CMD);
	m_cmdTC->SetValue(cmdSTR);

	wxString codeSTR = wxString::Format("%d", DEFAULT_DATA1);
	m_data1InputValue->SetValue(codeSTR);

	wxString maskSTR = wxString::Format("%d", DEFAULT_DATA2);
	m_data2InputValue->SetValue(maskSTR);

	// Set Validator
	//this->m_pageTC->SetValidator(this->m_numberValidator);
	this->m_cmdTC->SetValidator(this->m_numberValidator);
	this->m_data1InputValue->SetValidator(this->m_numberValidator);
	this->m_data2InputValue->SetValidator(this->m_numberValidator);

#endif

	// Save Member
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

}

WritePage05H::~WritePage05H(){

}


void WritePage05H::OnRadioButtonCook(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

#if 0
	this->m_pageTC->SetValidator(this->m_numberValidator);

	if (this->m_pageTC->GetValue() == wxEmptyString) return;

	long decimal4 = PMBUSHelper::HexToDecimal(this->m_pageTC->GetValue().c_str());

	this->m_pageTC->SetValue(wxString::Format("%ld", decimal4));
#endif

	/* ------------------- */
	
	this->m_cmdTC->SetValidator(this->m_numberValidator);

	if (this->m_cmdTC->GetValue() == wxEmptyString) return;

	long decimal3 = PMBUSHelper::HexToDecimal(this->m_cmdTC->GetValue().c_str());

	this->m_cmdTC->SetValue(wxString::Format("%ld", decimal3));

	/* ------------------- */
	
	this->m_data1InputValue->SetValidator(this->m_numberValidator);

	if (this->m_data1InputValue->GetValue() == wxEmptyString) return;

	long decimal = PMBUSHelper::HexToDecimal(this->m_data1InputValue->GetValue().c_str());

	this->m_data1InputValue->SetValue(wxString::Format("%ld", decimal));

	/* ------------------- */

	this->m_data2InputValue->SetValidator(this->m_numberValidator);

	if (this->m_data2InputValue->GetValue() == wxEmptyString) return;

	long decimal2 = PMBUSHelper::HexToDecimal(this->m_data2InputValue->GetValue().c_str());

	this->m_data2InputValue->SetValue(wxString::Format("%ld", decimal2));

}

void WritePage05H::OnRadioButtonRaw(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

#if 0
	this->m_pageTC->SetValidator(this->m_hexValidator);

	if (this->m_pageTC->GetValue() == wxEmptyString) return;

	wxString hexString4 = wxString::Format("%02lx", wxAtoi(this->m_pageTC->GetValue()));
	this->m_pageTC->SetValue(hexString4);
#endif

	/* ------------------- */

	this->m_cmdTC->SetValidator(this->m_hexValidator);

	if (this->m_cmdTC->GetValue() == wxEmptyString) return;

	wxString hexString3 = wxString::Format("%02lx", wxAtoi(this->m_cmdTC->GetValue()));
	this->m_cmdTC->SetValue(hexString3);

	/* ------------------- */
	
	this->m_data1InputValue->SetValidator(this->m_hexValidator);

	if (this->m_data1InputValue->GetValue() == wxEmptyString) return;

	wxString hexString = wxString::Format("%02lx", wxAtoi(this->m_data1InputValue->GetValue()));
	this->m_data1InputValue->SetValue(hexString);

	/* ------------------- */

	this->m_data2InputValue->SetValidator(this->m_hexValidator);

	if (this->m_data2InputValue->GetValue() == wxEmptyString) return;

	wxString hexString2 = wxString::Format("%02lx", wxAtoi(this->m_data2InputValue->GetValue()));
	this->m_data2InputValue->SetValue(hexString2);

}

void WritePage05H::OnPageComboBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void WritePage05H::OnDataCountComboBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	if (m_dataCountCB->GetSelection() == 0){
		this->m_data2InputValue->Enable(false);
	}
	else if (m_dataCountCB->GetSelection() == 1){
		this->m_data2InputValue->Enable(true);
	}

}

#define CMD_05H_BYTES_TO_READ  6/**< Bytes To Read */
void WritePage05H::OnButtonWrite(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	unsigned char page = 0;
	unsigned char cmd  = 0;
	unsigned char data1 = 0;
	unsigned char data2 = 0;

	double page_double = 0;
	double cmd_double  = 0;
	double data1_double = 0;
	double data2_double = 0;

	// Get Page

	switch (this->m_pageCB->GetSelection()){

	case 0:
		page = 0;
		break;

	case 1:
		page = 1;
		break;


	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}


	// Raw
	if (this->m_rawRadioButton->GetValue() == true){
		//page = (unsigned char)PMBUSHelper::HexToDecimal(this->m_pageTC->GetValue().c_str());
		cmd  = (unsigned char)PMBUSHelper::HexToDecimal(this->m_cmdTC->GetValue().c_str());
		data1 = (unsigned char)PMBUSHelper::HexToDecimal(this->m_data1InputValue->GetValue().c_str());
		data2 = (unsigned char)PMBUSHelper::HexToDecimal(this->m_data2InputValue->GetValue().c_str());
		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, cmd = %02x, data1 = %02x, data2 = %02x", cmd, data1, data2);
	}
	// Cook
	else if (this->m_cookRadioButton->GetValue() == true){

		//this->m_pageTC->GetValue().ToDouble(&page_double);
		//page = (unsigned char)page_double;

		this->m_cmdTC->GetValue().ToDouble(&cmd_double);
		cmd  = (unsigned char)cmd_double;
		
		this->m_data1InputValue->GetValue().ToDouble(&data1_double);
		data1 = (unsigned char)data1_double;

		this->m_data2InputValue->GetValue().ToDouble(&data2_double);
		data2 = (unsigned char)data2_double;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Select Raw, cmd = %d, data1 = %d, data2 = %d", cmd, data1, data2);
	}

	unsigned char smbAlertValueArray[5];
	smbAlertValueArray[0] = (m_dataCountCB->GetSelection() == 0) ? 3 : 4; // block count
	smbAlertValueArray[1] = page; // page
	smbAlertValueArray[2] = cmd;  // command code
	smbAlertValueArray[3] = data1;
	smbAlertValueArray[4] = data2;

	unsigned char SendBuffer[64];
	unsigned int sendDataLength = PMBUSHelper::ProductWriteCMDBuffer(
		m_currentIO,
		SendBuffer,
		sizeof(SendBuffer),
		0x05, // CMD
		smbAlertValueArray,
		(m_dataCountCB->GetSelection() == 0) ? 4 : 5//sizeof(smbAlertValueArray)
		);

	PMBUSSendCOMMAND_t CMD05H;

	CMD05H.m_sendDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE) ? sendDataLength : 64;//sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMD05H.m_bytesToRead = PMBUSHelper::GetBytesToReadOfWriteCMD(*this->m_currentIO, CMD_05H_BYTES_TO_READ);//(*this->m_currentIO == IOACCESS_SERIALPORT) ? CMD_05H_BYTES_TO_READ : CMD_05H_BYTES_TO_READ + 1;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMD05H.m_sendData[idx] = SendBuffer[idx];
	}

	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(CMD05H);
			PSU_DEBUG_PRINT(MSG_DEBUG, "Size of m_sendCMDVector is %ld", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, CMD05H);
	}

}

wxBEGIN_EVENT_TABLE(WritePage05H, wxPanel)
EVT_RADIOBUTTON(CID_RADIO_BOX_COOK, WritePage05H::OnRadioButtonCook)
EVT_RADIOBUTTON(CID_RADIO_BOX_RAW, WritePage05H::OnRadioButtonRaw)
EVT_COMBOBOX(CID_PAGE_COMBOBOX, WritePage05H::OnPageComboBox)
EVT_COMBOBOX(CID_DATA_COUNT_COMBOBOX, WritePage05H::OnDataCountComboBox)
EVT_BUTTON(CID_BUTTON_WRITE, WritePage05H::OnButtonWrite)
wxEND_EVENT_TABLE()
