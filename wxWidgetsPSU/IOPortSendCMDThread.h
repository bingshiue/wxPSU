/**
 * @file IOPortSendCMDThread.h
 */
#ifndef _IOPORTSENDCMDTHREAD_H_
#define _IOPORTSENDCMDTHREAD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/dataview.h"
#include "CommonDef.h"
#include "AppSettings.h"
#include "IOAccess.h"
#include "PMBUSCommandType.h"
#include "PMBUSDataViewListModel.h"
#include "PMBUSStatusPanel.h"
#include "PMBUSStatusDCHPanel.h"
#include "PMBUSHelper.h"
#include "PSUStatusBar.h"
#include "IOPortReadCMDThread.h"
#include "STDPage.h"
#include "PEC.h"

#define SERIAL_SEND_DATA_SIZE  10/**< Serial Send Data Size */
#define HID_SEND_DATA_SIZE  64/**< HID Send Data Size */

/**
@brief Serial Port Send Thread.
*/
class IOPortSendCMDThread : public wxThread {
public:
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	bool          m_running;/**< Indicate thread is running */
	unsigned int  m_register;/**< Register */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */
	unsigned int  *m_pollingTime;/**< polling time */
	BOOL          m_enumIOPort[IO_PORT_MAX_COUNT];

	IOPortSendCMDThread(wxSemaphore* semaphore);
	IOPortSendCMDThread(
		IOACCESS*    ioaccess,
		unsigned int* currentIO,
		wxSemaphore* semaphore,
		AppSettings_t* appSettings,
		unsigned int* pollingTime,
		PMBUSCOMMAND_t *pmBusCommand,
		RECVBUFF_t *recvBuff,
		wxObjectDataPtr<PSUDataViewListModel>* dataViewListModel,
		PSUStatusBar *status_bar,
		STDPage* stdPage,
		PMBUSStatusPanel* pmbusStatusPanel,
		PMBUSStatusDCHPanel* pmbusStatusDCHPanel,
		std::vector<PMBUSSendCOMMAND_t> *sendCMDVector
						);
	virtual ~IOPortSendCMDThread();

	wxSemaphore *m_rxTxSemaphore;
	AppSettings_t *m_appSettings;
	PMBUSCOMMAND_t *m_pmBusCommand;
	RECVBUFF_t *m_recvBuff;

	IOPortReadCMDThread *m_IOPortReadCMDThread;

	wxObjectDataPtr<PSUDataViewListModel> *m_dataViewListCtrl;
	PSUStatusBar  *m_status_bar;
	STDPage *m_stdPage;
	PMBUSStatusPanel* m_pmbusStatusPanel;
	PMBUSStatusDCHPanel* m_pmbusStatusDCHPanel;

	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	void productSendBuff(unsigned int idx, unsigned int command, unsigned int responseDataLength);
	void productDataBuff(unsigned int cmdIndex, unsigned int responseDataLength);

	void UpdateSTDPage(void);

	void UpdateSTATUSPanel(unsigned int index);

	unsigned int findPMBUSCMDIndex(unsigned int cmd_register);

	// thread execution starts here
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
};

#endif