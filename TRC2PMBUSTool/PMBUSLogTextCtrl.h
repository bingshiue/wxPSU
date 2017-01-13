/**
 * @file PMBUSLogTextCtrl.h
 */
#ifndef _PMBUSLOGTEXTCTRL_H_
#define _PMBUSLOGTEXTCTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "CommonDef.h"


class PMBUSLogTextCtrl : public wxTextCtrl {

public:
	
	enum {
		MENU_ID_POPUP_SELECTALL = 7050,
		MENU_ID_POPUP_COPY,
		MENU_ID_POPUP_CLEAR
	};

	PMBUSLogTextCtrl(wxWindow* parent, wxWindowID id);

	~PMBUSLogTextCtrl();

protected:

	void OnContextMenu(wxContextMenuEvent& event);

	void OnSelectAll(wxCommandEvent& event);

	void OnCopy(wxCommandEvent& event);

	void OnClear(wxCommandEvent& event);

private:

	wxMenu *m_popupMenu;

	wxMenuItem *m_selectAllMenuItem;
	wxMenuItem *m_copyMenuItem;
	wxMenuItem *m_clearMenuItem;


	wxDECLARE_EVENT_TABLE();

};



#endif