/**
 * @file AppSettings.h
 */
#ifndef _APPSETTINGS_H_
#define _APPSETTINGS_H_

#include <Windows.h>
#include <wx/wx.h>

enum {
	RunMode_Iterations = 0,
	RunMode_Continually,
	RunMode_StopAnError
};

enum {
	Log_Mode_Log_ALL = 0,
	Log_Mode_Log_Error_Only
};

enum {
	Generic_Disable = 0,
	Generic_Enable
};

enum {
	PMBUS_ReadMethod_1_1 = 0,
	PMBUS_ReadMethod_1_2
};

enum {
	I2C_AdaptorModuleBoard_API2CS12_000= 0,
	I2C_AdaptorModuleBoard_R90000_95611,
	I2C_AdaptorModuleBoard_R90000_9271_USB,
	I2C_AdaptorModuleBoard_TOTALPHASE,
};

#define DEFAULT_I2C_ADAPTOR_MODULE  (unsigned long)I2C_AdaptorModuleBoard_R90000_95611
#define DEFAULT_I2C_SLAVEADDRESS    0xb6
#define DEFAULT_RUN_MODE            (unsigned long)(RunMode_Continually)//0x01 //RunMode_Continually
#define DEFAULT_ITERATIONS_VALUE    10000
#define DEFAULT_ENABLE_CHECKSUM     (unsigned long)Generic_Enable

#define DEFAULT_LOG_MODE            (unsigned long)Log_Mode_Log_ALL
#define DEFAULT_LOG_TO_FILE         (unsigned long)Generic_Disable
#define DEFAULT_LOG_FILE_PATH       ""

#define DEFAULT_PMBUS_READ_METHOD     (unsigned long)PMBUS_ReadMethod_1_1

#define DEFAULT_COMPORT_NUM           0x01
#define DEFAULT_COMPORT_BUADRATE      CBR_9600
#define DEFAULT_COMPORT_BYTESIZE      8
#define DEFAULT_COMPORT_STOPBITS      ONESTOPBIT
#define DEFAULT_COMPORT_PARITYCHECK   NOPARITY

typedef struct comport_setting {
	unsigned long m_comportNumber;
	unsigned long m_buadRate;
	unsigned long m_byteSize;
	unsigned long m_stopBits;
	unsigned long m_parityCheck;

	void Reset(void){
		m_comportNumber = DEFAULT_COMPORT_NUM;
		m_buadRate      = DEFAULT_COMPORT_BUADRATE;
		m_byteSize      = DEFAULT_COMPORT_BYTESIZE;
		m_stopBits      = DEFAULT_COMPORT_STOPBITS;
		m_parityCheck   = DEFAULT_COMPORT_PARITYCHECK;
	}


} COMPORT_SETTING_t;

typedef struct appSettings_t {
	COMPORT_SETTING_t m_comportSetting;
	
	unsigned long m_I2CAdaptorModuleBoard;/**< I2C Adaptor Module Board */
	unsigned long m_I2CSlaveAddress;/**< I2C Slave Address */
	unsigned long m_runMode;/**< Run Mode */
	unsigned long m_IterationsValue;/**< Iteration Value */
	unsigned long m_EnableChecksum;/**< Enable Checksum */
	unsigned long m_logMode;/**< Log Mode */
	unsigned long m_logToFile;/**< Log To File */
	     wxString m_logFilePath;/**< Log File Path */
	unsigned long m_pmbusReadMethod;/**< PM Bus Read Method */

	/* ----- Developer Setting ----- */
	unsigned long m_developerMode;/**< Developer Mode */

	void Reset(void){
		this->m_comportSetting.Reset();

		this->m_I2CAdaptorModuleBoard = DEFAULT_I2C_ADAPTOR_MODULE;
		this->m_I2CSlaveAddress = DEFAULT_I2C_SLAVEADDRESS;
		this->m_runMode = DEFAULT_RUN_MODE;
		this->m_IterationsValue = DEFAULT_ITERATIONS_VALUE;
		this->m_EnableChecksum = Generic_Enable;
		this->m_logMode = DEFAULT_LOG_MODE;/**< Log Mode */
		this->m_logToFile = DEFAULT_LOG_TO_FILE;/**< Log To File */
		this->m_logFilePath = wxString::Format("%s", DEFAULT_LOG_FILE_PATH);
		this->m_pmbusReadMethod = DEFAULT_PMBUS_READ_METHOD;

		this->m_developerMode = Generic_Disable;
	}

} AppSettings_t;

#endif