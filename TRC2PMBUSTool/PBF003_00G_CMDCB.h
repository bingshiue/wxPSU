/**
 * @file PBF003_00G_CMDCB.h
 */
#ifndef _PBF003_00G_CMDCB_H_
#define _PBF003_00G_CMDCB_H_

#include "PBF003_00G_CBQuery.h"
#include "PBF003_00G_CBCoefficients.h"
#include "PBF003_00G_CBCook.h"
#include "PBF003_00G_CBRaw.h"
#include "PBF003_00G.h"

CMDQueryCBFunc g_PBF003_00G_CMDQueryCBFunc[PBF003_00G_CMD_TABLE_SIZE] = {
	PFB003_00G_Query_0900H,
	PFB003_00G_Query_0902H,
	PFB003_00G_Query_0904H,
	PFB003_00G_Query_0905H,
	PFB003_00G_Query_0906H,
	PFB003_00G_Query_0907H,
	PFB003_00G_Query_0908H,
	PFB003_00G_Query_0909H,
	PFB003_00G_Query_0910H,
	PFB003_00G_Query_0920H,
	PFB003_00G_Query_0921H,
	PFB003_00G_Query_0999H,

};

CMDCoefficientsCBFunc g_PBF003_00G_CMDCoefficientsCBFunc[PBF003_00G_CMD_TABLE_SIZE] = {
	PFB003_00G_Coefficients_0900H,
	PFB003_00G_Coefficients_0902H,
	PFB003_00G_Coefficients_0904H,
	PFB003_00G_Coefficients_0905H,
	PFB003_00G_Coefficients_0906H,
	PFB003_00G_Coefficients_0907H,
	PFB003_00G_Coefficients_0908H,
	PFB003_00G_Coefficients_0909H,
	PFB003_00G_Coefficients_0910H,
	PFB003_00G_Coefficients_0920H,
	PFB003_00G_Coefficients_0921H,
	PFB003_00G_Coefficients_0999H,

};

CMDCookCBFunc g_PBF003_00G_CMDCookCBFunc[PBF003_00G_CMD_TABLE_SIZE] = {
	PFB003_00G_Cook_0900H,
	PFB003_00G_Cook_0902H,
	PFB003_00G_Cook_0904H,
	PFB003_00G_Cook_0905H,
	PFB003_00G_Cook_0906H,
	PFB003_00G_Cook_0907H,
	PFB003_00G_Cook_0908H,
	PFB003_00G_Cook_0909H,
	PFB003_00G_Cook_0910H,
	PFB003_00G_Cook_0920H,
	PFB003_00G_Cook_0921H,
	PFB003_00G_Cook_0999H,

};

CMDRawCBFunc g_PBF003_00G_CMDRawCBFunc[PBF003_00G_CMD_TABLE_SIZE] = {
	PFB003_00G_Raw_0900H,
	PFB003_00G_Raw_0902H,
	PFB003_00G_Raw_0904H,
	PFB003_00G_Raw_0905H,
	PFB003_00G_Raw_0906H,
	PFB003_00G_Raw_0907H,
	PFB003_00G_Raw_0908H,
	PFB003_00G_Raw_0909H,
	PFB003_00G_Raw_0910H,
	PFB003_00G_Raw_0920H,
	PFB003_00G_Raw_0921H,
	PFB003_00G_Raw_0999H,
};


#endif