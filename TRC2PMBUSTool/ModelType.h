/**
 * @file ModelType.h
 */
#ifndef _MODELTYPE_H_
#define _MODELTYPE_H_

#include "PMBUSCommandType.h"

#define STANDARD_PMBUS_MODEL  true/**< Standard PMBUS Model */
#define NON_STANDARD_PMBUS_MODEL  false/**< Non-Standard PMBUS Model */

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

} MODEL_TYPE_t;

#endif
