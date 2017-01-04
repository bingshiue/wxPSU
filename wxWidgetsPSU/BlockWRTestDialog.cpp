/**
* @file BlockWRTestDialog.cpp
*/

#include "BlockWRTestDialog.h"
#include "Task.h"

#define BLOCK_WR_TEST_DIALOG_WIDTH   1024
#define BLOCK_WR_TEST_DIALOG_HEIGHT   600

#define BLOCK_WR_TEST_DIALOG_TC_WIDTH  30

// Block Write - Block Read 1AH Command
#define DEF_SET_1_SLAVE_ADDR    wxT("B6")
#define DEF_SET_1_CMD           wxT("1A")
#define DEF_SET_1_WRITE_BYTES          1
#define DEF_SET_1_WRITE_BYTE_1  wxT("87")
#define DEF_SET_1_WRITE_BYTE_2  wxT("00")
#define DEF_SET_1_WRITE_BYTE_3  wxT("00")
#define DEF_SET_1_READ_BYTES    wxT("02")

// Block Write - Block Read 1BH Command
#define DEF_SET_2_SLAVE_ADDR    wxT("B6")
#define DEF_SET_2_CMD           wxT("1B")
#define DEF_SET_2_WRITE_BYTES          1
#define DEF_SET_2_WRITE_BYTE_1  wxT("7A")
#define DEF_SET_2_WRITE_BYTE_2  wxT("00")
#define DEF_SET_2_WRITE_BYTE_3  wxT("00")
#define DEF_SET_2_READ_BYTES    wxT("02")

// Block Write - Block Read 30H Command
#define DEF_SET_3_SLAVE_ADDR    wxT("B6")
#define DEF_SET_3_CMD           wxT("30")
#define DEF_SET_3_WRITE_BYTES		   2
#define DEF_SET_3_WRITE_BYTE_1  wxT("86")
#define DEF_SET_3_WRITE_BYTE_2  wxT("01")
#define DEF_SET_3_WRITE_BYTE_3  wxT("00")
#define DEF_SET_3_READ_BYTES    wxT("06")

// Block Write - Block Read 06H Command
#define DEF_SET_4_SLAVE_ADDR    wxT("B6")
#define DEF_SET_4_CMD           wxT("06")
#define DEF_SET_4_WRITE_BYTES          3
#define DEF_SET_4_WRITE_BYTE_1  wxT("00")
#define DEF_SET_4_WRITE_BYTE_2  wxT("1b")
#define DEF_SET_4_WRITE_BYTE_3  wxT("7a")
#define DEF_SET_4_READ_BYTES    wxT("02")

BlockWRTestDialog::BlockWRTestDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : wxDialog(parent, wxID_ANY, wxString(wxT("Customize PMBUS Block WR CMD Test")), wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_WIDTH, BLOCK_WR_TEST_DIALOG_HEIGHT)){

	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

	// Setup Text Validator
	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

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
	this->m_outputLog = true;
	m_outputLogCheckBox->SetValue(this->m_outputLog);

	m_optionsSBS->Add(m_setCountSelectST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_setCountSelectCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_optionsSBS->Add(m_outputLogCheckBox, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 1 Components Initialize
	m_Set1SlaveAddrST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set1CMDST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set1NumOfWriteBytesST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("Num of Write Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set1WriteByte1ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set1WriteByte2ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set1WriteByte3ST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set1NumOfReadBytesST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set1SlaveAddrTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_SLAVE_ADDR, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1CMDTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_CMD, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1WriteBytesCB = new wxComboBox(m_set1SBS->GetStaticBox(), CID_SET_1_WRITE_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set1WriteBytesCB->Append(wxString::Format("%d", idx + 1));
	}
	m_Set1WriteBytesCB->Select(DEF_SET_1_WRITE_BYTES - 1);

	m_Set1WriteByte1TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_1, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1WriteByte2TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_2, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set1WriteByte3TC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_WRITE_BYTE_3, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set1WriteByteTCArray[0] = m_Set1WriteByte1TC;
	m_Set1WriteByteTCArray[1] = m_Set1WriteByte2TC;
	m_Set1WriteByteTCArray[2] = m_Set1WriteByte3TC;

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx >= DEF_SET_1_WRITE_BYTES){
			m_Set1WriteByteTCArray[idx]->Enable(false);
		}
	}

	m_Set1NumOfReadBytesTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_READ_BYTES, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set1SlaveAddrTC->SetMaxLength(2);
	m_Set1CMDTC->SetMaxLength(2);
	m_Set1WriteByte1TC->SetMaxLength(2);
	m_Set1WriteByte2TC->SetMaxLength(2);
	m_Set1WriteByte3TC->SetMaxLength(2);
	m_Set1NumOfReadBytesTC->SetMaxLength(2);

	m_Set1SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set1CMDTC->SetValidator(m_hexValidator);
	m_Set1WriteByte1TC->SetValidator(m_hexValidator);
	m_Set1WriteByte2TC->SetValidator(m_hexValidator);
	m_Set1WriteByte3TC->SetValidator(m_hexValidator);
	m_Set1NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set1SBS->Add(m_Set1SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1NumOfWriteBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1WriteByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());


	// Set 2 Components Initialize
	m_Set2SlaveAddrST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set2CMDST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set2NumOfWriteBytesST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Num of Write Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set2WriteByte1ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set2WriteByte2ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set2WriteByte3ST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set2NumOfReadBytesST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set2SlaveAddrTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_SLAVE_ADDR, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2CMDTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_CMD, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2WriteBytesCB = new wxComboBox(m_set2SBS->GetStaticBox(), CID_SET_2_WRITE_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set2WriteBytesCB->Append(wxString::Format("%d", idx + 1));
	}
	m_Set2WriteBytesCB->Select(DEF_SET_2_WRITE_BYTES - 1);

	m_Set2WriteByte1TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_1, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2WriteByte2TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_2, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set2WriteByte3TC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_WRITE_BYTE_3, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set2WriteByteTCArray[0] = m_Set2WriteByte1TC;
	m_Set2WriteByteTCArray[1] = m_Set2WriteByte2TC;
	m_Set2WriteByteTCArray[2] = m_Set2WriteByte3TC;

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx >= DEF_SET_2_WRITE_BYTES){
			m_Set2WriteByteTCArray[idx]->Enable(false);
		}
	}

	m_Set2NumOfReadBytesTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_READ_BYTES, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set2SlaveAddrTC->SetMaxLength(2);
	m_Set2CMDTC->SetMaxLength(2);
	m_Set2WriteByte1TC->SetMaxLength(2);
	m_Set2WriteByte2TC->SetMaxLength(2);
	m_Set2WriteByte3TC->SetMaxLength(2);
	m_Set2NumOfReadBytesTC->SetMaxLength(2);

	m_Set2SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set2CMDTC->SetValidator(m_hexValidator);
	m_Set2WriteByte1TC->SetValidator(m_hexValidator);
	m_Set2WriteByte2TC->SetValidator(m_hexValidator);
	m_Set2WriteByte3TC->SetValidator(m_hexValidator);
	m_Set2NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set2SBS->Add(m_Set2SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2NumOfWriteBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2WriteByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 3 Components Initialize
	m_Set3SlaveAddrST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set3CMDST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set3NumOfWriteBytesST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Num of Write Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set3WriteByte1ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set3WriteByte2ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set3WriteByte3ST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set3NumOfReadBytesST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set3SlaveAddrTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_SLAVE_ADDR, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3CMDTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_CMD, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3WriteBytesCB = new wxComboBox(m_set3SBS->GetStaticBox(), CID_SET_3_WRITE_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set3WriteBytesCB->Append(wxString::Format("%d", idx + 1));
	}
	m_Set3WriteBytesCB->Select(DEF_SET_3_WRITE_BYTES - 1);

	m_Set3WriteByte1TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_1, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3WriteByte2TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_2, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set3WriteByte3TC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_WRITE_BYTE_3, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set3WriteByteTCArray[0] = m_Set3WriteByte1TC;
	m_Set3WriteByteTCArray[1] = m_Set3WriteByte2TC;
	m_Set3WriteByteTCArray[2] = m_Set3WriteByte3TC;

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx >= DEF_SET_3_WRITE_BYTES){
			m_Set3WriteByteTCArray[idx]->Enable(false);
		}
	}

	m_Set3NumOfReadBytesTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_READ_BYTES, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set3SlaveAddrTC->SetMaxLength(2);
	m_Set3CMDTC->SetMaxLength(2);
	m_Set3WriteByte1TC->SetMaxLength(2);
	m_Set3WriteByte2TC->SetMaxLength(2);
	m_Set3WriteByte3TC->SetMaxLength(2);
	m_Set3NumOfReadBytesTC->SetMaxLength(2);

	m_Set3SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set3CMDTC->SetValidator(m_hexValidator);
	m_Set3WriteByte1TC->SetValidator(m_hexValidator);
	m_Set3WriteByte2TC->SetValidator(m_hexValidator);
	m_Set3WriteByte3TC->SetValidator(m_hexValidator);
	m_Set3NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set3SBS->Add(m_Set3SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3NumOfWriteBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3WriteByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 4 Components Initialize
	m_Set4SlaveAddrST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set4CMDST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set4NumOfWriteBytesST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Num of Write Bytes"), wxDefaultPosition, wxDefaultSize);
	m_Set4WriteByte1ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA1"), wxDefaultPosition, wxDefaultSize);
	m_Set4WriteByte2ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA2"), wxDefaultPosition, wxDefaultSize);
	m_Set4WriteByte3ST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("DATA3"), wxDefaultPosition, wxDefaultSize);
	m_Set4NumOfReadBytesST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set4SlaveAddrTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_SLAVE_ADDR, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4CMDTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_CMD, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4WriteBytesCB = new wxComboBox(m_set4SBS->GetStaticBox(), CID_SET_4_WRITE_BYTES_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set4WriteBytesCB->Append(wxString::Format("%d", idx + 1));
	}
	m_Set4WriteBytesCB->Select(DEF_SET_4_WRITE_BYTES - 1);

	m_Set4WriteByte1TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_1, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4WriteByte2TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_2, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));
	m_Set4WriteByte3TC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_WRITE_BYTE_3, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set4WriteByteTCArray[0] = m_Set4WriteByte1TC;
	m_Set4WriteByteTCArray[1] = m_Set4WriteByte2TC;
	m_Set4WriteByteTCArray[2] = m_Set4WriteByte3TC;

	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx >= DEF_SET_4_WRITE_BYTES){
			m_Set4WriteByteTCArray[idx]->Enable(false);
		}
	}

	m_Set4NumOfReadBytesTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_READ_BYTES, wxDefaultPosition, wxSize(BLOCK_WR_TEST_DIALOG_TC_WIDTH, -1));

	m_Set4SlaveAddrTC->SetMaxLength(2);
	m_Set4CMDTC->SetMaxLength(2);
	m_Set4WriteByte1TC->SetMaxLength(2);
	m_Set4WriteByte2TC->SetMaxLength(2);
	m_Set4WriteByte3TC->SetMaxLength(2);
	m_Set4NumOfReadBytesTC->SetMaxLength(2);

	m_Set4SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set4CMDTC->SetValidator(m_hexValidator);
	m_Set4WriteByte1TC->SetValidator(m_hexValidator);
	m_Set4WriteByte2TC->SetValidator(m_hexValidator);
	m_Set4WriteByte3TC->SetValidator(m_hexValidator);
	m_Set4NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set4SBS->Add(m_Set4SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4NumOfWriteBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteBytesCB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteByte1ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteByte1TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteByte2ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteByte2TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteByte3ST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4WriteByte3TC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

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

BlockWRTestDialog::~BlockWRTestDialog(){

	PMBUSReadTestTask* pmbusReadTestTask = NULL;
	pmbusReadTestTask = (PMBUSReadTestTask*)TaskEx::GetTask(task_ID_PMBUSReadTestTask, 0);

	if (pmbusReadTestTask != NULL){
		pmbusReadTestTask->m_running = false;
	}

	wxLog::SetActiveTarget(m_oldLog);
}

void BlockWRTestDialog::OnBtnSTART(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	this->SetupBlockWRCMDArray();

	if (TaskEx::GetCount(task_ID_PMBUSBlockWRTestTask) == 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Create PMBUSBlockWRTestTask Task");
		new(TP_PMBUSBlockWRTestTask)PMBUSBlockWRTestTask(this->m_ioaccess, this->m_currentIO, this->m_pmbusBlockWRCMDArray, this->m_setCountSelectCB->GetSelection(), &this->m_outputLog);
		this->m_btnSTART->Enable(false);
		this->m_btnSTOP->Enable(true);
		this->m_setCountSelectCB->Enable(false);
		this->m_outputLogCheckBox->Enable(false);
		this->DisableAllTextCtrl();

		this->m_logTC->Clear();
		PSU_DEBUG_PRINT(MSG_ALERT, "Start To Send Write CMD");

	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "Another One PMBUSWriteTestTask Task is Running");
	}

}

void BlockWRTestDialog::OnBtnSTOP(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	PMBUSBlockWRTestTask* pmbusBlockWRTestTask = NULL;
	pmbusBlockWRTestTask = (PMBUSBlockWRTestTask*)TaskEx::GetTask(task_ID_PMBUSBlockWRTestTask, 0);

	if (pmbusBlockWRTestTask != NULL){
		pmbusBlockWRTestTask->m_running = false;

		this->m_btnSTART->Enable(true);
		this->m_btnSTOP->Enable(false);
		this->m_setCountSelectCB->Enable(true);
		this->m_outputLogCheckBox->Enable(true);
		this->EnableTextCtrlBySelect(this->m_setCountSelectCB->GetSelection());
	}

}

void BlockWRTestDialog::OnSetCountSelectCB(wxCommandEvent& event){
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

void BlockWRTestDialog::OnOutputLogCheckBox(wxCommandEvent& event){

	if (this->m_outputLogCheckBox->GetValue() == true){
		this->m_outputLog = true;
	}
	else{
		this->m_outputLog = false;
	}

}

void BlockWRTestDialog::OnSet1WriteBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx > this->m_Set1WriteBytesCB->GetSelection()){
			m_Set1WriteByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set1WriteByteTCArray[idx]->Enable(true);
		}
	}
}

void BlockWRTestDialog::OnSet2WriteBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx > this->m_Set2WriteBytesCB->GetSelection()){
			m_Set2WriteByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set2WriteByteTCArray[idx]->Enable(true);
		}
	}
}

void BlockWRTestDialog::OnSet3WriteBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx > this->m_Set3WriteBytesCB->GetSelection()){
			m_Set3WriteByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set3WriteByteTCArray[idx]->Enable(true);
		}
	}
}

void BlockWRTestDialog::OnSet4WriteBytesCB(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		if (idx > this->m_Set4WriteBytesCB->GetSelection()){
			m_Set4WriteByteTCArray[idx]->Enable(false);
		}
		else{
			m_Set4WriteByteTCArray[idx]->Enable(true);
		}
	}
}

void BlockWRTestDialog::EnableTextCtrlBySelect(int select){

	switch (select){

	case 0:// Set Count Select is 1

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set1WriteBytesCB->GetSelection()){
				m_Set1WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set1NumOfReadBytesTC->Enable(true);


		m_Set2SlaveAddrTC->Enable(false);
		m_Set2CMDTC->Enable(false);
		m_Set2WriteBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			m_Set2WriteByteTCArray[idx]->Enable(false);
		}
		m_Set2NumOfReadBytesTC->Enable(false);

		m_Set3SlaveAddrTC->Enable(false);
		m_Set3CMDTC->Enable(false);
		m_Set3WriteBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			m_Set3WriteByteTCArray[idx]->Enable(false);
		}
		m_Set3NumOfReadBytesTC->Enable(false);

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4WriteBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			m_Set4WriteByteTCArray[idx]->Enable(false);
		}
		m_Set4NumOfReadBytesTC->Enable(false);

		break;

	case 1:// Set Count Select is 2

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set1WriteBytesCB->GetSelection()){
				m_Set1WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set2WriteBytesCB->GetSelection()){
				m_Set2WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set2WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set2NumOfReadBytesTC->Enable(true);

		m_Set3SlaveAddrTC->Enable(false);
		m_Set3CMDTC->Enable(false);
		m_Set3WriteBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			m_Set3WriteByteTCArray[idx]->Enable(false);
		}
		m_Set3NumOfReadBytesTC->Enable(false);

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4WriteBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			m_Set4WriteByteTCArray[idx]->Enable(false);
		}
		m_Set4NumOfReadBytesTC->Enable(false);

		break;

	case 2:// Set Count Select is 3

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set1WriteBytesCB->GetSelection()){
				m_Set1WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set2WriteBytesCB->GetSelection()){
				m_Set2WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set2WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set2NumOfReadBytesTC->Enable(true);

		m_Set3SlaveAddrTC->Enable(true);
		m_Set3CMDTC->Enable(true);
		m_Set3WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set3WriteBytesCB->GetSelection()){
				m_Set3WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set3WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set3NumOfReadBytesTC->Enable(true);

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4WriteBytesCB->Enable(false);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			m_Set4WriteByteTCArray[idx]->Enable(false);
		}
		m_Set4NumOfReadBytesTC->Enable(false);

		break;

	case 3:// Set Count Select is 4

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set1WriteBytesCB->GetSelection()){
				m_Set1WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set1WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set2WriteBytesCB->GetSelection()){
				m_Set2WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set2WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set2NumOfReadBytesTC->Enable(true);

		m_Set3SlaveAddrTC->Enable(true);
		m_Set3CMDTC->Enable(true);
		m_Set3WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set3WriteBytesCB->GetSelection()){
				m_Set3WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set3WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set3NumOfReadBytesTC->Enable(true);

		m_Set4SlaveAddrTC->Enable(true);
		m_Set4CMDTC->Enable(true);
		m_Set4WriteBytesCB->Enable(true);
		for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
			if (idx > this->m_Set4WriteBytesCB->GetSelection()){
				m_Set4WriteByteTCArray[idx]->Enable(false);
			}
			else{
				m_Set4WriteByteTCArray[idx]->Enable(true);
			}
		}
		m_Set4NumOfReadBytesTC->Enable(true);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

}

void BlockWRTestDialog::DisableAllTextCtrl(void){

	m_Set1SlaveAddrTC->Enable(false);
	m_Set1CMDTC->Enable(false);
	m_Set1WriteBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set1WriteByteTCArray[idx]->Enable(false);
	}
	m_Set1NumOfReadBytesTC->Enable(false);

	m_Set2SlaveAddrTC->Enable(false);
	m_Set2CMDTC->Enable(false);
	m_Set2WriteBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set2WriteByteTCArray[idx]->Enable(false);
	}
	m_Set2NumOfReadBytesTC->Enable(false);

	m_Set3SlaveAddrTC->Enable(false);
	m_Set3CMDTC->Enable(false);
	m_Set3WriteBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set3WriteByteTCArray[idx]->Enable(false);
	}
	m_Set3NumOfReadBytesTC->Enable(false);

	m_Set4SlaveAddrTC->Enable(false);
	m_Set4CMDTC->Enable(false);
	m_Set4WriteBytesCB->Enable(false);
	for (int idx = 0; idx < MAX_WRITE_DATA_BYTES; idx++){
		m_Set4WriteByteTCArray[idx]->Enable(false);
	}
	m_Set4NumOfReadBytesTC->Enable(false);

}

void BlockWRTestDialog::SetupBlockWRCMDArray(void){

	this->m_pmbusBlockWRCMDArray[0].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1SlaveAddrTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[0].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1CMDTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[0].m_numOfWriteBytes = (unsigned char)this->m_Set1WriteBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusBlockWRCMDArray[0].m_numOfWriteBytes; idx++){
		this->m_pmbusBlockWRCMDArray[0].m_writeBytes[idx] = PMBUSHelper::HexToDecimal(m_Set1WriteByteTCArray[idx]->GetValue().c_str());
	}
	this->m_pmbusBlockWRCMDArray[0].m_numOfReadBytes = PMBUSHelper::HexToDecimal(m_Set1NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[0].m_numOfReadBytes += 1;


	this->m_pmbusBlockWRCMDArray[1].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2SlaveAddrTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[1].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2CMDTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[1].m_numOfWriteBytes = (unsigned char)this->m_Set2WriteBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusBlockWRCMDArray[1].m_numOfWriteBytes; idx++){
		this->m_pmbusBlockWRCMDArray[1].m_writeBytes[idx] = PMBUSHelper::HexToDecimal(m_Set2WriteByteTCArray[idx]->GetValue().c_str());
	}
	this->m_pmbusBlockWRCMDArray[1].m_numOfReadBytes = PMBUSHelper::HexToDecimal(m_Set2NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[1].m_numOfReadBytes += 1;


	this->m_pmbusBlockWRCMDArray[2].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3SlaveAddrTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[2].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3CMDTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[2].m_numOfWriteBytes = (unsigned char)this->m_Set3WriteBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusBlockWRCMDArray[2].m_numOfWriteBytes; idx++){
		this->m_pmbusBlockWRCMDArray[2].m_writeBytes[idx] = PMBUSHelper::HexToDecimal(m_Set3WriteByteTCArray[idx]->GetValue().c_str());
	}
	this->m_pmbusBlockWRCMDArray[2].m_numOfReadBytes = PMBUSHelper::HexToDecimal(m_Set3NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[2].m_numOfReadBytes += 1;


	this->m_pmbusBlockWRCMDArray[3].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4SlaveAddrTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[3].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4CMDTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[3].m_numOfWriteBytes = (unsigned char)this->m_Set4WriteBytesCB->GetSelection() + 1;
	for (int idx = 0; idx < this->m_pmbusBlockWRCMDArray[3].m_numOfWriteBytes; idx++){
		this->m_pmbusBlockWRCMDArray[3].m_writeBytes[idx] = PMBUSHelper::HexToDecimal(m_Set4WriteByteTCArray[idx]->GetValue().c_str());
	}
	this->m_pmbusBlockWRCMDArray[3].m_numOfReadBytes = PMBUSHelper::HexToDecimal(m_Set4NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusBlockWRCMDArray[3].m_numOfReadBytes += 1;

}

void BlockWRTestDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	PMBUSBlockWRTestTask* pmbusBlockWRTestTask = NULL;
	pmbusBlockWRTestTask = (PMBUSBlockWRTestTask*)TaskEx::GetTask(task_ID_PMBUSBlockWRTestTask, 0);

	if (pmbusBlockWRTestTask != NULL){
		pmbusBlockWRTestTask->m_running = false;
	}

	while (TaskEx::GetCount(task_ID_PMBUSBlockWRTestTask) != 0){
		wxMilliSleep(100);
	}

	this->EndModal(wxID_CANCEL);
}

void BlockWRTestDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
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

void BlockWRTestDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
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

wxBEGIN_EVENT_TABLE(BlockWRTestDialog, wxDialog)
EVT_BUTTON(CID_BTN_START, BlockWRTestDialog::OnBtnSTART)
EVT_BUTTON(CID_BTN_STOP, BlockWRTestDialog::OnBtnSTOP)
EVT_COMBOBOX(CID_SET_COUNT_SELECT_COMBOBOX, BlockWRTestDialog::OnSetCountSelectCB)
EVT_CHECKBOX(CID_OUTPUT_LOG_CHECKBOX, BlockWRTestDialog::OnOutputLogCheckBox)
EVT_COMBOBOX(CID_SET_1_WRITE_BYTES_COMBOBOX, BlockWRTestDialog::OnSet1WriteBytesCB)
EVT_COMBOBOX(CID_SET_2_WRITE_BYTES_COMBOBOX, BlockWRTestDialog::OnSet2WriteBytesCB)
EVT_COMBOBOX(CID_SET_3_WRITE_BYTES_COMBOBOX, BlockWRTestDialog::OnSet3WriteBytesCB)
EVT_COMBOBOX(CID_SET_4_WRITE_BYTES_COMBOBOX, BlockWRTestDialog::OnSet4WriteBytesCB)
EVT_CLOSE(BlockWRTestDialog::OnDialogClose)
wxEND_EVENT_TABLE()