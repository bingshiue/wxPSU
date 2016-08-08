/**
 * @file PMBUSStatusBar.cpp
 * @brief Our custom status bar class.
 */

#include "PMBUSStatusBar.h"

#ifdef __VISUALC__
// 'this' : used in base member initializer list -- so what??
#pragma warning(disable: 4355)
#endif

#define FILED_IO_SETTING_WIDTH             150
#define FILED_I2C_CLOCK_WIDTH               50
#define FILED_RUN_MODE_WIDTH                75
#define FILED_MONITORING_COMMAND_WIDTH     150
#define FILED_GAUGE_WIDTH                  100
#define FILED_MONITOR_TIME                 100
#define FILED_MONITOR_SUMMARY              (DEFAULT_WINDOW_WIDTH - (FILED_IO_SETTING_WIDTH + FILED_I2C_CLOCK_WIDTH + FILED_RUN_MODE_WIDTH \
 + FILED_MONITORING_COMMAND_WIDTH + FILED_GAUGE_WIDTH + FILED_MONITOR_TIME))


PMBUSStatusBar::PMBUSStatusBar(wxWindow *parent, long style) : wxStatusBar(parent, wxID_ANY, style, "PSUStatusBar")
#if wxUSE_TIMER
, m_timer(this)
#endif
#if wxUSE_CHECKBOX
//, m_checkbox(NULL)
#endif
{
	int widths[Field_Max];
	widths[Field_IO_Setting] = FILED_IO_SETTING_WIDTH;
	widths[Field_I2C_Clock] = FILED_I2C_CLOCK_WIDTH;
	widths[Field_Run_Mode] = FILED_RUN_MODE_WIDTH;
	widths[Field_Monitoring_Command] = FILED_MONITORING_COMMAND_WIDTH;
	widths[Field_Gauge] = FILED_GAUGE_WIDTH;
	widths[Field_Monitoring_Time] = FILED_MONITOR_TIME; 
	widths[Field_Monitoring_Summary] = -1;//FILED_MONITOR_SUMMARY;// -1; // growable

	SetFieldsCount(Field_Max);
	SetStatusWidths(Field_Max, widths);

#if wxUSE_CHECKBOX
	//m_checkbox = new wxCheckBox(this, StatusBar_Checkbox, wxT("&Toggle clock"));
	//m_checkbox->SetValue(true);
#endif

	m_gauge = new wxGauge(this, wxID_ANY, 100);

	m_gauge->SetValue(0);

	this->SetStatusText(wxT("Disconnect"), Field_IO_Setting);//Com3-9600-N81
	this->SetStatusText(wxT("100kHz"), Field_I2C_Clock);

	unsigned long runMode = PMBUSHelper::GetAppSettings()->m_runMode;

	switch (runMode){

	case RunMode_Iterations:
		this->SetStatusText(wxT("Iterations"), Field_Run_Mode);
		break;

	case RunMode_Continually:
		this->SetStatusText(wxT("Continually"), Field_Run_Mode);
		break;

	case RunMode_StopAnError:
		this->SetStatusText(wxT("Stop An Error"), Field_Run_Mode);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error")
		break;

	}

#if wxUSE_TIMER
	//m_timer.Start(1000);
#endif

	//m_sw.Start();

	m_beginTime = wxDateTime::Now();

	//SetMinHeight(wxMax(m_statbmp->GetBestSize().GetHeight(),
		//m_checkbox->GetBestSize().GetHeight()));
}

#ifdef __VISUALC__
#pragma warning(default: 4355)
#endif

PMBUSStatusBar::~PMBUSStatusBar()
{
#if wxUSE_TIMER
	if (m_timer.IsRunning())
	{
		m_timer.Stop();
	}
#endif
}

void PMBUSStatusBar::UpdateClock()
{

	wxTimeSpan Elapsed = wxDateTime::Now() - m_beginTime;

	SetStatusText(Elapsed.Format(), Field_Monitoring_Time);

}

void PMBUSStatusBar::OnSize(wxSizeEvent& event){
	// ReSize Gauge
	if (!this->m_gauge){
		return;
	}

	wxRect rect;
	if (!GetFieldRect(Field_Gauge, rect))
	{
		event.Skip();
		return;
	}

	wxRect rectCheck = rect;
	rectCheck.Deflate(1);
	m_gauge->SetSize(rectCheck);
}

void PMBUSStatusBar::OnToggleClock(wxCommandEvent& event){

}

void PMBUSStatusBar::OnIdle(wxIdleEvent& event){

}

void PMBUSStatusBar::setMonitoringCMDName(wxString& cmdName){
	SetStatusText(cmdName, Field_Monitoring_Command);
}

void PMBUSStatusBar::setMonitoringSummary(wxString& summary){
	SetStatusText(summary, Field_Monitoring_Summary);
}

wxBEGIN_EVENT_TABLE(PMBUSStatusBar, wxStatusBar)
EVT_SIZE(PMBUSStatusBar::OnSize)
#if wxUSE_CHECKBOX
//EVT_CHECKBOX(StatusBar_Checkbox, PSUStatusBar::OnToggleClock)
#endif
#if wxUSE_TIMER
EVT_TIMER(wxID_ANY, PMBUSStatusBar::OnTimer)
#endif
EVT_IDLE(PMBUSStatusBar::OnIdle)
wxEND_EVENT_TABLE()