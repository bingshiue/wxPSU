/**
 * @file AppSettings.h
 */
#ifndef _APPSETTINGS_H_
#define _APPSETTINGS_H_

#include <Windows.h>

enum {
	RunMode_Iterations = 0,
	RunMode_Continually,
	RunMode_StopAnError
};

#define DEFAULT_I2C_SLAVEADDRESS  0xb6
#define DEFAULT_RUN_MODE          (unsigned long)(RunMode_Continually)//0x01 //RunMode_Continually
#define DEFAULT_ITERATIONS_VALUE  10000

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
	
	unsigned long m_I2CSlaveAddress;/**< I2C Slave Address */
	unsigned long m_runMode;/**< Run Mode */
	unsigned long m_IterationsValue;/**< Iteration Value */

	void Reset(void){
		this->m_comportSetting.Reset();

		this->m_I2CSlaveAddress = DEFAULT_I2C_SLAVEADDRESS;
		this->m_runMode = DEFAULT_RUN_MODE;
		this->m_IterationsValue = DEFAULT_ITERATIONS_VALUE;
	}

} AppSettings_t;

#endif