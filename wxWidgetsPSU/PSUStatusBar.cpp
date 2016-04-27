/**
* @file PSUStatusBar.cpp
* @brief Our custom status bar class.
*/

#include "PSUStatusBar.h"

#ifdef __VISUALC__
// 'this' : used in base member initializer list -- so what??
#pragma warning(disable: 4355)
#endif

PSUStatusBar::PSUStatusBar(wxWindow *parent, long style) 
	: wxStatusBar(parent, wxID_ANY, style, "PSUStatusBar")
#if wxUSE_TIMER
	, m_timer(this)
#endif
#if wxUSE_CHECKBOX
	//, m_checkbox(NULL)
#endif
{
	int widths[Field_Max];
	widths[Field_SerialPort_Setting] = 120;
	widths[Field_I2C_Clock] = 50;
	widths[Field_Run_Mode] = 80;
	widths[Field_Monitoring_Command] = 150;
	widths[Field_Reserved] = 100;
	widths[Field_Monitoring_Time] = -1; // growable
	widths[Field_Monitoring_Summary] = -1;

#if wxUSE_CHECKBOX
	//m_checkbox = new wxCheckBox(this, StatusBar_Checkbox, wxT("&Toggle clock"));
	//m_checkbox->SetValue(true);
#endif

	SetFieldsCount(Field_Max);
	SetStatusWidths(Field_Max, widths);

	this->SetStatusText(wxT("Com3-9600-N81"), Field_SerialPort_Setting);
	this->SetStatusText(wxT("100kHz"), Field_I2C_Clock);
	this->SetStatusText(wxT("Continually"), Field_Run_Mode);


#if wxUSE_TIMER
	m_timer.Start(1000);
#endif

	m_sw.Start();
	m_startTime = m_sw.Time()/1000;

	t1 = time(NULL);

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
	//SetStatusText(wxDateTime::Now().FormatTime(), Field_Clock);
	long currentTime = m_sw.Time()/1000;

	t2 = time(NULL);

	wxDateTime wdt(t2-t1);
 
		
	//wxDateTime::ToTimezone(wxDateTime::GMT0);

	//wxString strLong = wxString::Format(wxT("%ld"), currentTime - m_startTime);

	//SetStatusText(strLong, Field_Monitoring_Time);

	SetStatusText(wdt.FormatISOTime(), Field_Monitoring_Time);

}

void PSUStatusBar::OnSize(wxSizeEvent& event){

}

void PSUStatusBar::OnToggleClock(wxCommandEvent& event){

}

void PSUStatusBar::OnIdle(wxIdleEvent& event){

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