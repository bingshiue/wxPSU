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
#include "PMBUSCommandType.h"

/**
@brief Serial Port Read Thread.
*/
class SerialReadThread : public wxThread{
public:
	SerialReadThread(wxSemaphore* semaphore, PMBUSCOMMAND_t *pmBusCommand, RECVBUFF_t *recvBuff, unsigned int recvBuffSize);
	virtual ~SerialReadThread();

	bool m_running;

	wxSemaphore* m_rxTxSemaphore;

	PMBUSCOMMAND_t *m_pmBusCommand;

	RECVBUFF_t* m_recvBuff;

	unsigned int m_recvBuffSize;

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif