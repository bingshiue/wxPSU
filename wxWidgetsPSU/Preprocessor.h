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

// Auto Query All Commands When I/O Open
#define AUTO_QUERY_ALL_CMDS_WHEN_IO_OPEN   (TRUE)

#endif