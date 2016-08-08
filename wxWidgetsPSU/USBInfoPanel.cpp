/**
 * @file USBInfoPanel.cpp
 */

#include "USBInfoPanel.h"

USBInfoPanel::USBInfoPanel(wxWindow* parent) : wxPanel(parent){

	/* Initial Sizer */
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_horizon1 = new wxBoxSizer(wxHORIZONTAL);
	m_fgSizer1 = new wxFlexGridSizer(5, 4, 5, 5);
	m_horizon2 = new wxBoxSizer(wxHORIZONTAL);
	m_horizon3 = new wxBoxSizer(wxHORIZONTAL);
	m_horizon4 = new wxBoxSizer(wxHORIZONTAL);
	m_horizon5 = new wxBoxSizer(wxHORIZONTAL);

	/* Section 1 */
	m_VIDST = new wxStaticText(this, wxID_ANY, wxT("VID"));
	m_VIDTC = new wxTextCtrl(this, wxID_ANY);

	m_PIDST = new wxStaticText(this, wxID_ANY, wxT("PID"));
	m_PIDTC = new wxTextCtrl(this, wxID_ANY);

	m_st1 = new wxStaticLine(this);

	m_horizon1->Add(m_VIDST, wxSizerFlags().Border());
	m_horizon1->Add(m_VIDTC, wxSizerFlags().Border());
	m_horizon1->Add(m_PIDST, wxSizerFlags().Border());
	m_horizon1->Add(m_PIDTC, wxSizerFlags().Border());

	/* Section 2 */
	m_comport0IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 0 ID"));
	m_comport0IDTC = new wxTextCtrl(this, wxID_ANY);

	m_comport1IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 1 ID"));
	m_comport1IDTC = new wxTextCtrl(this, wxID_ANY);

	m_comport2IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 2 ID"));
	m_comport2IDTC = new wxTextCtrl(this, wxID_ANY);

	m_comport3IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 3 ID"));
	m_comport3IDTC = new wxTextCtrl(this, wxID_ANY);

	m_i2cportIDST = new wxStaticText(this, wxID_ANY, wxT("I2C Port ID"));
	m_i2cportIDTC = new wxTextCtrl(this, wxID_ANY);

	m_spiportIDST = new wxStaticText(this, wxID_ANY, wxT("SPI Port ID"));
	m_spiportIDTC = new wxTextCtrl(this, wxID_ANY);

	m_canportIDST = new wxStaticText(this, wxID_ANY, wxT("CAN Port ID"));
	m_canportIDTC = new wxTextCtrl(this, wxID_ANY);

	m_sdqportIDST = new wxStaticText(this, wxID_ANY, wxT("SDQ Port ID"));
	m_sdqportIDTC = new wxTextCtrl(this, wxID_ANY);

	m_gpioInST = new wxStaticText(this, wxID_ANY, wxT("GPIO IN"));
	m_gpioInTC = new wxTextCtrl(this, wxID_ANY);

	m_gpioOutST = new wxStaticText(this, wxID_ANY, wxT("GPIO OUT"));
	m_gpioOutTC = new wxTextCtrl(this, wxID_ANY);

	this->m_fgSizer1->Add(m_comport0IDST);
	this->m_fgSizer1->Add(m_comport0IDTC);

	this->m_fgSizer1->Add(m_comport1IDST);
	this->m_fgSizer1->Add(m_comport1IDTC);

	this->m_fgSizer1->Add(m_comport2IDST);
	this->m_fgSizer1->Add(m_comport2IDTC);

	this->m_fgSizer1->Add(m_comport3IDST);
	this->m_fgSizer1->Add(m_comport3IDTC);

	this->m_fgSizer1->Add(m_i2cportIDST);
	this->m_fgSizer1->Add(m_i2cportIDTC);

	this->m_fgSizer1->Add(m_spiportIDST);
	this->m_fgSizer1->Add(m_spiportIDTC);

	this->m_fgSizer1->Add(m_canportIDST);
	this->m_fgSizer1->Add(m_canportIDTC);

	this->m_fgSizer1->Add(m_sdqportIDST);
	this->m_fgSizer1->Add(m_sdqportIDTC);

	this->m_fgSizer1->Add(m_gpioInST);
	this->m_fgSizer1->Add(m_gpioInTC);

	this->m_fgSizer1->Add(m_gpioOutST);
	this->m_fgSizer1->Add(m_gpioOutTC);

	m_st2 = new wxStaticLine(this);

	/* Section 3 */
	m_VendorIDST = new wxStaticText(this, wxID_ANY, wxT("Vendor ID"));
	m_VendorIDTC = new wxTextCtrl(this, wxID_ANY);

	m_ProductIDST = new wxStaticText(this, wxID_ANY, wxT("Product ID"));
	m_ProductIDTC = new wxTextCtrl(this, wxID_ANY);

	m_VendorNameST = new wxStaticText(this, wxID_ANY, wxT("Vendor Name"), wxDefaultPosition, wxSize(100,-1));
	m_VendorNameTC = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(300, wxDefaultCoord));

	m_ProductNameST = new wxStaticText(this, wxID_ANY, wxT("Product Name"), wxDefaultPosition, wxSize(100, -1));
	m_ProductNameTC = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(300, wxDefaultCoord));

	m_versionST = new wxStaticText(this, wxID_ANY, wxT("Version"), wxDefaultPosition, wxSize(100, -1));
	m_versionTC = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(300, wxDefaultCoord));

	m_horizon2->Add(m_VendorIDST, wxSizerFlags().Border());
	m_horizon2->Add(m_VendorIDTC, wxSizerFlags().Border());
	m_horizon2->Add(m_ProductIDST, wxSizerFlags().Border());
	m_horizon2->Add(m_ProductIDTC, wxSizerFlags().Border());

	m_horizon3->Add(m_VendorNameST, wxSizerFlags().Border());
	m_horizon3->Add(m_VendorNameTC, wxSizerFlags().Border());

	m_horizon4->Add(m_ProductNameST, wxSizerFlags().Border());
	m_horizon4->Add(m_ProductNameTC, wxSizerFlags().Border());

	m_horizon5->Add(m_versionST, wxSizerFlags().Border());
	m_horizon5->Add(m_versionTC, wxSizerFlags().Border());

	m_st3 = new wxStaticLine(this);

	/* Add element to topLevelSizer */
	m_topLevelSizer->Add(m_horizon1);
	m_topLevelSizer->Add(m_st1, wxSizerFlags().Expand().Border());

	m_topLevelSizer->Add(this->m_fgSizer1);
	m_topLevelSizer->Add(m_st2, wxSizerFlags().Expand().Border());

	m_topLevelSizer->Add(m_horizon2);
	m_topLevelSizer->Add(m_horizon3);
	m_topLevelSizer->Add(m_horizon4);
	m_topLevelSizer->Add(m_horizon5);

	m_topLevelSizer->Add(m_st3, wxSizerFlags().Expand().Border());

	this->SetSizerAndFit(m_topLevelSizer);
}

USBInfoPanel::~USBInfoPanel(){

}

wxBEGIN_EVENT_TABLE(USBInfoPanel, wxPanel)

wxEND_EVENT_TABLE()