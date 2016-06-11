/**
 * @file ComportDialog.cpp
 */

#include "ComportDialog.h"

ComportDialog::ComportDialog(wxWindow *parent) : wxDialog(parent, wxID_ANY, wxString(wxT("Com Port"))) {

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(COMPLUG_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_parent = parent;

	m_TopLevelSizer = new wxBoxSizer(wxHORIZONTAL);

	m_SettingSBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT(""));
	m_SettingFGS = new wxFlexGridSizer(5,2,5,5);

	m_RightVerticalSizer = new wxBoxSizer(wxVERTICAL);
	m_ButtonSizer = new wxBoxSizer(wxVERTICAL);
	m_CheckBoxSizer = new wxBoxSizer(wxVERTICAL);

	m_ComportNumberST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Comport Number"));
	m_BuadRateST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Buad Rate"));
	m_ParityCheckST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Parity Check"));
	m_DataBitsST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Data Bits"));
	m_StopBitsST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Stop Bits"));

	m_ComportNumberCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100,-1));
	m_ComportNumberCB->Append("1");
	m_ComportNumberCB->Append("2");
	m_ComportNumberCB->Append("3");
	m_ComportNumberCB->Append("4");
	m_ComportNumberCB->Append("5");
	m_ComportNumberCB->Append("6");
	m_ComportNumberCB->Append("7");
	m_ComportNumberCB->Append("8");
	m_ComportNumberCB->SetSelection(0);

	m_BuadRateCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_BuadRateCB->Append("110");
	m_BuadRateCB->Append("300");
	m_BuadRateCB->Append("600");
	m_BuadRateCB->Append("1200");
	m_BuadRateCB->Append("2400");
	m_BuadRateCB->Append("4800");
	m_BuadRateCB->Append("9600");
	m_BuadRateCB->Append("11400");
	m_BuadRateCB->Append("19200");
	m_BuadRateCB->Append("38400");
	m_BuadRateCB->Append("56000");
	m_BuadRateCB->Append("57600");
	m_BuadRateCB->Append("115200");
	m_BuadRateCB->SetSelection(6);


	m_ParityCheckCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_ParityCheckCB->Append("N");
	m_ParityCheckCB->Append("O");
	m_ParityCheckCB->Append("E");
	m_ParityCheckCB->Append("M");
	m_ParityCheckCB->Append("S");
	m_ParityCheckCB->SetSelection(0);


	m_DataBitsCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_DataBitsCB->Append("5");
	m_DataBitsCB->Append("6");
	m_DataBitsCB->Append("7");
	m_DataBitsCB->Append("8");
	m_DataBitsCB->SetSelection(3);

	m_StopBitsCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_StopBitsCB->Append("1");
	m_StopBitsCB->Append("1.5");
	m_StopBitsCB->Append("2");
	m_StopBitsCB->SetSelection(0);

	m_SettingFGS->Add(m_ComportNumberST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_ComportNumberCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_BuadRateST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_BuadRateCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_ParityCheckST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_ParityCheckCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_DataBitsST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_DataBitsCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_StopBitsST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_StopBitsCB, wxSizerFlags().Align(wxCENTER).Border());

	m_SettingSBS->Add(m_SettingFGS);

	m_OKButton = new wxButton(this, CID_OK_BUTTOUN, wxT("OK"));
	m_CancelButton = new wxButton(this, wxID_CLOSE, wxT("Cancel"));

	m_ButtonSizer->Add(m_OKButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_CancelButton, wxSizerFlags().Align(wxCENTER).Border());

	m_paddiingST = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, 50));
	m_TurnOnRTS = new wxCheckBox(this, wxID_ANY, wxT("Turn On RTS"));
	m_TurnOnDTR = new wxCheckBox(this, wxID_ANY, wxT("Turn On DTR"));

	
	m_CheckBoxSizer->Add(m_paddiingST, wxSizerFlags().Border().Align(wxUP));
	m_CheckBoxSizer->Add(m_TurnOnRTS, wxSizerFlags().Border().Align(wxDOWN));
	m_CheckBoxSizer->Add(m_TurnOnDTR, wxSizerFlags().Border().Align(wxDOWN));

	m_RightVerticalSizer->Add(m_ButtonSizer, wxSizerFlags().Align(wxCENTER).Border());
	m_RightVerticalSizer->Add(m_CheckBoxSizer, wxSizerFlags().Align(wxDOWN).Border());

	m_TopLevelSizer->Add(m_SettingSBS, wxSizerFlags().Align(wxCENTER).Expand());
	m_TopLevelSizer->Add(m_RightVerticalSizer, wxSizerFlags(0).Align(wxCENTER).Expand());

	// Setup Sizer
	SetSizerAndFit(m_TopLevelSizer);

	// Setup Escapse ID
	SetEscapeId(wxID_CLOSE);
}

ComportDialog::~ComportDialog(){

}

void ComportDialog::OnOKButton(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

wxBEGIN_EVENT_TABLE(ComportDialog, wxDialog)
EVT_BUTTON(CID_OK_BUTTOUN, ComportDialog::OnOKButton)
wxEND_EVENT_TABLE()