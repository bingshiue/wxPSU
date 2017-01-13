/**
 * @file PMBUSBitmapButton.cpp
 */

#include "PMBUSBitmapButton.h"

PMBUSBitmapButton::PMBUSBitmapButton(wxWindow *parent,
	wxWindowID id,
	const wxBitmap& bitmap,
	const wxPoint& pos,
	const wxSize& size,
	long style) : wxBitmapButton(parent, id, bitmap, pos, size, style){

}

PMBUSBitmapButton::~PMBUSBitmapButton(){

}

void PMBUSBitmapButton::OnMouseEnter(wxMouseEvent& event){
	SetCursor(wxCURSOR_HAND);
}

void PMBUSBitmapButton::OnMouseLeave(wxMouseEvent& event){
	SetCursor(wxNullCursor);
}

wxBEGIN_EVENT_TABLE(PMBUSBitmapButton, wxBitmapButton)
EVT_ENTER_WINDOW(PMBUSBitmapButton::OnMouseEnter)
EVT_LEAVE_WINDOW(PMBUSBitmapButton::OnMouseLeave)
wxEND_EVENT_TABLE()