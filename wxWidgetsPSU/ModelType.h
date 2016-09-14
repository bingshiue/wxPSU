/**
 * @file ModelType.h
 */
#ifndef _MODELTYPE_H_
#define _MODELTYPE_H_

#include "PMBUSCommandType.h"

enum {
	Model_FSG003_000G = 0,
	Model_Generic,
	Model_LIST_Size
};

#define DEFAULT_MODEL (unsigned long)Model_FSG003_000G

#define MODEL_LIST_SIZE  (Model_LIST_Size)

typedef struct model_type_t {
	
	wchar_t* m_modelName;/**< Model Name */
	PMBUSCOMMAND_t* m_modelCMDTable;/**< Model CMD Table */
	unsigned int m_modelCMDTableSize;/**< Model CMD Table Size */
	CMDQueryCBFunc* m_cmdQueryCBFunc;/**< CMD Query Function */
	CMDCookCBFunc* m_cmdCookCBFunc;/**< CMD Cook Function */
	CMDRawCBFunc* m_cmdRawCBFunc;/**< CMD Raw Function */

} MODEL_TYPE_t;

#endif