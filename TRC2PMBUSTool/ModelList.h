/**
 * @file ModelList.h
 */
#ifndef _MODELLIST_H_
#define _MODELLIST_H_

#include "Models.h"
#include "ModelType.h"

// GIGABYTE CRPS 001
#include "GIGABYTE_CRPS001.h"
#include "GIGABYTE_CRPS001_CMDCB.h"

#include "GIGABYTE_CRPS_ALL_PMBUS_CMDS.h"
#include "GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDCB.h"

// ACBEL RFWE_24_28_1200W_SCP
#include "ACBEL_RFWE_24_28_1200W_SCP.h"
#include "ACBEL_RFWE_24_28_1200W_SCP_CMDCB.h"

// FSG003-000G
#include "FSG003_000G.h"
#include "FSG003_000G_CMDCB.h"

// PBF003-00G
#include "PBF003_00G.h"
#include "PBF003_00G_CMDCB.h"

// Generic Model (For Test Purpose)
#include "Generic_Model.h"
#include "Generic_CMDCB.h"

MODEL_TYPE_t g_GIGABYTEModelList[GIGABYTE_MODEL_LIST_SIZE] = {
	// [0]  GIGABYTE CRPS 001
	{
		GIGABYTE_CRPS001_MODEL_NAME,
		g_GIGABYTE_CRPS001_CMDTable,
		GIGABYTE_CRPS001_CMD_TABLE_SIZE,
		g_GIGABYTE_CRPS001_CMDQueryCBFunc,
		g_GIGABYTE_CRPS001_CMDCoefficientsCBFunc,
		g_GIGABYTE_CRPS001_CMDCookCBFunc,
		g_GIGABYTE_CRPS001_CMDRawCBFunc
	}

	// [1]  GIGABYTE CRPS ALL PMBUS COMMANDS
	,{
		GIGABYTE_CRPS_ALL_PMBUS_CMDS_MODEL_NAME,
		g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDTable,
		GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMD_TABLE_SIZE,
		g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDQueryCBFunc,
		g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDCoefficientsCBFunc,
		g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDCookCBFunc,
		g_GIGABYTE_CRPS_ALL_PMBUS_CMDS_CMDRawCBFunc
	}

#if (HAVE_GENERIC_MODEL == TRUE)
	// [2] Generic Model (For Test Purpose)
	, {
		GENERIC_MODEL_NAME,
		g_Generic_CMDTable,
		GENERIC_CMD_TABLE_SIZE,
		g_Generic_CMDQueryCBFunc,
		g_Generic_CMDCoefficientsCBFunc,
		g_Generic_CMDCookCBFunc,
		g_Generic_CMDRawCBFunc
	}
#endif
};


MODEL_TYPE_t g_ACBELModelList[ACBEL_MODEL_LIST_SIZE] = {
	// [0] RFWE_24_28_1200W_SCP
	{
		ACBEL_RFWE_24_28_1200W_SCP_MODEL_NAME,
		g_ACBEL_RFWE_24_28_1200W_SCP_CMDTable,
		ACBEL_RFWE_24_28_1200W_SCP_CMD_TABLE_SIZE,
		g_ACBEL_RFWE_24_28_1200W_SCP_CMDQueryCBFunc,
		g_ACBEL_RFWE_24_28_1200W_SCP_CMDCoefficientsCBFunc,
		g_ACBEL_RFWE_24_28_1200W_SCP_CMDCookCBFunc,
		g_ACBEL_RFWE_24_28_1200W_SCP_CMDRawCBFunc
	}


	// [1] PBF003-00G
	,{
		PBF003_00G_MODEL_NAME,
		g_PBF003_00G_CMDTable,
		PBF003_00G_CMD_TABLE_SIZE,
		g_PBF003_00G_CMDQueryCBFunc,
		g_PBF003_00G_CMDCoefficientsCBFunc,
		g_PBF003_00G_CMDCookCBFunc,
		g_PBF003_00G_CMDRawCBFunc
	}

#if (HAVE_GENERIC_MODEL == TRUE)
	// [2] Generic Model (For Test Purpose)
	, {
		GENERIC_MODEL_NAME,
		g_Generic_CMDTable,
		GENERIC_CMD_TABLE_SIZE,
		g_Generic_CMDQueryCBFunc,
		g_Generic_CMDCoefficientsCBFunc,
		g_Generic_CMDCookCBFunc,
		g_Generic_CMDRawCBFunc
	}
#endif
};


MODEL_TYPE_t g_NECModelList[NEC_MODEL_LIST_SIZE] = {
	// [0]  FSG003-000G
	{
		FSG003_000G_MODEL_NAME,
		g_FSG003_000G_CMDTable,
		FSG003_000G_CMD_TABLE_SIZE,
		g_FSG003_000G_CMDQueryCBFunc,
		g_FSG003_000G_CMDCoefficientsCBFunc,
		g_FSG003_000G_CMDCookCBFunc,
		g_FSG003_000G_CMDRawCBFunc
	}
#if (HAVE_GENERIC_MODEL == TRUE)
	// [1] Generic Model (For Test Purpose)
	,{
		GENERIC_MODEL_NAME,
		g_Generic_CMDTable,
		GENERIC_CMD_TABLE_SIZE,
		g_Generic_CMDQueryCBFunc,
		g_Generic_CMDCoefficientsCBFunc,
		g_Generic_CMDCookCBFunc,
		g_Generic_CMDRawCBFunc
	}
#endif
};

MODEL_TYPE_t g_GENERICModelList[GENERIC_MODEL_LIST_SIZE] = {
	// [0] Generic Model (For Test Purpose)
	{
		GENERIC_MODEL_NAME,
		g_Generic_CMDTable,
		GENERIC_CMD_TABLE_SIZE,
		g_Generic_CMDQueryCBFunc,
		g_Generic_CMDCoefficientsCBFunc,
		g_Generic_CMDCookCBFunc,
		g_Generic_CMDRawCBFunc
	}
};

#endif
