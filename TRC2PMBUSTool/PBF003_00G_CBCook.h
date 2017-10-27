/**
 * @file PBF003_00G_CBCook.h
 */
#ifndef _PBF003_00G_CBCOOK_H_
#define _PBF003_00G_CBCOOK_H_

#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"

// Declare Cook CB Functions
int PFB003_00G_Cook_0900H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0902H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0904H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0905H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0906H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0907H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0908H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0909H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0910H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0920H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0921H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0922H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0923H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);
int PFB003_00G_Cook_0999H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);


#endif /* _PBF003_00G_CBCOOK_H_ */
