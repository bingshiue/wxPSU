/**
 * @file CustomerList.h
 */
#ifndef _CUSTOMERLIST_H_
#define _CUSTOMERLIST_H_

#include "CustomerType.h"
#include "Customers.h"
#include "Models.h"
#include "ModelType.h"
#include "ModelList.h"

CUSTOMER_TYPE_t g_CustomerList[CUSTOMER_LIST_SIZE] = {
	
	{
		GIGABYTE_CUSTOMER_NAME,
		g_GIGABYTEModelList,
		GIGABYTE_MODEL_LIST_SIZE
	}
	
#if 0
	,{
		NEC_CUSTOMER_NAME,
		g_NECModelList,
		NEC_MODEL_LIST_SIZE
	}
#endif

#if (HAVE_GENERIC_CUSTOMER == TRUE)
	,{
		GENERIC_CUSTOMER_NAME,
		g_GENERICModelList,
		GENERIC_MODEL_LIST_SIZE
	}
#endif

};

#endif