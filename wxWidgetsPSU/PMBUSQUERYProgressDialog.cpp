/**
 * @file PMBUSQUERYProgressDialog.cpp
 */

#include "PMBUSQUERYProgressDialog.h"

wxDEFINE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_INTERRUPT, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_END, wxThreadEvent);

PMBUSQUERYProgressDialog::PMBUSQUERYProgressDialog(wxWindow *parent, wxString title, IOACCESS* ioaccess, unsigned int* currentIO) : 
	wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(200,130)){

	// Setup Icon
	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(QUERY_16));

	this->SetIcon(icon);

	// IO Access
	m_ioaccess = ioaccess;
	// Current I/O
	m_currentIO = currentIO;

	// Initialize Sizer
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_statisticsSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Query Commands"));

	// Initialize GUI Component
	m_infoST = new wxStaticText(this->m_statisticsSB->GetStaticBox(), wxID_ANY, wxT("00000/00000"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
	m_okButton = new wxButton(this, CID_BTN_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize);

	// Add GUI Component To Static Box
	m_statisticsSB->Add(this->m_infoST, wxSizerFlags(0).Align(wxALIGN_CENTRE_HORIZONTAL));

	// Add Sizer To Top Level Sizer
	this->m_topLevelSizer->Add(m_statisticsSB, wxSizerFlags(0).Border().Expand());

	this->m_topLevelSizer->Add(m_okButton, wxSizerFlags(0).Border().Align(wxALIGN_CENTRE_HORIZONTAL));

	// Set Sizer
	SetSizer(m_topLevelSizer);
	//SetSizerAndFit(m_topLevelSizer);

	// Set Escape ID
	SetEscapeId(wxID_CLOSE);

}

PMBUSQUERYProgressDialog::~PMBUSQUERYProgressDialog(){

}

bool PMBUSQUERYProgressDialog::Update(int value, const wxString& newmsg, bool *skip){

	bool result = false;

	this->m_infoST->SetLabelText(newmsg);

	return result;

}

void PMBUSQUERYProgressDialog::OnQUERYSequenceUpdate(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnQUERYSequenceUpdate : %d", event.GetInt());

	this->m_infoST->SetLabel(wxString::Format("%3d/%3d", event.GetInt()+1, PMBUSHelper::GetCurrentCMDTableSize()));

}

void PMBUSQUERYProgressDialog::OnQUERYSequenceInterrupt(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnQUERYSequenceInterrupt");

}

void PMBUSQUERYProgressDialog::OnQUERYSequenceEnd(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnQUERYSequenceEnd");

	int HasError = event.GetInt();

	if (HasError == 1){
		PSU_DEBUG_PRINT(MSG_ERROR, "Query Commands Failed ! Please Check PSU Device Status !");
	}

	// Close Dialog
	this->EndModal(wxID_OK);
}

void PMBUSQUERYProgressDialog::OnBtnOK(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnBtnOK");

	this->EndModal(wxID_OK);
}

void PMBUSQUERYProgressDialog::OnDialogClose(wxCloseEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	this->EndModal(wxID_CANCEL);
}

wxBEGIN_EVENT_TABLE(PMBUSQUERYProgressDialog, wxDialog)
EVT_THREAD(wxEVT_COMMAND_QUERY_SEQUENCE_UPDATE, PMBUSQUERYProgressDialog::OnQUERYSequenceUpdate)
EVT_THREAD(wxEVT_COMMAND_QUERY_SEQUENCE_INTERRUPT, PMBUSQUERYProgressDialog::OnQUERYSequenceInterrupt)
EVT_THREAD(wxEVT_COMMAND_QUERY_SEQUENCE_END, PMBUSQUERYProgressDialog::OnQUERYSequenceEnd)
EVT_BUTTON(CID_BTN_OK, PMBUSQUERYProgressDialog::OnBtnOK)
EVT_CLOSE(PMBUSQUERYProgressDialog::OnDialogClose)
wxEND_EVENT_TABLE()