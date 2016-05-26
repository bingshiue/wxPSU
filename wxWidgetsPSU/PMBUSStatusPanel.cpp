/**
 * @file PMBusStatusPanel.cpp
 */

#include "PMBUSStatusPanel.h"
#include "green.xpm"
#include "red.xpm"

PMBUSStatusPanel::PMBUSStatusPanel(wxWindow* parent) : wxPanel(parent) {
	// Load Bitmap
	m_green = new wxBitmap(green_xpm);
	m_red = new wxBitmap(red_xpm);

	// Status_WORD
	this->m_statusWordSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_WORD"));
	this->m_statusWord_GS_1 = new wxGridSizer(2, 4, 5, 5);
	this->m_statusWord_GS_2 = new wxGridSizer(2, 4, 5, 5);

	this->m_statusWord_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_statusWord_HS_9  = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_10 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_11 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_12 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_13 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_14 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_15 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusWord_HS_16 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbBUSY = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOFF = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_OV_FAULT = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUT_OC_FAULT = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_UV_FAULT = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTEMPERATURE = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbCML = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbNONE_OF_THE_ABOVE = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);

	this->m_stbVOUT = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIOUTPOUT = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbINPUT = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbMFR_SPECIFIC = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPOWER_GOOD = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbFANS = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbOTHER = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbUNKNOW = new wxStaticBitmap(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stBUSY = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("BUSY(MSB)"));
	m_stOFF = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("OFF"));
	m_stVOUT_OV_FAULT = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_FAULT"));
	m_stIOUT_OC_FAULT = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("IOUT_OC_FAULT"));
	m_stVIN_UV_FAULT = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("VIN_UV_FAULT"));
	m_stTEMPERATURE = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("TEMPERATURE"));
	m_stCML = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("CML"));
	m_stNONE_OF_THE_ABOVE = new wxStaticText(this, wxID_ANY, wxT("NONE_OF_THE_ABOVE(LSB)"));

	m_stVOUT = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("VOUT(MSB)"));
	m_stIOUTPOUT = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("IOUT/POUT"));
	m_stINPUT = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("INPUT"));
	m_stMFR_SPECIFIC = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("MFR_SPECIFIC"));
	m_stPOWER_GOOD = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("POWER_GOOD"));
	m_stFANS = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("FANS"));
	m_stOTHER = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("OTHER"));
	m_stUNKNOW = new wxStaticText(this->m_statusWordSBS->GetStaticBox(), wxID_ANY, wxT("UNKNOW(LSB)"));
	                                          

	m_statusWord_HS_1->Add(m_stbBUSY,0,wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_1->Add(m_stBUSY, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_2->Add(m_stbOFF, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_2->Add(m_stOFF, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_3->Add(m_stbVOUT_OV_FAULT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_3->Add(m_stVOUT_OV_FAULT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_4->Add(m_stbIOUT_OC_FAULT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_4->Add(m_stIOUT_OC_FAULT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_5->Add(m_stbVIN_UV_FAULT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_5->Add(m_stVIN_UV_FAULT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_6->Add(m_stbTEMPERATURE, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_6->Add(m_stTEMPERATURE, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_7->Add(m_stbCML, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_7->Add(m_stCML, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_8->Add(m_stbNONE_OF_THE_ABOVE, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_8->Add(m_stNONE_OF_THE_ABOVE, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_9->Add(m_stbVOUT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_9->Add(m_stVOUT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_10->Add(m_stbIOUTPOUT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_10->Add(m_stIOUTPOUT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_11->Add(m_stbINPUT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_11->Add(m_stINPUT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_12->Add(m_stbMFR_SPECIFIC, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_12->Add(m_stMFR_SPECIFIC, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_13->Add(m_stbPOWER_GOOD, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_13->Add(m_stPOWER_GOOD, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_14->Add(m_stbFANS, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_14->Add(m_stFANS, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_15->Add(m_stbOTHER, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_15->Add(m_stOTHER, 0, wxALIGN_CENTER_VERTICAL);

	m_statusWord_HS_16->Add(m_stbUNKNOW, 0, wxALIGN_CENTER_VERTICAL);
	m_statusWord_HS_16->Add(m_stUNKNOW, 0, wxALIGN_CENTER_VERTICAL);

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

	m_statusWord_sl = new wxStaticLine(this->m_statusWordSBS->GetStaticBox(),wxID_ANY, wxDefaultPosition, wxSize(200,-1));

	m_statusWordSBS->AddSpacer(5);

	m_statusWordSBS->Add(m_statusWord_sl, wxSizerFlags(0).Expand());

	m_statusWordSBS->AddSpacer(5);

	m_statusWordSBS->Add(m_statusWord_GS_2, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */

	// Status_INPUT
	this->m_statusInputSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_INPUT"));
	//m_statusInputSBS->GetStaticBox()->SetFont(wxFont(wxSWISS_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	this->m_statusInput_GS_1 = new wxGridSizer(2, 4, 5, 5);

	this->m_statusInput_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusInput_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbVIN_OV_FAULT = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_OV_WARNING = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_UV_WARNING = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVIN_UV_FAULT_Input = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbUNIT_OFF = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIIN_OC_FAULT = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbIIN_OC_WARNING = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbPIN_OP_WARNING = new wxStaticBitmap(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stVIN_OV_FAULT = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_OV_FAULT(MSB)"));
	m_stVIN_OV_WARNING = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_OV_WARNING"));
	m_stVIN_UV_WARNING = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_UV_WARNING"));
	m_stVIN_UV_FAULT_2 = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("VIN_UV_FAULT"));
	m_stUNIT_OFF = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("UNIT_OFF"));
	m_stIIN_OC_FAULT = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("IIN_OC_FAULT"));
	m_stIIN_OC_WARNING = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("IIN_OC_WARNING"));
	m_stPIN_OP_WARNING = new wxStaticText(this->m_statusInputSBS->GetStaticBox(), wxID_ANY, wxT("PIN_OP_WARNING(LSB)"));
																							
	m_statusInput_HS_1->Add(m_stbVIN_OV_FAULT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_1->Add(m_stVIN_OV_FAULT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_2->Add(m_stbVIN_OV_WARNING, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_2->Add(m_stVIN_OV_WARNING, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_3->Add(m_stbVIN_UV_WARNING, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_3->Add(m_stVIN_UV_WARNING, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_4->Add(m_stbVIN_UV_FAULT_Input, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_4->Add(m_stVIN_UV_FAULT_2, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_5->Add(m_stbUNIT_OFF, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_5->Add(m_stUNIT_OFF, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_6->Add(m_stbIIN_OC_FAULT, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_6->Add(m_stIIN_OC_FAULT, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_7->Add(m_stbIIN_OC_WARNING, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_7->Add(m_stIIN_OC_WARNING, 0, wxALIGN_CENTER_VERTICAL);

	m_statusInput_HS_8->Add(m_stbPIN_OP_WARNING, 0, wxALIGN_CENTER_VERTICAL);
	m_statusInput_HS_8->Add(m_stPIN_OP_WARNING, 0, wxALIGN_CENTER_VERTICAL);

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

	// Status_VOUT
	this->m_statusVoutSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("STATUS_INPUT"));

	this->m_statusVout_GS_1 = new wxGridSizer(2, 4, 5, 5);

	this->m_statusVout_HS_1 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_2 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_3 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_4 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_5 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_6 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_7 = new wxBoxSizer(wxHORIZONTAL);
	this->m_statusVout_HS_8 = new wxBoxSizer(wxHORIZONTAL);

	this->m_stbVOUT_OV_FAULT_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_OV_WARNING_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_UV_WARNING_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_UV_FAULT_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_MAX_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTON_MAX_FAULT_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbTOFF_MAX_WARNING_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);
	this->m_stbVOUT_TRACKING_ERROR_Vout = new wxStaticBitmap(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, *m_green);

	m_stVOUT_OV_FAULT_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_FAULT(MSB)"));
	m_stVOUT_OV_WARNING_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_OV_WARNING"));
	m_stVOUT_UV_WARNING_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_UV_WARNING"));
	m_stVOUT_UV_FAULT_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_UV_FAULT"));
	m_stVOUT_MAX_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_MAX"));
	m_stTON_MAX_FAULT_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("TON_MAX_FAULT"));
	m_stTOFF_MAX_WARNING_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("TOFF_MAX_WARNING"));
	m_stVOUT_TRACKING_ERROR_Vout = new wxStaticText(this->m_statusVoutSBS->GetStaticBox(), wxID_ANY, wxT("VOUT_TRACKING_ERROR(LSB)"));

	m_statusVout_HS_1->Add(m_stbVOUT_OV_FAULT_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_1->Add(m_stVOUT_OV_FAULT_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_2->Add(m_stbVOUT_OV_WARNING_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_2->Add(m_stVOUT_OV_WARNING_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_3->Add(m_stbVOUT_UV_WARNING_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_3->Add(m_stVOUT_UV_WARNING_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_4->Add(m_stbVOUT_UV_FAULT_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_4->Add(m_stVOUT_UV_FAULT_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_5->Add(m_stbVOUT_MAX_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_5->Add(m_stVOUT_MAX_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_6->Add(m_stbTON_MAX_FAULT_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_6->Add(m_stTON_MAX_FAULT_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_7->Add(m_stbTOFF_MAX_WARNING_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_7->Add(m_stTOFF_MAX_WARNING_Vout, 0, wxALIGN_CENTER_VERTICAL);

	m_statusVout_HS_8->Add(m_stbVOUT_TRACKING_ERROR_Vout, 0, wxALIGN_CENTER_VERTICAL);
	m_statusVout_HS_8->Add(m_stVOUT_TRACKING_ERROR_Vout, 0, wxALIGN_CENTER_VERTICAL);

	this->m_statusVout_GS_1->Add(m_statusVout_HS_1);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_2);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_3);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_4);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_5);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_6);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_7);
	this->m_statusVout_GS_1->Add(m_statusVout_HS_8);

	m_statusVoutSBS->Add(m_statusVout_GS_1, wxSizerFlags(1).Expand().Border(wxALL, 0));

	/* ------------------------------------------------------------------------------ */


	// Status_IOUT


	/* ------------------------------------------------------------------------------ */

	// Status_TEMPERATURE


	/* ------------------------------------------------------------------------------ */

	// Status_CML


	/* ------------------------------------------------------------------------------ */

	// Status_OTHER


	/* ------------------------------------------------------------------------------ */

	// Add Components in Top Level Sizer
	this->m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	this->m_topLevelSizer->Add(m_statusWordSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusInputSBS, wxSizerFlags(0).Expand());
	this->m_topLevelSizer->Add(m_statusVoutSBS, wxSizerFlags(0).Expand());

	SetSizer(this->m_topLevelSizer);
}

PMBUSStatusPanel::~PMBUSStatusPanel(){

}