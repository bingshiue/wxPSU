/**
 * @file Customers.h
 */
#ifndef _CUSTOMERS_H_
#define _CUSTOMERS_H_

#include "Preprocessor.h"

enum {
	Customer_NEC = 0,

#if (HAVE_GENERIC_CUSTOMER == TRUE)
	Customer_Generic,
#endif

	Customer_LIST_Size
};

#define CUSTOMER_LIST_SIZE  (Customer_LIST_Size)

#define NEC_CUSTOMER_NAME      L"NEC"
#define GENERIC_CUSTOMER_NAME  L"GENERIC"

#endif