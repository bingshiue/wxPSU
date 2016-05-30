/**
 * @file CalibrationDialog.h
 */

#ifndef _CALIBRATIONDIALOG_H_
#define _CALIBRATIONDIALOG_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>
#include <wx/artprov.h>
#include <wx/colordlg.h>
#include <wx/wfstream.h>
#include <wx/animate.h>
#include <wx/statline.h>

#include "CommonDef.h"

class CalibrationDialog : public wxDialog
{
public:
	CalibrationDialog(wxWindow *parent);

	void OnButton(wxCommandEvent& event);

	enum {
		CID_BTN_APPLY = 6001,
		CID_BTN_DONE,
		CID_BTN_READ,
		//CID_BTN_EXIT

		CID_CB_CALIBRATION_ITEM,
		CID_CB_POINTER,
	};

	enum {
		Output_Current_Main = 0,
		Output_Current_SB,
		Output_Voltage_Main_PWM,
		Output_Voltage_SB_PWM,
		Output_Voltage_LS_PWM,
		AC_Vin_Current_110V_AC,
		AC_Vin_Current_220V_AC,
		AC_Vin_Power_110V_AC,
		AC_Vin_Power_220V_AC
	};

	enum {
		Pointer_Selection_0 = 0,
		Pointer_Selection_1,
		Pointer_Selection_2,
		Pointer_Selection_3,
	};

private:
	wxButton *m_btnApply, *m_btnDone, *m_btnRead, *m_btnExit;

	wxBoxSizer *m_bottonSizer;

	wxBoxSizer *m_calibrationItemSizer;

	wxStaticBoxSizer *m_settingControlSBS;

	wxStaticText *m_calibrationItemST;
	wxComboBox *m_calibrationItemCB;

	wxGridSizer *m_calibrationItemGridSizer;

	wxStaticText *m_pointerST;
	wxComboBox *m_pointerCB;

	wxStaticText *m_padding1ST;
	wxStaticText *m_padding2ST;

	wxStaticText *m_data1ST;
	wxTextCtrl *m_data1TC;

	wxStaticText *m_resolution1ST;
	wxTextCtrl *m_resolution1TC;

	wxStaticText *m_data2ST;
	wxTextCtrl *m_data2TC;

	wxStaticText *m_resolution2ST;
	wxTextCtrl *m_resolution2TC;

	wxBoxSizer *m_sizerTop;

	void OnBtnApply(wxCommandEvent& event);
	void OnBtnDone(wxCommandEvent& event);
	void OnBtnRead(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};



#endif