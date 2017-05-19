/**
 * @file GIGABYTE_CRPS001_CBQuery.cpp
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "GIGABYTE_CRPS001_CBQuery.h"

int GB_CRPS_Query_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

int GB_CRPS_Query_00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_02H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_03H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_04H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_07H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_08H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_09H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_0aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_0bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_0cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_0dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_0eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_0fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_10H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_11H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_12H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_13H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_14H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_15H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_16H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_17H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_18H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_1bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_1cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_1dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_1eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_1fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_20H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_21H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_22H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_23H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_24H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_25H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_26H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_27H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_28H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_29H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_2AH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_2BH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_2CH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_2DH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_2EH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_2FH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_32H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_33H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_34H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_35H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_36H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_37H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_38H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_39H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_3aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_3bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_3cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_3dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_3eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_3fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_40H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_41H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_42H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_43H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_44H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_45H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_46H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_47H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_48H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_49H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_4bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_4cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_4dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_4eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_4fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_50H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_51H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_52H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_53H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_54H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_55H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_56H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_57H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_58H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_59H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_5aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_5bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_5cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_5dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_5eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_5fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_60H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_61H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_62H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_63H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_64H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_65H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_66H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_67H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_68H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_69H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_6aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_6bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_6cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_6dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_6eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_6fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_71H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_72H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_73H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_74H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_75H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_76H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_77H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_78H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_79H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_7aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_7bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_7cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_7dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_7eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_7fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_80H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_81H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_82H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_83H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_84H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_85H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_86H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_87H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_88H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_89H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8b00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8c00H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8b01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8c01H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_8fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_90H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_92H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_93H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_94H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_95H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_96H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_97H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_98H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_99H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_9aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_9bH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_9cH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_9dH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_9eH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_9fH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_a0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_a9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_aaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_abH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_acH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_adH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_aeH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_afH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_b0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_b9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_baH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_bbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_bcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_bdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_beH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_bfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_c0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_c9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_caH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_cbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_ccH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_cdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_ceH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_cfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_d0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_d9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_daH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_dbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_dcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_ddH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_deH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_dfH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_e0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_e9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_eaH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_ebH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_ecH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_edH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_eeH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_efH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_f0H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f1H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f2H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f3H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f4H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f5H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f6H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f7H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f8H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_f9H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_faH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_fbH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_fcH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_fdH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_feH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_ffH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }

int GB_CRPS_Query_05H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_06H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_19H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_1aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_30H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_31H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_4aH(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_70H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }
int GB_CRPS_Query_91H(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){ return GB_CRPS_Query_Common(pmbuscmd, string, sizeOfstr); }


#define CMD_SUPPORT_MASK         (0x80)
#define CMD_ACCSSS_WRITE_MASK    (0x40)
#define CMD_ACCSSS_READ_MASK     (0x20)
#define CMD_ACCSSS_FORMAT_MASK   (0x1C)
#define CMD_ACCSSS_RESERVED_MASK (0x03)
int GB_CRPS_Query_Common(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr){

	// Bits     Value                 Meaning
	//  7         1           Command is supported
	//	          0           Command is not supported
	//  6         1           Command is supported for write
	//            0           Command is not supported for write
	//  5         1           Command is supported for read
	//	          0           Command is not supported for read
	// 4:2       000          Linear Data Format used
	//           001          16 bit signed number
	//           010          Reserved
	//           011          Direct Mode Format used
	//           100          8 bit unsigned number
	//           101          VID Mode Format used
	//           110          Manufacturer specific format used
	//           111          Command does not return numeric data.This is also used for commands that return blocks of data.
	// 1:0       XXX          Reserved for future use
	unsigned char support = 0;
	unsigned char write = 0;
	unsigned char read = 0;
	unsigned char format = 0;

	const wchar_t* tmp_wchar;

	wxString wxstr("");

	// Support
	if (!(pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_SUPPORT_MASK)){

		support = cmd_unsupport;

		wxstr += wxString::Format("Unsupport");

		tmp_wchar = wxstr.wc_str();
		COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

		PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());

		return EXIT_SUCCESS;
	}
	else{
		support = cmd_support;
	}

	// Write 
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_READ_MASK){
		wxstr += wxString::Format("R");
	}
	else{
		wxstr += wxString::Format("");
	}

	// for "/"
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_READ_MASK){
		if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_WRITE_MASK){
			wxstr += wxString::Format("/");
		}
	}

	// Read 
	if (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_WRITE_MASK){
		wxstr += wxString::Format("W");
	}
	else{
		wxstr += wxString::Format("");
	}

	wxstr += wxString::Format(",");

	// Data Format
	/* Update Data Format in CMD */
	PSU_DEBUG_PRINT(MSG_DEBUG, "Start Update Data Format in CMD");
	// Get Query CMD
	int queryCMD;
	queryCMD = pmbuscmd->m_cmdStatus.m_AddtionalData[1];

	// Get Index of Query CMD 
	int queryCMDIndex = -1;
	                                                     // CMD's Page
	queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, sizeOfstr);

#if 0
	for (int idx = 0; idx < (signed)PMBUSHelper::CurrentCMDTableSize; idx++){
		if (PMBUSHelper::getPMBUSCMDData()[idx].m_register == queryCMD){
			queryCMDIndex = idx;
			break;
		}
	}
#endif

	if (queryCMDIndex < 0){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD, queryCMD=%02xH, CMD's page=%d", queryCMD, sizeOfstr);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "queryCMDIndex = %d", queryCMDIndex);
	}

	// Set Direct Data Fomat Coefficient
	pmbuscmd_t* target;
	target = PMBUSHelper::getPMBUSCMDData();

	// Update support field
	target[queryCMDIndex].m_cmdStatus.m_support = support;

	PSU_DEBUG_PRINT(MSG_DEBUG, "format=%02x", (pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_FORMAT_MASK) >> 2);
	switch ((pmbuscmd->m_recvBuff.m_dataBuff[1] & CMD_ACCSSS_FORMAT_MASK) >> 2){

	case 0:
		wxstr += wxString::Format("Linear");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_LinearData_Format;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 1:
		wxstr += wxString::Format("16 bit signed");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_16bit_Signed_Number;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 2:
		wxstr += wxString::Format("Reserved");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_Reserved;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 3:
		wxstr += wxString::Format("Direct");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_DirectData_Format;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 4:
		wxstr += wxString::Format("8 bit unsigned");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_8bit_Unsigned_Number;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 5:
		wxstr += wxString::Format("VID Mode");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_VID_Mode;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 6:
		wxstr += wxString::Format("Manufacturer specific format");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_Manufacturer_Specific;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	case 7:
		wxstr += wxString::Format("Block or None");
		target[queryCMDIndex].m_dataFormat.m_formatType = cmd_data_format_Don_t_Return_Numeric_Data;
		PSU_DEBUG_PRINT(MSG_DEBUG, "Data Format=%d", target[queryCMDIndex].m_dataFormat.m_formatType);
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
		break;
	}

	PSU_DEBUG_PRINT(MSG_DEBUG, "End Update Data Format in CMD");

	tmp_wchar = wxstr.wc_str();
	COPY_WIDE_CHARACTERS(string, tmp_wchar, 256);

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", wxstr.c_str());


#if 0
	const wchar_t* tmp_wchar;
	unsigned char tmp_buffer[256];

	PSU_DEBUG_PRINT(MSG_DEBUG, "GB_CRPS_Query_Common");

	wxString wxstr("");

	tmp_wchar = wxstr.wc_str();
	
	lstrcpyn(string, tmp_wchar, 256);
#endif

	return EXIT_SUCCESS;
}
