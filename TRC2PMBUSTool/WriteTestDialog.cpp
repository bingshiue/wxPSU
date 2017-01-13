/**
 * @file WriteTestDialog.cpp
 */

#include "WriteTestDialog.h"
#include "Task.h"

#define WRITE_TEST_DIALOG_WIDTH   1024
#define WRITE_TEST_DIALOG_HEIGHT   600

#define WRITE_TEST_DIALOG_TC_WIDTH  30

#define DEF_SET_1_SLAVE_ADDR    wxT("B6")
#define DEF_SET_1_CMD           wxT("00")
#define DEF_SET_1_WRITE_BYTES          1
#define DEF_SET_1_WRITE_BYTE_1  wxT("00")
#define DEF_SET_1_WRITE_BYTE_2  wxT("00")
#define DEF_SET_1_WRITE_BYTE_3  wxT("00")
#define DEF_SET_1_WRITE_BYTE_4  wxT("00")
#define DEF_SET_1_WRITE_BYTE_5  wxT("00")

#define DEF_SET_2_SLAVE_ADDR    wxT("B6")
#define DEF_SET_2_CMD           wxT("3A")
#define DEF_SET_2_WRITE_BYTES          1
#define DEF_SET_2_WRITE_BYTE_1  wxT("D4")
#define DEF_SET_2_WRITE_BYTE_2  wxT("00")
#define DEF_SET_2_WRITE_BYTE_3  wxT("00")
#define DEF_SET_2_WRITE_BYTE_4  wxT("00")
#define DEF_SET_2_WRITE_BYTE_5  wxT("00")

#define DEF_SET_3_SLAVE_ADDR    wxT("B6")
#define DEF_SET_3_CMD           wxT("3B")
#define DEF_SET_3_WRITE_BYTES		   2
#define DEF_SET_3_WRITE_BYTE_1  wxT("00")
#define DEF_SET_3_WRITE_BYTE_2  wxT("38")
#define DEF_SET_3_WRITE_BYTE_3  wxT("00")
#define DEF_SET_3_WRITE_BYTE_4  wxT("00")
#define DEF_SET_3_WRITE_BYTE_5  wxT("00")

#define DEF_SET_4_SLAVE_ADDR    wxT("B6")
#define DEF_SET_4_CMD           wxT("05")
#define DEF_SET_4_WRITE_BYTES          5
#define DEF_SET_4_WRITE_BYTE_1  wxT("04")
#define DEF_SET_4_WRITE_BYTE_2  wxT("00")
#define DEF_SET_4_WRITE_BYTE_3  wxT("1b")
#define DEF_SET_4_WRITE_BYTE_4  wxT("7a")
#define DEF_SET_4_WRITE_BYTE_5  wxT("90")

WriteTestDialog::WriteTestDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : wxDialog(parent, wxID_ANY, wxString(wxT("Customize PMBUS Write CMD Test")), wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_WIDTH, WRITE_TEST_DIALOG_HEIGHT)){

	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

	// Setup Text Validator
	DecCharIncludes = wxT("0123456789");
	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

	m_decValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decValidator.SetCharIncludes(DecCharIncludes);

	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_optionsSBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Options"));
	m_set1SBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Set 1 (Input Format : Hexdecimal)"));
	m_set2SBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Set 2 (Input Format : Hexdecimal)"));
	m_set3SBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Set 3 (Input Format : Hexdecimal)"));
	m_set4SBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Set 4 (Input Format : Hexdecimal)"));
	m_btnSizer = new wxBoxSizer(wxHORIZONTAL);

	m_setCountSelectST = new wxStaticText(m_optionsSBS->GetStaticBox(), wxID_ANY, wxT("Sets To Run"), wxDefaultPosition, wxDefaultSize);
	m_setCountSelectCB = new wxComboBox(m_optionsSBS->GetStaticBox(), CID_SET_COUNT_SELECT_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	for (unsigned int idx = 0; idx < MAX_SET_COUNT; idx++){
		m_setCountSelectCB->Append(wxString::Format("%d", idx + 1));
	}
	m_setCountSelectCB->Select(0);

	m_outputLogCheckBox = new wxCheckBox(m_optionsSBS->GetStaticBox(), CID_OUTPUT_LOG_CHECKBOX, wxT("Output Log"));
	this->m_outputLog = false;
	m_outputLogCheckBox->SetValue(this->m_outputLog);

	m_intervalTimeST = new wxStaticText(m_optionsSBS->GetStaticBox(), wxID_ANY, wxT("Interval Time"), wxDefaultPosition, wxDefaultSize);
	m_intervalTimeTC = new wxTextCtrl(m_optionsSBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(50, -1));
	m_intervalTimeTC->SetMaxLength(4);
	m_intervalTimeTC->SetValidator(m_decValidator);

	m_intervalTimeUnitST = new wxStaticText(m_optionsSBS->GetStaticBox(), wxID_ANY, wxT("Millisecond"), wxDefaultPosition, wxDefaultSize);

	m_optionsSBS->Add(m_setCountSelectST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_setCountSelectCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_outputLogCheckBox, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_intervalTimeST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_intervalTimeTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_intervalTimeUnitST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 1 Components Initialize
	m_Set1SlaveAddrST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set1CMDST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set1NumOfSendBytesST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("Num of Send Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set1SendByte1ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set1SendByte2ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set1SendByte3ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set1SendByte4ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA4"), wxDefaultPosition, wxDefaultSize);
	m_Set1SendByte5ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA5"), wxDefaultPosition, wxDefaultSize);

	m_Set1SlaveAddrTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_SLAVE_ADDR, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH,-1));
	m_Set1CMDTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_CMD, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1SendBytesCB = new wxComboBox(m_set1SBS->GetStaticBox(), CID_SET_1_SEND_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set1SendBytesCB->Append(wxString::Format("%d", idx+1));
	}
	m_Set1SendBytesCB->Select(DEF_SET_1_WRITE_BYTES-1);

	m_Set1SendByte1TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_1, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1SendByte2TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_2, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1SendByte3TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_3, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1SendByte4TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_4, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1SendByte5TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_5, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));

	m_Set1SendByteTCArray[0] = m_Set1SendByte1TC;
	m_Set1SendByteTCArray[1] = m_Set1SendByte2TC;
	m_Set1SendByteTCArray[2] = m_Set1SendByte3TC;
	m_Set1SendByteTCArray[3] = m_Set1SendByte4TC;
	m_Set1SendByteTCArray[4] = m_Set1SendByte5TC;

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx >= DEF_SET_1_WRITE_BYTES){
			m_Set1SendByteTCArray[idx]->Enable(false);
		}
	}

	m_Set1SlaveAddrTC->SetMaxLength(2);
	m_Set1CMDTC->SetMaxLength(2);
	m_Set1SendByte1TC->SetMaxLength(2);
	m_Set1SendByte2TC->SetMaxLength(2);
	m_Set1SendByte3TC->SetMaxLength(2);
	m_Set1SendByte4TC->SetMaxLength(2);
	m_Set1SendByte5TC->SetMaxLength(2);

	m_Set1SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set1CMDTC->SetValidator(m_hexValidator);
	m_Set1SendByte1TC->SetValidator(m_hexValidator);
	m_Set1SendByte2TC->SetValidator(m_hexValidator);
	m_Set1SendByte3TC->SetValidator(m_hexValidator);
	m_Set1SendByte4TC->SetValidator(m_hexValidator);
	m_Set1SendByte5TC->SetValidator(m_hexValidator);

	m_set1SBS->Add(m_Set1SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1NumOfSendBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte4ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte4TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte5ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SendByte5TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 2 Components Initialize
	m_Set2SlaveAddrST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set2CMDST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set2NumOfSendBytesST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Num of Send Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set2SendByte1ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set2SendByte2ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set2SendByte3ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set2SendByte4ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA4"), wxDefaultPosition, wxDefaultSize);
	m_Set2SendByte5ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA5"), wxDefaultPosition, wxDefaultSize);

	m_Set2SlaveAddrTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_SLAVE_ADDR, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2CMDTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_CMD, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2SendBytesCB = new wxComboBox(m_set2SBS->GetStaticBox(), CID_SET_2_SEND_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set2SendBytesCB->Append(wxString::Format("%d", idx+1));
	}
	m_Set2SendBytesCB->Select(DEF_SET_2_WRITE_BYTES - 1);

	m_Set2SendByte1TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_1, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2SendByte2TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_2, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2SendByte3TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_3, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2SendByte4TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_4, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2SendByte5TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_5, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));

	m_Set2SendByteTCArray[0] = m_Set2SendByte1TC;
	m_Set2SendByteTCArray[1] = m_Set2SendByte2TC;
	m_Set2SendByteTCArray[2] = m_Set2SendByte3TC;
	m_Set2SendByteTCArray[3] = m_Set2SendByte4TC;
	m_Set2SendByteTCArray[4] = m_Set2SendByte5TC;

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx >= DEF_SET_2_WRITE_BYTES){
			m_Set2SendByteTCArray[idx]->Enable(false);
		}
	}

	m_Set2SlaveAddrTC->SetMaxLength(2);
	m_Set2CMDTC->SetMaxLength(2);
	m_Set2SendByte1TC->SetMaxLength(2);
	m_Set2SendByte2TC->SetMaxLength(2);
	m_Set2SendByte3TC->SetMaxLength(2);
	m_Set2SendByte4TC->SetMaxLength(2);
	m_Set2SendByte5TC->SetMaxLength(2);

	m_Set2SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set2CMDTC->SetValidator(m_hexValidator);
	m_Set2SendByte1TC->SetValidator(m_hexValidator);
	m_Set2SendByte2TC->SetValidator(m_hexValidator);
	m_Set2SendByte3TC->SetValidator(m_hexValidator);
	m_Set2SendByte4TC->SetValidator(m_hexValidator);
	m_Set2SendByte5TC->SetValidator(m_hexValidator);

	m_set2SBS->Add(m_Set2SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2NumOfSendBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte4ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte4TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte5ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SendByte5TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 3 Components Initialize
	m_Set3SlaveAddrST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set3CMDST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set3NumOfSendBytesST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Num of Send Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set3SendByte1ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set3SendByte2ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set3SendByte3ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set3SendByte4ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA4"), wxDefaultPosition, wxDefaultSize);
	m_Set3SendByte5ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA5"), wxDefaultPosition, wxDefaultSize);

	m_Set3SlaveAddrTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_SLAVE_ADDR, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3CMDTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_CMD, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3SendBytesCB = new wxComboBox(m_set3SBS->GetStaticBox(), CID_SET_3_SEND_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set3SendBytesCB->Append(wxString::Format("%d", idx+1));
	}
	m_Set3SendBytesCB->Select(DEF_SET_3_WRITE_BYTES - 1);

	m_Set3SendByte1TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_1, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3SendByte2TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_2, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3SendByte3TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_3, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3SendByte4TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_4, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3SendByte5TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_5, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));

	m_Set3SendByteTCArray[0] = m_Set3SendByte1TC;
	m_Set3SendByteTCArray[1] = m_Set3SendByte2TC;
	m_Set3SendByteTCArray[2] = m_Set3SendByte3TC;
	m_Set3SendByteTCArray[3] = m_Set3SendByte4TC;
	m_Set3SendByteTCArray[4] = m_Set3SendByte5TC;

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx >= DEF_SET_3_WRITE_BYTES){
			m_Set3SendByteTCArray[idx]->Enable(false);
		}
	}

	m_Set3SlaveAddrTC->SetMaxLength(2);
	m_Set3CMDTC->SetMaxLength(2);
	m_Set3SendByte1TC->SetMaxLength(2);
	m_Set3SendByte2TC->SetMaxLength(2);
	m_Set3SendByte3TC->SetMaxLength(2);
	m_Set3SendByte4TC->SetMaxLength(2);
	m_Set3SendByte5TC->SetMaxLength(2);

	m_Set3SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set3CMDTC->SetValidator(m_hexValidator);
	m_Set3SendByte1TC->SetValidator(m_hexValidator);
	m_Set3SendByte2TC->SetValidator(m_hexValidator);
	m_Set3SendByte3TC->SetValidator(m_hexValidator);
	m_Set3SendByte4TC->SetValidator(m_hexValidator);
	m_Set3SendByte5TC->SetValidator(m_hexValidator);

	m_set3SBS->Add(m_Set3SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3NumOfSendBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte4ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte4TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte5ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SendByte5TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 4 Components Initialize
	m_Set4SlaveAddrST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set4CMDST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set4NumOfSendBytesST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Num of Send Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set4SendByte1ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set4SendByte2ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set4SendByte3ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set4SendByte4ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA4"), wxDefaultPosition, wxDefaultSize);
	m_Set4SendByte5ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA5"), wxDefaultPosition, wxDefaultSize);

	m_Set4SlaveAddrTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_SLAVE_ADDR, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4CMDTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_CMD, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4SendBytesCB = new wxComboBox(m_set4SBS->GetStaticBox(), CID_SET_4_SEND_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set4SendBytesCB->Append(wxString::Format("%d", idx+1));
	}
	m_Set4SendBytesCB->Select(DEF_SET_4_WRITE_BYTES - 1);

	m_Set4SendByte1TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_1, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4SendByte2TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_2, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4SendByte3TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_3, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4SendByte4TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_4, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4SendByte5TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_5, wxDefaultPosition, wxSize(WRITE_TEST_DIALOG_TC_WIDTH, -1));

	m_Set4SendByteTCArray[0] = m_Set4SendByte1TC;
	m_Set4SendByteTCArray[1] = m_Set4SendByte2TC;
	m_Set4SendByteTCArray[2] = m_Set4SendByte3TC;
	m_Set4SendByteTCArray[3] = m_Set4SendByte4TC;
	m_Set4SendByteTCArray[4] = m_Set4SendByte5TC;

	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx >= DEF_SET_4_WRITE_BYTES){
			m_Set4SendByteTCArray[idx]->Enable(false);
		}
	}

	m_Set4SlaveAddrTC->SetMaxLength(2);
	m_Set4CMDTC->SetMaxLength(2);
	m_Set4SendByte1TC->SetMaxLength(2);
	m_Set4SendByte2TC->SetMaxLength(2);
	m_Set4SendByte3TC->SetMaxLength(2);
	m_Set4SendByte4TC->SetMaxLength(2);
	m_Set4SendByte5TC->SetMaxLength(2);

	m_Set4SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set4CMDTC->SetValidator(m_hexValidator);
	m_Set4SendByte1TC->SetValidator(m_hexValidator);
	m_Set4SendByte2TC->SetValidator(m_hexValidator);
	m_Set4SendByte3TC->SetValidator(m_hexValidator);
	m_Set4SendByte4TC->SetValidator(m_hexValidator);
	m_Set4SendByte5TC->SetValidator(m_hexValidator);

	m_set4SBS->Add(m_Set4SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4NumOfSendBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte4ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte4TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte5ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SendByte5TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	//
	m_stline1 = new wxStaticLine(this);
	m_stline2 = new wxStaticLine(this);

	m_btnSTART = new wxButton(this, CID_BTN_START, wxT("START"));
	m_btnSTOP = new wxButton(this, CID_BTN_STOP, wxT("STOP"));

	m_logTC = new PMBUSLogTextCtrl(this, wxID_ANY);

	// Add Components To Sizer
	m_btnSizer->Add(m_btnSTART);
	m_btnSizer->Add(m_btnSTOP);


	m_topLevelSizer->Add(m_optionsSBS, wxSizerFlags().Expand().Border());

	m_topLevelSizer->Add(m_set1SBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_set2SBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_set3SBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_set4SBS, wxSizerFlags().Expand().Border());

	m_topLevelSizer->Add(m_stline1, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_btnSizer, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_stline2, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_logTC, wxSizerFlags(1).Expand().Border());

	this->m_btnSTART->Enable(true);
	this->m_btnSTOP->Enable(false);

	EnableTextCtrlBySelect(this->m_setCountSelectCB->GetSelection());

	SetSizer(m_topLevelSizer);

}

WriteTestDialog::~WriteTestDialog(){

	PMBUSReadTestTask* pmbusReadTestTask = NULL;
	pmbusReadTestTask = (PMBUSReadTestTask*)TaskEx::GetTask(task_ID_PMBUSReadTestTask, 0);

	if (pmbusReadTestTask != NULL){
		pmbusReadTestTask->m_running = false;
	}

	wxLog::SetActiveTarget(m_oldLog);
}

void WriteTestDialog::OnBtnSTART(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	int intervalTime = wxAtoi(this->m_intervalTimeTC->GetValue());
	if (intervalTime <= 0) intervalTime = 0;

	this->SetupWriteCMDArray();

	if (TaskEx::GetCount(task_ID_PMBUSWriteTestTask) == 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Create PMBUSWriteTestTask Task");
		new(TP_PMBUSWriteTestTask)PMBUSWriteTestTask(this->m_ioaccess, this->m_currentIO, this->m_pmbusWriteCMDArray, this->m_setCountSelectCB->GetSelection(), &this->m_outputLog, intervalTime);
		this->m_btnSTART->Enable(false);
		this->m_btnSTOP->Enable(true);
		this->m_setCountSelectCB->Enable(false);
		this->m_outputLogCheckBox->Enable(false);
		this->DisableAllTextCtrl();

		this->m_logTC->Clear();
		PSU_DEBUG_PRINT(MSG_ALERT, "Start To Send Write CMD");
		PSU_DEBUG_PRINT(MSG_ALERT, "Interval Time is %d Millisecond", intervalTime);

	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "Another One PMBUSWriteTestTask Task is Running");
	}

}

void WriteTestDialog::OnBtnSTOP(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	PMBUSWriteTestTask* pmbusWriteTestTask = NULL;
	pmbusWriteTestTask = (PMBUSWriteTestTask*)TaskEx::GetTask(task_ID_PMBUSWriteTestTask, 0);

	if (pmbusWriteTestTask != NULL){
		pmbusWriteTestTask->m_running = false;

		this->m_btnSTART->Enable(true);
		this->m_btnSTOP->Enable(false);
		this->m_setCountSelectCB->Enable(true);
		this->m_outputLogCheckBox->Enable(true);
		this->EnableTextCtrlBySelect(this->m_setCountSelectCB->GetSelection());
	}

}

void WriteTestDialog::OnSetCountSelectCB(wxCommandEvent& event){
	int cnt_select = this->m_setCountSelectCB->GetSelection();

	switch (cnt_select){

	case 0:// Set Count Select is 1
	case 1:// Set Count Select is 2
	case 2:// Set Count Select is 3
	case 3:// Set Count Select is 4

		EnableTextCtrlBySelect(cnt_select);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

}

void WriteTestDialog::OnOutputLogCheckBox(wxCommandEvent& event){

	if (this->m_outputLogCheckBox->GetValue() == true){
		this->m_outputLog = true;
	}
	else{
		this->m_outputLog = false;
	}

}

void WriteTestDialog::OnSet1SendBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx > this->m_Set1SendBytesCB->GetSelection()){
			m_Set1SendByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set1SendByteTCArray[idx]->Enable(true);
		}
	}
}

void WriteTestDialog::OnSet2SendBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx > this->m_Set2SendBytesCB->GetSelection()){
			m_Set2SendByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set2SendByteTCArray[idx]->Enable(true);
		}
	}
}

void WriteTestDialog::OnSet3SendBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx > this->m_Set3SendBytesCB->GetSelection()){
			m_Set3SendByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set3SendByteTCArray[idx]->Enable(true);
		}
	}
}

void WriteTestDialog::OnSet4SendBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		if (idx > this->m_Set4SendBytesCB->GetSelection()){
			m_Set4SendByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set4SendByteTCArray[idx]->Enable(true);
		}
	}
}

void WriteTestDialog::EnableTextCtrlBySelect(int select){

	switch (select){

	case 0:// Set Count Select is 1

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set1SendBytesCB->GetSelection()){
				m_Set1SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1SendByteTCArray[idx]->Enable(true);
			}
		}


		m_Set2SlaveAddrTC->Enable(false);
		m_Set2CMDTC->Enable(false);
		m_Set2SendBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			m_Set2SendByteTCArray[idx]->Enable(false);
		}

		m_Set3SlaveAddrTC->Enable(false);
		m_Set3CMDTC->Enable(false);
		m_Set3SendBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			m_Set3SendByteTCArray[idx]->Enable(false);
		}

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4SendBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			m_Set4SendByteTCArray[idx]->Enable(false);
		}

		break;

	case 1:// Set Count Select is 2

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set1SendBytesCB->GetSelection()){
				m_Set1SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set2SendBytesCB->GetSelection()){
				m_Set2SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set2SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set3SlaveAddrTC->Enable(false);
		m_Set3CMDTC->Enable(false);
		m_Set3SendBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			m_Set3SendByteTCArray[idx]->Enable(false);
		}

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4SendBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			m_Set4SendByteTCArray[idx]->Enable(false);
		}

		break;

	case 2:// Set Count Select is 3

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set1SendBytesCB->GetSelection()){
				m_Set1SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set2SendBytesCB->GetSelection()){
				m_Set2SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set2SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set3SlaveAddrTC->Enable(true);
		m_Set3CMDTC->Enable(true);
		m_Set3SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set3SendBytesCB->GetSelection()){
				m_Set3SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set3SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4SendBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			m_Set4SendByteTCArray[idx]->Enable(false);
		}

		break;

	case 3:// Set Count Select is 4

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set1SendBytesCB->GetSelection()){
				m_Set1SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set2SendBytesCB->GetSelection()){
				m_Set2SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set2SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set3SlaveAddrTC->Enable(true);
		m_Set3CMDTC->Enable(true);
		m_Set3SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set3SendBytesCB->GetSelection()){
				m_Set3SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set3SendByteTCArray[idx]->Enable(true);
			}
		}

		m_Set4SlaveAddrTC->Enable(true);
		m_Set4CMDTC->Enable(true);
		m_Set4SendBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
			if (idx > this->m_Set4SendBytesCB->GetSelection()){
				m_Set4SendByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set4SendByteTCArray[idx]->Enable(true);
			}
		}

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

}

void WriteTestDialog::DisableAllTextCtrl(void){

	m_Set1SlaveAddrTC->Enable(false);
	m_Set1CMDTC->Enable(false);
	m_Set1SendBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set1SendByteTCArray[idx]->Enable(false);
	}

	m_Set2SlaveAddrTC->Enable(false);
	m_Set2CMDTC->Enable(false);
	m_Set2SendBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set2SendByteTCArray[idx]->Enable(false);
	}

	m_Set3SlaveAddrTC->Enable(false);
	m_Set3CMDTC->Enable(false);
	m_Set3SendBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set3SendByteTCArray[idx]->Enable(false);
	}

	m_Set4SlaveAddrTC->Enable(false);
	m_Set4CMDTC->Enable(false);
	m_Set4SendBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_SEND_DATA_BYTES; idx++){
		m_Set4SendByteTCArray[idx]->Enable(false);
	}

}

void WriteTestDialog::SetupWriteCMDArray(void){

	this->m_pmbusWriteCMDArray[0].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1SlaveAddrTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[0].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1CMDTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[0].m_numOfSendBytes = (unsigned char)this->m_Set1SendBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusWriteCMDArray[0].m_numOfSendBytes; idx++){
		this->m_pmbusWriteCMDArray[0].m_sendBytes[idx] = PMBUSHelper::HexToDecimal(m_Set1SendByteTCArray[idx]->GetValue().c_str());
	}


	this->m_pmbusWriteCMDArray[1].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2SlaveAddrTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[1].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2CMDTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[1].m_numOfSendBytes = (unsigned char)this->m_Set2SendBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusWriteCMDArray[1].m_numOfSendBytes; idx++){
		this->m_pmbusWriteCMDArray[1].m_sendBytes[idx] = PMBUSHelper::HexToDecimal(m_Set2SendByteTCArray[idx]->GetValue().c_str());
	}


	this->m_pmbusWriteCMDArray[2].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3SlaveAddrTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[2].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3CMDTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[2].m_numOfSendBytes = (unsigned char)this->m_Set3SendBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusWriteCMDArray[2].m_numOfSendBytes; idx++){
		this->m_pmbusWriteCMDArray[2].m_sendBytes[idx] = PMBUSHelper::HexToDecimal(m_Set3SendByteTCArray[idx]->GetValue().c_str());
	}


	this->m_pmbusWriteCMDArray[3].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4SlaveAddrTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[3].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4CMDTC->GetValue().c_str());
	this->m_pmbusWriteCMDArray[3].m_numOfSendBytes = (unsigned char)this->m_Set4SendBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusWriteCMDArray[3].m_numOfSendBytes; idx++){
		this->m_pmbusWriteCMDArray[3].m_sendBytes[idx] = PMBUSHelper::HexToDecimal(m_Set4SendByteTCArray[idx]->GetValue().c_str());
	}

}

void WriteTestDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	PMBUSWriteTestTask* pmbusWriteTestTask = NULL;
	pmbusWriteTestTask = (PMBUSWriteTestTask*)TaskEx::GetTask(task_ID_PMBUSWriteTestTask, 0);

	if (pmbusWriteTestTask != NULL){
		pmbusWriteTestTask->m_running = false;
	}

	while (TaskEx::GetCount(task_ID_PMBUSWriteTestTask) != 0){
		wxMilliSleep(100);
	}

	this->EndModal(wxID_CANCEL);

}

void WriteTestDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
{

	switch (level) {

	case wxLOG_FatalError:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
	case wxLOG_Error:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
		//case wxLOG_Warning:
		//break;
		//case wxLOG_Message:
		//break;
		//case wxLOG_Status:
		//break;
		//case wxLOG_Info:
		//break;
		//case wxLOG_Debug:
		//break;

	default:
		text->SetDefaultStyle(wxTextAttr(*wxBLUE, *wxWHITE));
		break;
	}

#ifdef _DEBUG

	//text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));
	text->AppendText(wxString::Format("%-8s   %s", threadstr, msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s %10s           %s", timestr, threadstr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#else
	//text->AppendText(wxString::Format("%9s           %s", timestr, msg));
	text->AppendText(wxString::Format("%-s", msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s           %s", timestr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#endif
}

void WriteTestDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
#if 0
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}
#endif

	DoLogLine(
		level,
		this->m_logTC,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
		);

}

wxBEGIN_EVENT_TABLE(WriteTestDialog, wxDialog)
EVT_BUTTON(CID_BTN_START, WriteTestDialog::OnBtnSTART)
EVT_BUTTON(CID_BTN_STOP, WriteTestDialog::OnBtnSTOP)
EVT_COMBOBOX(CID_SET_COUNT_SELECT_COMBOBOX, WriteTestDialog::OnSetCountSelectCB)
EVT_CHECKBOX(CID_OUTPUT_LOG_CHECKBOX, WriteTestDialog::OnOutputLogCheckBox)
EVT_COMBOBOX(CID_SET_1_SEND_BYTES_COMBOBOX, WriteTestDialog::OnSet1SendBytesCB)
EVT_COMBOBOX(CID_SET_2_SEND_BYTES_COMBOBOX, WriteTestDialog::OnSet2SendBytesCB)
EVT_COMBOBOX(CID_SET_3_SEND_BYTES_COMBOBOX, WriteTestDialog::OnSet3SendBytesCB)
EVT_COMBOBOX(CID_SET_4_SEND_BYTES_COMBOBOX, WriteTestDialog::OnSet4SendBytesCB)
EVT_CLOSE(WriteTestDialog::OnDialogClose)
wxEND_EVENT_TABLE()