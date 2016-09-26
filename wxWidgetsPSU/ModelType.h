/**
 * @file ModelType.h
 */
#ifndef _MODELTYPE_H_
#define _MODELTYPE_H_

#include "PMBUSCommandType.h"

typedef struct model_type_t {
	
	wchar_t* m_modelName;/**< Model Name */
	PMBUSCOMMAND_t* m_modelCMDTable;/**< Model CMD Table */
	unsigned int m_modelCMDTableSize;/**< Model CMD Table Size */
	CMDQueryCBFunc* m_cmdQueryCBFunc;/**< CMD Query Function */
	CMDCookCBFunc* m_cmdCookCBFunc;/**< CMD Cook Function */
	CMDRawCBFunc* m_cmdRawCBFunc;/**< CMD Raw Function */

} MODEL_TYPE_t;

#endif