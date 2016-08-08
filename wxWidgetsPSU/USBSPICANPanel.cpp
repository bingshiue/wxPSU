/**
 * @file USBSPICANPanel.cpp
 */

#include "USBSPICANPanel.h"

USBSPICANPanel::USBSPICANPanel(wxWindow* parent) : wxPanel(parent){

	/* Initial Sizer */
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_fgSizer1 = new wxFlexGridSizer(3, 2, 5, 5);
	m_fgSizer2 = new wxFlexGridSizer(4, 2, 5, 5);
	m_spiPortSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("SPI Port"));
	m_canPortSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("CAN Port"));

	/* Section 1 */
	m_spiRecvBuffSizeST = new wxStaticText(m_spiPortSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_spiRecvBuffSizeTC = new wxTextCtrl(m_spiPortSB->GetStaticBox(), wxID_ANY);

	m_spiRecvTimeoutST = new wxStaticText(m_spiPortSB->GetStaticBox(), wxID_ANY, wxT("Received Timeout (ms)"));
	m_spiRecvTimeoutTC = new wxTextCtrl(m_spiPortSB->GetStaticBox(), wxID_ANY);

	m_spiBitRateSpeedST = new wxStaticText(m_spiPortSB->GetStaticBox(), wxID_ANY, wxT("Bit Rate Speed (KHz)"));
	m_spiBitRateSpeedCB = new wxComboBox(m_spiPortSB->GetStaticBox(), wxID_ANY);

	m_fgSizer1->Add(m_spiRecvBuffSizeST);
	m_fgSizer1->Add(m_spiRecvBuffSizeTC);

	m_fgSizer1->Add(m_spiRecvTimeoutST);
	m_fgSizer1->Add(m_spiRecvTimeoutTC);

	m_fgSizer1->Add(m_spiBitRateSpeedST);
	m_fgSizer1->Add(m_spiBitRateSpeedCB);

	m_spiPortSB->Add(m_fgSizer1, wxSizerFlags(1).Expand());

	/* Section 2 */
	m_canRecvBuffSizeST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_canRecvBuffSizeTC = new wxTextCtrl(m_canPortSB->GetStaticBox(), wxID_ANY);

	m_canRecvMSGSizeST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Received Message Size"));
	m_canRecvMSGSizeTC = new wxTextCtrl(m_canPortSB->GetStaticBox(), wxID_ANY);

	m_canRecvTimeoutST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Received Timeout (ms)"));
	m_canRecvTimeoutTC = new wxTextCtrl(m_canPortSB->GetStaticBox(), wxID_ANY);

	m_canBitRateSpeedST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Bit Rate Speed (KHz)"));
	m_canBitRateSpeedCB = new wxComboBox(m_canPortSB->GetStaticBox(), wxID_ANY);

	m_fgSizer2->Add(m_canRecvBuffSizeST);
	m_fgSizer2->Add(m_canRecvBuffSizeTC);

	m_fgSizer2->Add(m_canRecvMSGSizeST);
	m_fgSizer2->Add(m_canRecvMSGSizeTC);

	m_fgSizer2->Add(m_canRecvTimeoutST);
	m_fgSizer2->Add(m_canRecvTimeoutTC);

	m_fgSizer2->Add(m_canBitRateSpeedST);
	m_fgSizer2->Add(m_canBitRateSpeedCB);

	m_canPortSB->Add(m_fgSizer2, wxSizerFlags(1).Expand());

	/* Add elements to topLevelSizer */
	m_topLevelSizer->Add(m_spiPortSB, wxSizerFlags(0).Expand());
	m_topLevelSizer->Add(m_canPortSB, wxSizerFlags(1).Expand());

	this->SetSizerAndFit(m_topLevelSizer);
}

USBSPICANPanel::~USBSPICANPanel(){

}


wxBEGIN_EVENT_TABLE(USBSPICANPanel, wxPanel)

wxEND_EVENT_TABLE()