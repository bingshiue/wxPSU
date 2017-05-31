/**
 * @file STDPage.cpp
 */

#include "STDPage.h"

#define PADDING_DEFAULT_WIDTH  50
#define PADDING_DEFAULT_HEIGHT  2

#define TEXT_DEFAULT_WIDTH  50
#define TEXT_DEFAULT_HEIGHT -1

#define TEXTCTRL_DEFAULT_WIDTH  75
#define TEXTCTRL_DEFAULT_HEIGHT 20

STDPage::STDPage(wxWindow* parent) : wxPanel(parent){
	// Set Parent
	this->m_parent = parent;
	
	// Initial Static Box
	m_staticBox = new wxStaticBox(this, wxID_ANY, wxString("Real-Time Data"));
	
	// Initial Sizer 
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_staticBoxlSizer = new wxStaticBoxSizer(this->m_staticBox,wxVERTICAL);

	m_flexGridSizer_1 = new wxFlexGridSizer(4, 4, 3, 3);
	m_flexGridSizer_2 = new wxFlexGridSizer(4, 4, 3, 3);

	m_flexGridSizer_1->SetFlexibleDirection(wxHORIZONTAL);
	m_flexGridSizer_2->SetFlexibleDirection(wxHORIZONTAL);

	m_flexGridSizer_1->AddGrowableCol(0);
	m_flexGridSizer_1->AddGrowableCol(1);
	m_flexGridSizer_1->AddGrowableCol(2);
	m_flexGridSizer_1->AddGrowableCol(3);

	m_flexGridSizer_2->AddGrowableCol(0);
	m_flexGridSizer_2->AddGrowableCol(1);
	m_flexGridSizer_2->AddGrowableCol(2);
	m_flexGridSizer_2->AddGrowableCol(3);

	//m_horizonSizer1 = new wxBoxSizer(wxHORIZONTAL);

	// Initial Padding Static Text
	//m_stPadding_1 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	//m_stPadding_2 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	//m_stPadding_3 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	//m_stPadding_4 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	//m_stPadding_5 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));

	// Initial Combo Box
	//m_stPage = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("Page"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));

	//m_comboBox = new wxComboBox(this->m_staticBoxlSizer->GetStaticBox(), PAGE_SELECT_COMBO, wxEmptyString, wxDefaultPosition, wxSize(100, -1));
	//m_comboBox->Append(wxT("0"));
	//m_comboBox->Append(wxT("1"));
	//m_comboBox->Append(wxT("2"));
	//m_comboBox->Append(wxT("3"));
	//m_comboBox->Append(wxT("4"));
	//m_comboBox->Append(wxT("5"));

	//m_comboBox->SetSelection(0);
	//m_comboBox->Enable(false);

	// Initail Static Line
	m_staticLine_1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition);
	m_staticLine_2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition);
	m_staticLine_3 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition);
	
	// Initail Static Text
	m_stPIN = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("PIN"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stPOUT = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("POUT"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stVIN = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("VIN"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stIIN = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("IIN"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stVOUT = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("VOUT"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stIOUT = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("IOUT"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stVoSBY = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("VoSBY"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stIoSBY = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("IoSBY"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));

	m_stVCAP = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("VCAP"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stAMD8D = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("AMB(8D)"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stSEC8E = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("SEC(8E)"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stPRI8F = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("PRI(8F)"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stFAN1 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("FAN1"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stFAN2 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("FAN2"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stFAN3 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("FAN3"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));
	m_stFAN4 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString("FAN4"), wxDefaultPosition, wxSize(TEXT_DEFAULT_WIDTH, TEXT_DEFAULT_HEIGHT));

	// Initail TextCtrl 
	wxColour TCInitColor = wxColour( 183, 196, 222 );// R:183 G:196 B:222 (Mizuiro)

	wxFont tcFont(wxNORMAL_FONT->GetPointSize() + 3, wxFONTFAMILY_DECORATIVE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	m_tcPIN = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcPIN->SetBackgroundColour(TCInitColor);
	m_tcPIN->SetFont(tcFont);
	m_tcPOUT = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcPOUT->SetBackgroundColour(TCInitColor);
	m_tcPOUT->SetFont(tcFont);
	m_tcVIN = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcVIN->SetBackgroundColour(TCInitColor);
	m_tcVIN->SetFont(tcFont);
	m_tcIIN = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcIIN->SetBackgroundColour(TCInitColor);
	m_tcIIN->SetFont(tcFont);
	m_tcVOUT = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcVOUT->SetBackgroundColour(TCInitColor);
	m_tcVOUT->SetFont(tcFont);
	m_tcIOUT = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcIOUT->SetBackgroundColour(TCInitColor);
	m_tcIOUT->SetFont(tcFont);
	m_tcVoSBY = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcVoSBY->SetBackgroundColour(TCInitColor);
	m_tcVoSBY->SetFont(tcFont);
	m_tcIoSBY = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcIoSBY->SetBackgroundColour(TCInitColor);
	m_tcIoSBY->SetFont(tcFont);

	m_tcVCAP = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcVCAP->SetBackgroundColour(TCInitColor);
	m_tcVCAP->SetFont(tcFont);
	m_tcAMD8D = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcAMD8D->SetBackgroundColour(TCInitColor);
	m_tcAMD8D->SetFont(tcFont);
	m_tcSEC8E = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcSEC8E->SetBackgroundColour(TCInitColor);
	m_tcSEC8E->SetFont(tcFont);
	m_tcPRI8F = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcPRI8F->SetBackgroundColour(TCInitColor);
	m_tcPRI8F->SetFont(tcFont);
	m_tcFAN1 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcFAN1->SetBackgroundColour(TCInitColor);
	m_tcFAN1->SetFont(tcFont);
	m_tcFAN2 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcFAN2->SetBackgroundColour(TCInitColor);
	m_tcFAN2->SetFont(tcFont);
	m_tcFAN3 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcFAN3->SetBackgroundColour(TCInitColor);
	m_tcFAN3->SetFont(tcFont);
	m_tcFAN4 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER | wxBORDER_NONE);
	m_tcFAN4->SetBackgroundColour(TCInitColor);
	m_tcFAN4->SetFont(tcFont);

	// Add Component to Sizer
	m_flexGridSizer_1->Add(m_stPIN, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcPIN, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_stPOUT, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcPOUT, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	
	m_flexGridSizer_1->Add(m_stVIN, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcVIN, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_stIIN, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcIIN, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());

	m_flexGridSizer_1->Add(m_stVOUT, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcVOUT, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_stIOUT, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcIOUT, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());

	m_flexGridSizer_1->Add(m_stVoSBY, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcVoSBY, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_stIoSBY, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_1->Add(m_tcIoSBY, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());

	m_flexGridSizer_2->Add(m_stVCAP, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcVCAP, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_stAMD8D, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcAMD8D, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());

	m_flexGridSizer_2->Add(m_stSEC8E, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcSEC8E, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_stPRI8F, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcPRI8F, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());

	m_flexGridSizer_2->Add(m_stFAN1, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcFAN1, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_stFAN2, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcFAN2, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());

	m_flexGridSizer_2->Add(m_stFAN3, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcFAN3, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_stFAN4, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());
	m_flexGridSizer_2->Add(m_tcFAN4, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Expand());


	//this->m_horizonSizer1->Add(m_stPage);
	//this->m_horizonSizer1->Add(m_comboBox);

	//m_staticBoxlSizer->Add(m_horizonSizer1, wxSizerFlags().Expand());

	//m_staticBoxlSizer->Add(m_stPadding_1, wxSizerFlags(1).Expand());// Padding Static Text

	m_staticBoxlSizer->Add(m_staticLine_1, wxSizerFlags(0).Expand().Border(wxALL, 5));

	//m_staticBoxlSizer->Add(m_stPadding_2, wxSizerFlags(0).Expand());// Padding Static Text

	m_staticBoxlSizer->Add(m_flexGridSizer_1, wxSizerFlags(1).Expand());

	//m_staticBoxlSizer->Add(m_stPadding_3, wxSizerFlags(0).Expand());// Padding Static Text

	m_staticBoxlSizer->Add(m_staticLine_2, wxSizerFlags(0).Expand().Border(wxALL, 5));

	//m_staticBoxlSizer->Add(m_stPadding_4, wxSizerFlags(0).Expand());// Padding Static Text

	m_staticBoxlSizer->Add(m_flexGridSizer_2, wxSizerFlags(1).Expand());

	//m_staticBoxlSizer->Add(m_stPadding_5), wxSizerFlags(0).Expand();// Padding Static Text

	m_staticBoxlSizer->Add(m_staticLine_3, wxSizerFlags(0).Expand().Border(wxALL, 5));
	
	// Add Sizer To Top Level Sizer
	m_topLevelSizer->Add(m_staticBoxlSizer, wxSizerFlags(1).Expand());

	// Setup Sizer
	SetSizer(m_topLevelSizer);
}

STDPage::~STDPage(){

};