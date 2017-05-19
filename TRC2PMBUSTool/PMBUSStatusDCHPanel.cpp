/**
 * @file PMBusStatusDCHPanel.cpp
 */
#include "PMBUSHelper.h"
#include "PMBUSCBCook.h"
#include "PMBUSStatusDCHPanel.h"
#include "green.xpm"
#include "red.xpm"

PMBUSStatusDCHPanel::PMBUSStatusDCHPanel(wxWindow* parent) : wxScrolledWindow(parent) {
	// Load Bitmap
	m_green = new wxBitmap(LOAD_PNG_RESOURCE(green_light_24));//green_xpm);
	m_red = new wxBitmap(LOAD_PNG_RESOURCE(red_light_24));//red_xpm);

	// Status_WORD
	this->m_statusWordSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_WORD"));
	this->m_statusWord_GS_1 = new wxGridSizer(2, 4, 0, 0);
	this->m_statusWord_GS_2 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusWord_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_statusWord_HS_9 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_10 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_11 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_12 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_13 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_14 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_15 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_16 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbBUSY_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOFF_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_OV_FAULT_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_OC_FAULT_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_UV_FAULT_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTEMPERATURE_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbCML_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbNONE_OF_THE_ABOVE_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);

	this->m_stbVOUT_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUTPOUT_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINPUT_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbMFR_SPECIFIC_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPOWER_GOOD_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFANS_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOTHER_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbUNKNOW_Word = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stBUSY_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("BUSY(MSB)"));
	m_stOFF_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("OFF"));
	m_stVOUT_OV_FAULT_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_FAULT"));
	m_stIOUT_OC_FAULT_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_FAULT"));
	m_stVIN_UV_FAULT_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("VIN_UV_FAULT"));
	m_stTEMPERATURE_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("TEMPERATURE"));
	m_stCML_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("CML"));
	m_stNONE_OF_THE_ABOVE_Word = new wxStaticText(this, wxID_ANY, wxT("NONE_OF_THE_ABOVE(LSB)"));

	m_stVOUT_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("VOUT(MSB)"));
	m_stIOUTPOUT_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("IOUT/POUT"));
	m_stINPUT_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("INPUT"));
	m_stMFR_SPECIFIC_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("MFR_SPECIFIC"));
	m_stPOWER_GOOD_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("POWER_GOOD"));
	m_stFANS_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("FANS"));
	m_stOTHER_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("OTHER"));
	m_stUNKNOW_Word = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("UNKNOW(LSB)"));


	m_statusWord_HS_1->Add(m_stbBUSY_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_1->Add(m_stBUSY_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_2->Add(m_stbOFF_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_2->Add(m_stOFF_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_3->Add(m_stbVOUT_OV_FAULT_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_3->Add(m_stVOUT_OV_FAULT_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_4->Add(m_stbIOUT_OC_FAULT_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_4->Add(m_stIOUT_OC_FAULT_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_5->Add(m_stbVIN_UV_FAULT_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_5->Add(m_stVIN_UV_FAULT_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_6->Add(m_stbTEMPERATURE_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_6->Add(m_stTEMPERATURE_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_7->Add(m_stbCML_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_7->Add(m_stCML_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_8->Add(m_stbNONE_OF_THE_ABOVE_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_8->Add(m_stNONE_OF_THE_ABOVE_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_9->Add(m_stbVOUT_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_9->Add(m_stVOUT_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_10->Add(m_stbIOUTPOUT_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_10->Add(m_stIOUTPOUT_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_11->Add(m_stbINPUT_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_11->Add(m_stINPUT_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_12->Add(m_stbMFR_SPECIFIC_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_12->Add(m_stMFR_SPECIFIC_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_13->Add(m_stbPOWER_GOOD_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_13->Add(m_stPOWER_GOOD_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_14->Add(m_stbFANS_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_14->Add(m_stFANS_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_15->Add(m_stbOTHER_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_15->Add(m_stOTHER_Word, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_16->Add(m_stbUNKNOW_Word, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_16->Add(m_stUNKNOW_Word, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusWord_GS_1->Add(m_statusWord_HS_1);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_2);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_3);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_4);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_5);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_6);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_7);
	this->m_statusWord_GS_1->Add(m_statusWord_HS_8);

	this->m_statusWord_GS_2->Add(m_statusWord_HS_9);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_10);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_11);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_12);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_13);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_14);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_15);
	this->m_statusWord_GS_2->Add(m_statusWord_HS_16);

	m_statusWordSBS->Add(m_statusWord_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	m_statusWord_sl = new wxStaticLine(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize(200, -1));

	m_statusWordSBS->AddSpacer(5);

	m_statusWordSBS->Add(m_statusWord_sl, wxSizerFlags(0).Expand());

	m_statusWordSBS->AddSpacer(5);

	m_statusWordSBS->Add(m_statusWord_GS_2, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_INPUT
	this->m_statusInputSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_INPUT"));
	//m_statusInputSBS->GetStaticBox()->SetFont(wxFont(wxSWISS_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	this->m_statusInput_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusInput_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbVIN_OV_FAULT_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_OV_WARNING_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_UV_WARNING_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_UV_FAULT_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbUNIT_OFF_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIIN_OC_FAULT_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIIN_OC_WARNING_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPIN_OP_WARNING_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stVIN_OV_FAULT_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_OV_FAULT(MSB)"));
	m_stVIN_OV_WARNING_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_OV_WARNING"));
	m_stVIN_UV_WARNING_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_UV_WARNING"));
	m_stVIN_UV_FAULT_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_UV_FAULT"));
	m_stUNIT_OFF_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("UNIT_OFF"));
	m_stIIN_OC_FAULT_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("IIN_OC_FAULT"));
	m_stIIN_OC_WARNING_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("IIN_OC_WARNING"));
	m_stPIN_OP_WARNING_Input = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("PIN_OP_WARNING(LSB)"));

	m_statusInput_HS_1->Add(m_stbVIN_OV_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_1->Add(m_stVIN_OV_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_2->Add(m_stbVIN_OV_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_2->Add(m_stVIN_OV_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_3->Add(m_stbVIN_UV_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_3->Add(m_stVIN_UV_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_4->Add(m_stbVIN_UV_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_4->Add(m_stVIN_UV_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_5->Add(m_stbUNIT_OFF_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_5->Add(m_stUNIT_OFF_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_6->Add(m_stbIIN_OC_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_6->Add(m_stIIN_OC_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_7->Add(m_stbIIN_OC_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_7->Add(m_stIIN_OC_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_8->Add(m_stbPIN_OP_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_8->Add(m_stPIN_OP_WARNING_Input, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusInput_GS_1->Add(m_statusInput_HS_1);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_2);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_3);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_4);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_5);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_6);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_7);
	this->m_statusInput_GS_1->Add(m_statusInput_HS_8);

	m_statusInputSBS->Add(m_statusInput_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_VOUT 1
	this->m_statusVout1SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_VOUT_1"));

	this->m_statusVout1_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusVout1_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout1_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbVOUT_OV_FAULT_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_OV_WARNING_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_UV_WARNING_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_UV_FAULT_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_MAX_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTON_MAX_FAULT_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTOFF_MAX_WARNING_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_TRACKING_ERROR_Vout1 = new wxStaticBitmap(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stVOUT_OV_FAULT_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_FAULT(MSB)"));
	m_stVOUT_OV_WARNING_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_WARNING"));
	m_stVOUT_UV_WARNING_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_UV_WARNING"));
	m_stVOUT_UV_FAULT_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_UV_FAULT"));
	m_stVOUT_MAX_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_MAX"));
	m_stTON_MAX_FAULT_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("TON_MAX_FAULT"));
	m_stTOFF_MAX_WARNING_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("TOFF_MAX_WARNING"));
	m_stVOUT_TRACKING_ERROR_Vout1 = new wxStaticText(this->m_statusVout1SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_TRACKING_ERROR(LSB)"));

	m_statusVout1_HS_1->Add(m_stbVOUT_OV_FAULT_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_1->Add(m_stVOUT_OV_FAULT_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_2->Add(m_stbVOUT_OV_WARNING_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_2->Add(m_stVOUT_OV_WARNING_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_3->Add(m_stbVOUT_UV_WARNING_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_3->Add(m_stVOUT_UV_WARNING_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_4->Add(m_stbVOUT_UV_FAULT_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_4->Add(m_stVOUT_UV_FAULT_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_5->Add(m_stbVOUT_MAX_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_5->Add(m_stVOUT_MAX_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_6->Add(m_stbTON_MAX_FAULT_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_6->Add(m_stTON_MAX_FAULT_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_7->Add(m_stbTOFF_MAX_WARNING_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_7->Add(m_stTOFF_MAX_WARNING_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout1_HS_8->Add(m_stbVOUT_TRACKING_ERROR_Vout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout1_HS_8->Add(m_stVOUT_TRACKING_ERROR_Vout1, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_1);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_2);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_3);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_4);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_5);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_6);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_7);
	this->m_statusVout1_GS_1->Add(m_statusVout1_HS_8);

	m_statusVout1SBS->Add(m_statusVout1_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_VOUT 2
	this->m_statusVout2SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_VOUT_2"));

	this->m_statusVout2_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusVout2_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout2_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbVOUT_OV_FAULT_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_OV_WARNING_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_UV_WARNING_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_UV_FAULT_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_MAX_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTON_MAX_FAULT_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTOFF_MAX_WARNING_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_TRACKING_ERROR_Vout2 = new wxStaticBitmap(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stVOUT_OV_FAULT_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_FAULT(MSB)"));
	m_stVOUT_OV_WARNING_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_WARNING"));
	m_stVOUT_UV_WARNING_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_UV_WARNING"));
	m_stVOUT_UV_FAULT_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_UV_FAULT"));
	m_stVOUT_MAX_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_MAX"));
	m_stTON_MAX_FAULT_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("TON_MAX_FAULT"));
	m_stTOFF_MAX_WARNING_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("TOFF_MAX_WARNING"));
	m_stVOUT_TRACKING_ERROR_Vout2 = new wxStaticText(this->m_statusVout2SBS->GetStaticBox(), wxID_ANY, wxT("VOUT_TRACKING_ERROR(LSB)"));

	m_statusVout2_HS_1->Add(m_stbVOUT_OV_FAULT_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_1->Add(m_stVOUT_OV_FAULT_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_2->Add(m_stbVOUT_OV_WARNING_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_2->Add(m_stVOUT_OV_WARNING_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_3->Add(m_stbVOUT_UV_WARNING_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_3->Add(m_stVOUT_UV_WARNING_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_4->Add(m_stbVOUT_UV_FAULT_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_4->Add(m_stVOUT_UV_FAULT_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_5->Add(m_stbVOUT_MAX_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_5->Add(m_stVOUT_MAX_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_6->Add(m_stbTON_MAX_FAULT_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_6->Add(m_stTON_MAX_FAULT_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_7->Add(m_stbTOFF_MAX_WARNING_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_7->Add(m_stTOFF_MAX_WARNING_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout2_HS_8->Add(m_stbVOUT_TRACKING_ERROR_Vout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout2_HS_8->Add(m_stVOUT_TRACKING_ERROR_Vout2, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_1);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_2);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_3);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_4);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_5);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_6);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_7);
	this->m_statusVout2_GS_1->Add(m_statusVout2_HS_8);

	m_statusVout2SBS->Add(m_statusVout2_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_IOUT 1
	this->m_statusIout1SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_IOUT_1"));

	this->m_statusIout1_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusIout1_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout1_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbIOUT_OC_FAULT_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_OC_LV_FAULT_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_OC_WARNING_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_UC_FAULT_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbCURRENT_SHARE_FAULT_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIN_POWER_LIMITING_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPOUT_OC_FAULT_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPOUT_OP_WARNING_Iout1 = new wxStaticBitmap(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stIOUT_OC_FAULT_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_FAULT(MSB)"));
	m_stIOUT_OC_LV_FAULT_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_LV_FAULT"));
	m_stIOUT_OC_WARNING_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_WARNING"));
	m_stIOUT_UC_FAULT_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_UC_FAULT"));
	m_stCURRENT_SHARE_FAULT_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("CURRENT_SHARE_FAULT"));
	m_stIN_POWER_LIMITING_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("IN_POWER_LIMITING"));
	m_stPOUT_OC_FAULT_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("POUT_OP_FAULT"));
	m_stPOUT_OP_WARNING_Iout1 = new wxStaticText(this->m_statusIout1SBS->GetStaticBox(), wxID_ANY, wxT("POUT_OP_WARNING(LSB)"));

	m_statusIout1_HS_1->Add(m_stbIOUT_OC_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_1->Add(m_stIOUT_OC_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_2->Add(m_stbIOUT_OC_LV_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_2->Add(m_stIOUT_OC_LV_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_3->Add(m_stbIOUT_OC_WARNING_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_3->Add(m_stIOUT_OC_WARNING_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_4->Add(m_stbIOUT_UC_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_4->Add(m_stIOUT_UC_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_5->Add(m_stbCURRENT_SHARE_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_5->Add(m_stCURRENT_SHARE_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_6->Add(m_stbIN_POWER_LIMITING_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_6->Add(m_stIN_POWER_LIMITING_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_7->Add(m_stbPOUT_OC_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_7->Add(m_stPOUT_OC_FAULT_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout1_HS_8->Add(m_stbPOUT_OP_WARNING_Iout1, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout1_HS_8->Add(m_stPOUT_OP_WARNING_Iout1, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_1);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_2);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_3);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_4);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_5);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_6);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_7);
	this->m_statusIout1_GS_1->Add(m_statusIout1_HS_8);

	m_statusIout1SBS->Add(m_statusIout1_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_IOUT 2
	this->m_statusIout2SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_IOUT_2"));

	this->m_statusIout2_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusIout2_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusIout2_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbIOUT_OC_FAULT_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_OC_LV_FAULT_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_OC_WARNING_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_UC_FAULT_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbCURRENT_SHARE_FAULT_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIN_POWER_LIMITING_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPOUT_OC_FAULT_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPOUT_OP_WARNING_Iout2 = new wxStaticBitmap(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stIOUT_OC_FAULT_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_FAULT(MSB)"));
	m_stIOUT_OC_LV_FAULT_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_LV_FAULT"));
	m_stIOUT_OC_WARNING_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_WARNING"));
	m_stIOUT_UC_FAULT_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("IOUT_UC_FAULT"));
	m_stCURRENT_SHARE_FAULT_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("CURRENT_SHARE_FAULT"));
	m_stIN_POWER_LIMITING_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("IN_POWER_LIMITING"));
	m_stPOUT_OC_FAULT_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("POUT_OC_FAULT"));
	m_stPOUT_OP_WARNING_Iout2 = new wxStaticText(this->m_statusIout2SBS->GetStaticBox(), wxID_ANY, wxT("POUT_OP_WARNING(LSB)"));

	m_statusIout2_HS_1->Add(m_stbIOUT_OC_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_1->Add(m_stIOUT_OC_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_2->Add(m_stbIOUT_OC_LV_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_2->Add(m_stIOUT_OC_LV_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_3->Add(m_stbIOUT_OC_WARNING_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_3->Add(m_stIOUT_OC_WARNING_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_4->Add(m_stbIOUT_UC_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_4->Add(m_stIOUT_UC_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_5->Add(m_stbCURRENT_SHARE_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_5->Add(m_stCURRENT_SHARE_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_6->Add(m_stbIN_POWER_LIMITING_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_6->Add(m_stIN_POWER_LIMITING_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_7->Add(m_stbPOUT_OC_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_7->Add(m_stPOUT_OC_FAULT_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusIout2_HS_8->Add(m_stbPOUT_OP_WARNING_Iout2, 0, wxALIGN_CENTER_VERTICAL);
	m_statusIout2_HS_8->Add(m_stPOUT_OP_WARNING_Iout2, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_1);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_2);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_3);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_4);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_5);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_6);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_7);
	this->m_statusIout2_GS_1->Add(m_statusIout2_HS_8);

	m_statusIout2SBS->Add(m_statusIout2_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));


	/* ------------------------------------------------------------------------------ */

	// Status_TEMPERATURE
	this->m_statusTemperatureSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_TEMPERATURE"));

	this->m_statusTemperature_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusTemperature_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusTemperature_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbOT_FAULT_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOT_WARNING_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbUT_WARNING_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbUT_FAULT_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED3_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED2_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED1_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED0_Temperature = new wxStaticBitmap(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stOT_FAULT_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("OT_FAULT(MSB)"));
	m_stOT_WARNING_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("OT_WARNING"));
	m_stUT_WARNING_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("UT_WARNING"));
	m_stUT_FAULT_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("UT_FAULT"));
	m_stRESERVED3_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED3"));
	m_stRESERVED2_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED2"));
	m_stRESERVED1_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED1"));
	m_stRESERVED0_Temperature = new wxStaticText(this->m_statusTemperatureSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED0(LSB)"));

	m_statusTemperature_HS_1->Add(m_stbOT_FAULT_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_1->Add(m_stOT_FAULT_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_2->Add(m_stbOT_WARNING_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_2->Add(m_stOT_WARNING_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_3->Add(m_stbUT_WARNING_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_3->Add(m_stUT_WARNING_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_4->Add(m_stbUT_FAULT_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_4->Add(m_stUT_FAULT_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_5->Add(m_stbRESERVED3_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_5->Add(m_stRESERVED3_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_6->Add(m_stbRESERVED2_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_6->Add(m_stRESERVED2_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_7->Add(m_stbRESERVED1_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_7->Add(m_stRESERVED1_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	m_statusTemperature_HS_8->Add(m_stbRESERVED0_Temperature, 0, wxALIGN_CENTER_VERTICAL);
	m_statusTemperature_HS_8->Add(m_stRESERVED0_Temperature, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_1);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_2);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_3);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_4);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_5);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_6);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_7);
	this->m_statusTemperature_GS_1->Add(m_statusTemperature_HS_8);

	m_statusTemperatureSBS->Add(m_statusTemperature_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_CML
	this->m_statusCMLSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_CML"));

	this->m_statusCML_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusCML_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusCML_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbINVALID_COMMAND_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINVALID_DATA_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPEC_FAILED_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbMEMORY_FAULT_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPROCESSOR_FAULT_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbCOMMUNICATION_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOTHER_MEMORY_CML = new wxStaticBitmap(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stINVALID_COMMAND_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("INVALID_COMMAND(MSB)"));
	m_stINVALID_DATA_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("INVALID_DATA"));
	m_stPEC_FAILED_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("PEC_FAILED"));
	m_stMEMORY_FAULT_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("MEMORY_FAULT"));
	m_stPROCESSOR_FAULT_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("PROCESSOR_FAULT"));
	m_stRESERVED_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED"));
	m_stCOMMUNICATION_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("COMMUNICATION"));
	m_stOTHER_MEMORY_CML = new wxStaticText(this->m_statusCMLSBS->GetStaticBox(), wxID_ANY, wxT("OTHER_MEMORY(LSB)"));

	m_statusCML_HS_1->Add(m_stbINVALID_COMMAND_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_1->Add(m_stINVALID_COMMAND_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_2->Add(m_stbINVALID_DATA_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_2->Add(m_stINVALID_DATA_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_3->Add(m_stbPEC_FAILED_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_3->Add(m_stPEC_FAILED_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_4->Add(m_stbMEMORY_FAULT_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_4->Add(m_stMEMORY_FAULT_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_5->Add(m_stbPROCESSOR_FAULT_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_5->Add(m_stPROCESSOR_FAULT_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_6->Add(m_stbRESERVED_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_6->Add(m_stRESERVED_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_7->Add(m_stbCOMMUNICATION_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_7->Add(m_stCOMMUNICATION_CML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusCML_HS_8->Add(m_stbOTHER_MEMORY_CML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusCML_HS_8->Add(m_stOTHER_MEMORY_CML, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusCML_GS_1->Add(m_statusCML_HS_1);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_2);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_3);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_4);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_5);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_6);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_7);
	this->m_statusCML_GS_1->Add(m_statusCML_HS_8);

	m_statusCMLSBS->Add(m_statusCML_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_OTHER
	this->m_statusOTHERSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_OTHER"));

	this->m_statusOTHER_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusOTHER_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusOTHER_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbRESERVED7_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED6_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINPUT_A_FUSE_FAULT_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINPUT_B_FUSE_FAULT_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINPUT_A_ORING_FAULT_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINPUT_B_ORING_FAULT_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOUTPUT_ORING_FAULT_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbRESERVED_OTHER = new wxStaticBitmap(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stRESERVED7_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED7(MSB)"));
	m_stRESERVED6_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED6"));
	m_stINPUT_A_FUSE_FAULT_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("INPUT_A_FUSE_FAULT"));
	m_stINPUT_B_FUSE_FAULT_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("INPUT_B_FUSE_FAULT"));
	m_stINPUT_A_ORING_FAULT_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("INPUT_A_ORING_FAULT"));
	m_stINPUT_B_ORING_FAULT_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("INPUT_B_ORING_FAULT"));
	m_stOUTPUT_ORING_FAULT_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("OUTPUT_ORING_FAULT"));
	m_stRESERVED_OTHER = new wxStaticText(this->m_statusOTHERSBS->GetStaticBox(), wxID_ANY, wxT("RESERVED(LSB)"));

	m_statusOTHER_HS_1->Add(m_stbRESERVED7_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_1->Add(m_stRESERVED7_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_2->Add(m_stbRESERVED6_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_2->Add(m_stRESERVED6_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_3->Add(m_stbINPUT_A_FUSE_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_3->Add(m_stINPUT_A_FUSE_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_4->Add(m_stbINPUT_B_FUSE_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_4->Add(m_stINPUT_B_FUSE_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_5->Add(m_stbINPUT_A_ORING_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_5->Add(m_stINPUT_A_ORING_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_6->Add(m_stbINPUT_B_ORING_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_6->Add(m_stINPUT_B_ORING_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_7->Add(m_stbOUTPUT_ORING_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_7->Add(m_stOUTPUT_ORING_FAULT_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusOTHER_HS_8->Add(m_stbRESERVED_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusOTHER_HS_8->Add(m_stRESERVED_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_1);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_2);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_3);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_4);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_5);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_6);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_7);
	this->m_statusOTHER_GS_1->Add(m_statusOTHER_HS_8);

	m_statusOTHERSBS->Add(m_statusOTHER_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// FAN12
	this->m_statusFAN12SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_FAN12"));

	this->m_statusFAN12_GS_1 = new wxGridSizer(2, 4, 0, 0);

	this->m_statusFAN12_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusFAN12_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbFAN_1_FAULT_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFAN_2_FAULT_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFAN_1_WARNING_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFAN_2_WARNING_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFAN_1_SPEED_OVERRIDDEN_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFAN_2_SPEED_OVERRIDDEN_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbAIRFLOW_FAULT_FAN12 = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbAIRFLOW_WARNING_OTHER = new wxStaticBitmap(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stFAN_1_FAULT_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("FAN_1_FAULT(MSB)"));
	m_stFAN_2_FAULT_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("FAN_2_FAULT"));
	m_stFAN_1_WARNING_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("FAN_1_WARNING"));
	m_stFAN_2_WARNING_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("FAN_2_WARNING"));
	m_stFAN_1_SPEED_OVERRIDDEN_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("FAN_1_SPEED_OVERRIDDEN"));
	m_stFAN_2_SPEED_OVERRIDDEN_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("FAN_2_SPEED_OVERRIDDEN"));
	m_stAIRFLOW_FAULT_FAN12 = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("AIRFLOW_FAULT"));
	m_stAIRFLOW_WARNING_OTHER = new wxStaticText(this->m_statusFAN12SBS->GetStaticBox(), wxID_ANY, wxT("AIRFLOW_WARNING(LSB)"));

	m_statusFAN12_HS_1->Add(m_stbFAN_1_FAULT_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_1->Add(m_stFAN_1_FAULT_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_2->Add(m_stbFAN_2_FAULT_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_2->Add(m_stFAN_2_FAULT_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_3->Add(m_stbFAN_1_WARNING_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_3->Add(m_stFAN_1_WARNING_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_4->Add(m_stbFAN_2_WARNING_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_4->Add(m_stFAN_2_WARNING_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_5->Add(m_stbFAN_1_SPEED_OVERRIDDEN_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_5->Add(m_stFAN_1_SPEED_OVERRIDDEN_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_6->Add(m_stbFAN_2_SPEED_OVERRIDDEN_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_6->Add(m_stFAN_2_SPEED_OVERRIDDEN_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_7->Add(m_stbAIRFLOW_FAULT_FAN12, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_7->Add(m_stAIRFLOW_FAULT_FAN12, 0, wxALIGN_CENTER_VERTICAL);

	m_statusFAN12_HS_8->Add(m_stbAIRFLOW_WARNING_OTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusFAN12_HS_8->Add(m_stAIRFLOW_WARNING_OTHER, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_1);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_2);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_3);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_4);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_5);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_6);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_7);
	this->m_statusFAN12_GS_1->Add(m_statusFAN12_HS_8);

	m_statusFAN12SBS->Add(m_statusFAN12_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));


	/* ------------------------------------------------------------------------------ */


	// Add Components in Top Level Sizer
	this->m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	this->m_topLevelSizer->Add(m_statusWordSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusVout1SBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusVout2SBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusIout1SBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusIout2SBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusInputSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusTemperatureSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusCMLSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusOTHERSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusFAN12SBS, wxSizerFlags(0).Expand());

	SetSizer(this->m_topLevelSizer);

	// this part makes the scrollbars show up
	this->FitInside(); // ask the sizer about the needed size
	this->SetScrollRate(5, 5);
}

PMBUSStatusDCHPanel::~PMBUSStatusDCHPanel(){

}


void PMBUSStatusDCHPanel::UpdatePanel(void){
	// Update Status WORD Field
	Update_StatusWORD();
	// Update Status Input Field
	Update_StatusINPUT();
	// Update Status VOUT Field
	Update_StatusVOUT();
	// Update Status VOUT2 Field
	Update_StatusVOUT2();
	// Update Status IOUT Field
	Update_StatusIOUT();
	// Update Status IOUT2 Field
	Update_StatusIOUT2();
	// Update Status TEMPERATURE Field
	Update_StatusTemperature();
	// Update Status CML Field
	Update_StatusCML();
	// Update Status OTHER Field
	Update_StatusOTHER();
	// Update Status FAN12 Field
	Update_StatusFAN12();
}

void PMBUSStatusDCHPanel::Update_StatusWORD(void){
	const unsigned short status[16] = {
		STATUS_WORD_HIGH_VOUT,
		STATUS_WORD_HIGH_IOUTPOUT,
		STATUS_WORD_HIGH_INPUT,
		STATUS_WORD_HIGH_MFR_SPECIFIC,
		STATUS_WORD_HIGH_POWERGOOD,
		STATUS_WORD_HIGH_FANS,
		STATUS_WORD_HIGH_OTHER,
		STATUS_WORD_HIGH_UNKNOWN,
		STATUS_WORD_LOW_BUSY,
		STATUS_WORD_LOW_OFF,
		STATUS_WORD_LOW_VOUT_OV_FAULT,
		STATUS_WORD_LOW_IOUT_OC_FAULT,
		STATUS_WORD_LOW_VIN_UV_FAULT,
		STATUS_WORD_LOW_TEMPERATURE,
		STATUS_WORD_LOW_CML,
		STATUS_WORD_LOW_NONE_OF_THE_ABOVE
	};

	wxStaticBitmap *sbArray[16] = {
		this->m_stbVOUT_Word,
		this->m_stbIOUTPOUT_Word,
		this->m_stbINPUT_Word,
		this->m_stbMFR_SPECIFIC_Word,
		this->m_stbPOWER_GOOD_Word,
		this->m_stbFANS_Word,
		this->m_stbOTHER_Word,
		this->m_stbUNKNOW_Word,
		this->m_stbBUSY_Word,
		this->m_stbOFF_Word,
		this->m_stbVOUT_OV_FAULT_Word,
		this->m_stbIOUT_OC_FAULT_Word,
		this->m_stbVIN_UV_FAULT_Word,
		this->m_stbTEMPERATURE_Word,
		this->m_stbCML_Word,
		this->m_stbNONE_OF_THE_ABOVE_Word,
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_word.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_word.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 16; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_word.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusINPUT(void){
	const unsigned char status[8] = {
		STATUS_INPUT_VIN_OV_FAULT,
		STATUS_INPUT_VIN_OV_WARNING,
		STATUS_INPUT_VIN_UV_WARNING,
		STATUS_INPUT_VIN_UV_FAULT,
		STATUS_INPUT_Unit_Off_For_Insufficient_Input_Voltage,
		STATUS_INPUT_IIN_OC_FAULT,
		STATUS_INPUT_IIN_OC_WARNING,
		STATUS_INPUT_PIN_OP_WARNING,
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbVIN_OV_FAULT_Input,
		m_stbVIN_OV_WARNING_Input,
		m_stbVIN_UV_WARNING_Input,
		m_stbVIN_UV_FAULT_Input,
		m_stbUNIT_OFF_Input,
		m_stbIIN_OC_FAULT_Input,
		m_stbIIN_OC_WARNING_Input,
		m_stbPIN_OP_WARNING_Input
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_input.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_input.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_input.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusVOUT(void){
	const unsigned char status[8] = {
		STATUS_VOUT_VOUT_OV_FAULT,
		STATUS_VOUT_VOUT_OV_WARNING,
		STATUS_VOUT_VOUT_UV_WARNING,
		STATUS_VOUT_VOUT_UV_FAULT,
		STATUS_VOUT_VOUT_MAX,
		STATUS_VOUT_TON_MAX_FAULT,
		STATUS_VOUT_TOFF_MAX_WARNING,
		STATUS_VOUT_VOUT_Tracking_Error
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbVOUT_OV_FAULT_Vout1,
		m_stbVOUT_OV_WARNING_Vout1,
		m_stbVOUT_UV_WARNING_Vout1,
		m_stbVOUT_UV_FAULT_Vout1,
		m_stbVOUT_MAX_Vout1,
		m_stbTON_MAX_FAULT_Vout1,
		m_stbTOFF_MAX_WARNING_Vout1,
		m_stbVOUT_TRACKING_ERROR_Vout1
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_vout.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_vout.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_vout.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusVOUT2(void){
	const unsigned char status[8] = {
		STATUS_VOUT_VOUT_OV_FAULT,
		STATUS_VOUT_VOUT_OV_WARNING,
		STATUS_VOUT_VOUT_UV_WARNING,
		STATUS_VOUT_VOUT_UV_FAULT,
		STATUS_VOUT_VOUT_MAX,
		STATUS_VOUT_TON_MAX_FAULT,
		STATUS_VOUT_TOFF_MAX_WARNING,
		STATUS_VOUT_VOUT_Tracking_Error
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbVOUT_OV_FAULT_Vout2,
		m_stbVOUT_OV_WARNING_Vout2,
		m_stbVOUT_UV_WARNING_Vout2,
		m_stbVOUT_UV_FAULT_Vout2,
		m_stbVOUT_MAX_Vout1,
		m_stbTON_MAX_FAULT_Vout2,
		m_stbTOFF_MAX_WARNING_Vout2,
		m_stbVOUT_TRACKING_ERROR_Vout2
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_vout2.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_vout2.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_vout2.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusIOUT(void){
	const unsigned char status[8] = {
		STATUS_IOUT_IOUT_OC_FAULT,
		STATUS_IOUT_IOUT_OC_LV_FAULT,
		STATUS_IOUT_IOUT_OC_WARNING,
		STATUS_IOUT_IOUT_UC_FAULT,
		STATUS_IOUT_Current_Share_Fault,
		STATUS_IOUT_In_Power_Limiting_Mode,
		STATUS_IOUT_POUT_OP_FAULT,
		STATUS_IOUT_POUT_OP_WARNING
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbIOUT_OC_FAULT_Iout1,
		m_stbIOUT_OC_LV_FAULT_Iout1,
		m_stbIOUT_OC_WARNING_Iout1,
		m_stbIOUT_UC_FAULT_Iout1,
		m_stbCURRENT_SHARE_FAULT_Iout1,
		m_stbIN_POWER_LIMITING_Iout1,
		m_stbPOUT_OC_FAULT_Iout1,
		m_stbPOUT_OP_WARNING_Iout1
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_iout.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_iout.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_iout.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusIOUT2(void){
	const unsigned char status[8] = {
		STATUS_IOUT_IOUT_OC_FAULT,
		STATUS_IOUT_IOUT_OC_LV_FAULT,
		STATUS_IOUT_IOUT_OC_WARNING,
		STATUS_IOUT_IOUT_UC_FAULT,
		STATUS_IOUT_Current_Share_Fault,
		STATUS_IOUT_In_Power_Limiting_Mode,
		STATUS_IOUT_POUT_OP_FAULT,
		STATUS_IOUT_POUT_OP_WARNING
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbIOUT_OC_FAULT_Iout2,
		m_stbIOUT_OC_LV_FAULT_Iout2,
		m_stbIOUT_OC_WARNING_Iout2,
		m_stbIOUT_UC_FAULT_Iout2,
		m_stbCURRENT_SHARE_FAULT_Iout2,
		m_stbIN_POWER_LIMITING_Iout2,
		m_stbPOUT_OC_FAULT_Iout2,
		m_stbPOUT_OP_WARNING_Iout2
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_iout2.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_iout2.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_iout2.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusTemperature(void){
	const unsigned char status[8] = {
		STATUS_TEMPERATURE_OT_FAULT,
		STATUS_TEMPERATURE_OT_WARNING,
		STATUS_TEMPERATURE_UT_WARNING,
		STATUS_TEMPERATURE_UT_FAULT,
		STATUS_TEMPERATURE_Reserved_3,
		STATUS_TEMPERATURE_Reserved_2,
		STATUS_TEMPERATURE_Reserved_1,
		STATUS_TEMPERATURE_Reserved_0
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbOT_FAULT_Temperature,
		m_stbOT_WARNING_Temperature,
		m_stbUT_WARNING_Temperature,
		m_stbUT_FAULT_Temperature,
		m_stbRESERVED3_Temperature,
		m_stbRESERVED2_Temperature,
		m_stbRESERVED1_Temperature,
		m_stbRESERVED0_Temperature
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_temperature.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_temperature.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_temperature.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusCML(void){
	const unsigned char status[8] = {
		STATUS_CML_Invalid_Or_Unsupported_Command_Received,
		STATUS_CML_Invalid_Or_Unsupported_Data_Received,
		STATUS_CML_Packet_Error_Check_Failed,
		STATUS_CML_Memory_Fault_Detected,
		STATUS_CML_Processor_Fault_Detected,
		STATUS_CML_Reserved,
		STATUS_CML_A_communication_fault,
		STATUS_CML_Other_Memory_Or_Logic_Fault
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbINVALID_COMMAND_CML,
		m_stbINVALID_DATA_CML,
		m_stbPEC_FAILED_CML,
		m_stbMEMORY_FAULT_CML,
		m_stbPROCESSOR_FAULT_CML,
		m_stbRESERVED_CML,
		m_stbCOMMUNICATION_CML,
		m_stbOTHER_MEMORY_CML
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_cml.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_cml.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_cml.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusOTHER(void){
	const unsigned char status[8] = {
		STATUS_OTHER_Reserved_2,
		STATUS_OTHER_Reserved_1,
		STATUS_OTHER_Input_A_Fuse_Or_Circuit_Breaker_Fault,
		STATUS_OTHER_Input_B_Fuse_Or_Circuit_Breaker_Fault,
		STATUS_OTHER_Input_A_ORing_Device_Fault,
		STATUS_OTHER_Input_B_ORing_Device_Fault,
		STATUS_OTHER_Output_ORing_Device_Fault,
		STATUS_OTHER_Reserved_0
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbRESERVED7_OTHER,
		m_stbRESERVED6_OTHER,
		m_stbINPUT_A_FUSE_FAULT_OTHER,
		m_stbINPUT_B_FUSE_FAULT_OTHER,
		m_stbINPUT_A_ORING_FAULT_OTHER,
		m_stbINPUT_B_ORING_FAULT_OTHER,
		m_stbOUTPUT_ORING_FAULT_OTHER,
		m_stbRESERVED_OTHER
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_other.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_other.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_other.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}

void PMBUSStatusDCHPanel::Update_StatusFAN12(void){
	const unsigned char status[8] = {
		STATUS_FAN_1_2_Fan_1_Fault,
		STATUS_FAN_1_2_Fan_2_Fault,
		STATUS_FAN_1_2_Fan_1_Warning,
		STATUS_FAN_1_2_Fan_2_Warning,
		STATUS_FAN_1_2_Fan_1_Speed_Overridden,
		STATUS_FAN_1_2_Fan_2_Speed_Overridden,
		STATUS_FAN_1_2_Airflow_Fault,
		STATUS_FAN_1_2_Airflow_Warning
	};

	wxStaticBitmap *sbArray[8] = {
		m_stbFAN_1_FAULT_FAN12,
		m_stbFAN_2_FAULT_FAN12,
		m_stbFAN_1_WARNING_FAN12,
		m_stbFAN_2_WARNING_FAN12,
		m_stbFAN_1_SPEED_OVERRIDDEN_FAN12,
		m_stbFAN_2_SPEED_OVERRIDDEN_FAN12,
		m_stbAIRFLOW_FAULT_FAN12,
		m_stbAIRFLOW_WARNING_OTHER
	};

	if (PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status_dch == PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.previous_status_dch) { return; }

	for (unsigned int idx = 0; idx < 8; idx++){
		if ((PMBUSHelper::GetPMBusStatus()->m_status_fan_1_2.status_dch & status[idx]) == status[idx]) {
			sbArray[idx]->SetBitmap(*m_red);
		}
		else{
			sbArray[idx]->SetBitmap(*m_green);
		}
	}
}
