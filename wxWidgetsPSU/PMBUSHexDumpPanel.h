/**
 * @file PMBUSHexDumpPanel.h
 */
#ifndef _PMBUSHEXDUMP_H_
#define _PMBUSHEXDUMP_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class PMBUSHexDumpPanel : public wxScrolledWindow {
public:
	/**
	  * @brief Constructor.
	*/
	PMBUSHexDumpPanel(wxWindow* parent);
	/**
	 * @brief Deconstructor.
	 */
	~PMBUSHexDumpPanel();

protected:


private:

};

#endif