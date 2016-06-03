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

#define DEFAULT_ITERATIONS_VALUE  10000

typedef struct appSettings_t {

	unsigned int m_runMode;/**< Run Mode */
	unsigned int m_IterationsSettingValue;/**< Iteration Setting Value */

	void Reset(void){
		this->m_runMode = RunMode_Continually;	
		this->m_IterationsSettingValue = DEFAULT_ITERATIONS_VALUE;
	}

} AppSettings_t;

#endif