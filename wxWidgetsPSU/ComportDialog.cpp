/**
 * @file ComportDialog.cpp
 */

#include "ComportDialog.h"

ComportDialog::ComportDialog(wxWindow *parent, IOACCESS* ioaccess, AppSettings_t* appSettings) : wxDialog(parent, wxID_ANY, wxString(wxT("Com Port"))) {

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(COMPLUG_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_parent = parent;
	m_ioaccess = ioaccess;
	m_appSettings = appSettings;

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
	int select = 0;
	
	// Comport Number
	this->m_appSettings->m_comportSetting.m_comportNumber = wxAtoi(m_ComportNumberCB->GetValue());

	// BuadRate
	select = m_BuadRateCB->GetSelection();

	switch (select){

	case 0:// "110"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_110;
		break;
	case 1:// "300"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_300;
		break;
	case 2:// "600"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_600;
		break;
	case 3:// "1200"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_1200;
		break;
	case 4:// "2400"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_2400;
		break;
	case 5:// "4800"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_4800;
		break;
	case 6:// "9600"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_9600;
		break;
	case 7:// "11400"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_14400;
		break;
	case 8:// "19200"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_19200;
		break;
	case 9:// "38400"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_38400;
		break;
	case 10://"56000"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_56000;
		break;
	case 11://"57600"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_57600;
		break;
	case 12://"115200"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_115200;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	// Byte Size
	this->m_appSettings->m_comportSetting.m_byteSize = wxAtoi(m_DataBitsCB->GetValue());

	// Stop Bits
	select = m_StopBitsCB->GetSelection();

	switch (select){
	case 0 :// "1"
		this->m_appSettings->m_comportSetting.m_stopBits = ONESTOPBIT;
		break;

	case 1: // "1.5"
		this->m_appSettings->m_comportSetting.m_stopBits = ONE5STOPBITS;

		break;

	case 2: // "2"
		this->m_appSettings->m_comportSetting.m_stopBits = TWOSTOPBITS;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	// Parity Size
	select = m_ParityCheckCB->GetSelection();

	switch (select){

	case 0: // "N"
		this->m_appSettings->m_comportSetting.m_parityCheck = NOPARITY;
		break;

	case 1: // "O"
		this->m_appSettings->m_comportSetting.m_parityCheck = ODDPARITY;
		break;

	case 2: // "E"
		this->m_appSettings->m_comportSetting.m_parityCheck = EVENPARITY;
		break;

	case 3: // "M"
		this->m_appSettings->m_comportSetting.m_parityCheck = MARKPARITY;
		break;

	case 4: //"S"
		this->m_appSettings->m_comportSetting.m_parityCheck = SPACEPARITY;
		break;

	default :
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	this->EndModal(0);
}

wxBEGIN_EVENT_TABLE(ComportDialog, wxDialog)
EVT_BUTTON(CID_OK_BUTTOUN, ComportDialog::OnOKButton)
wxEND_EVENT_TABLE()