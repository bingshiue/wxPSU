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

	static void ProductReadCMDBuffer(PMBUSCOMMAND_t* pmBusCommand, unsigned char* sendBuffer,unsigned int* currentIO,unsigned int idx, unsigned int command, unsigned int responseDataLength);
	static int ProductWriteCMDBuffer(unsigned int *currentIO, unsigned char *buff, unsigned int sizeOfBuffer, unsigned char cmd, unsigned char *dataBuffer, unsigned int sizeOfDataBuffer);

	static void ProductDataBuffer(PMBUSCOMMAND_t* pmBusCommand, unsigned int* currentIO, unsigned int cmdIndex, unsigned int responseDataLength);

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

	static void setWinTitleBase(wxString base);

	static wxString& getWinTitleBase(void);

	static unsigned int& getCurrentISPTarget(void);

	static unsigned int IsI2CBusNotAcknowlwdge(unsigned int *currentIO, unsigned char *buffer, unsigned int SizeOfBuffer);

	static bool isOwnReadAccess(unsigned int access);

	static void setPMBUSCMDData(PMBUSCOMMAND_t *PMBusCMDData);

	static PMBUSCOMMAND_t* getPMBUSCMDData(void);

	static int getIndexOfCMD(int cmd, int page = 0);

protected :

private :
	static unsigned char m_slaveAddress;

	static PMBUSSTATUS_t m_pmbusStatus;

	static AppSettings_t* m_appSettings;

	static USBINFO m_USBInfo;

	static wxString m_timeString;

	static wxString m_winTitleBase;

	static PMBUSCOMMAND_t *m_PMBusCMDData;

};

#endif