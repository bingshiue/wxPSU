/**
 * @file PMBUSMFRPanel.cpp
 */

#include "PMBUSMFRPanel.h"

PMBUSMFRPanel::PMBUSMFRPanel(wxWindow* parent) : wxScrolledWindow(parent) {

	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);

	m_upSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT(""));
	m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	m_writeButton = new wxButton(m_upSBS->GetStaticBox(), wxID_ANY, wxT("Write"));
	//m_writeButton->SetBitmap(wxBITMAP(CLEAR));
	m_readButton = new wxButton(m_upSBS->GetStaticBox(), wxID_ANY, wxT("Read"));
	m_verifyButton = new wxButton(m_upSBS->GetStaticBox(), wxID_ANY, wxT("Verify"));

	m_buttonSizer->Add(m_writeButton);
	m_buttonSizer->Add(m_readButton);
	m_buttonSizer->Add(m_verifyButton);

	m_sl = new wxStaticLine(this);

	m_barCodeLabelSNSizer = new wxBoxSizer(wxHORIZONTAL);

	m_barCodeLabelSNST = new wxStaticText(this, wxID_ANY, wxT("Bar-Code Label S/N"), wxDefaultPosition, wxSize(300,-1));
	m_barCodeLabelSNTC = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500,-1));
	m_barCodeLabelSNTC->SetBackgroundColour(wxColour(248, 220, 133));

	m_barCodeLabelSNSizer->Add(m_barCodeLabelSNST);
	m_barCodeLabelSNSizer->Add(m_barCodeLabelSNTC);

	m_upSBS->Add(m_buttonSizer, wxSizerFlags().Border());
	m_upSBS->Add(m_sl, wxSizerFlags().Expand().Border());
	m_upSBS->Add(m_barCodeLabelSNSizer, wxSizerFlags().Border());

	/* ----------------------------------------- */

	m_downSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("MFR Information"));
	m_mfrInfoline1Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_mfrInfoline2Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_mfrInfoline3Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_mfrInfoline4Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_mfrInfoline5Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_mfrInfoline6Sizer = new wxBoxSizer(wxHORIZONTAL);

	m_vendorNameCB = new wxCheckBox(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_vendorNameST = new wxStaticText(m_downSBS->GetStaticBox(), wxID_ANY, wxT("Vendor Name"), wxDefaultPosition, wxSize(285, -1));
	m_vendorNameTC = new wxTextCtrl(m_downSBS->GetStaticBox(), wxID_ANY, wxT("ACBEL"), wxDefaultPosition, wxSize(500, -1));

	m_mfrInfoline1Sizer->Add(m_vendorNameCB, wxSizerFlags().Border(wxRIGHT));
	m_mfrInfoline1Sizer->Add(m_vendorNameST);
	m_mfrInfoline1Sizer->Add(m_vendorNameTC);

	m_vendorPartNumberCB = new wxCheckBox(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_vendorPartNumberST = new wxStaticText(m_downSBS->GetStaticBox(), wxID_ANY, wxT("Vendor Part Number"), wxDefaultPosition, wxSize(285, -1));
	m_vendorPartNumberTC = new wxTextCtrl(m_downSBS->GetStaticBox(), wxID_ANY, wxT("FSF007-000G"), wxDefaultPosition, wxSize(350, -1));

	m_mfrInfoline2Sizer->Add(m_vendorPartNumberCB, wxSizerFlags().Border(wxRIGHT));
	m_mfrInfoline2Sizer->Add(m_vendorPartNumberST);
	m_mfrInfoline2Sizer->Add(m_vendorPartNumberTC);

	m_vendorAssemblyRevisionCB = new wxCheckBox(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_vendorAssemblyRevisionST = new wxStaticText(m_downSBS->GetStaticBox(), wxID_ANY, wxT("Vendor Assembly Revision"), wxDefaultPosition, wxSize(285, -1));
	m_vendorAssemblyRevisionTC = new wxTextCtrl(m_downSBS->GetStaticBox(), wxID_ANY, wxT("A01"), wxDefaultPosition, wxSize(350, -1));

	m_mfrInfoline3Sizer->Add(m_vendorAssemblyRevisionCB, wxSizerFlags().Border(wxRIGHT));
	m_mfrInfoline3Sizer->Add(m_vendorAssemblyRevisionST);
	m_mfrInfoline3Sizer->Add(m_vendorAssemblyRevisionTC);

	m_LocationOfManufactureCB = new wxCheckBox(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_LocationOfManufactureST = new wxStaticText(m_downSBS->GetStaticBox(), wxID_ANY, wxT("Location Of Manufacture"), wxDefaultPosition, wxSize(285, -1));
	m_LocationOfManufactureTC = new wxTextCtrl(m_downSBS->GetStaticBox(), wxID_ANY, wxT("TWN"), wxDefaultPosition, wxSize(500, -1));

	m_mfrInfoline4Sizer->Add(m_LocationOfManufactureCB, wxSizerFlags().Border(wxRIGHT));
	m_mfrInfoline4Sizer->Add(m_LocationOfManufactureST);
	m_mfrInfoline4Sizer->Add(m_LocationOfManufactureTC);

	m_DateOfManufactureCB = new wxCheckBox(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_DateOfManufactureST = new wxStaticText(m_downSBS->GetStaticBox(), wxID_ANY, wxT("Date Of Manufacture"), wxDefaultPosition, wxSize(285, -1));
	m_DateOfManufactureTC = new wxTextCtrl(m_downSBS->GetStaticBox(), wxID_ANY, wxT("160610"), wxDefaultPosition, wxSize(350, -1));

	m_mfrInfoline5Sizer->Add(m_DateOfManufactureCB, wxSizerFlags().Border(wxRIGHT));
	m_mfrInfoline5Sizer->Add(m_DateOfManufactureST);
	m_mfrInfoline5Sizer->Add(m_DateOfManufactureTC);

	m_vendorSerialNumberCB = new wxCheckBox(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_vendorSerialNumberST = new wxStaticText(m_downSBS->GetStaticBox(), wxID_ANY, wxT("Vendor Serial Number"), wxDefaultPosition, wxSize(285, -1));
	m_vendorSerialNumbereTC = new wxTextCtrl(m_downSBS->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, -1));

	m_mfrInfoline6Sizer->Add(m_vendorSerialNumberCB, wxSizerFlags().Border(wxRIGHT));
	m_mfrInfoline6Sizer->Add(m_vendorSerialNumberST);
	m_mfrInfoline6Sizer->Add(m_vendorSerialNumbereTC);


	m_downSBS->Add(m_mfrInfoline1Sizer, wxSizerFlags().Border(wxTOP | wxBOTTOM));
	m_downSBS->Add(m_mfrInfoline2Sizer, wxSizerFlags().Border(wxTOP | wxBOTTOM));
	m_downSBS->Add(m_mfrInfoline3Sizer, wxSizerFlags().Border(wxTOP | wxBOTTOM));
	m_downSBS->Add(m_mfrInfoline4Sizer, wxSizerFlags().Border(wxTOP | wxBOTTOM));
	m_downSBS->Add(m_mfrInfoline5Sizer, wxSizerFlags().Border(wxTOP | wxBOTTOM));
	m_downSBS->Add(m_mfrInfoline6Sizer, wxSizerFlags().Border(wxTOP | wxBOTTOM));

	/* ----------------------------------------- */

	m_topLevelSizer->Add(m_upSBS, wxSizerFlags().Expand());
	m_topLevelSizer->Add(m_downSBS, wxSizerFlags().Expand());

	this->SetSizer(m_topLevelSizer);
		 
}

PMBUSMFRPanel::~PMBUSMFRPanel(){

}

wxBEGIN_EVENT_TABLE(PMBUSMFRPanel, wxScrolledWindow)

wxEND_EVENT_TABLE()