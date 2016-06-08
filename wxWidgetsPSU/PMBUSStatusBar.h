 /**
  * @file PMBUSStatusBar.h
  * @brief Our custom status bar class.
  */
#ifndef _PMBUSSTATUSBAR_H_
#define _PMBUSSTATUSBAR_H_

#include "CommonDef.h"
#include "main.h"

class PMBUSStatusBar : public wxStatusBar
{
public:
	enum
	{
		Field_IO_Setting = 0,
		Field_I2C_Clock,
		Field_Run_Mode,
		Field_Monitoring_Command,
		Field_Gauge,
		Field_Monitoring_Time,
		Field_Monitoring_Summary,
		Field_Max
	};

	PMBUSStatusBar(wxWindow *parent, long style = wxSTB_DEFAULT_STYLE);
	virtual ~PMBUSStatusBar();

	void UpdateClock();

	// event handlers
#if wxUSE_TIMER
	void OnTimer(wxTimerEvent& WXUNUSED(event)) { UpdateClock(); }
#endif
	void OnSize(wxSizeEvent& event);
	void OnToggleClock(wxCommandEvent& event);
	void OnIdle(wxIdleEvent& event);

	wxTimer* getTimer(void) { return &this->m_timer; }
	wxGauge* getGauge(void) { return this->m_gauge; }
	wxDateTime& getBeginDateTime(void) { return this->m_beginTime; }

	void setMonitoringCMDName(wxString& cmdName);
	void setMonitoringSummary(wxString& summary);

private:
	// toggle the state of the status bar controls
	void DoToggle();

#if wxUSE_TIMER
	wxTimer m_timer;
#endif

#if wxUSE_CHECKBOX
	//wxCheckBox *m_checkbox;
#endif
	wxStaticBitmap *m_statbmp;

	wxGauge *m_gauge;

	//wxStopWatch m_sw;
	wxDateTime m_beginTime;

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

#endif