/** 
 * @file PMBUSArtProv.h
 */
#ifndef _PMBUSARTPROV_H_
#define _PMBUSARTPROV_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/artprov.h"

class PMBUSArtProvider : public wxArtProvider
{
protected:
	virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client,
		const wxSize& size) wxOVERRIDE;
};

#endif