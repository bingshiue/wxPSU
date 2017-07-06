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
#define TP_SendRebootCheckTask (0.5f)
#define TP_ReceiveRebootCheckTask (0.5f)
#define TP_UserCancelISPPostDelayTask (0.9f)
#define TP_UserCancelISPTask (0.9f)
#define TP_SendUSBAdaptorBitRateTask (0.5f)
#define TP_SendUSBAdaptorUARTSettingTask (0.5f)
#define TP_SendUSBAdaptorConfigTask (0.5f)
#define TP_SendUSBAdaptorParameterTask (0.5f)
#define TP_ReceiveUSBAdaptorSettingCMDTask (0.5f)
#define TP_ClearIOReadBufferTask (0.5f)
#define TP_PMBUSReadTestTask (0.5f)
#define TP_PMBUSWriteTestTask (0.5f)
#define TP_PMBUSBlockWRTestTask (0.5f)
#define TP_PickitConfigTask (0.5f)
#define TP_E2PRomWriteDataTask (0.5f)
#define TP_E2PRomReadDataTask (0.5f)
#define TP_SendReadCMDTask (0.5f)
#define TP_ReceiveReadCMDTask (0.5f)
#define TP_FindAvailableSlaveI2CDeviceTask (0.5f)

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
	task_ID_ReceiveISPEndCMDTask,
	task_ID_SendRebootCheckTask,
	task_ID_ReceiveRebootCheckTask,
	task_ID_UserCancelISPPostDelayTask,
	task_ID_UserCancelISPTask,
	task_ID_SendUSBAdaptorBitRateTask,
	task_ID_SendUSBAdaptorUARTSettingTask,
	task_ID_SendUSBAdaptorConfigTask,
	task_ID_SendUSBAdaptorParameterTask,
	task_ID_ReceiveUSBAdaptorSettingCMDTask,
	task_ID_ClearIOReadBufferTask,
	task_ID_PMBUSReadTestTask,
	task_ID_PMBUSWriteTestTask,
	task_ID_PMBUSBlockWRTestTask,
	task_ID_PickitConfigTask,
	task_ID_E2PRomWriteDataTask,
	task_ID_E2PRomReadDataTask,
	task_ID_SendReadCMDTask,
	task_ID_ReceiveReadCMDTask,
	task_ID_FindAvailableSlaveI2CDeviceTask,
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

	/**
	 * @brief Product ISP Start CMD Send Buffer.
	 */
	unsigned int ProductISPStartCMDSendBuffer(unsigned char* buffer);
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

class SendRebootCheckTask : public TaskEx {
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
	SendRebootCheckTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser *m_tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~SendRebootCheckTask(void);

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

class ReceiveRebootCheckTask : public TaskEx {
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
	ReceiveRebootCheckTask(IOACCESS* ioaccess, unsigned int* currentIO, TIHexFileParser* m_tiHexFileStat, unsigned char* ispStatus);

	/**
	* @brief Deconstructor.
	*/
	~ReceiveRebootCheckTask(void);

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

class SendReadCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	pmbusReadCMD_t m_pmbusReadCommand;/**< Read Command */
	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];/**< Send Buffer */

	double m_elapsedTimer;/**< for compute elapsed time */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

public:
	/**
	 * @brief Constructor.
	 */
	SendReadCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, pmbusReadCMD_t pmbusReadCommand);

	/**
	 * @brief Deconstructor.
	 */
	~SendReadCMDTask(void);

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
	 * @brief Product ReadCMD Buffer.
	 */
	int ProductReadCMDBuffer(PMBUSReadCMD_t* pmBusReadCMD, unsigned char* sendBuffer, unsigned int* currentIO);

};

class ReceiveReadCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	RECVBUFF_t    m_recvBuff;/**< Receive Buffer */
	pmbusReadCMD_t m_pmbusReadCommand;/**< Read Command */

	unsigned int m_bytesToRead;/**< Bytes To Read */

	double m_elapsedTimer;/**< for compute elapsed time */

	BOOL m_enumIOPort[IO_PORT_MAX_COUNT];

public:
	/**
	 * @brief Constructor.
	 */
	ReceiveReadCMDTask(IOACCESS* ioaccess, unsigned int* currentIO, pmbusReadCMD_t pmbusReadCommand);

	/**
	 * @brief Deconstructor.
	 */
	~ReceiveReadCMDTask(void);

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

class ReceiveUSBAdaptorSettingCMDTask : public TaskEx {
	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	* @brief Constructor.
	*/
	ReceiveUSBAdaptorSettingCMDTask(IOACCESS* ioaccess, unsigned int* currentIO);

	/**
	* @brief Deconstructor.
	*/
	~ReceiveUSBAdaptorSettingCMDTask(void);

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

class UserCancelISPPostDelayTask : public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

public:
	/**
	 * @brief Constructor.
	 */
	UserCancelISPPostDelayTask();

	/**
	 * @brief Deconstructor.
	 */
	~UserCancelISPPostDelayTask(void);

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

class UserCancelISPTask : public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

	unsigned char* m_ispStatus;

public:
	/**
	 * @brief Constructor.
	 */
	UserCancelISPTask(unsigned char* ispStatus);

	/**
	 * @brief Deconstructor.
	 */
	~UserCancelISPTask(void);

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

class SendUSBAdaptorBitRateTask : public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS* m_IOAccess;
	unsigned int *m_currentUseIO;

	unsigned short m_i2cBitRate;
	unsigned short m_spiBitRate;
	unsigned short m_canBitRate;

	unsigned short m_i2cBusTimeOut;

	unsigned int ProductSendBuffer(unsigned char *buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendUSBAdaptorBitRateTask(IOACCESS* ioaccess, unsigned int* currentUseIO, unsigned short i2cBitRate, unsigned short spiBitRate, unsigned short canBitRate, unsigned short m_i2cBusTimeOut);

	/**
	* @brief Deconstructor.
	*/
	~SendUSBAdaptorBitRateTask(void);

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

class SendUSBAdaptorUARTSettingTask : public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS* m_IOAccess;
	unsigned int *m_currentUseIO;

	unsigned char m_uartPort;
	unsigned char m_buadRate;
	unsigned char m_dataBits;
	unsigned char m_stopBits;
	unsigned char m_parityCheck;

	unsigned int ProductSendBuffer(unsigned char *buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendUSBAdaptorUARTSettingTask(IOACCESS* ioaccess, unsigned int* currentUseIO, unsigned char UartPort, unsigned char BuadRate, unsigned char DataBits, unsigned char StopBits, unsigned char ParityCheck);

	/**
	* @brief Deconstructor.
	*/
	~SendUSBAdaptorUARTSettingTask(void);

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

class SendUSBAdaptorConfigTask : public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS* m_IOAccess;
	unsigned int *m_currentUseIO;

	unsigned char  m_AutoReport;
	unsigned char  m_SMBus;
	unsigned char  m_PWMEnable;
	unsigned char  m_ClockInDI6;
	unsigned char  m_ClockInDI7;
	unsigned short m_I2CBusTimeout;

	unsigned int ProductSendBuffer(unsigned char *buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendUSBAdaptorConfigTask(
		IOACCESS*      ioaccess, 
		unsigned int*  currentUseIO, 
		unsigned char  AutoReport, 
		unsigned char  SMBus, 
		unsigned char  PWMEnable, 
		unsigned char  ClockInDI6,
		unsigned char  ClockInDI7,
		unsigned short I2CBusTimeout
	);

	/**
	* @brief Deconstructor.
	*/
	~SendUSBAdaptorConfigTask(void);

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

class SendUSBAdaptorParameterTask : public TaskEx{
	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS* m_IOAccess;
	unsigned int *m_currentUseIO;

	unsigned char  m_digitalOutput;
	unsigned short m_pwmFreq;
	unsigned short m_pwmDuty;

	unsigned int ProductSendBuffer(unsigned char *buffer);

public:
	/**
	* @brief Constructor.
	*/
	SendUSBAdaptorParameterTask(
		IOACCESS*      ioaccess,
		unsigned int*  currentUseIO,
		unsigned char  digitalOutput,
		unsigned short pwmFreq,
		unsigned short pwmDuty
		);

	/**
	* @brief Deconstructor.
	*/
	~SendUSBAdaptorParameterTask(void);

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

class ClearIOReadBufferTask : public TaskEx {

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */

	double m_elapsedTimer;/**< for compute elapsed time */
	bool m_readUntilNoData;

public:
	/**
	 * @brief Constructor.
	 */
	ClearIOReadBufferTask(IOACCESS* ioaccess, unsigned int* currentIO, bool readUntilNoData);

	/**
	* @brief Deconstructor.
	*/
	~ClearIOReadBufferTask(void);

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

class PMBUSReadTestTask :public TaskEx {
		
	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	PMBUSReadCMD_t* m_pmbusReadCMDArray;/**< Read CMD Array */
	int m_setsToRun;

	unsigned char m_sendBuff[256];
	unsigned char m_recvBuff[256];

	DWORD startTick;
	DWORD stopTick;

public:

	bool m_running;
	bool* m_outputLog;
	int runningIndex;
	int m_intervalTime;

	/**
	 * @brief Constructor.
	 */
	PMBUSReadTestTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSReadCMD_t* pmbusReadCMD, int setsToRun, bool* outputLog, int intervalTime);

	/**
	 * @brief Deconstructor.
	 */
	~PMBUSReadTestTask(void);

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
	 * @brief Product Read CMD Buffer.
	 */
	int ProductReadCMDBuffer(PMBUSReadCMD_t* pmBusReadCMD, unsigned char* sendBuffer, unsigned int* currentIO);

};

class PMBUSWriteTestTask :public TaskEx {
	
	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	PMBUSWriteCMD_t* m_pmbusWriteCMDArray;/**< Write CMD Array */
	int m_setsToRun;

	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];
	unsigned char m_recvBuff[SEND_BUFFER_MAX_SIZE];

	DWORD startTick;
	DWORD stopTick;

public:

	bool m_running;
	bool* m_outputLog;
	int runningIndex;
	int m_intervalTime;

	/**
	* @brief Constructor.
	*/
	PMBUSWriteTestTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSWriteCMD_t* pmbusWriteCMD, int setsToRun, bool* outputLog, int intervalTime);

	/**
	* @brief Deconstructor.
	*/
	~PMBUSWriteTestTask(void);

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
	* @brief Product Write CMD Buffer.
	*/
	int ProductWriteCMDBuffer(PMBUSWriteCMD_t* pmBusWriteCMD, unsigned char* sendBuffer, unsigned int* currentIO);
};

class PMBUSBlockWRTestTask :public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */
	PMBUSBlockWRCMD_t* m_pmbusBlockWRCMDArray;/**< Block WR CMD Array */
	int m_setsToRun;

	unsigned char m_sendBuff[SEND_BUFFER_MAX_SIZE];
	unsigned char m_recvBuff[SEND_BUFFER_MAX_SIZE];

	DWORD startTick;
	DWORD stopTick;

public:

	bool m_running;
	bool* m_outputLog;
	int runningIndex;
	int m_intervalTime;

	/**
	* @brief Constructor.
	*/
	PMBUSBlockWRTestTask(IOACCESS* ioaccess, unsigned int* currentIO, PMBUSBlockWRCMD_t* pmbusBlockWRCMD, int setsToRun, bool* outputLog, int intervalTime);

	/**
	* @brief Deconstructor.
	*/
	~PMBUSBlockWRTestTask(void);

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
	* @brief Product Block Write Read CMD Buffer.
	*/
	int ProductBlockWRCMDBuffer(PMBUSBlockWRCMD_t* pmBusBlockWRCMD, unsigned char* sendBuffer, unsigned int* currentIO);
};

#define MAX_FRU_FILE_SIZE  256 // Max FRU File Size 
class E2PRomWriteDataTask : public TaskEx {
	wxEvtHandler *m_evtHandler;
	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */

	unsigned char m_e2pRomSlaveAddr;/**< E2PRom Slave Address */
	unsigned char *m_fruBinaryContent;/**< FRU Binary Content */
	unsigned int m_fruBinaryLength;/**< FRU Binary Length */

	unsigned char m_e2pRomContent[MAX_FRU_FILE_SIZE];/**< Buffer for Put Read E2PRom Content */

public:

	bool m_running;
	bool* m_outputLog;
	int runningIndex;
	int m_writeIntervalTime;
	int m_readIntervalTime;

	/**
	 * @brief Constructor.
	 */
	E2PRomWriteDataTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler, unsigned char e2pRomSlaveAddr, unsigned char* fruBinaryContent, unsigned int fruBinaryLength, bool* outputLog, int writeIntervalTime, int readIntervalTime);

	/**
	 * @brief Deconstructor.
	 */
	~E2PRomWriteDataTask(void);

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


	int DumpE2PROM(unsigned char* RecvBuffer, unsigned int* currentIO);

};

class E2PRomReadDataTask : public TaskEx {
	wxEvtHandler *m_evtHandler;
	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */

	unsigned char m_e2pRomSlaveAddr;/**< E2PRom Slave Address */
	unsigned char m_e2pRomContent[MAX_FRU_FILE_SIZE];/**< Buffer for Put Read E2PRom Content */
	unsigned char *m_targetE2pRomContent;/**< Pointer of Target E2PRom Content */

public:

	bool m_running;
	bool* m_outputLog;
	int runningIndex;
	int m_readIntervalTime;

	/**
	* @brief Constructor.
	*/
	E2PRomReadDataTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler, unsigned char e2pRomSlaveAddr, unsigned char* e2pRomContent,bool* outputLog, int readIntervalTime);

	/**
	* @brief Deconstructor.
	*/
	~E2PRomReadDataTask(void);

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


	int DumpE2PROM(unsigned char* RecvBuffer, unsigned int* currentIO);
};

class PickitConfigTask : public TaskEx {

	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS* m_IOAccess;
	unsigned int *m_currentUseIO;

public:

	/**
	 * @brief Constructor.
	 */
	PickitConfigTask(IOACCESS* ioaccess, unsigned int* currentIO);

	/**
	 * @brief Deconstructor.
	 */
	~PickitConfigTask(void);

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

#define MAX_SLAVE_DEVICES 128
class FindAvailableSlaveI2CDeviceTask : public TaskEx {
	wxEvtHandler *m_evtHandler;
	double m_elapsedTimer;/**< for compute elapsed time */

	IOACCESS     *m_IOAccess;/**< IO Access */
	unsigned int *m_CurrentIO;/**< Current IO */

	unsigned char m_SlaveAddr;/**< Slave Address */
	unsigned char m_AvailableSlaveDevices[MAX_SLAVE_DEVICES];/**< Available Slave Devices */
	unsigned char* m_pAvailableSlaveDevices;/**< Pointer of Available Slave Devices */

public:

	bool m_running;
	bool* m_outputLog;

	/**
	* @brief Constructor.
	*/
	FindAvailableSlaveI2CDeviceTask(IOACCESS* ioaccess, unsigned int* currentIO, wxEvtHandler* evtHandler, unsigned char* availableSlaveDevices,bool* outputLog);

	/**
	* @brief Deconstructor.
	*/
	~FindAvailableSlaveI2CDeviceTask(void);

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
