/**
 * @file PMBUSBitmapButton.h
 */

#ifndef _PMBUSBITMAPBUTTON_H_
#define _PMBUSBITMAPBUTTON_H_

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
#include "version.h"

class PMBUSBitmapButton : public wxBitmapButton {

public:

	PMBUSBitmapButton(wxWindow *parent,
		wxWindowID id,
		const wxBitmap& bitmap,
		const wxPoint& pos,
		const wxSize& size,
		long style);

	~PMBUSBitmapButton();

private:

	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif