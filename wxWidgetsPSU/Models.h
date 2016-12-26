/**
 * @file Models.h
 */
#ifndef _MODELS_H_
#define _MODELS_H_

#include "Preprocessor.h"

// GIGABYTE Models
enum GIGABYTE_MODEL {
	GIGABYTE_Model_CRPS001 = 0,

	GIGABYTE_Model_CRPS001_ALL_PMBUS_COMMANDS,

#if (HAVE_GENERIC_MODEL == TRUE)
	GIGABYTE_Model_Generic,
#endif

	GIGABYTE_Model_LIST_Size
};
#define GIGABYTE_MODEL_LIST_SIZE  (GIGABYTE_Model_LIST_Size)

// NEC Models
enum NEC_MODEL {
	NEC_Model_FSG003_000G = 0,

#if (HAVE_GENERIC_MODEL == TRUE)
	NEC_Model_Generic,
#endif
	
	NEC_Model_LIST_Size
};
#define NEC_MODEL_LIST_SIZE  (NEC_Model_LIST_Size)

// Generic Models
enum GENERIC_MODEL {
	GENERIC_Model_Generic = 0,
	GENERIC_Model_LIST_Size
};
#define GENERIC_MODEL_LIST_SIZE  (GENERIC_Model_LIST_Size)

#endif