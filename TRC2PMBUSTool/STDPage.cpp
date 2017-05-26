/**
 * @file STDPage.cpp
 */

#include "STDPage.h"

#define PADDING_DEFAULT_WIDTH  50
#define PADDING_DEFAULT_HEIGHT 10

#define TEXT_DEFAULT_WIDTH  50
#define TEXT_DEFAULT_HEIGHT 20

#define TEXTCTRL_DEFAULT_WIDTH  70
#define TEXTCTRL_DEFAULT_HEIGHT 20

STDPage::STDPage(wxWindow* parent) : wxPanel(parent){
	// Set Parent
	this->m_parent = parent;
	
	// Initial Static Box
	m_staticBox = new wxStaticBox(this, wxID_ANY, wxString("Real-Time Data"));
	
	// Initial Sizer 
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_staticBoxlSizer = new wxStaticBoxSizer(this->m_staticBox,wxVERTICAL);

	m_gridSizer_1 = new wxGridSizer(4, 4, 3, 3);
	m_gridSizer_2 = new wxGridSizer(4, 4, 3, 3);

	m_horizonSizer1 = new wxBoxSizer(wxHORIZONTAL);

	// Initial Padding Static Text
	m_stPadding_1 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	m_stPadding_2 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	m_stPadding_3 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	m_stPadding_4 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	m_stPadding_5 = new wxStaticText(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));

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
	wxColour TCInitColor = wxColour(157, 216, 140);

	m_tcPIN = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcPIN->SetBackgroundColour(TCInitColor);
	m_tcPOUT = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcPOUT->SetBackgroundColour(TCInitColor);
	m_tcVIN = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcVIN->SetBackgroundColour(TCInitColor);
	m_tcIIN = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcIIN->SetBackgroundColour(TCInitColor);
	m_tcVOUT = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcVOUT->SetBackgroundColour(TCInitColor);
	m_tcIOUT = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcIOUT->SetBackgroundColour(TCInitColor);
	m_tcVoSBY = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcVoSBY->SetBackgroundColour(TCInitColor);
	m_tcIoSBY = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcIoSBY->SetBackgroundColour(TCInitColor);

	m_tcVCAP = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcVCAP->SetBackgroundColour(TCInitColor);
	m_tcAMD8D = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcAMD8D->SetBackgroundColour(TCInitColor);
	m_tcSEC8E = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcSEC8E->SetBackgroundColour(TCInitColor);
	m_tcPRI8F = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcPRI8F->SetBackgroundColour(TCInitColor);
	m_tcFAN1 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcFAN1->SetBackgroundColour(TCInitColor);
	m_tcFAN2 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcFAN2->SetBackgroundColour(TCInitColor);
	m_tcFAN3 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcFAN3->SetBackgroundColour(TCInitColor);
	m_tcFAN4 = new wxTextCtrl(this->m_staticBoxlSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(TEXTCTRL_DEFAULT_WIDTH, TEXTCTRL_DEFAULT_HEIGHT), wxTE_READONLY | wxTE_CENTER);
	m_tcFAN4->SetBackgroundColour(TCInitColor);

	// Add Component to Sizer
	m_gridSizer_1->Add(m_stPIN);
	m_gridSizer_1->Add(m_tcPIN);
	m_gridSizer_1->Add(m_stPOUT);
	m_gridSizer_1->Add(m_tcPOUT);
	
	m_gridSizer_1->Add(m_stVIN);
	m_gridSizer_1->Add(m_tcVIN);
	m_gridSizer_1->Add(m_stIIN);
	m_gridSizer_1->Add(m_tcIIN);

	m_gridSizer_1->Add(m_stVOUT);
	m_gridSizer_1->Add(m_tcVOUT);
	m_gridSizer_1->Add(m_stIOUT);
	m_gridSizer_1->Add(m_tcIOUT);

	m_gridSizer_1->Add(m_stVoSBY);
	m_gridSizer_1->Add(m_tcVoSBY);
	m_gridSizer_1->Add(m_stIoSBY);
	m_gridSizer_1->Add(m_tcIoSBY);

	m_gridSizer_2->Add(m_stVCAP);
	m_gridSizer_2->Add(m_tcVCAP);
	m_gridSizer_2->Add(m_stAMD8D);
	m_gridSizer_2->Add(m_tcAMD8D);

	m_gridSizer_2->Add(m_stSEC8E);
	m_gridSizer_2->Add(m_tcSEC8E);
	m_gridSizer_2->Add(m_stPRI8F);
	m_gridSizer_2->Add(m_tcPRI8F);

	m_gridSizer_2->Add(m_stFAN1);
	m_gridSizer_2->Add(m_tcFAN1);
	m_gridSizer_2->Add(m_stFAN2);
	m_gridSizer_2->Add(m_tcFAN2);

	m_gridSizer_2->Add(m_stFAN3);
	m_gridSizer_2->Add(m_tcFAN3);
	m_gridSizer_2->Add(m_stFAN4);
	m_gridSizer_2->Add(m_tcFAN4);


	//this->m_horizonSizer1->Add(m_stPage);
	//this->m_horizonSizer1->Add(m_comboBox);

	m_staticBoxlSizer->Add(m_horizonSizer1);

	m_staticBoxlSizer->Add(m_stPadding_1);// Padding Static Text

	m_staticBoxlSizer->Add(m_staticLine_1, wxSizerFlags().Expand());

	m_staticBoxlSizer->Add(m_stPadding_2);// Padding Static Text

	m_staticBoxlSizer->Add(m_gridSizer_1, wxSizerFlags(1).Expand());

	m_staticBoxlSizer->Add(m_stPadding_3);// Padding Static Text

	m_staticBoxlSizer->Add(m_staticLine_2, wxSizerFlags().Expand());

	m_staticBoxlSizer->Add(m_stPadding_4);// Padding Static Text

	m_staticBoxlSizer->Add(m_gridSizer_2, wxSizerFlags(1).Expand());

	m_staticBoxlSizer->Add(m_stPadding_5);// Padding Static Text

	m_staticBoxlSizer->Add(m_staticLine_3, wxSizerFlags().Expand());
	
	// Add Sizer To Top Level Sizer
	m_topLevelSizer->Add(m_staticBoxlSizer, wxSizerFlags(1).Expand());

	// Setup Sizer
	SetSizer(m_topLevelSizer);
}

STDPage::~STDPage(){

};