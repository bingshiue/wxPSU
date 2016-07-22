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
#include "PMBUSCMDListModel.h"
#include "PMBUSStatusPanel.h"
#include "PMBUSStatusDCHPanel.h"
#include "PMBUSHelper.h"
#include "PMBUSStatusBar.h"
#include "IOPortReadCMDThread.h"
#include "STDPage.h"
#include "PEC.h"
#include "TIHexFileParser.h"

#define TP_SendWriteCMDTask (0.5f)
#define TP_ReceiveWriteCMDTask (0.5f)
#define TP_SendISPStartCMDTask (0.5f)
#define TP_ReceiveISPStartCMDTask (0.5f)
#define TP_SendISPStartVerifyCMDTask (0.5f)
#define TP_ReceiveISPStartVerifyCMDTask (0.5f)
#define TP_SendISPWriteDataTask (0.5f)
#define TP_ReceiveISPWriteDataTask (0.5f)
#define TP_SendISPCheckStatusTask (0.5f)
#define TP_ReceiveISPCheckStatusTask (0.5f)
#define TP_SendISPEndCMDTask (0.5f)
#define TP_ReceiveISPEndCMDTask (0.5f)

enum {
	task_ID_SendWriteCMDTask = 0,
	task_ID_ReceiveWriteCMDTask,
	task_ID_SendISPStartCMDTask,
	task_ID_ReceiveISPStartCMDTask,
	task_ID_SendISPStartVerifyCMDTask,
	task_ID_ReceiveISPStartVerifyCMDTask,
	task_ID_SendISPWriteDataTask,
	task_ID_ReceiveISPWriteDataTask,
	task_ID_SendISPCheckStatusTask,
	task_ID_ReceiveISPCheckStatusTask,
	task_ID_SendISPEndCMDTask,
	task_ID_ReceiveISPEndCMDTask
};

class SendISPStartCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	PMBUSSendCOMMAND_t m_pmbusSendCommand;/**< Send Command */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned char m_target;

	double m_elapsedTimer;/**< for compute elapsed time */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

public:
	/**
	* @brief Constructor.
	*/
	SendISPStartCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand, TIHexFileParser *m_tiHexFileStat, unsigned char* ispStatus, unsigned char target);

	/**
	* @brief Deconstructor.
	*/
	~SendISPStartCMDTask(void);

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

class ReceiveISPStartCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */
	PMBUSSendCOMMAND_t m_pmbusSendCommand;/**< Send Command */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned char m_target;

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

public:
	/**
	* @brief Constructor.
	*/
	ReceiveISPStartCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSSendCOMMAND_t pmbusSendCommand, TIHexFileParser* m_tiHexFileStat, unsigned char* ispStatus, unsigned char target);

	/**
	* @brief Deconstructor.
	*/
	~ReceiveISPStartCMDTask(void);

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

class SendISPStartVerifyCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned char m_target;

	double m_elapsedTimer;/**< for compute elapsed time */

	unsigned int ProductSendBuffer(unsigned char* buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendISPStartVerifyCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *m_tiHexFileStat, unsigned char* ispStatus, unsigned char target);

	/**
	* @brief Deconstructor.
	*/
	~SendISPStartVerifyCMDTask(void);

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

class ReceiveISPStartVerifyCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned char m_target;

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	* @brief Constructor.
	*/
	ReceiveISPStartVerifyCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* m_tiHexFileStat, unsigned char* ispStatus, unsigned char target);

	/**
	* @brief Deconstructor.
	*/
	~ReceiveISPStartVerifyCMDTask(void);

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

class SendISPWriteDataTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */

	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	* @brief Constructor.
	*/
	SendISPWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~SendISPWriteDataTask(void);

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
	/**
	 * @brief Product Send Buffer.
	 */
	unsigned int ProductSendBuffer(unsigned char *buffer);
};

class ReceiveISPWriteDataTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	 * @brief Constructor.
	 */
	ReceiveISPWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* m_tiHexFileStat, unsigned char* ispStatus);

	/**
	 * @brief Deconstructor.
	 */
	~ReceiveISPWriteDataTask(void);

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

class SendISPCheckStatusTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	double m_elapsedTimer;/**< for compute elapsed time */

	unsigned int ProductSendBuffer(unsigned char* buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendISPCheckStatusTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *m_tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~SendISPCheckStatusTask(void);

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

class ReceiveISPCheckStatusTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	* @brief Constructor.
	*/
	ReceiveISPCheckStatusTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* m_tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~ReceiveISPCheckStatusTask(void);

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

class SendISPEndCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	double m_elapsedTimer;/**< for compute elapsed time */

	unsigned int ProductSendBuffer(unsigned char* buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendISPEndCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *m_tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~SendISPEndCMDTask(void);

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

class ReceiveISPEndCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */

	TIHexFileParser *m_tiHexFileStat;
	unsigned char *m_ispStatus;

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	* @brief Constructor.
	*/
	ReceiveISPEndCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* m_tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~ReceiveISPEndCMDTask(void);

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
