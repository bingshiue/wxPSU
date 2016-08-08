/**
 * @file USBI2CRS232Panel.cpp
 */

#include "USBI2CRS232Panel.h"

USBI2CRS232Panel::USBI2CRS232Panel(wxWindow* parent) : wxPanel(parent){

	/* Initial Sizer */
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
    m_i2cportSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("I2C Port"));
	m_rs232portSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("RS232 Port"));
	m_fgSizer1 = new wxFlexGridSizer(3, 3, 5, 5);
	m_fgSizer2 = new wxFlexGridSizer(6, 2, 5, 5);

	/* Section 1 */
	m_i2cBitRateST = new wxStaticText(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("Bit Rate Speed (KHz)"));
	m_i2cBitRateCB = new wxComboBox(m_i2cportSB->GetStaticBox(), wxID_ANY);
	m_smbusCheckBox = new wxCheckBox(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("SMBus"));

	m_fgSizer1->Add(m_i2cBitRateST);
	m_fgSizer1->Add(m_i2cBitRateCB);
	m_fgSizer1->Add(m_smbusCheckBox);

	m_commBusTimeoutST = new wxStaticText(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("Comm/Bus Timeout (ms)"));
	m_commBusTimeoutTC1 = new wxTextCtrl(m_i2cportSB->GetStaticBox(), wxID_ANY);
	m_commBusTimeoutTC2 = new wxTextCtrl(m_i2cportSB->GetStaticBox(), wxID_ANY);

	m_fgSizer1->Add(m_commBusTimeoutST);
	m_fgSizer1->Add(m_commBusTimeoutTC1);
	m_fgSizer1->Add(m_commBusTimeoutTC2);

	m_i2cRecvBuffSizeST = new wxStaticText(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_i2cRecvBuffSizeTC = new wxTextCtrl(m_i2cportSB->GetStaticBox(), wxID_ANY);

	m_fgSizer1->Add(m_i2cRecvBuffSizeST);
	m_fgSizer1->Add(m_i2cRecvBuffSizeTC);
	

	m_i2cportSB->Add(m_fgSizer1, wxSizerFlags(1).Expand());

	/* Section 2 */
	m_rs232PortNumberST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Port Number"));
	m_rs232PortNumberCB = new wxComboBox(m_rs232portSB->GetStaticBox(), wxID_ANY);

	m_rs232BuadRateST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Buad Rate"));
	m_rs232BuadRateCB = new wxComboBox(m_rs232portSB->GetStaticBox(), wxID_ANY);

	m_rs232DataBitsST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Data Bits"));
	m_rs232DataBitsCB = new wxComboBox(m_rs232portSB->GetStaticBox(), wxID_ANY);

	m_rs232StopBitsST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Stop Bits"));
	m_rs232StopBitsCB = new wxComboBox(m_rs232portSB->GetStaticBox(), wxID_ANY);

	m_rs232ParityCheckST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Parity Check"));
	m_rs232ParityCheckCB = new wxComboBox(m_rs232portSB->GetStaticBox(), wxID_ANY);

	m_rs232RecvBuffSizeST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_rs232RecvBuffSizeTC = new wxTextCtrl(m_rs232portSB->GetStaticBox(), wxID_ANY);

	m_fgSizer2->Add(m_rs232PortNumberST);
	m_fgSizer2->Add(m_rs232PortNumberCB);

	m_fgSizer2->Add(m_rs232BuadRateST);
	m_fgSizer2->Add(m_rs232BuadRateCB);

	m_fgSizer2->Add(m_rs232DataBitsST);
	m_fgSizer2->Add(m_rs232DataBitsCB);

	m_fgSizer2->Add(m_rs232StopBitsST);
	m_fgSizer2->Add(m_rs232StopBitsCB);

	m_fgSizer2->Add(m_rs232ParityCheckST);
	m_fgSizer2->Add(m_rs232ParityCheckCB);

	m_fgSizer2->Add(m_rs232RecvBuffSizeST);
	m_fgSizer2->Add(m_rs232RecvBuffSizeTC);

	m_rs232portSB->Add(m_fgSizer2, wxSizerFlags(1).Expand());

	/* Add element to topLevelSizer */
	m_topLevelSizer->Add(m_i2cportSB, wxSizerFlags(0).Expand());
	m_topLevelSizer->Add(m_rs232portSB, wxSizerFlags(1).Expand());

	this->SetSizerAndFit(m_topLevelSizer);
}

USBI2CRS232Panel::~USBI2CRS232Panel(){

}


wxBEGIN_EVENT_TABLE(USBI2CRS232Panel, wxPanel)

wxEND_EVENT_TABLE()