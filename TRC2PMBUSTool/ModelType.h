/**
 * @file ModelType.h
 */
#ifndef _MODELTYPE_H_
#define _MODELTYPE_H_

#include "PMBUSCommandType.h"

#define STANDARD_PMBUS_MODEL  true/**< Standard PMBUS Model */
#define NON_STANDARD_PMBUS_MODEL  false/**< Non-Standard PMBUS Model */

typedef struct model_option_t {

	unsigned int m_default_i2c_address;/**< Default I2C Address */
	unsigned int m_default_cmd_polling_time;/**< Default CMD Polling Time */
	bool         m_isp_support;/**< ISP Support */

	model_option_t() {
		m_default_i2c_address = 0x00;
		m_default_cmd_polling_time = 0x00;
		m_isp_support = false;
	}

	model_option_t(unsigned int default_i2c_address, unsigned int default_cmd_polling_time, bool isp_support) {
		m_default_i2c_address = default_i2c_address;
		m_default_cmd_polling_time = default_cmd_polling_time;
		m_isp_support = isp_support;
	}

} MODEL_OPTION_t;

typedef struct model_type_t {
	
	wchar_t* m_modelName;/**< Model Name */
	PMBUSCOMMAND_t* m_modelCMDTable;/**< Model CMD Table */
	unsigned int m_modelCMDTableSize;/**< Model CMD Table Size */
	CMDQueryCBFunc* m_cmdQueryCBFunc;/**< CMD Query Function */
	CMDCoefficientsCBFunc* m_cmdCoefficientsFunc;/**< CMD Coefficients Function */
	CMDCookCBFunc* m_cmdCookCBFunc;/**< CMD Cook Function */
	CMDRawCBFunc* m_cmdRawCBFunc;/**< CMD Raw Function */
	PMBUSCMDBufferProvider_t  m_pmbusCMDbufferProvider;/**< PMBUS CMD Buffer Provider */
	bool m_isStandardPMBUSModel;/**< Is Standard PMBUS Model */
	MODEL_OPTION_t m_modelOption;/**< Model Option */

} MODEL_TYPE_t;

#endif
