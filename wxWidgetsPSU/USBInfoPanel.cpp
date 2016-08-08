/**
 * @file USBInfoPanel.cpp
 */

#include "USBInfoPanel.h"

#define COMPORT_0_ID wxT("17/1")
#define COMPORT_1_ID wxT("18/2")
#define COMPORT_2_ID wxT("19/3")
#define COMPORT_3_ID wxT("20/4")
#define I2CPORT_ID wxT("21/5")
#define SPIPORT_ID wxT("22/6")
#define CANPORT_ID wxT("23/7")
#define SDQPORT_ID wxT("24/8")
#define GPIO_IN wxT("25/9")
#define GPIO_OUT wxT("26/10")

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
	m_VIDTC->SetEditable(false);
	m_VIDTC->SetBackgroundColour(wxColour(255, 255, 255));

	wxString vid = wxString::Format("%04x", PMBUSHelper::GetUSBInfo()->m_vid);
	m_VIDTC->SetValue(vid);

	m_PIDST = new wxStaticText(this, wxID_ANY, wxT("PID"));
	m_PIDTC = new wxTextCtrl(this, wxID_ANY);
	m_PIDTC->SetEditable(false);
	m_PIDTC->SetBackgroundColour(wxColour(255, 255, 255));

	wxString pid = wxString::Format("%04x", PMBUSHelper::GetUSBInfo()->m_pid);
	m_PIDTC->SetValue(pid);

	m_st1 = new wxStaticLine(this);

	m_horizon1->Add(m_VIDST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon1->Add(m_VIDTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon1->Add(m_PIDST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon1->Add(m_PIDTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));

	/* Section 2 */
	m_comport0IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 0 ID"));
	m_comport0IDTC = new wxTextCtrl(this, wxID_ANY);
	m_comport0IDTC->SetValue(COMPORT_0_ID);
	m_comport0IDTC->SetEditable(false);

	m_comport1IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 1 ID"));
	m_comport1IDTC = new wxTextCtrl(this, wxID_ANY);
	m_comport1IDTC->SetValue(COMPORT_1_ID);
	m_comport1IDTC->SetEditable(false);

	m_comport2IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 2 ID"));
	m_comport2IDTC = new wxTextCtrl(this, wxID_ANY);
	m_comport2IDTC->SetValue(COMPORT_2_ID);
	m_comport2IDTC->SetEditable(false);

	m_comport3IDST = new wxStaticText(this, wxID_ANY, wxT("Com Port 3 ID"));
	m_comport3IDTC = new wxTextCtrl(this, wxID_ANY);
	m_comport3IDTC->SetValue(COMPORT_3_ID);
	m_comport3IDTC->SetEditable(false);

	m_i2cportIDST = new wxStaticText(this, wxID_ANY, wxT("I2C Port ID"));
	m_i2cportIDTC = new wxTextCtrl(this, wxID_ANY);
	m_i2cportIDTC->SetValue(I2CPORT_ID);
	m_i2cportIDTC->SetEditable(false);

	m_spiportIDST = new wxStaticText(this, wxID_ANY, wxT("SPI Port ID"));
	m_spiportIDTC = new wxTextCtrl(this, wxID_ANY);
	m_spiportIDTC->SetValue(SPIPORT_ID);
	m_spiportIDTC->SetEditable(false);

	m_canportIDST = new wxStaticText(this, wxID_ANY, wxT("CAN Port ID"));
	m_canportIDTC = new wxTextCtrl(this, wxID_ANY);
	m_canportIDTC->SetValue(CANPORT_ID);
	m_canportIDTC->SetEditable(false);

	m_sdqportIDST = new wxStaticText(this, wxID_ANY, wxT("SDQ Port ID"));
	m_sdqportIDTC = new wxTextCtrl(this, wxID_ANY);
	m_sdqportIDTC->SetValue(SDQPORT_ID);
	m_sdqportIDTC->SetEditable(false);

	m_gpioInST = new wxStaticText(this, wxID_ANY, wxT("GPIO IN"));
	m_gpioInTC = new wxTextCtrl(this, wxID_ANY);
	m_gpioInTC->SetValue(GPIO_IN);
	m_gpioInTC->SetEditable(false);

	m_gpioOutST = new wxStaticText(this, wxID_ANY, wxT("GPIO OUT"));
	m_gpioOutTC = new wxTextCtrl(this, wxID_ANY);
	m_gpioOutTC->SetValue(GPIO_OUT);
	m_gpioOutTC->SetEditable(false);

	this->m_fgSizer1->Add(m_comport0IDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_comport0IDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_comport1IDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_comport1IDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_comport2IDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_comport2IDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_comport3IDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_comport3IDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_i2cportIDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_i2cportIDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_spiportIDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_spiportIDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_canportIDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_canportIDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_sdqportIDST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_sdqportIDTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_gpioInST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_gpioInTC, wxSizerFlags().Align(wxALIGN_CENTER));

	this->m_fgSizer1->Add(m_gpioOutST, wxSizerFlags().Align(wxALIGN_CENTER));
	this->m_fgSizer1->Add(m_gpioOutTC, wxSizerFlags().Align(wxALIGN_CENTER));

	m_st2 = new wxStaticLine(this);

	/* Section 3 */
	m_VendorIDST = new wxStaticText(this, wxID_ANY, wxT("Vendor ID"));
	m_VendorIDTC = new wxTextCtrl(this, wxID_ANY);
	m_VendorIDTC->SetEditable(false);

	//wxString vid = wxString::Format("%04x",PMBUSHelper::GetUSBInfo()->m_vid);
	m_VendorIDTC->SetValue(vid);

	m_ProductIDST = new wxStaticText(this, wxID_ANY, wxT("Product ID"));
	m_ProductIDTC = new wxTextCtrl(this, wxID_ANY);
	m_ProductIDTC->SetEditable(false);

	//wxString pid = wxString::Format("%04x", PMBUSHelper::GetUSBInfo()->m_pid);
	m_ProductIDTC->SetValue(pid);

	m_VendorNameST = new wxStaticText(this, wxID_ANY, wxT("Vendor Name"), wxDefaultPosition, wxSize(100,-1));
	m_VendorNameTC = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(300, wxDefaultCoord));
	m_VendorNameTC->SetEditable(false);

	wxString vendorName(PMBUSHelper::GetUSBInfo()->m_vendor_name);
	m_VendorNameTC->SetValue(vendorName);

	m_ProductNameST = new wxStaticText(this, wxID_ANY, wxT("Product Name"), wxDefaultPosition, wxSize(100, -1));
	m_ProductNameTC = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(300, wxDefaultCoord));
	m_ProductNameTC->SetEditable(false);

	wxString productName(PMBUSHelper::GetUSBInfo()->m_product_name);
	m_ProductNameTC->SetValue(productName);

	m_versionST = new wxStaticText(this, wxID_ANY, wxT("Version"), wxDefaultPosition, wxSize(100, -1));
	m_versionTC = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(300, wxDefaultCoord));
	m_versionTC->SetEditable(false);

	wxString version = wxString::Format("%04x", PMBUSHelper::GetUSBInfo()->m_release);
	m_versionTC->SetValue(version);

	m_horizon2->Add(m_VendorIDST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon2->Add(m_VendorIDTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon2->Add(m_ProductIDST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon2->Add(m_ProductIDTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));

	m_horizon3->Add(m_VendorNameST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon3->Add(m_VendorNameTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));

	m_horizon4->Add(m_ProductNameST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon4->Add(m_ProductNameTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));

	m_horizon5->Add(m_versionST, wxSizerFlags().Border().Align(wxALIGN_CENTER));
	m_horizon5->Add(m_versionTC, wxSizerFlags().Border().Align(wxALIGN_CENTER));

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