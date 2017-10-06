/**
 * @file PBF003_00G_CBQuery.h
 */

#ifndef _PBF003_00G_CBQUERY_H_
#define _PBF003_00G_CBQUERY_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "PEC.h"

// Declare Query CB Functions
int PFB003_00G_Query_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Query_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);


#endif /* _PBF003_00G_CBQUERY_H_ */
