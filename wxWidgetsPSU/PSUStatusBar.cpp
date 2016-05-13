/**
* @file PSUStatusBar.cpp
* @brief Our custom status bar class.
*/

#include "PSUStatusBar.h"

#ifdef __VISUALC__
// 'this' : used in base member initializer list -- so what??
#pragma warning(disable: 4355)
#endif

PSUStatusBar::PSUStatusBar(wxWindow *parent, long style) : wxStatusBar(parent, wxID_ANY, style, "PSUStatusBar")
#if wxUSE_TIMER
	, m_timer(this)
#endif
#if wxUSE_CHECKBOX
	//, m_checkbox(NULL)
#endif
{
	int widths[Field_Max];
	widths[Field_IO_Setting] = 120;
	widths[Field_I2C_Clock] = 50;
	widths[Field_Run_Mode] = 100;
	widths[Field_Monitoring_Command] = 150;
	widths[Field_Gauge] = 100;
	widths[Field_Monitoring_Time] = 50; // growable
	widths[Field_Monitoring_Summary] = -1;

	SetFieldsCount(Field_Max);
	SetStatusWidths(Field_Max, widths);

#if wxUSE_CHECKBOX
	//m_checkbox = new wxCheckBox(this, StatusBar_Checkbox, wxT("&Toggle clock"));
	//m_checkbox->SetValue(true);
#endif

	m_gauge = new wxGauge(this, wxID_ANY, 100);

	m_gauge->SetValue(0);

	this->SetStatusText(wxT("Com3-9600-N81"), Field_IO_Setting);
	this->SetStatusText(wxT("100kHz"), Field_I2C_Clock);
	this->SetStatusText(wxT("Continually"), Field_Run_Mode);


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

PSUStatusBar::~PSUStatusBar()
{
#if wxUSE_TIMER
	if (m_timer.IsRunning())
	{
		m_timer.Stop();
	}
#endif
}

void PSUStatusBar::UpdateClock()
{

	wxTimeSpan Elapsed = wxDateTime::Now() - m_beginTime;

	SetStatusText(Elapsed.Format(), Field_Monitoring_Time);

}

void PSUStatusBar::OnSize(wxSizeEvent& event){
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

void PSUStatusBar::OnToggleClock(wxCommandEvent& event){

}

void PSUStatusBar::OnIdle(wxIdleEvent& event){

}

void PSUStatusBar::setMonitoringCMDName(wxString& cmdName){
	SetStatusText(cmdName, Field_Monitoring_Command);
}

void PSUStatusBar::setMonitoringSummary(wxString& summary){
	SetStatusText(summary, Field_Monitoring_Summary);
}

wxBEGIN_EVENT_TABLE(PSUStatusBar, wxStatusBar)
EVT_SIZE(PSUStatusBar::OnSize)
#if wxUSE_CHECKBOX
//EVT_CHECKBOX(StatusBar_Checkbox, PSUStatusBar::OnToggleClock)
#endif
#if wxUSE_TIMER
EVT_TIMER(wxID_ANY, PSUStatusBar::OnTimer)
#endif
EVT_IDLE(PSUStatusBar::OnIdle)
wxEND_EVENT_TABLE()