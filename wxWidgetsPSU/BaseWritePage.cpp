/**
 * @file WritePage.cpp
 */

#include "BaseWritePage.h"

BaseWritePage::BaseWritePage(wxWindow* parent, wxString& label) : wxPanel(parent) {

	// Set Parent
	this->m_parent = parent;

	// Set Label
	this->m_Label = label;

	// Base LayOut
	this->BaseLayOut();

	// Setup Validator
	this->SetupValidator();

	// Set Background Color
	this->SetBackgroundColour(wxColour(248,168,133));
}


BaseWritePage::~BaseWritePage(){

}

void BaseWritePage::BaseLayOut(void){
	// Initial Static Box
	m_staticBox = new wxStaticBox(this, wxID_ANY, this->m_Label);

	// Initial Sizer 
	m_staticBoxlSizer = new wxStaticBoxSizer(this->m_staticBox, wxVERTICAL);
	m_horizonSizer1 = new wxBoxSizer(wxHORIZONTAL);

	// Initialize Radio Button
	this->m_cookRadioButton = new wxRadioButton(this, CID_RADIO_BOX_COOK, L"cook", wxDefaultPosition, wxSize(75, -1));
	this->m_rawRadioButton = new wxRadioButton(this, CID_RADIO_BOX_RAW, L"raw", wxDefaultPosition, wxSize(75, -1));

	// Initial Button
	this->m_writeButton = new wxButton(this, CID_BUTTON_WRITE, L"Write");

	// Initial Padding Static Text
	m_stPadding_1 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	m_stPadding_2 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));

	// Initail Static Line
	m_staticLine_1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(280, -1));

	// Add Component To Sizer
	m_horizonSizer1->Add(this->m_cookRadioButton, 0, wxALIGN_CENTER_VERTICAL);

	m_horizonSizer1->Add(this->m_rawRadioButton, 0, wxALIGN_CENTER_VERTICAL);

	m_horizonSizer1->Add(this->m_writeButton, 0, wxALIGN_CENTER_VERTICAL);

	m_staticBoxlSizer->Add(m_horizonSizer1);

	m_staticBoxlSizer->Add(m_stPadding_1);

	m_staticBoxlSizer->Add(m_staticLine_1);

	m_staticBoxlSizer->Add(m_stPadding_2);

	SetSizer(m_staticBoxlSizer);
}

void BaseWritePage::SetupValidator(void){
	DecimalCharIncludes = wxT("0123456789");
	m_numberValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_numberValidator.SetCharIncludes(DecimalCharIncludes);

	HexCharIncludes = wxT("0123456789abcdef");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);
}