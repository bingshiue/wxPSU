/**
 * @file AppSettings.h
 */
#ifndef _APPSETTINGS_H_
#define _APPSETTINGS_H_

enum RUNMODE {
	RunMode_Iterations = 0,
	RunMode_Continually,
	RunMode_StopAnError
};

#define DEFAULT_I2C_SLAVEADDRESS  0xb6
#define DEFAULT_ITERATIONS_VALUE  10000

typedef struct appSettings_t {
	unsigned char m_I2CSlaveAddress;/**< I2C Slave Address */
	unsigned int m_runMode;/**< Run Mode */
	unsigned int m_IterationsSettingValue;/**< Iteration Setting Value */

	void Reset(void){
		this->m_I2CSlaveAddress = DEFAULT_I2C_SLAVEADDRESS;
		this->m_runMode = RunMode_Continually;	
		this->m_IterationsSettingValue = DEFAULT_ITERATIONS_VALUE;
	}

} AppSettings_t;

#endif