/**
 * @file PBF003_00G_CBCoefficients.h
 */

#ifndef _PBF003_00G_CBCOEFFICIENTS_H_
#define _PBF003_00G_CBCOEFFICIENTS_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "PEC.h"

// Declare Coefficients CB Functions
int PFB003_00G_Coefficients_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Coefficients_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

#endif /* _PBF003_00G_CBCOEFFICIENTS_H_ */
