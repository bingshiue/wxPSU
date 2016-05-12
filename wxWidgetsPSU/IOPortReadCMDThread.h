/**
 * @file IOPortReadCMDThread.h
 */
#ifndef _IOPORTREADCMDTHREAD_H_
#define _IOPORTREADCMDTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "IOAccess.h"
#include "PMBUSCommandType.h"

/**
@brief Serial Port Read Thread.
*/
class IOPortReadCMDThread : public wxThread {
public:
	IOPortReadCMDThread(
						IOACCESS*    ioaccess,
						unsigned int* currentIO,
						wxSemaphore* semaphore, 
						PMBUSCOMMAND_t *pmBusCommand, 
						RECVBUFF_t *recvBuff, 
						unsigned int recvBuffSize, 
						unsigned int bytesToRead
						);
	virtual ~IOPortReadCMDThread();

	bool m_running;

	IOACCESS     *m_IOAccess;/**< IO Access */

	unsigned int *m_CurrentIO;/**< Current IO */

	wxSemaphore* m_rxTxSemaphore;

	PMBUSCOMMAND_t *m_pmBusCommand;

	RECVBUFF_t* m_recvBuff;

	unsigned int m_recvBuffSize;

	unsigned int m_bytesToRead;

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif