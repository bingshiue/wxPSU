/**
 * @file PMBUSFWUpdatePanel.h
 */
#ifndef _PMBUSFWUPDATEPANEL_H
#define _PMBUSFWUPDATEPANEL_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/progdlg.h"

#include "CommonDef.h"
#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "TIHexFileParser.h"
#include "TIHexMMAPModel.h"
#include "PMBUSLogTextCtrl.h"

#include "Task.h"

enum {
	ID_HEXMMAP_DVC = 8100,

	MENU_ID_POPUP_SAVEHEX,

	CID_WRITE_BUTTON,
	CID_CLOSE_BUTTON,
};

class PMBUSFWUpdatePanel : public wxPanel, private wxLog {
public:
	
	PMBUSFWUpdatePanel(wxNotebook* parent, wxString hexFilePath, TIHexFileParser tiHexFileStat, IOACCESS* ioaccess, unsigned int* currentIO, bool* isMonitorRunning, unsigned char target, unsigned long developerMode);

	~PMBUSFWUpdatePanel();

	void SetupHexMMAPDVL(void);

	unsigned int& GetIndexOfNotebook(void);

	unsigned int ProductSendBuffer(unsigned char* buffer);

	bool isCloseButtonPressed(void);

protected :

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;

private:

	wxNotebook *m_parent;

	wxDataViewCtrl *m_tiHexMMAPDVC;

	wxObjectDataPtr<TIHexMMAPModel> m_tiHexMMAPModel;

	TIHexFileParser m_tiHexFileStat;

	IOACCESS *m_ioaccess;
	
	unsigned int *m_currentIO;

	bool *m_isMonitorRunning;

	unsigned char m_target;

	unsigned long m_developerMode;

	bool m_pressedCloseButton;

	wxMenu* m_popupMenu;
	wxMenuItem* m_saveHexMenuItem;

	wxStaticLine *m_st1;
	wxStaticLine *m_st2;
	//wxStaticLine *m_st3;

	wxStaticText *m_fileNameST;
	//wxTextCtrl *m_fileNameTC;

	wxStaticText *m_startAddressST;
	wxTextCtrl *m_startAddressTC;

	wxStaticText *m_endAddressST;
	wxTextCtrl *m_endAddressTC;

	wxStaticText *m_addressRangeST;
	wxTextCtrl *m_addressRangeTC;

	wxStaticText *m_dataBytesST;
	wxTextCtrl *m_dataBytesTC;
    
	wxButton *m_writeButton;
	wxButton *m_closeButton;

	wxFlexGridSizer *m_fileStatFGS;
	wxBoxSizer *m_buttonSizer;

	wxStaticBoxSizer *m_statisticSBS;

	wxBoxSizer *m_topLevelSizer;

	PMBUSLogTextCtrl *m_logTC;

	wxString m_hexFilePath;

	unsigned long m_startAddress;
	unsigned long m_endAddress;
	unsigned long m_addressRange;
	unsigned long m_dataBytes;

	unsigned int m_dvlRowCount;

	unsigned int m_indexOfNotebook;

	void OnWriteButton(wxCommandEvent& event);
	void OnCloseButton(wxCommandEvent& event);

	void OnPopUpMenu(wxDataViewEvent &event);
	void OnSaveHex(wxCommandEvent& event);

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	wxDECLARE_EVENT_TABLE();
};

#endif