/**
 * @file PMBUSFWUpdatePanel.h
 */
#ifndef _PMBUSFWUPDATEPANEL_H
#define _PMBUSFWUPDATEPANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "TIHexFileParser.h"
#include "TIHexMMAPModel.h"

enum {
	ID_HEXMMAP_DVC = 8100,

	CID_WRITE_BUTTON,
	CID_CLOSE_BUTTON,
};

class PMBUSFWUpdatePanel : public wxPanel {
public:
	
	PMBUSFWUpdatePanel(wxNotebook* parent, wxString hexFilePath, TIHexFileParser& tiHexFileStat);

	~PMBUSFWUpdatePanel();

	void SetupHexMMAPDVL(void);

	unsigned int& GetIndexOfNotebook(void) { return this->m_indexOfNotebook;  }

protected :


private:

	wxNotebook *m_parent;

	wxDataViewCtrl *m_tiHexMMAPDVC;

	wxObjectDataPtr<TIHexMMAPModel> m_tiHexMMAPModel;

	TIHexFileParser m_tiHexFileStat;

	wxStaticText *m_fileNameST;

	wxStaticText *m_startAddressST;
	wxStaticText *m_endAddressST;
	wxStaticText *m_addressRangeST;
	wxStaticText *m_dataBytesST;
    

	wxButton *m_writeButton;
	wxButton *m_closeButton;

	wxBoxSizer *m_buttonSizer;

	wxStaticBoxSizer *m_statisticSBS;

	wxBoxSizer *m_topLevelSizer;

	wxString m_hexFilePath;

	unsigned long m_startAddress;
	unsigned long m_endAddress;
	unsigned long m_addressRange;
	unsigned long m_dataBytes;


	unsigned int m_indexOfNotebook;

	void OnWriteButton(wxCommandEvent& event);
	void OnCloseButton(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif