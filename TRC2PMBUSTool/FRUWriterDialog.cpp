/**
 * @file FRUWriterDialog.cpp
 */
#include "FRUWriterDialog.h"

wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_WRITE_END, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_READ_END, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_READ_INTERRUPT, wxThreadEvent);

#define FRU_WRITER_DIALOG_WIDTH   (800)
#define FRU_WRITER_DIALOG_HEIGHT  (480)

#define DEF_E2PROM_SLAVE_ADDR           wxT("AE")
#define DEF_E2PROM_ST_WIDTH                 160
#define DEF_E2PROM_TC_WIDTH                 420
#define DEF_E2PROM_SLAVE_ADDR_WIDTH          30

#define MAX_FRU_FILE_LOAD_LENGTH            256
#define MAX_FRU_FILE_WRITE_LENGTH           256
#define MAX_FRU_FILE_READ_LENGTH            256

#define MAX_RECV_BUFFER_LENGTH              256

#define WRITE_CMD_INTERVAL_TIME              10 // Millisecond
#define READ_CMD_INTERVAL_TIME               10 // Millisecond

#define MAX_E2PROM_WRITE_RETRY_TIMES          3
#define MAX_E2PROM_READ_RETRY_TIMES           3

#define DUMP_BINARY_CONTENT                 

FRUWriterDialog::FRUWriterDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : wxDialog(parent, wxID_ANY, wxString(wxT("FRU Writer/Reader")), wxDefaultPosition, wxSize(FRU_WRITER_DIALOG_WIDTH, FRU_WRITER_DIALOG_HEIGHT)){

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(E2PROM_16));

	this->SetIcon(icon);

	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

	this->outputLog = false;

	// Setup Text Validator
	DecCharIncludes = wxT("0123456789");
	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

	m_decValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decValidator.SetCharIncludes(DecCharIncludes);

	// Initialize Sizer 
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_e2pROMSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("EEPROM"));
	m_e2pROMLine1Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_e2pROMLine2Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_btnSizer = new wxBoxSizer(wxHORIZONTAL);

	// Initilaize Components
	m_fruFileST = new wxStaticText(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT("FRU File"), wxDefaultPosition, wxSize(DEF_E2PROM_ST_WIDTH, -1));
	m_fruFileTC = new wxTextCtrl(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(DEF_E2PROM_TC_WIDTH,-1));
	m_fruFileTC->SetEditable(false);
	m_floppyLoadBB = new wxBitmapButton(m_e2pROMSBS->GetStaticBox(), CID_BTN_LOAD, wxBITMAP_PNG(FLOPPY_16));

	m_e2pROMSlaveAddrST = new wxStaticText(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT("EEPROM Slave Address"), wxDefaultPosition, wxSize(DEF_E2PROM_ST_WIDTH, -1));
	m_e2pROMSlaveAddrTC = new wxTextCtrl(m_e2pROMSBS->GetStaticBox(), wxID_ANY, DEF_E2PROM_SLAVE_ADDR, wxDefaultPosition, wxSize(DEF_E2PROM_SLAVE_ADDR_WIDTH, -1));
	m_e2pROMSlaveAddrTC->SetValidator(m_hexValidator);
	m_e2pROMSlaveAddrTC->SetMaxLength(2);

	//m_stline1 = new wxStaticLine(this);
	//m_stline2 = new wxStaticLine(this);

	m_btnWRITE = new wxButton(this, CID_BTN_WRITE, wxT("WRITE"));
	m_btnWRITE->Enable(false);

	m_btnREAD = new wxButton(this, CID_BTN_READ, wxT("READ"));
	m_btnREAD->Enable(true);

	m_logTC = new PMBUSLogTextCtrl(this, wxID_ANY);

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	this->m_logTC->SetFont(font);


	// Add Components To Sizer
	m_e2pROMLine1Sizer->Add(m_e2pROMSlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine1Sizer->Add(m_e2pROMSlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMSBS->Add(m_e2pROMLine1Sizer);

	m_e2pROMLine2Sizer->Add(m_fruFileST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine2Sizer->Add(m_fruFileTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine2Sizer->Add(m_floppyLoadBB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMSBS->Add(m_e2pROMLine2Sizer);

	m_btnSizer->Add(m_btnREAD);
	m_btnSizer->Add(m_btnWRITE);

	m_topLevelSizer->Add(m_e2pROMSBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_btnSizer, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_logTC, wxSizerFlags(1).Expand().Border());

	memset(this->m_fruBinaryContent, 0, MAX_FRU_FILE_SIZE);
	//memset(this->m_e2pRomContent, 0, MAX_FRU_FILE_SIZE);

	SetSizer(m_topLevelSizer);
}

FRUWriterDialog::~FRUWriterDialog(){

	wxLog::SetActiveTarget(m_oldLog);
}

void FRUWriterDialog::OnBtnLOAD(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	unsigned int readBytes = 0;

	// Load FRU Binary File
	wxFileDialog LoadBINFileDialog(this, L"Load FRU Binary File", "", "", "BIN Files (*.bin)|*.bin", wxFD_OPEN);

	LoadBINFileDialog.Centre();

	// If the user changed idea...
	if (LoadBINFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

	wxString path = LoadBINFileDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_ALERT, "BINARY File Path : %s", path.c_str());

	// Update FRU File Path Static Text
	m_fruFileTC->SetValue(path);

	// Open Binary File
	wxFile *fruFile = new wxFile(path, wxFile::read);

	if (fruFile->IsOpened() != true){
		PSU_DEBUG_PRINT(MSG_ERROR, "Open BINARY File Failed");
		return;
	}

	// Load Conten Of FRU Buiary File
	PSU_DEBUG_PRINT(MSG_ALERT, "BINARY File Size is %d Bytes", fruFile->Length());

	// If File Size Large Than 256, Should be a error
	if (fruFile->Length() > MAX_FRU_FILE_LOAD_LENGTH){
		PSU_DEBUG_PRINT(MSG_ERROR, "BINARY FILE Size Large Than %d", MAX_FRU_FILE_LOAD_LENGTH);
		wxDELETE(fruFile);
		return;
	}

	readBytes = fruFile->Read((void*)this->m_fruBinaryContent, MAX_FRU_FILE_LOAD_LENGTH);
	this->m_fruFileLength = readBytes;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Bytes Loaeded : %d", readBytes);

#ifdef DUMP_BINARY_CONTENT
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------- BINARY FILE CONTENT -------------------");
	PMBUSHelper::PrintFRUContent(this->m_fruBinaryContent, readBytes);
#endif

	// Seems like No Error On FRU Binary File Content
	m_btnWRITE->Enable(true);
	wxDELETE(fruFile);
}

void FRUWriterDialog::OnBtnWRITE(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	// Disable Read/Write Button
	this->m_btnREAD->Enable(false);
	this->m_btnWRITE->Enable(false);

	// New E2PRomWriteDataTask To Write
	int count = TaskEx::GetCount(task_ID_E2PRomWriteDataTask);
	
	if (count > 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Another E2PRomWriteDataTask is Running");
		return;
	}

	new(TP_E2PRomWriteDataTask) E2PRomWriteDataTask(this->m_ioaccess, this->m_currentIO, this->GetEventHandler(), (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()), this->m_fruBinaryContent, this->m_fruFileLength, &this->outputLog, WRITE_CMD_INTERVAL_TIME, READ_CMD_INTERVAL_TIME);

}

void FRUWriterDialog::OnBtnREAD(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	this->m_preWriteBTNEnable = this->m_btnWRITE->IsEnabled();

	this->m_btnREAD->Enable(false);
	this->m_btnWRITE->Enable(false);

	// New E2PRomReadDataTask To Write
	int count = TaskEx::GetCount(task_ID_E2PRomReadDataTask);

	if (count > 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Another E2PRomReadDataTask is Running");
		return;
	}

	new(TP_E2PRomReadDataTask) E2PRomReadDataTask(this->m_ioaccess, this->m_currentIO, this->GetEventHandler(), (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()), &this->outputLog, READ_CMD_INTERVAL_TIME);

}

void FRUWriterDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	this->EndModal(wxID_CANCEL);

}

void FRUWriterDialog::OnE2PRomWriteEnd(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	// Enable Read/Write Button
	this->m_btnREAD->Enable(true);
	this->m_btnWRITE->Enable(true);

	wxMessageBox(wxT("Write & Verify E2PROM Success"),
		wxT("Write E2PROM Success"),  // caption
		wxOK | wxICON_INFORMATION);
}

void FRUWriterDialog::OnE2PRomReadEnd(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	this->m_btnREAD->Enable(true);
	if (this->m_preWriteBTNEnable == true){
		this->m_btnWRITE->Enable(true);
	}

	wxMessageBox(wxT("Read E2PROM Success"),
		wxT("Read E2PROM Success"),  // caption
		wxOK | wxICON_INFORMATION);
}

void FRUWriterDialog::OnE2PRomWriteInterrupt(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	// Enable Read/Write Button
	this->m_btnREAD->Enable(true);
	this->m_btnWRITE->Enable(true);

	wxMessageBox(wxT("Write & Verify E2PROM Failed"),
		wxT("Write E2PROM Failed"),  // caption
		wxOK | wxICON_ERROR);
}

void FRUWriterDialog::OnE2PRomReadInterrupt(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	this->m_btnREAD->Enable(true);
	if (this->m_preWriteBTNEnable == true){
		this->m_btnWRITE->Enable(true);
	}

	wxMessageBox(wxT("Read E2PROM Failed"),
		wxT("Read E2PROM Failed"),  // caption
		wxOK | wxICON_ERROR);
}

void FRUWriterDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
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

void FRUWriterDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
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

wxBEGIN_EVENT_TABLE(FRUWriterDialog, wxDialog)
EVT_BUTTON(CID_BTN_LOAD, FRUWriterDialog::OnBtnLOAD)
EVT_BUTTON(CID_BTN_READ, FRUWriterDialog::OnBtnREAD)
EVT_BUTTON(CID_BTN_WRITE, FRUWriterDialog::OnBtnWRITE)
EVT_THREAD(wxEVT_COMMAND_E2PROM_WRITE_END, FRUWriterDialog::OnE2PRomWriteEnd)
EVT_THREAD(wxEVT_COMMAND_E2PROM_READ_END, FRUWriterDialog::OnE2PRomReadEnd)
EVT_THREAD(wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT, FRUWriterDialog::OnE2PRomWriteInterrupt)
EVT_THREAD(wxEVT_COMMAND_E2PROM_READ_INTERRUPT, FRUWriterDialog::OnE2PRomReadInterrupt)
EVT_CLOSE(FRUWriterDialog::OnDialogClose)
wxEND_EVENT_TABLE()