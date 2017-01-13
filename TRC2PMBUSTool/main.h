/**
 * @file main.h
 */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/colordlg.h"
#include "wx/fontdlg.h"
#include "wx/numdlg.h"
#include "wx/aboutdlg.h"

#include "wx/dataview.h"
#include "wx/datetime.h"
#include "wx/splitter.h"
#include "wx/aboutdlg.h"
#include "wx/colordlg.h"
#include "wx/choicdlg.h"
#include "wx/numdlg.h"
#include "wx/spinctrl.h"
#include "wx/imaglist.h"
#include "wx/notebook.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/datstrm.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>

#include "wx/grid.h"
#include "wx/headerctrl.h"
#include "wx/generic/gridctrl.h"
#include "wx/generic/grideditors.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/infobar.h"
#include "wx/fswatcher.h"
#include <wx/stdpaths.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/busyinfo.h>
#include <wx/snglinst.h>

#define APP_NAME "TRC2 PMBUS Tool"

class WXPSU : public wxApp
{
public:
	/**
	 * @brief OnInit.
	 */
	virtual bool OnInit() wxOVERRIDE;

	/**
	 * @brief OnExit.
	 */
	virtual int OnExit() wxOVERRIDE;

private:

	wxSingleInstanceChecker *m_singleInstanceChecker;
};


#endif