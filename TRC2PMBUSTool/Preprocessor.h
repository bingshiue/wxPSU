/**
 * @file Preprocessor.h
 * @brief Define Preprocessor for wxWidgets PSU
 */
#ifndef _PREPROCESSOR_H_
#define _PREPROCESSOR_H_

// Customer
#define HAVE_GENERIC_CUSTOMER              (TRUE)//(FALSE)

// Model
#define HAVE_GENERIC_MODEL                 (TRUE)//(FALSE)

// Increase CPU Overhead When Do ISP
#define INCREASE_CPU_OVERHEAD              (TRUE)//(FALSE)

// Write Pages Input Parameter Default Format (Decimal or Hex)
#define WRITE_PAGES_DEFAULT_FORMAT_HEX     (TRUE)//(FALSE)

// Read Pages Input Parameter Default Format (Decimal or Hex)
#define READ_PAGES_DEFAULT_FORMAT_HEX      (TRUE)//(FALSE)

// Don't Enable ISP Function (Disable Administratot Menu Item)
#define DEFAULT_DONT_ENABLE_ISP            (FALSE)

// Only Enable ISP Run In Test in ISP Develop Mode
#define ONLY_ENABLE_ISP_RUNIN_TEST_IN_DEVELOP_MODE  (FALSE)

#endif