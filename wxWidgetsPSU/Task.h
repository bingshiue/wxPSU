/**
 * @brief Task.h
 */
#ifndef _TASK_H_
#define _TASK_H_

#ifdef _MSC_VER
#pragma warning(disable:4291)
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/dataview.h"

#include "CommonDef.h"
#include "TaskSystem.h"
#include "TaskSystemEx.h"
#include "IOAccess.h"
#include "PMBUSCommandType.h"
#include "PMBUSDataViewListModel.h"
#include "PMBUSStatusPanel.h"
#include "PMBUSStatusDCHPanel.h"
#include "PMBUSHelper.h"
#include "PMBUSStatusBar.h"
#include "IOPortReadCMDThread.h"
#include "STDPage.h"
#include "PEC.h"

#define TP_SendWriteCMDTask (0.5f)
#define TP_ReceiveWriteCMDTask (0.5f)

enum {
	task_ID_SendWriteCMDTask = 0,
	task_ID_ReceiveWriteCMDTask,

};

class SendWriteCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	PMBUSSendCOMMAND_t m_pmbusSendCommand;/**< Send Command */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	double m_elapsedTimer;/**< for compute elapsed time */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

public:
	/**
	 * @brief Constructor.
	 */
	SendWriteCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand);

	/**
	 * @brief Deconstructor.
	 */
	~SendWriteCMDTask(void);

	/**
	 * @brief Draw function.
	 */
	void Draw(void);

	/**
	 * @brief Main update function.
	 *
	 * @param elapsedTime elapsed time
	 * @retval success or failure
	 */
	int Main(double elapsedTime);
	
};


class ReceiveWriteCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */
	PMBUSSendCOMMAND_t m_pmbusSendCommand;/**< Send Command */

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

public :
	/**
	 * @brief Constructor.
	 */
	ReceiveWriteCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand);

	/**
	 * @brief Deconstructor.
	 */
	~ReceiveWriteCMDTask(void);

	/**
	 * @brief Draw function.
	 */
	void Draw(void);

	/**
	 * @brief Main update function.
	 *
	 * @param elapsedTime elapsed time
	 * @retval success or failure
	 */
	int Main(double elapsedTime);

};

#endif
