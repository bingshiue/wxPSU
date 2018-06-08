/**
 * @file ISPSequenceThread.h
 */
#ifndef _ISPSEQUENCETHREAD_H_
#define _ISPSEQUENCETHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/progdlg.h"

#include "IOAccess.h"
#include "PMBUSCommandType.h"
//#include "TIHexFileParser.h"
#include "tihexclass.h"
#include "TIHexMMAPModel.h"

#include "Task.h"

/**
 * @brief ISP Sequence Thread.
 */
class ISPSequenceThread : public wxThread {
public:
	ISPSequenceThread(
		wxString hexFilePath,
		tihex<>* tiHexFileStat,
		IOACCESS*    ioaccess,
		unsigned int* currentIO,
		unsigned char target, 
		unsigned long developerMode,
		wxEvtHandler* evtHandlerMain,
		wxEvtHandler* evtHandler,
		unsigned char* ispStatus,
		wxProgressDialog *progressDialog
		);

	virtual ~ISPSequenceThread();

	bool m_running;

	wxString m_hexFilePath;

	tihex<>* m_tiHexFileStat;

	IOACCESS     *m_ioaccess;/**< IO Access */

	unsigned int *m_currentIO;/**< Current IO */

	unsigned char m_target;

	unsigned long m_developerMode;

	wxEvtHandler *m_evtHandlerMain;

	wxEvtHandler *m_evtHandler;

	unsigned char *m_ispStatus;

	wxProgressDialog *m_progressDialog;

	unsigned long m_startAddress;
	unsigned long m_endAddress;
	unsigned long m_addressRange;
	unsigned long m_dataBytes;


	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;

	unsigned int ProductSendBuffer(unsigned char* buffer);
};

#endif
