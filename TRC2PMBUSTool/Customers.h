/**
 * @file Customers.h
 */
#ifndef _CUSTOMERS_H_
#define _CUSTOMERS_H_

#include "Preprocessor.h"

enum {
	
	Customer_GIGABYTE = 0,

#if 0
	Customer_NEC,
#endif

#if (HAVE_GENERIC_CUSTOMER == TRUE)
	Customer_Generic,
#endif

	Customer_LIST_Size
};

#define CUSTOMER_LIST_SIZE  (Customer_LIST_Size)

#define GIGABYTE_CUSTOMER_NAME L"GIGABYTE"
#define NEC_CUSTOMER_NAME      L"NEC"
#define GENERIC_CUSTOMER_NAME  L"GENERIC"

#endif