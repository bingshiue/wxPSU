/**
 * @file PMBUSStatusPanel.h
 */
#ifndef _PMBUSSTATUSPANEL_H_
#define _PMBUSSTATUSPANEL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>
#include <wx/artprov.h>
#include <wx/colordlg.h>
#include <wx/wfstream.h>
#include <wx/animate.h>
#include <wx/statline.h>

class PMBUSStatusPanel : public wxScrolledWindow {
public:
	/**
	 * @brief Constructor.
	 */
	PMBUSStatusPanel(wxWindow* parent);
	/**
	 * @brief Deconstructor.
	 */
	~PMBUSStatusPanel();

	void UpdatePanel(void);

	void Update_StatusWORD(void);

	void Update_StatusINPUT(void);

	void Update_StatusVOUT(void);

	void Update_StatusIOUT(void);

	void Update_StatusTemperature(void);

	void Update_StatusCML(void);

	void Update_StatusOTHER(void);

	void Update_StatusFAN12(void);

	// Top Level Sizer
	wxBoxSizer *m_topLevelSizer;

	// Bitmap
	wxBitmap *m_green;
	wxBitmap *m_red;

	// Status_WORD
	wxGridSizer *m_statusWord_GS_1;
	wxStaticBoxSizer *m_statusWordSBS;

	wxBoxSizer *m_statusWord_HS_1;
	wxBoxSizer *m_statusWord_HS_2;
	wxBoxSizer *m_statusWord_HS_3;
	wxBoxSizer *m_statusWord_HS_4;
	wxBoxSizer *m_statusWord_HS_5;
	wxBoxSizer *m_statusWord_HS_6;
	wxBoxSizer *m_statusWord_HS_7;
	wxBoxSizer *m_statusWord_HS_8;

	wxStaticBitmap *m_stbBUSY_Word;
	wxStaticBitmap *m_stbOFF_Word;
	wxStaticBitmap *m_stbVOUT_OV_FAULT_Word;
	wxStaticBitmap *m_stbIOUT_OC_FAULT_Word;
	wxStaticBitmap *m_stbVIN_UV_FAULT_Word;
	wxStaticBitmap *m_stbTEMPERATURE_Word;
	wxStaticBitmap *m_stbCML_Word;
	wxStaticBitmap *m_stbNONE_OF_THE_ABOVE_Word;


	wxStaticText *m_stBUSY_Word;
	wxStaticText *m_stOFF_Word;
	wxStaticText *m_stVOUT_OV_FAULT_Word;
	wxStaticText *m_stIOUT_OC_FAULT_Word;
	wxStaticText *m_stVIN_UV_FAULT_Word;
	wxStaticText *m_stTEMPERATURE_Word;
	wxStaticText *m_stCML_Word;
	wxStaticText *m_stNONE_OF_THE_ABOVE_Word;

	wxStaticLine *m_statusWord_sl;

	wxGridSizer *m_statusWord_GS_2;

	wxBoxSizer *m_statusWord_HS_9;
	wxBoxSizer *m_statusWord_HS_10;
	wxBoxSizer *m_statusWord_HS_11;
	wxBoxSizer *m_statusWord_HS_12;
	wxBoxSizer *m_statusWord_HS_13;
	wxBoxSizer *m_statusWord_HS_14;
	wxBoxSizer *m_statusWord_HS_15;
	wxBoxSizer *m_statusWord_HS_16;

	wxStaticBitmap *m_stbVOUT_Word;
	wxStaticBitmap *m_stbIOUTPOUT_Word;
	wxStaticBitmap *m_stbINPUT_Word;
	wxStaticBitmap *m_stbMFR_SPECIFIC_Word;
	wxStaticBitmap *m_stbPOWER_GOOD_Word;
	wxStaticBitmap *m_stbFANS_Word;
	wxStaticBitmap *m_stbOTHER_Word;
	wxStaticBitmap *m_stbUNKNOW_Word;

	wxStaticText *m_stVOUT_Word;
	wxStaticText *m_stIOUTPOUT_Word;
	wxStaticText *m_stINPUT_Word;
	wxStaticText *m_stMFR_SPECIFIC_Word;
	wxStaticText *m_stPOWER_GOOD_Word;
	wxStaticText *m_stFANS_Word;
	wxStaticText *m_stOTHER_Word;
	wxStaticText *m_stUNKNOW_Word;


	// Status_INPUT
	wxGridSizer *m_statusInput_GS_1;
	wxStaticBoxSizer *m_statusInputSBS;

	wxBoxSizer *m_statusInput_HS_1;
	wxBoxSizer *m_statusInput_HS_2;
	wxBoxSizer *m_statusInput_HS_3;
	wxBoxSizer *m_statusInput_HS_4;
	wxBoxSizer *m_statusInput_HS_5;
	wxBoxSizer *m_statusInput_HS_6;
	wxBoxSizer *m_statusInput_HS_7;
	wxBoxSizer *m_statusInput_HS_8;

	wxStaticBitmap *m_stbVIN_OV_FAULT_Input;
	wxStaticBitmap *m_stbVIN_OV_WARNING_Input;
	wxStaticBitmap *m_stbVIN_UV_WARNING_Input;
	wxStaticBitmap *m_stbVIN_UV_FAULT_Input;
	wxStaticBitmap *m_stbUNIT_OFF_Input;
	wxStaticBitmap *m_stbIIN_OC_FAULT_Input;
	wxStaticBitmap *m_stbIIN_OC_WARNING_Input;
	wxStaticBitmap *m_stbPIN_OP_WARNING_Input;

	wxStaticText *m_stVIN_OV_FAULT_Input;
	wxStaticText *m_stVIN_OV_WARNING_Input;
	wxStaticText *m_stVIN_UV_WARNING_Input;
	wxStaticText *m_stVIN_UV_FAULT_Input;
	wxStaticText *m_stUNIT_OFF_Input;
	wxStaticText *m_stIIN_OC_FAULT_Input;
	wxStaticText *m_stIIN_OC_WARNING_Input;
	wxStaticText *m_stPIN_OP_WARNING_Input;

	// Status_VOUT
	wxGridSizer *m_statusVout_GS_1;
	wxStaticBoxSizer *m_statusVoutSBS;

	wxBoxSizer *m_statusVout_HS_1;
	wxBoxSizer *m_statusVout_HS_2;
	wxBoxSizer *m_statusVout_HS_3;
	wxBoxSizer *m_statusVout_HS_4;
	wxBoxSizer *m_statusVout_HS_5;
	wxBoxSizer *m_statusVout_HS_6;
	wxBoxSizer *m_statusVout_HS_7;
	wxBoxSizer *m_statusVout_HS_8;

	wxStaticBitmap *m_stbVOUT_OV_FAULT_Vout;
	wxStaticBitmap *m_stbVOUT_OV_WARNING_Vout;
	wxStaticBitmap *m_stbVOUT_UV_WARNING_Vout;
	wxStaticBitmap *m_stbVOUT_UV_FAULT_Vout;
	wxStaticBitmap *m_stbVOUT_MAX_Vout;
	wxStaticBitmap *m_stbTON_MAX_FAULT_Vout;
	wxStaticBitmap *m_stbTOFF_MAX_WARNING_Vout;
	wxStaticBitmap *m_stbVOUT_TRACKING_ERROR_Vout;

	wxStaticText *m_stVOUT_OV_FAULT_Vout;
	wxStaticText *m_stVOUT_OV_WARNING_Vout;
	wxStaticText *m_stVOUT_UV_WARNING_Vout;
	wxStaticText *m_stVOUT_UV_FAULT_Vout;
	wxStaticText *m_stVOUT_MAX_Vout;
	wxStaticText *m_stTON_MAX_FAULT_Vout;
	wxStaticText *m_stTOFF_MAX_WARNING_Vout;
	wxStaticText *m_stVOUT_TRACKING_ERROR_Vout;

	// Status_IOUT
	wxGridSizer *m_statusIout_GS_1;
	wxStaticBoxSizer *m_statusIoutSBS;

	wxBoxSizer *m_statusIout_HS_1;
	wxBoxSizer *m_statusIout_HS_2;
	wxBoxSizer *m_statusIout_HS_3;
	wxBoxSizer *m_statusIout_HS_4;
	wxBoxSizer *m_statusIout_HS_5;
	wxBoxSizer *m_statusIout_HS_6;
	wxBoxSizer *m_statusIout_HS_7;
	wxBoxSizer *m_statusIout_HS_8;

	wxStaticBitmap *m_stbIOUT_OC_FAULT_Iout;
	wxStaticBitmap *m_stbIOUT_OC_LV_FAULT_Iout;
	wxStaticBitmap *m_stbIOUT_OC_WARNING_Iout;
	wxStaticBitmap *m_stbIOUT_UC_FAULT_Iout;
	wxStaticBitmap *m_stbCURRENT_SHARE_FAULT_Iout;
	wxStaticBitmap *m_stbIN_POWER_LIMITING_Iout;
	wxStaticBitmap *m_stbPOUT_OC_FAULT_Iout;
	wxStaticBitmap *m_stbPOUT_OP_WARNING_Iout;

	wxStaticText *m_stIOUT_OC_FAULT_Iout;
	wxStaticText *m_stIOUT_OC_LV_FAULT_Iout;
	wxStaticText *m_stIOUT_OC_WARNING_Iout;
	wxStaticText *m_stIOUT_UC_FAULT_Iout;
	wxStaticText *m_stCURRENT_SHARE_FAULT_Iout;
	wxStaticText *m_stIN_POWER_LIMITING_Iout;
	wxStaticText *m_stPOUT_OC_FAULT_Iout;
	wxStaticText *m_stPOUT_OP_WARNING_Iout;

	// Status_TEMPERATURE
	wxGridSizer *m_statusTemperature_GS_1;
	wxStaticBoxSizer *m_statusTemperatureSBS;

	wxBoxSizer *m_statusTemperature_HS_1;
	wxBoxSizer *m_statusTemperature_HS_2;
	wxBoxSizer *m_statusTemperature_HS_3;
	wxBoxSizer *m_statusTemperature_HS_4;
	wxBoxSizer *m_statusTemperature_HS_5;
	wxBoxSizer *m_statusTemperature_HS_6;
	wxBoxSizer *m_statusTemperature_HS_7;
	wxBoxSizer *m_statusTemperature_HS_8;

	wxStaticBitmap *m_stbOT_FAULT_Temperature;
	wxStaticBitmap *m_stbOT_WARNING_Temperature;
	wxStaticBitmap *m_stbUT_WARNING_Temperature;
	wxStaticBitmap *m_stbUT_FAULT_Temperature;
	wxStaticBitmap *m_stbRESERVED3_Temperature;
	wxStaticBitmap *m_stbRESERVED2_Temperature;
	wxStaticBitmap *m_stbRESERVED1_Temperature;
	wxStaticBitmap *m_stbRESERVED0_Temperature;

	wxStaticText *m_stOT_FAULT_Temperature;
	wxStaticText *m_stOT_WARNING_Temperature;
	wxStaticText *m_stUT_WARNING_Temperature;
	wxStaticText *m_stUT_FAULT_Temperature;
	wxStaticText *m_stRESERVED3_Temperature;
	wxStaticText *m_stRESERVED2_Temperature;
	wxStaticText *m_stRESERVED1_Temperature;
	wxStaticText *m_stRESERVED0_Temperature;

	// Status_CML
	wxGridSizer *m_statusCML_GS_1;
	wxStaticBoxSizer *m_statusCMLSBS;

	wxBoxSizer *m_statusCML_HS_1;
	wxBoxSizer *m_statusCML_HS_2;
	wxBoxSizer *m_statusCML_HS_3;
	wxBoxSizer *m_statusCML_HS_4;
	wxBoxSizer *m_statusCML_HS_5;
	wxBoxSizer *m_statusCML_HS_6;
	wxBoxSizer *m_statusCML_HS_7;
	wxBoxSizer *m_statusCML_HS_8;

	wxStaticBitmap *m_stbINVALID_COMMAND_CML;
	wxStaticBitmap *m_stbINVALID_DATA_CML;
	wxStaticBitmap *m_stbPEC_FAILED_CML;
	wxStaticBitmap *m_stbMEMORY_FAULT_CML;
	wxStaticBitmap *m_stbPROCESSOR_FAULT_CML;
	wxStaticBitmap *m_stbRESERVED_CML;
	wxStaticBitmap *m_stbCOMMUNICATION_CML;
	wxStaticBitmap *m_stbOTHER_MEMORY_CML;

	wxStaticText *m_stINVALID_COMMAND_CML;
	wxStaticText *m_stINVALID_DATA_CML;
	wxStaticText *m_stPEC_FAILED_CML;
	wxStaticText *m_stMEMORY_FAULT_CML;
	wxStaticText *m_stPROCESSOR_FAULT_CML;
	wxStaticText *m_stRESERVED_CML;
	wxStaticText *m_stCOMMUNICATION_CML;
	wxStaticText *m_stOTHER_MEMORY_CML;

	// Status_OTHER
	wxGridSizer *m_statusOTHER_GS_1;
	wxStaticBoxSizer *m_statusOTHERSBS;

	wxBoxSizer *m_statusOTHER_HS_1;
	wxBoxSizer *m_statusOTHER_HS_2;
	wxBoxSizer *m_statusOTHER_HS_3;
	wxBoxSizer *m_statusOTHER_HS_4;
	wxBoxSizer *m_statusOTHER_HS_5;
	wxBoxSizer *m_statusOTHER_HS_6;
	wxBoxSizer *m_statusOTHER_HS_7;
	wxBoxSizer *m_statusOTHER_HS_8;

	wxStaticBitmap *m_stbRESERVED7_OTHER;
	wxStaticBitmap *m_stbRESERVED6_OTHER;
	wxStaticBitmap *m_stbINPUT_A_FUSE_FAULT_OTHER;
	wxStaticBitmap *m_stbINPUT_B_FUSE_FAULT_OTHER;
	wxStaticBitmap *m_stbINPUT_A_ORING_FAULT_OTHER;
	wxStaticBitmap *m_stbINPUT_B_ORING_FAULT_OTHER;
	wxStaticBitmap *m_stbOUTPUT_ORING_FAULT_OTHER;
	wxStaticBitmap *m_stbRESERVED_OTHER;

	wxStaticText *m_stRESERVED7_OTHER;
	wxStaticText *m_stRESERVED6_OTHER;
	wxStaticText *m_stINPUT_A_FUSE_FAULT_OTHER;
	wxStaticText *m_stINPUT_B_FUSE_FAULT_OTHER;
	wxStaticText *m_stINPUT_A_ORING_FAULT_OTHER;
	wxStaticText *m_stINPUT_B_ORING_FAULT_OTHER;
	wxStaticText *m_stOUTPUT_ORING_FAULT_OTHER;
	wxStaticText *m_stRESERVED_OTHER;

	// Status_FAN12
	wxGridSizer *m_statusFAN12_GS_1;
	wxStaticBoxSizer *m_statusFAN12SBS;

	wxBoxSizer *m_statusFAN12_HS_1;
	wxBoxSizer *m_statusFAN12_HS_2;
	wxBoxSizer *m_statusFAN12_HS_3;
	wxBoxSizer *m_statusFAN12_HS_4;
	wxBoxSizer *m_statusFAN12_HS_5;
	wxBoxSizer *m_statusFAN12_HS_6;
	wxBoxSizer *m_statusFAN12_HS_7;
	wxBoxSizer *m_statusFAN12_HS_8;

	wxStaticBitmap *m_stbFAN_1_FAULT_FAN12;
	wxStaticBitmap *m_stbFAN_2_FAULT_FAN12;
	wxStaticBitmap *m_stbFAN_1_WARNING_FAN12;
	wxStaticBitmap *m_stbFAN_2_WARNING_FAN12;
	wxStaticBitmap *m_stbFAN_1_SPEED_OVERRIDDEN_FAN12;
	wxStaticBitmap *m_stbFAN_2_SPEED_OVERRIDDEN_FAN12;
	wxStaticBitmap *m_stbAIRFLOW_FAULT_FAN12;
	wxStaticBitmap *m_stbAIRFLOW_WARNING_OTHER;

	wxStaticText *m_stFAN_1_FAULT_FAN12;
	wxStaticText *m_stFAN_2_FAULT_FAN12;
	wxStaticText *m_stFAN_1_WARNING_FAN12;
	wxStaticText *m_stFAN_2_WARNING_FAN12;
	wxStaticText *m_stFAN_1_SPEED_OVERRIDDEN_FAN12;
	wxStaticText *m_stFAN_2_SPEED_OVERRIDDEN_FAN12;
	wxStaticText *m_stAIRFLOW_FAULT_FAN12;
	wxStaticText *m_stAIRFLOW_WARNING_OTHER;

protected:

private:

};

#endif
