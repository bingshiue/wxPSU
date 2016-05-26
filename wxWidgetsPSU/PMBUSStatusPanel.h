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

class PMBUSStatusPanel : public wxPanel {
public:
	/**
	 * @brief Constructor.
	 */
	PMBUSStatusPanel(wxWindow* parent);
	/**
	 * @brief Deconstructor.
	 */
	~PMBUSStatusPanel();

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

	wxStaticBitmap *m_stbBUSY;
	wxStaticBitmap *m_stbOFF;
	wxStaticBitmap *m_stbVOUT_OV_FAULT;
	wxStaticBitmap *m_stbIOUT_OC_FAULT;
	wxStaticBitmap *m_stbVIN_UV_FAULT;
	wxStaticBitmap *m_stbTEMPERATURE;
	wxStaticBitmap *m_stbCML;
	wxStaticBitmap *m_stbNONE_OF_THE_ABOVE;


	wxStaticText *m_stBUSY;
	wxStaticText *m_stOFF;
	wxStaticText *m_stVOUT_OV_FAULT;
	wxStaticText *m_stIOUT_OC_FAULT;
	wxStaticText *m_stVIN_UV_FAULT;
	wxStaticText *m_stTEMPERATURE;
	wxStaticText *m_stCML;
	wxStaticText *m_stNONE_OF_THE_ABOVE;

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

	wxStaticBitmap *m_stbVOUT;
	wxStaticBitmap *m_stbIOUTPOUT;
	wxStaticBitmap *m_stbINPUT;
	wxStaticBitmap *m_stbMFR_SPECIFIC;
	wxStaticBitmap *m_stbPOWER_GOOD;
	wxStaticBitmap *m_stbFANS;
	wxStaticBitmap *m_stbOTHER;
	wxStaticBitmap *m_stbUNKNOW;

	wxStaticText *m_stVOUT;
	wxStaticText *m_stIOUTPOUT;
	wxStaticText *m_stINPUT;
	wxStaticText *m_stMFR_SPECIFIC;
	wxStaticText *m_stPOWER_GOOD;
	wxStaticText *m_stFANS;
	wxStaticText *m_stOTHER;
	wxStaticText *m_stUNKNOW;


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

	wxStaticBitmap *m_stbVIN_OV_FAULT;
	wxStaticBitmap *m_stbVIN_OV_WARNING;
	wxStaticBitmap *m_stbVIN_UV_WARNING;
	wxStaticBitmap *m_stbVIN_UV_FAULT_Input;
	wxStaticBitmap *m_stbUNIT_OFF;
	wxStaticBitmap *m_stbIIN_OC_FAULT;
	wxStaticBitmap *m_stbIIN_OC_WARNING;
	wxStaticBitmap *m_stbPIN_OP_WARNING;

	wxStaticText *m_stVIN_OV_FAULT;
	wxStaticText *m_stVIN_OV_WARNING;
	wxStaticText *m_stVIN_UV_WARNING;
	wxStaticText *m_stVIN_UV_FAULT_2;
	wxStaticText *m_stUNIT_OFF;
	wxStaticText *m_stIIN_OC_FAULT;
	wxStaticText *m_stIIN_OC_WARNING;
	wxStaticText *m_stPIN_OP_WARNING;

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


	// Status_TEMPERATURE


	// Status_CML


	// Status_OTHER



protected:

private:

};

#endif
