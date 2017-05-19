/**
 * @file PMBUSFWProgressDialog.cpp
 */

#include "PMBUSFWProgressDialog.h"

wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_END, wxThreadEvent);

PMBUSFWProgressDialog::PMBUSFWProgressDialog(wxWindow *parent, wxString title, int range, unsigned char* ispStatus, IncreaseCPUOverHeadThread* increaseCPUOverHeadThread, IOACCESS* ioaccess, unsigned int* currentIO) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
#if wxUSE_TIMER
, m_timer(this)
#endif
{
	// Setup Icon
	wxIcon icon;
	icon.CopyFromBitmap(LOAD_PNG_RESOURCE(chip_16));

	this->SetIcon(icon);

	m_ispStatus = ispStatus;

	m_increaseCPUOverHeadThread = increaseCPUOverHeadThread;

	m_ioaccess = ioaccess;

	m_currentIO = currentIO;

	// Initialize Sizer
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);

	// Initialize Static Box Sizer
	m_statisticsSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Statistics"));
	m_logSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Log"));

	// Information Static Text
	m_infoST = new wxStaticText(this->m_statisticsSB->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(250, 80));// 200, 60));

	// Set Log Target
	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	m_logTC = new PMBUSLogTextCtrl(m_logSB->GetStaticBox(), wxID_ANY);
	
	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	this->m_logTC->SetFont(font);

	// Initialize GUI Component

#ifdef _WIN32	
	m_gauge = new wxGauge(this, CID_GAUGE_PROGRES, range, wxDefaultPosition, wxDefaultSize, wxGA_SMOOTH | wxGA_PROGRESS);
#else
#ifdef __GNUC__
	m_gauge = new wxGauge(this, CID_GAUGE_PROGRES, range, wxDefaultPosition, wxDefaultSize, wxGA_SMOOTH);
#endif
#endif

	m_okCancelButton = new wxButton(this, CID_BTN_CANCELOK, wxT("Cancel"), wxDefaultPosition, wxSize(250, -1));

	// Add GUI Component To Static Box
	m_statisticsSB->Add(this->m_infoST, wxSizerFlags(0).Border());// .Align(wxALIGN_CENTER_HORIZONTAL));

	m_logSB->Add(this->m_logTC, wxSizerFlags(1).Border().Expand());

	// Add Sizer To Top Level Sizer
	//this->m_topLevelSizer->Add(this->m_infoST, wxSizerFlags(0).Border());
	this->m_topLevelSizer->Add(m_statisticsSB, wxSizerFlags(0).Border().Expand());

	//this->m_topLevelSizer->Add(this->m_logTC, wxSizerFlags(1).Border().Expand());
	this->m_topLevelSizer->Add(m_logSB, wxSizerFlags(1).Border().Expand());

	this->m_topLevelSizer->Add(this->m_gauge, wxSizerFlags().Border().Expand());

	this->m_topLevelSizer->Add(this->m_okCancelButton, wxSizerFlags().Border().Align(wxALIGN_CENTER_HORIZONTAL));

	// Set Sizer
	//SetSizerAndFit(m_topLevelSizer);
	SetSizer(m_topLevelSizer);

	SetEscapeId(wxID_CLOSE);

#if wxUSE_TIMER
	// Start Timer
	this->m_timer.Start(1000);
#endif

	// Save Begin Time
	this->m_beginTime = wxDateTime::Now();
}

PMBUSFWProgressDialog::~PMBUSFWProgressDialog(){
	wxLog::SetActiveTarget(m_oldLog);

#if wxUSE_TIMER
	if (m_timer.IsRunning())
	{
		m_timer.Stop();
	}
#endif

}

bool PMBUSFWProgressDialog::Update(int value, const wxString& newmsg, bool *skip){
	bool result = false;

	this->m_infoST->SetLabelText(newmsg);

	this->m_gauge->SetValue(value);

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

void PMBUSFWProgressDialog::OnISPSequenceUpdate(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnISPSequenceUpdate");

	static int previous_percentage = 0;
	int percentage = event.GetInt();
	wxString information = event.GetString();

#ifndef _DEBUG
	if (previous_percentage != percentage){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Percentage = %d%%", percentage);
		previous_percentage = percentage;
	}
#endif

	wxTimeSpan Elapsed = wxDateTime::Now() - m_beginTime;
	information += wxT("\n");
	information += wxT("\n");
	information += wxT("Elapsed Time : ");
	information += Elapsed.Format();

	this->Update(percentage, information);

	/*
	// Update Dialogs
	//not_cancel = dialog.Update((int)percentage, information);
	int not_cancel = m_progressDialog->Update((int)percentage, information);

	if (not_cancel == false){
	m_ispStatus = ISP_Status_UserRequestCancel;
	}
	*/
}

void PMBUSFWProgressDialog::OnISPSequenceInterrupt(wxThreadEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnISPSequenceInterrupt");

	int ispStatus = event.GetInt();

	// If Error Occurs
	if ((ispStatus & 0xff) > 0x02) {

		PSU_DEBUG_PRINT(MSG_DEBUG, "ispStatus = 0x%xH", ispStatus);

		switch (ispStatus){

		case ISP_Status_VerifyBeforeStart:
			// Verify Before Start

			break;

		case ISP_Status_UserRequestCancel:
			// User Cancel ISP
			PSU_DEBUG_PRINT(MSG_DEBUG, "User Cancel ISP Sequence !");

			new(TP_ClearIOReadBufferTask) ClearIOReadBufferTask(this->m_ioaccess, this->m_currentIO, false);
			new(TP_UserCancelISPPostDelayTask) UserCancelISPPostDelayTask();

			break;

		case ISP_Status_SendDataFailed:
			wxMessageBox(wxT("Send Data Failed ! \n\n IO Port Send Data Failed"),
				wxT("Error !"),  // caption
				wxOK | wxICON_ERROR);

			break;

		case ISP_Status_ResponseDataError:
			wxMessageBox(wxT("Response Data Error ! \n\n This may caused by Unstable IO or Incorrect Image"),
				wxT("Error !"),  // caption
				wxOK | wxICON_ERROR);

			break;


		case ISP_Status_RebootCheckError:
			wxMessageBox(wxT("DSP Reboot Check Error ! \n\n DSP Reboot Failed"),
				wxT("Error !"),  // caption
				wxOK | wxICON_ERROR);

			break;

		default:
			PSU_DEBUG_PRINT(MSG_DEBUG, "Something Error Occurs, ispStatus = %02x", ispStatus);
			break;

		}
	}

}

void PMBUSFWProgressDialog::OnISPSequenceEnd(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnISPSequenceEnd");

	this->m_okCancelButton->SetLabel("Close");

	wxMessageBox(wxT("ISP Sequence ALL Complete, Please Press Close Button To Exit"), wxT("ISP Complete"), wxOK | wxICON_INFORMATION, this);

	//this->Resume();
}


void PMBUSFWProgressDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_ALERT, "OnDialogClose");

	*this->m_ispStatus = ISP_Status_UserRequestCancel;

	//new(0.1f) UserCancelISPTask(this->m_ispStatus); // This sometimes cause GUI thread reply slowly

	#if (INCREASE_CPU_OVERHEAD == TRUE)
	if (PMBUSHelper::GetAppSettings()->m_increaseCPUOverhead == Generic_Disable){
		if (m_increaseCPUOverHeadThread != NULL){
			m_increaseCPUOverHeadThread->Delete();
		}
	}
	#endif

	while (Task::GetCount() > 0){
		// If Task Count > 0, Wait
		PSU_DEBUG_PRINT(MSG_DEBUG, "Wait For Remain Task End, Task Count = %d", Task::GetCount());

		wxMilliSleep(10);
	};

	this->EndModal(wxID_CANCEL);
}

void PMBUSFWProgressDialog::OnBtnCancelOK(wxCommandEvent& event) {

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnBtnCancelOK");

	*this->m_ispStatus = ISP_Status_UserRequestCancel;

	//new(0.1f) UserCancelISPTask(this->m_ispStatus); // This sometimes cause GUI thread reply slowly

	#if (INCREASE_CPU_OVERHEAD == TRUE)
	if (PMBUSHelper::GetAppSettings()->m_increaseCPUOverhead == Generic_Disable){
		if (m_increaseCPUOverHeadThread != NULL){
			m_increaseCPUOverHeadThread->Delete();
		}
	}
	#endif

	while (Task::GetCount() > 0){		
		// If Task Count > 0, Wait
		PSU_DEBUG_PRINT(MSG_DEBUG, "Wait For Remain Task End, Task Count = %d", Task::GetCount());

		wxMilliSleep(10);
	};

	this->EndModal(wxID_CANCEL);
}

wxBEGIN_EVENT_TABLE(PMBUSFWProgressDialog, wxDialog)
EVT_THREAD(wxEVT_COMMAND_ISP_SEQUENCE_UPDATE, PMBUSFWProgressDialog::OnISPSequenceUpdate)
EVT_THREAD(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, PMBUSFWProgressDialog::OnISPSequenceInterrupt)
EVT_THREAD(wxEVT_COMMAND_ISP_SEQUENCE_END, PMBUSFWProgressDialog::OnISPSequenceEnd)
EVT_BUTTON(CID_BTN_CANCELOK, PMBUSFWProgressDialog::OnBtnCancelOK)
EVT_CLOSE(PMBUSFWProgressDialog::OnDialogClose)
wxEND_EVENT_TABLE()
