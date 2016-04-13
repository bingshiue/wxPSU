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

#include "wx/grid.h"
#include "wx/headerctrl.h"
#include "wx/generic/gridctrl.h"
#include "wx/generic/grideditors.h"

class MyApp : public wxApp
{
public:
	/**
	 * @brief OnInit.
	 */
	virtual bool OnInit() wxOVERRIDE;
};


#endif