/**
 * @file BaseWritePage.cpp
 */

#include "BaseWritePage.h"

BaseWritePage::BaseWritePage(wxWindow* parent, wxString& label) : wxPanel(parent) {

	// Set Parent
	this->m_parent = parent;

	// Set Label
	this->m_Label = label;

	// Data Format
	this->m_dataFormat = cmd_data_format_LinearData_Format;

	// Base LayOut
	this->BaseLayOut();

	// Setup Validator
	this->SetupValidator();

	// Set Background Color
	this->SetBackgroundColour(wxColour(248, 168, 133));//255, 94, 25

	// Set Coifficients Static Text
	this->m_coefficientsST = NULL;

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
	this->m_cookRadioButton = new wxRadioButton(this, CID_RADIO_BOX_COOK, L"decimal", wxDefaultPosition, wxSize(75, -1));
	this->m_rawRadioButton = new wxRadioButton(this, CID_RADIO_BOX_RAW, L"hex", wxDefaultPosition, wxSize(75, -1));

	// Initial Button
	this->m_writeButton = new wxButton(this, CID_BUTTON_WRITE, L"Write");

	// Initial Padding Static Text
	m_stPadding_WriteButton = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(30, PADDING_DEFAULT_HEIGHT));

	m_stPadding_1 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));
	m_stPadding_2 = new wxStaticText(this, wxID_ANY, wxString(" "), wxDefaultPosition, wxSize(PADDING_DEFAULT_WIDTH, PADDING_DEFAULT_HEIGHT));

	// Initail Static Line
	m_staticLine_1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(280, -1));

	// Add Component To Sizer
	m_horizonSizer1->Add(this->m_cookRadioButton, wxSizerFlags(0).Border());//0, wxALIGN_CENTER_VERTICAL);

	m_horizonSizer1->Add(this->m_rawRadioButton, wxSizerFlags(0).Border());//0, wxALIGN_CENTER_VERTICAL);

	m_horizonSizer1->Add(this->m_stPadding_WriteButton, wxSizerFlags(0).Expand().Border());

	m_horizonSizer1->Add(this->m_writeButton, wxSizerFlags(1).Align(wxALIGN_CENTER_VERTICAL));

	m_staticBoxlSizer->Add(m_horizonSizer1, wxSizerFlags(0).Expand());

	m_staticBoxlSizer->Add(m_stPadding_1);

	m_staticBoxlSizer->Add(m_staticLine_1, wxSizerFlags(0).Expand());

	m_staticBoxlSizer->Add(m_stPadding_2);

	SetSizer(m_staticBoxlSizer);
}

void BaseWritePage::changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd) {
	PSU_DEBUG_PRINT(MSG_DEBUG, "Base Class")
}

void BaseWritePage::SetupValidator(void){
	DecimalCharIncludes = wxT("0123456789.");
	m_numberValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_numberValidator.SetCharIncludes(DecimalCharIncludes);

	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);
}

wxStaticBox* BaseWritePage::getStaticBox(void){
	return this->m_staticBox;
}

wxBEGIN_EVENT_TABLE(BaseWritePage, wxPanel)
// Empty
wxEND_EVENT_TABLE()