/**
 * @file PMBUSFWProgressDialog.cpp
 */

#include "PMBUSFWProgressDialog.h"

PMBUSFWProgressDialog::PMBUSFWProgressDialog(wxWindow *parent, wxString title, int range) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400) )
{
	// Setup Icon
	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(CHIP_16));

	this->SetIcon(icon);

	// Set Log Target
	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	m_logTC = new PMBUSLogTextCtrl(this, wxID_ANY);
	//m_logTC->SetSize(600, 300);

	// Initialize Sizer
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);

	// Initialize GUI Component

	m_gauge = new wxGauge(this, wxID_ANY, range, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL | wxGA_SMOOTH | wxGA_PROGRESS);

	m_okCancelButton = new wxButton(this, wxID_ANY, wxT("Cancel"));


	// Add GUI Component To Sizer
	this->m_topLevelSizer->Add(this->m_logTC, wxSizerFlags(1).Border().Expand());

	this->m_topLevelSizer->Add(this->m_gauge, wxSizerFlags().Align(wxALIGN_CENTRE).Border().Expand());

	this->m_topLevelSizer->Add(this->m_okCancelButton, wxSizerFlags().Align(wxALIGN_CENTRE).Border().Expand());

	// Set Sizer
	//SetSizerAndFit(m_topLevelSizer);
	SetSizer(m_topLevelSizer);

	SetEscapeId(wxID_CLOSE);

}

PMBUSFWProgressDialog::~PMBUSFWProgressDialog(){
	wxLog::SetActiveTarget(m_oldLog);
}

bool PMBUSFWProgressDialog::Update(int value, const wxString& newmsg, bool *skip){
	bool result = false;


	return result;
}

void PMBUSFWProgressDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
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

void PMBUSFWProgressDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
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

wxBEGIN_EVENT_TABLE(PMBUSFWProgressDialog, wxDialog)
//EVT_BUTTON(CID_BTN_APPLY, CalibrationDialog::OnBtnApply)
//EVT_BUTTON(CID_BTN_DONE, CalibrationDialog::OnBtnDone)
//EVT_BUTTON(CID_BTN_READ, CalibrationDialog::OnBtnRead)
//EVT_COMBOBOX(CID_CB_CALIBRATION_ITEM, CalibrationDialog::OnCBCalibrationItem)
//EVT_COMBOBOX(CID_CB_POINTER, CalibrationDialog::OnCBPointer)
//EVT_TEXT(CID_TC_DATA_1, CalibrationDialog::OnTCData1)
//EVT_TEXT_ENTER(CID_TC_DATA_1, CalibrationDialog::OnTCData1)
wxEND_EVENT_TABLE()