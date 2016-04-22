 /**
  * @file PSUStatusBar.h
  * @brief Our custom status bar class.
  */
#ifndef _PSUSTATUSBAR_H_
#define _PSUSTATUSBAR_H_

#include "main.h"

class PSUStatusBar : public wxStatusBar
{
public:
	PSUStatusBar(wxWindow *parent, long style = wxSTB_DEFAULT_STYLE);
	virtual ~PSUStatusBar();

	void UpdateClock();

	// event handlers
#if wxUSE_TIMER
	void OnTimer(wxTimerEvent& WXUNUSED(event)) { UpdateClock(); }
#endif
	void OnSize(wxSizeEvent& event);
	void OnToggleClock(wxCommandEvent& event);
	void OnIdle(wxIdleEvent& event);

private:
	// toggle the state of the status bar controls
	void DoToggle();

	enum
	{
		Field_SerialPort_Setting = 0,
		Field_I2C_Clock,
		Field_Run_Mode,
		Field_Monitoring_Command,
		Field_Reserved,
		Field_Monitoring_Time,
		Field_Monitoring_Summary,
		Field_Max
	};

#if wxUSE_TIMER
	wxTimer m_timer;
#endif

#if wxUSE_CHECKBOX
	//wxCheckBox *m_checkbox;
#endif
	wxStaticBitmap *m_statbmp;

	wxStopWatch m_sw;
	time_t t1;
	time_t t2;
	long m_startTime;

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

#endif