/**
* @file SerialPortReadThread.h
*/
#ifndef _SERIALPORTSENDTHREAD_H_
#define _SERIALPORTSENDTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "SerialPort.h"

/**
@brief Serial Port Send Thread.
*/
class SerialSendThread : public wxThread{
public:
	SerialSendThread(wxSemaphore* semaphore);
	virtual ~SerialSendThread();

	wxSemaphore* m_rxTxSemaphore;

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif