/**
 * @file SerialPortReadThread.h
 */
#ifndef _SERIALPORTREADTHREAD_H_
#define _SERIALPORTREADTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "SerialPort.h"

/**
@brief Serial Port Read Thread.
*/
class SerialReadThread : public wxThread{
public:
	SerialReadThread(wxSemaphore* semaphore);
	virtual ~SerialReadThread();

	wxSemaphore* m_rxTxSemaphore;

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif