/**
 * @file CustomerType.h
 */
#ifndef _CUSTOMERTYPE_H_
#define _CUSTOMERTYPE_H_

#include "ModelType.h"

typedef struct customer_type_t {

	wchar_t* m_customerName;/**< Customer Name */

	MODEL_TYPE_t* m_modelTypeList;/**< Model Type List */

	unsigned int m_modelTypeListSize;/**< Model Type List Size */

}CUSTOMER_TYPE_t;


#endif