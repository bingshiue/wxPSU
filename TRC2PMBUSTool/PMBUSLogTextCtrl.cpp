/**
 * @file PMBUSLogTextCtrl.cpp
 */
#include "PMBUSLogTextCtrl.h"

PMBUSLogTextCtrl::PMBUSLogTextCtrl(wxWindow* parent, wxWindowID id) : wxTextCtrl(parent, id, "", wxDefaultPosition, wxDefaultSize,
	wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH)
{
	// Initialize Popup Menu
	/*
	|----------------
	| Select All
	|----------------
	| Copy
	| Clear
	|----------------
	*/

	this->m_popupMenu = new wxMenu();

	this->m_selectAllMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_SELECTALL, wxT("Selec ALL"), wxT("Selec ALL"), wxITEM_NORMAL);
	this->m_selectAllMenuItem->SetBitmap(LOAD_PNG_RESOURCE(select_all_16));

	this->m_copyMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_COPY, wxT("Copy"), wxT("Copy"), wxITEM_NORMAL);
	this->m_copyMenuItem->SetBitmap(LOAD_PNG_RESOURCE(copy_16));

	this->m_clearMenuItem = new wxMenuItem((wxMenu*)0, MENU_ID_POPUP_CLEAR, wxT("Clear"), wxT("Clear"), wxITEM_NORMAL);
	this->m_clearMenuItem->SetBitmap(LOAD_PNG_RESOURCE(clear_16));

	// Append
	this->m_popupMenu->Append(this->m_selectAllMenuItem);

	this->m_popupMenu->AppendSeparator();

	this->m_popupMenu->Append(this->m_copyMenuItem);

	this->m_popupMenu->Append(this->m_clearMenuItem);

}

PMBUSLogTextCtrl::~PMBUSLogTextCtrl(){

}

void PMBUSLogTextCtrl::OnContextMenu(wxContextMenuEvent& event){
	
	PopupMenu(this->m_popupMenu);

#if 0
	wxMenu* menu = new wxMenu;
	// Some standard items
	menu->Append(wxID_UNDO, _("&Undo"));
	menu->Append(wxID_REDO, _("&Redo"));
	menu->AppendSeparator();
	menu->Append(wxID_CUT, _("Cu&t"));
	menu->Append(wxID_COPY, _("&Copy"));
	menu->Append(wxID_PASTE, _("&Paste"));
	menu->Append(wxID_CLEAR, _("&Delete"));
	menu->AppendSeparator();
	menu->Append(wxID_SELECTALL, _("Select &All"));

	// Add any custom items here

	PopupMenu(menu);
#endif
}

void PMBUSLogTextCtrl::OnSelectAll(wxCommandEvent& event){

	this->SelectAll();
}

void PMBUSLogTextCtrl::OnCopy(wxCommandEvent& event){

	this->Copy();
}

void PMBUSLogTextCtrl::OnClear(wxCommandEvent& event){
	
	this->Clear();
}

wxBEGIN_EVENT_TABLE(PMBUSLogTextCtrl, wxTextCtrl)
EVT_CONTEXT_MENU(PMBUSLogTextCtrl::OnContextMenu)
EVT_MENU(MENU_ID_POPUP_SELECTALL, PMBUSLogTextCtrl::OnSelectAll)
EVT_MENU(MENU_ID_POPUP_COPY, PMBUSLogTextCtrl::OnCopy)
EVT_MENU(MENU_ID_POPUP_CLEAR, PMBUSLogTextCtrl::OnClear)
wxEND_EVENT_TABLE()
