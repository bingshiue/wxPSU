 /**
  * @file PMBUSHelper.h
  */
#ifndef _PMBUSHELPER_H_
#define _PMBUSHELPER_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "CommonDef.h"
#include "PMBUSStatus.h"
#include "PMBUSCommandType.h"
#include "AppSettings.h"
#include "USBInfoType.h"

class PMBUSHelper {
public :

	enum {
		positive = 0,
		negative
	};

	enum {
		response_ng = 0,
		response_ok,
	};

	static unsigned int IspErrRetry;
	static unsigned int IspStartVerifyRetry;
	static unsigned int CurrentCMDTableSize;
	static unsigned int CurrentISPTarget;

	static unsigned int runInMode;
	static int runInTimes;

	static unsigned char  cmd_3AH_previous;
	static unsigned char  cmd_78H_previous;
	static unsigned short cmd_79H_previous;
	static unsigned char  cmd_7AH_previous;
	static unsigned char  cmd_7BH_previous;
	static unsigned char  cmd_7CH_previous;
	static unsigned char  cmd_7DH_previous;
	static unsigned char  cmd_7EH_previous;
	static unsigned char  cmd_7FH_previous;
	static unsigned char  cmd_81H_previous;

	static void SetSlaveAddress(unsigned char slaveAddress);
	static unsigned char& GetSlaveAddress(void);
	static PMBUSSTATUS_t* GetPMBusStatus(void);
	static USBINFO* GetUSBInfo(void);

	static void SetAppSettings(AppSettings_t* appSettings);
	static AppSettings_t* GetAppSettings(void);

	static double ParseLinearDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer);
	static double ParseDirectDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer, PMBUSCOMMAND_t* PMBusCMDData);

	static int ProductDirectData(unsigned char *dest, double value, PMBUSCOMMAND_t* PMBusCMDData);

	static int ProductFakeLinearData(unsigned char *dest, double value, double scale);
	static int ProductLinearData(unsigned char *dest, double value, double scale);

	static int ProductReadCMDBuffer(PMBUSCOMMAND_t* pmBusCommand, unsigned char* sendBuffer,unsigned int* currentIO,unsigned int idx, unsigned int command, unsigned int responseDataLength);
	static int ProductReadCMDBuffer(PMBUSReadCMD_t* pmBusReadCMD, unsigned char* sendBuffer, unsigned int* currentIO);

	static int ProductWriteCMDBuffer(unsigned int *currentIO, unsigned char *buff, unsigned int sizeOfBuffer, unsigned char cmd, unsigned char *dataBuffer, unsigned int sizeOfDataBuffer);

	static void ProductDataBuffer(unsigned char* DestBuff, unsigned int* currentIO, unsigned char* SourceBuff, unsigned int responseDataLength);
	static void ProductDataBuffer(PMBUSCOMMAND_t* pmBusCommand, unsigned int* currentIO, unsigned int cmdIndex, unsigned int responseDataLength);


	static int ProductE2PRomWriteBuffer(unsigned char fruSlaveAddr, unsigned char* fruContentBuffer, unsigned int idx, unsigned char* sendBuffer, unsigned int* currentIO);
	static int ProductE2PRomReadBuffer(unsigned char fruSlaveAddr, unsigned int idx, unsigned char* sendBuffer, unsigned int* currentIO);
	static void PrintFRUContent(unsigned char* contentBuffer, unsigned int dumpSize);

	static long HexToDecimal(wxString string);

	static void GetNowDateTimeString(wxString& string);

	static unsigned char IsResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer);
	static unsigned char IsISPStartVerifyResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer, unsigned char target);
	static unsigned char IsISPCheckStatusResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer);
	static unsigned char IsISPRebootCheckResponseOK(unsigned int *currentIO, unsigned char *buffer, unsigned int sizeOfBuffer);
	static unsigned char ComputeISPDataCheckSum(unsigned char *buffer, unsigned int dataStartIndex, unsigned int dataEndIndex);

	static void PrintISPCheckStatusError(unsigned char error);

	static wxString& GetNowTimeString(void);

	static void GetPIDAndVIDFromString(wxString string, unsigned int* pid, unsigned int* vid);

	static void SetCurrentCMDTableSize(unsigned int size);

	static unsigned int GetCurrentCMDTableSize(void);

	static int& getTotalPhaseWriteReadLastError(void);

	static void setWinTitleBase(wxString base);

	static wxString& getWinTitleBase(void);

	static unsigned int& getCurrentISPTarget(void);

	static unsigned int IsI2CBusNotAcknowlwdge(unsigned int *currentIO, unsigned char *buffer, unsigned int SizeOfBuffer);

	static bool isOwnReadAccess(unsigned int access);

	static void setPMBUSCMDData(PMBUSCOMMAND_t *PMBusCMDData);

	static PMBUSCOMMAND_t* getPMBUSCMDData(void);

	static int getIndexOfCMD(int cmd, int page = 0);
	/**
	 * @brief Getter & Setter for FW Upload Mode Command.
	 */
	static unsigned char& getFWUploadModeCMD(void);
	/**
	 * @brief Getter & Setter for FW Upload Command.
	 */
	static unsigned char& getFWUploadCMD(void);
	/**
	 * @brief Getter & Setter for FW Upload Status Command.
	 */
	static unsigned char& getFWUploadStatusCMD(void);
	/**
	 * @brief Get Expected Response Data Length by I/O.
	 */
	static int getExpectedDataLengthByIO(unsigned int CurrentUseIO, unsigned int CMDResponseDataLength, unsigned char BaseDataLength);
	/**
	 * @brief Dump Receive Buffer.
	 */
	static void dumpReceiveBuffer(unsigned char* buffer, int bufferLength);
	/**
	 * @brief Re-Judge IO Thread Send Failure.
	 */
	static bool ReJudgeIOThreadSendFailure(bool failed, unsigned int CurrentUseIO);
	/**
	 * @brief Get BytesToRead Of Write CMD.
	 */
	static unsigned int GetBytesToReadOfWriteCMD(unsigned int CurrentUseIO, unsigned int BaseLength);
	/**
	 * @brief Get MFR_ID.
	 */
	static wxString& getDefaultMFR_ID(void);
	/**
	 * @brief Get MFR_MODEL.
	 */
	static wxString& getDefaultMFR_MODEL(void);
	/**
	 * @brief Get MFR_REVISION.
	 */
	static wxString& getDefaultMFR_REVISION(void);
	/**
	 * @brief Get MFR_LOCATION.
	 */
	static wxString& getDefaultMFR_LOCATION(void);
	/**
	 * @brief Get MFR_DATE.
	 */
	static wxString& getDefaultMFR_DATE(void);
	/**
	 * @brief Get MFR_SERIAL.
	 */
	static wxString& getDefaultMFR_SERIAL(void);
	/**
	 * @brief Parse Customized Read CMD Recive Data.
	 */
	static void ParseCustomizedReadCMDRecvData(unsigned char cmd, unsigned char* DataBuff, unsigned int DataLengh);
	/**
	 * @brief Get Index of CMD-Field in Send Buffer By Giving Current I/O.
	 */
	static unsigned int getIndexOfCMDFieldInSendBuffer(unsigned int* currentUseIO);
	/**
	 * @brief Get Send Vector Critical Section Object.
	 */
	static wxCriticalSection* getSendVectorCriticalSectionObject(void);
        /**
         * @brief Get GetTickCount.
         */
        static unsigned long GetTickCount(void);

protected :

private :
	static unsigned char m_slaveAddress;

	static PMBUSSTATUS_t m_pmbusStatus;

	static AppSettings_t* m_appSettings;

	static int TotalPhaseWriteReadLastError;

	static USBINFO m_USBInfo;

	static wxString m_timeString;

	static wxString m_winTitleBase;

	static PMBUSCOMMAND_t *m_PMBusCMDData;

	static unsigned char m_FWUploadModeCMD;/**< FW Upload Mode Command */

	static unsigned char m_FWUploadCMD;/**< FW Upload Command */

	static unsigned char m_FWUploadStatusCMD;/**< FW Upload Status Command */

	static wxString m_default_mfr_id;

	static wxString m_default_mfr_model;

	static wxString m_default_mfr_revision;

	static wxString m_default_mfr_location;

	static wxString m_default_mfr_date;

	static wxString m_default_mfr_serial;

	static wxCriticalSection m_SendVectorCritsect;

};

#endif
