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
#include "PMBUSHelper.h"
#include "PMBUSLogTextCtrl.h"
#include "Task.h"

#define CALIBRATION_DIALOG_WIDTH   800 /**< Calibration Dialog Width */
#define CALIBRATION_DIALOG_HEIGHT  400 /**< Calibration Dialog Height */

typedef struct data_resolution_t {

	double m_data1;/**< Data 1 */
	double m_Resolution1;/**< Resolution 1 */
	double m_data2;/**< Data 2 */ 
	double m_Resolution2;/**< Resolution 2 */

} DATA_RESOLUTION_t;

#define CALIBRARTION_ITEM_SIZE  10 /**< Size Of Calibration Items */

class CalibrationDialog : public wxDialog, private wxLog
{
public:
	CalibrationDialog(wxWindow *parent, IOACCESS* ioaccess, unsigned int* currentIO, bool* monitor_running, bool* monitor_pause, std::vector<PMBUSSendCOMMAND_t>* sendCMDVector);

	~CalibrationDialog();

	void OnButton(wxCommandEvent& event);

	enum {
		CID_BTN_APPLY = 6001,
		CID_BTN_DONE,
		CID_BTN_READ,
		//CID_BTN_EXIT

		CID_CB_CALIBRATION_ITEM,
		CID_CB_POINTER,

		CID_TC_DATA_1,
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
		AC_Vin_Power_220V_AC,
		ACS_SETPOINT,
		CALIBRATION_ITEM_SIZE
	};

	enum {
		Pointer_Selection_0 = 0,
		Pointer_Selection_1,
		Pointer_Selection_2,
		Pointer_Selection_3,
		Pointer_Selection_4,
		Pointer_Selection_5,
		Pointer_Selection_6,
		Pointer_Selection_7,
		Pointer_Selection_8,
		Pointer_Selection_9,
	};

	static unsigned char calibrationItemCommand[CALIBRATION_ITEM_SIZE];/**< Calibration Item Command */
	static unsigned char calibrationItemPointerMask[CALIBRATION_ITEM_SIZE];/**< Calibration Item Pointer Mask Value */
	static unsigned char calibrationItemPointerValue[10];/**< Calibration Item Pointer Value */
	static double defSelectablePointerCount[CALIBRATION_ITEM_SIZE];/**< Default Selectable Pointer Count */
	static DATA_RESOLUTION_t m_dataResolution[CALIBRATION_ITEM_SIZE];/**< Data & Resolution */

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:
	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

	bool *m_monitor_running;
	bool *m_monitor_pause;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

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

	wxString DecimalCharIncludes;
	wxTextValidator m_numberValidator;

	PMBUSLogTextCtrl *m_logTC;

	wxLog* m_oldLog;

	wxString m_calibrationItemString[CALIBRARTION_ITEM_SIZE];

	void OnBtnApply(wxCommandEvent& event);
	void OnBtnDone(wxCommandEvent& event);
	void OnBtnRead(wxCommandEvent& event);

	void OnCBCalibrationItem(wxCommandEvent& event);
	void OnCBPointer(wxCommandEvent& event);

	void OnTCData1(wxCommandEvent& event);

	int ProductSendBuffer(unsigned char* buffer, unsigned int SizeOfBuffer, bool done = false);

	bool ValidateInputData(void);

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	wxDECLARE_EVENT_TABLE();
};



#endif
