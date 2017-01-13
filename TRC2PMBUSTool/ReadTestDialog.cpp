/**
 * @file ReadTestDialog.cpp
 */

#include "ReadTestDialog.h"
#include "Task.h"

#define READ_TEST_DIALOG_WIDTH   800
#define READ_TEST_DIALOG_HEIGHT  600

#define DEF_SET_1_SLAVE_ADDR  wxT("B6")
#define DEF_SET_1_CMD         wxT("00")
#define DEF_SET_1_READ_BYTES  wxT("01")

#define DEF_SET_2_SLAVE_ADDR  wxT("B6")
#define DEF_SET_2_CMD         wxT("01")
#define DEF_SET_2_READ_BYTES  wxT("01")

#define DEF_SET_3_SLAVE_ADDR  wxT("B6")
#define DEF_SET_3_CMD         wxT("3B")
#define DEF_SET_3_READ_BYTES  wxT("02")

#define DEF_SET_4_SLAVE_ADDR  wxT("B6")
#define DEF_SET_4_CMD         wxT("AA")
#define DEF_SET_4_READ_BYTES  wxT("0F")

ReadTestDialog::ReadTestDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : wxDialog(parent, wxID_ANY, wxString(wxT("Customize PMBUS Read CMD Test")), wxDefaultPosition, wxSize(READ_TEST_DIALOG_WIDTH, READ_TEST_DIALOG_HEIGHT)){

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
		m_setCountSelectCB->Append(wxString::Format("%d",idx+1));
	}
	m_setCountSelectCB->Select(0);

	m_outputLogCheckBox = new wxCheckBox(m_optionsSBS->GetStaticBox(), CID_OUTPUT_LOG_CHECKBOX, wxT("Output Log"));
	this->m_outputLog = false;
	m_outputLogCheckBox->SetValue(this->m_outputLog);

	m_intervalTimeST = new wxStaticText(m_optionsSBS->GetStaticBox(), wxID_ANY, wxT("Interval Time"), wxDefaultPosition, wxDefaultSize);
	m_intervalTimeTC = new wxTextCtrl(m_optionsSBS->GetStaticBox(), wxID_ANY, wxT("0"));
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
	m_Set1NumOfReadBytesST = new wxStaticText(m_set1SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set1SlaveAddrTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_SLAVE_ADDR);
	m_Set1CMDTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_CMD);
	m_Set1NumOfReadBytesTC = new wxTextCtrl(m_set1SBS->GetStaticBox(), wxID_ANY, DEF_SET_1_READ_BYTES);
	
	m_Set1SlaveAddrTC->SetMaxLength(2);
	m_Set1CMDTC->SetMaxLength(2);
	m_Set1NumOfReadBytesTC->SetMaxLength(2);

	m_Set1SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set1CMDTC->SetValidator(m_hexValidator);
	m_Set1NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set1SBS->Add(m_Set1SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set1SBS->Add(m_Set1NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 2 Components Initialize
	m_Set2SlaveAddrST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set2CMDST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set2NumOfReadBytesST = new wxStaticText(m_set2SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set2SlaveAddrTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_SLAVE_ADDR);
	m_Set2CMDTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_CMD);
	m_Set2NumOfReadBytesTC = new wxTextCtrl(m_set2SBS->GetStaticBox(), wxID_ANY, DEF_SET_2_READ_BYTES);

	m_Set2SlaveAddrTC->SetMaxLength(2);
	m_Set2CMDTC->SetMaxLength(2);
	m_Set2NumOfReadBytesTC->SetMaxLength(2);

	m_Set2SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set2CMDTC->SetValidator(m_hexValidator);
	m_Set2NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set2SBS->Add(m_Set2SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set2SBS->Add(m_Set2NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 3 Components Initialize
	m_Set3SlaveAddrST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set3CMDST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set3NumOfReadBytesST = new wxStaticText(m_set3SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set3SlaveAddrTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_SLAVE_ADDR);
	m_Set3CMDTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_CMD);
	m_Set3NumOfReadBytesTC = new wxTextCtrl(m_set3SBS->GetStaticBox(), wxID_ANY, DEF_SET_3_READ_BYTES);

	m_Set3SlaveAddrTC->SetMaxLength(2);
	m_Set3CMDTC->SetMaxLength(2);
	m_Set3NumOfReadBytesTC->SetMaxLength(2);

	m_Set3SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set3CMDTC->SetValidator(m_hexValidator);
	m_Set3NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set3SBS->Add(m_Set3SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3NumOfReadBytesST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set3SBS->Add(m_Set3NumOfReadBytesTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());

	// Set 4 Components Initialize
	m_Set4SlaveAddrST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Slave Address"), wxDefaultPosition, wxDefaultSize);
	m_Set4CMDST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("CMD"), wxDefaultPosition, wxDefaultSize);
	m_Set4NumOfReadBytesST = new wxStaticText(m_set4SBS->GetStaticBox(), wxID_ANY, wxT("Num of Read Bytes"), wxDefaultPosition, wxDefaultSize);

	m_Set4SlaveAddrTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_SLAVE_ADDR);
	m_Set4CMDTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_CMD);
	m_Set4NumOfReadBytesTC = new wxTextCtrl(m_set4SBS->GetStaticBox(), wxID_ANY, DEF_SET_4_READ_BYTES);

	m_Set4SlaveAddrTC->SetMaxLength(2);
	m_Set4CMDTC->SetMaxLength(2);
	m_Set4NumOfReadBytesTC->SetMaxLength(2);

	m_Set4SlaveAddrTC->SetValidator(m_hexValidator);
	m_Set4CMDTC->SetValidator(m_hexValidator);
	m_Set4NumOfReadBytesTC->SetValidator(m_hexValidator);

	m_set4SBS->Add(m_Set4SlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4SlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4CMDST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_set4SBS->Add(m_Set4CMDTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
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

ReadTestDialog::~ReadTestDialog(){

	PMBUSReadTestTask* pmbusReadTestTask = NULL;
	pmbusReadTestTask = (PMBUSReadTestTask*)TaskEx::GetTask(task_ID_PMBUSReadTestTask, 0);

	if (pmbusReadTestTask != NULL){
		pmbusReadTestTask->m_running = false;
	}

	wxLog::SetActiveTarget(m_oldLog);
}

void ReadTestDialog::OnBtnSTART(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	int intervalTime = wxAtoi(this->m_intervalTimeTC->GetValue());
	if (intervalTime <= 0) intervalTime = 0;

	this->SetupReadCMDArray();

	if (TaskEx::GetCount(task_ID_PMBUSReadTestTask) == 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Create PMBUSReadTestTask Task");
		new(TP_PMBUSReadTestTask)PMBUSReadTestTask(this->m_ioaccess, this->m_currentIO, this->m_pmbusReadCMDArray, this->m_setCountSelectCB->GetSelection(), &this->m_outputLog, intervalTime);
		this->m_btnSTART->Enable(false);
		this->m_btnSTOP->Enable(true);
		this->m_setCountSelectCB->Enable(false);
		this->m_outputLogCheckBox->Enable(false);
		this->DisableAllTextCtrl();

		this->m_logTC->Clear();
		PSU_DEBUG_PRINT(MSG_ALERT, "Start To Send Read CMD");
		PSU_DEBUG_PRINT(MSG_ALERT, "Interval Time is %d Millisecond", intervalTime);

	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "Another One PMBUSReadTestTask Task is Running");
	}

}

void ReadTestDialog::OnBtnSTOP(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	PMBUSReadTestTask* pmbusReadTestTask = NULL;
	pmbusReadTestTask = (PMBUSReadTestTask*)TaskEx::GetTask(task_ID_PMBUSReadTestTask, 0);

	if (pmbusReadTestTask != NULL){
		pmbusReadTestTask->m_running = false;
	}
	
	this->m_btnSTART->Enable(true);
	this->m_btnSTOP->Enable(false);
	this->m_setCountSelectCB->Enable(true);
	this->m_outputLogCheckBox->Enable(true);
	this->EnableTextCtrlBySelect(this->m_setCountSelectCB->GetSelection());
}

void ReadTestDialog::OnSetCountSelectCB(wxCommandEvent& event){
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

void ReadTestDialog::OnOutputLogCheckBox(wxCommandEvent& event){

	if (this->m_outputLogCheckBox->GetValue() == true){
		this->m_outputLog = true;
	}
	else{
		this->m_outputLog = false;
	}

}

void ReadTestDialog::EnableTextCtrlBySelect(int select){

	switch (select){

	case 0:// Set Count Select is 1

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(false);
		m_Set2CMDTC->Enable(false);
		m_Set2NumOfReadBytesTC->Enable(false);

		m_Set3SlaveAddrTC->Enable(false);
		m_Set3CMDTC->Enable(false);
		m_Set3NumOfReadBytesTC->Enable(false);

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4NumOfReadBytesTC->Enable(false);


		break;

	case 1:// Set Count Select is 2

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2NumOfReadBytesTC->Enable(true);

		m_Set3SlaveAddrTC->Enable(false);
		m_Set3CMDTC->Enable(false);
		m_Set3NumOfReadBytesTC->Enable(false);

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4NumOfReadBytesTC->Enable(false);

		break;

	case 2:// Set Count Select is 3

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2NumOfReadBytesTC->Enable(true);

		m_Set3SlaveAddrTC->Enable(true);
		m_Set3CMDTC->Enable(true);
		m_Set3NumOfReadBytesTC->Enable(true);

		m_Set4SlaveAddrTC->Enable(false);
		m_Set4CMDTC->Enable(false);
		m_Set4NumOfReadBytesTC->Enable(false);

		break;

	case 3:// Set Count Select is 4

		m_Set1SlaveAddrTC->Enable(true);
		m_Set1CMDTC->Enable(true);
		m_Set1NumOfReadBytesTC->Enable(true);

		m_Set2SlaveAddrTC->Enable(true);
		m_Set2CMDTC->Enable(true);
		m_Set2NumOfReadBytesTC->Enable(true);

		m_Set3SlaveAddrTC->Enable(true);
		m_Set3CMDTC->Enable(true);
		m_Set3NumOfReadBytesTC->Enable(true);

		m_Set4SlaveAddrTC->Enable(true);
		m_Set4CMDTC->Enable(true);
		m_Set4NumOfReadBytesTC->Enable(true);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

}

void ReadTestDialog::DisableAllTextCtrl(void){
	m_Set1SlaveAddrTC->Enable(false);
	m_Set1CMDTC->Enable(false);
	m_Set1NumOfReadBytesTC->Enable(false);

	m_Set2SlaveAddrTC->Enable(false);
	m_Set2CMDTC->Enable(false);
	m_Set2NumOfReadBytesTC->Enable(false);

	m_Set3SlaveAddrTC->Enable(false);
	m_Set3CMDTC->Enable(false);
	m_Set3NumOfReadBytesTC->Enable(false);

	m_Set4SlaveAddrTC->Enable(false);
	m_Set4CMDTC->Enable(false);
	m_Set4NumOfReadBytesTC->Enable(false);
}

void ReadTestDialog::SetupReadCMDArray(void){
	
	this->m_pmbusReadCMDArray[0].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1SlaveAddrTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[0].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1CMDTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[0].m_numOfReadBytes = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set1NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[0].m_numOfReadBytes += 1;

	this->m_pmbusReadCMDArray[1].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2SlaveAddrTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[1].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2CMDTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[1].m_numOfReadBytes = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set2NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[1].m_numOfReadBytes += 1;

	this->m_pmbusReadCMDArray[2].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3SlaveAddrTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[2].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3CMDTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[2].m_numOfReadBytes = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set3NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[2].m_numOfReadBytes += 1;

	this->m_pmbusReadCMDArray[3].m_slaveAddr = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4SlaveAddrTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[3].m_cmd = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4CMDTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[3].m_numOfReadBytes = (unsigned char)PMBUSHelper::HexToDecimal(this->m_Set4NumOfReadBytesTC->GetValue().c_str());
	this->m_pmbusReadCMDArray[3].m_numOfReadBytes += 1;
}

void ReadTestDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	PMBUSReadTestTask* pmbusReadTestTask = NULL;
	pmbusReadTestTask = (PMBUSReadTestTask*)TaskEx::GetTask(task_ID_PMBUSReadTestTask, 0);

	if (pmbusReadTestTask != NULL){
		pmbusReadTestTask->m_running = false;
	}

	while (TaskEx::GetCount(task_ID_PMBUSReadTestTask) != 0){
		wxMilliSleep(100);
	}

	this->EndModal(wxID_CANCEL);

}

void ReadTestDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
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

void ReadTestDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
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

wxBEGIN_EVENT_TABLE(ReadTestDialog, wxDialog)
EVT_BUTTON(CID_BTN_START, ReadTestDialog::OnBtnSTART)
EVT_BUTTON(CID_BTN_STOP, ReadTestDialog::OnBtnSTOP)
EVT_COMBOBOX(CID_SET_COUNT_SELECT_COMBOBOX, ReadTestDialog::OnSetCountSelectCB)
EVT_CHECKBOX(CID_OUTPUT_LOG_CHECKBOX, ReadTestDialog::OnOutputLogCheckBox)
EVT_CLOSE(ReadTestDialog::OnDialogClose)
wxEND_EVENT_TABLE()