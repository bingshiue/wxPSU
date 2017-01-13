/**
 * @file QUERYSequenceThread.h
 */
#ifndef _QUERYSEQUENCETHREAD_H_
#define _QUERYSEQUENCETHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/progdlg.h"

#include "CommonDef.h"
#include "IOAccess.h"
#include "PMBUSCommandType.h"
#include "Task.h"

/**
 * @brief QUERY Sequence Thread.
 */
class QUERYSequenceThread : public wxThread {
public:
	QUERYSequenceThread(
		IOACCESS*    ioaccess,
		unsigned int* currentIO,
		wxEvtHandler* evtHandlerMain,
		wxEvtHandler* evtHandler,
		wxProgressDialog *progressDialog
		);

	virtual ~QUERYSequenceThread();

	bool m_running;

	IOACCESS     *m_ioaccess;/**< IO Access */
	unsigned int *m_currentIO;/**< Current IO */
	wxEvtHandler *m_evtHandlerMain;
	wxEvtHandler *m_evtHandler;
	wxProgressDialog *m_progressDialog;

	unsigned char m_sendBuffer[64];
	RECVBUFF_t    m_recvBuff;
	IOPortReadCMDThread *m_IOPortReadCMDThread;
	wxSemaphore *m_rxTxSemaphore;

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;

};

#endif