/**
 * @file I2CIntefaceDialog.cpp
 */

#include "I2CInterfaceDialog.h"

I2CInterfaceDialog::I2CInterfaceDialog(wxWindow *parent, IOACCESS* ioaccess, AppSettings_t* appSettings) : wxDialog(parent, wxID_ANY, wxString(wxT("I2C Interface"))) {
	
	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(HWINFO_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_ioaccess = ioaccess;
	m_appSettings = appSettings;

	m_TopLevelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_LeftSizer = new wxBoxSizer(wxVERTICAL);

	m_i2cIFModuleSBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("I2C Interface Module"));

	m_generalFlexSizer = new wxFlexGridSizer(6,2,5,5);
	m_ButtonSizer = new wxBoxSizer(wxVERTICAL);

	m_moduleNameST = new wxStaticText(m_i2cIFModuleSBS->GetStaticBox(), wxID_ANY, wxT("Module Name"));
	m_moduleNameCB = new wxComboBox(m_i2cIFModuleSBS->GetStaticBox(), wxID_ANY, wxT(""));
	m_moduleNameCB->Append("API2CS12-000");
	m_moduleNameCB->Append("R90000-95611");
	m_moduleNameCB->Append("R90000-9271(USB)");
	m_moduleNameCB->Append("TOTAL PHASE");
	m_moduleNameCB->SetSelection(1);


	m_i2cIFModuleSBS->Add(m_moduleNameST, wxSizerFlags().Align(wxCENTER).Border());
	m_i2cIFModuleSBS->Add(m_moduleNameCB, wxSizerFlags().Align(wxCENTER).Border());

	m_generalNB = new wxNotebook(this, wxID_ANY);
	m_generalPanel = new wxPanel(m_generalNB, wxID_ANY);

	m_RegisterAddrLengthST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Register Addr Length"));
	m_MaxReadBytesST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Max Read Bytes"));
	m_MaxWriteBytesST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Mzx Write Bytes"));
	m_TrasmitTimeoutST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Transmit Timeout (ms)"));
	m_WriteCycleTimeST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Write Cycle Time (ms)"));
	m_PollingCycleTimeST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Polling Cycle Time (ms)"));

	m_RegisterAddrLengthCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_RegisterAddrLengthCB->Append("1");
	m_RegisterAddrLengthCB->Append("2");
	m_RegisterAddrLengthCB->Append("3");
	m_RegisterAddrLengthCB->Append("4");
	m_RegisterAddrLengthCB->SetSelection(0);

	m_MaxReadBytesCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_MaxReadBytesCB->Append("1");
	m_MaxReadBytesCB->Append("4");
	m_MaxReadBytesCB->Append("8");
	m_MaxReadBytesCB->Append("16");
	m_MaxReadBytesCB->Append("32");
	m_MaxReadBytesCB->Append("64");
	m_MaxReadBytesCB->SetSelection(4);

	m_MaxWriteBytesCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_MaxWriteBytesCB->Append("1");
	m_MaxWriteBytesCB->Append("4");
	m_MaxWriteBytesCB->Append("8");
	m_MaxWriteBytesCB->Append("16");
	m_MaxWriteBytesCB->Append("32");
	m_MaxWriteBytesCB->Append("64");
	m_MaxWriteBytesCB->SetSelection(4);

	m_TrasmitTimeoutCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_TrasmitTimeoutCB->Append("100");
	m_TrasmitTimeoutCB->Append("200");
	m_TrasmitTimeoutCB->Append("500");
	m_TrasmitTimeoutCB->Append("1000");
	m_TrasmitTimeoutCB->Append("1500");
	m_TrasmitTimeoutCB->Append("2000");
	m_TrasmitTimeoutCB->SetSelection(1);

	m_WriteCycleTimeCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_WriteCycleTimeCB->Append("0");
	m_WriteCycleTimeCB->Append("5");
	m_WriteCycleTimeCB->Append("10");
	m_WriteCycleTimeCB->Append("15");
	m_WriteCycleTimeCB->Append("20");
	m_WriteCycleTimeCB->Append("30");
	m_WriteCycleTimeCB->SetSelection(2);

	m_PollingCycleTimeCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_PollingCycleTimeCB->Append("0");
	m_PollingCycleTimeCB->Append("5");
	m_PollingCycleTimeCB->Append("10");
	m_PollingCycleTimeCB->Append("20");
	m_PollingCycleTimeCB->Append("50");
	m_PollingCycleTimeCB->Append("100");
	m_PollingCycleTimeCB->Append("200");
	m_PollingCycleTimeCB->Append("300");
	m_PollingCycleTimeCB->Append("500");
	m_PollingCycleTimeCB->Append("1000");
	m_PollingCycleTimeCB->Append("1500");
	m_PollingCycleTimeCB->Append("2000");
	m_PollingCycleTimeCB->SetSelection(3);

	m_generalFlexSizer->Add(m_RegisterAddrLengthST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_RegisterAddrLengthCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxReadBytesST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxReadBytesCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxWriteBytesST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxWriteBytesCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_TrasmitTimeoutST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_TrasmitTimeoutCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_WriteCycleTimeST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_WriteCycleTimeCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_PollingCycleTimeST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_PollingCycleTimeCB, wxSizerFlags().Align(wxCENTER).Border());
	
	m_generalPanel->SetSizer(m_generalFlexSizer);

	m_generalNB->AddPage(m_generalPanel, wxT("General"));

	m_OkButton = new wxButton(this, CID_OK_BUTTOUN, wxT("OK"), wxDefaultPosition, wxSize(80, -1));
	m_CancelButton = new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxSize(80, -1));
	m_ComportButton = new wxButton(this, CID_COMPORT_BUTTOUN, wxT("Comport"), wxDefaultPosition, wxSize(80, -1));
	m_ComportButton->SetBitmap(wxBITMAP_PNG(COMPLUG_16));

	m_USBSettingButton = new wxButton(this, wxID_ANY, wxT("Setting"), wxDefaultPosition, wxSize(80, -1));
	m_USBSettingButton->SetBitmap(wxBITMAP_PNG(USB_16));

	m_ButtonSizer->Add(m_OkButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_CancelButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_ComportButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_USBSettingButton, wxSizerFlags().Align(wxCENTER).Border());

	/* ------------------------------------ */
	m_LeftSizer->Add(m_i2cIFModuleSBS, wxSizerFlags().Expand());
	m_LeftSizer->Add(m_generalNB, wxSizerFlags().Expand());

	m_TopLevelSizer->Add(m_LeftSizer);
	m_TopLevelSizer->Add(m_ButtonSizer);

	// Setup Sizer
	SetSizerAndFit(m_TopLevelSizer);

}

I2CInterfaceDialog::~I2CInterfaceDialog(){

}


void I2CInterfaceDialog::OnOKButton(wxCommandEvent& event){
	this->EndModal(0);
}

void I2CInterfaceDialog::OnComportButton(wxCommandEvent& event){
	ComportDialog* comportDialog = new ComportDialog(this, this->m_ioaccess, this->m_appSettings);
	comportDialog->Centre();
	comportDialog->ShowModal();

	delete comportDialog;
}

wxBEGIN_EVENT_TABLE(I2CInterfaceDialog, wxDialog)
EVT_BUTTON(CID_OK_BUTTOUN, I2CInterfaceDialog::OnOKButton)
EVT_BUTTON(CID_COMPORT_BUTTOUN, I2CInterfaceDialog::OnComportButton)
wxEND_EVENT_TABLE()