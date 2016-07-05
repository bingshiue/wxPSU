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
#include "AppSettings.h"

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

	static void SetSlaveAddress(unsigned char slaveAddress);
	static unsigned char& GetSlaveAddress(void);
	static PMBUSSTATUS_t* GetPMBusStatus(void);

	static void SetAppSettings(AppSettings_t* appSettings);
	static AppSettings_t* GetAppSettings(void);

	static double ParseLinearDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer);
	static int ProductFakeLinearData(unsigned char *dest, double value, double scale);
	static int ProductLinearData(unsigned char *dest, double value, double scale);

	static int ProductWriteCMDBuffer(unsigned int *currentIO, unsigned char *buff, unsigned int sizeOfBuffer, unsigned char cmd, unsigned char *dataBuffer, unsigned int sizeOfDataBuffer);

	static long HexToDecimal(wxString string);

	static void GetNowDateTimeString(wxString& string);

	static unsigned char IsResponseOK(unsigned char *buffer, unsigned int sizeOfBuffer);
	static unsigned char ComputeISPDataCheckSum(unsigned char *buffer, unsigned int dataStartIndex, unsigned int dataEndIndex);

protected :

private :
	static unsigned char m_slaveAddress;

	static PMBUSSTATUS_t m_pmbusStatus;

	static AppSettings_t* m_appSettings;
};

#endif