/**
 * @file PBF003_00G_CBRaw.h
 */
#ifndef _PBF003_00G_CBRAW_H_
#define _PBF003_00G_CBRAW_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "PEC.h"

// Declare Raw CB Functions
int PFB003_00G_Raw_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);
int PFB003_00G_Raw_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);



#endif /* _PBF003_00G_CBRAW_H_ */
