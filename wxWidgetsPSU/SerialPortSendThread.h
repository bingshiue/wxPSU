/**
 * @file SerialPortSendThread.h
 */
#ifndef _SERIALPORTSENDTHREAD_H_
#define _SERIALPORTSENDTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/dataview.h"
#include "SerialPort.h"
#include "PMBUSCommandType.h"
#include "PMBUSDataViewListModel.h"
#include "SerialPortReadThread.h"

#define CMD_DATA_SIZE 10/**< Command Data Size */

/**
@brief Serial Port Send Thread.
*/
class SerialSendThread : public wxThread{
public:
	unsigned int  m_running;/**< Indicate thread is running */
	unsigned int  m_register;/**< Register */
	unsigned char m_sendBuff[CMD_DATA_SIZE];/**< Send Buffer */
	unsigned int  m_pollingTime;/**< polling time */

	SerialSendThread(wxSemaphore* semaphore);
	SerialSendThread(wxSemaphore* semaphore, unsigned int runMode, unsigned int pollingTime, PMBUSCOMMAND_t *pmBusCommand, RECVBUFF_t *recvBuff, wxObjectDataPtr<PSUDataViewListModel>* dataViewListModel);
	virtual ~SerialSendThread();

	wxSemaphore *m_rxTxSemaphore;
	unsigned int m_runMode;
	PMBUSCOMMAND_t *m_pmBusCommand;
	RECVBUFF_t *m_recvBuff;

	SerialReadThread *m_serialPortReadCommandThread;

	wxObjectDataPtr<PSUDataViewListModel> *m_dataViewListCtrl;

	void productSendBuff(unsigned int command,unsigned int responseDataLength);

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif