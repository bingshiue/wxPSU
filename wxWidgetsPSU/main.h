/**
 * @file main.h
 */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
	/**
	 * @brief OnInit.
	 */
	virtual bool OnInit() wxOVERRIDE;
};


#endif